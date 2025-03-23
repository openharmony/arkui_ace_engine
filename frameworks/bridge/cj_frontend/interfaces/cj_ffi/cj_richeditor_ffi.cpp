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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_richeditor_ffi.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"

#include "cj_lambda.h"
#include "securec.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
std::vector<NG::TextResponseType> RESPONSE_TYPES = {
    NG::TextResponseType::RIGHT_CLICK, NG::TextResponseType::LONG_PRESS, NG::TextResponseType::SELECTED_BY_MOUSE
};

std::vector<NG::TextSpanType> EDITOR_TYPES = {
    NG::TextSpanType::TEXT, NG::TextSpanType::IMAGE, NG::TextSpanType::MIXED
};

std::vector<CopyOptions> COPYOPTIONS_TYPES = {
    CopyOptions::None, CopyOptions::InApp, CopyOptions::Local
};

TextInputAction TransfromToTextInputAction(int32_t value)
{
    if (value < static_cast<int32_t>(TextInputAction::BEGIN) || value > static_cast<int32_t>(TextInputAction::END)) {
        return TextInputAction::UNSPECIFIED;
    }
    return static_cast<TextInputAction>(value);
}

void ParseNativeFont(const NativeFont& origin, Font& font)
{
    Dimension sizeDime(origin.size, static_cast<DimensionUnit>(origin.sizeUnit));

    if (sizeDime.IsNegative() || sizeDime.Unit() == DimensionUnit::PERCENT) {
        auto theme = GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        sizeDime = theme->GetTextStyle().GetFontSize();
    }

    font.fontSize = sizeDime;
    font.fontStyle = static_cast<FontStyle>(origin.style);
    font.fontWeight = ConvertStrToFontWeight(origin.weight);
    font.fontFamilies = ConvertStrToFontFamilies(origin.family);
}

void ParseDataDetectorConfig(NativeTextDataDetectorConfig origin, TextDetectConfig& textDetectConfig)
{
    auto actualVec = *reinterpret_cast<std::vector<std::string>*>(origin.types);
    std::string textTypes;
    for (size_t i = 0; i < actualVec.size(); i++) {
        if (i != 0) {
            textTypes.append(",");
        }
        textTypes.append(actualVec[i]);
    }
    if (origin.hasOnDetectResultUpdate) {
        auto onDetectResultUpdate = [cjCallback = CJLambda::Create(origin.onDetectResultUpdate)](
            const std::string& value) -> void {
            cjCallback(value.c_str());
        };
        textDetectConfig.onResult = std::move(onDetectResultUpdate);
    }

    if (origin.hasColor) {
        textDetectConfig.entityColor = Color(origin.color);
    }

    if (origin.hasDecoration) {
        auto decoration = origin.decoration;
        textDetectConfig.entityDecorationType = static_cast<TextDecoration>(decoration.type);
        if (decoration.hasColor) {
            textDetectConfig.entityDecorationColor = Color(decoration.color);
        }
        if (decoration.hasStyle) {
            textDetectConfig.entityDecorationStyle = static_cast<TextDecorationStyle>(decoration.style);
        }
    }
}

}

extern "C" {
void FfiOHOSAceFrameworkRichEditorCreateWithController(int64_t controllerId)
{
    RichEditorModel::GetInstance()->Create();
    RefPtr<RichEditorBaseControllerBase> controller = RichEditorModel::GetInstance()->GetRichEditorController();

    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        nativeController->SetInstanceId(Container::CurrentId());
        nativeController->SetController(controller);
    } else {
        LOGE("RichEditorController is invalid ");
    }
}

void FfiOHOSAceFrameworkRichEditorCreateWithStyledStringController(int64_t controllerId)
{
    RichEditorModel::GetInstance()->Create(true);
    RefPtr<RichEditorBaseControllerBase> controller = RichEditorModel::GetInstance()->GetRichEditorController();

    auto nativeController = FFIData::GetData<NativeRichEditorController>(controllerId);
    if (nativeController != nullptr) {
        nativeController->SetInstanceId(Container::CurrentId());
        nativeController->SetController(controller);
    } else {
        LOGE("RichEditorController is invalid ");
    }
}

void FfiOHOSAceFrameworkRichEditorCustomKeyboard(void(*builder)())
{
    auto builderFunc = CJLambda::Create(builder);
    RichEditorModel::GetInstance()->SetCustomKeyboard(std::move(builderFunc));
}

void FfiOHOSAceFrameworkRichEditorBindSelectionMenu(
    int32_t spantype, void(*content)(), int32_t responseType, void(*onAppear)(), void(*onDisappear)())
{
    if (!Utils::CheckParamsValid(responseType, RESPONSE_TYPES.size())) {
        LOGE("BindSelectionMenu error, invalid value for responseType");
        return;
    }

    if (!Utils::CheckParamsValid(spantype, EDITOR_TYPES.size())) {
        LOGE("BindSelectionMenu error, invalid value for spantype");
        return;
    }

    NG::SelectMenuParam menuParam;
    menuParam.onAppear = [onAppear = CJLambda::Create(onAppear)](
        int32_t start, int32_t end) { onAppear(); };
    menuParam.onDisappear = [onDisappear = CJLambda::Create(onDisappear)]() { onDisappear(); };

    std::function<void()> buildFunc = CJLambda::Create(content);

    RichEditorModel::GetInstance()->BindSelectionMenu(
        EDITOR_TYPES[spantype], RESPONSE_TYPES[responseType], buildFunc, menuParam);
}

void FfiOHOSAceFrameworkRichEditorCopyOptions(int32_t copyOptions)
{
    if (!Utils::CheckParamsValid(copyOptions, COPYOPTIONS_TYPES.size())) {
        LOGE("CopyOptions error, invalid value for copyOptions");
        return;
    }
    RichEditorModel::GetInstance()->SetCopyOption(COPYOPTIONS_TYPES[copyOptions]);
}

void FfiOHOSAceFrameworkRichEditorOnReady(void(*callback)())
{
    RichEditorModel::GetInstance()->SetOnReady(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkRichEditorOnDeleteComplete(void(*callback)())
{
    RichEditorModel::GetInstance()->SetOnDeleteComplete(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkRichEditorAboutToIMEInput(bool(*callback)(NativeRichEditorInsertValue))
{
    auto aboutToIMEInputFunc = [cjCallback = CJLambda::Create(callback)](
        const NG::RichEditorInsertValue& insertValue) -> bool {
        auto utilstring = UtfUtils::Str16ToStr8(insertValue.GetInsertValue()).c_str();
        NativeRichEditorInsertValue result {
            insertValue.GetInsertOffset(), utilstring
        };
        return cjCallback(result);
    };
    RichEditorModel::GetInstance()->SetAboutToIMEInput(std::move(aboutToIMEInputFunc));
}

void FfiOHOSAceFrameworkRichEditorAboutToIMEInput12(bool(*callback)(NativeRichEditorInsertValue12))
{
    auto aboutToIMEInputFunc = [cjCallback = CJLambda::Create(callback)](
        const NG::RichEditorInsertValue& insertValue) -> bool {
        NativeRichEditorInsertValue12 result {
            insertValue.GetInsertOffset(),
            Utils::MallocCString(UtfUtils::Str16ToStr8(insertValue.GetInsertValue())),
            Utils::MallocCString(UtfUtils::Str16ToStr8(insertValue.GetPreviewText()))
        };
        return cjCallback(result);
    };
    RichEditorModel::GetInstance()->SetAboutToIMEInput(std::move(aboutToIMEInputFunc));
}

void FfiOHOSAceFrameworkRichEditorOnIMEInputComplete(void(*callback)(NativeRichEditorTextSpanResult))
{
    auto onIMEInputCompleteFunc = [cjCallback = CJLambda::Create(callback)](
        const NG::RichEditorAbstractSpanResult& textSpanResult) {
        NativeRichEditorSpanPosition spanPosition {
            textSpanResult.GetSpanIndex(),
            textSpanResult.GetSpanRangeStart(),
            textSpanResult.GetSpanRangeEnd()
        };

        NativeTextDecorationResult decoration {
            static_cast<int32_t>(textSpanResult.GetTextDecoration()),
            textSpanResult.GetColor().c_str(),
        };

        NativeRichEditorTextStyleResult textStyle {
            textSpanResult.GetFontColor().c_str(),
            textSpanResult.GetFontSize(),
            static_cast<int32_t>(textSpanResult.GetFontStyle()),
            textSpanResult.GetFontWeight(),
            textSpanResult.GetFontFamily().c_str(),
            decoration
        };
        auto utilstring = UtfUtils::Str16ToStr8(textSpanResult.GetValue()).c_str();
        NativeRichEditorTextSpanResult result {
            spanPosition,
            utilstring,
            textStyle,
            textSpanResult.OffsetInSpan(),
            textSpanResult.OffsetInSpan() + textSpanResult.GetEraseLength()
        };

        cjCallback(result);
    };
    RichEditorModel::GetInstance()->SetOnIMEInputComplete(std::move(onIMEInputCompleteFunc));
}

void FfiOHOSAceFrameworkRichEditorOnIMEInputComplete12(void(*callback)(NativeRichEditorTextSpanResult12))
{
    auto onIMEInputCompleteFunc = [cjCallback = CJLambda::Create(callback)](
        const NG::RichEditorAbstractSpanResult& textSpanResult) {
        NativeRichEditorTextSpanResult12 result;
        NativeRichEditorController::ParseRichEditorAbstractTextSpanResult(textSpanResult, result);
        cjCallback(result);
    };
    RichEditorModel::GetInstance()->SetOnIMEInputComplete(std::move(onIMEInputCompleteFunc));
}

void FfiOHOSAceFrameworkRichEditorOnSelect(void(*callback)(NativeRichEditorSelection))
{
    auto onSelectFunc = [cjCallback = CJLambda::Create(callback)](const BaseEventInfo* info) {
        const auto* eventInfo = TypeInfoHelper::DynamicCast<SelectionInfo>(info);
        auto selectionInfo = eventInfo->GetSelection();

        auto selectionStart = selectionInfo.selection[0];
        auto selectionEnd = selectionInfo.selection[1];

        const std::list<ResultObject>& spanObjectList = selectionInfo.resultObjects;
        auto spans = new NativeRichEditorSpanResult[spanObjectList.size()];
        size_t idx = 0;
        for (const ResultObject& spanObject : spanObjectList) {
            NativeRichEditorSpanResult current;
            if (spanObject.type == SelectSpanType::TYPESPAN) {
                current.isText = true;
                NativeRichEditorTextSpanResult textResult;
                NativeRichEditorController::ParseRichEditorTextSpanResult(spanObject, textResult);
                current.textResult = textResult;
            } else {
                current.isText = false;
                NativeRichEditorImageSpanResult imageResult;
                NativeRichEditorController::ParseRichEditorImageSpanResult(spanObject, imageResult);
                current.imageResult = imageResult;
            }
            spans[idx] = current;
            idx ++;
        }
        NativeRichEditorSelection result;
        result.selectionStart = selectionStart;
        result.selectionEnd = selectionEnd;
        result.spans = spans;
        result.spanSize = static_cast<int64_t>(spanObjectList.size());

        cjCallback(result);
        delete[] spans;
    };
    RichEditorModel::GetInstance()->SetOnSelect(std::move(onSelectFunc));
}

void FfiOHOSAceFrameworkRichEditorAboutToDelete(bool(*callback)(NativeRichEditorDeleteValue))
{
    auto aboutToDeleteFunc = [cjCallback = CJLambda::Create(callback)](
            const NG::RichEditorDeleteValue& deleteValue) -> bool {
        const std::list<NG::RichEditorAbstractSpanResult>& deleteSpans = deleteValue.GetRichEditorDeleteSpans();
        auto spans = new NativeRichEditorSpanResult[deleteSpans.size()];
        size_t idx = 0;
        for (const NG::RichEditorAbstractSpanResult& spanObject : deleteSpans) {
            NativeRichEditorSpanResult current;
            if (spanObject.GetType() == NG::SpanResultType::TEXT) {
                current.isText = true;
                NativeRichEditorTextSpanResult textResult;
                NativeRichEditorController::ParseRichEditorAbstractTextSpanResult(spanObject, textResult);
                current.textResult = textResult;
            } else {
                current.isText = false;
                NativeRichEditorImageSpanResult imageResult;
                NativeRichEditorController::ParseRichEditorAbstractImageSpanResult(spanObject, imageResult);
                current.imageResult = imageResult;
            }
            spans[idx] = current;
            idx ++;
        }
        NativeRichEditorDeleteValue result;
        result.offset = deleteValue.GetOffset();
        result.direction = static_cast<int32_t>(deleteValue.GetRichEditorDeleteDirection());
        result.length = deleteValue.GetLength();
        result.richEditorDeleteSpans = spans;
        result.spanSize = static_cast<int64_t>(deleteSpans.size());

        auto res = cjCallback(result);
        delete[] spans;
        return res;
    };
    RichEditorModel::GetInstance()->SetAboutToDelete(std::move(aboutToDeleteFunc));
}

void FfiOHOSAceFrameworkRichEditorAboutToDelete12(bool(*callback)(NativeRichEditorDeleteValue12))
{
    auto aboutToDeleteFunc = [cjCallback = CJLambda::Create(callback)](
            const NG::RichEditorDeleteValue& deleteValue) -> bool {
        const std::list<NG::RichEditorAbstractSpanResult>& deleteSpans = deleteValue.GetRichEditorDeleteSpans();
        auto spans = new NativeRichEditorSpanResult12[deleteSpans.size()];
        size_t idx = 0;
        for (const NG::RichEditorAbstractSpanResult& spanObject : deleteSpans) {
            NativeRichEditorSpanResult12 current;
            if (spanObject.GetType() == NG::SpanResultType::TEXT ||
                spanObject.GetType() == NG::SpanResultType::SYMBOL) {
                current.isText = true;
                NativeRichEditorTextSpanResult12 textResult;
                NativeRichEditorController::ParseRichEditorAbstractTextSpanResult(spanObject, textResult);
                current.textResult = textResult;
            } else {
                current.isText = false;
                NativeRichEditorImageSpanResult12 imageResult;
                NativeRichEditorController::ParseRichEditorAbstractImageSpanResult(spanObject, imageResult);
                current.imageResult = imageResult;
            }
            spans[idx] = current;
            idx ++;
        }
        NativeRichEditorDeleteValue12 result;
        result.offset = deleteValue.GetOffset();
        result.direction = static_cast<int32_t>(deleteValue.GetRichEditorDeleteDirection());
        result.length = deleteValue.GetLength();
        result.richEditorDeleteSpans = spans;
        result.spanSize = static_cast<int64_t>(deleteSpans.size());

        auto res = cjCallback(result);
        delete[] spans;
        return res;
    };
    RichEditorModel::GetInstance()->SetAboutToDelete(std::move(aboutToDeleteFunc));
}

void FfiOHOSAceFrameworkRichEditorOnPaste(void(*callback)(int64_t))
{
    auto onPast = [cjCallback = CJLambda::Create(callback)](NG::TextCommonEvent& info) {
        auto nativePasteEvent = FFIData::Create<NativePasteEvent>(&info);
        if (nativePasteEvent == nullptr) {
            return;
        }
        cjCallback(nativePasteEvent->GetID());
    };
    RichEditorModel::GetInstance()->SetOnPaste(std::move(onPast));
}

void FfiOHOSAceFrameworkRichEditorPreventDefault(int64_t id)
{
    auto nativePasteEvent = FFIData::GetData<NativePasteEvent>(id);
    nativePasteEvent->PreventDefault();
}

void FfiOHOSAceFrameworkRichEditorOnDidChange(void(*callback)(CJTextRange rangeBefore, CJTextRange rangeAfter))
{
    auto onDidChange = [cjCallback = CJLambda::Create(callback)](const NG::RichEditorChangeValue& changeValue) {
        const auto& rangeBefore = changeValue.GetRangeBefore();
        const auto& rangeAfter = changeValue.GetRangeAfter();
        CJTextRange cjRangeBefore = { rangeBefore.start, rangeBefore.end };
        CJTextRange cjRangeAfter = { rangeAfter.start, rangeAfter.end };

        cjCallback(cjRangeBefore, cjRangeAfter);
    };
    RichEditorModel::GetInstance()->SetOnDidChange(std::move(onDidChange));
}

void FfiOHOSAceFrameworkRichEditorEnableDataDetector(bool enable)
{
    RichEditorModel::GetInstance()->SetTextDetectEnable(enable);
}

void FfiOHOSAceFrameworkRichEditorDataDetectorConfig(NativeTextDataDetectorConfig config)
{
    TextDetectConfig textDetectConfig;
    ParseDataDetectorConfig(config, textDetectConfig);
    RichEditorModel::GetInstance()->SetTextDetectConfig(textDetectConfig);
}

void FfiOHOSAceFrameworkRichEditorEditMenuOptions(
    CjOnCreateMenu cjOnCreateMenu, CjOnMenuItemClick cjOnMenuItemClick)
{
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClick;
    ViewAbstract::ParseEditMenuOptions(cjOnCreateMenu, cjOnMenuItemClick, onCreateMenuCallback, onMenuItemClick);
    RichEditorModel::GetInstance()->SetSelectionMenuOptions(
        std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

void FfiOHOSAceFrameworkRichEditorEnablePreviewText(bool enable)
{
    RichEditorModel::GetInstance()->SetSupportPreviewText(enable);
}

void FfiOHOSAceFrameworkRichEditorPlaceholder(const char* value, NativePlaceholderStyle style)
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    if (!pipelineContext) {
        LOGE("pipelineContext is null");
        return;
    }

    PlaceholderOptions options;
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    options.value = convert.from_bytes(value);

    Font font;
    if (style.hasFont) {
        ParseNativeFont(style.font, font);
    }

    if (style.hasFontColor) {
        options.fontColor = Color(style.fontColor);
    }

    auto textTheme = pipelineContext->GetTheme<TextTheme>();
    TextStyle textStyle = textTheme ? textTheme->GetTextStyle() : TextStyle();
    options.fontSize = font.fontSize.value_or(textStyle.GetFontSize());
    options.fontFamilies = !font.fontFamilies.empty() ? font.fontFamilies : textStyle.GetFontFamilies();
    options.fontWeight = font.fontWeight.value_or(textStyle.GetFontWeight());
    options.fontStyle = font.fontStyle.value_or(textStyle.GetFontStyle());
    if (!options.fontColor.has_value()) {
        Color fontColor;
        auto richEditorTheme = pipelineContext->GetTheme<NG::RichEditorTheme>();
        options.fontColor = richEditorTheme ? richEditorTheme->GetPlaceholderColor() : fontColor;
    }

    RichEditorModel::GetInstance()->SetPlaceholder(options);
}

void FfiOHOSAceFrameworkRichEditorCaretColor(uint32_t color)
{
    RichEditorModel::GetInstance()->SetCaretColor(Color(color));
}

void FfiOHOSAceFrameworkRichEditorSelectedBackgroundColor(uint32_t color)
{
    RichEditorModel::GetInstance()->SetSelectedBackgroundColor(Color(color));
}

void FfiOHOSAceFrameworkRichEditorEnterKeyType(uint32_t value)
{
    TextInputAction textInputAction = TransfromToTextInputAction(value);
    RichEditorModel::GetInstance()->SetEnterKeyType(textInputAction);
}

void FfiOHOSAceFrameworkRichEditorEnableKeyboardOnFocus(bool enable)
{
    RichEditorModel::GetInstance()->SetRequestKeyboardOnFocus(enable);
}

void FfiOHOSAceFrameworkRichEditorCustomKeyboardWithOptions(void(*builder)(), NativeKeyboardOptions options)
{
    auto builderFunc = CJLambda::Create(builder);
    RichEditorModel::GetInstance()->SetCustomKeyboard(std::move(builderFunc), options.supportAvoidance);
}

void FfiOHOSAceFrameworkRichEditorOnDidIMEInput(void(*callback)(NativeTextRange))
{
    auto onDidIMEInputFunc = [cjCallback = CJLambda::Create(callback)](const TextRange& textRange) {
        NativeTextRange range { textRange.start, textRange.end };
        return cjCallback(range);
    };
    RichEditorModel::GetInstance()->SetOnDidIMEInput(std::move(onDidIMEInputFunc));
}

void FfiOHOSAceFrameworkRichEditorOnSelectionChange(void(*callback)(NativeRichEditorRange))
{
    auto onSelectionChange = [cjCallback = CJLambda::Create(callback)](const BaseEventInfo* info) {
        const auto* eventInfo = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        NativeRichEditorRange range { eventInfo->start_, eventInfo->end_ };
        cjCallback(range);
    };
    RichEditorModel::GetInstance()->SetOnSelectionChange(std::move(onSelectionChange));
}

void FfiOHOSAceFrameworkRichEditorOnEditingChange(void(*callback)(bool))
{
    auto onEditingChange = [cjCallback = CJLambda::Create(callback)](const bool& isEditing) {
        cjCallback(isEditing);
    };
    RichEditorModel::GetInstance()->SetOnEditingChange(std::move(onEditingChange));
}

void FfiOHOSAceFrameworkRichEditorOnSubmit(bool(*callback)(int32_t, CJSubmitEvent))
{
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onsubmit = [cjCallback = CJLambda::Create(callback), node = targetNode](
                        int32_t key, NG::TextFieldCommonEvent& event) {
        PipelineContext::SetCallBackNode(node);
        auto submitEvent = std::make_unique<CJSubmitEvent>();
        std::string text = UtfUtils::Str16ToStr8(event.GetText());
        size_t len = text.length() + 1;
        submitEvent->text = (char*)malloc(len);
        submitEvent->keepEditable = event.IsKeepEditable();
        if (submitEvent->text) {
            const char* src = text.c_str();
            errno_t ret = strncpy_s(submitEvent->text, len, src, len - 1);
            if (ret != EOK) {
                free(submitEvent->text);
                return;
            }
            event.SetKeepEditable(cjCallback(key, *submitEvent));
            free(submitEvent->text);
        } else {
            event.SetKeepEditable(cjCallback(key, *submitEvent));
        }
    };
    RichEditorModel::GetInstance()->SetOnSubmit(std::move(onsubmit));
}

void FfiOHOSAceFrameworkRichEditorOnCut(void(*callback)(int64_t))
{
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onCut = [cjCallback = CJLambda::Create(callback), node = targetNode](NG::TextCommonEvent& info) {
        auto nativeCutEvent = FFIData::Create<NativePasteEvent>(&info);
        if (nativeCutEvent == nullptr) {
            return;
        }
        PipelineContext::SetCallBackNode(node);
        cjCallback(nativeCutEvent->GetID());
    };
    RichEditorModel::GetInstance()->SetOnCut(std::move(onCut));
}

void FfiOHOSAceFrameworkRichEditorOnCopy(void(*callback)(int64_t))
{
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onCopy = [cjCallback = CJLambda::Create(callback), node = targetNode](NG::TextCommonEvent& info) {
        auto nativeCopyEvent = FFIData::Create<NativePasteEvent>(&info);
        if (nativeCopyEvent == nullptr) {
            return;
        }
        PipelineContext::SetCallBackNode(node);
        cjCallback(nativeCopyEvent->GetID());
    };
    RichEditorModel::GetInstance()->SetOnCopy(std::move(onCopy));
}

void FfiOHOSAceFrameworkRichEditorOnWillChange(bool(*callback)(NativeRichEditorChangeValue))
{
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onWillChange = [cjCallback = CJLambda::Create(callback)](
                            const NG::RichEditorChangeValue& changeValue) {
        NativeRichEditorChangeValue nativeParams;
        const auto& rangeBefore = changeValue.GetRangeBefore();
        nativeParams.rangeBefore = { rangeBefore.start, rangeBefore.end };

        auto replacedSpans = changeValue.GetRichEditorReplacedSpans();
        auto replacedImageSpans = changeValue.GetRichEditorReplacedImageSpans();
        auto replacedSymbolSpans = changeValue.GetRichEditorReplacedSymbolSpans();

        auto nativeReplacedSpans = new NativeRichEditorTextSpanResult12[replacedSpans.size()];
        auto nativeReplacedImageSpans = new NativeRichEditorImageSpanResult12[replacedImageSpans.size()];
        auto nativeReplacedSymbolSpans = new NativeRichEditorTextSpanResult12[replacedSymbolSpans.size()];

        for (size_t i = 0; i < replacedSpans.size(); i++) {
            NativeRichEditorTextSpanResult12 current;
            NativeRichEditorController::ParseRichEditorAbstractTextSpanResult(replacedSpans[i], current);
            nativeReplacedSpans[i] = current;
        }
        for (size_t i = 0; i < replacedImageSpans.size(); i++) {
            NativeRichEditorImageSpanResult12 current;
            NativeRichEditorController::ParseRichEditorAbstractImageSpanResult(replacedImageSpans[i], current);
            nativeReplacedImageSpans[i] = current;
        }
        for (size_t i = 0; i < replacedSymbolSpans.size(); i++) {
            NativeRichEditorTextSpanResult12 current;
            NativeRichEditorController::ParseRichEditorAbstractSymbolSpanResult(replacedSymbolSpans[i], current);
            nativeReplacedSymbolSpans[i] = current;
        }

        nativeParams.replacedSpans = nativeReplacedSpans;
        nativeParams.replacedImageSpans = nativeReplacedImageSpans;
        nativeParams.replacedSymbolSpans = nativeReplacedSymbolSpans;
        nativeParams.replacedSpansSize = static_cast<int64_t>(replacedSpans.size());
        nativeParams.replacedImageSpansSize = static_cast<int64_t>(replacedImageSpans.size());
        nativeParams.replacedSymbolSpansSize = static_cast<int64_t>(replacedSymbolSpans.size());
        bool res = cjCallback(nativeParams);
        delete[] nativeReplacedSpans;
        delete[] nativeReplacedImageSpans;
        delete[] nativeReplacedSymbolSpans;

        return res;
    };
    RichEditorModel::GetInstance()->SetOnWillChange(std::move(onWillChange));
}

void FfiOHOSAceFrameworkRichEditorSetEnableHapticFeedback(bool enable)
{
    RichEditorModel::GetInstance()->SetEnableHapticFeedback(enable);
}
}
