#include "pch.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(void* data, uint32_t size)
    : size(size)
{
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &bufferId);
}

VertexBuffer::VertexBuffer(VertexBuffer&& vertexBuffer) noexcept
    : bufferId(vertexBuffer.bufferId), size(vertexBuffer.size)
{
    vertexBuffer.bufferId = 0;
    vertexBuffer.size = 0;
}

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
}

void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
