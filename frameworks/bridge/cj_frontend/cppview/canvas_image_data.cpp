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

#include "bridge/cj_frontend/cppview/canvas_image_data.h"

#include "core/pipeline/pipeline_base.h"
namespace OHOS::Ace::Framework {
constexpr double DIFF = 1e-10;
constexpr int32_t PIXEL_SIZE = 4;

NativeImageData::NativeImageData() : FFIData() {}

NativeImageData::~NativeImageData()
{
    LOGI("Native ImageData Destroyed: %{public}" PRId64, GetID());
}

bool NativeImageData::GetImageDataSize(double width, double height, int32_t& finalWidth, int32_t& finalHeight)
{
    double density = GetDensity();
    width *= density;
    height *= density;
    if (NonPositive(width) || NonPositive(height)) {
        TAG_LOGE(AceLogTag::ACE_CANVAS,
            "Failed to construct 'ImageData': The input 'width' or 'height' is non-positive number or not number.");
        return false;
    }
    // Integer Overflow.
    width += DIFF;
    height += DIFF;
    if ((width > INT32_MAX) || (height > INT32_MAX) || ((width > 0) && (height > (INT32_MAX / width / PIXEL_SIZE)))) {
        return false;
    }
    finalWidth = static_cast<int32_t>(width);
    finalHeight = static_cast<int32_t>(height);
    return true;
}

int32_t NativeImageData::GetHeight() const
{
    return height_;
}

int32_t NativeImageData::GetWidth() const
{
    return width_;
}

std::vector<uint8_t> NativeImageData::GetData() const
{
    return data;
}

double NativeImageData::GetDensity()
{
    double density = PipelineBase::GetCurrentDensity();
    return ((GetUnit() == CanvasUnit::DEFAULT) && !NearZero(density)) ? density : 1.0;
}
} // namespace OHOS::Ace::Framework