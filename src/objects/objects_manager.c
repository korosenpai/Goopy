#include "objects_manager.h"
#include "objects.h"
#include <raylib.h>
#include <stdio.h>

#include "selected_obj_menu.h"

// id of selected object, whom render axis and translation panels
// id is calculated as position of obj in array
static int _selected_obj = -1;

void manager_unselect_obj() {
    _selected_obj = -1;
}

// TODO: implement to move obj easier
// true if clicked on element and still click when out of it
// move obj to dir
// static bool dragging_obj;

// static int sphere_count = 0;
// static Sphere spheres[MAX_OBJ_COUNT] = {};
static int _obj_count = 0;
static Object _objects[MAX_OBJ_COUNT] = {};


void manager_move_selected_obj(Ray* ray) {
    if (_selected_obj < 0) return;
    axis_move(ray, _objects[_selected_obj].axes, &_objects[_selected_obj].position);
}


void manager_render_objects() {
    // TODO: maybe calculate everything directly here?
    for (int i = 0; i < _obj_count; i ++) {
        OBJ_PTR_RENDER(_objects + i, i == _selected_obj);

        if (i == _selected_obj) {
            axes_render(_objects[i].axes, _objects[i].position);
        }
    }
}

void manager_render_selected_obj_menu(Camera3D* camera) {
    if (_selected_obj < 0) return;

    selected_obj_render_menu_sphere(camera, _objects + _selected_obj);
}

// determine what obj the mouse is hitting and if mouse is pressed select it
void manager_select_obj(Ray* ray) {
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return;

    // check if colliding with any sphere
    RayCollision obj_hit = {0};
    for (int i = 0; i < _obj_count; i++) {

        obj_hit = OBJ_PTR_SELECT(_objects + i, ray);
        if (!obj_hit.hit) continue;

        _selected_obj = i;
        // printf("selected obj %d\n", _selected_obj);
        return;
    }

    // if nothing hit
    manager_unselect_obj();

}


void manager_destroy_objects() {
    for (int i = 0; i < _obj_count; i++) {
        object_destroy(_objects + i);
    }
}

////////////// ADD OBJECTS //////////////

void manager_add_sphere(Vector3 position, float radius, Color color) {
    if (_obj_count + 1 == MAX_OBJ_COUNT) {
        printf("max sphere creation reached\n");
        return;
    }

    _objects[_obj_count] = sphere_create(position, radius, color);
    _obj_count++;
}
