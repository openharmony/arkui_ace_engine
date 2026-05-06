/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "mouse_style.h"

#include "base/log/log_wrapper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t MOUSESTYLE_LOG_LIMIT = 10;
}
bool MouseStyleManager::SetMouseFormat(int32_t windowId, int32_t nodeId,
    std::variant<MouseFormat, CustomCursorInfo> mouseFormat, bool isByPass, MouseStyleChangeReason reason)
{
    TAG_LOGD(AceLogTag::ACE_MOUSE, "SetMouseFormat windowId = %{public}d, "
        "nodeId = " SEC_PLD(%{public}d) ", "
        "mouseFormat = %{public}d, reason = %{public}d", windowId, SEC_PARAM(nodeId),
        std::holds_alternative<MouseFormat>(mouseFormat) ? std::get<MouseFormat>(mouseFormat)
                                                         : MouseFormat::CUSTOM_CURSOR, reason);
    if (isByPass) {
        return false;
    }
    if (userSetCursor_ && reason == MouseStyleChangeReason::INNER_SET_MOUSESTYLE) {
        return false;
    }
    if (reason == MouseStyleChangeReason::INNER_SET_MOUSESTYLE &&
        (!mouseStyleNodeId_.has_value() || mouseStyleNodeId_.value() != nodeId)) {
        return false;
    }

    MouseStyleChangeLog mouseStyleChangeLog;
    mouseStyleChangeLog.windowId = windowId;
    mouseStyleChangeLog.changeNodeId = nodeId;
    mouseStyleChangeLog.reason = reason;
    if (vsyncMouseStyleChanges_.empty()) {
        mouseStyleChangeLog.beforeMouseStyle = mouseFormat_;
    } else {
        mouseStyleChangeLog.beforeMouseStyle = vsyncMouseStyleChanges_.back().afterMouseStyle;
    }
    mouseStyleChangeLog.afterMouseStyle = mouseFormat;

    vsyncMouseStyleChanges_.push_back(mouseStyleChangeLog);
    return true;
}

void MouseStyleManager::ProcessVsyncMouseStyleChanges(
    int32_t& windowId, int32_t& changeNodeId, MouseStyleChangeReason& changeReason)
{
    for (const auto& iter : vsyncMouseStyleChanges_) {
        if (iter.reason >= changeReason) {
            mouseFormat_ = iter.afterMouseStyle;
            windowId = iter.windowId;
            changeNodeId = iter.changeNodeId;
            changeReason = iter.reason;
        }
    }
}

bool MouseStyleManager::IsMouseStyleChanged() const
{
    if (std::holds_alternative<CustomCursorInfo>(lastVsyncMouseFormat_) &&
        std::holds_alternative<CustomCursorInfo>(mouseFormat_) &&
        std::get<CustomCursorInfo>(lastVsyncMouseFormat_) == std::get<CustomCursorInfo>(mouseFormat_)) {
        TAG_LOGI(AceLogTag::ACE_MOUSE, "VsyncMouseFormat custom mouse format is same as last vsync");
        return false;
    } else if (std::holds_alternative<MouseFormat>(lastVsyncMouseFormat_) &&
               std::holds_alternative<MouseFormat>(mouseFormat_) &&
               std::get<MouseFormat>(mouseFormat_) == std::get<MouseFormat>(lastVsyncMouseFormat_)) {
        TAG_LOGI(AceLogTag::ACE_MOUSE, "VsyncMouseFormat mouseFormat_ and "
            "lastVsyncMouseFormat_ = %{public}d is same.", std::get<MouseFormat>(mouseFormat_));
        return false;
    }
    return true;
}

void MouseStyleManager::ApplyMouseStyleChange(int32_t windowId)
{
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    if (std::holds_alternative<CustomCursorInfo>(mouseFormat_)) {
        const auto& customCursorInfo = std::get<CustomCursorInfo>(mouseFormat_);
        mouseStyle->SetUeaCustomCursor(
            windowId, customCursorInfo.pixelMap, customCursorInfo.focusX, customCursorInfo.focusY);
    } else {
        mouseStyle->SetPointerStyle(windowId, std::get<MouseFormat>(mouseFormat_));
    }
}

void MouseStyleManager::VsyncMouseFormat()
{
    if (vsyncMouseStyleChanges_.empty()) {
        return;
    }

    MouseStyleChangeLog mouseStyleChangeLog;
    mouseStyleChangeLog.beforeMouseStyle = lastVsyncMouseFormat_;
    lastVsyncMouseFormat_ = mouseFormat_;
    MouseStyleChangeReason changeReason = MouseStyleChangeReason::INNER_SET_MOUSESTYLE;
    int32_t changeNodeId = -1;
    int32_t windowId = -1;
    ProcessVsyncMouseStyleChanges(windowId, changeNodeId, changeReason);
    mouseStyleChangeLog.afterMouseStyle = mouseFormat_;
    mouseStyleChangeLog.changeNodeId = changeNodeId;
    mouseStyleChangeLog.reason = changeReason;

    if (!IsMouseStyleChanged()) {
        vsyncMouseStyleChanges_.clear();
        return;
    }

    TAG_LOGD(AceLogTag::ACE_MOUSE, "VsyncMouseFormat setPointerStyle, windowId is %{public}d, "
        "nodeId is %{public}d, last vsync mouseFormat is %{public}d, set mouseFormat is %{public}d",
        windowId, changeNodeId,
        std::holds_alternative<MouseFormat>(lastVsyncMouseFormat_) ? std::get<MouseFormat>(lastVsyncMouseFormat_)
                                                                   : MouseFormat::CUSTOM_CURSOR,
        std::holds_alternative<MouseFormat>(mouseFormat_) ? std::get<MouseFormat>(mouseFormat_)
                                                          : MouseFormat::CUSTOM_CURSOR);
    ApplyMouseStyleChange(windowId);

    mouseStyleChangeLogs_.push_back(mouseStyleChangeLog);
    if (mouseStyleChangeLogs_.size() > MOUSESTYLE_LOG_LIMIT) {
        mouseStyleChangeLogs_.pop_front();
    }
    vsyncMouseStyleChanges_.clear();
}

void MouseStyleManager::DumpMouseStyleChangeLog()
{
    for (const auto& iter : mouseStyleChangeLogs_) {
        TAG_LOGI(AceLogTag::ACE_MOUSE, "MouseStyleChangeLog: windowId is %{public}d, "
            "nodeId is %{public}d, beforeMouseStyle is %{public}d, afterMouseStyle is %{public}d",
            iter.windowId, iter.changeNodeId,
            std::holds_alternative<MouseFormat>(iter.beforeMouseStyle) ? std::get<MouseFormat>(iter.beforeMouseStyle)
                                                                   : MouseFormat::CUSTOM_CURSOR,
            std::holds_alternative<MouseFormat>(iter.afterMouseStyle) ? std::get<MouseFormat>(iter.afterMouseStyle)
                                                                  : MouseFormat::CUSTOM_CURSOR);
    }
}

} // namespace OHOS::Ace