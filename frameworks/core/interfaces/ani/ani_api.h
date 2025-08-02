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
#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

#define ARKUI_ANI_API_VERSION 100
#define ARKUI_ANI_MODIFIER_FUNCTION_NAME "GetArkUIAniModifiers"

struct _ArkUINode;
struct _ArkUIContentSlot;
struct _ArkUINodeContent;
typedef class __ani_ref* ani_ref;
typedef class __ani_object* ani_object;
typedef struct __ani_env ani_env;
typedef int64_t ani_long;
typedef class __ani_fn_object *ani_fn_object;
typedef _ArkUINode* ArkUINodeHandle;
typedef int ArkUI_Int32;
typedef _ArkUIContentSlot* ArkUIContentSlot;
typedef _ArkUINodeContent* ArkUINodeContent;
typedef struct WebviewControllerInfo {
    std::function<int32_t()> getWebIdFunc = nullptr;
    std::function<void(int32_t)> completeWindowNewFunc = nullptr;
    std::function<long()> getNativePtrFunc = nullptr;
    std::function<void()> releaseRefFunc = nullptr;
    std::function<void(int32_t)> setWebIdFunc = nullptr;
    std::function<void(const std::string&)> setHapPathFunc = nullptr;
} WebviewControllerInfo;

struct ArkUIAniImageModifier {
    void (*setPixelMap)(ArkUINodeHandle node, void* pixelmap);
};

struct ArkUIAniWebModifier {
    void (*setWebOptions)(ArkUINodeHandle node, const WebviewControllerInfo& controllerInfo);
    void (*setWebControllerControllerHandler)(void* controllerHandler, const WebviewControllerInfo& controllerInfo);
};
struct ArkUIAniCommonModifier {
    ani_ref* (*getHostContext)();
    void (*syncInstanceId)(ArkUI_Int32 id);
    void (*restoreInstanceId)();
    void (*setDrawCallback)(ani_env* env, ani_long ptr, ani_fn_object fnObj);
};
struct ArkUIAniDrawModifier {
    void (*setDrawModifier)(ani_env* env, ani_long ptr, ani_object fnObj);
    void (*invalidate)(ani_env* env, ani_long ptr);
};
struct ArkUIAniContentSlotModifier {
    ArkUIContentSlot (*construct)(ArkUI_Int32 id);
    void (*setContentSlotOptions)(ArkUIContentSlot node, ArkUINodeContent value);
};
struct ArkUIAniModifiers {
    ArkUI_Int32 version;
    const ArkUIAniImageModifier* (*getImageAniModifier)();
    const ArkUIAniWebModifier* (*getWebAniModifier)();
    const ArkUIAniCommonModifier* (*getCommonAniModifier)();
    const ArkUIAniContentSlotModifier* (*getContentSlotAniModifier)();
    const ArkUIAniDrawModifier* (*getArkUIAniDrawModifier)();
};

__attribute__((visibility("default"))) const ArkUIAniModifiers* GetArkUIAniModifiers(void);
#ifdef __cplusplus
};
#endif

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ANI_API_H