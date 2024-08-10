/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/adapter/skia_color_filter.h"

namespace OHOS::Ace::NG {

RefPtr<ColorFilter> ColorFilter::MakeFromMatrix(const float rowMajor[20])
{
    return AceType::MakeRefPtr<SkiaColorFilter>(rowMajor);
}

SkiaColorFilter::SkiaColorFilter(const float rowMajor[20])
{
    rawColorFilter_ = SkColorFilters::Matrix(rowMajor);
}

sk_sp<SkColorFilter> SkiaColorFilter::GetSkColorFilter() const
{
    return rawColorFilter_;
}

} // namespace OHOS::Ace::NG
