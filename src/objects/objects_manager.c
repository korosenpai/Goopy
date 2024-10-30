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


void manager_reset_obj_update() {

    for (int i = 0; i < _obj_count; i ++) {
        _objects[i].updated = false;
    }
}

void manager_move_selected_obj(Ray* ray) {
    if (_selected_obj < 0) return;
    axes_move(ray, _objects[_selected_obj].axes, &_objects[_selected_obj].position);
    // TODO: here update shader for this obj (add id to object, so to be found (position in array))
}


void manager_render_objects() {
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

    // find obj hit closest to cursor
    bool did_hit_obj = false;
    float closest_dist = 999;

    // check if colliding with any obj
    RayCollision obj_hit = {0};
    for (int i = 0; i < _obj_count; i++) {

        obj_hit = OBJ_PTR_SELECT(_objects + i, ray);
        if (!obj_hit.hit) continue;
        did_hit_obj = true;

        if (obj_hit.distance < closest_dist) {
            closest_dist = obj_hit.distance;

            _selected_obj = i;
        }
        // printf("selected obj %d\n", _selected_obj);
    }

    // if nothing hit
    if (!did_hit_obj)
        manager_unselect_obj();

}


void manager_destroy_objects() {
    for (int i = 0; i < _obj_count; i++) {
        object_destroy(_objects + i);
    }
}

////////////// ADD OBJECTS //////////////

void manager_add_object(Shader* shader, Object obj) {
    if (_obj_count + 1 == MAX_OBJ_COUNT) {
        printf("max object creation reached\n");
        return;
    }

    _objects[_obj_count] = obj;
    shader_add_obj(shader, _objects + _obj_count);
    _obj_count++;

}



