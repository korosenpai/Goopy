#include "selected_obj_menu.h"
#include <raymath.h>

#include <raylib.h>
void selected_obj_render_menu_sphere(Camera3D* camera, Object* obj) {
    // https://stackoverflow.com/questions/6139451/how-can-i-convert-3d-space-coordinates-to-2d-space-coordinates
    
    Vector2 obj_pos = geometry_project_3d_to_2d(&obj->position, camera);
    DrawCircleV(obj_pos, 50.0f, RED);
    // printf("%f - %f\n", obj_pos.x, obj_pos.y);


}
