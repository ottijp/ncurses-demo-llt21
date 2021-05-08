#include <ncurses.h>
#include <unistd.h>

void printStatus();
void printCharacters();

const int LLT[][9] = {
  {1,0,0,1,0,0,1,1,1},
  {1,0,0,1,0,0,1,1,1},
  {1,1,1,0,1,0,0,1,0}
};
const int originx = 5;
const int originy = 2;

int main()
{
  // setup ncurses
  initscr();
  cbreak();
  noecho();
  curs_set(FALSE);

  // initial print
  printStatus();
  printCharacters();

  // main loop
  while(getch() != 'q') {}

  // cleanup
  endwin();

  return 0;
}

void printStatus()
{
  mvprintw(LINES - 1, 0, "Press q to exit");
  refresh();
}

void printCharacters()
{
  const int charCount = sizeof(LLT) / sizeof(LLT[0]);
  for(int c = 0; c < charCount; c++)
  {
    const int coriginx = originx + c * 4;
    const int coriginy = originy;
    for (int p = 0; p < 9; p++)
    {
      if (LLT[c][p] == 1)
      {
        const int x = coriginx + p % 3;
        const int y = coriginy + p / 3;
        mvaddch(y, x, '#');
        usleep(300 * 1000);
        refresh();
      }
    }
  }
}
