#ifndef CAPPLET_GLERRORHANDLER_HPP_
#define CAPPLET_GLERRORHANDLER_HPP_

#include <signal.h>

#define ASSERT(x) if(!(x)) raise(SIGBREAK);
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

#endif /* CAPPLET_GLERRORHANDLER_HPP_ */
