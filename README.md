# 🌈종합프로젝트 7조   

종합프로젝트를 위해 만들어진 레퍼지토리 입니다  
----------------
## 프로젝트 배경 + 목적
>현재 사회에서의 드론을 사용하는 사람이 점점 늘고 있고 거기에 대해 늘어나느 드론수를 제어할 수 있는 드론 관제 시스템이 필요해 질 것이다. 그것을 생각해 보았을 때 드론의 위치를 받고 그 위치를 저장해와서 그 경로에 겹치지 않게 관제 모니터링을 할 수 있는 프로그램을 만들어 더 편리한 드론 및 무인이동체에 대한 교통관제를 할 수 있게 기여할 것입니다.  
>이 프로그램은 기본적으로 Qt와 안드로이드 스튜디오를 사용하며, 다른 곳에서 가져온 구글 api 및 클라우드를 이용한 아마존 서버를 이용하며 사용하는 프로토콜은 mqtt입니다.  
----------------
## 기본적인 환경 셋팅법
--------------
>[Qt 다운로드](https://www.qt.io/download)(필자가 사용한 버전은 5.15.2이며 현재 프로그래밍 하는 모든 것들은 이 버전을 기준으로 작성됩니다.)  
>[안드로이드 스튜디오 설치](https://developer.android.com/studio?hl=ko&gclsrc=aw.ds&gclid=CjwKCAjw7p6aBhBiEiwA83fGurLAt9bAn2gd_q->M7j7MqdHcVeZE54WhXfpIzDQcTi40DapoUSBb1xoClM8QAvD_BwE)  
>[비주얼 스튜디오 설치](https://visualstudio.microsoft.com/ko/downloads/)(필자는 2019버전으로 진행하였으며 비주얼 스튜디오는 본인이 원하는 버전으로 사용하면 된다.)  

#### Qt 설치시 반드시 Qt chart와 msvc 2019(본인이 설치한 비주얼 스튜디오의 버전)는 설치한다.  

>서버를 가동하기 위해 [aws](https://aws.amazon.com/ko/)홈페이지로 들어가 회원가입 및 가상서버 EC2를 구축하며 [sdk](https://aws.amazon.com/ko/sdk-for-cpp/)를 본인의 컴퓨터/서버로 사용될 기기/하드웨어에 설치합니다.  
>만약 서버가 있다면 위 EC2구축은 하지 않아도 됩니다.  
>그 후 aws-sdk-cpp빌드 후 설치한 다음 모듈/라이브러리를 qt로 가져오며 헤더파일로 포함 시킨 후 사용합니다.  
#### 이곳에 있는 코드들은 기본적으로 sdk를 설치 한 하드웨어/기기에서 작성된 것이며 다른 기기에서는 sdk가 없기 때문에 호환되지 않는다는 것을 명심해주시길 바랍니다.  
--------------------------------
