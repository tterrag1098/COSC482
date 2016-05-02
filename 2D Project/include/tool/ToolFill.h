#ifndef TOOLFILL_H
#define TOOLFILL_H

#include "Tool.h"
#include "UI.h"
#include "PointBlob.h"
#include <stack>
#include <unordered_set>

class ToolFill : public Tool
{
    public:
        ToolFill();
        virtual ~ToolFill();

        bool mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;

    protected:
    private:
        void floodFill(std::vector<glm::vec2>& points, sf::Vector2u size, glm::vec2 pos, glm::vec4 col);

};

namespace std
{
template<>
struct hash<glm::vec2>
{
    std::size_t operator()(const glm::vec2& v) const
    {
        return hash<int>()(v.x) ^ (hash<int>()(v.y) << 1);
    }
};
}

#endif // TOOLFILL_H
