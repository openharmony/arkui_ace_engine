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

class ACE_FORCE_EXPORT BorderImage final : public AceType {
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

    const std::string& GetBundleName()
    {
        return bundleName_;
    }

    void SetBundleName(const std::string& bundleName)
    {
        bundleName_ = bundleName;
    }

    const std::string& GetModuleName()
    {
        return moduleName_;
    }

    void SetModuleName(const std::string& moduleName)
    {
        moduleName_ = moduleName;
    }

    std::string SliceToString()
    {
        std::string str;
        if (borderImageLeft_.GetBorderImageSlice() == borderImageRight_.GetBorderImageSlice() &&
            borderImageRight_.GetBorderImageSlice() == borderImageTop_.GetBorderImageSlice() &&
            borderImageTop_.GetBorderImageSlice() == borderImageBottom_.GetBorderImageSlice()) {
            str.append(borderImageLeft_.GetBorderImageSlice().ToString());
        } else {
            str.append("left: [").append(borderImageLeft_.GetBorderImageSlice().ToString()).append("] ");
            str.append("right: [").append(borderImageRight_.GetBorderImageSlice().ToString()).append("] ");
            str.append("top: [").append(borderImageTop_.GetBorderImageSlice().ToString()).append("] ");
            str.append("bottom: [").append(borderImageBottom_.GetBorderImageSlice().ToString()).append("]");
        }
        return str;
    }

    std::string OutsetToString()
    {
        std::string str;
        if (borderImageLeft_.GetBorderImageOutset() == borderImageRight_.GetBorderImageOutset() &&
            borderImageRight_.GetBorderImageOutset() == borderImageTop_.GetBorderImageOutset() &&
            borderImageTop_.GetBorderImageOutset() == borderImageBottom_.GetBorderImageOutset()) {
            str.append(borderImageLeft_.GetBorderImageOutset().ToString());
        } else {
            str.append("left: [").append(borderImageLeft_.GetBorderImageOutset().ToString()).append("] ");
            str.append("right: [").append(borderImageRight_.GetBorderImageOutset().ToString()).append("] ");
            str.append("top: [").append(borderImageTop_.GetBorderImageOutset().ToString()).append("] ");
            str.append("bottom: [").append(borderImageBottom_.GetBorderImageOutset().ToString()).append("]");
        }
        return str;
    }

    std::string WidthToString()
    {
        std::string str;
        if (borderImageLeft_.GetBorderImageWidth() == borderImageRight_.GetBorderImageWidth() &&
            borderImageRight_.GetBorderImageWidth() == borderImageTop_.GetBorderImageWidth() &&
            borderImageTop_.GetBorderImageWidth() == borderImageBottom_.GetBorderImageWidth()) {
            str.append(borderImageLeft_.GetBorderImageWidth().ToString());
        } else {
            str.append("left: [").append(borderImageLeft_.GetBorderImageWidth().ToString()).append("] ");
            str.append("right: [").append(borderImageRight_.GetBorderImageWidth().ToString()).append("] ");
            str.append("top: [").append(borderImageTop_.GetBorderImageWidth().ToString()).append("] ");
            str.append("bottom: [").append(borderImageBottom_.GetBorderImageWidth().ToString()).append("]");
        }
        return str;
    }

    struct BorderImageOption {
        std::optional<Dimension> leftDimension;
        std::optional<Dimension> rightDimension;
        std::optional<Dimension> topDimension;
        std::optional<Dimension> bottomDimension;
        std::optional<Dimension> startDimension;
        std::optional<Dimension> endDimension;
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

    std::optional<BorderImageEdge> borderImageStart_;
    std::optional<BorderImageEdge> borderImageEnd_;
private:
    std::string src_;
    std::string bundleName_;
    std::string moduleName_;
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
