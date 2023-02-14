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

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS ::Ace {
class Window : public AceType {
    DECLARE_ACE_TYPE(Window, AceType);
};

class FontManager : public AceType {
    DECLARE_ACE_TYPE(FontManager, AceType);
};

class ManagerInterface : public AceType {
    DECLARE_ACE_TYPE(ManagerInterface, AceType);
};

class OffscreenCanvas : public AceType {
    DECLARE_ACE_TYPE(Frontend, AceType);
};
} // namespace OHOS::Ace
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NODE_ID = 143;
} // namespace

// static method
float PipelineContext::GetCurrentRootWidth()
{
    return 1.0f;
}

float PipelineContext::GetCurrentRootHeight()
{
    return 1.0f;
}

RefPtr<PipelineContext> PipelineContext::GetCurrentContext()
{
    static RefPtr<PipelineContext> pipeline = AceType::MakeRefPtr<PipelineContext>();
    return pipeline;
}

// non-static method
void PipelineContext::AddWindowFocusChangedCallback(int32_t nodeId) {}

void PipelineContext::SetupRootElement() {}

void PipelineContext::OnTouchEvent(const TouchEvent& point, bool isSubPipe) {}

void PipelineContext::OnMouseEvent(const MouseEvent& event) {}

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

void PipelineContext::ShowContainerTitle(bool isShow) {}

void PipelineContext::SetContainerWindow(bool isShow) {}

void PipelineContext::SetAppBgColor(const Color& color) {}

void PipelineContext::SetAppTitle(const std::string& title) {}

void PipelineContext::SetAppIcon(const RefPtr<PixelMap>& icon) {}

void PipelineContext::OnSurfaceDensityChanged(double density) {}

void PipelineContext::SetRootRect(double width, double height, double offset) {}

void PipelineContext::FlushBuild() {}

void PipelineContext::NotifyMemoryLevel(int32_t level) {}

void PipelineContext::FlushMessages() {}

void PipelineContext::Finish(bool autoFinish) const {}

void PipelineContext::FlushVsync(uint64_t nanoTimestamp, uint32_t frameCount) {}

void PipelineContext::FlushPipelineWithoutAnimation() {}

void PipelineContext::FlushFocus() {}

void PipelineContext::FlushAnimation(uint64_t nanoTimestamp) {}

void PipelineContext::OnVirtualKeyboardHeightChange(float keyboardHeight) {}

void PipelineContext::OnSurfaceChanged(int32_t width, int32_t height, WindowSizeChangeReason type) {}

void PipelineContext::OnSurfacePositionChanged(int32_t posX, int32_t posY) {}

void PipelineContext::FlushReload() {}

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
    selectOverlayManager_->CreateAndShowSelectOverlay(selectOverlayInfo);
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

// core/pipeline_ng/pipeline_context.h depends on the specific impl
void UITaskScheduler::FlushTask() {}

UITaskScheduler::~UITaskScheduler() = default;

void PipelineContext::AddDirtyLayoutNode(const RefPtr<FrameNode>& dirty) {}

void PipelineContext::AddDirtyRenderNode(const RefPtr<FrameNode>& dirty) {}

const RefPtr<StageManager>& PipelineContext::GetStageManager()
{
    auto stageNode = MakeRefPtr<FrameNode>(V2::PAGE_ETS_TAG, -1, MakeRefPtr<PagePattern>(nullptr), true);
    stageManager_ = MakeRefPtr<StageManager>(stageNode);
    return stageManager_;
}

void PipelineContext::AddBuildFinishCallBack(std::function<void()>&& callback) {}

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
    return overlayManager_;
}
void PipelineContext::AddPredictTask(PredictTask&& task) {}

void PipelineContext::FlushPipelineImmediately() {}

void PipelineContext::AddVisibleAreaChangeNode(
    const RefPtr<FrameNode>& node, double ratio, const VisibleRatioCallback& callback)
{}
void PipelineContext::RemoveVisibleAreaChangeNode(int32_t nodeId) {}
} // namespace OHOS::Ace::NG
