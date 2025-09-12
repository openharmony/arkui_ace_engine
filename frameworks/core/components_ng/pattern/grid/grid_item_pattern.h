/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/grid/grid_item_accessibility_property.h"
#include "core/components_ng/pattern/grid/grid_item_event_hub.h"
#include "core/components_ng/pattern/grid/grid_item_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_item_layout_property.h"
#include "core/components_ng/pattern/grid/grid_item_model.h"
#include "core/components_ng/pattern/grid/grid_item_theme.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/syntax/shallow_builder.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT GridItemPattern : public Pattern {
    DECLARE_ACE_TYPE(GridItemPattern, Pattern);

public:
    explicit GridItemPattern(const RefPtr<ShallowBuilder>& shallowBuilder) : shallowBuilder_(shallowBuilder) {}
    explicit GridItemPattern(const RefPtr<ShallowBuilder>& shallowBuilder, GridItemStyle gridItemStyle)
        : shallowBuilder_(shallowBuilder), gridItemStyle_(gridItemStyle)
    {}
    ~GridItemPattern() override = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<GridItemLayoutAlgorithm>();
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<GridItemLayoutProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<GridItemEventHub>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<GridItemAccessibilityProperty>();
    }


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

    FocusPattern GetFocusPattern() const override
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, FocusPattern());
        auto pipeline = host->GetContext();
        CHECK_NULL_RETURN(pipeline, FocusPattern());
        auto theme = pipeline->GetTheme<GridItemTheme>();
        CHECK_NULL_RETURN(theme, FocusPattern());
        auto focusColor = theme->GetGridItemFocusColor();
        FocusPaintParam focusPaintParam;
        focusPaintParam.SetPaintColor(focusColor);
        return { FocusType::SCOPE, true, FocusStyleType::CUSTOM_REGION, focusPaintParam };
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        Pattern::ToJsonValue(json, filter);
        if (filter.IsFastFilter()) {
            json->PutFixedAttr("selectable", selectable_ ? "true" : "false", filter, FIXED_ATTR_SELECTABLE);
            return;
        }
        json->PutExtAttr("style", gridItemStyle_ == GridItemStyle::NONE ? "NONE" : "PLAIN", filter);
        json->PutExtAttr("forceRebuild", forceRebuild_ ? "true" : "false", filter);
        json->PutFixedAttr("selectable", selectable_ ? "true" : "false", filter, FIXED_ATTR_SELECTABLE);
        json->PutExtAttr("selected", isSelected_ ? "true" : "false", filter);
    }

    void MarkIsSelected(bool isSelected);

    bool IsSelected() const
    {
        return isSelected_;
    }

    void SetSelected(bool selected)
    {
        isSelected_ = selected;
    }

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
    bool isSelected_ = false;

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
