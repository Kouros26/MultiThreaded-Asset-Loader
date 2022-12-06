#include <string.h>
#include "IResource.h"

class Texture : public IResource {
public:
    unsigned int id;
    std::string type;
    std::string path;
};