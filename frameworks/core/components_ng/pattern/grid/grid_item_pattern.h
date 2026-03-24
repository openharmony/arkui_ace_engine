/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_ITEM_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_ITEM_PATTERN_H

#include <memory>
#include <optional>

#include "core/components_ng/pattern/grid/grid_item_constants.h"
#include "core/components_ng/pattern/scrollable/selectable_item_pattern.h"

namespace OHOS::Ace {
class Color;
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
class GridItemAccessibilityProperty;
class GridItemEventHub;
class GridItemLayoutAlgorithm;
class GridItemLayoutProperty;
class InspectorFilter;
class InputEvent;
class ShallowBuilder;
class TouchEventImpl;

class ACE_EXPORT GridItemPattern : public SelectableItemPattern {
    DECLARE_ACE_TYPE(GridItemPattern, SelectableItemPattern);

public:
    explicit GridItemPattern(const RefPtr<ShallowBuilder>& shallowBuilder);
    explicit GridItemPattern(const RefPtr<ShallowBuilder>& shallowBuilder, GridItemStyle gridItemStyle);
    ~GridItemPattern() override;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override;

    RefPtr<EventHub> CreateEventHub() override;

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override;


    void BeforeCreateLayoutWrapper() override;

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override
    {
        return false;
    }

    void SetForceRebuild(bool forceRebuild)
    {
        forceRebuild_ = forceRebuild;
    }

    void SetSelectable(bool selectable);

    bool ForceRebuild() const
    {
        return forceRebuild_;
    }

    bool Selectable() const
    {
        return selectable_;
    }

    FocusPattern GetFocusPattern() const override;

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    void MarkIsSelected(bool isSelected);

    void SetIrregularItemInfo(GridItemIndexInfo info)
    {
        irregularItemInfo_ = info;
    }
    std::optional<GridItemIndexInfo> GetIrregularItemInfo() const
    {
        return irregularItemInfo_;
    }

    void DumpAdvanceInfo() override;
    void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) override;

    void ResetGridItemInfo()
    {
        irregularItemInfo_.reset();
    }

    void UpdateGridItemStyle(GridItemStyle gridItemStyle);
    void UpdateGridItemStyleMultiThread(GridItemStyle gridItemStyle);

    bool IsEnableChildrenMatchParent() override
    {
        return true;
    }

    bool IsEnableFix() override
    {
        return true;
    }

    bool IsEnableMatchParent() override
    {
        return true;
    }

    GridItemStyle GetGridItemStyle() const
    {
        return gridItemStyle_;
    }

protected:
    void OnModifyDone() override;

private:
    void SetAccessibilityAction();
    void OnAttachToFrameNode() override;
    void OnAttachToFrameNodeMultiThread();
    void OnAttachToMainTree() override;
    void OnAttachToMainTreeMultiThread();
    void InitFocusPaintRect(const RefPtr<FocusHub>& focusHub);
    void GetInnerFocusPaintRect(RoundRect& paintRect);
    Color GetBlendGgColor();
    void InitHoverEvent();
    void HandleHoverEvent(bool isHover);
    void InitPressEvent();
    void HandlePressEvent(bool isPressed);
    void InitDisableStyle();
    void InitOnFocusEvent(const RefPtr<FocusHub>& focusHub);
    void HandleFocusEvent();

    RefPtr<ShallowBuilder> shallowBuilder_;
    bool forceRebuild_ = false;
    bool selectable_ = true;

    RefPtr<InputEvent> hoverEvent_;
    RefPtr<TouchEventImpl> touchListener_;
    bool isHover_ = false;
    bool isPressed_ = false;
    GridItemStyle gridItemStyle_ = GridItemStyle::NONE;
    std::optional<GridItemIndexInfo> irregularItemInfo_;

    ACE_DISALLOW_COPY_AND_MOVE(GridItemPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_ITEM_PATTERN_H
