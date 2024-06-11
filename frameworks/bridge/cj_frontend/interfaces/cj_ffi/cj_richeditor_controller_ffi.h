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
#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "ffi_remote_data.h"

extern "C" {
struct NativeTextDecoration {
    int32_t type;
    uint32_t color;
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

struct NativeMargin {
    double top;
    int32_t topUnit;
    double right;
    int32_t rightUnit;
    double bottom;
    int32_t bottomUnit;
    double left;
    int32_t leftUnit;
};

struct NativeBorderRadiuses {
    double top;
    int32_t topUnit;
    double right;
    int32_t rightUnit;
    double bottom;
    int32_t bottomUnit;
    double left;
    int32_t leftUnit;
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

struct NativeRichEditorImageSpanOptions {
    int32_t offset;
    NativeRichEditorImageSpanStyle imageStyle;
};

struct NativeRichEditorSpanPosition {
    int32_t spanIndex;
    int32_t spanStart;
    int32_t spanEnd;
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

struct NativeRichEditorTextSpanResult {
    NativeRichEditorSpanPosition spanPosition;
    const char* value;
    NativeRichEditorTextStyleResult textStyle;
    int32_t offsetInSpanStart;
    int32_t offsetInSpanEnd;
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

struct NativeRichEditorSpanResultList {
    NativeRichEditorSpanResult* array;
    int64_t size;
    void (*free)(int64_t, NativeRichEditorSpanResult*);
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

CJ_EXPORT int64_t FfiOHOSAceFrameworkRichEditorControllerCtor();
CJ_EXPORT int64_t FfiOHOSAceFrameworkRichEditorControllerGetCaretOffset(int64_t id);
CJ_EXPORT bool FfiOHOSAceFrameworkRichEditorControllerSetCaretOffset(int64_t id, int64_t value);
CJ_EXPORT int32_t FfiOHOSAceFrameworkRichEditorControllerAddTextSpan(int64_t id, const char* value,
    NativeRichEditorTextSpanOptions params);
CJ_EXPORT int32_t FfiOHOSAceFrameworkRichEditorControllerAddImageSpan(int64_t id, const char* value,
    NativeRichEditorImageSpanOptions params);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorControllerDeleteSpans(int64_t id, int32_t start,  int32_t end);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorControllerDeleteAllSpans(int64_t id);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorControllerCloseSelectionMenu(int64_t id);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorControllerUpdateSpanStyleText(int64_t id, int32_t start,
    int32_t end, NativeRichEditorTextStyle params);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorControllerUpdateSpanStyleImage(int64_t id, int32_t start,
    int32_t end, NativeRichEditorImageSpanStyle params);
CJ_EXPORT NativeRichEditorSpanResultList FfiOHOSAceFrameworkRichEditorControllerGetSpans(int64_t id,
    int32_t start, int32_t end);
CJ_EXPORT void FfiOHOSAceFrameworkRichEditorControllerUpdateParagraphStyle(int64_t id, int32_t start,
    int32_t end, NativeRichEditorParagraphStyle params);
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

    int32_t AddImageSpan(std::string value, NativeRichEditorImageSpanOptions params);

    void DeleteSpans(int32_t start, int32_t end);

    void DeleteAllSpans();

    void CloseSelectionMenu();

    void UpdateSpanStyleText(int32_t start, int32_t end, NativeRichEditorTextStyle style);

    void UpdateSpanStyleImage(int32_t start, int32_t end, NativeRichEditorImageSpanStyle style);

    NativeRichEditorSpanResultList GetSpans(int32_t start, int32_t end);

    void UpdateParagraphStyle(int32_t start, int32_t end, NativeRichEditorParagraphStyle params);

    void ParseImageSpanStyle(const NativeRichEditorImageSpanStyle& nativeStyle, ImageSpanAttribute& imageStyle);

    void ParseTextStyle(const NativeRichEditorTextStyle& nativeStyle, TextStyle& style);

    static void ParseTextStyleResult(const TextStyleResult& textStyle,
        NativeRichEditorTextStyleResult& nativeTextStyle);

    static void ParseRichEditorTextSpanResult(const ResultObject& spanObject,
        NativeRichEditorTextSpanResult& nativeTextResult);

    static void ParseRichEditorImageSpanResult(const ResultObject& spanObject,
        NativeRichEditorImageSpanResult& nativeImageResult);

    static void ParseRichEditorAbstractTextSpanResult(const NG::RichEditorAbstractSpanResult& spanObject,
        NativeRichEditorTextSpanResult& nativeTextResult);

    static void ParseRichEditorAbstractImageSpanResult(const NG::RichEditorAbstractSpanResult& spanObject,
        NativeRichEditorImageSpanResult& nativeImageResult);

    void SetInstanceId(int32_t id)
    {
        instanceId_ = id;
    }

private:
    WeakPtr<RichEditorBaseControllerBase> controller_;
    struct UpdateSpanStyle updateSpanStyle_;
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;
};
} // namespace OHOS::Ace::Framework

#endif //OHOS_ACE_FRAMEWORK_CJ_RICHEDITOR_CONTROLLER_FFI_H