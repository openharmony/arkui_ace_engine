/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_DRAWING_COLOR_FILTER_OHOS_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_DRAWING_COLOR_FILTER_OHOS_H

#include "effect/color_filter.h"

#include "base/image/drawing_color_filter.h"

namespace OHOS::Ace {

class DrawingColorFilterOhos : public DrawingColorFilter {
public:
    explicit DrawingColorFilterOhos(std::shared_ptr<Rosen::Drawing::ColorFilter> colorFilter)
        : colorFilter_(std::move(colorFilter)) {}
    ~DrawingColorFilterOhos() override = default;
    void* GetDrawingColorFilterSptrAddr() override;
    napi_value GetDrawingColorFilterNapiValue(NativeEngine* nativeEngine) override;

private:
    std::shared_ptr<Rosen::Drawing::ColorFilter> colorFilter_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_DRAWING_COLOR_FILTER_OHOS_H