#include "ToolFill.h"

ToolFill::ToolFill() : Tool("Fill", 3, 0) {}

ToolFill::~ToolFill() {}

void ToolFill::floodFill(std::vector<glm::vec2>& points, sf::Vector2u size, glm::vec2 pos, glm::vec4 col)
{
    if (pos.y < 0 || pos.y >= size.y || pos.x < 0 || pos.x >= size.x)
    	return;

    std::stack<glm::vec2> stack;
    std::unordered_set<glm::vec2> found;

    stack.push(pos);
    while (!stack.empty())
    {
    	glm::vec2 p = stack.top();
    	stack.pop();
    	int x = p.x;
    	int y = p.y;
    	if (y < 0 || y >= size.y || x < 0 || x >= size.x || found.find(p) != found.end())
    		continue;
    	glm::vec4 val = readColor(size, x, y);
    	if (val == col)
    	{
    		found.emplace(p);
    		stack.push({x + 1, y});
    		stack.push({x - 1, y});
    		stack.push({x, y + 1});
    		stack.push({x, y - 1});
    	}
    }

    for (glm::vec2 p : found)
    {
        points.push_back(p);
    }
}

bool ToolFill::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    sf::Vector2u size = ctx.getUI()->getEngine()->getSize();
    glm::vec4 col = readColor(size, ctx.event.x, ctx.event.y);
    glm::vec4 newCol = ctx.getUI()->getSelectedColor();

    if (col == newCol) return false;

    std::vector<glm::vec2> points;
    floodFill(points, size, {ctx.event.x, ctx.event.y}, col);
    ctx.getUI()->getEngine()->addObject(new PointBlob(newCol, points));
    return true;
}
