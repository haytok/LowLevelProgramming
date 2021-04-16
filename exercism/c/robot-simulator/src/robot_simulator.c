#include "robot_simulator.h"

robot_status_t robot_create(robot_direction_t direction, int x, int y) {
    robot_status_t status;
    status.direction = direction;
    status.position = (robot_position_t){.x = x, .y = y};
    return status;
}

void robot_move(robot_status_t * robot, const char *commands) {
    char *head = malloc(sizeof(char) * 1024);
    // 文字列の先頭アドレスのコピーは memcpy を使うと良い。
    memcpy(head, commands, 1024);
    while (*head) {
        if (strncmp(head, "R", 1) == 0) {
            robot->direction++;
            robot->direction %= DIRECTION_MAX;
        } else if (strncmp(head, "L", 1) == 0) {
            robot->direction--;
            robot->direction %= DIRECTION_MAX;
        } else if (strncmp(head, "A", 1) == 0) {
            switch (robot->direction) {
                case DIRECTION_NORTH: {
                    robot->position.y++;
                    break;
                }
                case DIRECTION_EAST: {
                    robot->position.x++;
                    break;
                }
                case DIRECTION_SOUTH: {
                    robot->position.y--;
                    break;
                }
                case DIRECTION_WEST: {
                    robot->position.x--;
                    break;
                }
                default: {
                    break;
                }
            }
        }
        head++;
    }
}
