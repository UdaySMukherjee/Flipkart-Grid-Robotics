# Pick and Place Robot with QR Recognition

## Overview

This ReadMe provides an overview of a Pick and Place robot system designed to automate the process of picking up parcels, checking for QR codes, and placing them at their final destination with the QR code facing upwards. The system utilizes the YOLOv5 model for object recognition, a custom dataset, and two cameras for the entire process.

## System Components

### 1. YOLOv5 Object Recognition

We have integrated the YOLOv5 model for object recognition, which is capable of detecting various objects within our custom dataset. The custom dataset includes boxes, QR codes, and final destination markers. The YOLOv5 model identifies the presence and locations of these objects.

### 2. Dual Cameras

#### a. Top Camera

A top-mounted camera is responsible for detecting the presence of boxes, QR codes, and destination markers. It captures an overhead view of the workspace and provides crucial information for object recognition and navigation.

#### b. Side Camera

The side-mounted camera is used to detect QR codes on the sides of parcels. This camera is positioned near a rotating plate, allowing it to capture the QR codes' location when the parcels are in a specific orientation.

## Operation

The system operates as follows:

1. **Object Detection:** The top camera continuously captures images and feeds them to the YOLOv5 model. The model identifies the presence and locations of boxes, QR codes, and destination markers in real-time.

2. **QR Code Recognition:** After detecting a parcel (box), the system automatically identifies the QR code. The process is designed to be quick and efficient, ensuring that the QR code is found in a single iteration.

3. **Destination Determination:** The system uses the information obtained from the top camera to determine the final destination for the parcel based on the detected markers.

4. **Pick and Place:** The robot's arm picks up the parcel, ensuring the QR code faces upwards, and transports it to the determined final destination. The side camera can be used to confirm the correct orientation of the QR code.

## Usage

This system is designed for automated pick-and-place operations, making it suitable for various logistics and warehousing applications. It can be controlled via software interfaces or programmable logic controllers (PLCs) depending on your specific requirements.

## Dependencies

To run the system, you will need the following:

- YOLOv5 model with the custom dataset.
- Robotic arm or similar automation hardware.
- Top and side cameras.
- Appropriate control and communication interfaces for robot control.

## Installation and Configuration

1. Install and configure the YOLOv5 model with the custom dataset for object recognition.

2. Set up the cameras and ensure they are calibrated correctly to provide a clear view of the workspace.

3. Integrate the robotic arm or automation hardware and configure it for pick-and-place operations.

4. Implement the necessary software for system control and communication.

## Acknowledgments

This project was made possible by the hard work and dedication of our team. We extend our gratitude to the developers of YOLOv5 and the creators of the custom dataset.

## Contact

For any questions, suggestions, or inquiries, please contact us at [udaysankar2003@gmail.com](mailto:udaysankar2003@gmail.com).

Thank you for using our Pick and Place Robot with QR Recognition system. We hope it streamlines your logistics and warehousing operations and improves efficiency.

