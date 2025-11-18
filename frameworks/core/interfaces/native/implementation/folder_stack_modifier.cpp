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
    auto arkOpts = Converter::OptConvertPtr<Ark_FolderStackOptions>(options);
    if (arkOpts) {
        auto list = Converter::OptConvert<std::vector<std::string>>(arkOpts->upperItems);
        if (list) {
            FolderStackModelNGStatic::SetUpdateUpperItems(frameNode, *list);
        }
    }
}
} // FolderStackInterfaceModifier
namespace FolderStackAttributeModifier {
void SetAlignContentImpl(Ark_NativePointer node,
                         const Opt_Alignment* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    FolderStackModelNGStatic::SetAlignment(frameNode, Converter::OptConvertPtr<Alignment>(value));
}
void SetOnFolderStateChangeImpl(Ark_NativePointer node,
                                const Opt_OnFoldStatusChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement reset value
        return;
    }
    auto onChange = [arkCallback = CallbackHelper(*optValue)](const FolderEventInfo& folderEventInfo) {
        Ark_OnFoldStatusChangeInfo eventInfo;
        eventInfo.foldStatus = Converter::ArkValue<Ark_FoldStatus>(folderEventInfo.GetFolderState());
        arkCallback.Invoke(eventInfo);
    };
    FolderStackModelNGStatic::SetOnFolderStateChange(frameNode, std::move(onChange));
}
void SetOnHoverStatusChangeImpl(Ark_NativePointer node,
                                const Opt_OnHoverStatusChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement reset value
        return;
    }
    auto onChange = [arkCallback = CallbackHelper(*optValue)](const FolderEventInfo& folderEventInfo) {
        Ark_HoverEventParam eventInfo;
        eventInfo.foldStatus = Converter::ArkValue<Ark_FoldStatus>(folderEventInfo.GetFolderState());
        arkCallback.Invoke(eventInfo);
    };
    FolderStackModelNGStatic::SetOnHoverStatusChange(frameNode, std::move(onChange));
}
void SetEnableAnimationImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        FolderStackModelNG::SetEnableAnimation(frameNode, true);
        return;
    }
    FolderStackModelNG::SetEnableAnimation(frameNode, *convValue);
}
void SetAutoHalfFoldImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        FolderStackModelNG::SetAutoHalfFold(frameNode, true);
        return;
    }
    FolderStackModelNG::SetAutoHalfFold(frameNode, *convValue);
}
} // FolderStackAttributeModifier
const GENERATED_ArkUIFolderStackModifier* GetFolderStackModifier()
{
    static const GENERATED_ArkUIFolderStackModifier ArkUIFolderStackModifierImpl {
        FolderStackModifier::ConstructImpl,
        FolderStackInterfaceModifier::SetFolderStackOptionsImpl,
        FolderStackAttributeModifier::SetAlignContentImpl,
        FolderStackAttributeModifier::SetOnFolderStateChangeImpl,
        FolderStackAttributeModifier::SetOnHoverStatusChangeImpl,
        FolderStackAttributeModifier::SetEnableAnimationImpl,
        FolderStackAttributeModifier::SetAutoHalfFoldImpl,
    };
    return &ArkUIFolderStackModifierImpl;
}

}
