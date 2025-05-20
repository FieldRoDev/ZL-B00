# ZL_B00(KINCO MOTOR&DRIVER) 시리즈 구동모듈 CANOPEN 프로토콜 제어 시스템
---
## 시스템 구성
### 주요 파일 구조
|파일명|설명|
|-----|---|
|main.cpp|ROS 초기화 및 CLI 명령 루프 처리|
|ZL_B.cpp|주행 및 조향 모터 제어를 포함한 상위 로직 관리|
|ZL_B_traction.cpp|주행 모터 제어 명령 처리|
|ZL_B_steer.cpp|조향 모터 제어 명령 처리|
|canopen.cpp|CANOPEN 프로토콜 메세지 송수신 처리|
### ROS 토픽
|토픽|타입|설명|
|----|---|---|
|/can0/rx|can_msgs/Frame|수신된 CAN 프레임|
|/can0/tx|can_msgs/Frame|송신된 CAN 프레임|
|/pdo/tx|ZL_B00/pdo_tx_msgs|/can0/rx에서 파싱된 메세지|
---
## 사용 방법
### 명령어 목록
|명령어|기능|
|---|---|
|zlb stop|모든 모터 정지|
