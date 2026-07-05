CC = gcc
CFLAGS = -D_POSIX_C_SOURCE=200809L -std=c11 -Wall -Wextra -Werror -pedantic -g
LDFLAGS = -lncurses -lcheck -lm -lpthread -lrt -lsubunit

SRC_DIR = .
TETRIS_DIR = $(SRC_DIR)/brick_game/tetris
GUI_DIR = $(SRC_DIR)/brick_game/gui/cli
TEST_DIR = $(SRC_DIR)/tests
DOCS_DIR = docs

TETRIS_SRC = $(TETRIS_DIR)/s21_finite_state_machine.c $(TETRIS_DIR)/s21_logic.c
GUI_SRC = $(GUI_DIR)/s21_interface.c
TEST_SRC = $(TEST_DIR)/s21_test_*.c

OBJ_DIR = obj
OBJECTS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(TETRIS_SRC) $(GUI_SRC)))

TARGET = brick_game_tetris
TEST_TARGET = s21_test_brick_game
INSTALL_DIR = /usr/local/s21_brick_game
DOCUMENTATION_REPO = brickgame_documentation.html
DOCUMENTATION_INSTALL_REPO = brickgame_install_documentation.html

OS := $(shell uname -s)
ifeq ($(OS),Darwin)
    MEMCHECK_CMD = leaks -atExit --
    OPEN_CMD = open
else
    MEMCHECK_CMD = valgrind --tool=memcheck --leak-check=full \
               --track-origins=yes --show-leak-kinds=all \
               --suppressions=ncurses.supp
    OPEN_CMD = xdg-open
endif

all: format build test gcov_report cppcheck memcheck

build: $(TARGET)

$(OBJ_DIR)/%.o: $(TETRIS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(GUI_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

$(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO):
	@echo "Generating documentation to install directory..."
	@test -f tetris_pieces.png || { echo "Error: tetris_pieces.png not found"; exit 1; }
	@cp tetris_pieces.png $(INSTALL_DIR)/
	@echo "<!DOCTYPE html>" > $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "<html lang=\"en\">" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "<head>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <meta charset=\"UTF-8\">" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <title>BrickGame v1.0 - Tetris Documentation</title>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <style>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        body { font-family: Arial, sans-serif; margin: 20px; }" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        h1 { color: #333; }" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        h2 { color: #555; }" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        p { line-height: 1.6; }" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        ul { list-style-type: disc; margin-left: 20px; }" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        img { max-width: 100%; height: auto; }" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    </style>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "</head>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "<body>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <h1>BrickGame v1.0 - Tetris Documentation</h1>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <p>This is a BrickGame game, made for all people who love pixel games! Here you can read the rules and details you need to know to play this modification.</p>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <h2>Game Overview</h2>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <p>Every time in space, a block called a Tetromino appears. All Tetromino forms can be seen in the <code>misc/images</code> directory. These blocks fall down automatically, but you can move them left or right using the arrow keys. The game takes place on a field that is 10 pixels wide and 20 pixels high.</p>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <p>When one or more rows are completely filled, they disappear, and you earn score points:</p>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <ul>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li>1 row: 100 points</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li>2 rows: 300 points</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li>3 rows: 700 points</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li>4 rows: 1500 points</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    </ul>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <p>If your blocks reach the top of the field, you lose, and your score is saved to the <code>high_score.txt</code> file.</p>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <h2>Game Mechanics</h2>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <ul>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li><strong>Rotation:</strong> Rotate Tetrominoes using the spacebar.</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li><strong>Horizontal Movement:</strong> Move Tetrominoes left or right with the arrow keys.</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li><strong>Fast Drop:</strong> Press the down arrow and hold to move the Tetromino to the bottom instantly.</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li><strong>Next Figure Preview:</strong> A special window shows the next Tetromino to help you plan your moves.</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li><strong>Line Clearing:</strong> Completed rows disappear, increasing your score.</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li><strong>Game Over:</strong> The game ends if blocks reach the top of the field.</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li><strong>Tetromino Shapes:</strong> The game includes all standard Tetromino shapes (see image below).</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    </ul>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <img src=\"tetris_pieces.png\" alt=\"Tetromino Shapes\">" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <h2>Levels and Speed</h2>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <p>The game features a leveling system. Each time you earn 600 points, your level increases by 1, up to a maximum of 10 levels. With each level, the speed of the falling Tetrominoes increases (speed decreases from 500ms, reducing by 50ms per level). Be careful as the game gets faster!</p>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <ul>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li><strong>Start (s):</strong> Begin the game.</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li><strong>Pause (p):</strong> Pause or resume the game.</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li><strong>Quit (q):</strong> End the game (note: your current score will be lost, but the high score remains).</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li><strong>Left Arrow:</strong> Move Tetromino left.</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li><strong>Right Arrow:</strong> Move Tetromino right.</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li><strong>Down Arrow:</strong> Move Tetromino down (hold for fast drop).</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li><strong>Up Arrow:</strong> Not used in this game.</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li><strong>Spacebar:</strong> Rotate Tetromino.</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    </ul>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <h2>Technical Details</h2>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <h3>Part 1: Main Assignment</h3>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <p>The program is developed in C11 using gcc, consisting of:</p>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <ul>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li>A library in <code>src/brick_game/tetris</code> implementing Tetris logic with a finite state machine.</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li>A terminal interface in <code>src/gui/cli</code> using <code>ncurses</code>.</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li>The library includes functions for user input and returning the game field matrix.</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li>Build configured with Makefile (targets: all, install, uninstall, clean, dvi, dist, test, gcov_report).</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li>Adheres to Google Style and structural programming principles.</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li>Covered by unit tests with <code>check</code> library (80%+ coverage on Darwin/Ubuntu).</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li>Field size: 10x20 pixels.</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li>Requires a diagram of the finite state machine (states and transitions).</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    </ul>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <h3>Part 2: Score and High Score</h3>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <p>Features:</p>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <ul>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li>Score tracking displayed in a sidebar.</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li>High score saved to <code>high_score.txt</code> and updated if exceeded.</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    </ul>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <h3>Part 3: Level Mechanics</h3>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <p>Includes a leveling system:</p>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <ul>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li>Level increases by 1 every 600 points (max 10 levels).</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "        <li>Speed increases with each level (500ms initial, -50ms per level).</li>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    </ul>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <h2>Author</h2>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "    <p>Good luck, guy. One day you are going to reach the top and become the king of Tetris!  P.S: Vladimir (F.A.S.T aka norreyll), the s21_BrickGame project writer!</p>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "</body>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "</html>" >> $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO)
	@echo "Generating documentation process to install directory finished successfully!"

install: $(TARGET) $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO) dvi
	@mkdir -p $(INSTALL_DIR)
	@cp $(TARGET) $(INSTALL_DIR)
	@echo "Installation complete. Binary installed to $(INSTALL_DIR)/$(TARGET)"
	@echo "Documentation succesfully saved to $(INSTALL_DIR)/$(CREATE_DOCUMENTATION)"

uninstall:
	@rm -f $(INSTALL_DIR)/$(TARGET) $(INSTALL_DIR)/$(DOCUMENTATION_INSTALL_REPO) $(INSTALL_DIR)/tetris_pieces.png 
	@rm -rf $(DOCS_DIR)
	@echo "Uninstallation complete."

clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TEST_TARGET) coverage *.gcda *.gcno *.info *.gz

dvi: $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "Documentation of BrickGame V1.0"
	@echo "This is a BrickGame game, made for all of people, who love pixel games!"
	@echo "Here you can read some rules, that you need to know to play this modification"
	@echo "Everytime in space a block appearing. This block called Tetromino."
	@echo "All of Tetromino forms you can see in misc/images directory"
	@echo "In fact, all of this blocks are falling down."
	@echo "But you can move them to other directions, such as left or right, using arrows."
	@echo "All of that blocks are placed in a field, 10 pixels in a row and 20 in a column"
	@echo "When you have one or more rows complete, they are dissapearing while you are getting score points"
	@echo "1 row costs 100 points, 2 rows cost 300 points, 3 cost 700 and 4 cost 1500 points"
	@echo "If your blocks reach the top, you lose, and your scores are writing to high_score.txt file"
	@echo "There are more than 10 levels of the game, that you achive after each 600 points"
	@echo "But remember - each level increase your speed, be careful"
	@echo "As a good and qualified brickgame, you can rotate Tetromino, using space button"
	@echo "There is a special window, where you can see the next figure that might help tou to play more accurate"
	@echo "If you are certain in your decision, press bottom arrow to make it faster!"
	@echo "To start the game, press a Start (s) button"
	@echo "If you want to make a relax, press Pause (p) button"
	@echo "But if you are dissapointed in a game - you can quit, using your (q) button"
	@echo "Remember - in that case you will lose your result, plunging it into the abyss..."
	@echo "But one thing will left - the finite state machine will do all to let you stay here"
	@echo "In a classic pixel BrickGame!"
	@echo "Good luck, guy. One day you are gonna to reach the top and become a king of Tetris)"
	@echo "P.S: Vladimir (F.A.S.T aka norreyll), a s21_BrickGame project writer!"
	@echo "Opening HTML documentation..."
	@$(OPEN_CMD) $(DOCS_DIR)/$(DOCUMENTATION_REPO) 2>/dev/null || echo "Unable to open browser automatically. Please open $(DOCS_DIR)/$(DOCUMENTATION_REPO) manually."
	@echo "Thanks for checking our HTML documentation :)"

$(DOCS_DIR)/$(DOCUMENTATION_REPO):
	@mkdir -p $(DOCS_DIR)
	@echo "Generating documentation..."
	@test -f tetris_pieces.png || { echo "Error: tetris_pieces.png not found"; exit 1; }
	@cp tetris_pieces.png $(DOCS_DIR)/
	@echo "<!DOCTYPE html>" > $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "<html lang=\"en\">" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "<head>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <meta charset=\"UTF-8\">" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <title>BrickGame v1.0 - Tetris Documentation</title>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <style>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        body { font-family: Arial, sans-serif; margin: 20px; }" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        h1 { color: #333; }" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        h2 { color: #555; }" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        p { line-height: 1.6; }" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        ul { list-style-type: disc; margin-left: 20px; }" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        img { max-width: 100%; height: auto; }" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    </style>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "</head>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "<body>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <h1>BrickGame v1.0 - Tetris Documentation</h1>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <p>This is a BrickGame game, made for all people who love pixel games! Here you can read the rules and details you need to know to play this modification.</p>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <h2>Game Overview</h2>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <p>Every time in space, a block called a Tetromino appears. All Tetromino forms can be seen in the <code>misc/images</code> directory. These blocks fall down automatically, but you can move them left or right using the arrow keys. The game takes place on a field that is 10 pixels wide and 20 pixels high.</p>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <p>When one or more rows are completely filled, they disappear, and you earn score points:</p>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <ul>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li>1 row: 100 points</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li>2 rows: 300 points</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li>3 rows: 700 points</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li>4 rows: 1500 points</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    </ul>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <p>If your blocks reach the top of the field, you lose, and your score is saved to the <code>high_score.txt</code> file.</p>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <h2>Game Mechanics</h2>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <ul>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li><strong>Rotation:</strong> Rotate Tetrominoes using the spacebar.</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li><strong>Horizontal Movement:</strong> Move Tetrominoes left or right with the arrow keys.</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li><strong>Fast Drop:</strong> Press the down arrow and hold to move the Tetromino to the bottom instantly.</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li><strong>Next Figure Preview:</strong> A special window shows the next Tetromino to help you plan your moves.</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li><strong>Line Clearing:</strong> Completed rows disappear, increasing your score.</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li><strong>Game Over:</strong> The game ends if blocks reach the top of the field.</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li><strong>Tetromino Shapes:</strong> The game includes all standard Tetromino shapes (see image below).</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    </ul>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <img src=\"tetris_pieces.png\" alt=\"Tetromino Shapes\">" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <h2>Levels and Speed</h2>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <p>The game features a leveling system. Each time you earn 600 points, your level increases by 1, up to a maximum of 10 levels. With each level, the speed of the falling Tetrominoes increases (speed decreases from 500ms, reducing by 50ms per level). Be careful as the game gets faster!</p>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <h2>Controls</h2>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <ul>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li><strong>Start (s):</strong> Begin the game.</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li><strong>Pause (p):</strong> Pause or resume the game.</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li><strong>Quit (q):</strong> End the game (note: your current score will be lost, but the high score remains).</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li><strong>Left Arrow:</strong> Move Tetromino left.</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li><strong>Right Arrow:</strong> Move Tetromino right.</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li><strong>Down Arrow:</strong> Move Tetromino down (hold for fast drop).</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li><strong>Up Arrow:</strong> Not used in this game.</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li><strong>Spacebar:</strong> Rotate Tetromino.</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    </ul>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <h2>Technical Details</h2>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <h3>Part 1: Main Assignment</h3>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <p>The program is developed in C11 using gcc, consisting of:</p>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <ul>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li>A library in <code>src/brick_game/tetris</code> implementing Tetris logic with a finite state machine.</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li>A terminal interface in <code>src/gui/cli</code> using <code>ncurses</code>.</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li>The library includes functions for user input and returning the game field matrix.</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li>Build configured with Makefile (targets: all, install, uninstall, clean, dvi, dist, test, gcov_report).</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li>Adheres to Google Style and structural programming principles.</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li>Covered by unit tests with <code>check</code> library (80%+ coverage on Darwin/Ubuntu).</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li>Field size: 10x20 pixels.</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li>Requires a diagram of the finite state machine (states and transitions).</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    </ul>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <h3>Part 2: Score and High Score</h3>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <p>Features:</p>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <ul>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li>Score tracking displayed in a sidebar.</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li>High score saved to <code>high_score.txt</code> and updated if exceeded.</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    </ul>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <h3>Part 3: Level Mechanics</h3>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <p>Includes a leveling system:</p>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <ul>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li>Level increases by 1 every 600 points (max 10 levels).</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "        <li>Speed increases with each level (500ms initial, -50ms per level).</li>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    </ul>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <h2>Author</h2>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "    <p>Good luck, guy. One day you are going to reach the top and become the king of Tetris!  P.S: Vladimir (F.A.S.T aka norreyll), the s21_BrickGame project writer!</p>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "</body>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "</html>" >> $(DOCS_DIR)/$(DOCUMENTATION_REPO)
	@echo "Generating documentation process finished successfully!"

dist: dvi
	@echo "Creating distribution archive..."
	@tar -czf brick_game.tar.gz $(TARGET) $(DOCS_DIR)/$(DOCUMENTATION_REPO) $(DOCS_DIR)/tetris_pieces.png diagram/fsm_diagram_graphviz.png diagram/fsm_diagram_graphviz.txt diagram/fsm_diagram.txt
	@echo "Distribution archive brick_game.tar.gz created successfully!"

test:
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_SRC) $(TETRIS_SRC) $(LDFLAGS)
	./$(TEST_TARGET)

gcov_report:
	@echo "Generating coverage report..."
	rm -f coverage.info
	rm -rf coverage
	gcc --coverage $(CFLAGS) -o $(TEST_TARGET) $(TEST_SRC) $(TETRIS_SRC) $(LDFLAGS)
	./$(TEST_TARGET)
	lcov --capture --directory . --output-file coverage.info \
		--exclude '/usr/*' --exclude '*/tests/*' --ignore-errors unused
	genhtml coverage.info --output-directory coverage --ignore-errors unused
	@echo "Coverage report in coverage/index.html"
	$(OPEN_CMD) coverage/index.html 2>/dev/null || echo "Open coverage/index.html manually"

format:
	@echo "Running clang-format..."
	@clang-format -style=Google -n $(TETRIS_DIR)/s21_*.c $(TETRIS_DIR)/*.h $(GUI_DIR)/s21_*.c $(GUI_DIR)/*.h $(TEST_DIR)/s21_test_*.c > clang_format_output.txt 2>&1 || true
	@if [ -s clang_format_output.txt ]; then \
		echo "Clang-format issues found, applying fixes..."; \
		clang-format -style=Google -i $(TETRIS_DIR)/s21_*.c $(TETRIS_DIR)/*.h $(GUI_DIR)/s21_*.c $(GUI_DIR)/*.h $(TEST_DIR)/s21_test_*.c; \
	else \
		echo "Clang-format is OK"; \
	fi
	@rm -f clang_format_output.txt

cppcheck:
	@echo "Running cppcheck..."
	@cppcheck --enable=all --std=c11 $(TETRIS_DIR)/s21_*.c $(TETRIS_DIR)/*.h $(GUI_DIR)/s21_*.c $(GUI_DIR)/*.h $(TEST_DIR)/s21_test_*.c --suppress=missingIncludeSystem

memcheck: $(TEST_TARGET)
	@echo "Running memory checker..."
	@$(MEMCHECK_CMD) --num-callers=20 ./$(TEST_TARGET)

valgrind: $(TEST_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=ncurses.supp ./$(TEST_TARGET)

leaks:
	leaks --atExit -- ./$(TEST_TARGET)

rebuild: clean all

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: all clean test gcov_report format cppcheck memcheck rebuild install uninstall dvi dist