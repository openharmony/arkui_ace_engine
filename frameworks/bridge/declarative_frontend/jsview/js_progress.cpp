/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_progress.h"

#include "core/components/common/properties/color.h"
#include "core/components/progress/progress_component.h"
#include "core/components/progress/progress_theme.h"
#include "core/components/track/track_component.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void JSProgress::Create(const JSCallbackInfo& info)
{
    if (info.Length() != 1 || !info[0]->IsObject()) {
        LOGE("create progress fail beacase the param is invaild");
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto jsValue = paramObject->GetProperty("value");
    if (!jsValue->IsNumber()) {
        LOGE("create progress fail beacase the value is not number");
        return;
    }
    auto value = jsValue->ToNumber<double>();

    auto total = 100;
    auto jsTotal = paramObject->GetProperty("total");
    if (jsTotal->IsNumber()) {
        total = jsTotal->ToNumber<int>();
    } else {
        LOGE("create progress fail because the total is not value");
    }

    auto progressType = ProgressType::LINEAR;
    auto jsStyle = paramObject->GetProperty("style");
    if (jsStyle->IsNumber()) {
        progressType = static_cast<ProgressType>(jsStyle->ToNumber<int32_t>());
    } else {
        LOGE("create progress fail becaude the style is not value");
    }

    RefPtr<ProgressComponent> progressComponent =
        AceType::MakeRefPtr<OHOS::Ace::ProgressComponent>(0.0, value, 0.0, total, progressType);
    if (!progressComponent) {
        LOGE("Progress Component is null");
        return;
    }

    ViewStackProcessor::GetInstance()->Push(progressComponent);

    RefPtr<ProgressTheme> theme = GetTheme<ProgressTheme>();
    RefPtr<TrackComponent> track = progressComponent->GetTrack();
    track->SetSelectColor(theme->GetTrackSelectedColor());
    track->SetCachedColor(theme->GetTrackCachedColor());
    track->SetBackgroundColor(theme->GetTrackBgColor());
    track->SetTrackThickness(theme->GetTrackThickness());
}

void JSProgress::JSBind(BindingTarget globalObj)
{
    JSClass<JSProgress>::Declare("Progress");
    MethodOptions opt = MethodOptions::NONE;

    JSClass<JSProgress>::StaticMethod("create", &JSProgress::Create, opt);
    JSClass<JSProgress>::StaticMethod("value", &JSProgress::SetValue, opt);
    JSClass<JSProgress>::StaticMethod("color", &JSProgress::SetColor, opt);
    JSClass<JSProgress>::StaticMethod("cricularStyle", &JSProgress::SetCricularStyle, opt);
    JSClass<JSProgress>::Inherit<JSViewAbstract>();
    JSClass<JSProgress>::Bind(globalObj);
}

void JSProgress::SetValue(double value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto progress = AceType::DynamicCast<ProgressComponent>(component);
    progress->SetValue(value);
}

void JSProgress::SetColor(std::string& color)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto progress = AceType::DynamicCast<ProgressComponent>(component);
    RefPtr<TrackComponent> track = progress->GetTrack();
    track->SetSelectColor(Color::FromString(color));
}

void JSProgress::SetCricularStyle(const JSCallbackInfo& info)
{
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto progress = AceType::DynamicCast<ProgressComponent>(component);
    RefPtr<ProgressTheme> theme = GetTheme<ProgressTheme>();

    Dimension strokeWidthDimension;
    auto jsStrokeWidth = paramObject->GetProperty("strokeWidth");
    if (!ParseJsDimensionVp(jsStrokeWidth, strokeWidthDimension)) {
        LOGI("circular Style error. now use default strokeWidth");
        strokeWidthDimension = theme->GetTrackThickness();
    }
    progress->SetTrackThickness(strokeWidthDimension);

    auto jsScaleCount = paramObject->GetProperty("scaleCount");
    auto scaleCount = jsScaleCount->IsNumber() ? jsScaleCount->ToNumber<int32_t>() : theme->GetScaleNumber();
    progress->SetScaleNumber(scaleCount);

    Dimension scaleWidthDimension;
    auto jsScaleWidth = paramObject->GetProperty("scaleWidth");
    if (!ParseJsDimensionVp(jsScaleWidth, scaleWidthDimension)) {
        LOGI("circular Style error. now use default scaleWidth");
        scaleWidthDimension = theme->GetScaleWidth();
    }
    progress->SetScaleWidth(scaleWidthDimension);
}

}; // namespace OHOS::Ace::Framework
