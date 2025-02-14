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

#include "core/components_ng/svg/effect/svg_colorfilter_effect.h"

namespace OHOS::Ace::NG {
std::shared_ptr<RSRecordingColorFilter> SvgColorFilterEffect::GetRsColorFilter(const ImageColorFilter& imageColorFilter)
{
    if (imageColorFilter.colorFilterMatrix_) {
        RSColorMatrix colorMatrix;
        colorMatrix.SetArray(imageColorFilter.colorFilterMatrix_->data());
        return RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix);
    }
    if (!imageColorFilter.colorFilterDrawing_) {
        return nullptr;
    }
    auto colorFilterSptrAddr = static_cast<std::shared_ptr<RSColorFilter>*>(
        imageColorFilter.colorFilterDrawing_->GetDrawingColorFilterSptrAddr());
    if (!colorFilterSptrAddr || !(*colorFilterSptrAddr)) {
        return nullptr;
    }
    return *colorFilterSptrAddr;
}
}