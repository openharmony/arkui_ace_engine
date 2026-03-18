/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "securec.h"

#include "native_type.h"
#include "core/components_ng/pattern/text/span/mutable_span_string.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/node/styled_string_impl.h"
#include "core/text/html_utils.h"

namespace OHOS::Ace::NG {
namespace {
    constexpr int32_t API_TARGET_VERSION_MASK = 1000;
    constexpr int32_t COLOR_FILTER_MATRIX_SIZE = 20;
    constexpr float DEFAULT_TEXT_SIZE = 16.0f;
    constexpr int32_t DEFAULT_FONT_WEIGHT = 3;
    constexpr int32_t MAX_POINTS = 10;
    constexpr int32_t MAX_HISTORY_EVENT_COUNT = 20;
    const std::vector<float> DEFAULT_COLORFILTER_MATRIX = {
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };
}
namespace NodeModifier {
ArkUINodeEvent CreateNodeEventFromTouchEvent(int32_t nodeId, void* extraParam, TouchEventInfo& eventInfo);
void ParseTouchPoints(std::array<ArkUITouchPoint, NG::MAX_POINTS> touchPoints,
    ArkUINodeEvent& event, TouchEventInfo& eventInfo, bool usePx);
void ParseHistoryEvent(std::array<ArkUIHistoryTouchEvent, NG::MAX_HISTORY_EVENT_COUNT> allHistoryEvents,
    std::array<std::array<ArkUITouchPoint, NG::MAX_POINTS>, NG::MAX_HISTORY_EVENT_COUNT> allHistoryPoints,
    ArkUINodeEvent& event, TouchEventInfo& eventInfo, bool usePx);
ArkUINodeEvent CreateNodeEventOnClick(void* extraParam, int32_t nodeId, bool usePx, GestureEvent& info);
}
void GetGestureEvent(ArkUIAPIEventGestureAsyncEvent& ret, GestureEvent& info);
void ConvertIMMEventToAxisEvent(GestureEvent& info, ArkUIAxisEvent& axisEvent);
void ConvertIMMEventToMouseEvent(GestureEvent& info, ArkUIMouseEvent& mouseEvent);
void ConvertIMMEventToTouchEvent(GestureEvent& info, ArkUITouchEvent& touchEvent,
    std::array<ArkUITouchPoint, NG::MAX_POINTS>& points);
PaddingProperty ConvertToCalcPaddingProperty(const std::optional<CalcDimension>& top,
    const std::optional<CalcDimension>& bottom, const std::optional<CalcDimension>& left,
    const std::optional<CalcDimension>& right);
struct NativeHandle {
    std::shared_ptr<OHOS::Rosen::Drawing::ColorFilter> value = nullptr;
};
}
namespace OHOS::Ace::StyledStringAdapter {
namespace {
constexpr int32_t UNSPECIFIED_SPAN_TYPE = -1;

RefPtr<SpanBase> ParseFontSpan(const ArkUISpanStyle& style, int32_t start, int32_t length)
{
    ArkUITextStyle textStyle = style.textStyle;
    Font font;
    font.fontColor = Color(textStyle.fontColor);
    font.fontFamiliesNG = OHOS::Ace::Framework::ConvertStrToFontFamilies(textStyle.fontFamily);
    font.fontSize = Dimension(textStyle.fontSize, DimensionUnit::VP);
    font.fontStyle = static_cast<OHOS::Ace::FontStyle>(textStyle.fontStyle);
    font.strokeWidth = Dimension(textStyle.strokeWidth, DimensionUnit::VP);
    font.strokeColor = Color(textStyle.strokeColor);
    font.superscript = static_cast<OHOS::Ace::SuperscriptStyle>(textStyle.superscript);
    if (auto result = textStyle.fontWeight;
        result >= 0 && result <= static_cast<uint32_t>(OHOS::Ace::FontWeight::REGULAR)) {
        font.fontWeight = static_cast<OHOS::Ace::FontWeight>(result);
    }
    auto fontSpan = AceType::MakeRefPtr<FontSpan>(font, start, start + length);
    return fontSpan;
}

void ParseLeadingMargin(SpanParagraphStyle& spanParagraphStyle, const ArkUIParagraphStyle& paragraphStyle)
{
    if (paragraphStyle.onDrawLeadingMargin) {
        std::optional<NG::DrawableLeadingMargin> drawableLeadingMargin;
        drawableLeadingMargin = std::make_optional<NG::DrawableLeadingMargin>();
        drawableLeadingMargin->onDraw_ = [func = paragraphStyle.onDrawLeadingMargin]
            (NG::DrawingContext& context, NG::LeadingMarginSpanOptions leadingMarginOptions) -> void {
                ArkUIDrawingContext drawContext;
                drawContext.canvas = reinterpret_cast<ArkUICanvasHandle>(&context.canvas);
                drawContext.width = context.width;
                drawContext.height = context.height;
                ArkUILeadingMarginSpanDrawInfo info;
                info.x = leadingMarginOptions.x;
                info.top = leadingMarginOptions.top;
                info.bottom = leadingMarginOptions.bottom;
                info.baseline = leadingMarginOptions.baseline;
                info.direction = static_cast<int32_t>(leadingMarginOptions.direction);
                info.start = leadingMarginOptions.start;
                info.end = leadingMarginOptions.end;
                info.first = leadingMarginOptions.first;
                auto onDrawLeadingMargin =
                    reinterpret_cast<void (*)(ArkUIDrawingContext*, ArkUILeadingMarginSpanDrawInfo*)>(func);
                if (onDrawLeadingMargin) {
                    onDrawLeadingMargin(&drawContext, &info);
                }
        };
        drawableLeadingMargin->getLeadingMarginFunc_ = [func = paragraphStyle.onGetLeadingMargin]() -> CalcDimension {
            float disntance = 0.0f;
            auto onGetLeadingMargin = reinterpret_cast<float(*)()>(func);
            if (onGetLeadingMargin) {
                disntance = onGetLeadingMargin();
            }
            return CalcDimension(disntance, DimensionUnit::VP);
        };
        spanParagraphStyle.drawableLeadingMargin = drawableLeadingMargin;
    } else {
        spanParagraphStyle.leadingMargin = std::make_optional<NG::LeadingMargin>();
        if (!paragraphStyle.pixelMapRawData.empty()) {
            std::vector<uint8_t> pixelMapRawData;
            std::copy(paragraphStyle.pixelMapRawData.begin(), paragraphStyle.pixelMapRawData.end(),
                std::back_inserter(pixelMapRawData));
            spanParagraphStyle.leadingMargin->pixmap = PixelMap::DecodeTlv(pixelMapRawData);
        }
        spanParagraphStyle.leadingMargin->size =
            NG::LeadingMarginSize(Dimension(paragraphStyle.width, DimensionUnit::VP),
            Dimension(paragraphStyle.height, DimensionUnit::VP));
    }
}

RefPtr<SpanBase> ParseParagraphStyle(const ArkUISpanStyle& style, int32_t start, int32_t length)
{
    ArkUIParagraphStyle paragraphStyle = style.paragraphStyle;
    SpanParagraphStyle spanParagraphStyle;
    spanParagraphStyle.align = static_cast<OHOS::Ace::TextAlign>(paragraphStyle.textAlign);
    spanParagraphStyle.textVerticalAlign =
        static_cast<OHOS::Ace::TextVerticalAlign>(paragraphStyle.textVerticalAlignment);
    spanParagraphStyle.maxLines = paragraphStyle.maxLines;
    spanParagraphStyle.textOverflow = static_cast<OHOS::Ace::TextOverflow>(paragraphStyle.overflow);
    spanParagraphStyle.wordBreak = static_cast<OHOS::Ace::WordBreak>(paragraphStyle.wordBreak);
    auto textIndent = paragraphStyle.textIndent;
    spanParagraphStyle.textIndent = Dimension(LessOrEqual(textIndent, 0.0) ? 0.0 : textIndent, DimensionUnit::VP);
    spanParagraphStyle.paragraphSpacing = Dimension(paragraphStyle.paragraphSpacing, DimensionUnit::VP);
    ParseLeadingMargin(spanParagraphStyle, paragraphStyle);
    spanParagraphStyle.textDirection = static_cast<OHOS::Ace::TextDirection>(paragraphStyle.textDirection);
    auto paragraphStyleSpan = AceType::MakeRefPtr<NapiParagraphStyleSpan>(spanParagraphStyle, start, start + length);
    paragraphStyleSpan->onNapiDrawLeadingMargin_ = paragraphStyle.onDrawLeadingMargin;
    paragraphStyleSpan->onNapiGetLeadingMargin_ = paragraphStyle.onGetLeadingMargin;
    return paragraphStyleSpan;
}

void ParseLongPress(GestureStyle& gestureInfo, const ArkUIGestureStyle& gestureStyle)
{
    CHECK_NULL_VOID(gestureStyle.onLongPress);
    gestureInfo.onLongPress = [longPressFunc = gestureStyle.onLongPress](GestureEvent& info) {
        ArkUINodeEvent event;
        event.kind = GESTURE_ASYNC_EVENT;
        event.nodeId = 0;
        event.gestureAsyncEvent.subKind = static_cast<int32_t>(ON_ACTION_START);
        event.apiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion() % NG::API_TARGET_VERSION_MASK;
        NG::GetGestureEvent(event.gestureAsyncEvent, info);
        if (info.GetInputEventType() == InputEventType::AXIS) {
            ArkUIAxisEvent rawInputEvent;
            NG::ConvertIMMEventToAxisEvent(info, rawInputEvent);
            event.gestureAsyncEvent.rawPointerEvent = &rawInputEvent;
            longPressFunc(event);
            return;
        }
        if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON) {
            ArkUIMouseEvent rawInputEvent;
            NG::ConvertIMMEventToMouseEvent(info, rawInputEvent);
            event.gestureAsyncEvent.rawPointerEvent = &rawInputEvent;
            longPressFunc(event);
            return;
        }
        if (info.GetInputEventType() == InputEventType::KEYBOARD) {
            ArkUIKeyEvent rawInputEvent;
            rawInputEvent.deviceId = info.GetDeviceId();
            rawInputEvent.sourceType = static_cast<int32_t>(info.GetSourceDevice());
            event.gestureAsyncEvent.rawPointerEvent = &rawInputEvent;
            longPressFunc(event);
            return;
        }
        ArkUITouchEvent rawInputEvent;
        std::array<ArkUITouchPoint, NG::MAX_POINTS> points;
        NG::ConvertIMMEventToTouchEvent(info, rawInputEvent, points);
        event.gestureAsyncEvent.rawPointerEvent = &rawInputEvent;
        longPressFunc(event);
    };
}

RefPtr<SpanBase> ParseGestureStyle(const ArkUISpanStyle& style, int32_t start, int32_t length)
{
    ArkUIGestureStyle gestureStyle = style.gestureStyle;
    GestureStyle gestureInfo;
    gestureInfo.onClick = std::nullopt;
    gestureInfo.onLongPress = std::nullopt;
    gestureInfo.onTouch = std::nullopt;
    if (gestureStyle.onClick) {
        gestureInfo.onClick = [clickFunc = gestureStyle.onClick](GestureEvent& info) {
            auto event = NG::NodeModifier::CreateNodeEventOnClick(nullptr, 0, false, info);
            clickFunc(event);
        };
    }
    ParseLongPress(gestureInfo, gestureStyle);
    if (gestureStyle.onTouch) {
        gestureInfo.onTouch =[touchFunc = gestureStyle.onTouch](TouchEventInfo& info) {
            auto nodeEvent = NG::NodeModifier::CreateNodeEventFromTouchEvent(0, nullptr, info);
            std::array<ArkUITouchPoint, NG::MAX_POINTS> touchPoints;
            NG::NodeModifier::ParseTouchPoints(touchPoints, nodeEvent, info, false);
            std::array<ArkUIHistoryTouchEvent, NG::MAX_HISTORY_EVENT_COUNT> allHistoryEvents;
            std::array<std::array<ArkUITouchPoint, NG::MAX_POINTS>, NG::MAX_HISTORY_EVENT_COUNT> allHistoryPoints;
            NG::NodeModifier::ParseHistoryEvent(allHistoryEvents, allHistoryPoints, nodeEvent, info, false);
            touchFunc(nodeEvent);
        };
    }
    auto result = AceType::MakeRefPtr<NapiGestureSpan>(gestureInfo, start, start + length);
    result->onNapiClick_ = gestureStyle.onNapiClick;
    result->onNapiLongPress_ = gestureStyle.onNapiLongPress;
    result->onNapiTouch_ = gestureStyle.onNapiTouch;
    return result;
}

RefPtr<SpanBase> ParseTextShadowStyle(const ArkUISpanStyle& style, int32_t start, int32_t length)
{
    ArkUITextShadowStyle textShadowStyle = style.textShadowStyle;
    std::vector<Shadow> shadows(textShadowStyle.textShadow.size());
    for (auto& shadow : textShadowStyle.textShadow) {
        Shadow tempShadow;
        tempShadow.SetColor(Color(shadow.color));
        tempShadow.SetOffsetX(shadow.offsetX);
        tempShadow.SetOffsetY(shadow.offsetY);
        tempShadow.SetIsFilled(shadow.isFill);
        tempShadow.SetShadowType(static_cast<ShadowType>(shadow.type));
        tempShadow.SetBlurRadius(shadow.radius);
        shadows.push_back(tempShadow);
    }
    return AceType::MakeRefPtr<TextShadowSpan>(shadows, start, start + length);
}

RefPtr<SpanBase> ParseDecorationStyle(const ArkUISpanStyle& style, int32_t start, int32_t length)
{
    ArkUIDecorationStyle decorationStyle = style.decorationStyle;
    TextDecorationOptions options;
    options.enableMultiType = decorationStyle.enableMultiType;
    return AceType::MakeRefPtr<DecorationSpan>(
        std::vector<TextDecoration>({static_cast<TextDecoration>(decorationStyle.type)}),
        Color(decorationStyle.color), static_cast<TextDecorationStyle>(decorationStyle.style),
        decorationStyle.thicknessScale, options, start, start + length, nullptr);
}

RefPtr<SpanBase> ParseBaselineOffsetStyle(const ArkUISpanStyle& style, int32_t start, int32_t length)
{
    return AceType::MakeRefPtr<BaselineOffsetSpan>(
        Dimension(style.baselineOffsetStyle.baselineOffset, DimensionUnit::VP), start, start + length);
}

RefPtr<SpanBase> ParseLetterSpacingStyle(const ArkUISpanStyle& style, int32_t start, int32_t length)
{
    return AceType::MakeRefPtr<LetterSpacingSpan>(
        Dimension(style.letterSpacingStyle.letterSpacing, DimensionUnit::VP), start, start + length);
}

RefPtr<SpanBase> ParseLineHeightStyle(const ArkUISpanStyle& style, int32_t start, int32_t length)
{
    return AceType::MakeRefPtr<LineHeightSpan>(Dimension(style.lineHeightStyle.lineHeight, DimensionUnit::VP),
        start, start + length);
}

RefPtr<SpanBase> ParseUrlStyle(const ArkUISpanStyle& style, int32_t start, int32_t length)
{
    return AceType::MakeRefPtr<UrlSpan>(style.urlStyle.url, start, start + length);
}

RefPtr<SpanBase> ParseBackgroundColorStyle(const ArkUISpanStyle& style, int32_t start, int32_t length)
{
    auto backgroundColorStyle = style.backgroundColorStyle;
    TextBackgroundStyle textBackgroundStyle;
    textBackgroundStyle.backgroundColor = Color(backgroundColorStyle.color);
    textBackgroundStyle.backgroundRadius = {
        CalcDimension(backgroundColorStyle.topLeftRadius, DimensionUnit::VP),
        CalcDimension(backgroundColorStyle.topRightRadius, DimensionUnit::VP),
        CalcDimension(backgroundColorStyle.bottomRightRadius, DimensionUnit::VP),
        CalcDimension(backgroundColorStyle.bottomLeftRadius, DimensionUnit::VP) };
    textBackgroundStyle.backgroundRadius->multiValued = true;
    return AceType::MakeRefPtr<BackgroundColorSpan>(textBackgroundStyle, start, start + length);
}

RefPtr<SpanBase> ParseUserDatSpan(const ArkUISpanStyle& style, int32_t start, int32_t length)
{
    return AceType::MakeRefPtr<ExtSpan>(style.userDataSpan.userData, start, start + length);
}

RefPtr<SpanBase> ParseCustomSpan(const ArkUICustomSpan& customSpan, int32_t start, int32_t length)
{
    std::function<CustomSpanMetrics(CustomSpanMeasureInfo)> onMeasureCallback =
        [onMeasure = customSpan.onMeasure](CustomSpanMeasureInfo customSpanMeasureInfo) -> CustomSpanMetrics {
            auto metrics = CustomSpanMetrics{ .width = 0.0f, .height = std::optional<float>(0) };
            auto onMeasureFunc = reinterpret_cast<ArkUICustomSpanMetrics* (*)(float)>(onMeasure);
            CHECK_NULL_RETURN(onMeasureFunc, metrics);
            ArkUICustomSpanMetrics* arkuiCustomSpanMetrics = onMeasureFunc(customSpanMeasureInfo.fontSize);
            CHECK_NULL_RETURN(arkuiCustomSpanMetrics, metrics);
            metrics.width = arkuiCustomSpanMetrics->width;
            metrics.height = arkuiCustomSpanMetrics->height;
            return metrics;
    };
    std::function<void(NG::DrawingContext&, CustomSpanOptions)> onDrawCallback =
        [onDraw = customSpan.onDraw](NG::DrawingContext& context, CustomSpanOptions customSpanOptions) -> void {
        auto onDrawFunc = reinterpret_cast<void (*)(ArkUIDrawingContext*, ArkUICustomSpanDrawInfo*)>(onDraw);
        CHECK_NULL_VOID(onDrawFunc);
        ArkUIDrawingContext drawContext;
        drawContext.canvas = reinterpret_cast<ArkUICanvasHandle>(&context.canvas);
        drawContext.width = context.width;
        drawContext.height = context.height;
        ArkUICustomSpanDrawInfo drawInfo;
        drawInfo.optionsX = customSpanOptions.x;
        drawInfo.optionsLineTop = customSpanOptions.lineTop;
        drawInfo.optionsLineBottom = customSpanOptions.lineBottom;
        drawInfo.optionsBaseLine = customSpanOptions.baseline;
        onDrawFunc(&drawContext, &drawInfo);
    };
    auto result = AceType::MakeRefPtr<NapiCustomSpan>(onMeasureCallback, onDrawCallback, start, start + length);
    result->onNapiMeasure_ = customSpan.onMeasure;
    result->onNapiDraw_ = customSpan.onDraw;
    return result;
}

RefPtr<SpanBase> ParseCustomSpan(const ArkUISpanStyle& style, int32_t start, int32_t length)
{
    return ParseCustomSpan(style.customSpan, start, length);
}

void ConvertToImageSpanAttribute(ImageSpanAttribute& imageStyle, const ArkUIImageAttachment& imageAttachment)
{
    imageStyle.verticalAlign = static_cast<VerticalAlign>(imageAttachment.verticalAlign);
    imageStyle.objectFit = static_cast<ImageFit>(imageAttachment.objectFit);
    imageStyle.marginProp = NG::ConvertToCalcPaddingProperty(
        CalcDimension(imageAttachment.margin.top, DimensionUnit::VP),
        CalcDimension(imageAttachment.margin.bottom, DimensionUnit::VP),
        CalcDimension(imageAttachment.margin.left, DimensionUnit::VP),
        CalcDimension(imageAttachment.margin.right, DimensionUnit::VP));
    imageStyle.paddingProp =  NG::ConvertToCalcPaddingProperty(
        CalcDimension(imageAttachment.padding.top, DimensionUnit::VP),
        CalcDimension(imageAttachment.padding.bottom, DimensionUnit::VP),
        CalcDimension(imageAttachment.padding.left, DimensionUnit::VP),
        CalcDimension(imageAttachment.padding.right, DimensionUnit::VP));
    imageStyle.borderRadius = {
        CalcDimension(imageAttachment.topLeftRadius, DimensionUnit::VP),
        CalcDimension(imageAttachment.topRightRadius, DimensionUnit::VP),
        CalcDimension(imageAttachment.bottomRightRadius, DimensionUnit::VP),
        CalcDimension(imageAttachment.bottomLeftRadius, DimensionUnit::VP) };
    imageStyle.borderRadius->multiValued = true;
    imageStyle.syncLoad = imageAttachment.syncLoad;
    imageStyle.supportSvg2 = imageAttachment.supportSvg;
    ImageSpanSize imageSize;
    if (imageAttachment.width.has_value()) {
        imageSize.width = CalcDimension(imageAttachment.width.value(), DimensionUnit::VP);
    }
    if (imageAttachment.height.has_value()) {
        imageSize.height = CalcDimension(imageAttachment.height.value(), DimensionUnit::VP);
    }
    imageStyle.size = imageSize;
    bool isDrawingColorFilter = imageAttachment.isDrawingColorFilter.value_or(false);
    if (isDrawingColorFilter) {
        imageStyle.colorFilterMatrix = std::nullopt;
        auto handle = reinterpret_cast<NG::NativeHandle*>(imageAttachment.drawingColorFilter);
        auto filterPtr = handle->value;
        if (filterPtr) {
            imageStyle.drawingColorFilter =
                DrawingColorFilter::CreateDrawingColorFilterFromNative(static_cast<void*>(&filterPtr));
        }
    } else if (imageAttachment.isDrawingColorFilter.has_value()) {
        imageStyle.drawingColorFilter = std::nullopt;
        if (imageAttachment.colorFilter.size() != NG::COLOR_FILTER_MATRIX_SIZE) {
            imageStyle.colorFilterMatrix = NG::DEFAULT_COLORFILTER_MATRIX;
        } else {
            imageStyle.colorFilterMatrix = imageAttachment.colorFilter;
        }
    }
}

ImageSpanOptions CreateImageSpanOptions(const ArkUIImageAttachment& imageAttachment)
{
    ImageSpanOptions options;
    if (!imageAttachment.isPixelMap.value_or(true)) {
        options.image = imageAttachment.resource;
        options.bundleName = "";
        options.moduleName = "";
        options.isUriPureNumber = false;
    } else if (imageAttachment.isPixelMap.has_value()) {
        std::vector<uint8_t> pixelMapRawData;
        std::copy(imageAttachment.pixelMapRawData.begin(), imageAttachment.pixelMapRawData.end(),
            std::back_inserter(pixelMapRawData));
        options.imagePixelMap = PixelMap::DecodeTlv(pixelMapRawData);
    }
    ImageSpanAttribute imageStyle;
    ConvertToImageSpanAttribute(imageStyle, imageAttachment);
    options.imageAttribute = imageStyle;
    return options;
}

RefPtr<SpanBase> ParseImageSpan(const ArkUISpanStyle& style, int32_t start, int32_t length)
{
    ImageSpanOptions options = CreateImageSpanOptions(style.imageAttachment);
    auto imageSpan = AceType::MakeRefPtr<ImageSpan>(options);
    imageSpan->UpdateStartIndex(start);
    imageSpan->UpdateEndIndex(start + length);
    return imageSpan;
}

using SpanBaseParserFunc = RefPtr<SpanBase> (*)(const ArkUISpanStyle& style, int32_t start, int32_t length);

static const std::map<SpanType, SpanBaseParserFunc> spanBaseParserMap = {
    { SpanType::Url, &ParseUrlStyle },
    { SpanType::Font, &ParseFontSpan },
    { SpanType::Image, &ParseImageSpan },
    { SpanType::ExtSpan, &ParseUserDatSpan },
    { SpanType::Gesture, &ParseGestureStyle },
    { SpanType::CustomSpan, &ParseCustomSpan },
    { SpanType::TextShadow, &ParseTextShadowStyle },
    { SpanType::Decoration, &ParseDecorationStyle },
    { SpanType::LineHeight, &ParseLineHeightStyle },
    { SpanType::ParagraphStyle, &ParseParagraphStyle },
    { SpanType::LetterSpacing, &ParseLetterSpacingStyle },
    { SpanType::BaselineOffset, &ParseBaselineOffsetStyle },
    { SpanType::BackgroundColor, &ParseBackgroundColorStyle },
};

RefPtr<SpanBase> ParseSpanBase(const ArkUISpanStyle& style, int32_t maxLength)
{
    CHECK_NULL_RETURN(style.styledKey != UNSPECIFIED_SPAN_TYPE, nullptr);
    int32_t start = style.start;
    int32_t length = style.length;
    start = (start < 0 || start >= maxLength) ? 0 : start;
    length = (length <= 0 || (length > maxLength - start)) ? maxLength - start : length;
    auto spanType = static_cast<SpanType>(style.styledKey);
    auto it = spanBaseParserMap.find(spanType);
    CHECK_NULL_RETURN(it != spanBaseParserMap.end(), nullptr);
    SpanBaseParserFunc parserFunc = it->second;
    CHECK_NULL_RETURN(parserFunc, nullptr);
    return parserFunc(style, start, length);
}

std::vector<RefPtr<SpanBase>> ParseSpanBaseVector(const std::vector<ArkUISpanStyle>& styles, int32_t maxLength)
{
    std::vector<RefPtr<SpanBase>> spans;
    for (const auto& style : styles) {
        CHECK_NULL_CONTINUE(style.styledKey != UNSPECIFIED_SPAN_TYPE);
        auto spanType = static_cast<SpanType>(style.styledKey);
        CHECK_NULL_CONTINUE(spanType != SpanType::Image && spanType != SpanType::CustomSpan);
        auto spanBase = ParseSpanBase(style, maxLength);
        CHECK_NULL_CONTINUE(spanBase);
        spans.push_back(spanBase);
    }
    return spans;
}

ArkUI_StyledString_Descriptor* CreateArkUIStyledStringDescriptorWithString(ArkUI_CharPtr value,
    const std::vector<ArkUISpanStyle>& styles)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "ArkUI_StyledString_Descriptor create with string");
    ArkUI_StyledString_Descriptor* descriptor = new ArkUI_StyledString_Descriptor();
    MutableSpanString* spanString = new MutableSpanString(UtfUtils::Str8ToStr16(std::string(value)));
    int32_t maxLength = spanString->GetLength();
    auto spans = ParseSpanBaseVector(styles, maxLength);
    spanString->BindWithSpans(spans);
    descriptor->spanString = spanString;
    return descriptor;
}

ArkUI_StyledString_Descriptor* CreateArkUIStyledStringDescriptorWithImage(ArkUIImageAttachment attachment)
{
    ArkUI_StyledString_Descriptor* descriptor = new ArkUI_StyledString_Descriptor();
    ImageSpanOptions options = CreateImageSpanOptions(attachment);
    MutableSpanString* spanString = new MutableSpanString(options);
    descriptor->spanString = spanString;
    return descriptor;
}

ArkUI_StyledString_Descriptor* CreateArkUIStyledStringDescriptorWithCustomSpan(ArkUICustomSpan value)
{
    RefPtr<NapiCustomSpan> customSpan = AceType::DynamicCast<NapiCustomSpan>(ParseCustomSpan(value, 0, 1));
    CHECK_NULL_RETURN(customSpan, nullptr);
    auto span = AceType::DynamicCast<CustomSpan>(customSpan);
    CHECK_NULL_RETURN(span, nullptr);
    MutableSpanString* spanString = new MutableSpanString(span);
    ArkUI_StyledString_Descriptor* descriptor = new ArkUI_StyledString_Descriptor();
    descriptor->spanString = spanString;
    return descriptor;
}

ArkUI_StyledString_Descriptor* CreateArkUIStyledStringDescriptor()
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "ArkUI_StyledString_Descriptor create");
    return new ArkUI_StyledString_Descriptor;
}

void DestroyArkUIStyledStringDescriptor(ArkUI_StyledString_Descriptor* descriptor)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "ArkUI_StyledString_Descriptor destroy");
    CHECK_NULL_VOID(descriptor);
    if (descriptor->html) {
        delete descriptor->html;
        descriptor->html = nullptr;
    }
    if (descriptor->spanString) {
        auto* spanString = reinterpret_cast<SpanString*>(descriptor->spanString);
        delete spanString;
        descriptor->spanString = nullptr;
    }
    delete descriptor;
    descriptor = nullptr;
}

ArkUI_Int32 UnmarshallStyledStringDescriptor(
    uint8_t* buffer, size_t bufferSize, ArkUI_StyledString_Descriptor* descriptor)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "UnmarshallStyledStringDescriptor");
    CHECK_NULL_RETURN(buffer && descriptor && bufferSize > 0, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    std::vector<uint8_t> vec(buffer, buffer + bufferSize);
    MutableSpanString* spanString = new MutableSpanString(u"");
    spanString->DecodeTlvExt(vec, spanString, nullptr);
    descriptor->spanString = reinterpret_cast<void*>(spanString);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 MarshallStyledStringDescriptor(
    uint8_t* buffer, size_t bufferSize, ArkUI_StyledString_Descriptor* descriptor, size_t* resultSize)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "MarshallStyledStringDescriptor");
    CHECK_NULL_RETURN(buffer && resultSize && descriptor, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(descriptor->spanString, ArkUI_ErrorCode::ARKUI_ERROR_CODE_INVALID_STYLED_STRING);
    auto spanStringRawPtr = reinterpret_cast<SpanString*>(descriptor->spanString);
    std::vector<uint8_t> tlvData;
    spanStringRawPtr->EncodeTlv(tlvData);
    *resultSize = tlvData.size();
    if (bufferSize < *resultSize) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto data = tlvData.data();
    std::copy(data, data + *resultSize, buffer);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

const char* ConvertToHtml(ArkUI_StyledString_Descriptor* descriptor)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "ConvertToHtml");
    CHECK_NULL_RETURN(descriptor && descriptor->spanString, "");
    auto spanStringRawPtr = reinterpret_cast<SpanString*>(descriptor->spanString);
    auto htmlStr = HtmlUtils::ToHtml(spanStringRawPtr);
    char* html = new char[htmlStr.length() + 1];
    CHECK_NULL_RETURN(html, "");
    std::copy(htmlStr.begin(), htmlStr.end(), html);
    html[htmlStr.length()] = '\0';
    descriptor->html = html;
    return descriptor->html;
}

ArkUI_Int32 GetLength(const ArkUI_StyledString_Descriptor* descriptor, int32_t* length)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "GetLength");
    CHECK_NULL_RETURN(descriptor && length, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto spanStringRawPtr = reinterpret_cast<SpanString*>(descriptor->spanString);
    CHECK_NULL_RETURN(spanStringRawPtr, ArkUI_ErrorCode::ARKUI_ERROR_CODE_INVALID_STYLED_STRING);
    *length = spanStringRawPtr->GetLength();
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 GetString(const ArkUI_StyledString_Descriptor* descriptor, char* buffer, ArkUI_Int32 bufferSize,
    ArkUI_Int32* writeLength)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "GetString");
    CHECK_NULL_RETURN(descriptor && buffer && writeLength, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto spanStringRawPtr = reinterpret_cast<SpanString*>(descriptor->spanString);
    CHECK_NULL_RETURN(spanStringRawPtr, ArkUI_ErrorCode::ARKUI_ERROR_CODE_INVALID_STYLED_STRING);
    auto content = spanStringRawPtr->GetString();
    int32_t contentLength = static_cast<int32_t>(content.size());
    *writeLength = contentLength;
    if (bufferSize < contentLength + 1) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    auto size = static_cast<size_t>(bufferSize);
    if (strncpy_s(buffer, size, content.c_str(), contentLength) != 0) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR;
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 IsEqual(const ArkUI_StyledString_Descriptor* firstDescriptor,
    const ArkUI_StyledString_Descriptor* secondDescriptor, bool* isEqual)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "IsEqual");
    CHECK_NULL_RETURN(firstDescriptor && secondDescriptor && isEqual, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto firstSpanStringRawPtr = reinterpret_cast<SpanString*>(firstDescriptor->spanString);
    auto secondSpanStringRawPtr = reinterpret_cast<SpanString*>(secondDescriptor->spanString);
    CHECK_NULL_RETURN(firstSpanStringRawPtr && secondSpanStringRawPtr,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_INVALID_STYLED_STRING);
    auto length = secondSpanStringRawPtr->GetLength();
    auto secondSpanStringRefPtr = secondSpanStringRawPtr->GetSubSpanString(0, length);
    *isEqual = firstSpanStringRawPtr->IsEqualToSpanString(secondSpanStringRefPtr);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SubStyledString(const ArkUI_StyledString_Descriptor* descriptor,
    ArkUI_StyledString_Descriptor* subDescriptor, ArkUI_Uint32 start, ArkUI_Uint32 length)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "SubStyledString");
    CHECK_NULL_RETURN(descriptor && subDescriptor, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto spanStringRawPtr = reinterpret_cast<SpanString*>(descriptor->spanString);
    CHECK_NULL_RETURN(spanStringRawPtr, ArkUI_ErrorCode::ARKUI_ERROR_CODE_INVALID_STYLED_STRING);
    CHECK_NULL_RETURN(spanStringRawPtr->CheckRange(start, length), ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    MutableSpanString* spanString = new MutableSpanString(u"");
    auto subSpanString = spanStringRawPtr->GetSubSpanString(start, length);
    spanString->AppendSpanString(subSpanString);
    subDescriptor->spanString = reinterpret_cast<void*>(spanString);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

void ApplyUrlStyle(ArkUISpanStyle& style, const RefPtr<SpanBase>& span)
{
    CHECK_NULL_VOID(span);
    auto urlSpan = AceType::DynamicCast<UrlSpan>(span);
    CHECK_NULL_VOID(urlSpan);
    ArkUIUrlStyle urlStyle;
    urlStyle.url = urlSpan->GetUrlSpanAddress();
    style.urlStyle = urlStyle;
}

void ApplyFontStyle(ArkUISpanStyle& style, const RefPtr<SpanBase>& span)
{
    CHECK_NULL_VOID(span);
    auto fontSpan = AceType::DynamicCast<FontSpan>(span);
    CHECK_NULL_VOID(fontSpan);
    ArkUITextStyle textStyle;
    auto font = fontSpan->GetFont();
    textStyle.fontColor = font.fontColor ? font.fontColor->GetValue() : 0xFF000000;
    textStyle.fontFamily = font.GetFontFamily().c_str();
    textStyle.fontSize = font.fontSize ? font.fontSize->ConvertToVp() : NG::DEFAULT_TEXT_SIZE;
    textStyle.fontWeight = font.fontWeight ? static_cast<uint32_t>(font.fontWeight.value())
        : static_cast<uint32_t>(NG::DEFAULT_FONT_WEIGHT);
    textStyle.fontStyle = font.fontStyle ? static_cast<int32_t>(font.fontStyle.value()) : 0;
    textStyle.strokeWidth = font.strokeWidth ? font.strokeWidth->ConvertToVp() : 0;
    textStyle.strokeColor = font.strokeColor ? font.strokeColor->GetValue() : textStyle.fontColor;
    textStyle.superscript = font.superscript ? static_cast<int32_t>(font.superscript.value()) : 0;
    style.textStyle = textStyle;
}


void ParseImageSpanMarginAndPadding(ArkUIImageAttachment& imageAttachment, ImageSpanAttribute imageAttribute)
{
    auto marginProp = imageAttribute.marginProp;
    if (marginProp.has_value()) {
        imageAttachment.margin.top = marginProp->top.value_or(NG::CalcLength()).GetDimension().ConvertToVp();
        imageAttachment.margin.bottom = marginProp->bottom.value_or(NG::CalcLength()).GetDimension().ConvertToVp();
        imageAttachment.margin.left = marginProp->left.value_or(NG::CalcLength()).GetDimension().ConvertToVp();
        imageAttachment.margin.right = marginProp->right.value_or(NG::CalcLength()).GetDimension().ConvertToVp();
    }
    auto paddingProp = imageAttribute.paddingProp;
    if (paddingProp.has_value()) {
        imageAttachment.padding.top = paddingProp->top.value_or(NG::CalcLength()).GetDimension().ConvertToVp();
        imageAttachment.padding.bottom = paddingProp->bottom.value_or(NG::CalcLength()).GetDimension().ConvertToVp();
        imageAttachment.padding.left = paddingProp->left.value_or(NG::CalcLength()).GetDimension().ConvertToVp();
        imageAttachment.padding.right = paddingProp->right.value_or(NG::CalcLength()).GetDimension().ConvertToVp();
    }
}

void ParseImageSpanAttribute(ArkUIImageAttachment& imageAttachment,
    const std::optional<ImageSpanAttribute>& imageAttribute)
{
    CHECK_NULL_VOID(imageAttribute.has_value());
    auto imageStyle = imageAttribute.value();
    auto imageSize = imageStyle.size;
    if (imageSize.has_value()) {
        if (imageSize->width.has_value()) {
            imageAttachment.width = imageSize->width.value().ConvertToVp();
        }
        if (imageSize->height.has_value()) {
            imageAttachment.height = imageSize->height.value().ConvertToVp();
        }
    }
    ParseImageSpanMarginAndPadding(imageAttachment, imageStyle);
    auto borderRadius = imageStyle.borderRadius;
    if (borderRadius.has_value()) {
        imageAttachment.topLeftRadius = borderRadius->radiusTopLeft.value_or(Dimension()).ConvertToVp();
        imageAttachment.topRightRadius = borderRadius->radiusTopRight.value_or(Dimension()).ConvertToVp();
        imageAttachment.bottomRightRadius = borderRadius->radiusBottomRight.value_or(Dimension()).ConvertToVp();
        imageAttachment.bottomLeftRadius = borderRadius->radiusBottomLeft.value_or(Dimension()).ConvertToVp();
    }
    if (imageStyle.colorFilterMatrix.has_value() &&
        imageStyle.colorFilterMatrix.value().size() == NG::COLOR_FILTER_MATRIX_SIZE) {
        imageAttachment.isDrawingColorFilter = false;
        imageAttachment.colorFilter = imageStyle.colorFilterMatrix.value();
    }
    if (imageStyle.drawingColorFilter.has_value() && imageStyle.drawingColorFilter.value()) {
        imageAttachment.isDrawingColorFilter = true;
        auto drawingColorFilter = imageStyle.drawingColorFilter.value();
        auto filterSptr = reinterpret_cast<std::shared_ptr<OHOS::Rosen::Drawing::ColorFilter>*>(
            drawingColorFilter->GetDrawingColorFilterSptrAddr());
        if (filterSptr) {
            imageAttachment.drawingColorFilter = reinterpret_cast<void*>(filterSptr);
        }
    }
    imageAttachment.syncLoad = imageStyle.syncLoad;
    imageAttachment.supportSvg = imageStyle.supportSvg2;
    imageAttachment.verticalAlign = static_cast<int32_t>(imageStyle.verticalAlign.value_or(VerticalAlign::BOTTOM));
    imageAttachment.objectFit = static_cast<int32_t>(imageStyle.objectFit.value_or(ImageFit::COVER));
}

void ApplyImageSpan(ArkUISpanStyle& style, const RefPtr<SpanBase>& span)
{
    CHECK_NULL_VOID(span);
    auto imageSpan = AceType::DynamicCast<ImageSpan>(span);
    CHECK_NULL_VOID(imageSpan);
    ArkUIImageAttachment imageAttachment;
    auto options = imageSpan->GetImageSpanOptions();
    imageAttachment.resource = options.image.value_or("");
    if (!imageAttachment.resource.empty()) {
        imageAttachment.isPixelMap = false;
    }
    if (options.imagePixelMap.has_value() && options.imagePixelMap.value()) {
        std::vector<uint8_t> pixelMapRawData;
        std::vector<uint8_t> data;
        options.imagePixelMap.value()->EncodeTlv(data);
        imageAttachment.pixelMapRawData = data;
        imageAttachment.isPixelMap = true;
    }
    ParseImageSpanAttribute(imageAttachment, options.imageAttribute);
    style.imageAttachment = imageAttachment;
}

void ApplyUserDatSpan(ArkUISpanStyle& style, const RefPtr<SpanBase>& span)
{
    CHECK_NULL_VOID(span);
    auto extSpan = AceType::DynamicCast<ExtSpan>(span);
    CHECK_NULL_VOID(extSpan);
    ArkUIUserDataSpan userDataSpan;
    userDataSpan.userData = extSpan->userData_;
    style.userDataSpan = userDataSpan;
}

void ApplyGestureStyle(ArkUISpanStyle& style, const RefPtr<SpanBase>& span)
{
    CHECK_NULL_VOID(span);
    auto napiGestureSpan = AceType::DynamicCast<NapiGestureSpan>(span);
    CHECK_NULL_VOID(napiGestureSpan);
    ArkUIGestureStyle gestureStyle;
    gestureStyle.onNapiClick = napiGestureSpan->onNapiClick_;
    gestureStyle.onNapiLongPress = napiGestureSpan->onNapiLongPress_;
    gestureStyle.onNapiTouch = napiGestureSpan->onNapiTouch_;
    style.gestureStyle = gestureStyle;
}

void ApplyCustomSpan(ArkUISpanStyle& style, const RefPtr<SpanBase>& span)
{
    CHECK_NULL_VOID(span);
    auto napiCustomSpan = AceType::DynamicCast<NapiCustomSpan>(span);
    CHECK_NULL_VOID(napiCustomSpan);
    ArkUICustomSpan customSpan;
    customSpan.onMeasure = napiCustomSpan->onNapiMeasure_;
    customSpan.onDraw = napiCustomSpan->onNapiDraw_;
    style.customSpan = customSpan;
}

void ApplyLineHeightStyle(ArkUISpanStyle& style, const RefPtr<SpanBase>& span)
{
    CHECK_NULL_VOID(span);
    auto lineHeightSpan = AceType::DynamicCast<LineHeightSpan>(span);
    CHECK_NULL_VOID(lineHeightSpan);
    ArkUILineHeightStyle lineHeightStyle;
    lineHeightStyle.lineHeight = lineHeightSpan->GetLineHeight().ConvertToVp();
    style.lineHeightStyle = lineHeightStyle;
}

void ApplyTextShadowStyle(ArkUISpanStyle& style, const RefPtr<SpanBase>& span)
{
    CHECK_NULL_VOID(span);
    auto textShadowSpan = AceType::DynamicCast<TextShadowSpan>(span);
    CHECK_NULL_VOID(textShadowSpan);
    auto shadows = textShadowSpan->GetTextShadow();
    ArkUITextShadowStyle textShadowStyle;
    for (const auto& shadow : shadows) {
        ArkUIShadowOptions textShadow;
        textShadow.color = shadow.GetColor().GetValue();
        textShadow.offsetX = shadow.GetOffset().GetX();
        textShadow.offsetY = shadow.GetOffset().GetY();
        textShadow.isFill = shadow.GetIsFilled();
        textShadow.radius = shadow.GetBlurRadius();
        textShadow.type = static_cast<int32_t>(shadow.GetShadowType());
        textShadowStyle.textShadow.emplace_back(textShadow);
    }
    style.textShadowStyle = textShadowStyle;
}

void ApplyDecorationStyle(ArkUISpanStyle& style, const RefPtr<SpanBase>& span)
{
    CHECK_NULL_VOID(span);
    auto decorationSpan = AceType::DynamicCast<DecorationSpan>(span);
    CHECK_NULL_VOID(decorationSpan);
    ArkUIDecorationStyle decorationStyle;
    auto color = decorationSpan->GetColor();
    decorationStyle.color = color.has_value() ? color->GetValue() : 0;
    auto decorationTypes = decorationSpan->GetTextDecorationTypes();
    decorationStyle.type = decorationTypes.empty() ? ArkUI_TextDecorationType::ARKUI_TEXT_DECORATION_TYPE_NONE:
        static_cast<ArkUI_TextDecorationType>(decorationTypes[0]);
    auto textDecorationStyle = decorationSpan->GetTextDecorationStyle();
    decorationStyle.style = textDecorationStyle.has_value() ?
        static_cast<ArkUI_TextDecorationStyle>(textDecorationStyle.value()) :
        ArkUI_TextDecorationStyle::ARKUI_TEXT_DECORATION_STYLE_SOLID;
    decorationStyle.thicknessScale = decorationSpan->GetTextDecorationLineThicknessScale().value_or(1.0f);
    auto options = decorationSpan->GetTextDecorationOptions();
    decorationStyle.enableMultiType = options.has_value() ? options->enableMultiType.value_or(false) : false;
    style.decorationStyle = decorationStyle;
}

void ApplyParagraphStyle(ArkUISpanStyle& style, const RefPtr<SpanBase>& span)
{
    CHECK_NULL_VOID(span);
    auto napiParagraphStyleSpan = AceType::DynamicCast<NapiParagraphStyleSpan>(span);
    CHECK_NULL_VOID(napiParagraphStyleSpan);
    SpanParagraphStyle spanParagraphStyle = napiParagraphStyleSpan->GetParagraphStyle();
    ArkUIParagraphStyle paragraphStyle;
    paragraphStyle.textAlign = static_cast<int32_t>(spanParagraphStyle.align.value_or(TextAlign::START));
    paragraphStyle.textIndent = spanParagraphStyle.textIndent.value_or(Dimension()).ConvertToVp();
    paragraphStyle.maxLines = spanParagraphStyle.maxLines.value_or(INT32_MAX);
    paragraphStyle.overflow = static_cast<int32_t>(spanParagraphStyle.textOverflow.value_or(TextOverflow::CLIP));
    paragraphStyle.wordBreak = static_cast<int32_t>(spanParagraphStyle.wordBreak.value_or(WordBreak::NORMAL));
    paragraphStyle.paragraphSpacing = spanParagraphStyle.paragraphSpacing.value_or(Dimension()).ConvertToVp();
    paragraphStyle.textVerticalAlignment = static_cast<std::int32_t>(
        spanParagraphStyle.textVerticalAlign.value_or(TextVerticalAlign::BASELINE));
    paragraphStyle.onDrawLeadingMargin = napiParagraphStyleSpan->onNapiDrawLeadingMargin_;
    paragraphStyle.onGetLeadingMargin = napiParagraphStyleSpan->onNapiGetLeadingMargin_;
    paragraphStyle.textDirection = static_cast<int32_t>(spanParagraphStyle.textDirection.
        value_or(TextDirection::AUTO));
    auto leadingMargin = spanParagraphStyle.leadingMargin;
    if (leadingMargin.has_value()) {
        auto size = leadingMargin->size;
        paragraphStyle.height = size.Height().ConvertToVp();
        paragraphStyle.width = size.Width().ConvertToVp();
        auto pixelMap = leadingMargin->pixmap;
        if (pixelMap) {
            std::vector<uint8_t> data;
            pixelMap->EncodeTlv(data);
            paragraphStyle.pixelMapRawData = data;
        }
    }
    style.paragraphStyle = paragraphStyle;
}

void ApplyLetterSpacingStyle(ArkUISpanStyle& style, const RefPtr<SpanBase>& span)
{
    CHECK_NULL_VOID(span);
    auto letterSpacingSpan = AceType::DynamicCast<LetterSpacingSpan>(span);
    CHECK_NULL_VOID(letterSpacingSpan);
    ArkUILetterSpacingStyle letterSpacingStyle;
    letterSpacingStyle.letterSpacing = letterSpacingSpan->GetLetterSpacing().ConvertToVp();
    style.letterSpacingStyle = letterSpacingStyle;
}

void ApplyBaselineOffsetStyle(ArkUISpanStyle& style, const RefPtr<SpanBase>& span)
{
    CHECK_NULL_VOID(span);
    auto baselineOffsetSpan = AceType::DynamicCast<BaselineOffsetSpan>(span);
    CHECK_NULL_VOID(baselineOffsetSpan);
    ArkUIBaselineOffsetStyle baselineOffsetStyle;
    baselineOffsetStyle.baselineOffset = baselineOffsetSpan->GetBaselineOffset().ConvertToVp();
    style.baselineOffsetStyle = baselineOffsetStyle;
}

void ApplyBackgroundColorStyle(ArkUISpanStyle& style, const RefPtr<SpanBase>& span)
{
    CHECK_NULL_VOID(span);
    auto backgroundColorSpan = AceType::DynamicCast<BackgroundColorSpan>(span);
    CHECK_NULL_VOID(backgroundColorSpan);
    ArkUIBackgroundColorStyle backgroundColorStyle;
    TextBackgroundStyle backgroundStyle = backgroundColorSpan->GetBackgroundColor();
    backgroundColorStyle.color = backgroundStyle.backgroundColor.has_value() ?
        backgroundStyle.backgroundColor->GetValue() : 0;
    auto radius = backgroundStyle.backgroundRadius;
    if (radius.has_value()) {
        backgroundColorStyle.topLeftRadius = radius->radiusTopLeft.value_or(Dimension()).ConvertToVp();
        backgroundColorStyle.topRightRadius = radius->radiusTopRight.value_or(Dimension()).ConvertToVp();
        backgroundColorStyle.bottomLeftRadius = radius->radiusBottomLeft.value_or(Dimension()).ConvertToVp();
        backgroundColorStyle.bottomRightRadius = radius->radiusBottomRight.value_or(Dimension()).ConvertToVp();
    }
    style.backgroundColorStyle = backgroundColorStyle;
}

using SpanStyleHandler = void (*)(ArkUISpanStyle& style, const RefPtr<SpanBase>& span);

static const std::map<SpanType, SpanStyleHandler> spanStyleHandlerMap = {
    { SpanType::Url, &ApplyUrlStyle },
    { SpanType::Font, &ApplyFontStyle },
    { SpanType::Image, &ApplyImageSpan },
    { SpanType::ExtSpan, &ApplyUserDatSpan },
    { SpanType::Gesture, &ApplyGestureStyle },
    { SpanType::CustomSpan, &ApplyCustomSpan },
    { SpanType::LineHeight, &ApplyLineHeightStyle },
    { SpanType::TextShadow, &ApplyTextShadowStyle },
    { SpanType::Decoration, &ApplyDecorationStyle },
    { SpanType::ParagraphStyle, &ApplyParagraphStyle },
    { SpanType::LetterSpacing, &ApplyLetterSpacingStyle },
    { SpanType::BaselineOffset, &ApplyBaselineOffsetStyle },
    { SpanType::BackgroundColor, &ApplyBackgroundColorStyle },
};

ArkUISpanStyle CreateSpanStyle(const RefPtr<SpanBase>& span)
{
    ArkUISpanStyle spanStyle;
    CHECK_NULL_RETURN(span, spanStyle);
    spanStyle.start = span->GetStartIndex();
    spanStyle.length = span->GetLength();
    spanStyle.styledKey = static_cast<int32_t>(span->GetSpanType());
    auto it = spanStyleHandlerMap.find(span->GetSpanType());
    CHECK_NULL_RETURN(it != spanStyleHandlerMap.end(), spanStyle);
    SpanStyleHandler handler = it->second;
    handler(spanStyle, span);
    return spanStyle;
}

ArkUI_Int32 GetStyles(const ArkUI_StyledString_Descriptor* descriptor, ArkUI_Uint32 start, ArkUI_Uint32 length,
    ArkUI_Int32 styledKey, std::vector<ArkUISpanStyle>& styles)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "GetStyles");
    CHECK_NULL_RETURN(descriptor, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto spanStringRawPtr = reinterpret_cast<SpanString*>(descriptor->spanString);
    CHECK_NULL_RETURN(spanStringRawPtr, ArkUI_ErrorCode::ARKUI_ERROR_CODE_INVALID_STYLED_STRING);
    CHECK_NULL_RETURN(spanStringRawPtr->CheckRange(start, length), ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    std::vector<RefPtr<SpanBase>> spans;
    if (styledKey == UNSPECIFIED_SPAN_TYPE) {
        spans = spanStringRawPtr->GetSpans(start, length);
    } else {
        auto spanType = static_cast<SpanType>(styledKey);
        spans = spanStringRawPtr->GetSpans(start, length, spanType);
    }
    for (const auto& spanBase : spans) {
        styles.push_back(CreateSpanStyle(spanBase));
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 FromHtml(ArkUI_StyledString_Descriptor* descriptor, ArkUI_CharPtr html)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "FromHtml");
    CHECK_NULL_RETURN(descriptor && html, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto styledString = HtmlUtils::FromHtml(std::string(html));
    MutableSpanString* spanString = new MutableSpanString(u"");
    spanString->AppendSpanString(styledString);
    descriptor->spanString = reinterpret_cast<void*>(spanString);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 ReplaceString(ArkUI_StyledString_Descriptor* descriptor, ArkUI_Uint32 start, ArkUI_Uint32 length,
    ArkUI_CharPtr string)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "ReplaceString");
    CHECK_NULL_RETURN(descriptor && string, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto spanStringRawPtr = reinterpret_cast<MutableSpanString*>(descriptor->spanString);
    CHECK_NULL_RETURN(spanStringRawPtr, ArkUI_ErrorCode::ARKUI_ERROR_CODE_INVALID_STYLED_STRING);
    CHECK_NULL_RETURN(spanStringRawPtr->CheckRange(start, length), ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    spanStringRawPtr->ReplaceString(start, length, UtfUtils::Str8ToStr16(std::string(string)));
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 InsertString(ArkUI_StyledString_Descriptor* descriptor, ArkUI_Uint32 start, ArkUI_CharPtr string)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "InsertString");
    CHECK_NULL_RETURN(descriptor && string, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto spanStringRawPtr = reinterpret_cast<MutableSpanString*>(descriptor->spanString);
    CHECK_NULL_RETURN(spanStringRawPtr, ArkUI_ErrorCode::ARKUI_ERROR_CODE_INVALID_STYLED_STRING);
    CHECK_NULL_RETURN(spanStringRawPtr->CheckRange(start, 0, true), ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    spanStringRawPtr->InsertString(start, UtfUtils::Str8ToStr16(std::string(string)));
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 RemoveString(ArkUI_StyledString_Descriptor* descriptor, ArkUI_Uint32 start, ArkUI_Uint32 length)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "RemoveString");
    CHECK_NULL_RETURN(descriptor, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto spanStringRawPtr = reinterpret_cast<MutableSpanString*>(descriptor->spanString);
    CHECK_NULL_RETURN(spanStringRawPtr, ArkUI_ErrorCode::ARKUI_ERROR_CODE_INVALID_STYLED_STRING);
    CHECK_NULL_RETURN(spanStringRawPtr->CheckRange(start, length), ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    spanStringRawPtr->RemoveString(start, length);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 ReplaceStyle(ArkUI_StyledString_Descriptor* descriptor, const ArkUISpanStyle& spanStyle)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "ReplaceStyle");
    CHECK_NULL_RETURN(descriptor, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(spanStyle.styledKey != UNSPECIFIED_SPAN_TYPE, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto spanStringRawPtr = reinterpret_cast<MutableSpanString*>(descriptor->spanString);
    CHECK_NULL_RETURN(spanStringRawPtr, ArkUI_ErrorCode::ARKUI_ERROR_CODE_INVALID_STYLED_STRING);
    auto start = spanStyle.start;
    auto length = spanStyle.length;
    auto spanType = static_cast<SpanType>(spanStyle.styledKey);
    CHECK_EQUAL_RETURN(spanType == SpanType::Image &&
        (length != 1 || !spanStringRawPtr->IsSpeicalNode(start, SpanType::Image)),
        true, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_EQUAL_RETURN(spanType == SpanType::CustomSpan &&
        (length != 1 || !spanStringRawPtr->IsSpeicalNode(start, SpanType::CustomSpan)),
        true, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(spanStringRawPtr->CheckRange(start, length), ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto maxLength = spanStringRawPtr->GetLength();
    auto spanBase = ParseSpanBase(spanStyle, maxLength);
    spanStringRawPtr->ReplaceSpan(start, length, spanBase);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetStyle(ArkUI_StyledString_Descriptor* descriptor, const ArkUISpanStyle& spanStyle)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "SetStyle");
    CHECK_NULL_RETURN(descriptor, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(spanStyle.styledKey != UNSPECIFIED_SPAN_TYPE, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto spanStringRawPtr = reinterpret_cast<MutableSpanString*>(descriptor->spanString);
    CHECK_NULL_RETURN(spanStringRawPtr, ArkUI_ErrorCode::ARKUI_ERROR_CODE_INVALID_STYLED_STRING);
    auto start = spanStyle.start;
    auto length = spanStyle.length;
    auto spanType = static_cast<SpanType>(spanStyle.styledKey);
    CHECK_EQUAL_RETURN(spanType == SpanType::Image &&
        (length != 1 || !spanStringRawPtr->IsSpeicalNode(start, SpanType::Image)),
        true, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_EQUAL_RETURN(spanType == SpanType::CustomSpan &&
        (length != 1 || !spanStringRawPtr->IsSpeicalNode(start, SpanType::CustomSpan)),
        true, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(spanStringRawPtr->CheckRange(start, length), ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto maxLength = spanStringRawPtr->GetLength();
    auto spanBase = ParseSpanBase(spanStyle, maxLength);
    spanStringRawPtr->AddSpan(spanBase);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 RemoveStyle(ArkUI_StyledString_Descriptor* descriptor, ArkUI_Uint32 start, ArkUI_Uint32 length,
    ArkUI_Int32 styledKey)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "RemoveStyle");
    CHECK_NULL_RETURN(descriptor, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto spanStringRawPtr = reinterpret_cast<MutableSpanString*>(descriptor->spanString);
    CHECK_NULL_RETURN(spanStringRawPtr, ArkUI_ErrorCode::ARKUI_ERROR_CODE_INVALID_STYLED_STRING);
    CHECK_NULL_RETURN(spanStringRawPtr->CheckRange(start, length), ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    if (styledKey == UNSPECIFIED_SPAN_TYPE) {
        spanStringRawPtr->RemoveSpans(start, length);
    } else {
        auto type = static_cast<SpanType>(styledKey);
        spanStringRawPtr->RemoveSpan(start, length, type);
    }
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 ClearStyles(ArkUI_StyledString_Descriptor* descriptor)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "ClearStyles");
    CHECK_NULL_RETURN(descriptor, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto spanStringRawPtr = reinterpret_cast<MutableSpanString*>(descriptor->spanString);
    CHECK_NULL_RETURN(spanStringRawPtr, ArkUI_ErrorCode::ARKUI_ERROR_CODE_INVALID_STYLED_STRING);
    spanStringRawPtr->ClearAllSpans();
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 ReplaceStyledString(ArkUI_StyledString_Descriptor* descriptor, ArkUI_Uint32 start, ArkUI_Uint32 length,
    const ArkUI_StyledString_Descriptor* other)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "ReplaceStyledString");
    CHECK_NULL_RETURN(descriptor && other, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto spanStringRawPtr = reinterpret_cast<MutableSpanString*>(descriptor->spanString);
    auto otherSpanStringRawPtr = reinterpret_cast<SpanString*>(other->spanString);
    CHECK_NULL_RETURN(spanStringRawPtr && otherSpanStringRawPtr,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_INVALID_STYLED_STRING);
    CHECK_NULL_RETURN(spanStringRawPtr->CheckRange(start, length), ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto spanStringlength = otherSpanStringRawPtr->GetLength();
    auto otherSpanStringRefPtr = otherSpanStringRawPtr->GetSubSpanString(0, spanStringlength);
    spanStringRawPtr->ReplaceSpanString(start, length, otherSpanStringRefPtr);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 InsertStyledString(ArkUI_StyledString_Descriptor* descriptor, ArkUI_Uint32 start,
    const ArkUI_StyledString_Descriptor* other)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "InsertStyledString");
    CHECK_NULL_RETURN(descriptor && other, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto spanStringRawPtr = reinterpret_cast<MutableSpanString*>(descriptor->spanString);
    auto otherSpanStringRawPtr = reinterpret_cast<SpanString*>(other->spanString);
    CHECK_NULL_RETURN(spanStringRawPtr && otherSpanStringRawPtr,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_INVALID_STYLED_STRING);
    CHECK_NULL_RETURN(spanStringRawPtr->CheckRange(start, 0, true), ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto spanStringlength = otherSpanStringRawPtr->GetLength();
    auto otherSpanStringRefPtr = otherSpanStringRawPtr->GetSubSpanString(0, spanStringlength);
    spanStringRawPtr->InsertSpanString(start, otherSpanStringRefPtr);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 AppendStyledString(ArkUI_StyledString_Descriptor* descriptor, const ArkUI_StyledString_Descriptor* other)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "AppendStyledString");
    CHECK_NULL_RETURN(descriptor && other, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto spanStringRawPtr = reinterpret_cast<MutableSpanString*>(descriptor->spanString);
    auto otherSpanStringRawPtr = reinterpret_cast<SpanString*>(other->spanString);
    CHECK_NULL_RETURN(spanStringRawPtr && otherSpanStringRawPtr,
        ArkUI_ErrorCode::ARKUI_ERROR_CODE_INVALID_STYLED_STRING);
    auto length = otherSpanStringRawPtr->GetLength();
    auto otherSpanStringRefPtr = otherSpanStringRawPtr->GetSubSpanString(0, length);
    spanStringRawPtr->AppendSpanString(otherSpanStringRefPtr);
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 InvalidateCustomSpan(const ArkUI_StyledString_Descriptor* descriptor)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "InvalidateCustomSpan");
    CHECK_NULL_RETURN(descriptor, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    auto spanStringRawPtr = reinterpret_cast<SpanString*>(descriptor->spanString);
    CHECK_NULL_RETURN(spanStringRawPtr, ArkUI_ErrorCode::ARKUI_ERROR_CODE_INVALID_STYLED_STRING);
    spanStringRawPtr->MarkDirtyFrameNode();
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

void GetReplacementStyledString(const ArkUITextEditorChangeEvent* event, ArkUI_StyledString_Descriptor* descriptor)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "GetReplacementStyledString");
    CHECK_NULL_VOID(event && descriptor);
    auto* result = new OHOS::Ace::MutableSpanString(u"");
    auto* replacementStyledString = reinterpret_cast<OHOS::Ace::MutableSpanString*>(event->replacementStyledString);
    if (replacementStyledString) {
        auto length = replacementStyledString->GetLength();
        result->AppendSpanString(replacementStyledString->GetSubSpanString(0, length));
    }
    descriptor->spanString = result;
}

void GetPreviewStyledString(const ArkUITextEditorChangeEvent* event, ArkUI_StyledString_Descriptor* descriptor)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "GetPreviewStyledString");
    CHECK_NULL_VOID(event && descriptor);
    auto* result = new OHOS::Ace::MutableSpanString(u"");
    auto* previewStyledString = reinterpret_cast<OHOS::Ace::MutableSpanString*>(event->previewStyledString);
    if (previewStyledString) {
        auto length = previewStyledString->GetLength();
        result->AppendSpanString(previewStyledString->GetSubSpanString(0, length));
    }
    descriptor->spanString = result;
}
} // namespace

const ArkUIStyledStringAPI* GetStyledStringAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIStyledStringAPI impl {
        .createArkUIStyledStringDescriptor = CreateArkUIStyledStringDescriptor,
        .createArkUIStyledStringDescriptorWithString = CreateArkUIStyledStringDescriptorWithString,
        .createArkUIStyledStringDescriptorWithImage = CreateArkUIStyledStringDescriptorWithImage,
        .createArkUIStyledStringDescriptorWithCustomSpan = CreateArkUIStyledStringDescriptorWithCustomSpan,
        .destroyArkUIStyledStringDescriptor = DestroyArkUIStyledStringDescriptor,
        .unmarshallStyledStringDescriptor = UnmarshallStyledStringDescriptor,
        .marshallStyledStringDescriptor = MarshallStyledStringDescriptor,
        .convertToHtml = ConvertToHtml,
        .getLength = GetLength,
        .getString = GetString,
        .isEqual = IsEqual,
        .subStyledString = SubStyledString,
        .getStyles = GetStyles,
        .fromHtml = FromHtml,
        .replaceString = ReplaceString,
        .insertString = InsertString,
        .removeString = RemoveString,
        .replaceStyle = ReplaceStyle,
        .setStyle = SetStyle,
        .removeStyle = RemoveStyle,
        .clearStyles = ClearStyles,
        .replaceStyledString = ReplaceStyledString,
        .insertStyledString = InsertStyledString,
        .appendStyledString = AppendStyledString,
        .invalidateCustomSpan = InvalidateCustomSpan,
        .getReplacementStyledString = GetReplacementStyledString,
        .getPreviewStyledString = GetPreviewStyledString
    };
    CHECK_INITIALIZED_FIELDS_END(impl, 0, 0, 0); // don't move this line
    return &impl;
}
} // namespace OHOS::Ace::StyledStringAdapter
