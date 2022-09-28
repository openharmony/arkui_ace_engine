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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_PAINT_METHOD_H

#include "experimental/svg/model/SkSVGDOM.h"
#include "flutter/third_party/txt/src/txt/paragraph.h"
#include "third_party/skia/include/core/SkPath.h"

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/render/adapter/skia_canvas.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/image/image_loader.h"
#include "core/image/image_object.h"
#include "core/image/image_source_info.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class CustomPaintPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(CustomPaintPaintMethod, NodePaintMethod)
public:
    ~CustomPaintPaintMethod() override = default;

    void SetFillColor(const Color& color)
    {
        fillState_.SetColor(color);
        fillState_.SetTextColor(color);
    }

    void FillRect(PaintWrapper* paintWrapper, const Rect& rect);
    void StrokeRect(PaintWrapper* paintWrapper, const Rect& rect);

    virtual std::unique_ptr<Ace::ImageData> GetImageData(double left, double top, double width, double height) = 0;
    void PutImageData(PaintWrapper* paintWrapper, const Ace::ImageData& imageData);

protected:
    bool HasShadow() const;
    void UpdateLineDash(SkPaint& paint);
    void UpdatePaintShader(const OffsetF& offset, SkPaint& paint, const Ace::Gradient& gradient);
    void UpdatePaintShader(const Ace::Pattern& pattern, SkPaint& paint);
    void InitPaintBlend(SkPaint& paint);
    SkPaint GetStrokePaint();

    PaintState fillState_;
    StrokePaintState strokeState_;

    // save alpha and compositeType in GlobalPaintState
    GlobalPaintState globalState_;

    bool smoothingEnabled_ = true;
    std::string smoothingQuality_ = "low";
    bool antiAlias_ = false;
    Shadow shadow_;
    bool isOffscreen_ = false;

    RefPtr<PipelineContext> context_;

    SkPaint imagePaint_;
    SkPaint cachePaint_;
    SkBitmap cacheBitmap_;
    SkBitmap canvasCache_;
    std::unique_ptr<SkCanvas> skCanvas_;
    std::unique_ptr<SkCanvas> cacheCanvas_;

    RefPtr<FlutterRenderTaskHolder> renderTaskHolder_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_PAINT_METHOD_H
