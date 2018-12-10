#include "removeStack.h"
#include <experimental/filesystem>

globalStack::globalStack()
{
	m_stack.push("NotEmpty");
}

globalStack::~globalStack()
{
	clearAndDelete();
}

globalStack & globalStack::getInstance()
{
	static globalStack instance;
	return instance;
}

std::string globalStack::fetchPath()
{
	std::string tempAdress;
	tempAdress.append("tempFile");
	tempAdress.append(std::to_string(m_stack.size()));
	tempAdress.append(".delete");
	m_stack.push(tempAdress);
	return tempAdress;
}

void globalStack::clearAndDelete()
{
	// Delete temporary created files
	while (m_stack.size() > 1) {
		// Fetch the top element & delete file
		std::experimental::filesystem::remove(m_stack.top().c_str());
		// Pop the top element
		m_stack.pop();
	}
}
