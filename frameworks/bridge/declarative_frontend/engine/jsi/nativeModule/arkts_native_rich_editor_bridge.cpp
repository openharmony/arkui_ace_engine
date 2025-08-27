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
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
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
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (enableDataDetectorArg->IsNull() || enableDataDetectorArg->IsUndefined() ||
        !enableDataDetectorArg->IsBoolean()) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorEnableDataDetector(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t enableDataDetector = enableDataDetectorArg->Uint32Value(vm);
    nodeModifiers->getRichEditorModifier()->setRichEditorEnableDataDetector(nativeNode, enableDataDetector);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetEnableDataDetector(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorEnableDataDetector(nativeNode);
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
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (!typesArg->IsArray(vm)) {
        nodeModifiers->getRichEditorModifier()->
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
    nodeModifiers->getRichEditorModifier()->
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
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->
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
        spanPositionObj, panda::StringRef::NewFromUtf16(vm, event.GetValue().c_str()),
        panda::StringRef::NewFromUtf16(vm, event.GetPreviewText().c_str()),
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
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorOnIMEInputComplete(nativeNode);
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
    nodeModifiers->getRichEditorModifier()->setRichEditorOnIMEInputComplete(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnIMEInputComplete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnIMEInputComplete(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

Local<panda::ArrayRef> CreateTextShadowObjectArray(EcmaVM* vm, const TextStyleResult& textStyle)
{
    auto textShadowArray = panda::ArrayRef::New(vm, textStyle.textShadows.size());
    int32_t index = 0;
    for (const auto& it : textStyle.textShadows) {
        const char* keys[] = { "radius", "color", "offsetX", "offsetY" };
        Local<JSValueRef> values[] = {  panda::NumberRef::New(vm, static_cast<double>(it.GetBlurRadius())),
            panda::StringRef::NewFromUtf8(vm, it.GetColor().ToString().c_str()),
            panda::NumberRef::New(vm, static_cast<double>(it.GetOffset().GetX())),
            panda::NumberRef::New(vm, static_cast<double>(it.GetOffset().GetY())) };
        auto textShadowObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        panda::ArrayRef::SetValueAt(vm, textShadowArray, index, textShadowObj);
        index++;
    }
    return textShadowArray;
}

void CreateTextStyleObj(
    EcmaVM* vm, Local<panda::ObjectRef>& textStyleObj, const NG::RichEditorAbstractSpanResult& spanResult)
{
    const char* decorationObjKeys[] = { "type", "color", "style" };
    auto textDecoration = static_cast<int32_t>(spanResult.GetTextDecoration());
    auto textDecorationStyle = static_cast<int32_t>(spanResult.GetTextDecorationStyle());
    Local<JSValueRef> decorationObjValues[] = { panda::NumberRef::New(vm, textDecoration),
        panda::StringRef::NewFromUtf8(vm, spanResult.GetColor().c_str()),
        panda::NumberRef::New(vm, textDecorationStyle) };
    auto decorationObj = panda::ObjectRef::NewWithNamedProperties(
        vm, ArraySize(decorationObjKeys), decorationObjKeys, decorationObjValues);

    auto textShadowObjectArray = CreateTextShadowObjectArray(vm, spanResult.GetTextStyle());

    const char* textStyleObjKeys[] = { "fontColor", "fontFeature", "fontSize", "lineHeight", "letterSpacing",
        "fontStyle", "fontWeight", "fontFamily", "decoration", "textShadow" };
    Local<JSValueRef> textStyleObjValues[] = { panda::StringRef::NewFromUtf8(vm, spanResult.GetFontColor().c_str()),
        panda::StringRef::NewFromUtf8(vm, UnParseFontFeatureSetting(spanResult.GetFontFeatures()).c_str()),
        panda::NumberRef::New(vm, static_cast<double>(spanResult.GetFontSize())),
        panda::NumberRef::New(vm, static_cast<double>(spanResult.GetTextStyle().lineHeight)),
        panda::NumberRef::New(vm, static_cast<double>(spanResult.GetTextStyle().letterSpacing)),
        panda::NumberRef::New(vm, static_cast<int32_t>(static_cast<int32_t>(spanResult.GetFontStyle()))),
        panda::NumberRef::New(vm, static_cast<int32_t>(spanResult.GetFontWeight())),
        panda::StringRef::NewFromUtf8(vm, spanResult.GetFontFamily().c_str()), decorationObj, textShadowObjectArray };
    textStyleObj =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(textStyleObjKeys), textStyleObjKeys, textStyleObjValues);
}

void SetTextChangeSpanResult(
    EcmaVM* vm, panda::Local<panda::ObjectRef>& resultObj, const NG::RichEditorAbstractSpanResult& spanResult)
{
    auto textStyleObj = panda::ObjectRef::New(vm);
    CreateTextStyleObj(vm, textStyleObj, spanResult);
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "value"),
        panda::StringRef::NewFromUtf16(vm, spanResult.GetValue().c_str()));
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "previewText"),
        panda::StringRef::NewFromUtf16(vm, spanResult.GetPreviewText().c_str()));
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "textStyle"),
        textStyleObj);
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "paragraphStyle"),
        CreateParagraphStyle(vm, spanResult.GetTextStyle()));
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
            panda::StringRef::NewFromUtf16(vm, resultObject.valueString.c_str()));
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "textStyle"),
            CreateTextStyleResult(vm, resultObject.textStyle));
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "paragraphStyle"),
            CreateParagraphStyle(vm, resultObject.textStyle));
    } else if (resultObject.type == SelectSpanType::TYPESYMBOLSPAN) {
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "value"),
            panda::StringRef::NewFromUtf16(vm, resultObject.valueString.c_str()));
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
                panda::StringRef::NewFromUtf16(vm, resultObject.valueString.c_str()));
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

void SetSymbolChangeSpanResult(
    EcmaVM* vm, panda::Local<panda::ObjectRef>& resultObj, const NG::RichEditorAbstractSpanResult& spanResult)
{
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "symbolSpanStyle"),
        CreateSymbolSpanStyleResult(vm, spanResult.GetSymbolSpanStyle()));
    resultObj->Set(
        vm, panda::StringRef::NewFromUtf8(vm, "valueResource"), CreateValueResource(vm, spanResult.GetValueResource()));
    resultObj->Set(
        vm, panda::StringRef::NewFromUtf8(vm, "paragraphStyle"), CreateParagraphStyle(vm, spanResult.GetTextStyle()));
}

void SetImageChangeSpanResult(
    EcmaVM* vm, panda::Local<panda::ObjectRef>& resultObj, const NG::RichEditorAbstractSpanResult& spanResult)
{
    auto valuePixelMap = spanResult.GetValuePixelMap();
    auto returnWidth = spanResult.GetSizeWidth();
    auto returnHeight = spanResult.GetSizeHeight();
    if (valuePixelMap) {
#ifdef PIXEL_MAP_SUPPORTED
        if (NearZero(returnWidth) || NearZero(returnHeight)) {
            returnWidth = valuePixelMap->GetWidth();
            returnHeight = valuePixelMap->GetHeight();
        }
        auto jsPixmap = Framework::ConvertPixmap(valuePixelMap);
        if (!jsPixmap->IsUndefined()) {
            resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "valuePixelMap"),
                panda::StringRef::NewFromUtf8(vm, jsPixmap->ToString().c_str()));
        }
#endif
    } else {
        resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "valueResourceStr"),
            panda::StringRef::NewFromUtf8(vm, spanResult.GetValueResourceStr().c_str()));
    }
    ImageStyleResult imageStyleResult;
    imageStyleResult.size[0] = static_cast<double>(returnWidth);
    imageStyleResult.size[1] = static_cast<double>(returnHeight);
    imageStyleResult.verticalAlign = static_cast<int32_t>(spanResult.GetVerticalAlign());
    imageStyleResult.objectFit = static_cast<int32_t>(spanResult.GetObjectFit());
    imageStyleResult.borderRadius = spanResult.GetBorderRadius();
    imageStyleResult.margin = spanResult.GetMargin();
    resultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "imageStyle"), CreateImageStyleResult(vm, imageStyleResult));
}

void SetChangeTextSpans(
    EcmaVM* vm, const std::vector<NG::RichEditorAbstractSpanResult>& spanList, panda::Local<panda::ArrayRef>& jsArray)
{
    int32_t index = 0;
    for (const auto& it : spanList) {
        auto spanPositionObj = panda::ObjectRef::New(vm);
        auto spanResultObj = panda::ObjectRef::New(vm);
        auto spanRangeArray = panda::ArrayRef::New(vm, NUM_2);
        auto offsetInSpanArray = panda::ArrayRef::New(vm, NUM_2);
        panda::ArrayRef::SetValueAt(vm, spanRangeArray, NUM_0, panda::NumberRef::New(vm, it.GetSpanRangeStart()));
        panda::ArrayRef::SetValueAt(vm, spanRangeArray, NUM_1, panda::NumberRef::New(vm, it.GetSpanRangeEnd()));
        spanPositionObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "spanRange"), spanRangeArray);
        spanPositionObj->Set(
            vm, panda::StringRef::NewFromUtf8(vm, "spanIndex"), panda::NumberRef::New(vm, it.GetSpanIndex()));
        spanResultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "spanPosition"), spanPositionObj);
        panda::ArrayRef::SetValueAt(vm, offsetInSpanArray, NUM_0, panda::NumberRef::New(vm, it.OffsetInSpan()));
        panda::ArrayRef::SetValueAt(
            vm, offsetInSpanArray, NUM_1, panda::NumberRef::New(vm, it.OffsetInSpan() + it.GetEraseLength()));
        spanResultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "offsetInSpan"), offsetInSpanArray);
        switch (it.GetType()) {
            case NG::SpanResultType::TEXT:
                SetTextChangeSpanResult(vm, spanResultObj, it);
                break;
            case NG::SpanResultType::IMAGE:
                SetImageChangeSpanResult(vm, spanResultObj, it);
                break;
            case NG::SpanResultType::SYMBOL:
                SetSymbolChangeSpanResult(vm, spanResultObj, it);
                break;
            default:
                break;
        }
        panda::ArrayRef::SetValueAt(vm, jsArray, index++, spanResultObj);
    }
}

panda::Local<panda::ObjectRef> CreateOnWillChange(EcmaVM* vm, const NG::RichEditorChangeValue& changeValue)
{
    auto onWillChangeObj = panda::ObjectRef::New(vm);
    auto rangeBeforeObj = panda::ObjectRef::New(vm);
    const auto& rangeBefore = changeValue.GetRangeBefore();
    rangeBeforeObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "start"), panda::NumberRef::New(vm, rangeBefore.start));
    rangeBeforeObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "end"), panda::NumberRef::New(vm, rangeBefore.end));
    onWillChangeObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "rangeBefore"), rangeBeforeObj);
    auto replacedSpansArray = panda::ArrayRef::New(vm);
    SetChangeTextSpans(vm, changeValue.GetRichEditorReplacedSpans(), replacedSpansArray);
    onWillChangeObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "replacedSpans"), replacedSpansArray);
    auto replacedImageSpansArray = panda::ArrayRef::New(vm);
    SetChangeTextSpans(vm, changeValue.GetRichEditorReplacedImageSpans(), replacedImageSpansArray);
    onWillChangeObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "replacedImageSpans"), replacedImageSpansArray);
    auto replacedSymbolSpansArray = panda::ArrayRef::New(vm);
    SetChangeTextSpans(vm, changeValue.GetRichEditorReplacedSymbolSpans(), replacedSymbolSpansArray);
    onWillChangeObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "replacedSymbolSpans"), replacedSymbolSpansArray);

    return onWillChangeObj;
}

ArkUINativeModuleValue RichEditorBridge::SetOnWillChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (!callbackArg->IsFunction(vm)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorOnWillChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(const RichEditorChangeValue&)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](const RichEditorChangeValue& changeValue) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            auto eventObject = CreateOnWillChange(vm, changeValue);
            panda::Local<panda::JSValueRef> params[NUM_1] = { eventObject };
            auto ret = func->Call(vm, func.ToLocal(), params, NUM_1);
            if (ret->IsBoolean()) {
                return ret->ToBoolean(vm)->Value();
            }
            return true;
        };
    nodeModifiers->getRichEditorModifier()->setRichEditorOnWillChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnWillChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnWillChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnDidChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (!callbackArg->IsFunction(vm)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorOnDidChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const RichEditorChangeValue&)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](const RichEditorChangeValue& changeValue) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

            const auto& rangeBeforeValue = changeValue.GetRangeBefore();
            const char* keysOfRangeBefore[] = { "start", "end" };
            Local<JSValueRef> valuesOfRangeBefore[] = { panda::NumberRef::New(vm, rangeBeforeValue.start),
                panda::NumberRef::New(vm, rangeBeforeValue.end) };
            auto rangeBeforeObj = panda::ObjectRef::NewWithNamedProperties(
                vm, ArraySize(keysOfRangeBefore), keysOfRangeBefore, valuesOfRangeBefore);

            const auto& rangeAfterValue = changeValue.GetRangeAfter();
            const char* keysOfRangeAfter[] = { "start", "end" };
            Local<JSValueRef> valuesOfRangeAfter[] = { panda::NumberRef::New(vm, rangeAfterValue.start),
                panda::NumberRef::New(vm, rangeAfterValue.end) };
            auto rangeAftereObj = panda::ObjectRef::NewWithNamedProperties(
                vm, ArraySize(keysOfRangeAfter), keysOfRangeAfter, valuesOfRangeAfter);

            panda::Local<panda::JSValueRef> params[NUM_2] = { rangeBeforeObj, rangeAftereObj };
            auto ret = func->Call(vm, func.ToLocal(), params, NUM_2);
            if (ret->IsBoolean()) {
                return ret->ToBoolean(vm)->Value();
            }
            return true;
        };
    nodeModifiers->getRichEditorModifier()->setRichEditorOnDidChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnDidChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnDidChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void CreateImageStyleObj(EcmaVM* vm, Local<panda::ObjectRef>& imageStyleObj, Local<panda::ObjectRef>& spanResultObj,
    const NG::RichEditorAbstractSpanResult& spanResult)
{
    auto imageSizeArray = panda::ArrayRef::New(vm, NUM_2);
    panda::ArrayRef::SetValueAt(vm, imageSizeArray, NUM_0, panda::NumberRef::New(vm, spanResult.GetSizeWidth()));
    panda::ArrayRef::SetValueAt(vm, imageSizeArray, NUM_1, panda::NumberRef::New(vm, spanResult.GetSizeHeight()));

    imageStyleObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "size"), imageSizeArray);
    imageStyleObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "verticalAlign"),
        panda::NumberRef::New(vm, static_cast<int32_t>(spanResult.GetVerticalAlign())));
    imageStyleObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "objectFit"),
        panda::NumberRef::New(vm, static_cast<int32_t>(spanResult.GetObjectFit())));
    if (spanResult.GetValuePixelMap()) {
#ifdef PIXEL_MAP_SUPPORTED
        auto jsPixmap = Framework::ConvertPixmap(spanResult.GetValuePixelMap());
        if (!jsPixmap->IsUndefined()) {
            spanResultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "valuePixelMap"),
                panda::StringRef::NewFromUtf8(vm, jsPixmap->ToString().c_str()));
        }
#endif
    } else {
        spanResultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "valueResourceStr"),
            panda::StringRef::NewFromUtf8(vm, spanResult.GetValueResourceStr().c_str()));
    }
}

void SetDeleteSpan(
    EcmaVM* vm, panda::Local<panda::ObjectRef>& spanResultObj, const NG::RichEditorAbstractSpanResult& spanResult)
{
    CHECK_NULL_VOID(vm);
    switch (spanResult.GetType()) {
        case NG::SpanResultType::TEXT: {
            SetTextChangeSpanResult(vm, spanResultObj, spanResult);
            break;
        }
        case NG::SpanResultType::IMAGE: {
            auto imageStyleObj = panda::ObjectRef::New(vm);
            CreateImageStyleObj(vm, imageStyleObj, spanResultObj, spanResult);
            const char* keys[] = { "borderRadius", "margin" };
            Local<JSValueRef> values[] = { panda::StringRef::NewFromUtf8(vm, spanResult.GetBorderRadius().c_str()),
                panda::StringRef::NewFromUtf8(vm, spanResult.GetMargin().c_str()) };
            auto layoutStyleObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            imageStyleObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "layoutStyle"), layoutStyleObj);
            spanResultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "imageStyle"), imageStyleObj);
            break;
        }
        case NG::SpanResultType::SYMBOL: {
            spanResultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "value"),
                panda::StringRef::NewFromUtf8(vm, spanResult.GetValueString().c_str()));
            spanResultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "symbolSpanStyle"),
                CreateSymbolSpanStyleResult(vm, spanResult.GetSymbolSpanStyle()));
            spanResultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "valueResource"),
                CreateValueResource(vm, spanResult.GetValueResource()));
            break;
        }
        default:
            break;
    }
}

panda::Local<panda::ObjectRef> CreateDeleteSpans(EcmaVM* vm, const NG::RichEditorDeleteValue& deleteValue)
{
    int32_t index = 0;
    auto list = deleteValue.GetRichEditorDeleteSpans();
    auto richEditorDeleteSpans = panda::ArrayRef::New(vm, list.size());
    for (const auto& it : list) {
        auto spanPositionObj = panda::ObjectRef::New(vm);
        auto spanResultObj = panda::ObjectRef::New(vm);
        auto spanRangeArray = panda::ArrayRef::New(vm, NUM_2);
        auto offsetInSpanArray = panda::ArrayRef::New(vm, NUM_2);
        panda::ArrayRef::SetValueAt(vm, spanRangeArray, NUM_0, panda::NumberRef::New(vm, it.GetSpanRangeStart()));
        panda::ArrayRef::SetValueAt(vm, spanRangeArray, NUM_1, panda::NumberRef::New(vm, it.GetSpanRangeEnd()));
        spanPositionObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "spanRange"), spanRangeArray);
        spanPositionObj->Set(
            vm, panda::StringRef::NewFromUtf8(vm, "spanIndex"), panda::NumberRef::New(vm, it.GetSpanIndex()));
        spanResultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "spanPosition"), spanPositionObj);
        panda::ArrayRef::SetValueAt(vm, offsetInSpanArray, NUM_0, panda::NumberRef::New(vm, it.OffsetInSpan()));
        panda::ArrayRef::SetValueAt(
            vm, offsetInSpanArray, NUM_1, panda::NumberRef::New(vm, it.OffsetInSpan() + it.GetEraseLength()));
        spanResultObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "offsetInSpan"), offsetInSpanArray);
        SetDeleteSpan(vm, spanResultObj, it);
        panda::ArrayRef::SetValueAt(vm, richEditorDeleteSpans, index++, spanResultObj);
    }
    return richEditorDeleteSpans;
}

ArkUINativeModuleValue RichEditorBridge::SetAboutToDelete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (!callbackArg->IsFunction(vm)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorAboutToDelete(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(const RichEditorDeleteValue&)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](const RichEditorDeleteValue& deleteValue) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            auto deleteSpansObj = CreateDeleteSpans(vm, deleteValue);
            const char* keys[] = { "offset", "direction", "length", "richEditorDeleteSpans" };
            Local<JSValueRef> values[] = { panda::NumberRef::New(vm, deleteValue.GetOffset()),
                panda::NumberRef::New(vm, static_cast<int32_t>(deleteValue.GetRichEditorDeleteDirection())),
                panda::NumberRef::New(vm, deleteValue.GetLength()), deleteSpansObj };
            auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            panda::Local<panda::JSValueRef> params[NUM_1] = { eventObject };
            auto ret = func->Call(vm, func.ToLocal(), params, NUM_1);
            if (ret->IsBoolean()) {
                return ret->ToBoolean(vm)->Value();
            }
            return true;
        };
    nodeModifiers->getRichEditorModifier()->setRichEditorAboutToDelete(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetAboutToDelete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorAboutToDelete(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ParseFont(EcmaVM* vm, const panda::Local<panda::ObjectRef>& fontObject, Font& font)
{
    if (fontObject->IsUndefined()) {
        return;
    }
    Local<JSValueRef> fontSize = fontObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "size"));
    CalcDimension size;
    if (!fontSize->IsNull() && ArkTSUtils::ParseJsDimensionFpNG(vm, fontSize, size) && !size.IsNegative() &&
        size.Unit() != DimensionUnit::PERCENT) {
        font.fontSize = size;
    } else if (size.IsNegative() || size.Unit() == DimensionUnit::PERCENT) {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        size = theme->GetTextStyle().GetFontSize();
        font.fontSize = size;
    }
    Local<JSValueRef> fontStyle = fontObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "style"));
    if (fontStyle->IsNumber()) {
        font.fontStyle = static_cast<Ace::FontStyle>(fontStyle->Uint32Value(vm));
    }
    Local<JSValueRef> fontWeight = fontObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "weight"));
    if (!fontWeight->IsNull()) {
        std::string weight;
        if (fontWeight->IsNumber()) {
            weight = std::to_string(fontWeight->Int32Value(vm));
        } else {
            ArkTSUtils::ParseJsString(vm, fontWeight, weight);
        }
        font.fontWeight = OHOS::Ace::Framework::ConvertStrToFontWeight(weight);
    }
    Local<JSValueRef> fontFamily = fontObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "family"));
    if (!fontFamily->IsNull()) {
        std::vector<std::string> fontFamilies;
        if (ArkTSUtils::ParseJsFontFamilies(vm, fontFamily, fontFamilies)) {
            font.fontFamilies = fontFamilies;
        }
    }
}

void PushDimensionVector(const std::optional<Dimension>& valueDim, std::vector<double>& dimensions)
{
    dimensions.push_back(static_cast<double>(valueDim.has_value()));
    if (valueDim.has_value()) {
        dimensions.push_back(valueDim.value().Value());
        dimensions.push_back(static_cast<double>(valueDim.value().Unit()));
    } else {
        dimensions.push_back(NUM_0);
        dimensions.push_back(NUM_0);
    }
}

std::optional<uint32_t> ParseColorResourceId(const EcmaVM* vm, const Local<JSValueRef>& colorVal)
{
    if (!colorVal->IsObject(vm)) {
        return std::nullopt;
    }
    auto colorObj = colorVal->ToObject(vm);
    ArkTSUtils::CompleteResourceObject(vm, colorObj);
    Local<JSValueRef> resIdArg = colorObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    if (!resIdArg->IsNumber()) {
        return std::nullopt;
    }
    uint32_t typeValue = 0;
    auto typeArg = colorObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    if (typeArg->IsNumber()) {
        typeValue = typeArg->Uint32Value(vm);
    }
    if (typeValue != static_cast<uint32_t>(OHOS::Ace::NG::ResourceType::COLOR)) {
        return std::nullopt;
    }
    return resIdArg->ToNumber(vm)->Value();
}

void ParsePlaceholderStyle(EcmaVM* vm, const Local<JSValueRef>& styleArg, PlaceholderOptions& options,
    std::optional<Color>& fontColorOpt, std::optional<uint32_t>& colorResourceIdOpt)
{
    Font font;
    if (styleArg->IsObject(vm)) {
        auto styleObj = styleArg->ToObject(vm);
        auto fontArg = styleObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "font"));
        if (fontArg->IsObject(vm)) {
            auto fontObj = fontArg->ToObject(vm);
            ParseFont(vm, fontObj, font);
        }
        auto fontColorArg = styleObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "fontColor"));
        Color fontColorParsed;
        if (!fontColorArg->IsNull() && ArkTSUtils::ParseJsColor(vm, fontColorArg, fontColorParsed)) {
            fontColorOpt = fontColorParsed;
            colorResourceIdOpt = ParseColorResourceId(vm, fontColorArg);
        }
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textTheme = pipeline->GetTheme<TextTheme>();
    TextStyle textStyle = textTheme ? textTheme->GetTextStyle() : TextStyle();
    options.fontSize = font.fontSize.value_or(textStyle.GetFontSize());
    options.fontFamilies = !font.fontFamilies.empty() ? font.fontFamilies : textStyle.GetFontFamilies();
    options.fontWeight = font.fontWeight.value_or(textStyle.GetFontWeight());
    options.fontStyle = font.fontStyle.value_or(textStyle.GetFontStyle());
    if (!fontColorOpt.has_value()) {
        Color fontColor;
        auto richEditorTheme = pipeline->GetTheme<OHOS::Ace::NG::RichEditorTheme>();
        options.fontColor = richEditorTheme ? richEditorTheme->GetPlaceholderColor() : fontColor;
    }
}

ArkUINativeModuleValue RichEditorBridge::SetPlaceholder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    PlaceholderOptions options;
    std::optional<Color> fontColor = std::nullopt;
    std::optional<uint32_t> colorResourceId = std::nullopt;
    std::string placeholderValue;
    ArkTSUtils::ParseJsString(vm, valueArg, placeholderValue);
    ParsePlaceholderStyle(vm, styleArg, options, fontColor, colorResourceId);
    colorResourceId = -1;
    std::vector<ArkUI_CharPtr> stringParameters;
    stringParameters.push_back(placeholderValue.c_str());
    if (!options.fontFamilies.empty()) {
        for (size_t index = 0; index < options.fontFamilies.size(); index++) {
            stringParameters.push_back(options.fontFamilies[index].c_str());
        }
    }
    std::vector<double> valuesVector;
    valuesVector.push_back(static_cast<double>(options.fontWeight.has_value()));
    valuesVector.push_back(options.fontWeight.has_value() ? static_cast<double>(options.fontWeight.value()) : 0.0);
    valuesVector.push_back(static_cast<double>(options.fontStyle.has_value()));
    valuesVector.push_back(options.fontStyle.has_value() ? static_cast<double>(options.fontStyle.value()) : 0.0);
    valuesVector.push_back(static_cast<double>(fontColor.has_value() || options.fontColor.has_value()));
    auto optionColor = static_cast<double>(options.fontColor.has_value() ? options.fontColor.value().GetValue() : 0.0);
    valuesVector.push_back(fontColor.has_value() ? static_cast<double>(fontColor.value().GetValue()) : optionColor);
    valuesVector.push_back(static_cast<double>(colorResourceId.has_value()));
    valuesVector.push_back(colorResourceId.has_value() ? static_cast<double>(colorResourceId.value()) : 0.0);
    PushDimensionVector(options.fontSize, valuesVector);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->setRichEditorPlaceholder(
        nativeNode, stringParameters.data(), stringParameters.size(), valuesVector.data(), valuesVector.size());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetPlaceholder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorPlaceholder(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetCopyOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    uint32_t CopyOptionsValue = static_cast<uint32_t>(CopyOptions::Distributed);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber()) {
        CopyOptionsValue = secondArg->Uint32Value(vm);
        nodeModifiers->getRichEditorModifier()->setRichEditorCopyOptions(nativeNode, CopyOptionsValue);
    } else {
        nodeModifiers->getRichEditorModifier()->resetRichEditorCopyOptions(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetCopyOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    nodeModifiers->getRichEditorModifier()->resetRichEditorCopyOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnSelectionChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorOnSelectionChange(nativeNode);
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
    nodeModifiers->getRichEditorModifier()->setRichEditorOnSelectionChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnSelectionChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnSelectionChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetCaretColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorCaretColor(nativeNode);
    } else {
        nodeModifiers->getRichEditorModifier()->setRichEditorCaretColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetCaretColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorCaretColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorOnSelect(nativeNode);
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
    nodeModifiers->getRichEditorModifier()->setRichEditorOnSelect(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnSelect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnSubmit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorOnSubmit(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, NG::TextFieldCommonEvent&)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](int32_t key, NG::TextFieldCommonEvent& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        const char* keys[] = { "text", "keepEditableState" };
        Local<JSValueRef> values[] = { panda::StringRef::NewFromUtf16(vm, event.GetText().c_str()),
            panda::FunctionRef::New(vm, Framework::JSRichEditor::JsKeepEditableState) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        eventObject->SetNativePointerFieldCount(vm, NUM_1);
        eventObject->SetNativePointerField(vm, 0, static_cast<void*>(&event));
        panda::Local<panda::JSValueRef> params[NUM_2] = {
            panda::IntegerRef::New(vm, key), eventObject };
        func->Call(vm, func.ToLocal(), params, NUM_2);
    };
    nodeModifiers->getRichEditorModifier()->setRichEditorOnSubmit(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnSubmit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnSubmit(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetAboutToIMEInput(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorAboutToIMEInput(nativeNode);
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
            panda::StringRef::NewFromUtf16(vm, insertValue.GetInsertValue().c_str()),
            panda::StringRef::NewFromUtf16(vm, insertValue.GetPreviewText().c_str()) };
        auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
        panda::Local<panda::JSValueRef> params[NUM_1] = { eventObject };
        auto ret = func->Call(vm, func.ToLocal(), params, NUM_1);
        if (ret->IsBoolean()) {
            return ret->ToBoolean(vm)->Value();
        }
        return true;
    };
    nodeModifiers->getRichEditorModifier()->setRichEditorAboutToIMEInput(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetAboutToIMEInput(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    nodeModifiers->getRichEditorModifier()->resetRichEditorAboutToIMEInput(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnReady(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getRichEditorModifier()->resetOnReady(nativeNode);
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
    nodeModifiers->getRichEditorModifier()->setOnReady(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnReady(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetOnReady(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnDeleteComplete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getRichEditorModifier()->resetOnDeleteComplete(nativeNode);
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
    nodeModifiers->getRichEditorModifier()->setOnDeleteComplete(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnDeleteComplete(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetOnDeleteComplete(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnEditingChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getRichEditorModifier()->resetOnEditingChange(nativeNode);
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
    nodeModifiers->getRichEditorModifier()->setOnEditingChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnEditingChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetOnEditingChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetSelectedBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorSelectedBackgroundColor(nativeNode);
    } else {
        nodeModifiers->getRichEditorModifier()->setRichEditorSelectedBackgroundColor(
            nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetSelectedBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorSelectedBackgroundColor(nativeNode);
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
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorOnPaste(nativeNode);
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
    nodeModifiers->getRichEditorModifier()->setRichEditorOnPaste(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnPaste(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnPaste(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnCut(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorOnCut(nativeNode);
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
    nodeModifiers->getRichEditorModifier()->setRichEditorOnCut(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnCut(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnCut(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorOnCopy(nativeNode);
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
    nodeModifiers->getRichEditorModifier()->setRichEditorOnCopy(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnCopy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> enableArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (enableArg->IsUndefined() || enableArg->IsNull() || !enableArg->IsBoolean()) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorEnableKeyboardOnFocus(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool enable = false;
    enable = enableArg->ToBoolean(vm)->BooleaValue(vm);
    nodeModifiers->getRichEditorModifier()->setRichEditorEnableKeyboardOnFocus(nativeNode, enable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorEnableKeyboardOnFocus(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetEnablePreviewText(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> enableArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (enableArg->IsUndefined() || enableArg->IsNull() || !enableArg->IsBoolean()) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorEnablePreviewText(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool enable = false;
    enable = enableArg->ToBoolean(vm)->BooleaValue(vm);
    nodeModifiers->getRichEditorModifier()->setRichEditorEnablePreviewText(nativeNode, enable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetEnablePreviewText(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorEnablePreviewText(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}


ArkUINativeModuleValue RichEditorBridge::SetEditMenuOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClickCallback;
    NG::OnPrepareMenuCallback onPrepareMenuCallback;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (!ArkTSUtils::ParseSelectionMenuOptions(
        runtimeCallInfo, vm, onCreateMenuCallback, onMenuItemClickCallback, onPrepareMenuCallback)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorEditMenuOptions(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    nodeModifiers->getRichEditorModifier()->setRichEditorEditMenuOptions(nativeNode,
        reinterpret_cast<void*>(&onCreateMenuCallback), reinterpret_cast<void*>(&onMenuItemClickCallback),
        reinterpret_cast<void*>(&onPrepareMenuCallback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetEditMenuOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorEditMenuOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetEnterKeyType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    uint32_t enterKeyType = static_cast<uint32_t>(TextInputAction::NEW_LINE);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber()) {
        enterKeyType = secondArg->Uint32Value(vm);
        nodeModifiers->getRichEditorModifier()->setRichEditorEnterKeyType(nativeNode, enterKeyType);
    } else {
        nodeModifiers->getRichEditorModifier()->resetRichEditorEnterKeyType(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetEnterKeyType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorEnterKeyType(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetBarState(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber()) {
        uint32_t barStateValue = secondArg->Uint32Value(vm);
        nodeModifiers->getRichEditorModifier()->setRichEditorBarState(nativeNode, barStateValue);
    } else {
        nodeModifiers->getRichEditorModifier()->resetRichEditorBarState(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetBarState(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorBarState(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetMaxLength(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (!secondArg->IsNumber()) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorMaxLength(nativeNode);
    } else {
        int32_t maxLength = secondArg->Int32Value(vm);
        if (std::isinf(static_cast<float>(secondArg->ToNumber(vm)->Value()))) {
            maxLength = INT32_MAX;
        }
        if (maxLength >= 0) {
            nodeModifiers->getRichEditorModifier()->setRichEditorMaxLength(nativeNode, maxLength);
        } else {
            nodeModifiers->getRichEditorModifier()->resetRichEditorMaxLength(nativeNode);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetMaxLength(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorMaxLength(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetMaxLines(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber() && secondArg->Int32Value(vm) > 0) {
        nodeModifiers->getRichEditorModifier()->setRichEditorMaxLines(nativeNode, secondArg->Uint32Value(vm));
    } else {
        nodeModifiers->getRichEditorModifier()->resetRichEditorMaxLines(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetMaxLines(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorMaxLines(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetStopBackPress(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        nodeModifiers->getRichEditorModifier()->setRichEditorStopBackPress(nativeNode, value);
    } else {
        nodeModifiers->getRichEditorModifier()->resetRichEditorStopBackPress(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetStopBackPress(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorStopBackPress(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetKeyboardAppearance(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber()) {
        uint32_t keyboardAppearance = secondArg->Uint32Value(vm);
        nodeModifiers->getRichEditorModifier()->
            setRichEditorKeyboardAppearance(nativeNode, keyboardAppearance);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetKeyboardAppearance(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorKeyboardAppearance(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetOnDidIMEInput(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getRichEditorModifier()->resetRichEditorOnDidIMEInput(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(TextRange&)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](TextRange& event) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

        const auto& textRange= event;
        const char* keysOfTextRange[] = { "start", "end" };
        Local<JSValueRef> valuesOfTextRange[] = { panda::NumberRef::New(vm, textRange.start),
            panda::NumberRef::New(vm, textRange.end) };
        auto textRangeObj = panda::ObjectRef::NewWithNamedProperties(
            vm, ArraySize(keysOfTextRange), keysOfTextRange, valuesOfTextRange);
        panda::Local<panda::JSValueRef> params[NUM_1] = {textRangeObj};
        func->Call(vm, func.ToLocal(), params, NUM_1);
    };
    nodeModifiers->getRichEditorModifier()->setRichEditorOnDidIMEInput(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetOnDidIMEInput(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorOnDidIMEInput(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::SetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        nodeModifiers->getRichEditorModifier()->setRichEditorEnableHapticFeedback(nativeNode, value);
    } else {
        nodeModifiers->getRichEditorModifier()->resetRichEditorEnableHapticFeedback(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RichEditorBridge::ResetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getRichEditorModifier()->resetRichEditorEnableHapticFeedback(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}