#include "s21_finite_state_machine.h"

GameState current_state = kStateStart;

// Inites state ising kStateStart.
void FsmInit(void) { current_state = kStateStart; }

// Handles transitions from kStateStart.
void handle_state_start(UserAction_t action) {
  if (action == Start) {
    current_state = kStateMoving;
    userInput(Start, false);
  } else if (action == Terminate) {
    current_state = kStateGameOver;
    userInput(Terminate, false);
  }
}

// Handles transitions from kStateSpawn.
void handle_state_spawn(void) { current_state = kStateMoving; }

// Handles action-specific transitions in kStateMoving.
void handle_moving_action(UserAction_t action) {
  switch (action) {
    case Pause:
      current_state = kStatePaused;
      userInput(Pause, false);
      break;
    case Terminate:
      current_state = kStateGameOver;
      userInput(Terminate, false);
      break;
    case Left:
    case Right:
    case Down:
    case Action:
      userInput(action, false);
      if (is_terminated) {
        current_state = kStateGameOver;
      }
      break;
    default:
      break;
  }
}

// Handles transitions from kStateMoving.
void handle_state_moving(UserAction_t action) {
  if (is_terminated) {
    current_state = kStateGameOver;
    return;
  }
  handle_moving_action(action);
}

// Handles transitions from kStatePaused.
void handle_state_paused(UserAction_t action) {
  if (action == Pause) {
    current_state = kStateMoving;
    userInput(Pause, false);
  } else if (action == Terminate) {
    current_state = kStateGameOver;
    userInput(Terminate, false);
  }
}

// Handles transitions from kStateGameOver.
void handle_state_game_over(UserAction_t action) {
  if (action == Start) {
    current_state = kStateStart;
    FsmTransition(Start);
  } else if (action == Terminate) {
    userInput(Terminate, false);
  }
}

// Main function to transition between states.
void FsmTransition(UserAction_t action) {
  switch (current_state) {
    case kStateStart:
      handle_state_start(action);
      break;
    case kStateSpawn:
      handle_state_spawn();
      break;
    case kStateMoving:
      handle_state_moving(action);
      break;
    case kStatePaused:
      handle_state_paused(action);
      break;
    case kStateGameOver:
      handle_state_game_over(action);
      break;
  }
}