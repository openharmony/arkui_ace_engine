/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "ui/view/components/menu_view.h"

#include "core/components_ng/pattern/menu/menu_view.h"
#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "ui/view_stack/view_stack_processor.h"
#include "core/interfaces/native/node/menu_modifier.h"
#include "core/interfaces/native/node/menu_item_modifier.h"

#include "core/components_ng/pattern/menu/menu_model_ng.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "core/components_ng/pattern/menu/menu_view.h"

namespace OHOS::Ace::Kit {
namespace {
const std::pair<RefPtr<FrameNode>, RefPtr<FrameNode>> NULL_MENU_PAIR = { nullptr, nullptr };
} // namespace

RefPtr<FrameNode> MenuView::Create(std::vector<OptionParam>&& params, MenuType type, const MenuParam& menuParam)
{
    std::vector<NG::OptionParam> aceParams;
    for (const OptionParam& optionParam : params) {
        NG::OptionParam aceOptionParam;
        aceOptionParam.value = optionParam.value;
        aceOptionParam.icon = optionParam.icon;
        aceOptionParam.enabled = optionParam.enabled;
        aceOptionParam.action = optionParam.action;
        if (optionParam.symbol) {
            aceOptionParam.symbol = [symbol = optionParam.symbol](WeakPtr<NG::FrameNode> weakAceFrameNode) {
                RefPtr<NG::FrameNode> aceFrameNode = weakAceFrameNode.Upgrade();
                CHECK_NULL_VOID(aceFrameNode);
                symbol(reinterpret_cast<void*>(AceType::RawPtr(aceFrameNode)));
            };
        }
        aceOptionParam.symbolUserDefinedIdealFontSize = optionParam.symbolUserDefinedIdealFontSize;
        aceOptionParam.disableSystemClick = optionParam.disableSystemClick;
        aceOptionParam.isPasteOption = optionParam.isPasteOption;
        aceParams.push_back(aceOptionParam);
    }

    NG::MenuParam aceMenuParam;
    aceMenuParam.isShowInSubWindow = menuParam.isShowInSubWindow;
    aceMenuParam.placement = static_cast<Placement>(menuParam.placement);
    aceMenuParam.systemMaterial = menuParam.systemMaterial;
    const auto* menuViewModifier = NG::NodeModifier::GetMenuViewInnerModifier();
    CHECK_NULL_RETURN(menuViewModifier, nullptr);
    auto aceNode = menuViewModifier->createWithOptionParams(
        std::move(aceParams), menuParam.targetId, menuParam.targetTag, static_cast<NG::MenuType>(type), aceMenuParam);
    RefPtr<FrameNode> node = AceType::MakeRefPtr<FrameNodeImpl>(aceNode);
    return node;
}

std::pair<RefPtr<FrameNode>, RefPtr<FrameNode>> MenuView::NavigationCreateMenu(
    std::vector<OptionParam>&& params, const MenuParam& menuParam)
{
    const auto* menuModifier = NG::NodeModifier::GetMenuInnerModifier();
    CHECK_NULL_RETURN(menuModifier, NULL_MENU_PAIR);
    RefPtr<NG::FrameNode> menuAceNode = menuModifier->createMenu();
    CHECK_NULL_RETURN(menuAceNode, NULL_MENU_PAIR);
    RefPtr<FrameNode> menuNode = AceType::MakeRefPtr<FrameNodeImpl>(menuAceNode);
    CHECK_NULL_RETURN(menuNode, NULL_MENU_PAIR);
    menuAceNode->SetKitNode(menuNode);
    NG::MenuParam aceMenuParam;
    aceMenuParam.isShowInSubWindow = menuParam.isShowInSubWindow;
    aceMenuParam.placement = static_cast<Placement>(menuParam.placement);
    aceMenuParam.systemMaterial = menuParam.systemMaterial;
    const auto* menuViewModifier = NG::NodeModifier::GetMenuViewInnerModifier();
    CHECK_NULL_RETURN(menuViewModifier, NULL_MENU_PAIR);
    auto menuWrapperAceNode = menuViewModifier->createWithCustomNode(
        menuAceNode, menuParam.targetId, menuParam.targetTag, aceMenuParam, true, nullptr);
    CHECK_NULL_RETURN(menuWrapperAceNode, NULL_MENU_PAIR);
    RefPtr<FrameNode> menuWrapperNode = AceType::MakeRefPtr<FrameNodeImpl>(menuWrapperAceNode);
    CHECK_NULL_RETURN(menuWrapperNode, NULL_MENU_PAIR);
    menuWrapperAceNode->SetKitNode(menuWrapperNode);
    for (const OptionParam& optionParam : params) {
        NG::OptionParam aceOptionParam;
        aceOptionParam.value = optionParam.value;
        aceOptionParam.enabled = optionParam.enabled;
        aceOptionParam.action = optionParam.action;
        aceOptionParam.symbolUserDefinedIdealFontSize = optionParam.symbolUserDefinedIdealFontSize;
        aceOptionParam.disableSystemClick = optionParam.disableSystemClick;
        aceOptionParam.isPasteOption = optionParam.isPasteOption;
        const auto* menuItemModifier = NG::NodeModifier::GetMenuItemInnerModifier();
        CHECK_NULL_RETURN(menuItemModifier, NULL_MENU_PAIR);
        auto menuItemAceNode = menuItemModifier->createWithParam(std::move(aceOptionParam), aceMenuParam);
        if (menuItemAceNode) {
            menuAceNode->AddChild(menuItemAceNode);
        }
    }
    return { menuWrapperNode, menuNode };
}
} // OHOS::Ace::Kit