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
#ifndef OHOS_ACE_FRAMEWORK_CJ_RICHEDITOR_CONTROLLER_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_RICHEDITOR_CONTROLLER_FFI_H

#include <cinttypes>
#include <optional>
#include <string>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_text_clock_ffi.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "cj_lambda.h"
#include "ffi_remote_data.h"

using VectorUInt32Ptr = void*;
using VectorNativeTextShadows = void*;

extern "C" {
struct NativeTextDecoration {
    int32_t type;
    uint32_t color;
};

struct NativeRichEditorSpanPosition {
    int32_t spanIndex;
    int32_t spanStart;
    int32_t spanEnd;
};

struct NativeShadowOptionsResult {
    double radius;
    ExternalString color;
    double offsetX;
    double offsetY;
};

struct NativeRichEditorLayoutStyleResult {
    ExternalString borderRadius;
    ExternalString margin;
};

struct NativeRichEditorGesture {
    void (*onClick)(CJClickInfo clickInfo);
    void (*onLongPress)(CJGestureEvent info);
};

struct NativeRichEditorTextStyle {
    uint32_t fontColor;
    double fontSize;
    int32_t fontSizeUnit;
    int32_t fontStyle;
    const char* fontWeight;
    const char* fontFamily;
    NativeTextDecoration decoration;
};

struct NativeRichEditorTextSpanOptions {
    int32_t offset;
    NativeRichEditorTextStyle style;
};

struct NativeRichEditorTextStyle12 {
    uint32_t fontColor;
    double fontSize;
    int32_t fontSizeUnit;
    int32_t fontStyle;
    const char* fontWeight;
    const char* fontFamily;
    NativeTextDecoration decoration;
    VectorNativeTextShadows textShadow;
    bool hasTextShadow;
    NativeOptionLength lineHeight;
    NativeOptionLength letterSpacing;
    NativeOptionCString fontFeature;
};

struct NativeLayoutStyle {
    NativeMargin margin;
    NativeBorderRadiuses borderRadius;
};

struct LengthOption {
    double value;
    int32_t unit;
    bool hasValue;
};

struct NativeRichEditorImageSpanStyle {
    LengthOption width;
    LengthOption height;
    int32_t verticalAlign;
    int32_t objectFit;
    NativeLayoutStyle layoutStyle;
};

struct NativeRichEditorImageSpanStyleResult {
    double size0;
    double size1;
    int32_t verticalAlign;
    int32_t objectFit;
    NativeRichEditorLayoutStyleResult layoutStyle;
};

struct NativeRichEditorImageSpanResult12 {
    NativeRichEditorSpanPosition spanPosition;
    int64_t valuePixelMap;
    ExternalString valueResourceStr;
    NativeRichEditorImageSpanStyleResult imageStyle;
    int32_t offsetInSpanStart;
    int32_t offsetInSpanEnd;
};

struct NativeRichEditorImageSpanOptions {
    int32_t offset;
    NativeRichEditorImageSpanStyle imageStyle;
};

struct NativeRichEditorImageSpanOptions12 {
    int32_t offset;
    NativeRichEditorImageSpanStyle imageStyle;
    NativeRichEditorGesture gesture;
};

struct NativeTextDecorationResult {
    int32_t type;
    const char* color;
};

struct NativeRichEditorTextStyleResult {
    const char* fontColor;
    double fontSize;
    int32_t fontStyle;
    int32_t fontWeight;
    const char* fontFamily;
    NativeTextDecorationResult decoration;
};

struct NativeRichEditorSymbolSpanStyleResult {
    ExternalString fontColor;
    double fontSize;
    int32_t fontWeight;
    int32_t renderingStrategy;
    int32_t effectStrategy;
};

struct NativeRichEditorTextStyleResult12 {
    ExternalString fontColor;
    double fontSize;
    int32_t fontStyle;
    int32_t fontWeight;
    ExternalString fontFamily;
    NativeTextDecorationResult decoration;
    NativeShadowOptionsResult* textShadow;
    void (*free)(int64_t, NativeShadowOptionsResult*);
    int64_t textShadowSize;
    double lineHeight;
    double letterSpacing;
    ExternalString fontFeature;
};

struct NativeRichEditorParagraphStyleResult {
    int32_t textAlign;
    ExternalString margin0;
    ExternalString margin1;
    int32_t wordBreak;
    int32_t lineBreakStrategy;
};

struct NativeRichEditorTextSpanResult {
    NativeRichEditorSpanPosition spanPosition;
    const char* value;
    NativeRichEditorTextStyleResult textStyle;
    int32_t offsetInSpanStart;
    int32_t offsetInSpanEnd;
};

struct NativeRichEditorTextSpanResult12 {
    NativeRichEditorSpanPosition spanPosition;
    ExternalString value;
    NativeRichEditorTextStyleResult12 textStyle;
    int32_t offsetInSpanStart;
    int32_t offsetInSpanEnd;
    NativeRichEditorSymbolSpanStyleResult symbolSpanStyle;
    NativeRichEditorParagraphStyleResult paragraphStyle;
    ExternalString previewText;
};

struct NativeRichEditorImageSpanResult {
    double width;
    double height;
    int32_t verticalAlign;
    int32_t objectFit;
};

struct NativeRichEditorSpanResult {
    bool isText;
    NativeRichEditorTextSpanResult textResult;
    NativeRichEditorImageSpanResult imageResult;
};

struct NativeRichEditorSpanResult12 {
    bool isText;
    NativeRichEditorTextSpanResult12 textResult;
    NativeRichEditorImageSpanResult12 imageResult;
};

struct NativeRichEditorSpanResultList {
    NativeRichEditorSpanResult* array;
    int64_t size;
    void (*free)(int64_t, NativeRichEditorSpanResult*);
};

struct NativeRichEditorSpanResultList12 {
    NativeRichEditorSpanResult12* array;
    int64_t size;
    void (*free)(int64_t, NativeRichEditorSpanResult12*);
};

struct NativeRichEditorSelection {
    int32_t selectionStart;
    int32_t selectionEnd;
    NativeRichEditorSpanResult* spans;
    int64_t spanSize;
};

struct NativeRichEditorDeleteValue {
    int32_t offset;
    int32_t direction;
    int32_t length;
    NativeRichEditorSpanResult* richEditorDeleteSpans;
    int64_t spanSize;
};

struct NativeRichEditorDeleteValue12 {
    int32_t offset;
    int32_t direction;
    int32_t length;
    NativeRichEditorSpanResult12* richEditorDeleteSpans;
    int64_t spanSize;
};

struct NativeLeadingMarginPlaceholder {
    int64_t pixelMap;
    double width;
    int32_t widthUnit;
    double height;
    int32_t heightUnit;
};

struct NativeRichEditorParagraphStyle {
    int32_t textAlign;
    int32_t marginType;
    double margin;
    int32_t marginUnit;
    NativeLeadingMarginPlaceholder placeholder;
};

struct NativeRichEditorRange {
    int32_t start;
    int32_t end;
};

struct NativeRichEditorSymbolSpanStyle {
    VectorUInt32Ptr fontColor;
    bool hasFontColor;
    NativeOptionLength fontSize;
    const char* fontWeight;
    int32_t renderingStrategy;
    int32_t effectStrategy;
};

struct NativeRichEditorSymbolSpanOptions {
    int32_t offset;
    NativeRichEditorSymbolSpanStyle style;
};

struct NativePreviewText {
    int32_t offset;
    ExternalString value;
};

struct NativeRichEditorParagraphsResult {
    NativeRichEditorParagraphStyleResult style;
    int32_t rangeStart;
    int32_t rangeEnd;
};

struct NativeParagraphsResultList {
    NativeRichEditorParagraphsResult* array;
    int64_t size;
    void (*free)(int64_t, NativeRichEditorParagraphsResult*);
};

struct NativeRichEditorSelectionWithFree {
    int32_t selectionStart;
    int32_t selectionEnd;
    NativeRichEditorSpanResult12* spans;
    int64_t spanSize;
    void (*free)(int64_t, NativeRichEditorSpanResult12*);
};

struct NativeRichEditorTextSpanOptions12 {
    int32_t offset;
    NativeRichEditorTextStyle12 style;
    NativeRichEditorParagraphStyle paragraphStyle;
    NativeRichEditorGesture gesture;
};

CJ_EXPORT int64_t FfiOHOSAceFrameworkRichEditorControllerCtor();
CJ_EXPORT int64_t FfiOHOSAceFrameworkRichEditorControllerGetCaretOffset(int64_t id);
CJ_EXPORT bool FfiOHOSAceFrameworkRichEditorControllerSetCaretOffset(int64_t id, int64_t value);
CJ_EXPORT int32_t FfiOHOSAceFrameworkRichEditorControllerAddTextSpan(int64_t id, const char* value,
    NativeRichEditorTextSpanOptions params);
CJ_EXPORT int32_t FfiOHOSAceFrameworkRichEditorControllerAddTextSpan12(int64_t id, const char* value,
    NativeRichEditorTextSpanOptions12 params);
CJ_EXPORT int32_t FfiOHOSAceFrameworkRichEditorControllerAddImageSpan(int64_t id, const char* value,
    NativeRichEditorImageSpanOptions params);
CJ_EXPORT int32_t FfiOHOSAceFrameworkRichEditorControllerAddImageSpan12(int64_t id, const char* value,
    NativeRichEditorImageSpanOptions12 params);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorControllerDeleteSpans(int64_t id, int32_t start,  int32_t end);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorControllerDeleteAllSpans(int64_t id);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorControllerCloseSelectionMenu(int64_t id);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorControllerUpdateSpanStyleText(int64_t id, int32_t start,
    int32_t end, NativeRichEditorTextStyle params);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorControllerUpdateSpanStyleText12(int64_t id, int32_t start,
    int32_t end, NativeRichEditorTextStyle12 params);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorControllerUpdateSpanStyleImage(int64_t id, int32_t start,
    int32_t end, NativeRichEditorImageSpanStyle params);
CJ_EXPORT NativeRichEditorSpanResultList FfiOHOSAceFrameworkRichEditorControllerGetSpans(int64_t id,
    int32_t start, int32_t end);
CJ_EXPORT NativeRichEditorSpanResultList12 FfiOHOSAceFrameworkRichEditorControllerGetSpans12(int64_t id,
    int32_t start, int32_t end);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorControllerUpdateParagraphStyle(int64_t id, int32_t start,
    int32_t end, NativeRichEditorParagraphStyle params);
CJ_EXPORT bool FfiOHOSAceFrameworkRichEditorControllerIsEditing(int64_t id);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorControllerStopEditing(int64_t id);
CJ_EXPORT NativeRichEditorRange FfiOHOSAceFrameworkRichEditorStyledStringControllerGetSelection(int64_t id);
CJ_EXPORT int32_t FfiOHOSAceFrameworkRichEditorControllerAddBuilderSpan(int64_t id, void(*value)(), int32_t offset);
CJ_EXPORT int32_t FfiOHOSAceFrameworkRichEditorControllerAddSymbolSpan(int64_t id, uint32_t value,
    NativeRichEditorSymbolSpanOptions params);
CJ_EXPORT NativePreviewText FfiOHOSAceFrameworkRichEditorControllerGetPreviewText(int64_t id);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorControllerSetSelection(int64_t id,
    int32_t start, int32_t end, int32_t menuPolicy);
CJ_EXPORT NativeParagraphsResultList FfiOHOSAceFrameworkRichEditorControllerGetParagraphs(int64_t id,
    int32_t start, int32_t end);
CJ_EXPORT NativeRichEditorSelectionWithFree FfiOHOSAceFrameworkRichEditorControllerGetSelection(int64_t id);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorControllerSetTypingStyle(int64_t id, NativeRichEditorTextStyle12 value);
CJ_EXPORT NativeRichEditorTextStyleResult12 FfiOHOSAceFrameworkRichEditorControllerGetTypingStyle(int64_t id);
}

namespace OHOS::Ace::Framework {

enum MarginType {
    NONE = 0,
    MARGIN_LENGTH = 1,
    MARGIN_PLACEHOLDER = 2
};

class ACE_EXPORT NativeRichEditorController : public OHOS::FFI::FFIData {
    DECL_TYPE(NativeRichEditorController, OHOS::FFI::FFIData)
public:
    NativeRichEditorController();

    void SetController(const RefPtr<RichEditorBaseControllerBase>& controller)
    {
        controller_ = controller;
    }

    int32_t GetCaretOffset();

    bool SetCaretOffset(int32_t value);

    int32_t AddTextSpan(std::string value, NativeRichEditorTextSpanOptions params);

    int32_t AddTextSpan(std::string value, NativeRichEditorTextSpanOptions12 params);

    int32_t AddImageSpan(std::string value, NativeRichEditorImageSpanOptions params);

    int32_t AddImageSpan(std::string value, NativeRichEditorImageSpanOptions12 params);

    void DeleteSpans(int32_t start, int32_t end);

    void DeleteAllSpans();

    void CloseSelectionMenu();

    void UpdateSpanStyleText(int32_t start, int32_t end, NativeRichEditorTextStyle style);

    void UpdateSpanStyleText(int32_t start, int32_t end, NativeRichEditorTextStyle12 style);

    void UpdateSpanStyleImage(int32_t start, int32_t end, NativeRichEditorImageSpanStyle style);

    NativeRichEditorSpanResultList GetSpans(int32_t start, int32_t end);

    NativeRichEditorSpanResultList12 GetSpans12(int32_t start, int32_t end);

    void UpdateParagraphStyle(int32_t start, int32_t end, NativeRichEditorParagraphStyle params);

    bool IsEditing();

    void StopEditing();

    NativeRichEditorRange StyledStringGetSelection();

    int32_t AddBuilderSpan(std::function<void()> builderFunc, int32_t offset);

    int32_t AddSymbolSpan(uint32_t value, NativeRichEditorSymbolSpanOptions params);

    NativePreviewText GetPreviewText();

    void SetSelection(int32_t start, int32_t end, int32_t menuPolicy);

    NativeParagraphsResultList GetParagraphs(int32_t start, int32_t end);

    NativeRichEditorSelectionWithFree GetSelection();

    void SetTypingStyle(NativeRichEditorTextStyle12 value);

    NativeRichEditorTextStyleResult12 GetTypingStyle();

    void ParseImageSpanStyle(const NativeRichEditorImageSpanStyle& nativeStyle, ImageSpanAttribute& imageStyle);

    std::optional<NG::MarginProperty> ParseMargin(const NativeMargin& nativeMargin);

    std::optional<NG::BorderRadiusProperty> ParseBorderRadius(const NativeBorderRadiuses& nativeBorderRadius);

    void ParseTextStyle(const NativeRichEditorTextStyle& nativeStyle, TextStyle& style);

    void ParseTextStyle12(const NativeRichEditorTextStyle12& nativeStyle,
        TextStyle& style, struct UpdateSpanStyle& updateSpanStyle);

    void ParseTextStyleOptionValue(const NativeRichEditorTextStyle12& nativeStyle,
    TextStyle& style, struct UpdateSpanStyle& updateSpanStyle);

    void ParseParagraphStyle(const NativeRichEditorParagraphStyle& nativeStyle, struct UpdateParagraphStyle& style);

    void ParseUserGesture(const NativeRichEditorGesture& nativeGesture, UserGestureOptions& gestureOption);

    void ParseTextShadow(VectorNativeTextShadows nativeShadows, std::vector<Shadow>& shadows);

    void ParseSymbolStyle(const NativeRichEditorSymbolSpanStyle& nativeStyle,
        TextStyle& style, struct UpdateSpanStyle& updateSpanStyle);

    static void ParseTextStyleResult(const TextStyleResult& textStyle,
        NativeRichEditorTextStyleResult& nativeTextStyle);

    static void ParseTextStyleResult(const TextStyleResult& textStyle,
        NativeRichEditorTextStyleResult12& nativeTextStyle);

    static void ParseSymbolSpanStyleResult(const SymbolSpanStyle& symbolSpanStyle,
        NativeRichEditorSymbolSpanStyleResult& nativeTextStyle);

    static void ParseImageStyleResult(const ImageStyleResult& textStyle,
        NativeRichEditorImageSpanStyleResult& nativeImageStyle);

    static void ParseTypingStyleResult(const UpdateSpanStyle& typingStyle,
        NativeRichEditorTextStyleResult12& nativeTextStyle);

    static void ParseRichEditorTextSpanResult(const ResultObject& spanObject,
        NativeRichEditorTextSpanResult& nativeTextResult);

    static void ParseRichEditorTextSpanResult(const ResultObject& spanObject,
        NativeRichEditorTextSpanResult12& nativeTextResult);

    static void ParseRichEditorImageSpanResult(const ResultObject& spanObject,
        NativeRichEditorImageSpanResult& nativeImageResult);

    static void ParseRichEditorImageSpanResult(const ResultObject& spanObject,
        NativeRichEditorImageSpanResult12& nativeImageResult);

    static void ParseRichEditorParagraphStyleResult(const ParagraphInfo& info,
        NativeRichEditorParagraphStyleResult& nativeParagraphStyleResult);

    static void ParseRichEditorParagraphStyleResult(const TextStyleResult& textStyleResult,
        NativeRichEditorParagraphStyleResult& nativeParagraphStyleResult);

    static void ParseRichEditorAbstractTextSpanResult(const NG::RichEditorAbstractSpanResult& spanObject,
        NativeRichEditorTextSpanResult& nativeTextResult);

    static void ParseRichEditorAbstractTextSpanResult(const NG::RichEditorAbstractSpanResult& spanObject,
        NativeRichEditorTextSpanResult12& nativeTextResult);

    static void ParseRichEditorAbstractImageSpanResult(const NG::RichEditorAbstractSpanResult& spanObject,
        NativeRichEditorImageSpanResult& nativeImageResult);

    static void ParseRichEditorAbstractImageSpanResult(const NG::RichEditorAbstractSpanResult& spanObject,
        NativeRichEditorImageSpanResult12& nativeImageResult);

    static void ParseRichEditorAbstractSymbolSpanResult(const NG::RichEditorAbstractSpanResult& spanObject,
        NativeRichEditorTextSpanResult12& nativeSymbolResult);

    static void ParseRichEditorAbstractTextStyleResult(const NG::RichEditorAbstractSpanResult& spanObject,
        NativeRichEditorTextStyleResult& nativeTextStyleResult);

    static void ParseRichEditorAbstractTextStyleResult(const NG::RichEditorAbstractSpanResult& spanObject,
        NativeRichEditorTextStyleResult12& nativeTextStyleResult);

    static void ParseRichEditorAbstractImageStyleResult(const NG::RichEditorAbstractSpanResult& spanObject,
        NativeRichEditorImageSpanStyleResult& nativeImageStyleResult);

    void SetInstanceId(int32_t id)
    {
        instanceId_ = id;
    }

private:
    WeakPtr<RichEditorBaseControllerBase> controller_;
    struct UpdateSpanStyle updateSpanStyle_;
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;
    struct UpdateSpanStyle typingStyle_;
};
} // namespace OHOS::Ace::Framework

#endif //OHOS_ACE_FRAMEWORK_CJ_RICHEDITOR_CONTROLLER_FFI_H