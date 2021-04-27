#pragma once

class VertexBuffer
{
private:
	uint32_t bufferId;
	uint64_t size;
public:
	VertexBuffer(void* data, uint64_t size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	uint64_t GetSize() const { return size; }

};

