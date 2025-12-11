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

int32_t FormSnapshotUtil::GetNonTransparentRatio(const std::shared_ptr<Media::PixelMap> &pixelMap)
{
    if (!pixelMap) {
        TAG_LOGW(AceLogTag::ACE_FORM, "GetNonTransparentRatio pixelmap is nullptr");
        return 0;
    }

    AceTraceBeginWithArgs("CreateAlphaPixelMap_%dx%d", pixelMap->GetWidth(), pixelMap->GetHeight());
    Media::InitializationOptions opts = {
        .size = {pixelMap->GetWidth(), pixelMap->GetHeight()},
        .pixelFormat = Media::PixelFormat::ALPHA_8,
    };
    std::unique_ptr<Media::PixelMap> alphaPixelMap = Media::PixelMap::Create(*pixelMap, opts);
    AceTraceEnd();
    if (!alphaPixelMap) {
        TAG_LOGE(AceLogTag::ACE_FORM, "GetNonTransparentRatio create new pixel map failed");
        return 0;
    }

    AceTraceBeginWithArgs("CalculateTransparentRatio_%dx%d", pixelMap->GetWidth(), pixelMap->GetHeight());
    const uint8_t *data = alphaPixelMap->GetPixels();
    const int32_t dataLength = alphaPixelMap->GetByteCount();
    int32_t threshold = dataLength * THRESHOLD_FOR_NONTRANSPARENCY_RATIO / PERCENTAGE_DENOMINATOR;
    int32_t count = 0;
    for (int32_t index = 0; index < dataLength; index++) {
        auto pixelDump = data[index];
        if ((pixelDump & ALPHA_8_MASK) == 0) {
            continue;
        }
        count++;
        if (count >= threshold) {
            break;
        }
    }
    AceTraceEnd();
    
    if (count == 0 || dataLength == 0) {
        return 0;
    }

    if (count >= threshold) {
        return THRESHOLD_FOR_NONTRANSPARENCY_RATIO;
    }

    int32_t percentageValue = std::round((static_cast<double>(count) / dataLength) * PERCENTAGE_DENOMINATOR);
    TAG_LOGW(AceLogTag::ACE_FORM,
        "GetNonTransparentRatio count:%{public}d, total:%{public}d, percentageValue:%{public}d", count, dataLength,
        percentageValue);
    return percentageValue;
}
} // namespace OHOS::Ace::NG
