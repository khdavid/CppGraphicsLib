#pragma once
#include <glew.h>
#include <vector>

#include "nodes/graphicsNode.h"
#include "spriteBase.h"

class TriangleSprite : public SpriteBase
{
public:
  using SpriteBase::SpriteBase;
  ~TriangleSprite();
  virtual void init(const std::vector<Vertex>& vertices);
  virtual void render() override;
private:
  size_t numOfVertices_ = 0;
  GLuint vboVertices_ = 0;
  GLint vertexPositionAttr_ = 0;
  GLint vertexColorAttr_ = 0;

};

