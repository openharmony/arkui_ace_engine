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

#include "core/components_ng/pattern/text/base_text_select_geometry_utils.h"

#include <algorithm>
#include <unordered_map>

#include "core/common/container.h"
#include "base/geometry/transform_util.h"
#include "core/components_ng/pattern/scrollable/nestable_scroll_container.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"
#include "core/components_ng/render/render_context.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

bool BaseTextSelectGeometryUtils::GetFrameNodeContentRect(const RefPtr<FrameNode>& node, RectF& contentRect)
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
        contentRect = RectF(OffsetF(0.0f, 0.0f), renderContext->GetPaintRectWithoutTransform().GetSize());
    }
    return true;
}

bool BaseTextSelectGeometryUtils::GetScrollableClipContentRect(const RefPtr<FrameNode>& node, RectF& rect)
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

std::pair<ContentClipMode, std::optional<ContentClip>> BaseTextSelectGeometryUtils::GetScrollableClipInfo(
    const RefPtr<FrameNode>& node)
{
    auto props = AceType::DynamicCast<ScrollablePaintProperty>(node->GetPaintProperty<PaintProperty>());
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

bool BaseTextSelectGeometryUtils::CheckUnsupportedTransformMatrix(
    const RefPtr<RenderContext>& context, bool checkScale)
{
    CHECK_NULL_RETURN(context, false);
    auto transformMatrix = context->GetTransformMatrix();
    if (!transformMatrix) {
        return false;
    }
    DecomposedTransform transform;
    TransformUtil::DecomposeTransform(transform, transformMatrix.value());
    const int32_t zIndex = 2;
    Quaternion identity(0.0f, 0.0f, 0.0f, 1.0f);
    if (transform.quaternion != identity || !NearZero(transform.translate[zIndex])) {
        return true;
    }
    if (checkScale) {
        for (const auto& scalValue : transform.scale) {
            if (!NearEqual(scalValue, 1.0f)) {
                return true;
            }
        }
    }
    return false;
}

bool BaseTextSelectGeometryUtils::CheckHasTransformMatrix(const RefPtr<RenderContext>& context)
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

bool BaseTextSelectGeometryUtils::HasUnsupportedTransform(
    const RefPtr<FrameNode>& host, bool checkScale)
{
    CHECK_NULL_RETURN(host, false);
    auto node = host;
    while (node) {
        auto renderContext = node->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, false);
        if (node->GetTag() == V2::WINDOW_SCENE_ETS_TAG) {
            return false;
        }
        if (renderContext->HasMotionPath()) {
            return true;
        }
        auto rotateVector = renderContext->GetTransformRotate();
        if (rotateVector.has_value() && !NearZero(rotateVector->w) &&
            !(NearZero(rotateVector->x) && NearZero(rotateVector->y) && NearZero(rotateVector->z))) {
            return true;
        }
        if (CheckUnsupportedTransformMatrix(renderContext, checkScale)) {
            return true;
        }
        auto translate = renderContext->GetTransformTranslate();
        if (translate && !NearZero(translate->z.Value())) {
            return true;
        }
        if (checkScale) {
            auto scale = renderContext->GetTransformScale();
            if (scale && (!NearEqual(scale->x, 1.0f) || !NearEqual(scale->y, 1.0f))) {
                return true;
            }
        }
        node = node->GetAncestorNodeOfFrame(true);
    }
    return false;
}

bool BaseTextSelectGeometryUtils::HasTransformAttr(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_RETURN(host, false);
    auto node = host;
    auto hasTransform = false;
    VectorF scaleIdentity(1.0f, 1.0f);
    Vector5F rotateIdentity(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    while (node) {
        auto renderContext = node->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, false);
        if (node->GetTag() == V2::WINDOW_SCENE_ETS_TAG) {
            break;
        }
        if (renderContext->HasMotionPath()) {
            hasTransform = true;
            break;
        }
        auto rotateVector = renderContext->GetTransformRotate();
        if (rotateVector.has_value() && !(rotateIdentity == rotateVector.value())) {
            hasTransform = true;
            break;
        }
        auto scaleVector = renderContext->GetTransformScale();
        if (scaleVector.has_value() && !(scaleIdentity == scaleVector.value())) {
            hasTransform = true;
            break;
        }
        auto translate = renderContext->GetTransformTranslate();
        if (translate && !NearZero(translate->z.Value())) {
            hasTransform = true;
            break;
        }
        if (CheckHasTransformMatrix(renderContext)) {
            hasTransform = true;
            break;
        }
        node = node->GetAncestorNodeOfFrame(true);
    }
    return hasTransform;
}

bool BaseTextSelectGeometryUtils::GetRenderClipValue(const RefPtr<FrameNode>& host, bool defaultClip)
{
    CHECK_NULL_RETURN(host, defaultClip);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, defaultClip);
    return renderContext->GetClipEdge().value_or(defaultClip);
}

RectF BaseTextSelectGeometryUtils::GetVisibleRect(const RefPtr<FrameNode>& node, const RectF& visibleRect)
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

RectF BaseTextSelectGeometryUtils::MergeSelectedBoxes(
    const std::vector<RectF>& boxes, const RectF& contentRect, const RectF& textRect, const OffsetF& paintOffset)
{
    if (boxes.empty()) {
        return RectF();
    }
    auto frontRect = boxes.front();
    auto backRect = boxes.back();
    float selectAreaRight = frontRect.Right();
    float selectAreaLeft = frontRect.Left();
    if (boxes.size() != 1) {
        std::unordered_map<float, RectF> selectLineRect;
        for (const auto& box : boxes) {
            auto combineLineRect = box;
            auto top = box.Top();
            if (selectLineRect.find(top) == selectLineRect.end()) {
                selectLineRect.insert({ top, combineLineRect });
            } else {
                combineLineRect = combineLineRect.CombineRectT(selectLineRect[top]);
                selectLineRect.insert({ top, combineLineRect });
            }
            selectAreaRight = std::max(selectAreaRight, combineLineRect.Right());
            selectAreaLeft = std::min(selectAreaLeft, combineLineRect.Left());
        }
    }
    return { selectAreaLeft + textRect.GetX() + paintOffset.GetX(),
        frontRect.GetY() + textRect.GetY() + paintOffset.GetY(), selectAreaRight - selectAreaLeft,
        backRect.Bottom() - frontRect.Top() };
}

void BaseTextSelectGeometryUtils::GetGlobalPointsWithTransform(
    const RefPtr<FrameNode>& host, bool hasTransform, std::vector<OffsetF>& points)
{
    CHECK_NULL_VOID(hasTransform);
    auto parent = host;
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

void BaseTextSelectGeometryUtils::GetGlobalRectWithTransform(
    const RefPtr<FrameNode>& host, bool hasTransform, RectF& localRect)
{
    CHECK_NULL_VOID(hasTransform);
    auto rectVertex = GetGlobalRectVertexWithTransform(host, hasTransform, localRect);
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

std::vector<OffsetF> BaseTextSelectGeometryUtils::GetGlobalRectVertexWithTransform(
    const RefPtr<FrameNode>& host, bool hasTransform, const RectF& rect, float extendValue)
{
    std::vector<OffsetF> rectVertices = {
        OffsetF(rect.Left() - extendValue, rect.Top() - extendValue),
        OffsetF(rect.Right() + extendValue, rect.Top() - extendValue),
        OffsetF(rect.Left() - extendValue, rect.Bottom() + extendValue),
        OffsetF(rect.Right() + extendValue, rect.Bottom() + extendValue)
    };
    GetGlobalPointsWithTransform(host, hasTransform, rectVertices);
    return rectVertices;
}

bool BaseTextSelectGeometryUtils::CalculateClippedRect(const RefPtr<FrameNode>& host, RectF& contentRect)
{
    CHECK_NULL_RETURN(host, false);
    auto parent = host->GetAncestorNodeOfFrame(true);
    while (parent) {
        RectF parentContentRect;
        if (!GetFrameNodeContentRect(parent, parentContentRect)) {
            return false;
        }
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, false);
        if (renderContext->GetClipEdge().value_or(false)) {
            contentRect = contentRect.Constrain(parentContentRect);
        }
        contentRect.SetOffset(contentRect.GetOffset() + parent->GetPaintRectWithTransform().GetOffset());
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return true;
}

void BaseTextSelectGeometryUtils::UpdateClipHandleViewPort(
    const RefPtr<FrameNode>& host, bool renderClipValue, RectF& rect)
{
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (renderClipValue) {
        return;
    }
    auto clipNode = host->GetAncestorNodeOfFrame(true);
    RefPtr<FrameNode> prevNode;
    while (clipNode) {
        renderContext = clipNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        if (renderContext->GetClipEdge().value_or(false)) {
            break;
        }
        prevNode = clipNode;
        clipNode = clipNode->GetAncestorNodeOfFrame(true);
    }
    if (clipNode) {
        RectF visibleRect;
        RectF frameRect;
        clipNode->GetVisibleRect(visibleRect, frameRect);
        if (GreatNotEqual(rect.Top(), visibleRect.Bottom()) || GreatNotEqual(rect.Left(), visibleRect.Right())) {
            return;
        }
        rect.SetHeight(visibleRect.Bottom() - rect.Top());
        rect.SetWidth(visibleRect.Right() - rect.Left());
        return;
    }
    // root node.
    if (prevNode) {
        auto geoNode = prevNode->GetGeometryNode();
        CHECK_NULL_VOID(geoNode);
        RectF visibleRect = geoNode->GetFrameRect();
        if (GreatNotEqual(rect.Top(), visibleRect.Height()) || GreatNotEqual(rect.Left(), visibleRect.Width())) {
            return;
        }
        rect.SetHeight(visibleRect.Height() - rect.Top());
        rect.SetWidth(visibleRect.Width() - rect.Left());
    }
}

} // namespace OHOS::Ace::NG
