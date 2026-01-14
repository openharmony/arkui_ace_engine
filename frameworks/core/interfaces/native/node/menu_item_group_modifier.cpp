/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_view.h"
#include "core/interfaces/native/node/menu_item_modifier.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::NG {
void SetMenuItemGroupHeaderNode(ArkUINodeHandle node, ArkUINodeHandle headerNode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (headerNode == nullptr) {
        return;
    }

    auto* headerUINode = reinterpret_cast<UINode*>(headerNode);
    RefPtr<UINode> header = AceType::Claim(headerUINode);
    MenuItemGroupView::SetHeader(frameNode, header);
}

void SetMenuItemGroupHeader(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemGroupView::SetHeader(frameNode, value);
}

void SetMenuItemGroupHeaderStrRes(ArkUINodeHandle node, ArkUI_CharPtr value, void* resRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemGroupView::SetHeader(frameNode, value);
    if (SystemProperties::ConfigChangePerform() && resRawPtr) {
        auto* resObj = reinterpret_cast<ResourceObject*>(resRawPtr);
        auto headerResObj = AceType::Claim(resObj);
        MenuItemGroupView::CreateWithStringResourceObj(frameNode, headerResObj, MenuItemGroupStringType::HEADER);
    }
}

void SetMenuItemGroupFooterNode(ArkUINodeHandle node, ArkUINodeHandle footerNode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (footerNode == nullptr) {
        return;
    }

    auto* footerUINode = reinterpret_cast<UINode*>(footerNode);
    RefPtr<UINode> footer = AceType::Claim(footerUINode);
    MenuItemGroupView::SetFooter(frameNode, footer);
}

void SetMenuItemGroupFooter(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemGroupView::SetFooter(frameNode, value);
}

void SetMenuItemGroupFooterStrRes(ArkUINodeHandle node, ArkUI_CharPtr value, void* resRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    MenuItemGroupView::SetFooter(frameNode, value);
    if (SystemProperties::ConfigChangePerform() && resRawPtr) {
        auto* resObj = reinterpret_cast<ResourceObject*>(resRawPtr);
        auto footerResObj = AceType::Claim(resObj);
        MenuItemGroupView::CreateWithStringResourceObj(frameNode, footerResObj, MenuItemGroupStringType::FOOTER);
    }
}

ArkUINodeHandle CreateMenuItemGroup()
{
    MenuItemGroupView::Create();
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    return reinterpret_cast<ArkUINodeHandle>(frameNode);
}

namespace NodeModifier {
const ArkUIMenuItemGroupModifier* GetMenuItemGroupModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (isCurrentUseNewPipeline) {
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIMenuItemGroupModifier modifier = {
            .setMenuItemGroupHeaderNode = SetMenuItemGroupHeaderNode,
            .setMenuItemGroupFooterNode = SetMenuItemGroupFooterNode,
            .setMenuItemGroupHeaderStrRes = SetMenuItemGroupHeaderStrRes,
            .setMenuItemGroupFooterStrRes = SetMenuItemGroupFooterStrRes,
            .createMenuItemGroup = CreateMenuItemGroup,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
    } else {
        return nullptr;
    }
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG