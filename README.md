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

- curl 옵션 정리 (curl --help 를 사용하시오)
  - 1. -d --data : POST request로 특정 데이터를 보낼 때 사용한다  
  - 2. -H --header : request에 함께 제공되는 Headers 정보를 포함한다  
  - 3. -X --request : POST,GET,PUT,DELETE 등 request method를 사용하기 위함  
  - 4. -l : 헤더만 가져오기  
  - 5. -i : 헤더와 바디까지 가져오기  
  - 6. -F : 파일 업로드  
  - 7. -u : 인증  
  - 8. -L : Redirect  
  - 9. -U : 프록시 인증  
  - 10. -u : Authentication  
  - 11. -e : Referer 지정  
  - 12. -b : Cookies  
  - 13. -A : User Agent 지정  
  - 14. -t : telnet 등 
  - 15. -o : output 파일명 저장 
  - 16. jq : json 처리 
- debug  
  ```
  curl --trace-ascii debug.dump http://google.com
  ```

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
https://github.com/json-c/json-c  
https://github.com/rbtylee/tutorial-jsonc/blob/master/tutorial/index.md  
## OpenWeatherMap API 사용법  
OpenWeatherMap 사이트 회원가입 후 인증키 발급받고 API 공식문서 대로 진행  
- 참고 사이트  
https://openweathermap.org/current

## 리눅스 사용하기 좋은 명령어 
- `grep` :  특정 단어 찾기  
```history | grep "curl"```  
- `>` : 명령어 실행 결과 저장하기  
```ls > result.txt```

## XML, JSON 차이 
- XML(eXtensible Markup Language) : 확장 마크업 언어  
<> 로 묶어쓴다. 
- JSON (JavaScript Object Notation) : 속성-값 쌍(attribute–value pairs), 배열 자료형  
- 공통점
  - 1. 둘 다 데이터를 저장 및 전달을 위해 만들어짐  
  - 2. 기계와 사람이 쉽게 읽을 수 있다
  - 3. 계층적인 데이터 구조를 가지고 있다
  - 4. 다양한 프로그래밍 언어에 의해 파싱 될 수 있다
  - 5. XMLHttpRequest 객체를 이용해서 서버로부터 데이터를 전송 받을 수 있다
- 차이점 
  - 1. JSON은 종료 태그를 사용하지 않는다
  - 2. JSON 구문이 XML 구문보다 짧다
  - 3. JSON 데이터가 XML 보다 빨리 읽고 쓸 수 있다
  - 4. XML은 배열을 사용할 수 없지만, JSON은 가능하다
  - 5. XML은 XML 파서로 파싱되며, JSON은 자바스크립트 표준 함수인 eval() 함수로 파싱된다
- 결론
  - XML은 XML DOM(Document Object Model)을 이용하여 해당 문서에 접근하고, JSON은 바로 파싱하므로 XML보다 빠르다  
  하지만 JSON은 전송받은 데이터의 무결성을 사용자가 직접 검증해야한다. 
  따라서 데이터의 검증이 필요한 곳에서는 스키마를 사용하여 데이터의 무결성을 검증할 수 있는 XML이 사용된다
