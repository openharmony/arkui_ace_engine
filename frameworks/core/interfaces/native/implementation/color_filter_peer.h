/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "base/image/image_color_filter.h"
#include "base/memory/referenced.h"

struct ColorFilterPeer final {
    void SetColorFilterMatrix(const std::vector<float>&& matrix)
    {
        if (!colorFilter_) {
            colorFilter_ = OHOS::Ace::Referenced::MakeRefPtr<OHOS::Ace::ImageColorFilter>();
        }
        colorFilter_->SetColorFilterMatrix(std::move(matrix));
    }

    const std::vector<float>& GetColorFilterMatrix() const
    {
        if (!colorFilter_) {
            static const std::vector<float> emptyMatrix;
            return emptyMatrix;
        }
        return colorFilter_->GetColorFilterMatrix();
    }

    OHOS::Ace::RefPtr<OHOS::Ace::ImageColorFilter>& GetColorFilter()
    {
        return colorFilter_;
    }

    void SetColorFilter(const OHOS::Ace::RefPtr<OHOS::Ace::ImageColorFilter>& colorFilter)
    {
        colorFilter_ = colorFilter;
    }

private:
    OHOS::Ace::RefPtr<OHOS::Ace::ImageColorFilter> colorFilter_;
};
