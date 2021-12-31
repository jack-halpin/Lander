#include "Level.h"
#include <fstream>
#include <sstream>
#include <string>

Level::Level(std::string fileName, LineRenderer *pRenderer)
    : m_fileName(fileName)
    , m_pRenderer(pRenderer)
{

}

void Level::LoadLevel()
{
    m_levelData.clear();

	std::string line;
	std::ifstream fstream(m_fileName);
	if (fstream)
	{
        // Each line in the file contains two points as a percentage of screen
        // heigth and width
		while (std::getline(fstream, line)) // read each line from level file
		{
            std::string point;
			std::istringstream sstream(line);
            float x, y;
            sstream >> x;
            sstream >> y;
            
            // Is there a special character
            if (!sstream.eof())
            {
                char special;
                sstream >> special;
                switch (special)
                {
                    case '*':
                    {
                        break;
                    }
                }   
            }
            m_levelData.push_back(glm::vec2(x, y));
		}
	}
}

void Level::Render()
{
    for (const auto& line : m_levelData)
    {
        m_pRenderer->Add(line, glm::vec3(1.0f, 1.0f, 1.0f));
    }
    m_pRenderer->Flush();
}
