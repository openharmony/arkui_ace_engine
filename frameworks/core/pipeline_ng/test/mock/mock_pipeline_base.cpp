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

#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

#include "base/utils/utils.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NODE_ID = 143;
} // namespace
RefPtr<MockPipelineBase> MockPipelineBase::pipeline_;

void MockPipelineBase::SetUp()
{
    pipeline_ = AceType::MakeRefPtr<MockPipelineBase>();
}

void MockPipelineBase::TearDown()
{
    pipeline_ = nullptr;
}

RefPtr<MockPipelineBase> MockPipelineBase::GetCurrent()
{
    return pipeline_;
}

void MockPipelineBase::SetRootSize(double rootWidth, double rootHeight)
{
    rootWidth_ = rootWidth;
    rootHeight_ = rootHeight;
}

float PipelineContext::GetCurrentRootWidth()
{
    return static_cast<float>(MockPipelineBase::GetCurrent()->rootWidth_);
}

float PipelineContext::GetCurrentRootHeight()
{
    return static_cast<float>(MockPipelineBase::GetCurrent()->rootHeight_);
}

RefPtr<PipelineContext> PipelineContext::GetCurrentContext()
{
    return MockPipelineBase::GetCurrent();
}

void PipelineContext::AddWindowFocusChangedCallback(int32_t nodeId) {}

void PipelineContext::SetupRootElement() {}

void PipelineContext::OnTouchEvent(const TouchEvent& point, bool isSubPipe) {}

void PipelineContext::OnMouseEvent(const MouseEvent& event) {}

void PipelineContext::FlushTouchEvents() {}

void PipelineContext::OnAxisEvent(const AxisEvent& event) {}

void PipelineContext::OnDragEvent(int32_t x, int32_t y, DragEventAction action) {}

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

void PipelineContext::ShowContainerTitle(bool isShow, bool hasDeco) {}

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

void PipelineContext::FlushAnimation(uint64_t nanoTimestamp) {}

void PipelineContext::OnVirtualKeyboardHeightChange(
    float keyboardHeight, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{}

void PipelineContext::OnSurfaceChanged(int32_t width, int32_t height, WindowSizeChangeReason type,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{}

void PipelineContext::OnLayoutCompleted(const std::string& componentId) {}

void PipelineContext::OnDrawCompleted(const std::string& componentId) {}

void PipelineContext::SetNeedRenderNode(const RefPtr<FrameNode>& node) {}

void PipelineContext::OnSurfacePositionChanged(int32_t posX, int32_t posY) {}

void PipelineContext::FlushReload() {}

void PipelineContext::SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize) {}

const RefPtr<SelectOverlayManager>& PipelineContext::GetSelectOverlayManager()
{
    if (selectOverlayManager_) {
        return selectOverlayManager_;
    }
    const std::string rootTag = "root";
    auto root = AceType::MakeRefPtr<FrameNode>(rootTag, -1, AceType::MakeRefPtr<Pattern>(), true);
    selectOverlayManager_ = AceType::MakeRefPtr<SelectOverlayManager>(root);

    // mock the selectOverlayInfo, the SelectOverlayId is NODE_ID
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    SelectHandleInfo firstHandleInfo;
    selectOverlayInfo.firstHandle = firstHandleInfo;
    SelectHandleInfo secondHandleInfo;
    selectOverlayInfo.secondHandle = secondHandleInfo;
    selectOverlayManager_->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);
    return selectOverlayManager_;
}

const RefPtr<DragDropManager>& PipelineContext::GetDragDropManager()
{
    dragDropManager_ = AceType::MakeRefPtr<DragDropManager>();
    return dragDropManager_;
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

// core/pipeline_ng/pipeline_context.h depends on the specific impl
void UITaskScheduler::FlushTask() {}

UITaskScheduler::~UITaskScheduler() = default;

void PipelineContext::AddDirtyLayoutNode(const RefPtr<FrameNode>& dirty) {}

void PipelineContext::AddDirtyRenderNode(const RefPtr<FrameNode>& dirty) {}

const RefPtr<StageManager>& PipelineContext::GetStageManager()
{
    return stageManager_;
}

void PipelineContext::AddBuildFinishCallBack(std::function<void()>&& callback)
{
    buildFinishCallbacks_.emplace_back(std::move(callback));
}

const RefPtr<FullScreenManager>& PipelineContext::GetFullScreenManager()
{
    if (fullScreenManager_) {
        return fullScreenManager_;
    }
    auto root = AceType::MakeRefPtr<FrameNode>("ROOT", -1, AceType::MakeRefPtr<Pattern>(), true);
    fullScreenManager_ = AceType::MakeRefPtr<FullScreenManager>(root);
    return fullScreenManager_;
}

const RefPtr<OverlayManager>& PipelineContext::GetOverlayManager()
{
    if (!overlayManager_) {
        overlayManager_ = AceType::MakeRefPtr<OverlayManager>(nullptr);
    }
    return overlayManager_;
}

void PipelineContext::AddPredictTask(PredictTask&& task) {}

void PipelineContext::AddAfterLayoutTask(std::function<void()>&& task) {}

void PipelineContext::FlushPipelineImmediately() {}

FrameInfo* PipelineContext::GetCurrentFrameInfo(uint64_t recvTime, uint64_t timeStamp)
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

void PipelineContext::UpdateSystemSafeArea(const SafeAreaInsets& systemSafeArea) {};

SafeAreaInsets PipelineContext::GetSystemSafeArea() const
{
    return {};
}

void PipelineContext::UpdateCutoutSafeArea(const SafeAreaInsets& cutoutSafeArea) {};

SafeAreaInsets PipelineContext::GetCutoutSafeArea() const
{
    return {};
}

void PipelineContext::AddWindowSceneTouchEventCallback(int32_t pointId, WindowSceneTouchEventCallback&& callback) {}

SafeAreaInsets PipelineContext::GetSafeArea() const
{
    // top inset = 1
    return SafeAreaInsets({}, { 0, 1 }, {}, {});
}

void PipelineContext::AddFontNodeNG(const WeakPtr<NG::UINode>& node) {}

void PipelineContext::RemoveFontNodeNG(const WeakPtr<NG::UINode>& node) {}
} // namespace OHOS::Ace::NG

namespace OHOS::Ace {
class ManagerInterface : public AceType {
    DECLARE_ACE_TYPE(ManagerInterface, AceType);
};
class FontManager : public AceType {
    DECLARE_ACE_TYPE(FontManager, AceType);
};

namespace {
constexpr double DISPLAY_WIDTH = 720;
constexpr double DISPLAY_HEIGHT = 1280;
} // namespace

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
    return NG::MockPipelineBase::GetCurrent();
}

double PipelineBase::NormalizeToPx(const Dimension& dimension) const
{
    if ((dimension.Unit() == DimensionUnit::VP) || (dimension.Unit() == DimensionUnit::FP)) {
        return (dimension.Value() * dipScale_);
    } else if (dimension.Unit() == DimensionUnit::LPX) {
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
    return { 0., 0., DISPLAY_WIDTH, DISPLAY_HEIGHT };
}

void PipelineBase::SetTextFieldManager(const RefPtr<ManagerInterface>& manager)
{
    textFieldManager_ = manager;
}
} // namespace OHOS::Ace
