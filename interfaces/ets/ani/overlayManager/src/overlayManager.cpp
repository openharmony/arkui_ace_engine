/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <ani.h>
#include <string>

#include "base/log/log_wrapper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "frameworks/core/interfaces/native/ani/frame_node_peer_impl.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "ui/base/referenced.h"

using namespace OHOS::Ace;

static void PostOverlayTask(
    std::function<void(RefPtr<NG::OverlayManager>)>&& task, int32_t containerId, const std::string& name)
{
    auto context = NG::PipelineContext::GetContextByContainerId(containerId);
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    context->GetTaskExecutor()->PostTask(
        [task = std::move(task), weak = WeakPtr<NG::OverlayManager>(overlayManager), containerId] {
            ContainerScope scope(containerId);
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            task(overlayManager);
        },
        TaskExecutor::TaskType::UI, name);
}

static bool IsUndefinedObject(ani_env *env, ani_ref object_ref)
{
    ani_boolean isUndefined = ANI_TRUE;
    if (ANI_OK != env->Reference_IsUndefined(object_ref, &isUndefined)) {
        return false;
    }
    return (bool)isUndefined;
}

static bool IsOverlayManagerOptionsObject(ani_env *env, ani_object object)
{
    ani_class optionsClass = nullptr;
    if (ANI_OK != env->FindClass("@ohos.arkui.UIContext.OverlayManagerOptions", &optionsClass)) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "Cannot find class OverlayManagerOptions.");
        return false;
    }
    ani_boolean isOptions = ANI_FALSE;
    if (env->Object_InstanceOf(object, optionsClass, &isOptions)) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "The object is not OverlayManagerOptions.");
        return false;
    }
    return (bool)isOptions;
}

static ani_status GetBoolFromAni(ani_env* env, ani_object obj, const char* name, bool* value)
{
    ani_status status = ANI_ERROR;
    if (value == nullptr) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "The value is null.");
        return status;
    }
    ani_ref refValue = nullptr;
    status = env->Object_GetPropertyByName_Ref(obj, name, &refValue);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "Get property renderRootOverlay failed(%{public}d).", status);
        return status;
    }
    if (IsUndefinedObject(env, refValue)) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "The refValue is undefined.");
        return status;
    }
    ani_boolean boolValue = ANI_FALSE;
    status = env->Object_CallMethodByName_Boolean(static_cast<ani_object>(refValue), "toBoolean", ":z", &boolValue);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "Unbox bool value failed");
        return status;
    }
    *value = static_cast<bool>(boolValue);
    return status;
}

static bool GetOverlayManagerInfo(ani_env* env, ani_object options, NG::OverlayManagerInfo& overlayInfo)
{
    if (IsUndefinedObject(env, options)) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "The options is undefined");
        return false;
    }

    if (!IsOverlayManagerOptionsObject(env, options)) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "The type of options is not right.");
        return false;
    }

    if (GetBoolFromAni(env, options, "renderRootOverlay", &overlayInfo.renderRootOverlay) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "Get property renderRootOverlay failed.");
        return false;
    }

    if (GetBoolFromAni(env, options, "enableBackPressedEvent", &overlayInfo.enableBackPressedEvent) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "Get property enableBackPressedEvent failed.");
        return false;
    }
    return true;
}

static ani_boolean SetOverlayManagerOptions(ani_env* env, ani_object options)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "ani SetOverlayManagerOptions enter");
    ani_boolean ret = ANI_FALSE;
    RefPtr<NG::PipelineContext> context = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(context, ret);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, ret);

    auto overlayInfo = NG::OverlayManagerInfo {
        .renderRootOverlay = true,
        .enableBackPressedEvent = false,
    };
    if (!GetOverlayManagerInfo(env, options, overlayInfo)) {
        return ret;
    }

    return overlayManager->SetOverlayManagerOptions(overlayInfo) ? ANI_TRUE : ANI_FALSE;
}

static ani_status CreateAniBoolean(ani_env* env, bool value, ani_object& result)
{
    ani_status state;
    ani_class booleanClass;
    if ((state = env->FindClass("std.core.Boolean", &booleanClass)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "FindClass std.core.Boolean failed, %{public}d", state);
        return state;
    }
    ani_method booleanClassCtor;
    if ((state = env->Class_FindMethod(booleanClass, "<ctor>", "z:", &booleanClassCtor)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "Class_FindMethod Boolean ctor failed, %{public}d", state);
        return state;
    }
    ani_boolean aniValue = value;
    if ((state = env->Object_New(booleanClass, booleanClassCtor, &result, aniValue)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "New Boolean object failed, %{public}d", state);
        return state;
    }
    return state;
}

static ani_object GetOverlayManagerOptions(ani_env* env)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "ani GetOverlayManagerOptions enter");
    ani_object options = {};
    RefPtr<NG::PipelineContext> context = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(context, options);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, options);

    auto overlayInfo = overlayManager->GetOverlayManagerOptions();
    if (!overlayInfo.has_value()) {
        overlayInfo = NG::OverlayManagerInfo {
            .renderRootOverlay = true,
            .enableBackPressedEvent = false,
        };
    }

    ani_class cls;
    if (ANI_OK != env->FindClass("@ohos.arkui.UIContext.OverlayManagerOptionsInner", &cls)) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "FindClass OverlayManagerOptionsInner failed");
        return options;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", ":", &ctor)) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "Cannot find OverlayManagerOptionsInner ctor");
        return options;
    }
    if (ANI_OK != env->Object_New(cls, ctor, &options)) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "Create OverlayManagerOptionsInner object failed");
        return options;
    }

    ani_object renderRootOverlayObj;
    CreateAniBoolean(env, overlayInfo->renderRootOverlay, renderRootOverlayObj);
    if (ANI_OK != env->Object_SetPropertyByName_Ref(options, "renderRootOverlay", renderRootOverlayObj)) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "Set property renderRootOverlay failed");
    }

    ani_object enableBackPressedEventObj;
    CreateAniBoolean(env, overlayInfo->enableBackPressedEvent, enableBackPressedEventObj);
    if (ANI_OK != env->Object_SetPropertyByName_Ref(options, "enableBackPressedEvent", enableBackPressedEventObj)) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "Set property enableBackPressedEvent failed");
    }

    return options;
}

static void AddComponentContent(ani_env* env, ani_long aniNode, ani_int aniIndex)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "ani AddComponentContent enter: index: %{public}d", (int32_t)aniIndex);
    FrameNodePeer* peerNode = (FrameNodePeer*)aniNode;
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peerNode);
    CHECK_NULL_VOID(frameNode);
    auto index = static_cast<int>(aniIndex);
    auto context = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto instanceId = context->GetInstanceId();
    auto task = [weak = Referenced::WeakClaim(Referenced::RawPtr(frameNode)), index](
            const RefPtr<NG::OverlayManager>& overlayManager) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        overlayManager->AddFrameNodeToOverlay(frameNode, index);
    };
    PostOverlayTask(std::move(task), instanceId, "ani AddComponentContent");
}

static void AddComponentContentWithOrder(ani_env* env, ani_long aniNode, ani_object aniLevelOrder)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "ani AddComponentContentWithOrder enter");
    std::optional<double> orderNumber = std::nullopt;
    if (aniLevelOrder != 0) {
        ani_class levelOrderCls;
        ani_status status = env->FindClass("@ohos.promptAction.LevelOrder", &levelOrderCls);
        if (status != ANI_OK) {
            TAG_LOGE(AceLogTag::ACE_OVERLAY, "Find LevelOrder failed(%{public}d)", status);
            return;
        }

        ani_method getOrderMethod;
        status = env->Class_FindMethod(levelOrderCls, "getOrder", ":d", &getOrderMethod);
        if (status != ANI_OK) {
            TAG_LOGE(AceLogTag::ACE_OVERLAY, "Find getOrder failed(%{public}d)", status);
            return;
        }

        ani_double orderValue;
        status = env->Object_CallMethod_Double(aniLevelOrder, getOrderMethod, &orderValue);
        if (status != ANI_OK) {
            TAG_LOGE(AceLogTag::ACE_OVERLAY, "Call getOrder failed(%{public}d)", status);
            return;
        }
        orderNumber = std::make_optional(orderValue);
    }

    FrameNodePeer* peerNode = (FrameNodePeer*)aniNode;
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peerNode);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->AddFrameNodeWithOrder(frameNode, orderNumber);
}

static void RemoveComponentContent(ani_env* env, ani_long aniNode)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "ani RemoveComponentContent enter");
    FrameNodePeer* peerNode = (FrameNodePeer*)aniNode;
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peerNode);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto instanceId = context->GetInstanceId();
    auto task = [weak = Referenced::WeakClaim(Referenced::RawPtr(frameNode))](
            const RefPtr<NG::OverlayManager>& overlayManager) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        overlayManager->RemoveFrameNodeOnOverlay(frameNode);
    };
    PostOverlayTask(std::move(task), instanceId, "ani RemoveComponentContent");
}

static void ShowComponentContent(ani_env* env, ani_long aniNode)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "ani ShowComponentContent enter");
    FrameNodePeer* peerNode = (FrameNodePeer*)aniNode;
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peerNode);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto instanceId = context->GetInstanceId();
    auto task = [weak = Referenced::WeakClaim(Referenced::RawPtr(frameNode))](
            const RefPtr<NG::OverlayManager>& overlayManager) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        overlayManager->ShowNodeOnOverlay(frameNode);
    };
    PostOverlayTask(std::move(task), instanceId, "ani ShowComponentContent");
}

static void HideComponentContent(ani_env* env, ani_long aniNode)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "ani HideComponentContent enter");
    FrameNodePeer* peerNode = (FrameNodePeer*)aniNode;
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peerNode);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto instanceId = context->GetInstanceId();
    auto task = [weak = Referenced::WeakClaim(Referenced::RawPtr(frameNode))](
            const RefPtr<NG::OverlayManager>& overlayManager) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        overlayManager->HideNodeOnOverlay(frameNode);
    };
    PostOverlayTask(std::move(task), instanceId, "ani HideComponentContent");
}

static void ShowAllComponentContents(ani_env* env)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "ani ShowAllComponentContents enter");
    RefPtr<NG::PipelineContext> context = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    auto instanceId = context->GetInstanceId();
    auto task = [](const RefPtr<NG::OverlayManager>& overlayManager) {
        overlayManager->ShowAllNodesOnOverlay();
    };
    PostOverlayTask(std::move(task), instanceId, "ani ShowAllComponentContents");
}

static void HideAllComponentContents(ani_env* env)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "ani HideAllComponentContents enter");
    RefPtr<NG::PipelineContext> context = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    auto instanceId = context->GetInstanceId();
    auto task = [instanceId](const RefPtr<NG::OverlayManager>& overlayManager) {
        overlayManager->HideAllNodesOnOverlay();
    };
    PostOverlayTask(std::move(task), instanceId, "ani HideAllComponentContents");
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "ani OverlayManager ANI_Constructor start");
    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }

    ani_namespace ns;
    if (ANI_OK != env->FindNamespace("@ohos.overlayManager.overlayManager", &ns)) {
        return ANI_ERROR;
    }
    std::array methods = {
        ani_native_function {"setOverlayManagerOptions", nullptr, reinterpret_cast<void *>(SetOverlayManagerOptions)},
        ani_native_function {"getOverlayManagerOptions", nullptr, reinterpret_cast<void *>(GetOverlayManagerOptions)},
        ani_native_function {"addComponentContent", nullptr, reinterpret_cast<void *>(AddComponentContent)},
        ani_native_function {"addComponentContentWithOrder", nullptr,
            reinterpret_cast<void *>(AddComponentContentWithOrder)},
        ani_native_function {"removeComponentContent", nullptr, reinterpret_cast<void *>(RemoveComponentContent)},
        ani_native_function {"showComponentContent", nullptr, reinterpret_cast<void *>(ShowComponentContent)},
        ani_native_function {"hideComponentContent", nullptr, reinterpret_cast<void *>(HideComponentContent)},
        ani_native_function {"showAllComponentContents", nullptr, reinterpret_cast<void *>(ShowAllComponentContents)},
        ani_native_function {"hideAllComponentContents", nullptr, reinterpret_cast<void *>(HideAllComponentContents)},
    };
    if (ANI_OK != env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size())) {
        return ANI_ERROR;
    }

    *result = ANI_VERSION_1;
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "ani OverlayManager ANI_Constructor end");
    return ANI_OK;
}