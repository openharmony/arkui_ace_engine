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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_CONTRAST_ENHANCER_IMAGE_OHOS_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_CONTRAST_ENHANCER_IMAGE_OHOS_H

#include "base/image/contrast_enhancer_image.h"

namespace OHOS {
namespace Media {
namespace VideoProcessingEngine {
class ContrastEnhancerImage;
}
} // namespace Media

namespace Ace {

class ContrastEnhancerImageOhos : public ContrastEnhancerImage {
    DECLARE_ACE_TYPE(ContrastEnhancerImageOhos, ContrastEnhancerImage);

public:
    ContrastEnhancerImageOhos() = default;
    ~ContrastEnhancerImageOhos() override = default;

    ContrastEnhancerErrorCode SetParameter(const ContrastEnhancerParameters& parameter) override;
    ContrastEnhancerErrorCode ComposeFOVImage(ContrastEnhancerRect displayArea, const RefPtr<PixelMap>& oriPixelMap,
        const RefPtr<PixelMap>& lhdrPixelMap, RefPtr<PixelMap>& outPixelMap, const ContrastEnhancerInfo& info) override;

private:
    std::shared_ptr<Media::VideoProcessingEngine::ContrastEnhancerImage> enhancer_;
};

} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_CONTRAST_ENHANCER_IMAGE_OHOS_H
