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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_IAMGE_COLOR_FILTER_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_IAMGE_COLOR_FILTER_H

#include <vector>

#include "base/memory/ace_type.h"

namespace OHOS {
namespace Ace {
class ImageColorFilter : public AceType {
    DECLARE_ACE_TYPE(ImageColorFilter, AceType);

public:
    ImageColorFilter() = default;
    ~ImageColorFilter() override = default;
    void SetColorFilterMatrix(const std::vector<float>&& matrix)
    {
        colorfiltermatrix_ = std::move(matrix);
    }

    const std::vector<float>& GetColorFilterMatrix() const
    {
        return colorfiltermatrix_;
    }

private:
    std::vector<float> colorfiltermatrix_;
};

} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_IAMGE_COLOR_FILTER_H