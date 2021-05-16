#pragma once

#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"


class VertexArray {
private:
	uint32_t arrayId;
public:
	VertexArray();
	~VertexArray();

	VertexArray(VertexArray&& vertexArray) noexcept;

	void AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
	void AddBuffer(const IndexBuffer& indexBuffer);
	void Bind() const;
	void Unbind() const;

};
