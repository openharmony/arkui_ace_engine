/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SPLIT_CONTAINER_RENDER_SPLIT_CONTAINER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SPLIT_CONTAINER_RENDER_SPLIT_CONTAINER_H

#include "base/memory/referenced.h"
#include "core/components/flex/render_flex.h"
#include "core/components/split_container/split_container_component.h"
#include "core/gestures/drag_recognizer.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

class RenderSplitContainer : public RenderNode {
    DECLARE_ACE_TYPE(RenderSplitContainer, RenderNode);

public:
    RenderSplitContainer() = default;
    ~RenderSplitContainer() override = default;

    void LayoutChildren();
    virtual void HandleDragStart(const Offset& startPoint) = 0;
    virtual void HandleDragUpdate(const Offset& currentPoint) = 0;
    virtual void HandleDragEnd(const Offset& endPoint, double velocity) = 0;
    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    void InitializeRecognizer();

    bool GetResizable() const
    {
        return resizable_;
    }

    bool HandleMouseEvent(const MouseEvent& event) override;
    void HandleMouseHoverEvent(MouseState mouseState) override;

protected:
    void OnTouchTestHit(
        const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result) override;
    virtual void ResetComponentMember();
    RefPtr<DragRecognizer> dragDetector_;
    bool resizable_ = false;
    double layoutWidth_ = 0.0;
    double layoutHeight_ = 0.0;
    bool preIsDraged_ = false;
    bool isDraged_ = false;
    bool isDragedMoving_ = false;
    std::map<int32_t, std::list<MagicLayoutNode>> magicNodes_;
    std::set<RefPtr<RenderNode>> displayNodes_;
    std::set<RefPtr<RenderNode>> disableHideNodes_;
    std::vector<Rect> splitRects_;
    std::vector<double> dragSplitOffset_;

private:
    void UpdateComponentAttr(const RefPtr<Component>& component);
    void InitProperties();
    double GetMainSize(const RefPtr<RenderNode>& renderNode) const;
    double GetMainMinSize(const RefPtr<RenderNode>& renderNode) const;
    void UpdateDisplayNode();

    SplitType splitType_ = SplitType::ROW_SPLIT;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SPLIT_CONTAINER_RENDER_SPLIT_CONTAINER_H