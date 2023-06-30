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

#include "core/components_ng/pattern/grid/grid_item_accessibility_property.h"
#include "core/components_ng/pattern/grid/grid_item_event_hub.h"
#include "core/components_ng/pattern/grid/grid_item_layout_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/syntax/shallow_builder.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT GridItemPattern : public Pattern {
    DECLARE_ACE_TYPE(GridItemPattern, Pattern);

public:
    explicit GridItemPattern(const RefPtr<ShallowBuilder>& shallowBuilder) : shallowBuilder_(shallowBuilder) {}
    ~GridItemPattern() override = default;

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
        auto layoutProperty = dirty->GetLayoutProperty();
        CHECK_NULL_RETURN(layoutProperty, false);
        auto gridItemLayoutProperty = AceType::DynamicCast<GridItemLayoutProperty>(layoutProperty);
        CHECK_NULL_RETURN(gridItemLayoutProperty, false);
        mainIndex_ = gridItemLayoutProperty->GetMainIndex().value_or(-1);
        crossIndex_ = gridItemLayoutProperty->GetCrossIndex().value_or(-1);
        return false;
    }

    int32_t GetMainIndex() const
    {
        return mainIndex_;
    }
    int32_t GetCrossIndex() const
    {
        return crossIndex_;
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
        return { FocusType::SCOPE, true, FocusStyleType::INNER_BORDER };
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        Pattern::ToJsonValue(json);
        json->Put("forceRebuild", forceRebuild_ ? "true" : "false");
        json->Put("selectable", selectable_ ? "true" : "false");
    }

    void MarkIsSelected(bool isSelected);

    bool IsSelected() const
    {
        return isSelected_;
    }

protected:
    void OnModifyDone() override;
private:
    void SetAccessibilityAction();
    RefPtr<ShallowBuilder> shallowBuilder_;
    bool forceRebuild_ = false;
    bool selectable_ = true;
    bool isSelected_ = false;
    int32_t mainIndex_ = -1;
    int32_t crossIndex_ = -1;

    ACE_DISALLOW_COPY_AND_MOVE(GridItemPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_ITEM_PATTERN_H
