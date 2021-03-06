#include "pch.h"

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(uint32_t* data, uint32_t count) : count(count) {
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &bufferId);
}

IndexBuffer::IndexBuffer(IndexBuffer&& indexBuffer) noexcept
    : bufferId(indexBuffer.bufferId), count(indexBuffer.count)
{
    indexBuffer.bufferId = 0;
    indexBuffer.count = 0;
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
