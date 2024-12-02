/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_view.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"

namespace OHOS::Ace::NG {
using MenuItemGroupType = std::variant<std::optional<std::string>, void*>;
}

namespace OHOS::Ace::NG::Converter {
template<>
MenuItemGroupType Convert(const Ark_ResourceStr& src)
{
    return Converter::OptConvert<std::string>(src);
}

template<>
MenuItemGroupType Convert(const Ark_Resource& src)
{
    return Converter::OptConvert<std::string>(src);
}

template<>
MenuItemGroupType Convert(const Ark_String& src)
{
    return Converter::OptConvert<std::string>(src);
}

template<>
MenuItemGroupType Convert(const Callback_Any& src)
{
    return nullptr;
}

struct MenuItemGroupOptions {
    std::optional<MenuItemGroupType> header;
    std::optional<MenuItemGroupType> footer;
};

template<>
MenuItemGroupOptions Convert(const Ark_MenuItemGroupOptions& src)
{
    return {
        .header = Converter::OptConvert<MenuItemGroupType>(src.header),
        .footer = Converter::OptConvert<MenuItemGroupType>(src.footer)
    };
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace MenuItemGroupModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
}
} // MenuItemGroupModifier
namespace MenuItemGroupInterfaceModifier {
void SetMenuItemGroupOptionsImpl(Ark_NativePointer node,
                                 const Opt_MenuItemGroupOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    auto options = value ? Converter::OptConvert<Converter::MenuItemGroupOptions>(*value) : std::nullopt;
    if (options.has_value()) {
        if (auto headerPtr = std::get_if<std::optional<std::string>>(&(*(options.value().header))); headerPtr) {
            MenuItemGroupView::SetHeader(frameNode, *headerPtr);
        }
        if (auto footerPtr = std::get_if<std::optional<std::string>>(&(*(options.value().footer))); footerPtr) {
            MenuItemGroupView::SetFooter(frameNode, *footerPtr);
        }
    } else {
        MenuItemGroupView::SetHeader(frameNode, std::nullopt);
        MenuItemGroupView::SetHeader(frameNode, std::nullopt);
    }
    LOGE("MenuItemGroupModifier::SetMenuItemGroupOptionsImpl isn't implemented, Ark_CustomBuilder isn't supported");
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
