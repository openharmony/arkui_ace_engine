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
namespace TextPickerSelectedOpsAccessor {
inline void ProcessCascadeSelected(const std::vector<OHOS::Ace::NG::TextCascadePickerOptions>& options,
    uint32_t index, std::vector<uint32_t>& selectedValues)
{
    if (static_cast<int32_t>(index) > static_cast<int32_t>(selectedValues.size()) - 1) {
        selectedValues.emplace_back(0);
    }
    if (selectedValues[index] >= options.size()) {
        selectedValues[index] = 0;
    }
    if (static_cast<int32_t>(selectedValues[index]) <= static_cast<int32_t>(options.size()) - 1 &&
        options[selectedValues[index]].children.size() > 0) {
        ProcessCascadeSelected(options[selectedValues[index]].children, index + 1, selectedValues);
    }
}

void ApplyTextPickerSelected(FrameNode* frameNode, const Ark_Union_Number_Array_Number* selected)
{
    CHECK_NULL_VOID(frameNode && selected);
    Opt_Union_Number_Array_Number selectedOpt = {};
    selectedOpt.tag = INTEROP_TAG_OBJECT;
    selectedOpt.value = *selected;
    if (TextPickerModelStatic::IsSingle(frameNode)) {
        std::vector<OHOS::Ace::NG::RangeContent> rangeResult;
        TextPickerModelStatic::GetSingleRange(frameNode, rangeResult);
        auto indexOpt = Converter::OptConvert<uint32_t>(selectedOpt);
        uint32_t index = indexOpt.value_or(0);
        if (GreatOrEqual(index, static_cast<int32_t>(rangeResult.size())) || LessNotEqual(index, 0)) {
            index = 0;
        }
        TextPickerModelStatic::SetSelected(frameNode, index);
    } else {
        std::vector<OHOS::Ace::NG::TextCascadePickerOptions> options;
        TextPickerModelStatic::GetMultiOptions(frameNode, options);
        auto indexesOpt = Converter::OptConvert<std::vector<uint32_t>>(selectedOpt);
        std::vector<uint32_t> indexes = indexesOpt.value_or(std::vector<uint32_t>());
        if (TextPickerModelStatic::IsCascade(frameNode)) {
            TextPickerModelStatic::SetHasSelectAttr(frameNode, true);
            ProcessCascadeSelected(options, 0, indexes);
            uint32_t maxCount = TextPickerModelStatic::GetMaxCount(frameNode);
            uint32_t indexesSize = static_cast<uint32_t>(indexes.size());
            if (LessNotEqual(indexesSize, maxCount)) {
                auto diff = maxCount - indexesSize;
                for (uint32_t i = 0; i < diff; i++) {
                    indexes.emplace_back(0);
                }
            }
        } else {
            auto count = TextPickerModelStatic::IsCascade(frameNode) ?
                TextPickerModelStatic::GetMaxCount(frameNode) : options.size();
            for (uint32_t i = 0; i < count; i++) {
                if (indexes.size() == 0 || (indexes.size() > 0 && indexes.size() < i + 1)) {
                    indexes.emplace_back(0);
                } else if (indexes[i] >= options[i].rangeResult.size()) {
                    indexes[i] = 0;
                }
            }
        }
        TextPickerModelStatic::SetSelecteds(frameNode, indexes);
    }
}

Ark_NativePointer RegisterTextPickerSelectedCallbackImpl(Ark_NativePointer node,
                                                         const Ark_Union_Number_Array_Number* selected,
                                                         const TextPickerSelectedCallback* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode && selected && callback, nullptr);

    ApplyTextPickerSelected(frameNode, selected);

    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const std::vector<double>& selected) {
        if (selected.size() == 1) {
            auto result = Converter::ArkUnion<Ark_Union_Number_Array_Number, Ark_Number>(selected[0]);
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.Invoke(result);
        } else {
            Converter::ArkArrayHolder<Array_Number> arrayHolder(selected);
            Array_Number array = arrayHolder.ArkValue();
            auto result = Converter::ArkUnion<Ark_Union_Number_Array_Number, Array_Number>(array);
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.Invoke(result);
        }
    };
    TextPickerModelStatic::SetOnSelectedChangeEvent(frameNode, std::move(onEvent));
    return node;
}
} // TextPickerSelectedOpsAccessor

const GENERATED_ArkUITextPickerSelectedOpsAccessor* GetTextPickerSelectedOpsAccessor()
{
    static const GENERATED_ArkUITextPickerSelectedOpsAccessor TextPickerSelectedOpsAccessorImpl {
        TextPickerSelectedOpsAccessor::RegisterTextPickerSelectedCallbackImpl,
    };
    return &TextPickerSelectedOpsAccessorImpl;
}
} // namespace OHOS::Ace::NG::GeneratedModifier