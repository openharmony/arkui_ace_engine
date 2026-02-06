/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/menu/bridge/menu/arkts_native_menu_bridge.h"

#include "bridge/declarative_frontend/ark_theme/theme_apply/js_menu_theme.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NG {
namespace {
const std::string FORMAT_FONT = "%s|%s|%s";
const std::string DEFAULT_ERR_CODE = "-1";
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int COUNT_PROP = 4;
constexpr uint32_t TRANSPARENT_COLOR = 0x00000000;
constexpr uint32_t FOREGROUND_COLOR = 0x00000001;
const Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };

struct RadiusParseParams {
    std::vector<ArkUI_Float32> radiusValues;
    std::vector<int32_t> radiusUnits;
    std::vector<void*> resObjs;
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

bool ParseMenuDividerOptions(EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, const ArkUIMenuModifier* menuModifier,
    std::vector<Local<JSValueRef>>& args, bool isGroupDivider)
{
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, false);
    bool isJsView = IsJsView(firstArg, vm);
    if (isJsView) {
        Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
        if (secondArg->IsObject(vm)) {
            auto secondObj = secondArg->ToObject(vm);
            args[NUM_0] = secondObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "strokeWidth"));
            args[NUM_1] = secondObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "color"));
            args[NUM_2] = secondObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "startMargin"));
            args[NUM_3] = secondObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "endMargin"));
            args[NUM_4] = secondObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "mode"));
        }
    } else {
        args[NUM_0] = runtimeCallInfo->GetCallArgRef(NUM_1);
        args[NUM_1] = runtimeCallInfo->GetCallArgRef(NUM_2);
        args[NUM_2] = runtimeCallInfo->GetCallArgRef(NUM_3);
        args[NUM_3] = runtimeCallInfo->GetCallArgRef(NUM_4);
        args[NUM_4] = runtimeCallInfo->GetCallArgRef(NUM_5);
        if (args[NUM_0]->IsUndefined() && args[NUM_1]->IsUndefined() && args[NUM_2]->IsUndefined() &&
            args[NUM_3]->IsUndefined() && args[NUM_4]->IsUndefined()) {
            if (isGroupDivider) {
                menuModifier->resetMenuItemGroupDivider(nativeNode);
            } else {
                menuModifier->resetMenuItemDivider(nativeNode);
            }
            return false;
        }
    }
    return true;
}

ArkUIMenuDividerOptions BuildMenuDividerOptions(bool isJsView, bool isGroupDivider)
{
    ArkUIMenuDividerOptions dividerOptions;
    dividerOptions.mode = 0;
    if (isJsView) {
        if (isGroupDivider) {
            dividerOptions.strokeWidth = { 0.0f, static_cast<int32_t>(DimensionUnit::INVALID) };
            dividerOptions.color = FOREGROUND_COLOR;
        } else {
            dividerOptions.strokeWidth = { 0.0f, static_cast<int32_t>(DimensionUnit::VP) };
            dividerOptions.color = TRANSPARENT_COLOR;
        }
        dividerOptions.startMargin = { 0.0f, static_cast<int32_t>(DimensionUnit::VP) };
        dividerOptions.endMargin = { 0.0f, static_cast<int32_t>(DimensionUnit::VP) };
    } else {
        dividerOptions.strokeWidth = { 0.0f, static_cast<int32_t>(DimensionUnit::PX) };
        dividerOptions.color = TRANSPARENT_COLOR;
        dividerOptions.startMargin = { 0.0f, static_cast<int32_t>(DimensionUnit::PX) };
        dividerOptions.endMargin = { 0.0f, static_cast<int32_t>(DimensionUnit::PX) };
    }
    return dividerOptions;
}

void ParseMenuDividerStrokeWidth(EcmaVM* vm, std::vector<Local<JSValueRef>>& args,
    ArkUIMenuDividerOptions& dividerOptions, bool isJsView, bool isGroupDivider)
{
    CalcDimension strokeWidth;
    if (isJsView) {
        if (isGroupDivider) {
            if (!ArkTSUtils::ParseJsLengthMetrics(vm, args[NUM_0], strokeWidth)) {
                strokeWidth.Reset();
                strokeWidth.SetUnit(DimensionUnit::INVALID);
            }
            if (strokeWidth.IsNegative() || strokeWidth.Unit() < DimensionUnit::PX ||
                strokeWidth.Unit() > DimensionUnit::LPX) {
                strokeWidth.Reset();
                strokeWidth.SetUnit(DimensionUnit::INVALID);
            }
        } else {
            if (!ArkTSUtils::ParseJsLengthMetrics(vm, args[NUM_0], strokeWidth)) {
                strokeWidth.Reset();
                strokeWidth.SetUnit(dividerOptions.mode == 1 ? DimensionUnit::INVALID : DimensionUnit::PX);
            }
            if (strokeWidth.IsNegative()) {
                strokeWidth.Reset();
                strokeWidth.SetUnit(dividerOptions.mode == 1 ? DimensionUnit::INVALID : DimensionUnit::PX);
            }
        }
    } else {
        if (!ArkTSUtils::ParseJsLengthMetrics(vm, args[NUM_0], strokeWidth)) {
            strokeWidth = Dimension(0.0);
        }
    }
    dividerOptions.strokeWidth.value = strokeWidth.Value();
    dividerOptions.strokeWidth.units = static_cast<int32_t>(strokeWidth.Unit());
}

void ParseMenuDividerColor(EcmaVM* vm, std::vector<Local<JSValueRef>>& args, ArkUIMenuDividerOptions& dividerOptions,
    ArkUINodeHandle nativeNode, RefPtr<ResourceObject>& colorResObj)
{
    Color color;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::ParseJsColorAlpha(vm, args[NUM_1], color, colorResObj, nodeInfo)) {
        dividerOptions.color = color.GetValue();
    }
}

void ParseMenuDividerStartMargin(EcmaVM* vm, std::vector<Local<JSValueRef>>& args,
    ArkUIMenuDividerOptions& dividerOptions, bool isJsView, bool isGroupDivider)
{
    CalcDimension startMargin;
    if (isJsView) {
        if (isGroupDivider) {
            if (!ArkTSUtils::ParseJsLengthMetrics(vm, args[NUM_2], startMargin)) {
                startMargin.Reset();
                startMargin.SetUnit(DimensionUnit::INVALID);
            }
            if (startMargin.IsNegative() || startMargin.Unit() < DimensionUnit::PX ||
                startMargin.Unit() > DimensionUnit::LPX) {
                startMargin.Reset();
                startMargin.SetUnit(DimensionUnit::INVALID);
            }
        } else {
            if (!ArkTSUtils::ParseJsLengthMetrics(vm, args[NUM_2], startMargin)) {
                startMargin.Reset();
                startMargin.SetUnit(dividerOptions.mode == 1 ? DimensionUnit::INVALID : DimensionUnit::PX);
            }
            if (startMargin.IsNegative()) {
                startMargin.Reset();
                startMargin.SetUnit(dividerOptions.mode == 1 ? DimensionUnit::INVALID : DimensionUnit::PX);
            }
        }
    } else {
        if (!ArkTSUtils::ParseJsLengthMetrics(vm, args[NUM_2], startMargin)) {
            startMargin = Dimension(0.0);
        }
    }
    dividerOptions.startMargin.value = startMargin.Value();
    dividerOptions.startMargin.units = static_cast<int32_t>(startMargin.Unit());
}

void ParseMenuDividerEndMargin(EcmaVM* vm, std::vector<Local<JSValueRef>>& args,
    ArkUIMenuDividerOptions& dividerOptions, bool isJsView, bool isGroupDivider)
{
    CalcDimension endMargin;
    if (isJsView) {
        if (isGroupDivider) {
            if (!ArkTSUtils::ParseJsLengthMetrics(vm, args[NUM_3], endMargin)) {
                endMargin.Reset();
                endMargin.SetUnit(DimensionUnit::INVALID);
            }
            if (endMargin.IsNegative() || endMargin.Unit() < DimensionUnit::PX ||
                endMargin.Unit() > DimensionUnit::LPX) {
                endMargin.Reset();
                endMargin.SetUnit(DimensionUnit::INVALID);
            }
        } else {
            if (!ArkTSUtils::ParseJsLengthMetrics(vm, args[NUM_3], endMargin)) {
                endMargin.Reset();
                endMargin.SetUnit(dividerOptions.mode == 1 ? DimensionUnit::INVALID : DimensionUnit::PX);
            }
            if (endMargin.IsNegative()) {
                endMargin.Reset();
                endMargin.SetUnit(dividerOptions.mode == 1 ? DimensionUnit::INVALID : DimensionUnit::PX);
            }
        }
    } else {
        if (!ArkTSUtils::ParseJsLengthMetrics(vm, args[NUM_3], endMargin)) {
            endMargin = Dimension(0.0);
        }
    }
    dividerOptions.endMargin.value = endMargin.Value();
    dividerOptions.endMargin.units = static_cast<int32_t>(endMargin.Unit());
}

void ParseMenuDividerMode(EcmaVM* vm, std::vector<Local<JSValueRef>>& args, ArkUIMenuDividerOptions& dividerOptions)
{
    if (args[NUM_4]->IsNumber() && args[NUM_4]->Int32Value(vm) == 1) {
        dividerOptions.mode = 1;
    }
}

ArkUINativeModuleValue SetMenuDivider(ArkUIRuntimeCallInfo* runtimeCallInfo, bool isGroupDivider)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuModifier = nodeModifiers->getMenuModifier();
    CHECK_NULL_RETURN(menuModifier, panda::JSValueRef::Undefined(vm));
    std::vector<Local<JSValueRef>> args(NUM_5, panda::JSValueRef::Undefined(vm));
    // 0: index of strokeWidth value, 1: index of color value, 2: index of startMargin value,
    // 3: index of endMargin value, 4: index of mode value
    bool isJsView = IsJsView(firstArg, vm);
    CHECK_EQUAL_RETURN(ParseMenuDividerOptions(vm, runtimeCallInfo, menuModifier, args, isGroupDivider), false,
        panda::JSValueRef::Undefined(vm));
    RefPtr<ResourceObject> colorResObj;
    ArkUIMenuDividerOptions dividerOptions = BuildMenuDividerOptions(isJsView, isGroupDivider);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto isNeedParseOptions = !(isJsView && !secondArg->IsObject(vm));
    if (isNeedParseOptions) {
        ParseMenuDividerMode(vm, args, dividerOptions);
        ParseMenuDividerStrokeWidth(vm, args, dividerOptions, isJsView, isGroupDivider);
        ParseMenuDividerStartMargin(vm, args, dividerOptions, isJsView, isGroupDivider);
        ParseMenuDividerEndMargin(vm, args, dividerOptions, isJsView, isGroupDivider);
        ParseMenuDividerColor(vm, args, dividerOptions, nativeNode, colorResObj);
    }
    auto colorRawPtr = AceType::RawPtr(colorResObj);
    if (isGroupDivider) {
        menuModifier->setMenuItemGroupDividerWithResource(nativeNode, &dividerOptions, colorRawPtr);
    } else {
        menuModifier->setMenuItemDividerWithResource(nativeNode, &dividerOptions, colorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ResetMenuDivider(ArkUIRuntimeCallInfo* runtimeCallInfo, bool isGroupDivider)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuModifier = nodeModifiers->getMenuModifier();
    CHECK_NULL_RETURN(menuModifier, panda::JSValueRef::Undefined(vm));
    if (isGroupDivider) {
        menuModifier->resetMenuItemGroupDivider(nativeNode);
    } else {
        menuModifier->resetMenuItemDivider(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

bool ParseFontOptions(EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUINodeHandle nativeNode, bool isJsView,
    std::vector<Local<JSValueRef>>& args)
{
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, false);
    auto menuModifier = nodeModifiers->getMenuModifier();
    CHECK_NULL_RETURN(menuModifier, false);
    if (isJsView) {
        Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
        if (secondArg->IsObject(vm)) {
            auto obj = secondArg->ToObject(vm);
            args[NUM_0] = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "size"));
            args[NUM_1] = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "weight"));
            args[NUM_2] = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "family"));
            args[NUM_3] = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "style"));
        } else {
            if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE)) {
                menuModifier->resetFont(nativeNode);
            }
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
        menuModifier->resetFont(nativeNode);
        return false;
    }
    return true;
}

void SetFontOptions(EcmaVM* vm, std::vector<Local<JSValueRef>>& args, ArkUIMenuFontOptions& menuFontOptions,
    RefPtr<ResourceObject>& sizeResObj)
{
    CalcDimension size;
    if (!ArkTSUtils::ParseJsDimensionFp(vm, args[NUM_0], size, sizeResObj, false)) {
        size = Dimension(0.0);
    }
    menuFontOptions.size.value = size.Value();
    menuFontOptions.size.units = static_cast<int32_t>(size.Unit());
    menuFontOptions.sizeRawPtr = AceType::RawPtr(sizeResObj);

    std::string weight = DEFAULT_ERR_CODE;
    if (args[NUM_1]->IsNumber()) {
        weight = std::to_string(args[NUM_1]->Int32Value(vm));
    } else {
        if (!ArkTSUtils::ParseJsString(vm, args[NUM_1], weight) || weight.empty()) {
            weight = DEFAULT_ERR_CODE;
        }
    }
    menuFontOptions.weight = static_cast<int32_t>(Framework::ConvertStrToFontWeight(weight));

    int32_t style = args[NUM_3]->IsNumber() ? args[NUM_3]->Int32Value(vm) : -1;
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        menuFontOptions.style = style;
    } else {
        menuFontOptions.style = static_cast<int32_t>(DEFAULT_FONT_STYLE);
    }
}

void SetFontFamily(EcmaVM* vm, bool isJsView, std::vector<Local<JSValueRef>>& args,
    ArkUIMenuFontOptions& menuFontOptions, RefPtr<ResourceObject>& familyResObj)
{
    if (isJsView && !args[NUM_2]->IsString(vm) && !args[NUM_2]->IsObject(vm)) {
        menuFontOptions.family = nullptr;
        menuFontOptions.familyRawPtr = AceType::RawPtr(familyResObj);
    } else {
        std::string family;
        if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, args[NUM_2], family, familyResObj) || family.empty()) {
            family = DEFAULT_ERR_CODE;
        }
        menuFontOptions.family = family.c_str();
        menuFontOptions.familyRawPtr = AceType::RawPtr(familyResObj);
    }
}

void SetRadiusResObjs(std::vector<void*>& resObjs, RefPtr<ResourceObject>& topLeftResObj,
    RefPtr<ResourceObject>& topRightResObj, RefPtr<ResourceObject>& bottomLeftResObj,
    RefPtr<ResourceObject>& bottomRightResObj)
{
    if (topLeftResObj) {
        topLeftResObj->IncRefCount();
    }
    if (topRightResObj) {
        topRightResObj->IncRefCount();
    }
    if (bottomLeftResObj) {
        bottomLeftResObj->IncRefCount();
    }
    if (bottomRightResObj) {
        bottomRightResObj->IncRefCount();
    }
    resObjs.push_back(AceType::RawPtr(topLeftResObj));
    resObjs.push_back(AceType::RawPtr(topRightResObj));
    resObjs.push_back(AceType::RawPtr(bottomLeftResObj));
    resObjs.push_back(AceType::RawPtr(bottomRightResObj));
}

void SetRadiusValues(std::vector<ArkUI_Float32>& radiusValues, CalcDimension topLeft, CalcDimension topRight,
    CalcDimension bottomLeft, CalcDimension bottomRight)
{
    radiusValues.push_back(topLeft.Value());
    radiusValues.push_back(topRight.Value());
    radiusValues.push_back(bottomLeft.Value());
    radiusValues.push_back(bottomRight.Value());
}

void SetRadiusUnits(std::vector<int32_t>& radiusUnits, CalcDimension topLeft, CalcDimension topRight,
    CalcDimension bottomLeft, CalcDimension bottomRight)
{
    radiusUnits.push_back(static_cast<int32_t>(topLeft.Unit()));
    radiusUnits.push_back(static_cast<int32_t>(topRight.Unit()));
    radiusUnits.push_back(static_cast<int32_t>(bottomLeft.Unit()));
    radiusUnits.push_back(static_cast<int32_t>(bottomRight.Unit()));
}

bool ParseRadiusOptions(
    EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, bool isJsView, std::vector<Local<JSValueRef>>& args)
{
    if (isJsView) {
        Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
        if (secondArg->IsNumber() || secondArg->IsString(vm)) {
            args[NUM_0] = secondArg;
            args[NUM_1] = secondArg;
            args[NUM_2] = secondArg;
            args[NUM_3] = secondArg;
            args[NUM_4] = panda::JSValueRef::False(vm);
        }
        if (secondArg->IsObject(vm)) {
            auto secondObj = secondArg->ToObject(vm);
            args[NUM_0] = secondObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "topLeft"));
            args[NUM_1] = secondObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "topRight"));
            args[NUM_2] = secondObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "bottomLeft"));
            args[NUM_3] = secondObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "bottomRight"));
            if (args[NUM_0]->IsUndefined() && args[NUM_1]->IsUndefined() && args[NUM_2]->IsUndefined() &&
                args[NUM_3]->IsUndefined()) {
                return false;
            } else {
                args[NUM_4] = panda::JSValueRef::True(vm);
            }
        }
    } else {
        args[NUM_0] = runtimeCallInfo->GetCallArgRef(NUM_1);
        args[NUM_1] = runtimeCallInfo->GetCallArgRef(NUM_2);
        args[NUM_2] = runtimeCallInfo->GetCallArgRef(NUM_3);
        args[NUM_3] = runtimeCallInfo->GetCallArgRef(NUM_4);
        args[NUM_4] = runtimeCallInfo->GetCallArgRef(NUM_5);
    }
    if (args[NUM_0]->IsUndefined() && args[NUM_1]->IsUndefined() && args[NUM_2]->IsUndefined() &&
        args[NUM_3]->IsUndefined()) {
        return false;
    }
    return true;
}

bool ParseRadius(EcmaVM* vm, ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUINodeHandle nativeNode, bool isJsView,
    RadiusParseParams& radiusParseParams)
{
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, false);
    auto menuModifier = nodeModifiers->getMenuModifier();
    CHECK_NULL_RETURN(menuModifier, false);
    std::vector<Local<JSValueRef>> args(NUM_5, panda::JSValueRef::Undefined(vm));
    // 0: index of top left value, 1: index of top right value, 2: index of bottom left value,
    // 3: index of bottom right value, 4: check is object radius
    if (!ParseRadiusOptions(vm, runtimeCallInfo, isJsView, args)) {
        menuModifier->resetRadius(nativeNode);
        return false;
    }
    CalcDimension topLeft;
    CalcDimension topRight;
    CalcDimension bottomLeft;
    CalcDimension bottomRight;
    RefPtr<ResourceObject> topLeftResObj;
    RefPtr<ResourceObject> topRightResObj;
    RefPtr<ResourceObject> bottomLeftResObj;
    RefPtr<ResourceObject> bottomRightResObj;
    if (args[NUM_4]->IsBoolean() && !args[NUM_4]->ToBoolean(vm)->Value()) {
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, args[NUM_0], topLeft, true)) {
            menuModifier->resetRadius(nativeNode);
            return false;
        }
        if (LessNotEqual(topLeft.Value(), 0.0)) {
            menuModifier->resetRadius(nativeNode);
            return false;
        }
        topRight = topLeft;
        bottomLeft = topLeft;
        bottomRight = topLeft;
    } else {
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, args[NUM_0], topLeft, topLeftResObj, true)) {
            topLeft = CalcDimension(0.0, DimensionUnit::VP);
        }
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, args[NUM_1], topRight, topRightResObj, true)) {
            topRight = CalcDimension(0.0, DimensionUnit::VP);
        }
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, args[NUM_2], bottomLeft, bottomLeftResObj, true)) {
            bottomLeft = CalcDimension(0.0, DimensionUnit::VP);
        }
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, args[NUM_3], bottomRight, bottomRightResObj, true)) {
            bottomRight = CalcDimension(0.0, DimensionUnit::VP);
        }
    }
    SetRadiusValues(radiusParseParams.radiusValues, topLeft, topRight, bottomLeft, bottomRight);
    SetRadiusUnits(radiusParseParams.radiusUnits, topLeft, topRight, bottomLeft, bottomRight);
    SetRadiusResObjs(radiusParseParams.resObjs, topLeftResObj, topRightResObj, bottomLeftResObj, bottomRightResObj);
    return true;
}
} // namespace

ArkUINativeModuleValue MenuBridge::SetMenuFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    bool isJsView = IsJsView(firstArg, vm);
    if (isJsView && argsNumber < NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuModifier = nodeModifiers->getMenuModifier();
    CHECK_NULL_RETURN(menuModifier, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, colorResObj, nodeInfo)) {
        menuModifier->resetMenuFontColor(nativeNode);
    } else {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        menuModifier->setMenuFontColor(nativeNode, color.GetValue(), colorRawPtr);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::ResetMenuFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuModifier = nodeModifiers->getMenuModifier();
    CHECK_NULL_RETURN(menuModifier, panda::JSValueRef::Undefined(vm));
    menuModifier->resetMenuFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::SetFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuModifier = nodeModifiers->getMenuModifier();
    CHECK_NULL_RETURN(menuModifier, panda::JSValueRef::Undefined(vm));
    std::vector<Local<JSValueRef>> args(NUM_4, panda::JSValueRef::Undefined(vm));
    // 0: index of font size value, 1: index of font weight value, 2: index of font family value,
    // 3: index of font style value
    bool isJsView = IsJsView(firstArg, vm);
    CHECK_EQUAL_RETURN(
        ParseFontOptions(vm, runtimeCallInfo, nativeNode, isJsView, args), false, panda::JSValueRef::Undefined(vm));
    ArkUIMenuFontOptions menuFontOptions;
    RefPtr<ResourceObject> sizeResObj;
    RefPtr<ResourceObject> familyResObj;
    SetFontOptions(vm, args, menuFontOptions, sizeResObj);
    SetFontFamily(vm, isJsView, args, menuFontOptions, familyResObj);
    menuModifier->setFont(nativeNode, &menuFontOptions);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::ResetFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuModifier = nodeModifiers->getMenuModifier();
    CHECK_NULL_RETURN(menuModifier, panda::JSValueRef::Undefined(vm));
    menuModifier->resetFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}


ArkUINativeModuleValue MenuBridge::SetRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = IsJsView(firstArg, vm);
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (isJsView && argsNumber < NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuModifier = nodeModifiers->getMenuModifier();
    CHECK_NULL_RETURN(menuModifier, panda::JSValueRef::Undefined(vm));
    RadiusParseParams radiusParseParams;
    if (!ParseRadius(vm, runtimeCallInfo, nativeNode, isJsView, radiusParseParams)) {
        return panda::JSValueRef::Undefined(vm);
    }
    menuModifier->setRadius(nativeNode, radiusParseParams.radiusValues.data(), radiusParseParams.radiusUnits.data(),
        radiusParseParams.resObjs.data(), COUNT_PROP);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::ResetRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuModifier = nodeModifiers->getMenuModifier();
    CHECK_NULL_RETURN(menuModifier, panda::JSValueRef::Undefined(vm));
    menuModifier->resetRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::SetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    bool isJsView = IsJsView(firstArg, vm);
    if (isJsView && argsNumber < NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuModifier = nodeModifiers->getMenuModifier();
    CHECK_NULL_RETURN(menuModifier, panda::JSValueRef::Undefined(vm));

    if (isJsView && widthArg->IsObject(vm)) {
        auto obj = widthArg->ToObject(vm);
        auto layoutPolicy = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id_"));
        if (layoutPolicy->IsString(vm)) {
            auto commonModifier = nodeModifiers->getCommonModifier();
            CHECK_NULL_RETURN(commonModifier, panda::JSValueRef::Undefined(vm));
            nativeNode = reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
            commonModifier->clearWidthOrHeight(nativeNode, true);
            auto policy = CommonBridge::ParseLayoutPolicy(layoutPolicy->ToString(vm)->ToString(vm));
            commonModifier->setWidthLayoutPolicy(nativeNode, static_cast<ArkUI_Int32>(policy) - NUM_1);
            return panda::JSValueRef::Undefined(vm);
        }
    }

    CalcDimension width;
    RefPtr<ResourceObject> resObj;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, widthArg, width, resObj, false)) {
        menuModifier->resetMenuWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto resPtr = AceType::RawPtr(resObj);
    menuModifier->setMenuWidthWithResource(nativeNode, width.Value(), static_cast<int32_t>(width.Unit()), resPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::ResetWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuModifier = nodeModifiers->getMenuModifier();
    CHECK_NULL_RETURN(menuModifier, panda::JSValueRef::Undefined(vm));
    menuModifier->resetMenuWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::SetMenuItemDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return SetMenuDivider(runtimeCallInfo, false);
}

ArkUINativeModuleValue MenuBridge::ResetMenuItemDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return ResetMenuDivider(runtimeCallInfo, false);
}

ArkUINativeModuleValue MenuBridge::SetMenuItemGroupDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return SetMenuDivider(runtimeCallInfo, true);
}

ArkUINativeModuleValue MenuBridge::ResetMenuItemGroupDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    return ResetMenuDivider(runtimeCallInfo, true);
}

ArkUINativeModuleValue MenuBridge::SetSubMenuExpandingMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuModifier = nodeModifiers->getMenuModifier();
    CHECK_NULL_RETURN(menuModifier, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber()) {
        menuModifier->setSubMenuExpandingMode(nativeNode, secondArg->ToNumber(vm)->Value());
    } else {
        bool isJsView = IsJsView(firstArg, vm);
        if (!isJsView) {
            menuModifier->resetSubMenuExpandingMode(nativeNode);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::ResetSubMenuExpandingMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuModifier = nodeModifiers->getMenuModifier();
    CHECK_NULL_RETURN(menuModifier, panda::JSValueRef::Undefined(vm));
    menuModifier->resetSubMenuExpandingMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::SetSubMenuExpandSymbol(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuModifier = nodeModifiers->getMenuModifier();
    CHECK_NULL_RETURN(menuModifier, panda::JSValueRef::Undefined(vm));
    std::function<void(WeakPtr<NG::FrameNode>)> symbolApply;
    if (secondArg->IsObject(vm)) {
        ArkTSUtils::SetSymbolOptionApply(vm, symbolApply, secondArg);
        menuModifier->setSubMenuExpandSymbol(nativeNode, reinterpret_cast<void*>(&symbolApply));
    } else {
        bool isJsView = IsJsView(firstArg, vm);
        if (!isJsView) {
            menuModifier->resetSubMenuExpandSymbol(nativeNode);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::ResetSubMenuExpandSymbol(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuModifier = nodeModifiers->getMenuModifier();
    CHECK_NULL_RETURN(menuModifier, panda::JSValueRef::Undefined(vm));
    menuModifier->resetSubMenuExpandSymbol(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::SetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber != NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuModifier = nodeModifiers->getMenuModifier();
    CHECK_NULL_RETURN(menuModifier, panda::JSValueRef::Undefined(vm));
    CalcDimension fontSize;
    RefPtr<ResourceObject> fontSizeResObj;
    bool isJsView = IsJsView(firstArg, vm);
    if (!ArkTSUtils::ParseJsDimensionFp(vm, fontSizeArg, fontSize, fontSizeResObj) || fontSize.IsNegative()) {
        if (!isJsView) {
            menuModifier->resetMenuFontSize(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    } else {
        auto fontSizeRawPtr = AceType::RawPtr(fontSizeResObj);
        menuModifier->setMenuFontSize(nativeNode, fontSize.Value(), static_cast<int>(fontSize.Unit()), fontSizeRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::ResetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuModifier = nodeModifiers->getMenuModifier();
    CHECK_NULL_RETURN(menuModifier, panda::JSValueRef::Undefined(vm));
    menuModifier->resetMenuFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuBridge::CreateMenu(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuModifier = nodeModifiers->getMenuModifier();
    CHECK_NULL_RETURN(menuModifier, panda::JSValueRef::Undefined(vm));
    menuModifier->createMenu();
    Framework::JSMenuTheme::ApplyTheme();
    return panda::JSValueRef::Undefined(vm);
}

void MenuBridge::RegisterMenuAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "create",
        "setMenuFontColor",
        "resetMenuFontColor",
        "setFont",
        "resetFont",
        "setRadius",
        "resetRadius",
        "setWidth",
        "resetWidth",
        "setMenuItemDivider",
        "resetMenuItemDivider",
        "setMenuItemGroupDivider",
        "resetMenuItemGroupDivider",
        "setSubMenuExpandingMode",
        "resetSubMenuExpandingMode",
        "setSubMenuExpandSymbol",
        "resetSubMenuExpandSymbol",
        "setFontSize",
        "resetFontSize",
    };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::CreateMenu),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::SetMenuFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::ResetMenuFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::SetFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::ResetFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::SetRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::ResetRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::SetWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::ResetWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::SetMenuItemDivider),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::ResetMenuItemDivider),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::SetMenuItemGroupDivider),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::ResetMenuItemGroupDivider),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::SetSubMenuExpandingMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::ResetSubMenuExpandingMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::SetSubMenuExpandSymbol),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::ResetSubMenuExpandSymbol),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::SetFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::ResetFontSize),
    };
    auto menu = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "menu"), menu);
}

} // namespace OHOS::Ace::NG
