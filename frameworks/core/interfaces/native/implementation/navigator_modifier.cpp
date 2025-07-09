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

#include "core/components_ng/pattern/navigator/navigator_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"

namespace OHOS::Ace::NG {
struct NavigatorOptions {
    std::string target;
    std::optional<NavigatorType> type;
};
} // OHOS::Ace::NG

namespace OHOS::Ace::NG::Converter {
template<>
NavigatorOptions Convert(const Ark_Literal_String_target_NavigationType_type& src)
{
    return {
        .target = Converter::Convert<std::string>(src.target),
        .type = Converter::OptConvert<NavigatorType>(src.type),
    };
}

template<>
void AssignCast(std::optional<NavigatorType>& dst, const Ark_NavigationType& src)
{
    switch (src) {
        case ARK_NAVIGATION_TYPE_PUSH: dst = NavigatorType::PUSH; break;
        case ARK_NAVIGATION_TYPE_BACK: dst = NavigatorType::BACK; break;
        case ARK_NAVIGATION_TYPE_REPLACE: dst = NavigatorType::REPLACE; break;
        default: LOGE("Unexpected enum value in Ark_NavigationType: %{public}d", src);
    }
}
} // OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NavigatorModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return nullptr;
}
} // NavigatorModifier
namespace NavigatorInterfaceModifier {
void SetNavigatorOptions0Impl(Ark_NativePointer node,
                              const Opt_Literal_String_target_NavigationType_type* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto navOptionsOpt = Converter::OptConvert<NavigatorOptions>(*value);
    CHECK_NULL_VOID(navOptionsOpt);

    NavigatorModelNG::SetUri(frameNode, navOptionsOpt->target);
    if (navOptionsOpt->type) {
        NavigatorModelNG::SetType(frameNode, *(navOptionsOpt->type));
    }
}
void SetNavigatorOptions1Impl(Ark_NativePointer node)
{
    // no sense to implement this due nothing arguments
}
} // NavigatorInterfaceModifier
namespace NavigatorAttributeModifier {
void ActiveImpl(Ark_NativePointer node,
                Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    NavigatorModelNG::SetActive(frameNode, Converter::Convert<bool>(value));
}
void TypeImpl(Ark_NativePointer node,
              Ark_NavigationType value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto typeOpt = Converter::OptConvert<NavigatorType>(value);
    CHECK_NULL_VOID(typeOpt);
    NavigatorModelNG::SetType(frameNode, *typeOpt);
}
void TargetImpl(Ark_NativePointer node,
                const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    NavigatorModelNG::SetUri(frameNode, Converter::Convert<std::string>(*value));
}
void ParamsImpl(Ark_NativePointer node,
                const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("NavigatorAttributeModifier::ParamsImpl - the CustomObjects is not implemented yet!");
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
} // OHOS::Ace::NG::GeneratedModifier
