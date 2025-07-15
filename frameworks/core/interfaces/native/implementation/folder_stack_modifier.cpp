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

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_model_ng.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_model_ng_static.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace FolderStackModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = FolderStackModelNGStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // FolderStackModifier
namespace FolderStackInterfaceModifier {
void SetFolderStackOptionsImpl(Ark_NativePointer node,
                               const Opt_FolderStackOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto arkOpts = Converter::OptConvert<Ark_FolderStackOptions>(*options);
    if (arkOpts) {
        auto list = Converter::OptConvert<std::vector<std::string>>(arkOpts->upperItems);
        if (list) {
            FolderStackModelNGStatic::SetUpdateUpperItems(frameNode, *list);
        }
    }
}
} // FolderStackInterfaceModifier
namespace FolderStackAttributeModifier {
void AlignContentImpl(Ark_NativePointer node,
                      Ark_Alignment value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    FolderStackModelNGStatic::SetAlignment(frameNode, Converter::OptConvert<Alignment>(value));
}
void OnFolderStateChangeImpl(Ark_NativePointer node,
                             const OnFoldStatusChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onChange = [arkCallback = CallbackHelper(*value)](const FolderEventInfo& folderEventInfo) {
        Ark_OnFoldStatusChangeInfo eventInfo;
        eventInfo.foldStatus = Converter::ArkValue<Ark_FoldStatus>(folderEventInfo.GetFolderState());
        arkCallback.Invoke(eventInfo);
    };
    FolderStackModelNG::SetOnFolderStateChange(frameNode, std::move(onChange));
}
void OnHoverStatusChangeImpl(Ark_NativePointer node,
                             const OnHoverStatusChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onChange = [arkCallback = CallbackHelper(*value)](const FolderEventInfo& folderEventInfo) {
        Ark_HoverEventParam eventInfo;
        eventInfo.foldStatus = Converter::ArkValue<Ark_FoldStatus>(folderEventInfo.GetFolderState());
        arkCallback.Invoke(eventInfo);
    };
    FolderStackModelNG::SetOnHoverStatusChange(frameNode, std::move(onChange));
}
void EnableAnimationImpl(Ark_NativePointer node,
                         Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    FolderStackModelNG::SetEnableAnimation(frameNode, Converter::Convert<bool>(value));
}
void AutoHalfFoldImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    FolderStackModelNG::SetAutoHalfFold(frameNode, Converter::Convert<bool>(value));
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
