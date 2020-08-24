#include "trianglemesh.hpp"


#include "trianglemesh.hpp"

TriangleMesh::TriangleMesh(const char *filepath) {
    
    std::string inputfile = filepath;
    unsigned long pos = inputfile.find_last_of("/");
    std::string mtlbasepath = inputfile.substr(0, pos + 1);  

    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warnings;
    std::string errors;

    bool ret = tinyobj::LoadObj(&attributes, &shapes, &materials, &warnings, &errors, inputfile.c_str(), mtlbasepath.c_str());
    if (!warnings.empty()) {
    std::cout << "Warning: " << warnings << std::endl;
    }

    if (!errors.empty()) {
    std::cerr << "Error: " << errors << std::endl;
    }

    if (!ret) {
    exit(1);
    }

    std::vector<Vertex> vertices;

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(triangles)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            int fv = shapes[s].mesh.num_face_vertices[f];

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                tinyobj::real_t vx = attributes.vertices[3*idx.vertex_index+0];
                tinyobj::real_t vy = attributes.vertices[3*idx.vertex_index+1];
                tinyobj::real_t vz = attributes.vertices[3*idx.vertex_index+2];
                tinyobj::real_t nx = attributes.normals[3*idx.normal_index+0];
                tinyobj::real_t ny = attributes.normals[3*idx.normal_index+1];
                tinyobj::real_t nz = attributes.normals[3*idx.normal_index+2];
                tinyobj::real_t tx = attributes.texcoords[2*idx.texcoord_index+0];
                tinyobj::real_t ty = attributes.texcoords[2*idx.texcoord_index+1];

                Vertex vert;
                vert.P = Vector3f(vx, vy, vz);
                vert.Ng = Vector3f(nx, ny, nz);
                vert.UV = Vector2f(tx, ty);
                vertices.push_back(vert);

            }
            index_offset += fv;


        }
    }

    // Loops vertices
    for (int i = 0; i < vertices.size() / 3; ++i) {
        tris.push_back(std::make_shared<Triangle>(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]));
    }

    std::cout<<"> Successfully opened "<<inputfile<<"! \n\n";
    
    shapes.clear();
    materials.clear();
}

bool TriangleMesh::intersect(const Ray &r, SurfaceInteraction &interaction) const {
    
    
    bool hit_tri = false;
    long tri_idx;
    float t = r.t_max;
    SurfaceInteraction temp;
    long triangles_size = tris.size();
    for (long i = 0; i < triangles_size; ++i) {
        if (tris[i]->intersect(r, temp)) {
            hit_tri = true;
            tri_idx = i;
            r.t_max = temp.t;
            interaction = temp;
        }
    }
    return hit_tri;
}