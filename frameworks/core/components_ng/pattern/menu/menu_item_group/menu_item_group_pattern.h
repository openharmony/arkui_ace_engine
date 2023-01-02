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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_GROUP_MENU_ITEM_GROUP_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_GROUP_MENU_ITEM_GROUP_PATTERN_H

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "base/utils/utils.h"
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

    void AddHeader(const RefPtr<NG::UINode>& header)
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        if (headerIndex_ < 0) {
            headerIndex_ = itemStartIndex_;
            host->AddChild(header);
            itemStartIndex_++;
        } else {
            host->ReplaceChild(host->GetChildAtIndex(headerIndex_), header);
        }
        auto frameNode = AceType::DynamicCast<FrameNode>(header);
        CHECK_NULL_VOID(frameNode);
    }

    void AddFooter(const RefPtr<NG::UINode>& footer)
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        if (footerIndex_ < 0) {
            footerIndex_ = itemStartIndex_;
            host->AddChild(footer);
            itemStartIndex_++;
        } else {
            host->ReplaceChild(host->GetChildAtIndex(footerIndex_), footer);
        }
        auto frameNode = AceType::DynamicCast<FrameNode>(footer);
        CHECK_NULL_VOID(frameNode);
    }

private:
    int32_t headerIndex_ = -1;
    int32_t footerIndex_ = -1;
    int32_t itemStartIndex_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(MenuItemGroupPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_GROUP_MENU_ITEM_GROUP_PATTERN_H
