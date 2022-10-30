#pragma once

#include "lib/glm/glm/vec4.hpp"
#include "vector"
#include "string"
class Colors {
private:
    std::vector<std::pair<std::string, glm::vec4>> allColors
            {
                    std::make_pair("CYAN", glm::vec4(0.0, 1.0, 1.0, 1.0)),
                    std::make_pair("PURPLE", glm::vec4(1.0, 0.0, 1.0, 1.0)),
                    std::make_pair("GREEN", glm::vec4(0.0, 1.0, 0.0, 1.0)),
                    std::make_pair("YELLOW", glm::vec4(1.0, 1.0, 0.0, 1.0)),
                    std::make_pair("ORANGE", glm::vec4(1.0, 0.5, 0.0, 1.0)),
                    std::make_pair("SILVER", glm::vec4(0.9, 0.91, 0.98, 1.0)),
                    std::make_pair("CORAL", glm::vec4(1.0, 0.498039, 0.0, 1.0))
            };
public:
    const std::vector<std::pair<std::string, glm::vec4>> &getAllColors() const;
};
