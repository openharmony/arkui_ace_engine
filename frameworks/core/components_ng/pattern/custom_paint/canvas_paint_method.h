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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_PAINT_METHOD_H

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/custom_paint/canvas_paint_op.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_paint_method.h"
#include "core/components_ng/pattern/custom_paint/offscreen_canvas_pattern.h"

#ifdef USE_FAST_TASKPOOL
#include <memory>
#endif

namespace OHOS::Ace::NG {
class CanvasPaintMethod;
class RosenRenderContext;
using TaskFunc = std::function<void(CanvasPaintMethod&)>;
using OnModifierUpdateFunc = std::function<void(void)>;
class CanvasPaintMethod : public CustomPaintPaintMethod {
    DECLARE_ACE_TYPE(CanvasPaintMethod, CustomPaintPaintMethod)
public:
    CanvasPaintMethod() = default;
    CanvasPaintMethod(const WeakPtr<PipelineBase> context, RefPtr<RenderingContext2DModifier> contentModifier,
        const WeakPtr<FrameNode>& frameNode)
        : frameNode_(frameNode)
    {
        matrix_.reset();
        context_ = context;
        imageShadow_ = std::make_unique<Shadow>();
        contentModifier_ = contentModifier;
        InitImageCallbacks();
    }

    ~CanvasPaintMethod() override = default;

    void GetFastTaskPool();
    void UpdateContentModifier(PaintWrapper* paintWrapper) override;

#ifndef USE_FAST_TASKPOOL
    void PushTask(const TaskFunc& task);
#endif
    bool HasTask() const;
    void FlushTask();

    double GetWidth()
    {
        return lastLayoutSize_.Width();
    }

    double GetHeight()
    {
        return lastLayoutSize_.Height();
    }

    void SetOnModifierUpdateFunc(OnModifierUpdateFunc&& func)
    {
        onModifierUpdate_ = std::move(func);
    }

    void CloseImageBitmap(const std::string& src);
    void DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& canvasImage);
    void DrawPixelMapWithoutGlobalState(const RefPtr<PixelMap>& pixelMap, const Ace::CanvasImage& canvasImage);
    std::unique_ptr<Ace::ImageData> GetImageData(
        RefPtr<RosenRenderContext> renderContext, double left, double top, double width, double height);
    void GetImageData(const RefPtr<RenderContext>& renderContext, const std::shared_ptr<Ace::ImageData>& imageData);
    void TransferFromImageBitmap(const RefPtr<OffscreenCanvasPattern>& offscreenCanvas);
    std::string ToDataURL(RefPtr<RosenRenderContext> renderContext, const std::string& args);
    bool DrawBitmap(RefPtr<RosenRenderContext> renderContext, RSBitmap& currentBitmap);
    std::string GetJsonData(const std::string& path);

    void FillText(const std::string& text, double x, double y, std::optional<double> maxWidth);
    void StrokeText(const std::string& text, double x, double y, std::optional<double> maxWidth);
    double MeasureText(const std::string& text, const PaintState& state);
    double MeasureTextHeight(const std::string& text, const PaintState& state);
    TextMetrics MeasureTextMetrics(const std::string& text, const PaintState& state);
    void SetTransform(const TransformParam& param) override;
    void Reset();

private:
    void ImageObjReady(const RefPtr<Ace::ImageObject>& imageObj) override;
    void ImageObjFailed() override;
    void PaintText(const SizeF& contentSize, double x, double y, std::optional<double> maxWidth, bool isStroke,
        bool hasShadow = false);
    double GetBaselineOffset(TextBaseline baseline, std::unique_ptr<OHOS::Rosen::Typography>& paragraph);
    bool UpdateParagraph(const std::string& text, bool isStroke, bool hasShadow = false);
    void UpdateTextStyleForeground(bool isStroke, Rosen::TextStyle& txtStyle, bool hasShadow);
    void PaintShadow(const RSPath& path, const Shadow& shadow, RSCanvas* canvas, const RSBrush* brush = nullptr,
        const RSPen* pen = nullptr) override;
    void Path2DRect(const PathArgs& args) override;
    RSCanvas* GetRawPtrOfRSCanvas() override
    {
        return rsCanvas_.get();
    }
#ifndef USE_FAST_TASKPOOL
    std::list<TaskFunc> tasks_;
    bool needMarkDirty_ = true;
#else
    friend class CustomPaintPattern;
    std::unique_ptr<CanvasPaintOp> fastTaskPool_ = std::make_unique<CanvasPaintOp>();
#endif

    RefPtr<Ace::ImageObject> imageObj_ = nullptr;
    OnModifierUpdateFunc onModifierUpdate_;
    WeakPtr<FrameNode> frameNode_;

    ACE_DISALLOW_COPY_AND_MOVE(CanvasPaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_PAINT_METHOD_H
