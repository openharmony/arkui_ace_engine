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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CORE_PROPERTIES_BORDER_IMAGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CORE_PROPERTIES_BORDER_IMAGE_H

#include <cstdint>

#include "base/geometry/dimension.h"
#include "base/geometry/offset.h"
#include "base/geometry/size.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/border_image_edge.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/radius.h"

namespace OHOS::Ace {

class ACE_EXPORT BorderImage final : public AceType {
    DECLARE_ACE_TYPE(BorderImage, AceType);

public:
    const static uint8_t OUTSET_BIT = 1 << 0;
    const static uint8_t REPEAT_BIT = 1 << 1;
    const static uint8_t SLICE_BIT = 1 << 2;
    const static uint8_t SOURCE_BIT = 1 << 3;
    const static uint8_t WIDTH_BIT = 1 << 4;
    const static uint8_t GRADIENT_BIT = 1 << 5;

    BorderImage() = default;
    explicit BorderImage(const std::string& src)
    {
        src_ = src;
    }

    ~BorderImage() override = default;

    const std::string& GetSrc() const
    {
        return src_;
    }

    void SetSrc(const std::string& src)
    {
        src_ = src;
    }

    struct BorderImageOption {
        std::optional<Dimension> leftDimension;
        std::optional<Dimension> rightDimension;
        std::optional<Dimension> topDimension;
        std::optional<Dimension> bottomDimension;
    };

    void SetEdgeSlice(BorderImageDirection direction, const Dimension& sliceDimension);

    void SetEdgeOutset(BorderImageDirection direction, const Dimension& outsetDimension);

    void SetEdgeWidth(BorderImageDirection direction, const Dimension& widthDimension);

    void SetRepeatMode(BorderImageRepeat repeatMode)
    {
        repeatMode_ = repeatMode;
    }

    BorderImageRepeat GetRepeatMode()
    {
        return repeatMode_;
    }

    void SetNeedFillCenter(bool needFillCenter)
    {
        needFillCenter_ = needFillCenter;
    }

    bool GetNeedFillCenter() const
    {
        return needFillCenter_;
    }

    BorderImageEdge& GetBorderImageEdge(BorderImageDirection direction);

    bool HasBorderImageWidth() const
    {
        return hasBorderImageWidth_;
    }

private:
    std::string src_;
    BorderImageEdge borderImageLeft_;
    BorderImageEdge borderImageTop_;
    BorderImageEdge borderImageRight_;
    BorderImageEdge borderImageBottom_;
    BorderImageRepeat repeatMode_ = BorderImageRepeat::STRETCH;
    bool needFillCenter_ = false;
    bool hasBorderImageWidth_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_CORE_PROPERTIES_BORDER_IMAGE_H
