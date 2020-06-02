#ifndef CONIO_H
#define CONIO_H

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <cstdio>

#ifdef __cplusplus
extern "C" {
#endif

enum COLORS {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHTGRAY = 7,
    DARKGRAY = 8,
    LIGHTBLUE = 9,
    LIGHTGREEN = 10,
    LIGHTCYAN = 11,
    LIGHTRED = 12,
    LIGHTMAGENTA = 13,
    YELLOW = 14,
    WHITE = 15,
    BLINK = 128
};

enum CURSORTYPE
{
    NOCURSOR,
    SOLIDCURSOR,
    NORMALCURSOR
};

struct text_info
{
    unsigned char attribute;
    unsigned char normattr;
    int screenheight;
    int screenwidth;
    int curx;
    int cury;
};

static int _kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

static int _getch();
static int get_cursor_position2(int *x, int *y)
{
    *x = -1;
    *y = -1;

    char buf[32];
    unsigned int i = 0;
    int ch;

    printf("\x1B[6n");

    while (i < sizeof(buf) - 1)
    {
        ch = _getch();
        if (ch == EOF || ch == 'R') break;
        buf[i++] = ch;
    }
    buf[i] = '\0';

    if (buf[0] != '\x1b' || buf[1] != '[') return -1;

    if (sscanf(&buf[2], "%d;%d", y, x) != 2) return -1;

    return 0;
}

static int _wherex()
{
    int x, y;
    get_cursor_position2(&x, &y);
    return x;
}

static int _wherey()
{
    int x, y;
    get_cursor_position2(&x, &y);
    return y;
}

static void _gotoxy(int x, int y)
{
    printf("\x1b[%d;%dH", y, x);
    fflush(stdout);
}

static void _clrscr()
{
    puts("\x1b[2J\x1b[1;1H");
    fflush(stdout);
}

static void _textcolor(int newcolor)
{
    const char * s = "\x1b[30m";

    switch (newcolor)
    {
        case BLACK:
            s = "\x1b[30m";
            break;

        case BLUE:
            s = "\x1b[34m";
            break;

        case GREEN:
            s = "\x1b[32m";
            break;

        case CYAN:
            s = "\x1b[36m";
            break;

        case RED:
            s = "\x1b[31;1m";
            break;

        case MAGENTA:
            s = "\x1b[35m";
            break;

        case BROWN:
            s = "\x1b[31m";
            break;

        case LIGHTGRAY:
            s = "\x1b[30;1m";
            break;

        case DARKGRAY:
            s = "\x1b[30m";
            break;

        case LIGHTBLUE:
            s = "\x1b[34;1m";
            break;

        case LIGHTGREEN:
            s = "\x1b[32,1m";;
            break;

        case LIGHTCYAN:
            s = "\x1b[36;1m";
            break;

        case LIGHTRED:
            s = "\x1b[31;1m";
            break;

        case LIGHTMAGENTA:
            s = "\x1b[35;1m";
            break;

        case YELLOW:
            s = "\x1b[33;1m";
            break;

        case WHITE:
            s = "\x1b[37;1m";
            break;

        case BLINK:
            s = "\x1b[30m";
            break;
    };

    puts(s);
}

static void _textbackground(int newcolor)
{
    const char * s = "\x1b[40m";

    switch (newcolor)
    {
        case BLACK:
            s = "\x1b[40m";
            break;

        case BLUE:
            s = "\x1b[44m";
            break;

        case GREEN:
            s = "\x1b[42m";
            break;

        case CYAN:
            s = "\x1b[46m";
            break;

        case RED:
            s = "\x1b[41;1m";
            break;

        case MAGENTA:
            s = "\x1b[45m";
            break;

        case BROWN:
            s = "\x1b[41m";
            break;

        case LIGHTGRAY:
            s = "\x1b[40;1m";
            break;

        case DARKGRAY:
            s = "\x1b[40m";
            break;

        case LIGHTBLUE:
            s = "\x1b[44;1m";
            break;

        case LIGHTGREEN:
            s = "\x1b[42,1m";;
            break;

        case LIGHTCYAN:
            s = "\x1b[46;1m";
            break;

        case LIGHTRED:
            s = "\x1b[41;1m";
            break;

        case LIGHTMAGENTA:
            s = "\x1b[45;1m";
            break;

        case YELLOW:
            s = "\x1b[43;1m";
            break;

        case WHITE:
            s = "\x1b[47;1m";
            break;

        case BLINK:
            s = "\x1b[40m";
            break;
    };

    puts(s);
}

int _getch()
{
    struct termios old, new_t;
    int ch;

    tcgetattr(0, &old);

    new_t = old;
    new_t.c_lflag &= ~ICANON;
    new_t.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &new_t);

    ch = getchar();

    tcsetattr(0, TCSANOW, &old);

    return ch;
}

static int _getche()
{
    struct termios old, new_t;
    int ch;

    tcgetattr(0, &old);

    new_t = old;
    new_t.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &new_t);

    ch = getchar();

    tcsetattr(0, TCSANOW, &old);
    return ch;
}

#ifdef __cplusplus
}
#endif
#endif

#endif
