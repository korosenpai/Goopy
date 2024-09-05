#pragma  once

#include <raylib.h>

// typedef enum {SPHERE, CUBE} OBJ_TYPE;

#define SELECTED_COLOR GOLD

#define AXIS_MAX_LENGTH 1.0
#define AXIS_MIN_LENGTH 0.1
typedef struct {
    Vector3 offset; // depends on center of obj (will be center of axis)
    float width;
    float height;
    float length;
    Vector3 last_touched_position; // used to move it
} Axis;

Axis axis_new_x();
Axis axis_new_y();
Axis axis_new_z();

typedef struct {
    Vector3 position; // of center
    float radius;

    Color color;
    // bool is_selected // TODO:
    Axis axes[3];
} Sphere;


typedef struct {
    Vector3 position;
    float width;
    float height;
    float length;
    Color color;
} Cube;

typedef struct {} Octahedron;
typedef struct {} Capsule;
typedef struct {} Cylinder;
typedef struct {} Torus;
typedef struct {} Ellipsoid;


Sphere sphere_create(Vector2 position);
