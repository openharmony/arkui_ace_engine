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

#include "form_snapshot_util.h"

#include <cmath>

#include "base/log/ace_trace.h"
#include "base/log/log_wrapper.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t ALPHA_MASK = 0xFF000000;
constexpr uint8_t ALPHA_8_MASK = 0xFF;
constexpr int32_t THRESHOLD_FOR_NONTRANSPARENCY_RATIO = 10;
constexpr int32_t PERCENTAGE_DENOMINATOR = 100;

uint32_t PixelMapSamplingDump(const std::shared_ptr<Media::PixelMap> &pixelMap, int32_t x, int32_t y)
{
    if (x < 0 || y < 0 || x >= pixelMap->GetWidth() || y >= pixelMap->GetHeight()) {
        TAG_LOGE(AceLogTag::ACE_FORM, "PixelMapSamplingDump fail: x or y invalid");
        return 0;
    }
    uint32_t pixel = 0;
    pixelMap->ReadPixel({x, y}, pixel);
    return pixel;
}
} // namespace

bool FormSnapshotUtil::IsTransparent(const std::shared_ptr<Media::PixelMap> &pixelMap)
{
    if (!pixelMap) {
        TAG_LOGW(AceLogTag::ACE_FORM, "IsTransparent pixelmap is nullptr");
        return true;
    }
    auto pixelDump = PixelMapSamplingDump(pixelMap, pixelMap->GetWidth() / 2, 0) |
                     PixelMapSamplingDump(pixelMap, 0, pixelMap->GetHeight() / 2) |
                     PixelMapSamplingDump(pixelMap, pixelMap->GetWidth() / 2, pixelMap->GetHeight() / 2) |
                     PixelMapSamplingDump(pixelMap, pixelMap->GetWidth() - 2, pixelMap->GetHeight() / 2) |
                     PixelMapSamplingDump(pixelMap, pixelMap->GetWidth() / 2, pixelMap->GetHeight() - 2);
    return (pixelDump & ALPHA_MASK) == 0;
}

bool FormSnapshotUtil::GetNonTransparentRatio(
    const std::shared_ptr<Media::PixelMap> &pixelMap, int32_t &percentageValue)
{
    if (!pixelMap) {
        TAG_LOGE(AceLogTag::ACE_FORM, "GetNonTransparentRatio pixelmap is nullptr");
        return false;
    }
    if (pixelMap->GetWidth() <= 0 || pixelMap->GetHeight() <= 0) {
        TAG_LOGE(AceLogTag::ACE_FORM, "GetNonTransparentRatio width or height not valid");
        return false;
    }
 
    std::shared_ptr<Media::PixelMap> targetPixelMap = pixelMap;
    if (targetPixelMap->GetPixelFormat() != Media::PixelFormat::RGBA_8888) {
        ACE_SCOPED_TRACE("ConvertFormPixelMap_%dx%d", targetPixelMap->GetWidth(), targetPixelMap->GetHeight());
        TAG_LOGW(AceLogTag::ACE_FORM, "pixelFormat[%{public}d] not matched", targetPixelMap->GetPixelFormat());
        Media::InitializationOptions opts = {
            .size = {targetPixelMap->GetWidth(), targetPixelMap->GetHeight()},
            .pixelFormat = Media::PixelFormat::RGBA_8888,
        };
        std::unique_ptr<Media::PixelMap> uniquePixelMap = Media::PixelMap::Create(*targetPixelMap, opts);
        if (!uniquePixelMap) {
            TAG_LOGE(AceLogTag::ACE_FORM, "GetNonTransparentRatio pixelFormat convert failed");
            return false;
        }
        targetPixelMap = std::move(uniquePixelMap);
    }
 
    // PixelFormat::RGBA_8888图像格式单个像素占4个字节
    int32_t pixelBytes = 4;
    const uint32_t *data = reinterpret_cast<const uint32_t *>(targetPixelMap->GetPixels());
    const int32_t dataLength = targetPixelMap->GetByteCount() / pixelBytes;
    if (dataLength == 0) {
        TAG_LOGE(AceLogTag::ACE_FORM, "GetNonTransparentRatio dataLength is 0");
        return false;
    }
 
    AceTraceBeginWithArgs("CalculateTransparentRatio_%dx%d", targetPixelMap->GetWidth(), targetPixelMap->GetHeight());
    int32_t threshold = dataLength * THRESHOLD_FOR_NONTRANSPARENCY_RATIO / PERCENTAGE_DENOMINATOR;
    int32_t count = 0;
    for (int32_t index = 0; index < dataLength; index++) {
        auto pixelDump = data[index];
        if ((pixelDump & ALPHA_MASK) == 0) {
            continue;
        }
        count++;
        if (count >= threshold) {
            break;
        }
    }
    AceTraceEnd();
    percentageValue = std::round((static_cast<double>(count) / dataLength) * PERCENTAGE_DENOMINATOR);
    TAG_LOGW(AceLogTag::ACE_FORM, "GetNonTransparentRatio count:%{public}d, total:%{public}d, percentageValue:%{public}d",
        count, dataLength, percentageValue);
    return true;
}
} // namespace OHOS::Ace::NG
