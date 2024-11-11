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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TabContentInterfaceModifier {
void SetTabContentOptionsImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(undefined);
    //auto convValue = Converter::OptConvert<type>(undefined); // for enums
    //TabContentModelNG::SetSetTabContentOptions(frameNode, convValue);
}
} // TabContentInterfaceModifier
namespace TabContentAttributeModifier {
void TabBar0Impl(Ark_NativePointer node,
                 const Ark_Type_TabContentAttribute_tabBar_value* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TabContentModelNG::SetTabBar0(frameNode, convValue);
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
