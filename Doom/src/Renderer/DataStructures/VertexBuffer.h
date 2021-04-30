#pragma once

class VertexBuffer
{
private:
	uint32_t bufferId;
	uint32_t size;
public:
	VertexBuffer(void* data, uint32_t size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	uint32_t GetSize() const { return size; }

};

