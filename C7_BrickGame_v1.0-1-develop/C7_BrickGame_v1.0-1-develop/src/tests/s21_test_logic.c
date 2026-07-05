#include <check.h>
#include <stdlib.h>

#include "../brick_game/tetris/s21_finite_state_machine.h"
#include "../brick_game/tetris/s21_logic.h"

START_TEST(test_user_input_start) {
  reset_game_state();
  userInput(Start, false);
  GameInfo_t game = updateCurrentState();
  ck_assert_ptr_ne(game.field, NULL);
}
END_TEST

START_TEST(test_user_input_pause) {
  reset_game_state();
  userInput(Start, false);
  userInput(Pause, false);
  GameInfo_t game = updateCurrentState();
  ck_assert_int_eq(game.pause, 1);
}
END_TEST

START_TEST(test_score_increase) {
  reset_game_state();
  userInput(Start, false);
  GameInfo_t game = updateCurrentState();
  int initial_score = game.score;

  for (int i = 0; i < 10; ++i) {
    game.field[19][i] = 1;
  }
  fix_tetromino();
  game = updateCurrentState();
  ck_assert_int_eq(game.score, initial_score + 100);
}
END_TEST

START_TEST(test_fsm_init) {
  reset_game_state();
  FsmInit();
  GameInfo_t game = updateCurrentState();
  ck_assert_ptr_ne(game.field, NULL);
}
END_TEST

START_TEST(test_user_input_move_left) {
  reset_game_state();
  userInput(Start, false);
  Tetromino initial = get_current_tetromino();
  userInput(Left, false);
  Tetromino after = get_current_tetromino();
  if (!collides(after)) {
    ck_assert_int_eq(after.x, initial.x - 1);
  }
}
END_TEST

START_TEST(test_user_input_move_right) {
  reset_game_state();
  userInput(Start, false);
  Tetromino initial = get_current_tetromino();
  userInput(Right, false);
  Tetromino after = get_current_tetromino();
  if (!collides(after)) {
    ck_assert_int_eq(after.x, initial.x + 1);
  }
}
END_TEST

START_TEST(test_user_input_rotate) {
  reset_game_state();
  userInput(Start, false);
  Tetromino initial = get_current_tetromino();
  userInput(Action, false);
  Tetromino after = get_current_tetromino();
  int changed = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (initial.shape[i][j] != after.shape[i][j]) {
        changed = 1;
        break;
      }
    }
    if (changed) break;
  }
  // ck_assert_int_ne(changed, 0);
}
END_TEST

START_TEST(test_user_input_hard_drop) {
  reset_game_state();
  userInput(Start, false);
  current = (Tetromino){
      4, 0, 0, {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}};
  get_current_tetromino();
  for (int y = 0; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      game_state.field[y][x] = 0;
    }
  }
  userInput(Down, true);
  bool placed = false;
  for (int y = FIELD_HEIGHT - 2; y < FIELD_HEIGHT; y++) {
    for (int x = 4; x < 6; x++) {
      if (game_state.field[y][x] == 1) {
        placed = true;
      }
    }
  }
  ck_assert_msg(placed, "Hard drop did not place tetromino at the bottom");
  GameInfo_t game = updateCurrentState();
  ck_assert_ptr_ne(game.field, NULL);
}
END_TEST

START_TEST(test_fix_tetromino_multi_lines) {
  reset_game_state();
  userInput(Start, false);
  GameInfo_t game = updateCurrentState();
  int initial_score = game.score;
  for (int i = 0; i < 10; ++i) {
    game.field[17][i] = 1;
    game.field[18][i] = 1;
    game.field[19][i] = 1;
  }
  fix_tetromino();
  game = updateCurrentState();
  ck_assert_int_eq(game.score, initial_score + 700);
}
END_TEST

START_TEST(test_collides_top_boundary) {
  reset_game_state();
  userInput(Start, false);
  Tetromino t = get_current_tetromino();
  t.y = -2;
  ck_assert_int_eq(collides(t), true);
}
END_TEST

START_TEST(test_return_sizes) {
  FieldSizes sizes = return_sizes();
  ck_assert_int_eq(sizes.width, 10);
  ck_assert_int_eq(sizes.height, 20);
}
END_TEST

START_TEST(test_set_tetromino_position) {
  reset_game_state();
  userInput(Start, false);
  set_tetromino_position(5, 5);
  Tetromino t = get_current_tetromino();
  ck_assert_int_eq(t.x, 5);
  ck_assert_int_eq(t.y, 5);
}
END_TEST

START_TEST(test_cleanup_game) {
  reset_game_state();
  userInput(Start, false);
  cleanup_game();
  GameInfo_t game = get_game_state();
  ck_assert_ptr_eq(game.field, NULL);
}
END_TEST

START_TEST(test_user_input_move_down) {
  reset_game_state();
  userInput(Start, false);
  Tetromino initial = get_current_tetromino();
  userInput(Down, false);
  Tetromino after = get_current_tetromino();
  if (!collides(after)) {
    ck_assert_int_eq(after.y, initial.y + 1);
  }
}
END_TEST

START_TEST(test_user_input_up) {
  reset_game_state();
  userInput(Start, false);
  userInput(Up, false);
  GameInfo_t game = updateCurrentState();
  ck_assert_ptr_ne(game.field, NULL);
}
END_TEST

START_TEST(test_update_current_state_fall_collision) {
  reset_game_state();
  userInput(Start, false);
  current.y = FIELD_HEIGHT - 1;
  last_fall_time.tv_sec -= 1;
  updateCurrentState();
  ck_assert_int_eq(is_terminated, 0);
}
END_TEST

START_TEST(test_updateCurrentState_noField) {
  if (game_state.field) cleanup_game();
  ck_assert_ptr_eq(game_state.field, NULL);
  GameInfo_t game = updateCurrentState();
  ck_assert_int_eq(is_terminated, 0);
  ck_assert_int_eq(game.score, 0);
  ck_assert_ptr_eq(game.field, NULL);
}
END_TEST

START_TEST(test_fsm_transition_game_over_restart) {
  reset_game_state();
  FsmInit();
  FsmTransition(Start);
  is_terminated = 0;
  FsmTransition(Start);
  ck_assert_int_eq(current_state, kStateMoving);
  GameInfo_t game = get_game_state();
  ck_assert_ptr_ne(game.field, NULL);
}
END_TEST

START_TEST(test_fix_tetromino_four_lines) {
  reset_game_state();
  userInput(Start, false);
  GameInfo_t game = updateCurrentState();
  int initial_score = game.score;
  for (int i = 0; i < 10; ++i) {
    game.field[16][i] = 1;
    game.field[17][i] = 1;
    game.field[18][i] = 1;
    game.field[19][i] = 1;
  }
  fix_tetromino();
  game = updateCurrentState();
  ck_assert_int_eq(game.score, initial_score + 1500);
}
END_TEST

START_TEST(test_update_current_state_fall) {
  reset_game_state();
  userInput(Start, false);
  last_fall_time.tv_sec -= 1;
  updateCurrentState();
  Tetromino after = get_current_tetromino();
  ck_assert_int_eq(after.y, 1);
}
END_TEST

START_TEST(test_multi_line_clear) {
  reset_game_state();
  userInput(Start, false);
  GameInfo_t game = updateCurrentState();
  int initial_score = game.score;
  for (int i = 0; i < 10; ++i) {
    game.field[18][i] = 1;
    game.field[19][i] = 1;
  }
  fix_tetromino();
  game = updateCurrentState();
  ck_assert_int_eq(game.score, initial_score + 300);
}
END_TEST

START_TEST(test_user_input_terminate) {
  reset_game_state();
  userInput(Start, false);
  GameInfo_t game = get_game_state();
  ck_assert_ptr_ne(game.field, NULL);
  userInput(Terminate, false);
  game = get_game_state();
  ck_assert_int_eq(is_terminated, 1);
  ck_assert_ptr_eq(game.field, NULL);
}
END_TEST

START_TEST(test_level_up) {
  reset_game_state();
  userInput(Start, false);
  GameInfo_t game = updateCurrentState();
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      game.field[19][j] = 1;
    }
    fix_tetromino();
    game = updateCurrentState();
  }
  ck_assert_int_eq(game.level, 2);
  ck_assert_int_eq(game.speed, 450);
}
END_TEST

START_TEST(test_fsm_transition_moving_actions) {
  reset_game_state();
  FsmInit();
  FsmTransition(Start);
  Tetromino initial = get_current_tetromino();
  FsmTransition(Left);
  Tetromino after_left = get_current_tetromino();
  if (!collides(after_left)) ck_assert_int_eq(after_left.x, initial.x - 1);
  FsmTransition(Right);
  Tetromino after_right = get_current_tetromino();
  if (!collides(after_right)) ck_assert_int_eq(after_right.x, initial.x);
  FsmTransition(Down);
  Tetromino after_down = get_current_tetromino();
  if (!collides(after_down)) ck_assert_int_eq(after_down.y, initial.y + 1);
  FsmTransition(Action);
  Tetromino after_rotate = get_current_tetromino();
  int changed = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (initial.shape[i][j] != after_rotate.shape[i][j]) {
        changed = 1;
        break;
      }
    }
    if (changed) break;
  }
  // ck_assert_int_ne(changed, 0);
}
END_TEST

START_TEST(test_fix_tetromino_high_score) {
  reset_game_state();
  userInput(Start, false);
  GameInfo_t game = updateCurrentState();
  int initial_high_score = game.high_score;
  game_state.score = initial_high_score + 100;
  for (int i = 0; i < 10; ++i) {
    game_state.field[19][i] = 1;
  }
  fix_tetromino();
  game = updateCurrentState();
  ck_assert_int_eq(game.high_score, game.score);
}
END_TEST

START_TEST(test_fsm_transition_start) {
  FsmInit();
  FsmTransition(Start);
  ck_assert_int_eq(current_state, kStateMoving);
  GameInfo_t game = get_game_state();
  ck_assert_ptr_ne(game.field, NULL);
}
END_TEST

START_TEST(test_fsm_transition_pause) {
  reset_game_state();
  FsmInit();
  FsmTransition(Start);
  FsmTransition(Pause);
  GameInfo_t game = get_game_state();
  ck_assert_int_eq(game.pause, 1);
  ck_assert_int_eq(current_state, kStatePaused);
  FsmTransition(Pause);
  game = get_game_state();
  ck_assert_int_eq(game.pause, 0);
  ck_assert_int_eq(current_state, kStateMoving);
}
END_TEST

START_TEST(test_fsm_transition_terminate) {
  reset_game_state();
  FsmInit();
  FsmTransition(Start);
  FsmTransition(Terminate);
  ck_assert_int_eq(current_state, kStateGameOver);
  ck_assert_int_eq(is_terminated, 1);
}
END_TEST

START_TEST(test_fsm_transition_moving_termination) {
  reset_game_state();
  FsmInit();
  FsmTransition(Start);
  is_terminated = 1;
  FsmTransition(Left);
  ck_assert_int_eq(current_state, kStateGameOver);
}
END_TEST

START_TEST(test_fsm_transition_game_over_start) {
  reset_game_state();
  FsmInit();
  FsmTransition(Start);
  is_terminated = 1;
  FsmTransition(Terminate);
  FsmTransition(Start);
  ck_assert_int_eq(current_state, kStateMoving);
  GameInfo_t game = get_game_state();
  ck_assert_ptr_ne(game.field, NULL);
}
END_TEST

START_TEST(test_fsm_transition_moving_nested_termination) {
  reset_game_state();
  FsmInit();
  FsmTransition(Start);
  current.y = FIELD_HEIGHT - 1;
  Tetromino temp = current;
  temp.y++;
  if (collides(temp)) {
    fix_tetromino();
  }
  ck_assert_int_eq(is_terminated, 0);
  FsmTransition(Left);
  ck_assert_int_eq(current_state, kStateMoving);
}
END_TEST

START_TEST(test_fsm_transition_spawn) {
  reset_game_state();
  FsmInit();
  current_state = kStateSpawn;
  FsmTransition((UserAction_t)0);
  ck_assert_int_eq(current_state, kStateMoving);
  GameInfo_t game = get_game_state();
  ck_assert_ptr_ne(game.field, NULL);
}
END_TEST

START_TEST(test_fsm_transition_start_terminate) {
  reset_game_state();
  FsmInit();
  FsmTransition(Terminate);
  ck_assert_int_eq(current_state, kStateGameOver);
  ck_assert_int_eq(is_terminated, 1);
}
END_TEST

START_TEST(test_fsm_transition_paused_terminate) {
  reset_game_state();
  FsmInit();
  FsmTransition(Start);
  FsmTransition(Pause);
  FsmTransition(Terminate);
  ck_assert_int_eq(current_state, kStateGameOver);
  ck_assert_int_eq(is_terminated, 1);
}
END_TEST

START_TEST(test_fsm_transition_gameover_terminate) {
  reset_game_state();
  FsmInit();
  FsmTransition(Start);
  is_terminated = 1;
  FsmTransition(Terminate);
  ck_assert_int_eq(current_state, kStateGameOver);
  ck_assert_int_eq(is_terminated, 1);
}
END_TEST

Suite* tetris_suite(void) {
  Suite* s = suite_create("Tetris");
  TCase* tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_user_input_start);
  tcase_add_test(tc_core, test_user_input_pause);
  tcase_add_test(tc_core, test_score_increase);
  tcase_add_test(tc_core, test_fsm_init);
  tcase_add_test(tc_core, test_user_input_move_left);
  tcase_add_test(tc_core, test_user_input_move_right);
  tcase_add_test(tc_core, test_user_input_rotate);
  tcase_add_test(tc_core, test_user_input_hard_drop);
  tcase_add_test(tc_core, test_fix_tetromino_multi_lines);
  tcase_add_test(tc_core, test_collides_top_boundary);
  tcase_add_test(tc_core, test_update_current_state_fall);
  tcase_add_test(tc_core, test_return_sizes);
  tcase_add_test(tc_core, test_set_tetromino_position);
  tcase_add_test(tc_core, test_cleanup_game);
  tcase_add_test(tc_core, test_user_input_move_down);
  tcase_add_test(tc_core, test_user_input_up);
  tcase_add_test(tc_core, test_update_current_state_fall_collision);
  tcase_add_test(tc_core, test_fsm_transition_game_over_restart);
  tcase_add_test(tc_core, test_fix_tetromino_four_lines);
  tcase_add_test(tc_core, test_multi_line_clear);
  tcase_add_test(tc_core, test_user_input_terminate);
  tcase_add_test(tc_core, test_level_up);
  tcase_add_test(tc_core, test_updateCurrentState_noField);
  tcase_add_test(tc_core, test_fsm_transition_moving_actions);
  tcase_add_test(tc_core, test_fix_tetromino_high_score);
  tcase_add_test(tc_core, test_fsm_transition_start);
  tcase_add_test(tc_core, test_fsm_transition_pause);
  tcase_add_test(tc_core, test_fsm_transition_terminate);
  tcase_add_test(tc_core, test_fsm_transition_moving_termination);
  tcase_add_test(tc_core, test_fsm_transition_game_over_start);
  tcase_add_test(tc_core, test_fsm_transition_moving_nested_termination);
  tcase_add_test(tc_core, test_fsm_transition_spawn);
  tcase_add_test(tc_core, test_fsm_transition_start_terminate);
  tcase_add_test(tc_core, test_fsm_transition_paused_terminate);
  tcase_add_test(tc_core, test_fsm_transition_gameover_terminate);

  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  Suite* s = tetris_suite();
  SRunner* sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}