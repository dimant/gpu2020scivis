#ifndef HISTOGRAMDATA_H
#define HISTOGRAMDATA_H

class HistogramData
{
private:
	float* _data;

	size_t _ndata;

public:
	HistogramData() : _data(0), _ndata(0)
	{
	}

	void setData(float* data, size_t ndata)
	{
		_data = data;
		_ndata = ndata;
	}

	const float* getData() const
	{
		return _data;
	}

	const float& getSize() const
	{
		return _ndata;
	}
};

#endif