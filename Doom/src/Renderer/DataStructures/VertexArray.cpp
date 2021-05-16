#include "pch.h"

#include "VertexArray.h"


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &arrayId);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &arrayId);
}

VertexArray::VertexArray(VertexArray&& vertexArray) noexcept
	: arrayId(vertexArray.arrayId)
{
	vertexArray.arrayId = 0;
}

void VertexArray::AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)
{
	Bind();
	vertexBuffer.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		#pragma warning(disable:4312)
		glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.GetStride(), (const void*)offset);
		#pragma warning(default:4312) 
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
	Unbind();
	vertexBuffer.Unbind();
}

void VertexArray::AddBuffer(const IndexBuffer& indexBuffer)
{
	Bind();
	indexBuffer.Bind();
	Unbind();
	indexBuffer.Unbind();
}

void VertexArray::Bind() const
{
	glBindVertexArray(arrayId);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

