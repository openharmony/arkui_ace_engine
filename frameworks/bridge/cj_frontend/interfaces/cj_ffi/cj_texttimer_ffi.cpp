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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_texttimer_ffi.h"

#include "cj_lambda.h"
#include "bridge/common/utils/utils.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::Framework {

NativeTextTimerController::NativeTextTimerController() : FFIData()
{
    LOGI("Native TextAreaController constructed: %{public}" PRId64, GetID());
}

void NativeTextTimerController::Start()
{
    if (controller_) {
        controller_->Start();
    }
}

void NativeTextTimerController::Pause()
{
    if (controller_) {
        controller_->Pause();
    }
}

void NativeTextTimerController::Reset()
{
    if (controller_) {
        controller_->Reset();
    }
}

namespace {
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
constexpr double MAX_COUNT_DOWN = 86400000.0;
} // namespace

} // namespace OHOS::Ace::Framework

extern "C" {
void FfiOHOSAceFrameworkTextTimerCreate(bool isCountDown, int64_t count, int64_t controllerId)
{
    auto textTimer = TextTimerModel::GetInstance()->Create();

    TextTimerModel::GetInstance()->SetIsCountDown(isCountDown);
    if (isCountDown) {
        if (count > 0 && count < MAX_COUNT_DOWN) {
            TextTimerModel::GetInstance()->SetInputCount(count);
        } else {
            LOGE("Parameter out of range, use default value.");
        }
    }

    auto controller = FFIData::GetData<NativeTextTimerController>(controllerId);
    if (controller != nullptr) {
        controller->SetController(textTimer);
    } else {
        LOGE("textTimerControllerId is invalid ");
    }
}

void FfiOHOSAceFrameworkTextTimerSetFormat(const char* value)
{
    std::string valueString = static_cast<std::string>(value);
    std::regex pattern(
        R"(^([Yy]*[_|\W\s]*[M]*[_|\W\s]*[d]*[_|\W\s]*[D]*[_|\W\s]*[Hh]*[_|\W\s]*[m]*[_|\W\s]*[s]*[_|\W\s]*[S]*)$)");
    if (!std::regex_match(value, pattern)) {
        LOGE("The arg is wrong, because of format matching error.");
        return;
    }
    TextTimerModel::GetInstance()->SetFormat(valueString);
}

void FfiOHOSAceFrameworkTextTimerSetFontSize(double fontSize, int32_t unit)
{
    Dimension value(fontSize, static_cast<DimensionUnit>(unit));
    TextTimerModel::GetInstance()->SetFontSize(value);
}

void FfiOHOSAceFrameworkTextTimerSetFontWeight(const char* fontWeight)
{
    TextTimerModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(fontWeight));
}

void FfiOHOSAceFrameworkTextTimerSetFontColor(uint32_t textColor)
{
    TextTimerModel::GetInstance()->SetTextColor(Color(textColor));
}

void FfiOHOSAceFrameworkTextTimerSetFontStyle(int32_t fontStyle)
{
    if (!Utils::CheckParamsValid(fontStyle, FONT_STYLES.size())) {
        LOGE("invalid value for font style");
        return;
    }
    TextTimerModel::GetInstance()->SetItalicFontStyle(FONT_STYLES[fontStyle]);
}

void FfiOHOSAceFrameworkTextTimerSetFontFamily(const char* fontFamily)
{
    std::vector<std::string> fontFamilies;
    fontFamilies = ConvertStrToFontFamilies(fontFamily);
    TextTimerModel::GetInstance()->SetFontFamily(fontFamilies);
}

void FfiOHOSAceFrameworkTextTimerSetOnTimer(void (*callback)(int64_t utc, int64_t elapsedTime))
{
    auto lambda = [lambda = CJLambda::Create(callback)](const long utc,
                      const long elapsedTime) -> void { lambda(utc, elapsedTime); };
    TextTimerModel::GetInstance()->SetOnTimer(lambda);
}

int64_t FfiOHOSAceFrameworkTextTimerControllerCtor()
{
    auto controller = FFIData::Create<NativeTextTimerController>();
    if (controller == nullptr) {
        return FFI_ERROR_CODE;
    }
    return controller->GetID();
}

void FfiOHOSAceFrameworkTextTimerControllerStart(int64_t selfID)
{
    auto self = FFIData::GetData<NativeTextTimerController>(selfID);
    if (self != nullptr) {
        self->Start();
    } else {
        LOGE("FfiTextArea: invalid textTimerController");
    }
}

void FfiOHOSAceFrameworkTextTimerControllerPause(int64_t selfID)
{
    auto self = FFIData::GetData<NativeTextTimerController>(selfID);
    if (self != nullptr) {
        self->Pause();
    } else {
        LOGE("FfiTextArea: invalid textTimerController");
    }
}

void FfiOHOSAceFrameworkTextTimerControllerReset(int64_t selfID)
{
    auto self = FFIData::GetData<NativeTextTimerController>(selfID);
    if (self != nullptr) {
        self->Reset();
    } else {
        LOGE("FfiTextArea: invalid textTimerController");
    }
}
}