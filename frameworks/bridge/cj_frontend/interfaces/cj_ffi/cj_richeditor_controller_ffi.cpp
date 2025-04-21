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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_richeditor_controller_ffi.h"

#include "pixel_map_impl.h"
#include "base/utils/utf_helper.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components/common/properties/text_style_parser.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {

const int64_t SUB_FLAG = 2;

std::vector<FontStyle> FONTSTYLE_TYPES = {
    FontStyle::NORMAL, FontStyle::ITALIC
};

std::vector<TextDecoration> TEXTDECORATION_TYPES = {
    TextDecoration::NONE,
    TextDecoration::UNDERLINE,
    TextDecoration::OVERLINE,
    TextDecoration::LINE_THROUGH
};

std::vector<TextAlign> TEXT_ALIGNS = {
    TextAlign::START,
    TextAlign::CENTER,
    TextAlign::END,
    TextAlign::LEFT,
    TextAlign::RIGHT,
    TextAlign::JUSTIFY
};

std::vector<VerticalAlign> VERTICAL_ALIGNS = {
    VerticalAlign::TOP,
    VerticalAlign::CENTER,
    VerticalAlign::BOTTOM,
    VerticalAlign::BASELINE
};

std::vector<ImageFit> IMAGEFIT_TYPES = {
    ImageFit::FILL,
    ImageFit::CONTAIN,
    ImageFit::COVER,
    ImageFit::NONE,
    ImageFit::SCALE_DOWN,
    ImageFit::FITWIDTH
};

std::vector<MarginType> MARGIN_TYPES = {
    MarginType::NONE,
    MarginType::MARGIN_LENGTH,
    MarginType::MARGIN_PLACEHOLDER
};

std::function<void(const GestureEvent& event)> FormatGestureEvenFunction(void (*callback)(CJGestureEventV2 info))
{
    std::function<void(const GestureEvent& event)> result = [ffiOnAction = CJLambda::Create(callback)](
                                                                const GestureEvent& event) -> void {
        CJGestureEventV2 ffiGestureEvent {};
        CJEventTarget ffiEventTarget {};
        CJArea ffiArea {};
        CJPosition ffiPosition {};
        CJPosition ffiGlobalPosition {};

        const auto& eventTarget = event.GetTarget();
        ffiArea.width = eventTarget.area.GetWidth().ConvertToVp();
        ffiArea.height = eventTarget.area.GetHeight().ConvertToVp();
        const auto& localOffset = eventTarget.area.GetOffset();
        const auto& origin = eventTarget.origin;
        ffiPosition.x = localOffset.GetX().ConvertToVp();
        ffiPosition.y = localOffset.GetY().ConvertToVp();
        ffiGlobalPosition.x = origin.GetX().ConvertToVp() + localOffset.GetX().ConvertToVp();
        ffiGlobalPosition.y = origin.GetY().ConvertToVp() + localOffset.GetY().ConvertToVp();

        ffiArea.globalPosition = &ffiGlobalPosition;
        ffiArea.position = &ffiPosition;

        ffiEventTarget.area = &ffiArea;

        auto& fingerList = event.GetFingerList();
        ffiGestureEvent.fingerListSize = static_cast<int32_t>(fingerList.size());
        ffiGestureEvent.fingerList = new CJFingerInfo[fingerList.size()];
        TransformNativeCJFingerInfo(ffiGestureEvent.fingerList, fingerList);

        ffiGestureEvent.target = &ffiEventTarget;
        ffiGestureEvent.timestamp = event.GetTimeStamp().time_since_epoch().count();
        ffiGestureEvent.repeat = event.GetRepeat();
        ffiGestureEvent.source = static_cast<int32_t>(event.GetSourceDevice());
        ffiGestureEvent.offsetX = event.GetOffsetX();
        ffiGestureEvent.offsetY = event.GetOffsetY();
        ffiGestureEvent.scale = event.GetScale();
        ffiGestureEvent.pinchCenterX = event.GetPinchCenter().GetX();
        ffiGestureEvent.pinchCenterY = event.GetPinchCenter().GetY();
        ffiGestureEvent.angle = event.GetAngle();
        ffiGestureEvent.speed = event.GetSpeed();
        ffiGestureEvent.tiltX = event.GetTiltX().value_or(0.0f);
        ffiGestureEvent.tiltY = event.GetTiltY().value_or(0.0f);
        ffiGestureEvent.sourceTool = static_cast<int32_t>(event.GetSourceTool());
        ffiGestureEvent.velocityX = PipelineBase::Px2VpWithCurrentDensity(event.GetVelocity().GetVelocityX());
        ffiGestureEvent.velocityY = PipelineBase::Px2VpWithCurrentDensity(event.GetVelocity().GetVelocityY());
        ffiGestureEvent.velocity = PipelineBase::Px2VpWithCurrentDensity(event.GetVelocity().GetVelocityValue());
        ffiGestureEvent.pressure = event.GetForce();
        ffiGestureEvent.axisHorizontal = event.GetHorizontalAxis();
        ffiGestureEvent.axisVertical = event.GetVerticalAxis();
        ffiGestureEvent.deviceId = event.GetDeviceId();
        ffiGestureEvent.baseEventInfoPtr = dynamic_cast<const BaseEventInfo*>(&event);
        ffiOnAction(ffiGestureEvent);
    };
    return result;
}

char* MallocCString(const std::string& origin)
{
    auto len = origin.length() + 1;
    char* res = static_cast<char*>(malloc(sizeof(char) * len));
    if (res == nullptr) {
        return nullptr;
    }
    return std::char_traits<char>::copy(res, origin.c_str(), len);
}
}

namespace OHOS::Ace::Framework {
static void NativeShaowOptionsFree(int64_t size, NativeShadowOptionsResult* src)
{
    if (!src) {
        return;
    }
    delete[] src;
}

void NativeRichEditorController::ParseTextStyleResult(
    const TextStyleResult& textStyle, NativeRichEditorTextStyleResult& nativeTextStyle)
{
    nativeTextStyle.fontColor = MallocCString(textStyle.fontColor);
    nativeTextStyle.fontSize = textStyle.fontSize;
    nativeTextStyle.fontStyle = textStyle.fontStyle;
    nativeTextStyle.fontWeight = textStyle.fontWeight;
    nativeTextStyle.fontFamily = MallocCString(textStyle.fontFamily);
    NativeTextDecorationResult decoration;
    decoration.type = textStyle.decorationType;
    decoration.color = MallocCString(textStyle.decorationColor);
    nativeTextStyle.decoration = decoration;
}

void NativeRichEditorController::ParseTextStyleResult(
    const TextStyleResult& textStyle, NativeRichEditorTextStyleResult12& nativeTextStyle)
{
    nativeTextStyle.fontColor = Utils::MallocCString(textStyle.fontColor.c_str());
    nativeTextStyle.fontSize = textStyle.fontSize;
    nativeTextStyle.fontStyle = textStyle.fontStyle;
    nativeTextStyle.fontWeight = textStyle.fontWeight;
    nativeTextStyle.fontFamily = Utils::MallocCString(textStyle.fontFamily.c_str());
    NativeTextDecorationResult decoration;
    decoration.type = textStyle.decorationType;
    decoration.color = textStyle.decorationColor.c_str();
    nativeTextStyle.decoration = decoration;

    auto textShadows = textStyle.textShadows;
    auto nativbeTextShadow = new NativeShadowOptionsResult[textShadows.size()];
    int32_t index = 0;
    for (const auto& it : textShadows) {
        NativeShadowOptionsResult current;
        current.radius = it.GetBlurRadius();
        current.color = Utils::MallocCString(it.GetColor().ToString());
        current.offsetX = it.GetOffset().GetX();
        current.offsetY = it.GetOffset().GetY();
        nativbeTextShadow[index] = current;
        index++;
    }
    nativeTextStyle.textShadow = nativbeTextShadow;
    nativeTextStyle.textShadowSize = static_cast<int64_t>(textShadows.size());
    nativeTextStyle.free = NativeShaowOptionsFree;
    nativeTextStyle.lineHeight = textStyle.lineHeight;
    nativeTextStyle.letterSpacing = textStyle.letterSpacing;
    nativeTextStyle.fontFeature = Utils::MallocCString(
        UnParseFontFeatureSetting(textStyle.fontFeature));
}

void NativeRichEditorController::ParseImageStyleResult(
    const ImageStyleResult& imageStyleResult, NativeRichEditorImageSpanStyleResult& nativeImageStyle)
{
    nativeImageStyle.size0 = static_cast<double>(imageStyleResult.size[0]);
    nativeImageStyle.size1 = static_cast<double>(imageStyleResult.size[1]);
    nativeImageStyle.verticalAlign = static_cast<int32_t>(imageStyleResult.verticalAlign);
    nativeImageStyle.objectFit = static_cast<int32_t>(imageStyleResult.objectFit);
    NativeRichEditorLayoutStyleResult layoutStyle;
    layoutStyle.borderRadius = Utils::MallocCString(imageStyleResult.borderRadius);
    layoutStyle.margin = Utils::MallocCString(imageStyleResult.margin);
    nativeImageStyle.layoutStyle = layoutStyle;
}

void NativeRichEditorController::ParseTypingStyleResult(
    const UpdateSpanStyle& typingStyle, NativeRichEditorTextStyleResult12& nativeTextStyle)
{
    nativeTextStyle.fontColor = Utils::MallocCString(typingStyle.updateTextColor.value().ColorToString());
    nativeTextStyle.fontSize = typingStyle.updateFontSize.value().ConvertToVp();
    nativeTextStyle.fontStyle = static_cast<int32_t>(typingStyle.updateItalicFontStyle.value());
    nativeTextStyle.fontWeight = static_cast<int32_t>(typingStyle.updateFontWeight.value());
    nativeTextStyle.fontFamily = Utils::MallocCString(V2::ConvertFontFamily(typingStyle.updateFontFamily.value()));
    NativeTextDecorationResult decoration;
    decoration.type = static_cast<int32_t>(typingStyle.updateTextDecoration.value());
    decoration.color = typingStyle.updateTextDecorationColor.value().ColorToString().c_str();
    nativeTextStyle.decoration = decoration;

    auto textShadows = typingStyle.updateTextShadows.value();
    auto nativbeTextShadow = new NativeShadowOptionsResult[textShadows.size()];
    int32_t index = 0;
    for (const auto& it : textShadows) {
        NativeShadowOptionsResult current;
        current.radius = it.GetBlurRadius();
        current.color = Utils::MallocCString(it.GetColor().ToString());
        current.offsetX = it.GetOffset().GetX();
        current.offsetY = it.GetOffset().GetY();
        nativbeTextShadow[index] = current;
        index++;
    }
    nativeTextStyle.textShadow = nativbeTextShadow;
    nativeTextStyle.textShadowSize = static_cast<int64_t>(textShadows.size());
    nativeTextStyle.free = NativeShaowOptionsFree;
    nativeTextStyle.lineHeight = typingStyle.updateLineHeight.value().ConvertToVp();
    nativeTextStyle.letterSpacing = typingStyle.updateLetterSpacing.value().ConvertToVp();
    nativeTextStyle.fontFeature = Utils::MallocCString(
        UnParseFontFeatureSetting(typingStyle.updateFontFeature.value()));
}

void NativeRichEditorController::ParseRichEditorTextSpanResult(
    const ResultObject& spanObject, NativeRichEditorTextSpanResult& nativeTextResult)
{
    NativeRichEditorSpanPosition spanPosition;
    spanPosition.spanIndex = spanObject.spanPosition.spanIndex;
    spanPosition.spanStart = spanObject.spanPosition.spanRange[0];
    spanPosition.spanEnd = spanObject.spanPosition.spanRange[1];
    NativeRichEditorTextStyleResult nativeTextStyle;
    ParseTextStyleResult(spanObject.textStyle, nativeTextStyle);

    nativeTextResult.textStyle = nativeTextStyle;
    nativeTextResult.offsetInSpanStart = spanObject.offsetInSpan[0];
    nativeTextResult.offsetInSpanEnd = spanObject.offsetInSpan[1];
    nativeTextResult.spanPosition = spanPosition;
    std::string u8ValueString = UtfUtils::Str16ToStr8(spanObject.valueString);
    auto len = u8ValueString.size() + 1;
    char* cString = static_cast<char*>(malloc(sizeof(char) * len));
    if (cString == nullptr) {
        LOGE("ParseRichEditorTextSpanResult error, malloc cString failed");
        return;
    }
    std::char_traits<char>::copy(cString, u8ValueString.c_str(), len);
    nativeTextResult.value = cString;
}

void NativeRichEditorController::ParseRichEditorTextSpanResult(
    const ResultObject& spanObject, NativeRichEditorTextSpanResult12& nativeTextResult)
{
    NativeRichEditorSpanPosition spanPosition;
    spanPosition.spanIndex = spanObject.spanPosition.spanIndex;
    spanPosition.spanStart = spanObject.spanPosition.spanRange[0];
    spanPosition.spanEnd = spanObject.spanPosition.spanRange[1];
    NativeRichEditorTextStyleResult12 nativeTextStyle;
    ParseTextStyleResult(spanObject.textStyle, nativeTextStyle);

    nativeTextResult.textStyle = nativeTextStyle;
    nativeTextResult.offsetInSpanStart = spanObject.offsetInSpan[0];
    nativeTextResult.offsetInSpanEnd = spanObject.offsetInSpan[1];
    nativeTextResult.spanPosition = spanPosition;
    nativeTextResult.value = Utils::MallocCString(UtfUtils::Str16ToStr8(spanObject.valueString));

    NativeRichEditorParagraphStyleResult nativeParagraphStyle;
    ParseRichEditorParagraphStyleResult(spanObject.textStyle, nativeParagraphStyle);

    NativeRichEditorSymbolSpanStyleResult nativeSymbolStyle;
    ParseSymbolSpanStyleResult(spanObject.symbolSpanStyle, nativeSymbolStyle);

    nativeTextResult.symbolSpanStyle = nativeSymbolStyle;
    nativeTextResult.paragraphStyle = nativeParagraphStyle;
    nativeTextResult.previewText = Utils::MallocCString(UtfUtils::Str16ToStr8(spanObject.previewText));
}

void NativeRichEditorController::ParseRichEditorImageSpanResult(
    const ResultObject& spanObject, NativeRichEditorImageSpanResult& nativeImageResult)
{
    nativeImageResult.width = spanObject.imageStyle.size[0];
    nativeImageResult.height = spanObject.imageStyle.size[1];
    nativeImageResult.verticalAlign = spanObject.imageStyle.verticalAlign;
    nativeImageResult.objectFit = spanObject.imageStyle.objectFit;
}

void NativeRichEditorController::ParseRichEditorImageSpanResult(
    const ResultObject& spanObject, NativeRichEditorImageSpanResult12& nativeImageResult)
{
    NativeRichEditorSpanPosition spanPosition;
    spanPosition.spanIndex = spanObject.spanPosition.spanIndex;
    spanPosition.spanStart = spanObject.spanPosition.spanRange[0];
    spanPosition.spanEnd = spanObject.spanPosition.spanRange[1];

    nativeImageResult.spanPosition = spanPosition;
    nativeImageResult.offsetInSpanStart = spanObject.offsetInSpan[0];
    nativeImageResult.offsetInSpanEnd = spanObject.offsetInSpan[1];
    nativeImageResult.valueResourceStr = Utils::MallocCString(std::to_string(spanObject.valueResource->GetId()));

    auto valuePixelMap = spanObject.valuePixelMap;
    if (valuePixelMap) {
#ifdef PIXEL_MAP_SUPPORTED
        auto ffiPixelMap = FFIData::Create<OHOS::Media::PixelMapImpl>(valuePixelMap->GetPixelMapSharedPtr());
        nativeImageResult.valuePixelMap = ffiPixelMap->GetID();
#endif
    }
    NativeRichEditorImageSpanStyleResult imageStyle;
    ParseImageStyleResult(spanObject.imageStyle, imageStyle);
    nativeImageResult.imageStyle = imageStyle;
}

void NativeRichEditorController::ParseRichEditorParagraphStyleResult(
    const ParagraphInfo& info, NativeRichEditorParagraphStyleResult& nativeParagraphStyle)
{
    nativeParagraphStyle.margin0 = Utils::MallocCString(info.leadingMarginSize[0]);
    nativeParagraphStyle.margin1 = Utils::MallocCString(info.leadingMarginSize[1]);
    nativeParagraphStyle.textAlign = info.textAlign;
    nativeParagraphStyle.wordBreak = info.wordBreak;
    nativeParagraphStyle.lineBreakStrategy = info.lineBreakStrategy;
}

void NativeRichEditorController::ParseRichEditorAbstractTextSpanResult(
    const NG::RichEditorAbstractSpanResult& spanObject, NativeRichEditorTextSpanResult& nativeTextResult)
{
    NativeRichEditorSpanPosition spanPosition;
    spanPosition.spanIndex = spanObject.GetSpanIndex();
    spanPosition.spanStart = spanObject.GetSpanRangeStart();
    spanPosition.spanEnd = spanObject.GetSpanRangeEnd();
    NativeRichEditorTextStyleResult nativeTextStyle;
    nativeTextStyle.fontColor = MallocCString(spanObject.GetFontColor());
    nativeTextStyle.fontSize = spanObject.GetFontSize();
    nativeTextStyle.fontStyle = static_cast<int32_t>(spanObject.GetFontStyle());
    nativeTextStyle.fontWeight = spanObject.GetFontWeight();
    nativeTextStyle.fontFamily = MallocCString(spanObject.GetFontFamily());
    NativeTextDecorationResult decoration;
    decoration.type = static_cast<int32_t>(spanObject.GetTextDecoration());
    decoration.color = MallocCString(spanObject.GetColor());
    nativeTextStyle.decoration = decoration;

    nativeTextResult.textStyle = nativeTextStyle;
    nativeTextResult.offsetInSpanStart = spanObject.OffsetInSpan();
    nativeTextResult.offsetInSpanEnd = spanObject.OffsetInSpan() + spanObject.GetEraseLength();
    nativeTextResult.spanPosition = spanPosition;
    nativeTextResult.value = MallocCString(UtfUtils::Str16ToStr8(spanObject.GetValue()));
}

void NativeRichEditorController::ParseRichEditorAbstractImageSpanResult(
    const NG::RichEditorAbstractSpanResult& spanObject, NativeRichEditorImageSpanResult& nativeImageResult)
{
    nativeImageResult.width = spanObject.GetSizeWidth();
    nativeImageResult.height = spanObject.GetSizeHeight();
    nativeImageResult.verticalAlign = static_cast<int32_t>(spanObject.GetVerticalAlign());
    nativeImageResult.objectFit = static_cast<int32_t>(spanObject.GetObjectFit());
}

void NativeRichEditorController::ParseRichEditorAbstractTextSpanResult(
    const NG::RichEditorAbstractSpanResult& spanObject, NativeRichEditorTextSpanResult12& nativeTextResult)
{
    NativeRichEditorSpanPosition spanPosition;
    spanPosition.spanIndex = spanObject.GetSpanIndex();
    spanPosition.spanStart = spanObject.GetSpanRangeStart();
    spanPosition.spanEnd = spanObject.GetSpanRangeEnd();

    NativeRichEditorTextStyleResult12 nativeTextStyle;
    ParseRichEditorAbstractTextStyleResult(spanObject, nativeTextStyle);

    NativeRichEditorParagraphStyleResult nativeParagraphStyle;
    ParseRichEditorParagraphStyleResult(spanObject.GetTextStyle(), nativeParagraphStyle);

    nativeTextResult.textStyle = nativeTextStyle;
    nativeTextResult.offsetInSpanStart = spanObject.OffsetInSpan();
    nativeTextResult.offsetInSpanEnd = spanObject.OffsetInSpan() + spanObject.GetEraseLength();
    nativeTextResult.spanPosition = spanPosition;
    nativeTextResult.paragraphStyle = nativeParagraphStyle;
    nativeTextResult.previewText = Utils::MallocCString(UtfUtils::Str16ToStr8(spanObject.GetPreviewText()).c_str());
    nativeTextResult.value = Utils::MallocCString(UtfUtils::Str16ToStr8(spanObject.GetValue()).c_str());
}

void NativeRichEditorController::ParseRichEditorAbstractImageSpanResult(
    const NG::RichEditorAbstractSpanResult& spanObject, NativeRichEditorImageSpanResult12& nativeImageResult)
{
    NativeRichEditorSpanPosition spanPosition;
    spanPosition.spanIndex = spanObject.GetSpanIndex();
    spanPosition.spanStart = spanObject.GetSpanRangeStart();
    spanPosition.spanEnd = spanObject.GetSpanRangeEnd();

    nativeImageResult.spanPosition = spanPosition;
    nativeImageResult.offsetInSpanStart = spanObject.OffsetInSpan();
    nativeImageResult.offsetInSpanEnd = spanObject.OffsetInSpan() + spanObject.GetEraseLength();
    nativeImageResult.valueResourceStr = Utils::MallocCString(spanObject.GetValueResourceStr());

    auto valuePixelMap = spanObject.GetValuePixelMap();
    if (valuePixelMap) {
#ifdef PIXEL_MAP_SUPPORTED
        auto ffiPixelMap = FFIData::Create<OHOS::Media::PixelMapImpl>(valuePixelMap->GetPixelMapSharedPtr());
        nativeImageResult.valuePixelMap = ffiPixelMap->GetID();
#endif
    }
    NativeRichEditorImageSpanStyleResult imageStyle;
    ParseRichEditorAbstractImageStyleResult(spanObject, imageStyle);
    nativeImageResult.imageStyle = imageStyle;
}

void NativeRichEditorController::ParseRichEditorAbstractSymbolSpanResult(
    const NG::RichEditorAbstractSpanResult& spanObject, NativeRichEditorTextSpanResult12& nativeSymbolResult)
{
    NativeRichEditorSpanPosition spanPosition;
    spanPosition.spanIndex = spanObject.GetSpanIndex();
    spanPosition.spanStart = spanObject.GetSpanRangeStart();
    spanPosition.spanEnd = spanObject.GetSpanRangeEnd();

    nativeSymbolResult.offsetInSpanStart = spanObject.OffsetInSpan();
    nativeSymbolResult.offsetInSpanEnd = spanObject.OffsetInSpan() + spanObject.GetEraseLength();
    nativeSymbolResult.value = Utils::MallocCString(spanObject.GetValueString());

    NativeRichEditorSymbolSpanStyleResult nativeSymbolStyle;
    ParseSymbolSpanStyleResult(spanObject.GetSymbolSpanStyle(), nativeSymbolStyle);

    NativeRichEditorParagraphStyleResult nativeParagraphStyle;
    ParseRichEditorParagraphStyleResult(spanObject.GetTextStyle(), nativeParagraphStyle);

    nativeSymbolResult.symbolSpanStyle = nativeSymbolStyle;
    nativeSymbolResult.paragraphStyle = nativeParagraphStyle;
    nativeSymbolResult.previewText = Utils::MallocCString(UtfUtils::Str16ToStr8(spanObject.GetPreviewText()));
}

void NativeRichEditorController::ParseRichEditorAbstractTextStyleResult(
    const NG::RichEditorAbstractSpanResult& spanObject, NativeRichEditorTextStyleResult& nativeTextStyle)
{
    nativeTextStyle.fontColor = spanObject.GetFontColor().c_str();
    nativeTextStyle.fontSize = spanObject.GetFontSize();
    nativeTextStyle.fontStyle = static_cast<int32_t>(spanObject.GetFontStyle());
    nativeTextStyle.fontWeight = spanObject.GetFontWeight();
    nativeTextStyle.fontFamily = spanObject.GetFontFamily().c_str();
    NativeTextDecorationResult decoration;
    decoration.type = static_cast<int32_t>(spanObject.GetTextDecoration());
    decoration.color = spanObject.GetColor().c_str();
    nativeTextStyle.decoration = decoration;
}

void NativeRichEditorController::ParseRichEditorAbstractTextStyleResult(
    const NG::RichEditorAbstractSpanResult& spanObject, NativeRichEditorTextStyleResult12& nativeTextStyle)
{
    nativeTextStyle.fontColor = Utils::MallocCString(spanObject.GetFontColor().c_str());
    nativeTextStyle.fontSize = spanObject.GetFontSize();
    nativeTextStyle.fontStyle = static_cast<int32_t>(spanObject.GetFontStyle());
    nativeTextStyle.fontWeight = spanObject.GetFontWeight();
    nativeTextStyle.fontFamily = Utils::MallocCString(spanObject.GetFontFamily().c_str());
    NativeTextDecorationResult decoration;
    decoration.type = static_cast<int32_t>(spanObject.GetTextDecoration());
    decoration.color = spanObject.GetColor().c_str();
    nativeTextStyle.decoration = decoration;

    auto textShadows = spanObject.GetTextStyle().textShadows;
    auto nativbeTextShadow = new NativeShadowOptionsResult[textShadows.size()];
    int32_t index = 0;
    for (const auto& it : textShadows) {
        NativeShadowOptionsResult current;
        current.radius = it.GetBlurRadius();
        current.color = Utils::MallocCString(it.GetColor().ToString());
        current.offsetX = it.GetOffset().GetX();
        current.offsetY = it.GetOffset().GetY();
        nativbeTextShadow[index] = current;
        index++;
    }
    nativeTextStyle.textShadow = nativbeTextShadow;
    nativeTextStyle.textShadowSize = static_cast<int64_t>(textShadows.size());
    nativeTextStyle.free = NativeShaowOptionsFree;
    nativeTextStyle.lineHeight = spanObject.GetTextStyle().lineHeight;
    nativeTextStyle.letterSpacing = spanObject.GetTextStyle().letterSpacing;
    nativeTextStyle.fontFeature = Utils::MallocCString(
        UnParseFontFeatureSetting(spanObject.GetFontFeatures()));
}

void NativeRichEditorController::ParseRichEditorParagraphStyleResult(
    const TextStyleResult& textStyleResult, NativeRichEditorParagraphStyleResult& nativeParagraphStyle)
{
    nativeParagraphStyle.margin0 = Utils::MallocCString(textStyleResult.leadingMarginSize[0]);
    nativeParagraphStyle.margin1 = Utils::MallocCString(textStyleResult.leadingMarginSize[1]);
    nativeParagraphStyle.textAlign = textStyleResult.textAlign;
    nativeParagraphStyle.wordBreak = textStyleResult.wordBreak;
    nativeParagraphStyle.lineBreakStrategy = textStyleResult.lineBreakStrategy;
}

void NativeRichEditorController::ParseSymbolSpanStyleResult(
    const SymbolSpanStyle& symbolSpanStyle, NativeRichEditorSymbolSpanStyleResult& nativeSymbolResult)
{
    nativeSymbolResult.fontColor = Utils::MallocCString(symbolSpanStyle.symbolColor);
    nativeSymbolResult.fontSize = symbolSpanStyle.fontSize;
    nativeSymbolResult.fontWeight = symbolSpanStyle.fontWeight;
    nativeSymbolResult.renderingStrategy = symbolSpanStyle.renderingStrategy;
    nativeSymbolResult.effectStrategy = symbolSpanStyle.effectStrategy;
}

void NativeRichEditorController::ParseRichEditorAbstractImageStyleResult(
    const NG::RichEditorAbstractSpanResult& spanObject, NativeRichEditorImageSpanStyleResult& nativeImageStyle)
{
    nativeImageStyle.size0 = static_cast<double>(spanObject.GetSizeWidth());
    nativeImageStyle.size1 = static_cast<double>(spanObject.GetSizeHeight());
    nativeImageStyle.verticalAlign = static_cast<int32_t>(spanObject.GetVerticalAlign());
    nativeImageStyle.objectFit = static_cast<int32_t>(spanObject.GetObjectFit());
    NativeRichEditorLayoutStyleResult layoutStyle;
    layoutStyle.borderRadius = Utils::MallocCString(spanObject.GetBorderRadius());
    layoutStyle.margin = Utils::MallocCString(spanObject.GetMargin());
    nativeImageStyle.layoutStyle = layoutStyle;
}

NativeRichEditorController::NativeRichEditorController() : FFIData()
{
    LOGI("Native TextAreaController constructed: %{public}" PRId64, GetID());
}

int32_t NativeRichEditorController::GetCaretOffset()
{
    auto controller = controller_.Upgrade();
    int32_t caretOffset = -1;
    if (controller) {
        caretOffset = controller->GetCaretOffset();
    }
    return caretOffset;
}

bool NativeRichEditorController::SetCaretOffset(int32_t value)
{
    auto controller = controller_.Upgrade();
    int32_t caretPosition = value;
    bool success = false;

    if (controller) {
        success = controller->SetCaretOffset(caretPosition);
    }
    return success;
}

int32_t NativeRichEditorController::AddTextSpan(std::string value, NativeRichEditorTextSpanOptions params)
{
    TextSpanOptions options;
    options.value = UtfUtils::Str8ToStr16(value);
    options.offset = params.offset;

    auto pipelineContext = PipelineBase::GetCurrentContext();
    if (!pipelineContext) {
        return -1;
    }
    auto theme = pipelineContext->GetTheme<TextTheme>();
    TextStyle style = theme ? theme->GetTextStyle() : TextStyle();

    ParseTextStyle(params.style, style);
    options.style = style;

    int32_t spanIndex = 0;
    auto controller = controller_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    if (richEditorController) {
        spanIndex = richEditorController->AddTextSpan(options);
    }
    return spanIndex;
}

int32_t NativeRichEditorController::AddTextSpan(std::string value, NativeRichEditorTextSpanOptions12 params)
{
    TextSpanOptions options;
    options.value = UtfUtils::Str8ToStr16(value);
    options.offset = params.offset;

    auto pipelineContext = PipelineBase::GetCurrentContext();
    if (!pipelineContext) {
        return -1;
    }
    auto theme = pipelineContext->GetTheme<TextTheme>();
    TextStyle style = theme ? theme->GetTextStyle() : TextStyle();

    ParseTextStyle12(params.style, style, updateSpanStyle_);
    options.style = style;
    options.useThemeFontColor = updateSpanStyle_.useThemeFontColor;
    options.useThemeDecorationColor = updateSpanStyle_.useThemeDecorationColor;

    struct UpdateParagraphStyle paraStyle;
    ParseParagraphStyle(params.paragraphStyle, paraStyle);
    options.paraStyle = paraStyle;

    UserGestureOptions gestureOption;
    ParseUserGesture(params.gesture, gestureOption);
    options.userGestureOption = std::move(gestureOption);

    int32_t spanIndex = 0;
    auto controller = controller_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    if (richEditorController) {
        spanIndex = richEditorController->AddTextSpan(options);
    }
    return spanIndex;
}

void NativeRichEditorController::ParseTextStyle(const NativeRichEditorTextStyle& nativeStyle, TextStyle& style)
{
    if (!Utils::CheckParamsValid(nativeStyle.fontStyle, FONTSTYLE_TYPES.size())) {
        LOGE("AddTextSpan error, invalid value for fontStyle");
    }

    if (!Utils::CheckParamsValid(nativeStyle.decoration.type, TEXTDECORATION_TYPES.size())) {
        LOGE("AddTextSpan error, invalid value for fontStyle");
    }

    auto fontColor = Color(nativeStyle.fontColor);
    style.SetTextColor(fontColor);
    updateSpanStyle_.updateTextColor = fontColor;
    auto size = CalcDimension(nativeStyle.fontSize, static_cast<DimensionUnit>(nativeStyle.fontSizeUnit));
    style.SetFontSize(size);
    updateSpanStyle_.updateFontSize = size;
    style.SetFontStyle(FONTSTYLE_TYPES[nativeStyle.fontStyle]);
    updateSpanStyle_.updateItalicFontStyle = FONTSTYLE_TYPES[nativeStyle.fontStyle];
    auto fontWeight = ConvertStrToFontWeight(nativeStyle.fontWeight);
    style.SetFontWeight(fontWeight);
    updateSpanStyle_.updateFontWeight = fontWeight;
    auto fontFamily = ConvertStrToFontFamilies(nativeStyle.fontFamily);
    style.SetFontFamilies(fontFamily);
    updateSpanStyle_.updateFontFamily = fontFamily;
    style.SetTextDecoration(TEXTDECORATION_TYPES[nativeStyle.decoration.type]);
    updateSpanStyle_.updateTextDecoration = TEXTDECORATION_TYPES[nativeStyle.decoration.type];
    auto decorationColor = Color(nativeStyle.decoration.color);
    style.SetTextDecorationColor(decorationColor);
    updateSpanStyle_.updateTextDecorationColor = decorationColor;
}

void NativeRichEditorController::ParseTextStyle12(const NativeRichEditorTextStyle12& nativeStyle,
    TextStyle& style, struct UpdateSpanStyle& updateSpanStyle)
{
    auto fontColor = Color(nativeStyle.fontColor);
    style.SetTextColor(fontColor);
    updateSpanStyle.updateTextColor = fontColor;
    auto size = CalcDimension(nativeStyle.fontSize, static_cast<DimensionUnit>(nativeStyle.fontSizeUnit));
    style.SetFontSize(size);
    updateSpanStyle.updateFontSize = size;
    style.SetFontStyle(FONTSTYLE_TYPES[nativeStyle.fontStyle]);
    updateSpanStyle.updateItalicFontStyle = FONTSTYLE_TYPES[nativeStyle.fontStyle];
    auto fontWeight = ConvertStrToFontWeight(nativeStyle.fontWeight);
    style.SetFontWeight(fontWeight);
    updateSpanStyle.updateFontWeight = fontWeight;
    auto fontFamily = ConvertStrToFontFamilies(nativeStyle.fontFamily);
    style.SetFontFamilies(fontFamily);
    updateSpanStyle.updateFontFamily = fontFamily;
    style.SetTextDecoration(TEXTDECORATION_TYPES[nativeStyle.decoration.type]);
    updateSpanStyle.updateTextDecoration = TEXTDECORATION_TYPES[nativeStyle.decoration.type];
    auto decorationColor = Color(nativeStyle.decoration.color);
    style.SetTextDecorationColor(decorationColor);
    updateSpanStyle.updateTextDecorationColor = decorationColor;
    ParseTextStyleOptionValue(nativeStyle, style, updateSpanStyle);
}

void NativeRichEditorController::ParseTextStyleOptionValue(const NativeRichEditorTextStyle12& nativeStyle,
    TextStyle& style, struct UpdateSpanStyle& updateSpanStyle)
{
    if (nativeStyle.hasTextShadow) {
        std::vector<Shadow> shadows;
        ParseTextShadow(nativeStyle.textShadow, shadows);
        updateSpanStyle.updateTextShadows = shadows;
        style.SetTextShadows(shadows);
    }
    auto theme = GetTheme<TextTheme>();
    auto height = theme->GetTextStyle().GetLineHeight();
    auto letters = theme->GetTextStyle().GetLetterSpacing();
    updateSpanStyle.updateLineHeight = height;
    updateSpanStyle.updateLetterSpacing = letters;
    style.SetLineHeight(height);
    style.SetLetterSpacing(letters);
    if (nativeStyle.lineHeight.hasValue) {
        auto nativeLineHeight = nativeStyle.lineHeight.value;
        auto lineHeight = Dimension(nativeLineHeight.value, static_cast<DimensionUnit>(nativeLineHeight.unitType));
        if (!lineHeight.IsNegative() && lineHeight.Unit() != DimensionUnit::PERCENT) {
            updateSpanStyle.updateLineHeight = lineHeight;
            style.SetLineHeight(lineHeight);
        }
    }
    if (nativeStyle.letterSpacing.hasValue) {
        auto nativeSpacing = nativeStyle.letterSpacing.value;
        auto letterSpacing = Dimension(nativeSpacing.value, static_cast<DimensionUnit>(nativeSpacing.unitType));
        if (!letterSpacing.IsNegative() && letterSpacing.Unit() != DimensionUnit::PERCENT) {
            updateSpanStyle.updateLetterSpacing = letterSpacing;
            style.SetLetterSpacing(letterSpacing);
        }
    }
    if (nativeStyle.fontFeature.hasValue) {
        auto nativeFontFeature = nativeStyle.fontFeature.value;
        NG::FONT_FEATURES_LIST fontFeatures = ParseFontFeatureSettings(nativeFontFeature);
        updateSpanStyle.updateFontFeature = fontFeatures;
        style.SetFontFeatures(fontFeatures);
    } else {
        auto fontFeatures = theme->GetTextStyle().GetFontFeatures();
        updateSpanStyle.updateFontFeature = fontFeatures;
        style.SetFontFeatures(fontFeatures);
    }
}

void NativeRichEditorController::ParseParagraphStyle(const NativeRichEditorParagraphStyle& nativeStyle,
    struct UpdateParagraphStyle& style)
{
    style.textAlign = TEXT_ALIGNS[nativeStyle.textAlign];

    auto type = MARGIN_TYPES[nativeStyle.marginType];
    switch (type) {
        case MarginType::NONE:
            break;
        case MarginType::MARGIN_LENGTH:
            {
                style.leadingMargin = std::make_optional<NG::LeadingMargin>();
                Dimension resWidth(nativeStyle.margin, static_cast<DimensionUnit>(nativeStyle.marginUnit));
                auto widthCalc = CalcDimension(resWidth.ConvertToPx());
                auto heightCalc = CalcDimension(0.0);
                style.leadingMargin->size = NG::LeadingMarginSize(widthCalc, heightCalc);
                break;
            }
        case MarginType::MARGIN_PLACEHOLDER:
            {
                auto placeholder = nativeStyle.placeholder;
                style.leadingMargin = std::make_optional<NG::LeadingMargin>();
#if defined(PIXEL_MAP_SUPPORTED)
                auto nativePixelMap = FFIData::GetData<Media::PixelMapImpl>(placeholder.pixelMap);
                if (nativePixelMap == nullptr) {
                    return;
                }
                auto pixelMap = nativePixelMap->GetRealPixelMap();
                style.leadingMargin->pixmap = PixelMap::CreatePixelMap(&pixelMap);
#endif
                Dimension width(placeholder.width, static_cast<DimensionUnit>(placeholder.widthUnit));
                Dimension height(placeholder.height, static_cast<DimensionUnit>(placeholder.heightUnit));
                auto widthCalc = CalcDimension(width.ConvertToPx());
                auto heightCalc = CalcDimension(height.ConvertToPx());
                style.leadingMargin->size = NG::LeadingMarginSize(widthCalc, heightCalc);
                break;
            }
        default:
            break;
    }
}

void NativeRichEditorController::ParseUserGesture(const NativeRichEditorGesture& nativeGesture,
    UserGestureOptions& gestureOption)
{
    if (reinterpret_cast<int64_t>(nativeGesture.onClick) > 0) {
        auto onClick = [ffiOnClick = CJLambda::Create(nativeGesture.onClick)](const GestureEvent& event) -> void {
            CJClickInfo cjClickInfo {};
            CJEventTarget cjEventTarget {};
            CJArea cjArea {};
            CJPosition cjPosition {};
            CJPosition cjGlobalPosition {};
            AssambleCJClickInfo(event, cjClickInfo, cjEventTarget, cjArea, cjPosition, cjGlobalPosition);
            ffiOnClick(cjClickInfo);
        };
        gestureOption.onLongPress = std::move(onClick);
    } else {
        gestureOption.onClick = nullptr;
    }

    if (reinterpret_cast<int64_t>(nativeGesture.onLongPress) > 0) {
        auto onLongPress = FormatGestureEvenFunction(nativeGesture.onLongPress);
        gestureOption.onLongPress = std::move(onLongPress);
    } else {
        gestureOption.onLongPress = nullptr;
    }
}

void NativeRichEditorController::ParseTextShadow(VectorNativeTextShadows nativeShadows, std::vector<Shadow>& shadows)
{
    auto nativeTextShadowVec = *reinterpret_cast<std::vector<NativeTextShadowV2>*>(nativeShadows);
    for (size_t i = 0; i < nativeTextShadowVec.size(); i++) {
        Dimension dOffsetX(nativeTextShadowVec[i].offsetX, DimensionUnit::VP);
        Dimension dOffsetY(nativeTextShadowVec[i].offsetY, DimensionUnit::VP);
        Shadow shadow;
        shadow.SetBlurRadius(nativeTextShadowVec[i].radius);
        shadow.SetOffsetX(dOffsetX.Value());
        shadow.SetOffsetY(dOffsetY.Value());
        shadow.SetColor(Color(nativeTextShadowVec[i].color));
        shadow.SetIsFilled(nativeTextShadowVec[i].isFilled);
        shadow.SetShadowType(nativeTextShadowVec[i].type == 0 ? ShadowType::COLOR : ShadowType::BLUR);
        shadows.push_back(shadow);
    }
}

int32_t NativeRichEditorController::AddImageSpan(std::string value, NativeRichEditorImageSpanOptions params)
{
    int32_t spanIndex = 0;
    ImageSpanOptions options;
    auto context = PipelineBase::GetCurrentContext();
    bool isCard = context->IsFormRender();
    std::string image = value;
    std::string bundleName;
    std::string moduleName;
    if (isCard) {
        SrcType srcType = ImageSourceInfo::ResolveURIType(image);
        bool notSupport =
            (srcType == SrcType::NETWORK || srcType == SrcType::FILE || srcType == SrcType::DATA_ABILITY);
        if (notSupport) {
            image.clear();
        }
    }
    options.image = image;
    options.bundleName = bundleName;
    options.moduleName = moduleName;

    std::string assetSrc = options.image.value();
    SrcType srcType = ImageSourceInfo::ResolveURIType(assetSrc);
    if (assetSrc[0] == '/') {
        assetSrc = assetSrc.substr(1); // get the asset src without '/'.
    } else if (assetSrc[0] == '.' && assetSrc.size() > SUB_FLAG && assetSrc[1] == '/') {
        assetSrc = assetSrc.substr(2); // get the asset src without './'.
    }
    if (srcType == SrcType::ASSET) {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, -1);
        auto assetManager = pipelineContext->GetAssetManager();
        CHECK_NULL_RETURN(assetManager, -1);
        auto assetData = assetManager->GetAsset(assetSrc);
        CHECK_NULL_RETURN(assetData, -1);
    }

    options.offset = params.offset;
    ImageSpanAttribute imageStyle;
    ParseImageSpanStyle(params.imageStyle, imageStyle);
    options.imageAttribute = imageStyle;
    auto controller = controller_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    if (richEditorController) {
        spanIndex = richEditorController->AddImageSpan(options);
    }
    return spanIndex;
}

int32_t NativeRichEditorController::AddImageSpan(std::string value, NativeRichEditorImageSpanOptions12 params)
{
    int32_t spanIndex = 0;
    ImageSpanOptions options;
    auto context = PipelineBase::GetCurrentContext();
    bool isCard = context->IsFormRender();
    std::string image = value;
    std::string bundleName;
    std::string moduleName;
    if (isCard) {
        SrcType srcType = ImageSourceInfo::ResolveURIType(image);
        bool notSupport =
            (srcType == SrcType::NETWORK || srcType == SrcType::FILE || srcType == SrcType::DATA_ABILITY);
        if (notSupport) {
            image.clear();
        }
    }
    options.image = image;
    options.bundleName = bundleName;
    options.moduleName = moduleName;

    std::string assetSrc = options.image.value();
    SrcType srcType = ImageSourceInfo::ResolveURIType(assetSrc);
    if (assetSrc[0] == '/') {
        assetSrc = assetSrc.substr(1); // get the asset src without '/'.
    } else if (assetSrc[0] == '.' && assetSrc.size() > SUB_FLAG && assetSrc[1] == '/') {
        assetSrc = assetSrc.substr(2); // get the asset src without './'.
    }
    if (srcType == SrcType::ASSET) {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, -1);
        auto assetManager = pipelineContext->GetAssetManager();
        CHECK_NULL_RETURN(assetManager, -1);
        auto assetData = assetManager->GetAsset(assetSrc);
        CHECK_NULL_RETURN(assetData, -1);
    }

    options.offset = params.offset;
    ImageSpanAttribute imageStyle;
    ParseImageSpanStyle(params.imageStyle, imageStyle);
    options.imageAttribute = imageStyle;

    UserGestureOptions gestureOption;
    ParseUserGesture(params.gesture, gestureOption);
    options.userGestureOption = std::move(gestureOption);

    auto controller = controller_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    if (richEditorController) {
        spanIndex = richEditorController->AddImageSpan(options);
    }
    return spanIndex;
}

void NativeRichEditorController::ParseImageSpanStyle(
    const NativeRichEditorImageSpanStyle& nativeStyle, ImageSpanAttribute& imageStyle)
{
    if (nativeStyle.width.hasValue && nativeStyle.height.hasValue) {
        ImageSpanSize imageSize;

        auto imageSpanWidth = CalcDimension(
            nativeStyle.width.value,
            static_cast<DimensionUnit>(nativeStyle.width.unit)
        );
        imageSize.width = imageSpanWidth;
        updateSpanStyle_.updateImageWidth = imageSpanWidth;

        auto imageSpanHeight = CalcDimension(
            nativeStyle.height.value,
            static_cast<DimensionUnit>(nativeStyle.height.unit)
        );
        imageSize.height = imageSpanHeight;
        updateSpanStyle_.updateImageHeight = imageSpanHeight;

        imageStyle.size = imageSize;
    }

    auto align = VERTICAL_ALIGNS[nativeStyle.verticalAlign];
    imageStyle.verticalAlign = align;
    updateSpanStyle_.updateImageVerticalAlign = align;

    auto fit = IMAGEFIT_TYPES[nativeStyle.objectFit];
    imageStyle.objectFit = fit;
    updateSpanStyle_.updateImageFit = fit;

    imageStyle.marginProp = ParseMargin(nativeStyle.layoutStyle.margin);
    updateSpanStyle_.marginProp = imageStyle.marginProp;

    imageStyle.borderRadius = ParseBorderRadius(nativeStyle.layoutStyle.borderRadius);
    updateSpanStyle_.borderRadius = imageStyle.borderRadius;
}

std::optional<NG::MarginProperty> NativeRichEditorController::ParseMargin(const NativeMargin& nativeMargin)
{
    std::optional<NG::MarginProperty> marginProp = std::nullopt;

    std::optional<CalcDimension> left = CalcDimension(
        nativeMargin.left, static_cast<DimensionUnit>(nativeMargin.leftUnit));
    std::optional<CalcDimension> right = CalcDimension(
        nativeMargin.right, static_cast<DimensionUnit>(nativeMargin.rightUnit));
    std::optional<CalcDimension> top = CalcDimension(
        nativeMargin.top, static_cast<DimensionUnit>(nativeMargin.topUnit));
    std::optional<CalcDimension> bottom = CalcDimension(
        nativeMargin.bottom, static_cast<DimensionUnit>(nativeMargin.bottomUnit));

    marginProp = NG::ConvertToCalcPaddingProperty(top, bottom, left, right);

    return marginProp;
}

std::optional<NG::BorderRadiusProperty> NativeRichEditorController::ParseBorderRadius(
    const NativeBorderRadiuses& nativeBorderRadius)
{
    NG::BorderRadiusProperty prop;

    prop.radiusTopLeft = CalcDimension(
        nativeBorderRadius.topLeftRadiuses, static_cast<DimensionUnit>(nativeBorderRadius.topLeftUnit));
    prop.radiusTopRight = CalcDimension(
        nativeBorderRadius.topRightRadiuses, static_cast<DimensionUnit>(nativeBorderRadius.topRightUnit));
    prop.radiusBottomLeft = CalcDimension(
        nativeBorderRadius.bottomLeftRadiuses, static_cast<DimensionUnit>(nativeBorderRadius.bottomLeftUnit));
    prop.radiusBottomRight = CalcDimension(
        nativeBorderRadius.bottomRightRadiuses, static_cast<DimensionUnit>(nativeBorderRadius.bottomRightUnit));
    prop.multiValued = true;

    return prop;
}

void NativeRichEditorController::DeleteSpans(int32_t start, int32_t end)
{
    RangeOptions options;

    options.start = start;
    options.end = end;

    auto controller = controller_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    if (richEditorController) {
        richEditorController->DeleteSpans(options);
    }
}

void NativeRichEditorController::DeleteAllSpans()
{
    RangeOptions options;

    auto controller = controller_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    if (richEditorController) {
        richEditorController->DeleteSpans(options);
    }
}

void NativeRichEditorController::CloseSelectionMenu()
{
    auto controller = controller_.Upgrade();
    if (controller) {
        controller->CloseSelectionMenu();
    }
}

void NativeRichEditorController::UpdateSpanStyleText(
    int32_t start, int32_t end, NativeRichEditorTextStyle style)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);

    if (start < 0) {
        start = 0;
    }
    if (end < 0) {
        end = INT_MAX;
    }
    if (start > end) {
        start = 0;
        end = INT_MAX;
    }
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    TextStyle textStyle = theme ? theme->GetTextStyle() : TextStyle();
    ImageSpanAttribute imageStyle;

    ParseTextStyle(style, textStyle);

    auto controller = controller_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    CHECK_NULL_VOID(richEditorController);
    richEditorController->SetUpdateSpanStyle(updateSpanStyle_);
    richEditorController->UpdateSpanStyle(start, end, textStyle, imageStyle);
}

void NativeRichEditorController::UpdateSpanStyleText(
    int32_t start, int32_t end, NativeRichEditorTextStyle12 style)
{
    ContainerScope scope(instanceId_ < 0 ? Container::CurrentId() : instanceId_);

    if (start < 0) {
        start = 0;
    }
    if (end < 0) {
        end = INT_MAX;
    }
    if (start > end) {
        start = 0;
        end = INT_MAX;
    }
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    TextStyle textStyle = theme ? theme->GetTextStyle() : TextStyle();
    ImageSpanAttribute imageStyle;

    ParseTextStyle12(style, textStyle, updateSpanStyle_);

    auto controller = controller_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    CHECK_NULL_VOID(richEditorController);
    richEditorController->SetUpdateSpanStyle(updateSpanStyle_);
    richEditorController->UpdateSpanStyle(start, end, textStyle, imageStyle);
}

void NativeRichEditorController::UpdateSpanStyleImage(
    int32_t start, int32_t end, NativeRichEditorImageSpanStyle style)
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    if (!pipelineContext) {
        return;
    }
    auto theme = pipelineContext->GetTheme<TextTheme>();
    TextStyle textStyle = theme ? theme->GetTextStyle() : TextStyle();
    ImageSpanAttribute imageStyle;

    ParseImageSpanStyle(style, imageStyle);

    auto controller = controller_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    CHECK_NULL_VOID(richEditorController);
    richEditorController->SetUpdateSpanStyle(updateSpanStyle_);
    richEditorController->UpdateSpanStyle(start, end, textStyle, imageStyle);
}

static void NativeRichEditorSpanResultListFree(int64_t size, NativeRichEditorSpanResult* src)
{
    if (!src) {
        return;
    }
    for (int64_t i = 0; i < size; i++) {
        if (src[i].textResult.value) {
            free((void*) src[i].textResult.value);
        }
        if (src[i].textResult.textStyle.fontColor) {
            free((void*) src[i].textResult.textStyle.fontColor);
        }
        if (src[i].textResult.textStyle.fontFamily) {
            free((void*) src[i].textResult.textStyle.fontFamily);
        }
        if (src[i].textResult.textStyle.decoration.color) {
            free((void*) src[i].textResult.textStyle.decoration.color);
        }
    }
    delete[] src;
}

static void NativeRichEditorSpanResultListFree12(int64_t size, NativeRichEditorSpanResult12* src)
{
    if (!src) {
        return;
    }
    delete[] src;
}

static void NativeParagraphsResultListFree(int64_t size, NativeRichEditorParagraphsResult* src)
{
    if (!src) {
        return;
    }
    delete[] src;
}

NativeRichEditorSpanResultList NativeRichEditorController::GetSpans(int32_t start, int32_t end)
{
    NativeRichEditorSpanResultList result;
    auto controller = controller_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    if (richEditorController) {
        LOGI("RichEditor GetSpans, start: %{public}d", start);
        LOGI("RichEditor GetSpans, end: %{public}d", end);

        SelectionInfo selectionInfo = richEditorController->GetSpansInfo(start, end);
        const std::list<ResultObject>& spanObjectList = selectionInfo.GetSelection().resultObjects;
        if (spanObjectList.size() == 0) {
            return result;
        }
        auto spans = new NativeRichEditorSpanResult[spanObjectList.size()];
        size_t idx = 0;
        for (const ResultObject& spanObject : spanObjectList) {
            NativeRichEditorSpanResult current;
            if (spanObject.type == SelectSpanType::TYPESPAN) {
                current.isText = true;
                NativeRichEditorTextSpanResult textResult;
                ParseRichEditorTextSpanResult(spanObject, textResult);
                current.textResult = textResult;
            } else {
                current.isText = false;
                NativeRichEditorImageSpanResult imageResult;
                ParseRichEditorImageSpanResult(spanObject, imageResult);
                current.imageResult = imageResult;
            }
            spans[idx] = current;
            idx ++;
        }
        result.array = spans;
        result.size = static_cast<int64_t>(spanObjectList.size());
        result.free = NativeRichEditorSpanResultListFree;
        LOGI("FfiOHOSAceFrameworkRichEditorOnSelect parse success");
    }
    return result;
}

NativeRichEditorSpanResultList12 NativeRichEditorController::GetSpans12(int32_t start, int32_t end)
{
    NativeRichEditorSpanResultList12 result;
    auto controller = controller_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    if (richEditorController) {
        LOGI("RichEditor GetSpans, start: %{public}d", start);
        LOGI("RichEditor GetSpans, end: %{public}d", end);

        SelectionInfo selectionInfo = richEditorController->GetSpansInfo(start, end);
        const std::list<ResultObject>& spanObjectList = selectionInfo.GetSelection().resultObjects;
        if (spanObjectList.size() == 0) {
            return result;
        }
        auto spans = new NativeRichEditorSpanResult12[spanObjectList.size()];
        size_t idx = 0;
        for (const ResultObject& spanObject : spanObjectList) {
            NativeRichEditorSpanResult12 current;
            if (spanObject.type == SelectSpanType::TYPESPAN || spanObject.type == SelectSpanType::TYPESYMBOLSPAN) {
                current.isText = true;
                NativeRichEditorTextSpanResult12 textResult;
                ParseRichEditorTextSpanResult(spanObject, textResult);
                current.textResult = textResult;
            } else {
                current.isText = false;
                NativeRichEditorImageSpanResult12 imageResult;
                ParseRichEditorImageSpanResult(spanObject, imageResult);
                current.imageResult = imageResult;
            }
            spans[idx] = current;
            idx ++;
        }
        result.array = spans;
        result.size = static_cast<int64_t>(spanObjectList.size());
        result.free = NativeRichEditorSpanResultListFree12;
        LOGI("FfiOHOSAceFrameworkRichEditorOnSelect parse success");
    }
    return result;
}

void NativeRichEditorController::UpdateParagraphStyle(
    int32_t start, int32_t end, NativeRichEditorParagraphStyle params)
{
    struct UpdateParagraphStyle style;
    ParseParagraphStyle(params, style);

    auto controller = controller_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    if (richEditorController) {
        richEditorController->UpdateParagraphStyle(start, end, style);
    }
}

bool NativeRichEditorController::IsEditing()
{
    auto controller = controller_.Upgrade();
    if (controller) {
        return controller->IsEditing();
    }
    return false;
}

void NativeRichEditorController::StopEditing()
{
    auto controller = controller_.Upgrade();
    if (controller) {
        controller->StopEditing();
    }
}

NativeRichEditorRange NativeRichEditorController::StyledStringGetSelection()
{
    auto controller = controller_.Upgrade();
    if (controller) {
        auto styledStringController = AceType::DynamicCast<RichEditorStyledStringControllerBase>(controller);
        SelectionRangeInfo value = styledStringController->GetSelection();
        return {value.start_, value.end_};
    }
    return {};
}

int32_t NativeRichEditorController::AddBuilderSpan(std::function<void()> builderFunc, int32_t offset)
{
    auto controller = controller_.Upgrade();
    if (controller) {
        auto controller = controller_.Upgrade();
        auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
        if (!richEditorController) {
            return 0;
        }
        ViewStackModel::GetInstance()->NewScope();
        builderFunc();
        auto customNode = AceType::DynamicCast<NG::UINode>(ViewStackModel::GetInstance()->Finish());
        if (!customNode) {
            return 0;
        }
        SpanOptionBase options;
        if (offset > 0) {
            options.offset = offset;
        }
        return richEditorController->AddPlaceholderSpan(customNode, options);
    }
    return 0;
}

int32_t NativeRichEditorController::AddSymbolSpan(uint32_t value, NativeRichEditorSymbolSpanOptions params)
{
    auto controller = controller_.Upgrade();
    if (controller) {
        auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
        SymbolSpanOptions options;
        options.symbolId = value;
        options.offset = params.offset;

        auto pipelineContext = PipelineBase::GetCurrentContext();
        auto theme = pipelineContext->GetThemeManager()->GetTheme<NG::RichEditorTheme>();
        TextStyle style = theme ? theme->GetTextStyle() : TextStyle();
        ParseSymbolStyle(params.style, style, updateSpanStyle_);
        options.style = style;
        return richEditorController->AddSymbolSpan(options);
    }
    return 0;
}

void NativeRichEditorController::ParseSymbolStyle(
    const NativeRichEditorSymbolSpanStyle& nativeStyle, TextStyle& style, struct UpdateSpanStyle& updateSpanStyle)
{
    std::vector<Color> symbolColor;
    if (nativeStyle.hasFontColor) {
        auto actualVec = *reinterpret_cast<std::vector<uint32_t>*>(nativeStyle.fontColor);
        for (auto color: actualVec) {
            symbolColor.emplace_back(Color(color));
        }
        updateSpanStyle.updateSymbolColor = symbolColor;
        style.SetSymbolColorList(symbolColor);
    }

    CalcDimension size;
    if (nativeStyle.fontSize.hasValue) {
        auto nativefontSize = nativeStyle.fontSize.value;
        auto fontSizeDime = Dimension(nativefontSize.value, static_cast<DimensionUnit>(nativefontSize.unitType));
        if (!fontSizeDime.IsNegative() && fontSizeDime.Unit() != DimensionUnit::PERCENT) {
            updateSpanStyle.updateSymbolFontSize = fontSizeDime;
            style.SetFontSize(fontSizeDime);
        }
    }
    updateSpanStyle.updateSymbolFontWeight = ConvertStrToFontWeight(nativeStyle.fontWeight);
    style.SetFontWeight(ConvertStrToFontWeight(nativeStyle.fontWeight));

    updateSpanStyle.updateSymbolRenderingStrategy = nativeStyle.renderingStrategy;
    style.SetRenderStrategy(nativeStyle.renderingStrategy);

    updateSpanStyle.updateSymbolEffectStrategy = 0;
    style.SetEffectStrategy(0);
}

NativePreviewText NativeRichEditorController::GetPreviewText()
{
    auto controller = controller_.Upgrade();
    if (controller) {
        auto info = controller->GetPreviewTextInfo();
        return {info.offset.value_or(0), Utils::MallocCString(UtfUtils::Str16DebugToStr8(info.value.value_or(u"")))};
    }
    return {};
}

void NativeRichEditorController::SetSelection(int32_t start, int32_t end, int32_t menuPolicy)
{
    auto controller = controller_.Upgrade();
    SelectionOptions options;
    options.menuPolicy = static_cast<MenuPolicy>(menuPolicy);
    if (controller) {
        controller->SetSelection(start, end, options);
    }
}

NativeParagraphsResultList NativeRichEditorController::GetParagraphs(int32_t start, int32_t end)
{
    NativeParagraphsResultList result;
    auto controller = controller_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    if (richEditorController) {
        const std::vector<ParagraphInfo>& infos = richEditorController->GetParagraphsInfo(start, end);
        if (infos.size() == 0) {
            return result;
        }
        auto spans = new NativeRichEditorParagraphsResult[infos.size()];
        for (size_t i = 0; i < infos.size(); ++i) {
            auto paragraphInfo = infos[i];
            NativeRichEditorParagraphsResult current;
            current.rangeStart = paragraphInfo.range.first;
            current.rangeEnd = paragraphInfo.range.second;
            NativeRichEditorParagraphStyleResult nativeParagraphStyle;
            ParseRichEditorParagraphStyleResult(paragraphInfo, nativeParagraphStyle);
            current.style = nativeParagraphStyle;
            spans[i] = current;
        }
        result.array = spans;
        result.size = static_cast<int64_t>(infos.size());
        result.free = NativeParagraphsResultListFree;
        return result;
    }
    return result;
}

NativeRichEditorSelectionWithFree NativeRichEditorController::GetSelection()
{
    NativeRichEditorSelectionWithFree result;
    auto controller = controller_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    if (richEditorController) {
        SelectionInfo selectInfo = richEditorController->GetSelectionSpansInfo();

        const std::list<ResultObject>& spanObjectList = selectInfo.GetSelection().resultObjects;
        auto spans = new NativeRichEditorSpanResult12[spanObjectList.size()];
        size_t idx = 0;
        for (const ResultObject& spanObject : spanObjectList) {
            NativeRichEditorSpanResult12 current;
            if (spanObject.type == SelectSpanType::TYPESPAN || spanObject.type == SelectSpanType::TYPESYMBOLSPAN) {
                current.isText = true;
                NativeRichEditorTextSpanResult12 textResult;
                ParseRichEditorTextSpanResult(spanObject, textResult);
                current.textResult = textResult;
            } else {
                current.isText = false;
                NativeRichEditorImageSpanResult12 imageResult;
                ParseRichEditorImageSpanResult(spanObject, imageResult);
                current.imageResult = imageResult;
            }
            spans[idx] = current;
            idx ++;
        }

        result.selectionStart = selectInfo.GetSelection().selection[0];
        result.selectionEnd = selectInfo.GetSelection().selection[1];
        result.spans = spans;
        result.spanSize = static_cast<int64_t>(spanObjectList.size());
        result.free = NativeRichEditorSpanResultListFree12;
    }
    return result;
}

void NativeRichEditorController::SetTypingStyle(NativeRichEditorTextStyle12 value)
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    if (!pipelineContext) {
        LOGE("pipelineContext is null");
        return;
    }
    auto theme = pipelineContext->GetThemeManager()->GetTheme<NG::RichEditorTheme>();
    TextStyle textStyle = theme ? theme->GetTextStyle() : TextStyle();

    auto controller = controller_.Upgrade();
    if (controller) {
        ParseTextStyle12(value, textStyle, typingStyle_);
        controller->SetTypingStyle(typingStyle_, textStyle);
    }
}

NativeRichEditorTextStyleResult12 NativeRichEditorController::GetTypingStyle()
{
    auto controller = controller_.Upgrade();
    NativeRichEditorTextStyleResult12 result;
    if (controller) {
        auto typingStyle = controller->GetTypingStyle();
        NativeRichEditorTextStyleResult12 result;
        ParseTypingStyleResult(typingStyle.value_or(UpdateSpanStyle()), result);
    }
    return result;
}
}

extern "C" {
int64_t FfiOHOSAceFrameworkRichEditorControllerCtor()
{
    auto controller = FFIData::Create<NativeRichEditorController>();
    if (controller == nullptr) {
        return FFI_ERROR_CODE;
    }
    return controller->GetID();
}

int64_t FfiOHOSAceFrameworkRichEditorControllerGetCaretOffset(int64_t controllerId)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        return nativeController->GetCaretOffset();
    } else {
        LOGE("RichEditor: invalid richEditorController id");
        return -1;
    }
}

bool FfiOHOSAceFrameworkRichEditorControllerSetCaretOffset(int64_t controllerId, int64_t value)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        return nativeController->SetCaretOffset(value);
    } else {
        LOGE("RichEditor: invalid richEditorController id");
        return false;
    }
}

int32_t FfiOHOSAceFrameworkRichEditorControllerAddTextSpan(
    int64_t controllerId, const char* value, NativeRichEditorTextSpanOptions params)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        return nativeController->AddTextSpan(value, params);
    } else {
        LOGE("RichEditor: invalid richEditorController id");
        return 0;
    }
}

int32_t FfiOHOSAceFrameworkRichEditorControllerAddTextSpan12(
    int64_t controllerId, const char* value, NativeRichEditorTextSpanOptions12 params)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        return nativeController->AddTextSpan(value, params);
    } else {
        LOGE("RichEditor: invalid richEditorController id");
        return 0;
    }
}

int32_t FfiOHOSAceFrameworkRichEditorControllerAddImageSpan(
    int64_t controllerId, const char* value, NativeRichEditorImageSpanOptions params)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        return nativeController->AddImageSpan(value, params);
    } else {
        LOGE("RichEditor: invalid richEditorController id");
        return 0;
    }
}

int32_t FfiOHOSAceFrameworkRichEditorControllerAddImageSpan12(
    int64_t controllerId, const char* value, NativeRichEditorImageSpanOptions12 params)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        return nativeController->AddImageSpan(value, params);
    } else {
        LOGE("RichEditor: invalid richEditorController id");
        return 0;
    }
}

void FfiOHOSAceFrameworkRichEditorControllerDeleteSpans(int64_t controllerId, int32_t start,  int32_t end)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        return nativeController->DeleteSpans(start, end);
    } else {
        LOGE("RichEditor: invalid richEditorController id");
    }
}

void FfiOHOSAceFrameworkRichEditorControllerDeleteAllSpans(int64_t controllerId)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        return nativeController->DeleteAllSpans();
    } else {
        LOGE("RichEditor: invalid richEditorController id");
    }
}

void FfiOHOSAceFrameworkRichEditorControllerCloseSelectionMenu(int64_t controllerId)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        nativeController->CloseSelectionMenu();
    } else {
        LOGE("RichEditor: invalid richEditorController id");
    }
}

void FfiOHOSAceFrameworkRichEditorControllerUpdateSpanStyleText(
    int64_t controllerId, int32_t start, int32_t end, NativeRichEditorTextStyle params)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        nativeController->UpdateSpanStyleText(start, end, params);
    } else {
        LOGE("RichEditor: invalid richEditorController id");
    }
}

void FfiOHOSAceFrameworkRichEditorControllerUpdateSpanStyleText12(
    int64_t controllerId, int32_t start, int32_t end, NativeRichEditorTextStyle12 params)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        nativeController->UpdateSpanStyleText(start, end, params);
    } else {
        LOGE("RichEditor: invalid richEditorController id");
    }
}

void FfiOHOSAceFrameworkRichEditorControllerUpdateSpanStyleImage(
    int64_t controllerId, int32_t start, int32_t end, NativeRichEditorImageSpanStyle params)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        nativeController->UpdateSpanStyleImage(start, end, params);
    } else {
        LOGE("RichEditor: invalid richEditorController id");
    }
}

NativeRichEditorSpanResultList FfiOHOSAceFrameworkRichEditorControllerGetSpans(
    int64_t controllerId, int32_t start, int32_t end)
{
    NativeRichEditorSpanResultList result;
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        result = nativeController->GetSpans(start, end);
    } else {
        LOGE("RichEditor: invalid richEditorController id");
    }
    return result;
}

NativeRichEditorSpanResultList12 FfiOHOSAceFrameworkRichEditorControllerGetSpans12(
    int64_t controllerId, int32_t start, int32_t end)
{
    NativeRichEditorSpanResultList12 result;
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        result = nativeController->GetSpans12(start, end);
    } else {
        LOGE("RichEditor: invalid richEditorController id");
    }
    return result;
}

void FfiOHOSAceFrameworkRichEditorControllerUpdateParagraphStyle(
    int64_t controllerId, int32_t start, int32_t end, NativeRichEditorParagraphStyle params)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        nativeController->UpdateParagraphStyle(start, end, params);
    } else {
        LOGE("RichEditor: invalid richEditorController id");
    }
}

bool FfiOHOSAceFrameworkRichEditorControllerIsEditing(int64_t controllerId)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        return nativeController->IsEditing();
    } else {
        LOGE("RichEditor: invalid richEditorController id");
        return false;
    }
}

void FfiOHOSAceFrameworkRichEditorControllerStopEditing(int64_t controllerId)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        nativeController->StopEditing();
    } else {
        LOGE("RichEditor: invalid richEditorController id");
    }
}

NativeRichEditorRange FfiOHOSAceFrameworkRichEditorStyledStringControllerGetSelection(int64_t controllerId)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        return nativeController->StyledStringGetSelection();
    } else {
        LOGE("RichEditor: invalid richEditorController id");
        return {};
    }
}

int32_t FfiOHOSAceFrameworkRichEditorControllerAddBuilderSpan(int64_t controllerId, void(*value)(), int32_t offset)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        auto builderFunc = CJLambda::Create(value);
        return nativeController->AddBuilderSpan(builderFunc, offset);
    } else {
        LOGE("RichEditor: invalid richEditorController id");
        return {};
    }
}

int32_t FfiOHOSAceFrameworkRichEditorControllerAddSymbolSpan(
    int64_t controllerId, uint32_t value, NativeRichEditorSymbolSpanOptions params)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        return nativeController->AddSymbolSpan(value, params);
    } else {
        LOGE("RichEditor: invalid richEditorController id");
        return {};
    }
}

NativePreviewText FfiOHOSAceFrameworkRichEditorControllerGetPreviewText(int64_t controllerId)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        return nativeController->GetPreviewText();
    } else {
        LOGE("RichEditor: invalid richEditorController id");
        return {};
    }
}

void FfiOHOSAceFrameworkRichEditorControllerSetSelection(int64_t controllerId,
    int32_t start, int32_t end, int32_t menuPolicy)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        return nativeController->SetSelection(start, end, menuPolicy);
    } else {
        LOGE("RichEditor: invalid richEditorController id");
    }
}

NativeParagraphsResultList FfiOHOSAceFrameworkRichEditorControllerGetParagraphs(
    int64_t controllerId, int32_t start, int32_t end)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        return nativeController->GetParagraphs(start, end);
    } else {
        LOGE("RichEditor: invalid richEditorController id");
        return {};
    }
}

NativeRichEditorSelectionWithFree FfiOHOSAceFrameworkRichEditorControllerGetSelection(int64_t controllerId)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        return nativeController->GetSelection();
    } else {
        LOGE("RichEditor: invalid richEditorController id");
        return {};
    }
}

void FfiOHOSAceFrameworkRichEditorControllerSetTypingStyle(int64_t controllerId, NativeRichEditorTextStyle12 value)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        nativeController->SetTypingStyle(value);
    } else {
        LOGE("RichEditor: invalid richEditorController id");
    }
}

NativeRichEditorTextStyleResult12 FfiOHOSAceFrameworkRichEditorControllerGetTypingStyle(int64_t controllerId)
{
    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        return nativeController->GetTypingStyle();
    } else {
        LOGE("RichEditor: invalid richEditorController id");
        return {};
    }
}
}