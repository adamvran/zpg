#include "Callback.h"
void Callback::errorCallback(int error, const char* description) { fputs(description, stderr); }
