#include <iostream>

#define ROWS 3
#define COLS 3

#define MAINCHAR '*'
#define RESET(X) (X=0)

const char shape1 = 'x';
const char shape2 = 'o';

const char shape3 = 'X';
const char shape4 = 'O';

int xwin {}, owin {};

class Game {
public:
    int currow_pos {strt_pos(ROWS)}, curcol_pos {strt_pos(ROWS)}; 
public:
    bool render(char arry[ROWS][COLS]) {
        std::cout << std::endl;

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                std::cout << arry[i][j] << ' ';
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;
        return true;
    }

    bool fill_board(char arry[ROWS][COLS], char ch) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                arry[i][j] = ch;
            }
        }

        return true;
    }

    int strt_pos(int rows) {
        return rows/2;
    }

    char takein(int currow_pos, int curcol_pos) {
        char ch;

        std::cout << "Cell" << '[' << currow_pos << ']' << '[' << curcol_pos << ']' << ": ";
        std::cin >> ch;

        return ch;
    }

    bool isValidMove(char moves[], char ch, int n) {
        int s = 0;
        int e = n-1;

        while (s <= e) {
            int mid = (s+e)/2;

            if (moves[mid] == ch) return true;
            else if (moves[mid] > ch) e = mid-1;
            else s = mid+1;
        }

        return false;
    }

    bool sortch(char arry[], int n) {
        int j = 0;
        for (int i = 0; i < n; i++) {
            char curr = arry[i];
            j = i-1;

            while (j >= 0 && arry[j] > curr) {
                arry[j+1] = arry[j];
                j--;
            }
            arry[j+1] = curr;
        }

        return true;
    }

    bool isItFilled(char arry[ROWS][COLS]) {
        if (
            (arry[currow_pos][curcol_pos] == shape1 || arry[currow_pos][curcol_pos] == shape2)
                                               || 
            (arry[currow_pos][curcol_pos] == shape3 || arry[currow_pos][curcol_pos] == shape4)
        ) return true;
        
        return false;
    }

    int move(char arry[ROWS][COLS], char move) {
       /* switch (move) {
            case 'x': arry[currow_pos][curcol_pos] = 'x';
            break;

            case 'o': arry[currow_pos][curcol_pos] = 'o';
            break;

            case 'q': return false;
            break;

            } */

        if (move == shape1 || move == shape3) {
            int x = isItFilled(arry);
            if (x) {
                std::cerr << "There is already a value here!!" << std::endl;
                return true;
            } else {
                arry[currow_pos][curcol_pos] = shape3;
            }
        }

        else if (move == shape2 || move == shape4) {
            int x = isItFilled(arry);
            if (x) {
                std::cerr << "There is already a value here!!" << std::endl;
                return true;
            } else {
                arry[currow_pos][curcol_pos] = shape4;
            }
        }

        else if (move  == 'q') {
            std::cout << "User chose to quit!!" << std::endl;
            exit(0);
        }

        else if (move == 'j') {
            if (currow_pos >= ROWS-1) {
                currow_pos--;
                std::cerr << "You can't move more than that!!" << std::endl;
            }

            currow_pos++;
        }

        else if (move == 'k') {
            if (currow_pos <= 0) {
                currow_pos++;
                std::cerr << "You can't move more than that!!" << std::endl;
            }

            currow_pos--;
        }

        else if (move == 'l') {
            if (curcol_pos >= ROWS-1) {
                curcol_pos--;
                std::cerr << "You can't move more than that!!" << std::endl;
            }

            curcol_pos++;
        }

        else if (move == 'h') {
            if (curcol_pos <= 0) {
                curcol_pos++;
                std::cerr << "You can't move more than that!!" << std::endl;
            }
            curcol_pos--;
        }

        return true;
        }

    void winner(char arry[ROWS][COLS]) {
        char horiWin = hori_win(arry);
        char digon1Win = digon1(arry);
        char digon2Win = digon2(arry);
        char col_win = colm_win(arry);

        if (horiWin == shape1 || digon1Win == shape1 || digon2Win == shape1 || col_win == shape1) {
            render(arry);
            std::cout << shape3 <<  " Won!!" << std::endl;
            exit(0);
        }
        else if (horiWin == shape2 || digon1Win == shape2 || digon2Win == shape2 || col_win == shape2) {
            render(arry);
            std::cout << shape4 << " Won!!" << std::endl;
            exit(0);
        }

        if (isDraw(arry)) {
            std::cout << "Draw!!" << std::endl;
            exit(0);
        }
    }

   char hori_win(char arry[ROWS][COLS]) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (arry[i][j] == shape1 || arry[i][j] == shape3) {
                    xwin += 1;
                }
                else if (arry[i][j] == shape2 || arry[i][j] == shape4) {
                    owin += 1;
                }
            }

            if (xwin == ROWS) return shape1;
            else if (owin == ROWS) return shape2;

            RESET(xwin);
            RESET(owin);
        }
        return 'z';
    }

    char digon1(char arry[ROWS][COLS]) {
        int i = ROWS-1, j = 0;

        while (i >= 0 && j < ROWS) {
            if (arry[i][j] == shape1 || arry[i][j] == shape3) {
                xwin += 1;
            } 
            else if (arry[i][j] == shape2 || arry[i][j] == shape4) {
                owin += 1;
            }

            i--;
            j++;
        }

        if (xwin == ROWS) return shape1;
        else if (owin == ROWS) return shape2;

        RESET(owin);
        RESET(xwin);

        return 'z';
    }


    char digon2(char arry[ROWS][COLS]) {
        int i = 0, j = 0;

        while (i < ROWS && j < ROWS) {
            if (arry[i][j] == shape1 || arry[i][j] == shape3) {
                xwin += 1;
            } 
            else if (arry[i][j] == shape2 || arry[i][j] == shape4) {
                owin += 1;
            }

            i++;
            j++;
        }

        if (xwin == ROWS) return shape1;
        else if (owin == ROWS) return shape2;

        RESET(owin);
        RESET(xwin);

        return 'z';
    }

    char colm_win(char arry[ROWS][COLS]) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < ROWS; j++) {
                if (arry[j][i] == shape1 || arry[j][i] == shape3) {
                    xwin += 1;
                }
                else if (arry[j][i] == shape2 || arry[j][i] == shape4) {
                    owin += 1;
                }
            }

            if (xwin == ROWS) return shape1;
            else if (owin == ROWS) return shape2;

            RESET(owin);
            RESET(xwin);
        }

        return 'z';
    }

    bool isDraw(char arry[ROWS][COLS]) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (arry[i][j] == MAINCHAR) {
                    return false;
                }
            }
        }

        return true;
    }
};

int main() {
    Game main;
    char board[ROWS][COLS];
    main.fill_board(board, MAINCHAR);

    bool quit = true;

    char valid_moves[] = {'j', 'k', 'h', 'l', 'x', 'o', 'X', 'O', 'q'};
    char move;

    int arrlen = sizeof(valid_moves)/sizeof(valid_moves[0]);
    main.sortch(valid_moves, arrlen);

    while (quit) {

        main.render(board);
        move = main.takein(main.currow_pos, main.curcol_pos); // Take input from the user
        if (main.isValidMove(valid_moves, move, arrlen)) {   // If the input is matches moves lsted in array valid_moves
            quit = main.move(board, move);                  // Then check the move and perform a certain action according to it
        }
        else {
            std::cout << "Invalid move!!" << std::endl;             // Else if the input given by user doesn't match valid moves
            main.render(board);                                     // Render the board
            move = main.takein(main.currow_pos, main.curcol_pos);   // and take input again
        }

        main.winner(board);                                         // Check the winner
    }

    return 0;
}
