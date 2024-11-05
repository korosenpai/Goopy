#include "config_state.h"

ConfigurationState config_state_create() {
    return (ConfigurationState) {
        .obj_placing_distance = DEFAULT_OBJ_PLACING_DISTANCE,
    };

}
