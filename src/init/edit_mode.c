#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <ectaz.h>

struct termios base_termios;

__attribute__((constructor))
void get_base_termios(void)
{
    if (tcgetattr(STDIN_FILENO, &base_termios)) die("tcgetattr");
}

__attribute__((constructor))
void enable_raw_mode(void)
{
    struct termios raw = base_termios;

    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw)) die("tcsetattr");
}

__attribute__((destructor))
void disable_raw_mode(void)
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &base_termios)) die("tcsetattr");
}
