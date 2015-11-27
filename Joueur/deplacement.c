#include <ncurses.h>
#include <unistd.h>
#include <string.h>

int main(void) {
  int x = 0, y = 0, y_init=0, ch, row, col;
 
  char str[80];
  char mesg[]="o";
  initscr();
  noecho();
  curs_set(FALSE);
  keypad(stdscr, TRUE);
  cbreak();

  while(1) {
	clear();
	getmaxyx(stdscr,row,col); /* get the number of rows and columns */	
 	
 	
 	if((x >= 0) && (x < col) && (y >= 0) && (y < row)){
 		
 		
 		mvprintw(y, x, "%s", mesg);
		ch = getch();
		switch(ch){
			case KEY_UP: 
				y--;
				break;
			case KEY_DOWN:
				y++;
				break;	
			case KEY_RIGHT:
				x++;
				break;		
			case KEY_LEFT:
				x--;
				break;
		}					
	}
	else if(y < 0 ) y = row-1;
	else if(x < 0 ) x = col-1; 
	else if(y > row-1 ) y = 0;
	else if(x > col-1 ) x = 0;
   		refresh();
   	
 }
 	endwin();			/* End curses mode		  */
}
