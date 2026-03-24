/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/common/interaction/interaction_data.h"

#include "base/image/pixel_map.h"

namespace OHOS::Ace {

// Special member functions for ShadowInfoCore
// Implemented here with full PixelMap definition available
// This allows forward declaration in header while maintaining initialization support
ShadowInfoCore::ShadowInfoCore() = default;
ShadowInfoCore::ShadowInfoCore(const RefPtr<PixelMap>& pm, int32_t ox, int32_t oy)
    : pixelMap(pm), x(ox), y(oy) {}
ShadowInfoCore::~ShadowInfoCore() = default;
ShadowInfoCore::ShadowInfoCore(const ShadowInfoCore&) = default;
ShadowInfoCore::ShadowInfoCore(ShadowInfoCore&&) = default;
ShadowInfoCore& ShadowInfoCore::operator=(const ShadowInfoCore&) = default;
ShadowInfoCore& ShadowInfoCore::operator=(ShadowInfoCore&&) = default;

std::shared_ptr<::OHOS::Media::PixelMap> ShadowInfoCore::GetPixelMapSharedPtr() const
{
    if (pixelMap) {
        return pixelMap->GetPixelMapSharedPtr();
    }
    return nullptr;
}

} // namespace OHOS::Ace
