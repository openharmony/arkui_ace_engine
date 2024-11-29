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
namespace FolderStackModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
}
} // FolderStackModifier
namespace FolderStackInterfaceModifier {
void SetFolderStackOptionsImpl(Ark_NativePointer node,
                               const Opt_FolderStackOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = options ? Converter::OptConvert<type>(*options) : std::nullopt;
    //FolderStackModelNG::SetSetFolderStackOptions(frameNode, convValue);
}
} // FolderStackInterfaceModifier
namespace FolderStackAttributeModifier {
void AlignContentImpl(Ark_NativePointer node,
                      Ark_Alignment value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //FolderStackModelNG::SetAlignContent(frameNode, convValue);
}
void OnFolderStateChangeImpl(Ark_NativePointer node,
                             const OnFoldStatusChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //FolderStackModelNG::SetOnFolderStateChange(frameNode, convValue);
}
void OnHoverStatusChangeImpl(Ark_NativePointer node,
                             const OnHoverStatusChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //FolderStackModelNG::SetOnHoverStatusChange(frameNode, convValue);
}
void EnableAnimationImpl(Ark_NativePointer node,
                         Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //FolderStackModelNG::SetEnableAnimation(frameNode, convValue);
}
void AutoHalfFoldImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //FolderStackModelNG::SetAutoHalfFold(frameNode, convValue);
}
} // FolderStackAttributeModifier
const GENERATED_ArkUIFolderStackModifier* GetFolderStackModifier()
{
    static const GENERATED_ArkUIFolderStackModifier ArkUIFolderStackModifierImpl {
        FolderStackModifier::ConstructImpl,
        FolderStackInterfaceModifier::SetFolderStackOptionsImpl,
        FolderStackAttributeModifier::AlignContentImpl,
        FolderStackAttributeModifier::OnFolderStateChangeImpl,
        FolderStackAttributeModifier::OnHoverStatusChangeImpl,
        FolderStackAttributeModifier::EnableAnimationImpl,
        FolderStackAttributeModifier::AutoHalfFoldImpl,
    };
    return &ArkUIFolderStackModifierImpl;
}

}
