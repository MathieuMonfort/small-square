//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#ifndef SMALLSQUARE_CAMERA_H
#define SMALLSQUARE_CAMERA_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace std;
using namespace glm;

namespace smallsquare{
    class Camera {

    public:
        mat4 rotation = mat4(1.0f);
        vec3 position = vec3(1.0f);

        Camera(vec3 position, vec3 rotation);

        [[nodiscard]]
        mat4 GetView() const;
        [[nodiscard]]
        mat4 GetInvertedView() const;

        [[nodiscard]]
        vec3 GetFront() const;
        [[nodiscard]]
        vec3 GetRight() const;
        [[nodiscard]]
        vec3 GetUp() const;

    };
}

#endif













