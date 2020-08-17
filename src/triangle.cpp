#include "../src/triangle.hpp"

bool Triangle::intersect(const Ray &r, SurfaceInteraction &interaction) const {
    
    float u, v, t_temp = 0.0f;

     Vector3f pvec = glm::cross(r.d, e2);
     float det = glm::dot(e1, pvec);
     if (det ==  0.0f) return false;
     float inv_det = 1.0f / det;
     Vector3f tvec = r.o - v0;
     u = glm::dot(tvec, pvec) * inv_det;
     if (u < 0.0f || u > 1.0f ) return false;
     Vector3f qvec = glm::cross(tvec, e1);
     v = glm::dot(r.d, qvec) * inv_det;
     if (v < 0.0f || u + v > 1.0f) return false;
     t_temp = glm::dot(e2, qvec) * inv_det;
     if (t_temp < r.t_max) {
         if (t_temp > r.t_min) {
             interaction.t = t_temp;
             interaction.p = r.o + interaction.t * r.d;
             Vector3f outward_normal = this->n;
             interaction.Ng = this->n;
             //interaction.set_face_normal(r, outward_normal);

             // Barycentric coords
             Vector3f bary = get_barycentric(interaction.p);
             interaction.Ng = glm::normalize((bary.x * N[0]) + (bary.y * N[1]) + bary.z * N[2]);

             //interaction.AOV = bary;
             Vector2f ST = bary.x * uv[0] + bary.y * uv[1] + bary.z * uv[2];
             interaction.AOV = Vector3f(ST.x, ST.y, 0.0f);
             //interaction.AOV = glm::normalize((bary.x * N[0]) + (bary.y * N[1]) + bary.z * N[2]);

             return true;
         }
     }
     return false;
}

Vector3f Triangle::get_barycentric(Vector3f &p) const {
    Vector3f v2_ = p - v0;
    float d00 = glm::dot(e1, e1);
    float d01 = glm::dot(e1, e2);
    float d11 = glm::dot(e2, e2);
    float d20 = glm::dot(v2_, e1);
    float d21 = glm::dot(v2_, e2);
    float d = d00 * d11 - d01 * d01;
    float v = (d11 * d20 - d01 * d21) / d;
    float w = (d00 * d21 - d01 * d20) / d;
    float u = 1 - v - w;
    return Vector3f(u, v, w);
}