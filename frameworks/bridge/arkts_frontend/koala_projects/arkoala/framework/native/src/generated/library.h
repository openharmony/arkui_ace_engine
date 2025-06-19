#ifndef KOALA_UI_LIBRARY_H
#define KOALA_UI_LIBRARY_H

#include "arkoala_api_generated.h"
#include <string>

const GENERATED_ArkUIAnyAPI* GetAnyImpl(int kind, int version, std::string* result);

#endif //KOALA_UI_LIBRARY_H