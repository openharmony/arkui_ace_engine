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

#include "core/components_ng/pattern/selection_container/selection_select_overlay.h"

#include "base/log/log_wrapper.h"
#include "base/utils/string_utils.h"
#include "base/utils/utf_helper.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/common/clipboard/clipboard_proxy.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/select_content_overlay/select_content_overlay_manager.h"
#include "core/components_ng/pattern/selection_container/selection_container_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
OffsetF GetHandleAnchorPoint(const RectF& rect)
{
    auto point = rect.GetOffset();
    point.SetY(point.GetY() + rect.Height() / 2.0f);
    return point;
}

CopyOptions MergeCopyOption(CopyOptions current, CopyOptions next)
{
    return static_cast<int32_t>(current) <= static_cast<int32_t>(next) ? current : next;
}
} // namespace

bool SelectionSelectOverlay::CheckHandleVisible(const RectF& paintRect)
{
    return !paintRect.IsEmpty();
}

void SelectionSelectOverlay::CalcHandleLevelMode(const RectF&, const RectF&)
{
    SetHandleLevelMode(HandleLevelMode::OVERLAY);
}

RefPtr<FrameNode> SelectionSelectOverlay::GetOwner()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetHost();
}

bool SelectionSelectOverlay::PreProcessOverlay(const OverlayRequest& request)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    SetUsingMouse(pattern->IsUsingMouse());
    SetEnableHandleLevel(true);
    SetEnableSubWindowMenu(true);
    SetMenuTranslateIsSupport(IsShowTranslate());
    SetIsSupportMenuSearch(IsShowSearch());
    CheckEnableContainerModal();
    return true;
}

std::optional<SelectHandleInfo> SelectionSelectOverlay::GetFirstHandleInfo()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto startChild = pattern->GetSelectionStartChild();
    CHECK_NULL_RETURN(startChild, std::nullopt);
    return startChild->GetFirstHandleInfo();
}

std::optional<SelectHandleInfo> SelectionSelectOverlay::GetSecondHandleInfo()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto endChild = pattern->GetSelectionEndChild();
    CHECK_NULL_RETURN(endChild, std::nullopt);
    return endChild->GetSecondHandleInfo();
}

RectF SelectionSelectOverlay::GetSelectAreaFromRects(SelectRectsType pos)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, {});
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_RETURN(manager, {});
    auto overlayRoot = manager->GetSelectOverlayRoot();
    CHECK_NULL_RETURN(overlayRoot, {});

    RectF selectArea;
    bool hasArea = false;
    for (const auto& weakChild : pattern->GetChildList()) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        if (child->GetSelectionText().empty()) {
            continue;
        }
        auto childArea = child->GetSelectionArea(overlayRoot, pos);
        if (pos == SelectRectsType::LEFT_TOP_POINT) {
            ApplySelectAreaWithKeyboard(childArea);
            return childArea;
        }
        if (pos == SelectRectsType::RIGHT_BOTTOM_POINT) {
            selectArea = childArea;
            hasArea = true;
            continue;
        }
        if (childArea.IsEmpty()) {
            continue;
        }
        selectArea = hasArea ? selectArea.CombineRectT(childArea) : childArea;
        hasArea = true;
    }
    if (!hasArea) {
        return GetSelectAreaFromHandleFallback();
    }
    auto containerNode = pattern->GetHost();
    if (containerNode && pos == SelectRectsType::ALL_LINES) {
        auto visibleRect = GetContainerVisibleRect(containerNode, overlayRoot);
        if (!visibleRect.IsEmpty()) {
            selectArea = selectArea.IntersectRectT(visibleRect);
            selectArea.SetWidth(std::max(selectArea.Width(), 0.0f));
            selectArea.SetHeight(std::max(selectArea.Height(), 0.0f));
        }
    }
    ApplySelectAreaWithKeyboard(selectArea);
    return selectArea;
}

void SelectionSelectOverlay::OnUpdateMenuInfo(SelectMenuInfo& menuInfo, SelectOverlayDirtyFlag dirtyFlag)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto hasSelectedText = HasValidSelectedText();
    menuInfo.showCopyAll = pattern->HasSelectableText() && !pattern->IsSelectAll();
    menuInfo.showCopy = hasSelectedText;
    menuInfo.showTranslate = hasSelectedText && IsShowTranslate() && IsNeedMenuTranslate();
    menuInfo.showSearch = hasSelectedText && IsShowSearch() && IsNeedMenuSearch();
    menuInfo.showShare = hasSelectedText && IsSupportMenuShare() && IsNeedMenuShare();
    menuInfo.aiMenuOptionType = TextDataDetectType::INVALID;
    menuInfo.isAskCeliaEnabled = hasSelectedText && IsAskCeliaSupported();
    menuInfo.isShowAskCeliaInRightClick = menuInfo.isAskCeliaEnabled;
    menuInfo.menuIsShow = IsShowMenu();
    menuInfo.showCut = false;
    menuInfo.showPaste = false;
    menuInfo.hasOnPrepareMenuCallback = onPrepareMenuCallback_ ? true : false;
}

void SelectionSelectOverlay::OnUpdateSelectOverlayInfo(SelectOverlayInfo& overlayInfo, int32_t requestCode)
{
    overlayInfo.clipHandleDrawRect = IsClipHandleWithViewPort();
    BaseTextSelectOverlay::OnUpdateSelectOverlayInfo(overlayInfo, requestCode);
    auto overlayPattern = pattern_.Upgrade();
    CHECK_NULL_VOID(overlayPattern);
    overlayPattern->CopySelectionMenuParams(overlayInfo);
    auto handleColor = GetHandleColor();
    if (handleColor.has_value()) {
        overlayInfo.handlerColor = handleColor;
    }
    OnUpdateOnCreateMenuCallback(overlayInfo);
    overlayInfo.menuCallback.showMenuOnMoveDone = [weak = WeakClaim(this)]() {
        auto overlay = weak.Upgrade();
        CHECK_NULL_RETURN(overlay, true);
        auto overlayPattern = (overlay->pattern_).Upgrade();
        CHECK_NULL_RETURN(overlayPattern, true);
        return !overlayPattern->IsSelectedTypeChange();
    };
}

void SelectionSelectOverlay::OnResetTextSelection()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->ResetAllSelection();
}

std::optional<Color> SelectionSelectOverlay::GetHandleColor()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, std::nullopt);
    auto layoutProperty = host->GetLayoutProperty<SelectionContainerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, std::nullopt);
    return layoutProperty->GetCaretColor();
}

void SelectionSelectOverlay::OnMenuItemAction(OptionMenuActionId id, OptionMenuType type)
{
    switch (id) {
        case OptionMenuActionId::COPY: {
            auto pat = pattern_.Upgrade();
            CHECK_NULL_VOID(pat);
            pat->HandleOnCopy();
            break;
        }
        case OptionMenuActionId::SELECT_ALL: {
            auto pat = pattern_.Upgrade();
            CHECK_NULL_VOID(pat);
            pat->HandleOnSelectAll();
            break;
        }
        case OptionMenuActionId::TRANSLATE:
            HandleOnTranslate();
            break;
        case OptionMenuActionId::SEARCH:
            HandleOnSearch();
            break;
        case OptionMenuActionId::SHARE:
            HandleOnShare();
            break;
        case OptionMenuActionId::ASK_CELIA:
            HandleOnAskCelia();
            break;
        default:
            TAG_LOGI(AceLogTag::ACE_TEXT, "Unsupported menu option id %{public}d", id);
            break;
    }
}

void SelectionSelectOverlay::OnMenuItemAction(OptionMenuActionId id, OptionMenuType type, const std::string& labelInfo)
{
    OnMenuItemAction(id, type);
}

void SelectionSelectOverlay::OnHandleMoveStart(const GestureEvent& event, bool isFirst)
{
    BaseTextSelectOverlay::OnHandleMoveStart(event, isFirst);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    auto overlayRoot = manager->GetSelectOverlayRoot();
    CHECK_NULL_VOID(overlayRoot);

    auto fixedChild = isFirst ? pattern->GetSelectionEndChild() : pattern->GetSelectionStartChild();
    CHECK_NULL_VOID(fixedChild);
    auto fixedHandle = isFirst ? fixedChild->GetSecondHandleInfo() : fixedChild->GetFirstHandleInfo();
    CHECK_NULL_VOID(fixedHandle);
    auto containerNode = pattern->GetHostNode();
    CHECK_NULL_VOID(containerNode);
    auto fixedPointInContainer = overlayRoot->ConvertPoint(GetHandleAnchorPoint(fixedHandle->paintRect), containerNode);
    auto fixedIndexes = fixedChild->GetSelectionIndexes();
    auto fixedIndex = isFirst ? fixedIndexes.endIndex : fixedIndexes.startIndex;
    auto fixedHandleIsTopOnStart = !isFirst;
    pattern->HandleSelectionStart(fixedPointInContainer, fixedChild, fixedIndex, fixedIndex, fixedHandleIsTopOnStart);
    manager->MarkInfoChange(isFirst ? DIRTY_FIRST_HANDLE : DIRTY_SECOND_HANDLE);
    manager->SetHandleCircleIsShow(isFirst, false);
}

void SelectionSelectOverlay::OnHandleMove(const RectF& rect, bool isFirst)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    auto overlayRoot = manager->GetSelectOverlayRoot();
    CHECK_NULL_VOID(overlayRoot);
    auto containerNode = pattern->GetHostNode();
    CHECK_NULL_VOID(containerNode);
    auto movingPointInContainer = overlayRoot->ConvertPoint(GetHandleAnchorPoint(rect), containerNode);
    pattern->HandleSelectionUpdate(movingPointInContainer);
    manager->MarkInfoChange(DIRTY_SELECT_TEXT);
}

void SelectionSelectOverlay::OnHandleMoveDone(const RectF& rect, bool isFirst)
{
    BaseTextSelectOverlay::OnHandleMoveDone(rect, isFirst);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    auto overlayRoot = manager->GetSelectOverlayRoot();
    CHECK_NULL_VOID(overlayRoot);
    auto containerNode = pattern->GetHostNode();
    CHECK_NULL_VOID(containerNode);
    auto movingPointInContainer = overlayRoot->ConvertPoint(GetHandleAnchorPoint(rect), containerNode);
    pattern->ProcessHandleMoveSelectionEnd(movingPointInContainer);
    if (!pattern->IsSelectedTypeChange()) {
        manager->ShowOptionMenu();
    }
    manager->MarkInfoChange((isFirst ? DIRTY_FIRST_HANDLE : DIRTY_SECOND_HANDLE) | DIRTY_SELECT_AREA |
                            DIRTY_SELECT_TEXT | DIRTY_COPY_ALL_ITEM | DIRTY_ASK_CELIA);
    if (pattern->CheckSelectedTypeChange()) {
        CloseOverlay(false, CloseReason::CLOSE_REASON_NORMAL);
        ProcessOverlay({ .animation = true });
    }
    manager->SetHandleCircleIsShow(isFirst, true);
    if (pattern->GetSelectionText().empty()) {
        CloseOverlay(false, CloseReason::CLOSE_REASON_NORMAL);
    }
    containerNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

std::string SelectionSelectOverlay::GetSelectedText()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, "");
    return UtfUtils::Str16DebugToStr8(pattern->GetSelectionText());
}

bool SelectionSelectOverlay::AllowTranslate()
{
    return HasValidSelectedText();
}

bool SelectionSelectOverlay::AllowSearch()
{
    return HasValidSelectedText();
}

bool SelectionSelectOverlay::AllowShare()
{
    return HasValidSelectedText();
}

bool SelectionSelectOverlay::IsShowTranslate() const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto textTheme = context->GetTheme<TextTheme>();
    CHECK_NULL_RETURN(textTheme, false);
    return textTheme->IsShowTranslate();
}

bool SelectionSelectOverlay::IsShowSearch() const
{
    auto container = Container::Current();
    if (container && container->IsSceneBoardWindow()) {
        return false;
    }
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto textTheme = context->GetTheme<TextTheme>();
    CHECK_NULL_RETURN(textTheme, false);
    return textTheme->IsShowSearch();
}

bool SelectionSelectOverlay::HasValidSelectedText() const
{
    return ResolveCopyOptionForSelectedText().has_value();
}

std::optional<CopyOptions> SelectionSelectOverlay::ResolveCopyOptionForSelectedText() const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto childList = pattern->GetChildList();
    std::optional<CopyOptions> selectedCopyOption;
    for (const auto& weakChild : childList) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        if (child->GetSelectionText().empty()) {
            continue;
        }
        auto childCopyOption = child->GetCopyOption();
        if (!child->CanSelect() || childCopyOption == CopyOptions::None) {
            // Defensive guard: selected text with CopyOptions::None means state is inconsistent; block copy.
            TAG_LOGW(AceLogTag::ACE_TEXT, "Selected child is not copyable, block container copy.");
            return std::nullopt;
        }
        selectedCopyOption = selectedCopyOption.has_value()
                                 ? MergeCopyOption(selectedCopyOption.value(), childCopyOption)
                                 : childCopyOption;
    }
    return selectedCopyOption;
}

RectF SelectionSelectOverlay::GetSelectAreaFromHandleFallback()
{
    RectF rect;
    auto firstHandle = GetFirstHandleInfo();
    if (firstHandle) {
        rect = firstHandle->paintRect;
        ApplySelectAreaWithKeyboard(rect);
        return rect;
    }
    auto secondHandle = GetSecondHandleInfo();
    if (secondHandle) {
        rect = secondHandle->paintRect;
    }
    ApplySelectAreaWithKeyboard(rect);
    return rect;
}

RectF SelectionSelectOverlay::GetContainerVisibleRect(
    const RefPtr<FrameNode>& containerNode, const RefPtr<FrameNode>& overlayRoot)
{
    CHECK_NULL_RETURN(containerNode, {});
    CHECK_NULL_RETURN(overlayRoot, {});
    auto geoNode = containerNode->GetGeometryNode();
    CHECK_NULL_RETURN(geoNode, {});
    auto frameRect = geoNode->GetFrameRect();
    auto leftTop = containerNode->ConvertPoint(frameRect.GetOffset(), overlayRoot);
    auto rightBottom = containerNode->ConvertPoint(
        { frameRect.Right(), frameRect.Bottom() }, overlayRoot);
    RectF visibleRect(leftTop.GetX(), leftTop.GetY(),
        rightBottom.GetX() - leftTop.GetX(), rightBottom.GetY() - leftTop.GetY());
    return GetVisibleRect(containerNode, visibleRect);
}

bool SelectionSelectOverlay::IsAskCeliaSupported() const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    CHECK_NULL_RETURN(!pattern->GetSelectionText().empty(), false);
    for (const auto& weakChild : pattern->GetChildList()) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        if (child->IsAskCeliaSupported()) {
            return true;
        }
    }
    return false;
}

void SelectionSelectOverlay::HandleOnAskCelia()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    HideMenu(true);
    auto selectedContent = pattern->GetSelectionText();
    for (const auto& weakChild : pattern->GetChildList()) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        if (child->HandleOnAskCelia(selectedContent)) {
            return;
        }
    }
}

} // namespace OHOS::Ace::NG
