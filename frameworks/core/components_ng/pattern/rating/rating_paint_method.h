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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RATING_RATING_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RATING_RATING_PAINT_METHOD_H

#include "core/components_ng/render/image_painter.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT RatingPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(RatingPaintMethod, NodePaintMethod)
public:
    RatingPaintMethod(const RefPtr<CanvasImage>& foregroundImageCanvas, const RefPtr<CanvasImage>& secondaryImageCanvas,
        const RefPtr<CanvasImage>& backgroundImageCanvas, const ImagePaintConfig& singleStarImagePaintConfig,
        int32_t starNum)
        : foregroundImageCanvas_(foregroundImageCanvas), secondaryImageCanvas_(secondaryImageCanvas),
          backgroundImageCanvas_(backgroundImageCanvas), singleStarImagePaintConfig_(singleStarImagePaintConfig),
          starNum_(starNum)
    {}
    ~RatingPaintMethod() override = default;

    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override;

private:
    RefPtr<CanvasImage> foregroundImageCanvas_;
    RefPtr<CanvasImage> secondaryImageCanvas_;
    RefPtr<CanvasImage> backgroundImageCanvas_;

    ImagePaintConfig singleStarImagePaintConfig_;
    int32_t starNum_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(RatingPaintMethod);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RATING_RATING_PAINT_METHOD_H