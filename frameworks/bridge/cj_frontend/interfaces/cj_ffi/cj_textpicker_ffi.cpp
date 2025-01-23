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
    auto cancelId = [result](const GestureEvent&) {
        result();
    };
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
        [properties, settingData, dialogEvent, cancelEvent,
            weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            overlayManager->ShowTextDialog(properties, settingData, dialogEvent, cancelEvent);
        },
        TaskExecutor::TaskType::UI, "CJTextPickerDialogShow");
}
} // namespace OHOS::Ace

extern "C" {
VectorRangeContentHandle FFICJVectorCreateRangeContent(int64_t size)
{
    return new std::vector<CJRangeContent>(size);
}

void FFICJVectorRangeContentDelete(VectorRangeContentHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<CJRangeContent>*>(vec);
    delete actualVec;
}

void FFICJVectorRangeContentSetElement(
    VectorRangeContentHandle vec, int64_t index, CJRangeContent rangeContentOptions)
{
    auto actualVec = reinterpret_cast<std::vector<CJRangeContent>*>(vec);
    (*actualVec)[index] = rangeContentOptions;
}

VectorTextCascadePickerOptionsHandle FFICJVectorCreateTextCascadePickerOptions(int64_t size)
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

void FfiOHOSAceFrameworkTextPickerCreate(ParseTextArrayParam params)
{
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    bool firstBuild = targetNode && targetNode->IsFirstBuilding();
    if (!firstBuild) {
        return;
    }
    
    // auto actualVec = reinterpret_cast<std::vector<std::string>*>(vecContent);
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    if (!param.result.empty()) {
        TextPickerModel::GetInstance()->SetSingleRange(true);
        FfiOHOSAceFrameworkTextPickerCreateSingle(theme, param);
    } else {
        FfiOHOSAceFrameworkTextPickerCreateMulti(theme, optionsAttr, param);
    }
    WeakPtr<NG::FrameNode> targetNode =
            AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());        
        auto valuechangeEvent = [lambda = CJLambda::Create(param.valueChangeEvent), node = targetNode](const std::string& value) -> void {
            LOGI("FfiOHOSAceFrameworkRefreshCreateWithChangeEvent value is %{public}s", value.c_str());
            PipelineContext::SetCallBackNode(node);
            bool newValue = value == "true";
            lambda(newValue);
        };
        auto selectedchangeEvent = [lambda = CJLambda::Create(param.selectedChangeEvent), node = targetNode](const std::string& value) -> void {
            LOGI("FfiOHOSAceFrameworkRefreshCreateWithChangeEvent value is %{public}s", value.c_str());
            PipelineContext::SetCallBackNode(node);
            bool newValue = value == "true";
            lambda(newValue);
        };   
    TextPickerModel::GetInstance()->SetOnValueChangeEvent(std::move(valuechangeEvent));
    TextPickerModel::GetInstance()->SetOnSelectedChangeEvent(std::move(selectedchangeEvent));   
    return;
}

void FfiOHOSAceFrameworkTextPickerCreateSingle(const RefPtr<PickerTheme>& theme, ParseTextArrayParam& param)
{
    TextPickerModel::GetInstance()->Create(theme, param.kind);
    TextPickerModel::GetInstance()->SetRange(param.result);
    TextPickerModel::GetInstance()->SetSelected(param.selected);
    TextPickerModel::GetInstance()->SetValue(param.value);
    TextPickerModel::GetInstance()->SetDefaultAttributes(theme);
}

void FfiOHOSAceFrameworkTextPickerCreateMulti(const RefPtr<PickerTheme>& theme, ParseTextArrayParam& param)
{
    TextPickerModel::GetInstance()->MultiInit(theme);
    TextPickerModel::GetInstance()->SetValues(param.values);
    TextPickerModel::GetInstance()->SetSelecteds(param.selecteds);
    TextPickerModel::GetInstance()->SetIsCascade(param.isCascade);
    TextPickerModel::GetInstance()->SetHasSelectAttr(param.isHasSelectAttr);
    TextPickerModel::GetInstance()->SetColumns(param.options);
    TextPickerModel::GetInstance()->SetDefaultAttributes(theme);
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

void FfiOHOSAceFrameworkTextPickerSetTextStyle(uint32_t color, double size, int32_t unit,
    const char* weight, const char* family, uint32_t style)
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

void FfiOHOSAceFrameworkTextPickerSetDisappearTextStyle(uint32_t color, double size, int32_t unit,
    const char* weight, const char* family, uint32_t style)
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

void FfiOHOSAceFrameworkTextPickerSetSelectedTextStyle(uint32_t color, double size, int32_t unit,
    const char* weight, const char* family, uint32_t style)
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
    const auto& indexarray = * reinterpret_cast<std::vector<uint32_t>*>(values);
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
}
