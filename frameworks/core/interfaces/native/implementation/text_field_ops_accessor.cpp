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

#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text_field/text_field_model_static.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextFieldOpsAccessor {
Ark_NativePointer RegisterTextFieldValueCallbackImpl(Ark_NativePointer node,
                                                     const Ark_ResourceStr* value,
                                                     const TextFieldValueCallback* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode && value && callback, nullptr);
    auto text = Converter::OptConvert<std::u16string>(*value);

    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto textValue = pattern->GetTextUtf16Value();
    if (text.has_value() && text.value() != textValue) {
        auto changed = pattern->InitValueText(text.value());
        pattern->SetTextChangedAtCreation(changed);
    }

    auto onEvent = [arkCallback = CallbackHelper(*callback)](const std::u16string& content) {
        Converter::ConvContext ctx;
        auto arkContent = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(content, &ctx);
        arkCallback.Invoke(arkContent);
    };
    TextFieldModelStatic::SetOnChangeEvent(frameNode, std::move(onEvent));
    return node;
}
} // TextFieldOpsAccessor
const GENERATED_ArkUITextFieldOpsAccessor* GetTextFieldOpsAccessor()
{
    static const GENERATED_ArkUITextFieldOpsAccessor TextFieldOpsAccessorImpl {
        TextFieldOpsAccessor::RegisterTextFieldValueCallbackImpl,
    };
    return &TextFieldOpsAccessorImpl;
}

}
