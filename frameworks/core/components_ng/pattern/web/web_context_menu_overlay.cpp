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
#include <codecvt>
#include <iterator>
#include <regex>
#include <string>

#include "base/utils/utils.h"
#include "core/common/ai/text_translation_adapter.h"
#include "core/common/share/text_share_adapter.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/manager/select_content_overlay/select_content_overlay_manager.h"
#include "core/components_ng/pattern/web/web_pattern.h"

namespace OHOS::Ace::NG {
namespace {
using EditFlags = NWeb::NWebContextMenuParams::ContextMenuEditStateFlags;
using CopyOption = NWeb::NWebPreference::CopyOptionMode;

const std::string ASK_CELIA_TAG = "askCelia";
const size_t MAX_TRANSLATE_SIZE = 5000;

std::unordered_set<std::string> SUPPORT_MENU_ITEM = { OH_DEFAULT_CUT, OH_DEFAULT_COPY, OH_DEFAULT_PASTE,
    OH_DEFAULT_SELECT_ALL, OH_DEFAULT_TRANSLATE, OH_DEFAULT_SEARCH, OH_DEFAULT_SHARE, OH_DEFAULT_AI_WRITE,
    OH_DEFAULT_ASK_CELIA };
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
    SelectHandleInfo handleInfo;
    handleInfo.paintRect = {};
    handleInfo.isShow = false;
    return handleInfo;
}

std::optional<SelectHandleInfo> WebContextMenuOverlay::GetSecondHandleInfo()
{
    SelectHandleInfo handleInfo;
    handleInfo.paintRect = {};
    handleInfo.isShow = false;
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
    menuInfo.showCut = (flags & EditFlags::CM_ES_CAN_CUT) && isEdit_ && hasText_;
    menuInfo.showCopy = ((flags & EditFlags::CM_ES_CAN_COPY) && hasText_) || isImage_;
    menuInfo.showPaste = (flags & EditFlags::CM_ES_CAN_PASTE) && isEdit_;
    menuInfo.showCopyAll = (flags & EditFlags::CM_ES_CAN_SELECT_ALL) || !isEdit_;
    auto value = pattern->contextMenuParam_->GetSelectionText();
    auto queryWord = std::regex_replace(value, std::regex("^\\s+|\\s+$"), "");
    bool hasQueryWord = !queryWord.empty();
    auto delegate = pattern->delegate_;
    auto copyOption = delegate ? delegate->GetCopyOptionMode() : CopyOption::NONE;
    bool canCopyOut = copyOption != CopyOption::NONE && copyOption != CopyOption::IN_APP;
    menuInfo.showSearch = canCopyOut && hasQueryWord;
    menuInfo.showTranslate = canCopyOut && hasQueryWord;
    menuInfo.showShare = hasQueryWord && canCopyOut && IsNeedMenuShareForWeb() && IsSupportMenuShare();
    menuInfo.showAIWrite = pattern->IsShowAIWrite() && canCopyOut && isEdit_;
    canShowAIMenu_ = canCopyOut && !isEdit_ && hasQueryWord;
    menuInfo.isAskCeliaEnabled = canShowAIMenu_;
    menuInfo.menuType = OptionMenuType::MOUSE_MENU;
    menuInfo.menuIsShow = IsShowMenu();
    menuInfo.showCameraInput = false;
}

RectF WebContextMenuOverlay::GetSelectArea()
{
    return RectF(rightClickOffset_.GetX(), rightClickOffset_.GetY(), 0.0f, 0.0f);
}

std::string WebContextMenuOverlay::GetSelectedText()
{
    auto pattern = GetPattern<WebPattern>();
    CHECK_NULL_RETURN(pattern, "");
    return pattern->GetSelectInfo();
}

void WebContextMenuOverlay::CloseAndCancel(const RefPtr<WebPattern>& pattern)
{
    CloseOverlay(true, CloseReason::CLOSE_REASON_NORMAL);
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->contextMenuResult_);
    pattern->contextMenuResult_->Cancel();
}

void WebContextMenuOverlay::HandleOnAskCelia(const RefPtr<WebPattern>& pattern)
{
    CHECK_NULL_VOID(pattern);
    auto it = pattern->textDetectResult_.menuOptionAndAction.find(ASK_CELIA_TAG);
    if (it == pattern->textDetectResult_.menuOptionAndAction.end() || it->second.empty()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "HandleOnAskCelia failed no askCelia option.");
        return;
    }
    auto& funcVariant = it->second.begin()->second;
    if (!std::holds_alternative<std::function<void(int, std::string)>>(funcVariant)) {
        TAG_LOGE(AceLogTag::ACE_WEB, "HandleOnAskCelia failed option type error.");
        return;
    }
    auto func = std::get<std::function<void(int, std::string)>>(funcVariant);
    if (!func) {
        TAG_LOGE(AceLogTag::ACE_WEB, "HandleOnAskCelia failed option is null.");
        return;
    }
    TAG_LOGI(AceLogTag::ACE_WEB, "HandleOnAskCelia execute.");
    func(true, GetSelectedText());
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
        case OptionMenuActionId::TRANSLATE:
            HandleOnWebTranslate();
            break;
        case OptionMenuActionId::SEARCH:
            HandleOnSearch();
            break;
        case OptionMenuActionId::SHARE:
            HandleOnShare();
            break;
        case OptionMenuActionId::AI_WRITE:
            pattern->HandleOnAIWrite();
            CloseAndCancel(pattern);
            break;
        case OptionMenuActionId::ASK_CELIA:
            HandleOnAskCelia(pattern);
            CloseAndCancel(pattern);
            break;
        case OptionMenuActionId::DISAPPEAR:
            pattern->contextMenuResult_->Cancel();
            break;
        default:
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
    rightClickOffset_ = selectInfo.rightClickOffset;
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto windowManager = pipeline->GetWindowManager();
    // Check whether the current window is in container modal mode and floating state, and whether the page offset
    // relative to the window needs to be added.
    if (pipeline->GetWindowModal() == WindowModal::CONTAINER_MODAL && windowManager &&
        windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FULLSCREEN) {
        auto stageManager = pipeline->GetStageManager();
        CHECK_NULL_VOID(stageManager);
        auto page = stageManager->GetLastPage();
        CHECK_NULL_VOID(page);
        auto pageOffset = page->GetOffsetRelativeToWindow();
        selectInfo.rightClickOffset = selectInfo.rightClickOffset + pageOffset;
        TAG_LOGD(AceLogTag::ACE_WEB, "CalculateMenuOffset pageOffset:%{public}s", pageOffset.ToString().c_str());
    }
}

std::vector<NG::MenuItemParam> WebContextMenuOverlay::FilterSupportedMenuItems(
    const std::vector<NG::MenuItemParam>& menuItemList)
{
    std::vector<NG::MenuItemParam> supportMenuItems;
    std::copy_if(menuItemList.begin(), menuItemList.end(), std::back_inserter(supportMenuItems),
        [](const auto& item) { return SUPPORT_MENU_ITEM.count(item.menuOptionsParam.id); });
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

bool WebContextMenuOverlay::IsNeedMenuShareForWeb()
{
    const auto& shareContent = GetSelectedText();
    std::string_view sv(shareContent);
    // whitespace characters to trim (same as \s in regex for ASCII whitespace)
    constexpr auto ws = " \t\n\r\f\v";
    const auto start = sv.find_first_not_of(ws);
    if (start == std::string_view::npos) {
        return false;
    }
    const auto end = sv.find_last_not_of(ws);
    const auto trimmedLen = end - start + 1;
    const auto maxShareLength = static_cast<size_t>(TextShareAdapter::GetMaxTextShareLength());
    return trimmedLen <= maxShareLength;
}

void WebContextMenuOverlay::HandleOnWebTranslate()
{
    HideMenu(true);
    auto value = GetSelectedText();
    auto queryWord = std::regex_replace(value, std::regex("^\\s+|\\s+$"), "");
    if (queryWord.empty()) {
        return;
    }
    RectF rect = GetSelectArea();
    EdgeF rectLeftTop = GetSelectAreaStartLeftTop();
    EdgeF rectRightBottom = GetSelectAreaEndRightBottom();
    rect = ConvertWindowToScreenDomain(rect);
    rectLeftTop = ConvertWindowToScreenDomain(rectLeftTop);
    rectRightBottom = ConvertWindowToScreenDomain(rectRightBottom);
    if (queryWord.size() > MAX_TRANSLATE_SIZE) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring wQueryWord = converter.from_bytes(queryWord);
        queryWord = converter.to_bytes(wQueryWord.substr(0, MAX_TRANSLATE_SIZE));
    }
    TextTranslationAdapter::StartAITextTranslationTask(
        queryWord, GetTranslateParamRectStr(rect, rectLeftTop, rectRightBottom));
}
} // namespace OHOS::Ace::NG