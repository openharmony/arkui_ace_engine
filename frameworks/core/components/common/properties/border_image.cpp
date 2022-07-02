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

#include "core/components/common/properties/border_image.h"

namespace OHOS::Ace {

void BorderImage::SetEdgeSlice(BorderImageDirection direction, const Dimension& sliceDimension)
{
    switch (direction) {
        case BorderImageDirection::TOP:
            borderImageTop_.SetBorderImageSlice(sliceDimension);
            break;
        case BorderImageDirection::BOTTOM:
            borderImageBottom_.SetBorderImageSlice(sliceDimension);
            break;
        case BorderImageDirection::LEFT:
            borderImageLeft_.SetBorderImageSlice(sliceDimension);
            break;
        case BorderImageDirection::RIGHT:
            borderImageRight_.SetBorderImageSlice(sliceDimension);
            break;
    }
}

void BorderImage::SetEdgeOutset(BorderImageDirection direction, const Dimension& outsetDimension)
{
    switch (direction) {
        case BorderImageDirection::TOP:
        // LOGE("xxy BorderImage::outset TOP set %{public}f", outsetDimension.Value());
            borderImageTop_.SetBorderImageOutset(outsetDimension);
            break;
        case BorderImageDirection::BOTTOM:
        // LOGE("xxy BorderImage::outset BOTTOM set %{public}f", outsetDimension.Value());
            borderImageBottom_.SetBorderImageOutset(outsetDimension);
            break;
        case BorderImageDirection::LEFT:
        // LOGE("xxy BorderImage::outset LEFT set %{public}f", outsetDimension.Value());
            borderImageLeft_.SetBorderImageOutset(outsetDimension);
            break;
        case BorderImageDirection::RIGHT:
        // LOGE("xxy BorderImage::outset RIGHT set %{public}f", outsetDimension.Value());
            borderImageRight_.SetBorderImageOutset(outsetDimension);
            break;
    }
}

void BorderImage::SetEdgeWidth(BorderImageDirection direction, const Dimension& widthDimension)
{
    switch (direction) {
        case BorderImageDirection::TOP:
            borderImageTop_.SetBorderImageWidth(widthDimension);
            break;
        case BorderImageDirection::BOTTOM:
            borderImageBottom_.SetBorderImageWidth(widthDimension);
            break;
        case BorderImageDirection::LEFT:
            borderImageLeft_.SetBorderImageWidth(widthDimension);
            break;
        case BorderImageDirection::RIGHT:
            borderImageRight_.SetBorderImageWidth(widthDimension);
            break;
    }
    if (!hasBorderImageWidth_ && widthDimension.Value() > 0) {
        hasBorderImageWidth_ = true;
    }
}

BorderImageEdge& BorderImage::GetBorderImageEdge(BorderImageDirection direction)
{
    switch (direction) {
        case BorderImageDirection::TOP:
            return borderImageTop_;
        case BorderImageDirection::BOTTOM:
            return borderImageBottom_;
        case BorderImageDirection::LEFT:
            return borderImageLeft_;
        case BorderImageDirection::RIGHT:
            return borderImageRight_;
    }
}
}