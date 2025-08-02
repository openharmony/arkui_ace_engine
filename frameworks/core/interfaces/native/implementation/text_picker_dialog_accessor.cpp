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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#ifdef ARKUI_CAPI_UNITTEST
#include "test/unittest/capi/stubs/mock_text_picker_dialog_view.h"
#else
#include "core/components_ng/pattern/text_picker/textpicker_dialog_view.h"
#endif
#include "core/interfaces/native/utility/callback_helper.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextPickerDialogAccessor {
void BuildDialogPropertiesCallbacks(const Ark_TextPickerDialogOptions options, DialogProperties& dialogProps)
{
    auto didAppearCallbackOpt = Converter::OptConvert<Callback_Void>(options.onDidAppear);
    if (didAppearCallbackOpt) {
        auto onDidAppear = [arkCallback = CallbackHelper(*didAppearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        dialogProps.onDidAppear = onDidAppear;
    }
    auto didDisappearCallbackOpt = Converter::OptConvert<Callback_Void>(options.onDidDisappear);
    if (didDisappearCallbackOpt) {
        auto onDidDisappear = [arkCallback = CallbackHelper(*didDisappearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        dialogProps.onDidDisappear = onDidDisappear;
    }
    auto willAppearCallbackOpt = Converter::OptConvert<Callback_Void>(options.onWillAppear);
    if (willAppearCallbackOpt) {
        auto onWillAppear = [arkCallback = CallbackHelper(*willAppearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        dialogProps.onWillAppear = onWillAppear;
    }
    auto willDisappearCallbackOpt = Converter::OptConvert<Callback_Void>(options.onWillDisappear);
    if (willDisappearCallbackOpt) {
        auto onWillDisappear = [arkCallback = CallbackHelper(*willDisappearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        dialogProps.onWillDisappear = onWillDisappear;
    }
}
DialogProperties BuildDialogProperties(const Ark_TextPickerDialogOptions options)
{
    DialogProperties dialogProps;
    auto alignment = Converter::OptConvert<DialogAlignment>(options.alignment);
    if (alignment) {
        dialogProps.alignment = alignment.value();
    }
    auto offset = Converter::OptConvert<DimensionOffset>(options.offset);
    if (offset) {
        dialogProps.offset = offset.value();
    }
    dialogProps.backgroundBlurStyle = static_cast<int32_t>(Converter::OptConvert<BlurStyle>(
        options.backgroundBlurStyle).value_or(BlurStyle::COMPONENT_REGULAR));
    dialogProps.backgroundColor = Converter::OptConvert<Color>(options.backgroundColor);
    dialogProps.shadow = Converter::OptConvert<Shadow>(options.shadow);
    auto enableHoverMode = Converter::OptConvert<bool>(options.enableHoverMode);
    if (enableHoverMode) {
        dialogProps.enableHoverMode = enableHoverMode.value();
    }
    auto hoverModeArea = Converter::OptConvert<HoverModeAreaType>(options.hoverModeArea);
    if (hoverModeArea) {
        dialogProps.hoverModeArea = hoverModeArea.value();
    }
    dialogProps.maskRect = Converter::OptConvert<DimensionRect>(options.maskRect);
    BuildDialogPropertiesCallbacks(options, dialogProps);
    return dialogProps;
}
void BuildCascadeSelection(std::vector<NG::TextCascadePickerOptions>& opts,
    TextPickerSettingData& settingData, std::vector<uint32_t> selectedIndexes,
    std::vector<std::string> selectedValues)
{
    if (static_cast<int32_t>(selectedIndexes.size()) > 0) {
        auto tmpOpts = opts;
        for (int i = 0; i < static_cast<int32_t>(selectedIndexes.size()); i++) {
            if (static_cast<int32_t>(tmpOpts.size()) == 0) {
                break;
            }
            auto index = selectedIndexes.at(i);
            if (index >= static_cast<int32_t>(tmpOpts.size()) || index < 0) {
                index = 0;
            }
            settingData.selectedValues.push_back(index);
            settingData.values.push_back(tmpOpts.at(index).rangeResult.at(0));
            tmpOpts = tmpOpts.at(index).children;
        }
    } else if (static_cast<int32_t>(selectedValues.size()) > 0) {
        auto tmpOpts = opts;
        for (int i = 0; i < static_cast<int32_t>(selectedValues.size()); i++) {
            if (static_cast<int32_t>(tmpOpts.size()) == 0) {
                break;
            }
            auto valueStr = selectedValues.at(i);
            auto index = 0;

            auto checkValidValue = (std::find_if(tmpOpts.begin(), tmpOpts.end(),
                [valueStr](TextCascadePickerOptions item) { return item.rangeResult[0] == valueStr; }));
            if (checkValidValue != tmpOpts.end()) {
                index = static_cast<uint32_t>(std::distance(tmpOpts.begin(), checkValidValue));
            }
            if (index >= static_cast<int32_t>(tmpOpts.size()) || index < 0) {
                index = 0;
            }
            settingData.selectedValues.push_back(index);
            settingData.values.push_back(tmpOpts.at(index).rangeResult.at(0));
            tmpOpts = tmpOpts.at(index).children;
        }
    }
}
void CreateRangeWithSelection(const Ark_TextPickerDialogOptions options, TextPickerSettingData& settingData)
{
    std::vector<uint32_t> selectedIndexes;
    auto pickerSelectedOpt = Converter::OptConvert<Converter::PickerSelectedType>(options.selected);
    if (pickerSelectedOpt) {
        auto selectedValue = pickerSelectedOpt.value();
        if (auto selected = std::get_if<uint32_t>(&selectedValue); selected) {
            selectedIndexes.push_back(*selected);
        } else {
            selectedIndexes = std::get<std::vector<uint32_t>>(selectedValue);
        }
    }
    std::vector<std::string> selectedValues;
    auto pickerValueOpt = Converter::OptConvert<Converter::PickerValueType>(options.value);
    if (pickerValueOpt) {
        auto pickerValue = pickerValueOpt.value();
        if (auto value = std::get_if<std::string>(&pickerValue); value) {
            selectedValues.push_back(*value);
        } else {
            selectedValues = std::get<std::vector<std::string>>(pickerValue);
        }
    }

    auto pickerRangeOpt = Converter::OptConvert<PickerRangeType>(options.range);
    if (pickerRangeOpt) {
        auto pickerRange = pickerRangeOpt.value();
        auto rangeVector = std::get_if<std::pair<bool, std::vector<NG::RangeContent>>>(&pickerRange);
        auto optionsVector = std::get_if<std::pair<bool, std::vector<NG::TextCascadePickerOptions>>>(&pickerRange);

        if (rangeVector && (static_cast<int32_t>(rangeVector->second.size()) > 0)) {
            auto range = rangeVector->second;
            settingData.rangeVector = range;

            auto selectedIndex = static_cast<int32_t>(selectedIndexes.size()) > 0 ? selectedIndexes.at(0) : 0;
            if (selectedIndex >= static_cast<int32_t>(range.size()) || selectedIndex < 0) {
                selectedIndex = 0;
            }
            settingData.selected = selectedIndex;
            settingData.selectedValues.push_back(selectedIndex);
        } else if (optionsVector && (static_cast<int32_t>(optionsVector->second.size()) > 0)) {
            auto opts = optionsVector->second;
            settingData.options = opts;
            BuildCascadeSelection(opts, settingData, selectedIndexes, selectedValues);
        }
    }
}
TextPickerSettingData BuildPickerSettingData(const Ark_TextPickerDialogOptions options)
{
    TextPickerSettingData settingData;
    CreateRangeWithSelection(options, settingData);

    auto height = Converter::OptConvert<Dimension>(options.defaultPickerItemHeight);
    if (height) {
        settingData.height = height.value();
    }

    auto canLoop = Converter::OptConvert<bool>(options.canLoop);
    if (canLoop) {
        settingData.canLoop = canLoop.value();
    }

    auto disappearTextStyle = Converter::OptConvert<PickerTextStyle>(options.disappearTextStyle);
    if (disappearTextStyle) {
        settingData.properties.disappearTextStyle_ = disappearTextStyle.value();
    }
    auto textStyle = Converter::OptConvert<PickerTextStyle>(options.textStyle);
    if (textStyle) {
        settingData.properties.normalTextStyle_ = textStyle.value();
    }
    auto selectedTextStyle = Converter::OptConvert<PickerTextStyle>(options.selectedTextStyle);
    if (selectedTextStyle) {
        settingData.properties.selectedTextStyle_ = selectedTextStyle.value();
    }
    return settingData;
}
std::vector<ButtonInfo> BuildButtonInfos(const Ark_TextPickerDialogOptions options)
{
    std::vector<ButtonInfo> buttonInfos;
    auto acceptButtonInfo = Converter::OptConvert<ButtonInfo>(options.acceptButtonStyle);
    if (acceptButtonInfo.has_value()) {
        buttonInfos.push_back(acceptButtonInfo.value());
    }
    auto cancelButtonInfo = Converter::OptConvert<ButtonInfo>(options.cancelButtonStyle);
    if (cancelButtonInfo.has_value()) {
        buttonInfos.push_back(cancelButtonInfo.value());
    }
    return buttonInfos;
}
DialogTextEvent BuildTextEvent(Callback_TextPickerResult_Void callback)
{
    return [arkCallback = CallbackHelper(callback)](const std::string& info) -> void {
        Ark_TextPickerResult textPickerRes;
        auto data = JsonUtil::ParseJsonString(info);

        std::vector<uint32_t> indexes;
        auto jsonIndex = data->GetValue("index");
        auto isIndexesArray = jsonIndex->IsArray();
        if (isIndexesArray) {
            for (auto i = 0; i < jsonIndex->GetArraySize(); i++) {
                indexes.push_back(jsonIndex->GetArrayItem(i)->GetUInt());
            }
        } else {
            indexes.push_back(jsonIndex->GetUInt());
        }
        Converter::ArkArrayHolder<Array_Number> indexesHolder(indexes);
        if (isIndexesArray) {
            Array_Number arkValues = indexesHolder.ArkValue();
            textPickerRes.index = Converter::ArkUnion<Ark_Union_Number_Array_Number, Array_Number>(arkValues);
        } else if (static_cast<int32_t>(indexes.size()) > 0) {
            textPickerRes.index = Converter::ArkUnion<Ark_Union_Number_Array_Number, Ark_Number>(
                Converter::ArkValue<Ark_Number>(indexes.at(0)));
        }

        std::vector<std::string> values;
        auto jsonValue = data->GetValue("value");
        auto isValuesArray = jsonValue->IsArray();
        if (isValuesArray) {
            for (auto i = 0; i < jsonValue->GetArraySize(); i++) {
                values.push_back(jsonValue->GetArrayItem(i)->GetString());
            }
        } else {
            values.push_back(data->GetString("value"));
        }
        Converter::ArkArrayHolder<Array_String> holder(values);
        if (isValuesArray) {
            Array_String arkValues = holder.ArkValue();
            textPickerRes.value = Converter::ArkUnion<Ark_Union_String_Array_String, Array_String>(arkValues);
        } else if (static_cast<int32_t>(values.size()) > 0) {
            textPickerRes.value = Converter::ArkUnion<Ark_Union_String_Array_String, Ark_String>(
                Converter::ArkValue<Ark_String>(values.at(0)));
        }

        arkCallback.Invoke(textPickerRes);
    };
}
void ShowImpl(const Opt_TextPickerDialogOptions* options)
{
    CHECK_NULL_VOID(options);
    auto arkOptionsOpt = Converter::OptConvert<Ark_TextPickerDialogOptions>(*options);
    if (!arkOptionsOpt.has_value()) { return; }

    Ark_TextPickerDialogOptions arkOptions = arkOptionsOpt.value();
    DialogProperties dialogProps = BuildDialogProperties(arkOptions);
    TextPickerSettingData settingData = BuildPickerSettingData(arkOptions);
    std::vector<ButtonInfo> buttonInfos = BuildButtonInfos(arkOptions);

    std::map<std::string, DialogTextEvent> dialogEvent;
    auto acceptCallbackOpt = Converter::OptConvert<Callback_TextPickerResult_Void>(arkOptions.onAccept);
    if (acceptCallbackOpt) {
        dialogEvent["acceptId"] = BuildTextEvent(*acceptCallbackOpt);
    }
    auto changeCallbackOpt = Converter::OptConvert<Callback_TextPickerResult_Void>(arkOptions.onChange);
    if (changeCallbackOpt) {
        dialogEvent["changeId"] = BuildTextEvent(*changeCallbackOpt);
    }

    std::map<std::string, DialogGestureEvent> dialogCancelEvent;
    auto cancelCallbackOpt = Converter::OptConvert<Callback_Void>(arkOptions.onCancel);
    if (cancelCallbackOpt) {
        auto onCancelFunc = [arkCallback = CallbackHelper(*cancelCallbackOpt)](const GestureEvent& info) -> void {
            arkCallback.Invoke();
        };
        dialogCancelEvent["cancelId"] = onCancelFunc;
    }
#ifndef ARKUI_CAPI_UNITTEST
    TextPickerDialogView::Show(dialogProps, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
#else
    MockTextPickerDialogView::Show(dialogProps, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
#endif
}
} // TextPickerDialogAccessor
const GENERATED_ArkUITextPickerDialogAccessor* GetTextPickerDialogAccessor()
{
    static const GENERATED_ArkUITextPickerDialogAccessor TextPickerDialogAccessorImpl {
        TextPickerDialogAccessor::ShowImpl,
    };
    return &TextPickerDialogAccessorImpl;
}

}
