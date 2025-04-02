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

#include "core/components_ng/base/frame_node.h"
#include "core/components/picker/picker_text_component.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG {

struct TextPickerOptions {
    std::vector<NG::RangeContent> range;
    uint32_t kind = 0;
    uint32_t selected = 0;
    std::string value = "";
    std::vector<NG::TextCascadePickerOptions> options;
    std::vector<uint32_t> selecteds;
    std::vector<std::string> values;
    bool hasValue = false;
    bool hasSelected = false;
    bool isCascade = false;
    uint32_t maxCount = 0;
};

size_t ProcessCascadeOptionDepth(const NG::TextCascadePickerOptions& option)
{
    size_t depth = 1;
    if (option.children.size() == 0) {
        return depth;
    }

    for (auto&& pos : option.children) {
        size_t tmpDep = 1;
        tmpDep += ProcessCascadeOptionDepth(pos);
        if (tmpDep > depth) {
            depth = tmpDep;
        }
    }
    return depth;
}

void ValidateSelectedValues(std::vector<uint32_t>& selectedValues, std::vector<std::string>& values,
    uint32_t index, bool isHasSelectAttr, std::vector<std::string>& resultStr)
{
    if (index + 1 > selectedValues.size()) {
        selectedValues.emplace_back(0);
    } else {
        if (selectedValues[index] >= resultStr.size()) {
            selectedValues[index] = 0;
        }
    }

    if (!isHasSelectAttr && selectedValues[index] == 0 && !values[index].empty()) {
        auto valueIterator = std::find(resultStr.begin(), resultStr.end(), values[index]);
        if (valueIterator != resultStr.end()) {
            auto localDistance = std::distance(resultStr.begin(), valueIterator);
            selectedValues[index] = localDistance > 0 ? static_cast<uint32_t>(localDistance) : 0;
        }
    }
}

void ValidateCascadeOptions(std::vector<NG::TextCascadePickerOptions>& options, std::vector<uint32_t>& selectedValues,
    std::vector<std::string>& values, uint32_t index, bool isHasSelectAttr)
{
    std::vector<std::string> resultStr;
    for (size_t i = 0; i < options.size(); i++) {
        std::string textStr = "";
        if (options[i].rangeResult.size() > 0) {
            textStr = options[i].rangeResult.front();
        }
        resultStr.emplace_back(textStr);
    }
    if (index + 1 > values.size()) {
        if (resultStr.size() > 0) {
            values.emplace_back(resultStr.front());
        } else {
            values.emplace_back("");
        }
    } else {
        if (resultStr.size() > 0) {
            auto valueIterator = std::find(resultStr.begin(), resultStr.end(), values[index]);
            if (valueIterator == resultStr.end()) {
                values[index] = resultStr.front();
            }
        } else {
            values[index] = "";
        }
    }

    ValidateSelectedValues(selectedValues, values, index, isHasSelectAttr, resultStr);
    std::vector<NG::TextCascadePickerOptions> children = options[selectedValues[index]].children;
    if (!children.empty()) {
        ValidateCascadeOptions(children, selectedValues, values, index + 1, isHasSelectAttr);
    }
}

void CheckSelecteds(TextPickerOptions& options, uint32_t index)
{
    if (options.selecteds.size() < index + 1) {
        options.selecteds.emplace_back(0);
    } else {
        if (options.selecteds[index] >= options.options[index].rangeResult.size()) {
            options.selecteds[index] = 0;
        }
    }
}

void ValidateMultiTextPickerOptions(TextPickerOptions& options)
{
    if (options.options.empty()) return;

    if (!options.isCascade && options.hasSelected) {
        for (uint32_t i = 0; i < options.options.size(); i++) {
            CheckSelecteds(options, i);
        }
    } else if (options.isCascade) {
        ValidateCascadeOptions(options.options, options.selecteds, options.values, 0, options.hasSelected);
        options.maxCount = 1;
        for (size_t i = 0; i < options.options.size(); i++) {
            size_t tmp = ProcessCascadeOptionDepth(options.options[i]);
            if (tmp > options.maxCount) {
                options.maxCount = tmp;
            }
        }
        if (options.selecteds.size() < options.maxCount) {
            auto differ = options.maxCount - options.selecteds.size();
            for (uint32_t i = 0; i < differ; i++) {
                options.selecteds.emplace_back(0);
            }
        }
        if (options.values.size() < options.maxCount) {
            auto differ = options.maxCount - options.values.size();
            for (uint32_t i = 0; i < differ; i++) {
                options.values.emplace_back("");
            }
        }
    }
}

void ValidateSingleTextPickerOptions(TextPickerOptions& options)
{
    if (options.range.empty()) return;

    if (!options.hasValue) {
        options.value = options.range.front().text_;
    }
    if (!options.hasSelected) {
        auto value = options.value;
        auto valueIterator = std::find_if(
            options.range.begin(), options.range.end(),
            [value](const NG::RangeContent& rangeContrent) -> bool {
                return rangeContrent.text_.compare(value) == 0;
            });
        if (valueIterator != options.range.end()) {
            options.selected = static_cast<uint32_t>(std::distance(options.range.begin(), valueIterator));
        } else {
            options.selected = 0;
        }
    }

    if (options.selected >= options.range.size()) {
        options.selected = 0;
    }
}
}

namespace OHOS::Ace::NG::Converter {
    uint32_t CalculateKind(bool fromRangeContent, const std::vector<NG::RangeContent>& range)
    {
        uint32_t kind = 0;
        if (!fromRangeContent) {
            kind = NG::TEXT;
        } else {
            kind |= NG::ICON;
            for (const auto& rangeContent : range) {
                if (!rangeContent.text_.empty()) {
                    kind |= NG::TEXT;
                    break;
                }
            }
        }
        return kind;
    }

    template<>
    TextPickerOptions Convert(const Ark_TextPickerOptions& src)
    {
        TextPickerOptions dst;
        auto pickerValueOpt = Converter::OptConvert<PickerValueType>(src.value);
        if (pickerValueOpt) {
            auto pickerValue = pickerValueOpt.value();
            dst.hasValue = true;
            if (auto value = std::get_if<std::string>(&pickerValue); value) {
                dst.value = *value;
                dst.values.emplace_back(dst.value);
            } else {
                dst.values = std::move(std::get<std::vector<std::string>>(pickerValue));
            }
        }
        auto pickerSelectedOpt = Converter::OptConvert<PickerSelectedType>(src.selected);
        if (pickerSelectedOpt) {
            auto pickerSelected = pickerSelectedOpt.value();
            dst.hasSelected = true;
            if (auto selected = std::get_if<uint32_t>(&pickerSelected); selected) {
                dst.selected = *selected;
                dst.selecteds.emplace_back(dst.selected);
            } else {
                dst.selecteds = std::move(std::get<std::vector<uint32_t>>(pickerSelected));
            }
        }
        auto pickerRangeOpt = Converter::OptConvert<PickerRangeType>(src.range);
        if (pickerRangeOpt) {
            auto pickerRange = pickerRangeOpt.value();
            auto rangeVector = std::get_if<std::pair<bool, std::vector<NG::RangeContent>>>(&pickerRange);
            if (rangeVector) {
                auto fromRangeContent = rangeVector->first;
                dst.range = rangeVector->second;
                dst.kind = CalculateKind(fromRangeContent, dst.range);
                if (fromRangeContent) {
                    dst.value = "";
                    dst.hasValue = true;
                }
            } else {
                auto options = std::get<std::pair<bool, std::vector<NG::TextCascadePickerOptions>>>(pickerRange);
                dst.options = std::move(options.second);
                dst.isCascade = options.first;
            }
        }
        return dst;
    }
}

inline void ProcessCascadeSelected(
    const std::vector<OHOS::Ace::NG::TextCascadePickerOptions>& options,
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

namespace OHOS::Ace::NG::Converter {
template<>
ItemDivider Convert(const Ark_DividerOptions& src)
{
    ItemDivider divider;
    divider.strokeWidth = OptConvert<Dimension>(src.strokeWidth).value_or(divider.strokeWidth);
    divider.color = OptConvert<Color>(src.color).value_or(divider.color);
    divider.startMargin = OptConvert<Dimension>(src.startMargin).value_or(divider.startMargin);
    divider.endMargin = OptConvert<Dimension>(src.endMargin).value_or(divider.endMargin);
    return divider;
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextPickerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // TextPickerModifier
namespace TextPickerInterfaceModifier {
void SetSingleRange(FrameNode* frameNode, const Ark_Union_Number_Array_Number* value)
{
    std::vector<OHOS::Ace::NG::RangeContent> rangeResult;
    TextPickerModelNG::GetSingleRange(frameNode, rangeResult);
    auto indexOpt = Converter::OptConvert<uint32_t>(*value);
    uint32_t index = indexOpt.value_or(0);
    if (GreatOrEqual(index, static_cast<int32_t>(rangeResult.size())) || LessNotEqual(index, 0)) {
        index = 0;
    }
    TextPickerModelNG::SetSelected(frameNode, index);
}
void SetMultiRange(FrameNode* frameNode, const Ark_Union_Number_Array_Number* value)
{
    std::vector<OHOS::Ace::NG::TextCascadePickerOptions> options;
    TextPickerModelNG::GetMultiOptions(frameNode, options);
    auto count = TextPickerModelNG::IsCascade(frameNode) ? TextPickerModelNG::GetMaxCount(frameNode) : options.size();

    auto indexesOpt = Converter::OptConvert<std::vector<uint32_t>>(*value);
    std::vector<uint32_t> indexes = indexesOpt.value_or(std::vector<uint32_t>());
    if (TextPickerModelNG::IsCascade(frameNode)) {
        TextPickerModelNG::SetHasSelectAttr(frameNode, true);
        ProcessCascadeSelected(options, 0, indexes);
        uint32_t maxCount = TextPickerModelNG::GetMaxCount(frameNode);
        auto indexesSize = static_cast<int32_t>(indexes.size());
        if (LessNotEqual(indexesSize, maxCount)) {
            auto diff = maxCount - indexesSize;
            for (uint32_t i = 0; i < diff; i++) {
                indexes.emplace_back(0);
            }
        }
    } else {
        for (uint32_t i = 0; i < count; i++) {
            if (indexes.size() == 0 || (indexes.size() > 0 && indexes.size() < i + 1)) {
                indexes.emplace_back(0);
            } else if (indexes[i] >= options[i].rangeResult.size()) {
                indexes[i] = 0;
            }
        }
    }
    TextPickerModelNG::SetSelecteds(frameNode, indexes);
}
void SetTextPickerOptionsImpl(Ark_NativePointer node,
                              const Opt_TextPickerOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);

    auto textPickerOptionsOpt = Converter::OptConvert<TextPickerOptions>(*options);
    if (textPickerOptionsOpt.has_value()) {
        auto textPickerOptions = textPickerOptionsOpt.value();
        if (!textPickerOptions.range.empty()) {
            ValidateSingleTextPickerOptions(textPickerOptions);
            //do not change the order of calls
            TextPickerModelNG::SetTextPickerSingeRange(true);
            // need check
            // TextPickerModelNG::InitialSetupSinglePicker(frameNode, textPickerOptions.kind);
            TextPickerModelNG::SetRange(frameNode, textPickerOptions.range);
            TextPickerModelNG::SetValue(frameNode, textPickerOptions.value);
            TextPickerModelNG::SetSelected(frameNode, textPickerOptions.selected);
        } else if (!textPickerOptions.options.empty()) {
            ValidateMultiTextPickerOptions(textPickerOptions);
            //do not change the order of calls
            TextPickerModelNG::SetTextPickerSingeRange(false);
            TextPickerModelNG::SetIsCascade(frameNode, textPickerOptions.isCascade);
            TextPickerModelNG::SetHasSelectAttr(frameNode, textPickerOptions.hasSelected);
            TextPickerModelNG::SetColumns(frameNode, textPickerOptions.options);
            TextPickerModelNG::SetValues(frameNode, textPickerOptions.values);
            if (textPickerOptions.isCascade || textPickerOptions.hasSelected) {
                TextPickerModelNG::SetSelecteds(frameNode, textPickerOptions.selecteds);
            }
        }
    }
}
} // TextPickerInterfaceModifier
namespace TextPickerAttributeModifier {
void DefaultPickerItemHeightImpl(Ark_NativePointer node,
                                 const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto height = Converter::OptConvert<Dimension>(*value);
    // need check
    // TextPickerModelNG::SetDefaultPickerItemHeight(frameNode, height);
}
void CanLoopImpl(Ark_NativePointer node,
                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetCanLoop(frameNode, Converter::Convert<bool>(value));
}
void DisappearTextStyleImpl(Ark_NativePointer node,
                            const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto pickerStyle = Converter::Convert<PickerTextStyle>(*value);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    TextPickerModelNG::SetDisappearTextStyle(frameNode, theme, pickerStyle);
}
void TextStyleImpl(Ark_NativePointer node,
                   const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto pickerStyle = Converter::Convert<PickerTextStyle>(*value);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    TextPickerModelNG::SetNormalTextStyle(frameNode, theme, pickerStyle);
}
void SelectedTextStyleImpl(Ark_NativePointer node,
                           const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto pickerStyle = Converter::Convert<PickerTextStyle>(*value);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    TextPickerModelNG::SetSelectedTextStyle(frameNode, theme, pickerStyle);
}
void OnAcceptImpl(Ark_NativePointer node,
                  const Callback_String_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetOnAccept(frameNode, convValue);
}
void OnCancelImpl(Ark_NativePointer node,
                  const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetOnCancel(frameNode, convValue);
}
void OnChangeImpl(Ark_NativePointer node,
                  const Type_TextPickerAttribute_onChange_callback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onChange =
        [arkCallback = CallbackHelper(*value)](const std::vector<std::string>& values,
                                               const std::vector<double>&selecteds) {
        Converter::ArkArrayHolder<Array_String> stringHolder(values);
        Array_String stringArrayValues = stringHolder.ArkValue();
        auto value = Converter::ArkUnion<Ark_Union_String_Array_String, Array_String>(stringArrayValues);
        std::vector<int32_t> selectedIndexes;
        for (const auto tmp : selecteds) {
            selectedIndexes.push_back(static_cast<int32_t>(tmp));
        }

        Converter::ArkArrayHolder<Array_Number> numberHolder(selectedIndexes);
        Array_Number intArrayValues = numberHolder.ArkValue();
        auto index = Converter::ArkUnion<Ark_Union_Number_Array_Number, Array_Number>(intArrayValues);
        arkCallback.Invoke(value, index);
    };
    TextPickerModelNG::SetOnCascadeChange(frameNode, std::move(onChange));
}
void SelectedIndexImpl(Ark_NativePointer node,
                       const Ark_Union_Number_Array_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    if (TextPickerModelNG::IsSingle(frameNode)) {
        TextPickerInterfaceModifier::SetSingleRange(frameNode, value);
    } else {
        TextPickerInterfaceModifier::SetMultiRange(frameNode, value);
    }
}
void DividerImpl(Ark_NativePointer node,
                 const Opt_DividerOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto dividerParams = Converter::OptConvert<ItemDivider>(*value);

    ItemDivider divider;
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    if (theme) {
        divider.strokeWidth = theme->GetDividerThickness();
        divider.color = theme->GetDividerColor();
    }

    divider.strokeWidth = dividerParams && dividerParams->strokeWidth.IsNonNegative() &&
        dividerParams->strokeWidth.Unit() != DimensionUnit::PERCENT
        ? dividerParams->strokeWidth
        : divider.strokeWidth;
    divider.color = dividerParams ? dividerParams->color : divider.color;
    divider.startMargin = dividerParams && dividerParams->startMargin.IsNonNegative() &&
        dividerParams->startMargin.Unit() != DimensionUnit::PERCENT
        ? dividerParams->startMargin
        : divider.startMargin;
    divider.endMargin = dividerParams && dividerParams->endMargin.IsNonNegative() &&
        dividerParams->endMargin.Unit() != DimensionUnit::PERCENT
        ? dividerParams->endMargin
        : divider.endMargin;

    TextPickerModelNG::SetDivider(frameNode, divider);
}
void GradientHeightImpl(Ark_NativePointer node,
                        const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto heightDimension = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(heightDimension);
    if (heightDimension && heightDimension->ConvertToVp() > 1.0f) {
        heightDimension.reset();
    }
    // need check
    // TextPickerModelNG::SetGradientHeight(frameNode, heightDimension);
}
void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                 const Callback_Union_Number_Array_Number_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const std::vector<double>& index) {
        if (index.size() == 1) {
            auto result = Converter::ArkUnion<Ark_Union_Number_Array_Number, Ark_Number>(index[0]);
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.Invoke(result);
        } else {
            Converter::ArkArrayHolder<Array_Number> arrayHolder(index);
            Array_Number array = arrayHolder.ArkValue();
            auto result = Converter::ArkUnion<Ark_Union_Number_Array_Number, Array_Number>(array);
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.Invoke(result);
        }
    };
    // need check
    // TextPickerModelNG::SetOnSelectedChangeEvent(frameNode, std::move(onEvent));
}
void _onChangeEvent_valueImpl(Ark_NativePointer node,
                              const Callback_Union_String_Array_String_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
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
    // need check
    // TextPickerModelNG::SetOnValueChangeEvent(frameNode, std::move(onEvent));
}
} // TextPickerAttributeModifier
const GENERATED_ArkUITextPickerModifier* GetTextPickerModifier()
{
    static const GENERATED_ArkUITextPickerModifier ArkUITextPickerModifierImpl {
        TextPickerModifier::ConstructImpl,
        TextPickerInterfaceModifier::SetTextPickerOptionsImpl,
        TextPickerAttributeModifier::DefaultPickerItemHeightImpl,
        TextPickerAttributeModifier::CanLoopImpl,
        TextPickerAttributeModifier::DisappearTextStyleImpl,
        TextPickerAttributeModifier::TextStyleImpl,
        TextPickerAttributeModifier::SelectedTextStyleImpl,
        TextPickerAttributeModifier::OnAcceptImpl,
        TextPickerAttributeModifier::OnCancelImpl,
        TextPickerAttributeModifier::OnChangeImpl,
        TextPickerAttributeModifier::SelectedIndexImpl,
        TextPickerAttributeModifier::DividerImpl,
        TextPickerAttributeModifier::GradientHeightImpl,
        TextPickerAttributeModifier::_onChangeEvent_selectedImpl,
        TextPickerAttributeModifier::_onChangeEvent_valueImpl,
    };
    return &ArkUITextPickerModifierImpl;
}

}
