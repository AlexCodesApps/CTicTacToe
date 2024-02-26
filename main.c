#include <stdio.h>
int mapArray[3][3] = 
{{0,0,0},
{0,0,0},
{0,0,0}};
int orderedArray[9] = {0};
int num1, num2;
int quit = 0;

void PrintArray() {
    for (int i = 0; i < 3; i++) {
        for (int i2 = 0; i2 < 3; i2++) {
        printf("%d", mapArray[i][i2]);
        }
        printf("\n");
    }
    printf("\n");
}
void SetPoint(int x, int y, int num) {
    if (mapArray[y][x]) return;
    mapArray[y][x] = num;
    orderedArray[(y*3)+x] = num;
}
void AISetPoint() {
    int orderedSlot;
    static int winCons[8][3] = {{0, 3, 6},{1, 4, 7},{2, 5, 8},{0,1,2},{3,4,5},{6,7,8},{0,4,8},{2,4,6}};
    static int preferedSquares[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
    for (int i = 0; i < 8; i++)
    {
        if (orderedArray[winCons[i][0]] == orderedArray[winCons[i][1]] || orderedArray[winCons[i][1]] == orderedArray[winCons[i][2]] || orderedArray[winCons[i][0]] == orderedArray[winCons[i][2]]) {
            int count = 0;
            for (int b = 0; b < 3; b++)
            {
                if (orderedArray[winCons[i][b]]) count++;
            }
            if (count != 2) continue;
            
            for (int a = 0; a < 3; a++) {
                if (orderedArray[winCons[i][a]]) continue;
                else orderedSlot = winCons[i][a];
                goto slot;
            }
        }
    }
    for (int i = 0; i < 9; i++) {
        if (orderedArray[preferedSquares[i]] == 0) {
            orderedSlot = preferedSquares[i];
            goto slot;
            }
    }
    return;
slot: ;
    int x = orderedSlot % 3;
    int y = (orderedSlot- x )/3;
    SetPoint(x, y, 2);
}
void OfficialWin(int num) {
    printf("Winner: ");
    if (num == 1) printf("PLAYER!");
    else if (num == 2) printf("COMPUTER!");
    else printf("The Unsung One...");
    printf("\n");
    PrintArray();
    quit = 1;
}
void WinCondition(int num) {
    for (int i = 0; i < 3; i++)
    {
        if (mapArray[i][0] == mapArray[i][1] &&  mapArray[i][1] == mapArray[i][2] && mapArray[i][0] == num) goto win;
        if (mapArray[0][i] == mapArray[1][i] && mapArray[1][i] == mapArray[2][i] && mapArray[0][i] == num) goto win;
    }
    if (orderedArray[0] == orderedArray[4] && orderedArray[4] == orderedArray[8] && orderedArray[0] == num) goto win;
    if (orderedArray[2] == orderedArray[4] && orderedArray[4] == orderedArray[6] && orderedArray[2] == num) goto win;
    return;
    win:
        OfficialWin(num);
}
void Draw() {
    if (quit) return;
    int count = 0;
    for (int i = 0; i < 9; i++) {
        if (orderedArray[i] != 0) count++;
    }
    if (count == 9) {
        printf("Its a draw...\n");
        PrintArray();
        quit = 1;
    }
}
void GetInput(int *num) {
    printf("Enter numbers 0 - 2\n");
    if (scanf("%d", num) != 1 || *num > 2 || *num < 0) {
        printf("Invalid Input\n");
        while ((getchar()) != '\n');
        GetInput(num);
    }
}
void GameLoop() {
    PrintArray();
    printf("X Value\n");
    GetInput(&num1);
    printf("Y Value\n");
    GetInput(&num2);
    SetPoint(num1,num2, 1);
    WinCondition(1);
    if (quit) return;
    AISetPoint();
    WinCondition(2);
    Draw();
    while (!quit) GameLoop();
}
int main() {
    printf("Tic-Tac-Toe With A Bot!\n");
    GameLoop();
}