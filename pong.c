#include <stdio.h>

void print_screen(int ball_x, int ball_y, int left_y, int right_y, int score_l, int score_r);
int update_paddle(int current_y, char input, char up_key, char down_key, int height);
int check_victory(int score_left, int score_right);

int main(void) {
    int width = 80, height = 25, left_paddle_y = 12, right_paddle_y = 12, ball_x = 40, ball_y = 12,
     ball_dx = 1, ball_dy = 1, score_left = 0, score_right = 0, game_running = 1;

    while (game_running == 1) {
        print_screen(ball_x, ball_y, left_paddle_y, right_paddle_y, score_left, score_right);

        if (check_victory(score_left, score_right) == 1) game_running = 0;

        if (game_running == 1) {
            char input_char = ' ';
            int valid_input = 0;
            while (valid_input == 0) {
                printf("Введите A/Z для P1, K/M for P2, пробел чтобы пропустить + ENTER: ");
                if (scanf("%c", &input_char) == 1) {
                    char clear_char = ' ';
                    while (input_char != '\n' && scanf("%c", &clear_char) == 1 && clear_char != '\n') {
                    }
                    if (input_char == 'A' || input_char == 'a' || input_char == 'Z' || input_char == 'z' ||
                        input_char == 'K' || input_char == 'k' || input_char == 'M' || input_char == 'm' ||
                        input_char == ' ') {
                        valid_input = 1;
                    }
                }
            }
            left_paddle_y = update_paddle(left_paddle_y, input_char, 'A', 'Z', height);
            right_paddle_y = update_paddle(right_paddle_y, input_char, 'K', 'M', height);
            ball_x += ball_dx, ball_y += ball_dy;
            if (ball_y <= 1 || ball_y >= height - 2) ball_dy = -ball_dy;
            if (ball_x == 3 &&
                (ball_y == left_paddle_y - 1 || ball_y == left_paddle_y || ball_y == left_paddle_y + 1))
                ball_dx = -ball_dx;
            if (ball_x == width - 4 &&
                (ball_y == right_paddle_y - 1 || ball_y == right_paddle_y || ball_y == right_paddle_y + 1))
                ball_dx = -ball_dx;
            if (ball_x <= 0) score_right++, ball_x = 40, ball_y = 12, ball_dx = 1;
            if (ball_x >= width - 1) score_left++, ball_x = 40, ball_y = 1, ball_dx = -1;
        }
    }
}

void print_screen(int ball_x, int ball_y, int left_y, int right_y, int score_l, int score_r) {
    for (int i = 0; i < 25; i++) printf("\n");
    printf("               ИГРОК 1: %d                        ИГРОК 2: %d\n", score_l, score_r);
    for (int y = 0; y < 25; y++) {
        for (int x = 0; x < 80; x++) {
            if (y == 0 || y == 24)
                printf("-");
            else if (x == 0 || x == 79 || x == 40)
                printf("|");
            else if (x == ball_x && y == ball_y)
                printf("o");
            else if (x == 2 && (y == left_y - 1 || y == left_y || y == left_y + 1))
                printf("[");
            else if (x == 77 && (y == right_y - 1 || y == right_y || y == right_y + 1))
                printf("]");
            else
                printf(" ");
        }
        printf("\n");
    }
}

int update_paddle(int current_y, char input, char up_key, char down_key, int height) {
    int res_y = current_y;
    if ((input == up_key || input == (up_key + 32)) && current_y > 2) {
        res_y--;
    }
    if ((input == down_key || input == (down_key + 32)) && current_y < height - 3) {
        res_y++;
    } 
    return res_y;
}

int check_victory(int score_left, int score_right) {
    int victory = 0;
    if (score_left == 21) {
        printf("ИГРОК 1 ПОБЕДИЛ!\n");
        victory = 1;
    }
    if (score_right == 21) {
        printf("ИГРОК 2 ПОБЕДИЛ!\n");
        victory = 1;
    }
    return victory;
}
