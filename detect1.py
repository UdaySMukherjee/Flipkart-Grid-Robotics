
import csv
import os
import platform
import sys
from pathlib import Path
import cv2
import torch



# Define constants for file paths
FILE = Path(__file__).resolve()  # Get the current script file
ROOT = FILE.parents[0]  # YOLOv5 root directory
if str(ROOT) not in sys.path:
    sys.path.append(str(ROOT))  # Add YOLOv5 root directory to the Python path
ROOT = Path(os.path.relpath(ROOT, Path.cwd()))  # Make ROOT path relative

# Import necessary modules and functions from YOLOv5 codebase
from ultralytics.utils.plotting import Annotator, colors, save_one_box
from models.common import DetectMultiBackend
from utils.dataloaders import IMG_FORMATS, VID_FORMATS, LoadImages, LoadScreenshots, LoadStreams
from utils.general import (
    LOGGER, Profile, check_file, check_img_size, check_imshow, check_requirements, colorstr, cv2,
    increment_path, non_max_suppression, print_args, scale_boxes, strip_optimizer, xyxy2xywh)
from utils.torch_utils import select_device, smart_inference_mode

@smart_inference_mode()
def run(
        weights= ROOT / 'last.pt',  # Model weights path or Triton URL
        source=1,  # Source for inference (file, dir, URL, webcam, etc.)
        data=ROOT / 'data/coco128.yaml',  # Dataset configuration path
        imgsz=(640, 640),  # Inference image size (height, width)
        conf_thres=0.25,  # Confidence threshold for detection
        iou_thres=0.45,  # NMS (Non-Maximum Suppression) IOU threshold
        max_det=1000,  # Maximum detections per image
        device='',  # Device for inference (CPU or GPU)
        view_img=False,  # Show results
        classes=None,  # Filter by class
        agnostic_nms=False,  # Class-agnostic NMS
        augment=False,  # Augmented inference
        visualize=False,  # Visualize features
        update=False,  # Update all models
        project=ROOT / 'runs/detect',  # Save results to project directory
        name='exp',  # Save results with this name
        exist_ok=False,  # Existing project/name is ok, do not increment
        line_thickness=3,  # Bounding box thickness (pixels)
        hide_labels=False,  # Hide labels
        hide_conf=False,  # Hide confidences
        half=False,  # Use FP16 half-precision inference
        dnn=False,  # Use OpenCV DNN for ONNX inference
        vid_stride=1,  # Video frame-rate stride
):
    source = str(source)

    # Determine if the source is a file, URL, webcam, or screenshot
    is_file = Path(source).suffix[1:] in (IMG_FORMATS + VID_FORMATS)
    is_url = source.lower().startswith(('rtsp://', 'rtmp://', 'http://', 'https://'))
    webcam = source.isnumeric() or source.endswith('.streams') or (is_url and not is_file)
    screenshot = source.lower().startswith('screen')
    if is_url and is_file:
        source1 = check_file(source)  # Download the source if it's a URL

    # Load model
    device = select_device(device)  # Select the specified device (CPU or GPU)
    model = DetectMultiBackend(weights, device=device, dnn=dnn, data=data, fp16=half)  # Load the YOLOv5 model
    stride, names, pt = model.stride, model.names, model.pt
    imgsz = check_img_size(imgsz, s=stride)  # Check and adjust the image size for the model

    # Determine batch size based on the source (webcam or other)
    bs = 1  # Batch size
    if webcam:
        view_img = check_imshow(warn=True)  # Check if image display is supported
        dataset = LoadStreams(source, img_size=imgsz, stride=stride, auto=pt, vid_stride=vid_stride)
        bs = len(dataset)  # Batch size is the number of streams when using webcam
    elif screenshot:
        dataset = LoadScreenshots(source, img_size=imgsz, stride=stride, auto=pt)
    else:
        dataset = LoadImages(source, img_size=imgsz, stride=stride, auto=pt, vid_stride=vid_stride)
    vid_path, vid_writer = [None] * bs, [None] * bs  # Initialize variables for video handling

    # Warm up the model with an initial image
    model.warmup(imgsz=(1 if pt or model.triton else bs, 3, *imgsz))

    # Initialize variables for counting processed images and measuring time
    seen, windows, dt = 0, [], (Profile(), Profile(), Profile())

    # Iterate through the dataset and perform inference
    for path, im, im0s, vid_cap, s in dataset:
        with dt[0]:
            im = torch.from_numpy(im).to(model.device)  # Convert image to PyTorch tensor
            im = im.half() if model.fp16 else im.float()  # Convert to FP16 if specified
            im /= 255  # Normalize image pixel values to the range [0, 1]
            if len(im.shape) == 3:
                im = im[None]  # Add a batch dimension if the image is not batched

        # Perform inference
        with dt[1]:
            pred = model(im, augment=augment, visualize=visualize)

        # Apply Non-Maximum Suppression (NMS) to filter detections
        with dt[2]:
            pred = non_max_suppression(pred, conf_thres, iou_thres, classes, agnostic_nms, max_det=max_det)

        # Create or append to a CSV file to store detection results
        def write_to_csv(image_name, prediction, confidence):
            data = {'Image Name': image_name, 'Prediction': prediction, 'Confidence': confidence}
            with open(csv_path, mode='a', newline='') as f:
                writer = csv.DictWriter(f, fieldnames=data.keys())
                if not csv_path.is_file():
                    writer.writeheader()
                writer.writerow(data)

        # Process predictions
        for i, det in enumerate(pred):  # Per image
            seen += 1
            if webcam:  # When batch_size >= 1
                p, im0, frame = path[i], im0s[i].copy(), dataset.count
                s += f'{i}: '
            else:
                p, im0, frame = path, im0s.copy(), getattr(dataset, 'frame', 0)

            s += '%gx%g ' % im.shape[2:]  # Print image size
            gn = torch.tensor(im0.shape)[[1, 0, 1, 0]]  # Normalization gain (width, height, width, height)
            imc = im0.copy()  # Make a copy of the original image for saving crops
            annotator = Annotator(im0, line_width=line_thickness, example=str(names))  # Initialize annotator
            if len(det):
                
                # Rescale boxes from img_size to im0 size
                det[:, :4] = scale_boxes(im.shape[2:], det[:, :4], im0.shape).round()
                # print(det)

                # Print detection results
                for c in det[:, 5].unique():
                    n = (det[:, 5] == c).sum()  # Count detections per class
                    # print(132,names[int(c)])
                    s += f"{n} {names[int(c)]}{'s' * (n > 1)}, "  # Add class count to the string

                # Write results to CSV and visualize if specified
                for *xyxy, conf, cls in reversed(det):
                    point = []
                    for i in xyxy:
                        # print(type(i))
                        point.append(int(i))

                    x_mid = point[0] +point[2]
                    y_mid = point[1] +point[3]
                    # center = ( torch.tensor(x_mid, dtype=torch.int), torch.tensor(y_mid, dtype=torch.int)) 
                    center = (x_mid, y_mid)

                    # print(147,xyxy)

                    c = int(cls)  # Integer class
                    label = names[c] if hide_conf else f'{names[c]}'  # Class label
                    confidence = float(conf)
                    if( confidence <0.5 and (c == 0 or c == 1 or c ==2)):
                        continue
                    if(round(confidence) >=0.5 and (c == 1)):
                        print("QR DETECTED")
                    
                    confidence_str = f'{confidence:.2f}'  # Confidence score as a string
                    s += confidence_str + ' '

                    if view_img:  # Add bounding box and label to the image
                        c = int(cls)  # Integer class
                        label = None if hide_labels else (names[c] if hide_conf else f'{names[c]} {conf:.2f}')
                        annotator.box_label(xyxy, label, color=colors(c, True))
                        # annotator.kpts(kpts=center, radius=1)

            # Stream results
            im0 = annotator.result()
            # cv2.circle(im0, center, 10, (100,100,100), -1)
            if view_img:
                if platform.system() == 'Linux' and p not in windows:
                    windows.append(p)
                    cv2.namedWindow(str(p), cv2.WINDOW_NORMAL | cv2.WINDOW_KEEPRATIO)  # Allow window resize (Linux)
                    cv2.resizeWindow(str(p), im0.shape[1], im0.shape[0])
                cv2.imshow(str(p), im0)
                cv2.waitKey(1)  # Wait for a key press for 1 millisecond

        # Print processing time for the current image
        LOGGER.info(f"{s}{'' if len(det) else '(no detections), '}{dt[1].dt * 1E3:.1f}ms")

    # Print processing speed (pre-process, inference, NMS) per image
    t = tuple(x.t / seen * 1E3 for x in dt)
    LOGGER.info(f'Speed: %.1fms pre-process, %.1fms inference, %.1fms NMS per image at shape {(1, 3, *imgsz)}' % t)

    if update:
        strip_optimizer(weights[0])  # Update the model (to fix SourceChangeWarning)

# Hyperparameter Tuning
weight_path = "C:\\Users\\UDAY SANKAR\\Desktop\\yolov5\\last.pt"

if __name__ == '__main__':
    run(weights=weight_path, source=1)
