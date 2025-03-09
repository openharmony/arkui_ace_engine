/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/property/measure_property.h"

#include "core/common/ace_application_info.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

void CalcSize::Reset()
{
    width_.reset();
    height_.reset();
}

bool CalcSize::IsValid() const
{
    return (width_ && height_) && (width_->GetDimension().Unit() != DimensionUnit::AUTO &&
                                      height_->GetDimension().Unit() != DimensionUnit::AUTO);
}

void CalcSize::SetSizeT(const CalcSize& Size)
{
    width_ = Size.Width();
    height_ = Size.Height();
}

bool CalcSize::UpdateSizeWithCheck(const CalcSize& size)
{
    if ((width_ == size.width_) && ((height_ == size.height_))) {
        return false;
    }
    if (size.width_) {
        width_ = size.width_;
    }
    if (size.height_) {
        height_ = size.height_;
    }
    return true;
}

bool CalcSize::ClearSize(bool clearWidth, bool clearHeight)
{
    bool changed = false;
    if (clearWidth && width_.has_value()) {
        width_.reset();
        changed = true;
    }
    if (clearHeight && height_.has_value()) {
        height_.reset();
        changed = true;
    }
    return changed;
}

bool CalcSize::WidthFixed(bool checkPercent) const
{
    return width_ && (!checkPercent || (checkPercent && width_->GetDimension().Unit() != DimensionUnit::PERCENT));
}

bool CalcSize::HeightFixed(bool checkPercent) const
{
    return height_ && (!checkPercent || (checkPercent && height_->GetDimension().Unit() != DimensionUnit::PERCENT));
}

bool CalcSize::PercentWidth() const
{
    return width_ && (width_->GetDimension().Unit() == DimensionUnit::PERCENT ||
                         (width_->GetDimension().Unit() == DimensionUnit::CALC &&
                             width_->CalcValue().find("%") != std::string::npos));
}

bool CalcSize::PercentHeight() const
{
    return height_ && (height_->GetDimension().Unit() == DimensionUnit::PERCENT ||
                          (height_->GetDimension().Unit() == DimensionUnit::CALC &&
                              height_->CalcValue().find("%") != std::string::npos));
}

std::string CalcSize::ToString() const
{
    static const int32_t precision = 2;
    std::stringstream ss;
    ss << "[" << std::fixed << std::setprecision(precision);
    ss << (width_ ? width_->ToString() : "NA");
    ss << " x ";
    ss << (height_ ? height_->ToString() : "NA");
    ss << "]";
    std::string output = ss.str();
    return output;
}

void MeasureProperty::Reset()
{
    minSize.reset();
    maxSize.reset();
    selfIdealSize.reset();
    preMinSize.reset();
    preMaxSize.reset();
    preSelfIdealSize.reset();
}

bool MeasureProperty::UpdateSelfIdealSizeWithCheck(const CalcSize& size)
{
    if (selfIdealSize == size) {
        return false;
    }
    if (selfIdealSize.has_value()) {
        return selfIdealSize->UpdateSizeWithCheck(size);
    }
    selfIdealSize = size;
    return true;
}

bool MeasureProperty::ClearSelfIdealSize(bool clearWidth, bool clearHeight)
{
    if (selfIdealSize.has_value()) {
        return selfIdealSize->ClearSize(clearWidth, clearHeight);
    }
    return false;
}

bool MeasureProperty::UpdateMaxSizeWithCheck(const CalcSize& size)
{
    if (maxSize == size) {
        return false;
    }
    if (maxSize.has_value()) {
        return maxSize->UpdateSizeWithCheck(size);
    }
    maxSize = size;
    return true;
}

bool MeasureProperty::UpdateMinSizeWithCheck(const CalcSize& size)
{
    if (minSize == size) {
        return false;
    }
    if (minSize.has_value()) {
        return minSize->UpdateSizeWithCheck(size);
    }
    minSize = size;
    return true;
}

bool MeasureProperty::PercentWidth() const
{
    if (selfIdealSize.has_value()) {
        return selfIdealSize->PercentWidth();
    }
    if (maxSize.has_value()) {
        return maxSize->PercentWidth();
    }
    if (minSize.has_value()) {
        return minSize->PercentWidth();
    }
    return false;
}

bool MeasureProperty::PercentHeight() const
{
    if (selfIdealSize.has_value()) {
        return selfIdealSize->PercentHeight();
    }
    if (maxSize.has_value()) {
        return maxSize->PercentHeight();
    }
    if (minSize.has_value()) {
        return minSize->PercentHeight();
    }
    return false;
}

std::string MeasureProperty::ToString() const
{
    std::string str;
    str.append("minSize: [").append(minSize.has_value() ? minSize->ToString() : "NA").append("]");
    str.append("maxSize: [").append(maxSize.has_value() ? maxSize->ToString() : "NA").append("]");
    str.append("selfIdealSize: [").append(selfIdealSize.has_value() ? selfIdealSize->ToString() : "NA").append("]");
    return str;
}

void MeasureProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    // this may affect XTS, check later.
    auto context = PipelineBase::GetCurrentContext();
    if (context && context->GetMinPlatformVersion() < static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN)) {
#if !defined(PREVIEW)
        /* no fixed attr below */
        if (!filter.IsFastFilter()) {
            std::string width = selfIdealSize.has_value() ?
                (selfIdealSize.value().Width().has_value() ?
                selfIdealSize.value().Width().value().ToString() : "-") : "-";
            std::string height = selfIdealSize.has_value() ?
                (selfIdealSize.value().Height().has_value() ?
                selfIdealSize.value().Height().value().ToString() : "-") : "-";
            json->PutExtAttr("width", width.c_str(), filter);
            json->PutExtAttr("height", height.c_str(), filter);

            auto jsonSize = JsonUtil::Create(true);
            jsonSize->Put("width", width.c_str());
            jsonSize->Put("height", height.c_str());
            json->PutExtAttr("size", jsonSize, filter);
        }
#else
        ToJsonValue_GetJsonSize(json, filter);
#endif
    } else {
        ToJsonValue_GetJsonSize(json, filter);
    }

    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto jsonConstraintSize = JsonUtil::Create(true);
    jsonConstraintSize->Put("minWidth",
        minSize.value_or(CalcSize()).Width().value_or(CalcLength(0, DimensionUnit::VP)).ToString().c_str());
    jsonConstraintSize->Put("minHeight",
        minSize.value_or(CalcSize()).Height().value_or(CalcLength(0, DimensionUnit::VP)).ToString().c_str());
    jsonConstraintSize->Put("maxWidth", maxSize.value_or(CalcSize())
                                            .Width()
                                            .value_or(CalcLength(Infinity<double>(), DimensionUnit::VP))
                                            .ToString()
                                            .c_str());
    jsonConstraintSize->Put("maxHeight", maxSize.value_or(CalcSize())
                                                .Height()
                                                .value_or(CalcLength(Infinity<double>(), DimensionUnit::VP))
                                                .ToString()
                                                .c_str());
    json->PutExtAttr("constraintSize", jsonConstraintSize->ToString().c_str(), filter);
}

void MeasureProperty::ToJsonValue_GetJsonSize(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto jsonSize = JsonUtil::Create(true);
    if (selfIdealSize.has_value()) {
        if (selfIdealSize.value().Width().has_value()) {
            auto widthStr = selfIdealSize.value().Width().value().ToString();
            json->PutExtAttr("width", widthStr.c_str(), filter);
            jsonSize->Put("width", widthStr.c_str());
        }
        if (selfIdealSize.value().Height().has_value()) {
            auto heightStr = selfIdealSize.value().Height().value().ToString();
            json->PutExtAttr("height", heightStr.c_str(), filter);
            jsonSize->Put("height", heightStr.c_str());
        }
    }
    json->PutExtAttr("size", jsonSize, filter);
}

MeasureProperty MeasureProperty::FromJson(const std::unique_ptr<JsonValue>& json)
{
    MeasureProperty ans;
    auto width = json->GetString("width");
    auto height = json->GetString("height");
    if (width != "-" || height != "-") {
        ans.selfIdealSize =
            CalcSize(width != "-" ? std::optional<CalcLength>(Dimension::FromString(width)) : std::nullopt,
                height != "-" ? std::optional<CalcLength>(Dimension::FromString(height)) : std::nullopt);
    }
    return ans;
}
} // namespace OHOS::Ace::NG
