/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CANVAS_RENDERER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CANVAS_RENDERER_PEER_IMPL_H


#include "base/geometry/animatable_dimension.h"
#include "base/geometry/rect.h"
#include "base/image/pixel_map.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "base/utils/string_utils.h"
#include "core/common/container_consts.h"
#include "arkoala_api_generated.h"
#include "canvas_path_accessor_peer_impl.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"
#include "core/components_ng/pattern/canvas/canvas_renderer_type.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components/common/properties/decoration.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
struct ImageSizeExt {
    ImageSizeExt()
    {
        x = std::nullopt;
        y = std::nullopt;
        dirtyX = std::nullopt;
        dirtyY = std::nullopt;
        dirtyWidth = std::nullopt;
        dirtyHeight = std::nullopt;
    }
    ~ImageSizeExt() = default;
    std::optional<double> x;
    std::optional<double> y;
    std::optional<double> dirtyX;
    std::optional<double> dirtyY;
    std::optional<double> dirtyWidth;
    std::optional<double> dirtyHeight;
};
class CanvasRendererPeerImpl : public CanvasPathPeerImpl {
public:
    CanvasRendererPeerImpl();
    ~CanvasRendererPeerImpl() override = default;

    void TriggerBeginPathImpl();
    void TriggerStroke0Impl();
    void TriggerRestoreImpl();
    void TriggerSaveImpl();
    void TriggerResetTransformImpl();
    void TriggerSaveLayerImpl();
    void TriggerRestoreLayerImpl();
    void TriggerResetImpl();
    std::optional<LineDashParam> TriggerGetLineDashImpl();
    void TriggerSetLineDashImpl(const std::vector<double>& segments);
    void TriggerClearRectImpl(const Rect& rect);
    void TriggerFillRectImpl(const Rect& rect);
    void TriggerStrokeRectImpl(const Rect& rect);
    void TriggerRotateImpl(double angle);
    void TriggerScaleImpl(double x, double y);
    void TriggerTranslateImpl(double x, double y);
    void TriggerSetGlobalAlphaImpl(double alpha);
    void TriggerFillTextImpl(const std::string& text, double x, double y, std::optional<double> maxWidth);
    void TriggerStrokeTextImpl(const std::string& text, double x, double y, std::optional<double> maxWidth);
    void TriggerSetTransformImpl(const TransformParam& param);
    void TriggerTransformImpl(const TransformParam& param);
    void TriggerSetGlobalCompositeOperationImpl(CompositeOperation& type);
    void TriggerSetFilterImpl(const std::string& filterStr);
    void TriggerSetImageSmoothingEnabledImpl(bool imageSmoothingEnabled);
    double TriggerGetLineDashOffsetImpl();
    void TriggerSetLineDashOffsetImpl(double dash);
    void TriggerSetLineWidthImpl(double width);
    void TriggerSetMiterLimitImpl(double limit);
    void TriggerSetShadowBlurImpl(double blur);
    void TriggerSetShadowColorImpl(Color& color);
    void TriggerSetShadowOffsetXImpl(double offsetX);
    void TriggerSetShadowOffsetYImpl(double offsetY);
    void TriggerStroke1Impl(const RefPtr<CanvasPath2D>& path);
    #ifdef PIXEL_MAP_SUPPORTED
    void TriggerTransferFromImageBitmapImpl(const RefPtr<PixelMap>& pixelMap);
    #else
    void TriggerTransferFromImageBitmapImpl(const double width, const double height);
    #endif
    void TriggerSetFillStyleImpl(const Color& color);
    void TriggerSetFillStyleImpl(const std::shared_ptr<Ace::Gradient>& gradient);
    void TriggerSetFillStyleImpl(const std::weak_ptr<Ace::Pattern>& pattern);
    void TriggerSetStrokeStyleImpl(const Color& color);
    void TriggerSetStrokeStyleImpl(const std::shared_ptr<Ace::Gradient>& gradient);
    void TriggerSetStrokeStyleImpl(const std::weak_ptr<Ace::Pattern>& pattern);
    void SetFont(std::string fontStr);
    std::shared_ptr<OHOS::Ace::Gradient> CreateLinearGradient(
        const double x0, const double y0, const double x1, const double y1);
    std::shared_ptr<OHOS::Ace::Gradient> CreateRadialGradient(const std::vector<double> params);
    std::shared_ptr<OHOS::Ace::Gradient> CreateConicGradient(const double startAngle, const double x, const double y);
    void ClearImageData();
    ImageSize GetImageSize(const double& x, const double& y, const double& width, const double& height);
    std::unique_ptr<Ace::ImageData> GetImageData(const ImageSize& imageSize);
    void GetPixelMap(const ImageSize& imageSize);
    double GetDimension(const Dimension& value, const bool force = false);
    void PutImageData(const Ace::ImageData& src, const ImageSizeExt& ext);
    std::optional<OHOS::Ace::TextMetrics> GetTextMetrics(const std::string& text);
    std::optional<TransformParam> GetTransform();
    void SetPixelMap(RefPtr<PixelMap> pixelMap);
    void SetImageSmoothingQuality(const std::string& quality);
    void SetLineCap(const std::string& quality);
    void SetLineJoin(const std::string& quality);
    void SetUnit(CanvasUnit unit)
    {
        unit_ = unit;
    }
    CanvasUnit GetUnit()
    {
        return unit_;
    }
    void SetDensity()
    {
        double density = GetDensity(true);
        if (!pattern_) {
            LOGE("ARKOALA CanvasRendererPeerImpl::TriggerUpdateFontFamilies pattern not bound to component.");
            return;
        }
        pattern_->SetDensity(density);
    }
    inline double GetDensity(bool useSystemDensity = false)
    {
        if (useSystemDensity) {
            return !NearZero(density_) ? density_ : 1.0;
        } else {
            return ((GetUnit() == CanvasUnit::DEFAULT) && !NearZero(density_)) ? density_ : 1.0;
        }
    }
    RefPtr<CanvasPattern> GetCanvasPattern()
    {
        return pattern_;
    }
    void SetCanvasPattern(const RefPtr<AceType>& pattern)
    {
        CHECK_NULL_VOID(pattern);
        auto canvasPattern = AceType::DynamicCast<CanvasPattern>(pattern);
        CHECK_NULL_VOID(canvasPattern);
        if (pattern_ == canvasPattern) {
            return;
        }
        pattern_ = canvasPattern;
    }

public:
    Ace::ImageData imageData;
    std::unordered_map<int32_t, std::shared_ptr<Ace::Pattern>> patterns;
    uint32_t patternCount = 0;

protected:
    OHOS::Ace::RefPtr<OHOS::Ace::NG::CanvasPattern> pattern_;

private:
    void ParseImageData(const ImageSizeExt& ext);
    Dimension GetDimensionValue(const std::string& str);

    OHOS::Ace::CanvasUnit unit_ = CanvasUnit::DEFAULT;
    double density_ = 1.0;
    int32_t densityCallbackId_ = 0;
    std::vector<OHOS::Ace::PaintState> savePaintState_;
    OHOS::Ace::PaintState paintState_;
};

} // namespace OHOS::Ace::NG::GeneratedModifier
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SCROLLER_PEER_IMPL_H
