#version 400
// https://cgmathprog.home.blog/2019/08/31/raymarching-from-scratch-part-1/

precision highp float;

uniform vec2 resolution;
uniform float time;

uniform float fov = 45.0; // the vectical field of view (FOV) in degrees
uniform vec3 cameraPos = vec3(0.0, 0.0, -3.0); // position of the camera in world coordinates
uniform vec3 front = vec3(0.0, 0.0, 1.0); // where are we looking at
uniform vec3 up = vec3(0.0, 1.0, 0.0); // what we consider to be up

uniform vec2 mouse;
uniform vec3 ro;
uniform vec3 rd;

uniform vec4 camera_quaternion;

out vec4 fragColor;

float sdSphere(vec3 p, vec3 center, float radius) {
    return length(p - center) - radius;
}

float sdBox(vec3 p, vec3 size) {
    return length(max(abs(p) - size, 0));
}

// map()
float sdf(vec3 pos) {
    float sphere1 = sdSphere(pos, vec3(0.), 1.0);
    float sphere2 = sdSphere(pos, vec3(2.0, 3.0, 5.0), 2.0);

    return min(sphere1, sphere2);
}

///////////// LIGHTING /////////////
// shamelessly copied from part 2
uniform float globalAmbient = 0.1; // how strong is the ambient lightning
uniform float globalDiffuse = 1.0; // how strong is the diffuse lightning
uniform float globalSpecular = 1.0; // how strong is the specular lightning
uniform float globalSpecularExponent = 64.0; // how focused is the shiny spot
uniform vec3 lightPos = vec3(-2.0, 5.0, -3.0); // position of the light source
uniform vec3 lightColor = vec3(0.9, 0.9, 0.68); // color of the light source
uniform vec3 ambientColor = vec3(1.0, 1.0, 1.0); // ambient color
#define DERIVATIVE_STEP 0.001

vec3 estimateNormal(vec3 p) {
    return normalize(vec3(
        sdf(vec3(p.x + DERIVATIVE_STEP, p.y, p.z)) - sdf(vec3(p.x - DERIVATIVE_STEP, p.y, p.z)),
        sdf(vec3(p.x, p.y + DERIVATIVE_STEP, p.z)) - sdf(vec3(p.x, p.y - DERIVATIVE_STEP, p.z)),
        sdf(vec3(p.x, p.y, p.z  + DERIVATIVE_STEP)) - sdf(vec3(p.x, p.y, p.z - DERIVATIVE_STEP))
    ));
}

vec3 blinnPhong(vec3 position, // hit point
                vec3 lightPosition, // position of the light source
                vec3 ambientCol, // ambient color
                vec3 lightCol, // light source color
                float ambientCoeff, // scale ambient contribution
                float diffuseCoeff, // scale diffuse contribution
                float specularCoeff, // scale specular contribution
                float specularExponent // how focused should the shiny spot be
)
{
    vec3 normal = estimateNormal(position);
    vec3 toEye = normalize(ro - position);
    vec3 toLight = normalize(lightPosition - position);
    vec3 reflection = reflect(-toLight, normal);

    vec3 ambientFactor = ambientCol * ambientCoeff;
    vec3 diffuseFactor = diffuseCoeff * lightCol * max(0.0, dot(normal, toLight));
    vec3 specularFactor = lightCol * pow(max(0.0, dot(toEye, reflection)), specularExponent)
                     * specularCoeff;

    return ambientFactor + diffuseFactor + specularFactor;
}

////////////////////////////////////

#define MAX_STEPS 32
#define MINIMUM_HIT_DIST 0.01
#define MAX_DIST 100.0
vec3 rayMarch(vec3 rayDir) {
    vec3 hitcolor = vec3(1.0, 1.0, 1.0);
    vec3 misscolor = vec3(0.0);

    float depth = 0.0;
    for (int i = 0; depth < MAX_DIST && i < MAX_STEPS; ++i) {
        vec3 pos = ro + rayDir * depth;
        float dist = sdf(pos);
        if (dist < MINIMUM_HIT_DIST) {
            // return hitcolor;
            return blinnPhong(pos, lightPos, ambientColor, lightColor,
                globalAmbient, globalDiffuse, globalSpecular, globalSpecularExponent);
        }
        depth += dist;
    }


    return misscolor;
}


mat2 rot2D(float angle) {
    float s = sin(angle);
    float c = cos(angle);
    return mat2(c, -s, s, c);
}
vec3 applyQuaternion(vec3 v, vec4 q) {

			// calculate quat * vector
      vec4 qv = vec4(
        q.w * v.x + q.y * v.z - q.z * v.y,
        q.w * v.y + q.z * v.x - q.x * v.z,
        q.w * v.z + q.x * v.y - q.y * v.x,
        -q.x * v.x - q.y * v.y - q.z * v.z
      );

			// calculate result * inverse quat
      return vec3(
        qv.x  * q.w + qv.w * -q.x + qv.y * -q.z - qv.z * -q.y,
        qv.y * q.w + qv.w * -q.y + qv.z * -q.x - qv.x  * -q.z,
        qv.z * q.w + qv.w * -q.z + qv.x  * -q.y - qv.y * -q.x
      );
}

vec3 get_ray_direction() {
    float aspect_ratio = resolution.x / resolution.y;
    // float fov2 = radians(fov) / 2.0;

    // vec2 screenCoord = gl_FragCoord.xy / resolution; // range 0...1
    // screenCoord -= 0.5; // -0.5...0.5
    // screenCoord *= 2.0; // -1...1 so 0,0 is center of canves
    // screenCoord.x *= resolution.x / resolution.y;

    // screenCoord *= aspect_ratio;

    // vec2 offsets = screenCoord * tan(fov2);

    // // compute 3 orthogonal unit vectors
    // vec3 rayFront = normalize(rd);
    // vec3 rayRight = normalize(cross(rayFront, normalize(up)));
    // vec3 rayUp = cross(rayRight, rayFront);
    // vec3 rayDir = rayFront + rayRight * offsets.x + rayUp * offsets.y;

    // return normalize(rayDir);

    vec2 uv = gl_FragCoord.xy / resolution; // range 0...1
    uv -= 0.5; // -0.5...0.5
    uv *= 2.0; // -1...1 so 0,0 is center of canves
    uv.x *= aspect_ratio;

    float d = 1.0 / tan(radians(fov) / 2.0);

    vec3 rayDirection = normalize(vec3(uv, -d));
    rayDirection = applyQuaternion(rayDirection, camera_quaternion);

    return normalize(rayDirection);
}

#define FOV 45.
void main() {
    // vec2 uv = gl_FragCoord.xy / resolution; // range 0...1
    // uv -= 0.5; // -0.5...0.5
    // uv *= 2.0; // -1...1 so 0,0 is center of canves
    // uv.x *= resolution.x / resolution.y;

    // vec3 col = vec3(0);

    // const float m_sensitivity = 1;
    // vec2 m = (mouse * 2.0 - resolution) / resolution.y * m_sensitivity;


    // vec3 ro = vec3(0, 3, 0); // ray origin
    // vec3 rd = normalize(FOV * vec3(uv.x, uv.y - .2, 1)); // ray direction

    vec3 rayDir = get_ray_direction();
    vec3 raymarchColor = rayMarch(rayDir);

    fragColor = vec4(raymarchColor, 1.0);
}

