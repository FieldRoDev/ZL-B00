ZL_B00: CANopen 모터 제어 시스템

🧭 개요

ZL_B00은 ROS 기반의 BLV Series R형 모터 제어 시스템으로, CANopen 통신을 통해 차동 구동 로봇의 위치 및 속도를 정밀하게 제어할 수 있도록 설계되었습니다.

🛠️ 시스템 구성

🧩 주요 파일 구조

파일명

설명

main.cpp

ROS 초기화 및 CLI 명령 루프 처리

ZL_B.cpp

트랙션 및 스티어링 모듈 제어를 포함한 상위 로직 관리

ZL_B_traction, ZL_B_steer

모터를 위한 SDO/PDO 제어 명령 처리

canopen.cpp

ROS 토픽을 통한 CAN 메시지 송수신 처리

🔗 ROS 토픽

토픽

타입

설명

/can0/rx

can_msgs/Frame

수신된 CAN 프레임

/can0/tx

can_msgs/Frame

송신할 CAN 프레임 (예: NMT, SDO)

/pdo/tx

ZL_B00/pdo_tx_msgs

/can0/rx에서 파싱된 DLC 4바이트 PDO 메시지

💻 사용 방법

🔡 명령어 목록

명령어

기능

zlb stop

모든 모터 정지

zlb reset

모든 모터 리셋 (SDO 리셋 명령 전송)

zlb traction velmode

트랙션 모터를 속도 제어 모드로 설정

zlb traction set rpm:100

트랙션 모터 속도 설정

zlb traction run

설정된 속도로 트랙션 모터 실행

zlb steer posmode

스티어링 모터를 위치 제어 모드로 설정

zlb steer set rpm:200 pos:1000

스티어링 속도 및 목표 위치 설정

zlb steer run abs

절대 위치로 스티어링 실행

zlb steer run inc

상대 위치로 스티어링 실행

finish

프로그램 종료

🧪 예시

zlb traction velmode
zlb traction set rpm:150
zlb traction run

🛑 안전한 종료 방식

finish 명령 입력 시:

메인 루프 종료

ZL_B 객체 소멸자 호출 → ros::shutdown() 실행

각 모듈에서 다음 항목들을 반드시 호출:

_spinner->stop()

subscriber.shutdown()

ros::waitForShutdown() 은 사용하지 않는 것이 안정적임

📁 의존 패키지

ROS Melodic

필수 ROS 패키지:

can_msgs, socketcan_bridge, ros_canopen

std_msgs, message_generation

📷 시스템 아키텍처



📝 라이선스

MIT

👤 유지보수자

조태희

GitHub 또는 프로젝트 채널을 통해 문의

