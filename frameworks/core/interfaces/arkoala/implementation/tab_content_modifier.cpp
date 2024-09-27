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
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"

namespace OHOS::Ace::NG {
namespace {
    struct TabBarOptions {
        std::optional<std::string> text;
        std::optional<std::string> icon;
    };
    
    using TabBarOptionsVariant = std::variant<
        Ark_String,
        Ark_Resource,
        Ark_Function,
        Literal_Opt_Union_String_Resource_icon_text
    >;
} // namespace

namespace Converter {
template<>
TabBarOptions Convert(const Literal_Opt_Union_String_Resource_icon_text& src)
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
    // keep it empty because RelativeContainer doesn`t have any options
}
} // TabContentInterfaceModifier
namespace TabContentAttributeModifier {
void TabBar0Impl(Ark_NativePointer node,
                 const Type_TabContentAttribute_tabBar_Arg0* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    std::optional<std::string> label = std::nullopt;
    std::optional<std::string> icon = std::nullopt;
    std::optional<TabBarBuilderFunc> builder = std::nullopt;
    auto options = Converter::OptConvert<TabBarOptionsVariant>(*value);
    if (auto arkText = std::get_if<Ark_String>(&options.value());
        arkText != nullptr) {
        label = Converter::Convert<std::string>(*arkText);
    } else if (auto arkText = std::get_if<Ark_Resource>(&options.value());
        arkText != nullptr) {
        label = Converter::OptConvert<std::string>(*arkText);
    } else if (auto arkText = std::get_if<Ark_Function>(&options.value());
        arkText != nullptr) {
        LOGE("ARKOALA TabContentAttributeModifier.CustomBuilder not implemented.");
    } else if (auto iconLabel = std::get_if<Literal_Opt_Union_String_Resource_icon_text>(&options.value());
        iconLabel != nullptr) {
        auto tabBarOptions = Converter::OptConvert<TabBarOptions>(*iconLabel);
        if (tabBarOptions) {
            label = tabBarOptions->text;
            icon = tabBarOptions->icon;
        }
    } else {
        LOGE("ARKOALA TabContentAttributeModifier.TabBar0Impl unknown value format.");
    }
    TabContentModelNG::SetTabBar(frameNode, label, icon, std::move(*builder));
}
void TabBar1Impl(Ark_NativePointer node,
                 const Type_TabContentAttribute_tabBar1_Arg0* value)
{
    //typedef Union_SubTabBarStyle_BottomTabBarStyle Type_TabContentAttribute_tabBar1_Arg0;
//     typedef struct Union_SubTabBarStyle_BottomTabBarStyle {
//     Ark_Int32 selector;
//     union {
//         struct Ark_SubTabBarStyle value0;
//         struct Ark_BottomTabBarStyle value1;
//     };
// } Union_SubTabBarStyle_BottomTabBarStyle;

    // Union_SubTabBarStyle_BottomTabBarStyle
    //     typedef struct Ark_SubTabBarStyle {
    //     Opt_IndicatorStyle _indicator;
    //     Opt_SelectedMode _selectedMode;
    //     Opt_BoardStyle _board;
    //     Opt_LabelStyle _labelStyle;
    //     Opt_Union_Padding_Length _padding;
    //     Opt_String _id;
    // } Ark_SubTabBarStyle;

//     typedef struct Ark_IndicatorStyle {
//     Opt_Length left;
//     Opt_Length top;
//     Opt_Length right;
//     Opt_Length bottom;
//     Opt_Length size;
//     Opt_Boolean mask;
//     Opt_ResourceColor color;
//     Opt_ResourceColor selectedColor;
// } Ark_IndicatorStyle;

// typedef struct Opt_SelectedMode {
//     enum Ark_Tag tag;
//     enum  Ark_SelectedMode value;
// } Opt_SelectedMode;

// typedef struct Ark_BoardStyle {
//     Opt_Length borderRadius;
// } Ark_BoardStyle;

// typedef struct Ark_LabelStyle {
//     Opt_TextOverflow overflow;
//     Opt_Number maxLines;
//     Opt_Union_Number_ResourceStr minFontSize;
//     Opt_Union_Number_ResourceStr maxFontSize;
//     Opt_TextHeightAdaptivePolicy heightAdaptivePolicy;
//     Opt_Font font;
// } Ark_LabelStyle;

// typedef struct Union_Ark_Padding_Length {
//     Ark_Int32 selector;
//     union {
//         struct Ark_Padding value0;
//         Ark_Length value1;
//     };
// } Union_Ark_Padding_Length;

// typedef struct Opt_String {
//     enum Ark_Tag tag;
//     Ark_String value;
// } Opt_String;

//     typedef struct Ark_BottomTabBarStyle {
//     Opt_LabelStyle _labelStyle;
//     Opt_Union_Padding_Length_LocalizedPadding _padding;
//     Opt_LayoutMode _layoutMode;
//     Opt_VerticalAlign _verticalAlign;
//     Opt_Boolean _symmetricExtensible;
//     Opt_String _id;
//     Opt_TabBarIconStyle _iconStyle;
// } Ark_BottomTabBarStyle;

// typedef struct Union_Ark_Padding_Length_LocalizedPadding {
//     Ark_Int32 selector;
//     union {
//         struct Ark_Padding value0;
//         Ark_Length value1;
//         struct Ark_LocalizedPadding value2;
//     };
// } Union_Ark_Padding_Length_LocalizedPadding;

// typedef struct Ark_LocalizedPadding {
//     Opt_CustomObject top;
//     Opt_CustomObject end;
//     Opt_CustomObject bottom;
//     Opt_CustomObject start;
// } Ark_LocalizedPadding;

// typedef struct Ark_Padding {
//     Opt_Length top;
//     Opt_Length right;
//     Opt_Length bottom;
//     Opt_Length left;
// } Ark_Padding;

// typedef struct Opt_LayoutMode {
//     enum Ark_Tag tag;
//     enum  Ark_LayoutMode value;
// } Opt_LayoutMode;

// typedef struct Opt_VerticalAlign {
//     enum Ark_Tag tag;
//     enum  Ark_VerticalAlign value;
// } Opt_VerticalAlign;

// typedef struct Ark_TabBarIconStyle {
//     Opt_ResourceColor selectedColor;
//     Opt_ResourceColor unselectedColor;
// } Ark_TabBarIconStyle;
// typedef struct Opt_TabBarIconStyle {
//     enum Ark_Tag tag;
//     Ark_TabBarIconStyle value;
// } Opt_TabBarIconStyle;
}
void OnWillShowImpl(Ark_NativePointer node,
                    Ark_Function event)
{
}
void OnWillHideImpl(Ark_NativePointer node,
                    Ark_Function event)
{
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
