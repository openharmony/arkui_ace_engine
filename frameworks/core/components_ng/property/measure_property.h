/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include <cstdint>
#include <optional>
#include <string>
#include <utility>

#include "core/common/ace_application_info.h"
#include "ui/properties/ng/measure_property.h"

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

    void Reset();

    bool IsValid() const;

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

    void SetSizeT(const CalcSize& Size);

    bool operator==(const CalcSize& Size) const
    {
        return (width_ == Size.width_) && (height_ == Size.height_);
    }

    bool operator!=(const CalcSize& Size) const
    {
        return !operator==(Size);
    }

    bool UpdateSizeWithCheck(const CalcSize& size);

    bool ClearSize(bool clearWidth, bool clearHeight);

    bool WidthFixed(bool checkPercent = true) const;

    bool HeightFixed(bool checkPercent = true) const;

    bool PercentWidth() const;

    bool PercentHeight() const;

    std::string ToString() const;

private:
    std::optional<CalcLength> width_;
    std::optional<CalcLength> height_;
};

struct MeasureProperty {
    std::optional<CalcSize> minSize;
    std::optional<CalcSize> maxSize;
    std::optional<CalcSize> selfIdealSize;
    std::optional<CalcSize> preMinSize;
    std::optional<CalcSize> preMaxSize;
    std::optional<CalcSize> preSelfIdealSize;

    void Reset();

    bool operator==(const MeasureProperty& measureProperty) const
    {
        return (minSize == measureProperty.minSize) && (maxSize == measureProperty.maxSize) &&
               (selfIdealSize == measureProperty.selfIdealSize);
    }

    bool UpdateSelfIdealSizeWithCheck(const CalcSize& size);

    bool ClearSelfIdealSize(bool clearWidth, bool clearHeight);

    bool UpdateMaxSizeWithCheck(const CalcSize& size);

    bool UpdateMinSizeWithCheck(const CalcSize& size);

    bool PercentWidth() const;

    bool PercentHeight() const;

    std::string ToString() const;

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;

    void ToJsonValue_GetJsonSize(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;

    static MeasureProperty FromJson(const std::unique_ptr<JsonValue>& json);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_MEASURE_PROPERTIES_H
