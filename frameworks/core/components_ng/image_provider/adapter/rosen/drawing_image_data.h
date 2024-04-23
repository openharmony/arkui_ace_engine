/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_ADAPTER_ROSEN_DRAWING_IMAGE_DATA_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_ADAPTER_ROSEN_DRAWING_IMAGE_DATA_H

#include "core/components_ng/image_provider/image_data.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/image_provider/svg_dom_base.h"

namespace OHOS::Ace::NG {
class DrawingImageData : public ImageData {
    DECLARE_ACE_TYPE(DrawingImageData, ImageData);
public:
    DrawingImageData(const void* data, size_t length);
    explicit DrawingImageData(std::shared_ptr<RSData> rsData) : rsData_(std::move(rsData)) {}
    size_t GetSize() const override;
    const void* GetData() const override;
    std::shared_ptr<RSData> GetRSData() const;
    std::pair<SizeF, int32_t> Parse() const;
    RefPtr<SvgDomBase> MakeSvgDom(const ImageSourceInfo& src);
    std::string ToString() const override;

private:
    std::shared_ptr<RSData> rsData_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_ADAPTER_ROSEN_DRAWING_IMAGE_DATA_H