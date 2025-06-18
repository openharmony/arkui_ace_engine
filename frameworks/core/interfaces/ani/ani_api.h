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
#include "core/common/ace_engine.h"
#include "core/components_ng/render/snapshot_param.h"

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
typedef int32_t ani_int;
typedef int64_t ani_long;
typedef class __ani_fn_object *ani_fn_object;
typedef _ArkUINode* ArkUINodeHandle;
typedef int ArkUI_Int32;
typedef _ArkUIContentSlot* ArkUIContentSlot;
typedef _ArkUINodeContent* ArkUINodeContent;

struct ArkUIAniImageModifier {
    void (*setPixelMap)(ArkUINodeHandle node, void* pixelmap);
};

struct ArkUIAniWebModifier {
    void (*setWebOptions)(ArkUINodeHandle node,
        std::function<void(int32_t)>&& onNWebId,
        std::function<void(const std::string&)>&& onHapPath);
};
struct ArkUIAniDragModifier {
    void (*setDragDropInfoPixelMap)(ani_ref event, ani_ref pixelMap);
    void (*setDragDropInfoCustomNode)(ani_ref event, ArkUINodeHandle node);
    void (*setDragDropInfoExtraInfo)(ani_ref event, std::string& extraInfo);
};
struct ArkUIAniCommonModifier {
    ani_ref* (*getHostContext)();
    void (*syncInstanceId)(ArkUI_Int32 id);
    void (*restoreInstanceId)();
    void (*setDrawCallback)(ani_env* env, ani_long ptr, ani_fn_object fnObj);
    ArkUI_Int32 (*getCurrentInstanceId)();
    ani_long (*builderProxyNodeConstruct)(ArkUI_Int32 id);
};
struct ArkUIAniCustomNodeModifier {
    ani_long (*constructCustomNode)(ani_int);
};
struct ArkUIAniDrawModifier {
    void (*setDrawModifier)(ani_env* env, ani_long ptr, ani_object fnObj);
    void (*invalidate)(ani_env* env, ani_long ptr);
};
struct ArkUIAniContentSlotModifier {
    ArkUIContentSlot (*construct)(ArkUI_Int32 id);
    void (*setContentSlotOptions)(ArkUIContentSlot node, ArkUINodeContent value);
};
struct ArkUIAniComponentSnapshotModifier {
    int32_t (*getCurrentIdSafely)();
    OHOS::Ace::RefPtr<OHOS::Ace::Container> (*getContainer)(int32_t instanceId);
    void (*createFromBuilder)(ArkUINodeHandle node,
    std::function<void(std::shared_ptr<OHOS::Media::PixelMap>, int32_t, std::function<void()>)>&& callback,
    OHOS::Ace::NG::SnapshotParam param);
};
struct ArkUIAniModifiers {
    ArkUI_Int32 version;
    const ArkUIAniImageModifier* (*getImageAniModifier)();
    const ArkUIAniWebModifier* (*getWebAniModifier)();
    const ArkUIAniDragModifier* (*getDragAniModifier) ();
    const ArkUIAniCommonModifier* (*getCommonAniModifier)();
    const ArkUIAniCustomNodeModifier* (*getCustomNodeAniModifier)();
    const ArkUIAniContentSlotModifier* (*getContentSlotAniModifier)();
    const ArkUIAniDrawModifier* (*getArkUIAniDrawModifier)();
    const ArkUIAniComponentSnapshotModifier* (*getComponentSnapshotAniModifier)();
};

__attribute__((visibility("default"))) const ArkUIAniModifiers* GetArkUIAniModifiers(void);
#ifdef __cplusplus
};
#endif

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ANI_API_H
