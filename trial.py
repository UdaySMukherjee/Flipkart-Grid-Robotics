import numpy as np
import cv2
from detect import run
def trial():
    video_capture_0 = cv2.VideoCapture(0)
    # print(type(video_capture_0))
    while True:
        ret0,frame0 = video_capture_0.read()

        
        run(source=0)
            
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
        
    video_capture_0.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    trial()

