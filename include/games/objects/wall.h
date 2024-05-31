//
// Created by mspt5 on 24-5-31.
//

#ifndef PROJ3_WALL_H
#define PROJ3_WALL_H

typedef struct {
    double last_pos_x;
    double pos_x;
    u16 width;
    u16 pos_y;
} Wall;

/// draw the wall
/// \param wall
void DrawWall(Wall *wall);

/// update wall position. attention, flash the wall at last position will be done here
/// \param wall
void UpdateWall(Wall *wall);

/// initial wall pos and width by random
/// \param wall
void InitialWall(Wall *wall);

#endif //PROJ3_WALL_H
