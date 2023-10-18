import numpy as np
import cv2
from detect import run
def test():
    video_capture_1 = cv2.VideoCapture(1)
    # print(type(video_capture_1))
    while True:
        ret0,frame0 = video_capture_1.read()

        
        run(source=0)
            
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
        
    video_capture_1.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    test()

