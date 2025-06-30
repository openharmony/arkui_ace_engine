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
#include "core/common/udmf/udmf_client.h"
#include "core/components_ng/render/adapter/component_snapshot.h"
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
typedef class __ani_string* ani_string;
typedef class __ani_enum_item* ani_enum_item;
typedef class __ani_error* ani_error;
typedef _ArkUINode* ArkUINodeHandle;
typedef int ArkUI_Int32;
typedef size_t ani_size;
typedef _ArkUIContentSlot* ArkUIContentSlot;
typedef _ArkUINodeContent* ArkUINodeContent;
struct ArkUIDragInfo {
    void* pixelMap;
    bool onlyForLifting = false;
    bool delayCreating = false;
};

struct ArkUIAniImageModifier {
    void (*setPixelMap)(ArkUINodeHandle node, void* pixelmap);
    void (*setResizableLattice)(ArkUINodeHandle node, void* lattice);
};

struct ArkUIAniWebModifier {
    void (*setWebOptions)(ArkUINodeHandle node,
        std::function<void(int32_t)>&& onNWebId,
        std::function<void(const std::string&)>&& onHapPath);
};
struct ArkUIAniDragModifier {
    void (*setDragData)(ani_ref event, ani_ref data);
    ani_ref (*getDragData)(ani_ref event);
    void (*getDragSummary)(ani_ref event, ani_ref summaryPtr);
    void (*setDragDropInfoPixelMap)(ani_ref event, ani_ref pixelMap);
    void (*setDragDropInfoCustomNode)(ani_ref event, ArkUINodeHandle node);
    void (*setDragDropInfoExtraInfo)(ani_ref event, const char* ptr);
    void (*setDragAllowDropNull)(ArkUINodeHandle node);
    void (*setDragAllowDrop)(ArkUINodeHandle node, const char** allowDrops, ArkUI_Int32 length);
    void (*setDragPreview)(ArkUINodeHandle node, ArkUIDragInfo dragInfo);
    const char* (*getUdKey)(ani_ref event);
};
struct ArkUIAniCommonModifier {
    ani_ref* (*getHostContext)();
    void (*syncInstanceId)(ArkUI_Int32 id);
    void (*restoreInstanceId)();
    void (*setDrawCallback)(ani_env* env, ani_long ptr, ani_fn_object fnObj);
    ArkUI_Int32 (*getCurrentInstanceId)();
    ani_long (*builderProxyNodeConstruct)(ArkUI_Int32 id);
    ani_ref (*getSharedLocalStorage)();
    void (*setBackgroundImagePixelMap)(ani_env* env, ArkUINodeHandle node, ani_ref pixelMapPtr, ArkUI_Int32 repeat);
    void (*setCustomCallback)(ani_env* env, ani_long ptr, ani_fn_object fnObjMeasure, ani_fn_object fnObjLayout);
    ArkUI_Int32 (*requireArkoalaNodeId)(ArkUI_Int32 capacity);
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
struct ArkUIAniWaterFlowModifier {
    void (*setWaterFlowOptions)(ani_env* env, ani_long ptr, ani_object fnObj);
};
struct ArkUIAniComponentSnapshotModifier {
    int32_t (*getCurrentIdSafely)();
    OHOS::Ace::RefPtr<OHOS::Ace::Container> (*getContainer)(int32_t instanceId);
    void (*createFromBuilder)(ArkUINodeHandle node,
    OHOS::Ace::NG::ComponentSnapshot::JsCallback&& callback,
    OHOS::Ace::NG::SnapshotParam param);
    void (*createFromComponent)(ArkUINodeHandle node,
    OHOS::Ace::NG::ComponentSnapshot::JsCallback&& callback,
    OHOS::Ace::NG::SnapshotParam param);
};
struct ArkUIAniAnimationModifier {
    bool (*hasAnimatableProperty)(ani_env* env, ArkUINodeHandle node, ani_string name);
    void (*updateAnimatableProperty)(
        ani_env* env, ArkUINodeHandle node, ani_string propertyName, ani_object property);
    void (*createAnimatableProperty)(
        ani_env* env, ArkUINodeHandle node, ani_string propertyName, ani_object property, ani_fn_object callback);
};
struct ArkUIAniDragControllerModifier {
    ani_object (*aniExecuteDragWithCallback)(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object custom,
        ani_long builderObj, ani_object destroyCallbackObj, ani_object dragInfo, ani_object callback);
    ani_object (*aniCreateDragAction)([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass,
        ani_object customArray, ani_object builderArray, ani_object destroyCallbackObj,
        [[maybe_unused]] ani_object dragInfoObj);
    ani_object (*aniDragActionStartDrag)(
        [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long dragActionPtr);
    void (*aniDragActionOn)([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, const char* type,
        ani_object callback, ani_long dragActionPtr);
    void (*aniDragActionOff)([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, const char* type,
        [[maybe_unused]] ani_object callback, ani_long dragActionPtr);
    void (*aniDragActionSetDragEventStrictReportingEnabled)(
        [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, bool enable);
    void (*aniDragActionCancelDataLoading)(
        [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string key);
    void (*aniDragActionNotifyDragStartReques)(
        [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_enum_item requestStatus);
};
struct ArkUIAniImageSpanModifier {
    void (*setPixelMap)(ArkUINodeHandle node, void* pixelmap);
    void (*setAltPixelMap)(ArkUINodeHandle node, void* pixelmap);
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
    const ArkUIAniWaterFlowModifier* (*getArkUIAniWaterFlowModifier)();
    const ArkUIAniComponentSnapshotModifier* (*getComponentSnapshotAniModifier)();
    const ArkUIAniAnimationModifier* (*getAnimationAniModifier)();
    const ArkUIAniDragControllerModifier* (*getDragControllerAniModifier)();
    const ArkUIAniImageSpanModifier* (*getImageSpanAniModifier)();
};

__attribute__((visibility("default"))) const ArkUIAniModifiers* GetArkUIAniModifiers(void);
#ifdef __cplusplus
};
#endif

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ANI_API_H
