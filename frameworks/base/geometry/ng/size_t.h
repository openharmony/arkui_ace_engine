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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_NG_PROPERTIES_SIZE_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_NG_PROPERTIES_SIZE_H

#include <cstdint>
#include <iomanip>
#include <optional>
#include <sstream>
#include <string>

#include "base/geometry/axis.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::NG {
template<typename T>
class SizeT {
public:
    SizeT() = default;
    ~SizeT() = default;
    SizeT(T width, T height) : width_(width), height_(height) {}

    void Reset()
    {
        width_ = 0;
        height_ = 0;
    }

    T Width() const
    {
        return width_;
    }

    T Height() const
    {
        return height_;
    }

    T MainSize(Axis axis) const
    {
        return axis == Axis::HORIZONTAL ? width_ : height_;
    }

    void SetWidth(T width)
    {
        width_ = width;
    }

    void SetHeight(T height)
    {
        height_ = height;
    }

    void SetSizeT(const SizeT& SizeT)
    {
        width_ = SizeT.Width();
        height_ = SizeT.Height();
    }

    SizeT& AddHeight(T height)
    {
        height_ += height;
        return *this;
    }

    SizeT& AddWidth(T value)
    {
        width_ += value;
        return *this;
    }

    SizeT& MinusHeight(T height)
    {
        height_ -= height;
        return *this;
    }

    SizeT& MinusWidth(T width)
    {
        width_ -= width;
        return *this;
    }

    void MinusPadding(const std::optional<T>& left, const std::optional<T>& right, const std::optional<T>& top,
        const std::optional<T>& bottom)
    {
        T tempWidth = width_ - left.value_or(0) - right.value_or(0);
        if (Positive(tempWidth)) {
            width_ = tempWidth;
        }
        T tempHeight = height_ - top.value_or(0) - bottom.value_or(0);
        if (Positive(tempHeight)) {
            height_ = tempHeight;
        }
    }

    void AddPadding(const std::optional<T>& left, const std::optional<T>& right, const std::optional<T>& top,
        const std::optional<T>& bottom)
    {
        width_ = width_ + left.value_or(0) + right.value_or(0);
        height_ = height_ + top.value_or(0) + bottom.value_or(0);
    }

    bool IsNonNegative() const
    {
        return NonNegative(width_) && NonNegative(height_);
    }

    // width and height all less than zero.
    bool IsNegative() const
    {
        return Negative(width_) && Negative(height_);
    }

    bool IsPositive() const
    {
        return Positive(width_) && Positive(height_);
    }

    bool IsNonPositive() const
    {
        return NonPositive(width_) && NonPositive(height_);
    }

    bool UpdateSizeWithCheck(const SizeT& size)
    {
        bool isModified = false;
        if (NonNegative(size.width_) && (width_ != size.width_)) {
            width_ = size.width_;
            isModified = true;
        }
        if (NonNegative(size.height_) && (height_ != size.height_)) {
            height_ = size.height_;
            isModified = true;
        }
        return isModified;
    }

    void UpdateIllegalSizeWithCheck(const SizeT& size)
    {
        if (Negative(width_) && NonNegative(size.width_)) {
            width_ = size.width_;
        }
        if (Negative(height_) && NonNegative(size.height_)) {
            height_ = size.height_;
        }
    }

    bool UpdateSizeWhenLarger(const SizeT& size)
    {
        bool isModified = false;
        if (NonNegative(size.width_)) {
            auto temp = width_ > size.width_ ? width_ : size.width_;
            if (width_ != temp) {
                isModified = true;
            }
            width_ = temp;
        }
        if (NonNegative(size.height_)) {
            auto temp = height_ > size.height_ ? height_ : size.height_;
            if (height_ != temp) {
                isModified = true;
            }
            height_ = temp;
        }
        return isModified;
    }

    bool UpdateSizeWhenSmaller(const SizeT& size)
    {
        bool isModified = false;
        if (NonNegative(size.width_)) {
            auto temp = width_ < size.width_ ? width_ : size.width_;
            if (width_ != temp) {
                isModified = true;
            }
            width_ = temp;
        }
        if (NonNegative(size.height_)) {
            auto temp = height_ < size.height_ ? height_ : size.height_;
            if (height_ != temp) {
                isModified = true;
            }
            height_ = temp;
        }
        return isModified;
    }

    // used this instead of IsValid.
    void Constrain(const SizeT& minSize, const SizeT& maxSize)
    {
        if (NonNegative(width_) && NonNegative(minSize.width_)) {
            width_ = width_ > minSize.width_ ? width_ : minSize.width_;
        }
        if (NonNegative(height_) && NonNegative(minSize.height_)) {
            height_ = height_ > minSize.height_ ? height_ : minSize.height_;
        }
        if (NonNegative(width_) && NonNegative(maxSize.width_)) {
            width_ = width_ < maxSize.width_ ? width_ : maxSize.width_;
        }
        if (NonNegative(height_) && NonNegative(maxSize.height_)) {
            height_ = height_ < maxSize.height_ ? height_ : maxSize.height_;
        }
    }

    SizeT operator*(double value) const
    {
        return SizeT(width_ * value, height_ * value);
    }

    bool operator==(const SizeT& SizeT) const
    {
        return NearEqual(width_, SizeT.width_) && NearEqual(height_, SizeT.height_);
    }

    bool operator!=(const SizeT& SizeT) const
    {
        return !operator==(SizeT);
    }

    SizeT operator+(const SizeT& SizeT) const
    {
        return SizeT(width_ + SizeT.Width(), height_ + SizeT.Height());
    }

    SizeT operator+=(const SizeT& SizeT)
    {
        width_ += SizeT.Width();
        height_ += SizeT.Height();
        return *this;
    }

    SizeT operator-(const SizeT& SizeT) const
    {
        return SizeT(width_ - SizeT.Width(), height_ - SizeT.Height());
    }

    SizeT operator-=(const SizeT& SizeT)
    {
        width_ -= SizeT.Width();
        height_ -= SizeT.Height();
        return *this;
    }

    void ApplyScale(double scale)
    {
        width_ *= scale;
        height_ *= scale;
    }

    /*
     * Please make sure that two SizeTs are both valid.
     * You can use IsValid() to see if a SizeT is valid.
     */
    bool operator>(const SizeT& SizeT) const
    {
        if (IsNonNegative() && SizeT.IsNonNegative()) {
            return GreatOrEqual(width_, SizeT.width_) && GreatOrEqual(height_, SizeT.height_);
        }
        return false;
    }

    /*
     * Please make sure that two SizeTs are both valid.
     * You can use IsValid() to see if a SizeT is valid.
     */
    bool operator<(const SizeT& SizeT) const
    {
        if (IsNonNegative() && SizeT.IsNonNegative()) {
            return LessOrEqual(width_, SizeT.width_) && LessOrEqual(height_, SizeT.height_);
        }
        return false;
    }

    double CalcRatio() const
    {
        return static_cast<double>(width_) / static_cast<double>(height_);
    }

    std::string ToString() const
    {
        static const int32_t precision = 2;
        std::stringstream ss;
        ss << "[" << std::fixed << std::setprecision(precision);
        ss << width_;
        ss << " x ";
        ss << height_;
        ss << "]";
        std::string output = ss.str();
        return output;
    }

private:
    T width_ { 0 };
    T height_ { 0 };
};

using SizeF = SizeT<float>;
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_NG_PROPERTIES_SIZE_H
