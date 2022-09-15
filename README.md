# CLI_OpenAPI_Weather_Project
- 목표 : 오픈 API 날씨데이터를 활용한 CLI 프로그램  
(Rest API, Curl 등의 지식들 습득)  

- 사용 예정 외부 Library  
json-c : c언어에서 json 파일 parsing을 위해서 사용  
API : OpenWeatherMap API  
## REST API란 ?
인터넷과 웹을 통해서 나의 컴퓨터를 제어할 때의 해결책  
Request, Response를 주고 받으며 Header, Body 정보로 데이터를 구분한다  
- Request Method  
-- CRUD (Create, Read, Update, Delete) --  
Create = POST  
Read = GET  
Update = PUT | PATCH  
Delete = DELETE  
- Status Code  
200번대 : 성공  
300번대 : Redirection(추가조치필요)  
400번대 : 클라이언트 오류  
500번대 : 서버 오류  
## Curl 이란 ? 
curl은 command line 또는 script에서 데이터 전송을 위해 사용하는 라이브러리이다  
HTTP, FTP 등 다양한 통신 프로토콜을 지원하며 SSL 인증 방식 역시 사용 가능하다  
- 두 가지 모두 GET 요청으로 조회하는 curl 명령어이다  
`curl http://localhost:8080`  
`curl --include --request GET 'http://localhost:8080'`  

- 서버에 Request 한 후, Response에서 Header 정보를 제외한 json 값만 찾는다  
```curl -H "Accept: application/json" --request GET 'https://api.openweathermap.org/data/2.5/weather?q=seoul&appid=89c7e8b990973c2078cdf69c21117339'```  

## json-c lib 사용법 
- 설치방법  
sudo apt-get install libjson-c-dev  

- 컴파일 방법  
gcc -o test test.c -ljson-c  

- Lib 구조
JSON 구조는 크게 Object 는 { } 로 구분 key-value 쌍으로 이루어진다  
값으로 Object, Array, String, Number, Boolean 등이 올 수 있다  

## OpenWeatherMap API 사용법  

## 리눅스 사용하기 좋은 명령어 
- grep  
```history | grep "curl"```
