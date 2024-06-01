/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef ARKUI_NATIVE_FRAME_INFORMATION_H
#define ARKUI_NATIVE_FRAME_INFORMATION_H

#include <string>

#include "native_type.h"
#include "node_extened.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ArkUI_ImageAnimatorFrameInfo {
    std::string src;
    ArkUI_DrawableDescriptor* drawableDescriptor;
    std::optional<int32_t> width;
    std::optional<int32_t> height;
    std::optional<int32_t> top;
    std::optional<int32_t> left;
    std::optional<int32_t> duration;
};

#ifdef __cplusplus
};
#endif

#endif