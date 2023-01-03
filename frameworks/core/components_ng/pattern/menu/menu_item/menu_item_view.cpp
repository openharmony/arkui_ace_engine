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

#include "core/components_ng/pattern/menu/menu_item/menu_item_view.h"

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_paint_property.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/option/option_theme.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> MenuItemView::CreateItemRow(const RefPtr<FrameNode>& menuItem)
{
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(row, nullptr);
    auto rowLayoutProps = row->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(rowLayoutProps, nullptr);
    rowLayoutProps->UpdateCrossAxisAlign(FlexAlign::CENTER);
    rowLayoutProps->UpdateFlexGrow(1);
    rowLayoutProps->UpdateMainAxisAlign(FlexAlign::SPACE_BETWEEN);
    rowLayoutProps->UpdateSpace(MENU_ITEM_ICON_PADDING);
    row->MountToParent(menuItem);
    return row;
}

void MenuItemView::AddIcon(const std::optional<std::string>& icon, const RefPtr<FrameNode>& row)
{
    auto iconPath = icon.value_or("");
    if (!iconPath.empty()) {
        auto iconNode = FrameNode::CreateFrameNode(
            V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
        auto props = iconNode->GetLayoutProperty<ImageLayoutProperty>();
        props->UpdateImageSourceInfo(ImageSourceInfo(iconPath));
        props->UpdateImageFit(ImageFit::SCALE_DOWN);
        props->UpdateCalcMaxSize(CalcSize(ICON_SIDE_LENGTH, ICON_SIDE_LENGTH));
        props->UpdateAlignment(Alignment::CENTER);

        iconNode->MountToParent(row);
        iconNode->MarkModifyDone();
    }
}

void MenuItemView::AddContent(const std::string& content, const RefPtr<FrameNode>& row)
{
    auto contentNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_VOID(contentNode);
    auto contentProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(contentProperty);
    contentProperty->UpdateFontSize(MENU_FONT_SIZE);
    contentProperty->UpdateContent(content);
    contentProperty->UpdateFlexGrow(1);
    contentNode->MountToParent(row);
    contentNode->MarkModifyDone();
}

void MenuItemView::AddLabelInfo(std::optional<std::string> labelInfo, const RefPtr<FrameNode>& row)
{
    auto labelStr = labelInfo.value_or("");
    if (!labelStr.empty()) {
        auto labelNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_VOID(labelNode);
        auto labelProperty = labelNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(labelProperty);
        labelProperty->UpdateFontSize(MENU_FONT_SIZE);
        labelProperty->UpdateContent(labelStr);
        labelNode->MountToParent(row);
        labelNode->MarkModifyDone();
    }
}

void MenuItemView::Create(const RefPtr<UINode>& customNode) {}

void MenuItemView::Create(const MenuItemProperties& menuItemProps)
{
    LOGI("MenuItemView::Create");
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    auto menuItem = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    CHECK_NULL_VOID(menuItem);
    stack->Push(menuItem);

    // set border radius
    auto renderContext = menuItem->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    BorderRadiusProperty border;
    border.SetRadius(ROUND_RADIUS_PHONE);
    renderContext->UpdateBorderRadius(border);

    auto paintProps = menuItem->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(paintProps);
    paintProps->UpdateHover(false);
    paintProps->UpdatePress(false);

    auto row = CreateItemRow(menuItem);

    auto leftRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_VOID(leftRow);
    auto leftRowLayoutProps = row->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(leftRowLayoutProps);
    leftRowLayoutProps->UpdateSpace(MENU_ITEM_ICON_PADDING);
    leftRow->MountToParent(row);

    AddIcon(menuItemProps.startIcon, leftRow);
    AddContent(menuItemProps.content, leftRow);
    auto rightRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_VOID(rightRow);
    auto rightRowLayoutProps = row->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(rightRowLayoutProps);
    rightRowLayoutProps->UpdateSpace(MENU_ITEM_ICON_PADDING);
    rightRow->MountToParent(row);

    AddLabelInfo(menuItemProps.labelInfo, rightRow);
    AddIcon(menuItemProps.endIcon, rightRow);

    auto buildFunc = menuItemProps.buildFunc;
    if (buildFunc.has_value()) {
        auto pattern = menuItem->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetSubBuilder(std::move(buildFunc.value_or(nullptr)));
    }
}

void MenuItemView::SetSelectIcon(bool isShow)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<MenuItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectIcon(isShow);
}

void MenuItemView::SetOnChange(std::function<void(bool)>&& onChange)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}
} // namespace OHOS::Ace::NG
