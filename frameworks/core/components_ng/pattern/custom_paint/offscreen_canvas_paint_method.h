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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_OFFSCREEN_CANVAS_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_OFFSCREEN_CANVAS_PAINT_METHOD_H

#include "core/components_ng/pattern/custom_paint/custom_paint_paint_method.h"

namespace OHOS::Ace::NG {
using setColorFunc = std::function<void (const std::string&)>;

class OffscreenCanvasPaintMethod : public CustomPaintPaintMethod {
    DECLARE_ACE_TYPE(OffscreenCanvasPaintMethod, CustomPaintPaintMethod)
public:
    OffscreenCanvasPaintMethod() = default;
    OffscreenCanvasPaintMethod(int32_t width, int32_t height);
    ~OffscreenCanvasPaintMethod() override = default;

    void DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& canvasImage);
    std::unique_ptr<Ace::ImageData> GetImageData(double left, double top, double width, double height);
    void GetImageData(const std::shared_ptr<Ace::ImageData>& imageData);
    std::string ToDataURL(const std::string& type, const double quality);

    void FillText(const std::string& text, double x, double y, std::optional<double> maxWidth, const PaintState& state);
    void StrokeText(
        const std::string& text, double x, double y, std::optional<double> maxWidth, const PaintState& state);
    double MeasureText(const std::string& text, const PaintState& state);
    double MeasureTextHeight(const std::string& text, const PaintState& state);
    TextMetrics MeasureTextMetrics(const std::string& text, const PaintState& state);
    void SetTransform(const TransformParam& param) override;
    TransformParam GetTransform() const override;
    void UpdateSize(int32_t width, int32_t height);
    void Reset();
    int32_t GetWidth()
    {
        return width_;
    }
    int32_t GetHeight()
    {
        return height_;
    }
    bool IsSucceed()
    {
        return isSucceed_;
    }
    size_t GetBitmapSize()
    {
        return bitmapSize_;
    }
private:
    void InitBitmap();
    void ImageObjReady(const RefPtr<Ace::ImageObject>& imageObj) override;
    void ImageObjFailed() override;
    void PaintText(const std::string& text, double x, double y, std::optional<double> maxWidth, bool isStroke,
        bool hasShadow = false);
    double GetBaselineOffset(TextBaseline baseline, std::unique_ptr<OHOS::Rosen::Typography>& paragraph);
    bool UpdateOffParagraph(const std::string& text, bool isStroke, const PaintState& state, bool hasShadow = false);
    void UpdateTextStyleForeground(bool isStroke, OHOS::Rosen::TextStyle& txtStyle, bool hasShadow);
    void PaintShadow(const RSPath& path, const Shadow& shadow, RSCanvas* canvas,
        const RSBrush* brush = nullptr, const RSPen* pen = nullptr) override;
    void Path2DRect(const PathArgs& args) override;
    RSCanvas* GetRawPtrOfRSCanvas() override
    {
        return rsCanvas_.get();
    }

    RSBitmap bitmap_;

    int32_t width_;
    int32_t height_;
    bool isSucceed_ = true;
    size_t bitmapSize_ = 0;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_PAINT_METHOD_H
