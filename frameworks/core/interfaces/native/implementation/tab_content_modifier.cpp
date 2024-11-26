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

#include "base/utils/string_utils.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"

namespace OHOS::Ace::NG {
namespace {
    struct TabBarOptions {
        std::optional<std::string> text;
        std::optional<std::string> icon;
    };

    using TabBarOptionsVariant = std::variant<
        Ark_String,
        Ark_Resource,
        Callback_Any,
        Ark_Literal_Union_String_Resource_icon_text
    >;
} // namespace

namespace Converter {
template<>
TabBarOptions Convert(const Ark_Literal_Union_String_Resource_icon_text& src)
{
    TabBarOptions options;
    options.text = OptConvert<std::string>(src.text);
    options.icon = OptConvert<std::string>(src.icon);
    return options;
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TabContentInterfaceModifier {
void SetTabContentOptionsImpl(Ark_NativePointer node)
{
    // keep it empty because TabContent doesn`t have any options
}
} // TabContentInterfaceModifier
namespace TabContentAttributeModifier {
void TabBar0Impl(Ark_NativePointer node,
                 const Ark_Type_TabContentAttribute_tabBar_value* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    std::optional<std::string> label = std::nullopt;
    std::optional<std::string> icon = std::nullopt;
    TabBarBuilderFunc builder = nullptr;
    auto options = Converter::OptConvert<TabBarOptionsVariant>(*value);
    if (auto arkText = std::get_if<Ark_String>(&options.value());
        arkText != nullptr) {
        label = Converter::Convert<std::string>(*arkText);
    } else if (auto arkText = std::get_if<Ark_Resource>(&options.value());
        arkText != nullptr) {
        label = Converter::OptConvert<std::string>(*arkText);
    } else if (auto arkText = std::get_if<Callback_Any>(&options.value());
        arkText != nullptr) {
        LOGE("ARKOALA TabContentAttributeModifier.CustomBuilder not implemented.");
    } else if (auto iconLabel = std::get_if<Ark_Literal_Union_String_Resource_icon_text>(&options.value());
        iconLabel != nullptr) {
        auto tabBarOptions = Converter::OptConvert<TabBarOptions>(*iconLabel);
        if (tabBarOptions) {
            label = tabBarOptions->text;
            icon = tabBarOptions->icon;
        }
    } else {
        LOGE("ARKOALA TabContentAttributeModifier.TabBar0Impl unknown value format.");
    }
    TabContentModelNG::SetTabBar(frameNode, label, icon, std::move(builder));
}
void TabBar1Impl(Ark_NativePointer node,
                 const Ark_Union_SubTabBarStyle_BottomTabBarStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TabContentModelNG::SetTabBar1(frameNode, convValue);
}
void OnWillShowImpl(Ark_NativePointer node,
                    const VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TabContentModelNG::SetOnWillShow(frameNode, convValue);
}
void OnWillHideImpl(Ark_NativePointer node,
                    const VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TabContentModelNG::SetOnWillHide(frameNode, convValue);
}
} // TabContentAttributeModifier
const GENERATED_ArkUITabContentModifier* GetTabContentModifier()
{
    static const GENERATED_ArkUITabContentModifier ArkUITabContentModifierImpl {
        TabContentInterfaceModifier::SetTabContentOptionsImpl,
        TabContentAttributeModifier::TabBar0Impl,
        TabContentAttributeModifier::TabBar1Impl,
        TabContentAttributeModifier::OnWillShowImpl,
        TabContentAttributeModifier::OnWillHideImpl,
    };
    return &ArkUITabContentModifierImpl;
}

}
