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
    UpdateTransformFlag();
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

void BaseTextSelectOverlay::HideMenu(bool noAnimation)
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->HideOptionMenu(noAnimation);
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
    auto offset = OffsetF(touchPoint.GetX(), touchPoint.GetY());
    if (hasTransform_) {
        RevertLocalPointWithTransform(offset);
        offset += GetPaintOffsetWithoutTransform();
    }
    return GetVisibleFrameRect().IsInRegion(PointF(offset.GetX(), offset.GetY()));
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
    if (hasTransform_) {
        overlayInfo.callerNodeInfo = {
            .paintFrameRect = GetPaintRectWithTransform(),
            .paintOffset = GetPaintRectOffsetWithTransform()
        };
    }
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
    auto paintOffset = GetPaintOffsetWithoutTransform() - context->GetRootRect().GetOffset();
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
    auto paintOffset = GetPaintOffsetWithoutTransform() - context->GetRootRect().GetOffset();
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
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        auto paintOffset = renderContext->GetPaintRectWithoutTransform().GetOffset();
        for (auto& pointElement : convertPoints) {
            pointElement = pointElement + paintOffset;
            renderContext->GetPointTransform(pointElement);
        }
        parent = parent->GetAncestorNodeOfFrame();
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
        parent = parent->GetAncestorNodeOfFrame();
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
    while (parent) {
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, OffsetF());
        offset += renderContext->GetPaintRectWithoutTransform().GetOffset();
        parent = parent->GetAncestorNodeOfFrame();
    }
    return offset;
}

void BaseTextSelectOverlay::UpdateTransformFlag()
{
    auto pattern = GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    while (host) {
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        auto noTransformRect = renderContext->GetPaintRectWithoutTransform();
        auto transformRect = renderContext->GetPaintRectWithTransform();
        hasTransform_ = noTransformRect != transformRect;
        if (hasTransform_) {
            break;
        }
        host = host->GetAncestorNodeOfFrame();
    }
}
} // namespace OHOS::Ace::NG
