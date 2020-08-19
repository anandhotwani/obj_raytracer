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
    std::cout << warnings << std::endl;
    }

    if (!errors.empty()) {
    std::cerr << errors << std::endl;
    }

    if (!ret) {
    exit(1);
    }

    std::vector<Vertex> vertices;

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
    // Loop over faces(polygon)
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

        // Vector3f this_normal = Vector3f(nx, ny, nz);
        // std::cout<<"Normal here is "<<glm::to_string(this_normal)<<"\n";

        Vertex vert;
        vert.P = Vector3f(vx, vy, vz);
        vert.Ng = Vector3f(nx, ny, nz);
        vert.UV = Vector2f(tx, ty);
        vertices.push_back(vert);
        // Optional: vertex colors
        // tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
        // tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
        // tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
        }
        index_offset += fv;

        // per-face material
        //shapes[s].mesh.material_ids[f];
    }
    }

    // std::vector<Vertex> vertices;
    // for (int i = 0; i < shapes.size(); ++i) {
    //     tinyobj::shape_t &shape = shapes[i];
    //     tinyobj::mesh_t &mesh = shape.mesh;
    //     for (int j = 0; j < mesh.indices.size(); ++j) {
    //         tinyobj::index_t idx = mesh.indices[j];

    //         Vector3f position = Vector3f(attributes.vertices[idx.vertex_index * 3],
    //                                      attributes.vertices[idx.vertex_index * 3 + 1],
    //                                      attributes.vertices[idx.vertex_index * 3 + 2]);

    //         Vector3f normal = Vector3f(attributes.vertices[idx.normal_index * 3],
    //                                    attributes.vertices[idx.normal_index * 3 + 1],
    //                                    attributes.vertices[idx.normal_index * 3 + 2]);

    //         std::cout<<"> Normal here is "<<glm::to_string(normal)<<"\n";

    //         Vector2f uv_coord = Vector2f(attributes.vertices[idx.texcoord_index * 2],
    //                                      attributes.vertices[idx.texcoord_index * 2 + 1]);

    //         Vertex vert;
    //         vert.P = position;
    //         vert.Ng = glm::normalize(normal);
    //         vert.UV = glm::normalize(uv_coord);
    //         vertices.push_back(vert);
            
    //     }
    for (int i = 0; i < vertices.size() / 3; ++i){
        tris.push_back(std::make_shared<Triangle>(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]));
    }


//     std::string inputfile = filepath;
//     unsigned long pos = inputfile.find_last_of("/");
//     std::string mtlbasepath = inputfile.substr(0, pos + 1);

//     std::cout<<"> Attempting to open  "<<inputfile<<" ... \n";
//     std::string err = tinyobj::LoadObj(shapes, materials, inputfile.c_str(), mtlbasepath.c_str());

//     if (!err.empty()) {
//         std::cout<<err<<std::endl;
//     }

//     long shapes_size, indices_size;
//     shapes_size = shapes.size();
//     std::cout<<"> Number of polygon objects found in the .obj file : "<<shapes.size()<<"\n";

//     // Load triangles
//     for (uint32_t i = 0; i < shapes_size; ++i) {
//         indices_size = shapes[i].mesh.indices.size() / 3;
//         std::cout<<"> Triangles found in mesh : "<<indices_size<<"\n";
//         for (size_t f = 0; f < indices_size; ++f) {
            
//             // Vertices
//             Vector3f v0 = Vector3f(
//                                     shapes[i].mesh.positions[shapes[i].mesh.indices[3 * f] * 3],
//                                     shapes[i].mesh.positions[shapes[i].mesh.indices[3 * f] * 3 + 1],
//                                     shapes[i].mesh.positions[shapes[i].mesh.indices[3 * f] * 3 + 2]
//                                     );
//             Vector3f v1 = Vector3f(
//                                     shapes[i].mesh.positions[shapes[i].mesh.indices[3 * f + 1] * 3],
//                                     shapes[i].mesh.positions[shapes[i].mesh.indices[3 * f + 1] * 3 + 1],
//                                     shapes[i].mesh.positions[shapes[i].mesh.indices[3 * f + 1] * 3 + 2]
//                                     );
//             Vector3f v2 = Vector3f(
//                                     shapes[i].mesh.positions[shapes[i].mesh.indices[3 * f + 2] * 3],
//                                     shapes[i].mesh.positions[shapes[i].mesh.indices[3 * f + 2] * 3 + 1],
//                                     shapes[i].mesh.positions[shapes[i].mesh.indices[3 * f + 2] * 3 + 2]
//                                     );
            
//             Vector2f UV0, UV1, UV2;
            
//             // Attempt to load texture coordinates, UV
//             if (shapes[i].mesh.indices[3 * f + 2] * 2 + 1 < shapes[i].mesh.texcoords.size()) {
//                 UV0 = Vector2f(
//                     shapes[i].mesh.texcoords[shapes[i].mesh.indices[3 * f] * 2],
//                     shapes[i].mesh.texcoords[shapes[i].mesh.indices[3 * f] * 2 + 1]
//                 );

//                 UV1 = Vector2f(
//                     shapes[i].mesh.texcoords[shapes[i].mesh.indices[3 * f + 1] * 2],
//                     shapes[i].mesh.texcoords[shapes[i].mesh.indices[3 * f + 1] * 2 + 1]
//                 );

//                 UV2 = Vector2f(
//                     shapes[i].mesh.texcoords[shapes[i].mesh.indices[3 * f + 2] * 2],
//                     shapes[i].mesh.texcoords[shapes[i].mesh.indices[3 * f + 2] * 2 + 1]
//                 );
                
//                 // Ensure UVs are in [0,1] range
//                 // UV0.x = saturate(UV0.x);
//                 // UV0.y = saturate(UV0.y);
//                 // UV1.x = saturate(UV1.x);
//                 // UV1.y = saturate(UV1.y);
//                 // UV2.x = saturate(UV2.x);
//                 // UV2.y = saturate(UV2.y);
                
// //                std::cout<<"UV Coordinates are : \n"<<"v0 : "<<glm::to_string(UV0)<<"\nv1 : "<<glm::to_string(UV1)<<"\nv2 : "<<glm::to_string(UV2)<<"\n";
//             }
//             else {
//                 UV0 = Vector2f(0.0f);
//                 UV1 = Vector2f(0.0f);
//                 UV2 = Vector2f(0.0f);
//             }

//             tris.push_back(std::make_shared<Triangle>(v0, v1, v2));
//         }
//     }
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