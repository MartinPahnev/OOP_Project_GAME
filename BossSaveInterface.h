#pragma once

#include <fstream>

class BossSaveInterface
{
public:

	virtual void saveToFile(std::ofstream& ofs) const = 0;
	virtual ~BossSaveInterface() = default;
};

