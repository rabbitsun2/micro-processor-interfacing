## 2_Raspberry Pi 4B - Camera Based (self-driving-car) Open Project

##### 1. Author: Doyun Jung(정도윤)
##### 2. Created Date(작성일자): 2022-07-09 (Last Modified: 2022-07-09)
##### 3. Description(설명): 
##### [한글(Korean)]
##### - 3.1. 1단계: RaspberryPi 4B에서 opencv_no_fillter_scarp_car.py로 사진 데이터를 수집한다.
#####   (선행 조건: /home/pi/AI_CAR/video, /home/pi/AI_CAR/model 폴더를 만들어준다.)
#####   (양방향으로 각각 1바퀴씩 수집한다.)
##### - 3.2. 2단계 - 학습 모델 생성
##### - 3.3. 2-1단계: PC에서 VScode 또는 spyder로 python을 실행한다. 
##### - 3.4. 2-2단계: car_create_model.py의 소스코드에서 폴더 경로를 수정해준다.
##### - 3.5. 2-3단계: 학습을 시켜준다.
##### - 3.6. val_loss값이 80~220 이내가 될 수 있도록 한다.
##### - 3.7. 3단계 - 학습 모델 h5파일 to 라즈베리파이4로 이동하여 실행하기
##### - 3.8. 3-1단계: 라즈베리파이에서 opencv_no_fillter_go_car.py 파일을 연다.
##### - 3.9. 3-2단계: h5파일이 /home/pi/AI_CAR/model 내에 존재할 수 있도록 이동해준다.
##### - 3.9. 3-3단계: python 파일을 실행해준다.
#####
##### [English]
##### - 3.1. Step 1: Collect photo data from RaspberryPi 4B with opencv_no_fillter_scarp_car.py.
#####           (Prerequisite: Create the /home/pi/AI_CAR/video, /home/pi/AI_CAR/model folders.)
#####           (Collect 1 lap in each direction.)
##### - 3.2. Step 2 - Create the training model
##### - 3.3. Step 2-1: Run python with VScode or spyder on your PC.
##### - 3.4. Step 2-2: Modify the folder path in the source code of car_create_model.py.
##### - 3.5. Step 2-3: Let them learn.
##### - 3.6. Make sure that the val_loss value is within 80-220.
##### - 3.7. Step 3 - Go to the training model h5 file to Raspberry Pi 4 and run it
##### - 3.8. Step 3-1: Open the opencv_no_fillter_go_car.py file on the Raspberry Pi.
##### - 3.9. Step 3-2: Move the h5 file so that it exists in /home/pi/AI_CAR/model.
##### - 3.9. Step 3-3: Execute the python file.
##### 4. Movie(영상): 
##### - 4.1. 220613 - RaspberryPi 4 - 자율주행자동차 (1차 실험) (실패), Accessed by 2022-07-09, Last Modified 2022-07-09, https://www.youtube.com/watch?v=fqQK9EIGQZo
##### - 4.2. 220613 - RaspberryPi 4 - 자율주행자동차 (2차 실험) (실패), Accessed by 2022-07-09, Last Modified 2022-07-09, https://www.youtube.com/watch?v=KyAEheWJWKg
##### - 4.3. 220613 - RaspberryPi 4 - 자율주행자동차 (3차 실험) (실패), Accessed by 2022-07-09, Last Modified 2022-07-09, https://www.youtube.com/watch?v=MYGFmWCGTEQ
##### - 4.4. 220613 - RaspberryPi 4 - 자율주행자동차 (4차 실험) (실패), Accessed by 2022-07-09, Last Modified 2022-07-09, https://www.youtube.com/watch?v=4Nej4thnHOk
##### - 4.5. 220707 - RaspberryPi4 - 자율주행 학습 태스트 영상(1부 - 정방향), Accessed by 2022-07-09, Last Modified 2022-07-09, https://www.youtube.com/watch?v=eU_9iToHMPU
##### - 4.6. 220707 - RaspberryPi4 - 자율주행 학습 태스트 영상(2부 - 역방향), Accessed by 2022-07-09, Last Modified 2022-07-09, https://www.youtube.com/watch?v=3F--r0VXg68
##### - 4.7 220708 - RaspberryPi4 - 자율주행 학습 태스트 영상(트랙: 테이프) (정방향 주행), Accessed by 2022-07-09, Last Modified 2022-07-09, https://www.youtube.com/watch?v=SQ4YL3CI6io
##### 5. System information (Raspberry Pi 4B)
##### - OS Platform and Distribution: Debian Linux 11, raspberry pi 4 64bit (Bullseyes, 2022-05)
##### - TensorFlow backend (yes / no): yes
##### - TensorFlow version: 2.90
##### - Keras version: 2.90
##### - Python version: 3.9.2
##### 6. References(참고자료): 
##### - 1. Raspberry Pi(라즈베리파이) 4, https://www.raspberrypi.org
##### - 2. End-to-End Lane Navigation via Nvidia Model, Accessed by 2022-07-09, Last Modified 2022-07-09, https://github.com/dctian/DeepPiCar/blob/master/models/lane_navigation/code/end_to_end_lane_navigation.ipynb, (참고 내용으로 pc에서 모델 학습에 사용한 python 코드는 해당 프로젝트에서 참고하였음)
#####       (For reference, the python code used for model training on PC was referenced in the project)
