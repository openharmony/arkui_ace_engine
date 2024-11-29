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
namespace BadgeModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
}
} // BadgeModifier
namespace BadgeInterfaceModifier {
void SetBadgeOptions0Impl(Ark_NativePointer node,
                          const Ark_BadgeParamWithNumber* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //BadgeModelNG::SetSetBadgeOptions0(frameNode, convValue);
}
void SetBadgeOptions1Impl(Ark_NativePointer node,
                          const Ark_BadgeParamWithString* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //BadgeModelNG::SetSetBadgeOptions1(frameNode, convValue);
}
} // BadgeInterfaceModifier
const GENERATED_ArkUIBadgeModifier* GetBadgeModifier()
{
    static const GENERATED_ArkUIBadgeModifier ArkUIBadgeModifierImpl {
        BadgeModifier::ConstructImpl,
        BadgeInterfaceModifier::SetBadgeOptions0Impl,
        BadgeInterfaceModifier::SetBadgeOptions1Impl,
    };
    return &ArkUIBadgeModifierImpl;
}

}
