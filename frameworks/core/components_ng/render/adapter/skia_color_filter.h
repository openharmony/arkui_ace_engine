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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SKIA_COLOR_FILTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SKIA_COLOR_FILTER_H

#include "include/core/SkColorFilter.h"
#include "include/core/SkRefCnt.h"

#include "core/components_ng/render/color_filter.h"

namespace OHOS::Ace::NG {

// Paint is interface for drawing styles.
class SkiaColorFilter : public ColorFilter {
    DECLARE_ACE_TYPE(NG::SkiaColorFilter, NG::ColorFilter);
public:
    explicit SkiaColorFilter(const float rowMajor[20]);
    ~SkiaColorFilter() override = default;

    sk_sp<SkColorFilter> GetSkColorFilter() const;

private:
    sk_sp<SkColorFilter> rawColorFilter_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SKIA_COLOR_FILTER_H
