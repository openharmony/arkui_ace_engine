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
#include "core/components_ng/pattern/text_picker/textpicker_model_static.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/validators.h"
#include "length_metrics_peer.h"
#include "text_picker_modifier.h"

namespace OHOS::Ace::NG {
namespace Converter {
void AssignArkValue(Ark_ResourceStr &dst, const std::string& src, ConvContext *ctx)
{
    dst = ArkUnion<Ark_ResourceStr, Ark_String>(src, ctx);
}
} // namespace Converter
namespace {
std::optional<Converter::PickerValueType> ProcessBindableValue(FrameNode* frameNode,
    const Opt_Union_ResourceStr_Array_ResourceStr_Bindable_Bindable& value)
{
    std::optional<Converter::PickerValueType> result;
    Converter::VisitUnion(value,
        [&result](const Ark_ResourceStr& src) {
            result = Converter::OptConvert<Converter::PickerValueType>(src);
        },
        [&result](const Array_ResourceStr& src) {
            result = Converter::OptConvert<Converter::PickerValueType>(src);
        },
        [&result, frameNode](const Ark_Bindable_Arkui_Component_Units_ResourceStr& src) {
            result = Converter::OptConvert<Converter::PickerValueType>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](
                    const std::vector<std::string>& value) {
                CHECK_NULL_VOID(value.size());
                Converter::ConvContext ctx;
                auto result = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(value[0], &ctx);
                PipelineContext::SetCallBackNode(weakNode);
                arkCallback.Invoke(result);
            };
            TextPickerModelStatic::SetOnValueChangeEvent(frameNode, std::move(onEvent));
        },
        [&result, frameNode](const Ark_Bindable_Array_Arkui_Component_Units_ResourceStr& src) {
            result = Converter::OptConvert<Converter::PickerValueType>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](
                    const std::vector<std::string>& value) {
                Converter::ConvContext ctx;
                auto result = Converter::ArkValue<Array_ResourceStr>(value, &ctx);
                PipelineContext::SetCallBackNode(weakNode);
                arkCallback.Invoke(result);
            };
            TextPickerModelStatic::SetOnValueChangeEvent(frameNode, std::move(onEvent));
        },
        [] {});
    return result;
}

std::optional<Converter::PickerSelectedType> ProcessBindableSelected(FrameNode* frameNode,
    const Opt_Union_I32_Array_I32_Bindable_Bindable& value)
{
    std::optional<Converter::PickerSelectedType> result;
    Converter::VisitUnion(value,
        [&result](const Ark_Int32& src) {
            result = Converter::OptConvert<Converter::PickerSelectedType>(src);
        },
        [&result](const Array_Int32& src) {
            result = Converter::OptConvert<Converter::PickerSelectedType>(src);
        },
        [&result, frameNode](const Ark_Bindable_I32& src) {
            result = Converter::OptConvert<Converter::PickerSelectedType>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](const std::vector<double>& index) {
                CHECK_NULL_VOID(index.size());
                auto result = Converter::ArkValue<Ark_Int32>(index[0]);
                PipelineContext::SetCallBackNode(weakNode);
                arkCallback.Invoke(result);
            };
            TextPickerModelStatic::SetOnSelectedChangeEvent(frameNode, std::move(onEvent));
        },
        [&result, frameNode](const Ark_Bindable_Array_I32& src) {
            result = Converter::OptConvert<Converter::PickerSelectedType>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](const std::vector<double>& index) {
                Converter::ConvContext ctx;
                auto result = Converter::ArkValue<Array_Int32>(index, &ctx);
                PipelineContext::SetCallBackNode(weakNode);
                arkCallback.Invoke(result);
            };
            TextPickerModelStatic::SetOnSelectedChangeEvent(frameNode, std::move(onEvent));
        },
        [] {});
    return result;
}
} // namespace

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

inline std::vector<Dimension> ParseColumnWidths(const Opt_Array_LengthMetrics& columnWidths)
{
    std::vector<Dimension> result;
    if (columnWidths.tag != 0 && columnWidths.value.array && columnWidths.value.length > 0) {
        result.reserve(static_cast<size_t>(columnWidths.value.length));
        for (auto i = 0; i < columnWidths.value.length; i++) {
            Ark_LengthMetrics lengthMetrics = columnWidths.value.array[i];
            result.emplace_back(Converter::OptConvert<Dimension>(lengthMetrics).value_or(Dimension()));
        }
    }
    return result;
}

TextPickerOptions ConvertOptions(FrameNode *frameNode, const Ark_TextPickerOptions& src)
{
    TextPickerOptions dst;
    auto pickerValueOpt = ProcessBindableValue(frameNode, src.value);
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
    auto pickerSelectedOpt = ProcessBindableSelected(frameNode, src.selected);
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

    // parse the columnWidths' data of TextPickerOptions
    dst.columnWidths = ParseColumnWidths(src.columnWidths);
    return dst;
}

void ProcessCascadeSelected(
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

namespace Converter {
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
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextPickerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = TextPickerModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // TextPickerModifier
namespace TextPickerInterfaceModifier {
void SetSingleRange(FrameNode* frameNode, const Opt_Union_I32_Array_I32* value)
{
    std::vector<OHOS::Ace::NG::RangeContent> rangeResult;
    TextPickerModelStatic::GetSingleRange(frameNode, rangeResult);
    auto indexOpt = Converter::OptConvertPtr<uint32_t>(value);
    uint32_t index = indexOpt.value_or(0);
    if (GreatOrEqual(index, static_cast<int32_t>(rangeResult.size())) || LessNotEqual(index, 0)) {
        index = 0;
    }
    TextPickerModelStatic::SetSelected(frameNode, index);
}
void SetMultiRange(FrameNode* frameNode, const Opt_Union_I32_Array_I32* value)
{
    std::vector<OHOS::Ace::NG::TextCascadePickerOptions> options;
    TextPickerModelStatic::GetMultiOptions(frameNode, options);
    auto count = TextPickerModelStatic::IsCascade(frameNode) ? TextPickerModelStatic::GetMaxCount(frameNode)
                                                             : options.size();

    auto indexesOpt = Converter::OptConvert<std::vector<uint32_t>>(*value);
    std::vector<uint32_t> indexes = indexesOpt.value_or(std::vector<uint32_t>());
    if (TextPickerModelStatic::IsCascade(frameNode)) {
        TextPickerModelStatic::SetHasSelectAttr(frameNode, true);
        ProcessCascadeSelected(options, 0, indexes);
        uint32_t maxCount = TextPickerModelStatic::GetMaxCount(frameNode);
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
    TextPickerModelStatic::SetSelecteds(frameNode, indexes);
}
void SetTextPickerOptionsImpl(Ark_NativePointer node,
                              const Opt_TextPickerOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    auto optOpts = Converter::GetOptPtr(options);
    CHECK_NULL_VOID(optOpts);

    auto textPickerOptions = ConvertOptions(frameNode, *optOpts);
    if (!textPickerOptions.range.empty()) {
        ValidateSingleTextPickerOptions(textPickerOptions);
        //do not change the order of calls
        TextPickerModelStatic::SetTextPickerSingeRange(true);
        TextPickerModelStatic::InitialSetupSinglePicker(frameNode, textPickerOptions.kind);
        TextPickerModelStatic::SetRange(frameNode, textPickerOptions.range);
        TextPickerModelStatic::SetValue(frameNode, textPickerOptions.value);
        TextPickerModelStatic::SetSelected(frameNode, textPickerOptions.selected);
        TextPickerModelStatic::SetColumnWidths(frameNode, textPickerOptions.columnWidths);
    } else if (!textPickerOptions.options.empty()) {
        ValidateMultiTextPickerOptions(textPickerOptions);
        //do not change the order of calls
        TextPickerModelStatic::SetTextPickerSingeRange(false);
        TextPickerModelStatic::SetIsCascade(frameNode, textPickerOptions.isCascade);
        TextPickerModelStatic::SetHasSelectAttr(frameNode, textPickerOptions.hasSelected);
        TextPickerModelStatic::SetColumns(frameNode, textPickerOptions.options);
        TextPickerModelStatic::SetValues(frameNode, textPickerOptions.values);
        TextPickerModelStatic::SetSelecteds(frameNode, textPickerOptions.selecteds);
        TextPickerModelStatic::SetColumnWidths(frameNode, textPickerOptions.columnWidths);
    }
}
} // TextPickerInterfaceModifier
namespace TextPickerAttributeModifier {
void SetDefaultPickerItemHeightImpl(Ark_NativePointer node,
                                    const Opt_Union_F64_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto height = Converter::OptConvertPtr<Dimension>(value);
    TextPickerModelStatic::SetDefaultPickerItemHeight(frameNode, height);
}
void SetCanLoopImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        TextPickerModelStatic::SetCanLoop(frameNode, true);
        return;
    }
    TextPickerModelStatic::SetCanLoop(frameNode, *convValue);
}
void SetDisappearTextStyleImpl(Ark_NativePointer node,
                               const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    auto convValue = Converter::OptConvertPtr<PickerTextStyle>(value);
    TextPickerModelStatic::SetDisappearTextStyle(frameNode, theme, *convValue);
}
void SetTextStyleImpl(Ark_NativePointer node,
                      const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    auto convValue = Converter::OptConvertPtr<PickerTextStyle>(value);
    TextPickerModelStatic::SetNormalTextStyle(frameNode, theme, *convValue);
}
void SetSelectedTextStyleImpl(Ark_NativePointer node,
                              const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    auto convValue = Converter::OptConvertPtr<PickerTextStyle>(value);
    TextPickerModelStatic::SetSelectedTextStyle(frameNode, theme, *convValue);
}
void SetDisableTextStyleAnimationImpl(Ark_NativePointer node,
                                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        TextPickerModelStatic::SetDisableTextStyleAnimation(frameNode, false);
        return;
    }
    TextPickerModelStatic::SetDisableTextStyleAnimation(frameNode, *convValue);
}
void SetDefaultTextStyleImpl(Ark_NativePointer node,
                             const Opt_TextPickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<PickerTextStyle>(value);
    TextPickerModelStatic::SetDefaultTextStyle(frameNode, *convValue);
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_OnTextPickerChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextPickerModelStatic::SetOnCascadeChange(frameNode, nullptr);
        return;
    }
    auto onChange =
        [arkCallback = CallbackHelper(*optValue)](const std::vector<std::string>& values,
            const std::vector<double>& selecteds) {
        Converter::ArkArrayHolder<Array_String> stringHolder(values);
        Array_String stringArrayValues = stringHolder.ArkValue();
        auto value = Converter::ArkUnion<Ark_Union_String_Array_String, Array_String>(stringArrayValues);

        std::vector<int32_t> selectedIndexes;
        for (const auto tmp : selecteds) {
            selectedIndexes.push_back(static_cast<int32_t>(tmp));
        }
        Converter::ArkArrayHolder<Array_Int32> numberHolder(selectedIndexes);
        Array_Int32 intArrayValues = numberHolder.ArkValue();
        if (static_cast<int32_t>(selectedIndexes.size()) == 1) {
            auto singleIndex = Converter::ArkUnion<Ark_Union_I32_Array_I32, Ark_Int32>(
                Converter::ArkValue<Ark_Int32>(selectedIndexes.at(0)));
            arkCallback.Invoke(value, singleIndex);
        } else {
            auto index = Converter::ArkUnion<Ark_Union_I32_Array_I32, Array_Int32>(intArrayValues);
            arkCallback.Invoke(value, index);
        }
    };
    TextPickerModelStatic::SetOnCascadeChange(frameNode, std::move(onChange));
}
void SetOnScrollStopImpl(Ark_NativePointer node,
                         const Opt_TextPickerScrollStopCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextPickerModelStatic::SetOnScrollStop(frameNode, nullptr);
        return;
    }
    auto onScrollStop = [arkCallback = CallbackHelper(*optValue)](const std::vector<std::string>& values,
            const std::vector<double>& selecteds) {
        Array_String stringArrayValues = Converter::ArkValue<Array_String>(values, Converter::FC);
        auto value = Converter::ArkUnion<Ark_Union_String_Array_String, Array_String>(stringArrayValues);

        std::vector<int32_t> selectedIndexes;
        for (const auto tmp : selecteds) {
            selectedIndexes.push_back(static_cast<int32_t>(tmp));
        }
        Array_Int32 intArrayValues = Converter::ArkValue<Array_Int32>(selectedIndexes, Converter::FC);
        if (static_cast<int32_t>(selectedIndexes.size()) == 1) {
            auto singleIndex = Converter::ArkUnion<Ark_Union_I32_Array_I32, Ark_Int32>(
                Converter::ArkValue<Ark_Int32>(selectedIndexes.at(0)));
            arkCallback.Invoke(value, singleIndex);
        } else {
            auto index = Converter::ArkUnion<Ark_Union_I32_Array_I32, Array_Int32>(intArrayValues);
            arkCallback.Invoke(value, index);
        }
    };
    TextPickerModelStatic::SetOnScrollStop(frameNode, std::move(onScrollStop));
}
void SetOnEnterSelectedAreaImpl(Ark_NativePointer node,
                                const Opt_TextPickerEnterSelectedAreaCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextPickerModelStatic::SetOnEnterSelectedArea(frameNode, nullptr);
        return;
    }
    auto onEnterSelectedArea = [arkCallback = CallbackHelper(*optValue)](const std::vector<std::string>& values,
            const std::vector<double>& selecteds) {
        Array_String stringArrayValues = Converter::ArkValue<Array_String>(values, Converter::FC);
        auto value = Converter::ArkUnion<Ark_Union_String_Array_String, Array_String>(stringArrayValues);

        std::vector<int32_t> selectedIndexes;
        for (const auto tmp : selecteds) {
            selectedIndexes.push_back(static_cast<int32_t>(tmp));
        }
        Array_Int32 intArrayValues = Converter::ArkValue<Array_Int32>(selectedIndexes, Converter::FC);
        if (static_cast<int32_t>(selectedIndexes.size()) == 1) {
            auto singleIndex = Converter::ArkUnion<Ark_Union_I32_Array_I32, Ark_Int32>(
                Converter::ArkValue<Ark_Int32>(selectedIndexes.at(0)));
            arkCallback.Invoke(value, singleIndex);
        } else {
            auto index = Converter::ArkUnion<Ark_Union_I32_Array_I32, Array_Int32>(intArrayValues);
            arkCallback.Invoke(value, index);
        }
    };
    TextPickerModelStatic::SetOnEnterSelectedArea(frameNode, std::move(onEnterSelectedArea));
}
void SetSelectedIndexImpl(Ark_NativePointer node,
                          const Opt_Union_I32_Array_I32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (TextPickerModelStatic::IsSingle(frameNode)) {
        TextPickerInterfaceModifier::SetSingleRange(frameNode, value);
    } else {
        TextPickerInterfaceModifier::SetMultiRange(frameNode, value);
    }
}
void SetDividerImpl(Ark_NativePointer node,
                    const Opt_DividerOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto dividerParams = Converter::OptConvertPtr<ItemDivider>(value);

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

    TextPickerModelStatic::SetDivider(frameNode, divider);
}
void SetGradientHeightImpl(Ark_NativePointer node,
                           const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto heightDimension = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(heightDimension);
    if (heightDimension && heightDimension->ConvertToVp() > 1.0f) {
        TextPickerModelStatic::SetGradientHeight(frameNode, heightDimension);
    }
}
void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TextPickerModelStatic::SetEnableHapticFeedback(frameNode, convValue);
}
void SetDigitalCrownSensitivityImpl(Ark_NativePointer node,
                                    const Opt_CrownSensitivity* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<CrownSensitivity>(value);
    TextPickerModelStatic::SetDigitalCrownSensitivity(frameNode, EnumToInt(convValue));
}
} // TextPickerAttributeModifier
const GENERATED_ArkUITextPickerModifier* GetTextPickerModifier()
{
    static const GENERATED_ArkUITextPickerModifier ArkUITextPickerModifierImpl {
        TextPickerModifier::ConstructImpl,
        TextPickerInterfaceModifier::SetTextPickerOptionsImpl,
        TextPickerAttributeModifier::SetDefaultPickerItemHeightImpl,
        TextPickerAttributeModifier::SetCanLoopImpl,
        TextPickerAttributeModifier::SetDisappearTextStyleImpl,
        TextPickerAttributeModifier::SetTextStyleImpl,
        TextPickerAttributeModifier::SetSelectedTextStyleImpl,
        TextPickerAttributeModifier::SetDisableTextStyleAnimationImpl,
        TextPickerAttributeModifier::SetDefaultTextStyleImpl,
        TextPickerAttributeModifier::SetOnChangeImpl,
        TextPickerAttributeModifier::SetOnScrollStopImpl,
        TextPickerAttributeModifier::SetOnEnterSelectedAreaImpl,
        TextPickerAttributeModifier::SetSelectedIndexImpl,
        TextPickerAttributeModifier::SetDividerImpl,
        TextPickerAttributeModifier::SetGradientHeightImpl,
        TextPickerAttributeModifier::SetEnableHapticFeedbackImpl,
        TextPickerAttributeModifier::SetDigitalCrownSensitivityImpl,
    };
    return &ArkUITextPickerModifierImpl;
}

}
