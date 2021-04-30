#pragma once


class IndexBuffer
{
private:
	uint32_t bufferId;
	uint32_t count = 0;
public:
	IndexBuffer(uint32_t* data, uint32_t count);

	~IndexBuffer();

	void Bind() const;

	void Unbind() const;

	inline uint32_t GetCount() const { return count; }
};

