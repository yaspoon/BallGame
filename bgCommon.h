#ifndef BG_COMMON
#define BG_COMMON

#define BALLGAME BallGame::instance()

typedef enum { C_IMMOVABLE, C_MOVEABLE } COLLIDABLE;

typedef struct Rect_s {
  float x;
  float y;

  float prevX;
  float prevY;

  int w;
  int h;
} Rect;

typedef struct {
    float x;
    float y;
} vec2;

typedef struct {
    vec2 top;
    vec2 left;
}axes;

typedef struct {
    float min;
    float max;
} projection;

#endif
