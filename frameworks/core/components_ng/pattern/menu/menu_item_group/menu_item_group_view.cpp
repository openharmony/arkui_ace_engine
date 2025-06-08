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

#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_view.h"

#include "core/components/select/select_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
namespace {
void UpdateRowPadding(const RefPtr<FrameNode>& row)
{
    CHECK_NULL_VOID(row);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto padding = CalcLength(theme->GetMenuItemHorIntervalPadding());

    auto layoutProps = row->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProps);
    layoutProps->UpdatePadding(PaddingProperty { padding, padding, std::nullopt, std::nullopt, std::nullopt,
        std::nullopt });
}
} // namespace

void MenuItemGroupView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::MENU_ITEM_GROUP_ETS_TAG, nodeId);
    auto menuItemGroup = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ITEM_GROUP_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<MenuItemGroupPattern>(); });
    CHECK_NULL_VOID(menuItemGroup);

    stack->Push(menuItemGroup);
}

RefPtr<FrameNode> MenuItemGroupView::CreateFrameNode(int32_t nodeId)
{
    const std::function<RefPtr<Pattern>(void)>& patternCreator =
        []() { return AceType::MakeRefPtr<MenuItemGroupPattern>(); };
    return FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, nodeId, patternCreator);
}

void MenuItemGroupView::SetHeader(const RefPtr<UINode>& header)
{
    CHECK_NULL_VOID(header);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    UpdateRowPadding(row);
    header->MountToParent(row);
    pattern->AddHeader(row);
}

void MenuItemGroupView::SetHeader(const std::string& headerStr)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto content = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_VOID(row && content);
    UpdateRowPadding(row);
    content->MountToParent(row);
    auto layoutProps = content->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(layoutProps);
    layoutProps->UpdateContent(headerStr);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        layoutProps->UpdateFontSize(theme->GetMenuItemGroupTitleTextFontSize());
        layoutProps->UpdateFontWeight(FontWeight::BOLD);
        layoutProps->UpdateTextColor(theme->GetMenuTextColor());
    } else {
        layoutProps->UpdateFontSize(theme->GetMenuFontSize());
        layoutProps->UpdateTextColor(theme->GetSecondaryFontColor());
    }
    layoutProps->UpdateMaxLines(1);
    layoutProps->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    pattern->AddHeaderContent(content);
    pattern->AddHeader(row);
}

void MenuItemGroupView::SetFooter(const RefPtr<UINode>& footer)
{
    CHECK_NULL_VOID(footer);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    UpdateRowPadding(row);
    footer->MountToParent(row);
    pattern->AddFooter(row);
}

void MenuItemGroupView::SetFooter(const std::string& footerStr)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto content = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_VOID(row && content);
    UpdateRowPadding(row);
    content->MountToParent(row);
    auto layoutProps = content->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(layoutProps);
    layoutProps->UpdateContent(footerStr);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    layoutProps->UpdateTextColor(theme->GetSecondaryFontColor());
    layoutProps->UpdateFontSize(theme->GetMenuFontSize());
    layoutProps->UpdateMaxLines(1);
    layoutProps->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    pattern->AddFooterContent(content);
    pattern->AddFooter(row);
}

void MenuItemGroupView::SetHeader(FrameNode* frameNode, const std::optional<std::string>& header)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto content = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_VOID(row && content);
    UpdateRowPadding(row);
    content->MountToParent(row);
    auto layoutProps = content->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(layoutProps);
    layoutProps->UpdateContent(header.value_or(" "));
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        layoutProps->UpdateFontSize(theme->GetMenuItemGroupTitleTextFontSize());
        layoutProps->UpdateFontWeight(FontWeight::BOLD);
        layoutProps->UpdateTextColor(theme->GetMenuTextColor());
    } else {
        layoutProps->UpdateFontSize(theme->GetMenuFontSize());
        layoutProps->UpdateTextColor(theme->GetSecondaryFontColor());
    }
    layoutProps->UpdateMaxLines(1);
    layoutProps->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    pattern->AddHeaderContent(content);
    pattern->AddHeader(row);
}

void MenuItemGroupView::SetFooter(FrameNode* frameNode, const std::optional<std::string>& footer)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto content = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_VOID(row && content);
    UpdateRowPadding(row);
    content->MountToParent(row);
    auto layoutProps = content->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(layoutProps);
    layoutProps->UpdateContent(footer.value_or(" "));
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    layoutProps->UpdateTextColor(theme->GetSecondaryFontColor());
    layoutProps->UpdateFontSize(theme->GetMenuFontSize());
    layoutProps->UpdateMaxLines(1);
    layoutProps->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    pattern->AddFooterContent(content);
    pattern->AddFooter(row);
}

void MenuItemGroupView::SetHeader(FrameNode* frameNode, std::function<RefPtr<UINode>()>&& builder)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    UpdateRowPadding(row);
    RefPtr<UINode> unitNode = builder();
    unitNode->MountToParent(row);
    pattern->AddHeader(row);
}

void MenuItemGroupView::SetFooter(FrameNode* frameNode, std::function<RefPtr<UINode>()>&& builder)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    UpdateRowPadding(row);
    RefPtr<UINode> unitNode = builder();
    unitNode->MountToParent(row);
    pattern->AddFooter(row);
}
} // namespace OHOS::Ace::NG
