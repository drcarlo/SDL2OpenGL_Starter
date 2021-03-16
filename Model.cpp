#include "Model.h"

Model::~Model()
{

}

bool Model::init()
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(file,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    // If the import failed, report it
    if (!scene) {
        std::cerr << importer.GetErrorString() << std::endl;
        return false;
    }


    for (int meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++) {
        aiMesh* mesh = scene->mMeshes[meshIndex];

        std::vector<GE::Vertex> vertices;
        float x, y, z, u = 0.0f, v = 0.0f, nx = 0.0f, ny = 0.0f, nz = 0.0f;
        for (int vertexIndex = 0; vertexIndex < mesh->mNumVertices; vertexIndex++) {
            const aiVector3D& vertexPosition = mesh->mVertices[vertexIndex];
            x = vertexPosition.x;
            y = vertexPosition.y;
            z = vertexPosition.z;

            if (mesh->HasNormals()) {
                const aiVector3D& normal = mesh->mNormals[meshIndex];
                nx = normal.x;
                ny = normal.y;
                nz = normal.z;
            }
            if (mesh->HasTextureCoords(0)) {
                const aiVector3D& vertexUV = mesh->mTextureCoords[0][meshIndex];
                u = vertexUV.x;
                v = vertexUV.y;
            }
            vertices.emplace_back(x, y, z, u, v, nx, ny, nz);
        }
        
        std::vector<unsigned int> indices;
        for (int faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++) {
            const aiFace& face = mesh->mFaces[faceIndex];

            if (face.mNumIndices != 3) continue;
            indices.push_back(face.mIndices[0]);
            indices.push_back(face.mIndices[1]);
            indices.push_back(face.mIndices[2]);
        }

        Texture* texture = new Texture("");
        unsigned int vao, vbo, ibo;
        // Create buffers and vertex arrays here, sending the vertex data to the GPU
        /*
        textures.push_back(texture);
        vaos.push_back(vao);
        vbos.push_back(vbo);
        ibos.push_back(ibo);
        indexCounts.push_back((unsigned int)indices.size());
        vertexCounts.push_back((unsigned int)vertices.size());*/
    }

    // Now we can access the file's contents.
    // We're done. Everything will be cleaned up by the importer destructor
    return true;
}
