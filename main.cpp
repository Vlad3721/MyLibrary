#include <stdio.h>
#include <windows.h>
#include <math.h>

#define width 165
#define height 75

class Screen{
public:
    int w = 0;
    int h = 0;
    char space = ' ';
    char wall = '#';
    char** screen;

    Screen(int w1 = 10, int h1 = 10) {
        w = w1;
        h = h1;
        screen = new char*[h];
        for (int i = 0;i < h;i++)
            screen[i] = new char[w+1];
        for (int y = 0;y < h;y++)
            screen[y][w]='\0';
    }

    ~Screen() {
        for(int i = 0;i < h;i++) {
            delete [] screen[i];
        }
        delete [] screen;
    }

    void show() {
        for (int y = 0;y < h;y++)
            printf("%s\n",screen[y]);
    }

    void fill(int type = 0) {
        switch (type) {
            case 0:
                for(int x = 0;x < w;x++)
                    for(int y = 0;y < h;y++)
                        if ((y>0) && (x>0) && (y<h-1) && (x<w-1))
                            screen[y][x] = space;
                        else
                            screen[y][x] = wall;
                break;
            default:
                break;
        }
    }

    void putLine(int x1,int y1,int x2,int y2,char b = '@') {
        //Расчёт тангенса
        float tg = 0;
        if (x2-x1 != 0)
            tg = (float)(y2-y1)/(x2-x1);
        //Помещение диагональных линий
        if ((x2-x1 != 0) && (y2-y1 != 0)) {
            int mx = 1;
            int my = 1;
            if ((y2-y1 < 0) && (x2-x1 > 0))
                my = -1;
            else if ((y2-y1 > 0) && (x2-x1 < 0))
                mx = -1;
            else if ((y2-y1 < 0) && (x2-x1 < 0)) {
                my = -1;
                mx = -1;
            }

            for(int x = 0;x <= abs(x2-x1);x++) {
                int Ox = x1+x*((x2-x1)/abs(x2-x1));
                int Oy = roundf(y1+tg*x*mx);
                screen[Oy][Ox] = b;
            }

            for(int y = 0;y <= abs(y2-y1);y++) {
                int Ox = roundf(x1+y/tg*my);
                int Oy = y1+y*((y2-y1)/abs(y2-y1));
                screen[Oy][Ox] = b;
            }
        }
        //Помещение вертикальных линий
        else if ((x2-x1 == 0) && (y2-y1 != 0)) {
            for(int y = 0;y <= abs(y2-y1);y++) {
                int Ox = x1;
                int Oy = y1+y*((y2-y1)/abs(y2-y1));
                screen[Oy][Ox] = b;
            }
        }
        //Помещение горизонтальных линий
        else if ((y2-y1 == 0) && (x2-x1 != 0)) {
            for(int x = 0;x <= abs(x2-x1);x++) {
                int Ox = x1+x*((x2-x1)/abs(x2-x1));
                int Oy = y1;
                screen[Oy][Ox] = b;
            }
        }
        else
            screen[y1][x1] = b;
    }
};

class Point{
public:
    int x = 0;
    int y = 0;
    int z = 0;
    Point(int px = 0,int py = 0,int pz = 0) {
        x = px;
        y = py;
        z = pz;
    }
};

class Camera{
public:
    int x = 0;
    int y = 0;
    int z = 0;

    int w = 5;
    int h = 5;
    int d = 1;

    int wx = 1;
    int wy = 0;
    int wz = 0;

    int hx = 0;
    int hy = 1;
    int hz = 0;

    int dx = 0;
    int dy = 0;
    int dz = 1;
    
    int corners[4][3];
    Camera(int px = 0,int py = 0,int pz = 0) {
        x = px;
        y = py;
        z = pz;
    }
};

// function for restart of cursor
void setcur(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
    Screen map(width,height);
    int LX1 = 3;
    int LY1 = 3;
    int LX2 = 4;
    int LY2 = 3;
    map.fill();
    system("cls");
    do {
        setcur(0,0);
        map.fill();
        map.putLine(LX1,LY1,LX2,LY2,'@');
        map.show();

        if (GetKeyState(VK_ESCAPE) < 0) break;

        if (GetKeyState('W') < 0) if (LY1 > 1) LY1--;
        if (GetKeyState('S') < 0) if (LY1 < height-2) LY1++;
        if (GetKeyState('A') < 0) if (LX1 > 1) LX1--;
        if (GetKeyState('D') < 0) if (LX1 < width-2) LX1++;

        if (GetKeyState(VK_UP) < 0) if (LY2 > 1) LY2--;
        if (GetKeyState(VK_DOWN) < 0) if (LY2 < height-2) LY2++;
        if (GetKeyState(VK_LEFT) < 0) if (LX2 > 1) LX2--;
        if (GetKeyState(VK_RIGHT) < 0) if (LX2 < width-2) LX2++;

        Sleep(10);
    } while(true);
    return 0;
}
