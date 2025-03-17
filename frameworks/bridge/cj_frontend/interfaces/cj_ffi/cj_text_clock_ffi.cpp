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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_text_clock_ffi.h"

#include "cj_lambda.h"
#include "bridge/common/utils/utils.h"
#include "core/components/common/properties/text_style_parser.h"


using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::Framework {

namespace {
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::string DEFAULT_FORMAT_API_ELEVEN = "aa hh:mm:ss";
const std::string DEFAULT_FORMAT_API_TEN = "hms";
const std::string TEXTCLOCK_DATE_TIME_OPTIONS_TWO_DIGIT_VAL = "2-digit";
const std::string TEXTCLOCK_DATE_TIME_OPTIONS_NUMERIC_VAL = "numeric";
} // namespace

NativeTextClockController::NativeTextClockController() : FFIData()
{
    LOGI("Native TextAreaController constructed: %{public}" PRId64, GetID());
}

void NativeTextClockController::Start()
{
    if (controller_) {
        controller_->Start();
    }
}

void NativeTextClockController::Stop()
{
    if (controller_) {
        controller_->Stop();
    }
}

namespace {
constexpr int32_t TWENTY_FOUR_HOUR_BASE = 24;
constexpr int32_t HOURS_WEST_LOWER_LIMIT = -14;
constexpr int32_t HOURS_WEST_UPPER_LIMIT = 12;
constexpr int32_t HOURS_WEST_GEOGRAPHICAL_LOWER_LIMIT = -12;
constexpr float HOURS_WEST[] = {9.5f, 3.5f, -3.5f, -4.5f, -5.5f, -5.75f, -6.5f, -9.5f, -10.5f, -12.75f};

bool HoursWestIsValid_(int32_t hoursWest)
{
    if (hoursWest < HOURS_WEST_LOWER_LIMIT || hoursWest > HOURS_WEST_UPPER_LIMIT) {
        return false;
    }
    if (hoursWest < HOURS_WEST_GEOGRAPHICAL_LOWER_LIMIT) {
        hoursWest += TWENTY_FOUR_HOUR_BASE;
    }
    return true;
}

float GetHoursWest(float hoursWest)
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN)) {
        for (float i : HOURS_WEST) {
            if (NearEqual(hoursWest, i)) {
                return hoursWest;
            }
        }
    }

    return int32_t(hoursWest);
}
} // namespace

} // namespace OHOS::Ace::Framework

extern "C" {
VectorNativeTextShadow FFICJCreateVectorNativeTextShadow(int64_t size)
{
    return new std::vector<NativeTextShadow>(size);
}

VectorNativeTextShadow FFICJCreateVectorNativeTextShadowV2(int64_t size)
{
    return new std::vector<NativeTextShadowV2>(size);
}

void FFICJVectorNativeTextShadowSetElement(
    VectorNativeTextShadow vec, int64_t index, NativeTextShadow textShadow)
{
    auto actualVec = reinterpret_cast<std::vector<NativeTextShadow>*>(vec);
    (*actualVec)[index] = textShadow;
}

void FFICJVectorNativeTextShadowSetElementV2(
    VectorNativeTextShadow vec, int64_t index, NativeTextShadowV2 textShadow)
{
    auto actualVec = reinterpret_cast<std::vector<NativeTextShadowV2>*>(vec);
    (*actualVec)[index] = textShadow;
}


void FFICJVectorNativeTextShadowDelete(VectorNativeTextShadow vec)
{
    auto actualVec = reinterpret_cast<std::vector<NativeTextShadow>*>(vec);
    delete actualVec;
}

void FFICJVectorNativeTextShadowDeleteV2(VectorNativeTextShadow vec)
{
    auto actualVec = reinterpret_cast<std::vector<NativeTextShadowV2>*>(vec);
    delete actualVec;
}

void FfiOHOSAceFrameworkTextClockCreateDefault(int64_t controllerId)
{
    auto textClock = TextClockModel::GetInstance()->Create();
    TextClockModel::GetInstance()->SetHoursWest(NAN);

    auto controller = FFIData::GetData<NativeTextClockController>(controllerId);
    if (controller != nullptr) {
        controller->SetController(textClock);
    } else {
        LOGE("textClockControllerId is invalid ");
    }
}

void FfiOHOSAceFrameworkTextClockCreateV2(float timeZoneOffset, int64_t controllerId)
{
    auto textClock = TextClockModel::GetInstance()->Create();
    if (HoursWestIsValid_(static_cast<int32_t>(timeZoneOffset))) {
        float hourWest = GetHoursWest(timeZoneOffset);
        TextClockModel::GetInstance()->SetHoursWest(hourWest);
    } else {
        TextClockModel::GetInstance()->SetHoursWest(NAN);
    }

    auto controller = FFIData::GetData<NativeTextClockController>(controllerId);
    if (controller != nullptr) {
        controller->SetController(textClock);
    } else {
        LOGE("textClockControllerId is invalid ");
    }
}

void FfiOHOSAceFrameworkTextClockCreate(int32_t timeZoneOffset, int64_t controllerId)
{
    auto textClock = TextClockModel::GetInstance()->Create();
    if (HoursWestIsValid_(timeZoneOffset)) {
        float hourWest = GetHoursWest(static_cast<float>(timeZoneOffset));
        TextClockModel::GetInstance()->SetHoursWest(hourWest);
    } else {
        TextClockModel::GetInstance()->SetHoursWest(NAN);
    }

    auto controller = FFIData::GetData<NativeTextClockController>(controllerId);
    if (controller != nullptr) {
        controller->SetController(textClock);
    } else {
        LOGE("textClockControllerId is invalid ");
    }
}

void FfiOHOSAceFrameworkTextClockCreateSimple(int64_t controllerId)
{
    auto textClock = TextClockModel::GetInstance()->Create();
    auto controller = FFIData::GetData<NativeTextClockController>(controllerId);
    if (controller != nullptr) {
        controller->SetController(textClock);
    } else {
        LOGE("textClockControllerId is invalid ");
    }
}

void FfiOHOSAceFrameworkTextClockFormat(const char* value)
{
    std::string format = static_cast<std::string>(value);
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        if (format.length() == 0) {
            TextClockModel::GetInstance()->SetFormat(DEFAULT_FORMAT_API_ELEVEN);
            return;
        }
    } else {
        std::regex pattern(
            R"(^([Yy]*[_|\W\s]*[M]*[_|\W\s]*[d]*[_|\W\s]*[D]*[_|\W\s]*[Hh]*[_|\W\s]*[m]*[_|\W\s]*[s]*[_|\W\s]*[S]*)$)");
        if (format.length() == 0 || !StringUtils::IsAscii(format) || !std::regex_match(format, pattern)) {
            TextClockModel::GetInstance()->SetFormat(DEFAULT_FORMAT_API_TEN);
            return;
        }
    }

    TextClockModel::GetInstance()->SetFormat(format);
}

void FfiOHOSAceFrameworkTextClockOnChange(void (*callback)(int64_t timeStamp))
{
    auto lambda = [lambda = CJLambda::Create(callback)](
                      const std::string& value) -> void { lambda(std::atol(value.c_str())); };
    TextClockModel::GetInstance()->SetOnDateChange(lambda);
}

void FfiOHOSAceFrameworkTextClockTextColor(uint32_t color)
{
    TextClockModel::GetInstance()->SetTextColor(Color(color));
}

void FfiOHOSAceFrameworkTextClockFontSize(double size, int32_t unit)
{
    CalcDimension fontSize = CalcDimension(size, DimensionUnit(unit));
    TextClockModel::GetInstance()->SetFontSize(fontSize);
}

void FfiOHOSAceFrameworkTextClockFontWeight(const char* fontWeight)
{
    TextClockModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(fontWeight));
}

void FfiOHOSAceFrameworkTextClockFontStyle(int32_t fontStyle)
{
    if (!Utils::CheckParamsValid(fontStyle, FONT_STYLES.size())) {
        LOGE("invalid value for font style");
        return;
    }
    TextClockModel::GetInstance()->SetItalicFontStyle(FONT_STYLES[fontStyle]);
}

void FfiOHOSAceFrameworkTextClockFontFamily(const char* fontFamily)
{
    std::vector<std::string> fontFamilies;
    fontFamilies = ConvertStrToFontFamilies(fontFamily);
    TextClockModel::GetInstance()->SetFontFamily(fontFamilies);
}

void FfiOHOSAceFrameworkTextClockDateTimeOptions(const char* hourOptions)
{
    ZeroPrefixType hourType = ZeroPrefixType::AUTO;
    if (hourOptions == TEXTCLOCK_DATE_TIME_OPTIONS_TWO_DIGIT_VAL) {
        hourType = ZeroPrefixType::SHOW;
    } else if (hourOptions == TEXTCLOCK_DATE_TIME_OPTIONS_NUMERIC_VAL) {
        hourType = ZeroPrefixType::HIDE;
    }
    TextClockModel::GetInstance()->SetDateTimeOptions(hourType);
}

void FfiOHOSAceFrameworkTextClockTextShadow(VectorStringPtr vecContent)
{
    auto nativeTextShadowVec = *reinterpret_cast<std::vector<NativeTextShadow>*>(vecContent);
    std::vector<Shadow> shadows(nativeTextShadowVec.size());
    for (size_t i = 0; i < nativeTextShadowVec.size(); i++) {
        Dimension dOffsetX(nativeTextShadowVec[i].offsetX, DimensionUnit::VP);
        Dimension dOffsetY(nativeTextShadowVec[i].offsetY, DimensionUnit::VP);
        shadows[i].SetBlurRadius(nativeTextShadowVec[i].radius);
        shadows[i].SetOffsetX(dOffsetX.Value());
        shadows[i].SetOffsetY(dOffsetY.Value());
        shadows[i].SetColor(Color(nativeTextShadowVec[i].color));
    }
    TextClockModel::GetInstance()->SetTextShadow(shadows);
}

void FfiOHOSAceFrameworkTextClockTextShadowV2(VectorStringPtr vecContent)
{
    auto nativeTextShadowVec = *reinterpret_cast<std::vector<NativeTextShadowV2>*>(vecContent);
    std::vector<Shadow> shadows(nativeTextShadowVec.size());
    for (size_t i = 0; i < nativeTextShadowVec.size(); i++) {
        Dimension dOffsetX(nativeTextShadowVec[i].offsetX, DimensionUnit::VP);
        Dimension dOffsetY(nativeTextShadowVec[i].offsetY, DimensionUnit::VP);
        shadows[i].SetBlurRadius(nativeTextShadowVec[i].radius);
        shadows[i].SetOffsetX(dOffsetX.Value());
        shadows[i].SetOffsetY(dOffsetY.Value());
        shadows[i].SetColor(Color(nativeTextShadowVec[i].color));
        shadows[i].SetIsFilled(nativeTextShadowVec[i].isFilled);
        shadows[i].SetShadowType(nativeTextShadowVec[i].type == 0 ? ShadowType::COLOR : ShadowType::BLUR);
    }
    TextClockModel::GetInstance()->SetTextShadow(shadows);
}

void FfiOHOSAceFrameworkTextClockFontFeature(const char* fontFeature)
{
    std::string fontFeatureSettings = fontFeature;
    TextClockModel::GetInstance()->SetFontFeature(ParseFontFeatureSettings(fontFeatureSettings));
}

int64_t FfiOHOSAceFrameworkTextClockControllerCtor()
{
    auto controller = FFIData::Create<NativeTextClockController>();
    if (controller == nullptr) {
        return FFI_ERROR_CODE;
    }
    return controller->GetID();
}

void FfiOHOSAceFrameworkTextClockControllerStart(int64_t selfID)
{
    auto self = FFIData::GetData<NativeTextClockController>(selfID);
    if (self != nullptr) {
        self->Start();
    } else {
        LOGE("FfiTextArea: invalid textClockController");
    }
}

void FfiOHOSAceFrameworkTextClockControllerStop(int64_t selfID)
{
    auto self = FFIData::GetData<NativeTextClockController>(selfID);
    if (self != nullptr) {
        self->Stop();
    } else {
        LOGE("FfiTextArea: invalid textClockController");
    }
}
}
