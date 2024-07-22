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
        case BorderImageDirection::START:
            if (!borderImageStart_.has_value()) {
                borderImageStart_ = BorderImageEdge();
            }
            borderImageStart_->SetBorderImageSlice(sliceDimension);
            break;
        case BorderImageDirection::END:
            if (!borderImageEnd_.has_value()) {
                borderImageEnd_ = BorderImageEdge();
            }
            borderImageEnd_->SetBorderImageSlice(sliceDimension);
            break;
        default:
            LOGE("Unsupported border image direction");
    }
}

void BorderImage::SetEdgeOutset(BorderImageDirection direction, const Dimension& outsetDimension)
{
    switch (direction) {
        case BorderImageDirection::TOP:
            borderImageTop_.SetBorderImageOutset(outsetDimension);
            break;
        case BorderImageDirection::BOTTOM:
            borderImageBottom_.SetBorderImageOutset(outsetDimension);
            break;
        case BorderImageDirection::LEFT:
            borderImageLeft_.SetBorderImageOutset(outsetDimension);
            break;
        case BorderImageDirection::RIGHT:
            borderImageRight_.SetBorderImageOutset(outsetDimension);
            break;
        case BorderImageDirection::START:
            if (!borderImageStart_.has_value()) {
                borderImageStart_ = BorderImageEdge();
            }
            borderImageStart_->SetBorderImageOutset(outsetDimension);
            break;
        case BorderImageDirection::END:
            if (!borderImageEnd_.has_value()) {
                borderImageEnd_ = BorderImageEdge();
            }
            borderImageEnd_->SetBorderImageOutset(outsetDimension);
            break;
        default:
            LOGE("Unsupported border image direction");
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
        case BorderImageDirection::START:
            if (!borderImageStart_.has_value()) {
                borderImageStart_ = BorderImageEdge();
            }
            borderImageStart_->SetBorderImageWidth(widthDimension);
            break;
        case BorderImageDirection::END:
            if (!borderImageEnd_.has_value()) {
                borderImageEnd_ = BorderImageEdge();
            }
            borderImageEnd_->SetBorderImageWidth(widthDimension);
            break;
        default:
            LOGE("Unsupported border image direction");
    }
    if (!hasBorderImageWidth_ && GreatNotEqual(widthDimension.Value(), 0.0)) {
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
        default:
            LOGE("Unsupported border image direction");
            return borderImageLeft_;
    }
}
}