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
            interaction.set_face_normal(r, outward_normal);
             return true;
         }
     }
     return false;
}