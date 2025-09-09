/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_PAINT_METHOD_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/pattern/image/image_content_modifier.h"
#include "core/components_ng/pattern/image/image_dfx.h"
#include "core/components_ng/pattern/image/image_overlay_modifier.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paint_wrapper.h"

namespace OHOS::Ace::NG {
struct ImagePaintMethodConfig {
    bool sensitive = false;
    bool selected = false;
    RefPtr<ImageOverlayModifier> imageOverlayModifier;
    RefPtr<ImageContentModifier> imageContentModifier;
    ImageInterpolation interpolation = ImageInterpolation::NONE;
};

class ACE_EXPORT ImagePaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(ImagePaintMethod, NodePaintMethod);
public:
    explicit ImagePaintMethod(
        const RefPtr<CanvasImage>& canvasImage, const ImagePaintMethodConfig& imagePainterMethodConfig = {})
        : selected_(imagePainterMethodConfig.selected), sensitive_(imagePainterMethodConfig.sensitive),
          canvasImage_(canvasImage), interpolationDefault_(imagePainterMethodConfig.interpolation),
          imageOverlayModifier_(imagePainterMethodConfig.imageOverlayModifier),
          imageContentModifier_(imagePainterMethodConfig.imageContentModifier)
    {}
    ~ImagePaintMethod() override = default;

    RefPtr<Modifier> GetOverlayModifier(PaintWrapper* paintWrapper) override;
    void UpdateOverlayModifier(PaintWrapper* paintWrapper) override;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override;
    void UpdateContentModifier(PaintWrapper* paintWrapper) override;
    void UpdatePaintMethod(
        const RefPtr<CanvasImage>& canvasImage, const ImagePaintMethodConfig& imagePainterMethodConfig = {});
    bool NeedsContentTransition();

private:
    void UpdatePaintConfig(PaintWrapper* paintWrapper);
    void UpdateBorderRadius(PaintWrapper* paintWrapper, ImageDfxConfig& imageDfxConfig);

    bool selected_ = false;
    bool sensitive_ = false;

    RefPtr<CanvasImage> canvasImage_;
    ImageInterpolation interpolationDefault_ = ImageInterpolation::NONE;

    RefPtr<ImageOverlayModifier> imageOverlayModifier_;
    RefPtr<ImageContentModifier> imageContentModifier_;

    ACE_DISALLOW_COPY_AND_MOVE(ImagePaintMethod);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_PAINT_METHOD_H
