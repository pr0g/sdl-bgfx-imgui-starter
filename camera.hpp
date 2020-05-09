#include "as/as-math-ops.hpp"

struct camera_t
{
    as::vec3_t position { 0.0f };
    float yaw { 0.0f };
    float pitch { 0.0f };

    as::mat4_t view() const
    {
        return as::mat::inverse(as::mat4_t{ orientation(), position });
    }

    as::mat3_t orientation() const
    {
        return as::mat3::rotation_zxy(pitch, yaw, 0.0f);
    }
};
