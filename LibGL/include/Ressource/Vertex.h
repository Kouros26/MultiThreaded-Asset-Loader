#include "../../LibMaths/Vec2/Vec2.h"
#include "../../LibMaths/Vec3/Vec3.h"

class Vertex {
public :
    // position
    lm::vec3 Position;
    // normal
    lm::vec3 Normal;
    // texCoords
    lm::vec2 TexCoords;
    // tangent
    lm::vec3 Tangent;
    // bitangent
    lm::vec3 Bitangent;
    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
};