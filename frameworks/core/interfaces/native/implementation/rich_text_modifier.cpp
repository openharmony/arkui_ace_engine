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

#ifdef WEB_SUPPORTED
#include "core/components_ng/pattern/web/ani/richtext_model_static.h"
#endif
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RichTextModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
#ifdef WEB_SUPPORTED
    auto frameNode = RichTextModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
#else
    return {};
#endif // WEB_SUPPORTED
}
} // RichTextModifier
namespace RichTextInterfaceModifier {
void SetRichTextOptionsImpl(Ark_NativePointer node,
                            const Ark_Union_String_Resource* content)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(content);
#ifdef WEB_SUPPORTED
    auto convValue = Converter::OptConvertPtr<std::string>(content);
    if (convValue.has_value()) {
        RichTextModelStatic::SetRichTextOptions(frameNode, convValue.value());
    }
#endif
}
} // RichTextInterfaceModifier
namespace RichTextAttributeModifier {
void SetOnStartImpl(Ark_NativePointer node,
                    const Opt_synthetic_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
#ifdef WEB_SUPPORTED
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto onCallback = [arkCallback = CallbackHelper(*optValue)](const BaseEventInfo* event) {
        arkCallback.InvokeSync();
    };
    RichTextModelStatic::SetOnPageStart(frameNode, std::move(onCallback));
#endif
}
void SetOnCompleteImpl(Ark_NativePointer node,
                       const Opt_synthetic_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
#ifdef WEB_SUPPORTED
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto onCallback = [arkCallback = CallbackHelper(*optValue)](const BaseEventInfo* event) {
        arkCallback.InvokeSync();
    };
    RichTextModelStatic::SetOnPageFinish(frameNode, std::move(onCallback));
#endif
}
} // RichTextAttributeModifier
const GENERATED_ArkUIRichTextModifier* GetRichTextModifier()
{
    static const GENERATED_ArkUIRichTextModifier ArkUIRichTextModifierImpl {
        RichTextModifier::ConstructImpl,
        RichTextInterfaceModifier::SetRichTextOptionsImpl,
        RichTextAttributeModifier::SetOnStartImpl,
        RichTextAttributeModifier::SetOnCompleteImpl,
    };
    return &ArkUIRichTextModifierImpl;
}

}
