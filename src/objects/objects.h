#pragma  once

#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>


typedef enum {
    OBJECT_NONE,
    SPHERE,
    CUBE,
    OCTAHEDRON,
    CAPSULE,
    CYLINDER,
    TORUS,
    ELLIPSOID,
} OBJ_TYPE;
#define OBJ_TYPE_STRING "None;Sphere;Cube;Octahedron;Capsule;Cylinder;Torus;Ellipsoid"
// NOTE: when strings used by dropdownmenu, it will give result as int (perf for conversion to enum)
// must be in same order as enum tho

#define OBJ_SELECTED_COLOR GOLD

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

// TODO:?
typedef enum {
    AXIS_NONE,
    AXIS_X,
    AXIS_Y,
    AXIS_Z,
} AXIS_SELECTED;

typedef struct {
    AXIS_SELECTED selected;
    Axis axes[3];
} Axes;


// obj pos is parent location
// ex in sphere pass sphere pos
void axes_render(Axis axes[3], Vector3 obj_pos);
void axes_move(Ray* ray, Axis axes[3], Vector3* obj_pos); // detect if obj needs to be moved


// TODO: add id (position in array; for shader)
#define OBJ_PTR_RENDER(obj_ptr, is_selected) ((obj_ptr)->render(obj_ptr, is_selected))
#define OBJ_RENDER(obj, is_selected) ((obj).render(&(obj), is_selected))
#define OBJ_PTR_SELECT(obj, ray_ptr) ((obj)->select(obj, ray_ptr))
typedef struct Object {
    OBJ_TYPE type;
    Vector3 position;
    Axis axes[3];
    Color color;

    float* data;
    bool updated; // if some state changed since last frame, (if not skip updating in shader) // TODO: at end to optimize
    RayCollision (* select) (const struct Object* self, const Ray* ray); // collision is checked in manager
    void (* render) (const struct Object* self, bool is_selected);
} Object;

void object_destroy(Object* obj);

Object obj_none_create();

#define OBJ_DEFAULT_COLOR CLITERAL(Color){0, 255, 0, 255}

// SPHERE data = { radius }
#define SPHERE_DEFAULT_RADIUS 1.0f
Object sphere_create(Vector3 position, float radius, Color color);

// CUBE data = { width, height, length }
#define CUBE_DEFAULT_SIZE 1.0f
Object cube_create(Vector3 position, float width, float height, float length, Color color);



