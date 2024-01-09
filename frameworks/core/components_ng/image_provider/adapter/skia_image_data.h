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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_ADAPTER_SKIA_IMAGE_DATA_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_ADAPTER_SKIA_IMAGE_DATA_H

#include "include/core/SkData.h"

#include "core/components_ng/image_provider/image_data.h"
#include "core/components_ng/image_provider/svg_dom_base.h"

namespace OHOS::Ace::NG {

class SkiaImageData : public ImageData {
    DECLARE_ACE_TYPE(SkiaImageData, ImageData);
public:
    SkiaImageData(const void* data, size_t length);
    explicit SkiaImageData(sk_sp<SkData> skData) : skData_(std::move(skData)) {}
    size_t GetSize() const override;
    const void* GetData() const override;
    sk_sp<SkData> GetSkData() const;
    const void* GetDataWrapper() const override;

    std::pair<SizeF, int32_t> Parse() const;
    RefPtr<SvgDomBase> MakeSvgDom(const std::optional<Color>& svgFillColor);
    std::string ToString() const override;

private:
    sk_sp<SkData> skData_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_ADAPTER_SKIA_IMAGE_DATA_H