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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_SVG_DOM_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_SVG_DOM_BASE_H

#include <optional>

#include "base/geometry/ng/size_t.h"
#include "base/geometry/size.h"
#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/render/canvas_image.h"

namespace OHOS::Ace::NG {

class SvgDomBase : public AceType {
    DECLARE_ACE_TYPE(SvgDomBase, AceType);

public:
    virtual SizeF GetContainerSize() const = 0;
    virtual void SetContainerSize(const SizeF& containerSize) = 0;
    virtual void SetSvgFillColor(const std::optional<Color>& color) = 0;
    virtual void DrawImage(
        RSCanvas& canvas, const ImageFit& imageFit, const Size& layout, const std::optional<Color>& color) = 0;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_SVG_DOM_BASE_H
