/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkPath.h"
#endif

#include "base/geometry/dimension.h"
#include "core/components/bubble/bubble_component.h"
#include "core/components/common/properties/edge.h"
#include "core/components/slider/render_slider.h"
#include "core/gestures/raw_recognizer.h"
#include "core/pipeline/base/render_node.h"

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BUBBLE_RENDER_BUBBLE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BUBBLE_RENDER_BUBBLE_H

namespace OHOS::Ace {
namespace {

constexpr Dimension BEZIER_WIDTH_HALF = 16.0_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_FIRST = 1.3_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_SECOND = 3.2_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_THIRD = 6.6_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_FOURTH = 16.0_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_FIRST = 0.1_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_SECOND = 3.0_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_THIRD = 8.0_vp;

} // namespace

class RenderBubble : public RenderNode {
    DECLARE_ACE_TYPE(RenderBubble, RenderNode);

public:
    ~RenderBubble() override = default;

    static RefPtr<RenderNode> Create();
    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    bool PopBubble();
    void FirePopEvent();
    bool HandleMouseEvent(const MouseEvent& event) override;
    double GetArrowOffset(const Placement& placement);
    void OnPaintFinish() override;

protected:
    enum class ErrorPositionType {
        NORMAL = 0,
        TOP_LEFT_ERROR,
        BOTTOM_RIGHT_ERROR,
    };

    RenderBubble();

    void OnHiddenChanged(bool hidden) override;
    void OnTouchTestHit(
        const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result) override;

    void HandleTouch(const Offset& clickPosition);
    Offset GetChildPosition(const Size& childSize);
    Offset GetPositionWithPlacement(const Size& childSize, const Offset& topPosition, const Offset& bottomPosition,
        const Offset& topArrowPosition, const Offset& bottomArrowPosition);
    Offset FitToScreen(const Offset& fitPosition, const Size& childSize);
    ErrorPositionType GetErrorPositionType(const Offset& childOffset, const Size& childSize);
    void UpdateAccessibilityInfo(Size size, Offset offset);
    void InitAccessibilityEventListener();
#ifndef USE_ROSEN_DRAWING
    void BuildCornerPath(SkPath& path, Placement placement, double radius);
    void BuildTopLinePath(SkPath& path, double arrowOffset, double radius);
    void BuildRightLinePath(SkPath& path, double arrowOffset, double radius);
    void BuildBottomLinePath(SkPath& path, double arrowOffset, double radius);
    void BuildLeftLinePath(SkPath& path, double arrowOffset, double radius);
    void BuildCompletePath(SkPath& path);
#else
    void BuildCornerPath(RSPath& path, Placement placement, double radius);
    void BuildTopLinePath(RSPath& path, double arrowOffset, double radius);
    void BuildRightLinePath(RSPath& path, double arrowOffset, double radius);
    void BuildBottomLinePath(RSPath& path, double arrowOffset, double radius);
    void BuildLeftLinePath(RSPath& path, double arrowOffset, double radius);
    void BuildCompletePath(RSPath& path);
#endif

    static const Dimension BUBBLE_SPACING;

    bool isShow_ = true;
    bool enableArrow_ = true;
    // Is there has enough space for showing arrow.
    bool showTopArrow_ = true;
    bool showBottomArrow_ = true;
    bool showCustomArrow_ = false;
    bool useCustom_ = false;
    bool isShowInSubWindow_ = false;
    Edge padding_;
    Edge margin_;
    Border border_;
    Size childSize_;
    Size targetSize_;
    Offset childOffset_;
    Offset targetOffset_;
    Offset arrowPosition_;
    Dimension arrowOffset_;
    Color maskColor_;
    Color backgroundColor_;
    Placement placement_ = Placement::BOTTOM;
    Placement arrowPlacement_ = Placement::TOP;
    ComposeId targetId_;
    std::function<void(const std::string&)> onVisibilityChange_;
    RefPtr<RawRecognizer> rawDetector_;
    RefPtr<BubbleComponent> bubbleComponent_;
    WeakPtr<StackElement> weakStack_;
    Dimension targetSpace_;

private:
    void InitArrowState();
    // Get size and position of target by targetId.
    void InitTargetSizeAndPosition();
    void UpdateCustomChildPosition();
    void GenerateChildPosition(const Size& childSize);
    void UpdateTouchRegion();
    void InitEdgeSize(Edge& edge);
    void InitArrowTopAndBottomPosition(Offset& topArrowPosition, Offset& bottomArrowPosition, Offset& topPosition,
        Offset& bottomPosition, const Size& childSize);
    void UpdateArrowOffset(const RefPtr<BubbleComponent>& bubble, const Placement& placement);
    TouchRegion touchRegion_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BUBBLE_RENDER_BUBBLE_H
