/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef KOALA_UI_LIBRARY_H
#define KOALA_UI_LIBRARY_H

#include "arkoala_api_generated.h"
#include <string>

const GENERATED_ArkUIAnyAPI* GetAnyImpl(int kind, int version, std::string* result);

#endif //KOALA_UI_LIBRARY_H