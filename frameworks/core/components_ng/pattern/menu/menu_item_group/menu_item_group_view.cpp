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

#include "core/common/resource/resource_parse_utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/menu/menu_tag_constants.h"

namespace OHOS::Ace::NG {
namespace {
void UpdateRowPadding(const RefPtr<FrameNode>& row)
{
    CHECK_NULL_VOID(row);
    auto pipeline = row->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto padding = CalcLength(theme->GetMenuItemHorIntervalPadding());

    auto layoutProps = row->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProps);
    layoutProps->UpdatePadding(
        PaddingProperty { padding, padding, std::nullopt, std::nullopt, std::nullopt, std::nullopt });
}
} // namespace

RefPtr<FrameNode> MenuItemGroupView::CreateFrameNode(int32_t nodeId)
{
    const std::function<RefPtr<Pattern>(void)>& patternCreator = []() {
        return AceType::MakeRefPtr<MenuItemGroupPattern>();
    };
    return FrameNode::GetOrCreateFrameNode(MENU_ITEM_GROUP_ETS_TAG, nodeId, patternCreator);
}

void MenuItemGroupView::CreateWithStringResourceObj(
    const RefPtr<ResourceObject>& resObj, const MenuItemGroupStringType type)
{
    CHECK_NULL_VOID(resObj);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithStringResourceObj(frameNode, resObj, type);
}

void MenuItemGroupView::CreateWithStringResourceObj(
    FrameNode* frameNode, const RefPtr<ResourceObject>& resObj, const MenuItemGroupStringType type)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "MenuItemGroup" + StringTypeToString(type);
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [pattern, key, type](const RefPtr<ResourceObject>& resObj) {
        std::string str = pattern->GetResCacheMapByKey(key);
        if (str.empty()) {
            CHECK_NE_VOID(ResourceParseUtils::ParseResString(resObj, str), true);
            pattern->AddResCache(key, str);
        }
        if (type == MenuItemGroupStringType::HEADER) {
            pattern->SetHeaderContent(str);
        } else if (type == MenuItemGroupStringType::FOOTER) {
            pattern->SetFooterContent(str);
        }
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

const std::string MenuItemGroupView::StringTypeToString(const MenuItemGroupStringType type)
{
    std::string rst;
    switch (type) {
        case MenuItemGroupStringType::HEADER:
            rst = "Header";
            break;
        case MenuItemGroupStringType::FOOTER:
            rst = "Footer";
            break;
        default:
            rst = "Unknown";
            break;
    }
    return rst;
}

void MenuItemGroupView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", MENU_ITEM_GROUP_ETS_TAG, nodeId);
    auto menuItemGroup = FrameNode::GetOrCreateFrameNode(
        MENU_ITEM_GROUP_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<MenuItemGroupPattern>(); });
    CHECK_NULL_VOID(menuItemGroup);

    stack->Push(menuItemGroup);
}

void MenuItemGroupView::Create(const RefPtr<UINode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto* stack = ViewStackProcessor::GetInstance();
    stack->Push(frameNode);
}

void MenuItemGroupView::SetHeader(const RefPtr<UINode>& header)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetHeader(frameNode, header);
}

void MenuItemGroupView::SetHeader(FrameNode* frameNode, const RefPtr<UINode>& header)
{
    CHECK_NULL_VOID(header);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    auto row = FrameNode::CreateFrameNode(
        ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(false));
    UpdateRowPadding(row);
    header->MountToParent(row);
    pattern->AddHeader(row);
}

void MenuItemGroupView::SetHeader(const std::string& headerStr)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetHeader(frameNode, headerStr);
}

void MenuItemGroupView::SetHeader(FrameNode* frameNode, const std::string& headerStr)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    auto row = FrameNode::CreateFrameNode(
        ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto content = FrameNode::CreateFrameNode(
        TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_VOID(row && content);
    UpdateRowPadding(row);
    content->MountToParent(row);
    auto layoutProps = content->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(layoutProps);
    layoutProps->UpdateContent(headerStr);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        layoutProps->UpdateFontSize(theme->GetMenuItemGroupTitleTextFontSize());
        layoutProps->UpdateFontWeight(theme->GetMenuHeaderFontWeight());
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
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetFooter(frameNode, footer);
}

void MenuItemGroupView::SetFooter(FrameNode* frameNode, const RefPtr<UINode>& footer)
{
    CHECK_NULL_VOID(footer);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    auto row = FrameNode::CreateFrameNode(
        ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(false));
    UpdateRowPadding(row);
    footer->MountToParent(row);
    pattern->AddFooter(row);
}

void MenuItemGroupView::SetFooter(const std::string& footerStr)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetFooter(frameNode, footerStr);
}

void MenuItemGroupView::SetFooter(FrameNode* frameNode, const std::string& footerStr)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemGroupPattern>();
    CHECK_NULL_VOID(pattern);
    auto row = FrameNode::CreateFrameNode(
        ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto content = FrameNode::CreateFrameNode(
        TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_VOID(row && content);
    UpdateRowPadding(row);
    content->MountToParent(row);
    auto layoutProps = content->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(layoutProps);
    layoutProps->UpdateContent(footerStr);
    auto pipeline = frameNode->GetContext();
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

void MenuItemGroupView::CreateCJ()
{
    Create();
}

void MenuItemGroupView::SetHeaderCJ(const RefPtr<UINode>& header)
{
    SetHeader(header);
}

void MenuItemGroupView::SetHeaderCJ(const std::string& headerStr)
{
    SetHeader(headerStr);
}

void MenuItemGroupView::SetFooterCJ(const RefPtr<UINode>& footer)
{
    SetFooter(footer);
}

void MenuItemGroupView::SetFooterCJ(const std::string& footerStr)
{
    SetFooter(footerStr);
}
} // namespace OHOS::Ace::NG
