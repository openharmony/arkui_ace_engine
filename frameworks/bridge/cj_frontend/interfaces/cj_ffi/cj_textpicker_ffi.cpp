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
#include "core/pipeline_ng/pipeline_context.h"

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
