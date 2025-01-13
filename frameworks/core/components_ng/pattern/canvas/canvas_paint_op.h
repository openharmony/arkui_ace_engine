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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_PAINT_OP_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_PAINT_OP_H

#include <memory>
#include <optional>

#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/pattern/canvas/canvas_paint_mem.h"

namespace OHOS::Ace {
struct BezierCurveParam;
class Rect;
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
class CanvasPaintMethod;
class OffscreenCanvasPattern;
class SvgDomBase;

#define X(T) T,
enum class Type : uint8_t {
#include "canvas_paint_ops.in"
};
#undef X

struct Op {
    uint32_t type : 8;
    uint32_t skip : 24;
};
static_assert(sizeof(Op) == 4, "size of canvas op shoule be 4");

struct SaveOp final : Op {
    static constexpr auto kType = Type::SaveOp;
    void Draw(CanvasPaintMethod* method) const;
};

struct RestoreOp final : Op {
    static constexpr auto kType = Type::RestoreOp;
    void Draw(CanvasPaintMethod* method) const;
};

struct FillRectOp final : Op {
    static constexpr auto kType = Type::FillRectOp;
    explicit FillRectOp(const Rect& rect): rect(std::move(rect)) {}
    Rect rect;
    void Draw(CanvasPaintMethod* method) const;
};

struct FillTextOp final : Op {
    static constexpr auto kType = Type::FillTextOp;
    FillTextOp(const std::string& text, double x, double y, std::optional<double> maxWidth)
        : text(std::move(text)), x(x), y(y), maxWidth(maxWidth) {}
    std::string text;
    double x, y;
    std::optional<double> maxWidth;
    void Draw(CanvasPaintMethod* method) const;
};

struct BezierCurveToOp final : Op {
    static constexpr auto kType = Type::BezierCurveToOp;
    explicit BezierCurveToOp(const BezierCurveParam& param): param(std::move(param)) {}
    BezierCurveParam param;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetTransformOp final : Op {
    static constexpr auto kType = Type::SetTransformOp;
    explicit SetTransformOp(const TransformParam& param): param(std::move(param)) {}
    TransformParam param;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetFillColorOp final : Op {
    static constexpr auto kType = Type::SetFillColorOp;
    explicit SetFillColorOp(const Color& color): color(std::move(color)) {}
    Color color;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetFillGradientOp final : Op {
    static constexpr auto kType = Type::SetFillGradientOp;
    explicit SetFillGradientOp(const std::shared_ptr<Ace::Gradient>& gradient): gradient(gradient) {}
    std::weak_ptr<Ace::Gradient> gradient;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetFillPatternNGOp final : Op {
    static constexpr auto kType = Type::SetFillPatternNGOp;
    explicit SetFillPatternNGOp(const std::weak_ptr<Ace::Pattern>& pattern): pattern(pattern) {}
    std::weak_ptr<Ace::Pattern> pattern;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetAlphaOp final : Op {
    static constexpr auto kType = Type::SetAlphaOp;
    explicit SetAlphaOp(double alpha): alpha(alpha) {}
    double alpha;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetFillRuleForPathOp final : Op {
    static constexpr auto kType = Type::SetFillRuleForPathOp;
    explicit SetFillRuleForPathOp(const CanvasFillRule& rule): rule(std::move(rule)) {}
    CanvasFillRule rule;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetFillRuleForPath2DOp final : Op {
    static constexpr auto kType = Type::SetFillRuleForPath2DOp;
    explicit SetFillRuleForPath2DOp(const CanvasFillRule& rule): rule(rule) {}
    CanvasFillRule rule;
    void Draw(CanvasPaintMethod* method) const;
};

struct FillOp final : Op {
    static constexpr auto kType = Type::FillOp;
    void Draw(CanvasPaintMethod* method) const;
};

struct Fill2DOp final : Op {
    static constexpr auto kType = Type::Fill2DOp;
    explicit Fill2DOp(const RefPtr<CanvasPath2D>& path): path(path) {}
    RefPtr<CanvasPath2D> path;
    void Draw(CanvasPaintMethod* method) const;
};

struct MoveToOp final : Op {
    static constexpr auto kType = Type::MoveToOp;
    MoveToOp(double x, double y): x(x), y(y) {}
    double x, y;
    void Draw(CanvasPaintMethod* method) const;
};

struct BeginPathOp final : Op {
    static constexpr auto kType = Type::BeginPathOp;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetFilterParamOp : Op {
    static constexpr auto kType = Type::SetFilterParamOp;
    explicit SetFilterParamOp(const std::string& filterStr): filterStr(std::move(filterStr)) {}
    std::string filterStr;
    void Draw(CanvasPaintMethod* method) const;
};

struct ClosePathOp final : Op {
    static constexpr auto kType = Type::ClosePathOp;
    void Draw(CanvasPaintMethod* method) const;
};

struct ClearRectOp final : Op {
    static constexpr auto kType = Type::ClearRectOp;
    explicit ClearRectOp(const Rect& rect): rect(std::move(rect)) {}
    Rect rect;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetStrokeColorOp final : Op {
    static constexpr auto kType = Type::SetStrokeColorOp;
    explicit SetStrokeColorOp(const Color& color): color(std::move(color)) {}
    Color color;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetStrokeGradientOp final : Op {
    static constexpr auto kType = Type::SetStrokeGradientOp;
    explicit SetStrokeGradientOp(const std::shared_ptr<Ace::Gradient>& gradient): gradient(gradient) {}
    std::weak_ptr<Ace::Gradient> gradient;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetStrokePatternNGOp final : Op {
    static constexpr auto kType = Type::SetStrokePatternNGOp;
    explicit SetStrokePatternNGOp(const std::weak_ptr<Ace::Pattern>& pattern): pattern(pattern) {}
    std::weak_ptr<Ace::Pattern> pattern;
    void Draw(CanvasPaintMethod* method) const;
};

struct LineToOp final : Op {
    static constexpr auto kType = Type::LineToOp;
    LineToOp(double x, double y): x(x), y(y) {}
    double x, y;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetLineJoinOp final : Op {
    static constexpr auto kType = Type::SetLineJoinOp;
    explicit SetLineJoinOp(LineJoinStyle style): style(std::move(style)) {}
    LineJoinStyle style;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetLineCapOp final : Op {
    static constexpr auto kType = Type::SetLineCapOp;
    explicit SetLineCapOp(LineCapStyle style): style(std::move(style)) {}
    LineCapStyle style;
    void Draw(CanvasPaintMethod* method) const;
};
struct SetLineWidthOp final : Op {
    static constexpr auto kType = Type::SetLineWidthOp;
    explicit SetLineWidthOp(double width): width(width) {}
    double width;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetMiterLimitOp final : Op {
    static constexpr auto kType = Type::SetMiterLimitOp;
    explicit SetMiterLimitOp(double limit): limit(limit) {}
    double limit;
    void Draw(CanvasPaintMethod* method) const;
};

struct StrokeOp final : Op {
    static constexpr auto kType = Type::StrokeOp;
    void Draw(CanvasPaintMethod* method) const;
};

struct Stroke2DOp final : Op {
    static constexpr auto kType = Type::Stroke2DOp;
    explicit Stroke2DOp(const RefPtr<CanvasPath2D>& path): path(path) {}
    RefPtr<CanvasPath2D> path;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetCompositeTypeOp final : Op {
    static constexpr auto kType = Type::SetCompositeTypeOp;
    explicit SetCompositeTypeOp(CompositeOperation operation): operation(std::move(operation)) {}
    CompositeOperation operation;
    void Draw(CanvasPaintMethod* method) const;
};

struct ClipOp final : Op {
    static constexpr auto kType = Type::ClipOp;
    void Draw(CanvasPaintMethod* method) const;
};

struct Clip2DOp final : Op {
    static constexpr auto kType = Type::Clip2DOp;
    explicit Clip2DOp(const RefPtr<CanvasPath2D>& path): path(path) {}
    RefPtr<CanvasPath2D> path;
    void Draw(CanvasPaintMethod* method) const;
};

struct StrokeRectOp final : Op {
    static constexpr auto kType = Type::StrokeRectOp;
    explicit StrokeRectOp(const Rect& rect): rect(std::move(rect)) {}
    Rect rect;
    void Draw(CanvasPaintMethod* method) const;
};

struct ArcOp final : Op {
    static constexpr auto kType = Type::ArcOp;
    explicit ArcOp(const ArcParam& param): param(std::move(param)) {}
    ArcParam param;
    void Draw(CanvasPaintMethod* method) const;
};

struct ArcToOp final : Op {
    static constexpr auto kType = Type::ArcToOp;
    explicit ArcToOp(const ArcToParam& param): param(std::move(param)) {}
    ArcToParam param;
    void Draw(CanvasPaintMethod* method) const;
};

struct AddRectOp final : Op {
    static constexpr auto kType = Type::AddRectOp;
    explicit AddRectOp(const Rect& rect): rect(std::move(rect)) {}
    Rect rect;
    void Draw(CanvasPaintMethod* method) const;
};

struct EllipseOp final : Op {
    static constexpr auto kType = Type::EllipseOp;
    explicit EllipseOp(const EllipseParam& param): param(std::move(param)) {}
    EllipseParam param;
    void Draw(CanvasPaintMethod* method) const;
};

struct QuadraticCurveToOp final : Op {
    static constexpr auto kType = Type::QuadraticCurveToOp;
    explicit QuadraticCurveToOp(const QuadraticCurveParam& param): param(std::move(param)) {}
    QuadraticCurveParam param;
    void Draw(CanvasPaintMethod* method) const;
};

struct PutImageDataOp final : Op {
    static constexpr auto kType = Type::PutImageDataOp;
    explicit PutImageDataOp(const Ace::ImageData& imageData): imageData(std::move(imageData)) {}
    Ace::ImageData imageData;
    void Draw(CanvasPaintMethod* method) const;
};

struct ScaleOp final : Op {
    static constexpr auto kType = Type::ScaleOp;
    ScaleOp(double x, double y): x(x), y(y) {}
    double x;
    double y;
    void Draw(CanvasPaintMethod* method) const;
};

struct RotateOp final : Op {
    static constexpr auto kType = Type::RotateOp;
    explicit RotateOp(double angle): angle(angle) {}
    double angle;
    void Draw(CanvasPaintMethod* method) const;
};

struct TransformOp final : Op {
    static constexpr auto kType = Type::TransformOp;
    explicit TransformOp(const TransformParam& param): param(std::move(param)) {}
    TransformParam param;
    void Draw(CanvasPaintMethod* method) const;
};

struct TranslateOp final : Op {
    static constexpr auto kType = Type::TranslateOp;
    TranslateOp(double x, double y): x(x), y(y) {}
    double x;
    double y;
    void Draw(CanvasPaintMethod* method) const;
};

struct SaveLayerOp final : Op {
    static constexpr auto kType = Type::SaveLayerOp;
    void Draw(CanvasPaintMethod* method) const;
};

struct RestoreLayerOp final : Op {
    static constexpr auto kType = Type::RestoreLayerOp;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetAntiAliasOp final : Op {
    static constexpr auto kType = Type::SetAntiAliasOp;
    explicit SetAntiAliasOp(bool isEnabled): isEnabled(isEnabled) {}
    bool isEnabled;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetTextDirectionOp final : Op {
    static constexpr auto kType = Type::SetTextDirectionOp;
    explicit SetTextDirectionOp(TextDirection direction): direction(std::move(direction)) {}
    TextDirection direction;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetLineDashOffsetOp final : Op {
    static constexpr auto kType = Type::SetLineDashOffsetOp;
    explicit SetLineDashOffsetOp(double offset): offset(offset) {}
    double offset;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetLineDashOp final : Op {
    static constexpr auto kType = Type::SetLineDashOp;
    explicit SetLineDashOp(const std::vector<double>& segments): segments(std::move(segments)) {}
    std::vector<double> segments;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetTextAlignOp final : Op {
    static constexpr auto kType = Type::SetTextAlignOp;
    explicit SetTextAlignOp(TextAlign align): align(std::move(align)) {}
    TextAlign align;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetTextBaselineOp final : Op {
    static constexpr auto kType = Type::SetTextBaselineOp;
    explicit SetTextBaselineOp(TextBaseline baseline): baseline(std::move(baseline)) {}
    TextBaseline baseline;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetShadowColorOp final : Op {
    static constexpr auto kType = Type::SetShadowColorOp;
    explicit SetShadowColorOp(const Color& color): color(std::move(color)) {}
    Color color;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetShadowBlurOp final : Op {
    static constexpr auto kType = Type::SetShadowBlurOp;
    explicit SetShadowBlurOp(double blur): blur(blur) {}
    double blur;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetShadowOffsetXOp final : Op {
    static constexpr auto kType = Type::SetShadowOffsetXOp;
    explicit SetShadowOffsetXOp(double x): x(x) {}
    double x;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetShadowOffsetYOp final : Op {
    static constexpr auto kType = Type::SetShadowOffsetYOp;
    explicit SetShadowOffsetYOp(double y): y(y) {}
    double y;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetSmoothingEnabledOp final : Op {
    static constexpr auto kType = Type::SetSmoothingEnabledOp;
    explicit SetSmoothingEnabledOp(bool enabled): enabled(enabled) {}
    bool enabled;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetSmoothingQualityOp final : Op {
    static constexpr auto kType = Type::SetSmoothingQualityOp;
    explicit SetSmoothingQualityOp(const std::string& quality): quality(std::move(quality)) {}
    std::string quality;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetFontSizeOp final : Op {
    static constexpr auto kType = Type::SetFontSizeOp;
    explicit SetFontSizeOp(const Dimension& size): size(std::move(size)) {}
    Dimension size;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetLetterSpacingOp final : Op {
    static constexpr auto kType = Type::SetLetterSpacingOp;
    explicit SetLetterSpacingOp(const Dimension& letterSpacing): letterSpacing(std::move(letterSpacing)) {}
    Dimension letterSpacing;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetFontStyleOp final : Op {
    static constexpr auto kType = Type::SetFontStyleOp;
    explicit SetFontStyleOp(OHOS::Ace::FontStyle style): style(std::move(style)) {}
    OHOS::Ace::FontStyle style;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetFontWeightOp final : Op {
    static constexpr auto kType = Type::SetFontWeightOp;
    explicit SetFontWeightOp(FontWeight weight): weight(std::move(weight)) {}
    FontWeight weight;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetFontFamiliesOp final : Op {
    static constexpr auto kType = Type::SetFontFamiliesOp;
    explicit SetFontFamiliesOp(const std::vector<std::string>& fontFamilies) : fontFamilies(std::move(fontFamilies)) {}
    std::vector<std::string> fontFamilies;
    void Draw(CanvasPaintMethod* method) const;
};

struct DrawSvgImageOp final : Op {
    static constexpr auto kType = Type::DrawSvgImageOp;
    DrawSvgImageOp(RefPtr<SvgDomBase> svgDom, const Ace::CanvasImage& canvasImage, const ImageFit& imageFit)
        : svgDom(svgDom), canvasImage(std::move(canvasImage)), imageFit(std::move(imageFit)) {}
    RefPtr<SvgDomBase> svgDom;
    Ace::CanvasImage canvasImage;
    ImageFit imageFit;
    void Draw(CanvasPaintMethod* method) const;
};

struct DrawImageOp final : Op {
    static constexpr auto kType = Type::DrawImageOp;
    DrawImageOp(const Ace::CanvasImage& canvasImage, double width, double height)
        : canvasImage(std::move(canvasImage)), width(width), height(height) {}
    Ace::CanvasImage canvasImage;
    double width;
    double height;
    void Draw(CanvasPaintMethod* method) const;
};

struct DrawPixelMapOp final : Op {
    static constexpr auto kType = Type::DrawPixelMapOp;
    DrawPixelMapOp(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& canvasImage)
        : pixelMap(pixelMap), canvasImage(std::move(canvasImage)) {}
    RefPtr<PixelMap> pixelMap;
    Ace::CanvasImage canvasImage;
    void Draw(CanvasPaintMethod* method) const;
};

#ifdef PIXEL_MAP_SUPPORTED
struct TransferFromImageBitmapOp final : Op {
    static constexpr auto kType = Type::TransferFromImageBitmapOp;
    explicit TransferFromImageBitmapOp(const RefPtr<PixelMap>& pixelMap)
        : pixelMap(pixelMap) {}
    RefPtr<PixelMap> pixelMap;
    void Draw(CanvasPaintMethod* method) const;
};
#endif

struct StrokeTextOp final : Op {
    static constexpr auto kType = Type::StrokeTextOp;
    StrokeTextOp(const std::string& text, double x, double y, std::optional<double> maxWidth)
        : text(std::move(text)), x(x), y(y), maxWidth(maxWidth) {}
    std::string text;
    double x;
    double y;
    std::optional<double> maxWidth;
    void Draw(CanvasPaintMethod* method) const;
};

struct ResetCanvasOp final : Op {
    static constexpr auto kType = Type::ResetCanvasOp;
    void Draw(CanvasPaintMethod* method) const;
};

struct ResetTransformOp final : Op {
    static constexpr auto kType = Type::ResetTransformOp;
    void Draw(CanvasPaintMethod* method) const;
};

struct SetInvalidateOp final : Op {
    static constexpr auto kType = Type::SetInvalidateOp;
    void Draw(CanvasPaintMethod* method) const;
};

typedef void (*DrawFn)(const void*, CanvasPaintMethod* method);
typedef void (*VoidFn)(const void*);

#define X(T)                                                                                   \
    [](const void* op, CanvasPaintMethod* method) {                                            \
        ((const T*)op)->Draw(method);                                                          \
    },
static const DrawFn DRAW_FNS[] = {
    #include "./canvas_paint_ops.in"
};
#undef X

#define X(T)                                                                                    \
    !std::is_trivially_destructible<T>::value ? [](const void* op) { ((const T*)op)->~T(); }    \
                                                : (VoidFn) nullptr,
static const VoidFn DTOR_FBS[] = {
    #include "./canvas_paint_ops.in"
};
#undef X

class CanvasPaintOp final {
public:
    CanvasPaintOp() : mHasText(false) {}
    ~CanvasPaintOp() { Reset(); }

    void Draw(CanvasPaintMethod* method) const;
    void Reset();
    bool Empty() const {return fUsed == 0; }

    bool HasText() const { return mHasText; }
    size_t UsedSize() const { return fUsed; }
    size_t AllocatedSize() const { return fReserved; }

    template <typename Fn, typename... Args>
    void Map(const Fn[], Args...) const;

    template <typename T> static constexpr inline T Align2(T x) { return (x + 1) >> 1 << 1; }
    template <typename T> static constexpr inline T Align4(T x) { return (x + 3) >> 2 << 2; }
    template <typename T> static constexpr inline T Align8(T x) { return (x + 7) >> 3 << 3; }

    template <typename T> static constexpr inline bool IsAlign2(T x) { return (x & 1) == 0; }
    template <typename T> static constexpr inline bool IsAlign4(T x) { return (x & 3) == 0; }
    template <typename T> static constexpr inline bool IsAlign8(T x) { return (x & 7) == 0; }
    template <typename T> static constexpr inline bool IsPow2(T value)
    {
        return (value & (value - 1)) == 0;
    }
    template <typename T> static constexpr inline T AlignPtr(T x)
    {
        return sizeof(void*) == POINTSIZE8 ? Align8(x) : Align4(x);
    }
    template <typename T> static constexpr inline bool IsAlignPtr(T x)
    {
        return sizeof(void*) == POINTSIZE8 ? IsAlign8(x) : IsAlign4(x);
    }

    template <typename T, typename... Args>
    void* Push(size_t pod, Args&&... args)
    {
        size_t skip = AlignPtr(sizeof(T) + pod);
        ACE_DCHECK(skip < (1 << SKIPSIZE));
        if (fUsed + skip > fReserved) {
            static_assert(IsPow2(PAGESIZE), "This math needs updating for non-pow2.");
            fReserved = (fUsed + skip + PAGESIZE) & ~(PAGESIZE - 1);
            fBytes.realloc(fReserved);
            if (!fBytes.get()) {
                TAG_LOGE(AceLogTag::ACE_CANVAS_COMPONENT, "realloc failed");
            }
        }
        ACE_DCHECK(fUsed + skip <= fReserved);
        auto op = (T*)(fBytes.get() + fUsed);
        fUsed += skip;
        new (op) T{std::forward<Args>(args)...};
        op->type = (uint32_t)T::kType;
        op->skip = skip;
        return op + 1;
    }

private:
    AutoTMalloc<uint8_t> fBytes;
    size_t fUsed = 0;
    size_t fReserved = 0;

    bool mHasText : 1;
    static constexpr uint8_t SKIPSIZE = 24;
    static constexpr uint8_t POINTSIZE8 = 8;
    static constexpr uint16_t PAGESIZE = 4096;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_PAINT_OP_H
