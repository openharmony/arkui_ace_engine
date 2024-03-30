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

#include "core/components_ng/pattern/text/base_text_select_overlay.h"

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scrollable/nestable_scroll_container.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NO_NEED_RESTART_SINGLE_HANDLE = 100;
} // namespace
void BaseTextSelectOverlay::ProcessOverlay(const OverlayRequest& request)
{
    if (!PreProcessOverlay(request)) {
        return;
    }
    auto checkClipboard = [weak = WeakClaim(this), request](bool hasData) {
        TAG_LOGI(AceLogTag::ACE_TEXT, "HasData callback from clipboard, data available ? %{public}d", hasData);
        auto overlay = weak.Upgrade();
        CHECK_NULL_VOID(overlay);
        overlay->SetShowPaste(hasData);
        overlay->SetMenuIsShow(request.menuIsShow);
        overlay->SetIsShowHandleLine(!request.hideHandleLine);
        overlay->latestReqeust_ = request;
        auto manager = SelectContentOverlayManager::GetOverlayManager(overlay);
        CHECK_NULL_VOID(manager);
        manager->Show(request.animation, request.requestCode);
    };
    auto textBase = hostTextBase_.Upgrade();
    CHECK_NULL_VOID(textBase);
    auto clipboard = textBase->GetClipboard();
    if (clipboard) {
        clipboard->HasData(checkClipboard);
    } else {
        checkClipboard(false);
    }
}

void BaseTextSelectOverlay::ProcessOverlayOnAreaChanged(const OverlayRequest& request)
{
    auto overlayRequest = request;
    overlayRequest.requestCode = NO_NEED_RESTART_SINGLE_HANDLE;
    ProcessOverlay(overlayRequest);
}

bool BaseTextSelectOverlay::CheckRestartHiddenHandleTask(int32_t requestCode)
{
    return requestCode != NO_NEED_RESTART_SINGLE_HANDLE;
}

bool BaseTextSelectOverlay::IsShowMouseMenu()
{
    auto overlayManager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_RETURN(overlayManager, false);
    return overlayManager->GetShowMenuType() == OptionMenuType::MOUSE_MENU;
}

bool BaseTextSelectOverlay::IsCurrentMenuVisibile()
{
    auto overlayManager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_RETURN(overlayManager, false);
    return overlayManager->IsMenuShow();
}

bool BaseTextSelectOverlay::IsHandleReverse()
{
    auto overlayManager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_RETURN(overlayManager, false);
    return overlayManager->IsHandleReverse();
}

bool BaseTextSelectOverlay::SelectOverlayIsOn()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_RETURN(manager, false);
    return manager->IsOpen();
}

void BaseTextSelectOverlay::CloseOverlay(bool animation, CloseReason reason)
{
    auto overlayManager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->Close(GetOwnerId(), animation, reason);
    AfterCloseOverlay();
}

void BaseTextSelectOverlay::ToggleMenu()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->ToggleOptionMenu();
}

void BaseTextSelectOverlay::ShowMenu()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->ShowOptionMenu();
}

void BaseTextSelectOverlay::HideMenu()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->HideOptionMenu();
}

void BaseTextSelectOverlay::DisableMenu()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->DisableMenu();
}

void BaseTextSelectOverlay::EnableMenu()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->EnableMenu();
}

void BaseTextSelectOverlay::UpdateAllHandlesOffset()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->MarkInfoChange(DIRTY_DOUBLE_HANDLE | DIRTY_SELECT_AREA);
}

void BaseTextSelectOverlay::UpdateFirstHandleOffset()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->MarkInfoChange(DIRTY_FIRST_HANDLE);
}

void BaseTextSelectOverlay::UpdateSecondHandleOffset()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->MarkInfoChange(DIRTY_SECOND_HANDLE);
}

RefPtr<FrameNode> BaseTextSelectOverlay::GetOwner()
{
    auto pattern = GetPattern<Pattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetHost();
}

void BaseTextSelectOverlay::OnHandleGlobalTouchEvent(SourceType sourceType, TouchType touchType)
{
    if (IsMouseClickDown(sourceType, touchType) || IsTouchUp(sourceType, touchType)) {
        CloseOverlay(false, CloseReason::CLOSE_REASON_CLICK_OUTSIDE);
    }
}

bool BaseTextSelectOverlay::CheckTouchInHostNode(const PointF& touchPoint)
{
    return GetVisibleFrameRect().IsInRegion(touchPoint);
}

void BaseTextSelectOverlay::OnUpdateSelectOverlayInfo(SelectOverlayInfo& overlayInfo, int32_t requestCode)
{
    overlayInfo.isSingleHandle = isSingleHandle_;
    overlayInfo.isHandleLineShow = isShowHandleLine_ && !isSingleHandle_;
    overlayInfo.recreateOverlay = isUsingMouse_;
    overlayInfo.rightClickOffset = mouseMenuOffset_;
    overlayInfo.isUsingMouse = isUsingMouse_;
    overlayInfo.isNewAvoid = true;
    overlayInfo.hitTestMode = HitTestMode::HTMDEFAULT;
}

RectF BaseTextSelectOverlay::GetVisibleRect(const RefPtr<FrameNode>& node, const RectF& visibleRect)
{
    CHECK_NULL_RETURN(node, visibleRect);
    auto parentNode = node->GetAncestorNodeOfFrame();
    CHECK_NULL_RETURN(parentNode, visibleRect);
    if (parentNode->GetTag() == V2::PAGE_ETS_TAG) {
        return visibleRect;
    }
    auto intersectRect = visibleRect;
    auto scrollablePattern = AceType::DynamicCast<NestableScrollContainer>(parentNode->GetPattern());
    auto geometryNode = parentNode->GetGeometryNode();
    if (scrollablePattern && geometryNode) {
        auto parentViewPort = RectF(parentNode->GetTransformRelativeOffset(), geometryNode->GetFrameSize());
        if (parentViewPort.IsIntersectWith(visibleRect)) {
            intersectRect = parentViewPort.IntersectRectT(visibleRect);
        } else {
            return RectF(0, 0, 0, 0);
        }
    }
    return GetVisibleRect(parentNode, intersectRect);
}

void BaseTextSelectOverlay::RemoveSelectionHoldCallback()
{
    auto overlayManager = SelectContentOverlayManager::GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->RemoveHoldSelectionCallback(GetOwnerId());
}

void BaseTextSelectOverlay::SetSelectionHoldCallback()
{
    auto overlayManager = SelectContentOverlayManager::GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    HoldSelectionInfo selectionInfo;
    selectionInfo.resetSelectionCallback = [weak = WeakClaim(this)]() {
        auto overlay = weak.Upgrade();
        CHECK_NULL_VOID(overlay);
        overlay->OnResetTextSelection();
    };
    selectionInfo.checkTouchInArea = [weak = WeakClaim(this)](const PointF& point) {
        auto overlay = weak.Upgrade();
        CHECK_NULL_RETURN(overlay, false);
        return overlay->CheckTouchInHostNode(point);
    };
    selectionInfo.eventFilter = [weak = WeakClaim(this)](SourceType sourceType, TouchType touchType) {
        auto overlay = weak.Upgrade();
        CHECK_NULL_RETURN(overlay, false);
        return overlay->IsAcceptResetSelectionEvent(sourceType, touchType);
    };
    overlayManager->SetHoldSelectionCallback(GetOwnerId(), selectionInfo);
}

RectF BaseTextSelectOverlay::GetVisibleContentRect()
{
    RectF visibleContentRect;
    auto pattern = GetPattern<Pattern>();
    CHECK_NULL_RETURN(pattern, visibleContentRect);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, visibleContentRect);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, visibleContentRect);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, visibleContentRect);
    auto paintOffset = host->GetPaintRectOffset() - context->GetRootRect().GetOffset();
    visibleContentRect = RectF(geometryNode->GetContentOffset() + paintOffset, geometryNode->GetContentSize());
    return GetVisibleRect(pattern->GetHost(), visibleContentRect);
}

RectF BaseTextSelectOverlay::GetVisibleFrameRect()
{
    RectF frameRect;
    auto pattern = GetPattern<Pattern>();
    CHECK_NULL_RETURN(pattern, frameRect);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, frameRect);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, frameRect);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, frameRect);
    auto paintOffset = host->GetPaintRectOffset() - context->GetRootRect().GetOffset();
    frameRect = RectF(paintOffset, geometryNode->GetFrameSize());
    return GetVisibleRect(host, frameRect);
}

RectF BaseTextSelectOverlay::MergeSelectedBoxes(
    const std::vector<RectF>& boxes, const RectF& contentRect, const RectF& textRect, const OffsetF& paintOffset)
{
    auto frontRect = boxes.front();
    auto backRect = boxes.back();
    RectF res;
    if (GreatNotEqual(backRect.Bottom(), frontRect.Bottom())) {
        res.SetRect(contentRect.GetX() + paintOffset.GetX(), frontRect.GetY() + textRect.GetY() + paintOffset.GetY(),
            contentRect.Width(), backRect.Bottom() - frontRect.Top());
    } else {
        res.SetRect(frontRect.GetX() + textRect.GetX() + paintOffset.GetX(),
            frontRect.GetY() + textRect.GetY() + paintOffset.GetY(), backRect.Right() - frontRect.Left(),
            backRect.Bottom() - frontRect.Top());
    }
    return res;
}
} // namespace OHOS::Ace::NG
