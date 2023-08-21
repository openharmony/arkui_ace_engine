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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_ITEM_GROUP_MENU_ITEM_GROUP_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_ITEM_GROUP_MENU_ITEM_GROUP_LAYOUT_ALGORITHM_H

#include <map>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/box_layout_algorithm.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT MenuItemGroupLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(MenuItemGroupLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    using ItemPositionMap = std::map<int32_t, std::pair<float, float>>;

    MenuItemGroupLayoutAlgorithm(int32_t headerIndex, int32_t footerIndex, int32_t itemStartIndex)
        : headerIndex_(headerIndex), footerIndex_(footerIndex), itemStartIndex_(itemStartIndex)
    {}
    ~MenuItemGroupLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    bool NeedHeaderPadding(const RefPtr<FrameNode>& host);
    bool NeedFooterPadding(const RefPtr<FrameNode>& host);

    void LayoutHeader(LayoutWrapper* layoutWrapper);
    void LayoutFooter(LayoutWrapper* layoutWrapper);
    void LayoutIndex(const RefPtr<LayoutWrapper>& wrapper, const OffsetF& offset);
    void LayoutMenuItem(LayoutWrapper* layoutWrapper);

    float GetChildrenMaxWidth(
        const std::list<RefPtr<LayoutWrapper>>& children, const LayoutConstraintF& layoutConstraint);
    std::list<WeakPtr<UINode>> GetItemsAndGroups(const RefPtr<FrameNode>& host) const;
    RefPtr<FrameNode> GetBrotherNode(const RefPtr<FrameNode>& host);
    bool IsLastNode(const RefPtr<FrameNode>& host) const;

    void UpdateHeaderAndFooterMargin(LayoutWrapper* layoutWrapper) const;

    int32_t headerIndex_ = -1;
    int32_t footerIndex_ = -1;
    int32_t itemStartIndex_ = 0;

    bool needHeaderPadding_ = false;
    bool needFooterPadding_ = false;

    float groupDividerPadding_ = 0.0f;

    ItemPositionMap itemPosition_;

    ACE_DISALLOW_COPY_AND_MOVE(MenuItemGroupLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_ITEM_GROUP_MENU_ITEM_GROUP_LAYOUT_ALGORITHM_H
