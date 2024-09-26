#include "vector_operations.h"

void vector3_ptr_to_array(Vector3* vec, float out[3]) {
    out[0] = vec->x;
    out[1] = vec->y;
    out[2] = vec->z;
}
void vector3_to_array(Vector3 vec, float out[3]) {
    out[0] = vec.x;
    out[1] = vec.y;
    out[2] = vec.z;
}

void vector2_ptr_to_array(Vector2* vec, float out[2]) {
    out[0] = vec->x;
    out[1] = vec->y;
}
void vector2_to_array(Vector2 vec, float out[2]) {
    out[0] = vec.x;
    out[1] = vec.y;
}
