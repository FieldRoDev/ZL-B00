# **ZL_B00(KINCO MOTOR&DRIVER) 시리즈 구동모듈 CANOPEN 프로토콜 제어 시스템**
### 주요 파일 구조
|파일명|설명|
|---|---|
|main.cpp|ROS 초기화 및 CLI 명령 루프 처리|
|ZL_B.cpp|주행 및 조향 모터 제어를 포함한 상위 로직 관리|
|ZL_B_traction.cpp|주행 모터 제어 명령 처리|
|ZL_B_steer.cpp|조향 모터 제어 명령 처리|
|canopen.cpp|CANOPEN 프로토콜 메세지 송수신 처리|
### ROS 토픽
|토픽|타입|설명|
|---|---|---|
|/can0/rx|can_msgs/Frame|수신된 CAN 프레임|
|/can0/tx|can_msgs/Frame|송신된 CAN 프레임|
|/pdo/tx|ZL_B00/pdo_tx_msgs|/can0/rx에서 파싱된 메세지|
### 명령어 목록
|명령어|기능|
|---|---|
|zlb stop|모든 모터 정지|
|zlb reset|모든 모터 리셋|
|zlb traction |stop|주행 모터 정지|
|zlb traction |velmode|주행 모터를 속도 제어 모드로 설정|
|zlb traction |set rpm=100|주행 모터 속도 설정|
|zlb traction |run|설정된 속도로 주행 모터 구동|
|zlb steer stop|조향 모터 정지|
|zlb steer posmode|조향 모터를 속도 제어 모드로 설정|
|zlb steer origin|조향 모터를 원점 위치로 구동|
|zlb steer set rpm=100|조향 모터 속도 설정|
|zlb steer set pos=100|조향 모터 타겟 위치 설정|
|zlb steer set rpm=100 pos=100|조향 모터 속도 및 타겟 위치 설정|
|zlb steer run abs|조향 모터 타겟 위치를 절대위치로 구동|
|zlb steer run inc|조향 모터 타겟 위치를 상대위치로 구동|
