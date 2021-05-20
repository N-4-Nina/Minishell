#ifndef TERMC_H
# define TERMC_H

void    enableRawMode(struct termios *term);
void    disableRawMode(struct termios *term);
int		term_init(struct termios *term);
#endif