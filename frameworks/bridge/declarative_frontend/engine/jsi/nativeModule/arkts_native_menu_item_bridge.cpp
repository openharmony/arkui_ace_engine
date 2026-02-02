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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_menu_item_bridge.h"

#include "bridge/declarative_frontend/ark_theme/theme_apply/js_menu_item_theme.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "frameworks/core/components_ng/base/view_stack_model.h"

using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const std::string FORMAT_FONT = "%s|%s|%s";
const std::string DEFAULT_ERR_CODE = "-1";
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int PARAM_ARR_LENGTH_1 = 1;

struct MenuItemParseResult {
    std::string contentStr;
    std::string labelStr;
    std::string startIconPath;
    std::string endIconPath;
    ImageSourceInfo startIconInfo;
    ImageSourceInfo endIconInfo;
    std::function<void(WeakPtr<NG::FrameNode>)> startSymbolApply;
    std::function<void(WeakPtr<NG::FrameNode>)> endSymbolApply;
    std::function<void()> buildFunc;
    RefPtr<ResourceObject> contentStrObj;
    RefPtr<ResourceObject> labelStrObj;
    RefPtr<ResourceObject> startIconObj;
    RefPtr<ResourceObject> endIconObj;
};

bool GetNativeNode(ArkUINodeHandle& nativeNode, const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    if (firstArg->IsNativePointer(vm)) {
        nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
        return true;
    }
    if (firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value()) {
        nativeNode = nullptr;
        return true;
    }
    return false;
}

bool IsJsView(const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    if (firstArg->IsBoolean()) {
        return firstArg->ToBoolean(vm)->Value();
    }
    return false;
}

bool ParseFontOptions(EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, bool isJsView,
    std::vector<Local<JSValueRef>>& args, bool isLabelFont)
{
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, false);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, false);
    auto menuItemModifier = nodeModifiers->getMenuItemModifier();
    CHECK_NULL_RETURN(menuItemModifier, false);
    if (isJsView) {
        Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
        if (secondArg->IsObject(vm)) {
            auto obj = secondArg->ToObject(vm);
            args[NUM_0] = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "size"));
            args[NUM_1] = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "weight"));
            args[NUM_2] = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "family"));
            args[NUM_3] = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "style"));
        } else {
            return false;
        }
    } else {
        args[NUM_0] = runtimeCallInfo->GetCallArgRef(NUM_1);
        args[NUM_1] = runtimeCallInfo->GetCallArgRef(NUM_2);
        args[NUM_2] = runtimeCallInfo->GetCallArgRef(NUM_3);
        args[NUM_3] = runtimeCallInfo->GetCallArgRef(NUM_4);
    }
    if (args[NUM_0]->IsUndefined() && args[NUM_1]->IsUndefined() && args[NUM_2]->IsUndefined() &&
        args[NUM_3]->IsUndefined()) {
        if (isLabelFont) {
            menuItemModifier->resetLabelFont(nativeNode);
        } else {
            menuItemModifier->resetContentFont(nativeNode);
        }
        return false;
    }
    return true;
}

void SetSymbolOptionApply(
    EcmaVM* vm, std::function<void(WeakPtr<NG::FrameNode>)>& symbolApply, const Local<JSValueRef> modifierObj)
{
    auto globalObj = JSNApi::GetGlobalObject(vm);
    auto globalFunc = globalObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "applySymbolGlyphModifierToNode"));
    if (globalFunc->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = globalFunc->ToObject(vm);
        if (!modifierObj->IsObject(vm)) {
            symbolApply = nullptr;
        } else {
            auto onApply = [vm, func = panda::CopyableGlobal(vm, func),
                               modifierParam = panda::CopyableGlobal(vm, modifierObj)](
                               WeakPtr<NG::FrameNode> frameNode) {
                panda::LocalScope pandaScope(vm);
                panda::TryCatch trycatch(vm);
                auto node = frameNode.Upgrade();
                CHECK_NULL_VOID(node);
                Local<JSValueRef> params[NUM_2];
                params[NUM_0] = modifierParam.ToLocal();
                params[NUM_1] = panda::NativePointerRef::New(vm, AceType::RawPtr(node));
                PipelineContext::SetCallBackNode(node);
                auto result = func->Call(vm, func.ToLocal(), params, 2);
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            };
            symbolApply = onApply;
        }
    }
}

void ParseMenuItemOptionsResource(EcmaVM* vm, const Local<ObjectRef>& menuItemObj,
    ArkUIMenuItemOptions& menuItemOptions, MenuItemParseResult& parseResult)
{
    Local<JSValueRef> startIcon = menuItemObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "startIcon"));
    Local<JSValueRef> content = menuItemObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "content"));
    Local<JSValueRef> endIcon = menuItemObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "endIcon"));
    Local<JSValueRef> label = menuItemObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "labelInfo"));
    Local<JSValueRef> symbolStart = menuItemObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "symbolStartIcon"));
    Local<JSValueRef> symbolEnd = menuItemObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "symbolEndIcon"));

    if (symbolStart->IsObject(vm)) {
        SetSymbolOptionApply(vm, parseResult.startSymbolApply, symbolStart);
        menuItemOptions.startSymbolApply = reinterpret_cast<void*>(&parseResult.startSymbolApply);
    } else if (ArkTSUtils::ParseJsMedia(vm, startIcon, parseResult.startIconPath, parseResult.startIconObj, true)) {
        std::string bundleName;
        std::string moduleName;
        ArkTSUtils::GetJsMediaBundleInfo(vm, startIcon, bundleName, moduleName);
        parseResult.startIconInfo = ImageSourceInfo(parseResult.startIconPath, bundleName, moduleName);
        menuItemOptions.startIconSrc = reinterpret_cast<void*>(&parseResult.startIconInfo);
    }

    ArkTSUtils::ParseJsString(vm, content, parseResult.contentStr, parseResult.contentStrObj);
    menuItemOptions.content = parseResult.contentStr.c_str();

    if (symbolEnd->IsObject(vm)) {
        SetSymbolOptionApply(vm, parseResult.endSymbolApply, symbolEnd);
        menuItemOptions.endSymbolApply = reinterpret_cast<void*>(&parseResult.endSymbolApply);
    } else if (ArkTSUtils::ParseJsMedia(vm, endIcon, parseResult.endIconPath, parseResult.endIconObj, true)) {
        std::string bundleName;
        std::string moduleName;
        ArkTSUtils::GetJsMediaBundleInfo(vm, endIcon, bundleName, moduleName);
        parseResult.endIconInfo = ImageSourceInfo(parseResult.endIconPath, bundleName, moduleName);
        menuItemOptions.endIconSrc = reinterpret_cast<void*>(&parseResult.endIconInfo);
    }

    if (ArkTSUtils::ParseJsString(vm, label, parseResult.labelStr, parseResult.labelStrObj)) {
        menuItemOptions.labelInfo = parseResult.labelStr.c_str();
    }

    if (SystemProperties::ConfigChangePerform()) {
        if (parseResult.contentStrObj) {
            menuItemOptions.contentResObj = AceType::RawPtr(parseResult.contentStrObj);
        }
        if (parseResult.labelStrObj) {
            menuItemOptions.labelResObj = AceType::RawPtr(parseResult.labelStrObj);
        }
        if (parseResult.startIconObj) {
            menuItemOptions.startIconResObj = AceType::RawPtr(parseResult.startIconObj);
        }
        if (parseResult.endIconObj) {
            menuItemOptions.endIconResObj = AceType::RawPtr(parseResult.endIconObj);
        }
    }
}
} // namespace

ArkUINativeModuleValue MenuItemBridge::SetMenuItemSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> isSelectedArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuItemModifier = nodeModifiers->getMenuItemModifier();
    CHECK_NULL_RETURN(menuItemModifier, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);
    bool isSelected = false;
    Local<JSValueRef> changeEventArg = panda::JSValueRef::Undefined(vm);
    if (isJsView) {
        if (isSelectedArg->IsObject(vm)) {
            auto jsObj = isSelectedArg->ToObject(vm);
            isSelectedArg = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
            changeEventArg = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "$value"));
        } else if (runtimeCallInfo->GetArgsNumber() > NUM_2) {
            changeEventArg = runtimeCallInfo->GetCallArgRef(NUM_2);
        }
        if (isSelectedArg->IsBoolean()) {
            isSelected = isSelectedArg->ToBoolean(vm)->Value();
        }
        menuItemModifier->setMenuItemSelected(nativeNode, isSelected);
        if (changeEventArg->IsFunction(vm)) {
            auto targetNode = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
            panda::Local<panda::FunctionRef> func = changeEventArg->ToObject(vm);
            std::function<void(bool)> callback = [vm, func = panda::CopyableGlobal(vm, func), node = targetNode](
                                                     bool selected) {
                panda::LocalScope pandaScope(vm);
                panda::TryCatch trycatch(vm);
                PipelineContext::SetCallBackNode(node);
                panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { panda::BooleanRef::New(vm, selected) };
                auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            };
            menuItemModifier->setSelectedChangeEvent(nativeNode, std::move(callback));
        }
    } else {
        if (isSelectedArg->IsBoolean()) {
            isSelected = isSelectedArg->ToBoolean(vm)->Value();
            menuItemModifier->setMenuItemSelected(nativeNode, isSelected);
        } else {
            menuItemModifier->resetMenuItemSelected(nativeNode);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::ResetMenuItemSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuItemModifier = nodeModifiers->getMenuItemModifier();
    CHECK_NULL_RETURN(menuItemModifier, panda::JSValueRef::Undefined(vm));
    menuItemModifier->resetMenuItemSelected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::SetLabelFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (isJsView && argsNumber < NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuItemModifier = nodeModifiers->getMenuItemModifier();
    CHECK_NULL_RETURN(menuItemModifier, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, colorResObj, nodeInfo)) {
        menuItemModifier->resetLabelFontColor(nativeNode);
    } else {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        menuItemModifier->setLabelFontColor(nativeNode, color.GetValue(), colorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::ResetLabelFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuItemModifier = nodeModifiers->getMenuItemModifier();
    CHECK_NULL_RETURN(menuItemModifier, panda::JSValueRef::Undefined(vm));
    menuItemModifier->resetLabelFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::SetContentFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (isJsView && argsNumber < NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuItemModifier = nodeModifiers->getMenuItemModifier();
    CHECK_NULL_RETURN(menuItemModifier, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, colorResObj, nodeInfo)) {
        menuItemModifier->resetContentFontColor(nativeNode);
    } else {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        menuItemModifier->setContentFontColor(nativeNode, color.GetValue(), colorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::ResetContentFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuItemModifier = nodeModifiers->getMenuItemModifier();
    CHECK_NULL_RETURN(menuItemModifier, panda::JSValueRef::Undefined(vm));
    menuItemModifier->resetContentFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::SetLabelFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuItemModifier = nodeModifiers->getMenuItemModifier();
    CHECK_NULL_RETURN(menuItemModifier, panda::JSValueRef::Undefined(vm));
    std::vector<Local<JSValueRef>> args(NUM_4, panda::JSValueRef::Undefined(vm));
    // 0: index of font size value, 1: index of font weight value, 2: index of font family value,
    // 3: index of font style value
    bool isJsView = IsJsView(firstArg, vm);
    CHECK_EQUAL_RETURN(
        ParseFontOptions(vm, runtimeCallInfo, isJsView, args, true), false, panda::JSValueRef::Undefined(vm));

    CalcDimension fontSize;
    RefPtr<ResourceObject> fontSizeResObj;
    if (!ArkTSUtils::ParseJsDimensionFp(vm, args[NUM_0], fontSize, fontSizeResObj, false)) {
        fontSize = Dimension(0.0);
    }

    std::string weight = DEFAULT_ERR_CODE;
    if (args[NUM_1]->IsNumber()) {
        weight = std::to_string(args[NUM_1]->Int32Value(vm));
    } else {
        if (!ArkTSUtils::ParseJsString(vm, args[NUM_1], weight) || weight.empty()) {
            weight = DEFAULT_ERR_CODE;
        }
    }

    int32_t style = -1;
    if (args[NUM_3]->IsNumber()) {
        style = args[NUM_3]->Int32Value(vm);
    }

    std::string family;
    RefPtr<ResourceObject> fontFamiliesResObj;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, args[NUM_2], family, fontFamiliesResObj) || family.empty()) {
        family = DEFAULT_ERR_CODE;
    }

    std::string fontSizeStr = fontSize.ToString();
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSizeStr.c_str(), weight.c_str(), family.c_str());
    auto fontFamiliesRawPtr = AceType::RawPtr(fontFamiliesResObj);
    auto fontSizeRawPtr = AceType::RawPtr(fontSizeResObj);
    menuItemModifier->setLabelFont(nativeNode, fontInfo.c_str(), style, fontFamiliesRawPtr, fontSizeRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::ResetLabelFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuItemModifier = nodeModifiers->getMenuItemModifier();
    CHECK_NULL_RETURN(menuItemModifier, panda::JSValueRef::Undefined(vm));
    menuItemModifier->resetLabelFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::SetContentFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuItemModifier = nodeModifiers->getMenuItemModifier();
    CHECK_NULL_RETURN(menuItemModifier, panda::JSValueRef::Undefined(vm));
    std::vector<Local<JSValueRef>> args(NUM_4, panda::JSValueRef::Undefined(vm));
    // 0: index of font size value, 1: index of font weight value, 2: index of font family value,
    // 3: index of font style value
    bool isJsView = IsJsView(firstArg, vm);
    CHECK_EQUAL_RETURN(
        ParseFontOptions(vm, runtimeCallInfo, isJsView, args, false), false, panda::JSValueRef::Undefined(vm));

    CalcDimension fontSize;
    RefPtr<ResourceObject> fontSizeResObj;
    if (!ArkTSUtils::ParseJsDimensionFp(vm, args[NUM_0], fontSize, fontSizeResObj, false)) {
        fontSize = Dimension(0.0);
    }

    std::string weight = DEFAULT_ERR_CODE;
    if (args[NUM_1]->IsNumber()) {
        weight = std::to_string(args[NUM_1]->Int32Value(vm));
    } else {
        if (!ArkTSUtils::ParseJsString(vm, args[NUM_1], weight) || weight.empty()) {
            weight = DEFAULT_ERR_CODE;
        }
    }

    int32_t style = -1;
    if (args[NUM_3]->IsNumber()) {
        style = args[NUM_3]->Int32Value(vm);
    }

    std::string family;
    RefPtr<ResourceObject> fontFamiliesResObj;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, args[NUM_2], family, fontFamiliesResObj) || family.empty()) {
        family = DEFAULT_ERR_CODE;
    }

    std::string fontSizeStr = fontSize.ToString();
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSizeStr.c_str(), weight.c_str(), family.c_str());
    auto fontFamiliesRawPtr = AceType::RawPtr(fontFamiliesResObj);
    auto fontSizeRawPtr = AceType::RawPtr(fontSizeResObj);
    menuItemModifier->setContentFont(nativeNode, fontInfo.c_str(), style, fontSizeRawPtr, fontFamiliesRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::ResetContentFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuItemModifier = nodeModifiers->getMenuItemModifier();
    CHECK_NULL_RETURN(menuItemModifier, panda::JSValueRef::Undefined(vm));
    menuItemModifier->resetContentFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::SetSelectIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> inputArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuItemModifier = nodeModifiers->getMenuItemModifier();
    CHECK_NULL_RETURN(menuItemModifier, panda::JSValueRef::Undefined(vm));
    bool isShow = false;
    std::string icon;
    RefPtr<ResourceObject> selectIconResObj;
    std::function<void(WeakPtr<NG::FrameNode>)> symbolApply;
    if (inputArg->IsBoolean()) {
        isShow = inputArg->ToBoolean(vm)->Value();
    } else if (inputArg->IsString(vm)) {
        icon = inputArg->ToString(vm)->ToString(vm);
        isShow = true;
    } else if (ArkTSUtils::ParseJsMedia(vm, inputArg, icon, selectIconResObj, isJsView)) {
        isShow = true;
    } else if (inputArg->IsObject(vm)) {
        isShow = true;
        Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
        Framework::JSViewAbstract::SetSymbolOptionApply(runtimeCallInfo, symbolApply, info[NUM_1]);
    }
    auto selectIconRawPtr = AceType::RawPtr(selectIconResObj);
    menuItemModifier->setSelectIcon(nativeNode, isShow);
    menuItemModifier->setSelectIconSrc(nativeNode, icon.c_str(), selectIconRawPtr);
    menuItemModifier->setSelectIconSymbol(nativeNode, reinterpret_cast<void*>(&symbolApply));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::ResetSelectIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuItemModifier = nodeModifiers->getMenuItemModifier();
    CHECK_NULL_RETURN(menuItemModifier, panda::JSValueRef::Undefined(vm));
    menuItemModifier->resetSelectIcon(nativeNode);
    menuItemModifier->resetSelectIconSrc(nativeNode);
    menuItemModifier->resetSelectIconSymbol(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::SetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber != NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuItemModifier = nodeModifiers->getMenuItemModifier();
    CHECK_NULL_RETURN(menuItemModifier, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);
    NG::FrameNode* frameNode = nullptr;
    if (isJsView) {
        frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    } else {
        frameNode = reinterpret_cast<FrameNode*>(nativeNode);
        CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    }
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            menuItemModifier->resetOnChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(bool)> callback = [vm, isJsView, frameNode, func = panda::CopyableGlobal(vm, func)](bool flag) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1] = { panda::BooleanRef::New(vm, flag) };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    menuItemModifier->setOnChange(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::ResetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuItemModifier = nodeModifiers->getMenuItemModifier();
    CHECK_NULL_RETURN(menuItemModifier, panda::JSValueRef::Undefined(vm));
    menuItemModifier->resetOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::Create(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuItemModifier = nodeModifiers->getMenuItemModifier();
    CHECK_NULL_RETURN(menuItemModifier, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> paramArg = runtimeCallInfo->GetCallArgRef(NUM_0);

    if (runtimeCallInfo->GetArgsNumber() < 1 || (!paramArg->IsObject(vm) && !paramArg->IsFunction(vm))) {
        menuItemModifier->createWithCustomNode(nullptr);
        JSMenuItemTheme::ApplyTheme();
        return panda::JSValueRef::Undefined(vm);
    }

    if (paramArg->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> builderFunc = paramArg->ToObject(vm);
        RefPtr<NG::UINode> customNode;
        {
            ViewStackModel::GetInstance()->NewScope();
            panda::TryCatch trycatch(vm);
            auto func = panda::CopyableGlobal(vm, builderFunc);
            auto result = builderFunc->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            customNode = AceType::DynamicCast<NG::UINode>(ViewStackModel::GetInstance()->Finish());
        }
        CHECK_NULL_RETURN(customNode, panda::JSValueRef::Undefined(vm));
        auto customNodeHandle = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(customNode));
        menuItemModifier->createWithCustomNode(customNodeHandle);
    } else {
        auto menuItemObj = paramArg->ToObject(vm);

        MenuItemParseResult parseResult;
        ArkUIMenuItemOptions menuItemOptions = {};

        ParseMenuItemOptionsResource(vm, menuItemObj, menuItemOptions, parseResult);

        auto builder = menuItemObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "builder"));
        if (!builder.IsEmpty() && builder->IsFunction(vm)) {
            panda::Local<panda::FunctionRef> subBuilderFunc = builder->ToObject(vm);
            auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            parseResult.buildFunc = [vm, func = panda::CopyableGlobal(vm, subBuilderFunc), node = targetNode]() {
                panda::LocalScope pandaScope(vm);
                panda::TryCatch trycatch(vm);
                PipelineContext::SetCallBackNode(node);
                auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            };
            menuItemOptions.buildFunc = reinterpret_cast<void*>(&parseResult.buildFunc);
        }
        menuItemModifier->createWithOptions(&menuItemOptions);
    }
    JSMenuItemTheme::ApplyTheme();
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG