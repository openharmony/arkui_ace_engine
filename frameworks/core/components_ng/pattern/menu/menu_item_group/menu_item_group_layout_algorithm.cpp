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

#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_layout_algorithm.h"

#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/multi_menu_layout_algorithm.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
void RecordItemsAndGroups(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<MenuItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    auto menu = pattern->GetMenu();
    CHECK_NULL_VOID(menu);
    auto menuPattern = menu->GetPattern<InnerMenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->RecordItemsAndGroups();
}

void MenuItemGroupLayoutAlgorithm::MeasureChildren(
    LayoutWrapper* layoutWrapper, float& maxChildrenWidth, SizeF& menuItemGroupSize)
{
    const auto& props = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(props);
    auto layoutConstraint = props->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);

    auto childConstraint = props->CreateChildConstraint();
    childConstraint.minSize = layoutConstraint->minSize;

    if (layoutConstraint->selfIdealSize.Width().has_value()) {
        childConstraint.selfIdealSize.SetWidth(layoutConstraint->selfIdealSize.Width().value());
    }
    UpdateHeaderAndFooterMargin(layoutWrapper);

    // measure children (header, footer, menuItem)
    maxChildrenWidth = GetChildrenMaxWidth(layoutWrapper->GetAllChildrenWithBuild(), childConstraint);
    menuItemGroupSize.SetWidth(maxChildrenWidth);
}

void MenuItemGroupLayoutAlgorithm::MeasureHeader(
    LayoutWrapper* layoutWrapper, const RefPtr<FrameNode>& host, float& totalHeight)
{
    CHECK_NULL_VOID(host);
    needHeaderPadding_ = NeedHeaderPadding(host);
    auto paintProperty = host->GetPaintProperty<MenuItemGroupPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateNeedHeaderPadding(needHeaderPadding_);
    float headerPadding = needHeaderPadding_ ? groupDividerPadding_ : 0.0f;
    totalHeight += headerPadding;
    if (headerIndex_ >= 0) {
        auto headerWrapper = layoutWrapper->GetOrCreateChildByIndex(headerIndex_);
        auto headerHeight = headerWrapper->GetGeometryNode()->GetMarginFrameSize().Height();
        totalHeight += (minItemHeight_ > headerHeight) ? minItemHeight_ : headerHeight;
    }
}

void MenuItemGroupLayoutAlgorithm::MeasureMenuItems(
    LayoutWrapper* layoutWrapper, float maxChildrenWidth, float& totalHeight)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto totalItemCount = layoutWrapper->GetTotalChildCount();
    int32_t currentIndex = itemStartIndex_;
    while (currentIndex < totalItemCount) {
        auto item = layoutWrapper->GetOrCreateChildByIndex(currentIndex);
        if (!item) {
            TAG_LOGW(AceLogTag::ACE_MENU, "currentIndex:%{public}d item is null in MenuItemGroup", currentIndex);
            ++currentIndex;
            continue;
        }
        auto childSize = item->GetGeometryNode()->GetMarginFrameSize();
        // set minimum size
        childSize.SetWidth(maxChildrenWidth);
        auto margin = item->GetLayoutProperty()->CreateMargin();
        MinusPaddingToSize(margin, childSize);
        if (item->GetLayoutProperty()->GetLayoutConstraint().has_value() &&
            !item->GetLayoutProperty()->GetLayoutConstraint()->selfIdealSize.Width().has_value()) {
            item->GetGeometryNode()->SetFrameSize(childSize);
        }

        float itemHeight;
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            itemHeight = childSize.Height() + margin.Height();
        } else {
            itemHeight = childSize.Height();
        }
        float endPos = totalHeight + itemHeight;
        itemPosition_[currentIndex] = { totalHeight, endPos };
        totalHeight = endPos;
        ++currentIndex;
    }

    if (footerIndex_ >= 0) {
        auto footerWrapper = layoutWrapper->GetOrCreateChildByIndex(footerIndex_);
        auto footerHeight = footerWrapper->GetGeometryNode()->GetMarginFrameSize().Height();
        totalHeight += (minItemHeight_ > footerHeight) ? minItemHeight_ : footerHeight;
    }
}

void MenuItemGroupLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    RecordItemsAndGroups(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    SizeF menuItemGroupSize;
    float maxChildrenWidth = 0.0f;
    MeasureChildren(layoutWrapper, maxChildrenWidth, menuItemGroupSize);
    minItemHeight_ = static_cast<float>(theme->GetOptionMinHeight().ConvertToPx());
    float totalHeight = 0.0f;
    MeasureHeader(layoutWrapper, host, totalHeight);
    MeasureMenuItems(layoutWrapper, maxChildrenWidth, totalHeight);

    // set menu size
    needFooterPadding_ = NeedFooterPadding(host);
    auto paintProperty = host->GetPaintProperty<MenuItemGroupPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateNeedFooterPadding(needFooterPadding_);
    float footerPadding = needFooterPadding_ ? groupDividerPadding_ : 0.0f;
    totalHeight += footerPadding;
    menuItemGroupSize.SetHeight(totalHeight);
    if (menuItemGroupSize != layoutWrapper->GetGeometryNode()->GetFrameSize()) {
        layoutWrapper->GetGeometryNode()->SetFrameSize(menuItemGroupSize);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void MenuItemGroupLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (headerIndex_ >= 0) {
        LayoutHeader(layoutWrapper);
    }
    if (footerIndex_ >= 0) {
        LayoutFooter(layoutWrapper);
    }
    LayoutMenuItem(layoutWrapper);
}

void MenuItemGroupLayoutAlgorithm::LayoutMenuItem(LayoutWrapper* layoutWrapper)
{
    // layout items.
    for (auto& pos : itemPosition_) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(pos.first);
        if (!wrapper) {
            TAG_LOGW(AceLogTag::ACE_MENU, "wrapper is out of boundary");
            continue;
        }
        LayoutIndex(wrapper, OffsetF(0.0, pos.second.first));
    }
}

void MenuItemGroupLayoutAlgorithm::LayoutHeader(LayoutWrapper* layoutWrapper)
{
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(headerIndex_);
    CHECK_NULL_VOID(wrapper);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto headerHeight = wrapper->GetGeometryNode()->GetFrameSize().Height();
    auto minItemHeight = static_cast<float>(theme->GetOptionMinHeight().ConvertToPx());
    float headerPadding = (needHeaderPadding_ ? groupDividerPadding_ : 0.0f) +
                          (headerHeight < minItemHeight ? (minItemHeight - headerHeight) / 2 : 0.0f);
    LayoutIndex(wrapper, OffsetF(0.0f, headerPadding));
}

void MenuItemGroupLayoutAlgorithm::LayoutFooter(LayoutWrapper* layoutWrapper)
{
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(footerIndex_);
    CHECK_NULL_VOID(wrapper);
    auto footerMainSize = wrapper->GetGeometryNode()->GetFrameSize();
    auto footerHeight = footerMainSize.Height();

    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto groupHeight = size.Height();

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);

    auto minItemHeight = static_cast<float>(theme->GetOptionMinHeight().ConvertToPx());
    float footerPadding = (needFooterPadding_ ? groupDividerPadding_ : 0.0f) +
                          (footerHeight < minItemHeight ? (minItemHeight - footerHeight) / 2 : 0.0f);
    LayoutIndex(wrapper, OffsetF(0.0f, (groupHeight - footerHeight - footerPadding)));
}

void MenuItemGroupLayoutAlgorithm::LayoutIndex(const RefPtr<LayoutWrapper>& wrapper, const OffsetF& offset)
{
    CHECK_NULL_VOID(wrapper);
    wrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
    wrapper->Layout();
}

// Need head padding if left brother is menu item group
bool MenuItemGroupLayoutAlgorithm::NeedHeaderPadding(const RefPtr<FrameNode>& host)
{
    auto brotherNode = GetBrotherNode(host);
    CHECK_NULL_RETURN(brotherNode, false);
    return brotherNode->GetTag() != V2::MENU_ITEM_GROUP_ETS_TAG;
}

bool MenuItemGroupLayoutAlgorithm::NeedFooterPadding(const RefPtr<FrameNode>& host)
{
    return !IsLastNode(host);
}

float MenuItemGroupLayoutAlgorithm::GetChildrenMaxWidth(
    const std::list<RefPtr<LayoutWrapper>>& children, const LayoutConstraintF& layoutConstraint)
{
    float width = layoutConstraint.minSize.Width();

    for (const auto& child : children) {
        child->Measure(MultiMenuLayoutAlgorithm::ResetLayoutConstraintMinWidth(child, layoutConstraint));
        auto childSize = child->GetGeometryNode()->GetMarginFrameSize();
        width = std::max(width, childSize.Width());
    }
    return width;
}

std::list<WeakPtr<UINode>> MenuItemGroupLayoutAlgorithm::GetItemsAndGroups(const RefPtr<FrameNode>& host) const
{
    std::list<WeakPtr<UINode>> itemsAndGroups;
    auto pattern = host->GetPattern<MenuItemGroupPattern>();
    CHECK_NULL_RETURN(pattern, itemsAndGroups);
    auto menu = pattern->GetMenu();
    CHECK_NULL_RETURN(menu, itemsAndGroups);
    auto menuPattern = menu->GetPattern<InnerMenuPattern>();
    CHECK_NULL_RETURN(menuPattern, itemsAndGroups);
    return menuPattern->GetItemsAndGroups();
}

// get the left brother node
RefPtr<FrameNode> MenuItemGroupLayoutAlgorithm::GetBrotherNode(const RefPtr<FrameNode>& host)
{
    auto itemsAndGroups = GetItemsAndGroups(host);
    if (itemsAndGroups.empty()) {
        return nullptr;
    }
    auto iter = std::find(itemsAndGroups.begin(), itemsAndGroups.end(), host);
    if (iter == itemsAndGroups.begin() || iter == itemsAndGroups.end()) {
        return nullptr;
    }
    return DynamicCast<FrameNode>((--iter)->Upgrade());
}

bool MenuItemGroupLayoutAlgorithm::IsLastNode(const RefPtr<FrameNode>& host) const
{
    auto itemsAndGroups = GetItemsAndGroups(host);
    if (itemsAndGroups.empty()) {
        return true;
    }
    return host == itemsAndGroups.back().Upgrade();
}

void MenuItemGroupLayoutAlgorithm::UpdateHeaderAndFooterMargin(LayoutWrapper* layoutWrapper) const
{
    if (headerIndex_ < 0 && footerIndex_ < 0) {
        // no header and footer, no need to update.
        return;
    }
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<MenuItemGroupPattern>();
    pattern->UpdateMenuItemIconInfo();

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto iconWidth = selectTheme->GetIconSideLength();
    auto iconContentPadding = selectTheme->GetIconContentPadding();
    auto margin = MarginProperty();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        if (pattern->HasSelectIcon()) {
            margin.left = CalcLength(iconWidth + iconContentPadding);
        } else {
            // no need to update zero margin.
            return;
        }
    } else {
        if (pattern->HasSelectIcon() && pattern->HasStartIcon()) {
            margin.left = CalcLength(iconWidth * 2.0 + iconContentPadding * 2.0);
        } else if (pattern->HasSelectIcon() || pattern->HasStartIcon()) {
            margin.left = CalcLength(iconWidth + iconContentPadding);
        } else {
            // no need to update zero margin.
            return;
        }
    }
    auto layoutDirection = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();
    if (layoutDirection == TextDirection::RTL) {
        auto temp = margin.right;
        margin.right = margin.left;
        margin.left = margin.right;
    }

    if (headerIndex_ >= 0) {
        auto headerWrapper = layoutWrapper->GetOrCreateChildByIndex(headerIndex_);
        auto headLayoutProps = headerWrapper->GetLayoutProperty();
        headLayoutProps->UpdateMargin(margin);
    }
    if (footerIndex_ >= 0) {
        auto footerWrapper = layoutWrapper->GetOrCreateChildByIndex(footerIndex_);
        auto footerLayoutProps = footerWrapper->GetLayoutProperty();
        footerLayoutProps->UpdateMargin(margin);
    }
}
} // namespace OHOS::Ace::NG
