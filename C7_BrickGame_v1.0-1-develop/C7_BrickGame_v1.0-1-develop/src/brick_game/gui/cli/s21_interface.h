/*
  This is a frontend (CLI) module of BrickGame (Tetris) Game
  @author: norreyll (aka F.A.S.T), a student of 21 School from Novosibirsk
*/

#ifndef S21_INTERFACE_H_
#define S21_INTERFACE_H_

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "./../../tetris/s21_finite_state_machine.h"
#include "./../../tetris/s21_logic.h"

#define FIELD_OFFSET_X 2
#define FIELD_OFFSET_Y 1

void cli_init(void);
void cli_cleanup(void);
void draw_field(WINDOW *win, const GameInfo_t *game);
void draw_sidebar(WINDOW *win, const GameInfo_t *game);
void draw_next(WINDOW *win, const GameInfo_t *game);

void process_input(int ch);
void draw_initial_screen(void);
void draw_game_screen(const GameInfo_t *game);
void cli_run(void);

extern WINDOW *game_win;
extern WINDOW *score_win;
extern WINDOW *next_win;
extern SCREEN *game_screen;

#endif  // S21_INTERFACE_H_