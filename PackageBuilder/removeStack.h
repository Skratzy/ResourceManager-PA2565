#ifndef _PB_REMOVE_STACK_H
#define _PB_REMOVE_STACK_H

#include <stack>
class  globalStack {
private:
	std::stack<std::string> m_stack;

public:
	globalStack();
	~globalStack();

	static globalStack& getInstance();
	
	std::string fetchPath();
	void clearAndDelete();
};

#endif
