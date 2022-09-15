# CLI_OpenAPI_Weather_Project
- 목표 : 오픈 API 날씨데이터를 활용한 CLI 프로그램  
(Rest API, Curl 등의 지식들 습득)  

- 사용 예정 외부 Library  
  - json-c : c언어에서 json 파일 parsing을 위해서 사용  
  - API : OpenWeatherMap API  

## REST API란 ?
인터넷과 웹을 통해서 나의 컴퓨터를 제어할 때의 해결책  
Request, Response를 주고 받으며 Header, Body 정보로 데이터를 구분한다  
- Request Method  
  - CRUD (Create, Read, Update, Delete) --  
    - 1. Create = POST  
    - 2. Read = GET  
    - 3. Update = PUT | PATCH  
    - 4. Delete = DELETE  
- Status Code  
    - 1. 200번대 : 성공  
    - 2. 300번대 : Redirection(추가조치필요)  
    - 3. 400번대 : 클라이언트 오류  
    - 4. 500번대 : 서버 오류  

## Curl 이란 ? 
curl은 command line 또는 script에서 데이터 전송을 위해 사용하는 라이브러리이다  
HTTP, FTP 등 다양한 통신 프로토콜을 지원하며 SSL 인증 방식 역시 사용 가능하다  
- 두 가지 모두 GET 요청으로 조회하는 curl 명령어이다  
`curl http://localhost:8080`  
`curl --include --request GET 'http://localhost:8080'`  

- 서버에 Request 한 후, Response에서 Header 정보를 제외한 json 값만 찾는다  
```curl -H "Accept: application/json" --request GET 'https://api.openweathermap.org/data/2.5/weather?q={CITY_NAME}&appid={SECRET_KEY}'```  

## json-c lib 사용법 
- 설치방법  
  - `sudo apt-get install libjson-c-dev`  

- 컴파일 방법  
  - `gcc -o test test.c -ljson-c`  

- Lib 구조
JSON 구조는 크게 Object 는 { } 로 구분 key-value 쌍으로 이루어진다  
값으로 Object, Array, String, Number, Boolean 등이 올 수 있다  
- 라이브러리 주요 구조체 및 함수  
  - 1 구조체  
    - json_object  
    ```
    struct json_object
    {
      enum json_type o_type
      json_object_private_delete_fn * _delete
      json_object_to_json_string_fn * _to_json_string
      int _ref_count
      struct printbuf * _pb
      union json_object::data o
      json_object_delete_fn _user_delete
      void * _userdata
    }
    ````
    
  - 2 함수  
    - json_object_get_type : 객체의 유형 가져오기 
    - json_object_foreach : 모든 json 객체 탐색
    - json_object_is_type : json_object의 타입 확인
    - json_object_get_boolean : 객체의 bool 값 가져오기
    - json_object_get_int : 객체의 정수 값 가져오기 
    - json_object_get_string : 객체의 문자열 값 가져오기 
    - json_object_new_object : 새로운 json 객체 생성 
    - json_object_new_int : 새로운 정수형 json 객체 생성 
    - json_object_new_boolean : 새로운 boolean json 객체 생성 
    - json_object_new_string : 새로운 문자형 json 객체 생성 
    - json_object_new_double : 새로운 dobule형 json 객체 생성 
    - json_object_new_array : 새로운 배열형 json 객체 생성 
    - json_object_array_add : 배열에 json 객체 추가 
    - json_object_array_put_idx : 저장된 인덱스의 배열에 json 객체 추가  
  - 3 enum json_type
    - json_type_null
    - json_type_boolean
    - json_type_double
    - json_type_int
    - json_type_object
    - json_type_array
    - json_type_string
- 관련 사이트  
https://linuxprograms.wordpress.com/2010/05/20/json-c-libjson-tutorial/

## OpenWeatherMap API 사용법  
OpenWeatherMap 사이트 회원가입 후 인증키 발급받고 API 공식문서 대로 진행  
- 참고 사이트  
https://openweathermap.org/current

## 리눅스 사용하기 좋은 명령어 
- `grep` :  특정 단어 찾기  
```history | grep "curl"```  
- `>` : 명령어 실행 결과 저장하기  
```ls > result.txt```

## 현재 상황
