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

#include "base/utils/utils.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_paint_property.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
void MenuItemGroupLayoutAlgorithm::Measure(FrameNode* frameNode)
{

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    groupDividerPadding_ = theme->GetDividerPaddingVertical() * 2 + theme->GetDefaultDividerWidth();

    const auto& props = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(props);
    auto layoutConstraint = props->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);

    auto childConstraint = props->CreateChildConstraint();
    childConstraint.minSize = layoutConstraint->minSize;

    if (layoutConstraint->selfIdealSize.Width().has_value()) {
        childConstraint.selfIdealSize.SetWidth(layoutConstraint->selfIdealSize.Width().value());
    }

    // measure children (header, footer, menuItem)
    float maxChildrenWidth = GetChildrenMaxWidth(frameNode->GetAllFrameNodeChildren(), childConstraint);
    SizeF menuItemGroupSize;
    menuItemGroupSize.SetWidth(maxChildrenWidth);
    float totalHeight = 0.0f;

    auto minItemHeight = static_cast<float>(theme->GetOptionMinHeight().ConvertToPx());

    // measure header
    needHeaderPadding_ = NeedHeaderPadding(Claim(frameNode));
    auto paintProperty = frameNode->GetPaintProperty<MenuItemGroupPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateNeedHeaderPadding(needHeaderPadding_);
    float headerPadding = needHeaderPadding_ ? static_cast<float>(groupDividerPadding_.ConvertToPx()) : 0.0f;
    totalHeight += headerPadding;
    if (headerIndex_ >= 0) {
        auto headerWrapper = frameNode->GetFrameNodeByIndex(headerIndex_);
        auto headerHeight = frameNode->GetGeometryNode()->GetFrameSize().Height();
        totalHeight += (minItemHeight > headerHeight) ? minItemHeight : headerHeight;
    }
    // measure menu item
    auto totalItemCount = frameNode->TotalChildCount();
    int32_t currentIndex = itemStartIndex_;
    while (currentIndex < totalItemCount) {
        auto item = frameNode->GetFrameNodeByIndex(currentIndex);
        auto childSize = item->GetGeometryNode()->GetFrameSize();
        // set minimum size
        childSize.SetWidth(maxChildrenWidth);
        item->GetGeometryNode()->SetFrameSize(childSize);

        float itemHeight = childSize.Height();
        float endPos = totalHeight + itemHeight;
        itemPosition_[currentIndex] = { totalHeight, endPos };
        totalHeight = endPos;
        ++currentIndex;
    }

    if (footerIndex_ >= 0) {
        auto footer = frameNode->GetFrameNodeByIndex(footerIndex_);
        auto footerHeight = footer->GetGeometryNode()->GetFrameSize().Height();
        totalHeight += (minItemHeight > footerHeight) ? minItemHeight : footerHeight;
    }
    // set menu size
    needFooterPadding_ = NeedFooterPadding(Claim(frameNode));
    paintProperty->UpdateNeedFooterPadding(needFooterPadding_);
    float footerPadding = needFooterPadding_ ? static_cast<float>(groupDividerPadding_.ConvertToPx()) : 0.0f;
    totalHeight += footerPadding;
    menuItemGroupSize.SetHeight(totalHeight);

    LOGD("finish measure, menuItemGroup size = %{public}f x %{public}f", menuItemGroupSize.Width(),
        menuItemGroupSize.Height());
    frameNode->GetGeometryNode()->SetFrameSize(menuItemGroupSize);
}

void MenuItemGroupLayoutAlgorithm::Layout(FrameNode* frameNode)
{
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (headerIndex_ >= 0) {
        LayoutHeader(frameNode);
    }
    if (footerIndex_ >= 0) {
        LayoutFooter(frameNode);
    }
    LayoutMenuItem(frameNode);
}

void MenuItemGroupLayoutAlgorithm::LayoutMenuItem(FrameNode* frameNode)
{
    // layout items.
    for (auto& pos : itemPosition_) {
        auto child = frameNode->GetFrameNodeByIndex(pos.first);
        if (!child) {
            LOGI("wrapper is out of boundary");
            continue;
        }
        LayoutIndex(child, OffsetF(0.0, pos.second.first));
    }
}

void MenuItemGroupLayoutAlgorithm::LayoutHeader(FrameNode* frameNode)
{
    auto child = frameNode->GetFrameNodeByIndex(headerIndex_);
    CHECK_NULL_VOID(child);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto headerHeight = child->GetGeometryNode()->GetFrameSize().Height();
    auto minItemHeight = static_cast<float>(theme->GetOptionMinHeight().ConvertToPx());
    float headerPadding = (needHeaderPadding_ ? static_cast<float>(groupDividerPadding_.ConvertToPx()) : 0.0f) +
                          (headerHeight < minItemHeight ? (minItemHeight - headerHeight) / 2 : 0.0f);
    LayoutIndex(child, OffsetF(static_cast<float>(theme->GetMenuIconPadding().ConvertToPx()), headerPadding));
}

void MenuItemGroupLayoutAlgorithm::LayoutFooter(FrameNode* frameNode)
{
    auto child = frameNode->GetFrameNodeByIndex(footerIndex_);
    CHECK_NULL_VOID(child);
    auto footerMainSize = child->GetGeometryNode()->GetFrameSize();
    auto footerHeight = footerMainSize.Height();

    auto size = frameNode->GetGeometryNode()->GetFrameSize();
    auto groupHeight = size.Height();

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);

    auto minItemHeight = static_cast<float>(theme->GetOptionMinHeight().ConvertToPx());
    float footerPadding = (needFooterPadding_ ? static_cast<float>(groupDividerPadding_.ConvertToPx()) : 0.0f) +
                          (footerHeight < minItemHeight ? (minItemHeight - footerHeight) / 2 : 0.0f);
    LayoutIndex(child, OffsetF(static_cast<float>(theme->GetMenuIconPadding().ConvertToPx()),
                             (groupHeight - footerHeight - footerPadding)));
}

void MenuItemGroupLayoutAlgorithm::LayoutIndex(const RefPtr<FrameNode>& frameNode, const OffsetF& offset)
{
    CHECK_NULL_VOID_NOLOG(frameNode);
    frameNode->GetGeometryNode()->SetMarginFrameOffset(offset);
    frameNode->Layout();
}

bool MenuItemGroupLayoutAlgorithm::NeedHeaderPadding(const RefPtr<FrameNode>& host)
{
    int32_t hostId = host->GetId();
    auto menu = AceType::DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_RETURN(menu, false);
    int32_t index = menu->GetChildIndexById(hostId);
    if (index == 0) {
        return false;
    }
    auto brotherNode = AceType::DynamicCast<FrameNode>(menu->GetChildAtIndex(index - 1));
    CHECK_NULL_RETURN_NOLOG(brotherNode, false);
    return brotherNode->GetTag() != V2::MENU_ITEM_GROUP_ETS_TAG;
}

bool MenuItemGroupLayoutAlgorithm::NeedFooterPadding(const RefPtr<FrameNode>& host)
{
    int32_t hostId = host->GetId();
    auto menu = AceType::DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_RETURN(menu, false);
    int32_t index = menu->GetChildIndexById(hostId);
    int32_t menuCount = menu->TotalChildCount();
    return index != (menuCount - 1);
}

float MenuItemGroupLayoutAlgorithm::GetChildrenMaxWidth(
    const std::list<RefPtr<FrameNode>>& children, const LayoutConstraintF& layoutConstraint)
{
    float width = layoutConstraint.minSize.Width();

    for (const auto& child : children) {
        child->Measure(layoutConstraint);
        auto childSize = child->GetGeometryNode()->GetFrameSize();
        width = std::max(width, childSize.Width());
    }
    return width;
}
} // namespace OHOS::Ace::NG
