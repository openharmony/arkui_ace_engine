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
#include "core/components_ng/pattern/image/image_modifier.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paint_wrapper.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ImagePaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(ImagePaintMethod, NodePaintMethod)
public:
    explicit ImagePaintMethod(const RefPtr<CanvasImage>& canvasImage, bool selected)
        : canvasImage_(canvasImage), selected_(selected)
    {}
    ~ImagePaintMethod() override = default;

    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override;
    CanvasDrawFunction GetOverlayDrawFunction(PaintWrapper* paintWrapper) override;

private:
    void UpdatePaintConfig(const RefPtr<ImageRenderProperty>& renderProps, PaintWrapper* paintWrapper);
    void UpdateBorderRadius(PaintWrapper* paintWrapper);
    RefPtr<CanvasImage> canvasImage_;
    bool selected_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(ImagePaintMethod);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_PAINT_METHOD_H