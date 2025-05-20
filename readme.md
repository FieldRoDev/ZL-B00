ZL_B00 CANopen Motor Control System

1. 개요

BLV 명종 모터를 ROS 바탕에서 CANopen 토픽까지 연결하여 위치/속도 및 조건 저지 가능한 키워드 인터페이스 구현

작업자 컨설러 메시지 입/출력을 통해 모터 지정 가능

2. 시스템 구조

2.1 함수

main.cpp : 초기화하고 사용자 입력을 받아 모든 명령을 통지

ZL_B.cpp : 다중 모터 구조(traction, steer) 등의 관리 기능 구현

ZL_B_traction, ZL_B_steer : CANopen 로 전력 및 속도/위치 명령 전발

canopen.cpp : can0 및 pdo 토픽에 대해 pub/sub 구현

2.2 통신 구조

최소 can0 전역을 통해 BLV 모터와 연결

/can0/rx 수신 구도에서 pdo_tx_msgs로 다시 그룹하여 /pdo/tx 토픽에 pub

3. ROS 토픽 정의

/can0/rx : CAN 수신 frame

/can0/tx : CAN 보낸 frame (SDO, NMT)

/pdo/tx : DLC == 4인 PDO 바이트를 id + data로 그룹한 상품 토픽

4. 명령어 포맷 (main loop)

명령

목적

zlb stop

명령으로 모든 모터 stop 명령 전발

zlb reset

모든 모터 reset SDO 명령 전발

zlb traction velmode

traction motor를 속도 명령 방식으로 설정

zlb traction set rpm:100

traction motor에 진정적인 속도를 set

zlb traction run

set한 속도로 run 명령 전발

zlb steer posmode

steering 모드의 position mode 설정

zlb steer set rpm:200 pos:1000

position speed 및 absolute position 설정

zlb steer run abs

absolute position로 run

zlb steer run inc

incremental position로 run

finish

로시 다 종료
