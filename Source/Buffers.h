#pragma once

#include <vector>
enum BufferType {
	VERTEX = 0x8892,
	INDEX = 0x8893,
};


class Buffer
{
	size_t bufferId;
	bool Created = false;
	void ComplieData(size_t Size, void* Start);
	BufferType Type;
public:
	void Create(BufferType Type);
	template <class Structure> void setData(std::vector<Structure> &vData);
	void Bind(bool State);
	void Delete();
};

template<class Structure>
inline void Buffer::setData(std::vector<Structure>& vData)
{
	if (!Created) return;
	ComplieData(sizeof(Structure) * vData.size(), &(vData[0]));
}
