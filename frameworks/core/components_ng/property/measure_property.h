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
#include "core/components_ng/property/calc_length.h"

namespace OHOS::Ace::NG {

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
        return width_ && height_;
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

    bool WidthFixed() const
    {
        return width_ && width_->GetDimension().Unit() != DimensionUnit::PERCENT;
    }

    bool HeightFixed() const
    {
        return height_ && height_->GetDimension().Unit() != DimensionUnit::PERCENT;
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

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const
    {
        // this may affect XTS, check later.
#if !defined(PREVIEW)
        std::string width =
            selfIdealSize.has_value()
                ? (selfIdealSize.value().Width().has_value() ? selfIdealSize.value().Width().value().ToString() : "-")
                : "-";
        std::string height =
            selfIdealSize.has_value()
                ? (selfIdealSize.value().Height().has_value() ? selfIdealSize.value().Height().value().ToString() : "-")
                : "-";
        json->Put("width", width.c_str());
        json->Put("height", height.c_str());

        auto jsonSize = JsonUtil::Create(true);
        jsonSize->Put("width", width.c_str());
        jsonSize->Put("height", height.c_str());
        json->Put("size", jsonSize);
#else
        auto jsonSize = JsonUtil::Create(true);
        if (selfIdealSize.has_value()) {
            if (selfIdealSize.value().Width().has_value()) {
                auto widthStr = selfIdealSize.value().Width().value().ToString();
                json->Put("width", widthStr.c_str());
                jsonSize->Put("width", widthStr.c_str());
            }
            if (selfIdealSize.value().Height().has_value()) {
                auto heightStr = selfIdealSize.value().Height().value().ToString();
                json->Put("height", heightStr.c_str());
                jsonSize->Put("height", heightStr.c_str());
            }
        }
        json->Put("size", jsonSize);
#endif

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
        json->Put("constraintSize", jsonConstraintSize->ToString().c_str());
    }

    static MeasureProperty FromJson(const std::unique_ptr<JsonValue>& json)
    {
        MeasureProperty ans;
        auto width = json->GetString("width");
        auto height = json->GetString("height");
        LOGD("UITree width=%{public}s height=%{public}s", width.c_str(), height.c_str());
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

    void SetEdges(const T& padding)
    {
        left = padding;
        right = padding;
        top = padding;
        bottom = padding;
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
        if (*this != value) {
            left = value.left;
            right = value.right;
            top = value.top;
            bottom = value.bottom;
            return true;
        }
        return false;
    }

    std::string ToString() const
    {
        std::string str;
        str.append("left: [").append(left.has_value() ? left->ToString() : "NA").append("]");
        str.append("right: [").append(right.has_value() ? right->ToString() : "NA").append("]");
        str.append("top: [").append(top.has_value() ? top->ToString() : "NA").append("]");
        str.append("bottom: [").append(bottom.has_value() ? bottom->ToString() : "NA").append("]");
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
        jsonValue->Put("top", top->ToString().c_str());
        jsonValue->Put("right", right->ToString().c_str());
        jsonValue->Put("bottom", bottom->ToString().c_str());
        jsonValue->Put("left", left->ToString().c_str());
        return jsonValue->ToString();
    }

    static PaddingPropertyT FromJsonString(const std::string& str)
    {
        LOGD("UITree str=%{public}s", str.c_str());
        PaddingPropertyT property;

        if (str.empty()) {
            LOGE("UITree |ERROR| empty string");
            return property;
        }

        if (str[0] >= '0' && str[0] <= '9') {
            LOGD("UITree decode number");
            property.top = property.right = property.bottom = property.left = T::FromString(str);
        } else if (str[0] == '{') {
            LOGD("UITree decode json");
            auto json = JsonUtil::ParseJsonString(str);
            if (!json->IsValid()) {
                LOGD("UITree invalid json [%{public}s]", json->ToString().c_str());
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
        str.append("left: [").append(left.has_value() ? std::to_string(left.value()) : "NA").append("]");
        str.append("right: [").append(right.has_value() ? std::to_string(right.value()) : "NA").append("]");
        str.append("top: [").append(top.has_value() ? std::to_string(top.value()) : "NA").append("]");
        str.append("bottom: [").append(bottom.has_value() ? std::to_string(bottom.value()) : "NA").append("]");
        return str;
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
};

using PaddingProperty = PaddingPropertyT<CalcLength>;
using MarginProperty = PaddingProperty;
using PaddingPropertyF = PaddingPropertyT<float>;
using MarginPropertyF = PaddingPropertyT<float>;
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_MEASURE_PROPERTIES_H