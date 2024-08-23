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

#include "cj_lambda.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
std::vector<NG::TextResponseType> RESPONSE_TYPES = {
    NG::TextResponseType::RIGHT_CLICK, NG::TextResponseType::LONG_PRESS
};

std::vector<NG::TextSpanType> EDITOR_TYPES = {
    NG::TextSpanType::TEXT, NG::TextSpanType::IMAGE, NG::TextSpanType::MIXED
};

std::vector<CopyOptions> COPYOPTIONS_TYPES = {
    CopyOptions::None, CopyOptions::InApp, CopyOptions::Local
};
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
        NativeRichEditorInsertValue result {
            insertValue.GetInsertOffset(), insertValue.GetInsertValue().c_str()
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

        NativeRichEditorTextSpanResult result {
            spanPosition,
            textSpanResult.GetValue().c_str(),
            textStyle,
            textSpanResult.OffsetInSpan(),
            textSpanResult.OffsetInSpan() + textSpanResult.GetEraseLength()
        };

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
}
