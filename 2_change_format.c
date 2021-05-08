#include <ncurses.h>

void printStatus();
void printMessage();

const int ATTR_SET[] = {
  A_BOLD | COLOR_PAIR(1),
  A_UNDERLINE | COLOR_PAIR(2),
  A_BLINK | COLOR_PAIR(3),
};
int attridx = 0;

int main()
{
  // setup ncurses
	initscr();
  cbreak();
  noecho();
  curs_set(FALSE);

  // setup color
  start_color();
  init_pair(1, COLOR_CYAN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLUE);
  init_pair(3, COLOR_GREEN, COLOR_WHITE);

  // initial print
  printMessage();
  printStatus();

  // main loop
  int ch;
	while((ch = getch()) != 'q') {
    switch (ch) {
      case 0x20:
        attridx = (attridx + 1) % (sizeof(ATTR_SET) / sizeof(int));
        printMessage();
        break;
    }
  }

  // cleanup
	endwin();

  return 0;
}

void printMessage()
{
  attrset(A_NORMAL);
  mvprintw(2, 5, "Welcome to  ");
  attrset(ATTR_SET[attridx]);
  mvprintw(2, 17, "LLT");
  attrset(A_NORMAL);
  mvprintw(2, 20, " !!");
	refresh();
}

void printStatus()
{
  mvprintw(LINES - 1, 0, "Press q to exit");
  refresh();
}
