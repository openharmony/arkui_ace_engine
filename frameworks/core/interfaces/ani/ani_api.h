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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ANI_API_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ANI_API_H

#include <functional>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

#define ARKUI_ANI_API_VERSION 100
#define ARKUI_ANI_MODIFIER_FUNCTION_NAME "GetArkUIAniModifiers"

struct _ArkUINode;

typedef _ArkUINode* ArkUINodeHandle;
typedef int ArkUI_Int32;

struct ArkUIAniImageModifier {
    void (*setPixelMap)(ArkUINodeHandle node, void* pixelmap);
};

struct ArkUIAniWebModifier {
    void (*setWebOptions)(ArkUINodeHandle node,
        std::function<void(int32_t)>&& onNWebId,
        std::function<void(const std::string&)>&& onHapPath);
};

struct ArkUIAniModifiers {
    ArkUI_Int32 version;
    const ArkUIAniImageModifier* (*getImageAniModifier)();
    const ArkUIAniWebModifier* (*getWebAniModifier)();
};

__attribute__((visibility("default"))) const ArkUIAniModifiers* GetArkUIAniModifiers(void);
#ifdef __cplusplus
};
#endif

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ANI_API_H