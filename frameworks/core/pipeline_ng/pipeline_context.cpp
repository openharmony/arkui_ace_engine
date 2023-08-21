/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/pipeline_ng/pipeline_context.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"

#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_client/core/ui/rs_ui_director.h"

#include "core/components_ng/render/adapter/rosen_window.h"
#endif

#include <algorithm>
#include <cinttypes>
#include <cstdint>
#include <memory>

#include "base/geometry/ng/offset_t.h"
#include "base/log/ace_trace.h"
#include "base/log/ace_tracker.h"
#include "base/log/event_report.h"
#include "base/log/frame_report.h"
#include "base/memory/referenced.h"
#include "base/thread/task_executor.h"
#include "base/utils/utils.h"
#include "core/animation/scheduler.h"
#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "core/common/layout_inspector.h"
#include "core/common/text_field_manager.h"
#include "core/common/thread_checker.h"
#include "core/common/window.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/app_bar/app_bar_view.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"
#include "core/components_ng/pattern/custom/custom_node_base.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/ace_events.h"
#include "core/event/touch_event.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace {
constexpr int32_t TIME_THRESHOLD = 2 * 1000000; // 3 millisecond
} // namespace

namespace OHOS::Ace::NG {

PipelineContext::PipelineContext(std::unique_ptr<Window> window, RefPtr<TaskExecutor> taskExecutor,
    RefPtr<AssetManager> assetManager, RefPtr<PlatformResRegister> platformResRegister,
    const RefPtr<Frontend>& frontend, int32_t instanceId)
    : PipelineBase(std::move(window), std::move(taskExecutor), std::move(assetManager), frontend, instanceId)
{
    window_->OnHide();
}

PipelineContext::PipelineContext(std::unique_ptr<Window> window, RefPtr<TaskExecutor> taskExecutor,
    RefPtr<AssetManager> assetManager, const RefPtr<Frontend>& frontend, int32_t instanceId)
    : PipelineBase(std::move(window), std::move(taskExecutor), std::move(assetManager), frontend, instanceId)
{
    window_->OnHide();
}

RefPtr<PipelineContext> PipelineContext::GetCurrentContext()
{
    auto currentContainer = Container::Current();
    CHECK_NULL_RETURN(currentContainer, nullptr);
    return DynamicCast<PipelineContext>(currentContainer->GetPipelineContext());
}

float PipelineContext::GetCurrentRootWidth()
{
    auto context = GetCurrentContext();
    CHECK_NULL_RETURN(context, 0.0f);
    return static_cast<float>(context->rootWidth_);
}

float PipelineContext::GetCurrentRootHeight()
{
    auto context = GetCurrentContext();
    CHECK_NULL_RETURN(context, 0.0f);
    return static_cast<float>(context->rootHeight_);
}

void PipelineContext::AddDirtyCustomNode(const RefPtr<UINode>& dirtyNode)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(dirtyNode);
    dirtyNodes_.emplace(dirtyNode);
    hasIdleTasks_ = true;
    window_->RequestFrame();
}

void PipelineContext::AddDirtyLayoutNode(const RefPtr<FrameNode>& dirty)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(dirty);
    taskScheduler_.AddDirtyLayoutNode(dirty);
    ForceLayoutForImplicitAnimation();
    hasIdleTasks_ = true;
    window_->RequestFrame();
}

void PipelineContext::AddDirtyRenderNode(const RefPtr<FrameNode>& dirty)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(dirty);
    taskScheduler_.AddDirtyRenderNode(dirty);
    hasIdleTasks_ = true;
    window_->RequestFrame();
}

void PipelineContext::FlushDirtyNodeUpdate()
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACE();
    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().BeginFlushBuild();
    }

    // SomeTimes, customNode->Update may add some dirty custom nodes to dirtyNodes_,
    // use maxFlushTimes to avoid dead cycle.
    int maxFlushTimes = 3;
    while (!dirtyNodes_.empty() && maxFlushTimes > 0) {
        decltype(dirtyNodes_) dirtyNodes(std::move(dirtyNodes_));
        for (const auto& node : dirtyNodes) {
            if (AceType::InstanceOf<NG::CustomNodeBase>(node)) {
                auto customNode = AceType::DynamicCast<NG::CustomNodeBase>(node);
                customNode->Update();
            }
        }
        --maxFlushTimes;
    }
    if (!dirtyNodes_.empty()) {
        LOGW("FlushDirtyNodeUpdate 3 times, still has dirty nodes");
    }

    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().EndFlushBuild();
    }
}

uint32_t PipelineContext::AddScheduleTask(const RefPtr<ScheduleTask>& task)
{
    CHECK_RUN_ON(UI);
    scheduleTasks_.try_emplace(++nextScheduleTaskId_, task);
    window_->RequestFrame();
    return nextScheduleTaskId_;
}

void PipelineContext::FlushVsync(uint64_t nanoTimestamp, uint32_t frameCount)
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACE();
    static const std::string abilityName = AceApplicationInfo::GetInstance().GetProcessName().empty()
                                               ? AceApplicationInfo::GetInstance().GetPackageName()
                                               : AceApplicationInfo::GetInstance().GetProcessName();
    window_->RecordFrameTime(nanoTimestamp, abilityName);
    FlushAnimation(GetTimeFromExternalTimer());
    FlushBuild();
    if (isFormRender_ && drawDelegate_ && rootNode_) {
        auto renderContext = AceType::DynamicCast<NG::RenderContext>(rootNode_->GetRenderContext());
        drawDelegate_->DrawRSFrame(renderContext);
        drawDelegate_ = nullptr;
    }
    FlushTouchEvents();
    if (!taskScheduler_.isEmpty()) {
#if !defined(PREVIEW)
        LayoutInspector::SupportInspector();
#endif
    }
    taskScheduler_.FlushTask();
    TryCallNextFrameLayoutCallback();
    auto hasAninmation = window_->FlushCustomAnimation(nanoTimestamp);
    if (hasAninmation) {
        RequestFrame();
    }
    FlushMessages();
    if (!isFormRender_ && onShow_ && onFocus_) {
        FlushFocus();
    }
    HandleOnAreaChangeEvent();
    HandleVisibleAreaChangeEvent();
}

void PipelineContext::FlushAnimation(uint64_t nanoTimestamp)
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACE();
    if (scheduleTasks_.empty()) {
        return;
    }

    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().BeginFlushAnimation();
    }

    decltype(scheduleTasks_) temp(std::move(scheduleTasks_));
    for (const auto& [id, weakTask] : temp) {
        auto task = weakTask.Upgrade();
        if (task) {
            task->OnFrame(nanoTimestamp);
        }
    }

    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().EndFlushAnimation();
    }
}

void PipelineContext::FlushMessages()
{
    ACE_FUNCTION_TRACE();
    window_->FlushTasks();
}

void PipelineContext::FlushFocus()
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACK();
    ACE_FUNCTION_TRACE();
    auto focusNode = dirtyFocusNode_.Upgrade();
    if (!focusNode || focusNode->GetFocusType() != FocusType::NODE) {
        dirtyFocusNode_.Reset();
    } else {
        auto focusNodeHub = focusNode->GetFocusHub();
        if (focusNodeHub) {
            focusNodeHub->RequestFocusImmediately();
        }
        dirtyFocusNode_.Reset();
        dirtyFocusScope_.Reset();
        return;
    }
    auto focusScope = dirtyFocusScope_.Upgrade();
    if (!focusScope || focusScope->GetFocusType() != FocusType::SCOPE) {
        dirtyFocusScope_.Reset();
    } else {
        auto focusScopeHub = focusScope->GetFocusHub();
        if (focusScopeHub) {
            focusScopeHub->RequestFocusImmediately();
        }
        dirtyFocusNode_.Reset();
        dirtyFocusScope_.Reset();
        return;
    }
    if (!RequestDefaultFocus()) {
        if (rootNode_ && rootNode_->GetFocusHub() && !rootNode_->GetFocusHub()->IsCurrentFocus()) {
            rootNode_->GetFocusHub()->RequestFocusImmediately();
        }
    }
}

void PipelineContext::FlushPipelineImmediately()
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACE();
    FlushPipelineWithoutAnimation();
}

void PipelineContext::FlushPipelineWithoutAnimation()
{
    FlushBuild();
    FlushTouchEvents();
    taskScheduler_.FlushTask();
    FlushMessages();
    FlushFocus();
}

void PipelineContext::FlushBuild()
{
    isRebuildFinished_ = false;
    FlushDirtyNodeUpdate();
    isRebuildFinished_ = true;
    FlushBuildFinishCallbacks();
}

void PipelineContext::FlushBuildFinishCallbacks()
{
    decltype(buildFinishCallbacks_) buildFinishCallbacks(std::move(buildFinishCallbacks_));
    for (const auto& func : buildFinishCallbacks) {
        if (func) {
            func();
        }
    }
}

void PipelineContext::RegisterRootEvent()
{
    if (!IsFormRender()) {
        return;
    }

    // To avoid conflicts between longPress and click events on the card,
    // use an empty longPress event placeholder in the EtsCard scenario
    auto hub = rootNode_->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(hub);
    auto event = [](const GestureEvent& info) mutable {
        LOGD("Not Support LongPress");
    };
    auto longPress = AceType::MakeRefPtr<NG::LongPressEvent>(std::move(event));
    hub->SetLongPressEvent(longPress, false, true);
}

void PipelineContext::SetupRootElement()
{
    CHECK_RUN_ON(UI);
    rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<RootPattern>());
    rootNode_->SetHostRootId(GetInstanceId());
    rootNode_->SetHostPageId(-1);
    RegisterRootEvent();
    CalcSize idealSize { CalcLength(rootWidth_), CalcLength(rootHeight_) };
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    layoutConstraint.maxSize = idealSize;
    rootNode_->UpdateLayoutConstraint(layoutConstraint);
    auto rootFocusHub = rootNode_->GetOrCreateFocusHub();
    rootFocusHub->SetFocusType(FocusType::SCOPE);
    rootFocusHub->SetFocusable(true);
    window_->SetRootFrameNode(rootNode_);
    rootNode_->AttachToMainTree();

    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<StagePattern>());
    auto appBarNode = installationFree_ ? AppBarView::Create(stageNode) : nullptr;
    if (windowModal_ == WindowModal::CONTAINER_MODAL) {
        rootNode_->AddChild(ContainerModalView::Create(appBarNode ? appBarNode : stageNode));
    } else {
        rootNode_->AddChild(appBarNode ? appBarNode : stageNode);
    }
#ifdef ENABLE_ROSEN_BACKEND
    if (!IsJsCard() && !isFormRender_) {
        auto rsWindow = static_cast<RosenWindow*>(GetWindow());
        if (rsWindow) {
            auto rsUIDirector = rsWindow->GetRsUIDirector();
            if (rsUIDirector) {
                rsUIDirector->SetAbilityBGAlpha(appBgColor_.GetAlpha());
            }
        }
    }
#endif
    stageManager_ = MakeRefPtr<StageManager>(stageNode);
    overlayManager_ = MakeRefPtr<OverlayManager>(
        DynamicCast<FrameNode>(installationFree_ ? stageNode->GetParent()->GetParent() : stageNode->GetParent()));
    fullScreenManager_ = MakeRefPtr<FullScreenManager>(rootNode_);
    selectOverlayManager_ = MakeRefPtr<SelectOverlayManager>(rootNode_);
    dragDropManager_ = MakeRefPtr<DragDropManager>();
    sharedTransitionManager_ = MakeRefPtr<SharedOverlayManager>(
        DynamicCast<FrameNode>(installationFree_ ? stageNode->GetParent()->GetParent() : stageNode->GetParent()));

    OnAreaChangedFunc onAreaChangedFunc = [weakOverlayManger = AceType::WeakClaim(AceType::RawPtr(overlayManager_))](
                                              const RectF& /* oldRect */, const OffsetF& /* oldOrigin */,
                                              const RectF& /* rect */, const OffsetF& /* origin */) {
        auto overlay = weakOverlayManger.Upgrade();
        CHECK_NULL_VOID(overlay);
        overlay->HideAllMenus();
        overlay->HideAllPopups();
    };
    rootNode_->SetOnAreaChangeCallback(std::move(onAreaChangedFunc));
    AddOnAreaChangeNode(rootNode_->GetId());

    LOGI("SetupRootElement success!");
}

void PipelineContext::SetupSubRootElement()
{
    CHECK_RUN_ON(UI);
    appBgColor_ = Color::TRANSPARENT;
    rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<RootPattern>());
    rootNode_->SetHostRootId(GetInstanceId());
    rootNode_->SetHostPageId(-1);
    CalcSize idealSize { CalcLength(rootWidth_), CalcLength(rootHeight_) };
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    layoutConstraint.maxSize = idealSize;
    rootNode_->UpdateLayoutConstraint(layoutConstraint);
    auto rootFocusHub = rootNode_->GetOrCreateFocusHub();
    rootFocusHub->SetFocusType(FocusType::SCOPE);
    rootFocusHub->SetFocusable(true);
    window_->SetRootFrameNode(rootNode_);
    rootNode_->AttachToMainTree();

#ifdef ENABLE_ROSEN_BACKEND
    if (!IsJsCard()) {
        auto rsWindow = static_cast<RosenWindow*>(GetWindow());
        if (rsWindow) {
            auto rsUIDirector = rsWindow->GetRsUIDirector();
            if (rsUIDirector) {
                rsUIDirector->SetAbilityBGAlpha(appBgColor_.GetAlpha());
            }
        }
    }
#endif
    // the subwindow for overlay not need stage
    stageManager_ = MakeRefPtr<StageManager>(nullptr);
    overlayManager_ = MakeRefPtr<OverlayManager>(rootNode_);
    fullScreenManager_ = MakeRefPtr<FullScreenManager>(rootNode_);
    selectOverlayManager_ = MakeRefPtr<SelectOverlayManager>(rootNode_);
    dragDropManager_ = MakeRefPtr<DragDropManager>();
}

const RefPtr<StageManager>& PipelineContext::GetStageManager()
{
    return stageManager_;
}

const RefPtr<DragDropManager>& PipelineContext::GetDragDropManager()
{
    return dragDropManager_;
}

const RefPtr<SelectOverlayManager>& PipelineContext::GetSelectOverlayManager()
{
    return selectOverlayManager_;
}

const RefPtr<OverlayManager>& PipelineContext::GetOverlayManager()
{
    return overlayManager_;
}

const RefPtr<FullScreenManager>& PipelineContext::GetFullScreenManager()
{
    return fullScreenManager_;
}

void PipelineContext::OnSurfaceChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    CHECK_RUN_ON(UI);
    LOGD("PipelineContext: OnSurfaceChanged start.");
    if (NearEqual(rootWidth_, width) && NearEqual(rootHeight_, height) &&
        type == WindowSizeChangeReason::CUSTOM_ANIMATION) {
        TryCallNextFrameLayoutCallback();
        return;
    }
    ExecuteSurfaceChangedCallbacks(width, height);
    // TODO: add adjust for textFieldManager when ime is show.
    taskExecutor_->PostTask(
        [weakFrontend = weakFrontend_, width, height]() {
            auto frontend = weakFrontend.Upgrade();
            if (frontend) {
                frontend->OnSurfaceChanged(width, height);
            }
        },
        TaskExecutor::TaskType::JS);

#ifdef ENABLE_ROSEN_BACKEND
    StartWindowSizeChangeAnimate(width, height, type);
#else
    SetRootRect(width, height, 0.0);
#endif
}

void PipelineContext::ExecuteSurfaceChangedCallbacks(int32_t newWidth, int32_t newHeight)
{
    for (auto&& [id, callback] : surfaceChangedCallbackMap_) {
        if (callback) {
            callback(newWidth, newHeight, rootWidth_, rootHeight_);
        }
    }
}

void PipelineContext::OnSurfacePositionChanged(int32_t posX, int32_t posY)
{
    for (auto&& [id, callback] : surfacePositionChangedCallbackMap_) {
        if (callback) {
            callback(posX, posY);
        }
    }
}

void PipelineContext::StartWindowSizeChangeAnimate(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    static const bool IsWindowSizeAnimationEnabled = SystemProperties::IsWindowSizeAnimationEnabled();
    if (!IsWindowSizeAnimationEnabled) {
        LOGE("no animation configured");
        SetRootRect(width, height, 0.0);
        return;
    }
    switch (type) {
        case WindowSizeChangeReason::RECOVER:
        case WindowSizeChangeReason::MAXIMIZE: {
            LOGI("PipelineContext::Root node RECOVER/MAXIMIZE animation, width = %{public}d, height = %{public}d",
                width, height);
            AnimationOption option;
            constexpr int32_t duration = 400;
            option.SetDuration(duration);
            auto curve = MakeRefPtr<DecelerationCurve>();
            option.SetCurve(curve);
            auto weak = WeakClaim(this);
            Animate(option, curve, [width, height, weak]() {
                auto pipeline = weak.Upgrade();
                CHECK_NULL_VOID(pipeline);
                pipeline->SetRootRect(width, height, 0.0);
                pipeline->FlushUITasks();
            });
            break;
        }
        case WindowSizeChangeReason::ROTATION: {
            LOGI("PipelineContext::Root node ROTATION animation, width = %{public}d, height = %{public}d", width,
                height);
            AnimationOption option;
            constexpr int32_t duration = 600;
            option.SetDuration(duration);
            auto curve = MakeRefPtr<CubicCurve>(0.2, 0.0, 0.2, 1.0); // animation curve: cubic [0.2, 0.0, 0.2, 1.0]
            option.SetCurve(curve);
            auto weak = WeakClaim(this);
            Animate(
                option, curve,
                [width, height, weak]() {
                    auto pipeline = weak.Upgrade();
                    CHECK_NULL_VOID(pipeline);
                    pipeline->SetRootRect(width, height, 0.0);
                    pipeline->FlushUITasks();
                },
                [weak]() {
                    auto pipeline = weak.Upgrade();
                    CHECK_NULL_VOID(pipeline);
                    pipeline->rotationAnimationCount_--;
                    if (pipeline->rotationAnimationCount_ < 0) {
                        LOGE("PipelineContext::Root node ROTATION animation callback"
                             "rotationAnimationCount Invalid %{public}d",
                            pipeline->rotationAnimationCount_);
                    }
                    if (pipeline->rotationAnimationCount_ == 0) {
                        pipeline->window_->SetDrawTextAsBitmap(false);
                    }
                });
            rotationAnimationCount_++;
            window_->SetDrawTextAsBitmap(true);
            break;
        }
        case WindowSizeChangeReason::DRAG_START:
        case WindowSizeChangeReason::DRAG:
        case WindowSizeChangeReason::DRAG_END:
        case WindowSizeChangeReason::RESIZE:
        case WindowSizeChangeReason::UNDEFINED:
        default: {
            LOGD("PipelineContext::RootNodeAnimation : unsupported type, no animation added");
            SetRootRect(width, height, 0.0f);
        }
    }
}

void PipelineContext::SetRootRect(double width, double height, double offset)
{
    LOGI("SetRootRect width %{public}f, height %{public}f, %{public}f", width, height, offset);
    CHECK_RUN_ON(UI);
    UpdateRootSizeAndScale(width, height);
    CHECK_NULL_VOID(rootNode_);
    GridSystemManager::GetInstance().SetWindowInfo(rootWidth_, density_, dipScale_);
    GridSystemManager::GetInstance().OnSurfaceChanged(width);
    SizeF sizeF { static_cast<float>(width), static_cast<float>(height) };
    if (rootNode_->GetGeometryNode()->GetFrameSize() != sizeF || rootNode_->IsLayoutDirtyMarked()) {
        CalcSize idealSize { CalcLength(width), CalcLength(height) };
        MeasureProperty layoutConstraint;
        layoutConstraint.selfIdealSize = idealSize;
        layoutConstraint.maxSize = idealSize;
        rootNode_->UpdateLayoutConstraint(layoutConstraint);
        // reset parentLayoutConstraint to update itself when next measure task
        rootNode_->GetGeometryNode()->ResetParentLayoutConstraint();
        rootNode_->MarkDirtyNode();
    }
    if (rootNode_->GetGeometryNode()->GetFrameOffset().GetY() != offset) {
        OffsetF newOffset = rootNode_->GetGeometryNode()->GetFrameOffset();
        newOffset.SetY(static_cast<float>(offset));
        rootNode_->GetGeometryNode()->SetMarginFrameOffset(newOffset);
        auto rootContext = rootNode_->GetRenderContext();
        rootContext->SyncGeometryProperties(RawPtr(rootNode_->GetGeometryNode()));
        RequestFrame();
    }
}

void PipelineContext::OnVirtualKeyboardHeightChange(float keyboardHeight)
{
    CHECK_RUN_ON(UI);
    float positionY = 0;
    auto manager = DynamicCast<TextFieldManagerNG>(PipelineBase::GetTextFieldManager());
    float height = 0.0f;
    if (manager) {
        height = manager->GetHeight();
        positionY = static_cast<float>(manager->GetClickPosition().GetY());
    }
    SizeF rootSize { static_cast<float>(rootWidth_), static_cast<float>(rootHeight_) };
    float offsetFix = (rootSize.Height() - positionY) > 100.0 ? keyboardHeight - (rootSize.Height() - positionY) / 2.0
                                                              : keyboardHeight;
    LOGI("OnVirtualKeyboardAreaChange positionY:%{public}f safeArea:%{public}f offsetFix:%{public}f, "
         "keyboardHeight %{public}f",
        positionY, (rootSize.Height() - keyboardHeight), offsetFix, keyboardHeight);
    if (NearZero(keyboardHeight)) {
        SetRootRect(rootSize.Width(), rootSize.Height(), 0);
    } else if (LessOrEqual(rootSize.Height() - positionY - height, height)) {
        SetRootRect(rootSize.Width(), rootSize.Height(), -keyboardHeight);
    } else if (positionY + height > (rootSize.Height() - keyboardHeight) && offsetFix > 0.0) {
        SetRootRect(rootSize.Width(), rootSize.Height(), -offsetFix);
    } else if ((positionY + height > rootSize.Height() - keyboardHeight &&
                   positionY < rootSize.Height() - keyboardHeight && height < keyboardHeight / 2.0f) &&
               NearZero(rootNode_->GetGeometryNode()->GetFrameOffset().GetY())) {
        SetRootRect(rootSize.Width(), rootSize.Height(), -height - offsetFix / 2.0f);
    }
}

bool PipelineContext::OnBackPressed()
{
    LOGD("OnBackPressed");
    CHECK_RUN_ON(PLATFORM);
    auto frontend = weakFrontend_.Upgrade();
    if (!frontend) {
        // return back.
        return false;
    }

    // If the tag of the last child of the rootnode is video, exit full screen.
    if (fullScreenManager_->OnBackPressed()) {
        LOGI("Exit full screen: back press accepted");
        return true;
    }

    // if has sharedTransition, back press will stop the sharedTransition
    if (sharedTransitionManager_->OnBackPressed()) {
        LOGI("sharedTransition stop: back press accepted");
        return true;
    }

    // if has popup, back press would hide popup and not trigger page back
    auto hasOverlay = false;
    taskExecutor_->PostSyncTask(
        [weakOverlay = AceType::WeakClaim(AceType::RawPtr(overlayManager_)), &hasOverlay]() {
            auto overlay = weakOverlay.Upgrade();
            CHECK_NULL_VOID_NOLOG(overlay);
            hasOverlay = overlay->RemoveOverlay();
        },
        TaskExecutor::TaskType::UI);
    if (hasOverlay) {
        LOGI("popup hidden: back press accepted");
        return true;
    }

    auto result = false;
    taskExecutor_->PostSyncTask(
        [weakFrontend = weakFrontend_, weakPipelineContext = WeakClaim(this), &result]() {
            auto frontend = weakFrontend.Upgrade();
            if (!frontend) {
                LOGW("frontend is nullptr");
                result = false;
                return;
            }
            auto context = weakPipelineContext.Upgrade();
            if (!context) {
                LOGW("pipelineContext is nullptr");
                result = false;
                return;
            }
            if (context->GetNavDestinationBackButtonNode()) {
                auto navDestinationNode =
                    AceType::DynamicCast<NavDestinationGroupNode>(context->GetNavDestinationBackButtonNode());
                if (navDestinationNode->GetNavDestinationBackButtonEvent()) {
                    GestureEvent gestureEvent;
                    navDestinationNode->GetNavDestinationBackButtonEvent()(gestureEvent);
                    result = true;
                }
            }
        },
        TaskExecutor::TaskType::UI);

    if (result) {
        // user accept
        LOGI("CallRouterBackToPopPage(): frontend accept");
        return true;
    }

    taskExecutor_->PostSyncTask(
        [weakFrontend = weakFrontend_, weakPipelineContext = WeakClaim(this), &result]() {
            auto frontend = weakFrontend.Upgrade();
            if (!frontend) {
                LOGW("frontend is nullptr");
                result = false;
                return;
            }
            result = frontend->OnBackPressed();
        },
        TaskExecutor::TaskType::JS);

    if (result) {
        // user accept
        LOGI("CallRouterBackToPopPage(): frontend accept");
        return true;
    }
    LOGI("CallRouterBackToPopPage(): return platform consumed");
    return false;
}

RefPtr<FrameNode> PipelineContext::GetNavDestinationBackButtonNode()
{
    auto lastPage = stageManager_->GetLastPage();
    CHECK_NULL_RETURN(lastPage, nullptr);
    auto navigationNode = lastPage->FindChildNodeOfClass<NavigationGroupNode>();
    CHECK_NULL_RETURN(navigationNode, nullptr);
    auto navigationContentNode = navigationNode->GetContentNode();
    CHECK_NULL_RETURN(navigationContentNode, nullptr);
    auto navDestinationNode = navigationContentNode->FindChildNodeOfClass<NavDestinationGroupNode>();
    CHECK_NULL_RETURN(navDestinationNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    CHECK_NULL_RETURN(titleBarNode, nullptr);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    CHECK_NULL_RETURN(backButtonNode, nullptr);
    auto backButtonLayoutProperty = backButtonNode->GetLayoutProperty<ImageLayoutProperty>();
    if (!backButtonLayoutProperty->HasVisibility()) {
        return nullptr;
    }

    if (backButtonLayoutProperty->GetVisibilityValue() != VisibleType::VISIBLE) {
        return nullptr;
    }
    return navDestinationNode;
}

void PipelineContext::OnTouchEvent(const TouchEvent& point, bool isSubPipe)
{
    CHECK_RUN_ON(UI);
    HandleEtsCardTouchEvent(point);
    auto scalePoint = point.CreateScalePoint(GetViewScale());
    LOGD("AceTouchEvent: x = %{public}f, y = %{public}f, type = %{public}zu", scalePoint.x, scalePoint.y,
        scalePoint.type);
    eventManager_->SetInstanceId(GetInstanceId());
    if (scalePoint.type == TouchType::DOWN) {
        isNeedShowFocus_ = false;
        CHECK_NULL_VOID_NOLOG(rootNode_);
        auto rootFocusHub = rootNode_->GetFocusHub();
        if (rootFocusHub) {
            rootFocusHub->ClearAllFocusState();
        }

        LOGD("receive touch down event, first use touch test to collect touch event target");
        TouchRestrict touchRestrict { TouchRestrict::NONE };
        touchRestrict.sourceType = point.sourceType;
        touchRestrict.touchEvent = point;
        eventManager_->TouchTest(scalePoint, rootNode_, touchRestrict, GetPluginEventOffset(), viewScale_, isSubPipe);

        for (const auto& weakContext : touchPluginPipelineContext_) {
            auto pipelineContext = DynamicCast<OHOS::Ace::PipelineBase>(weakContext.Upgrade());
            if (!pipelineContext) {
                continue;
            }
            auto pluginPoint =
                point.UpdateScalePoint(viewScale_, static_cast<float>(pipelineContext->GetPluginEventOffset().GetX()),
                    static_cast<float>(pipelineContext->GetPluginEventOffset().GetY()), point.id);
            // eventManager_ instance Id may changed.
            pipelineContext->OnTouchEvent(pluginPoint, true);
        }

        // restore instance Id.
        eventManager_->SetInstanceId(GetInstanceId());
    }
    if (isSubPipe) {
        return;
    }

    if (scalePoint.type == TouchType::MOVE) {
        touchEvents_.emplace_back(point);
        hasIdleTasks_ = true;
        window_->RequestFrame();
        return;
    }

    std::optional<TouchEvent> lastMoveEvent;
    if (scalePoint.type == TouchType::UP && !touchEvents_.empty()) {
        for (auto iter = touchEvents_.begin(); iter != touchEvents_.end(); ++iter) {
            auto movePoint = (*iter).CreateScalePoint(GetViewScale());
            if (scalePoint.id == movePoint.id) {
                lastMoveEvent = movePoint;
                touchEvents_.erase(iter++);
            }
        }
        if (lastMoveEvent.has_value()) {
            eventManager_->DispatchTouchEvent(lastMoveEvent.value());
        }
    }

    eventManager_->DispatchTouchEvent(scalePoint);

    if ((scalePoint.type == TouchType::UP) || (scalePoint.type == TouchType::CANCEL)) {
        // need to reset touchPluginPipelineContext_ for next touch down event.
        touchPluginPipelineContext_.clear();
        RemoveEtsCardTouchEventCallback(point.id);
    }

    hasIdleTasks_ = true;
    window_->RequestFrame();
}

void PipelineContext::OnSurfaceDensityChanged(double density)
{
    CHECK_RUN_ON(UI);
    LOGI("OnSurfaceDensityChanged density_(%{public}lf)", density_);
    LOGI("OnSurfaceDensityChanged dipScale_(%{public}lf)", dipScale_);
    density_ = density;
    if (!NearZero(viewScale_)) {
        LOGI("OnSurfaceDensityChanged viewScale_(%{public}lf)", viewScale_);
        dipScale_ = density_ / viewScale_;
    }
}

bool PipelineContext::OnDumpInfo(const std::vector<std::string>& params) const
{
    ACE_DCHECK(!params.empty());

    if (params[0] == "-element") {
        if (params.size() > 1 && params[1] == "-lastpage") {
            auto lastPage = stageManager_->GetLastPage();
            if (lastPage) {
                lastPage->DumpTree(0);
            }
        } else {
            rootNode_->DumpTree(0);
        }
    } else if (params[0] == "-render") {
    } else if (params[0] == "-focus") {
        if (rootNode_->GetFocusHub()) {
            rootNode_->GetFocusHub()->DumpFocusTree(0);
        }
    } else if (params[0] == "-layer") {
    } else if (params[0] == "-frontend") {
#ifndef WEARABLE_PRODUCT
    } else if (params[0] == "-multimodal") {
#endif
    } else if (params[0] == "-accessibility" || params[0] == "-inspector") {
        auto accessibilityManager = GetAccessibilityManager();
        if (accessibilityManager) {
            accessibilityManager->OnDumpInfo(params);
        }
    } else if (params[0] == "-rotation" && params.size() >= 2) {
    } else if (params[0] == "-animationscale" && params.size() >= 2) {
    } else if (params[0] == "-velocityscale" && params.size() >= 2) {
    } else if (params[0] == "-scrollfriction" && params.size() >= 2) {
    } else if (params[0] == "-threadstuck" && params.size() >= 3) {
    } else {
        return false;
    }
    return true;
}

void PipelineContext::FlushTouchEvents()
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(rootNode_);
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

void PipelineContext::OnMouseEvent(const MouseEvent& event)
{
    CHECK_RUN_ON(UI);

    if ((event.action == MouseAction::RELEASE || event.action == MouseAction::PRESS ||
            event.action == MouseAction::MOVE) &&
        (event.button == MouseButton::LEFT_BUTTON || event.pressedButtons == MOUSE_PRESS_LEFT)) {
        auto touchPoint = event.CreateTouchPoint();
        OnTouchEvent(touchPoint);
    }

    CHECK_NULL_VOID(rootNode_);
    auto scaleEvent = event.CreateScaleEvent(viewScale_);
    LOGD(
        "MouseEvent (x,y): (%{public}f,%{public}f), button: %{public}d, action: %{public}d, pressedButtons: %{public}d",
        scaleEvent.x, scaleEvent.y, scaleEvent.button, scaleEvent.action, scaleEvent.pressedButtons);
    TouchRestrict touchRestrict { TouchRestrict::NONE };
    touchRestrict.sourceType = event.sourceType;
    touchRestrict.hitTestType = SourceType::MOUSE;
    eventManager_->MouseTest(scaleEvent, rootNode_, touchRestrict);
    eventManager_->DispatchMouseEventNG(scaleEvent);
    eventManager_->DispatchMouseHoverEventNG(scaleEvent);
    eventManager_->DispatchMouseHoverAnimationNG(scaleEvent);
    window_->RequestFrame();
}

bool PipelineContext::ChangeMouseStyle(int32_t nodeId, MouseFormat format)
{
    if (mouseStyleNodeId_ != nodeId) {
        return false;
    }
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    return mouseStyle->ChangePointerStyle(GetWindowId(), format);
}

bool PipelineContext::OnKeyEvent(const KeyEvent& event)
{
    eventManager_->SetPressedKeyCodes(event.pressedCodes);
    // Need update while key tab pressed
    if (!isNeedShowFocus_ && event.action == KeyAction::DOWN &&
        (event.IsKey({ KeyCode::KEY_TAB }) || event.IsDirectionalKey())) {
        isNeedShowFocus_ = true;
        auto rootFocusHub = rootNode_->GetFocusHub();
        if (rootFocusHub) {
            rootFocusHub->PaintAllFocusState();
        }
        return true;
    }
    auto lastPage = stageManager_->GetLastPage();
    auto mainNode = lastPage ? lastPage : rootNode_;
    CHECK_NULL_RETURN(mainNode, false);
    if (!eventManager_->DispatchTabIndexEventNG(event, rootNode_, mainNode)) {
        return eventManager_->DispatchKeyEventNG(event, rootNode_);
    }
    return true;
}

bool PipelineContext::RequestDefaultFocus()
{
    CHECK_NULL_RETURN(stageManager_, false);
    auto lastPage = stageManager_->GetLastPage();
    auto mainNode = lastPage ? lastPage : rootNode_;
    CHECK_NULL_RETURN(mainNode, false);
    auto mainFocusHub = mainNode->GetFocusHub();
    CHECK_NULL_RETURN(mainFocusHub, false);
    if (mainFocusHub->IsDefaultHasFocused()) {
        LOGD("RequestDefaultFocus: %{public}s/%{public}d 's default focus node has be focused.",
            mainNode->GetTag().c_str(), mainNode->GetId());
        return false;
    }
    auto defaultFocusNode = mainFocusHub->GetChildFocusNodeByType();
    if (!defaultFocusNode) {
        LOGD("RequestDefaultFocus: %{public}s/%{public}d do not has default focus node.", mainNode->GetTag().c_str(),
            mainNode->GetId());
        return false;
    }
    if (!defaultFocusNode->IsFocusableWholePath()) {
        LOGD("RequestDefaultFocus: %{public}s/%{public}d 's default focus node is not focusable.",
            mainNode->GetTag().c_str(), mainNode->GetId());
        return false;
    }
    mainFocusHub->SetIsDefaultHasFocused(true);
    LOGD("Focus: request default focus node %{public}s", defaultFocusNode->GetFrameName().c_str());
    return defaultFocusNode->RequestFocusImmediately();
}

bool PipelineContext::RequestFocus(const std::string& targetNodeId)
{
    CHECK_NULL_RETURN(rootNode_, false);
    auto focusHub = rootNode_->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    auto currentFocusChecked = focusHub->RequestFocusImmediatelyById(targetNodeId);
    if (!isSubPipeline_ || currentFocusChecked) {
        LOGI("Request focus in current pipeline return is %{public}d", currentFocusChecked);
        return currentFocusChecked;
    }
    LOGI("Request focus in parent pipeline");
    auto parentPipelineBase = parentPipeline_.Upgrade();
    CHECK_NULL_RETURN(parentPipelineBase, false);
    auto parentPipelineContext = AceType::DynamicCast<NG::PipelineContext>(parentPipelineBase);
    CHECK_NULL_RETURN(parentPipelineContext, false);
    return parentPipelineContext->RequestFocus(targetNodeId);
}

void PipelineContext::AddDirtyFocus(const RefPtr<FrameNode>& node)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(node);
    if (node->GetFocusType() == FocusType::NODE) {
        dirtyFocusNode_ = WeakClaim(RawPtr(node));
    } else {
        dirtyFocusScope_ = WeakClaim(RawPtr(node));
    }
    window_->RequestFrame();
}

void PipelineContext::RootLostFocus(BlurReason reason) const
{
    CHECK_NULL_VOID(rootNode_);
    auto focusHub = rootNode_->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->LostFocus(reason);
    CHECK_NULL_VOID(overlayManager_);
    overlayManager_->HideAllMenus();
    overlayManager_->HideAllPopups();
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
    auto scaleEvent = event.CreateScaleEvent(viewScale_);
    LOGD("AxisEvent (x,y): (%{public}f,%{public}f), action: %{public}d, horizontalAxis: %{public}f, verticalAxis: "
         "%{public}f, pinchAxisScale: %{public}f",
        scaleEvent.x, scaleEvent.y, scaleEvent.action, scaleEvent.horizontalAxis, scaleEvent.verticalAxis,
        scaleEvent.pinchAxisScale);

    if (event.action == AxisAction::BEGIN) {
        TouchRestrict touchRestrict { TouchRestrict::NONE };
        touchRestrict.sourceType = event.sourceType;
        touchRestrict.hitTestType = SourceType::TOUCH;
        eventManager_->TouchTest(scaleEvent, rootNode_, touchRestrict);
    }
    eventManager_->DispatchTouchEvent(scaleEvent);

    if (event.action == AxisAction::BEGIN || event.action == AxisAction::UPDATE) {
        eventManager_->AxisTest(scaleEvent, rootNode_);
        eventManager_->DispatchAxisEvent(scaleEvent);
    }

    auto mouseEvent = ConvertAxisToMouse(event);
    OnMouseEvent(mouseEvent);
}

void PipelineContext::AddVisibleAreaChangeNode(
    const RefPtr<FrameNode>& node, double ratio, const VisibleRatioCallback& callback)
{
    CHECK_NULL_VOID(node);
    VisibleCallbackInfo info;
    info.callback = callback;
    info.visibleRatio = ratio;
    info.isCurrentVisible = false;
    auto iter = visibleAreaChangeNodes_.find(node->GetId());
    if (iter != visibleAreaChangeNodes_.end()) {
        auto& callbackList = iter->second;
        callbackList.emplace_back(info);
    } else {
        std::list<VisibleCallbackInfo> callbackList;
        callbackList.emplace_back(info);
        visibleAreaChangeNodes_[node->GetId()] = callbackList;
    }
}

void PipelineContext::RemoveVisibleAreaChangeNode(int32_t nodeId)
{
    visibleAreaChangeNodes_.erase(nodeId);
}

void PipelineContext::HandleVisibleAreaChangeEvent()
{
    if (visibleAreaChangeNodes_.empty()) {
        return;
    }
    for (auto& visibleChangeNode : visibleAreaChangeNodes_) {
        auto uiNode = ElementRegister::GetInstance()->GetUINodeById(visibleChangeNode.first);
        if (!uiNode) {
            continue;
        }
        auto frameNode = AceType::DynamicCast<FrameNode>(uiNode);
        if (!frameNode) {
            continue;
        }
        frameNode->TriggerVisibleAreaChangeCallback(visibleChangeNode.second);
    }
}

void PipelineContext::AddOnAreaChangeNode(int32_t nodeId)
{
    onAreaChangeNodeIds_.emplace(nodeId);
}

void PipelineContext::RemoveOnAreaChangeNode(int32_t nodeId)
{
    onAreaChangeNodeIds_.erase(nodeId);
}

void PipelineContext::HandleOnAreaChangeEvent()
{
    if (onAreaChangeNodeIds_.empty()) {
        return;
    }
    for (const auto& nodeId : onAreaChangeNodeIds_) {
        auto uiNode = ElementRegister::GetInstance()->GetUINodeById(nodeId);
        if (!uiNode) {
            continue;
        }
        auto frameNode = AceType::DynamicCast<FrameNode>(uiNode);
        if (!frameNode) {
            continue;
        }
        frameNode->TriggerOnAreaChangeCallback();
    }
}

void PipelineContext::OnShow()
{
    CHECK_RUN_ON(UI);
    onShow_ = true;
    window_->OnShow();
    window_->RequestFrame();
    FlushWindowStateChangedCallback(true);
}

void PipelineContext::OnHide()
{
    CHECK_RUN_ON(UI);
    onShow_ = false;
    window_->RequestFrame();
    window_->OnHide();
    OnVirtualKeyboardAreaChange(Rect());
    FlushWindowStateChangedCallback(false);
}

void PipelineContext::WindowFocus(bool isFocus)
{
    CHECK_RUN_ON(UI);
    onFocus_ = isFocus;
    if (!isFocus) {
        LOGD("WindowFocus: isFocus_ is %{public}d. Lost all focus.", onFocus_);
        RootLostFocus(BlurReason::WINDOW_BLUR);
        NotifyPopupDismiss();
        OnVirtualKeyboardAreaChange(Rect());
    }
    if (onFocus_ && onShow_) {
        LOGD("WindowFocus: onFocus_ and onShow_ are both true. Do FlushFocus().");
        FlushFocus();
    } else {
        LOGD("WindowFocus: onFocus_ is %{public}d, onShow_ is %{public}d.", onFocus_, onShow_);
    }
    FlushWindowFocusChangedCallback(isFocus);
}

void PipelineContext::ShowContainerTitle(bool isShow)
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        LOGW("ShowContainerTitle failed, Window modal is not container.");
        return;
    }
    auto containerNode = AceType::DynamicCast<FrameNode>(rootNode_->GetChildren().front());
    CHECK_NULL_VOID(containerNode);
    containerNode->GetPattern<ContainerModalPattern>()->ShowTitle(isShow);
}

void PipelineContext::SetContainerWindow(bool isShow)
{
#ifdef ENABLE_ROSEN_BACKEND
    if (!IsJsCard()) {
        auto rsWindow = static_cast<RosenWindow*>(GetWindow());
        if (rsWindow) {
            auto rsUIDirector = rsWindow->GetRsUIDirector();
            if (rsUIDirector) {
                rsUIDirector->SetContainerWindow(isShow, density_); // set container window show state to render service
            }
        }
    }
#endif
}

void PipelineContext::SetAppBgColor(const Color& color)
{
    appBgColor_ = color;
#ifdef ENABLE_ROSEN_BACKEND
    if (!IsJsCard()) {
        auto rsWindow = static_cast<RosenWindow*>(GetWindow());
        if (rsWindow) {
            auto rsUIDirector = rsWindow->GetRsUIDirector();
            if (rsUIDirector) {
                rsUIDirector->SetAbilityBGAlpha(appBgColor_.GetAlpha());
            }
        }
    }
#endif
    CHECK_NULL_VOID(rootNode_);
    auto rootPattern = rootNode_->GetPattern<RootPattern>();
    CHECK_NULL_VOID(rootPattern);
    rootPattern->SetAppBgColor(appBgColor_, windowModal_ == WindowModal::CONTAINER_MODAL);
}

void PipelineContext::SetAppTitle(const std::string& title)
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        LOGW("SetAppTitle failed, Window modal is not container.");
        return;
    }
    auto containerNode = AceType::DynamicCast<FrameNode>(rootNode_->GetChildren().front());
    CHECK_NULL_VOID(containerNode);
    containerNode->GetPattern<ContainerModalPattern>()->SetAppTitle(title);
}

void PipelineContext::SetAppIcon(const RefPtr<PixelMap>& icon)
{
    if (windowModal_ != WindowModal::CONTAINER_MODAL) {
        LOGW("SetAppIcon failed, Window modal is not container.");
        return;
    }
    auto containerNode = AceType::DynamicCast<FrameNode>(rootNode_->GetChildren().front());
    CHECK_NULL_VOID(containerNode);
    containerNode->GetPattern<ContainerModalPattern>()->SetAppIcon(icon);
}

void PipelineContext::FlushReload()
{
    LOGI("PipelineContext::FlushReload.");
    AnimationOption option;
    const int32_t duration = 400;
    option.SetDuration(duration);
    option.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(option, [weak = WeakClaim(this)]() {
        auto pipeline = weak.Upgrade();
        CHECK_NULL_VOID(pipeline);
        pipeline->stageManager_->ReloadStage();
        pipeline->FlushUITasks();
    });
}

void PipelineContext::Destroy()
{
    CHECK_RUN_ON(UI);
    LOGI("PipelineContext::Destroy begin.");
    taskScheduler_.CleanUp();
    scheduleTasks_.clear();
    dirtyNodes_.clear();
    rootNode_.Reset();
    stageManager_.Reset();
    overlayManager_.Reset();
    sharedTransitionManager_.Reset();
    dragDropManager_.Reset();
    selectOverlayManager_.Reset();
    fullScreenManager_.Reset();
    touchEvents_.clear();
    buildFinishCallbacks_.clear();
    onWindowStateChangedCallbacks_.clear();
    onWindowFocusChangedCallbacks_.clear();
    nodesToNotifyMemoryLevel_.clear();
    dirtyFocusNode_.Reset();
    dirtyFocusScope_.Reset();
    PipelineBase::Destroy();
    LOGI("PipelineContext::Destroy end.");
}

void PipelineContext::AddBuildFinishCallBack(std::function<void()>&& callback)
{
    buildFinishCallbacks_.emplace_back(std::move(callback));
}

void PipelineContext::AddWindowStateChangedCallback(int32_t nodeId)
{
    onWindowStateChangedCallbacks_.emplace(nodeId);
}

void PipelineContext::RemoveWindowStateChangedCallback(int32_t nodeId)
{
    onWindowStateChangedCallbacks_.erase(nodeId);
}

void PipelineContext::FlushWindowStateChangedCallback(bool isShow)
{
    auto iter = onWindowStateChangedCallbacks_.begin();
    while (iter != onWindowStateChangedCallbacks_.end()) {
        auto node = ElementRegister::GetInstance()->GetUINodeById(*iter);
        if (!node) {
            iter = onWindowStateChangedCallbacks_.erase(iter);
        } else {
            if (isShow) {
                node->OnWindowShow();
            } else {
                node->OnWindowHide();
            }
            ++iter;
        }
    }
}

void PipelineContext::AddWindowFocusChangedCallback(int32_t nodeId)
{
    onWindowFocusChangedCallbacks_.emplace_back(nodeId);
}

void PipelineContext::RemoveWindowFocusChangedCallback(int32_t nodeId)
{
    onWindowFocusChangedCallbacks_.remove(nodeId);
}

void PipelineContext::FlushWindowFocusChangedCallback(bool isFocus)
{
    auto iter = onWindowFocusChangedCallbacks_.begin();
    while (iter != onWindowFocusChangedCallbacks_.end()) {
        auto node = ElementRegister::GetInstance()->GetUINodeById(*iter);
        if (!node) {
            iter = onWindowFocusChangedCallbacks_.erase(iter);
        } else {
            if (isFocus) {
                node->OnWindowFocused();
            } else {
                node->OnWindowUnfocused();
            }
            ++iter;
        }
    }
}

void PipelineContext::OnDragEvent(int32_t x, int32_t y, DragEventAction action)
{
    auto manager = GetDragDropManager();
    CHECK_NULL_VOID(manager);
    if (manager->IsDragged()) {
        LOGI("current context is the source of drag");
        return;
    }

    std::string extraInfo;
    manager->GetExtraInfoFromClipboard(extraInfo);

    if (action == DragEventAction::DRAG_EVENT_END) {
        manager->OnDragEnd(static_cast<float>(x), static_cast<float>(y), extraInfo);
        manager->RestoreClipboardData();
        return;
    }

    manager->OnDragMove(static_cast<float>(x), static_cast<float>(y), extraInfo);
}

void PipelineContext::AddNodesToNotifyMemoryLevel(int32_t nodeId)
{
    nodesToNotifyMemoryLevel_.emplace_back(nodeId);
}

void PipelineContext::RemoveNodesToNotifyMemoryLevel(int32_t nodeId)
{
    nodesToNotifyMemoryLevel_.remove(nodeId);
}

void PipelineContext::NotifyMemoryLevel(int32_t level)
{
    LOGI("PipelineContext: NotifyMemoryLevel called");
    auto iter = nodesToNotifyMemoryLevel_.begin();
    while (iter != nodesToNotifyMemoryLevel_.end()) {
        auto node = ElementRegister::GetInstance()->GetUINodeById(*iter);
        if (!node) {
            iter = nodesToNotifyMemoryLevel_.erase(iter);
        } else {
            node->OnNotifyMemoryLevel(level);
            ++iter;
        }
    }
}
void PipelineContext::AddPredictTask(PredictTask&& task)
{
    taskScheduler_.AddPredictTask(std::move(task));
    window_->RequestFrame();
}

void PipelineContext::OnIdle(int64_t deadline)
{
    if (deadline == 0) {
        return;
    }
    CHECK_RUN_ON(UI);
    ACE_SCOPED_TRACE("OnIdle, targettime:%" PRId64 "", deadline);
    taskScheduler_.FlushPredictTask(deadline - TIME_THRESHOLD);
}

void PipelineContext::Finish(bool /*autoFinish*/) const
{
    CHECK_RUN_ON(UI);
    if (finishEventHandler_) {
        LOGI("call finishEventHandler");
        finishEventHandler_();
    } else {
        LOGE("fail to finish current context due to handler is nullptr");
    }
}

void PipelineContext::AddAfterLayoutTask(std::function<void()>&& task)
{
    taskScheduler_.AddAfterLayoutTask(std::move(task));
}

} // namespace OHOS::Ace::NG
