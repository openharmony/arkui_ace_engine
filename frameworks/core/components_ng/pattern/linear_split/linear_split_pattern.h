/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_SPLIT_LINEAR_SPLIT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_SPLIT_LINEAR_SPLIT_PATTERN_H

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/frame_scene_status.h"
#include "core/components_ng/event/input_event.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/linear_split/linear_split_layout_algorithm.h"
#include "core/components_ng/pattern/linear_split/linear_split_layout_property.h"
#include "core/components_ng/pattern/linear_split/linear_split_model_ng.h"
#include "core/components_ng/pattern/linear_split/linear_split_paint_method.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class LinearSplitPattern : public Pattern {
    DECLARE_ACE_TYPE(LinearSplitPattern, Pattern);

public:
    explicit LinearSplitPattern(SplitType splitType) : splitType_(splitType) {}

    ~LinearSplitPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<LinearSplitLayoutAlgorithm>(splitType_, dragSplitOffset_, childrenDragPos_, isOverParent_);
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<LinearSplitLayoutProperty>();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return MakeRefPtr<LinearSplitPaintMethod>(childrenOffset_, splitLength_, splitType_);
    }

    OffsetF GetParentOffset() const
    {
        return parentOffset_;
    }

private:
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;

    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandlePanStart(const GestureEvent& info);
    void HandlePanUpdate(const GestureEvent& info);
    void HandlePanEnd(const GestureEvent& info);
    void HandlePanStartBeforeAPI10(const GestureEvent& info);
    void HandlePanUpdateBeforeAPI10(const GestureEvent& info);
    void InitMouseEvent(const RefPtr<InputEventHub>& inputHub);
    void HandleMouseEvent(MouseInfo& info);
    void HandleHoverEvent(bool isHovered);
    MouseFormat GetMouseFormat();
    MouseFormat GetMouseFormatBeforeAPI10();
    void GetdragedSplitIndexOrIsMoving(const Point& point);
    bool ConstrainDragRange();
    bool IsStuck();
    bool ReachStart();
    bool ReachEnd();
    float GetMinPosFromIndex(std::size_t index);
    float GetMaxPosFromIndex(std::size_t index);
    void UpdateDragFRCSceneInfo(const GestureEvent& info, SceneStatus sceneStatus);
    bool CheckChildrenConstrains();

    std::vector<OffsetF> childrenOffset_;
    float splitLength_ = 0.0f;
    SplitType splitType_;
    RefPtr<DragEvent> dragEvent_;
    RefPtr<InputEvent> mouseEvent_;
    RefPtr<InputEvent> hoverEvent_;
    RefPtr<PanEvent> panEvent_;
    bool resizable_ = false;

    std::size_t dragedSplitIndex_ = -1;
    std::size_t mouseDragedSplitIndex_ = -1;
    std::vector<Rect> splitRects_;
    std::vector<float> dragSplitOffset_;
    OffsetF parentOffset_;
    std::vector<float> childrenDragPos_;
    std::vector<float> childrenConstrains_;
    bool isDragedMoving_ = false;
    bool isDraged_ = false;
    bool isOverParent_ = false;
    float preOffset_ = 0.0f;

    ACE_DISALLOW_COPY_AND_MOVE(LinearSplitPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_SPLIT_LINEAR_SPLIT_PATTERN_H