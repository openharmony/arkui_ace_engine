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
}

namespace OHOS::Ace::Framework {
void NativeRichEditorController::ParseTextStyleResult(
    const TextStyleResult& textStyle, NativeRichEditorTextStyleResult& nativeTextStyle)
{
    nativeTextStyle.fontColor = textStyle.fontColor.c_str();
    nativeTextStyle.fontSize = textStyle.fontSize;
    nativeTextStyle.fontStyle = textStyle.fontStyle;
    nativeTextStyle.fontWeight = textStyle.fontWeight;
    nativeTextStyle.fontFamily = textStyle.fontFamily.c_str();
    NativeTextDecorationResult decoration;
    decoration.type = textStyle.decorationType;
    decoration.color = textStyle.decorationColor.c_str();
    nativeTextStyle.decoration = decoration;
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

void NativeRichEditorController::ParseRichEditorImageSpanResult(
    const ResultObject& spanObject, NativeRichEditorImageSpanResult& nativeImageResult)
{
    nativeImageResult.width = spanObject.imageStyle.size[0];
    nativeImageResult.height = spanObject.imageStyle.size[1];
    nativeImageResult.verticalAlign = spanObject.imageStyle.verticalAlign;
    nativeImageResult.objectFit = spanObject.imageStyle.objectFit;
}

void NativeRichEditorController::ParseRichEditorAbstractTextSpanResult(
    const NG::RichEditorAbstractSpanResult& spanObject, NativeRichEditorTextSpanResult& nativeTextResult)
{
    NativeRichEditorSpanPosition spanPosition;
    spanPosition.spanIndex = spanObject.GetSpanIndex();
    spanPosition.spanStart = spanObject.GetSpanRangeStart();
    spanPosition.spanEnd = spanObject.GetSpanRangeEnd();
    NativeRichEditorTextStyleResult nativeTextStyle;
    nativeTextStyle.fontColor = spanObject.GetFontColor().c_str();
    nativeTextStyle.fontSize = spanObject.GetFontSize();
    nativeTextStyle.fontStyle = static_cast<int32_t>(spanObject.GetFontStyle());
    nativeTextStyle.fontWeight = spanObject.GetFontWeight();
    nativeTextStyle.fontFamily = spanObject.GetFontFamily().c_str();
    NativeTextDecorationResult decoration;
    decoration.type = static_cast<int32_t>(spanObject.GetTextDecoration());
    decoration.color = spanObject.GetColor().c_str();
    nativeTextStyle.decoration = decoration;

    nativeTextResult.textStyle = nativeTextStyle;
    nativeTextResult.offsetInSpanStart = spanObject.OffsetInSpan();
    nativeTextResult.offsetInSpanEnd = spanObject.OffsetInSpan() + spanObject.GetEraseLength();
    nativeTextResult.spanPosition = spanPosition;
    nativeTextResult.value = UtfUtils::Str16ToStr8(spanObject.GetValue()).c_str();
}

void NativeRichEditorController::ParseRichEditorAbstractImageSpanResult(
    const NG::RichEditorAbstractSpanResult& spanObject, NativeRichEditorImageSpanResult& nativeImageResult)
{
    nativeImageResult.width = spanObject.GetSizeWidth();
    nativeImageResult.height = spanObject.GetSizeHeight();
    nativeImageResult.verticalAlign = static_cast<int32_t>(spanObject.GetVerticalAlign());
    nativeImageResult.objectFit = static_cast<int32_t>(spanObject.GetObjectFit());
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
            delete src[i].textResult.value;
        }
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

void NativeRichEditorController::UpdateParagraphStyle(
    int32_t start, int32_t end, NativeRichEditorParagraphStyle params)
{
    struct UpdateParagraphStyle style;
    style.textAlign = TEXT_ALIGNS[params.textAlign];

    auto type = MARGIN_TYPES[params.marginType];
    switch (type) {
        case MarginType::NONE:
            break;
        case MarginType::MARGIN_LENGTH:
            {
                style.leadingMargin = std::make_optional<NG::LeadingMargin>();
                Dimension resWidth(params.margin, static_cast<DimensionUnit>(params.marginUnit));
                auto widthCalc = CalcDimension(resWidth.ConvertToPx());
                auto heightCalc = CalcDimension(0.0);
                style.leadingMargin->size = NG::LeadingMarginSize(widthCalc, heightCalc);
                break;
            }
        case MarginType::MARGIN_PLACEHOLDER:
            {
                auto placeholder = params.placeholder;
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
    auto controller = controller_.Upgrade();
    auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
    if (richEditorController) {
        richEditorController->UpdateParagraphStyle(start, end, style);
    }
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
}