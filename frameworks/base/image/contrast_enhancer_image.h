/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_CONTRAST_ENHANCER_IMAGE_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_CONTRAST_ENHANCER_IMAGE_H

#include <cstdint>
#include <string>

#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"

namespace OHOS {
namespace Ace {

struct ContrastEnhancerRect {
    int32_t x = 0;
    int32_t y = 0;
    int32_t w = 0;
    int32_t h = 0;
};

struct ContrastEnhancerInfo {
    int32_t pixelmapId = 0;
    int32_t contentId = 0;
    double curRatio = 0.0;
    double maxRatio = 0.0;
    double defaultRatio = 0.0;
    int32_t animationDuration = 0;
};

enum class ContrastEnhancerErrorCode : int32_t {
    OK = 0,
    ERROR = -1,
};

enum class ContrastEnhancerType : int32_t {
    ADAPTIVE_FOV = 0,
    ADAPTIVE_FOV2 = 1,
};

struct ContrastEnhancerParameters {
    std::string uri;
    ContrastEnhancerType type = ContrastEnhancerType::ADAPTIVE_FOV;
};

class ACE_FORCE_EXPORT ContrastEnhancerImage : public AceType {
    DECLARE_ACE_TYPE(ContrastEnhancerImage, AceType);

public:
    static RefPtr<ContrastEnhancerImage> Create();

    virtual ContrastEnhancerErrorCode SetParameter(const ContrastEnhancerParameters& parameter)
    {
        return ContrastEnhancerErrorCode::ERROR;
    }
    virtual ContrastEnhancerErrorCode ComposeFOVImage(ContrastEnhancerRect displayArea,
        const RefPtr<PixelMap>& oriPixelMap, const RefPtr<PixelMap>& lhdrPixelMap, RefPtr<PixelMap>& outPixelMap,
        const ContrastEnhancerInfo& info)
    {
        return ContrastEnhancerErrorCode::ERROR;
    }
};

} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_CONTRAST_ENHANCER_IMAGE_H
