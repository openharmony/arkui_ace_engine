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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_DATA_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_DATA_H

#include "core/components/common/properties/color.h"
#include "core/components_ng/image_provider/svg_dom_base.h"

namespace OHOS::Ace::NG {

class ImageData : public AceType {
    DECLARE_ACE_TYPE(ImageData, AceType);
public:
    static RefPtr<ImageData> MakeFromDataWithCopy(const void* data, size_t length);
    static RefPtr<ImageData> MakeFromDataWrapper(void* dataWrapper);
    virtual size_t GetSize() const = 0;
    virtual const void* GetData() const = 0;
    virtual RefPtr<SvgDomBase> MakeSvgDom(const std::optional<Color>& svgFillColor) = 0;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_DATA_H
