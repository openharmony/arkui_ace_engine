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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_GEOMETRY_NG_SIZE_T_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_GEOMETRY_NG_SIZE_T_H

#include <cstdint>
#include <iomanip>
#include <optional>
#include <sstream>
#include <string>

#include "ui/base/geometry/axis.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::NG {

template<typename T>
class SizeT {
public:
    SizeT() = default;
    ~SizeT() = default;
    SizeT(T width, T height) : width_(width), height_(height) {}

    SizeT(T crossSize, T mainSize, Axis axis)
    {
        if (axis == Axis::HORIZONTAL) {
            width_ = mainSize;
            height_ = crossSize;
        } else { // Axis::VERTICAL and others
            width_ = crossSize;
            height_ = mainSize;
        }
    }

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

    T CrossSize(Axis axis) const
    {
        return axis == Axis::HORIZONTAL ? height_ : width_;
    }

    void SetWidth(T width)
    {
        width_ = width;
    }

    void SetHeight(T height)
    {
        height_ = height;
    }

    void SetMainSize(T mainSize, Axis axis)
    {
        axis == Axis::HORIZONTAL ? width_ = mainSize : height_ = mainSize;
    }

    void SetCrossSize(T crossSize, Axis axis)
    {
        axis == Axis::HORIZONTAL ? height_ = crossSize : width_ = crossSize;
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
        if (NonNegative(tempWidth)) {
            width_ = tempWidth;
        }
        T tempHeight = height_ - top.value_or(0) - bottom.value_or(0);
        if (NonNegative(tempHeight)) {
            height_ = tempHeight;
        }
    }

    void MinusPaddingToNonNegative(const std::optional<T>& left, const std::optional<T>& right,
        const std::optional<T>& top, const std::optional<T>& bottom)
    {
        if (width_) {
            T tempWidth = width_ - left.value_or(0) - right.value_or(0);
            width_ = NonNegative(tempWidth) ? tempWidth : 0;
        }
        if (height_) {
            T tempHeight = height_ - top.value_or(0) - bottom.value_or(0);
            height_ = NonNegative(tempHeight) ? tempHeight : 0;
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
        bool widthUpdated = UpdateWidthWhenLarger(size);
        bool heightUpdated = UpdateHeightWhenLarger(size);
        return widthUpdated || heightUpdated;
    }

    bool UpdateWidthWhenLarger(const SizeT& size)
    {
        bool isModified = false;
        if (NonNegative(size.width_)) {
            auto temp = width_ > size.width_ ? width_ : size.width_;
            if (width_ != temp) {
                isModified = true;
            }
            width_ = temp;
        }
        return isModified;
    }

    bool UpdateHeightWhenLarger(const SizeT& size)
    {
        bool isModified = false;
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
        bool widthUpdated = UpdateWidthWhenSmaller(size);
        bool heightUpdated = UpdateHeightWhenSmaller(size);
        return widthUpdated || heightUpdated;
    }

    bool UpdateWidthWhenSmaller(const SizeT& size)
    {
        bool isModified = false;
        if (NonNegative(size.width_)) {
            auto temp = width_ < size.width_ ? width_ : size.width_;
            if (width_ != temp) {
                isModified = true;
            }
            width_ = temp;
        }
        return isModified;
    }

    bool UpdateHeightWhenSmaller(const SizeT& size)
    {
        bool isModified = false;
        if (NonNegative(size.height_)) {
            auto temp = height_ < size.height_ ? height_ : size.height_;
            if (height_ != temp) {
                isModified = true;
            }
            height_ = temp;
        }
        return isModified;
    }

    void UpdateMin(const SizeT& minSize)
    {
        if (NonNegative(minSize.width_)) {
            width_ = width_ > minSize.Width() ? width_ : minSize.Width();
        }
        if (NonNegative(minSize.height_)) {
            height_ = height_ > minSize.Height() ? height_ : minSize.Height();
        }
    }

    void UpdateMax(const SizeT& maxSize)
    {
        if (NonNegative(maxSize.width_)) {
            width_ = width_ < maxSize.Width() ? width_ : maxSize.Width();
        }
        if (NonNegative(maxSize.height_)) {
            height_ = height_ < maxSize.Height() ? height_ : maxSize.Height();
        }
    }

    void Constrain(const SizeT& minSize, const SizeT& maxSize, bool version10OrLarger = false)
    {
        if (version10OrLarger) {
            UpdateMax(maxSize);
            UpdateMin(minSize);
            return;
        }
        UpdateMin(minSize);
        UpdateMax(maxSize);
    }

    SizeT operator*(double value) const
    {
        return SizeT(width_ * value, height_ * value);
    }

    bool operator==(const SizeT& size) const
    {
        return NearEqual(width_, size.width_) && NearEqual(height_, size.height_);
    }

    bool operator!=(const SizeT& size) const
    {
        return !operator==(size);
    }

    SizeT operator+(const SizeT& size) const
    {
        return SizeT(width_ + size.Width(), height_ + size.Height());
    }

    SizeT& operator+=(const SizeT& size)
    {
        width_ += size.Width();
        height_ += size.Height();
        return *this;
    }

    SizeT operator-(const SizeT& size) const
    {
        return SizeT(width_ - size.Width(), height_ - size.Height());
    }

    SizeT& operator-=(const SizeT& size)
    {
        width_ -= size.Width();
        height_ -= size.Height();
        return *this;
    }

    void DivideScale(float scale)
    {
        if (NearZero(scale)) {
            return;
        }
        width_ /= scale;
        height_ /= scale;
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

template<typename T>
class OptionalSize {
public:
    OptionalSize() = default;
    ~OptionalSize() = default;
    OptionalSize(const std::optional<T>& width, const std::optional<T>& height) : width_(width), height_(height) {}
    OptionalSize(const T& width, const T& height) : width_(width), height_(height) {}
    explicit OptionalSize(const SizeT<T>& size) : width_(size.Width()), height_(size.Height()) {}

    void Reset()
    {
        width_.reset();
        height_.reset();
    }

    const std::optional<T>& Width() const
    {
        return width_;
    }

    const std::optional<T>& Height() const
    {
        return height_;
    }

    const std::optional<T>& MainSize(Axis axis) const
    {
        return axis == Axis::HORIZONTAL ? width_ : height_;
    }

    const std::optional<T>& CrossSize(Axis axis) const
    {
        return axis == Axis::HORIZONTAL ? height_ : width_;
    }

    void SetWidth(T width)
    {
        width_ = width;
    }

    void SetHeight(T height)
    {
        height_ = height;
    }

    void SetMainSize(T mainSize, Axis axis)
    {
        axis == Axis::HORIZONTAL ? width_ = mainSize : height_ = mainSize;
    }

    void SetCrossSize(T crossSize, Axis axis)
    {
        axis == Axis::HORIZONTAL ? height_ = crossSize : width_ = crossSize;
    }

    void SetMainSize(const std::optional<T>& mainSize, Axis axis)
    {
        axis == Axis::HORIZONTAL ? width_ = mainSize : height_ = mainSize;
    }

    void SetCrossSize(const std::optional<T>& crossSize, Axis axis)
    {
        axis == Axis::HORIZONTAL ? height_ = crossSize : width_ = crossSize;
    }

    void SetWidth(const std::optional<T>& width)
    {
        width_ = width;
    }

    void SetHeight(const std::optional<T>& height)
    {
        height_ = height;
    }

    void SetSize(const SizeT<T>& sizeF)
    {
        width_ = sizeF.Width();
        height_ = sizeF.Height();
    }

    void SetOptionalSize(const OptionalSize& size)
    {
        width_ = size.Width();
        height_ = size.Height();
    }

    OptionalSize& AddHeight(float height)
    {
        height_ = height_.value_or(0) + height;
        return *this;
    }

    OptionalSize& AddWidth(float width)
    {
        width_ = width_.value_or(0) + width;
        return *this;
    }

    OptionalSize& MinusHeight(float height)
    {
        height_ = height_.value_or(0) - height;
        return *this;
    }

    OptionalSize& MinusWidth(float width)
    {
        width_ = width_.value_or(0) - width;
        return *this;
    }

    void MinusPadding(const std::optional<T>& left, const std::optional<T>& right, const std::optional<T>& top,
        const std::optional<T>& bottom)
    {
        if (width_) {
            T tempWidth = width_.value() - left.value_or(0) - right.value_or(0);
            width_ = NonNegative(tempWidth) ? tempWidth : 0;
        }
        if (height_) {
            T tempHeight = height_.value() - top.value_or(0) - bottom.value_or(0);
            height_ = NonNegative(tempHeight) ? tempHeight : 0;
        }
    }

    void AddPadding(const std::optional<T>& left, const std::optional<T>& right, const std::optional<T>& top,
        const std::optional<T>& bottom)
    {
        if (width_) {
            width_ = width_.value() + left.value_or(0) + right.value_or(0);
        }
        if (height_) {
            height_ = height_.value() + top.value_or(0) + bottom.value_or(0);
        }
    }

    bool IsValid() const
    {
        return width_ && height_;
    }

    bool AtLeastOneValid() const
    {
        return width_ || height_;
    }

    bool IsNull() const
    {
        return !width_ && !height_;
    }

    bool IsNonNegative() const
    {
        return NonNegative(width_.value_or(-1)) && NonNegative(height_.value_or(-1));
    }

    // width and height all less than zero.
    bool IsNegative() const
    {
        return Negative(width_.value_or(-1)) && Negative(height_.value_or(-1));
    }

    bool IsPositive() const
    {
        return Positive(width_.value_or(-1)) && Positive(height_.value_or(-1));
    }

    bool IsNonPositive() const
    {
        return NonPositive(width_.value_or(-1)) && NonPositive(height_.value_or(-1));
    }

    bool UpdateSizeWithCheck(const OptionalSize& size)
    {
        bool isModified = false;
        if (size.width_ && (width_ != size.width_)) {
            width_ = size.width_;
            isModified = true;
        }
        if (size.height_ && (height_ != size.height_)) {
            height_ = size.height_;
            isModified = true;
        }
        return isModified;
    }

    bool UpdateSizeWithCheck(const SizeT<T>& size)
    {
        bool isModified = false;
        if (NonNegative(size.Width()) && (width_ != size.Width())) {
            width_ = size.Width();
            isModified = true;
        }
        if (NonNegative(size.Height()) && (height_ != size.Height())) {
            height_ = size.Height();
            isModified = true;
        }
        return isModified;
    }

    bool UpdateIllegalSizeWithCheck(const OptionalSize& size)
    {
        bool isModified = false;
        if (!width_ && size.Width()) {
            width_ = size.Width();
            isModified = true;
        }
        if (!height_ && size.Height()) {
            height_ = size.Height();
            isModified = true;
        }
        return isModified;
    }

    bool UpdateIllegalSizeWithCheck(const SizeT<T>& size)
    {
        bool isModified = false;
        if (!width_.has_value() && NonNegative(size.Width())) {
            width_ = size.Width();
            isModified = true;
        }
        if (!height_.has_value() && NonNegative(size.Height())) {
            height_ = size.Height();
            isModified = true;
        }
        return isModified;
    }

    bool UpdateSizeWhenLarger(const SizeT<T>& size)
    {
        bool widthUpdated = UpdateWidthWhenLarger(size);
        bool heightUpdated = UpdateHeightWhenLarger(size);
        return widthUpdated || heightUpdated;
    }

    bool UpdateWidthWhenLarger(const SizeT<T>& size)
    {
        bool isModified = false;
        if (NonNegative(size.Width()) && width_) {
            auto temp = width_.value_or(0) > size.Width() ? width_ : size.Width();
            if (width_ != temp) {
                isModified = true;
            }
            width_ = temp;
        }
        return isModified;
    }

    bool UpdateHeightWhenLarger(const SizeT<T>& size)
    {
        bool isModified = false;
        if (NonNegative(size.Height()) && height_) {
            auto temp = height_.value_or(0) > size.Height() ? height_ : size.Height();
            if (height_ != temp) {
                isModified = true;
            }
            height_ = temp;
        }
        return isModified;
    }

    bool UpdateSizeWhenSmaller(const SizeT<T>& size)
    {
        bool widthUpdated = UpdateWidthWhenSmaller(size);
        bool heightUpdated = UpdateHeightWhenSmaller(size);
        return widthUpdated || heightUpdated;
    }

    bool UpdateWidthWhenSmaller(const SizeT<T>& size)
    {
        bool isModified = false;
        if (NonNegative(size.Width())) {
            auto temp = width_.value_or(0) < size.Width() ? width_ : size.Width();
            if (width_ != temp) {
                isModified = true;
            }
            width_ = temp;
        }
        return isModified;
    }

    bool UpdateHeightWhenSmaller(const SizeT<T>& size)
    {
        bool isModified = false;
        if (NonNegative(size.Height())) {
            auto temp = height_.value_or(0) < size.Height() ? height_ : size.Height();
            if (height_ != temp) {
                isModified = true;
            }
            height_ = temp;
        }
        return isModified;
    }

    void UpdateMin(const SizeT<T>& minSize, bool forceOverwriteInvalidValue = false)
    {
        if (NonNegative(minSize.Width()) && (width_ || forceOverwriteInvalidValue)) {
            width_ = width_.value_or(0) > minSize.Width() ? width_ : minSize.Width();
        }
        if (NonNegative(minSize.Height()) && (height_ || forceOverwriteInvalidValue)) {
            height_ = height_.value_or(0) > minSize.Height() ? height_ : minSize.Height();
        }
    }

    void UpdateMax(const SizeT<T>& maxSize, bool forceOverwriteInvalidValue = false)
    {
        if (NonNegative(maxSize.Width()) && (width_ || forceOverwriteInvalidValue)) {
            width_ = width_.value_or(0) < maxSize.Width() ? width_ : maxSize.Width();
        }
        if (NonNegative(maxSize.Height()) && (height_ || forceOverwriteInvalidValue)) {
            height_ = height_.value_or(0) < maxSize.Height() ? Height() : maxSize.Height();
        }
    }

    void Constrain(const SizeT<T>& minSize, const SizeT<T>& maxSize, bool version10OrLarger = false,
        bool forceOverwriteInvalidValue = false)
    {
        if (version10OrLarger) {
            UpdateMax(maxSize, forceOverwriteInvalidValue);
            UpdateMin(minSize, forceOverwriteInvalidValue);
            return;
        }
        UpdateMin(minSize);
        UpdateMax(maxSize);
    }

    void ConstrainFloat(const SizeT<T>& minSize, const SizeT<T>& maxSize, bool isWidth, bool version10OrLarger = false)
    {
        if (isWidth) {
            if (version10OrLarger) {
                if (NonNegative(maxSize.Width()) && width_) {
                    width_ = width_.value_or(0) < maxSize.Width() ? width_ : maxSize.Width();
                }
                if (NonNegative(minSize.Width()) && width_) {
                    width_ = width_.value_or(0) > minSize.Width() ? width_ : minSize.Width();
                }
                return;
            }
            if (NonNegative(minSize.Width()) && width_) {
                width_ = width_.value_or(0) > minSize.Width() ? width_ : minSize.Width();
            }

            if (NonNegative(maxSize.Width()) && width_) {
                width_ = width_.value_or(0) < maxSize.Width() ? width_ : maxSize.Width();
            }
            return;
        }
        if (version10OrLarger) {
            if (NonNegative(maxSize.Height()) && height_) {
                height_ = height_.value_or(0) < maxSize.Height() ? Height() : maxSize.Height();
            }
            if (NonNegative(minSize.Height()) && height_) {
                height_ = height_.value_or(0) > minSize.Height() ? height_ : minSize.Height();
            }
            return;
        }
        if (NonNegative(minSize.Height()) && height_) {
            height_ = height_.value_or(0) > minSize.Height() ? height_ : minSize.Height();
        }
        if (NonNegative(maxSize.Height()) && height_) {
            height_ = height_.value_or(0) < maxSize.Height() ? Height() : maxSize.Height();
        }
    }

    OptionalSize operator*(double value) const
    {
        return OptionalSize(width_ ? *width_.value() * value : width_, height_ ? height_.value() * value : height_);
    }

    bool operator==(const OptionalSize& size) const
    {
        if (width_.has_value() ^ size.width_.has_value()) {
            return false;
        }
        if (!NearEqual(width_.value_or(0), size.width_.value_or(0))) {
            return false;
        }
        if (height_.has_value() ^ size.height_.has_value()) {
            return false;
        }
        if (!NearEqual(height_.value_or(0), size.height_.value_or(0))) {
            return false;
        }
        return true;
    }

    bool operator!=(const OptionalSize& size) const
    {
        return !operator==(size);
    }

    OptionalSize operator+(const OptionalSize& size) const
    {
        std::optional<T> width;
        if (width_) {
            width = width_.value() + size.width_.value_or(0);
        }
        std::optional<T> height;
        if (height_) {
            height = height_.value() + size.height_.value_or(0);
        }
        return OptionalSize(width, height);
    }

    OptionalSize& operator+=(const OptionalSize& size)
    {
        if (width_) {
            width_ = width_.value() + size.width_.value_or(0);
        }
        if (height_) {
            height_ = height_.value() + size.height_.value_or(0);
        }
        return *this;
    }

    OptionalSize operator-(const OptionalSize& size) const
    {
        std::optional<T> width;
        if (width_) {
            width = width_.value() - size.width_.value_or(0);
        }
        std::optional<T> height;
        if (height_) {
            height = height_.value() - size.height_.value_or(0);
        }
        return OptionalSize(width, height);
    }

    OptionalSize& operator-=(const OptionalSize& size)
    {
        if (width_) {
            width_ = width_.value() - size.width_.value_or(0);
        }
        if (height_) {
            height_ = height_.value() - size.height_.value_or(0);
        }
        return *this;
    }

    void ApplyScale(double scale)
    {
        width_ = width_ ? width_.value() * scale : width_;
        height_ = height_ ? height_.value() * scale : height_;
    }

    bool operator>(const SizeT<T>& size) const
    {
        if (IsNonNegative() && size.IsNonNegative()) {
            return GreatOrEqual(width_.value_or(0), size.Width()) && GreatOrEqual(height_.value_or(0), size.Height());
        }
        return false;
    }

    bool operator<(const SizeT<T>& size) const
    {
        if (IsNonNegative() && size.IsNonNegative()) {
            return LessOrEqual(width_.value_or(0), size.Width()) && LessOrEqual(height_.value_or(0), size.Height());
        }
        return false;
    }

    double CalcRatio() const
    {
        if (NearZero(height_.value_or(0))) {
            return 0.0;
        }
        return static_cast<double>(width_.value_or(0)) / static_cast<double>(height_.value());
    }

    SizeT<T> ConvertToSizeT() const
    {
        return { width_.value_or(-1), height_.value_or(-1) };
    }

    std::string ToString() const
    {
        static const int32_t precision = 2;
        std::stringstream ss;
        ss << "[" << std::fixed << std::setprecision(precision);
        if (width_) {
            ss << width_.value();
        } else {
            ss << "NA";
        }
        ss << " x ";
        if (height_) {
            ss << height_.value();
        } else {
            ss << "NA";
        }
        ss << "]";
        std::string output = ss.str();
        return output;
    }

private:
    std::optional<T> width_;
    std::optional<T> height_;
};

using OptionalSizeF = OptionalSize<float>;

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_GEOMETRY_NG_SIZE_T_H
