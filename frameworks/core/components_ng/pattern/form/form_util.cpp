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

#include "form_util.h"
#include "base/log/log_wrapper.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t ALPHA_MASK = 0xFF000000;

uint32_t PixelMapSamplingDump(std::shared_ptr<Media::PixelMap>& pixelMap, int32_t x, int32_t y)
{
    if (x < 0 || y < 0 || x >= pixelMap->GetWidth() || y >= pixelMap->GetHeight()) {
        TAG_LOGE(AceLogTag::ACE_FORM, "FormUtil::PixelMapSamplingDump fail: x or y invalid");
        return 0;
    }
    uint32_t pixel = 0;
    pixelMap->ReadPixel({x, y}, pixel);
    return pixel;
}
} // namespace

/**
 * @brief Determine whether the snapshot is transparent.
 * @param pixelMap the snapshot of SurfaceNode
 * @return true if the snapshot is transparent, false otherwise.
 */
bool FormUtil::IsTransparent(std::shared_ptr<Media::PixelMap>& pixelMap)
{
    if (!pixelMap) {
        TAG_LOGW(AceLogTag::ACE_FORM, "FormPattern::OnSnapshot pixelmap is nullptr");
        return true;
    }
    auto pixelDump = PixelMapSamplingDump(pixelMap, pixelMap->GetWidth() / 2, 0) |
                     PixelMapSamplingDump(pixelMap, 0, pixelMap->GetHeight() / 2) |
                     PixelMapSamplingDump(pixelMap, pixelMap->GetWidth() / 2, pixelMap->GetHeight() / 2) |
                     PixelMapSamplingDump(pixelMap, pixelMap->GetWidth() - 1, pixelMap->GetHeight() / 2) |
                     PixelMapSamplingDump(pixelMap, pixelMap->GetWidth() / 2, pixelMap->GetHeight() - 1);
    return (pixelDump & ALPHA_MASK) == 0;
}
} // namespace OHOS::Ace::NG
