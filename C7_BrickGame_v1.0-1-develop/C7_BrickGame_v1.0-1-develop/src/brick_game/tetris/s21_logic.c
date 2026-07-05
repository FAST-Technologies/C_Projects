#define _POSIX_C_SOURCE 200809L
#include "s21_logic.h"

static const char* HIGH_SCORE_FILE = "high_score.txt";
static bool timer_initialized = false;

// Array of tetromino shapes with all rotations (4 for I, L, J, S, Z, T, O).
const int SHAPES[7][4][4][4] = {
    // I
    {{{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},   // Horizontal
     {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}},   // Vertical
     {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},   // Horizontal
     {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}},  // Vertical
    // L
    {{{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}},
     {{0, 1, 1, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
     {{0, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}},
    // J
    {{{0, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}},
     {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
     {{0, 1, 1, 1}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}},
    // S
    {{{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},
     {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
     {{0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}},
    // Z
    {{{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
     {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
     {{0, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}},
    // T
    {{{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}},
     {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
     {{0, 1, 1, 1}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
     {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}},
    // O
    {{{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
     {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}}};

Tetromino current = {4, 0, 0, {{0}}};
Tetromino next = {0, 0, 0, {{0}}};
GameInfo_t game_state = {0};
const int FIELD_HEIGHT = 20;
const int FIELD_WIDTH = 10;
struct timespec last_fall_time = {0, 0};
int is_terminated;

// Initializes the game state, allocating memory for the field and next
// tetromino.
void init_game(void) {
  if (game_state.field || is_terminated) return;
  game_state.field = (int**)malloc(FIELD_HEIGHT * sizeof(int*));
  if (!game_state.field) exit(1);
  for (int i = 0; i < FIELD_HEIGHT; ++i) {
    game_state.field[i] = (int*)calloc(FIELD_WIDTH, sizeof(int));
    if (!game_state.field[i]) exit(1);
  }
  game_state.next = (int**)malloc(4 * sizeof(int*));
  if (!game_state.next) exit(1);
  for (int i = 0; i < 4; ++i) {
    game_state.next[i] = (int*)calloc(4, sizeof(int));
    if (!game_state.next[i]) exit(1);
  }
  game_state.score = 0;
  game_state.high_score = 0;
  FILE* fp = fopen(HIGH_SCORE_FILE, "r");
  if (fp) {
    fscanf(fp, "%d", &game_state.high_score);
    fclose(fp);
  }
  game_state.level = 1;
  game_state.speed = 500;
  game_state.pause = 0;
  is_terminated = 0;
  srand(time(NULL));
  current = generate_random_tetromino();
  next = generate_random_tetromino();
  clock_gettime(CLOCK_MONOTONIC, &last_fall_time);
  timer_initialized = true;
}

// Frees allocated memory and saves high score to file.
void cleanup_game(void) {
  if (game_state.field) {
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
      free(game_state.field[i]);
    }
    free(game_state.field);
  }
  if (game_state.next) {
    for (int i = 0; i < 4; ++i) {
      free(game_state.next[i]);
    }
    free(game_state.next);
  }
  FILE* fp = fopen(HIGH_SCORE_FILE, "w");
  if (fp) {
    fprintf(fp, "%d", game_state.high_score);
    fclose(fp);
  }
  game_state.field = NULL;
  game_state.next = NULL;
  is_terminated = 1;
  timer_initialized = false;
}

// Checks if a tetromino collides with the field boundaries or other blocks.
bool collides(Tetromino tetro) {
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      if (tetro.shape[y][x]) {
        int new_x = tetro.x + x;
        int new_y = tetro.y + y;
        if (new_x < 0 || new_x >= FIELD_WIDTH || new_y < 0 ||
            new_y >= FIELD_HEIGHT || game_state.field[new_y][new_x]) {
          return true;
        }
      }
    }
  }
  return false;
}

// Rotates the tetromino by selecting the next rotation from SHAPES array.
void rotate_tetromino(Tetromino* tetro) {
  int shape_idx = -1;
  for (int i = 0; i < 7; ++i) {
    if (memcmp(tetro->shape, SHAPES[i][tetro->rotation],
               sizeof(tetro->shape)) == 0) {
      shape_idx = i;
      break;
    }
  }
  if (shape_idx != -1) {
    tetro->rotation = (tetro->rotation + 1) % 4;
    memcpy(tetro->shape, SHAPES[shape_idx][tetro->rotation],
           sizeof(tetro->shape));
  }
}

// Places the current tetromino onto the game field.
void place_tetromino(void) {
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      if (current.shape[y][x]) {
        int field_y = current.y + y;
        int field_x = current.x + x;
        if (field_y >= 0 && field_y < FIELD_HEIGHT) {
          game_state.field[field_y][field_x] = 1;
        }
      }
    }
  }
}

// Checks and clears full lines, returning the number of lines cleared.
int clear_full_lines(void) {
  int lines_cleared = 0;
  for (int y = FIELD_HEIGHT - 1; y >= 0; --y) {
    bool full = true;
    for (int x = 0; x < FIELD_WIDTH; ++x) {
      if (!game_state.field[y][x]) {
        full = false;
        break;
      }
    }
    if (full) {
      ++lines_cleared;
      for (int move_y = y; move_y > 0; --move_y) {
        for (int x = 0; x < FIELD_WIDTH; ++x) {
          game_state.field[move_y][x] = game_state.field[move_y - 1][x];
        }
      }
      for (int x = 0; x < FIELD_WIDTH; ++x) {
        game_state.field[0][x] = 0;
      }
      ++y;
    }
  }
  return lines_cleared;
}

// Updates the score based on the number of lines cleared.
void update_score(int lines_cleared) {
  switch (lines_cleared) {
    case 1:
      game_state.score += 100;
      break;
    case 2:
      game_state.score += 300;
      break;
    case 3:
      game_state.score += 700;
      break;
    case 4:
      game_state.score += 1500;
      break;
  }
  if (game_state.score > game_state.high_score) {
    game_state.high_score = game_state.score;
  }
}

// Updates the game level and speed based on the score.
void update_level(void) {
  if (game_state.score >= game_state.level * 600 && game_state.level < 10) {
    game_state.level++;
    game_state.speed = 500 - (game_state.level - 1) * 50;
    if (game_state.speed < 50) game_state.speed = 50;
  }
}

// Resets the current and next tetromino for the next turn.
void reset_tetrominos(void) {
  current = next;
  current.x = 4;
  current.y = 0;
  next = generate_random_tetromino();
}

// Checks for game termination condition after tetromino reset.
void check_termination(void) {
  if (collides(current)) {
    is_terminated = 1;
  }
  clock_gettime(CLOCK_MONOTONIC, &last_fall_time);
}

// Main function to fix the tetromino and update game state.
void fix_tetromino(void) {
  place_tetromino();
  int lines_cleared = clear_full_lines();
  update_score(lines_cleared);
  update_level();
  reset_tetrominos();
  check_termination();
}

// Initializes or restarts the game based on the current state.
void handle_start_action(void) {
  if (is_terminated) {
    cleanup_game();
    is_terminated = 0;
    init_game();
  }
}

// Toggles the pause state.
void handle_pause_action(void) { game_state.pause = !game_state.pause; }

// Moves the tetromino horizontally if no collision.
void handle_horizontal_move(int dx, bool hold) {
  if (!hold) {
    Tetromino temp = current;
    temp.x += dx;
    if (!collides(temp)) {
      current.x = temp.x;
    }
  }
}

// Handles the Down action (soft or hard drop).
void handle_down_action(bool hold) {
  Tetromino temp = current;
  if (hold) {
    while (!collides(temp)) {
      current = temp;
      temp.y++;
    }
    fix_tetromino();
  } else {
    temp.y++;
    if (!collides(temp)) {
      current.y = temp.y;
    } else {
      fix_tetromino();
    }
  }
}

// Rotates the tetromino if no collision.
void handle_action_rotate(bool hold) {
  if (!hold) {
    Tetromino temp = current;
    rotate_tetromino(&temp);
    if (!collides(temp)) {
      current = temp;
    }
  }
}

// Processes user input to control the tetromino.
void userInput(UserAction_t action, bool hold) {
  if (!game_state.field && !is_terminated && action == Start) {
    init_game();
    return;
  }

  if (!game_state.field) return;
  if (game_state.pause && action != Pause && action != Terminate) return;
  if (is_terminated && action != Start && action != Terminate) return;

  switch (action) {
    case Start:
      handle_start_action();
      break;
    case Pause:
      handle_pause_action();
      break;
    case Terminate:
      cleanup_game();
      break;
    case Left:
      handle_horizontal_move(-1, hold);
      break;
    case Right:
      handle_horizontal_move(1, hold);
      break;
    case Down:
      handle_down_action(hold);
      break;
    case Up:
      break;
    case Action:
      handle_action_rotate(hold);
      break;
  }
}

// Updates the game state, moving the tetromino down periodically.
GameInfo_t updateCurrentState(void) {
  if (!game_state.field) {
    return game_state;
  }

  if (!game_state.pause && !is_terminated && timer_initialized) {
    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    long long elapsed_ms =
        (current_time.tv_sec - last_fall_time.tv_sec) * 1000LL +
        (current_time.tv_nsec - last_fall_time.tv_nsec) / 1000000LL;

    if (elapsed_ms >= game_state.speed) {
      Tetromino temp = current;
      temp.y++;
      if (!collides(temp)) {
        current.y = temp.y;
      } else {
        fix_tetromino();
      }
      last_fall_time = current_time;
    }
  }

  if (game_state.next) {
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        game_state.next[i][j] = next.shape[i][j];
      }
    }
  }

  return game_state;
}

// Resets the game state to initial conditions.
void reset_game_state(void) {
  if (game_state.field) cleanup_game();
  is_terminated = 0;
  init_game();
}

// Returns a copy of the current tetromino.
Tetromino get_current_tetromino(void) { return current; }

// Returns the current game state.
GameInfo_t get_game_state(void) { return game_state; }

// Returns the dimensions of the game field.
FieldSizes return_sizes(void) {
  FieldSizes sizes = {FIELD_WIDTH, FIELD_HEIGHT};
  return sizes;
}

// Sets the position of the current tetromino.
void set_tetromino_position(int x, int y) {
  current.x = x;
  current.y = y;
}

// Generates a random tetromino with initial rotation.
Tetromino generate_random_tetromino(void) {
  Tetromino t;
  t.x = 4;
  t.y = 0;
  t.rotation = 0;
  int shape_idx = rand() % 7;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      t.shape[i][j] = SHAPES[shape_idx][0][i][j];
    }
  }
  return t;
}