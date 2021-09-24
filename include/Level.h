#include <vector>
#include <string>
#include "LineRenderer.h"

#include <glm/glm.hpp>

class Level
{
public:
    Level(std::string fileName, LineRenderer *pRenderer);
    ~Level() {};

    void LoadLevel();
    void Render();
private:
    std::vector<glm::vec2> m_levelData;
    std::string m_fileName;
    LineRenderer *m_pRenderer;
};
