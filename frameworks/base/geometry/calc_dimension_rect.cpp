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

#include "base/geometry/calc_dimension_rect.h"
#include "base/json/json_util.h"

namespace OHOS::Ace {
CalcDimensionRect::CalcDimensionRect(
    const CalcDimension& width, const CalcDimension& height, const CalcDimension& x, const CalcDimension& y)
    : width_(width), height_(height), x_(x), y_(y)
{}

CalcDimensionRect::CalcDimensionRect(const DimensionRect& dimensionRect)
{
    width_ = dimensionRect.GetWidth();
    height_ = dimensionRect.GetHeight();
    x_ = dimensionRect.GetOffset().GetX();
    y_ = dimensionRect.GetOffset().GetY();
}

const CalcDimension& CalcDimensionRect::GetWidth() const
{
    return width_;
}

const CalcDimension& CalcDimensionRect::GetHeight() const
{
    return height_;
}

const CalcDimension& CalcDimensionRect::GetX() const
{
    return x_;
}

const CalcDimension& CalcDimensionRect::GetY() const
{
    return y_;
}

void CalcDimensionRect::SetWidth(const CalcDimension& width)
{
    width_ = width;
}

void CalcDimensionRect::SetHeight(const CalcDimension& height)
{
    height_ = height;
}

void CalcDimensionRect::SetX(const CalcDimension& x)
{
    x_ = x;
}

void CalcDimensionRect::SetY(const CalcDimension& y)
{
    y_ = y;
}

std::string CalcDimensionRect::ToString() const
{
    static const int32_t precision = 2;
    std::stringstream ss;
    ss << "Rect (" << std::fixed << std::setprecision(precision) << x_.ToString() << ", "
        << y_.ToString() << ") - [";
    ss << width_.ToString();
    ss << " x ";
    ss << height_.ToString();
    ss << "]";
    std::string output = ss.str();
    return output;
}

std::string CalcDimensionRect::ToJsonString() const
{
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("x", x_.ToString().c_str());
    jsonValue->Put("y", y_.ToString().c_str());
    jsonValue->Put("width", width_.ToString().c_str());
    jsonValue->Put("height", height_.ToString().c_str());
    return jsonValue->ToString();
}

CalcDimensionRect& CalcDimensionRect::operator=(const DimensionRect& newDimension)
{
    SetWidth(newDimension.GetWidth());
    SetHeight(newDimension.GetHeight());
    SetX(newDimension.GetOffset().GetX());
    SetY(newDimension.GetOffset().GetY());
    return *this;
}
} // namespace OHOS::Ace