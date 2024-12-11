#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>
#include <windows.h>
const int W = 20, H = 20;
int move = 'w',x = 'w',head = W / 2 + (H / 2) * W;
struct tile{
    int ptr = -1;
    char state = '.';
}game[W * H];
int main(){
    game[head] = {-1,'*'};
    game[2] = {-1,'+'};
    while(true){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
        for(int i = 0; i < W+2; i++)printf("-");
        printf("\n");
        for(int i = 0; i < H; i++){
            printf("|");
            for(int j = 0; j < W; j++){
                printf("%c", game[j + W * i].state);
            }
            printf("|\n");
        }
        for(int i = 0; i < W+2; i++)printf("-");
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        while(_kbhit())x = _getch();
        int tmp1 = 'w' * (x == 'w' && move != 's') + 'a' * (x == 'a' && move != 'd') + 's' * (x == 's' && move != 'w') + 'd' * (x == 'd' && move != 'a');
        move = tmp1==0?move:tmp1;
        if(x == 'q') break;
        auto f = [](int h){return (h + W * ((h % W == 0 && move == 'a') - (h % W == (W - 1) && move == 'd')) % (W * H)); };//fix right/left warp shift
        int tmp = head, dt = (move == 's') * W - (move == 'w') * W - (move == 'a') + (move == 'd') * 1;//dt = snake position delta for a move
        while(game[tmp].ptr != -1){
            tmp = game[tmp].ptr;
            if(game[game[tmp].ptr].ptr == -1 && game[((f(head) + dt + W * H) % (W * H))].state != '+')game[tmp].ptr = -1;
        }
        if(game[((f(head) + dt + W * H) % (W * H))].state == '*'){
            printf("you crashed! haha\n");
            break;
        }
        while(game[((f(head) + dt + W * H) % (W * H))].state == '+'){
            int x = rand() % (W * H);
            if(game[x].state == '*') continue;
            else game[x].state = '+'; break;
        }
        game[tmp].state = '.';
        game[head = ((f(head) + dt + W * H) % (W * H))] = {head,'*'};
    }
}