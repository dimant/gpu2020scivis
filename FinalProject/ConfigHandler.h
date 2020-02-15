#ifndef CONFIGHANDLER_H
#define CONFIGHANDLER_H

template<typename T>
class ConfigHandler
{
private:
	std::function<void(T)> _listener;

public:
	T Value;

	void connect(std::function<void(T)> l)
	{
		_listener = l;
	}

	void handle(bool changed)
	{
		if (changed && _listener)
		{
			_listener(Value);
		}
	}
};

#endif