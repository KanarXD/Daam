#pragma once


class IndexBuffer
{
private:
	uint32_t bufferId;
	uint64_t count = 0;
public:
	IndexBuffer(uint32_t* data, uint64_t count);

	~IndexBuffer();

	void Bind() const;

	void Unbind() const;

	inline uint64_t GetCount() const { return count; }
};

