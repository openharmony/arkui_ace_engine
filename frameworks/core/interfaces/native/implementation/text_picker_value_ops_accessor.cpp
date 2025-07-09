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

#include "arkoala_api_generated.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextPickerValueOpsAccessor {
Ark_NativePointer RegisterTextPickerValueCallbackImpl(Ark_NativePointer node,
                                                      const Ark_Union_String_Array_String* value,
                                                      const TextPickerValueCallback* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode && value && callback, nullptr);

    auto value_selector = value->selector;
    if (value_selector == 0) {
        const auto strValue = value->value0.chars;
        CHECK_NULL_RETURN(strValue, nullptr);
        TextPickerModelStatic::SetValue(frameNode, strValue);
    } else if (value_selector == 1) {
        auto array = value->value1.array;
        auto length = value->value1.length;
        CHECK_NULL_RETURN(array, nullptr);
        std::vector<std::string> arrayValue;
        arrayValue.reserve(length);
        for (int i = 0; i < length; ++i) {
            const auto& item = array[i];
            if (item.chars && item.length > 0) {
                arrayValue.emplace_back(item.chars, item.length);
            } else {
                arrayValue.emplace_back("");
            }
        }
        TextPickerModelStatic::SetValues(frameNode, arrayValue);
    }

    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const std::vector<std::string>& value) {
        if (value.size() == 1) {
            auto result = Converter::ArkUnion<Ark_Union_String_Array_String, Ark_String>(value[0]);
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.Invoke(result);
        } else {
            Converter::ArkArrayHolder<Array_String> arrayHolder(value);
            Array_String array = arrayHolder.ArkValue();
            auto result = Converter::ArkUnion<Ark_Union_String_Array_String, Array_String>(array);
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.Invoke(result);
        }
    };
    TextPickerModelStatic::SetOnValueChangeEvent(frameNode, std::move(onEvent));
    return node;
}
} // TextPickerValueOpsAccessor

const GENERATED_ArkUITextPickerValueOpsAccessor* GetTextPickerValueOpsAccessor()
{
    static const GENERATED_ArkUITextPickerValueOpsAccessor TextPickerValueOpsAccessorImpl {
        TextPickerValueOpsAccessor::RegisterTextPickerValueCallbackImpl,
    };
    return &TextPickerValueOpsAccessorImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
