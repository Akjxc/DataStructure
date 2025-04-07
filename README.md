# DataStructure

<git 커밋 / 푸시>
1) git 설정 확인(최초 1회)
git config --global user.name "GitHub 사용자명"
git config --global user.email "GitHub 이메일" (github 프라이버시 보호 이메일 사용할것, 기존 커밋이 프라이빗 이메일일경우 에러)

2) 변경된 파일 확인
git status

3) 변경된 사항 추가
git add .

4) 커밋 작성
git commit -m "작업 내용 간략한 설명"

5) github에 푸시
git push origin main
-> main 브런치에 푸시 (현재 브런치에 따라 main이 아닌 다른 것으로 작성할 수도 있음)

+) 새로운 브런치에서 작업하려면
git checkout -b 새로운_브랜치_이름
git push origin 새로운_브랜치_이름

<C 컴파일 및 실행>
1) gcc 설치확인
gcc --version
버전 나오면 이미 설치됨

2) gcc 설치
sudo apt update && sudo apt install -y gcc

3) c 파일 생성 및 코드 작성

4) 컴파일
gcc main.c -o main
- main은 컴파일하면서 지정되는 파일명(임의작성가능)
5) 실행
./main

+ <디버깅 환경설정>
1) .vscode 폴더 생성 후 launch.json 파일 생성

2) launch.json 파일에 아래 설정 추가
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug C Program",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/main",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": true,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}

3) F5 버튼으로 디버깅 시작