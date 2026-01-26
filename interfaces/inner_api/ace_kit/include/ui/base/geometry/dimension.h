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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_GEOMETRY_DIMENSION_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_GEOMETRY_DIMENSION_H

#include <optional>
#include <string>

#include "ui/base/macros.h"
#include "ui/base/utils/utils.h"

#define NEAR_ZERO(value) ((value > 0.0) ? ((value - 0.0) <= 0.000001f) : ((0.0 - value) <= 0.000001f))

namespace OHOS::Ace {

/**
 * @brief Enumeration of dimension units supported in ArkUI.
 *
 * This enum defines various units for representing sizes and distances in the UI,
 * similar to CSS length units but adapted for the ArkUI framework.
 */
enum class DimensionUnit {
    /*
     * Unit is invalid.
     */
    INVALID = -2,
    /*
     * Unit is empty.
     */
    NONE = -1,
    /*
     * Logical pixel used in Ace1.0. It's based on frontend design width.
     * For example, when a frontend with 750px design width running on a
     * device with 1080 pixels width, 1px represents 1.44 pixels.
     */
    PX = 0,
    /*
     * Density independent pixels, one vp is one pixel on a 160 dpi screen.
     */
    VP,
    /*
     * Scale independent pixels. This is like VP but will be scaled by
     * user's font size preference.
     */
    FP,
    /*
     * The percentage of either a value from the element's parent or from
     * another property of the element itself.
     */
    PERCENT,
    /*
     * logic pixels used in ACE2.0 instead of PX, and PX is the physical pixels in ACE2.0
     */
    LPX,
    /*
     * The value is calculated from the element's parent and another property of the element itself.
     */
    AUTO,
    /*
     * The value is expression.
     */
    CALC,
};

/*
 * Dimension contains a value and an unit to represent different
 * scales in one class.
 */
class ACE_FORCE_EXPORT Dimension {
public:
    /**
     * @brief Default constructor. Creates a dimension with value 0.0 and unit PX.
     */
    constexpr Dimension() = default;
    ~Dimension() = default;

    /**
     * @brief Constructs a dimension with specified value and unit.
     * @param value The numeric value of the dimension.
     * @param unit The unit of the dimension (default is PX).
     */
    constexpr explicit Dimension(double value, DimensionUnit unit = DimensionUnit::PX) : value_(value), unit_(unit) {}

    /**
     * @brief Resets the dimension to default state (0.0 PX).
     */
    void Reset()
    {
        value_ = 0.0;
        unit_ = DimensionUnit::PX;
    }

    /**
     * @brief Resets the dimension if the current value is NaN (Not a Number).
     * This is used to handle invalid floating-point values.
     */
    void ResetInvalidValue()
    {
        if (std::isnan(value_)) {
            Reset();
        }
    }

    /**
     * @brief Gets the numeric value of the dimension.
     * @return The dimension value.
     */
    constexpr double Value() const
    {
        return value_;
    }

    /**
     * @brief Sets the numeric value of the dimension.
     * @param value The new value to set.
     */
    void SetValue(double value)
    {
        value_ = value;
    }

    /**
     * @brief Gets the unit of the dimension.
     * @return The dimension unit.
     */
    constexpr DimensionUnit Unit() const
    {
        return unit_;
    }

    /**
     * @brief Sets the unit of the dimension.
     * @param unit The new unit to set.
     */
    void SetUnit(DimensionUnit unit)
    {
        unit_ = unit;
    }

    /**
     * @brief Checks if the dimension value is valid (greater than 0).
     * @return True if value > 0, false otherwise.
     */
    bool IsValid() const
    {
        return GreatNotEqual(value_, 0.0);
    }

    /**
     * @brief Checks if the dimension value is non-negative (greater than or equal to 0).
     * @return True if value >= 0, false otherwise.
     */
    bool IsNonNegative() const
    {
        return NonNegative(value_);
    }

    /**
     * @brief Checks if the dimension value is non-positive (less than or equal to 0).
     * @return True if value <= 0, false otherwise.
     */
    bool IsNonPositive() const
    {
        return NonPositive(value_);
    }

    /**
     * @brief Checks if the dimension value is negative (less than 0).
     * @return True if value < 0, false otherwise.
     */
    bool IsNegative() const
    {
        return !NonNegative(value_);
    }

    /**
     * @brief Converts the dimension to pixels using the specified scale factor.
     * @param dipScale The scale factor (pixels per VP/FP).
     * @return The dimension value in pixels.
     * @deprecated This method is deprecated. Use ConvertToPx() instead.
     */
    // Deprecated: don't use this to covert to px.
    double ConvertToPx(double dipScale) const
    {
        if (unit_ == DimensionUnit::VP || unit_ == DimensionUnit::FP) {
            return value_ * dipScale;
        }
        return value_;
    }

    /**
     * @brief Converts the dimension to VP (Virtual Pixels).
     * @note Does not support PERCENT unit conversion.
     * @return The dimension value in VP.
     */
    // Percentage unit conversion is not supported.
    double ConvertToVp() const;

    /**
     * @brief Converts the dimension to physical pixels.
     * @note Does not support PERCENT unit conversion.
     * @return The dimension value in physical pixels.
     */
    // Percentage unit conversion is not supported.
    double ConvertToPx() const;

    /**
     * @brief Converts the dimension to FP (Font Pixels).
     * @note Does not support PERCENT unit conversion.
     * @return The dimension value in FP.
     */
    // Percentage unit conversion is not supported.
    double ConvertToFp() const;

    /**
     * @brief Gets the adapted dimension unit based on the given dimension.
     * @param dimension The reference dimension.
     * @return The adapted dimension unit.
     */
    DimensionUnit GetAdaptDimensionUnit(const Dimension& dimension);

    /**
     * @brief Converts the dimension to pixels with optional min/max constraints.
     * @param minOptional Optional minimum value constraint.
     * @param maxOptional Optional maximum value constraint.
     * @param allowScale Whether to allow scaling (default is true).
     * @return The dimension value in pixels after applying constraints.
     */
    double ConvertToPxDistribute(
        std::optional<float> minOptional, std::optional<float> maxOptional, bool allowScale = true) const;

    /**
     * @brief Converts the dimension to pixels using custom font scale constraints.
     * @param minFontScale Minimum font scale factor.
     * @param maxFontScale Maximum font scale factor.
     * @return The dimension value in pixels.
     */
    double ConvertToPxByCustomFontScale(float minFontScale, float maxFontScale) const;

    /**
     * @brief Converts the dimension to pixels using application font scale.
     * @param minFontScale Minimum font scale factor.
     * @return The dimension value in pixels.
     */
    double ConvertToPxByAppFontScale(float minFontScale) const;

    /**
     * @brief Converts the dimension to VP using application font scale.
     * @return The dimension value in VP.
     */
    double ConvertToVpByAppFontScale() const;

    /**
     * @brief Gets the native value in the specified unit.
     * @param unit The target unit to convert to.
     * @return The dimension value in the specified unit.
     */
    double GetNativeValue(DimensionUnit unit) const
    {
        if (unit_ == unit || unit == DimensionUnit::PERCENT) {
            return value_;
        } else if (unit == DimensionUnit::PX) {
            return ConvertToPx();
        } else if (unit == DimensionUnit::FP) {
            return ConvertToFp();
        } else {
            return ConvertToVp();
        }
    }

    /**
     * @brief Converts the dimension to pixels with support for percentage units.
     * @param size The parent size used for percentage calculation.
     * @return The dimension value in pixels.
     */
    // support percentage unit conversion
    double ConvertToPxWithSize(double size) const;

    /**
     * @brief Normalizes the dimension to pixels using the specified scale factors.
     * @param vpScale Scale factor for VP to PX conversion.
     * @param fpScale Scale factor for FP to PX conversion.
     * @param lpxScale Scale factor for LPX to PX conversion.
     * @param parentLength Parent length for percentage calculation.
     * @param result Output parameter for the converted pixel value.
     * @return True if conversion succeeded, false otherwise.
     */
    bool NormalizeToPx(double vpScale, double fpScale, double lpxScale, double parentLength, double& result) const;

    /**
     * @brief Multiplies the dimension by a scalar value.
     * @param value The scalar value to multiply by.
     * @return A new dimension with the multiplied value and same unit.
     */
    constexpr Dimension operator*(double value) const
    {
        return Dimension(value_ * value, unit_);
    }

    /**
     * @brief Divides the dimension by a scalar value.
     * @param value The scalar value to divide by.
     * @return A new dimension with the divided value and same unit.
     * @note Returns a default dimension (0.0 PX) if the divisor is near zero.
     */
    constexpr Dimension operator/(double value) const
    {
        // NearZero cannot be used in a constant expression
        if (NEAR_ZERO(value)) {
            return {};
        }
        return Dimension(value_ / value, unit_);
    }

    /**
     * @brief Checks if two dimensions are equal.
     * @param dimension The dimension to compare with.
     * @return True if both units and values are equal, false otherwise.
     */
    bool operator==(const Dimension& dimension) const
    {
        return (unit_ == dimension.unit_) && NearEqual(value_, dimension.value_);
    }

    /**
     * @brief Checks if two dimensions are not equal.
     * @param dimension The dimension to compare with.
     * @return True if units or values are different, false otherwise.
     */
    bool operator!=(const Dimension& dimension) const
    {
        return !operator==(dimension);
    }

    /**
     * @brief Adds two dimensions with the same unit.
     * @param dimension The dimension to add.
     * @return A new dimension with the summed value and same unit.
     * @note Both dimensions must have the same unit, otherwise a DCHECK is triggered.
     */
    constexpr Dimension operator+(const Dimension& dimension) const
    {
        if (NEAR_ZERO(dimension.Value())) {
            return *this;
        }
        ACE_DCHECK(unit_ == dimension.unit_);
        return Dimension(value_ + dimension.value_, unit_);
    }

    /**
     * @brief Adds another dimension to this dimension and assigns the result.
     * @param dimension The dimension to add.
     * @return Reference to this dimension after addition.
     * @note Both dimensions must have the same unit, otherwise a DCHECK is triggered.
     */
    Dimension& operator+=(const Dimension& dimension)
    {
        ACE_DCHECK(unit_ == dimension.unit_);
        value_ += dimension.value_;
        return *this;
    }

    /**
     * @brief Subtracts another dimension from this dimension.
     * @param dimension The dimension to subtract.
     * @return A new dimension with the difference and same unit.
     * @note Both dimensions must have the same unit, otherwise a DCHECK is triggered.
     */
    constexpr Dimension operator-(const Dimension& dimension) const
    {
        if (NEAR_ZERO(dimension.Value())) {
            return *this;
        }
        ACE_DCHECK(unit_ == dimension.unit_);
        return Dimension(value_ - dimension.value_, unit_);
    }

    /**
     * @brief Returns the negated dimension (opposite sign).
     * @return A new dimension with negated value and same unit.
     */
    constexpr Dimension operator-() const
    {
        return Dimension(-value_, unit_);
    }

    /**
     * @brief Subtracts another dimension from this dimension and assigns the result.
     * @param dimension The dimension to subtract.
     * @return Reference to this dimension after subtraction.
     * @note Both dimensions must have the same unit, otherwise a DCHECK is triggered.
     */
    Dimension& operator-=(const Dimension& dimension)
    {
        ACE_DCHECK(unit_ == dimension.unit_);
        value_ -= dimension.value_;
        return *this;
    }

    /**
     * @brief Checks if this dimension is greater than another dimension.
     * @param dimension The dimension to compare with.
     * @return True if this dimension's value is greater, false otherwise.
     * @note Both dimensions must have the same unit, otherwise a DCHECK is triggered.
     */
    bool operator>(const Dimension& dimension) const
    {
        ACE_DCHECK(unit_ == dimension.unit_);
        return (value_ > dimension.value_);
    }

    /**
     * @brief Checks if this dimension is less than another dimension.
     * @param dimension The dimension to compare with.
     * @return True if this dimension's value is less, false otherwise.
     * @note Both dimensions must have the same unit, otherwise a DCHECK is triggered.
     */
    bool operator<(const Dimension& dimension) const
    {
        ACE_DCHECK(unit_ == dimension.unit_);
        return (value_ < dimension.value_);
    }

    /**
     * @brief Converts the dimension to a string representation.
     * @return A string in the format "valueunit" (e.g., "100.0vp", "50%").
     */
    std::string ToString() const;

    /**
     * @brief Creates a dimension from a string representation.
     * @param str The string to parse (e.g., "100vp", "50%", "16px").
     * @return A dimension object parsed from the string.
     */
    static Dimension FromString(const std::string& str);

private:
    double value_ = 0.0;
    DimensionUnit unit_ = DimensionUnit::PX;
};

/**
 * @brief Literal operator for creating VP (Virtual Pixel) dimensions.
 * @param value The numeric value in VP.
 * @return A dimension with VP unit.
 * @example auto d = 100.0_vp; // Creates Dimension(100.0, VP)
 */
inline constexpr Dimension operator""_vp(long double value)
{
    return Dimension(static_cast<double>(value), DimensionUnit::VP);
}

/**
 * @brief Literal operator for creating PX (Physical Pixel) dimensions.
 * @param value The numeric value in PX.
 * @return A dimension with PX unit.
 * @example auto d = 50.0_px; // Creates Dimension(50.0, PX)
 */
inline constexpr Dimension operator""_px(long double value)
{
    return Dimension(static_cast<double>(value), DimensionUnit::PX);
}

/**
 * @brief Literal operator for creating FP (Font Pixel) dimensions.
 * @param value The numeric value in FP.
 * @return A dimension with FP unit.
 * @remark FP dimensions scale with user font size preferences.
 * @example auto d = 16.0_fp; // Creates Dimension(16.0, FP)
 */
inline constexpr Dimension operator""_fp(long double value)
{
    return Dimension(static_cast<double>(value), DimensionUnit::FP);
}

/**
 * @brief Literal operator for creating percentage dimensions.
 * @param value The numeric percentage value.
 * @return A dimension with PERCENT unit.
 * @example auto d = 50.0_pct; // Creates Dimension(50.0, PERCENT)
 */
inline constexpr Dimension operator""_pct(long double value)
{
    return Dimension(static_cast<double>(value), DimensionUnit::PERCENT);
}

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_GEOMETRY_DIMENSION_H
