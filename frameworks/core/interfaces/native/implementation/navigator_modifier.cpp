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
namespace NavigatorModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
}
} // NavigatorModifier
namespace NavigatorInterfaceModifier {
void SetNavigatorOptions0Impl(Ark_NativePointer node,
                              const Opt_Literal_String_target_NavigationType_type* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigatorModelNG::SetSetNavigatorOptions0(frameNode, convValue);
}
void SetNavigatorOptions1Impl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(undefined);
    //auto convValue = Converter::OptConvert<type>(undefined); // for enums
    //NavigatorModelNG::SetSetNavigatorOptions1(frameNode, convValue);
}
} // NavigatorInterfaceModifier
namespace NavigatorAttributeModifier {
void ActiveImpl(Ark_NativePointer node,
                Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //NavigatorModelNG::SetActive(frameNode, convValue);
}
void TypeImpl(Ark_NativePointer node,
              Ark_NavigationType value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //NavigatorModelNG::SetType(frameNode, convValue);
}
void TargetImpl(Ark_NativePointer node,
                const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    //NavigatorModelNG::SetTarget(frameNode, convValue);
}
void ParamsImpl(Ark_NativePointer node,
                const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //NavigatorModelNG::SetParams(frameNode, convValue);
}
} // NavigatorAttributeModifier
const GENERATED_ArkUINavigatorModifier* GetNavigatorModifier()
{
    static const GENERATED_ArkUINavigatorModifier ArkUINavigatorModifierImpl {
        NavigatorModifier::ConstructImpl,
        NavigatorInterfaceModifier::SetNavigatorOptions0Impl,
        NavigatorInterfaceModifier::SetNavigatorOptions1Impl,
        NavigatorAttributeModifier::ActiveImpl,
        NavigatorAttributeModifier::TypeImpl,
        NavigatorAttributeModifier::TargetImpl,
        NavigatorAttributeModifier::ParamsImpl,
    };
    return &ArkUINavigatorModifierImpl;
}

}
