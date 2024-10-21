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

#include "core/components_ng/pattern/scrollable/nestable_scroll_container.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NO_NEED_RESTART_SINGLE_HANDLE = 100;
constexpr SelectOverlayDirtyFlag UPDATE_HANDLE_COLOR_FLAG = 101;
} // namespace
void BaseTextSelectOverlay::ProcessOverlay(const OverlayRequest& request)
{
    UpdateTransformFlag();
    if (!PreProcessOverlay(request) || AnimationUtils::IsImplicitAnimationOpen()) {
        return;
    }
    auto checkClipboard = [weak = WeakClaim(this), request](bool hasData) {
        TAG_LOGI(AceLogTag::ACE_TEXT, "HasData callback from clipboard, data available ? %{public}d", hasData);
        auto overlay = weak.Upgrade();
        CHECK_NULL_VOID(overlay);
        overlay->ShowSelectOverlay(request, hasData);
    };
    auto textBase = hostTextBase_.Upgrade();
    CHECK_NULL_VOID(textBase);
    auto clipboard = textBase->GetClipboard();
    if (clipboard) {
        auto mimeTypes = GetPasteMimeTypes();
        if (!mimeTypes.empty()) {
            clipboard->HasDataType(checkClipboard, mimeTypes);
            return;
        }
        clipboard->HasData(checkClipboard);
    } else {
        checkClipboard(false);
    }
}

void BaseTextSelectOverlay::ShowSelectOverlay(const OverlayRequest& request, bool hasClipboardData)
{
    SetShowPaste(hasClipboardData);
    SetMenuIsShow(request.menuIsShow);
    SetIsShowHandleLine(!request.hideHandleLine);
    latestReqeust_ = request;
    if (!SelectOverlayIsOn() && enableHandleLevel_) {
        auto firstLocalRect = GetFirstHandleLocalPaintRect();
        auto secondLocalRect = GetSecondHandleLocalPaintRect();
        CalcHandleLevelMode(firstLocalRect, secondLocalRect);
    }
    if (enableHandleLevel_) {
        auto host = GetOwner();
        CHECK_NULL_VOID(host);
        host->RegisterNodeChangeListener();
        RegisterScrollingListener(nullptr);
        CheckAndUpdateHostGlobalPaintRect();
    }
    auto manager = SelectContentOverlayManager::GetOverlayManager(Claim(this));
    CHECK_NULL_VOID(manager);
    manager->Show(request.animation, request.requestCode);
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

bool BaseTextSelectOverlay::SelectOverlayIsCreating()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_RETURN(manager, false);
    return manager->IsCreating();
}

void BaseTextSelectOverlay::CloseOverlay(bool animation, CloseReason reason)
{
    auto overlayManager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->Close(GetOwnerId(), false, reason);
    AfterCloseOverlay();
}

void BaseTextSelectOverlay::ToggleMenu()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->ToggleOptionMenu();
    UpdateOriginalMenuIsShow();
}

void BaseTextSelectOverlay::ShowMenu()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->ShowOptionMenu();
    UpdateOriginalMenuIsShow();
}

void BaseTextSelectOverlay::HideMenu(bool noAnimation)
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->HideOptionMenu(noAnimation);
    UpdateOriginalMenuIsShow();
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

void BaseTextSelectOverlay::UpdateViewPort()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->MarkInfoChange(DIRTY_VIEWPORT);
}

RefPtr<FrameNode> BaseTextSelectOverlay::GetOwner()
{
    auto pattern = GetPattern<Pattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetHost();
}

void BaseTextSelectOverlay::OnHandleGlobalTouchEvent(SourceType sourceType, TouchType touchType, bool touchInside)
{
    if (IsMouseClickDown(sourceType, touchType)) {
        CloseOverlay(false, CloseReason::CLOSE_REASON_CLICK_OUTSIDE);
    } else if (IsTouchUp(sourceType, touchType)) {
        HideMenu(true);
    }
}

bool BaseTextSelectOverlay::CheckTouchInHostNode(const PointF& touchPoint)
{
    auto host = GetOwner();
    CHECK_NULL_RETURN(host, false);
    auto geo = host->GetGeometryNode();
    CHECK_NULL_RETURN(geo, false);
    auto rect = RectF(OffsetF(0.0f, 0.0f), geo->GetFrameSize());
    return rect.IsInRegion(touchPoint);
}

void BaseTextSelectOverlay::OnUpdateSelectOverlayInfo(SelectOverlayInfo& overlayInfo, int32_t requestCode)
{
    overlayInfo.isSingleHandle = isSingleHandle_;
    overlayInfo.isHandleLineShow = isShowHandleLine_;
    overlayInfo.recreateOverlay = isUsingMouse_;
    overlayInfo.rightClickOffset = mouseMenuOffset_;
    overlayInfo.isUsingMouse = isUsingMouse_;
    overlayInfo.isNewAvoid = true;
    overlayInfo.hitTestMode = HitTestMode::HTMDEFAULT;
    if (hasTransform_) {
        overlayInfo.callerNodeInfo = {
            .paintFrameRect = GetPaintRectWithTransform(),
            .paintOffset = GetPaintRectOffsetWithTransform()
        };
    }
    overlayInfo.ancestorViewPort = GetAncestorNodeViewPort();
    overlayInfo.enableHandleLevel = enableHandleLevel_;
    overlayInfo.handleLevelMode = handleLevelMode_;
    if (enableHandleLevel_) {
        overlayInfo.scale = GetHostScale();
    }
    overlayInfo.afterOnClick = [weak = WeakClaim(this)](const GestureEvent&, bool isFirst) {
        auto overlay = weak.Upgrade();
        CHECK_NULL_VOID(overlay);
        overlay->UpdateOriginalMenuIsShow();
    };
}

RectF BaseTextSelectOverlay::GetVisibleRect(const RefPtr<FrameNode>& node, const RectF& visibleRect)
{
    CHECK_NULL_RETURN(node, visibleRect);
    auto parentNode = node->GetAncestorNodeOfFrame(true);
    CHECK_NULL_RETURN(parentNode, visibleRect);
    if (parentNode->GetTag() == V2::PAGE_ETS_TAG) {
        return visibleRect;
    }
    auto intersectRect = visibleRect;
    auto scrollablePattern = AceType::DynamicCast<NestableScrollContainer>(parentNode->GetPattern());
    auto geometryNode = parentNode->GetGeometryNode();
    if (scrollablePattern && geometryNode) {
        RectF parentViewPort;
        if (!GetFrameNodeContentRect(parentNode, parentViewPort)) {
            return RectF(0, 0, 0, 0);
        }
        parentViewPort += parentNode->GetTransformRelativeOffset();
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
    selectionInfo.checkTouchInArea = [weak = WeakClaim(this), manager = WeakClaim(AceType::RawPtr(overlayManager))](
                                         const PointF& point) {
        auto baseOverlay = weak.Upgrade();
        CHECK_NULL_RETURN(baseOverlay, false);
        auto overlayManager = manager.Upgrade();
        CHECK_NULL_RETURN(overlayManager, false);
        auto host = baseOverlay->GetOwner();
        CHECK_NULL_RETURN(host, false);
        auto localPoint = point;
        overlayManager->ConvertPointRelativeToNode(host, localPoint);
        return baseOverlay->CheckTouchInHostNode(localPoint);
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
    auto paintOffset = host->GetTransformRelativeOffset();
    visibleContentRect = RectF(geometryNode->GetContentOffset() + paintOffset, geometryNode->GetContentSize());
    if (enableHandleLevel_ && handleLevelMode_ == HandleLevelMode::EMBED) {
        return visibleContentRect;
    }
    return GetVisibleRect(pattern->GetHost(), visibleContentRect);
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

void BaseTextSelectOverlay::SetTransformPaintInfo(SelectHandleInfo& handleInfo, const RectF& localHandleRect)
{
    CHECK_NULL_VOID(hasTransform_);
    SelectHandlePaintInfo paintInfo;
    auto left = localHandleRect.Left() + localHandleRect.Width() / 2.0f;
    std::vector<OffsetF> points = { OffsetF(left, localHandleRect.Top()), OffsetF(left, localHandleRect.Bottom()) };
    GetGlobalPointsWithTransform(points);
    paintInfo.startPoint = points[0];
    paintInfo.endPoint = points[1];
    paintInfo.width = localHandleRect.Width();
    handleInfo.paintInfo = paintInfo;
    handleInfo.paintInfoConverter = [weak = WeakClaim(this)](const SelectHandlePaintInfo& paintInfo) {
        auto overlay = weak.Upgrade();
        CHECK_NULL_RETURN(overlay, RectF());
        return overlay->ConvertPaintInfoToRect(paintInfo);
    };
    handleInfo.isPaintHandleWithPoints = true;
    handleInfo.isShow =
        CheckHandleIsVisibleWithTransform(paintInfo.startPoint, paintInfo.endPoint, localHandleRect.Width());
}

bool BaseTextSelectOverlay::CheckHandleIsVisibleWithTransform(
    const OffsetF& startPoint, const OffsetF& endPoint, float epsilon)
{
    auto pattern = GetPattern<Pattern>();
    CHECK_NULL_RETURN(pattern, true);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, true);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, true);
    auto contentRect = geometryNode->GetContentRect();
    auto rectVertices = GetGlobalRectVertexWithTransform(contentRect, epsilon);
    auto leftTop = rectVertices[0];
    auto rightTop = rectVertices[1];
    auto leftBottom = rectVertices[2];
    auto rightBottom = rectVertices[3];
    auto isStartPointInRect = IsPointInRect(startPoint, leftBottom, rightBottom, rightTop, leftTop);
    auto isEndPointInRect = IsPointInRect(endPoint, leftBottom, rightBottom, rightTop, leftTop);
    if (isStartPointInRect && isEndPointInRect) {
        auto visibleContentRect = GetVisibleContentRectWithTransform(epsilon);
        leftTop = OffsetF(visibleContentRect.Left(), visibleContentRect.Top());
        rightTop = OffsetF(visibleContentRect.Right(), visibleContentRect.Top());
        leftBottom = OffsetF(visibleContentRect.Left(), visibleContentRect.Bottom());
        rightBottom = OffsetF(visibleContentRect.Right(), visibleContentRect.Bottom());
        isStartPointInRect = IsPointInRect(startPoint, leftBottom, rightBottom, rightTop, leftTop);
        isEndPointInRect = IsPointInRect(endPoint, leftBottom, rightBottom, rightTop, leftTop);
        return isStartPointInRect && isEndPointInRect;
    }
    return false;
}

bool BaseTextSelectOverlay::IsPointInRect(
    const OffsetF& point, const OffsetF& lb, const OffsetF& rb, const OffsetF& rt, const OffsetF& lt)
{
    auto crossProduct = [](const OffsetF& point, const OffsetF& point1, const OffsetF& point2) {
        auto pointStart = OffsetF(point2.GetX() - point1.GetX(), point2.GetY() - point1.GetY());
        auto pointEnd = OffsetF(point.GetX() - point1.GetX(), point.GetY() - point1.GetY());
        return pointStart.GetX() * pointEnd.GetY() - pointEnd.GetX() * pointStart.GetY();
    };
    auto bottomProduct = crossProduct(point, lb, rb);
    auto rightProduct = crossProduct(point, rb, rt);
    auto topProduct = crossProduct(point, rt, lt);
    auto leftProduct = crossProduct(point, lt, lb);
    std::vector<float> productVector = { bottomProduct, rightProduct, topProduct, leftProduct };
    auto minMax = std::minmax_element(productVector.begin(), productVector.end());
    // 所用向量叉积方向一致(都为正数或者都为负数)，表示点在矩形内. 最小值大于0或者最大值小于0.
    return Positive(*minMax.first) || Negative(* minMax.second);
}

RectF BaseTextSelectOverlay::GetVisibleContentRectWithTransform(float epsilon)
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
    visibleContentRect = geometryNode->GetContentRect();
    auto width = visibleContentRect.Width() + 2 * epsilon;
    auto height = visibleContentRect.Height() + 2 * epsilon;
    visibleContentRect.SetLeft(visibleContentRect.Left() - epsilon);
    visibleContentRect.SetTop(visibleContentRect.Top() - epsilon);
    visibleContentRect.SetWidth(width);
    visibleContentRect.SetHeight(height);
    GetGlobalRectWithTransform(visibleContentRect);
    return GetVisibleRect(pattern->GetHost(), visibleContentRect);
}

void BaseTextSelectOverlay::GetGlobalPointsWithTransform(std::vector<OffsetF>& points)
{
    CHECK_NULL_VOID(hasTransform_);
    auto pattern = GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    auto parent = pattern->GetHost();
    std::vector<PointF> convertPoints;
    auto pointConverter = [](const OffsetF& offset) { return PointF(offset.GetX(), offset.GetY()); };
    std::transform(points.begin(), points.end(), std::back_inserter(convertPoints), pointConverter);
    while (parent) {
        if (parent->GetTag() == V2::WINDOW_SCENE_ETS_TAG) {
            break;
        }
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        auto paintOffset = renderContext->GetPaintRectWithoutTransform().GetOffset();
        for (auto& pointElement : convertPoints) {
            pointElement = pointElement + paintOffset;
            renderContext->GetPointTransform(pointElement);
        }
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    points.clear();
    auto offsetConverter = [](const PointF& point) { return OffsetF(point.GetX(), point.GetY()); };
    std::transform(convertPoints.begin(), convertPoints.end(), std::back_inserter(points), offsetConverter);
}

void BaseTextSelectOverlay::GetGlobalRectWithTransform(RectF& localRect)
{
    CHECK_NULL_VOID(hasTransform_);
    auto rectVertex = GetGlobalRectVertexWithTransform(localRect);
    auto compareOffsetX = [](const OffsetF& offset1, const OffsetF& offset2) {
        return LessNotEqual(offset1.GetX(), offset2.GetX());
    };
    auto minMaxX = std::minmax_element(rectVertex.begin(), rectVertex.end(), compareOffsetX);
    auto compareOffsetY = [](const OffsetF& offset1, const OffsetF& offset2) {
        return LessNotEqual(offset1.GetY(), offset2.GetY());
    };
    auto minMaxY = std::minmax_element(rectVertex.begin(), rectVertex.end(), compareOffsetY);
    localRect.SetOffset(OffsetF(minMaxX.first->GetX(), minMaxY.first->GetY()));
    localRect.SetSize(
        SizeF(minMaxX.second->GetX() - minMaxX.first->GetX(), minMaxY.second->GetY() - minMaxY.first->GetY()));
}

std::vector<OffsetF> BaseTextSelectOverlay::GetGlobalRectVertexWithTransform(const RectF& rect, float extendValue)
{
    std::vector<OffsetF> rectVertices = {
        OffsetF(rect.Left() - extendValue, rect.Top() - extendValue),
        OffsetF(rect.Right() + extendValue, rect.Top() - extendValue),
        OffsetF(rect.Left() - extendValue, rect.Bottom() + extendValue),
        OffsetF(rect.Right() + extendValue, rect.Bottom() + extendValue)
    };
    GetGlobalPointsWithTransform(rectVertices);
    return rectVertices;
}

void BaseTextSelectOverlay::GetLocalPointWithTransform(OffsetF& localPoint)
{
    CHECK_NULL_VOID(hasTransform_);
    std::vector<OffsetF> points = { localPoint };
    GetLocalPointsWithTransform(points);
    localPoint = points[0];
}

void BaseTextSelectOverlay::GetLocalPointsWithTransform(std::vector<OffsetF>& localPoints)
{
    CHECK_NULL_VOID(hasTransform_);
    auto textPaintOffset = GetPaintRectOffsetWithTransform();
    GetGlobalPointsWithTransform(localPoints);
    for (auto& pointElement : localPoints) {
        pointElement = pointElement - textPaintOffset;
    }
}

RectF BaseTextSelectOverlay::GetPaintRectWithTransform()
{
    auto pattern = GetPattern<Pattern>();
    CHECK_NULL_RETURN(pattern, RectF());
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, RectF());
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, RectF());
    auto globalFrameRect = RectF(OffsetF(0.0f, 0.0f), geometryNode->GetFrameSize());
    GetGlobalRectWithTransform(globalFrameRect);
    return globalFrameRect;
}

OffsetF BaseTextSelectOverlay::GetPaintRectOffsetWithTransform()
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, OffsetF(0.0f, 0.0f));
    auto globalFrameRect = GetPaintRectWithTransform();
    return globalFrameRect.GetOffset() - pipeline->GetRootRect().GetOffset();
}

void BaseTextSelectOverlay::GetLocalRectWithTransform(RectF& rect)
{
    CHECK_NULL_VOID(hasTransform_);
    std::vector<OffsetF> localRectVertices = {
        OffsetF(rect.Left(), rect.Top()),
        OffsetF(rect.Right(), rect.Top()),
        OffsetF(rect.Left(), rect.Bottom()),
        OffsetF(rect.Right(), rect.Bottom())
    };
    GetLocalPointsWithTransform(localRectVertices);
    auto compareOffsetX = [](const OffsetF& offset1, const OffsetF& offset2) {
        return LessNotEqual(offset1.GetX(), offset2.GetX());
    };
    auto minMaxX = std::minmax_element(localRectVertices.begin(), localRectVertices.end(), compareOffsetX);
    auto compareOffsetY = [](const OffsetF& offset1, const OffsetF& offset2) {
        return LessNotEqual(offset1.GetY(), offset2.GetY());
    };
    auto minMaxY = std::minmax_element(localRectVertices.begin(), localRectVertices.end(), compareOffsetY);
    rect.SetOffset(OffsetF(minMaxX.first->GetX(), minMaxY.first->GetY()));
    rect.SetSize(SizeF(minMaxX.second->GetX() - minMaxX.first->GetX(), minMaxY.second->GetY() - minMaxY.first->GetY()));
}

void BaseTextSelectOverlay::RevertLocalPointWithTransform(OffsetF& point)
{
    CHECK_NULL_VOID(hasTransform_);
    auto pattern = GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    auto parent = pattern->GetHost();
    CHECK_NULL_VOID(parent);
    std::stack<RefPtr<FrameNode>> nodeStack;
    while (parent) {
        nodeStack.push(parent);
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    CHECK_NULL_VOID(!nodeStack.empty());
    PointF localPoint(point.GetX(), point.GetY());
    while (!nodeStack.empty()) {
        parent = nodeStack.top();
        CHECK_NULL_VOID(parent);
        nodeStack.pop();
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->GetPointWithRevert(localPoint);
        auto rectOffset = renderContext->GetPaintRectWithoutTransform().GetOffset();
        localPoint = localPoint - rectOffset;
    }
    point.SetX(localPoint.GetX());
    point.SetY(localPoint.GetY());
}

RectF BaseTextSelectOverlay::ConvertPaintInfoToRect(const SelectHandlePaintInfo& paintInfo)
{
    auto topOffset = paintInfo.startPoint;
    RevertLocalPointWithTransform(topOffset);
    auto bottomOffset = paintInfo.endPoint;
    RevertLocalPointWithTransform(bottomOffset);
    auto offset = topOffset + GetPaintOffsetWithoutTransform();
    auto size = SizeF(paintInfo.width, bottomOffset.GetY() - topOffset.GetY());
    return RectF(offset, size);
}

OffsetF BaseTextSelectOverlay::GetPaintOffsetWithoutTransform()
{
    auto pattern = GetPattern<Pattern>();
    CHECK_NULL_RETURN(pattern, OffsetF());
    OffsetF offset;
    auto parent = pattern->GetHost();
    if (!hasTransform_) {
        return parent->GetTransformRelativeOffset();
    }
    while (parent) {
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, OffsetF());
        offset += renderContext->GetPaintRectWithoutTransform().GetOffset();
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return offset;
}

void BaseTextSelectOverlay::UpdateTransformFlag()
{
    auto pattern = GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto hasTransform = false;
    while (host) {
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        if (host->GetTag() == V2::WINDOW_SCENE_ETS_TAG) {
            break;
        }
        if (!hasTransform) {
            auto noTransformRect = renderContext->GetPaintRectWithoutTransform();
            auto transformRect = renderContext->GetPaintRectWithTransform();
            hasTransform = noTransformRect != transformRect;
        }
        host = host->GetAncestorNodeOfFrame(true);
    }
    hasTransform_ = hasTransform;
}

std::optional<RectF> BaseTextSelectOverlay::GetAncestorNodeViewPort()
{
    if (IsClipHandleWithViewPort()) {
        RectF viewPort;
        if (GetClipHandleViewPort(viewPort)) {
            return viewPort;
        }
    }
    auto pattern = GetPattern<Pattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, std::nullopt);
    auto parent = host->GetAncestorNodeOfFrame(true);
    while (parent) {
        auto scrollableContainer = parent->GetPattern<NestableScrollContainer>();
        if (scrollableContainer) {
            return parent->GetTransformRectRelativeToWindow();
        }
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return std::nullopt;
}

bool BaseTextSelectOverlay::IsAcceptResetSelectionEvent(SourceType sourceType, TouchType touchType)
{
    return (sourceType == SourceType::MOUSE || sourceType == SourceType::TOUCH) && touchType == TouchType::DOWN;
}

float BaseTextSelectOverlay::GetHandleDiameter()
{
    auto overlayManager = SelectContentOverlayManager::GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, 0.0f);
    return overlayManager->GetHandleDiameter();
}

void BaseTextSelectOverlay::SwitchToOverlayMode()
{
    if (HasUnsupportedTransform() || IsHandleInParentSafeAreaPadding()) {
        return;
    }
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    handleLevelMode_ = HandleLevelMode::OVERLAY;
    manager->SwitchToHandleMode(handleLevelMode_);
}

void BaseTextSelectOverlay::SwitchToEmbedMode()
{
    CHECK_NULL_VOID(!isHandleMoving_);
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    handleLevelMode_ = HandleLevelMode::EMBED;
    manager->SwitchToHandleMode(handleLevelMode_);
}

VectorF BaseTextSelectOverlay::GetHostScale()
{
    auto pattern = GetPattern<Pattern>();
    auto unitScale = VectorF(1, 1);
    CHECK_NULL_RETURN(pattern, unitScale);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, unitScale);
    auto scaleX = 1.0f;
    auto scaleY = 1.0f;
    while (host && host->GetTag() != V2::WINDOW_SCENE_ETS_TAG) {
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, unitScale);
        auto scale = renderContext->GetTransformScaleValue(unitScale);
        scaleX *= std::abs(scale.x);
        scaleY *= std::abs(scale.y);
        auto transformMatrix = renderContext->GetTransformMatrix();
        if (transformMatrix.has_value()) {
            DecomposedTransform transform;
            TransformUtil::DecomposeTransform(transform, transformMatrix.value());
            scaleX *= std::abs(transform.scale[0]);
            scaleY *= std::abs(transform.scale[1]);
        }
        host = host->GetAncestorNodeOfFrame(true);
    }
    return VectorF(1.0f / scaleX, 1.0f / scaleY);
}

void BaseTextSelectOverlay::OnCloseOverlay(OptionMenuType menuType, CloseReason reason, RefPtr<OverlayInfo> info)
{
    isHandleDragging_ = false;
    originalMenuIsShow_ = false;
    if (enableHandleLevel_) {
        auto host = GetOwner();
        CHECK_NULL_VOID(host);
        host->UnregisterNodeChangeListener();
    }
}

void BaseTextSelectOverlay::SetHandleLevelMode(HandleLevelMode mode)
{
    if (handleLevelMode_ == mode) {
        return;
    }
    handleLevelMode_ = mode;
}

RectF BaseTextSelectOverlay::GetFirstHandleLocalPaintRect()
{
    return RectF();
}

RectF BaseTextSelectOverlay::GetSecondHandleLocalPaintRect()
{
    return RectF();
}

bool BaseTextSelectOverlay::IsPointsInRegion(const std::vector<PointF>& points, const RectF& regionRect)
{
    for (const auto& point : points) {
        if (!regionRect.IsInRegion(point)) {
            return false;
        }
    }
    return true;
}

void BaseTextSelectOverlay::GetHandlePoints(const RectF& handleRect, std::vector<PointF>& points, bool handleOnTop)
{
    auto diameter = GetHandleDiameter();
    auto handlePaintRect = handleRect;
    auto offsetX = handlePaintRect.Left() + (handlePaintRect.Width() - diameter) / 2.0f;
    auto offsetY = handleOnTop ? handlePaintRect.Top() - diameter : handlePaintRect.Bottom();
    handlePaintRect.SetOffset(OffsetF(offsetX, offsetY));
    handlePaintRect.SetSize(SizeF(diameter, diameter));
    points.push_back(PointF(handlePaintRect.Left(), handlePaintRect.Top()));
    points.push_back(PointF(handlePaintRect.Right(), handlePaintRect.Top()));
    points.push_back(PointF(handlePaintRect.Left(), handlePaintRect.Bottom()));
    points.push_back(PointF(handlePaintRect.Right(), handlePaintRect.Bottom()));
}

bool BaseTextSelectOverlay::CheckHandleCanPaintInHost(const RectF& firstRect, const RectF& secondRect)
{
    if (isChangeToOverlayModeAtEdge_) {
        return false;
    }
    std::vector<PointF> firstPoints;
    GetHandlePoints(firstRect, firstPoints, false);
    std::vector<PointF> secondPoints;
    GetHandlePoints(secondRect, secondPoints, false);
    auto host = GetOwner();
    CHECK_NULL_RETURN(host, false);
    auto parent = host;
    while (parent) {
        CHECK_NULL_RETURN(parent->GetGeometryNode(), false);
        auto parentRect = RectF();
        parentRect.SetSize(parent->GetGeometryNode()->GetFrameSize());
        if (IsPointsInRegion(firstPoints, parentRect) && IsPointsInRegion(secondPoints, parentRect)) {
            return true;
        }
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, false);
        auto isClip = renderContext->GetClipEdge().value_or(false);
        if (isClip) {
            break;
        }
        auto paintOffset = renderContext->GetPaintRectWithoutTransform().GetOffset();
        for (auto& point : firstPoints) {
            point = point + paintOffset;
            renderContext->GetPointTransform(point);
        }
        for (auto& point : secondPoints) {
            point = point + paintOffset;
            renderContext->GetPointTransform(point);
        }
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return false;
}

void BaseTextSelectOverlay::CalcHandleLevelMode(const RectF& firstLocalPaintRect, const RectF& secondLocalPaintRect)
{
    if (CheckHandleCanPaintInHost(firstLocalPaintRect, secondLocalPaintRect) || HasUnsupportedTransform() ||
        IsHandleInParentSafeAreaPadding(firstLocalPaintRect, secondLocalPaintRect)) {
        SetHandleLevelMode(HandleLevelMode::EMBED);
    } else {
        SetHandleLevelMode(HandleLevelMode::OVERLAY);
    }
}

void BaseTextSelectOverlay::OnAncestorNodeChanged(FrameNodeChangeInfoFlag flag)
{
    auto isStartScroll = IsAncestorNodeStartScroll(flag);
    auto isStartAnimation = IsAncestorNodeStartAnimation(flag);
    auto isTransformChanged = IsAncestorNodeTransformChange(flag);
    auto isStartTransition = IsAncestorNodeHasTransition(flag);
    auto isSwitchToEmbed = isStartScroll || isStartAnimation || isTransformChanged || isStartTransition;
    // parent size changes but the child does not change.
    if (IsAncestorNodeGeometryChange(flag)) {
        isSwitchToEmbed = isSwitchToEmbed || CheckAndUpdateHostGlobalPaintRect();
    }
    auto isScrollEnd = IsAncestorNodeEndScroll(flag);
    isSwitchToEmbed = isSwitchToEmbed && (!isScrollEnd || HasUnsupportedTransform());
    UpdateMenuWhileAncestorNodeChanged(
        isStartScroll || isStartAnimation || isTransformChanged || isStartTransition, isScrollEnd);
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAfterRenderTask([weak = WeakClaim(this), isSwitchToEmbed, isScrollEnd]() {
        auto overlay = weak.Upgrade();
        CHECK_NULL_VOID(overlay);
        if (isScrollEnd) {
            overlay->SwitchToOverlayMode();
            return;
        }
        if (isSwitchToEmbed) {
            overlay->SwitchToEmbedMode();
        }
    });
    if ((flag & FRAME_NODE_CONTENT_CLIP_CHANGE) == FRAME_NODE_CONTENT_CLIP_CHANGE) {
        if (IsOverlayMode() && IsHandleInParentSafeAreaPadding()) {
            SwitchToEmbedMode();
        }
        UpdateViewPort();
    }
}

void BaseTextSelectOverlay::UpdateMenuWhileAncestorNodeChanged(bool shouldHideMenu, bool shouldShowMenu)
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    if (shouldHideMenu) {
        manager->HideOptionMenu(true);
        return;
    }
    if (shouldShowMenu && originalMenuIsShow_ && !GetIsHandleDragging() && !GetSelectArea().IsEmpty()) {
        manager->ShowOptionMenu();
    }
}

bool BaseTextSelectOverlay::IsAncestorNodeStartAnimation(FrameNodeChangeInfoFlag flag)
{
    return ((flag & FRAME_NODE_CHANGE_START_ANIMATION) == FRAME_NODE_CHANGE_START_ANIMATION);
}

bool BaseTextSelectOverlay::IsAncestorNodeGeometryChange(FrameNodeChangeInfoFlag flag)
{
    return ((flag & FRAME_NODE_CHANGE_GEOMETRY_CHANGE) == FRAME_NODE_CHANGE_GEOMETRY_CHANGE);
}

bool BaseTextSelectOverlay::IsAncestorNodeStartScroll(FrameNodeChangeInfoFlag flag)
{
    return ((flag & FRAME_NODE_CHANGE_START_SCROLL) == FRAME_NODE_CHANGE_START_SCROLL);
}

bool BaseTextSelectOverlay::IsAncestorNodeEndScroll(FrameNodeChangeInfoFlag flag)
{
    return ((flag & FRAME_NODE_CHANGE_END_SCROLL) == FRAME_NODE_CHANGE_END_SCROLL);
}

bool BaseTextSelectOverlay::IsAncestorNodeTransformChange(FrameNodeChangeInfoFlag flag)
{
    return ((flag & FRAME_NODE_CHANGE_TRANSFORM_CHANGE) == FRAME_NODE_CHANGE_TRANSFORM_CHANGE);
}

bool BaseTextSelectOverlay::IsAncestorNodeHasTransition(FrameNodeChangeInfoFlag flag)
{
    return ((flag & FRAME_NODE_CHANGE_TRANSITION_START) == FRAME_NODE_CHANGE_TRANSITION_START);
}

bool BaseTextSelectOverlay::IsTouchAtHandle(const TouchEventInfo& info)
{
    auto overlayManager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_RETURN(overlayManager, false);
    CHECK_NULL_RETURN(!info.GetTouches().empty(), false);
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        auto localOffset = info.GetTouches().front().GetLocalLocation();
        auto globalOffset = info.GetTouches().front().GetGlobalLocation();
        touchAtHandle_ = overlayManager->IsTouchAtHandle(
            PointF(localOffset.GetX(), localOffset.GetY()), PointF(globalOffset.GetX(), globalOffset.GetY()));
    } else if (touchType == TouchType::UP) {
        if (touchAtHandle_) {
            touchAtHandle_ = false;
            return true;
        }
    }
    return touchAtHandle_;
}

bool BaseTextSelectOverlay::IsClickAtHandle(const GestureEvent& info)
{
    auto overlayManager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_RETURN(overlayManager, false);
    auto localOffset = info.GetLocalLocation();
    auto globalOffset = info.GetGlobalLocation();
    return overlayManager->IsTouchAtHandle(
        PointF(localOffset.GetX(), localOffset.GetY()), PointF(globalOffset.GetX(), globalOffset.GetY()));
}

bool BaseTextSelectOverlay::HasUnsupportedTransform()
{
    auto pattern = GetPattern<Pattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto parent = pattern->GetHost();
    CHECK_NULL_RETURN(parent, false);
    const int32_t zTranslateIndex = 2;
    while (parent) {
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, false);
        if (parent->GetTag() == V2::WINDOW_SCENE_ETS_TAG) {
            return false;
        }
        if (renderContext->HasMotionPath()) {
            return true;
        }
        auto rotateVector = renderContext->GetTransformRotate();
        if (rotateVector.has_value() && !NearZero(rotateVector->w) &&
            !(NearZero(rotateVector->x) && NearZero(rotateVector->y))) {
            return true;
        }
        auto transformMatrix = renderContext->GetTransformMatrix();
        if (transformMatrix) {
            DecomposedTransform transform;
            TransformUtil::DecomposeTransform(transform, transformMatrix.value());
            Quaternion identity(0.0f, 0.0f, 0.0f, 1.0f);
            if (transform.quaternion != identity || !NearZero(transform.translate[zTranslateIndex])) {
                return true;
            }
        }
        auto translate = renderContext->GetTransformTranslate();
        if (translate && !NearZero(translate->z.Value())) {
            return true;
        }
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return false;
}

bool BaseTextSelectOverlay::CheckSwitchToMode(HandleLevelMode mode)
{
    if (mode == HandleLevelMode::OVERLAY && (HasUnsupportedTransform() || IsHandleInParentSafeAreaPadding())) {
        return false;
    }
    return true;
}

void BaseTextSelectOverlay::OnSelectionMenuOptionsUpdate(
    const NG::OnCreateMenuCallback&& onCreateMenuCallback, const NG::OnMenuItemClickCallback&& onMenuItemClick)
{
    onCreateMenuCallback_ = onCreateMenuCallback;
    onMenuItemClick_ = onMenuItemClick;
}

void BaseTextSelectOverlay::RegisterScrollingListener(const RefPtr<FrameNode> scrollableNode)
{
    if (hasRegisterListener_) {
        return;
    }
    auto scrollingNode = scrollableNode;
    if (!scrollingNode) {
        auto host = GetOwner();
        CHECK_NULL_VOID(host);
        scrollingNode = host->GetAncestorNodeOfFrame(true);
        while (scrollingNode) {
            if (scrollingNode->GetTag() == V2::SWIPER_ETS_TAG) {
                break;
            }
            scrollingNode = scrollingNode->GetAncestorNodeOfFrame(true);
        }
    }
    if (scrollingNode) {
        auto pattern = scrollingNode->GetPattern<Pattern>();
        CHECK_NULL_VOID(pattern);
        auto scrollCallback = [weak = WeakClaim(this), scrollNode = WeakClaim(AceType::RawPtr(scrollableNode))] {
            auto overlay = weak.Upgrade();
            CHECK_NULL_VOID(overlay);
            overlay->OnHandleScrolling(scrollNode);
        };
        auto scrollListener = AceType::MakeRefPtr<ScrollingListener>(scrollCallback);
        pattern->RegisterScrollingListener(scrollListener);
        hasRegisterListener_ = true;
    }
}

void BaseTextSelectOverlay::OnHandleScrolling(const WeakPtr<FrameNode>& scrollingNode)
{
    if (SelectOverlayIsOn()) {
        HideMenu(true);
        auto taskExecutor = Container::CurrentTaskExecutor();
        taskExecutor->PostTask(
            [weak = WeakClaim(this), scrollingNode] {
                auto overlay = weak.Upgrade();
                CHECK_NULL_VOID(overlay);
                overlay->hasRegisterListener_ = false;
                if (overlay->SelectOverlayIsOn()) {
                    overlay->RegisterScrollingListener(scrollingNode.Upgrade());
                }
            },
            TaskExecutor::TaskType::UI, "RegisterScrollingListener");
    } else {
        hasRegisterListener_ = false;
    }
}

bool BaseTextSelectOverlay::CheckAndUpdateHostGlobalPaintRect()
{
    auto host = GetOwner();
    CHECK_NULL_RETURN(host, false);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto framePaintRect = RectF(host->GetTransformRelativeOffset(), geometryNode->GetFrameSize());
    auto changed = globalPaintRect_ != framePaintRect;
    globalPaintRect_ = framePaintRect;
    return changed;
}

bool BaseTextSelectOverlay::CheckHasTransformAttr()
{
    auto pattern = GetPattern<Pattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    auto hasTransform = false;
    VectorF scaleIdentity(1.0f, 1.0f);
    Vector5F rotateIdentity(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    while (host) {
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, false);
        if (host->GetTag() == V2::WINDOW_SCENE_ETS_TAG) {
            break;
        }
        if (renderContext->HasMotionPath()) {
            hasTransform = true;
            break;
        }
        // has rotate.
        auto rotateVector = renderContext->GetTransformRotate();
        if (rotateVector.has_value() && !(rotateIdentity == rotateVector.value())) {
            hasTransform = true;
            break;
        }
        // has scale.
        auto scaleVector = renderContext->GetTransformScale();
        if (scaleVector.has_value() && !(scaleIdentity == scaleVector.value())) {
            hasTransform = true;
            break;
        }
        // has z translate.
        auto translate = renderContext->GetTransformTranslate();
        if (translate && !NearZero(translate->z.Value())) {
            hasTransform = true;
            break;
        }
        if (CheckHasTransformMatrix(renderContext)) {
            hasTransform = true;
            break;
        }
        host = host->GetAncestorNodeOfFrame(true);
    }
    return hasTransform;
}

bool BaseTextSelectOverlay::CheckHasTransformMatrix(const RefPtr<RenderContext>& context)
{
    auto transformMatrix = context->GetTransformMatrix();
    CHECK_NULL_RETURN(transformMatrix, false);
    const int32_t xIndex = 0;
    const int32_t yIndex = 1;
    const int32_t zIndex = 2;
    const int32_t wIndex = 3;
    DecomposedTransform transform;
    TransformUtil::DecomposeTransform(transform, transformMatrix.value());
    if (!NearZero(transform.translate[zIndex])) {
        return true;
    }
    Quaternion quaternionIdentity(0.0f, 0.0f, 0.0f, 1.0f);
    if (transform.quaternion != quaternionIdentity) {
        return true;
    }
    Vector3F scaleIdentity(1.0f, 1.0f, 1.0f);
    Vector3F scaleVector(transform.scale[xIndex], transform.scale[yIndex], transform.scale[zIndex]);
    if (!(scaleVector == scaleIdentity)) {
        return true;
    }
    Vector3F skewIdentity(0.0f, 0.0f, 0.0f);
    Vector3F skewVector(transform.skew[xIndex], transform.skew[yIndex], transform.skew[zIndex]);
    if (!(skewVector == skewIdentity)) {
        return true;
    }
    Vector4F perspectiveIdentity(0.0f, 0.0f, 0.0f, 1.0f);
    Vector4F perspectiveVector(transform.perspective[xIndex], transform.perspective[yIndex],
        transform.perspective[zIndex], transform.perspective[wIndex]);
    return !(perspectiveVector == perspectiveIdentity);
}

bool BaseTextSelectOverlay::GetClipHandleViewPort(RectF& rect)
{
    auto host = GetOwner();
    CHECK_NULL_RETURN(host, false);
    if (HasUnsupportedTransform()) {
        return false;
    }
    RectF contentRect;
    if (!GetFrameNodeContentRect(host, contentRect)) {
        return false;
    }
    contentRect.SetOffset(contentRect.GetOffset() + host->GetPaintRectWithTransform().GetOffset());
    auto parent = host->GetAncestorNodeOfFrame(true);
    while (parent) {
        RectF parentContentRect;
        if (!GetFrameNodeContentRect(parent, parentContentRect)) {
            return false;
        }
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, false);
        if (renderContext->GetClipEdge().value_or(false)) {
            contentRect = contentRect.IntersectRectT(parentContentRect);
        }
        contentRect.SetOffset(contentRect.GetOffset() + parent->GetPaintRectWithTransform().GetOffset());
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    contentRect.SetWidth(std::max(contentRect.Width(), 0.0f));
    contentRect.SetHeight(std::max(contentRect.Height(), 0.0f));
    UpdateClipHandleViewPort(contentRect);
    rect = contentRect;
    return true;
}

bool BaseTextSelectOverlay::GetFrameNodeContentRect(const RefPtr<FrameNode>& node, RectF& contentRect)
{
    CHECK_NULL_RETURN(node, false);
    if (GetScrollableClipContentRect(node, contentRect)) {
        return true;
    }
    auto geometryNode = node->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    if (geometryNode->GetContent()) {
        contentRect = geometryNode->GetContentRect();
    } else {
        contentRect = RectF(OffsetF(0.0f, 0.0f), geometryNode->GetFrameSize());
    }
    return true;
}

void BaseTextSelectOverlay::MarkOverlayDirty()
{
    if (SelectOverlayIsOn()) {
        auto host = GetOwner();
        CHECK_NULL_VOID(host);
        auto overlayNode = host->GetOverlayNode();
        CHECK_NULL_VOID(overlayNode);
        overlayNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void BaseTextSelectOverlay::ApplySelectAreaWithKeyboard(RectF& selectArea)
{
    auto host = GetOwner();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    auto keyboardInset = safeAreaManager->GetKeyboardInset();
    if (keyboardInset.Length() <= 0) {
        return;
    }
    if (GreatOrEqual(selectArea.Top(), keyboardInset.start)) {
        selectArea.SetHeight(0.0f);
    }
}

void BaseTextSelectOverlay::OnHandleMarkInfoChange(
    const std::shared_ptr<SelectOverlayInfo> info, SelectOverlayDirtyFlag flag)
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    if ((flag & UPDATE_HANDLE_COLOR_FLAG) == UPDATE_HANDLE_COLOR_FLAG) {
        info->handlerColor = GetHandleColor();
        manager->MarkHandleDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void BaseTextSelectOverlay::UpdateHandleColor()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->MarkInfoChange(UPDATE_HANDLE_COLOR_FLAG);
}

std::pair<ContentClipMode, std::optional<ContentClip>> BaseTextSelectOverlay::GetScrollableClipInfo(
    const RefPtr<FrameNode>& node)
{
    auto props = DynamicCast<ScrollablePaintProperty>(node->GetPaintProperty<PaintProperty>());
    CHECK_NULL_RETURN(props, std::make_pair(ContentClipMode::DEFAULT, std::nullopt));
    auto clip = props->GetContentClip();
    CHECK_NULL_RETURN(clip, std::make_pair(ContentClipMode::DEFAULT, std::nullopt));
    auto mode = clip->first;
    if (mode == ContentClipMode::DEFAULT) {
        if (node->GetTag() == V2::GRID_ETS_TAG || node->GetTag() == V2::SCROLL_ETS_TAG) {
            mode = ContentClipMode::BOUNDARY;
        } else if (node->GetTag() == V2::LIST_ETS_TAG || node->GetTag() == V2::WATERFLOW_ETS_TAG) {
            mode = ContentClipMode::CONTENT_ONLY;
        }
    }
    return std::make_pair(mode, clip);
}

bool BaseTextSelectOverlay::GetScrollableClipContentRect(const RefPtr<FrameNode>& node, RectF& rect)
{
    auto clipInfo = GetScrollableClipInfo(node);
    auto geo = node->GetGeometryNode();
    CHECK_NULL_RETURN(geo, false);
    switch (clipInfo.first) {
        case ContentClipMode::SAFE_AREA:
        case ContentClipMode::CONTENT_ONLY: {
            rect = geo->GetPaddingRect();
            rect.SetOffset(rect.GetOffset() - geo->GetFrameOffset());
            return true;
        }
        case ContentClipMode::BOUNDARY: {
            rect = geo->GetFrameRect();
            rect.SetOffset({ 0.0f, 0.0f });
            return true;
        }
        case ContentClipMode::CUSTOM: {
            auto contentClip = clipInfo.second;
            CHECK_NULL_RETURN(contentClip, false);
            auto shapeRect = contentClip->second;
            CHECK_NULL_RETURN(shapeRect, false);
            auto clipOffset = shapeRect->GetOffset();
            rect = RectF(clipOffset.GetX().ConvertToPx(), clipOffset.GetY().ConvertToPx(),
                shapeRect->GetWidth().ConvertToPx(), shapeRect->GetHeight().ConvertToPx());
            return true;
        }
        default:
            return false;
    }
}

bool BaseTextSelectOverlay::CheckHandleIsInSafeAreaPadding(const RefPtr<FrameNode>& node, const RectF& handle)
{
    auto clipInfo = GetScrollableClipInfo(node);
    if (clipInfo.first != ContentClipMode::SAFE_AREA) {
        return false;
    }
    auto layoutProperty = node->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto safeAreaPadding = layoutProperty->GetOrCreateSafeAreaPadding();
    if (!safeAreaPadding.HasValue()) {
        return false;
    }
    auto geo = node->GetGeometryNode();
    CHECK_NULL_RETURN(geo, false);
    auto paddingRect = geo->GetPaddingRect();
    if (safeAreaPadding.left && LessNotEqual(handle.Left(), paddingRect.Left())) {
        return true;
    }
    if (safeAreaPadding.top && LessNotEqual(handle.Top(), paddingRect.Top())) {
        return true;
    }
    if (safeAreaPadding.right && GreatNotEqual(handle.Right(), paddingRect.Right())) {
        return true;
    }
    if (safeAreaPadding.bottom && GreatNotEqual(handle.Bottom(), paddingRect.Bottom())) {
        return true;
    }
    return false;
}

bool BaseTextSelectOverlay::IsHandleInParentSafeAreaPadding(const RectF& firstRect, const RectF& secondRect)
{
    auto firstHandlePaint = firstRect;
    auto secondHandlePaint = secondRect;
    auto parent = GetOwner();
    while (parent) {
        if (GetOwner() != parent) {
            if (CheckHandleIsInSafeAreaPadding(parent, secondHandlePaint)) {
                return true;
            }
            if (!IsSingleHandle() && CheckHandleIsInSafeAreaPadding(parent, firstHandlePaint)) {
                return true;
            }
        }
        auto context = parent->GetRenderContext();
        CHECK_NULL_RETURN(context, false);
        firstHandlePaint += context->GetPaintRectWithTransform().GetOffset();
        secondHandlePaint += context->GetPaintRectWithTransform().GetOffset();
        parent = parent->GetAncestorNodeOfFrame();
    }
    return false;
}

bool BaseTextSelectOverlay::IsHandleInParentSafeAreaPadding()
{
    auto overlayManager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_RETURN(overlayManager, false);
    auto overlayInfo = overlayManager->GetSelectOverlayInfo();
    CHECK_NULL_RETURN(overlayInfo, false);
    return IsHandleInParentSafeAreaPadding(
        overlayInfo->firstHandle.localPaintRect, overlayInfo->secondHandle.localPaintRect);
}
} // namespace OHOS::Ace::NG
