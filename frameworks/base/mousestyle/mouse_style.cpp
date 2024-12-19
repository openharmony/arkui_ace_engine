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

#include "base/mousestyle/mouse_style.h"
#include "mouse_style.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t MOUSESTYLE_LOG_LIMIT = 10;
}
bool MouseStyleManager::SetMouseFormat(int32_t windowId, int32_t nodeId, MouseFormat mouseFormat,
    bool isByPass, MouseStyleChangeReason reason)
{
    TAG_LOGD(AceLogTag::ACE_MOUSE, "SetMouseFormat windowId = %{public}d, nodeId = %{public}d, "
        "mouseFormat = %{public}d, reason = %{public}d", windowId, nodeId, mouseFormat, reason);
    if (isByPass) {
        return false;
    }
    if (userSetCursor_ && reason != MouseStyleChangeReason::USER_SET_MOUSESTYLE) {
        return false;
    }
    if (!userSetCursor_ && (!mouseStyleNodeId_.has_value() ||
        mouseStyleNodeId_.value() != nodeId)) {
        return false;
    }
    if (!windowId) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, false);
        windowId = static_cast<int32_t>(pipelineContext->GetFocusWindowId());
    }

    MouseStyleChangeLog mouseStyleChangeLog;
    mouseStyleChangeLog.windowId = windowId;
    mouseStyleChangeLog.changeNodeId = nodeId;
    if (vsyncMouseStyleChange_.empty()) {
        mouseStyleChangeLog.beforeMouseStyle = mouseFormat_;
    } else {
        mouseStyleChangeLog.beforeMouseStyle = vsyncMouseStyleChange_.back().afterMouseStyle;
    }
    mouseStyleChangeLog.afterMouseStyle = mouseFormat;
    mouseStyleChangeLog.reason = reason;
    vsyncMouseStyleChange_.push_back(mouseStyleChangeLog);
    return true;
}
    
void MouseStyleManager::VsyncMouseFormat()
{
    if (vsyncMouseStyleChange_.empty()) {
        return;
    }

    MouseStyleChangeLog mouseStyleChangeLog;
    mouseStyleChangeLog.beforeMouseStyle = lastVsyncMouseFormat_;
    lastVsyncMouseFormat_ = mouseFormat_;
    MouseStyleChangeReason changeReason = MouseStyleChangeReason::INNER_SET_MOUSESTYLE;
    int32_t changeNodeId = -1;
    int32_t windowId = -1;
    for (const auto& iter : vsyncMouseStyleChange_) {
        if (iter.reason >= changeReason) {
            mouseFormat_ = iter.afterMouseStyle;
            windowId = iter.windowId;
            changeNodeId = iter.changeNodeId;
            changeReason = iter.reason;
        }
    }
    mouseStyleChangeLog.afterMouseStyle = mouseFormat_;
    mouseStyleChangeLog.changeNodeId = changeNodeId;
    mouseStyleChangeLog.reason = changeReason;

    if (mouseFormat_ == lastVsyncMouseFormat_) {
        TAG_LOGI(AceLogTag::ACE_MOUSE, "VsyncMouseFormat mouseFormat_ and "
            "lastVsyncMouseFormat_ = %{public}d is same.", mouseFormat_);
        vsyncMouseStyleChange_.clear();
        return;
    }

    TAG_LOGI(AceLogTag::ACE_MOUSE, "VsyncMouseFormat setPointerStyle, windowId is %{public}d, "
        "nodeId is %{public}d, last vsync mouseFormat is %{public}d, set mouseFormat is %{public}d",
        windowId, changeNodeId, lastVsyncMouseFormat_, mouseFormat_);
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    mouseStyle->SetPointerStyle(static_cast<int32_t>(windowId), mouseFormat_);

    mouseStyleChangeLog_.push_back(mouseStyleChangeLog);
    if (mouseStyleChangeLog_.size() > MOUSESTYLE_LOG_LIMIT) {
        mouseStyleChangeLog_.pop_front();
    }
    vsyncMouseStyleChange_.clear();
}

void MouseStyleManager::DumpMouseStyleChangeLog()
{
    for (const auto& iter : mouseStyleChangeLog_) {
        TAG_LOGI(AceLogTag::ACE_MOUSE, "MouseStyleChangeLog: windowId is %{public}d, "
            "nodeId is %{public}d, beforeMouseStyle is %{public}d, afterMouseStyle is %{public}d",
            iter.windowId, iter.changeNodeId,
            iter.beforeMouseStyle, iter.afterMouseStyle);
    }
}

} // namespace OHOS::Ace