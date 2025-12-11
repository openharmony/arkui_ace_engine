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

#include "base/geometry/response_region.h"

namespace OHOS::Ace {
ResponseRegion::ResponseRegion(const NG::ResponseRegionSupportedTool& tool, const CalcDimension& x,
    const CalcDimension& y, const CalcDimension& width, const CalcDimension& height)
    : tool_(tool), width_(width), height_(height), x_(x), y_(y)
{}

ResponseRegion::ResponseRegion(const ResponseRegion& responseRegion)
{
    tool_ = responseRegion.GetTool();
    width_ = responseRegion.GetWidth();
    height_ = responseRegion.GetHeight();
    x_ = responseRegion.GetX();
    y_ = responseRegion.GetY();
}

const NG::ResponseRegionSupportedTool& ResponseRegion::GetTool() const
{
    return tool_;
}

const CalcDimension& ResponseRegion::GetWidth() const
{
    return width_;
}

const CalcDimension& ResponseRegion::GetHeight() const
{
    return height_;
}

const CalcDimension& ResponseRegion::GetX() const
{
    return x_;
}

const CalcDimension& ResponseRegion::GetY() const
{
    return y_;
}

void ResponseRegion::SetWidth(const CalcDimension& width)
{
    width_ = width;
}

void ResponseRegion::SetHeight(const CalcDimension& height)
{
    height_ = height;
}

void ResponseRegion::SetX(const CalcDimension& x)
{
    x_ = x;
}

void ResponseRegion::SetY(const CalcDimension& y)
{
    y_ = y;
}

void ResponseRegion::SetTool(const NG::ResponseRegionSupportedTool& tool)
{
    tool_ = tool;
}

ResponseRegion& ResponseRegion::operator=(const ResponseRegion& responseRegion)
{
    SetWidth(responseRegion.GetWidth());
    SetHeight(responseRegion.GetHeight());
    SetX(responseRegion.GetX());
    SetY(responseRegion.GetY());
    SetTool(responseRegion.GetTool());
    return *this;
}
} // namespace OHOS::Ace