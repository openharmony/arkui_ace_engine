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
#include "common_ani_modifier.h"
#include "ani_utils.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/multi_thread_build_manager.h"
#include "core/common/thread_checker.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "bridge/arkts_frontend/ani_graphics_module.h"
#include "bridge/arkts_frontend/arkts_frontend.h"
#include "bridge/arkts_frontend/ani_context_module.h"

#include <memory>
#include <vector>

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr int NUM_8 = 8;
}
static thread_local std::vector<int32_t> restoreInstanceIds_;

ani_ref* GetHostContext()
{
    auto contextValue = OHOS::Ace::Framework::AniContextModule::GetAniContext();
    if (contextValue) {
        return contextValue.get();
    }
    return nullptr;
}

void SyncInstanceId(ArkUI_Int32 instanceId)
{
    restoreInstanceIds_.emplace_back(ContainerScope::CurrentId());
    ContainerScope::UpdateCurrent(instanceId);
}

void RestoreInstanceId()
{
    if (restoreInstanceIds_.empty()) {
        ContainerScope::UpdateCurrent(-1);
        return;
    }
    ContainerScope::UpdateCurrent(restoreInstanceIds_.back());
    restoreInstanceIds_.pop_back();
}

void SetDrawCallback(ani_env* env, ani_long ptr, ani_fn_object fnObj)
{
    Framework::AniGraphicsModule::SetDrawCallback(env, ptr, fnObj);
}

ArkUI_Int32 GetCurrentInstanceId()
{
    return ContainerScope::CurrentId();
}

ArkUI_Int32 GetFocusedInstanceId()
{
    auto container = Container::GetFoucsed();
    CHECK_NULL_RETURN(container, -1);
    return container->GetInstanceId();
}

ani_long BuilderProxyNodeConstruct(ArkUI_Int32 id)
{
    auto proxyNode = NG::FrameNode::GetOrCreateFrameNode(
        "BuilderProxyNode", id, []() { return AceType::MakeRefPtr<StackPattern>(); });
    CHECK_NULL_RETURN(proxyNode, 0);
    auto stackLayoutAlgorithm = proxyNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_RETURN(stackLayoutAlgorithm, 0);
    stackLayoutAlgorithm->UpdateAlignment(Alignment::TOP_LEFT);
    proxyNode->IncRefCount();
    return reinterpret_cast<ani_long>(AceType::RawPtr(proxyNode));
}

ani_ref GetSharedLocalStorage()
{
    auto context = NG::PipelineContext::GetCurrentContextSafely();
    if (context == nullptr) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "GetSharedLocalStorage-ani can not get current context.");
        return nullptr;
    }
    auto frontend = context->GetFrontend();
    if (frontend == nullptr) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "GetSharedLocalStorage-ani can not get current frontend.");
        return nullptr;
    }
    auto arkTsFrontend = AceType::DynamicCast<ArktsFrontend>(frontend);
    if (arkTsFrontend == nullptr) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "GetSharedLocalStorage-ani can not convert to arkts frontend.");
        return nullptr;
    }
    int32_t currentInstance = Container::CurrentIdSafely();
    auto storage = arkTsFrontend->GetShared(currentInstance);
    if (storage) {
        return storage;
    }
    return nullptr;
}

void SetBackgroundImagePixelMap(ani_env* env, ArkUINodeHandle node, ani_ref pixelMapPtr, ArkUI_Int32 repeat)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pixelMapValue = reinterpret_cast<void*>(pixelMapPtr);
    CHECK_NULL_VOID(pixelMapValue);
#if defined(PIXEL_MAP_SUPPORTED)
    auto pixelMap = PixelMap::CreatePixelMap(pixelMapValue);
    CHECK_NULL_VOID(pixelMap);
    ViewAbstract::SetBackgroundImage(frameNode, ImageSourceInfo { pixelMap });
#endif
    auto arkRepeat = static_cast<OHOS::Ace::ImageRepeat>(repeat);
    if (arkRepeat >= OHOS::Ace::ImageRepeat::NO_REPEAT && arkRepeat <= OHOS::Ace::ImageRepeat::REPEAT) {
        ViewAbstract::SetBackgroundImageRepeat(frameNode, arkRepeat);
    } else {
        ViewAbstract::SetBackgroundImageRepeat(frameNode, OHOS::Ace::ImageRepeat::NO_REPEAT);
    }
}

void SetCustomCallback(ani_env* env, ani_long ptr, ani_fn_object fnObjMeasure, ani_fn_object fnObjLayout)
{
    Framework::AniGraphicsModule::SetCustomCallback(env, ptr, fnObjMeasure, fnObjLayout);
}

ArkUI_Int32 RequireArkoalaNodeId(ArkUI_Int32 capacity)
{
    auto cursor = ElementRegister::GetInstance()->RequireArkoalaNodeId(capacity);
    return cursor;
}

ani_boolean CheckIsUIThread(ArkUI_Int32 instanceId)
{
    SyncInstanceId(instanceId);
    bool res = CheckThread(TaskExecutor::TaskType::UI);
    RestoreInstanceId();
    return res;
}

ani_boolean IsDebugMode(ArkUI_Int32 instanceId)
{
    SyncInstanceId(instanceId);
    auto& aceApplicationInfo = AceApplicationInfo::GetInstance();
    bool res = aceApplicationInfo.IsDebugForParallel();
    RestoreInstanceId();
    return res;
}

void OnMeasureInnerMeasure(ani_env* env, ani_long ptr)
{
    Framework::AniGraphicsModule::OnMeasureInnerMeasure(env, ptr);
}

void OnLayoutInnerLayout(ani_env* env, ani_long ptr)
{
    Framework::AniGraphicsModule::OnLayoutInnerLayout(env, ptr);
}

void FrameNodeMarkDirtyNode(ani_env* env, ani_long ptr)
{
    Framework::AniGraphicsModule::FrameNodeMarkDirtyNode(env, ptr);
}

Alignment ParseAlignment(int32_t align)
{
    Alignment alignment = Alignment::CENTER;
    switch (align) {
        case NUM_0:
            alignment = Alignment::TOP_LEFT;
            break;
        case NUM_1:
            alignment = Alignment::TOP_CENTER;
            break;
        case NUM_2:
            alignment = Alignment::TOP_RIGHT;
            break;
        case NUM_3:
            alignment = Alignment::CENTER_LEFT;
            break;
        case NUM_4:
            alignment = Alignment::CENTER;
            break;
        case NUM_5:
            alignment = Alignment::CENTER_RIGHT;
            break;
        case NUM_6:
            alignment = Alignment::BOTTOM_LEFT;
            break;
        case NUM_7:
            alignment = Alignment::BOTTOM_CENTER;
            break;
        case NUM_8:
            alignment = Alignment::BOTTOM_RIGHT;
            break;
        default:
            break;
    }
    return alignment;
}

void SetOverlayComponent(ani_long node, ani_long builderPtr, AniOverlayOptions options)
{
    CHECK_NULL_VOID(node);
    FrameNode* frameNode = reinterpret_cast<FrameNode*>(node);
    FrameNodePeer* overlayNodePeer = builderPtr ? reinterpret_cast<FrameNodePeer*>(builderPtr) : nullptr;
    RefPtr<NG::FrameNode> overlayNode = FrameNodePeer::GetFrameNodeByPeer(overlayNodePeer);
    CalcDimension x(options.x, DimensionUnit::VP);
    CalcDimension y(options.y, DimensionUnit::VP);
    Alignment align = ParseAlignment(options.alignment);
    ViewAbstract::SetOverlayBuilder(frameNode, overlayNode, align, x, y);
}

void SetParallelScoped(ani_boolean parallel)
{
    MultiThreadBuildManager::SetIsThreadSafeNodeScope(parallel);
}

const ArkUIAniCommonModifier* GetCommonAniModifier()
{
    static const ArkUIAniCommonModifier impl = {
        .getHostContext = OHOS::Ace::NG::GetHostContext,
        .syncInstanceId = OHOS::Ace::NG::SyncInstanceId,
        .restoreInstanceId = OHOS::Ace::NG::RestoreInstanceId,
        .setDrawCallback = OHOS::Ace::NG::SetDrawCallback,
        .getCurrentInstanceId = OHOS::Ace::NG::GetCurrentInstanceId,
        .getFocusedInstanceId = OHOS::Ace::NG::GetFocusedInstanceId,
        .builderProxyNodeConstruct = OHOS::Ace::NG::BuilderProxyNodeConstruct,
        .getSharedLocalStorage = OHOS::Ace::NG::GetSharedLocalStorage,
        .setBackgroundImagePixelMap = OHOS::Ace::NG::SetBackgroundImagePixelMap,
        .setCustomCallback = OHOS::Ace::NG::SetCustomCallback,
        .requireArkoalaNodeId = OHOS::Ace::NG::RequireArkoalaNodeId,
        .checkIsUIThread = OHOS::Ace::NG::CheckIsUIThread,
        .isDebugMode =  OHOS::Ace::NG::IsDebugMode,
        .onMeasureInnerMeasure = OHOS::Ace::NG::OnMeasureInnerMeasure,
        .onLayoutInnerLayout = OHOS::Ace::NG::OnLayoutInnerLayout,
        .frameNodeMarkDirtyNode = OHOS::Ace::NG::FrameNodeMarkDirtyNode,
        .setOverlayComponent = OHOS::Ace::NG::SetOverlayComponent,
        .setParallelScoped = OHOS::Ace::NG::SetParallelScoped
    };
    return &impl;
}

void SetDrawModifier(ani_env* env, ani_long ptr, ani_int flag, ani_object fnObj)
{
    Framework::AniGraphicsModule::SetDrawModifier(env, ptr, flag, fnObj);
}

void Invalidate(ani_env* env, ani_long ptr)
{
    Framework::AniGraphicsModule::Invalidate(env, ptr);
}

const ArkUIAniDrawModifier* GetArkUIAniDrawModifier()
{
    static const ArkUIAniDrawModifier impl = {
        .setDrawModifier = OHOS::Ace::NG::SetDrawModifier,
        .invalidate = OHOS::Ace::NG::Invalidate,
    };
    return &impl;
}
} // namespace OHOS::Ace::NG
