#ifndef BG_COMMON
#define BG_COMMON
#include <iostream>

#define BALLGAME BallGame::instance()

typedef enum
{
    C_UNKNOWN = 0,
    C_IMMOVABLE,
    C_MOVEABLE
} COLLIDABLE;

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

struct ScreenDimensions
{
    int width;
    int height;
};

struct CollisionResult
{
    bool isColliding;
    vec2 minAxis;
    float minDistance;
};

#define STUB(message) (std::cout << __FILE__ << ":" << __FUNCTION__ << ":" << "Line-" << __LINE__ << ":" << message << std::endl);

#endif
