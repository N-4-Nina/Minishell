#include "../includes/nsh.h"

void    enableRawMode(struct termios *term)
{
    struct termios raw;
    
    tcgetattr(STDIN_FILENO, term);
    raw = *term;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void    disableRawMode(struct termios *term)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, term);
}

int term_init(struct termios *term)
{
    char *term_type;
    
    term_type = getenv("TERM");
    if (!term_type)
    {
        printf("TERM variable must be set ! \n");
        return (-1);
    }
    term = (struct termios*) NULL;
    if (tgetent(NULL, term_type) < 1)
    {
        printf("Terminal type is not defined or termcap database can't be accessed.\n");
        return (-1);
    }
    printf("term type = %s \n", term_type);
    return (1);
}