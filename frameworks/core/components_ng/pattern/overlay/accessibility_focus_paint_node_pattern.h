/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ROOT_ACCESSIBILITY_FOCUS_PAINT_NODE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ROOT_ACCESSIBILITY_FOCUS_PAINT_NODE_PATTERN_H

#include "core/components_ng/pattern/overlay/accessibility_focus_paint_node_layout_algorithm.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/render/render_context.h"
#include "core/pipeline_ng/pipeline_context.h"

#define CENTER_DIVISOR 2

namespace OHOS::Ace::NG {

class AccessibilityFocusPaintNodePattern : public Pattern {
    DECLARE_ACE_TYPE(AccessibilityFocusPaintNodePattern, Pattern);

public:
    AccessibilityFocusPaintNodePattern(const WeakPtr<FrameNode>& frameNode) : focusNode_(frameNode) {};
    ~AccessibilityFocusPaintNodePattern() override = default;
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<AccessibilityFocusPaintLayoutAlgorithm>();
    }

    void UpdateFocusNode(const WeakPtr<FrameNode>& frameNode)
    {
        RefPtr<NG::FrameNode> targetNode = frameNode.Upgrade();
        CHECK_NULL_VOID(targetNode);
        ACE_SCOPED_TRACE("AccessibilityFocusPainNode UpdateFocusNode[%s]", targetNode->GetTag().c_str());
        focusNode_ = targetNode;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        targetNode->SetPaintNode(host);
    }

    void UpdateRootNode(const WeakPtr<UINode>& frameNode)
    {
        rootNode_ = frameNode;
    }

    void UpdateRenderWithFocusNode()
    {
        RefPtr<NG::FrameNode> focusNode = focusNode_.Upgrade();
        CHECK_NULL_VOID(focusNode);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        ChangePaintNodeLayoutInner(focusNode, host, 0, 0);
    }

    void SetPosition(const NG::OffsetF& offset, const RefPtr<NG::FrameNode>& frameNode)
    {
        CHECK_NULL_VOID(frameNode);
        auto renderContext = frameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdatePosition(
            { Dimension(offset.GetX(), DimensionUnit::PX), Dimension(offset.GetY(), DimensionUnit::PX) });
    }

    void ChangeSize(float width, float height, const RefPtr<NG::FrameNode>& frameNode)
    {
        CHECK_NULL_VOID(frameNode);
        NG::CalcSize idealSize = { NG::CalcLength(width), NG::CalcLength(height) };
        NG::MeasureProperty layoutConstraint;
        layoutConstraint.selfIdealSize = idealSize;
        layoutConstraint.maxSize = idealSize;
        frameNode->UpdateLayoutConstraint(layoutConstraint);
    }

    void ChangelRotate(float degree, const RefPtr<NG::FrameNode>& frameNode)
    {
        auto value = NG::Vector5F(0, 0, 1, degree, 0);
        CHECK_NULL_VOID(frameNode);
        auto context = frameNode->GetRenderContext();
        CHECK_NULL_VOID(context);
        context->UpdateTransformRotate(value);
    }

    OffsetF GetPaintRectCenter(const RefPtr<NG::FrameNode>& focusNode)
    {
        CHECK_NULL_RETURN(focusNode, OffsetF());
        auto context = focusNode->GetRenderContext();
        CHECK_NULL_RETURN(context, OffsetF());
        auto paintRect = context->GetPaintRectWithoutTransform();
        auto offset = paintRect.GetOffset();
        PointF pointNode(offset.GetX() + paintRect.Width() / CENTER_DIVISOR,
            offset.GetY() + paintRect.Height() / CENTER_DIVISOR);
        context->GetPointTransformRotate(pointNode);
        auto parent = focusNode->GetAncestorNodeOfFrame(true);
        while (parent) {
            auto renderContext = parent->GetRenderContext();
            CHECK_NULL_RETURN(renderContext, OffsetF());
            offset = renderContext->GetPaintRectWithoutTransform().GetOffset();
            pointNode.SetX(offset.GetX() + pointNode.GetX());
            pointNode.SetY(offset.GetY() + pointNode.GetY());
            renderContext->GetPointTransformRotate(pointNode);
            parent = parent->GetAncestorNodeOfFrame(true);
        }
        return OffsetF(pointNode.GetX(), pointNode.GetY());
    }

    void IntersectRectF(RectF& finalRect, RectF parentRect)
    {
        auto left = std::max(finalRect.GetX(), parentRect.GetX());
        auto top = std::max(finalRect.GetY(), parentRect.GetY());
        auto right = std::min(finalRect.Width() + finalRect.GetX(), parentRect.Width() + parentRect.GetX());
        auto bottom = std::min(finalRect.Height() + finalRect.GetY(), parentRect.Height() + parentRect.GetY());
        if (left < right && top < bottom) {
            finalRect = RectF(left, top, right - left, bottom - top);
        } else {
            finalRect = RectF();
        }
    }

    bool IsScrollable(const RefPtr<NG::FrameNode>& frameNode)
    {
        CHECK_NULL_RETURN(frameNode, false);
        auto tag = frameNode->GetTag();
        return (tag == V2::LIST_ETS_TAG || tag == V2::SCROLL_ETS_TAG || tag == V2::TEXT_PICKER_ETS_TAG ||
            tag == V2::WATERFLOW_ETS_TAG || tag == V2::SWIPER_ETS_TAG || tag == V2::GRID_ETS_TAG);
    }

    RectF GetScrollableAncestorClip(const RefPtr<NG::FrameNode>& frameNode)
    {
        RectF rect;
        auto pipeline = frameNode->GetContextRefPtr();
        CHECK_NULL_RETURN(pipeline, rect);
        rect = pipeline->GetRootRect();
        auto parentFrameNode = frameNode->GetAncestorNodeOfFrame(true);
        while (parentFrameNode) {
            if (!IsScrollable(parentFrameNode)) {
                parentFrameNode = parentFrameNode->GetAncestorNodeOfFrame(true);
                continue;
            }
            auto parentContent = parentFrameNode->GetTransformRectRelativeToWindow();
            IntersectRectF(rect, parentContent);
            parentFrameNode = parentFrameNode->GetAncestorNodeOfFrame(true);
        }
        return rect;
    }

    void ChangePaintNodeLayoutInner(
        const RefPtr<NG::FrameNode>& focusNode, const RefPtr<NG::FrameNode>& paintNode, int32_t left, int32_t top)
    {
        CHECK_NULL_VOID(focusNode);
        auto trueCenter = GetPaintRectCenter(focusNode);
        auto rect = focusNode->GetTransformRectRelativeToWindow();
        RectF showRect(trueCenter.GetX() - (rect.Width() / CENTER_DIVISOR) - left,
            trueCenter.GetY() - (rect.Height() / CENTER_DIVISOR) - top,
            rect.Width(), rect.Height());
        auto scrollableAncestorsClip = GetScrollableAncestorClip(focusNode);
        IntersectRectF(showRect, scrollableAncestorsClip);
        auto host = GetHost();
        CHECK_NULL_VOID(host);

        auto geometryNode = focusNode->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto focusNodeGeoNode = geometryNode->Clone();
        focusNodeGeoNode->SetFrameOffset(NG::OffsetF(std::round(showRect.GetX()), std::round(showRect.GetY())));
        focusNodeGeoNode->SetFrameHeight(std::round(showRect.Height()));
        focusNodeGeoNode->SetFrameWidth(std::round(showRect.Width()));
        host->SetGeometryNode(focusNodeGeoNode);
        host->ForceSyncGeometryNode();

        auto paintRenderContext = host->GetRenderContext();
        CHECK_NULL_VOID(paintRenderContext);
        auto focusRenderContext = focusNode->GetRenderContext();
        CHECK_NULL_VOID(focusRenderContext);
        if (focusRenderContext->HasOpacity()) {
            paintRenderContext->UpdateOpacity(focusRenderContext->GetOpacityValue());
        }
    }

    void OnDetachFromFocusNode()
    {
        RefPtr<NG::FrameNode> targetNode = focusNode_.Upgrade();
        CHECK_NULL_VOID(targetNode);
        focusNode_ = nullptr;
    }

    WeakPtr<FrameNode>& GetFocusNode()
    {
        return focusNode_;
    }

    WeakPtr<UINode>& GetRootNode()
    {
        return rootNode_;
    }

private:
    WeakPtr<FrameNode> focusNode_;
    WeakPtr<UINode> rootNode_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ROOT_ACCESSIBILITY_FOCUS_PAINT_NODE_PATTERN_H