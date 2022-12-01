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

#define private public
#define protected public
#include "third_party/skia/include/core/SkBitmap.h"
#include "third_party/skia/include/core/SkPictureRecorder.h"

#include "frameworks/base/geometry/dimension.h"
#include "frameworks/base/geometry/ng/offset_t.h"
#include "frameworks/base/geometry/ng/size_t.h"
#include "frameworks/base/utils/utils.h"
#include "frameworks/core/components/common/properties/border_image.h"
#include "frameworks/core/components/common/properties/border_image_edge.h"
#include "frameworks/core/components/common/properties/decoration.h"
#include "frameworks/core/components_ng/base/modifier.h"
#include "frameworks/core/components_ng/render/adapter/rosen_render_context.h"
#include "frameworks/core/components_ng/render/adapter/skia_decoration_painter.h"
#include "frameworks/core/components_ng/render/adapter/svg_canvas_image.h"
#include "frameworks/core/components_ng/render/border_image_painter.h"
#include "frameworks/core/components_ng/render/canvas.h"
#include "frameworks/core/components_ng/render/render_context.h"
#include "frameworks/core/components_ng/render/render_property.h"
#include "frameworks/core/components_ng/test/mock/render/mock_render_context.h"
#undef private
#undef protected

namespace OHOS::Ace {
namespace {
const double DOUBLE_NUMBER = 20.0;
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
        default:
            LOGE("Unsupported border image direction");
    }
    if (!hasBorderImageWidth_ && GreatNotEqual(widthDimension.Value(), 0.0)) {
        hasBorderImageWidth_ = true;
    }
}

BorderImageEdge& BorderImage::GetBorderImageEdge(BorderImageDirection direction)
{
    OHOS::Ace::Dimension RosenDimension(DOUBLE_NUMBER);
    borderImageTop_.SetBorderImageSlice(RosenDimension);
    borderImageBottom_.SetBorderImageSlice(RosenDimension);
    borderImageLeft_.SetBorderImageSlice(RosenDimension);
    borderImageRight_.SetBorderImageSlice(RosenDimension);

    borderImageTop_.SetBorderImageWidth(RosenDimension);
    borderImageBottom_.SetBorderImageWidth(RosenDimension);
    borderImageLeft_.SetBorderImageWidth(RosenDimension);
    borderImageRight_.SetBorderImageWidth(RosenDimension);

    borderImageTop_.SetBorderImageOutset(RosenDimension);
    borderImageBottom_.SetBorderImageOutset(RosenDimension);
    borderImageLeft_.SetBorderImageOutset(RosenDimension);
    borderImageRight_.SetBorderImageOutset(RosenDimension);

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
