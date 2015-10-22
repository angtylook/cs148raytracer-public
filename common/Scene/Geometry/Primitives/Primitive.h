#pragma once

#include "common/Scene/Geometry/Primitives/PrimitiveBase.h"
#include "common/Scene/Geometry/Mesh/MeshObject.h"
#include "common/Scene/SceneObject.h"

template<int N>
class Primitive : public PrimitiveBase, public SceneObject
{
public:
    Primitive(class MeshObject* inputParent):
        parentMesh(inputParent), hasNormals(false), hasUVs(false)
    {
    }

    virtual ~Primitive()
    {
    }

    virtual void SetVertexPosition(int index, glm::vec3 position)
    {
        assert(index >= 0 && index < N);
        positions[index] = position;
    }

    virtual void SetVertexNormal(int index, glm::vec3 normal)
    {
        // Assume that SetVertexNormal is called IF AND ONLY IF normals are specified.
        assert(index >= 0 && index < N);
        normals[index] = normal;
        hasNormals = true;
    }

    virtual void SetVertexUV(int index, glm::vec2 uv)
    {
        // Assume that SetVertexUV is called IF AND ONLY IF uv coordinates are specified.
        assert(index >= 0 && index < N);
        uvs[index] = uv;
        hasUVs = true;
    }

    virtual int GetTotalVertices() const
    {
        return N;
    }

    virtual void Finalize()
    {
        UpdateBoundingBox();
    }

    virtual Box GetBoundingBox() override
    {
        return boundingBox;
    }

    virtual const class MeshObject* GetParentMeshObject() const override
    {
        return parentMesh;
    }

    virtual bool HasVertexNormals() const override
    {
        return hasNormals;
    }

    virtual glm::vec3 GetVertexNormal(int index) const override
    {
        return normals[index];
    }

protected:
    std::array<glm::vec3, N> positions;
    std::array<glm::vec3, N> normals;
    bool hasNormals;

    std::array<glm::vec2, N> uvs;
    bool hasUVs;

    void UpdateBoundingBox()
    {
        boundingBox.Reset();
        for (int i = 0; i < N; ++i) {
            boundingBox.maxVertex = glm::max(boundingBox.maxVertex, positions[i]);
            boundingBox.minVertex = glm::min(boundingBox.minVertex, positions[i]);
        }
    }
    Box boundingBox;
private:
    const class MeshObject* parentMesh;
};