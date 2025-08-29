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

#include "core/components_ng/pattern/web/web_context_select_overlay.h"

#include <algorithm>
#include <optional>

#include "base/utils/utils.h"
#include "core/components_ng/manager/select_content_overlay/select_content_overlay_manager.h"
#include "core/components_ng/pattern/web/web_pattern.h"

namespace OHOS::Ace::NG {

bool WebContextSelectOverlay::PreProcessOverlay(const OverlayRequest& request)
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, false);
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    pipeline->AddOnAreaChangeNode(host->GetId());
    SetEnableSubWindowMenu(true);
    return true;
}

bool WebContextSelectOverlay::CheckHandleVisible(const RectF& paintRect)
{
    return false;
}

std::optional<SelectHandleInfo> WebContextSelectOverlay::GetFirstHandleInfo()
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    SelectHandleInfo handleInfo;
    handleInfo.paintRect = {};
    handleInfo.isShow = CheckHandleVisible(handleInfo.paintRect);
    return handleInfo;
}

std::optional<SelectHandleInfo> WebContextSelectOverlay::GetSecondHandleInfo()
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    SelectHandleInfo handleInfo;
    handleInfo.paintRect = {};
    handleInfo.isShow = CheckHandleVisible(handleInfo.paintRect);
    return handleInfo;
}

void WebContextSelectOverlay::OnUpdateMenuInfo(SelectMenuInfo& menuInfo, SelectOverlayDirtyFlag dirtyFlag)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->contextMenuParam_);
    hasText_ = !pattern->contextMenuParam_->GetSelectionText().empty();
    hasImage_ = pattern->contextMenuParam_->HasImageContents();
    TAG_LOGI(AceLogTag::ACE_WEB, "OnUpdateMenuInfo hasText:%{public}d, hasImage:%{public}d", hasText_, hasImage_);
    menuInfo.showCopyAll = true;
    if (dirtyFlag == DIRTY_COPY_ALL_ITEM) {
        return;
    }
    menuInfo.showCopy = hasText_ || hasImage_;
    menuInfo.showCut = false;
    menuInfo.showPaste = false;
    menuInfo.menuIsShow = IsShowMenu();
    menuInfo.showCameraInput = false;
}

RectF WebContextSelectOverlay::GetSelectArea()
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_RETURN(pattern, {});
    return pattern->selectArea_;
}

std::string WebContextSelectOverlay::GetSelectedText()
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_RETURN(pattern, "");
    CHECK_NULL_RETURN(pattern->contextMenuParam_, "");
    return pattern->contextMenuParam_->GetSelectionText();
}

void WebContextSelectOverlay::OnMenuItemAction(OptionMenuActionId id, OptionMenuType type)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->contextMenuResult_);
    switch (id) {
        case OptionMenuActionId::COPY:
            if (hasText_) {
                pattern->contextMenuResult_->Copy();
            } else if (hasImage_) {
                pattern->contextMenuResult_->CopyImage();
            }
            CloseOverlay(true, CloseReason::CLOSE_REASON_NORMAL);
            break;
        case OptionMenuActionId::CUT:
            pattern->contextMenuResult_->Cut();
            CloseOverlay(true, CloseReason::CLOSE_REASON_NORMAL);
            break;
        case OptionMenuActionId::PASTE:
            pattern->contextMenuResult_->Paste();
            CloseOverlay(true, CloseReason::CLOSE_REASON_NORMAL);
            break;
        case OptionMenuActionId::SELECT_ALL:
            pattern->contextMenuResult_->SelectAll();
            CloseOverlay(true, CloseReason::CLOSE_REASON_NORMAL);
            break;
        case OptionMenuActionId::DISAPPEAR:
            pattern->contextMenuResult_->Cancel();
            break;
        default:
            TAG_LOGI(AceLogTag::ACE_WEB, "Unsupported menu option id %{public}d", id);
            break;
    }
}

void WebContextSelectOverlay::OnHandleMoveDone(const RectF& rect, bool isFirst)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
}

void WebContextSelectOverlay::OnCloseOverlay(OptionMenuType menuType, CloseReason reason, RefPtr<OverlayInfo> info)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->contextMenuResult_);
    pattern->contextMenuResult_->Cancel();
    pattern->curContextMenuResult_ = false;
}

void WebContextSelectOverlay::OnHandleGlobalTouchEvent(SourceType sourceType, TouchType touchType, bool touchInside)
{
    if (IsMouseClickDown(sourceType, touchType) || IsTouchUp(sourceType, touchType)) {
        CloseOverlay(false, CloseReason::CLOSE_REASON_CLICK_OUTSIDE);
    }
}

void WebContextSelectOverlay::OnUpdateSelectOverlayInfo(SelectOverlayInfo& selectInfo, int32_t requestCode)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->contextMenuParam_);
    selectInfo.handlerColor = Color(0xff007dff);
    selectInfo.handleReverse = IsHandleReverse();
    auto offset = pattern->GetCoordinatePoint().value_or(OffsetF());
    selectInfo.isUsingMouse = true;
    selectInfo.rightClickOffset =
        offset + OffsetF(pattern->contextMenuParam_->GetXCoord(), pattern->contextMenuParam_->GetYCoord());
    selectInfo.menuInfo.responseType = static_cast<int32_t>(TextResponseType::RIGHT_CLICK);
    selectInfo.menuInfo.editorType = static_cast<int32_t>(TextSpanType::MIXED);
    selectInfo.callerFrameNode = pattern->GetHost();
    selectInfo.isNewAvoid = true;
    selectInfo.selectArea = pattern->selectArea_;
    if (IsSingleHandle()) {
        selectInfo.isHandleLineShow = false;
        selectInfo.isSingleHandle = true;
    }
    selectInfo.recreateOverlay = requestCode == REQUEST_RECREATE;
    pattern->CopySelectionMenuParams(selectInfo, elementType_, responseType_);
}
} // namespace OHOS::Ace::NG
