// 2023.4.18,2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"

void Keyboard(bool* playing, int puzzle[5][5], int* x, int* y);
void Draw(HANDLE hOP, int x, int y, char* str, WORD color);

// 게임 함수들
void InitPuzzle(int puzzle[5][5]); // 퍼즐 초기화 함수
void Print(HANDLE hOP, int puzzle[5][5], int x, int y); // 화면에 퍼즐을 그려주는 함수
void DrawBlock(HANDLE hOP, int x, int y, char* str, WORD color);

void Swap(int* prevBlock, int* currBlock); // 두 블록을 교체해주는 함수
bool Check(int puzzle[5][5]); // 게임 클리어 확인

int main()
{
    system("mode con:lines=25 cols=48"); // 콘솔창의 가로(cols) 세로(lines) 크기 지정

    srand(time(NULL));
    rand();

    HANDLE hOP; // 핸들값 가져오기
    hOP = GetStdHandle(STD_OUTPUT_HANDLE);

    // 커서 숨기기
    CONSOLE_CURSOR_INFO curInfo;
    curInfo.bVisible = false;
    curInfo.dwSize = 1;
    SetConsoleCursorInfo(hOP, &curInfo);

    bool isPlaying = true;
    int nPuzzle[5][5];
    int nX = 4, nY = 4; // 처음 빈칸의 인덱스 번호

    InitPuzzle(nPuzzle);
    Print(hOP, nPuzzle, nX, nY);

    while (isPlaying)
    {
        if (_kbhit())
        {
            system("cls");

            Keyboard(&isPlaying, nPuzzle, &nX, &nY);
            Print(hOP, nPuzzle, nX, nY);
            isPlaying = !Check(nPuzzle);
            
            if (isPlaying == false)
            {
                cout << "게임 클리어!" << endl;
                system("pause");
            }

            while (_kbhit()) _getch();
        }
    }

    return 0;
}

// 2 * 3 + 6 * 2 - 8 / 4
// (2 * 3) + (6 * 2) - (8 / 4) --> 괄호치는 습관이 들면 실수가 줄어듬

void Keyboard(bool* playing, int puzzle[5][5], int* x, int* y)
{
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && *x < 4) // 오른쪽 방향키, 정의 - F12로 출처 타고 들어갈 수 있음
    {
        Swap(&puzzle[*y][*x], &puzzle[*y][*x + 1]);
        (*x)++; // 괄호가 없으면 주소값에 ++ 가 먼저 적용됨
    }
    else if (GetAsyncKeyState(VK_LEFT) & 0x8000 && *x > 0) // 왼쪽 방향키
    {
        Swap(&puzzle[*y][*x], &puzzle[*y][*x - 1]);
        (*x)--;
    }
    else if (GetAsyncKeyState(VK_UP) & 0x8000 && *y > 0) // 위쪽 방향키
    {
        Swap(&puzzle[*y][*x], &puzzle[*y - 1][*x]);
        (*y)--;
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000 && *y < 4) // 아래쪽 방향키
    {
        Swap(&puzzle[*y][*x], &puzzle[*y + 1][*x]);
        (*y)++;
    }
    else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) // ESC
        *playing = false;
}

void Draw(HANDLE hOP, int x, int y, char* str, WORD color)
{
    DWORD dwCharsWritten;
    COORD cdFill = { x,y };

    FillConsoleOutputAttribute(hOP, color, strlen(str), cdFill, &dwCharsWritten); // 색상을 입혀줌
    WriteConsoleOutputCharacter(hOP, str, strlen(str), cdFill, &dwCharsWritten); // 문자를 적어줌
    // str : 호환되지 않는다 뜨면 프로젝트 - 속성 - 고급 - 문자집합 - 멀티바이트 문자 집합 사용으로 변경
}

void InitPuzzle(int puzzle[5][5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
            puzzle[i][j] = i * 5 + j;
    }

    puzzle[0][0] = 24;
    puzzle[4][4] = 0;

    for (int i = 0; i < 999; i++) // 섞는 횟수 : 홀수, 전체횟수가 짝수여야 하는데 위에서 한번 섞었으므로
    {
        int nDestX = rand() % 5;
        int nDestY = rand() % 5;

        int nSrcX = rand() % 5;
        int nSrcY = rand() % 5;

        if ((nDestX == 4 && nDestY == 4) || (nSrcX == 4 && nSrcY == 4) || (nDestX == nSrcX && nDestY == nSrcY)) // 실제로 스왑을 시키지 않는 경우
        {
            i--;
            continue;
        }

        int nTemp = puzzle[nDestY][nDestX];
        puzzle[nDestY][nDestX] = puzzle[nSrcY][nSrcX];
        puzzle[nSrcY][nSrcX] = nTemp;
    }
}

void Print(HANDLE hOP, int puzzle[5][5], int x, int y)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            char* szTemp = new char;
            // itoa : 정수값을 문자로 변형 해주는 함수

            if (j == x && i == y) // 빈칸 블럭
                DrawBlock(hOP, 10 + j * 6, 5 + i * 3, (char*)"■", BG_WHITE | FG_BLACK);
            else
                DrawBlock(hOP, 10 + j * 6, 5 + i * 3, itoa(puzzle[i][j], szTemp, 10), BG_WHITE | FG_BLACK);
            // itoa 보안성 문제 -> 프로젝트 속성 - c++ 구성속성 - 일반 - SDL 검사 - 아니오
        }
    }
}

void DrawBlock(HANDLE hOP, int x, int y, char* str, WORD color)
{
    Draw(hOP, x + 0, y + 0, str, color);
    Draw(hOP, x + 2, y + 0, (char*)"■", color);
    Draw(hOP, x + 0, y + 1, (char*)"■", color);
    Draw(hOP, x + 2, y + 1, (char*)"■", color);
}

void Swap(int* prevBlock, int* currBlock)
{
    int nTemp = *prevBlock;
    *prevBlock = *currBlock;
    *currBlock = nTemp;
}

bool Check(int puzzle[5][5])
{
    bool isComplete = false;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (i == 4 && j == 4)
                isComplete = true;

            if (puzzle[i][j] != j + 1 + i * 5)
                break;
        }
    }

    return isComplete;
}
