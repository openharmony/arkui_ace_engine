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
    OffscreenCanvasPaintMethod(const RefPtr<PipelineContext> context, int32_t width, int32_t height);
    ~OffscreenCanvasPaintMethod() override = default;

    void DrawImage(PaintWrapper* paintWrapper, const Ace::CanvasImage& canvasImage, double width, double height);
    void DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& canvasImage);
    std::unique_ptr<Ace::ImageData> GetImageData(double left, double top, double width, double height);
    std::string ToDataURL(const std::string& type, const double quality);

    void FillText(const std::string& text, double x, double y, const PaintState& state);
    void StrokeText(const std::string& text, double x, double y, const PaintState& state);
    double MeasureText(const std::string& text, const PaintState& state);
    double MeasureTextHeight(const std::string& text, const PaintState& state);
    TextMetrics MeasureTextMetrics(const std::string& text, const PaintState& state);

    int32_t GetWidth()
    {
        return width_;
    }
    int32_t GetHeight()
    {
        return height_;
    }
private:
    void InitFilterFunc();
    void SetGrayFilter(const std::string& percent);
    void SetSepiaFilter(const std::string& percent);
    void SetInvertFilter(const std::string& percent);
    void SetOpacityFilter(const std::string& percent);
    void SetBrightnessFilter(const std::string& percent);
    void SetContrastFilter(const std::string& percent);
    void SetBlurFilter(const std::string& percent);
    void SetDropShadowFilter(const std::string& percent);
    void SetSaturateFilter(const std::string& percent);
    void SetHueRotateFilter(const std::string& percent);
    void SetColorFilter(float matrix[20]);

    bool GetFilterType(std::string& filterType, std::string& filterParam);
    bool IsPercentStr(std::string& percentStr);
    double PxStrToDouble(const std::string& str);
    double BlurStrToDouble(const std::string& str);

    void ImageObjReady(const RefPtr<ImageObject>& imageObj) override;
    void ImageObjFailed() override;

    sk_sp<SkImage> GetImage(const std::string& src) override { return sk_sp<SkImage>(); }
    bool HasImageShadow() const;
    void SetPaintImage() override;

    void PaintText(const std::string& text, double x, double y, bool isStroke, bool hasShadow = false);
    double GetAlignOffset(const std::string& text, TextAlign align, std::unique_ptr<txt::Paragraph>& paragraph);
    double GetBaselineOffset(TextBaseline baseline, std::unique_ptr<txt::Paragraph>& paragraph);
    bool UpdateOffParagraph(const std::string& text, bool isStroke, const PaintState& state, bool hasShadow = false);
    void UpdateTextStyleForeground(bool isStroke, txt::TextStyle& txtStyle, bool hasShadow);
    TextDirection GetTextDirection(const std::string& content);

    int32_t width_;
    int32_t height_;
    std::map<std::string, setColorFunc> filterFunc_;
    Shadow imageShadow_;
    std::string filterParam_ = "";
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_PAINT_METHOD_H
