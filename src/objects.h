#pragma  once

#include <raylib.h>

// typedef enum {SPHERE, CUBE} OBJ_TYPE;

#define SELECTED_COLOR GOLD

#define AXIS_MAX_LENGTH 1.0
#define AXIS_MIN_LENGTH 0.1
typedef struct {
    // when moving object, axis will automatically move with it
    Vector3 offset; // depends on center of obj (will be center of axis)
    float width;
    float height;
    float length;
    Color color;
    bool is_selected;
    // used to move it, we only need one direction,
    // ex x axis moves only on the x
    float last_touched_position;
} Axis;

Axis axis_new_x();
Axis axis_new_y();
Axis axis_new_z();

// obj pos is parent location
// ex in sphere pass sphere pos
void axes_render(Axis axes[3], Vector3 obj_pos);
void axis_move(Ray* ray, Axis axes[3], Vector3* obj_pos);


typedef struct {
    Vector3 position; // of center
    float radius;

    Color color;
    Axis axes[3];
} Sphere;

Sphere sphere_create(Vector3 position, float radius, Color color);

void sphere_render(Sphere* sphere);


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

