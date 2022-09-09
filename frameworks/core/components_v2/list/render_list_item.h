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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_RENDER_LIST_ITEM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_RENDER_LIST_ITEM_H

#include "base/geometry/dimension.h"
#include "core/components_v2/list/list_item_component.h"
#include "core/gestures/long_press_recognizer.h"
#include "core/gestures/drag_recognizer.h"
#include "core/pipeline/base/render_node.h"
#include "core/animation/spring_motion.h"
#include "core/components/list/list_item_theme.h"

namespace OHOS::Ace::V2 {

enum class ListItemChildType {
    ITEM_CHILD,
    SWIPER_START,
    SWIPER_END
};

enum class ListItemSwipeIndex {
    SWIPER_END = -1,
    ITEM_CHILD = 0,
    SWIPER_START = 1,
};

class RenderListItem : public RenderNode {
    DECLARE_ACE_TYPE(V2::RenderListItem, RenderNode);

public:
    static RefPtr<RenderNode> Create();

    RenderListItem() = default;
    ~RenderListItem() override = default;

    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    void Paint(RenderContext& context, const Offset& offset) override;
    void UpdateTouchRect() override;

    virtual bool IsForwardLayout() const
    {
        return true;
    }

    bool IsDeletable() const
    {
        return component_ ? (component_->GetEditMode() & EditMode::DELETABLE) != 0 : false;
    }

    bool IsMovable() const
    {
        return component_ ? (component_->GetEditMode() & EditMode::MOVABLE) != 0 : false;
    }

    StickyMode GetSticky() const
    {
        return component_ ? component_->GetSticky() : StickyMode::NONE;
    }

    int32_t GetZIndex() const
    {
        return component_ ? component_->GetZIndex() : 0;
    }

    void SetEditMode(bool editMode);

    ACE_DEFINE_COMPONENT_EVENT(OnDeleteClick, void(RefPtr<RenderListItem>));
    ACE_DEFINE_COMPONENT_EVENT(OnSelect, void(RefPtr<RenderListItem>));

    RefPtr<Component> GetComponent() override
    {
        return component_;
    }

    int32_t GetEditMode() const
    {
        return component_->GetEditMode();
    }

    bool GetSelectable() const
    {
        return selectable_;
    }

    OnSelectFunc GetOnSelectId() const
    {
        return onSelectId_;
    }

    void MarkIsSelected(bool isSelected)
    {
        isSelected_ = isSelected;
    }

    bool IsSelected() const
    {
        return isSelected_;
    }

    bool IsDragStart() const
    {
        return isDragStart_;
    }

    Dimension GetBorderRadius() const
    {
        return borderRadius_;
    }
    void SetIndex(int index)
    {
        index_ = index;
    }
    int GetIndex() const
    {
        return index_;
    }

    void RegisterGetChildCallback(std::function<RefPtr<RenderNode>(ListItemChildType)> callback)
    {
        getChildCallback_ = std::move(callback);
    }

    RefPtr<RenderNode> GetSwiperStartRenderNode() const
    {
        return getChildCallback_ ? getChildCallback_(ListItemChildType::SWIPER_START) : nullptr;
    }

    RefPtr<RenderNode> GetSwiperEndRenderNode() const
    {
        return getChildCallback_ ? getChildCallback_(ListItemChildType::SWIPER_END) : nullptr;
    }

    RefPtr<RenderNode> GetItemChildRenderNode() const
    {
        return getChildCallback_ ? getChildCallback_(ListItemChildType::ITEM_CHILD) : nullptr;
    }

    template<class T>
    T MakeValue(double mainValue, double crossValue) const
    {
        return IsVertical() ? T(crossValue, mainValue) : T(mainValue, crossValue);
    }

    double GetMainSize(const Size& size) const
    {
        return IsVertical() ? size.Height() : size.Width();
    }

    double GetCrossSize(const Size& size) const
    {
        return IsVertical() ? size.Width() : size.Height();
    }

    double GetMainAxis(const Offset& size) const
    {
        return IsVertical() ? size.GetY() : size.GetX();
    }

    double GetCrossAxis(const Offset& size) const
    {
        return IsVertical() ? size.GetX() : size.GetY();
    }

protected:
    void OnTouchTestHit(
        const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result) override;

private:
    int index_ = -1;
    void CreateDeleteButton();
    void PerfLayoutSwiperMode();
    void InitDragRecognizer();
    void HandleDragStart(const DragStartInfo& info);
    void HandleDragUpdate(const DragUpdateInfo& info);
    void HandleDragEnd(const DragEndInfo& info);
    void StartSpringMotion(double start, double end, double velocity);
    double GetFriction();
    void UpdatePostion(double delta);
    double CalculateFriction(double gamma);
    bool IsVertical() const;

    RefPtr<ListItemComponent> component_;
    std::function<RefPtr<RenderNode>(ListItemChildType)> getChildCallback_;
    RefPtr<RenderNode> swiperStart_;
    RefPtr<RenderNode> swiperEnd_;

    RefPtr<RenderNode> child_;
    RefPtr<RenderNode> button_;
    bool editMode_ = false;

    RefPtr<LongPressRecognizer> longPressRecognizer_;
    OnSelectFunc onSelectId_;
    bool selectable_ = true;
    bool isSelected_ = false;
    bool isDragStart_ = false;
    Dimension borderRadius_;

    double curOffset_ = 0.0;
    RefPtr<DragRecognizer> dragDetector_;
    RefPtr<Animator> springController_;
    RefPtr<SpringMotion> springMotion_;
    ListItemSwipeIndex swipeIndex = ListItemSwipeIndex::ITEM_CHILD;
    Size startSize_;
    Size endSize_;
    SwipeEdgeEffect edgeEffect_ = SwipeEdgeEffect::Spring;
    RefPtr<ListItemTheme> theme_;

    ACE_DISALLOW_COPY_AND_MOVE(RenderListItem);
};

} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_RENDER_LIST_ITEM_H
