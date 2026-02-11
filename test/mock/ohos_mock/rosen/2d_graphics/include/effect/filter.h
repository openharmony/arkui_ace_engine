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

#ifndef FILTER_H
#define FILTER_H

#include "effect/image_filter.h"
#include "effect/mask_filter.h"
#include "effect/path_effect.h"
#include "utils/scalar.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
class Filter {
public:
    enum class FilterQuality {
        NONE,
        LOW,
        MEDIUM,
        HIGH,
    };

    Filter() noexcept;
    ~Filter() {};

    virtual void SetMaskFilter(std::shared_ptr<MaskFilter> /* maskFilter */) {}

    virtual void SetImageFilter(std::shared_ptr<ImageFilter> /* imageFilter */) {}

    virtual void SetFilterQuality(FilterQuality fq) {}

    virtual void SetColorFilter(std::shared_ptr<ColorFilter> colorFilter) {}
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
