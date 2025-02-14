/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/pipeline/pipeline_context.h"
#include <cstdlib>
#include "base/utils/utils.h"

#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_base/include/platform/common/rs_system_properties.h"
#include "render_service_client/core/ui/rs_node.h"
#include "render_service_client/core/ui/rs_surface_node.h"
#include "render_service_client/core/ui/rs_ui_director.h"
#include "render_service_client/core/transaction/rs_transaction.h"

#include "core/animation/native_curve_helper.h"
#endif

#include "base/log/ace_tracker.h"
#include "base/log/dump_log.h"
#include "base/log/event_report.h"
#include "base/ressched/ressched_report.h"
#include "core/animation/card_transition_controller.h"
#include "core/animation/shared_transition_controller.h"
#include "core/common/font_manager.h"
#include "core/common/layout_inspector.h"
#include "core/common/text_field_manager.h"
#include "core/components/container_modal/container_modal_element.h"
#include "core/components/dialog/dialog_component.h"
#include "core/components/dialog_modal/dialog_modal_component.h"
#include "core/components/dialog_modal/dialog_modal_element.h"
#include "core/components/focus_animation/render_focus_animation.h"
#include "core/components/overlay/overlay_component.h"
#include "core/components/root/render_root.h"
#include "core/components/root/root_component.h"
#include "core/components/root/root_element.h"
#include "core/components/select_popup/select_popup_component.h"
#include "core/components/semi_modal/semi_modal_component.h"
#include "core/components/semi_modal/semi_modal_element.h"
#include "core/components/semi_modal/semi_modal_theme.h"
#include "core/components/stage/stage_component.h"
#include "core/components/theme/app_theme.h"
#include "core/components_v2/inspector/shape_composed_element.h"
#include "core/components_v2/list/render_list.h"
#include "core/pipeline/base/factories/flutter_render_factory.h"

namespace OHOS::Ace {
namespace {

constexpr int64_t SEC_TO_NANOSEC = 1000000000;
constexpr char JS_THREAD_NAME[] = "JS";
constexpr char UI_THREAD_NAME[] = "UI";
constexpr uint32_t DEFAULT_MODAL_COLOR = 0x00000000;
constexpr float ZOOM_DISTANCE_DEFAULT = 50.0;
constexpr float ZOOM_DISTANCE_MOVE_PER_WHEEL = 5.0;
constexpr int32_t FLUSH_RELOAD_TRANSITION_DURATION_MS = 400;
constexpr int32_t ROTATION_DIVISOR = 64; // from adapter/ohos/entrance/ace_view_ohos.cpp

PipelineContext::TimeProvider g_defaultTimeProvider = []() -> uint64_t {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * SEC_TO_NANOSEC + ts.tv_nsec);
};

Rect GetGlobalRect(const RefPtr<Element>& element)
{
    if (!element) {
        LOGE("element is null!");
        return Rect();
    }
    const auto& renderNode = element->GetRenderNode();
    if (!renderNode) {
        LOGE("Get render node failed!");
        return Rect();
    }
    return Rect(renderNode->GetGlobalOffset(), renderNode->GetLayoutSize());
}

void ThreadStuckTask(int32_t seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

} // namespace

PipelineContext::PipelineContext(std::shared_ptr<Window> window, RefPtr<TaskExecutor> taskExecutor,
    RefPtr<AssetManager> assetManager, RefPtr<PlatformResRegister> platformResRegister,
    const RefPtr<Frontend>& frontend, int32_t instanceId)
    : PipelineBase(window, std::move(taskExecutor), std::move(assetManager), frontend, instanceId,
          (std::move(platformResRegister))),
      timeProvider_(g_defaultTimeProvider)
{
    RegisterEventHandler(frontend->GetEventHandler());
    focusAnimationManager_ = AceType::MakeRefPtr<FocusAnimationManager>();
    sharedTransitionController_ = AceType::MakeRefPtr<SharedTransitionController>(AceType::WeakClaim(this));
    cardTransitionController_ = AceType::MakeRefPtr<CardTransitionController>(AceType::WeakClaim(this));
    if (frontend->GetType() == FrontendType::JS_CARD) {
        imageCache_.Reset();
    }
    renderFactory_ = AceType::MakeRefPtr<FlutterRenderFactory>();
    eventManager_ = AceType::MakeRefPtr<EventManager>();
    UpdateFontWeightScale();
    eventManager_->SetInstanceId(instanceId);
    textOverlayManager_ = AceType::MakeRefPtr<TextOverlayManager>(WeakClaim(this));
}

PipelineContext::PipelineContext(std::shared_ptr<Window> window, RefPtr<TaskExecutor>& taskExecutor,
    RefPtr<AssetManager> assetManager, const RefPtr<Frontend>& frontend)
    : PipelineBase(window, std::move(taskExecutor), std::move(assetManager), frontend, 0),
      timeProvider_(g_defaultTimeProvider)
{
    RegisterEventHandler(frontend->GetEventHandler());

    focusAnimationManager_ = AceType::MakeRefPtr<FocusAnimationManager>();
    sharedTransitionController_ = AceType::MakeRefPtr<SharedTransitionController>(AceType::WeakClaim(this));
    cardTransitionController_ = AceType::MakeRefPtr<CardTransitionController>(AceType::WeakClaim(this));
    renderFactory_ = AceType::MakeRefPtr<FlutterRenderFactory>();
    UpdateFontWeightScale();
    textOverlayManager_ = AceType::MakeRefPtr<TextOverlayManager>(WeakClaim(this));
}

PipelineContext::~PipelineContext()
{
    LOGI("PipelineContext destroyed");
}

void PipelineContext::FlushPipelineWithoutAnimation()
{
    FlushBuild();
    FlushPostAnimation();
    FlushLayout();
    FlushRender();
    FlushRenderFinish();
    FlushWindowBlur();
    if (onShow_ && onFocus_) {
        FlushFocus();
    }
    FireVisibleChangeEvent();
    ProcessPostFlush();
    ClearDeactivateElements();
    FlushMessages();
}

void PipelineContext::FlushMessages()
{
    ACE_FUNCTION_TRACK();
#ifdef ENABLE_ROSEN_BACKEND
    if (SystemProperties::GetRosenBackendEnabled() && rsUIDirector_) {
        rsUIDirector_->SendMessages();
    }
#endif
}

void PipelineContext::FlushBuild()
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACK();
    ACE_FUNCTION_TRACE();

    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().BeginFlushBuild();
    }

    isRebuildFinished_ = false;
    if (dirtyElements_.empty()) {
        isRebuildFinished_ = true;
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().EndFlushBuild();
        }
        return;
    }
    decltype(dirtyElements_) dirtyElements(std::move(dirtyElements_));
    for (const auto& elementWeak : dirtyElements) {
        auto element = elementWeak.Upgrade();
        // maybe unavailable when update parent
        if (element && element->IsActive()) {
            auto stageElement = AceType::DynamicCast<StageElement>(element);
            if (stageElement && stageElement->GetStackOperation() == StackOperation::POP) {
                stageElement->PerformBuild();
            } else {
                element->Rebuild();
            }
        }
    }
    isRebuildFinished_ = true;
    if (!buildAfterCallback_.empty()) {
        for (const auto& item : buildAfterCallback_) {
            item();
        }
        buildAfterCallback_.clear();
    }
    buildingFirstPage_ = false;

    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().EndFlushBuild();
    }
#if !defined(PREVIEW)
    LayoutInspector::SupportInspector();
#endif
}

void PipelineContext::FlushPredictLayout(int64_t deadline)
{
    CHECK_RUN_ON(UI);
    if (predictLayoutNodes_.empty()) {
        return;
    }
    ACE_FUNCTION_TRACE();
    decltype(predictLayoutNodes_) dirtyNodes(std::move(predictLayoutNodes_));
    for (const auto& dirtyNode : dirtyNodes) {
        dirtyNode->OnPredictLayout(deadline);
    }
}

void PipelineContext::FlushFocus()
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACK();
    auto focusNode = dirtyFocusNode_.Upgrade();
    if (!focusNode) {
        dirtyFocusNode_.Reset();
    } else {
        focusNode->RequestFocusImmediately();
        dirtyFocusNode_.Reset();
        dirtyFocusScope_.Reset();
        return;
    }
    auto focusScope = dirtyFocusScope_.Upgrade();
    if (!focusScope) {
        dirtyFocusScope_.Reset();
    } else {
        focusScope->RequestFocusImmediately();
        dirtyFocusNode_.Reset();
        dirtyFocusScope_.Reset();
        return;
    }
    if (!RequestDefaultFocus()) {
        if (rootElement_ && !rootElement_->IsCurrentFocus()) {
            rootElement_->RequestFocusImmediately();
        }
    }

    if (GetIsDeclarative()) {
        return;
    }
    decltype(needRebuildFocusElement_) rebuildElements(std::move(needRebuildFocusElement_));
    for (const auto& elementWeak : rebuildElements) {
        auto element = elementWeak.Upgrade();
        if (element) {
            element->RebuildFocusTree();
        }
    }
}

void PipelineContext::FireVisibleChangeEvent()
{
    ACE_FUNCTION_TRACK();
    if (GetIsDeclarative()) {
        HandleVisibleAreaChangeEvent();
        return;
    }

    auto accessibilityManager = GetAccessibilityManager();
    if (accessibilityManager) {
        accessibilityManager->TriggerVisibleChangeEvent();
    }
}

void PipelineContext::HandleVisibleAreaChangeEvent()
{
    if (visibleAreaChangeNodes_.empty()) {
        return;
    }
    for (auto& visibleChangeNode : visibleAreaChangeNodes_) {
        auto visibleNodeId = visibleChangeNode.first;
        auto composedElement = GetComposedElementById(visibleNodeId);
        if (!composedElement) {
            continue;
        }

        auto inspectorComposedElement = AceType::DynamicCast<V2::InspectorComposedElement>(composedElement);
        if (inspectorComposedElement) {
            inspectorComposedElement->TriggerVisibleAreaChangeCallback(visibleChangeNode.second);
        }
    }
}

void PipelineContext::RefreshStageFocus()
{
    CHECK_RUN_ON(UI);
    if (!rootElement_) {
        LOGE("Root element is null!");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return;
    }
    const auto& stageElement = GetStageElement();
    if (!stageElement) {
        LOGE("Get stage element failed!");
        return;
    }

    stageElement->RefreshFocus();
}

void PipelineContext::ShowContainerTitle(bool isShow, bool hasDeco, bool needUpdate)
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        LOGW("ShowContainerTitle failed, Window modal is not container.");
        return;
    }
    if (!rootElement_) {
        LOGW("ShowContainerTitle failed, rootElement_ is null.");
        return;
    }
    auto containerModal = AceType::DynamicCast<ContainerModalElement>(rootElement_->GetFirstChild());
    if (containerModal) {
        containerModal->ShowTitle(isShow, hasDeco);
    }
}

void PipelineContext::SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize, bool hideClose)
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        LOGW("Window modal is not container.");
        return;
    }
    if (!rootElement_) {
        LOGE("rootElement_ is null.");
        return;
    }
    auto containerModal = AceType::DynamicCast<ContainerModalElement>(rootElement_->GetFirstChild());
    if (containerModal) {
        containerModal->SetTitleButtonHide(hideSplit, hideMaximize, hideMinimize, hideClose);
    }
}

RefPtr<StageElement> PipelineContext::GetStageElement() const
{
    CHECK_RUN_ON(UI);
    if (!rootElement_) {
        LOGE("Root element is null!");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return {};
    }

    if (windowModal_ == WindowModal::SEMI_MODAL || windowModal_ == WindowModal::SEMI_MODAL_FULL_SCREEN) {
        auto semiElement = AceType::DynamicCast<SemiModalElement>(rootElement_->GetFirstChild());
        if (semiElement) {
            return semiElement->GetStageElement();
        }
    } else if (windowModal_ == WindowModal::DIALOG_MODAL) {
        auto dialogElement = AceType::DynamicCast<DialogModalElement>(rootElement_->GetFirstChild());
        if (dialogElement) {
            return dialogElement->GetStageElement();
        }
    } else if (windowModal_ == WindowModal::CONTAINER_MODAL) {
        auto containerElement = AceType::DynamicCast<ContainerModalElement>(rootElement_->GetFirstChild());
        if (containerElement) {
            return containerElement->GetStageElement();
        }
    } else {
        auto stack = rootElement_->GetFirstChild();
        if (stack) {
            return AceType::DynamicCast<StageElement>(stack->GetFirstChild());
        }
    }
    LOGE("Get stage element failed.");
    EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
    return {};
}

Rect PipelineContext::GetRootRect() const
{
    return Rect(0.0, 0.0, rootWidth_, rootHeight_);
}

Rect PipelineContext::GetStageRect() const
{
    return GetGlobalRect(GetStageElement());
}

Rect PipelineContext::GetPageRect() const
{
    return GetGlobalRect(GetLastStack());
}

bool PipelineContext::IsLastPage()
{
    const auto& stageElement = GetStageElement();
    if (!stageElement) {
        LOGE("Get stage element failed!");
        return true;
    }

    if (stageElement->GetChildrenList().size() <= 1) {
        return true;
    }

    return false;
}

RefPtr<ComposedElement> PipelineContext::GetComposedElementById(const ComposeId& id)
{
    CHECK_RUN_ON(UI);
    const auto& it = composedElementMap_.find(id);
    if (it != composedElementMap_.end() && !it->second.empty()) {
        return it->second.front();
    }
    return RefPtr<ComposedElement>();
}

void PipelineContext::CreateGeometryTransition()
{
    const auto& pageElement = GetLastPage();
    if (pageElement) {
        const auto& geometryTransitionMap = pageElement->GetGeometryTransition();
        std::vector<std::string> ids;
        for (const auto& [id, transformerInfo] : geometryTransitionMap) {
            ids.push_back(id);
        }
        for (const auto& id : ids) {
            const auto& transformerInfo = geometryTransitionMap.at(id);
            RefPtr<BoxElement> appearElement = transformerInfo.appearElement.Upgrade();
            RefPtr<BoxElement> disappearElement = transformerInfo.disappearElement.Upgrade();
            if (!appearElement) {
                pageElement->RemoveGeometryTransition(id);
                continue;
            }
            if (!disappearElement || !transformerInfo.isNeedCreate) {
                continue;
            }
            RefPtr<RenderNode> appearNode = appearElement->GetRenderNode();
            RefPtr<RenderNode> disappearNode = disappearElement->GetRenderNode();
            AnimationOption sharedOption = transformerInfo.sharedAnimationOption;
            if (!appearNode || !disappearNode) {
                continue;
            }
            appearNode->CreateGeometryTransitionFrom(disappearNode, sharedOption);
            disappearNode->CreateGeometryTransitionTo(appearNode, sharedOption);
            pageElement->FinishCreateGeometryTransition(id);
        }
    }
}

void PipelineContext::FlushLayout()
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACK();
    ACE_FUNCTION_TRACE();

    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().BeginFlushLayout();
    }

    if (dirtyLayoutNodes_.empty()) {
        FlushGeometryProperties();
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().EndFlushLayout();
        }
        return;
    }
    decltype(dirtyLayoutNodes_) dirtyNodes(std::move(dirtyLayoutNodes_));
    for (const auto& dirtyNode : dirtyNodes) {
        SaveExplicitAnimationOption(dirtyNode->GetExplicitAnimationOption());
        dirtyNode->OnLayout();
        ClearExplicitAnimationOption();
    }
    decltype(layoutTransitionNodeSet_) transitionNodes(std::move(layoutTransitionNodeSet_));
    for (const auto& transitionNode : transitionNodes) {
        transitionNode->CreateLayoutTransition();
    }
    for (const auto& dirtyNode : dirtyNodes) {
        dirtyNode->ClearExplicitAnimationOption();
    }
    alignDeclarationNodeList_.clear();

    CreateGeometryTransition();
    FlushGeometryProperties();
    TryCallNextFrameLayoutCallback();
    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().EndFlushLayout();
    }
}

void PipelineContext::FlushGeometryProperties()
{
    if (geometryChangedNodes_.empty()) {
        return;
    }

    decltype(dirtyLayoutNodes_) geometryChangedNodes(std::move(geometryChangedNodes_));
    for (const auto& dirtyNode : geometryChangedNodes) {
        dirtyNode->SyncGeometryProperties();
    }
}

void PipelineContext::CorrectPosition()
{
    const auto& pageElement = GetLastPage();
    if (pageElement) {
        const auto& geometryTransitionMap = pageElement->GetGeometryTransition();
        for (const auto& [id, transformerInfo] : geometryTransitionMap) {
            RefPtr<BoxElement> appearElement = transformerInfo.appearElement.Upgrade();
            RefPtr<BoxElement> disappearElement = transformerInfo.disappearElement.Upgrade();
            if (!appearElement || !disappearElement) {
                continue;
            }
            RefPtr<RenderNode> appearNode = appearElement->GetRenderNode();
            RefPtr<RenderNode> disappearNode = disappearElement->GetRenderNode();
            if (!appearNode || !disappearNode) {
                continue;
            }
            appearNode->UpdatePosition();
            disappearNode->UpdatePosition();
        }
    }
}

void PipelineContext::FlushRender()
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACK();
    ACE_FUNCTION_TRACE();

    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().BeginFlushRender();
    }

    if (dirtyRenderNodes_.empty() && dirtyRenderNodesInOverlay_.empty() && !needForcedRefresh_) {
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().EndFlushRender();
        }
        return;
    }

    CorrectPosition();

    Rect curDirtyRect;
    bool isDirtyRootRect = false;
    if (needForcedRefresh_) {
        curDirtyRect.SetRect(0.0, 0.0, rootWidth_, rootHeight_);
        isDirtyRootRect = true;
    }

    UpdateNodesNeedDrawOnPixelMap();

    auto context = RenderContext::Create();
    if (transparentHole_.IsValid()) {
        context->SetClipHole(transparentHole_);
    }
    if (!dirtyRenderNodes_.empty()) {
        decltype(dirtyRenderNodes_) dirtyNodes(std::move(dirtyRenderNodes_));
        for (const auto& dirtyNode : dirtyNodes) {
            context->Repaint(dirtyNode);
            if (!isDirtyRootRect) {
                Rect curRect = dirtyNode->GetDirtyRect();
                if (curRect == GetRootRect()) {
                    curDirtyRect = curRect;
                    isDirtyRootRect = true;
                    continue;
                }
                curDirtyRect = curDirtyRect.IsValid() ? curDirtyRect.CombineRect(curRect) : curRect;
            }
        }
    }
    if (!dirtyRenderNodesInOverlay_.empty()) {
        decltype(dirtyRenderNodesInOverlay_) dirtyNodesInOverlay(std::move(dirtyRenderNodesInOverlay_));
        for (const auto& dirtyNodeInOverlay : dirtyNodesInOverlay) {
            context->Repaint(dirtyNodeInOverlay);
            if (!isDirtyRootRect) {
                Rect curRect = dirtyNodeInOverlay->GetDirtyRect();
                if (curRect == GetRootRect()) {
                    curDirtyRect = curRect;
                    isDirtyRootRect = true;
                    continue;
                }
                curDirtyRect = curDirtyRect.IsValid() ? curDirtyRect.CombineRect(curRect) : curRect;
            }
        }
    }

    NotifyDrawOnPixelMap();

    if (rootElement_) {
        auto renderRoot = rootElement_->GetRenderNode();
        curDirtyRect = curDirtyRect * viewScale_;
        renderRoot->FinishRender(drawDelegate_, dirtyRect_.CombineRect(curDirtyRect));
        dirtyRect_ = curDirtyRect;
        if (isFirstLoaded_) {
            isFirstLoaded_ = false;
        }
    }
    needForcedRefresh_ = false;

    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().EndFlushRender();
    }
}

void PipelineContext::FlushRenderFinish()
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACK();
    ACE_FUNCTION_TRACE();

    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().BeginFlushRenderFinish();
    }
    if (!needPaintFinishNodes_.empty()) {
        decltype(needPaintFinishNodes_) Nodes(std::move(needPaintFinishNodes_));
        for (const auto& node : Nodes) {
            node->OnPaintFinish();
        }
    }
    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().EndFlushRenderFinish();
    }
}

void PipelineContext::DispatchDisplaySync(uint64_t nanoTimestamp) {}

void PipelineContext::FlushAnimation(uint64_t nanoTimestamp)
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACK();
    ACE_FUNCTION_TRACE();

    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().BeginFlushAnimation();
    }
    flushAnimationTimestamp_ = nanoTimestamp;
    isFlushingAnimation_ = true;

    ProcessPreFlush();
    if (scheduleTasks_.empty()) {
        isFlushingAnimation_ = false;
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().EndFlushAnimation();
        }
        return;
    }
    decltype(scheduleTasks_) temp(std::move(scheduleTasks_));
    for (const auto& scheduleTask : temp) {
        scheduleTask.second->OnFrame(nanoTimestamp);
    }
    isFlushingAnimation_ = false;

    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().EndFlushAnimation();
    }
}

void PipelineContext::FlushReloadTransition()
{
    AnimationOption option;
    option.SetDuration(FLUSH_RELOAD_TRANSITION_DURATION_MS);
    option.SetCurve(Curves::FRICTION);
    Animate(option, Curves::FRICTION, [this]() {
        FlushBuild();
        FlushPostAnimation();
        FlushLayout();
    });
}

void PipelineContext::FlushReload(const ConfigurationChange& configurationChange, bool fullUpdate)
{
    if (!rootElement_) {
        LOGE("PipelineContext::FlushReload rootElement is nullptr");
        return;
    }
    auto containerElement = AceType::DynamicCast<ContainerModalElement>(rootElement_->GetFirstChild());
    if (containerElement) {
        containerElement->FlushReload();
    }
}

void PipelineContext::FlushPostAnimation()
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACK();
    ACE_FUNCTION_TRACE();

    if (postAnimationFlushListeners_.empty()) {
        return;
    }
    decltype(postAnimationFlushListeners_) listeners(std::move(postAnimationFlushListeners_));
    for (const auto& listener : listeners) {
        listener->OnPostAnimationFlush();
    }
}

void PipelineContext::FlushPageUpdateTasks()
{
    CHECK_RUN_ON(UI);
    while (!pageUpdateTasks_.empty()) {
        const auto& task = pageUpdateTasks_.front();
        if (task) {
            task();
        }
        pageUpdateTasks_.pop();
    }
}

void PipelineContext::FlushAnimationTasks()
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACK();
    if (animationCallback_) {
        taskExecutor_->PostTask(animationCallback_, TaskExecutor::TaskType::JS, "ArkUIFlushAnimationTask",
            TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
    }
}

void PipelineContext::ProcessPreFlush()
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACE();

    // if we need clip hole
    if (transparentHole_.IsValid()) {
        hasMeetSubWindowNode_ = false;
        hasClipHole_ = false;
        isHoleValid_ = true;
        needForcedRefresh_ = true;
    } else {
        hasMeetSubWindowNode_ = false;
        hasClipHole_ = false;
        isHoleValid_ = false;
    }
    if (preFlushListeners_.empty()) {
        return;
    }
    decltype(preFlushListeners_) temp(std::move(preFlushListeners_));
    for (const auto& listener : temp) {
        listener->OnPreFlush();
    }
}

void PipelineContext::ProcessPostFlush()
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACK();
    ACE_FUNCTION_TRACE();

    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().BeginProcessPostFlush();
    }

    if (postFlushListeners_.empty()) {
        return;
    }
    decltype(postFlushListeners_) temp(std::move(postFlushListeners_));
    for (const auto& listener : temp) {
        listener->OnPostFlush();
    }
}

void PipelineContext::SetClipHole(double left, double top, double width, double height)
{
    if (!rootElement_) {
        return;
    }

    transparentHole_.SetLeft(left);
    transparentHole_.SetTop(top);
    transparentHole_.SetWidth(width);
    transparentHole_.SetHeight(height);
}

void PipelineContext::SetupRootElement()
{
    CHECK_RUN_ON(UI);
    RefPtr<StageComponent> rootStage = AceType::MakeRefPtr<StageComponent>(std::list<RefPtr<Component>>());
    if (isRightToLeft_) {
        rootStage->SetTextDirection(TextDirection::RTL);
    }
    if (GetIsDeclarative()) {
        rootStage->SetMainStackSize(MainStackSize::MAX);
    } else {
        rootStage->SetMainStackSize(MainStackSize::LAST_CHILD_HEIGHT);
    }

    auto stack = AceType::MakeRefPtr<StackComponent>(
        Alignment::TOP_LEFT, StackFit::INHERIT, Overflow::OBSERVABLE, std::list<RefPtr<Component>>());
    auto overlay = AceType::MakeRefPtr<OverlayComponent>(std::list<RefPtr<Component>>());
    overlay->SetTouchable(false);
    Component::MergeRSNode(overlay);
    stack->AppendChild(rootStage);
    stack->AppendChild(overlay);
    RefPtr<RootComponent> rootComponent;
    if (windowModal_ == WindowModal::SEMI_MODAL || windowModal_ == WindowModal::SEMI_MODAL_FULL_SCREEN) {
        if (modalColor_ == DEFAULT_MODAL_COLOR) {
            auto semiModalTheme = themeManager_->GetTheme<SemiModalTheme>();
            if (semiModalTheme) {
                SetModalColor(semiModalTheme->GetBgColor().GetValue());
            }
        }
        auto semiModal = SemiModalComponent::Create(
            stack, windowModal_ == WindowModal::SEMI_MODAL_FULL_SCREEN, modalHeight_, modalColor_);
        rootComponent = RootComponent::Create(semiModal);
    } else if (windowModal_ == WindowModal::DIALOG_MODAL) {
        rootStage->SetMainStackSize(MainStackSize::MAX);
        rootStage->SetAlignment(Alignment::BOTTOM_LEFT);
        auto dialogModal = DialogModalComponent::Create(stack);
        rootComponent = RootComponent::Create(dialogModal);
    } else if (windowModal_ == WindowModal::CONTAINER_MODAL) {
        auto containerModal = ContainerModalComponent::Create(AceType::WeakClaim(this), stack);
        rootComponent = RootComponent::Create(containerModal);
    } else {
        rootComponent = RootComponent::Create(stack);
    }
    rootElement_ = rootComponent->SetupElementTree(AceType::Claim(this));
    if (!rootElement_) {
        LOGE("SetupRootElement failed!");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return;
    }
    const auto& rootRenderNode = rootElement_->GetRenderNode();
    window_->SetRootRenderNode(rootRenderNode);
    auto renderRoot = AceType::DynamicCast<RenderRoot>(rootRenderNode);
    if (!renderRoot) {
        LOGE("render root is null.");
        return;
    }
    if (appBgColor_ != Color::WHITE) {
        SetAppBgColor(appBgColor_);
    } else {
        renderRoot->SetDefaultBgColor(windowModal_ == WindowModal::CONTAINER_MODAL);
    }
#ifdef ENABLE_ROSEN_BACKEND
    if (SystemProperties::GetRosenBackendEnabled() && rsUIDirector_ && renderRoot) {
        rsUIDirector_->SetRoot(rootRenderNode->GetRSNode()->GetId());
        if (windowModal_ == WindowModal::CONTAINER_MODAL) {
            rsUIDirector_->SetAbilityBGAlpha(appBgColor_.GetAlpha());
        } else {
            rsUIDirector_->SetAbilityBGAlpha(renderRoot->GetBgColor().GetAlpha());
        }
    }
#endif
    sharedTransitionController_->RegisterTransitionListener();
    cardTransitionController_->RegisterTransitionListener();
    if (windowModal_ == WindowModal::DIALOG_MODAL) {
        auto dialog = AceType::DynamicCast<DialogModalElement>(rootElement_->GetFirstChild());
        if (dialog) {
            dialog->RegisterTransitionListener();
        }
    }

    requestedRenderNode_.Reset();
}

RefPtr<Element> PipelineContext::SetupSubRootElement()
{
    LOGI("Set up SubRootElement!");

    RefPtr<StageComponent> rootStage = AceType::MakeRefPtr<StageComponent>(std::list<RefPtr<Component>>());
    if (isRightToLeft_) {
        rootStage->SetTextDirection(TextDirection::RTL);
    }
    if (GetIsDeclarative()) {
        rootStage->SetMainStackSize(MainStackSize::MAX);
    } else {
        rootStage->SetMainStackSize(MainStackSize::LAST_CHILD_HEIGHT);
    }
    auto stack = AceType::MakeRefPtr<StackComponent>(
        Alignment::TOP_LEFT, StackFit::KEEP, Overflow::OBSERVABLE, std::list<RefPtr<Component>>());

    auto overlay = AceType::MakeRefPtr<OverlayComponent>(std::list<RefPtr<Component>>());
    overlay->SetTouchable(false);
    stack->AppendChild(rootStage);
    stack->AppendChild(overlay);
    RefPtr<RootComponent> rootComponent;
    rootComponent = RootComponent::Create(stack);
    rootComponent->MarkContextMenu();
    rootElement_ = rootComponent->SetupElementTree(AceType::Claim(this));
    if (!rootElement_) {
        LOGE("Set up SubRootElement failed!");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return RefPtr<Element>();
    }
    const auto& rootRenderNode = rootElement_->GetRenderNode();
    window_->SetRootRenderNode(rootRenderNode);
#ifdef ENABLE_ROSEN_BACKEND
    if (SystemProperties::GetRosenBackendEnabled() && rsUIDirector_) {
        rsUIDirector_->SetRoot(rootRenderNode->GetRSNode()->GetId());
        auto renderRoot = AceType::DynamicCast<RenderRoot>(rootRenderNode);
        if (renderRoot) {
            rsUIDirector_->SetAbilityBGAlpha(renderRoot->GetBgColor().GetAlpha());
        }
    }
#endif
    sharedTransitionController_->RegisterTransitionListener();
    cardTransitionController_->RegisterTransitionListener();
    requestedRenderNode_.Reset();
    LOGI("Set up SubRootElement success!");
    return rootElement_;
}

bool PipelineContext::OnDumpInfo(const std::vector<std::string>& params) const
{
    ACE_DCHECK(!params.empty());

    if (params[0] == "-element") {
        if (params.size() > 1 && params[1] == "-lastpage") {
            GetLastPage()->DumpTree(0);
        } else {
            rootElement_->DumpTree(0);
        }
    } else if (params[0] == "-render") {
        if (params.size() > 1 && params[1] == "-lastpage") {
            GetLastPage()->GetRenderNode()->DumpTree(0);
        } else {
            rootElement_->GetRenderNode()->DumpTree(0);
        }
    } else if (params[0] == "-focus") {
        rootElement_->GetFocusScope()->DumpFocusTree(0);
    } else if (params[0] == "-layer") {
        auto rootNode = AceType::DynamicCast<RenderRoot>(rootElement_->GetRenderNode());
        rootNode->DumpLayerTree();
#ifndef WEARABLE_PRODUCT
    } else if (params[0] == "-multimodal") {
        multiModalManager_->DumpMultimodalScene();
#endif
    } else if (params[0] == "-accessibility" || params[0] == "-inspector") {
        DumpAccessibility(params);
    } else if (params[0] == "-rotation" && params.size() >= 2) {
        DumpLog::GetInstance().Print("Dump rotation");
        RotationEvent event { static_cast<double>(StringUtils::StringToInt(params[1])) };
        OnRotationEvent(event);
    } else if (params[0] == "-animationscale" && params.size() >= 2) {
        DumpLog::GetInstance().Print(std::string("Set Animation Scale. scale: ") + params[1]);
        Animator::SetDurationScale(StringUtils::StringToDouble(params[1]));
    } else if (params[0] == "-velocityscale" && params.size() >= 2) {
        DumpLog::GetInstance().Print(std::string("Set Velocity Scale. scale: ") + params[1]);
        Scrollable::SetVelocityScale(StringUtils::StringToDouble(params[1]));
    } else if (params[0] == "-scrollfriction" && params.size() >= 2) {
        DumpLog::GetInstance().Print(std::string("Set Scroll Friction. friction: ") + params[1]);
        Scrollable::SetFriction(StringUtils::StringToDouble(params[1]));
    } else if (params[0] == "-threadstuck" && params.size() >= 3) {
        MakeThreadStuck(params);
    } else {
        DumpLog::GetInstance().Print("Error: Unsupported dump params!");
        return false;
    }
    return true;
}

RefPtr<StackElement> PipelineContext::GetLastStack() const
{
    if (!rootElement_) {
        LOGE("Rootelement is null");
        return RefPtr<StackElement>();
    }
    if (isSubPipeline_) {
        const auto& stack = AceType::DynamicCast<StackElement>(rootElement_->GetFirstChild());
        if (!stack) {
            LOGE("Get stack failed, it is null");
            return RefPtr<StackElement>();
        }
        return stack;
    }
    const auto& pageElement = GetLastPage();
    if (!pageElement) {
        return RefPtr<StackElement>();
    }
    const auto& transitionElement = AceType::DynamicCast<PageTransitionElement>(pageElement->GetFirstChild());
    if (!transitionElement) {
        return RefPtr<StackElement>();
    }
    const auto& focusCollaboration =
        AceType::DynamicCast<FocusCollaborationElement>(transitionElement->GetContentElement());
    if (!focusCollaboration) {
        return RefPtr<StackElement>();
    }
    const auto& composedStack = AceType::DynamicCast<ComposedElement>(focusCollaboration->GetFirstChild());
    if (!composedStack) {
        return RefPtr<StackElement>();
    }
    const auto& stackElement = AceType::DynamicCast<StackElement>(composedStack->GetLastChild());
    if (!stackElement) {
        return RefPtr<StackElement>();
    }
    return stackElement;
}

RefPtr<PageElement> PipelineContext::GetLastPage() const
{
    const auto& stageElement = GetStageElement();
    if (!stageElement) {
        LOGE("Get last page failed, stage element is null.");
        return nullptr;
    }
    return AceType::DynamicCast<PageElement>(stageElement->GetLastChild());
}

RefPtr<RenderNode> PipelineContext::GetLastPageRender() const
{
    auto lastPage = GetLastPage();
    if (!lastPage) {
        return nullptr;
    }
    return lastPage->GetRenderNode();
}

bool PipelineContext::CanPushPage()
{
    auto stageElement = GetStageElement();
    return stageElement && stageElement->CanPushPage();
}

bool PipelineContext::IsTransitionStop() const
{
    auto stageElement = GetStageElement();
    return stageElement && stageElement->IsTransitionStop();
}

void PipelineContext::PushPage(const RefPtr<PageComponent>& pageComponent, const RefPtr<StageElement>& stage)
{
    ACE_FUNCTION_TRACE();
    CHECK_RUN_ON(UI);
    std::unordered_map<std::string, std::string> params { { "pageUrl", pageComponent->GetPageUrl() } };
    ResSchedReportScope report("push_page", params);
    auto stageElement = stage;
    if (!stageElement) {
        // if not target stage, use root stage
        stageElement = GetStageElement();
        if (!stageElement) {
            LOGE("Get stage element failed!");
            return;
        }
    }
    buildingFirstPage_ = isFirstPage_;
    isFirstPage_ = false;
    if (PageTransitionComponent::HasTransitionComponent(AceType::DynamicCast<Component>(pageComponent))) {
        stageElement->PushPage(pageComponent);
    } else {
        RefPtr<DisplayComponent> display = AceType::MakeRefPtr<DisplayComponent>(pageComponent);
        stageElement->PushPage(display);
    }

#if defined(ENABLE_ROSEN_BACKEND)
    if (GetIsDeclarative()) {
        FlushBuild();
        return;
    }
#endif
#if defined(ENABLE_NATIVE_VIEW)
    if (GetIsDeclarative()) {
        // if not use flutter scheduler, can flush pipeline immediately.
        if (isSurfaceReady_) {
            FlushPipelineImmediately();
        } else {
            FlushBuild();
        }
        return;
    }
#endif
    FlushBuildAndLayoutBeforeSurfaceReady();
}

void PipelineContext::PushPage(const RefPtr<PageComponent>& pageComponent)
{
    PushPage(pageComponent, nullptr);
}

void PipelineContext::PostponePageTransition()
{
    CHECK_RUN_ON(UI);
    // if not target stage, use root stage
    auto stageElement = GetStageElement();
    if (!stageElement) {
        LOGE("Get stage element failed!");
        return;
    }
    stageElement->PostponePageTransition();
}

void PipelineContext::LaunchPageTransition()
{
    CHECK_RUN_ON(UI);
    // if not target stage, use root stage
    auto stageElement = GetStageElement();
    if (!stageElement) {
        LOGE("Get stage element failed!");
        return;
    }
    stageElement->LaunchPageTransition();
}

void PipelineContext::GetBoundingRectData(int32_t nodeId, Rect& rect)
{
    auto composeElement = GetComposedElementById(std::to_string(nodeId));
    if (composeElement) {
        Rect resultRect = composeElement->GetRenderRect();
        rect.SetWidth(resultRect.Width());
        rect.SetHeight(resultRect.Height());
        rect.SetTop(resultRect.Top());
        rect.SetLeft(resultRect.Left());
    }
}

RefPtr<DialogComponent> PipelineContext::ShowDialog(
    const DialogProperties& dialogProperties, bool isRightToLeft, const std::string& inspectorTag)
{
    CHECK_RUN_ON(UI);
    const auto& dialog = DialogBuilder::Build(dialogProperties, AceType::WeakClaim(this));
    if (!dialog) {
        return nullptr;
    }
    dialog->SetInspectorTag(inspectorTag);
    auto customComponent = AceType::DynamicCast<Component>(dialogProperties.customComponent);
    if (customComponent) {
        dialog->SetCustomChild(customComponent);
    }
    dialog->SetTextDirection(isRightToLeft ? TextDirection::RTL : TextDirection::LTR);
    const auto& lastStack = GetLastStack();
    if (!lastStack) {
        return nullptr;
    }
    LOGI("PipelineContext::ShowDialog id is %{public}d", dialog->GetDialogId());
    lastStack->PushDialog(dialog);
    return dialog;
}

void PipelineContext::CloseContextMenu()
{
    auto menu = AceType::DynamicCast<SelectPopupComponent>(contextMenu_);
    if (menu) {
        menu->HideDialog(SELECT_INVALID_INDEX);
    }
}

bool PipelineContext::CanPopPage()
{
    auto stageElement = GetStageElement();
    return stageElement && stageElement->CanPopPage();
}

void PipelineContext::PopPage()
{
    CHECK_RUN_ON(UI);
    auto stageElement = GetStageElement();
    if (stageElement) {
        auto topElement = stageElement->GetTopPage();
        if (topElement != nullptr) {
            std::unordered_map<std::string, std::string> params { { "pageUrl", topElement->GetPageUrl() } };
            ResSchedReport::GetInstance().ResSchedDataReport("pop_page", params);
        }
        stageElement->Pop();
    }
    ExitAnimation();
}

void PipelineContext::PopToPage(int32_t pageId)
{
    CHECK_RUN_ON(UI);
    auto stageElement = GetStageElement();
    if (stageElement) {
        stageElement->PopToPage(pageId);
    }
}

void PipelineContext::RestorePopPage(const RefPtr<PageComponent>& pageComponent)
{
    CHECK_RUN_ON(UI);
    auto stageElement = GetStageElement();
    if (stageElement) {
        stageElement->RestorePopPage(pageComponent);
    }
}

bool PipelineContext::CanReplacePage()
{
    auto stageElement = GetStageElement();
    return stageElement && stageElement->CanReplacePage();
}

BaseId::IdType PipelineContext::AddPageTransitionListener(const PageTransitionListenable::CallbackFuncType& funcObject)
{
    if (!rootElement_) {
        LOGE("add page transition listener failed. root element is null.");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return 0;
    }
    auto stageElement = GetStageElement();
    if (!stageElement) {
        LOGE("add page transition listener failed. stage is null.");
        return 0;
    }
    return stageElement->AddPageTransitionListener(funcObject);
}

void PipelineContext::RemovePageTransitionListener(typename BaseId::IdType id)
{
    auto stageElement = GetStageElement();
    if (stageElement) {
        stageElement->RemovePageTransitionListener(id);
    }
}

void PipelineContext::ClearPageTransitionListeners()
{
    auto stageElement = GetStageElement();
    if (stageElement) {
        return stageElement->ClearPageTransitionListeners();
    }
}

void PipelineContext::ReplacePage(const RefPtr<PageComponent>& pageComponent, const RefPtr<StageElement>& stage,
    const std::function<void()>& listener)
{
    CHECK_RUN_ON(UI);
    auto stageElement = stage;
    if (!stage) {
        stageElement = GetStageElement();
        if (!stageElement) {
            LOGE("Get stage element failed!");
            return;
        }
    }
    if (PageTransitionComponent::HasTransitionComponent(AceType::DynamicCast<Component>(pageComponent))) {
        stageElement->Replace(pageComponent, listener);
    } else {
        RefPtr<DisplayComponent> display = AceType::MakeRefPtr<DisplayComponent>(pageComponent);
        stageElement->Replace(display, listener);
    }
}

void PipelineContext::ReplacePage(const RefPtr<PageComponent>& pageComponent)
{
    ReplacePage(pageComponent, nullptr);
}

bool PipelineContext::ClearInvisiblePages(const std::function<void()>& listener)
{
    auto stageElement = GetStageElement();
    return stageElement && stageElement->ClearOffStage(listener);
}

void PipelineContext::ExitAnimation()
{
    CHECK_RUN_ON(UI);
    if (IsLastPage()) {
        // semi modal use translucent theme and will do exit animation by ACE itself.
        if (windowModal_ == WindowModal::SEMI_MODAL || windowModal_ == WindowModal::SEMI_MODAL_FULL_SCREEN ||
            windowModal_ == WindowModal::DIALOG_MODAL) {
            taskExecutor_->PostTask(
                [weak = AceType::WeakClaim(this)]() {
                    auto context = weak.Upgrade();
                    if (!context) {
                        return;
                    }
                    context->Finish();
                },
                TaskExecutor::TaskType::UI, "ArkUIExitAnimation",
                TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
        } else {
            // return back to desktop
            Finish();
        }
    }
}

// return true if user accept or page is not last, return false if others condition
bool PipelineContext::CallRouterBackToPopPage()
{
    CHECK_RUN_ON(PLATFORM);
    auto frontend = weakFrontend_.Upgrade();
    if (!frontend) {
        // return back to desktop
        return false;
    }

    if (frontend->OnBackPressed()) {
        // if user accept
        LOGI("CallRouterBackToPopPage(): user consume the back key event");
        return true;
    }
    auto stageElement = GetStageElement();
    // declarative frontend need use GetRouterSize to judge, others use GetChildrenList
    if (frontend->GetRouterSize() <= 1 && stageElement && stageElement->GetChildrenList().size() <= 1) {
        LOGI("CallRouterBackToPopPage(): current page is the last page");
        return false;
    }
    frontend->CallRouterBack();
    LOGI("CallRouterBackToPopPage(): current page is not the last");
    return true;
}

bool PipelineContext::PopPageStackOverlay()
{
    auto pageStack = GetLastStack();
    if (!pageStack) {
        LOGW("No page stack in page.");
        return false;
    }
    if (!pageStack->HasOverlayChild()) {
        LOGI("No overlay in page, try to pop page.");
        return false;
    }
    LOGI("Pop page overlays");
    // If last child is popup, use PopPopup to trigger state change event.
    if (pageStack->PopPopupIfExist()) {
        return true;
    }

    if (pageStack->PopDialogIfExist()) {
        return true;
    }

    pageStack->PopComponent();
    return true;
}

void PipelineContext::HideOverlays()
{
    CloseContextMenu();
    if (textOverlayManager_) {
        textOverlayManager_->PopTextOverlay();
    }
}

void PipelineContext::ScheduleUpdate(const RefPtr<ComposedComponent>& compose)
{
    CHECK_RUN_ON(UI);
    ComposeId id = compose->GetId();
    const auto& it = composedElementMap_.find(id);
    if (it != composedElementMap_.end()) {
        for (const auto& composedElement : it->second) {
            composedElement->SetUpdateComponent(compose);
        }
    }
    FlushBuildAndLayoutBeforeSurfaceReady();
}

void PipelineContext::AddComposedElement(const ComposeId& id, const RefPtr<ComposedElement>& element)
{
    CHECK_RUN_ON(UI);
    auto it = composedElementMap_.find(id);
    if (it != composedElementMap_.end()) {
        it->second.emplace_back(element);
    } else {
        std::list<RefPtr<ComposedElement>> elements;
        elements.emplace_back(element);
        composedElementMap_[id] = std::move(elements);
    }
}

void PipelineContext::RemoveComposedElement(const ComposeId& id, const RefPtr<ComposedElement>& element)
{
    CHECK_RUN_ON(UI);
    auto it = composedElementMap_.find(id);
    if (it != composedElementMap_.end()) {
        it->second.remove(element);
        if (it->second.empty()) {
            composedElementMap_.erase(it);
        }
    }
}

void PipelineContext::AddDirtyElement(const RefPtr<Element>& dirtyElement)
{
    CHECK_RUN_ON(UI);
    if (!dirtyElement) {
        LOGW("dirtyElement is null");
        return;
    }
    dirtyElements_.emplace(dirtyElement);
    hasIdleTasks_ = true;
    window_->RequestFrame();
}

void PipelineContext::AddNeedRebuildFocusElement(const RefPtr<Element>& focusElement)
{
    CHECK_RUN_ON(UI);
    if (!focusElement) {
        LOGW("focusElement is null");
        return;
    }
    needRebuildFocusElement_.emplace(focusElement);
}

void PipelineContext::AddDirtyRenderNode(const RefPtr<RenderNode>& renderNode, bool overlay)
{
    CHECK_RUN_ON(UI);
    if (!renderNode) {
        LOGW("renderNode is null");
        return;
    }
    if (!overlay) {
        dirtyRenderNodes_.emplace(renderNode);
    } else {
        dirtyRenderNodesInOverlay_.emplace(renderNode);
    }
    hasIdleTasks_ = true;
    window_->RequestFrame();
}

void PipelineContext::AddNeedRenderFinishNode(const RefPtr<RenderNode>& renderNode)
{
    CHECK_RUN_ON(UI);
    if (!renderNode) {
        LOGW("renderNode is null");
        return;
    }
    needPaintFinishNodes_.emplace(renderNode);
}

void PipelineContext::AddDirtyLayoutNode(const RefPtr<RenderNode>& renderNode)
{
    CHECK_RUN_ON(UI);
    if (!renderNode) {
        LOGW("renderNode is null");
        return;
    }
    renderNode->SaveExplicitAnimationOption(explicitAnimationOption_);
    dirtyLayoutNodes_.emplace(renderNode);
    ForceLayoutForImplicitAnimation();
    hasIdleTasks_ = true;
    window_->RequestFrame();
}

void PipelineContext::AddPredictLayoutNode(const RefPtr<RenderNode>& renderNode)
{
    CHECK_RUN_ON(UI);
    if (!renderNode) {
        LOGW("renderNode is null");
        return;
    }
    predictLayoutNodes_.emplace(renderNode);
    ForceLayoutForImplicitAnimation();
    hasIdleTasks_ = true;
    window_->RequestFrame();
}

void PipelineContext::AddGeometryChangedNode(const RefPtr<RenderNode>& renderNode)
{
    geometryChangedNodes_.emplace(renderNode);
}

void PipelineContext::AddPreFlushListener(const RefPtr<FlushEvent>& listener)
{
    CHECK_RUN_ON(UI);
    preFlushListeners_.emplace_back(listener);
    window_->RequestFrame();
}

void PipelineContext::AddPostAnimationFlushListener(const RefPtr<FlushEvent>& listener)
{
    CHECK_RUN_ON(UI);
    postAnimationFlushListeners_.emplace_back(listener);
}

void PipelineContext::AddPostFlushListener(const RefPtr<FlushEvent>& listener)
{
    CHECK_RUN_ON(UI);
    postFlushListeners_.emplace_back(listener);
    window_->RequestFrame();
}

uint32_t PipelineContext::AddScheduleTask(const RefPtr<ScheduleTask>& task)
{
    CHECK_RUN_ON(UI);
    scheduleTasks_.try_emplace(++nextScheduleTaskId_, task);
    window_->RequestFrame();
    return nextScheduleTaskId_;
}

void PipelineContext::SetRequestedRotationNode(const WeakPtr<RenderNode>& renderNode)
{
    auto node = renderNode.Upgrade();
    if (!node) {
        return;
    }
    requestedRenderNode_ = renderNode;
}

void PipelineContext::RemoveRequestedRotationNode(const WeakPtr<RenderNode>& renderNode)
{
    if (requestedRenderNode_ == renderNode) {
        requestedRenderNode_.Reset();
    }
}

void PipelineContext::RemoveScheduleTask(uint32_t id)
{
    CHECK_RUN_ON(UI);
    scheduleTasks_.erase(id);
}

RefPtr<RenderNode> PipelineContext::DragTestAll(const TouchEvent& point)
{
    return DragTest(point, rootElement_->GetRenderNode(), 0);
}

RefPtr<RenderNode> PipelineContext::DragTest(
    const TouchEvent& point, const RefPtr<RenderNode>& renderNode, int32_t deep)
{
    if (AceType::InstanceOf<RenderBox>(renderNode) && renderNode->onDomDragEnter_ && renderNode->IsPointInBox(point)) {
        return renderNode;
    }

    std::list<RefPtr<RenderNode>> renderNodeLst = renderNode->GetChildren();
    for (auto it = renderNodeLst.begin(); it != renderNodeLst.end(); it++) {
        RefPtr<RenderNode> tmp = DragTest(point, *it, deep + 1);
        if (tmp != nullptr) {
            return tmp;
        }
    }
    return nullptr;
}

void PipelineContext::OnTouchEvent(const TouchEvent& point, bool isSubPipe, bool isEventsPassThrough)
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACE();
    if (!rootElement_) {
        LOGE("root element is nullptr");
        return;
    }
    auto scalePoint = point.CreateScalePoint(viewScale_);
    ResSchedReport::GetInstance().OnTouchEvent(scalePoint);
    if (scalePoint.type == TouchType::DOWN) {
        eventManager_->HandleOutOfRectCallback(
            { scalePoint.x, scalePoint.y, scalePoint.sourceType }, rectCallbackList_);
        eventManager_->HandleGlobalEvent(scalePoint, textOverlayManager_);
        TouchRestrict touchRestrict { TouchRestrict::NONE };
        touchRestrict.sourceType = point.sourceType;
        auto frontEnd = GetFrontend();
        if (frontEnd && (frontEnd->GetType() == FrontendType::JS_CARD)) {
            touchRestrict.UpdateForbiddenType(TouchRestrict::LONG_PRESS);
        }
        eventManager_->TouchTest(
            scalePoint, rootElement_->GetRenderNode(), touchRestrict, GetPluginEventOffset(), viewScale_, isSubPipe);

        for (size_t i = 0; i < touchPluginPipelineContext_.size(); i++) {
            auto pipelineContext = DynamicCast<PipelineContext>(touchPluginPipelineContext_[i].Upgrade());
            if (!pipelineContext || !pipelineContext->rootElement_) {
                continue;
            }
            auto pluginPoint = point.UpdateScalePoint(viewScale_, pipelineContext->GetPluginEventOffset().GetX(),
                pipelineContext->GetPluginEventOffset().GetY(), point.id);
            auto eventManager = pipelineContext->GetEventManager();
            if (eventManager) {
                eventManager->SetInstanceId(pipelineContext->GetInstanceId());
            }
            pipelineContext->OnTouchEvent(pluginPoint, true);
        }
    }
    isMoving_ = scalePoint.type == TouchType::MOVE ? true : isMoving_;
    if (isKeyEvent_) {
        SetIsKeyEvent(false);
    }
    if (isSubPipe) {
        return;
    }
    if (scalePoint.type == TouchType::MOVE) {
        touchEvents_.emplace_back(point);
        window_->RequestFrame();
        return;
    }

    std::optional<TouchEvent> lastMoveEvent;
    if (scalePoint.type == TouchType::UP && !touchEvents_.empty()) {
        for (auto iter = touchEvents_.begin(); iter != touchEvents_.end();) {
            auto movePoint = (*iter).CreateScalePoint(GetViewScale());
            if (scalePoint.id == movePoint.id) {
                lastMoveEvent = movePoint;
                iter = touchEvents_.erase(iter);
            } else {
                ++iter;
            }
        }
        if (lastMoveEvent.has_value()) {
            eventManager_->DispatchTouchEvent(lastMoveEvent.value());
        }
    }

    eventManager_->DispatchTouchEvent(scalePoint);
    if (scalePoint.type == TouchType::UP) {
        touchPluginPipelineContext_.clear();
        eventManager_->SetInstanceId(GetInstanceId());
    }
    window_->RequestFrame();
}

void PipelineContext::FlushTouchEvents()
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACE();
    if (!rootElement_) {
        LOGE("root element is nullptr");
        return;
    }
    {
        eventManager_->FlushTouchEventsBegin(touchEvents_);
        std::unordered_set<int32_t> moveEventIds;
        decltype(touchEvents_) touchEvents(std::move(touchEvents_));
        if (touchEvents.empty()) {
            return;
        }
        std::list<TouchEvent> touchPoints;
        for (auto iter = touchEvents.rbegin(); iter != touchEvents.rend(); ++iter) {
            auto scalePoint = (*iter).CreateScalePoint(GetViewScale());
            auto result = moveEventIds.emplace(scalePoint.id);
            if (result.second) {
                touchPoints.emplace_front(scalePoint);
            }
        }

        auto maxSize = touchPoints.size();
        for (auto iter = touchPoints.rbegin(); iter != touchPoints.rend(); ++iter) {
            maxSize--;
            if (maxSize == 0) {
                eventManager_->FlushTouchEventsEnd(touchPoints);
            }
            eventManager_->DispatchTouchEvent(*iter);
        }
    }
}

bool PipelineContext::OnKeyEvent(const NonPointerEvent& nonPointerEvent)
{
    CHECK_RUN_ON(UI);
    if (nonPointerEvent.eventType != UIInputEventType::KEY) {
        return false;
    }
    const auto& event = static_cast<const KeyEvent&>(nonPointerEvent);
    if (!rootElement_) {
        LOGE("the root element is nullptr");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return false;
    }
    rootElement_->HandleSpecifiedKey(event);
    SetShortcutKey(event);
    pressedKeyCodes = event.pressedCodes;
    isKeyCtrlPressed_ = !pressedKeyCodes.empty() && (pressedKeyCodes.back() == KeyCode::KEY_CTRL_LEFT ||
                                                        pressedKeyCodes.back() == KeyCode::KEY_CTRL_RIGHT);
    if ((event.code == KeyCode::KEY_CTRL_LEFT || event.code == KeyCode::KEY_CTRL_RIGHT) &&
        event.action == KeyAction::UP) {
        if (isOnScrollZoomEvent_) {
            zoomEventA_.type = TouchType::UP;
            zoomEventB_.type = TouchType::UP;
            LOGI("Send TouchEventA(%{public}f, %{public}f, %{public}zu)", zoomEventA_.x, zoomEventA_.y,
                zoomEventA_.type);
            OnTouchEvent(zoomEventA_);
            LOGI("Send TouchEventB(%{public}f, %{public}f, %{public}zu)", zoomEventB_.x, zoomEventB_.y,
                zoomEventB_.type);
            OnTouchEvent(zoomEventB_);
            isOnScrollZoomEvent_ = false;
        }
    }

    if (event.code == KeyCode::KEY_TAB && event.action == KeyAction::DOWN && !isTabKeyPressed_) {
        isTabKeyPressed_ = true;
    }
    CHECK_NULL_RETURN(rootElement_, false);
    auto lastPage = GetLastPage();
    bool isHandleByTabIndex = false;
    if (lastPage) {
        isHandleByTabIndex = rootElement_->HandleFocusByTabIndex(event, lastPage);
    } else {
        isHandleByTabIndex = rootElement_->HandleFocusByTabIndex(event, rootElement_);
    }
    if (isHandleByTabIndex) {
        TAG_LOGI(AceLogTag::ACE_INPUTTRACKING, "Tab index focus system handled this event");
        return true;
    }
    if (rootElement_->HandleKeyEvent(event)) {
        TAG_LOGI(AceLogTag::ACE_INPUTTRACKING, "Default focus system handled this event");
        return true;
    }
    return false;
}

bool PipelineContext::OnNonPointerEvent(const NonPointerEvent& nonPointerEvent)
{
    CHECK_RUN_ON(UI);
    if (nonPointerEvent.eventType == UIInputEventType::KEY) {
        return OnKeyEvent(nonPointerEvent);
    } else if (nonPointerEvent.eventType == UIInputEventType::CROWN) {
        const auto& crownEvent = static_cast<const CrownEvent&>(nonPointerEvent);
        RotationEvent rotationEvent;
        rotationEvent.value = crownEvent.degree * ROTATION_DIVISOR;
        return OnRotationEvent(rotationEvent);
    }
    return false;
}

bool PipelineContext::RequestDefaultFocus()
{
    RefPtr<FocusNode> defaultFocusNode;
    std::string mainNodeName;
    auto curPageElement = GetLastPage();
    if (curPageElement) {
        if (curPageElement->IsDefaultHasFocused()) {
            return false;
        }
        curPageElement->SetIsDefaultHasFocused(true);
        defaultFocusNode = curPageElement->GetChildDefaultFocusNode();
        mainNodeName = std::string(AceType::TypeName(curPageElement));
    } else if (rootElement_) {
        if (rootElement_->IsDefaultHasFocused()) {
            return false;
        }
        rootElement_->SetIsDefaultHasFocused(true);
        defaultFocusNode = rootElement_->GetChildDefaultFocusNode();
        mainNodeName = std::string(AceType::TypeName(rootElement_));
    } else {
        LOGE("RequestDefaultFocus: rootElement or pageElement is nullptr!");
        return false;
    }
    if (!defaultFocusNode) {
        return false;
    }
    if (!defaultFocusNode->IsFocusableWholePath()) {
        return false;
    }
    return defaultFocusNode->RequestFocusImmediately();
}

void PipelineContext::SetShortcutKey(const KeyEvent& event)
{
    if (event.action == KeyAction::DOWN) {
        auto codeValue = static_cast<int32_t>(event.code);
        if (codeValue == static_cast<int32_t>(KeyCode::KEY_SHIFT_LEFT) ||
            codeValue == static_cast<int32_t>(KeyCode::KEY_SHIFT_RIGHT)) {
            MarkIsShiftDown(true);
        } else if (codeValue == static_cast<int32_t>(KeyCode::KEY_CTRL_LEFT) ||
                   codeValue == static_cast<int32_t>(KeyCode::KEY_CTRL_RIGHT)) {
            MarkIsCtrlDown(true);
        } else if (codeValue == static_cast<int32_t>(KeyCode::KEY_A)) {
            MarkIsKeyboardA(true);
            if (subscribeCtrlA_) {
                subscribeCtrlA_();
            }
        } else if (codeValue == static_cast<int32_t>(KeyCode::KEY_C)) {
            if (textOverlayManager_) {
                textOverlayManager_->HandleCtrlC();
            }
        }
    } else if (event.action == KeyAction::UP) {
        auto codeValue = static_cast<int32_t>(event.code);
        if (codeValue == static_cast<int32_t>(KeyCode::KEY_SHIFT_LEFT) ||
            codeValue == static_cast<int32_t>(KeyCode::KEY_SHIFT_RIGHT)) {
            MarkIsShiftDown(false);
        } else if (codeValue == static_cast<int32_t>(KeyCode::KEY_CTRL_LEFT) ||
                   codeValue == static_cast<int32_t>(KeyCode::KEY_CTRL_RIGHT)) {
            MarkIsCtrlDown(false);
        } else if (codeValue == static_cast<int32_t>(KeyCode::KEY_A)) {
            MarkIsKeyboardA(false);
        }
    }
}

void PipelineContext::OnMouseEvent(const MouseEvent& event)
{
    CHECK_RUN_ON(UI);

    if ((event.action == MouseAction::RELEASE || event.action == MouseAction::PRESS ||
            event.action == MouseAction::MOVE) &&
        (event.button == MouseButton::LEFT_BUTTON || event.pressedButtons == MOUSE_PRESS_LEFT)) {
        auto touchPoint = event.CreateTouchPoint();
        OnTouchEvent(touchPoint);
    }

    CHECK_NULL_VOID(rootElement_);
    auto scaleEvent = event.CreateScaleEvent(viewScale_);
    if (event.action == MouseAction::PRESS && event.button != MouseButton::LEFT_BUTTON) {
        eventManager_->HandleOutOfRectCallback(
            { scaleEvent.x, scaleEvent.y, scaleEvent.sourceType }, rectCallbackList_);
    }
    eventManager_->MouseTest(scaleEvent, rootElement_->GetRenderNode());
    eventManager_->DispatchMouseEvent(scaleEvent);
    eventManager_->DispatchMouseHoverAnimation(scaleEvent);
    eventManager_->DispatchMouseHoverEvent(scaleEvent);
#ifdef ENABLE_ROSEN_BACKEND
    std::chrono::high_resolution_clock::duration epoch_time = event.time.time_since_epoch();
    auto eventTimestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(epoch_time);
    if (SystemProperties::GetRosenBackendEnabled() && rsUIDirector_) {
        std::string abilityName = AceApplicationInfo::GetInstance().GetProcessName().empty()
                                      ? AceApplicationInfo::GetInstance().GetPackageName()
                                      : AceApplicationInfo::GetInstance().GetProcessName();
        rsUIDirector_->SetTimeStamp(eventTimestamp.count(), abilityName);
    }
#endif
    FlushMessages();
}

void PipelineContext::CreateTouchEventOnZoom(const AxisEvent& event)
{
    zoomEventA_.id = 0;
    zoomEventB_.id = 1;
    zoomEventA_.type = zoomEventB_.type = TouchType::UNKNOWN;
    zoomEventA_.time = zoomEventB_.time = event.time;
    zoomEventA_.deviceId = zoomEventB_.deviceId = event.deviceId;
    zoomEventA_.sourceType = zoomEventB_.sourceType = SourceType::MOUSE;
    if (!isOnScrollZoomEvent_) {
        zoomEventA_.x = zoomEventA_.screenX = event.x - ZOOM_DISTANCE_DEFAULT;
        zoomEventA_.y = zoomEventA_.screenY = event.y;
        zoomEventA_.type = TouchType::DOWN;
        zoomEventB_.x = zoomEventB_.screenX = event.x + ZOOM_DISTANCE_DEFAULT;
        zoomEventB_.y = zoomEventB_.screenY = event.y;
        zoomEventB_.type = TouchType::DOWN;
        LOGI("Send TouchEventA(%{public}f, %{public}f, %{public}zu)", zoomEventA_.x, zoomEventA_.y, zoomEventA_.type);
        OnTouchEvent(zoomEventA_);
        LOGI("Send TouchEventB(%{public}f, %{public}f, %{public}zu)", zoomEventB_.x, zoomEventB_.y, zoomEventB_.type);
        OnTouchEvent(zoomEventB_);
        isOnScrollZoomEvent_ = true;
    }
    if (LessOrEqual(event.verticalAxis, 0.0)) {
        zoomEventA_.x = zoomEventA_.screenX -= ZOOM_DISTANCE_MOVE_PER_WHEEL;
        zoomEventA_.type = TouchType::MOVE;
        LOGI("Send TouchEventA(%{public}f, %{public}f, %{public}zu)", zoomEventA_.x, zoomEventA_.y, zoomEventA_.type);
        OnTouchEvent(zoomEventA_);
        zoomEventB_.x = zoomEventB_.screenX += ZOOM_DISTANCE_MOVE_PER_WHEEL;
        zoomEventB_.type = TouchType::MOVE;
        LOGI("Send TouchEventB(%{public}f, %{public}f, %{public}zu)", zoomEventB_.x, zoomEventB_.y, zoomEventB_.type);
        OnTouchEvent(zoomEventB_);
    } else {
        if (!NearEqual(zoomEventA_.x, event.x)) {
            zoomEventA_.x = zoomEventA_.screenX += ZOOM_DISTANCE_MOVE_PER_WHEEL;
            zoomEventA_.type = TouchType::MOVE;
            LOGI("Send TouchEventA(%{public}f, %{public}f, %{public}zu)", zoomEventA_.x, zoomEventA_.y,
                zoomEventA_.type);
            OnTouchEvent(zoomEventA_);
        }
        if (!NearEqual(zoomEventB_.x, event.x)) {
            zoomEventB_.x = zoomEventB_.screenX -= ZOOM_DISTANCE_MOVE_PER_WHEEL;
            zoomEventB_.type = TouchType::MOVE;
            LOGI("Send TouchEventB(%{public}f, %{public}f, %{public}zu)", zoomEventB_.x, zoomEventB_.y,
                zoomEventB_.type);
            OnTouchEvent(zoomEventB_);
        }
    }
}

MouseEvent ConvertAxisToMouse(const AxisEvent& event)
{
    MouseEvent result;
    result.x = event.x;
    result.y = event.y;
    result.action = MouseAction::MOVE;
    result.button = MouseButton::NONE_BUTTON;
    result.time = event.time;
    result.deviceId = event.deviceId;
    result.sourceType = event.sourceType;
    return result;
}

void PipelineContext::OnAxisEvent(const AxisEvent& event)
{
    if (isKeyCtrlPressed_ && !NearZero(event.verticalAxis) &&
        (event.action == AxisAction::BEGIN || event.action == AxisAction::UPDATE)) {
        CreateTouchEventOnZoom(event);
        return;
    }

    auto scaleEvent = event.CreateScaleEvent(viewScale_);

    if (event.action == AxisAction::BEGIN) {
        TouchRestrict touchRestrict { TouchRestrict::NONE };
        eventManager_->TouchTest(scaleEvent, rootElement_->GetRenderNode(), touchRestrict);
    }
    eventManager_->DispatchTouchEvent(scaleEvent);

    if (event.action == AxisAction::BEGIN || event.action == AxisAction::UPDATE) {
        eventManager_->AxisTest(scaleEvent, rootElement_->GetRenderNode());
        eventManager_->DispatchAxisEvent(scaleEvent);
    }

    auto mouseEvent = ConvertAxisToMouse(event);
    OnMouseEvent(mouseEvent);
}

void PipelineContext::AddToHoverList(const RefPtr<RenderNode>& node)
{
    CHECK_RUN_ON(UI);
    int32_t nodeId = node->GetAccessibilityNodeId();
    if (nodeId == 0) {
        return;
    }
    if (nodeId != hoverNodeId_) {
        // Hover node changed to the next id.
        hoverNodes_.clear();
        hoverNodes_.emplace_back(node);
        hoverNodeId_ = nodeId;
    } else {
        // Hover node add to current hover list.
        hoverNodes_.emplace_back(node);
    }
}

bool PipelineContext::OnRotationEvent(const RotationEvent& event) const
{
    CHECK_RUN_ON(UI);
    if (!rootElement_) {
        LOGE("the root element is nullptr");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return false;
    }

    RefPtr<StackElement> stackElement = GetLastStack();
    if (!stackElement) {
        LOGE("the stack element is nullptr");
        return false;
    }
    RefPtr<RenderNode> stackRenderNode = stackElement->GetRenderNode();
    if (!stackRenderNode) {
        LOGE("the stack render node is nullptr");
        return false;
    }

    return eventManager_->DispatchRotationEvent(event, stackRenderNode, requestedRenderNode_.Upgrade());
}

void PipelineContext::SetCardViewPosition(int id, float offsetX, float offsetY)
{
    auto accessibilityManager = GetAccessibilityManager();
    if (!accessibilityManager) {
        return;
    }
    accessibilityManager->SetCardViewPosition(id, offsetX, offsetY);
}

void PipelineContext::SetCardViewAccessibilityParams(const std::string& key, bool focus)
{
    auto accessibilityManager = GetAccessibilityManager();
    if (!accessibilityManager) {
        return;
    }
    accessibilityManager->SetCardViewParams(key, focus);
}

void PipelineContext::FlushVsync(uint64_t nanoTimestamp, uint32_t frameCount)
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACK();
#if defined(ENABLE_NATIVE_VIEW)
    if (frameCount_ < 2) {
        frameCount_++;
    }
#endif
#ifdef ENABLE_ROSEN_BACKEND
    if (SystemProperties::GetRosenBackendEnabled() && rsUIDirector_) {
        std::string abilityName = AceApplicationInfo::GetInstance().GetProcessName().empty()
                                      ? AceApplicationInfo::GetInstance().GetPackageName()
                                      : AceApplicationInfo::GetInstance().GetProcessName();
        rsUIDirector_->SetTimeStamp(nanoTimestamp, abilityName);
    }
#endif
    if (isSurfaceReady_) {
        FlushTouchEvents();
        FlushAnimation(GetTimeFromExternalTimer());
        FlushPipelineWithoutAnimation();
        FlushAnimationTasks();
        window_->FlushLayoutSize(width_, height_);
        hasIdleTasks_ = false;
    } else {
        LOGW("the surface is not ready, waiting");
    }
    if (isMoving_) {
        window_->RequestFrame();
        MarkForcedRefresh();
        isMoving_ = false;
    }
}

void PipelineContext::OnIdle(int64_t deadline)
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACE();
    auto front = GetFrontend();
    if (front && GetIsDeclarative()) {
        if (deadline != 0) {
            FlushPredictLayout(deadline);
        }
        return;
    }
    FlushPredictLayout(deadline);
    if (hasIdleTasks_) {
        FlushPipelineImmediately();
        window_->RequestFrame();
        MarkForcedRefresh();
        hasIdleTasks_ = false;
    }
    FlushPageUpdateTasks();
}

void PipelineContext::OnVirtualKeyboardHeightChange(float keyboardHeight,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction, const float safeHeight, const bool supportAvoidance,
    bool forceChange)
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACE();
#ifdef ENABLE_ROSEN_BACKEND
    if (rsTransaction) {
        FlushMessages();
        rsTransaction->Begin();
    }
#endif

    auto func = [this, keyboardHeight]() {
        double positionY = 0;
        if (textFieldManager_) {
            positionY = textFieldManager_->GetClickPosition().GetY();
        }
        auto newKeyboardHeight = keyboardHeight / viewScale_;
        auto height = height_ / viewScale_;
        double offsetFix =
            (height - positionY) > 100.0 ? newKeyboardHeight - (height - positionY) / 2.0 : newKeyboardHeight;
        LOGI("OnVirtualKeyboardAreaChange positionY:%{public}f safeArea:%{public}f offsetFix:%{public}f", positionY,
            (height - newKeyboardHeight), offsetFix);
        if (NearZero(newKeyboardHeight)) {
            if (textFieldManager_ && AceType::InstanceOf<TextFieldManager>(textFieldManager_)) {
                auto textFieldManager = AceType::DynamicCast<TextFieldManager>(textFieldManager_);
                if (textFieldManager->ResetSlidingPanelParentHeight()) {
                    return;
                }
            }
            SetRootSizeWithWidthHeight(width_, height_, 0);
            rootOffset_.SetY(0.0);
        } else if (positionY > (height - newKeyboardHeight) && offsetFix > 0.0) {
            if (textFieldManager_ && AceType::InstanceOf<TextFieldManager>(textFieldManager_)) {
                auto textFieldManager = AceType::DynamicCast<TextFieldManager>(textFieldManager_);
                if (textFieldManager->UpdatePanelForVirtualKeyboard(-offsetFix, height)) {
                    return;
                }
            }
            SetRootSizeWithWidthHeight(width_, height_, -offsetFix);
            rootOffset_.SetY(-offsetFix);
        }
    };

    AnimationOption option = AnimationUtil::CreateKeyboardAnimationOption(keyboardAnimationConfig_, keyboardHeight);
    Animate(option, option.GetCurve(), func);

#ifdef ENABLE_ROSEN_BACKEND
    if (rsTransaction) {
        rsTransaction->Commit();
    }
#endif
}

void PipelineContext::FlushPipelineImmediately()
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACE();
    if (isSurfaceReady_) {
        FlushPipelineWithoutAnimation();
    } else {
        LOGW("the surface is not ready, waiting");
    }
}

void PipelineContext::WindowSizeChangeAnimate(int32_t width, int32_t height, WindowSizeChangeReason type,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    static const bool IsWindowSizeAnimationEnabled = SystemProperties::IsWindowSizeAnimationEnabled();
    if (!rootElement_ || !rootElement_->GetRenderNode() || !IsWindowSizeAnimationEnabled) {
        LOGE("RootNodeAnimation: no root element found, no animation configured");
        SetRootSizeWithWidthHeight(width, height);
        return;
    }
    auto rootNode = AceType::DynamicCast<RenderRoot>(rootElement_->GetRenderNode());
    switch (type) {
        case WindowSizeChangeReason::RECOVER:
        case WindowSizeChangeReason::MAXIMIZE: {
            AnimationOption option;
            constexpr int32_t duration = 400;
            option.SetDuration(duration);
            auto curve = MakeRefPtr<DecelerationCurve>();
            option.SetCurve(curve);
            Animate(option, curve, [width, height, this]() {
                SetRootSizeWithWidthHeight(width, height);
                FlushLayout();
            });
            break;
        }
        case WindowSizeChangeReason::ROTATION: {
            SetRootSizeWithWidthHeight(width, height);
            FlushLayout();
            break;
        }
        case WindowSizeChangeReason::DRAG_START:
        case WindowSizeChangeReason::DRAG:
        case WindowSizeChangeReason::DRAG_END:
        case WindowSizeChangeReason::RESIZE:
        case WindowSizeChangeReason::UNDEFINED:
        default: {
            SetRootSizeWithWidthHeight(width, height);
        }
    }
}

void PipelineContext::OnSurfaceChanged(int32_t width, int32_t height, WindowSizeChangeReason type,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    CHECK_RUN_ON(UI);
    if (width_ == width && height_ == height && type == WindowSizeChangeReason::CUSTOM_ANIMATION) {
        TryCallNextFrameLayoutCallback();
        return;
    }
    // Refresh the screen when developers customize the resolution and screen density on the PC preview.
#if !defined(PREVIEW)
    if (width_ == width && height_ == height && isSurfaceReady_ && !isDensityUpdate_) {
        return;
    }
#endif

    for (auto&& [id, callback] : surfaceChangedCallbackMap_) {
        if (callback) {
            callback(width, height, width_, height_, type);
        }
    }

    width_ = width;
    height_ = height;

    ACE_SCOPED_TRACE("OnSurfaceChanged(%d, %d)", width, height);
    LOGI("Surface size changed, [%{public}d * %{public}d]", width, height);
    if (!NearZero(rootHeight_)) {
        double newRootHeight = height / viewScale_;
        double newRootWidth = width / viewScale_;
        double offsetHeight = rootHeight_ - newRootHeight;
        if (textFieldManager_ && GetLastPage()) {
            textFieldManager_->MovePage(GetLastPage()->GetPageId(), { newRootWidth, newRootHeight }, offsetHeight);
        }
    }

    taskExecutor_->PostTask(
        [weakFrontend = weakFrontend_, width, height]() {
            auto frontend = weakFrontend.Upgrade();
            if (frontend) {
                frontend->OnSurfaceChanged(width, height);
            }
        },
        TaskExecutor::TaskType::JS, "ArkUISurfaceChanged", TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));

    // init transition clip size when surface changed.
    const auto& pageElement = GetLastPage();
    if (pageElement) {
        const auto& transitionElement = AceType::DynamicCast<PageTransitionElement>(pageElement->GetFirstChild());
        if (transitionElement) {
            transitionElement->InitTransitionClip();
        }
    }
#ifdef ENABLE_ROSEN_BACKEND
    WindowSizeChangeAnimate(width, height, type, rsTransaction);
#else
    SetRootSizeWithWidthHeight(width, height);
#endif
    if (isSurfaceReady_) {
        return;
    }
    isSurfaceReady_ = true;
    FlushPipelineWithoutAnimation();
    MarkForcedRefresh();
#ifndef WEARABLE_PRODUCT
    multiModalManager_->OpenChannel(Claim(this));
#endif
}

void PipelineContext::OnSurfacePositionChanged(int32_t posX, int32_t posY)
{
    for (auto&& [id, callback] : surfacePositionChangedCallbackMap_) {
        if (callback) {
            callback(posX, posY);
        }
    }
}

void PipelineContext::OnSurfaceDensityChanged(double density)
{
    CHECK_RUN_ON(UI);
    ACE_SCOPED_TRACE("OnSurfaceDensityChanged(%lf)", density);
    isDensityUpdate_ = density != density_;
    density_ = density;
    if (!NearZero(viewScale_)) {
        dipScale_ = density_ / viewScale_;
    }
    if (isDensityUpdate_) {
        PipelineBase::OnSurfaceDensityChanged(density);
    }
}

void PipelineContext::OnSystemBarHeightChanged(double statusBar, double navigationBar)
{
    CHECK_RUN_ON(UI);
    ACE_SCOPED_TRACE("OnSystemBarHeightChanged(%lf, %lf)", statusBar, navigationBar);
    double statusBarHeight = 0.0;
    double navigationBarHeight = 0.0;
    if (!NearZero(viewScale_) && !NearZero(dipScale_)) {
        statusBarHeight = statusBar / viewScale_ / dipScale_;
        navigationBarHeight = navigationBar / viewScale_ / dipScale_;
    }

    if ((!NearEqual(statusBarHeight, statusBarHeight_)) || (!NearEqual(navigationBarHeight, navigationBarHeight_))) {
        statusBarHeight_ = statusBarHeight;
        navigationBarHeight_ = navigationBarHeight;
        if (windowModal_ == WindowModal::SEMI_MODAL || windowModal_ == WindowModal::SEMI_MODAL_FULL_SCREEN) {
            auto semiModal = AceType::DynamicCast<SemiModalElement>(rootElement_->GetFirstChild());
            if (semiModal) {
                semiModal->UpdateSystemBarHeight(statusBarHeight_, navigationBarHeight_);
            }
        } else if (windowModal_ == WindowModal::DIALOG_MODAL) {
            auto dialogModal = AceType::DynamicCast<DialogModalElement>(rootElement_->GetFirstChild());
            if (dialogModal) {
                dialogModal->UpdateSystemBarHeight(statusBarHeight_, navigationBarHeight_);
            }
        } else {
            // Normal modal, do nothing.
        }
    }
}

void PipelineContext::OnSurfaceDestroyed()
{
    CHECK_RUN_ON(UI);
    ACE_SCOPED_TRACE("OnSurfaceDestroyed");
    isSurfaceReady_ = false;
}

void PipelineContext::SetRootSizeWithWidthHeight(int32_t width, int32_t height, int32_t offset)
{
    CHECK_RUN_ON(UI);
    UpdateRootSizeAndScale(width, height);
    CHECK_NULL_VOID(rootElement_);
    const Rect paintRect(0.0, 0.0, rootWidth_, rootHeight_);
    auto rootNode = AceType::DynamicCast<RenderRoot>(rootElement_->GetRenderNode());
    if (!rootNode) {
        return;
    }
    auto stack = GetStageElement()->GetElementParent().Upgrade();
    if (stack) {
        auto renderStack = AceType::DynamicCast<RenderStack>(stack->GetRenderNode());
        if (renderStack) {
            renderStack->SetTop(Dimension(offset));
        }
    }
    if (!NearEqual(viewScale_, rootNode->GetScale()) || paintRect != rootNode->GetPaintRect() || isDensityUpdate_) {
        if (!NearEqual(viewScale_, rootNode->GetScale())) {
            rootNode->SetReset(true);
        }
        rootNode->SetPaintRect(paintRect);
        rootNode->SetScale(viewScale_);
        rootNode->MarkNeedLayout();
        rootNode->MarkNeedRender();
        focusAnimationManager_->SetAvailableRect(paintRect);
    }
    if (IsJsPlugin() || IsJsCard()) {
        return;
    }
    ScreenSystemManager::GetInstance().SetWindowInfo(rootWidth_, density_, dipScale_);
    ScreenSystemManager::GetInstance().OnSurfaceChanged(width);
}

void PipelineContext::SetAppBgColor(const Color& color)
{
    LOGI("Set bgColor %{public}u", color.GetValue());
    appBgColor_ = color;
#ifdef ENABLE_ROSEN_BACKEND
    if (rsUIDirector_) {
        rsUIDirector_->SetAbilityBGAlpha(appBgColor_.GetAlpha());
    }
#endif
    if (!themeManager_) {
        LOGW("themeManager_ is nullptr!");
        return;
    }
    auto appTheme = themeManager_->GetTheme<AppTheme>();
    if (!appTheme) {
        LOGW("appTheme is nullptr!");
        return;
    }
    appTheme->SetBackgroundColor(appBgColor_);
    if (!rootElement_) {
        LOGW("rootElement_ is nullptr!");
        return;
    }
    auto renderRoot = DynamicCast<RenderRoot>(rootElement_->GetRenderNode());
    if (!renderRoot) {
        LOGW("renderRoot is nullptr!");
        return;
    }
    if (windowModal_ == WindowModal::CONTAINER_MODAL) {
        auto containerModal = AceType::DynamicCast<ContainerModalElement>(rootElement_->GetFirstChild());
        if (containerModal) {
            containerModal->SetAppBgColor(appBgColor_);
            renderRoot->SetBgColor(Color::TRANSPARENT);
            return;
        }
    }
    renderRoot->SetBgColor(appBgColor_);
}

void PipelineContext::Finish(bool autoFinish) const
{
    CHECK_RUN_ON(UI);
    if (autoFinish && rootElement_ && onShow_) {
        if (windowModal_ == WindowModal::SEMI_MODAL || windowModal_ == WindowModal::SEMI_MODAL_FULL_SCREEN) {
            auto semiModal = AceType::DynamicCast<SemiModalElement>(rootElement_->GetFirstChild());
            if (!semiModal) {
                LOGE("SemiModal animate to exit app failed. semi modal is null");
                return;
            }
            semiModal->AnimateToExitApp();
            return;
        } else if (windowModal_ == WindowModal::DIALOG_MODAL) {
            // dialog modal use translucent theme and will do exit animation by ACE itself.
            auto dialogModal = AceType::DynamicCast<DialogModalElement>(rootElement_->GetFirstChild());
            if (!dialogModal) {
                LOGE("DialogModal animate to exit app failed. dialog modal is null");
                return;
            }
            dialogModal->AnimateToExitApp();
            return;
        } else {
            // normal force finish.
            Finish(false);
        }
    } else {
        if (finishEventHandler_) {
            finishEventHandler_();
        } else {
            LOGE("fail to finish current context due to handler is nullptr");
        }
    }
}

void PipelineContext::RequestFullWindow(int32_t duration)
{
    CHECK_RUN_ON(UI);
    if (!rootElement_) {
        LOGE("Root element is null!");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return;
    }
    auto semiModal = AceType::DynamicCast<SemiModalElement>(rootElement_->GetFirstChild());
    if (!semiModal) {
        LOGI("Get semiModal element failed. SemiModal element is null!");
        return;
    }
    if (semiModal->IsFullWindow()) {
        LOGI("Already in full window, skip it.");
        return;
    }
    isFullWindow_ = true;
    // when semi modal animating, no more full window request can be handled, so mark it as full window.
    semiModal->SetFullWindow(true);
    semiModal->AnimateToFullWindow(duration);
    NotifyStatusBarBgColor(semiModal->GetBackgroundColor());
    auto page = GetLastStack();
    if (!page) {
        return;
    }
    auto renderPage = AceType::DynamicCast<RenderStack>(page->GetRenderNode());
    if (!renderPage) {
        return;
    }
    // Change to full window, change page stack layout strategy.
    renderPage->SetStackFit(StackFit::INHERIT);
    renderPage->SetMainStackSize(MainStackSize::MAX);
    renderPage->MarkNeedLayout();
}

void PipelineContext::ShowFocusAnimation(
    const RRect& rrect, const Color& color, const Offset& offset, bool isIndented) const
{
    focusAnimationManager_->SetFocusAnimationProperties(rrect, color, offset, isIndented);
}

void PipelineContext::ShowFocusAnimation(
    const RRect& rrect, const Color& color, const Offset& offset, const Rect& clipRect) const
{
    focusAnimationManager_->SetFocusAnimationProperties(rrect, color, offset, clipRect);
}

void PipelineContext::AddDirtyFocus(const RefPtr<FocusNode>& node)
{
    CHECK_RUN_ON(UI);
    if (!node) {
        LOGW("node is null.");
        return;
    }
    if (node->IsChild()) {
        dirtyFocusNode_ = WeakClaim(RawPtr(node));
    } else {
        dirtyFocusScope_ = WeakClaim(RawPtr(node));
    }
    window_->RequestFrame();
}

void PipelineContext::CancelFocusAnimation() const
{
    focusAnimationManager_->CancelFocusAnimation();
}

void PipelineContext::PopFocusAnimation() const
{
    focusAnimationManager_->PopFocusAnimationElement();
}

void PipelineContext::PopRootFocusAnimation() const
{
    focusAnimationManager_->PopRootFocusAnimationElement();
}

void PipelineContext::PushFocusAnimation(const RefPtr<Element>& element) const
{
    focusAnimationManager_->PushFocusAnimationElement(element);
}

void PipelineContext::Destroy()
{
    CHECK_RUN_ON(UI);
    LOGI("PipelineContext::Destroy begin.");
    rootElement_.Reset();
    composedElementMap_.clear();
    dirtyElements_.clear();
    deactivateElements_.clear();
    dirtyRenderNodes_.clear();
    dirtyRenderNodesInOverlay_.clear();
    dirtyLayoutNodes_.clear();
    predictLayoutNodes_.clear();
    geometryChangedNodes_.clear();
    needPaintFinishNodes_.clear();
    dirtyFocusNode_.Reset();
    dirtyFocusScope_.Reset();
    postFlushListeners_.clear();
    postAnimationFlushListeners_.clear();
    preFlushListeners_.clear();
    sharedTransitionController_.Reset();
    cardTransitionController_.Reset();
    while (!pageUpdateTasks_.empty()) {
        pageUpdateTasks_.pop();
    }
    alignDeclarationNodeList_.clear();
    hoverNodes_.clear();
    renderFactory_.Reset();
    nodesToNotifyOnPreDraw_.clear();
    nodesNeedDrawOnPixelMap_.clear();
    layoutTransitionNodeSet_.clear();
    explicitAnimators_.clear();
    preTargetRenderNode_.Reset();
    sharedImageManager_.Reset();
    rectCallbackList_.clear();
    PipelineBase::Destroy();
    LOGI("PipelineContext::Destroy end.");
}

void PipelineContext::SendCallbackMessageToFrontend(const std::string& callbackId, const std::string& data)
{
    auto frontend = weakFrontend_.Upgrade();
    if (!frontend) {
        LOGE("frontend is nullptr");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return;
    }
    frontend->SendCallbackMessage(callbackId, data);
}

void PipelineContext::SendEventToFrontend(const EventMarker& eventMarker)
{
    auto frontend = weakFrontend_.Upgrade();
    if (!frontend) {
        LOGE("frontend is nullptr");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return;
    }
    auto handler = frontend->GetEventHandler();
    if (!handler) {
        LOGE("fail to trigger async event due to event handler is nullptr");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return;
    }
    handler->HandleAsyncEvent(eventMarker);
}

void PipelineContext::SendEventToFrontend(const EventMarker& eventMarker, const std::string& param)
{
    auto frontend = weakFrontend_.Upgrade();
    if (!frontend) {
        LOGE("frontend is nullptr");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return;
    }
    auto handler = frontend->GetEventHandler();
    if (!handler) {
        LOGE("fail to trigger async event due to event handler is nullptr");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return;
    }
    handler->HandleAsyncEvent(eventMarker, param);
}

bool PipelineContext::AccessibilityRequestFocus(const ComposeId& id)
{
    auto targetElement = GetComposedElementById(id);
    if (!targetElement) {
        LOGE("RequestFocusById targetElement is null.");
        EventReport::SendAccessibilityException(AccessibilityExcepType::GET_NODE_ERR);
        return false;
    }
    return RequestFocus(targetElement);
}

bool PipelineContext::RequestFocus(const RefPtr<Element>& targetElement)
{
    CHECK_RUN_ON(UI);
    if (!targetElement) {
        return false;
    }
    auto children = targetElement->GetChildren();
    for (const auto& childElement : children) {
        auto focusNode = AceType::DynamicCast<FocusNode>(childElement);
        if (focusNode) {
            if (focusNode->RequestFocusImmediately()) {
                return true;
            } else {
                continue;
            }
        }
        if (RequestFocus(childElement)) {
            return true;
        }
    }
    return false;
}

bool PipelineContext::RequestFocus(const std::string& targetNodeId, bool isSyncRequest)
{
    CHECK_NULL_RETURN(rootElement_, false);
    auto currentFocusChecked = rootElement_->RequestFocusImmediatelyById(targetNodeId);
    if (!isSubPipeline_ || currentFocusChecked) {
        LOGI("Request focus finish currentFocus is %{public}d", currentFocusChecked);
        return currentFocusChecked;
    }
    LOGI("Search focus in main pipeline");
    auto parentPipelineBase = parentPipeline_.Upgrade();
    CHECK_NULL_RETURN(parentPipelineBase, false);
    auto parentPipelineContext = AceType::DynamicCast<PipelineContext>(parentPipelineBase);
    CHECK_NULL_RETURN(parentPipelineContext, false);
    return parentPipelineContext->RequestFocus(targetNodeId);
}

RefPtr<RenderFocusAnimation> PipelineContext::GetRenderFocusAnimation() const
{
    return focusAnimationManager_->GetRenderFocusAnimation();
}

void PipelineContext::ShowShadow(const RRect& rrect, const Offset& offset) const
{
    focusAnimationManager_->SetShadowProperties(rrect, offset);
}

void PipelineContext::ShowShadow(const RRect& rrect, const Offset& offset, const Rect& clipRect) const
{
    focusAnimationManager_->SetShadowProperties(rrect, offset, clipRect);
}

void PipelineContext::PushShadow(const RefPtr<Element>& element) const
{
    focusAnimationManager_->PushShadow(element);
}

void PipelineContext::PopShadow() const
{
    focusAnimationManager_->PopShadow();
}

void PipelineContext::CancelShadow() const
{
    focusAnimationManager_->CancelShadow();
}

void PipelineContext::SetUseRootAnimation(bool useRoot)
{
    focusAnimationManager_->SetUseRoot(useRoot);
}

#ifndef WEARABLE_PRODUCT
void PipelineContext::SetMultimodalSubscriber(const RefPtr<MultimodalSubscriber>& multimodalSubscriber)
{
    multiModalManager_->SetMultimodalSubscriber(multimodalSubscriber);
}

void PipelineContext::SetWindowOnShow()
{
    window_->OnShow();
    window_->RequestFrame();
}

void PipelineContext::SetWindowOnHide()
{
    window_->RequestFrame();
    window_->OnHide();
}

void PipelineContext::OnShow()
{
    onShow_ = true;
    SetWindowOnShow();
    PerfMonitor::GetPerfMonitor()->SetAppForeground(true);
    auto multiModalScene = multiModalManager_->GetCurrentMultiModalScene();
    if (multiModalScene) {
        multiModalScene->Resume();
    }
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this)]() {
            auto context = weak.Upgrade();
            if (!context) {
                return;
            }
#ifdef ENABLE_ROSEN_BACKEND
            if (context->rsUIDirector_) {
                context->rsUIDirector_->GoForeground();
            }
#endif
            const auto& rootElement = context->rootElement_;
            if (!rootElement) {
                LOGE("render element is null!");
                return;
            }
            const auto& renderRoot = AceType::DynamicCast<RenderRoot>(rootElement->GetRenderNode());
            if (!renderRoot) {
                LOGE("render root is null!");
                return;
            }
            if ((context->windowModal_ == WindowModal::SEMI_MODAL) ||
                (context->windowModal_ == WindowModal::DIALOG_MODAL)) {
                renderRoot->SetDefaultBgColor();
            }
            renderRoot->NotifyOnShow();
        },
        TaskExecutor::TaskType::UI, "ArkUIRenderRootShow", TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
}

void PipelineContext::OnHide()
{
    onShow_ = false;
    SetWindowOnHide();
    PerfMonitor::GetPerfMonitor()->SetAppForeground(false);
    auto multiModalScene = multiModalManager_->GetCurrentMultiModalScene();
    if (multiModalScene) {
        multiModalScene->Hide();
    }
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this)]() {
            auto context = weak.Upgrade();
            if (!context) {
                return;
            }
            if (context->IsSubPipeline()) {
                context->FlushPipelineImmediately();
            }
#ifdef ENABLE_ROSEN_BACKEND
            if (context->rsUIDirector_) {
                context->rsUIDirector_->GoBackground();
                context->rsUIDirector_->SendMessages();
            }
#endif
            context->NotifyPopupDismiss();
            context->OnVirtualKeyboardAreaChange(Rect());
            const auto& rootElement = context->rootElement_;
            if (!rootElement) {
                LOGE("render element is null!");
                return;
            }
            const auto& renderRoot = AceType::DynamicCast<RenderRoot>(rootElement->GetRenderNode());
            if (!renderRoot) {
                LOGE("render root is null!");
                return;
            }
            renderRoot->NotifyOnHide();
        },
        TaskExecutor::TaskType::UI, "ArkUIRenderRootHide", TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
}
#endif

void PipelineContext::RefreshRootBgColor() const
{
    CHECK_RUN_ON(UI);
    if (!rootElement_) {
        return;
    }
    const auto& render = AceType::DynamicCast<RenderRoot>(rootElement_->GetRenderNode());
    if (render) {
        render->SetDefaultBgColor(windowModal_ == WindowModal::CONTAINER_MODAL);
    }
}

void PipelineContext::OnPageShow()
{
    CHECK_RUN_ON(UI);
    if (onPageShowCallBack_) {
        onPageShowCallBack_();
    }
}

void PipelineContext::SetTimeProvider(TimeProvider&& timeProvider)
{
    if (!timeProvider) {
        LOGE("Set time provider failed. provider is null.");
        return;
    }
    timeProvider_ = std::move(timeProvider);
}

uint64_t PipelineContext::GetTimeFromExternalTimer()
{
    if (isFlushingAnimation_) {
        return flushAnimationTimestamp_;
    } else {
        if (!timeProvider_) {
            LOGE("No time provider has been set.");
            return 0;
        }
        return timeProvider_();
    }
}

void PipelineContext::LoadSystemFont(const std::function<void()>& onFondsLoaded)
{
    GetTaskExecutor()->PostTask(
        [weak = WeakClaim(this), fontManager = fontManager_, onFondsLoaded]() {
            if (!fontManager) {
                return;
            }
            fontManager->LoadSystemFont();
            auto context = weak.Upgrade();
            if (!context) {
                return;
            }
            context->GetTaskExecutor()->PostTask(
                [onFondsLoaded]() {
                    if (onFondsLoaded) {
                        onFondsLoaded();
                    }
                },
                TaskExecutor::TaskType::UI, "ArkUISystemFondsLoaded",
                TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
        },
        TaskExecutor::TaskType::IO, "ArkUILoadSystemFont", TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
}

void PipelineContext::AddFontNode(const WeakPtr<RenderNode>& node)
{
    if (fontManager_) {
        fontManager_->AddFontNode(node);
    }
}

void PipelineContext::RemoveFontNode(const WeakPtr<RenderNode>& node)
{
    if (fontManager_) {
        fontManager_->RemoveFontNode(node);
    }
}

void PipelineContext::SetClickPosition(const Offset& position) const
{
    LOGI("SetClickPosition position:%{public}s rootOffset:%{public}s", position.ToString().c_str(),
        rootOffset_.ToString().c_str());
    if (textFieldManager_) {
        textFieldManager_->SetClickPosition(position - rootOffset_);
    }
}

const RefPtr<OverlayElement> PipelineContext::GetOverlayElement() const
{
    if (!rootElement_) {
        LOGE("Root element is null!");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return RefPtr<OverlayElement>();
    }
    auto overlay = AceType::DynamicCast<OverlayElement>(rootElement_->GetOverlayElement(windowModal_));
    if (!overlay) {
        LOGE("Get overlay element failed. overlay element is null!");
        return RefPtr<OverlayElement>();
    }
    return overlay;
}

void PipelineContext::FlushBuildAndLayoutBeforeSurfaceReady()
{
    if (isSurfaceReady_) {
        return;
    }
    GetTaskExecutor()->PostTask(
        [weak = AceType::WeakClaim(this)]() {
            auto context = weak.Upgrade();
            if (!context || context->isSurfaceReady_) {
                return;
            }

            context->FlushBuild();
            context->SetRootRect(context->width_, context->height_);
            context->FlushLayout();
        },
        TaskExecutor::TaskType::UI, "ArkUIFlushBuildAndLayout",
        TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
}

void PipelineContext::RootLostFocus(BlurReason reason) const
{
    if (rootElement_) {
        rootElement_->LostFocus(reason);
    }
}

void PipelineContext::WindowFocus(bool isFocus)
{
    onFocus_ = isFocus;
    if (!isFocus) {
        RootLostFocus(BlurReason::WINDOW_BLUR);
        NotifyPopupDismiss();
        OnVirtualKeyboardAreaChange(Rect());
    }
    if (onFocus_ && onShow_) {
        FlushFocus();
    }
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        return;
    }
    if (!rootElement_) {
        LOGE("WindowFocus failed, rootElement_ is null.");
        return;
    }
    auto containerModal = AceType::DynamicCast<ContainerModalElement>(rootElement_->GetFirstChild());
    if (containerModal) {
        containerModal->WindowFocus(isFocus);
    }
}

void PipelineContext::ContainerModalUnFocus() {}

void PipelineContext::AddPageUpdateTask(std::function<void()>&& task, bool directExecute)
{
    CHECK_RUN_ON(UI);
    pageUpdateTasks_.emplace(std::move(task));
    if (directExecute) {
        FlushPageUpdateTasks();
    } else {
        window_->RequestFrame();
    }
#if defined(ENABLE_NATIVE_VIEW)
    if (frameCount_ == 1) {
        OnIdle(0);
        FlushPipelineImmediately();
    }
#endif
}

void PipelineContext::MovePage(const Offset& rootRect, double offsetHeight)
{
    if (textFieldManager_ && GetLastPage()) {
        textFieldManager_->MovePage(GetLastPage()->GetPageId(), rootRect, offsetHeight);
    }
}

RefPtr<Element> PipelineContext::GetDeactivateElement(int32_t componentId) const
{
    CHECK_RUN_ON(UI);
    auto elementIter = deactivateElements_.find(componentId);
    if (elementIter != deactivateElements_.end()) {
        return elementIter->second;
    } else {
        return nullptr;
    }
}

void PipelineContext::AddDeactivateElement(const int32_t id, const RefPtr<Element>& element)
{
    CHECK_RUN_ON(UI);
    deactivateElements_.emplace(id, element);
}

void PipelineContext::ClearDeactivateElements()
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACK();
    for (auto iter = deactivateElements_.begin(); iter != deactivateElements_.end();) {
        auto element = iter->second;
        RefPtr<RenderNode> render = element ? element->GetRenderNode() : nullptr;
        if (!render || !render->IsDisappearing()) {
            iter = deactivateElements_.erase(iter);
        } else {
            iter++;
        }
    }
}

void PipelineContext::DumpAccessibility(const std::vector<std::string>& params) const
{
    auto accessibilityManager = GetAccessibilityManager();
    if (!accessibilityManager) {
        return;
    }
    accessibilityManager->OnDumpInfo(params);
}

void PipelineContext::UpdateWindowBlurRegion(
    int32_t id, RRect rRect, float progress, WindowBlurStyle style, const std::vector<RRect>& coords)
{
    CHECK_RUN_ON(UI);
    auto pos = windowBlurRegions_.find(id);
    if (pos != windowBlurRegions_.end()) {
        const auto& old = pos->second;
        if (NearEqual(progress, old.progress_) && rRect == old.innerRect_ && style == old.style_) {
            return;
        }
    }
    windowBlurRegions_[id] = { .progress_ = progress, .style_ = style, .innerRect_ = rRect, .coords_ = coords };
    needWindowBlurRegionRefresh_ = true;
}

void PipelineContext::ClearWindowBlurRegion(int32_t id)
{
    CHECK_RUN_ON(UI);
    auto pos = windowBlurRegions_.find(id);
    if (pos != windowBlurRegions_.end()) {
        windowBlurRegions_.erase(pos);
        needWindowBlurRegionRefresh_ = true;
    }
}

void PipelineContext::InitDragListener()
{
    if (!initDragEventListener_) {
        return;
    }
    initDragEventListener_();
}

void PipelineContext::StartSystemDrag(const std::string& str, const RefPtr<PixelMap>& pixmap)
{
    if (!dragEventHandler_) {
        return;
    }
    dragEventHandler_(str, pixmap);
}

void PipelineContext::SetPreTargetRenderNode(const RefPtr<DragDropEvent>& preDragDropNode)
{
    preTargetRenderNode_ = preDragDropNode;
}

const RefPtr<DragDropEvent>& PipelineContext::GetPreTargetRenderNode() const
{
    return preTargetRenderNode_;
}

void PipelineContext::SetInitRenderNode(const RefPtr<RenderNode>& initRenderNode)
{
    initRenderNode_ = initRenderNode;
}

const RefPtr<RenderNode>& PipelineContext::GetInitRenderNode() const
{
    return initRenderNode_;
}

void PipelineContext::ProcessDragEvent(
    const RefPtr<RenderNode>& renderNode, const RefPtr<DragEvent>& event, const Point& globalPoint)
{
    auto targetDragDropNode =
        AceType::DynamicCast<DragDropEvent>(renderNode->FindDropChild(globalPoint, globalPoint - pageOffset_));
    auto initDragDropNode = AceType::DynamicCast<DragDropEvent>(GetInitRenderNode());
    auto extraParams = JsonUtil::Create(true);
    extraParams->Put("customDragInfo", customDragInfo_.c_str());
    extraParams->Put("selectedText", selectedText_.c_str());
    extraParams->Put("imageSrc", imageSrc_.c_str());
    auto info = GestureEvent();
    info.SetGlobalPoint(globalPoint);
    auto preTargetDragDropNode = GetPreTargetRenderNode();
    if (targetDragDropNode == preTargetDragDropNode) {
        if (targetDragDropNode && targetDragDropNode->GetOnDragMove()) {
            auto renderList = renderNode->FindChildNodeOfClass<V2::RenderList>(globalPoint, globalPoint);
            if (renderList) {
                insertIndex_ = renderList->CalculateInsertIndex(renderList, info, selectedItemSize_);
            }

            if (insertIndex_ == static_cast<int32_t>(RenderNode::DEFAULT_INDEX)) {
                (targetDragDropNode->GetOnDragMove())(event, extraParams->ToString());
                return;
            }

            if (targetDragDropNode != initDragDropNode) {
                extraParams->Put("selectedIndex", -1);
            } else {
                extraParams->Put("selectedIndex", selectedIndex_);
            }

            extraParams->Put("insertIndex", insertIndex_);
            (targetDragDropNode->GetOnDragMove())(event, extraParams->ToString());
        }
    } else {
        if (preTargetDragDropNode && preTargetDragDropNode->GetOnDragLeave()) {
            (preTargetDragDropNode->GetOnDragLeave())(event, extraParams->ToString());
        }

        if (targetDragDropNode && targetDragDropNode->GetOnDragEnter()) {
            (targetDragDropNode->GetOnDragEnter())(event, extraParams->ToString());
        }

        SetPreTargetRenderNode(targetDragDropNode);
    }
}

void PipelineContext::ProcessDragEventEnd(
    const RefPtr<RenderNode>& renderNode, const RefPtr<DragEvent>& event, const Point& globalPoint)
{
    auto targetDragDropNode =
        AceType::DynamicCast<DragDropEvent>(renderNode->FindDropChild(globalPoint, globalPoint - pageOffset_));
    auto initDragDropNode = AceType::DynamicCast<DragDropEvent>(GetInitRenderNode());
    auto extraParams = JsonUtil::Create(true);
    extraParams->Put("customDragInfo", customDragInfo_.c_str());
    extraParams->Put("selectedText", selectedText_.c_str());
    extraParams->Put("imageSrc", imageSrc_.c_str());
    auto info = GestureEvent();
    info.SetGlobalPoint(globalPoint);
    auto preTargetDragDropNode = GetPreTargetRenderNode();

    auto textfield = renderNode->FindChildNodeOfClass<RenderTextField>(globalPoint, globalPoint);
    if (textfield) {
        auto value = textfield->GetEditingValue();
        value.Append(selectedText_);
        textfield->SetEditingValue(std::move(value));
    }

    if (targetDragDropNode && targetDragDropNode->GetOnDrop()) {
        auto renderList = renderNode->FindChildNodeOfClass<V2::RenderList>(globalPoint, globalPoint);
        if (renderList) {
            insertIndex_ = renderList->CalculateInsertIndex(renderList, info, selectedItemSize_);
        }

        if (insertIndex_ == static_cast<int32_t>(RenderNode::DEFAULT_INDEX)) {
            (targetDragDropNode->GetOnDrop())(event, extraParams->ToString());
            SetPreTargetRenderNode(nullptr);
            SetInitRenderNode(nullptr);
            return;
        }

        if (targetDragDropNode != initDragDropNode) {
            extraParams->Put("selectedIndex", -1);
        } else {
            extraParams->Put("selectedIndex", selectedIndex_);
        }

        extraParams->Put("insertIndex", insertIndex_);
        (targetDragDropNode->GetOnDrop())(event, extraParams->ToString());
    }

    if (initDragDropNode && initDragDropNode->GetOnDrop()) {
        (initDragDropNode->GetOnDrop())(event, extraParams->ToString());
    }

    SetPreTargetRenderNode(nullptr);
    SetInitRenderNode(nullptr);
}

void PipelineContext::OnDragEvent(const DragPointerEvent& pointerEvent, DragEventAction action,
    const RefPtr<NG::FrameNode>& node)
{
    if (!clipboard_) {
        clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(GetTaskExecutor());
    }

    if (!clipboardCallback_) {
        auto callback = [weakPipelineContext = WeakClaim(this)](const std::string& data) {
            auto pipelineContext = weakPipelineContext.Upgrade();
            if (pipelineContext) {
                auto json = JsonUtil::ParseJsonString(data);
                auto newData = JsonUtil::ParseJsonString(json->GetString("newData"));
                pipelineContext->selectedItemSize_.SetWidth(newData->GetDouble("width"));
                pipelineContext->selectedItemSize_.SetHeight(newData->GetDouble("height"));
                pipelineContext->selectedIndex_ = newData->GetInt("selectedIndex");
                pipelineContext->customDragInfo_ = newData->GetString("customDragInfo");
                pipelineContext->selectedText_ = newData->GetString("selectedText");
                pipelineContext->imageSrc_ = newData->GetString("imageSrc");
            }
        };
        clipboardCallback_ = callback;
    }

    if (clipboardCallback_) {
        clipboard_->GetData(clipboardCallback_);
    }

    auto renderNode = GetLastPageRender();
    if (!renderNode) {
        LOGE("PipelineContext::OnDragEvent renderNode is null.");
        return;
    }

    RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
    event->SetX(ConvertPxToVp(Dimension(pointerEvent.x, DimensionUnit::PX)));
    event->SetY(ConvertPxToVp(Dimension(pointerEvent.y, DimensionUnit::PX)));

    Point globalPoint(pointerEvent.x, pointerEvent.y);

    if (action == DragEventAction::DRAG_EVENT_START) {
        pageOffset_ = GetPageRect().GetOffset();
    }

    event->SetPressedKeyCodes(pointerEvent.pressedKeyCodes);

    if (action != DragEventAction::DRAG_EVENT_END) {
        ProcessDragEvent(renderNode, event, globalPoint);
    } else {
        ProcessDragEventEnd(renderNode, event, globalPoint);
    }
}

void PipelineContext::FlushWindowBlur()
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACK();

    if (!updateWindowBlurRegionHandler_) {
        return;
    }

    if (IsJsPlugin()) {
        return;
    }

    if (IsJsCard()) {
        if (!needWindowBlurRegionRefresh_) {
            return;
        }
        std::vector<std::vector<float>> blurRectangles;
        if (!windowBlurRegions_.empty()) {
            blurRectangles.push_back(std::vector<float> { 1 });
        }
        updateWindowBlurRegionHandler_(blurRectangles);
        needWindowBlurRegionRefresh_ = false;
        return;
    }
    if (!rootElement_) {
        LOGE("root element is null");
        return;
    }
    auto renderNode = rootElement_->GetRenderNode();
    if (!renderNode) {
        LOGE("get renderNode failed");
        return;
    }

    if (!windowBlurRegions_.empty()) {
        renderNode->WindowBlurTest();
    }

    float scale = GetViewScale();
    if (needWindowBlurRegionRefresh_) {
        std::vector<std::vector<float>> blurRectangles;
        for (auto& region : windowBlurRegions_) {
            std::vector<float> rectArray;
            // progress
            rectArray.push_back(region.second.progress_);
            // style
            rectArray.push_back(static_cast<float>(region.second.style_));
            for (auto item : region.second.coords_) {
                item.ApplyScaleAndRound(scale);
                const Rect& rect = item.GetRect();
                // rect
                rectArray.push_back(static_cast<float>(rect.Left()));
                rectArray.push_back(static_cast<float>(rect.Top()));
                rectArray.push_back(static_cast<float>(rect.Right()));
                rectArray.push_back(static_cast<float>(rect.Bottom()));
                const Corner& radius = item.GetCorner();
                // roundX roundY
                rectArray.push_back(static_cast<float>(radius.topLeftRadius.GetX().Value()));
                rectArray.push_back(static_cast<float>(radius.topLeftRadius.GetY().Value()));
            }
            blurRectangles.push_back(rectArray);
        }
        updateWindowBlurRegionHandler_(blurRectangles);
        needWindowBlurRegionRefresh_ = false;
    }
    if (updateWindowBlurDrawOpHandler_) {
        updateWindowBlurDrawOpHandler_();
    }
}

void PipelineContext::MakeThreadStuck(const std::vector<std::string>& params) const
{
    int32_t time = StringUtils::StringToInt(params[2]);
    if (time < 0 || (params[1] != JS_THREAD_NAME && params[1] != UI_THREAD_NAME)) {
        DumpLog::GetInstance().Print("Params illegal, please check!");
        return;
    }
    DumpLog::GetInstance().Print(params[1] + " thread will stuck for " + params[2] + " seconds.");
    if (params[1] == JS_THREAD_NAME) {
        taskExecutor_->PostTask([time] { ThreadStuckTask(time); }, TaskExecutor::TaskType::JS, "ArkUIThreadStuck",
            TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
    } else {
        taskExecutor_->PostTask([time] { ThreadStuckTask(time); }, TaskExecutor::TaskType::UI, "ArkUIThreadStuck",
            TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
    }
}

void PipelineContext::SetIsKeyEvent(bool isKeyEvent)
{
    if (focusAnimationManager_) {
        isKeyEvent_ = isKeyEvent;
        focusAnimationManager_->SetIsKeyEvent(isKeyEvent_);
    }
}

void PipelineContext::NavigatePage(uint8_t type, const PageTarget& target, const std::string& params)
{
    auto frontend = weakFrontend_.Upgrade();
    if (!frontend) {
        LOGE("frontend is nullptr");
        return;
    }
    frontend->NavigatePage(type, target, params);
}

void PipelineContext::AddKeyFrame(
    float fraction, const RefPtr<Curve>& curve, const std::function<void()>& propertyCallback)
{
    if (propertyCallback == nullptr) {
        LOGE("failed to add key frame, property callback is null!");
        return;
    }

    pendingImplicitLayout_.push(false);
    auto propertyChangeCallback = [weak = AceType::WeakClaim(this), callback = propertyCallback,
                                      id = Container::CurrentId()]() {
        ContainerScope scope(id);
        auto context = weak.Upgrade();
        if (context == nullptr) {
            LOGE("failed to add key frame, context is null!");
            return;
        }

        callback();
        if (context->pendingImplicitLayout_.top()) {
            context->FlushLayout();
        }
    };
    pendingImplicitLayout_.pop();

#ifdef ENABLE_ROSEN_BACKEND
    RSNode::AddKeyFrame(fraction, NativeCurveHelper::ToNativeCurve(curve), propertyChangeCallback);
#endif
}

void PipelineContext::AddKeyFrame(float fraction, const std::function<void()>& propertyCallback)
{
    if (propertyCallback == nullptr) {
        LOGE("failed to add key frame, property callback is null!");
        return;
    }

    pendingImplicitLayout_.push(false);
    auto propertyChangeCallback = [weak = AceType::WeakClaim(this), callback = propertyCallback,
                                      id = Container::CurrentId()]() {
        ContainerScope scope(id);
        auto context = weak.Upgrade();
        if (context == nullptr) {
            LOGE("failed to add key frame, context is null!");
            return;
        }

        callback();
        if (context->pendingImplicitLayout_.top()) {
            context->FlushLayout();
        }
    };
    pendingImplicitLayout_.pop();

#ifdef ENABLE_ROSEN_BACKEND
    RSNode::AddKeyFrame(fraction, propertyChangeCallback);
#endif
}

void PipelineContext::SaveExplicitAnimationOption(const AnimationOption& option)
{
    explicitAnimationOption_ = option;
}

void PipelineContext::CreateExplicitAnimator(const std::function<void()>& onFinishEvent)
{
    if (!onFinishEvent) {
        return;
    }
    auto animator = CREATE_ANIMATOR(AceType::WeakClaim(this));
    animator->AddStopListener([onFinishEvent, weakContext = AceType::WeakClaim(this), id = animator->GetId()] {
        auto context = weakContext.Upgrade();
        if (!context) {
            return;
        }
        context->PostAsyncEvent(onFinishEvent, "ArkUIAnimatorFinishEvent");
        context->explicitAnimators_.erase(id);
    });
    animator->SetDuration(explicitAnimationOption_.GetDuration());
    animator->SetStartDelay(explicitAnimationOption_.GetDelay());
    animator->SetIteration(explicitAnimationOption_.GetIteration());
    animator->SetTempo(explicitAnimationOption_.GetTempo());
    animator->SetAnimationDirection(explicitAnimationOption_.GetAnimationDirection());
    animator->SetFillMode(FillMode::FORWARDS);
    animator->Play();
    explicitAnimators_.emplace(animator->GetId(), animator);
}

void PipelineContext::ClearExplicitAnimationOption()
{
    explicitAnimationOption_ = AnimationOption();
}

AnimationOption PipelineContext::GetExplicitAnimationOption() const
{
    return explicitAnimationOption_;
}

bool PipelineContext::GetIsDeclarative() const
{
    RefPtr<Frontend> front = GetFrontend();
    if (front) {
        return (front->GetType() == FrontendType::DECLARATIVE_JS ||
                front->GetType() == FrontendType::JS_PLUGIN ||
                front->GetType() == FrontendType::DECLARATIVE_CJ);
    }
    return false;
}

void PipelineContext::SetForbidPlatformQuit(bool forbidPlatformQuit)
{
    forbidPlatformQuit_ = forbidPlatformQuit;
    auto stageElement = GetStageElement();
    if (!stageElement) {
        LOGE("Stage is null.");
        return;
    }
    auto renderStage = AceType::DynamicCast<RenderStage>(stageElement->GetRenderNode());
    if (!renderStage) {
        LOGE("RenderStage is null.");
        return;
    }
    renderStage->SetForbidSwipeToRight(forbidPlatformQuit_);
}

void PipelineContext::AddLayoutTransitionNode(const RefPtr<RenderNode>& node)
{
    CHECK_RUN_ON(UI);
    layoutTransitionNodeSet_.insert(node);
}

void PipelineContext::AddAlignDeclarationNode(const RefPtr<RenderNode>& node)
{
    CHECK_RUN_ON(UI);
    alignDeclarationNodeList_.emplace_front(node);
}

std::list<RefPtr<RenderNode>>& PipelineContext::GetAlignDeclarationNodeList()
{
    CHECK_RUN_ON(UI);
    return alignDeclarationNodeList_;
}

void PipelineContext::AddScreenOnEvent(std::function<void()>&& func)
{
    taskExecutor_->PostTask(
        [wp = WeakClaim(this), screenOnFunc = std::move(func)]() mutable {
            auto pipeline = wp.Upgrade();
            if (pipeline && pipeline->screenOnCallback_) {
                pipeline->screenOnCallback_(std::move(screenOnFunc));
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIScreenOnEvent",
        TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
}

void PipelineContext::AddScreenOffEvent(std::function<void()>&& func)
{
    taskExecutor_->PostTask(
        [wp = WeakClaim(this), screenOffFunc = std::move(func)]() mutable {
            auto pipeline = wp.Upgrade();
            if (pipeline && pipeline->screenOffCallback_) {
                pipeline->screenOffCallback_(std::move(screenOffFunc));
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIScreenOffEvent",
        TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
}

bool PipelineContext::IsWindowInScreen()
{
    if (queryIfWindowInScreenCallback_) {
        // We post an async task to do async query to avoid thread deadlock between UI thread and Platform thread
        taskExecutor_->PostTask(
            [wp = WeakClaim(this)] {
                auto pipeline = wp.Upgrade();
                if (!pipeline) {
                    return;
                }
                pipeline->queryIfWindowInScreenCallback_();
            },
            TaskExecutor::TaskType::PLATFORM, "ArkUIQueryIfWindowInScreen",
            TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
    }
    // Note that the result is not real-time result but the result from previous query
    return isWindowInScreen_;
}

void PipelineContext::NotifyOnPreDraw()
{
    decltype(nodesToNotifyOnPreDraw_) nodesToNotifyOnPreDraw(std::move(nodesToNotifyOnPreDraw_));
    for (const auto& node : nodesToNotifyOnPreDraw) {
        node->OnPreDraw();
    }
}

void PipelineContext::AddNodesToNotifyOnPreDraw(const RefPtr<RenderNode>& renderNode)
{
    nodesToNotifyOnPreDraw_.emplace(renderNode);
}

void PipelineContext::UpdateNodesNeedDrawOnPixelMap()
{
    for (const auto& dirtyNode : dirtyRenderNodes_) {
        SearchNodesNeedDrawOnPixelMap(dirtyNode);
    }
    for (const auto& dirtyNode : dirtyRenderNodesInOverlay_) {
        SearchNodesNeedDrawOnPixelMap(dirtyNode);
    }
}

void PipelineContext::SearchNodesNeedDrawOnPixelMap(const RefPtr<RenderNode>& renderNode)
{
    auto parent = renderNode;
    while (parent) {
        auto box = AceType::DynamicCast<RenderBox>(parent);
        if (box && box->GetPixelMap()) {
            nodesNeedDrawOnPixelMap_.emplace(parent);
        }
        parent = parent->GetParent().Upgrade();
    }
}

void PipelineContext::NotifyDrawOnPixelMap()
{
    decltype(nodesNeedDrawOnPixelMap_) nodesNeedDrawOnPixelMap(std::move(nodesNeedDrawOnPixelMap_));
    for (const auto& node : nodesNeedDrawOnPixelMap) {
        auto box = AceType::DynamicCast<RenderBox>(node);
        if (box) {
            box->DrawOnPixelMap();
        }
    }
}

void PipelineContext::PushVisibleCallback(NodeId id, double ratio, std::function<void(bool, double)>&& func)
{
    auto accessibilityManager = GetAccessibilityManager();
    if (!accessibilityManager) {
        return;
    }
    accessibilityManager->AddVisibleChangeNode(id, ratio, func);
}

void PipelineContext::AddVisibleAreaChangeNode(
    const ComposeId& nodeId, double ratio, const VisibleRatioCallback& callback)
{
    VisibleCallbackInfo info;
    info.callback = callback;
    info.visibleRatio = ratio;
    info.isCurrentVisible = false;
    auto iter = visibleAreaChangeNodes_.find(nodeId);
    if (iter != visibleAreaChangeNodes_.end()) {
        auto& callbackList = iter->second;
        callbackList.emplace_back(info);
    } else {
        std::list<VisibleCallbackInfo> callbackList;
        callbackList.emplace_back(info);
        visibleAreaChangeNodes_[nodeId] = callbackList;
    }
}

void PipelineContext::RemoveVisibleChangeNode(NodeId id)
{
    auto accessibilityManager = GetAccessibilityManager();
    if (!accessibilityManager) {
        return;
    }
    accessibilityManager->RemoveVisibleChangeNode(id);
}

bool PipelineContext::IsVisibleChangeNodeExists(NodeId index) const
{
    auto accessibilityManager = GetAccessibilityManager();
    if (!accessibilityManager) {
        return false;
    }
    return accessibilityManager->IsVisibleChangeNodeExists(index);
}

void PipelineContext::SetRSUIDirector(std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUIDirector)
{
#ifdef ENABLE_ROSEN_BACKEND
    rsUIDirector_ = rsUIDirector;
#endif
}

std::shared_ptr<OHOS::Rosen::RSUIDirector> PipelineContext::GetRSUIDirector()
{
#ifdef ENABLE_ROSEN_BACKEND
    return rsUIDirector_;
#else
    return nullptr;
#endif
}

void PipelineContext::StoreNode(int32_t restoreId, const WeakPtr<RenderElement>& node)
{
    auto ret = storeNode_.try_emplace(restoreId, node);
    if (!ret.second) {
        LOGW("store restore node fail, id = %{public}d", restoreId);
        storeNode_[restoreId] = node;
    }
}

std::unique_ptr<JsonValue> PipelineContext::GetStoredNodeInfo()
{
    auto jsonNodeInfo = JsonUtil::Create(true);
    auto iter = storeNode_.begin();
    while (iter != storeNode_.end()) {
        auto RenderElement = (iter->second).Upgrade();
        if (RenderElement) {
            std::string info = RenderElement->ProvideRestoreInfo();
            if (!info.empty()) {
                jsonNodeInfo->Put(std::to_string(iter->first).c_str(), info.c_str());
            }
        }
        ++iter;
    }
    return jsonNodeInfo;
}

void PipelineContext::RestoreNodeInfo(std::unique_ptr<JsonValue> nodeInfo)
{
    if (!nodeInfo->IsValid() || !nodeInfo->IsObject()) {
        LOGW("restore nodeInfo is invalid");
    }
    auto child = nodeInfo->GetChild();
    while (child->IsValid()) {
        auto key = child->GetKey();
        auto value = child->GetString();
        int vital = std::atoi(key.c_str());
        if (vital == 0) {
            LOGE("input %{public}s can not be converted to number.", key.c_str());
        }
        restoreNodeInfo_.try_emplace(vital, value);
        child = child->GetNext();
    }
}

std::string PipelineContext::GetRestoreInfo(int32_t restoreId)
{
    auto iter = restoreNodeInfo_.find(restoreId);
    if (iter != restoreNodeInfo_.end()) {
        std::string restoreNodeInfo = iter->second;
        restoreNodeInfo_.erase(iter);
        return restoreNodeInfo;
    }
    return "";
}

void PipelineContext::SetSinglePageId(int32_t pageId)
{
    auto stageElement = GetStageElement();
    if (!stageElement) {
        LOGE("Get stage element failed!");
        return;
    }

    stageElement->SetSinglePageId(pageId);
}

void PipelineContext::SetAppTitle(const std::string& title)
{
    CHECK_NULL_VOID(rootElement_);
    auto containerModalElement = AceType::DynamicCast<ContainerModalElement>(rootElement_->GetFirstChild());
    CHECK_NULL_VOID(containerModalElement);
    containerModalElement->SetAppTitle(title);
}

void PipelineContext::SetAppIcon(const RefPtr<PixelMap>& icon)
{
    CHECK_NULL_VOID(rootElement_);
    auto containerModalElement = AceType::DynamicCast<ContainerModalElement>(rootElement_->GetFirstChild());
    CHECK_NULL_VOID(containerModalElement);
    containerModalElement->SetAppIcon(icon);
}

} // namespace OHOS::Ace
