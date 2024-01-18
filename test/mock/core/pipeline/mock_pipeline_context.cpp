/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "mock_pipeline_context.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double DISPLAY_WIDTH = 720;
constexpr double DISPLAY_HEIGHT = 1280;
} // namespace

RefPtr<MockPipelineContext> MockPipelineContext::pipeline_;
uint64_t UITaskScheduler::frameId_ = 0;

// mock_pipeline_context =======================================================
void MockPipelineContext::SetUp()
{
    pipeline_ = AceType::MakeRefPtr<MockPipelineContext>();
    pipeline_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    pipeline_->rootWidth_ = DISPLAY_WIDTH;
    pipeline_->rootHeight_ = DISPLAY_HEIGHT;
    pipeline_->SetupRootElement();
}

void MockPipelineContext::TearDown()
{
    pipeline_ = nullptr;
}

RefPtr<MockPipelineContext> MockPipelineContext::GetCurrent()
{
    return pipeline_;
}

void MockPipelineContext::SetRootSize(double rootWidth, double rootHeight)
{
    rootWidth_ = rootWidth;
    rootHeight_ = rootHeight;
}
// mock_pipeline_context =======================================================

// pipeline_context ============================================================
float PipelineContext::GetCurrentRootWidth()
{
    return static_cast<float>(MockPipelineContext::GetCurrent()->rootWidth_);
}

float PipelineContext::GetCurrentRootHeight()
{
    return static_cast<float>(MockPipelineContext::GetCurrent()->rootHeight_);
}

std::shared_ptr<NavigationController> PipelineContext::GetNavigationController(
    const std::string& id)
{
    return nullptr;
}

void PipelineContext::AddOrReplaceNavigationNode(
    const std::string &id, const WeakPtr<FrameNode>& node) {}

void PipelineContext::DeleteNavigationNode(const std::string &id) {}

RefPtr<PipelineContext> PipelineContext::GetCurrentContext()
{
    return MockPipelineContext::GetCurrent();
}

RefPtr<PipelineContext> PipelineContext::GetMainPipelineContext()
{
    return MockPipelineContext::GetCurrent();
}

RefPtr<PipelineContext> PipelineContext::GetContextByContainerId(int32_t /* containerId */)
{
    return MockPipelineContext::GetCurrent();
}

void PipelineContext::AddWindowFocusChangedCallback(int32_t nodeId) {}

void PipelineContext::SetupRootElement()
{
    rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<RootPattern>());
    rootNode_->SetHostRootId(GetInstanceId());
    rootNode_->SetHostPageId(-1);
    rootNode_->SetActive(true);
    CalcSize idealSize { CalcLength(rootWidth_), CalcLength(rootHeight_) };
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    layoutConstraint.maxSize = idealSize;
    rootNode_->UpdateLayoutConstraint(layoutConstraint);
    auto rootFocusHub = rootNode_->GetOrCreateFocusHub();
    rootFocusHub->SetFocusType(FocusType::SCOPE);
    rootFocusHub->SetFocusable(true);
    rootNode_->AttachToMainTree();
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<StagePattern>());
    rootNode_->AddChild(stageNode);
    stageManager_ = MakeRefPtr<StageManager>(stageNode);
    overlayManager_ = MakeRefPtr<OverlayManager>(rootNode_);
    fullScreenManager_ = MakeRefPtr<FullScreenManager>(rootNode_);
    selectOverlayManager_ = MakeRefPtr<SelectOverlayManager>(rootNode_);
    dragDropManager_ = MakeRefPtr<DragDropManager>();
    sharedTransitionManager_ = MakeRefPtr<SharedOverlayManager>(rootNode_);
}

void PipelineContext::OnTouchEvent(const TouchEvent& point, const RefPtr<FrameNode>& node, bool isSubPipe) {}

void PipelineContext::OnMouseEvent(const MouseEvent& event, const RefPtr<FrameNode>& node) {}

void PipelineContext::OnAxisEvent(const AxisEvent& event, const RefPtr<FrameNode>& node) {}

void PipelineContext::OnTouchEvent(const TouchEvent& point, bool isSubPipe) {}

void PipelineContext::OnMouseEvent(const MouseEvent& event) {}

void PipelineContext::FlushTouchEvents() {}

void PipelineContext::OnAxisEvent(const AxisEvent& event) {}

void PipelineContext::OnDragEvent(const PointerEvent& pointerEvent, DragEventAction action) {}

void PipelineContext::OnIdle(int64_t deadline) {}

void PipelineContext::Destroy() {}

void PipelineContext::OnShow() {}

void PipelineContext::OnHide() {}

void PipelineContext::RemoveOnAreaChangeNode(int32_t nodeId) {}

void PipelineContext::AddWindowStateChangedCallback(int32_t nodeId) {}

void PipelineContext::RemoveWindowStateChangedCallback(int32_t nodeId) {}

void PipelineContext::AddNodesToNotifyMemoryLevel(int32_t nodeId) {}

void PipelineContext::RemoveNodesToNotifyMemoryLevel(int32_t nodeId) {}

void PipelineContext::WindowFocus(bool isFocus) {}

void PipelineContext::ContainerModalUnFocus() {}

void PipelineContext::ShowContainerTitle(bool isShow, bool hasDeco, bool needUpdate) {}

void PipelineContext::UpdateTitleInTargetPos(bool isShow, int32_t height) {}

void PipelineContext::SetContainerWindow(bool isShow) {}

void PipelineContext::SetAppBgColor(const Color& color) {}

void PipelineContext::SetAppTitle(const std::string& title) {}

void PipelineContext::SetAppIcon(const RefPtr<PixelMap>& icon) {}

void PipelineContext::OnSurfaceDensityChanged(double density) {}

void PipelineContext::SetRootRect(double width, double height, double offset) {}

void PipelineContext::FlushBuild() {}

void PipelineContext::FlushBuildFinishCallbacks()
{
    decltype(buildFinishCallbacks_) buildFinishCallbacks(std::move(buildFinishCallbacks_));
    for (const auto& func : buildFinishCallbacks) {
        if (func) {
            func();
        }
    }
}

void PipelineContext::NotifyMemoryLevel(int32_t level) {}

void PipelineContext::FlushMessages() {}

void PipelineContext::Finish(bool autoFinish) const {}

void PipelineContext::FlushVsync(uint64_t nanoTimestamp, uint32_t frameCount) {}

void PipelineContext::FlushPipelineWithoutAnimation() {}

void PipelineContext::FlushFocus() {}

void PipelineContext::DispatchDisplaySync(uint64_t nanoTimestamp) {}

void PipelineContext::FlushAnimation(uint64_t nanoTimestamp) {}

void PipelineContext::OnVirtualKeyboardHeightChange(
    float keyboardHeight, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{}

void PipelineContext::OnVirtualKeyboardHeightChange(
    float keyboardHeight, double positionY, double height, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{}

void PipelineContext::OnFoldStatusChange(FoldStatus foldStatus) {}

void PipelineContext::OnSurfaceChanged(int32_t width, int32_t height, WindowSizeChangeReason type,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{}

void PipelineContext::OnLayoutCompleted(const std::string& componentId) {}

bool PipelineContext::CheckPageFocus()
{
    return true;
}

void PipelineContext::OnDrawCompleted(const std::string& componentId) {}

void PipelineContext::SetNeedRenderNode(const RefPtr<FrameNode>& node) {}

void PipelineContext::OnSurfacePositionChanged(int32_t posX, int32_t posY) {}

void PipelineContext::FlushReload(const OnConfigurationChange& configurationChange) {}

void PipelineContext::SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize) {}

void PipelineContext::AddAnimationClosure(std::function<void()>&& animation) {}

void PipelineContext::SetCloseButtonStatus(bool isEnabled) {}

const RefPtr<SelectOverlayManager>& PipelineContext::GetSelectOverlayManager()
{
    return selectOverlayManager_;
}

const RefPtr<DragDropManager>& PipelineContext::GetDragDropManager()
{
    return dragDropManager_;
}

const RefPtr<StageManager>& PipelineContext::GetStageManager()
{
    return stageManager_;
}

const RefPtr<FullScreenManager>& PipelineContext::GetFullScreenManager()
{
    return fullScreenManager_;
}

const RefPtr<OverlayManager>& PipelineContext::GetOverlayManager()
{
    return overlayManager_;
}

uint32_t PipelineContext::AddScheduleTask(const RefPtr<ScheduleTask>& task)
{
    return 0;
}

void PipelineContext::RemoveScheduleTask(uint32_t id) {}

void PipelineContext::AddOnAreaChangeNode(int32_t nodeId) {}

bool PipelineContext::OnKeyEvent(const KeyEvent& event)
{
    return false;
}

bool PipelineContext::RequestFocus(const std::string& targetNodeId)
{
    return false;
}

bool PipelineContext::OnDumpInfo(const std::vector<std::string>& params) const
{
    return false;
}

bool PipelineContext::OnBackPressed()
{
    return false;
}

void PipelineContext::AddDirtyFocus(const RefPtr<FrameNode>& node) {}

void PipelineContext::AddDirtyDefaultFocus(const RefPtr<FrameNode>& node) {}

// core/pipeline_ng/pipeline_context.h depends on the specific impl
void UITaskScheduler::FlushTask() {}

UITaskScheduler::UITaskScheduler() {}

UITaskScheduler::~UITaskScheduler() = default;

void PipelineContext::AddDirtyLayoutNode(const RefPtr<FrameNode>& dirty) {}

void PipelineContext::AddDirtyRenderNode(const RefPtr<FrameNode>& dirty) {}

void PipelineContext::AddBuildFinishCallBack(std::function<void()>&& callback)
{
    buildFinishCallbacks_.emplace_back(std::move(callback));
}

void PipelineContext::AddPredictTask(PredictTask&& task) {}

void PipelineContext::AddAfterLayoutTask(std::function<void()>&& task)
{
    if (task) {
        task();
    }
}

void PipelineContext::AddAfterRenderTask(std::function<void()>&& task) {}

void PipelineContext::FlushPipelineImmediately() {}

FrameInfo* PipelineContext::GetCurrentFrameInfo(uint64_t /* recvTime */, uint64_t /* timeStamp */)
{
    return nullptr;
}

void PipelineContext::DumpPipelineInfo() const {}

void PipelineContext::AddVisibleAreaChangeNode(
    const RefPtr<FrameNode>& node, double ratio, const VisibleRatioCallback& callback, bool isUserCallback)
{
    CHECK_NULL_VOID(callback);
    callback(false, 0.0);
    callback(true, ratio);
}

void PipelineContext::RemoveVisibleAreaChangeNode(int32_t nodeId) {}

void PipelineContext::AddFormVisibleChangeNode(const RefPtr<FrameNode>& node, const std::function<void(bool)>& callback)
{}
void PipelineContext::RemoveFormVisibleChangeNode(int32_t nodeId) {}
void PipelineContext::HandleVisibleAreaChangeEvent() {}
void PipelineContext::HandleFormVisibleChangeEvent(bool isVisible) {}

bool PipelineContext::ChangeMouseStyle(int32_t nodeId, MouseFormat format)
{
    return true;
}

void PipelineContext::RestoreNodeInfo(std::unique_ptr<JsonValue> nodeInfo) {}

std::unique_ptr<JsonValue> PipelineContext::GetStoredNodeInfo()
{
    return nullptr;
}

void PipelineContext::StoreNode(int32_t restoreId, const WeakPtr<FrameNode>& node) {}

bool PipelineContext::GetRestoreInfo(int32_t restoreId, std::string& restoreInfo)
{
    return false;
}

void PipelineContext::AddDirtyCustomNode(const RefPtr<UINode>& dirtyNode) {}

void PipelineContext::AddWindowSizeChangeCallback(int32_t nodeId) {}

void PipelineContext::RemoveWindowSizeChangeCallback(int32_t nodeId) {}

void PipelineContext::AddNavigationStateCallback(
    int32_t pageId, int32_t nodeId, const std::function<void()>& callback, bool isOnShow) {}

void PipelineContext::RemoveNavigationStateCallback(int32_t pageId, int32_t nodeId) {}
void PipelineContext::FirePageChanged(int32_t pageId, bool isOnShow) {}
void PipelineContext::UpdateSystemSafeArea(const SafeAreaInsets& systemSafeArea) {};
void PipelineContext::UpdateCutoutSafeArea(const SafeAreaInsets& cutoutSafeArea) {};
void PipelineContext::UpdateNavSafeArea(const SafeAreaInsets& navSafeArea) {};
void PipelineContext::SetEnableKeyBoardAvoidMode(bool value) {};
bool PipelineContext::IsEnableKeyBoardAvoidMode()
{
    return false;
}
void PipelineContext::SetIgnoreViewSafeArea(bool value) {};
void PipelineContext::SetIsLayoutFullScreen(bool value) {};
void PipelineContext::SetIsNeedAvoidWindow(bool value) {};

SafeAreaInsets PipelineContext::GetSafeArea() const
{
    // top inset = 1
    return SafeAreaInsets({}, { 0, 1 }, {}, {});
}

void PipelineContext::AddFontNodeNG(const WeakPtr<UINode>& node) {}

void PipelineContext::RemoveFontNodeNG(const WeakPtr<UINode>& node) {}

void PipelineContext::SetWindowSceneConsumed(bool isConsumed) {}

void PipelineContext::AddIsFocusActiveUpdateEvent(
    const RefPtr<FrameNode>& node, const std::function<void(bool)>& eventCallback)
{}

void PipelineContext::RemoveIsFocusActiveUpdateEvent(const RefPtr<FrameNode>& node) {}

bool PipelineContext::HasDifferentDirectionGesture() const
{
    return false;
}

void PipelineContext::SetJSViewActive(bool active, WeakPtr<CustomNode> custom) {}

RefPtr<FrameNode> PipelineContext::FindNavigationNodeToHandleBack(const RefPtr<UINode>& node)
{
    return nullptr;
}

bool PipelineContext::SetIsFocusActive(bool isFocusActive)
{
    return false;
}

bool PipelineContext::NeedSoftKeyboard()
{
    return false;
}

void PipelineContext::SetCursor(int32_t cursorValue) {}

void PipelineContext::RestoreDefault() {}

void PipelineContext::HandleSubwindow(bool isShow) {}

std::string PipelineContext::GetCurrentExtraInfo()
{
    return std::string();
}

void PipelineContext::CloseFrontendAnimation() {}

void PipelineContext::OpenFrontendAnimation(
    const AnimationOption& option, const RefPtr<Curve>& curve, const std::function<void()>& finishCallback)
{}

bool PipelineContext::IsDragging() const
{
    return false;
}

void PipelineContext::SetIsDragging(bool isDragging) {}

void PipelineContext::ResetDragging() {}

void PipelineContext::UpdateOriginAvoidArea(const Rosen::AvoidArea& avoidArea, uint32_t type) {}

bool PipelineContext::PrintVsyncInfoIfNeed() const
{
    return false;
}

const SerializedGesture& PipelineContext::GetSerializedGesture() const
{
    return serializedGesture_;
}

} // namespace OHOS::Ace::NG
// pipeline_context ============================================================

// pipeline_base ===============================================================
namespace OHOS::Ace {
class ManagerInterface : public AceType {
    DECLARE_ACE_TYPE(ManagerInterface, AceType);
};
class FontManager : public AceType {
    DECLARE_ACE_TYPE(FontManager, AceType);
};

void PipelineBase::OpenImplicitAnimation(
    const AnimationOption& option, const RefPtr<Curve>& curve, const std::function<void()>& finishCallBack)
{}

bool PipelineBase::CloseImplicitAnimation()
{
    return true;
}

RefPtr<Frontend> PipelineBase::GetFrontend() const
{
    return nullptr;
}

void PipelineBase::SetTouchPipeline(const WeakPtr<PipelineBase>& context) {}

RefPtr<ImageCache> PipelineBase::GetImageCache() const
{
    return nullptr;
}

void PipelineBase::OnVsyncEvent(uint64_t nanoTimestamp, uint32_t frameCount) {}

void PipelineBase::SendEventToAccessibility(const AccessibilityEvent& accessibilityEvent) {}

void PipelineBase::OnActionEvent(const std::string& action) {}

void PipelineBase::SetRootSize(double density, int32_t width, int32_t height) {}

RefPtr<PipelineBase> PipelineBase::GetCurrentContext()
{
    return NG::MockPipelineContext::GetCurrent();
}

double PipelineBase::GetCurrentDensity()
{
    auto pipelineContext = NG::MockPipelineContext::GetCurrentContext();
    return pipelineContext ? pipelineContext->GetDensity() : 1.0;
}

double PipelineBase::Px2VpWithCurrentDensity(double px)
{
    double density = GetCurrentDensity();
    return px / density;
}

double PipelineBase::Vp2PxWithCurrentDensity(double vp)
{
    double density = GetCurrentDensity();
    return vp * density;
}

double PipelineBase::NormalizeToPx(const Dimension& dimension) const
{
    if ((dimension.Unit() == DimensionUnit::VP) || (dimension.Unit() == DimensionUnit::FP)) {
        return (dimension.Value() * dipScale_);
    }
    if (dimension.Unit() == DimensionUnit::LPX) {
        return (dimension.Value() * designWidthScale_);
    }
    return dimension.Value();
}

PipelineBase::~PipelineBase() = default;

uint64_t PipelineBase::GetTimeFromExternalTimer()
{
    return 1;
}

void PipelineBase::PostAsyncEvent(TaskExecutor::Task&& task, TaskExecutor::TaskType type) {}

void PipelineBase::PostAsyncEvent(const TaskExecutor::Task& task, TaskExecutor::TaskType type) {}

void PipelineBase::PostSyncEvent(const TaskExecutor::Task& task, TaskExecutor::TaskType type) {}

RefPtr<AccessibilityManager> PipelineBase::GetAccessibilityManager() const
{
    return nullptr;
}

bool PipelineBase::Animate(const AnimationOption& option, const RefPtr<Curve>& curve,
    const std::function<void()>& propertyCallback, const std::function<void()>& finishCallback)
{
    return true;
}

void PipelineBase::Destroy() {}
bool PipelineBase::MaybeRelease()
{
    return AceType::MaybeRelease();
}

void PipelineBase::AddEtsCardTouchEventCallback(int32_t ponitId, EtsCardTouchEventCallback&& callback) {}

double PipelineBase::ConvertPxToVp(const Dimension& dimension) const
{
    if (dimension.Unit() == DimensionUnit::PX) {
        return dimension.Value() / dipScale_;
    }
    return dimension.Value();
}

void PipelineBase::HyperlinkStartAbility(const std::string& address) const {}

void PipelineBase::RequestFrame() {}

Rect PipelineBase::GetCurrentWindowRect() const
{
    return { 0., 0., NG::DISPLAY_WIDTH, NG::DISPLAY_HEIGHT };
}

void PipelineBase::SetTextFieldManager(const RefPtr<ManagerInterface>& manager)
{
    textFieldManager_ = manager;
}

bool PipelineBase::HasFloatTitle() const
{
    return true;
}
} // namespace OHOS::Ace
// pipeline_base ===============================================================
