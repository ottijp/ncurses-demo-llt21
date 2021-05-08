#include <ncurses.h>
#include <string.h>

void printVolume();
void printStatus();
void printMousePos(int, int);

float volumes[] = {0.5, 0.5, 0.5, 0.5, 0.5};
int volumeCount = sizeof(volumes) / sizeof(float);
int selectingVolume = 0;

int main()
{
  // setup ncures
	initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(FALSE);
  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
  printf("\033[?1003h\n"); // Makes the terminal report mouse movement events

  // setup colors
  start_color();
  init_pair(1, COLOR_RED, COLOR_WHITE);

  // initial print
  printVolume();
  printStatus();

  // main loop
	int ch;
  MEVENT mevent;
	while((ch = getch()) != 'q')
	{
    switch(ch)
		{
      case KEY_UP:
        if (selectingVolume == 0) break;
        selectingVolume--;
        printVolume();
        break;
      case KEY_DOWN:
        if (selectingVolume >= volumeCount - 1) break;
        selectingVolume++;
        printVolume();
        break;
      case KEY_RIGHT:
        volumes[selectingVolume] += 0.1;
        if (volumes[selectingVolume] > 1) volumes[selectingVolume] = 1;
        printVolume();
        break;
      case KEY_LEFT:
        volumes[selectingVolume] -= 0.1;
        if (volumes[selectingVolume] < 0) volumes[selectingVolume] = 0;
        printVolume();
        break;
      case KEY_MOUSE:
        if (getmouse(&mevent) == OK)
        {
          volumes[selectingVolume] = (float)mevent.x / COLS;
          printMousePos(mevent.x, mevent.y);
          printVolume();
        }
        break;
		}
	}

  // cleanup
	endwin();

	return 0;
}

void printVolume()
{
  attrset(A_UNDERLINE);
  mvprintw(0, 1, "selecting volume: %d", selectingVolume + 1);

  for (int i = 0; i < volumeCount; i++)
  {
    if (i == selectingVolume)
    {
      attrset(COLOR_PAIR(1));
    }
    else
    {
      attrset (A_NORMAL);
    }
    int volumeCells = volumes[i] * (float)(COLS - 7);
    mvprintw(2 + i, 1, "Vol %d ", i + 1);
    for (int v = 0; v < volumeCells; v++)
    {
      mvaddch(2 + i, 8 + v, '#');
    }
    addch('\n');
  }

  attrset(A_NORMAL);
  refresh();
}

void printMousePos(int x, int y)
{
  char mousePosLabel[16];

  sprintf(mousePosLabel, "(%d, %d)", x, y);
  for (int i = COLS - 16 - 1; i < COLS; i++) {
    mvaddch(LINES - 1, i, ' ');
  }
  mvprintw(LINES - 1, COLS - strlen(mousePosLabel) - 1, mousePosLabel);
  refresh();
}

void printStatus()
{
  mvprintw(LINES - 1, 0, "Press q to exit");
  refresh();
}
