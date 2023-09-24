
# minishell
- minishell : **42cursus (3 Circle)**
   - Status : Finished
   - Completed Date : 2021/08/02
   - Evaluation : <span style="color: #008000">Success</sapn>
   - Score : <span style="color: #008000">95%</sapn>
   - Team : dohelee, trhee

- Reference
   - None

- Tester
   - None
  
- Issue
  1. `cat | cat | ls` : 에서 기대한 동작과 다름.
       - 원인 추측 : parent_process 함수에서 `fd[0]`가 닫히지 않고 출력해보면 계속 증가하는데, 이게 문제일 수  있음.
  2. `minishell` 에서 추가로 `minishell` 실행 시 환경변수 못 가져옴.
      - 또한 쉘에서 쉘로 접속 시 SHLVL=1 환경변수의 값도 1 증가시켜야 함
  3. `ls -al > a > b > c > d` : 마지막 파일 `d`만 생성되고 `a`, `b`, `c` 가 생성이 안됨.
  	  -  bash에서는 `a`, `b`, `c`, `d` 파일이 생성되고 마지막 파일 `d` 에만 결과가 출력됨. ( 나머지 `a`, `b`, `c`는 빈 파일 )
  4. `cat` : 인자 없이 실행 후, `cat` 명령어가 입력을 받는 도중  `ctrl+c`, `ctrl+\` , `ctrl+d` 가 발생하여 입력이 종료되고 난 후에 `echo $?` 출력시 결과 값이 원하는 값으로 출력 되지 않음
  	  - `ctrl+c` : 130,  `ctrl+\` : 131 , `ctrl+d` : 0 이 출력되야 함.
  	  - 현재 해당항목에 대한 것을 고려하지 않고 개발해서, 추가만 하면 됨.
  5. `unset PWD` 후 pwd 하면 경로가 출력이 안됨
      - 환경변수에 없어도 가져와야 함, `pwd` 출력 시 `getcwd` 함수를 사용해서 출력하면 해결 가능
  6. `export` : 인자 없이 입력 시 동작 미구현 및 `Segmentation Fault` 발생 **(평가완료 후 발견)**
      - 현재는 인자가 있을 경우만 동작. 
  7. `export $HOME:aaaa` 형식으로 기존 $HOME 환경변수에 추가할 수 있어야 함.
  	  - 현재는 $HOME 뒤에 붙이면 동작 안함 -> `echo $HOME:aaaa`로 찍어보면 /Users/dohelee:aaaa 처럼 나와야 됨.
  8. 빌트인 함수들을 따로 파일로 만들어서 하는 방법으로 진행한 사람도 있음, 현재 우리는 하드코딩 되어 있음.
  	  - 이것은 평가자에 따라서 다를 수 있으므로 참고만 하자
