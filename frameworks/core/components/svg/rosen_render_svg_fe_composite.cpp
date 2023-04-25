/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/core/components/svg/rosen_render_svg_fe_composite.h"

#ifndef NEW_SKIA
#include "include/effects/SkArithmeticImageFilter.h"
#else
#include "third_party/skia/include/effects/SkImageFilters.h"
#endif

namespace OHOS::Ace {

void RosenRenderSvgFeComposite::OnAsImageFilter(const sk_sp<SkImageFilter>& backImageFilter,
    const sk_sp<SkImageFilter>& foreImageFilter, sk_sp<SkImageFilter>& imageFilter) const
{
    if (operatorType_ == FeOperatorType::FE_ARITHMETIC) {
#ifndef NEW_SKIA
        imageFilter =
            SkArithmeticImageFilter::Make(k1_, k2_, k3_, k4_, true, backImageFilter, foreImageFilter, nullptr);
#else
        imageFilter =
            SkImageFilters::Arithmetic(k1_, k2_, k3_, k4_, true, backImageFilter, foreImageFilter, nullptr);
#endif
    } else {
        LOGD("this version skia not support SkBlendImageFilters");
    }
}

} // namespace OHOS::Ace
