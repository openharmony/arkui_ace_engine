/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/models/progress_model_impl.h"

#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
namespace {
const int32_t DEFALUT_PROGRESS_SCALE_NUMBER = 100;
const Dimension DEFALUT_PROGRESS_SCALE_WIDTH = Dimension(2);
} // namespace

void ProgressModelImpl::Create(double min, double value, double cachedValue, double max, NG::ProgressType type)
{
    auto progressComponent = AceType::MakeRefPtr<OHOS::Ace::ProgressComponent>(
        min, value, cachedValue, max, static_cast<ProgressType>(type));
    ViewStackProcessor::GetInstance()->ClaimElementId(progressComponent);
    auto theme = JSViewAbstract::GetTheme<ProgressTheme>();
    if (!theme) {
        LOGE("progress Theme is null");
        return;
    }

    progressComponent->InitStyle(theme);

    if (type == NG::ProgressType::SCALE) {
        progressComponent->SetScaleNumber(DEFALUT_PROGRESS_SCALE_NUMBER);
        progressComponent->SetScaleWidth(DEFALUT_PROGRESS_SCALE_WIDTH);
    }

    ViewStackProcessor::GetInstance()->Push(progressComponent);
}

void ProgressModelImpl::SetValue(double value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto progress = AceType::DynamicCast<ProgressComponent>(component);
    if (!progress) {
        LOGI("progress component is null.");
        return;
    }

    auto maxValue_ = progress->GetMaxValue();
    if (value > maxValue_) {
        LOGE("value is lager than total , set value euqals total");
        value = maxValue_;
    }
    progress->SetValue(value);
}

void ProgressModelImpl::SetColor(const Color& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto progress = AceType::DynamicCast<ProgressComponent>(component);
    if (!progress) {
        LOGI("progress component is null.");
        return;
    }
    RefPtr<TrackComponent> track = progress->GetTrack();

    track->SetSelectColor(value);
}

void ProgressModelImpl::SetBackgroundColor(const Color& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto progress = AceType::DynamicCast<ProgressComponent>(component);
    if (!progress) {
        LOGE("progress Component is null");
        return;
    }
    auto track = progress->GetTrack();
    if (!track) {
        LOGE("track Component is null");
        return;
    }

    track->SetBackgroundColor(value);
}

void ProgressModelImpl::SetStrokeWidth(const Dimension& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto progress = AceType::DynamicCast<ProgressComponent>(component);
    if (!progress) {
        LOGI("progress component is null.");
        return;
    }

    progress->SetTrackThickness(value);
}

void ProgressModelImpl::SetScaleCount(int32_t value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto progress = AceType::DynamicCast<ProgressComponent>(component);
    if (!progress) {
        LOGI("progress component is null.");
        return;
    }

    if (value > 0.0) {
        progress->SetScaleNumber(value);
    }
}

void ProgressModelImpl::SetScaleWidth(const Dimension& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto progress = AceType::DynamicCast<ProgressComponent>(component);
    if (!progress) {
        LOGI("progress component is null.");
        return;
    }

    progress->SetScaleWidth(value);
}

} // namespace OHOS::Ace::Framework
