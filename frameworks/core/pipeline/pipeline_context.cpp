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
#include "core/common/ace_engine.h"
#include "core/common/event_manager.h"
#include "core/common/font_manager.h"
#include "core/common/frontend.h"
#include "core/common/manager_interface.h"
#include "core/components/checkable/render_checkable.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/dialog/dialog_component.h"
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
#include "core/components/stage/stage_component.h"
#include "core/components/stage/stage_element.h"
#include "core/image/render_image_provider.h"
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
    themeManager_ = AceType::MakeRefPtr<ThemeManager>();
    renderFactory_ = AceType::MakeRefPtr<FlutterRenderFactory>();
    UpdateFontWeightScale();
}

void PipelineContext::FlushPipelineWithoutAnimation()
{
    FlushBuild();
    FlushLayout();
    FlushRender();
    FlushWindowBlur();
    FlushFocus();
    ProcessPostFlush();
    ClearDeactivateElements();
}

void PipelineContext::FlushBuild()
{
    ACE_FUNCTION_TRACE();

    if (dirtyElements_.empty()) {
        return;
    }
    decltype(dirtyElements_) dirtyElements(std::move(dirtyElements_));
    for (const auto& elementWeak : dirtyElements) {
        auto element = elementWeak.Upgrade();
        // maybe unavailable when update parent
        if (element) {
            element->Rebuild();
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

void PipelineContext::FlushPredictLayout()
{
    if (predictLayoutNodes_.empty()) {
        return;
    }
    ACE_FUNCTION_TRACE();
    decltype(predictLayoutNodes_) dirtyNodes(std::move(predictLayoutNodes_));
    for (const auto& dirtyNode : dirtyNodes) {
        dirtyNode->OnPredictLayout();
    }
}

void PipelineContext::FlushFocus()
{
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

void PipelineContext::RefreshStageFocus()
{
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
    auto overlay = GetOverlayElement();
    if (!overlay) {
        LOGE("Get stage element failed. overlay element is null!");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return RefPtr<StageElement>();
    }
    return AceType::DynamicCast<StageElement>(overlay->GetFirstChild());
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
    const auto& it = composedElementMap_.find(id);
    if (it != composedElementMap_.end() && !it->second.empty()) {
        return it->second.front();
    }
    return RefPtr<ComposedElement>();
}

void PipelineContext::FlushLayout()
{
    ACE_FUNCTION_TRACE();

    if (dirtyLayoutNodes_.empty()) {
        return;
    }
    decltype(dirtyLayoutNodes_) dirtyNodes(std::move(dirtyLayoutNodes_));
    for (const auto& dirtyNode : dirtyNodes) {
        dirtyNode->OnLayout();
    }
}

void PipelineContext::FlushRender()
{
    ACE_FUNCTION_TRACE();

    if (dirtyRenderNodes_.empty() && dirtyRenderNodesInOverlay_.empty() && !needForcedRefresh_) {
        return;
    }

    Rect curDirtyRect;
    bool isDirtyRootRect = false;
    if (needForcedRefresh_) {
        curDirtyRect.SetRect(0.0, 0.0, rootWidth_, rootHeight_);
        isDirtyRootRect = true;
    }
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

    if (rootElement_) {
        auto renderRoot = rootElement_->GetRenderNode();
        curDirtyRect = curDirtyRect * viewScale_;
        renderRoot->FinishRender(drawDelegate_, dirtyRect_.CombineRect(curDirtyRect));
        dirtyRect_ = curDirtyRect;
    }
    needForcedRefresh_ = false;
}

void PipelineContext::FlushAnimation(uint64_t nanoTimestamp)
{
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

void PipelineContext::FlushPageUpdateTasks()
{
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
    if (animationCallback_) {
        taskExecutor_->PostTask(animationCallback_, TaskExecutor::TaskType::JS);
    }
}

void PipelineContext::ProcessPreFlush()
{
    ACE_FUNCTION_TRACE();

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
    ACE_FUNCTION_TRACE();

    if (postFlushListeners_.empty()) {
        return;
    }
    decltype(postFlushListeners_) temp(std::move(postFlushListeners_));
    for (const auto& listener : temp) {
        listener->OnPostFlush();
    }
}

RefPtr<Element> PipelineContext::SetupRootElement()
{
    RefPtr<StageComponent> rootStage = AceType::MakeRefPtr<StageComponent>(std::list<RefPtr<Component>>());
    if (isRightToLeft_) {
        rootStage->SetTextDirection(TextDirection::RTL);
    }
    rootStage->SetMainStackSize(MainStackSize::LAST_CHILD);
    auto overlay = AceType::MakeRefPtr<OverlayComponent>(std::list<RefPtr<Component>>());
    overlay->AppendChild(rootStage);
    RefPtr<RootComponent> rootComponent;
    if (windowModal_ == WindowModal::SEMI_MODAL || windowModal_ == WindowModal::SEMI_MODAL_FULL_SCREEN) {
        auto semiModal = SemiModalComponent::Create(
            overlay, windowModal_ == WindowModal::SEMI_MODAL_FULL_SCREEN, modalHeight_, modalColor_);
        rootComponent = RootComponent::Create(semiModal);
    } else if (windowModal_ == WindowModal::DIALOG_MODAL) {
        rootStage->SetMainStackSize(MainStackSize::MAX);
        rootStage->SetAlignment(Alignment::BOTTOM_LEFT);
        auto dialogModal = DialogModalComponent::Create(overlay);
        rootComponent = RootComponent::Create(dialogModal);
    } else {
        rootComponent = RootComponent::Create(overlay);
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
        rootElement_->DumpTree(0);
    } else if (params[0] == "-render") {
        rootElement_->GetRenderNode()->DumpTree(0);
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
        DumpLog::GetInstance().Print("Report hiview event. EventID: " + params[1] + ", error type: " + params[2]);
        EventInfo eventInfo = { .eventType = StringUtils::StringToInt(params[1]),
            .errorType = StringUtils::StringToInt(params[2]) };
        EventReport::SendEvent(eventInfo);
    } else if (params[0] == "-threadstuck" && params.size() >= 3) {
        MakeThreadStuck(params);
    } else if (params[0] == "-jscrash") {
        EventReport::JsErrReport(
            AceEngine::Get().GetUid(), AceEngine::Get().GetPackageName(), "js crash reason", "js crash summary");
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

bool PipelineContext::CanPushPage()
{
    auto stageElement = GetStageElement();
    return stageElement && stageElement->CanPushPage();
}

void PipelineContext::PushPage(const RefPtr<PageComponent>& pageComponent)
{
    auto stageElement = GetStageElement();
    if (!stageElement) {
        LOGE("Get stage element failed!");
        return;
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
    FlushBuildAndLayoutBeforeSurfaceReady();
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

bool PipelineContext::ShowDialog(const DialogProperties& dialogProperties, bool isRightToLeft)
{
    const auto& dialog = DialogBuilder::Build(dialogProperties, AceType::WeakClaim(this));
    if (!dialog) {
        return false;
    }
    dialog->SetTextDirection(isRightToLeft ? TextDirection::RTL : TextDirection::LTR);
    const auto& lastStack = GetLastStack();
    if (!lastStack) {
        return false;
    }
    lastStack->PushDialog(dialog);
    return true;
}

bool PipelineContext::CanPopPage()
{
    auto stageElement = GetStageElement();
    return stageElement && stageElement->CanPopPage();
}

void PipelineContext::PopPage()
{
    LOGD("PopPageComponent");
    auto stageElement = GetStageElement();
    if (stageElement) {
        stageElement->Pop();
    }
}

void PipelineContext::PopToPage(int32_t pageId)
{
    LOGD("PopToPageComponent: page-%{public}d", pageId);
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

void PipelineContext::ReplacePage(const RefPtr<PageComponent>& pageComponent)
{
    LOGD("ReplacePageComponent");
    auto stageElement = GetStageElement();
    if (!stageElement) {
        LOGE("Get stage element failed!");
        return;
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

bool PipelineContext::ClearInvisiblePages()
{
    LOGD("ClearInvisiblePageComponents");
    auto stageElement = GetStageElement();
    return stageElement && stageElement->ClearOffStage();
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
                return true;
            }
            // return back to desktop
            return false;
        } else {
            return true;
        }
    }
}

void PipelineContext::ScheduleUpdate(const RefPtr<ComposedComponent>& compose)
{
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
    if (!dirtyElement) {
        LOGW("dirtyElement is null");
        return;
    }
    LOGD("schedule rebuild for %{public}s", AceType::TypeName(dirtyElement));
    dirtyElements_.emplace(dirtyElement);
    hasIdleTasks_ = true;
    window_->RequestFrame();
}

void PipelineContext::AddNeedRebuildFocusElement(const RefPtr<Element>& focusElement)
{
    if (!focusElement) {
        LOGW("focusElement is null");
        return;
    }
    LOGD("schedule rebuild focus element for %{public}s", AceType::TypeName(focusElement));
    needRebuildFocusElement_.emplace(focusElement);
}

void PipelineContext::AddDirtyRenderNode(const RefPtr<RenderNode>& renderNode, bool overlay)
{
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

void PipelineContext::AddDirtyLayoutNode(const RefPtr<RenderNode>& renderNode)
{
    if (!renderNode) {
        LOGW("renderNode is null");
        return;
    }
    LOGD("schedule layout for %{public}s", AceType::TypeName(renderNode));
    dirtyLayoutNodes_.emplace(renderNode);
    hasIdleTasks_ = true;
    window_->RequestFrame();
}

void PipelineContext::AddPredictLayoutNode(const RefPtr<RenderNode>& renderNode)
{
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
    preFlushListeners_.emplace_back(listener);
    window_->RequestFrame();
}

void PipelineContext::AddPostFlushListener(const RefPtr<FlushEvent>& listener)
{
    postFlushListeners_.emplace_back(listener);
    window_->RequestFrame();
}

uint32_t PipelineContext::AddScheduleTask(const RefPtr<ScheduleTask>& task)
{
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
    scheduleTasks_.erase(id);
}

void PipelineContext::OnTouchEvent(const TouchPoint& point)
{
    ACE_FUNCTION_TRACE();

    if (!rootElement_) {
        LOGE("the root element is nullptr on touch event");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return;
    }

    auto scalePoint = point.CreateScalePoint(viewScale_);
    LOGI("OnTouchEvent: x = %f, y = %f, type = %zu", scalePoint.x, scalePoint.y, scalePoint.type);
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
    return eventManager_.DispatchKeyEvent(event, rootElement_);
}

void PipelineContext::OnMouseEvent(const MouseEvent& event)
{
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
    ACE_FUNCTION_TRACE();
    FlushPredictLayout();
    if (hasIdleTasks_) {
        FlushPipelineImmediately();
        window_->RequestFrame();
        MarkForcedRefresh();
        hasIdleTasks_ = false;
    }
    FlushPageUpdateTasks();

    auto front = GetFrontend();
    if (front && GetIsDeclarative() && scheduleTasks_.empty()) {
        LOGD("Create GC task");
        GetTaskExecutor()->PostTask([front]() { front->TriggerGarbageCollection(); }, TaskExecutor::TaskType::JS);
    }
}

void PipelineContext::OnActionEvent(const std::string& action)
{
    if (actionEventHandler_) {
        actionEventHandler_(action);
    } else {
        LOGE("the action event handler is null");
    }
}

void PipelineContext::FlushPipelineImmediately()
{
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
    if (width_ == width && height_ == height) {
        return;
    }
    width_ = width;
    height_ = height;

    ACE_SCOPED_TRACE("OnSurfaceChanged(%d, %d)", width, height);

    if (!NearZero(rootHeight_)) {
        double newRootHeight = height / viewScale_;
        double newRootWidth = width / viewScale_;
        double offsetHeight = rootHeight_ - newRootHeight;
        if (textFieldManager_) {
            textFieldManager_->MovePage(GetLastStack(), { newRootWidth, newRootHeight }, offsetHeight);
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
    ACE_SCOPED_TRACE("OnSurfaceDensityChanged(%lf)", density);

    density_ = density;
    if (!NearZero(viewScale_)) {
        dipScale_ = density_ / viewScale_;
    }
}

void PipelineContext::OnSystemBarHeightChanged(double statusBar, double navigationBar)
{
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
    ACE_SCOPED_TRACE("OnSurfaceDestroyed");
    isSurfaceReady_ = false;
}

double PipelineContext::NormalizeToPx(const Dimension& dimension) const
{
    if ((dimension.Unit() == DimensionUnit::VP) || (dimension.Unit() == DimensionUnit::FP)) {
        return (dimension.Value() * dipScale_);
    }
    return dimension.Value();
}

void PipelineContext::SetRootSizeWithWidthHeight(int32_t width, int32_t height)
{
    auto frontend = weakFrontend_.Upgrade();
    if (!frontend) {
        LOGE("the frontend is nullptr");
        EventReport::SendAppStartException(AppStartExcepType::PIPELINE_CONTEXT_ERR);
        return;
    }
    const auto& windowConfig = frontend->GetWindowConfig();
    if (windowConfig.designWidth <= 0) {
        LOGE("the frontend design width <= 0");
        return;
    }
    if (GetIsDeclarative()) {
        viewScale_ = DEFAULT_VIEW_SCALE;
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

    density_ = density;
    SetRootSizeWithWidthHeight(width, height);
}

void PipelineContext::SetRootRect(double width, double height) const
{
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

void PipelineContext::Finish(bool autoFinish) const
{
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
    LOGD("Notify StatusBar BgColor, color: %{public}x", color.GetValue());
    if (statusBarBgColorEventHandler_) {
        statusBarBgColorEventHandler_(color);
    } else {
        LOGE("fail to finish current context due to handler is nullptr");
    }
}

void PipelineContext::NotifyPopupDismiss() const
{
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
    ClearImageCache();
    if (rootElement_) {
        rootElement_.Reset();
    }
    composedElementMap_.clear();
    dirtyElements_.clear();
    dirtyRenderNodes_.clear();
    dirtyRenderNodesInOverlay_.clear();
    dirtyLayoutNodes_.clear();
    predictLayoutNodes_.clear();
    dirtyFocusNode_.Reset();
    dirtyFocusScope_.Reset();
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

void PipelineContext::CanLoadImage(const std::string& src, const std::map<std::string, EventMarker>& callbacks)
{
    RenderImageProvider::CanLoadImage(AceType::Claim(this), src, callbacks);
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
    if (rootElement_) {
        const auto& renderRoot = AceType::DynamicCast<RenderRoot>(rootElement_->GetRenderNode());
        if (renderRoot) {
            renderRoot->NotifyOnShow();
        }
    }
}

void PipelineContext::OnHide()
{
    NotifyPopupDismiss();
    onShow_ = false;
    auto multiModalScene = multiModalManager_->GetCurrentMultiModalScene();
    if (multiModalScene) {
        multiModalScene->Hide();
    }
    if ((windowModal_ == WindowModal::SEMI_MODAL) || (windowModal_ == WindowModal::DIALOG_MODAL)) {
        taskExecutor_->PostTask(
            [weak = AceType::WeakClaim(this)]() {
                auto context = weak.Upgrade();
                if (!context) {
                    return;
                }
                const auto& root = context->rootElement_;
                if (!root) {
                    return;
                }
                const auto& render = AceType::DynamicCast<RenderRoot>(root->GetRenderNode());
                if (render) {
                    render->SetDefaultBgColor();
                }
            },
            TaskExecutor::TaskType::UI);
    }
    if (rootElement_) {
        const auto& renderRoot = AceType::DynamicCast<RenderRoot>(rootElement_->GetRenderNode());
        if (renderRoot) {
            renderRoot->NotifyOnHide();
        }
    }
}
#endif

void PipelineContext::RefreshRootBgColor() const
{
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
    if (!NearEqual(fontScale_, fontScale)) {
        fontScale_ = fontScale;
        fontManager_->RebuildFontNode();
    }
}

void PipelineContext::UpdateFontWeightScale()
{
    if (fontManager_) {
        fontManager_->UpdateFontWeightScale();
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
    if (textFieldManager_) {
        textFieldManager_->MovePage(GetLastStack(), rootRect, offsetHeight);
    }
}

RefPtr<Element> PipelineContext::GetDeactivateElement(int32_t componentId) const
{
    auto elementIter = deactivateElements_.find(componentId);
    if (elementIter != deactivateElements_.end()) {
        return elementIter->second;
    } else {
        return nullptr;
    }
}

void PipelineContext::AddDeactivateElement(const int32_t id, const RefPtr<Element>& element)
{
    deactivateElements_.emplace(id, element);
}

void PipelineContext::ClearDeactivateElements()
{
    if (!deactivateElements_.empty()) {
        deactivateElements_.erase(deactivateElements_.begin(), deactivateElements_.end());
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
    auto pos = windowBlurRegions_.find(id);
    if (pos != windowBlurRegions_.end()) {
        const auto& old = pos->second;
        if (NearEqual(progress, old.progress_) && rRect.NearEqual(old.innerRect_) && style == old.style_) {
            return;
        }
    }
    windowBlurRegions_[id] = { .progress_ = progress, .style_ = style, .innerRect_ = rRect, .coords_ = coords };
    needWindowBlurRegionRefresh_ = true;
}

void PipelineContext::ClearWindowBlurRegion(int32_t id)
{
    auto pos = windowBlurRegions_.find(id);
    if (pos != windowBlurRegions_.end()) {
        windowBlurRegions_.erase(pos);
        needWindowBlurRegionRefresh_ = true;
    }
}

void PipelineContext::FlushWindowBlur()
{
    // js card not support window blur
    if (IsJsCard()) {
        return;
    }

    if (!updateWindowBlurRegionHandler_) {
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

void PipelineContext::DrawLastFrame()
{
    if (drawDelegate_) {
        drawDelegate_->DrawLastFrame(Rect(0.0, 0.0, width_, height_));
    }
}

void PipelineContext::SetIsKeyEvent(bool isKeyEvent)
{
    if (focusAnimationManager_) {
        isKeyEvent_ = isKeyEvent;
        focusAnimationManager_->SetIsKeyEvent(isKeyEvent_);
    }
}

void PipelineContext::NavigatePage(uint8_t type, const std::string& uri)
{
    auto frontend = weakFrontend_.Upgrade();
    if (!frontend) {
        LOGE("frontend is nullptr");
        return;
    }
    frontend->NavigatePage(type, uri);
}

bool PipelineContext::GetIsDeclarative() const
{
    RefPtr<Frontend> front = GetFrontend();
    if (front) {
        return front->GetType() == FrontendType::DECLARATIVE_JS;
    }
    return false;
}

} // namespace OHOS::Ace
