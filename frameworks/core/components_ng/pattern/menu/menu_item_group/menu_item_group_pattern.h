/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_GROUP_MENU_ITEM_GROUP_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_GROUP_MENU_ITEM_GROUP_PATTERN_H

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_accessibility_property.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_layout_algorithm.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_paint_method.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_paint_property.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_view.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT MenuItemGroupPattern : public Pattern {
    DECLARE_ACE_TYPE(MenuItemGroupPattern, Pattern);

public:
    explicit MenuItemGroupPattern() = default;
    ~MenuItemGroupPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<MenuItemGroupAccessibilityProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<MenuItemGroupLayoutAlgorithm>(headerIndex_, footerIndex_, itemStartIndex_);
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return MakeRefPtr<MenuItemGroupPaintMethod>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<MenuItemGroupPaintProperty>();
    }

    void AddHeader(const RefPtr<NG::UINode>& header);
    void AddFooter(const RefPtr<NG::UINode>& footer);

    void AddHeaderContent(const RefPtr<NG::FrameNode>& headerContent)
    {
        headerContent_ = headerContent;
    }

    void AddFooterContent(const RefPtr<NG::FrameNode>& footerContent)
    {
        footerContent_ = footerContent;
    }

    RefPtr<FrameNode> GetMenu();

    std::u16string GetHeaderContent();

    bool HasSelectIcon() const
    {
        return hasSelectIcon_;
    }

    bool HasStartIcon() const
    {
        return hasStartIcon_;
    }

    // Travel children to update items icon info
    void UpdateMenuItemIconInfo();
    void OnExtItemPressed(bool press, bool beforeGroup);
    void OnIntItemPressed(int32_t index, bool press);
    void ModifyDivider();

protected:
    void OnMountToParentDone() override;

private:
    void ModifyFontSize();

    int32_t headerIndex_ = -1;
    int32_t footerIndex_ = -1;
    int32_t itemStartIndex_ = 0;

    // True: one of menu items in group has select icon;
    // False: none of menu items in group has select icon.
    bool hasSelectIcon_ = false;
    // True: one of menu items in group has start icon;
    // False: none of menu items in group has start icon.
    bool hasStartIcon_ = false;

    RefPtr<FrameNode> headerContent_;
    RefPtr<FrameNode> footerContent_;

    ACE_DISALLOW_COPY_AND_MOVE(MenuItemGroupPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_GROUP_MENU_ITEM_GROUP_PATTERN_H
