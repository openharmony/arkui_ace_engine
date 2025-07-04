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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_LIST_ARC_LIST_ITEM_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_LIST_ARC_LIST_ITEM_PATTERN_H

#include "core/components_ng/pattern/arc_list/arc_list_item_layout_property.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ArcListItemPattern : public ListItemPattern {
    DECLARE_ACE_TYPE(ArcListItemPattern, ListItemPattern);

public:
    ArcListItemPattern(const RefPtr<ShallowBuilder>& shallowBuilder) : ListItemPattern(shallowBuilder) {}
    ArcListItemPattern(const RefPtr<ShallowBuilder>& shallowBuilder, V2::ListItemStyle listItemStyle)
        : ListItemPattern(shallowBuilder, listItemStyle)
    {}
    ~ArcListItemPattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<ArcListItemLayoutProperty>();
    }

    FocusPattern GetFocusPattern() const override;

    void SetListItemDefaultAttributes(const RefPtr<FrameNode>& listItemNode) override;

    void HandleHoverEvent(bool isHover, const RefPtr<NG::FrameNode>& itemNode) override;
    void HandlePressEvent(bool isPressed, const RefPtr<NG::FrameNode>& itemNode) override;
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

private:
    Color GetBlendGgColor() override;
    void InitDisableEvent() override;
    void SetAccessibilityAction() override {}

    ACE_DISALLOW_COPY_AND_MOVE(ArcListItemPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_LIST_ARC_LIST_ITEM_PATTERN_H
