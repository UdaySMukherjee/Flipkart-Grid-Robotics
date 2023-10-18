from test import test
from trial import trial
def run():
    test()
    trial()

# ... (the rest of the code remains the same)

if __name__ == '__main__':
    run()

# import numpy as np
# import cv2

# video_capture_0 = cv2.VideoCapture(0)
# video_capture_1 = cv2.VideoCapture(1)

# while True:
#     ret0,frame0 = video_capture_0.read()
#     ret1,frame1 = video_capture_1.read()
    
#     if(ret0):
#         cv2.imshow("Cam0",frame0)
#     if(ret1):
#         cv2.imshow("Cam1",frame1)
        
#     if cv2.waitKey(1) & 0xFF == ord('q'):
#         break
    
# video_capture_0.release()
# video_capture_1.release()
# cv2.destroyAllWindows()