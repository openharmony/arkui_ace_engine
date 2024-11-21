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

#include "base/geometry/rect.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "base/utils/string_utils.h"
#include "arkoala_api.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components/common/properties/decoration.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {

class CanvasRendererPeerImpl : public Referenced {
public:
    CanvasRendererPeerImpl() = default;
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
    void TriggerTransferFromImageBitmapImpl(const Ace::ImageData& imageData);
    #endif
    void TriggerSetFillStyleImpl(const Color& color);
    void TriggerSetFillStyleImpl(const std::shared_ptr<Ace::Gradient>& gradient);
    void TriggerSetFillStyleImpl(const std::weak_ptr<Ace::Pattern>& pattern);
    void TriggerSetStrokeStyleImpl(const Color& color);
    void TriggerSetStrokeStyleImpl(const std::shared_ptr<Ace::Gradient>& gradient);
    void TriggerSetStrokeStyleImpl(const std::weak_ptr<Ace::Pattern>& pattern);
    void TriggerUpdateFontWeight(Ace::FontWeight weight);
    void TriggerUpdateFontStyle(Ace::FontStyle style);
    void TriggerUpdateFontFamilies(const std::vector<std::string>& families);
    void TriggerUpdateFontSize(const Dimension& size);

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

private:
    RefPtr<CanvasPattern> pattern_;
};

} // namespace OHOS::Ace::NG::GeneratedModifier
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SCROLLER_PEER_IMPL_H
