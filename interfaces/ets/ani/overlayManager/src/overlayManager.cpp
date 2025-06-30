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
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
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

static ani_boolean SetOverlayManagerOptions([[maybe_unused]] ani_env* env, ani_object options)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "ani SetOverlayManagerOptions enter");
    return ANI_TRUE;
}

static ani_object GetOverlayManagerOptions([[maybe_unused]] ani_env* env)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "ani GetOverlayManagerOptions enter");
    return nullptr;
}

static void AddComponentContent([[maybe_unused]] ani_env* env, ani_long aniNode, ani_int aniIndex)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "ani AddComponentContent enter: index: %{public}d", (int32_t)aniIndex);
    Ark_FrameNode peerNode = (Ark_FrameNode)aniNode;
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

static void AddComponentContentWithOrder([[maybe_unused]] ani_env* env, ani_long aniNode, ani_int aniLevelOrder)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "ani AddComponentContentWithOrder enter");
}

static void RemoveComponentContent([[maybe_unused]] ani_env* env, ani_long aniNode)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "ani RemoveComponentContent enter");
    Ark_FrameNode peerNode = (Ark_FrameNode)aniNode;
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

static void ShowComponentContent([[maybe_unused]] ani_env* env, ani_long aniNode)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "ani ShowComponentContent enter");
    Ark_FrameNode peerNode = (Ark_FrameNode)aniNode;
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

static void HideComponentContent([[maybe_unused]] ani_env* env, ani_long aniNode)
{
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "ani HideComponentContent enter");
    Ark_FrameNode peerNode = (Ark_FrameNode)aniNode;
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

static void ShowAllComponentContents([[maybe_unused]] ani_env* env)
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

static void HideAllComponentContents([[maybe_unused]] ani_env* env)
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
    if (ANI_OK != env->FindNamespace("L@ohos/overlayManager/overlayManager;", &ns)) {
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