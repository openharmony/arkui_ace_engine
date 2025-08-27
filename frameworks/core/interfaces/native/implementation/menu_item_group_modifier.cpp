/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_view_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace MenuItemGroupModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = MenuItemGroupViewStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // MenuItemGroupModifier
namespace MenuItemGroupInterfaceModifier {
void SetMenuItemGroupOptionsImpl(Ark_NativePointer node,
                                 const Opt_MenuItemGroupOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto arkOptions = Converter::OptConvert<Ark_MenuItemGroupOptions>(*value);
    CHECK_NULL_VOID(arkOptions);
    Converter::VisitUnion(arkOptions.value().header,
        [frameNode, node](const Ark_ResourceStr& value) {
            auto valueString = Converter::OptConvert<std::string>(value);
            MenuItemGroupViewStatic::SetHeader(frameNode, valueString);
        },
        [frameNode, node](const CustomNodeBuilder& value) {
            CallbackHelper(value).BuildAsync([frameNode](const RefPtr<UINode>& uiNode) {
                auto builder = [uiNode]() -> RefPtr<UINode> {
                    return uiNode;
                };
                MenuItemGroupViewStatic::SetHeader(frameNode, std::move(builder));
                }, node);
        },
        []() {}
    );
    Converter::VisitUnion(arkOptions.value().footer,
        [frameNode, node](const Ark_ResourceStr& value) {
            auto valueString = Converter::OptConvert<std::string>(value);
            MenuItemGroupViewStatic::SetFooter(frameNode, valueString);
        },
        [frameNode, node](const CustomNodeBuilder& value) {
            CallbackHelper(value).BuildAsync([frameNode](const RefPtr<UINode>& uiNode) {
                auto builder = [uiNode]() -> RefPtr<UINode> {
                    return uiNode;
                };
                MenuItemGroupViewStatic::SetFooter(frameNode, std::move(builder));
                }, node);
        },
        []() {}
    );
}
} // MenuItemGroupInterfaceModifier
const GENERATED_ArkUIMenuItemGroupModifier* GetMenuItemGroupModifier()
{
    static const GENERATED_ArkUIMenuItemGroupModifier ArkUIMenuItemGroupModifierImpl {
        MenuItemGroupModifier::ConstructImpl,
        MenuItemGroupInterfaceModifier::SetMenuItemGroupOptionsImpl,
    };
    return &ArkUIMenuItemGroupModifierImpl;
}

}
