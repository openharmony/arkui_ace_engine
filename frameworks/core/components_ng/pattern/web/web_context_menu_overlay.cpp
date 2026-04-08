/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/web/web_context_menu_overlay.h"

#include <algorithm>
#include <optional>

#include "base/utils/utils.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/manager/select_content_overlay/select_content_overlay_manager.h"
#include "core/components_ng/pattern/web/web_pattern.h"

namespace OHOS::Ace::NG {
namespace {
std::unordered_set<std::string> SUPPORT_MENU_ITEM = { OH_DEFAULT_CUT, OH_DEFAULT_COPY, OH_DEFAULT_PASTE,
    OH_DEFAULT_SELECT_ALL };
}

bool WebContextMenuOverlay::PreProcessOverlay(const OverlayRequest& request)
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, false);
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    pipeline->AddOnAreaChangeNode(host->GetId());
    SetEnableHandleLevel(true);
    SetEnableSubWindowMenu(true);
    CheckEnableContainerModal();
    return true;
}

bool WebContextMenuOverlay::CheckHandleVisible(const RectF& paintRect)
{
    return false;
}

std::optional<SelectHandleInfo> WebContextMenuOverlay::GetFirstHandleInfo()
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    SelectHandleInfo handleInfo;
    handleInfo.paintRect = {};
    handleInfo.isShow = CheckHandleVisible(handleInfo.paintRect);
    return handleInfo;
}

std::optional<SelectHandleInfo> WebContextMenuOverlay::GetSecondHandleInfo()
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    SelectHandleInfo handleInfo;
    handleInfo.paintRect = {};
    handleInfo.isShow = CheckHandleVisible(handleInfo.paintRect);
    return handleInfo;
}

void WebContextMenuOverlay::OnUpdateMenuInfo(SelectMenuInfo& menuInfo, SelectOverlayDirtyFlag dirtyFlag)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->contextMenuParam_);
    hasText_ = !pattern->contextMenuParam_->GetSelectionText().empty();
    isImage_ = pattern->contextMenuParam_->GetLinkUrl().empty() &&
               (pattern->contextMenuParam_->GetMediaType() ==
                   OHOS::NWeb::NWebContextMenuParams::ContextMenuMediaType::CM_MT_IMAGE);
    isEdit_ = pattern->contextMenuParam_->IsEditable();
    uint32_t flags = static_cast<uint32_t>(pattern->contextMenuParam_->GetEditStateFlags());
    TAG_LOGI(AceLogTag::ACE_WEB,
        "OnUpdateMenuInfo hasText:%{public}d, isImage_:%{public}d isEdit_:%{public}d flags:%{public}d", hasText_,
        isImage_, isEdit_, flags);
    if ((flags & NWeb::NWebContextMenuParams::ContextMenuEditStateFlags::CM_ES_CAN_CUT) && isEdit_ && hasText_) {
        menuInfo.showCut = true;
    } else {
        menuInfo.showCut = false;
    }
    if ((flags & NWeb::NWebContextMenuParams::ContextMenuEditStateFlags::CM_ES_CAN_COPY) && hasText_) {
        menuInfo.showCopy = true;
    } else {
        menuInfo.showCopy = false;
    }
    if ((flags & NWeb::NWebContextMenuParams::ContextMenuEditStateFlags::CM_ES_CAN_PASTE) && isEdit_) {
        menuInfo.showPaste = true;
    } else {
        menuInfo.showPaste = false;
    }
    if ((flags & NWeb::NWebContextMenuParams::ContextMenuEditStateFlags::CM_ES_CAN_SELECT_ALL)) {
        menuInfo.showCopyAll = true;
    } else {
        menuInfo.showCopyAll = false;
    }
    menuInfo.showCopy = menuInfo.showCopy || isImage_;
    menuInfo.menuType = OptionMenuType::MOUSE_MENU;
    menuInfo.menuIsShow = IsShowMenu();
    menuInfo.showCameraInput = false;
}

RectF WebContextMenuOverlay::GetSelectArea()
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_RETURN(pattern, {});
    return pattern->selectArea_;
}

std::string WebContextMenuOverlay::GetSelectedText()
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_RETURN(pattern, "");
    CHECK_NULL_RETURN(pattern->contextMenuParam_, "");
    return pattern->contextMenuParam_->GetSelectionText();
}

void WebContextMenuOverlay::OnMenuItemAction(OptionMenuActionId id, OptionMenuType type)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebContextMenuOverlay::OnMenuItemAction OptionMenuActionId:%{public}d", id);
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->contextMenuResult_);
    switch (id) {
        case OptionMenuActionId::COPY:
            if (isImage_) {
                pattern->contextMenuResult_->CopyImage();
            } else {
                pattern->contextMenuResult_->Copy();
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

void WebContextMenuOverlay::OnHandleMoveDone(const RectF& rect, bool isFirst)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
}

void WebContextMenuOverlay::OnCloseOverlay(OptionMenuType menuType, CloseReason reason, RefPtr<OverlayInfo> info)
{
    BaseTextSelectOverlay::OnCloseOverlay(menuType, reason, info);
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->contextMenuResult_);
    pattern->contextMenuResult_->Cancel();
    pattern->curContextMenuResult_ = false;
}

void WebContextMenuOverlay::OnHandleGlobalTouchEvent(SourceType sourceType, TouchType touchType, bool touchInside)
{
    if (IsMouseClickDown(sourceType, touchType) || IsTouchUp(sourceType, touchType)) {
        CloseOverlay(false, CloseReason::CLOSE_REASON_CLICK_OUTSIDE);
    }
}

void WebContextMenuOverlay::OnUpdateSelectOverlayInfo(SelectOverlayInfo& selectInfo, int32_t requestCode)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    BaseTextSelectOverlay::OnUpdateSelectOverlayInfo(selectInfo, requestCode);
    selectInfo.handlerColor = Color(0xff007dff);
    selectInfo.handleReverse = IsHandleReverse();
    selectInfo.isUsingMouse = true;
    CalculateMenuOffset(selectInfo);
    selectInfo.menuInfo.responseType = static_cast<int32_t>(TextResponseType::RIGHT_CLICK);
    selectInfo.menuInfo.editorType = static_cast<int32_t>(TextSpanType::MIXED);
    selectInfo.callerFrameNode = pattern->GetHost();
    selectInfo.isNewAvoid = true;
    selectInfo.selectArea = pattern->selectArea_;
    selectInfo.recreateOverlay = requestCode == REQUEST_RECREATE;
    SetEditMenuOption(selectInfo);
}

void WebContextMenuOverlay::CalculateMenuOffset(SelectOverlayInfo& selectInfo)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->contextMenuParam_);
    auto offset = pattern->GetCoordinatePoint().value_or(OffsetF());
    selectInfo.rightClickOffset =
        offset + OffsetF(pattern->contextMenuParam_->GetXCoord(), pattern->contextMenuParam_->GetYCoord());
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto windowManager = pipeline->GetWindowManager();
    // Check whether the current window is in container modal mode and floating state, and whether the page offset
    // relative to the window needs to be added.
    auto isContainerModal = pipeline->GetWindowModal() == WindowModal::CONTAINER_MODAL && windowManager &&
                            windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
    if (!isContainerModal) {
        auto stageManager = pipeline->GetStageManager();
        CHECK_NULL_VOID(stageManager);
        auto page = stageManager->GetLastPage();
        CHECK_NULL_VOID(page);
        auto pageOffset = page->GetOffsetRelativeToWindow();
        selectInfo.rightClickOffset = selectInfo.rightClickOffset + pageOffset;
        TAG_LOGD(AceLogTag::ACE_SELECT_OVERLAY, "CreateMenuNode pageOffset:%{public}s", pageOffset.ToString().c_str());
    }
}

std::vector<NG::MenuItemParam> WebContextMenuOverlay::FilterSupportedMenuItems(
    const std::vector<NG::MenuItemParam>& menuItemList)
{
    std::vector<NG::MenuItemParam> supportMenuItems;
    for (const auto& item : menuItemList) {
        if (SUPPORT_MENU_ITEM.find(item.menuOptionsParam.id) != SUPPORT_MENU_ITEM.end()) {
            supportMenuItems.push_back(item);
        }
    }
    return supportMenuItems;
}

std::vector<MenuOptionsParam> WebContextMenuOverlay::BuildMenuOptions(
    const std::vector<NG::MenuItemParam>& menuItemList)
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_RETURN(pattern, std::vector<MenuOptionsParam>());
    if (pattern->onCreateMenuCallback_) {
        auto supportMenuItems = FilterSupportedMenuItems(menuItemList);
        return pattern->onCreateMenuCallback_(supportMenuItems);
    }
    std::vector<MenuOptionsParam> options;
    auto supportMenuItems = FilterSupportedMenuItems(menuItemList);
    for (const auto& item : supportMenuItems) {
        options.push_back(item.menuOptionsParam);
    }
    return options;
}

void WebContextMenuOverlay::SetEditMenuOption(SelectOverlayInfo& selectInfo)
{
    auto createMenuCallback = [weak = AceType::WeakClaim(this)](
                                  const std::vector<NG::MenuItemParam>& menuItemList) -> std::vector<MenuOptionsParam> {
        auto overlay = weak.Upgrade();
        CHECK_NULL_RETURN(overlay, std::vector<MenuOptionsParam>());
        return overlay->BuildMenuOptions(menuItemList);
    };
    selectInfo.onCreateCallback.onCreateMenuCallback = createMenuCallback;
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->onPrepareMenuCallback_) {
        selectInfo.onCreateCallback.onPrepareMenuCallback = pattern->onPrepareMenuCallback_;
        selectInfo.menuInfo.hasOnPrepareMenuCallback = true;
    }
    if (pattern->onMenuItemClick_) {
        selectInfo.onCreateCallback.onMenuItemClick = pattern->onMenuItemClick_;
    }
    auto textRange = [](int32_t& start, int32_t& end) {
        start = -1;
        end = -1;
    };
    selectInfo.onCreateCallback.textRangeCallback = textRange;
}

void WebContextMenuOverlay::OnHandleGlobalEvent(
    const PointF& touchPoint, const PointF& localPoint, const TouchEvent& event)
{
    BaseTextSelectOverlay::OnHandleGlobalEvent(touchPoint, localPoint, event);
    if (event.sourceType == SourceType::TOUCH || event.sourceType == SourceType::TOUCH_PAD) {
        if (event.type == TouchType::DOWN) {
            CloseOverlay(false, CloseReason::CLOSE_REASON_CLICK_OUTSIDE);
        }
    }
}
} // namespace OHOS::Ace::NG