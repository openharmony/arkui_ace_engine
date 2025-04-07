/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_textpicker_ffi.h"

#include "cj_lambda.h"

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace {
std::map<std::string, NG::DialogTextEvent> TextPickerDialogEvent(
    std::function<void(CJTextPickerResult)> accept, std::function<void(CJTextPickerResult)> change)
{
    std::map<std::string, NG::DialogTextEvent> dialogEvent;
    auto acceptId = [accept](const std::string& info) {
        std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(info);
        if (!argsPtr) {
            LOGW("Parse param failed!");
            return;
        }
        const auto value = argsPtr->GetValue("value");
        const auto index = argsPtr->GetValue("index");
        CJTextPickerResult ffiClickInfo {};
        if (value->IsString()) {
            ffiClickInfo.value = value->GetString().c_str();
        } else {
            LOGW("context value not existed");
        }
        if (index->IsNumber()) {
            ffiClickInfo.index = index->GetUInt();
        } else {
            LOGW("context index not existed");
        }
        accept(ffiClickInfo);
    };
    dialogEvent["acceptId"] = acceptId;
    auto changeId = [change](const std::string& info) {
        std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(info);
        if (!argsPtr) {
            LOGW("Parse param failed!");
            return;
        }
        const auto value = argsPtr->GetValue("value");
        const auto index = argsPtr->GetValue("index");
        CJTextPickerResult ffiClickInfo {};
        if (value->IsString()) {
            ffiClickInfo.value = value->GetString().c_str();
        } else {
            LOGW("context value not existed");
        }
        if (index->IsNumber()) {
            ffiClickInfo.index = index->GetUInt();
        } else {
            LOGW("context index not existed");
        }
        change(ffiClickInfo);
    };
    dialogEvent["changeId"] = changeId;
    return dialogEvent;
}

std::map<std::string, NG::DialogGestureEvent> TextPickerCancelEvent(std::function<void()> result)
{
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    auto cancelId = [result](const GestureEvent&) { result(); };
    dialogCancelEvent["cancelId"] = cancelId;
    return dialogCancelEvent;
}

void TextPickerDialogShow(std::vector<std::string> range, uint32_t selected, const Dimension& height,
    const std::map<std::string, NG::DialogTextEvent>& dialogEvent,
    const std::map<std::string, NG::DialogGestureEvent>& cancelEvent)
{
    auto currentObj = Container::Current();
    if (!currentObj) {
        LOGE("container is non-valid");
        return;
    }
    auto pipelineContext = AccessibilityManager::DynamicCast<NG::PipelineContext>(currentObj->GetPipelineContext());
    if (!pipelineContext) {
        LOGE("pipeline context is non-valid");
        return;
    }
    auto executor = pipelineContext->GetTaskExecutor();
    if (!executor) {
        LOGE("task executor is non-valid");
        return;
    }
    auto theme = GetTheme<DialogTheme>();
    DialogProperties properties;
    NG::TextPickerSettingData settingData;

    settingData.selected = selected;
    settingData.height = height;
    settingData.values = range;

    if (SystemProperties::GetDeviceType() == DeviceType::PHONE) {
        properties.alignment = DialogAlignment::BOTTOM;
    } else {
        properties.alignment = DialogAlignment::CENTER;
    }
    properties.customStyle = false;
    properties.offset = DimensionOffset(Offset(0, -theme->GetMarginBottom().ConvertToPx()));

    auto context = AccessibilityManager::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    executor->PostTask(
        [properties, settingData, dialogEvent, cancelEvent, weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            overlayManager->ShowTextDialog(properties, settingData, dialogEvent, cancelEvent);
        },
        TaskExecutor::TaskType::UI, "CJTextPickerDialogShow");
}
} // namespace OHOS::Ace

extern "C" {
VectorRangeContentHandle FFICJCreateVectorRangeContent(int64_t size)
{
    return new std::vector<CJRangeContent>(size);
}

void FFICJVectorRangeContentDelete(VectorRangeContentHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<CJRangeContent>*>(vec);
    delete actualVec;
}

void FFICJVectorRangeContentSetElement(VectorRangeContentHandle vec, int64_t index, CJRangeContent rangeContentOptions)
{
    auto actualVec = reinterpret_cast<std::vector<CJRangeContent>*>(vec);
    (*actualVec)[index] = rangeContentOptions;
}

VectorTextCascadePickerOptionsHandle FFICJVectorTextCascadePickerOptions(int64_t size)
{
    return new std::vector<CJTextCascadePickerOptions>(size);
}

void FFICJVectorTextCascadePickerOptionsDelete(VectorTextCascadePickerOptionsHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<CJTextCascadePickerOptions>*>(vec);
    delete actualVec;
}

void FFICJVectorTextCascadePickerOptionsSetElement(
    VectorTextCascadePickerOptionsHandle vec, int64_t index, CJTextCascadePickerOptions textCascadeOptions)
{
    auto actualVec = reinterpret_cast<std::vector<CJTextCascadePickerOptions>*>(vec);
    (*actualVec)[index] = textCascadeOptions;
}

void FfiOHOSAceFrameworkTextPickerCreate(VectorStringPtr vecContent, uint32_t selected, const char* value)
{
    auto actualVec = reinterpret_cast<std::vector<std::string>*>(vecContent);
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    uint32_t kind = NG::TEXT;
    TextPickerModel::GetInstance()->SetSingleRange(true);

    std::vector<NG::RangeContent> result;

    for (const auto& text : *actualVec) {
        NG::RangeContent content;
        content.icon_ = "";
        content.text_ = text;
        result.emplace_back(content);
    }

    TextPickerModel::GetInstance()->Create(theme, kind);
    TextPickerModel::GetInstance()->SetRange(result);
    TextPickerModel::GetInstance()->SetSelected(selected);
    TextPickerModel::GetInstance()->SetValue(value);
    TextPickerModel::GetInstance()->SetDefaultAttributes(theme);

    return;
}

void FfiOHOSAceFrameworkTextPickerCreateSingle(CJTextArrayParamSingle params)
{
    const auto& actualVec = reinterpret_cast<std::vector<std::string>*>(params.result);
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    TextPickerModel::GetInstance()->SetDefaultAttributes(theme);

    std::vector<NG::RangeContent> result;

    for (const auto& text : *actualVec) {
        NG::RangeContent content;
        content.icon_ = "";
        content.text_ = text;
        result.emplace_back(content);
    }

    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto selectedchangeEvent = [lambda = CJLambda::Create(params.selectedChangeEvent), node = targetNode](
                                   const std::vector<double>& value) -> void {
        PipelineContext::SetCallBackNode(node);
        lambda(static_cast<uint32_t>(value[0]));
    };
    auto valuechangeEvent = [lambda = CJLambda::Create(params.valueChangeEvent), node = targetNode](
                                const std::vector<std::string>& value) -> void {
        PipelineContext::SetCallBackNode(node);
        lambda(value[0].c_str());
    };

    TextPickerModel::GetInstance()->SetSingleRange(true);
    TextPickerModel::GetInstance()->Create(theme, params.kind);
    TextPickerModel::GetInstance()->SetRange(result);
    TextPickerModel::GetInstance()->SetSelected(params.selected);
    TextPickerModel::GetInstance()->SetValue(params.value);
    TextPickerModel::GetInstance()->HasUserDefinedOpacity();
    TextPickerModel::GetInstance()->SetOnValueChangeEvent(std::move(valuechangeEvent));
    TextPickerModel::GetInstance()->SetOnSelectedChangeEvent(std::move(selectedchangeEvent));
}

void FfiOHOSAceFrameworkTextPickerCreateMulti(CJTextArrayParamMulti params)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    TextPickerModel::GetInstance()->SetDefaultAttributes(theme);
    TextPickerModel::GetInstance()->MultiInit(theme);

    const auto& valuesVec = reinterpret_cast<std::vector<std::string>*>(params.values);
    const auto& selectedVec = reinterpret_cast<std::vector<std::uint32_t>*>(params.selecteds);
    const auto& optionsVec = reinterpret_cast<std::vector<CJTextCascadePickerOptions>*>(params.options);

    std::vector<NG::TextCascadePickerOptions> options;
    for (const auto& content : *optionsVec) {
        NG::TextCascadePickerOptions option;
        option.rangeResult = *reinterpret_cast<std::vector<std::string>*>(content.rangeResult);
        options.emplace_back(option);
    }

    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto selectedchangeEvent = [lambda = CJLambda::Create(params.selectedsChangeEvent), node = targetNode](
                                   const std::vector<double>& value) -> void {
        PipelineContext::SetCallBackNode(node);
        std::vector<uint32_t> transSelelceds;
        for (const auto& val : value) {
            transSelelceds.push_back(static_cast<uint32_t>(val));
        }
        lambda(&transSelelceds);
        LOGI("bind selectedchangeEvent success");
    };
    auto valuechangeEvent = [lambda = CJLambda::Create(params.valuesChangeEvent), node = targetNode](
                                const std::vector<std::string>& value) -> void {
        PipelineContext::SetCallBackNode(node);
        auto transValues = new std::vector<std::string>();
        for (const auto& val : value) {
            transValues->push_back(val);
        }
        lambda(reinterpret_cast<VectorStringPtr>(transValues));
        LOGI("bind valuechangeEvent success");
        delete transValues;
    };

    TextPickerModel::GetInstance()->SetSelecteds(*selectedVec);
    TextPickerModel::GetInstance()->SetValues(*valuesVec);
    TextPickerModel::GetInstance()->SetIsCascade(params.isCascade);
    TextPickerModel::GetInstance()->SetHasSelectAttr(params.isHasSelectAttr);
    TextPickerModel::GetInstance()->SetColumns(options);
    TextPickerModel::GetInstance()->HasUserDefinedOpacity();
    TextPickerModel::GetInstance()->SetOnValueChangeEvent(std::move(valuechangeEvent));
    TextPickerModel::GetInstance()->SetOnSelectedChangeEvent(std::move(selectedchangeEvent));
}

void generateCascadeOptions(
    const std::vector<CJTextCascadePickerOptions>& optionsvec, std::vector<NG::TextCascadePickerOptions>& options)
{
    if (optionsvec.empty()) {
        return;
    }
    for (const CJTextCascadePickerOptions& content : optionsvec) {
        NG::TextCascadePickerOptions option;
        option.rangeResult = *reinterpret_cast<std::vector<std::string>*>(content.rangeResult);
        auto temp = reinterpret_cast<std::vector<CJTextCascadePickerOptions>*>(content.children);
        if (temp != nullptr) {
            generateCascadeOptions(*temp, option.children);
        }
        options.emplace_back(option);
    }
}

void FfiOHOSAceFrameworkTextPickerCreateCascade(CJTextArrayParamMulti params)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    TextPickerModel::GetInstance()->SetDefaultAttributes(theme);
    TextPickerModel::GetInstance()->MultiInit(theme);

    const auto& valuesVec = reinterpret_cast<std::vector<std::string>*>(params.values);
    const auto& selectedVec = reinterpret_cast<std::vector<std::uint32_t>*>(params.selecteds);
    const auto& optionsVec = reinterpret_cast<std::vector<CJTextCascadePickerOptions>*>(params.options);

    std::vector<NG::TextCascadePickerOptions> options;

    generateCascadeOptions(*optionsVec, options);

    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto selectedchangeEvent = [lambda = CJLambda::Create(params.selectedsChangeEvent), node = targetNode](
                                   const std::vector<double>& value) -> void {
        PipelineContext::SetCallBackNode(node);
        std::vector<uint32_t> transSelelceds;
        for (const auto& val : value) {
            transSelelceds.push_back(static_cast<uint32_t>(val));
        }
        lambda(&transSelelceds);
        LOGI("bind selectedchangeEvent success");
    };
    auto valuechangeEvent = [lambda = CJLambda::Create(params.valuesChangeEvent), node = targetNode](
                                const std::vector<std::string>& value) -> void {
        PipelineContext::SetCallBackNode(node);
        auto transValues = new std::vector<std::string>();
        for (const auto& val : value) {
            transValues->push_back(val);
        }
        lambda(reinterpret_cast<VectorStringPtr>(transValues));
        LOGI("bind valuechangeEvent success");
        delete transValues;
    };

    TextPickerModel::GetInstance()->SetSelecteds(*selectedVec);
    TextPickerModel::GetInstance()->SetValues(*valuesVec);
    TextPickerModel::GetInstance()->SetIsCascade(params.isCascade);
    TextPickerModel::GetInstance()->SetHasSelectAttr(params.isHasSelectAttr);
    TextPickerModel::GetInstance()->SetColumns(options);
    TextPickerModel::GetInstance()->HasUserDefinedOpacity();
    TextPickerModel::GetInstance()->SetOnValueChangeEvent(std::move(valuechangeEvent));
    TextPickerModel::GetInstance()->SetOnSelectedChangeEvent(std::move(selectedchangeEvent));
}

void FfiOHOSAceFrameworkTextPickerSetDefaultPickerItemHeight(double height, int32_t unit)
{
    Dimension heightDime(height, static_cast<DimensionUnit>(unit));
    TextPickerModel::GetInstance()->SetDefaultPickerItemHeight(heightDime);
    return;
}

void FfiOHOSAceFrameworkTextPickerSetCanLoop(bool value)
{
    TextPickerModel::GetInstance()->SetCanLoop(value);
}

void FfiOHOSAceFrameworkTextPickerSetTextStyle(
    uint32_t color, double size, int32_t unit, const char* weight, const char* family, uint32_t style)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle textStyle;

    textStyle.textColor = Color(color);
    CalcDimension fontSize = CalcDimension(size, DimensionUnit(unit));
    textStyle.fontSize = fontSize;

    std::string weightVal = weight;
    textStyle.fontWeight = ConvertStrToFontWeight(weightVal);

    std::string familyVal = family;
    textStyle.fontFamily = ConvertStrToFontFamilies(familyVal);
    textStyle.fontStyle = static_cast<FontStyle>(style);

    TextPickerModel::GetInstance()->SetNormalTextStyle(theme, textStyle);
}

void FfiOHOSAceFrameworkTextPickerSetDisappearTextStyle(
    uint32_t color, double size, int32_t unit, const char* weight, const char* family, uint32_t style)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle textStyle;

    textStyle.textColor = Color(color);
    CalcDimension fontSize = CalcDimension(size, DimensionUnit(unit));
    textStyle.fontSize = fontSize;

    std::string weightVal = weight;
    textStyle.fontWeight = ConvertStrToFontWeight(weightVal);

    std::string familyVal = family;
    textStyle.fontFamily = ConvertStrToFontFamilies(familyVal);
    textStyle.fontStyle = static_cast<FontStyle>(style);

    TextPickerModel::GetInstance()->SetDisappearTextStyle(theme, textStyle);
}

void FfiOHOSAceFrameworkTextPickerSetSelectedTextStyle(
    uint32_t color, double size, int32_t unit, const char* weight, const char* family, uint32_t style)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle textStyle;

    textStyle.textColor = Color(color);
    CalcDimension fontSize = CalcDimension(size, DimensionUnit(unit));
    textStyle.fontSize = fontSize;

    std::string weightVal = weight;
    textStyle.fontWeight = ConvertStrToFontWeight(weightVal);

    std::string familyVal = family;
    textStyle.fontFamily = ConvertStrToFontFamilies(familyVal);
    textStyle.fontStyle = static_cast<FontStyle>(style);

    TextPickerModel::GetInstance()->SetSelectedTextStyle(theme, textStyle);
}

void FfiOHOSAceFrameworkTextPickerSetGradientHeight(double length, int32_t unit)
{
    Dimension gradientDime(length, static_cast<DimensionUnit>(unit));
    TextPickerModel::GetInstance()->SetGradientHeight(gradientDime);
}

void FfiOHOSAceFrameworkTextPickerSetDivider(DividerParams params)
{
    Dimension widthDime(params.width, static_cast<DimensionUnit>(params.widthUnit));
    Dimension startMarginDime(params.startMargin, static_cast<DimensionUnit>(params.startMarginUnit));
    Dimension endMarginDime(params.endMargin, static_cast<DimensionUnit>(params.endMarginUnit));

    NG::ItemDivider divider;
    divider.strokeWidth = widthDime;
    divider.color = Color(params.color);
    divider.startMargin = startMarginDime;
    divider.endMargin = endMarginDime;

    TextPickerModel::GetInstance()->SetDivider(divider);
}

void FfiOHOSAceFrameworkTextPickerSetSelectedIndexSingle(uint32_t value)
{
    TextPickerModel::GetInstance()->SetSelected(value);
}

void FfiOHOSAceFrameworkTextPickerSetSelectedIndexMulti(VectorUInt32Handle values)
{
    const auto& indexarray = *reinterpret_cast<std::vector<uint32_t>*>(values);
    TextPickerModel::GetInstance()->SetSelecteds(indexarray);
}

void FfiOHOSAceFrameworkTextPickerOnChange(void (*callback)(CJTextPickerResult pickerResult))
{
    auto onChange = [lambda = CJLambda::Create(callback)](
                        const std::vector<std::string>& value, const std::vector<double>& index) -> void {
        CJTextPickerResult ffiClickInfo {};
        ffiClickInfo.value = value[0].c_str();
        ffiClickInfo.index = index[0];
        lambda(ffiClickInfo);
    };

    TextPickerModel::GetInstance()->SetOnCascadeChange(std::move(onChange));
    return;
}

void FfiOHOSAceFrameworkTextPickerDialogShow(VectorStringPtr vecContent, CJDialogShow value)
{
    auto actualVec = reinterpret_cast<std::vector<std::string>*>(vecContent);
    Dimension itemHeight(value.height, static_cast<DimensionUnit>(value.heightUnit));

    auto dialogEvent = TextPickerDialogEvent(CJLambda::Create(value.accept), CJLambda::Create(value.change));
    auto cancelEvent = TextPickerCancelEvent(CJLambda::Create(value.cancel));
    TextPickerDialogShow(*actualVec, value.selected, itemHeight, dialogEvent, cancelEvent);
    return;
}

void FfiOHOSAceFrameworkTextPickerSetOpacity(double opacity)
{
    ViewAbstractModel::GetInstance()->SetOpacity(opacity);
    TextPickerModel::GetInstance()->HasUserDefinedOpacity();
}
}
