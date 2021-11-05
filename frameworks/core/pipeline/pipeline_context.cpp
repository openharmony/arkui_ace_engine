/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include <utility>

#include "base/log/ace_trace.h"
#include "base/log/dump_log.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "base/thread/task_executor.h"
#include "base/utils/macros.h"
#include "base/utils/string_utils.h"
#include "core/animation/card_transition_controller.h"
#include "core/animation/shared_transition_controller.h"
#include "core/common/ace_application_info.h"
#include "core/common/ace_engine.h"
#include "core/common/event_manager.h"
#include "core/common/font_manager.h"
#include "core/common/frontend.h"
#include "core/common/manager_interface.h"
#include "core/common/thread_checker.h"
#include "core/components/checkable/render_checkable.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/custom_paint/offscreen_canvas.h"
#include "core/components/custom_paint/render_custom_paint.h"
#include "core/components/dialog/dialog_component.h"
#include "core/components/dialog/dialog_element.h"
#include "core/components/dialog_modal/dialog_modal_component.h"
#include "core/components/dialog_modal/dialog_modal_element.h"
#include "core/components/display/display_component.h"
#include "core/components/focus_animation/render_focus_animation.h"
#include "core/components/overlay/overlay_component.h"
#include "core/components/overlay/overlay_element.h"
#include "core/components/page/page_element.h"
#include "core/components/page_transition/page_transition_component.h"
#include "core/components/root/render_root.h"
#include "core/components/root/root_component.h"
#include "core/components/root/root_element.h"
#include "core/components/scroll/scrollable.h"
#include "core/components/semi_modal/semi_modal_component.h"
#include "core/components/semi_modal/semi_modal_element.h"
#include "core/components/theme/app_theme.h"
#include "core/components/stage/stage_component.h"
#include "core/components/stage/stage_element.h"
#include "core/image/image_provider.h"
#include "core/pipeline/base/composed_element.h"
#include "core/pipeline/base/factories/flutter_render_factory.h"
#include "core/pipeline/base/render_context.h"

namespace OHOS::Ace {
namespace {

constexpr int64_t SEC_TO_NANOSEC = 1000000000;
constexpr int32_t MOUSE_PRESS_LEFT = 1;
constexpr char JS_THREAD_NAME[] = "JS";
constexpr char UI_THREAD_NAME[] = "UI";
constexpr int32_t DEFAULT_VIEW_SCALE = 1;

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

RefPtr<OffscreenCanvas> PipelineContext::CreateOffscreenCanvas(int32_t width, int32_t height)
{
    return RenderOffscreenCanvas::Create(AceType::WeakClaim(this), width, height);
}

PipelineContext::PipelineContext(std::unique_ptr<Window> window, RefPtr<TaskExecutor> taskExecutor,
    RefPtr<AssetManager> assetManager, RefPtr<PlatformResRegister> platformResRegister,
    const RefPtr<Frontend>& frontend, int32_t instanceId)
    : window_(std::move(window)), taskExecutor_(std::move(taskExecutor)), assetManager_(std::move(assetManager)),
      platformResRegister_(std::move(platformResRegister)), weakFrontend_(frontend),
      timeProvider_(g_defaultTimeProvider), instanceId_(instanceId)
{
    frontendType_ = frontend->GetType();
    RegisterEventHandler(frontend->GetEventHandler());
    auto&& vsyncCallback = [weak = AceType::WeakClaim(this)](const uint64_t nanoTimestamp, const uint32_t frameCount) {
        auto context = weak.Upgrade();
        if (context) {
            context->OnVsyncEvent(nanoTimestamp, frameCount);
        }
    };
    ACE_DCHECK(window_);
    window_->SetVsyncCallback(vsyncCallback);
    focusAnimationManager_ = AceType::MakeRefPtr<FocusAnimationManager>();
    sharedTransitionController_ = AceType::MakeRefPtr<SharedTransitionController>(AceType::WeakClaim(this));
    cardTransitionController_ = AceType::MakeRefPtr<CardTransitionController>(AceType::WeakClaim(this));
    if (frontend->GetType() != FrontendType::JS_CARD) {
        imageCache_ = ImageCache::Create();
    }
    fontManager_ = FontManager::Create();
    renderFactory_ = AceType::MakeRefPtr<FlutterRenderFactory>();
    UpdateFontWeightScale();
}

PipelineContext::PipelineContext(std::unique_ptr<Window> window, RefPtr<TaskExecutor>& taskExecutor,
    RefPtr<AssetManager> assetManager, const RefPtr<Frontend>& frontend)
    : window_(std::move(window)), taskExecutor_(taskExecutor), assetManager_(std::move(assetManager)),
      weakFrontend_(frontend), timeProvider_(g_defaultTimeProvider)
{
    frontendType_ = frontend->GetType();

    RegisterEventHandler(frontend->GetEventHandler());
    auto&& vsyncCallback = [weak = AceType::WeakClaim(this)](const uint64_t nanoTimestamp, const uint32_t frameCount) {
        auto context = weak.Upgrade();
        if (context) {
            context->OnVsyncEvent(nanoTimestamp, frameCount);
        }
    };
    ACE_DCHECK(window_);
    window_->SetVsyncCallback(vsyncCallback);

    focusAnimationManager_ = AceType::MakeRefPtr<FocusAnimationManager>();
    sharedTransitionController_ = AceType::MakeRefPtr<SharedTransitionController>(AceType::WeakClaim(this));
    cardTransitionController_ = AceType::MakeRefPtr<CardTransitionController>(AceType::WeakClaim(this));
    fontManager_ = FontManager::Create();
    renderFactory_ = AceType::MakeRefPtr<FlutterRenderFactory>();
    UpdateFontWeightScale();
}

PipelineContext::~PipelineContext()
{
    LOG_DESTROY();
}

void PipelineContext::FlushPipelineWithoutAnimation()
{
    FlushBuild();
    FlushPostAnimation();
    FlushLayout();
    FlushRender();
    FlushRenderFinish();
    FlushWindowBlur();
    FlushFocus();
    FireVisibleChangeEvent();
    ProcessPostFlush();
    ClearDeactivateElements();
}

void PipelineContext::FlushBuild()
{
    ACE_FUNCTION_TRACE();
    CHECK_RUN_ON(UI);

    if (dirtyElements_.empty()) {
        return;
    }
    if (isFirstLoaded_) {
        LOGI("PipelineContext::FlushBuild()");
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
    if (!buildAfterCallback_.empty()) {
        for (const auto& item : buildAfterCallback_) {
            item();
        }
        buildAfterCallback_.clear();
    }
    buildingFirstPage_ = false;
}

void PipelineContext::FlushPredictLayout(int64_t targetTimestamp)
{
    CHECK_RUN_ON(UI);
    if (predictLayoutNodes_.empty()) {
        return;
    }
    ACE_FUNCTION_TRACE();
    decltype(predictLayoutNodes_) dirtyNodes(std::move(predictLayoutNodes_));
    for (const auto& dirtyNode : dirtyNodes) {
        dirtyNode->OnPredictLayout(targetTimestamp);
    }
}

void PipelineContext::FlushFocus()
{
    CHECK_RUN_ON(UI);
    if (dirtyFocusNode_) {
        dirtyFocusNode_->RequestFocusImmediately();
        dirtyFocusNode_.Reset();
        dirtyFocusScope_.Reset();
        return;
    }

    if (dirtyFocusScope_) {
        dirtyFocusScope_->RequestFocusImmediately();
        dirtyFocusScope_.Reset();
        return;
    }

    if (rootElement_ && !rootElement_->IsCurrentFocus()) {
        rootElement_->RequestFocusImmediately();
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
    auto accessibilityManager = GetAccessibilityManager();
    if (accessibilityManager) {
        accessibilityManager->TriggerVisibleChangeEvent();
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

RefPtr<StageElement> PipelineContext::GetStageElement() const
{
    CHECK_RUN_ON(UI);
    if (!rootElement_) {
        LOGE("Root element is null!");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return RefPtr<StageElement>();
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
    } else {
        auto stack = rootElement_->GetFirstChild();
        if (stack) {
            return AceType::DynamicCast<StageElement>(stack->GetFirstChild());
        }
    }
    LOGE("Get stage element failed.");
    EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
    return RefPtr<StageElement>();
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

    LOGD("Get stage element child size:%zu", stageElement->GetChildrenList().size());
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
    ACE_FUNCTION_TRACE();

    if (dirtyLayoutNodes_.empty()) {
        return;
    }
    if (isFirstLoaded_) {
        LOGI("PipelineContext::FlushLayout()");
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
    ACE_FUNCTION_TRACE();

    if (dirtyRenderNodes_.empty() && dirtyRenderNodesInOverlay_.empty() && !needForcedRefresh_) {
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
            LOGI("PipelineContext::FlushRender()");
            isFirstLoaded_ = false;
        }
    }
    needForcedRefresh_ = false;
}

void PipelineContext::FlushRenderFinish()
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACE();

    if (!needPaintFinishNodes_.empty()) {
        decltype(needPaintFinishNodes_) Nodes(std::move(needPaintFinishNodes_));
        for (const auto& node : Nodes) {
            node->OnPaintFinish();
        }
    }
}

void PipelineContext::FlushAnimation(uint64_t nanoTimestamp)
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACE();
    flushAnimationTimestamp_ = nanoTimestamp;
    isFlushingAnimation_ = true;

    ProcessPreFlush();
    if (scheduleTasks_.empty()) {
        isFlushingAnimation_ = false;
        return;
    }
    decltype(scheduleTasks_) temp(std::move(scheduleTasks_));
    for (const auto& scheduleTask : temp) {
        scheduleTask.second->OnFrame(nanoTimestamp);
    }
    isFlushingAnimation_ = false;
}

void PipelineContext::FlushPostAnimation()
{
    CHECK_RUN_ON(UI);
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
    if (animationCallback_) {
        taskExecutor_->PostTask(animationCallback_, TaskExecutor::TaskType::JS);
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
    ACE_FUNCTION_TRACE();

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

RefPtr<Element> PipelineContext::SetupRootElement()
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

    auto stack = AceType::MakeRefPtr<StackComponent>(Alignment::TOP_LEFT, StackFit::INHERIT,
        Overflow::OBSERVABLE, std::list<RefPtr<Component>>());
    auto overlay = AceType::MakeRefPtr<OverlayComponent>(std::list<RefPtr<Component>>());
    overlay->SetTouchable(false);
    stack->AppendChild(rootStage);
    stack->AppendChild(overlay);
    RefPtr<RootComponent> rootComponent;
    if (windowModal_ == WindowModal::SEMI_MODAL || windowModal_ == WindowModal::SEMI_MODAL_FULL_SCREEN) {
        auto semiModal = SemiModalComponent::Create(
            stack, windowModal_ == WindowModal::SEMI_MODAL_FULL_SCREEN, modalHeight_, modalColor_);
        rootComponent = RootComponent::Create(semiModal);
    } else if (windowModal_ == WindowModal::DIALOG_MODAL) {
        rootStage->SetMainStackSize(MainStackSize::MAX);
        rootStage->SetAlignment(Alignment::BOTTOM_LEFT);
        auto dialogModal = DialogModalComponent::Create(stack);
        rootComponent = RootComponent::Create(dialogModal);
    } else {
        rootComponent = RootComponent::Create(stack);
    }
    rootElement_ = rootComponent->SetupElementTree(AceType::Claim(this));
    if (!rootElement_) {
        LOGE("SetupRootElement failed!");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return RefPtr<Element>();
    }
    const auto& rootRenderNode = rootElement_->GetRenderNode();
    window_->SetRootRenderNode(rootRenderNode);
    sharedTransitionController_->RegisterTransitionListener();
    cardTransitionController_->RegisterTransitionListener();
    if (windowModal_ == WindowModal::DIALOG_MODAL) {
        auto dialog = AceType::DynamicCast<DialogModalElement>(rootElement_->GetFirstChild());
        if (dialog) {
            dialog->RegisterTransitionListener();
        }
    }

    requestedRenderNode_.Reset();
    LOGI("SetupRootElement success!");
    return rootElement_;
}

void PipelineContext::Dump(const std::vector<std::string>& params) const
{
    if (params.empty()) {
        LOGW("params is empty now, it's illegal!");
        return;
    }

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
    } else if (params[0] == "-frontend") {
        DumpFrontend();
#ifndef WEARABLE_PRODUCT
    } else if (params[0] == "-multimodal") {
        multiModalManager_->DumpMultimodalScene();
#endif
#ifdef ACE_MEMORY_MONITOR
    } else if (params[0] == "-memory") {
        MemoryMonitor::GetInstance().Dump();
#endif
    } else if (params[0] == "-accessibility") {
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
    } else if (params[0] == "-hiviewreport" && params.size() >= 3) {
        DumpLog::GetInstance().Print("Report hiview event. EventType: " + params[1] + ", error type: " + params[2]);
        EventInfo eventInfo = { .eventType = params[1], .errorType = StringUtils::StringToInt(params[2]) };
        EventReport::SendEvent(eventInfo);
    } else if (params[0] == "-threadstuck" && params.size() >= 3) {
        MakeThreadStuck(params);
    } else if (params[0] == "-jscrash") {
        EventReport::JsErrReport(
            AceApplicationInfo::GetInstance().GetPackageName(), "js crash reason", "js crash summary");
    } else {
        DumpLog::GetInstance().Print("Error: Unsupported dump params!");
    }
}

RefPtr<StackElement> PipelineContext::GetLastStack() const
{
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

void PipelineContext::AddRouterChangeCallback(const OnRouterChangeCallback& onRouterChangeCallback)
{
    OnRouterChangeCallback_ = onRouterChangeCallback;
}

void PipelineContext::onRouterChange(const std::string url)
{
    if (OnRouterChangeCallback_ != nullptr) {
        OnRouterChangeCallback_(url);
#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
        currentUrl_ = url;
#endif
    }
}

bool PipelineContext::CanPushPage()
{
    auto stageElement = GetStageElement();
    return stageElement && stageElement->CanPushPage();
}

void PipelineContext::PushPage(const RefPtr<PageComponent>& pageComponent, const RefPtr<StageElement>& stage)
{
    ACE_FUNCTION_TRACE();
    CHECK_RUN_ON(UI);
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
        LOGD("push page with transition.");
        stageElement->PushPage(pageComponent);
    } else {
        LOGD("push page without transition, do not support transition.");
        RefPtr<DisplayComponent> display = AceType::MakeRefPtr<DisplayComponent>(pageComponent);
        stageElement->PushPage(display);
    }
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
    if (GetIsDeclarative()) {
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

RefPtr<DialogComponent> PipelineContext::ShowDialog(const DialogProperties& dialogProperties, bool isRightToLeft)
{
    CHECK_RUN_ON(UI);
    const auto& dialog = DialogBuilder::Build(dialogProperties, AceType::WeakClaim(this));
    if (!dialog) {
        return nullptr;
    }
    auto customComponent = dialogProperties.customComponent;
    if (customComponent) {
        dialog->SetCustomChild(customComponent);
    }
    dialog->SetTextDirection(isRightToLeft ? TextDirection::RTL : TextDirection::LTR);
    const auto& lastStack = GetLastStack();
    if (!lastStack) {
        return nullptr;
    }
    lastStack->PushDialog(dialog);
    return dialog;
}

bool PipelineContext::CanPopPage()
{
    auto stageElement = GetStageElement();
    return stageElement && stageElement->CanPopPage();
}

void PipelineContext::PopPage()
{
    LOGD("PopPageComponent");
    CHECK_RUN_ON(UI);
    auto stageElement = GetStageElement();
    if (stageElement) {
        stageElement->Pop();
    }
    ExitAnimation();
}

void PipelineContext::PopToPage(int32_t pageId)
{
    LOGD("PopToPageComponent: page-%{public}d", pageId);
    CHECK_RUN_ON(UI);
    auto stageElement = GetStageElement();
    if (stageElement) {
        stageElement->PopToPage(pageId);
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

void PipelineContext::ReplacePage(const RefPtr<PageComponent>& pageComponent, const RefPtr<StageElement>& stage)
{
    LOGD("ReplacePageComponent");
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
        LOGD("replace page with transition.");
        stageElement->Replace(pageComponent);
    } else {
        LOGD("replace page without transition, do not support transition.");
        RefPtr<DisplayComponent> display = AceType::MakeRefPtr<DisplayComponent>(pageComponent);
        stageElement->Replace(display);
    }
}

void PipelineContext::ReplacePage(const RefPtr<PageComponent>& pageComponent)
{
    ReplacePage(pageComponent, nullptr);
}

bool PipelineContext::ClearInvisiblePages()
{
    LOGD("ClearInvisiblePageComponents");
    auto stageElement = GetStageElement();
    return stageElement && stageElement->ClearOffStage();
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
                TaskExecutor::TaskType::UI);
        } else {
            // return back to desktop
            Finish();
        }
    }
}

// return true if user accept or page is not last, return false if others condition
bool PipelineContext::CallRouterBackToPopPage()
{
    LOGD("CallRouterBackToPopPage");
    auto frontend = weakFrontend_.Upgrade();
    if (!frontend) {
        // return back to desktop
        return false;
    }

    if (frontend->OnBackPressed()) {
        // if user accept
        return true;
    } else {
        frontend->CallRouterBack();
        return true;
    }
}

void PipelineContext::NotifyAppStorage(const std::string& key, const std::string& value)
{
    LOGD("NotifyAppStorage");
    auto frontend = weakFrontend_.Upgrade();
    if (!frontend) {
        return;
    }
    frontend->NotifyAppStorage(key, value);
}

void PipelineContext::ScheduleUpdate(const RefPtr<ComposedComponent>& compose)
{
    CHECK_RUN_ON(UI);
    ComposeId id = compose->GetId();
    LOGD("update compose for id:%{public}s", id.c_str());
    const auto& it = composedElementMap_.find(id);
    if (it == composedElementMap_.end()) {
        LOGD("can't update composed for id:%{public}s, name:%{public}s", id.c_str(), compose->GetName().c_str());
    } else {
        for (const auto& composedElement : it->second) {
            composedElement->SetUpdateComponent(compose);
        }
    }
    FlushBuildAndLayoutBeforeSurfaceReady();
}

void PipelineContext::AddComposedElement(const ComposeId& id, const RefPtr<ComposedElement>& element)
{
    CHECK_RUN_ON(UI);
    LOGD("add new composed element id:%{public}s", id.c_str());
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
    LOGD("remove composed element id:%{public}s", id.c_str());
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
    LOGD("schedule rebuild for %{public}s", AceType::TypeName(dirtyElement));
    dirtyElements_.emplace(dirtyElement);
    hasIdleTasks_ = true;
    window_->RequestFrame();
}

void PipelineContext::RequestFrame()
{
    window_->RequestFrame();
}

void PipelineContext::AddNeedRebuildFocusElement(const RefPtr<Element>& focusElement)
{
    CHECK_RUN_ON(UI);
    if (!focusElement) {
        LOGW("focusElement is null");
        return;
    }
    LOGD("schedule rebuild focus element for %{public}s", AceType::TypeName(focusElement));
    needRebuildFocusElement_.emplace(focusElement);
}

void PipelineContext::AddDirtyRenderNode(const RefPtr<RenderNode>& renderNode, bool overlay)
{
    CHECK_RUN_ON(UI);
    if (!renderNode) {
        LOGW("renderNode is null");
        return;
    }
    LOGD("schedule render for %{public}s", AceType::TypeName(renderNode));
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
    LOGD("schedule render for %{public}s", AceType::TypeName(renderNode));
    needPaintFinishNodes_.emplace(renderNode);
}

void PipelineContext::AddDirtyLayoutNode(const RefPtr<RenderNode>& renderNode)
{
    CHECK_RUN_ON(UI);
    if (!renderNode) {
        LOGW("renderNode is null");
        return;
    }
    LOGD("schedule layout for %{public}s", AceType::TypeName(AceType::RawPtr(renderNode)));
    renderNode->SaveExplicitAnimationOption(explicitAnimationOption_);
    dirtyLayoutNodes_.emplace(renderNode);
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
    LOGD("schedule predict layout for %{public}s", AceType::TypeName(renderNode));
    predictLayoutNodes_.emplace(renderNode);
    hasIdleTasks_ = true;
    window_->RequestFrame();
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
    LOGD("add requested rotation node, type is %{public}s", node->TypeName());
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

RefPtr<RenderNode> PipelineContext::DragTestAll(const TouchPoint& point)
{
    return DragTest(point, rootElement_->GetRenderNode(), 0);
}

RefPtr<RenderNode> PipelineContext::DragTest(
    const TouchPoint& point, const RefPtr<RenderNode>& renderNode, int32_t deep)
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

void PipelineContext::OnTouchEvent(const TouchPoint& point)
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACE();
    if (!rootElement_) {
        LOGE("root element is nullptr");
        return;
    }
    auto scalePoint = point.CreateScalePoint(viewScale_);
    LOGD("OnTouchEvent: x = %{public}f, y = %{public}f, type = %{public}zu", scalePoint.x, scalePoint.y,
        scalePoint.type);
    if (scalePoint.type == TouchType::DOWN) {
        LOGD("receive touch down event, first use touch test to collect touch event target");
        TouchRestrict touchRestrict { TouchRestrict::NONE };
        auto frontEnd = GetFrontend();
        if (frontEnd && (frontEnd->GetType() == FrontendType::JS_CARD)) {
            touchRestrict.UpdateForbiddenType(TouchRestrict::LONG_PRESS);
        }
        eventManager_.TouchTest(scalePoint, rootElement_->GetRenderNode(), touchRestrict);
    }
    if (scalePoint.type == TouchType::MOVE) {
        isMoving_ = true;
    }
    if (isKeyEvent_) {
        SetIsKeyEvent(false);
    }
    eventManager_.DispatchTouchEvent(scalePoint);
}

bool PipelineContext::OnKeyEvent(const KeyEvent& event)
{
    CHECK_RUN_ON(UI);
    if (!rootElement_) {
        LOGE("the root element is nullptr");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return false;
    }
    if (!isKeyEvent_ && SystemProperties::GetDeviceType() == DeviceType::PHONE) {
        if (KeyCode::KEYBOARD_UP <= event.code && event.code <= KeyCode::KEYBOARD_RIGHT) {
            if (event.action == KeyAction::UP) {
                SetIsKeyEvent(true);
            }
            return true;
        } else if (event.code == KeyCode::KEYBOARD_ENTER) {
            if (event.action == KeyAction::CLICK) {
                SetIsKeyEvent(true);
            }
        }
    }
    rootElement_->HandleSpecifiedKey(event);
    NotifyDestroyEventDismiss();
    return eventManager_.DispatchKeyEvent(event, rootElement_);
}

void PipelineContext::OnMouseEvent(const MouseEvent& event)
{
    CHECK_RUN_ON(UI);
    LOGD("OnMouseEvent: x=%{public}f, y=%{public}f, type=%{public}d. button=%{public}d, pressbutton=%{public}d}",
        event.x, event.y, event.action, event.button, event.pressedButtons);

    auto touchPoint = event.CreateTouchPoint();
    if ((event.action == MouseAction::RELEASE || event.action == MouseAction::PRESS ||
            event.action == MouseAction::MOVE) &&
        (event.button == MouseButton::LEFT_BUTTON || event.pressedButtons == MOUSE_PRESS_LEFT)) {
        OnTouchEvent(touchPoint);
    }
    auto scaleEvent = event.CreateScaleEvent(viewScale_);
    eventManager_.MouseTest(scaleEvent, rootElement_->GetRenderNode());
    eventManager_.DispatchMouseEvent(scaleEvent);
    int32_t preHoverId = hoverNodeId_;
    std::list<RefPtr<RenderNode>> preHoverNodes;
    preHoverNodes.assign(hoverNodes_.begin(), hoverNodes_.end());
    // clear current hover node id and list.
    hoverNodeId_ = DEFAULT_HOVER_ENTER_ANIMATION_ID;
    hoverNodes_.clear();
    eventManager_.MouseHoverTest(scaleEvent, rootElement_->GetRenderNode());
    if (preHoverId != hoverNodeId_) {
        // Send Hover Exit Animation event to preHoverNodes.
        for (const auto& exitNode : preHoverNodes) {
            exitNode->OnMouseHoverExitAnimation();
        }
        // Send Hover Enter Animation event to curHoverNodes.
        for (const auto& enterNode : hoverNodes_) {
            enterNode->OnMouseHoverEnterAnimation();
        }
    } else {
        HandleMouseInputEvent(event);
    }
    if (touchPoint.type == TouchType::DOWN) {
        for (const auto& enterNode : hoverNodes_) {
            enterNode->OnMouseClickDownAnimation();
        }
    }
    if (touchPoint.type == TouchType::UP) {
        for (const auto& enterNode : hoverNodes_) {
            enterNode->OnMouseClickUpAnimation();
        }
    }
}

void PipelineContext::HandleMouseInputEvent(const MouseEvent& event)
{
    if (event.action == MouseAction::HOVER_EXIT) {
        for (const auto& exitNode : hoverNodes_) {
            exitNode->OnMouseHoverExitAnimation();
        }
    }
    if (event.action == MouseAction::PRESS) {
        for (const auto& exitNode : hoverNodes_) {
            exitNode->StopMouseHoverAnimation();
        }
    }
    if (event.action == MouseAction::HOVER_ENTER) {
        for (const auto& enterNode : hoverNodes_) {
            enterNode->OnMouseHoverEnterAnimation();
        }
    }
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

    return eventManager_.DispatchRotationEvent(event, stackRenderNode, requestedRenderNode_.Upgrade());
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

void PipelineContext::OnVsyncEvent(uint64_t nanoTimestamp, uint32_t frameCount)
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACE();

#if defined(ENABLE_NATIVE_VIEW)
    if (frameCount_ < 2) {
        frameCount_++;
    }
#endif

    if (isSurfaceReady_) {
        FlushAnimation(GetTimeFromExternalTimer());
        FlushPipelineWithoutAnimation();
        FlushAnimationTasks();
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

void PipelineContext::OnActionEvent(const std::string& action)
{
    CHECK_RUN_ON(UI);
    if (actionEventHandler_) {
        actionEventHandler_(action);
    } else {
        LOGE("the action event handler is null");
    }
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

RefPtr<Frontend> PipelineContext::GetFrontend() const
{
    return weakFrontend_.Upgrade();
}

void PipelineContext::OnSurfaceChanged(int32_t width, int32_t height)
{
    CHECK_RUN_ON(UI);
    // Refresh the screen when developers customize the resolution and screen density on the PC preview.
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
    if (width_ == width && height_ == height) {
        return;
    }
#endif

    for (auto&& [id, callback] : surfaceChangedCallbackMap_) {
        if (callback) {
            callback(width, height, width_, height_);
        }
    }

    width_ = width;
    height_ = height;

    ACE_SCOPED_TRACE("OnSurfaceChanged(%d, %d)", width, height);

    if (!NearZero(rootHeight_)) {
        double newRootHeight = height / viewScale_;
        double newRootWidth = width / viewScale_;
        double offsetHeight = rootHeight_ - newRootHeight;
        if (textFieldManager_ && GetLastPage()) {
            textFieldManager_->MovePage(GetLastPage()->GetPageId(), { newRootWidth, newRootHeight }, offsetHeight);
        }
    }
    GridSystemManager::GetInstance().OnSurfaceChanged(width);

    auto frontend = weakFrontend_.Upgrade();
    if (frontend) {
        frontend->OnSurfaceChanged(width, height);
    }

    // init transition clip size when surface changed.
    const auto& pageElement = GetLastPage();
    if (pageElement) {
        const auto& transitionElement = AceType::DynamicCast<PageTransitionElement>(pageElement->GetFirstChild());
        if (transitionElement) {
            transitionElement->InitTransitionClip();
        }
    }
    SetRootSizeWithWidthHeight(width, height);
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

void PipelineContext::OnSurfaceDensityChanged(double density)
{
    CHECK_RUN_ON(UI);
    ACE_SCOPED_TRACE("OnSurfaceDensityChanged(%lf)", density);

    density_ = density;
    if (!NearZero(viewScale_)) {
        dipScale_ = density_ / viewScale_;
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

double PipelineContext::NormalizeToPx(const Dimension& dimension) const
{
    if ((dimension.Unit() == DimensionUnit::VP) || (dimension.Unit() == DimensionUnit::FP)) {
        return (dimension.Value() * dipScale_);
    } else if (dimension.Unit() == DimensionUnit::LPX) {
        return (dimension.Value() * designWidthScale_);
    }
    return dimension.Value();
}

double PipelineContext::ConvertPxToVp(const Dimension& dimension) const
{
    if (dimension.Unit() == DimensionUnit::PX) {
        return dimension.Value() / dipScale_;
    }
    return dimension.Value();
}

void PipelineContext::SetRootSizeWithWidthHeight(int32_t width, int32_t height)
{
    CHECK_RUN_ON(UI);
    auto frontend = weakFrontend_.Upgrade();
    if (!frontend) {
        LOGE("the frontend is nullptr");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return;
    }
    auto& windowConfig = frontend->GetWindowConfig();
    if (windowConfig.designWidth <= 0) {
        LOGE("the frontend design width <= 0");
        return;
    }
    if (GetIsDeclarative()) {
        viewScale_ = DEFAULT_VIEW_SCALE;
        designWidthScale_ = static_cast<float>(width) / windowConfig.designWidth;
        windowConfig.designWidthScale = designWidthScale_;
    } else {
        viewScale_ = windowConfig.autoDesignWidth ? density_ : static_cast<float>(width) / windowConfig.designWidth;
        if (NearZero(viewScale_)) {
            LOGE("the view scale is zero");
            return;
        }
    }
    dipScale_ = density_ / viewScale_;
    rootHeight_ = height / viewScale_;
    rootWidth_ = width / viewScale_;
    SetRootRect(rootWidth_, rootHeight_);
    GridSystemManager::GetInstance().SetWindowInfo(rootWidth_, density_, dipScale_);
}

void PipelineContext::SetRootSize(double density, int32_t width, int32_t height)
{
    ACE_SCOPED_TRACE("SetRootSize(%lf, %d, %d)", density, width, height);

    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), density, width, height]() {
            auto context = weak.Upgrade();
            if (!context) {
                return;
            }
            context->density_ = density;
            context->SetRootSizeWithWidthHeight(width, height);
        },
        TaskExecutor::TaskType::UI);
}

void PipelineContext::SetRootRect(double width, double height) const
{
    CHECK_RUN_ON(UI);
    if (NearZero(viewScale_) || !rootElement_) {
        LOGE("the view scale is zero or root element is nullptr");
        return;
    }
    const Rect paintRect(0.0, 0.0, width, height);
    auto rootNode = AceType::DynamicCast<RenderRoot>(rootElement_->GetRenderNode());
    if (!rootNode) {
        return;
    }
    if (!NearEqual(viewScale_, rootNode->GetScale()) || paintRect != rootNode->GetPaintRect()) {
        if (!NearEqual(viewScale_, rootNode->GetScale())) {
            rootNode->SetReset(true);
        }
        rootNode->SetPaintRect(paintRect);
        rootNode->SetScale(viewScale_);
        rootNode->MarkNeedLayout();
        rootNode->MarkNeedRender();
        focusAnimationManager_->SetAvailableRect(paintRect);
    }
}

void PipelineContext::SetRootBgColor(const Color& color)
{
    rootBgColor_ = color;
    auto appTheme = themeManager_->GetTheme<AppTheme>();
    appTheme->SetBackgroundColor(color);
    if (rootElement_) {
        auto renderRoot = DynamicCast<RenderRoot>(rootElement_->GetRenderNode());
        if (renderRoot) {
            renderRoot->SetBgColor(color);
        }
    }
}

void PipelineContext::Finish(bool autoFinish) const
{
    CHECK_RUN_ON(UI);
    LOGD("finish current pipeline context, auto: %{public}d, root empty: %{public}d", autoFinish, !!rootElement_);
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
    LOGD("Request full window.");
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

void PipelineContext::NotifyStatusBarBgColor(const Color& color) const
{
    CHECK_RUN_ON(UI);
    LOGD("Notify StatusBar BgColor, color: %{public}x", color.GetValue());
    if (statusBarBgColorEventHandler_) {
        statusBarBgColorEventHandler_(color);
    } else {
        LOGE("fail to finish current context due to handler is nullptr");
    }
}

void PipelineContext::NotifyPopupDismiss() const
{
    CHECK_RUN_ON(UI);
    if (popupEventHandler_) {
        popupEventHandler_();
    }
}

void PipelineContext::NotifyRouterBackDismiss() const
{
    if (routerBackEventHandler_) {
        routerBackEventHandler_();
    }
}

void PipelineContext::NotifyPopPageSuccessDismiss(const std::string& pageUrl, const int32_t pageId) const
{
    CHECK_RUN_ON(UI);
    for (auto& iterPopSuccessHander : popPageSuccessEventHandler_) {
        if (iterPopSuccessHander) {
            iterPopSuccessHander(pageUrl, pageId);
        }
    }
}

void PipelineContext::NotifyIsPagePathInvalidDismiss(bool isPageInvalid) const
{
    CHECK_RUN_ON(UI);
    for (auto& iterPathInvalidHandler : isPagePathInvalidEventHandler_) {
        if (iterPathInvalidHandler) {
            iterPathInvalidHandler(isPageInvalid);
        }
    }
}

void PipelineContext::NotifyDestroyEventDismiss() const
{
    CHECK_RUN_ON(UI);
    for (auto& iterDestroyEventHander : destroyEventHandler_) {
        if (iterDestroyEventHander) {
            iterDestroyEventHander();
        }
    }
}

void PipelineContext::NotifyDispatchTouchEventDismiss(const TouchPoint& event) const
{
    CHECK_RUN_ON(UI);
    for (auto& iterDispatchTouchEventHander : dispatchTouchEventHandler_) {
        if (iterDispatchTouchEventHander) {
            iterDispatchTouchEventHander(event);
        }
    }
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
        dirtyFocusNode_ = node;
    } else {
        dirtyFocusScope_ = node;
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

void PipelineContext::ClearImageCache()
{
    if (imageCache_) {
        imageCache_->Clear();
    }
}

RefPtr<ImageCache> PipelineContext::GetImageCache() const
{
    return imageCache_;
}

void PipelineContext::Destroy()
{
    CHECK_RUN_ON(UI);
    LOGI("PipelineContext::Destroy begin.");
    ClearImageCache();
    rootElement_.Reset();
    composedElementMap_.clear();
    dirtyElements_.clear();
    deactivateElements_.clear();
    dirtyRenderNodes_.clear();
    dirtyRenderNodesInOverlay_.clear();
    dirtyLayoutNodes_.clear();
    predictLayoutNodes_.clear();
    dirtyFocusNode_.Reset();
    dirtyFocusScope_.Reset();
    postFlushListeners_.clear();
    postAnimationFlushListeners_.clear();
    preFlushListeners_.clear();
    needPaintFinishNodes_.clear();
    sharedTransitionController_.Reset();
    cardTransitionController_.Reset();
    while (!pageUpdateTasks_.empty()) {
        pageUpdateTasks_.pop();
    }
    alignDeclarationNodeList_.clear();
    hoverNodes_.clear();
    drawDelegate_.reset();
    renderFactory_.Reset();
    window_->Destroy();
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

RefPtr<AccessibilityManager> PipelineContext::GetAccessibilityManager() const
{
    auto frontend = weakFrontend_.Upgrade();
    if (!frontend) {
        LOGE("frontend is nullptr");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return nullptr;
    }
    return frontend->GetAccessibilityManager();
}

void PipelineContext::SendEventToAccessibility(const AccessibilityEvent& accessibilityEvent)
{
    auto accessibilityManager = GetAccessibilityManager();
    if (!accessibilityManager) {
        return;
    }
    accessibilityManager->SendAccessibilityAsyncEvent(accessibilityEvent);
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

void PipelineContext::RegisterFont(const std::string& familyName, const std::string& familySrc)
{
    fontManager_->RegisterFont(familyName, familySrc, AceType::Claim(this));
}

void PipelineContext::TryLoadImageInfo(
    const std::string& src, std::function<void(bool, int32_t, int32_t)>&& loadCallback)
{
    ImageProvider::TryLoadImageInfo(AceType::Claim(this), src, std::move(loadCallback));
}

void PipelineContext::SetAnimationCallback(AnimationCallback&& callback)
{
    if (!callback) {
        return;
    }
    animationCallback_ = std::move(callback);
}

#ifndef WEARABLE_PRODUCT
void PipelineContext::SetMultimodalSubscriber(const RefPtr<MultimodalSubscriber>& multimodalSubscriber)
{
    multiModalManager_->SetMultimodalSubscriber(multimodalSubscriber);
}

void PipelineContext::OnShow()
{
    onShow_ = true;
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
        TaskExecutor::TaskType::UI);
}

void PipelineContext::OnHide()
{
    onShow_ = false;
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
            context->NotifyPopupDismiss();
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
        TaskExecutor::TaskType::UI);
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
        render->SetDefaultBgColor();
    }
}

void PipelineContext::SetOnPageShow(OnPageShowCallBack&& onPageShowCallBack)
{
    if (!onPageShowCallBack) {
        LOGE("Set onShow callback failed, callback is null.");
        return;
    }
    onPageShowCallBack_ = std::move(onPageShowCallBack);
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

void PipelineContext::SetFontScale(float fontScale)
{
    const static float CARD_MAX_FONT_SCALE = 1.3f;
    if (!NearEqual(fontScale_, fontScale)) {
        fontScale_ = fontScale;
        if (isJsCard_ && GreatOrEqual(fontScale_, CARD_MAX_FONT_SCALE)) {
            fontScale_ = CARD_MAX_FONT_SCALE;
        }
        fontManager_->RebuildFontNode();
    }
}

void PipelineContext::UpdateFontWeightScale()
{
    if (fontManager_) {
        fontManager_->UpdateFontWeightScale();
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
                TaskExecutor::TaskType::UI);
        },
        TaskExecutor::TaskType::IO);
}

void PipelineContext::NotifyFontNodes()
{
    if (fontManager_) {
        fontManager_->NotifyVariationNodes();
    }
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
    if (textFieldManager_) {
        textFieldManager_->SetClickPosition(position);
    }
}

void PipelineContext::SetTextFieldManager(const RefPtr<ManagerInterface>& manager)
{
    textFieldManager_ = manager;
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
            context->SetRootRect(context->rootWidth_, context->rootHeight_);
            context->FlushLayout();
        },
        TaskExecutor::TaskType::UI);
}

void PipelineContext::RootLostFocus() const
{
    rootElement_->LostFocus();
}

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
    for (auto iter = deactivateElements_.begin(); iter != deactivateElements_.end();) {
        auto element = iter->second;
        RefPtr<RenderNode> render = element ? element->GetRenderNode() : nullptr;
        if (!render || !render->IsDisappearing()) {
            deactivateElements_.erase(iter++);
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
    if (params.size() == 1) {
        accessibilityManager->DumpTree(0, 0);
    } else if (params.size() == 2) {
        accessibilityManager->DumpProperty(params);
    } else if (params.size() == 3) {
        accessibilityManager->DumpHandleEvent(params);
    }
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

void PipelineContext::SetPreTargetRenderNode(const RefPtr<RenderNode>& preTargetRenderNode)
{
    preTargetRenderNode_ = preTargetRenderNode;
}

const RefPtr<RenderNode> PipelineContext::GetPreTargetRenderNode() const
{
    return preTargetRenderNode_;
}

bool PipelineContext::ProcessDragEvent(int action, double windowX, double windowY, const std::string& data)
{
    RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
    RefPtr<PasteData> pasteData = AceType::MakeRefPtr<PasteData>();
    event->SetPasteData(pasteData);
    event->SetX(ConvertPxToVp(Dimension(windowX, DimensionUnit::PX)));
    event->SetY(ConvertPxToVp(Dimension(windowY, DimensionUnit::PX)));
    auto json = JsonUtil::ParseJsonString(data);
    event->SetDescription(json->GetValue("description")->GetString());
    event->GetPasteData()->SetPlainText(json->GetValue("plainText")->GetString());

    auto renderNode = GetLastPageRender();
    if (!renderNode) {
        return false;
    }

    Point globalPoint(windowX, windowY);
    Point localPoint(windowX, windowY);

    if (action == DragEventAction::ACTION_DRAG_LOCATION) {
        auto targetRenderBox = AceType::DynamicCast<RenderBox>(renderNode->FindDropChild(globalPoint, localPoint));
        auto preTargetRenderBox = AceType::DynamicCast<RenderBox>(GetPreTargetRenderNode());

        if (targetRenderBox == preTargetRenderBox) {
            if (targetRenderBox && targetRenderBox->GetOnDragMove()) {
                (targetRenderBox->GetOnDragMove())(event);
            }
        } else {
            if (preTargetRenderBox && preTargetRenderBox->GetOnDragLeave()) {
                (preTargetRenderBox->GetOnDragLeave())(event);
            }
            if (targetRenderBox && targetRenderBox->GetOnDragEnter()) {
                (targetRenderBox->GetOnDragEnter())(event);
            }
            SetPreTargetRenderNode(targetRenderBox);
        }

        return targetRenderBox ? true : false;
    } else if (action == DragEventAction::ACTION_DROP) {
        auto targetRenderBox = AceType::DynamicCast<RenderBox>(renderNode->FindDropChild(globalPoint, localPoint));

        if (targetRenderBox && targetRenderBox->GetOnDrop()) {
            (targetRenderBox->GetOnDrop())(event);
        }
        SetPreTargetRenderNode(nullptr);
        return targetRenderBox ? true : false;
    }

    return true;
}

void PipelineContext::FlushWindowBlur()
{
    CHECK_RUN_ON(UI);

    if (!updateWindowBlurRegionHandler_) {
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
        taskExecutor_->PostTask([time] { ThreadStuckTask(time); }, TaskExecutor::TaskType::JS);
    } else {
        taskExecutor_->PostTask([time] { ThreadStuckTask(time); }, TaskExecutor::TaskType::UI);
    }
}

void PipelineContext::DumpFrontend() const
{
    auto frontend = weakFrontend_.Upgrade();
    if (frontend) {
        frontend->DumpFrontend();
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

void PipelineContext::SaveExplicitAnimationOption(const AnimationOption& option)
{
    explicitAnimationOption_ = option;
}

void PipelineContext::ClearExplicitAnimationOption()
{
    explicitAnimationOption_ = AnimationOption();
}

const AnimationOption PipelineContext::GetExplicitAnimationOption() const
{
    return explicitAnimationOption_;
}

bool PipelineContext::GetIsDeclarative() const
{
    RefPtr<Frontend> front = GetFrontend();
    if (front) {
        return front->GetType() == FrontendType::DECLARATIVE_JS;
    }
    return false;
}

void PipelineContext::SetForbidePlatformQuit(bool forbidePlatformQuit)
{
    forbidePlatformQuit_ = forbidePlatformQuit;
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
    renderStage->SetForbidSwipeToRight(forbidePlatformQuit_);
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
        TaskExecutor::TaskType::PLATFORM);
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
        TaskExecutor::TaskType::PLATFORM);
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
            TaskExecutor::TaskType::PLATFORM);
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

} // namespace OHOS::Ace
