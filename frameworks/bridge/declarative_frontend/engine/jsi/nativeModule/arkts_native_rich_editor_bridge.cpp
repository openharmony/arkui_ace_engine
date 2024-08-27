/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_rich_editor_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_richeditor.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/common/ace_application_info.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components_ng/pattern/rich_editor/selection_info.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_event_hub.h"
namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
const std::vector<std::string> TEXT_DETECT_TYPES = { "phoneNum", "url", "email", "location", "datetime" };
}

ArkUINativeModuleValue RichEditorBridge::SetEnableDataDetector(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> enableDataDetectorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (enableDataDetectorArg->IsNull() || enableDataDetectorArg->IsUndefined() ||
        !enableDataDetectorArg->IsBoolean()) {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorEnableDataDetector(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t enableDataDetector = enableDataDetectorArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getRichEditorModifier()->setRichEditorEnableDataDetector(nativeNode, enableDataDetector);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetEnableDataDetector(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorEnableDataDetector(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

Local<panda::ObjectRef> CreateParagraphStyle(EcmaVM *vm, const TextStyleResult& textStyleResult)
{
    auto leadingMarginArray = panda::ArrayRef::New(vm);
    panda::ArrayRef::SetValueAt(vm, leadingMarginArray, NUM_0,
        panda::StringRef::NewFromUtf8(vm, textStyleResult.leadingMarginSize[NUM_0].c_str()));
    panda::ArrayRef::SetValueAt(vm, leadingMarginArray, NUM_1,
        panda::StringRef::NewFromUtf8(vm, textStyleResult.leadingMarginSize[NUM_1].c_str()));
    const char* keys[] = { "textAlign", "leadingMargin" };
    Local<JSValueRef> values[] = { panda::NumberRef::New(vm, textStyleResult.textAlign), leadingMarginArray };
    auto returnObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        returnObject->Set(vm, panda::StringRef::NewFromUtf8(vm, "wordBreak"),
            panda::NumberRef::New(vm, textStyleResult.wordBreak));
        returnObject->Set(vm, panda::StringRef::NewFromUtf8(vm, "lineBreakStrategy"),
            panda::NumberRef::New(vm, textStyleResult.lineBreakStrategy));
    }
    return returnObject;
}

ArkUINativeModuleValue RichEditorBridge::SetDataDetectorConfig(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> typesArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (!typesArg->IsArray(vm)) {
        GetArkUINodeModifiers()->getRichEditorModifier()->
            resetRichEditorDataDetectorConfigWithEvent(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    struct ArkUITextDetectConfigStruct arkUITextDetectConfig;
    std::string types;
    auto array = panda::Local<panda::ArrayRef>(typesArg);
    for (size_t i = 0; i < array->Length(vm); i++) {
        auto value = panda::ArrayRef::GetValueAt(vm, array, i);
        auto index = value->Int32Value(vm);
        if (index < 0 || index >= static_cast<int32_t>(TEXT_DETECT_TYPES.size())) {
            return panda::JSValueRef::Undefined(vm);
        }
        if (i != 0) {
            types.append(",");
        }
        types.append(TEXT_DETECT_TYPES[index]);
    }
    arkUITextDetectConfig.types = types.c_str();
    std::function<void(const std::string&)> callback;
    if (callbackArg->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
        callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](const std::string& info) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            panda::Local<panda::JSValueRef> params[NUM_1] = {
                panda::StringRef::NewFromUtf8(vm, info.c_str()) };
            func->Call(vm, func.ToLocal(), params, NUM_1);
        };
        arkUITextDetectConfig.onResult = reinterpret_cast<void*>(&callback);
    }
    ParseAIEntityColor(runtimeCallInfo, arkUITextDetectConfig);
    GetArkUINodeModifiers()->getRichEditorModifier()->
        setRichEditorDataDetectorConfigWithEvent(nativeNode, &arkUITextDetectConfig);
    return panda::JSValueRef::Undefined(vm);
}

void RichEditorBridge::ParseAIEntityColor(
    ArkUIRuntimeCallInfo* runtimeCallInfo, struct ArkUITextDetectConfigStruct& arkUITextDetectConfig)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    TextDetectConfig textDetectConfig;
    Local<JSValueRef> entityColorArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    ArkTSUtils::ParseJsColorAlpha(vm, entityColorArg, textDetectConfig.entityColor);
    arkUITextDetectConfig.entityColor = textDetectConfig.entityColor.GetValue();

    Local<JSValueRef> entityDecorationTypeArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> entityDecorationColorArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Local<JSValueRef> entityDecorationStyleArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    arkUITextDetectConfig.entityDecorationType = static_cast<int32_t>(textDetectConfig.entityDecorationType);
    arkUITextDetectConfig.entityDecorationColor = arkUITextDetectConfig.entityColor;
    arkUITextDetectConfig.entityDecorationStyle = static_cast<int32_t>(textDetectConfig.entityDecorationStyle);

    if (entityDecorationTypeArg->IsInt()) {
        arkUITextDetectConfig.entityDecorationType = entityDecorationTypeArg->Int32Value(vm);
    }
    if (ArkTSUtils::ParseJsColorAlpha(vm, entityDecorationColorArg, textDetectConfig.entityDecorationColor)) {
        arkUITextDetectConfig.entityDecorationColor = textDetectConfig.entityDecorationColor.GetValue();
    }
    if (entityDecorationStyleArg->IsInt()) {
        arkUITextDetectConfig.entityDecorationStyle = entityDecorationStyleArg->Int32Value(vm);
    }
}

ArkUINativeModuleValue RichEditorBridge::ResetDataDetectorConfig(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->
        resetRichEditorDataDetectorConfigWithEvent(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

Local<panda::ObjectRef> CreateAbstractSpanResult(EcmaVM *vm, RichEditorAbstractSpanResult& event)
{
    const char* spanPositionObjKeys[] = { "spanRange", "spanIndex" };
    auto spanRange = panda::ArrayRef::New(vm);
    panda::ArrayRef::SetValueAt(vm, spanRange, NUM_0, panda::NumberRef::New(vm, event.GetSpanRangeStart()));
    panda::ArrayRef::SetValueAt(vm, spanRange, NUM_1, panda::NumberRef::New(vm, event.GetSpanRangeEnd()));
    Local<JSValueRef> spanPositionObjValues[] = { spanRange, panda::NumberRef::New(vm, event.GetSpanIndex()) };
    auto spanPositionObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(spanPositionObjKeys),
        spanPositionObjKeys, spanPositionObjValues);
    const char* decorationObjKeys[] = { "type", "color" };
    Local<JSValueRef> decorationObjValues[] = {
        panda::NumberRef::New(vm, static_cast<int32_t>(event.GetTextDecoration())),
        panda::StringRef::NewFromUtf8(vm, event.GetColor().c_str())
    };
    auto decorationObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(decorationObjKeys),
        decorationObjKeys, decorationObjValues);

    const char* textStyleObjKeys[] = { "fontColor", "fontFeature", "fontSize", "lineHeight",
        "letterSpacing", "fontStyle", "fontWeight", "fontFamily", "decoration"};
    Local<JSValueRef> textStyleObjValues[] = {
        panda::StringRef::NewFromUtf8(vm, event.GetFontColor().c_str()),
        panda::StringRef::NewFromUtf8(vm, UnParseFontFeatureSetting(event.GetFontFeatures()).c_str()),
        panda::NumberRef::New(vm, event.GetFontSize()),
        panda::NumberRef::New(vm, event.GetTextStyle().lineHeight),
        panda::NumberRef::New(vm, event.GetTextStyle().letterSpacing),
        panda::NumberRef::New(vm, static_cast<int32_t>(event.GetFontStyle())),
        panda::NumberRef::New(vm, event.GetFontWeight()),
        panda::StringRef::NewFromUtf8(vm, event.GetFontFamily().c_str()), decorationObj
    };
    auto textStyleObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(textStyleObjKeys),
        textStyleObjKeys, textStyleObjValues);
    auto offsetInSpan = panda::ArrayRef::New(vm);
    panda::ArrayRef::SetValueAt(vm, offsetInSpan, NUM_0, panda::NumberRef::New(vm, event.OffsetInSpan()));
    panda::ArrayRef::SetValueAt(vm, offsetInSpan, NUM_1,
        panda::NumberRef::New(vm, event.OffsetInSpan() + event.GetEraseLength()));

    const char* onIMEInputCompleteObjKeys[] = { "spanPosition", "value", "previewText", "textStyle",
        "offsetInSpan", "paragraphStyle" };
    Local<JSValueRef> onIMEInputCompleteObjValues[] = {
        spanPositionObj, panda::StringRef::NewFromUtf8(vm, event.GetValue().c_str()),
        panda::StringRef::NewFromUtf8(vm, event.GetPreviewText().c_str()),
        textStyleObj, offsetInSpan,
        CreateParagraphStyle(vm, event.GetTextStyle())
    };
    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(onIMEInputCompleteObjKeys),
        onIMEInputCompleteObjKeys, onIMEInputCompleteObjValues);
}

ArkUINativeModuleValue RichEditorBridge::SetOnIMEInputComplete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorOnIMEInputComplete(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(RichEditorAbstractSpanResult&)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](RichEditorAbstractSpanResult& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto onIMEInputCompleteObj = CreateAbstractSpanResult(vm, event);
        onIMEInputCompleteObj->SetNativePointerFieldCount(vm, NUM_1);
        onIMEInputCompleteObj->SetNativePointerField(vm, NUM_0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[NUM_1] = { onIMEInputCompleteObj };
        func->Call(vm, func.ToLocal(), params, NUM_1);
    };
    GetArkUINodeModifiers()->getRichEditorModifier()->setRichEditorOnIMEInputComplete(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnIMEInputComplete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorOnIMEInputComplete(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetCopyOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    uint32_t CopyOptionsValue = static_cast<uint32_t>(CopyOptions::Distributed);
    if (secondArg->IsNumber()) {
        CopyOptionsValue = secondArg->Uint32Value(vm);
        GetArkUINodeModifiers()->getRichEditorModifier()->setRichEditorCopyOptions(nativeNode, CopyOptionsValue);
    } else {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorCopyOptions(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetCopyOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorCopyOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnSelectionChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorOnSelectionChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* info)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](const BaseEventInfo* info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const auto* changeInfo = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        if (!changeInfo) {
            TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "richEditor SetOnSelectionChange callback execute failed.");
            return;
        }
        const char* keys[] = { "start", "end" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, changeInfo->start_),
            panda::NumberRef::New(vm, changeInfo->end_) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        panda::Local<panda::JSValueRef> params[NUM_1] = { eventObject };
        func->Call(vm, func.ToLocal(), params, NUM_1);
    };
    GetArkUINodeModifiers()->getRichEditorModifier()->setRichEditorOnSelectionChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnSelectionChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorOnSelectionChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetCaretColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorCaretColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getRichEditorModifier()->setRichEditorCaretColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetCaretColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorCaretColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

Local<panda::ObjectRef> CreateTextStyleResult(EcmaVM *vm, const TextStyleResult& textStyleResult)
{
    const char* decorationObjKeys[] = { "type", "color" };
    Local<JSValueRef> decorationObjValues[] = {
        panda::NumberRef::New(vm, static_cast<int32_t>(textStyleResult.decorationType)),
        panda::StringRef::NewFromUtf8(vm, textStyleResult.decorationColor.c_str())
    };
    auto decorationObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(decorationObjKeys),
        decorationObjKeys, decorationObjValues);

    auto leadingMarginArray = panda::ArrayRef::New(vm);
    panda::ArrayRef::SetValueAt(vm, leadingMarginArray, NUM_0,
        panda::StringRef::NewFromUtf8(vm, textStyleResult.leadingMarginSize[NUM_0].c_str()));
    panda::ArrayRef::SetValueAt(vm, leadingMarginArray, NUM_1,
        panda::StringRef::NewFromUtf8(vm, textStyleResult.leadingMarginSize[NUM_1].c_str()));

    const char* textStyleObjKeys[] = { "fontColor", "fontFeature", "fontSize", "fontStyle",
        "lineHeight", "letterSpacing", "fontWeight", "fontFamily", "decoration", "textAlign", "leadingMarginSize" };
    Local<JSValueRef> textStyleObjValues[] = {
        panda::StringRef::NewFromUtf8(vm, textStyleResult.fontColor.c_str()),
        panda::StringRef::NewFromUtf8(vm, UnParseFontFeatureSetting(textStyleResult.fontFeature).c_str()),
        panda::NumberRef::New(vm, textStyleResult.fontSize),
        panda::NumberRef::New(vm, textStyleResult.fontStyle),
        panda::NumberRef::New(vm, textStyleResult.lineHeight),
        panda::NumberRef::New(vm, textStyleResult.letterSpacing),
        panda::NumberRef::New(vm, textStyleResult.fontWeight),
        panda::StringRef::NewFromUtf8(vm, textStyleResult.fontFamily.c_str()), decorationObj,
        panda::NumberRef::New(vm, textStyleResult.textAlign), leadingMarginArray
    };
    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(textStyleObjKeys),
        textStyleObjKeys, textStyleObjValues);
}

Local<panda::ObjectRef> CreateSymbolSpanStyleResult(EcmaVM *vm, const SymbolSpanStyle& symbolSpanStyle)
{
    const char* symbolSpanStyleObjKeys[] = { "fontColor", "fontFeature", "fontSize", "lineHeight",
        "letterSpacing", "fontWeight", "renderingStrategy", "effectStrategy" };
    Local<JSValueRef> symbolSpanStyleObjValues[] = {
        panda::StringRef::NewFromUtf8(vm, symbolSpanStyle.symbolColor.c_str()),
        panda::StringRef::NewFromUtf8(vm, UnParseFontFeatureSetting(symbolSpanStyle.fontFeature).c_str()),
        panda::NumberRef::New(vm, symbolSpanStyle.fontSize),
        panda::NumberRef::New(vm, symbolSpanStyle.lineHeight),
        panda::NumberRef::New(vm, symbolSpanStyle.letterSpacing),
        panda::NumberRef::New(vm, symbolSpanStyle.fontWeight),
        panda::NumberRef::New(vm, symbolSpanStyle.renderingStrategy),
        panda::NumberRef::New(vm, symbolSpanStyle.effectStrategy)
    };
    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(symbolSpanStyleObjKeys),
        symbolSpanStyleObjKeys, symbolSpanStyleObjValues);
}

Local<panda::ArrayRef> CreateResourceObjectParam(EcmaVM *vm, const std::vector<ResourceObjectParams>& params)
{
    auto size = static_cast<int32_t>(params.size());
    auto valueResourceObj = panda::ArrayRef::New(vm, size);
    for (int32_t i = 0; i < size; i++) {
        const char* valueResourceItemKeys[] = { "type", "value" };
        auto type = panda::StringRef::NewFromUtf8(vm, "ResourceObjectParamType::NONE");
        if (params[i].type == ResourceObjectParamType::FLOAT) {
            type = panda::StringRef::NewFromUtf8(vm, "ResourceObjectParamType::FLOAT");
        } else if (params[i].type == ResourceObjectParamType::STRING) {
            type = panda::StringRef::NewFromUtf8(vm, "ResourceObjectParamType::STRING");
        } else if (params[i].type == ResourceObjectParamType::INT) {
            type = panda::StringRef::NewFromUtf8(vm, "ResourceObjectParamType::INT");
        } else {
            type = panda::StringRef::NewFromUtf8(vm, "ResourceObjectParamType::NONE");
        }
        Local<JSValueRef> valueResourceItemValues[] = { type,
            panda::StringRef::NewFromUtf8(vm, params[i].value->c_str())
        };
        auto valueResourceItem = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(valueResourceItemKeys),
            valueResourceItemKeys, valueResourceItemValues);
        panda::ArrayRef::SetValueAt(vm, valueResourceObj, i, valueResourceItem);
    }
    return valueResourceObj;
}

Local<panda::ObjectRef> CreateValueResource(EcmaVM *vm, const RefPtr<ResourceObject>& valueResource)
{
    const char* valueResourceKeys[] = { "bundleName", "moduleName", "id", "params", "type" };
    Local<JSValueRef> valueResourceValues[] = {
        panda::StringRef::NewFromUtf8(vm, valueResource->GetBundleName().c_str()),
        panda::StringRef::NewFromUtf8(vm, valueResource->GetModuleName().c_str()),
        panda::NumberRef::New(vm, valueResource->GetId()),
        CreateResourceObjectParam(vm, valueResource->GetParams()),
        panda::NumberRef::New(vm, valueResource->GetType())
    };
    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(valueResourceKeys),
        valueResourceKeys, valueResourceValues);
}

Local<panda::ObjectRef> CreateImageStyleResult(EcmaVM *vm, const ImageStyleResult& imageStyleResult)
{
    const char* layoutStyleObjKeys[] = { "borderRadius", "margin" };
    Local<JSValueRef> layoutStyleObjValues[] = {
        panda::StringRef::NewFromUtf8(vm, imageStyleResult.borderRadius.c_str()),
        panda::StringRef::NewFromUtf8(vm, imageStyleResult.margin.c_str())
    };
    auto layoutStyleObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(layoutStyleObjKeys),
        layoutStyleObjKeys, layoutStyleObjValues);

    auto sizeArray = panda::ArrayRef::New(vm);
    panda::ArrayRef::SetValueAt(vm, sizeArray, NUM_0, panda::NumberRef::New(vm, imageStyleResult.size[NUM_0]));
    panda::ArrayRef::SetValueAt(vm, sizeArray, NUM_1, panda::NumberRef::New(vm, imageStyleResult.size[NUM_1]));

    const char* imageSpanStyleObjKeys[] = { "size", "verticalAlign", "objectFit", "layoutStyle" };
    Local<JSValueRef> imageSpanStyleObjValues[] = {
        sizeArray, panda::NumberRef::New(vm, imageStyleResult.verticalAlign),
        panda::NumberRef::New(vm, imageStyleResult.objectFit), layoutStyleObj
    };
    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(imageSpanStyleObjKeys),
        imageSpanStyleObjKeys, imageSpanStyleObjValues);
}

Local<panda::ObjectRef> CreateSpanResultObject(EcmaVM *vm, const ResultObject& resultObject)
{
    auto offsetArray = panda::ArrayRef::New(vm);
    panda::ArrayRef::SetValueAt(vm, offsetArray, NUM_0, panda::NumberRef::New(vm, resultObject.offsetInSpan[NUM_0]));
    panda::ArrayRef::SetValueAt(vm, offsetArray, NUM_1, panda::NumberRef::New(vm, resultObject.offsetInSpan[NUM_1]));
    auto spanRangeArray = panda::ArrayRef::New(vm);
    panda::ArrayRef::SetValueAt(vm, spanRangeArray, NUM_0,
        panda::NumberRef::New(vm, resultObject.spanPosition.spanRange[NUM_0]));
    panda::ArrayRef::SetValueAt(vm, spanRangeArray, NUM_1,
        panda::NumberRef::New(vm, resultObject.spanPosition.spanRange[NUM_1]));
    const char* spanPositionObjKeys[] = { "spanIndex", "spanRange" };
    Local<JSValueRef> spanPositionObjValues[] = {
        panda::NumberRef::New(vm, resultObject.spanPosition.spanIndex), spanRangeArray
    };
    auto spanPositionObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(spanPositionObjKeys),
        spanPositionObjKeys, spanPositionObjValues);

    auto resultObj = panda::ObjectRef::New(vm);
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "offsetInSpan"), offsetArray);
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "spanPosition"), spanPositionObj);
    if (resultObject.type == SelectSpanType::TYPESPAN) {
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "value"),
            panda::StringRef::NewFromUtf8(vm, resultObject.valueString.c_str()));
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "textStyle"),
            CreateTextStyleResult(vm, resultObject.textStyle));
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "paragraphStyle"),
            CreateParagraphStyle(vm, resultObject.textStyle));
    } else if (resultObject.type == SelectSpanType::TYPESYMBOLSPAN) {
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "value"),
            panda::StringRef::NewFromUtf8(vm, resultObject.valueString.c_str()));
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "symbolSpanStyle"),
            CreateSymbolSpanStyleResult(vm, resultObject.symbolSpanStyle));
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "valueResource"),
            CreateValueResource(vm, resultObject.valueResource));
    } else if (resultObject.type == SelectSpanType::TYPEIMAGE) {
        if (resultObject.valuePixelMap) {
#if defined (PIXEL_MAP_SUPPORTED)
            auto jsPixmap = Framework::ConvertPixmap(resultObject.valuePixelMap);
            if (!jsPixmap->IsUndefined()) {
                resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "valuePixelMap"),
                    panda::StringRef::NewFromUtf8(vm, jsPixmap->ToString().c_str()));
            }
#endif
        } else {
            resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "valueResourceStr"),
                panda::StringRef::NewFromUtf8(vm, resultObject.valueString.c_str()));
        }
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "imageStyle"),
            CreateImageStyleResult(vm, resultObject.imageStyle));
    }

    return resultObj;
}

void CreatSelectEvent(EcmaVM *vm, const BaseEventInfo* info, panda::Local<panda::JSValueRef> params[])
{
    const auto* selectInfo = TypeInfoHelper::DynamicCast<SelectionInfo>(info);
    if (!selectInfo) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "richEditor SetOnSelect callback execute failed.");
        return;
    }
    const char* keys[] = { "selection", "spans" };
    auto selectionArray = panda::ArrayRef::New(vm, NUM_2);
    auto selectionObjValue = selectInfo->GetSelection();
    panda::ArrayRef::SetValueAt(vm, selectionArray, NUM_0,
        panda::NumberRef::New(vm, selectionObjValue.selection[NUM_0]));
    panda::ArrayRef::SetValueAt(vm, selectionArray, NUM_1,
        panda::NumberRef::New(vm, selectionObjValue.selection[NUM_1]));

    auto spanObjectArray = panda::ArrayRef::New(vm);
    auto idx = 0;
    for (const ResultObject& spanObject : selectionObjValue.resultObjects) {
        panda::ArrayRef::SetValueAt(vm, spanObjectArray, idx++, CreateSpanResultObject(vm, spanObject));
    }
    Local<JSValueRef> values[] = { selectionArray, spanObjectArray };
    auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
    params[NUM_1] = { eventObject };
}

ArkUINativeModuleValue RichEditorBridge::SetOnSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorOnSelect(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* info)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](const BaseEventInfo* info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1];
        CreatSelectEvent(vm, info, params);
        func->Call(vm, func.ToLocal(), params, NUM_1);
    };
    GetArkUINodeModifiers()->getRichEditorModifier()->setRichEditorOnSelect(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorOnSelect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnSubmit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorOnSubmit(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, NG::TextFieldCommonEvent&)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](int32_t key, NG::TextFieldCommonEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "text", "keepEditableState" };
        Local<JSValueRef> values[] = { panda::StringRef::NewFromUtf8(vm, event.GetText().c_str()),
            panda::FunctionRef::New(vm, Framework::JSRichEditor::JsKeepEditableState) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, NUM_1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[NUM_2] = {
            panda::IntegerRef::New(vm, key), eventObject };
        func->Call(vm, func.ToLocal(), params, NUM_2);
    };
    GetArkUINodeModifiers()->getRichEditorModifier()->setRichEditorOnSubmit(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnSubmit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorOnSubmit(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetAboutToIMEInput(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorAboutToIMEInput(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(const RichEditorInsertValue&)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](const RichEditorInsertValue& insertValue) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "insertOffset", "insertValue", "previewText" };
        Local<JSValueRef> values[] = { panda::NumberRef::New(vm, insertValue.GetInsertOffset()),
            panda::StringRef::NewFromUtf8(vm, insertValue.GetInsertValue().c_str()),
            panda::StringRef::NewFromUtf8(vm, insertValue.GetPreviewText().c_str()) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        panda::Local<panda::JSValueRef> params[NUM_1] = { eventObject };
        auto ret = func->Call(vm, func.ToLocal(), params, NUM_1);
        if (ret->IsBoolean()) {
            return ret->ToBoolean(vm)->Value();
        }
        return true;
    };
    GetArkUINodeModifiers()->getRichEditorModifier()->setRichEditorAboutToIMEInput(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetAboutToIMEInput(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorAboutToIMEInput(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnReady(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetOnReady(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(void)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        func->Call(vm, func.ToLocal(), nullptr, NUM_0);
    };
    GetArkUINodeModifiers()->getRichEditorModifier()->setOnReady(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnReady(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetOnReady(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnDeleteComplete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetOnDeleteComplete(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(void)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        func->Call(vm, func.ToLocal(), nullptr, NUM_0);
    };
    GetArkUINodeModifiers()->getRichEditorModifier()->setOnDeleteComplete(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnDeleteComplete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetOnDeleteComplete(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnEditingChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetOnEditingChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(bool)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](bool isInEditStatus) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1] = {
            panda::BooleanRef::New(vm, isInEditStatus) };
        func->Call(vm, func.ToLocal(), params, NUM_1);
    };
    GetArkUINodeModifiers()->getRichEditorModifier()->setOnEditingChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnEditingChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetOnEditingChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetSelectedBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorSelectedBackgroundColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getRichEditorModifier()->setRichEditorSelectedBackgroundColor(
            nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetSelectedBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorSelectedBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void CreateCommonEvent(EcmaVM *vm, TextCommonEvent& event, panda::Local<panda::JSValueRef> params[])
{
    auto eventObject = panda::ObjectRef::New(vm);
    eventObject->SetNativePointerFieldCount(vm, NUM_1);
    eventObject->Set(vm, panda::StringRef::NewFromUtf8(vm, "preventDefault"),
        panda::FunctionRef::New(vm, Framework::JsPreventDefault));
    eventObject->SetNativePointerField(vm, NUM_0, static_cast<void*>(&event));
    params[NUM_1] = { eventObject };
}

ArkUINativeModuleValue RichEditorBridge::SetOnPaste(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorOnPaste(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(TextCommonEvent&)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](TextCommonEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1];
        CreateCommonEvent(vm, event, params);
        func->Call(vm, func.ToLocal(), params, NUM_1);
    };
    GetArkUINodeModifiers()->getRichEditorModifier()->setRichEditorOnPaste(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnPaste(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorOnPaste(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnCut(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorOnCut(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(TextCommonEvent&)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](TextCommonEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1];
        CreateCommonEvent(vm, event, params);
        func->Call(vm, func.ToLocal(), params, NUM_1);
    };
    GetArkUINodeModifiers()->getRichEditorModifier()->setRichEditorOnCut(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnCut(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorOnCut(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorOnCopy(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(TextCommonEvent&)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](TextCommonEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1];
        CreateCommonEvent(vm, event, params);
        func->Call(vm, func.ToLocal(), params, NUM_1);
    };
    GetArkUINodeModifiers()->getRichEditorModifier()->setRichEditorOnCopy(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorOnCopy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> enableArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (enableArg->IsUndefined() || enableArg->IsNull() || !enableArg->IsBoolean()) {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorEnableKeyboardOnFocus(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool enable = false;
    enable = enableArg->ToBoolean(vm)->BooleaValue(vm);
    GetArkUINodeModifiers()->getRichEditorModifier()->setRichEditorEnableKeyboardOnFocus(nativeNode, enable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorEnableKeyboardOnFocus(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetEnablePreviewText(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> enableArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (enableArg->IsUndefined() || enableArg->IsNull() || !enableArg->IsBoolean()) {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorEnablePreviewText(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool enable = false;
    enable = enableArg->ToBoolean(vm)->BooleaValue(vm);
    GetArkUINodeModifiers()->getRichEditorModifier()->setRichEditorEnablePreviewText(nativeNode, enable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetEnablePreviewText(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorEnablePreviewText(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}


ArkUINativeModuleValue RichEditorBridge::SetEditMenuOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClickCallback;
    if (!ArkTSUtils::ParseSelectionMenuOptions(runtimeCallInfo, vm, onCreateMenuCallback, onMenuItemClickCallback)) {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorEditMenuOptions(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getRichEditorModifier()->setRichEditorEditMenuOptions(
        nativeNode, reinterpret_cast<void*>(&onCreateMenuCallback), reinterpret_cast<void*>(&onMenuItemClickCallback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetEditMenuOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorEditMenuOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetEnterKeyType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    uint32_t enterKeyType = static_cast<uint32_t>(TextInputAction::NEW_LINE);
    if (secondArg->IsNumber()) {
        enterKeyType = secondArg->Uint32Value(vm);
        GetArkUINodeModifiers()->getRichEditorModifier()->setRichEditorEnterKeyType(nativeNode, enterKeyType);
    } else {
        GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorEnterKeyType(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetEnterKeyType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRichEditorModifier()->resetRichEditorEnterKeyType(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}