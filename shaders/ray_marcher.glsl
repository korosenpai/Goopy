#version 400
// https://cgmathprog.home.blog/2019/08/31/raymarching-from-scratch-part-1/

precision highp float;

uniform vec2 resolution;
uniform float time;

uniform float fov = 45.0; // the vectical field of view (FOV) in degrees
uniform vec3 cameraPos = vec3(0.0, 0.0, -3.0); // position of the camera in world coordinates

// uniform vec2 mouse; // maybe add some light where mouse is?
uniform vec3 ro;
uniform vec4 camera_quaternion;

out vec4 fragColor;

//////////////////////////// OBJECT DATA ////////////////////////////
uniform int spheresCount;
int sphereElementsCount = 3;  // pos (3) + color (4) + radius // TODO: make it uniform?
uniform float sphereInfoArr[20 * 8];
// {pos1x, pos1y, pos1z, color1, radius1, ... posnx..z, colorn, radiusn}

uniform int cubeCount;
int cubeElementsCount= 3;  // pos (3) + color (4) + radius // TODO: make it uniform?
uniform float cubeInfoArr[20 * 8];

//////////////////////////// RAYMARCHING + SDFS ////////////////////////////
float sdSphere(vec3 p, vec3 center, float radius) {
    return length(p - center) - radius;
}

float sdBox(vec3 p, vec3 size) {
    return length(max(abs(p) - size, 0));
}

float smin(float a, float b, float k) {
    float h = max(k - abs(a - b), 0.0) / k;
    return min(a, b) - h*h*h*k*(1.0/6.0);
}


// map()
float sdf(vec3 pos) {
    float ground = pos.y;

    // float sphere1 = sdSphere(pos, vec3(0.), 1.0);
    // float sphere2 = sdSphere(pos, vec3(2.0, 3.0, 5.0), 2.0);
    // float box1 = sdBox(pos - vec3(1.0 + sin(time), .6, 0.0), vec3(0.5)); // NOTE: cube size must be half

    float d;
    d = ground;
    // d = smin(ground, ground, 1.0);
    // d = smin(d, sphere2, 1.0);
    // d = smin(d, box1, 1.5);

    /////// DRAW SPHERES ///////
    for (int i = 0; i < spheresCount; i++) {
        float x = sphereInfoArr[i * sphereElementsCount];
        float y = sphereInfoArr[i * sphereElementsCount + 1];
        float z = sphereInfoArr[i * sphereElementsCount + 2];
        
        float sphere = sdSphere(pos, vec3(x, y, z), 1.0);
        d = smin(d, sphere, 1.0);
    }

    for (int i = 0; i < cubeCount; i++) {
        float x = cubeInfoArr[i * cubeElementsCount];
        float y = cubeInfoArr[i * cubeElementsCount + 1];
        float z = cubeInfoArr[i * cubeElementsCount + 2];
        
        float cube = sdBox(pos - vec3(x, y, z), vec3(0.5));
        d = smin(d, cube, 1.0);
    }
    return d; 
}

#define MAX_STEPS 32
#define MINIMUM_HIT_DIST 0.01
#define MAX_DIST 100.0
float rayMarch(vec3 ro, vec3 rd) {
    float d0 = 0;

    for (int i = 0; i < MAX_STEPS && d0 < MAX_DIST; i++) {
        vec3 p = ro + d0 * rd; // current marching location

        float dS = sdf(p); // distance from scene
        d0 += dS;

        if (dS < MINIMUM_HIT_DIST) {
            break;
        };

    }

    return d0;

}

//////////////////////////// LIGHTING ////////////////////////////
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

// vec3 light = blinnPhong(p, lightPos, ambientColor, lightColor, globalAmbient, globalDiffuse, globalSpecular, globalSpecularExponent);
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

vec3 get_normal(vec3 p) {
    float d = sdf(p);
    // get dist of points around p to get slope of curve and extract normal
    vec2 e = vec2(.01, 0);
    vec3 n = d - vec3( // trick to quickly get points around
        sdf(p - e.xyy),
        sdf(p - e.yxy),
        sdf(p - e.yyx)
    );

    return normalize(n);
}

float get_light(vec3 p) {
    vec3 light_pos = vec3(0, 5, -6);
    // light_pos.x += sin(time) * 4; // make it spin around
    // light_pos.z -= cos(time) * 4;

    vec3 light_direction = normalize(light_pos - p);
    vec3 normal = get_normal(p);

    // dot product of two vectors
    // when perpendicular returns 0, when straight up parallel returns 1
    // and if angled returns angle of light
    float dif = dot(normal, light_direction); // range -1..1
    dif = clamp(dif, 0, 1); // range: 0..1

    // shadows
    // raymarch to light source and if we hit something before we are in the shade
    // also move p out from close to the object we hit to not kick out of the raymarch loop instantly
    // if offset is not large enough there will be artifacts (ex remove * 2 and look at center of obj)
    float d = rayMarch(p + normal * MINIMUM_HIT_DIST * 2, light_direction);
    if (d < length(light_pos - p)) dif  *= .1; // hit an obj, so we are in shadow


    return dif;
}

////////////////////////////////////////////////////////////////////////

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
    vec3 rd = get_ray_direction();
    // vec3 raymarchColor = rayMarch(rayDir);
    // fragColor = vec4(raymarchColor, 1.0);

    float dist = rayMarch(ro, rd);
    vec3 p = ro + rd * dist;

    vec3 col;
    col = blinnPhong(p, lightPos, ambientColor, lightColor, globalAmbient,
        globalDiffuse, globalSpecular, globalSpecularExponent);


    // TODO: fix lighting destroying in the distance
    // float dif = get_light(p); // diffused lighting
    // vec3 col = vec3(dif);

    // red cuz when looking to right x is positive -> (1, 0 ,0)
    // same idea for green and black
    // col = get_normal(p);


    fragColor = vec4(col, 1);
}

