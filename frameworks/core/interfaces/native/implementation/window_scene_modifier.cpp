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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WindowSceneInterfaceModifier {
void SetWindowSceneOptionsImpl(Ark_NativePointer node,
                               const Ark_Number* persistentId)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(persistentId);
    //auto convValue = Converter::OptConvert<type_name>(*persistentId);
    //WindowSceneModelNG::SetSetWindowSceneOptions(frameNode, convValue);
}
} // WindowSceneInterfaceModifier
namespace WindowSceneAttributeModifier {
void AttractionEffectImpl(Ark_NativePointer node,
                          const Ark_Position* destination,
                          const Ark_Number* fraction)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(destination);
    //auto convValue = Converter::OptConvert<type>(destination); // for enums
    //WindowSceneModelNG::SetAttractionEffect(frameNode, convValue);
}
} // WindowSceneAttributeModifier
const GENERATED_ArkUIWindowSceneModifier* GetWindowSceneModifier()
{
    static const GENERATED_ArkUIWindowSceneModifier ArkUIWindowSceneModifierImpl {
        WindowSceneInterfaceModifier::SetWindowSceneOptionsImpl,
        WindowSceneAttributeModifier::AttractionEffectImpl,
    };
    return &ArkUIWindowSceneModifierImpl;
}

}
