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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_MODIFIER_H

#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/image_painter.h"

namespace OHOS::Ace::NG {
constexpr float ANIMATION_END = 1.0f; // The image animation end with 1.0
constexpr uint32_t TWICE = 2;         // use to calculate image new width and height
constexpr double EPSILON = 0.0001;    // use to judge the end of action

// not in use, causes performance issues
class ImageModifier : public ContentModifier {
    DECLARE_ACE_TYPE(ImageModifier, ContentModifier);

public:
    ImageModifier();
    ~ImageModifier() override = default;
    void onDraw(DrawingContext& context) override;
    void SetImageFit(ImageFit imagefit);
    void UpdateImageData(const WeakPtr<CanvasImage>& canvasImage, const OffsetF& offset, const SizeF& contentSize);
    void Modify();
    void SetIsAltImage(bool isAltImage);

private:
    float GetValue(float value) const;
    void DrawImageWithAnimation(DrawingContext& context);
    void DrawImageWithoutAnimation(DrawingContext& context) const;
    void UpdatePaintConfig(float ratio);
    OffsetF offset_;
    SizeF contentSize_;
    RectF startSrcRect_;
    RectF endSrcRect_;
    RectF startDstRect_;
    RectF endDstRect_;
    ImageFit startImageFit_ = ImageFit::COVER;
    ImageFit endImageFit_ = ImageFit::COVER;
    bool isFirst_ = true;
    WeakPtr<CanvasImage> canvasImage_;
    RefPtr<AnimatablePropertyFloat> imageFit_;
    RefPtr<PropertyBool> flag_;
    bool isAltImage_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(ImageModifier);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_MODIFIER_H
