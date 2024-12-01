#pragma once
#include <vector>
class VBO
{
	size_t VBO_id;
	bool Created = false;
	void compileData(size_t Size, float* Begin);
public:
	void Create();
	template <class DataType> void setData(std::vector<DataType> &vData,float *start);
	void Bind(bool State);
	void Delete();
};

template<class DataType>
inline void VBO::setData(std::vector<DataType>& vData, float* start)
{
	if (!Created) return;
	compileData(vData.size() * sizeof(DataType), start);
}
