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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_MEASURE_PROPERTIES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_MEASURE_PROPERTIES_H

#include <array>
#include <cstdint>
#include <iomanip>
#include <optional>
#include <sstream>
#include <string>
#include <utility>

#include "base/geometry/ng/offset_t.h"
#include "base/json/json_util.h"
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/property/calc_length.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
const std::string BORDERZERO = "0.0";

enum class MeasureType {
    MATCH_PARENT,
    MATCH_CONTENT,
    MATCH_PARENT_CROSS_AXIS,
    MATCH_PARENT_MAIN_AXIS,
};

class CalcSize {
public:
    CalcSize() = default;
    ~CalcSize() = default;
    CalcSize(const CalcLength& width, const CalcLength& height) : width_(width), height_(height) {}
    CalcSize(std::optional<CalcLength> width, std::optional<CalcLength> height)
        : width_(std::move(width)), height_(std::move(height))
    {}

    void Reset()
    {
        width_.reset();
        height_.reset();
    }

    bool IsValid() const
    {
        return (width_ && height_) && (width_->GetDimension().Unit() != DimensionUnit::AUTO &&
                                          height_->GetDimension().Unit() != DimensionUnit::AUTO);
    }

    bool IsDimensionUnitAuto() const
    {
        return IsWidthDimensionUnitAuto() || IsHeightDimensionUnitAuto();
    }

    bool IsWidthDimensionUnitAuto() const
    {
        return width_ && width_->GetDimension().Unit() == DimensionUnit::AUTO;
    }

    bool IsHeightDimensionUnitAuto() const
    {
        return height_ && height_->GetDimension().Unit() == DimensionUnit::AUTO;
    }

    const std::optional<CalcLength>& Width() const
    {
        return width_;
    }

    const std::optional<CalcLength>& Height() const
    {
        return height_;
    }

    void SetWidth(const std::optional<CalcLength>& width)
    {
        width_ = width;
    }

    void SetHeight(const std::optional<CalcLength>& height)
    {
        height_ = height;
    }

    void SetSizeT(const CalcSize& Size)
    {
        width_ = Size.Width();
        height_ = Size.Height();
    }

    bool operator==(const CalcSize& Size) const
    {
        return (width_ == Size.width_) && (height_ == Size.height_);
    }

    bool operator!=(const CalcSize& Size) const
    {
        return !operator==(Size);
    }

    bool UpdateSizeWithCheck(const CalcSize& size)
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

    bool ClearSize(bool clearWidth, bool clearHeight)
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

    bool WidthFixed(bool checkPercent = true) const
    {
        return width_ && (!checkPercent || (checkPercent && width_->GetDimension().Unit() != DimensionUnit::PERCENT));
    }

    bool HeightFixed(bool checkPercent = true) const
    {
        return height_ && (!checkPercent || (checkPercent && height_->GetDimension().Unit() != DimensionUnit::PERCENT));
    }

    bool PercentWidth() const
    {
        return width_ && width_->GetDimension().Unit() == DimensionUnit::PERCENT;
    }

    bool PercentHeight() const
    {
        return height_ && height_->GetDimension().Unit() == DimensionUnit::PERCENT;
    }

    std::string ToString() const
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

private:
    std::optional<CalcLength> width_;
    std::optional<CalcLength> height_;
};

struct MeasureProperty {
    std::optional<CalcSize> minSize;
    std::optional<CalcSize> maxSize;
    std::optional<CalcSize> selfIdealSize;

    void Reset()
    {
        minSize.reset();
        maxSize.reset();
        selfIdealSize.reset();
    }

    bool operator==(const MeasureProperty& measureProperty) const
    {
        return (minSize == measureProperty.minSize) && (maxSize == measureProperty.maxSize) &&
               (selfIdealSize == measureProperty.selfIdealSize);
    }

    bool UpdateSelfIdealSizeWithCheck(const CalcSize& size)
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

    bool ClearSelfIdealSize(bool clearWidth, bool clearHeight)
    {
        if (selfIdealSize.has_value()) {
            return selfIdealSize->ClearSize(clearWidth, clearHeight);
        }
        return false;
    }

    bool UpdateMaxSizeWithCheck(const CalcSize& size)
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

    bool UpdateMinSizeWithCheck(const CalcSize& size)
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

    bool PercentWidth() const
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

    bool PercentHeight() const
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

    std::string ToString() const
    {
        std::string str;
        str.append("minSize: [").append(minSize.has_value() ? minSize->ToString() : "NA").append("]");
        str.append("maxSize: [").append(maxSize.has_value() ? maxSize->ToString() : "NA").append("]");
        str.append("selfIdealSize: [").append(selfIdealSize.has_value() ? selfIdealSize->ToString() : "NA").append("]");
        return str;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
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

    void ToJsonValue_GetJsonSize(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
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

    static MeasureProperty FromJson(const std::unique_ptr<JsonValue>& json)
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
};

template<typename T>
struct PaddingPropertyT {
    std::optional<T> left;
    std::optional<T> right;
    std::optional<T> top;
    std::optional<T> bottom;
    std::optional<T> start;
    std::optional<T> end;

    void SetEdges(const T& padding)
    {
        left = padding;
        right = padding;
        top = padding;
        bottom = padding;
    }

    void SetEdges(const T& leftValue, const T& rightValue, const T& topValue, const T& bottomValue)
    {
        left = leftValue;
        right = rightValue;
        top = topValue;
        bottom = bottomValue;
    }

    bool operator==(const PaddingPropertyT& value) const
    {
        return (left == value.left) && (right == value.right) && (top == value.top) && (bottom == value.bottom);
    }

    bool operator!=(const PaddingPropertyT& value) const
    {
        return !(*this == value);
    }

    bool UpdateWithCheck(const PaddingPropertyT& value)
    {
        if (value.start.has_value() || value.end.has_value()) {
            return UpdateLocalizedPadding(value);
        }
        start.reset();
        end.reset();
        if (*this != value) {
            left = value.left;
            right = value.right;
            top = value.top;
            bottom = value.bottom;
            return true;
        }
        return false;
    }

    bool UpdateLocalizedPadding(const PaddingPropertyT& value)
    {
        bool needUpdate = false;
        if (value.start.has_value() && start != value.start) {
            start = value.start;
            needUpdate = true;
        }
        if (value.end.has_value() && end != value.end) {
            end = value.end;
            needUpdate = true;
        }
        if (value.top.has_value() && top != value.top && (value.start.has_value() || value.end.has_value())) {
            top = value.top;
            needUpdate = true;
        }
        if (value.bottom.has_value() && bottom != value.bottom && (value.start.has_value() || value.end.has_value())) {
            bottom = value.bottom;
            needUpdate = true;
        }
        checkNeedReset(value);
        return needUpdate;
    }

    void checkNeedReset(const PaddingPropertyT& value)
    {
        auto isGreatThanFourteen =
            AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_FOURTEEN);
        if (!value.start.has_value() && start.has_value() && isGreatThanFourteen) {
            start.reset();
        }
        if (!value.end.has_value() && end.has_value() && isGreatThanFourteen) {
            end.reset();
        }
        if (!value.top.has_value() && top.has_value() && isGreatThanFourteen) {
            top.reset();
        }
        if (!value.bottom.has_value() && bottom.has_value() && isGreatThanFourteen) {
            bottom.reset();
        }
    }

    std::string ToString() const
    {
        std::string str;
        str.append("[").append(left.has_value() ? left->ToString() : "NA");
        str.append(",").append(right.has_value() ? right->ToString() : "NA");
        str.append(",").append(top.has_value() ? top->ToString() : "NA");
        str.append(",").append(bottom.has_value() ? bottom->ToString() : "NA").append("]");
        return str;
    }
    std::string ToJsonString() const
    {
        if (top == right && right == bottom && bottom == left) {
            if (top.has_value()) {
                return top->ToString();
            }
            return "0.0";
        }
        auto jsonValue = JsonUtil::Create(true);
        jsonValue->Put("top", top.has_value() ? top->ToString().c_str() : T{}.ToString().c_str());
        jsonValue->Put("right", right.has_value() ? right->ToString().c_str() : T{}.ToString().c_str());
        jsonValue->Put("bottom", bottom.has_value() ? bottom->ToString().c_str() : T{}.ToString().c_str());
        jsonValue->Put("left", left.has_value() ? left->ToString().c_str() : T{}.ToString().c_str());
        return jsonValue->ToString();
    }

    static PaddingPropertyT FromJsonString(const std::string& str)
    {
        PaddingPropertyT property;

        if (str.empty()) {
            LOGE("UITree |ERROR| empty string");
            return property;
        }

        if (str[0] >= '0' && str[0] <= '9') {
            property.top = property.right = property.bottom = property.left = T::FromString(str);
        } else if (str[0] == '{') {
            auto json = JsonUtil::ParseJsonString(str);
            if (!json->IsValid()) {
                return property;
            }
            property.top = T::FromString(json->GetString("top"));
            property.right = T::FromString(json->GetString("right"));
            property.bottom = T::FromString(json->GetString("bottom"));
            property.left = T::FromString(json->GetString("left"));
        } else {
            LOGE("UITree |ERROR| invalid str=%{public}s", str.c_str());
        }

        return property;
    }
};

template<>
struct PaddingPropertyT<float> {
    std::optional<float> left;
    std::optional<float> right;
    std::optional<float> top;
    std::optional<float> bottom;

    bool operator==(const PaddingPropertyT<float>& value) const
    {
        if (left.has_value() ^ value.left.has_value()) {
            return false;
        }
        if (!NearEqual(left.value_or(0), value.left.value_or(0))) {
            return false;
        }
        if (right.has_value() ^ value.right.has_value()) {
            return false;
        }
        if (!NearEqual(right.value_or(0), value.right.value_or(0))) {
            return false;
        }
        if (top.has_value() ^ value.top.has_value()) {
            return false;
        }
        if (!NearEqual(top.value_or(0), value.top.value_or(0))) {
            return false;
        }
        if (bottom.has_value() ^ value.bottom.has_value()) {
            return false;
        }
        if (!NearEqual(bottom.value_or(0), value.bottom.value_or(0))) {
            return false;
        }
        return true;
    }

    std::string ToString() const
    {
        std::string str;
        str.append("[").append(left.has_value() ? std::to_string(left.value()) : "NA");
        str.append(",").append(right.has_value() ? std::to_string(right.value()) : "NA");
        str.append(",").append(top.has_value() ? std::to_string(top.value()) : "NA");
        str.append(",").append(bottom.has_value() ? std::to_string(bottom.value()) : "NA").append("]");
        return str;
    }

    std::string ToJsonString() const
    {
        auto jsonValue = JsonUtil::Create(true);
        jsonValue->Put("top", top.has_value() ? std::to_string(top.value()).c_str() : BORDERZERO.c_str());
        jsonValue->Put("right", right.has_value() ? std::to_string(right.value()).c_str() : BORDERZERO.c_str());
        jsonValue->Put("bottom", bottom.has_value() ? std::to_string(bottom.value()).c_str() : BORDERZERO.c_str());
        jsonValue->Put("left", left.has_value() ? std::to_string(left.value()).c_str() : BORDERZERO.c_str());
        return jsonValue->ToString();
    }

    float Width() const
    {
        return left.value_or(0.0f) + right.value_or(0.0f);
    }

    float Height() const
    {
        return top.value_or(0.0f) + bottom.value_or(0.0f);
    }

    SizeF Size() const
    {
        return SizeF(Width(), Height());
    }

    OffsetF Offset() const
    {
        return OffsetF(left.value_or(0.0f), top.value_or(0.0f));
    }

    bool Empty()
    {
        return !left.has_value() && !right.has_value() && !top.has_value() && !bottom.has_value();
    }

    bool HasValue() const
    {
        return (left && !NearZero(left.value())) || (right && !NearZero(right.value())) ||
            (top && !NearZero(top.value())) || (bottom && !NearZero(bottom.value()));
    }

    PaddingPropertyT<float> Plus(const PaddingPropertyT<float>& another, bool skipNullOpt = true)
    {
        return Calculate(another, skipNullOpt, true);
    }

    PaddingPropertyT<float> Minus(const PaddingPropertyT<float>& another, bool skipNullOpt = true) const
    {
        return Calculate(another, skipNullOpt, false);
    }

    bool AllSidesFilled(bool checkZero = false)
    {
        // checking all sides has values and not zero
        if (checkZero) {
            return !NearZero(left.value_or(0.0f)) && !NearZero(right.value_or(0.0f)) && !NearZero(top.value_or(0.0f)) &&
                   !NearZero(bottom.value_or(0.0f));
        }
        return left.has_value() && right.has_value() && top.has_value() && bottom.has_value();
    }

    bool OptionalValueCover(const PaddingPropertyT<float>& another)
    {
        if (another.left.has_value() && !left.has_value()) {
            return false;
        }
        if (another.right.has_value() && !right.has_value()) {
            return false;
        }
        if (another.top.has_value() && !top.has_value()) {
            return false;
        }
        if (another.bottom.has_value() && !bottom.has_value()) {
            return false;
        }
        return true;
    }

    void Reset()
    {
        left.reset();
        right.reset();
        top.reset();
        bottom.reset();
    }

private:
    PaddingPropertyT<float> Calculate(const PaddingPropertyT<float>& another, bool skipNullOpt, bool isAdd) const
    {
        PaddingPropertyT<float> result;
        // skipNullOpt needs at least one padding has value to keep nullopt if two sides both null,
        // !skipNullOpt needs both sides has value
        int32_t factor = isAdd ? 1.0f : -1.0f;
        // to resolve cyclomatic complexity
        bool calculateCondition = (!skipNullOpt && left.has_value() && another.left.has_value()) ||
                                  (skipNullOpt && (left.has_value() || another.left.has_value()));
        if (calculateCondition) {
            result.left = left.value_or(0.0f) + factor * another.left.value_or(0.0f);
        }
        calculateCondition = (!skipNullOpt && right.has_value() && another.right.has_value()) ||
                             (skipNullOpt && (right.has_value() || another.right.has_value()));
        if (calculateCondition) {
            result.right = right.value_or(0.0f) + factor * another.right.value_or(0.0f);
        }
        calculateCondition = (!skipNullOpt && top.has_value() && another.top.has_value()) ||
                             (skipNullOpt && (top.has_value() || another.top.has_value()));
        if (calculateCondition) {
            result.top = top.value_or(0.0f) + factor * another.top.value_or(0.0f);
        }
        calculateCondition = (!skipNullOpt && bottom.has_value() && another.bottom.has_value()) ||
                             (skipNullOpt && (bottom.has_value() || another.bottom.has_value()));
        if (calculateCondition) {
            result.bottom = bottom.value_or(0.0f) + factor * another.bottom.value_or(0.0f);
        }
        return result;
    }
};

using PaddingProperty = PaddingPropertyT<CalcLength>;
using MarginProperty = PaddingProperty;
using PaddingPropertyF = PaddingPropertyT<float>;
using MarginPropertyF = PaddingPropertyT<float>;
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_MEASURE_PROPERTIES_H
