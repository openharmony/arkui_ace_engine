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

#include "base/log/log_wrapper.h"

namespace OHOS::Ace {

BorderImage::BorderImage(const std::string& src)
{
    src_ = src;
}

const std::string& BorderImage::GetSrc() const
{
    return src_;
}

void BorderImage::SetSrc(const std::string& src)
{
    src_ = src;
}

const std::string& BorderImage::GetBundleName()
{
    return bundleName_;
}

void BorderImage::SetBundleName(const std::string& bundleName)
{
    bundleName_ = bundleName;
}

const std::string& BorderImage::GetModuleName()
{
    return moduleName_;
}

void BorderImage::SetModuleName(const std::string& moduleName)
{
    moduleName_ = moduleName;
}

std::string BorderImage::SliceToString()
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

std::string BorderImage::OutsetToString()
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

std::string BorderImage::WidthToString()
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

void BorderImage::SetRepeatMode(BorderImageRepeat repeatMode)
{
    repeatMode_ = repeatMode;
}

BorderImageRepeat BorderImage::GetRepeatMode()
{
    return repeatMode_;
}

void BorderImage::SetNeedFillCenter(bool needFillCenter)
{
    needFillCenter_ = needFillCenter;
}

bool BorderImage::GetNeedFillCenter() const
{
    return needFillCenter_;
}

bool BorderImage::HasBorderImageWidth() const
{
    return hasBorderImageWidth_;
}

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

} // namespace OHOS::Ace