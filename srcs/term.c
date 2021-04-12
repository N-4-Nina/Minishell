#include "../includes/nsh.h"


void enableRawMode()
{
    struct termios orig_termios;
    struct termios raw;
    
    tcgetattr(STDIN_FILENO, &orig_termios);
    raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}
int term_init(void)
{
    char *term_type;
    
    term_type = getenv("TERM");
    if (!term_type)
    {
        printf("TERM variable must be set ! \n");
        return (-1);
    }
    if (tgetent(NULL, term_type) < 1)
    {
        fprintf(stderr, "Terminal type is not defined or termcap database can't be accessed.\n");
        return (-1);
    }
    enableRawMode();
    return (1);
}