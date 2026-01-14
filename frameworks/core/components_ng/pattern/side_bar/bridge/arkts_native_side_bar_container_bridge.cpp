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
#include "core/components_ng/pattern/side_bar/bridge/arkts_native_side_bar_container_bridge.h"

#include "jsnapi_expo.h"

#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_model_ng.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr uint32_t DEFAULT_SIDE_BAR_DIVIDER_COLOR = 0x08000000;
const CalcDimension DEFAULT_MAX_SIDE_BAR_WIDTH(280.0, DimensionUnit::VP);
const CalcDimension DEFAULT_SIDE_BAR_MIN_CONTENT_WIDTH(360.0, DimensionUnit::VP);
const Dimension DEFAULT_CONTROL_BUTTON_WIDTH = 32.0_vp;
const Dimension DEFAULT_CONTROL_BUTTON_WIDTH_V10 = 24.0_vp;
const Dimension DEFAULT_CONTROL_BUTTON_HEIGHT = 32.0_vp;
const Dimension DEFAULT_CONTROL_BUTTON_HEIGHT_V10 = 24.0_vp;
constexpr Dimension DEFAULT_CONTROL_BUTTON_LEFT = 16.0_vp;
constexpr Dimension DEFAULT_CONTROL_BUTTON_TOP = 48.0_vp;
static Dimension DEFAULT_SIDE_BAR_WIDTH = 200.0_vp;
static Dimension DEFAULT_MIN_SIDE_BAR_WIDTH = 200.0_vp;
constexpr Dimension DEFAULT_DIVIDER_STROKE_WIDTH = 1.0_vp;
constexpr Color DEFAULT_DIVIDER_COLOR = Color(0x08000000);
constexpr Dimension DEFAULT_DIVIDER_START_MARGIN = 0.0_vp;
constexpr Dimension DEFAULT_DIVIDER_END_MARGIN = 0.0_vp;
constexpr Dimension ZERO_DIVIDER_STROKE_WIDTH = 0.0_vp;

namespace {
FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

void ParseAndSetWidth(const ArkUIRuntimeCallInfo* runtimeCallInfo, WidthType widthType)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc < NUM_2) {
        return;
    }
    Local<JSValueRef> sideBarWidthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CalcDimension value;
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        DEFAULT_SIDE_BAR_WIDTH = 240.0_vp;
        DEFAULT_MIN_SIDE_BAR_WIDTH = 240.0_vp;
    }

    RefPtr<ResourceObject> valueResObj;
    auto isValid = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)
                       ? ArkTSUtils::ParseJsDimensionVpNG(vm, sideBarWidthArg, value, valueResObj)
                       : ArkTSUtils::ParseJsDimensionVp(vm, sideBarWidthArg, value, valueResObj);
    if (!isValid) {
        switch (widthType) {
            case WidthType::SIDEBAR_WIDTH:
                value = DEFAULT_SIDE_BAR_WIDTH;
                break;
            case WidthType::MIN_SIDEBAR_WIDTH:
                value = DEFAULT_MIN_SIDE_BAR_WIDTH;
                break;
            case WidthType::MAX_SIDEBAR_WIDTH:
                value = DEFAULT_MAX_SIDE_BAR_WIDTH;
                break;
            default:
                break;
        }
    }
    if (SystemProperties::ConfigChangePerform() && valueResObj) {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->parseAndSetWidthObj(
            static_cast<ArkUIWidthType>(widthType), AceType::RawPtr(valueResObj));
        return;
    }
    GetArkUINodeModifiers()->getSideBarContainerModifier()->parseAndSetWidth(
        static_cast<ArkUIWidthType>(widthType), &value, false);
}

void ParseSideBarWidthObject(
    const ArkUIRuntimeCallInfo* runtimeCallInfo, const Local<JSValueRef>& callbackArg, bool isNumber)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(callbackArg->IsFunction(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    std::function<void(const Dimension&)> onChangeEvent = [vm, func = panda::CopyableGlobal(vm, func), node = frameNode,
                                                              useNumber = isNumber](const Dimension& sideBarWidth) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(node));
        panda::Local<panda::PrimitiveRef> newParam;
        if (useNumber) {
            newParam = panda::NumberRef::New(vm, sideBarWidth.ConvertToVp());
        } else {
            auto strValue = sideBarWidth.ToString();
            newParam = panda::StringRef::NewFromUtf8(vm, strValue.c_str(), static_cast<int>(strValue.size()));
        }
        panda::Local<panda::JSValueRef> params[1] = { newParam };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getSideBarContainerModifier()->setOnSideBarWidthChangeEvent(
        reinterpret_cast<void*>(&onChangeEvent));
}

} // namespace

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

ArkUINativeModuleValue SideBarContainerBridge::SetSideBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> sideBarWidthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = nativeNodeArg->IsBoolean() && nativeNodeArg->ToBoolean(vm)->Value();
    if (isJsView) {
        if (sideBarWidthArg->IsObject(vm)) {
            auto callbackObj = sideBarWidthArg->ToObject(vm);
            CalcDimension value;
            auto sideBarWidthValue = callbackObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
            auto sideBarWidthCallbackValue = callbackObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "$value"));
            auto isValid = ArkTSUtils::ParseJsDimensionVpNG(vm, sideBarWidthValue, value);
            bool isNumber = sideBarWidthValue->IsNumber();
            if (isValid && sideBarWidthCallbackValue->IsFunction(vm)) {
                GetArkUINodeModifiers()->getSideBarContainerModifier()->parseAndSetWidth(
                    ArkUIWidthType::SIDEBAR_WIDTH, &value, true);
                ParseSideBarWidthObject(runtimeCallInfo, sideBarWidthCallbackValue, isNumber);
                return panda::JSValueRef::Undefined(vm);
            }
        }
        ParseAndSetWidth(runtimeCallInfo, WidthType::SIDEBAR_WIDTH);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension sideBarWidth;
    RefPtr<ResourceObject> sideBarWidthResObj;
    if (ArkTSUtils::ParseJsDimensionNG(
        vm, sideBarWidthArg, sideBarWidth, DimensionUnit::VP, sideBarWidthResObj, true) &&
        sideBarWidth.Value() >= 0) {
        auto widthRawPtr = AceType::RawPtr(sideBarWidthResObj);
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setSideBarWidth(
            nativeNode, sideBarWidth.Value(), static_cast<int32_t>(sideBarWidth.Unit()), widthRawPtr);
    } else {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->resetSideBarWidth(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetSideBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetSideBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetMinSideBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> minSideBarWidthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));

    bool isJsView = nativeNodeArg->IsBoolean() && nativeNodeArg->ToBoolean(vm)->Value();
    if (isJsView) {
        ParseAndSetWidth(runtimeCallInfo, WidthType::MIN_SIDEBAR_WIDTH);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension minSideBarWidth;
    RefPtr<ResourceObject> minSideBarWidthObj;
    if (ArkTSUtils::ParseJsDimensionNG(
        vm, minSideBarWidthArg, minSideBarWidth, DimensionUnit::VP, minSideBarWidthObj, true) &&
        minSideBarWidth.Value() >= 0) {
        auto minWidthRawPtr = AceType::RawPtr(minSideBarWidthObj);
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setMinSideBarWidth(
            nativeNode, minSideBarWidth.Value(), static_cast<int32_t>(minSideBarWidth.Unit()), minWidthRawPtr);
    } else {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->resetMinSideBarWidth(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetMinSideBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetMinSideBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void SetControlButtonIcon(EcmaVM* vm, SideBarControlButtonType iconType, Local<JSValueRef>& icon)
{
    if (icon->IsUndefined() || icon->IsNull()) {
        return;
    }
    std::string iconPath;
    RefPtr<ResourceObject> iconPathResObj;
    auto isStrType = ArkTSUtils::ParseJsMedia(vm, icon, iconPath, iconPathResObj);
    RefPtr<PixelMap> pixMap = nullptr;
#if defined(PIXEL_MAP_SUPPORTED)
    if (!isStrType) {
        pixMap = ArkTSUtils::CreatePixelMapFromNapiValue(vm, icon);
    }
#endif
    bool isNewframework = iconPathResObj && SystemProperties::ConfigChangePerform();
    if (isStrType || pixMap != nullptr) {
        switch (iconType) {
            case SideBarControlButtonType::SHOWN:
                if (isNewframework) {
                    GetArkUINodeModifiers()->getSideBarContainerModifier()->setControlButtonIconInfo(
                        nullptr, AceType::RawPtr(iconPathResObj), !isStrType, AceType::RawPtr(pixMap), NUM_0);
                } else {
                    GetArkUINodeModifiers()->getSideBarContainerModifier()->setControlButtonIconInfo(
                        iconPath.c_str(), nullptr, !isStrType, AceType::RawPtr(pixMap), NUM_0);
                }
                break;
            case SideBarControlButtonType::HIDDEN:
                if (isNewframework) {
                    GetArkUINodeModifiers()->getSideBarContainerModifier()->setControlButtonIconInfo(
                        nullptr, AceType::RawPtr(iconPathResObj), !isStrType, AceType::RawPtr(pixMap), NUM_1);
                } else {
                    GetArkUINodeModifiers()->getSideBarContainerModifier()->setControlButtonIconInfo(
                        iconPath.c_str(), nullptr, !isStrType, AceType::RawPtr(pixMap), NUM_1);
                }
                break;
            case SideBarControlButtonType::SWITCHING:
                if (isNewframework) {
                    GetArkUINodeModifiers()->getSideBarContainerModifier()->setControlButtonIconInfo(
                        nullptr, AceType::RawPtr(iconPathResObj), !isStrType, AceType::RawPtr(pixMap), NUM_2);
                } else {
                    GetArkUINodeModifiers()->getSideBarContainerModifier()->setControlButtonIconInfo(
                        iconPath.c_str(), nullptr, !isStrType, AceType::RawPtr(pixMap), NUM_2);
                }
                break;
            default:
                break;
        }
    }
}

void ParseControlButtonOG(EcmaVM* vm, Local<panda::ObjectRef>& value)
{
    if (!value->IsObject(vm)) {
        return;
    }
    auto width = value->Get(vm, panda::StringRef::NewFromUtf8(vm, "width"));
    auto height = value->Get(vm, panda::StringRef::NewFromUtf8(vm, "height"));
    auto left = value->Get(vm, panda::StringRef::NewFromUtf8(vm, "left"));
    auto top = value->Get(vm, panda::StringRef::NewFromUtf8(vm, "top"));

    if (!width->IsNull() && width->IsNumber()) {
        auto controlButtonWidth = CalcDimension(width->ToNumber(vm)->Value(), DimensionUnit::VP);
        if (LessNotEqual(controlButtonWidth.Value(), 0.0)) {
            controlButtonWidth = DEFAULT_CONTROL_BUTTON_WIDTH;
        }
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setControlButtonLayout(&controlButtonWidth, NUM_0);
    }

    if (!height->IsNull() && height->IsNumber()) {
        auto controlButtonHeight = CalcDimension(height->ToNumber(vm)->Value(), DimensionUnit::VP);
        if (LessNotEqual(controlButtonHeight.Value(), 0.0)) {
            controlButtonHeight = DEFAULT_CONTROL_BUTTON_HEIGHT;
        }
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setControlButtonLayout(&controlButtonHeight, NUM_1);
    }

    if (!left->IsNull() && left->IsNumber()) {
        auto dim = Dimension(left->ToNumber(vm)->Value(), DimensionUnit::VP);
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setControlButtonLayout(&dim, NUM_2);
    }

    if (!top->IsNull() && top->IsNumber()) {
        auto dim = Dimension(top->ToNumber(vm)->Value(), DimensionUnit::VP);
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setControlButtonLayout(&dim, NUM_3);
    }
}

void ParseControlButtonNG(EcmaVM* vm, Local<panda::ObjectRef>& value)
{
    if (!value->IsObject(vm)) {
        return;
    }
    auto width = value->Get(vm, panda::StringRef::NewFromUtf8(vm, "width"));
    auto height = value->Get(vm, panda::StringRef::NewFromUtf8(vm, "height"));
    auto left = value->Get(vm, panda::StringRef::NewFromUtf8(vm, "left"));
    auto top = value->Get(vm, panda::StringRef::NewFromUtf8(vm, "top"));

    auto controlButtonWidth = DEFAULT_CONTROL_BUTTON_WIDTH;
    if (width->IsNumber() && GreatOrEqual(width->ToNumber(vm)->Value(), 0.0)) {
        controlButtonWidth = CalcDimension(width->ToNumber(vm)->Value(), DimensionUnit::VP);
    }
    GetArkUINodeModifiers()->getSideBarContainerModifier()->setControlButtonLayout(&controlButtonWidth, NUM_0);

    auto controlButtonHeight = DEFAULT_CONTROL_BUTTON_HEIGHT;
    if (height->IsNumber() && GreatOrEqual(height->ToNumber(vm)->Value(), 0.0)) {
        controlButtonHeight = CalcDimension(height->ToNumber(vm)->Value(), DimensionUnit::VP);
    }
    GetArkUINodeModifiers()->getSideBarContainerModifier()->setControlButtonLayout(&controlButtonHeight, NUM_1);

    if (left->IsNumber() && GreatOrEqual(left->ToNumber(vm)->Value(), 0.0)) {
        auto controlButtonLeft = CalcDimension(left->ToNumber(vm)->Value(), DimensionUnit::VP);
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setControlButtonLayout(&controlButtonLeft, NUM_2);
    } else {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->resetControlButtonLeft();
    }

    auto controlButtonTop = DEFAULT_CONTROL_BUTTON_TOP;
    if (top->IsNumber() && GreatOrEqual(top->ToNumber(vm)->Value(), 0.0)) {
        controlButtonTop = CalcDimension(top->ToNumber(vm)->Value(), DimensionUnit::VP);
    }
    GetArkUINodeModifiers()->getSideBarContainerModifier()->setControlButtonLayout(&controlButtonTop, NUM_3);
}

void JsControlButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc < NUM_2) {
        return;
    }
    Local<JSValueRef> controlButtonArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetControlButtonIconRes();

    if (controlButtonArg->IsNull() || controlButtonArg->IsUndefined()) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            // controlButton icon set default style and position when input illegal value

            GetArkUINodeModifiers()->getSideBarContainerModifier()->resetControlButtonTwelve();
        }
        return;
    }
    if (controlButtonArg->IsObject(vm)) {
        auto value = controlButtonArg->ToObject(vm);
        if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TEN)) {
            ParseControlButtonOG(vm, value);
        } else {
            ParseControlButtonNG(vm, value);
        }

        auto icons = value->Get(vm, panda::StringRef::NewFromUtf8(vm, "icons"));
        if (icons->IsNull() || icons->IsUndefined()) {
            if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
                // controlButton icon set default style when input illegal value
                GetArkUINodeModifiers()->getSideBarContainerModifier()->resetControlButtonIconInfo();
            }
            return;
        }
        if (icons->IsObject(vm)) {
            auto iconsVal = icons->ToObject(vm);
            auto showIcon = iconsVal->Get(vm, panda::StringRef::NewFromUtf8(vm, "shown"));
            auto switchingIcon = iconsVal->Get(vm, panda::StringRef::NewFromUtf8(vm, "switching"));
            auto hiddenIcon = iconsVal->Get(vm, panda::StringRef::NewFromUtf8(vm, "hidden"));
            SetControlButtonIcon(vm, SideBarControlButtonType::SHOWN, showIcon);
            SetControlButtonIcon(vm, SideBarControlButtonType::HIDDEN, hiddenIcon);
            SetControlButtonIcon(vm, SideBarControlButtonType::SWITCHING, switchingIcon);
        }
    }
}

ArkUINativeModuleValue SideBarContainerBridge::SetControlButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = nativeNodeArg->IsBoolean() && nativeNodeArg->ToBoolean(vm)->Value();
    if (isJsView) {
        JsControlButton(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> leftArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> topArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> widthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> iconsShownArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Local<JSValueRef> iconsHiddenArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    Local<JSValueRef> iconsSwitchingArg = runtimeCallInfo->GetCallArgRef(NUM_7);
    ArkUI_Float32 values[NUM_4];
    if (leftArg->IsNumber() && leftArg->ToNumber(vm)->Value() >= 0) {
        values[NUM_0] = leftArg->ToNumber(vm)->Value();
    } else {
        values[NUM_0] = DEFAULT_CONTROL_BUTTON_LEFT.Value();
    }
    if (topArg->IsNumber() && topArg->ToNumber(vm)->Value() >= 0) {
        values[NUM_1] = topArg->ToNumber(vm)->Value();
    } else {
        values[NUM_1] = DEFAULT_CONTROL_BUTTON_TOP.Value();
    }
    if (widthArg->IsNumber() && widthArg->ToNumber(vm)->Value() >= 0) {
        values[NUM_2] = widthArg->ToNumber(vm)->Value();
    } else {
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            values[NUM_2] = DEFAULT_CONTROL_BUTTON_WIDTH_V10.Value();
        } else {
            values[NUM_2] = DEFAULT_CONTROL_BUTTON_WIDTH.Value();
        }
    }
    if (heightArg->IsNumber() && heightArg->ToNumber(vm)->Value() >= 0) {
        values[NUM_3] = heightArg->ToNumber(vm)->Value();
    } else {
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            values[NUM_3] = DEFAULT_CONTROL_BUTTON_HEIGHT_V10.Value();
        } else {
            values[NUM_3] = DEFAULT_CONTROL_BUTTON_HEIGHT.Value();
        }
    }
    std::string iconsShown;
    std::string iconsHidden;
    std::string iconsSwitching;
    RefPtr<ResourceObject> iconsShownObj;
    RefPtr<ResourceObject> iconsHiddenObj;
    RefPtr<ResourceObject> iconsSwitchingObj;
    struct ArkUIIconsStruct iconsStruct {
        nullptr, nullptr, nullptr
    };
    if (ArkTSUtils::ParseJsMedia(vm, iconsShownArg, iconsShown, iconsShownObj)) {
        iconsStruct.ShowIconInfo = iconsShown.c_str();
    }
    if (ArkTSUtils::ParseJsMedia(vm, iconsHiddenArg, iconsHidden, iconsHiddenObj)) {
        iconsStruct.HiddenIconInfo = iconsHidden.c_str();
    }
    if (ArkTSUtils::ParseJsMedia(vm, iconsSwitchingArg, iconsSwitching, iconsSwitchingObj)) {
        iconsStruct.SwitchingIconInfo = iconsSwitching.c_str();
    }
    auto iconsShownPtr = AceType::RawPtr(iconsShownObj);
    auto iconsHiddenPtr = AceType::RawPtr(iconsHiddenObj);
    auto iconsSwitchingPtr = AceType::RawPtr(iconsSwitchingObj);
    GetArkUINodeModifiers()->getSideBarContainerModifier()->setControlButton(nativeNode, values, NUM_4, &iconsStruct,
        iconsShownPtr, iconsHiddenPtr, iconsSwitchingPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetControlButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetControlButton(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetShowControlButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> showControlButtonArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isShow = true;
    bool isJsView = nativeNodeArg->IsBoolean() && nativeNodeArg->ToBoolean(vm)->Value();
    if (showControlButtonArg->IsBoolean()) {
        isShow = showControlButtonArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setShowControlButton(nativeNode, isShow);
    } else if (!isJsView || Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->resetShowControlButton(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetShowControlButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetShowControlButton(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetAutoHide(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> autoHideArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = nativeNodeArg->IsBoolean() && nativeNodeArg->ToBoolean(vm)->Value();
    if (autoHideArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(autoHideArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setAutoHide(nativeNode, value);
    } else if (!isJsView) {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->resetAutoHide(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetAutoHide(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetAutoHide(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetMaxSideBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> maxSideBarWidthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));

    bool isJsView = nativeNodeArg->IsBoolean() && nativeNodeArg->ToBoolean(vm)->Value();
    if (isJsView) {
        ParseAndSetWidth(runtimeCallInfo, WidthType::MAX_SIDEBAR_WIDTH);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension maxSideBarWidth(DEFAULT_MAX_SIDE_BAR_WIDTH);
    RefPtr<ResourceObject> maxSideBarWidthObj;
    if (ArkTSUtils::ParseJsDimensionNG(
        vm, maxSideBarWidthArg, maxSideBarWidth, DimensionUnit::VP, maxSideBarWidthObj, true) &&
        maxSideBarWidth.Value() >= 0) {
        auto maxSideBarWidthPtr = AceType::RawPtr(maxSideBarWidthObj);
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setSideBarContainerMaxSideBarWidth(
            nativeNode, maxSideBarWidth.Value(), static_cast<int32_t>(maxSideBarWidth.Unit()), maxSideBarWidthPtr);
    } else {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->resetSideBarContainerMaxSideBarWidth(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetMaxSideBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetSideBarContainerMaxSideBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetMinContentWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> minContentWidthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = nativeNodeArg->IsBoolean() && nativeNodeArg->ToBoolean(vm)->Value();
    if (isJsView) {
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
        if (minContentWidthArg->IsNull()) {
            GetArkUINodeModifiers()->getSideBarContainerModifier()->resetSideBarContainerMinContentWidth(nullptr);
            return panda::JSValueRef::Undefined(vm);
        }
        CalcDimension minContentWidth;
        RefPtr<ResourceObject> valueResObj;
        if (!ArkTSUtils::ParseJsDimensionVp(vm, minContentWidthArg, minContentWidth, valueResObj)) {
            GetArkUINodeModifiers()->getSideBarContainerModifier()->resetSideBarContainerMinContentWidth(nullptr);
            return panda::JSValueRef::Undefined(vm);
        }
        if (SystemProperties::ConfigChangePerform() && valueResObj) {
            GetArkUINodeModifiers()->getSideBarContainerModifier()->setSideBarContainerMinContentWidthJs(
                minContentWidth.Value(), static_cast<int32_t>(minContentWidth.Unit()), AceType::RawPtr(valueResObj));
            return panda::JSValueRef::Undefined(vm);
        }
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setSideBarContainerMinContentWidthJs(
            minContentWidth.Value(), static_cast<int32_t>(minContentWidth.Unit()), nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    CalcDimension minContentWidth(DEFAULT_SIDE_BAR_MIN_CONTENT_WIDTH);
    RefPtr<ResourceObject> minContentWidthObj;
    if (ArkTSUtils::ParseJsDimensionNG(
        vm, minContentWidthArg, minContentWidth, DimensionUnit::VP, minContentWidthObj, true) &&
        minContentWidth.Value() >= 0) {
        auto minContentWidthPtr = AceType::RawPtr(minContentWidthObj);
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setSideBarContainerMinContentWidth(
            nativeNode, minContentWidth.Value(), static_cast<int32_t>(minContentWidth.Unit()), minContentWidthPtr);
    } else {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->resetSideBarContainerMinContentWidth(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetMinContentWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetSideBarContainerMinContentWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetSideBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> sideBarPositionArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = nativeNodeArg->IsBoolean() && nativeNodeArg->ToBoolean(vm)->Value();
    int32_t sideBarPosition = static_cast<int32_t>(SideBarPosition::START);
    if (sideBarPositionArg->IsInt()) {
        sideBarPosition = sideBarPositionArg->Int32Value(vm);
    }
    if (sideBarPosition < static_cast<int32_t>(SideBarPosition::START) ||
        sideBarPosition > static_cast<int32_t>(SideBarPosition::END)) {
        if (!isJsView ||
            AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            GetArkUINodeModifiers()->getSideBarContainerModifier()->resetSideBarPosition(nativeNode);
        }
    } else {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setSideBarPosition(nativeNode, sideBarPosition);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetSideBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetSideBarPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ParseShowSideBarObject(const EcmaVM* vm, const Local<JSValueRef>& callbackArg)
{
    CHECK_NULL_VOID(callbackArg->IsFunction(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    std::function<void(bool)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](bool isShow) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[1] = { panda::BooleanRef::New(vm, isShow) };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getSideBarContainerModifier()->setSideBarOnChangeEvent(reinterpret_cast<void*>(&callback));
}

ArkUINativeModuleValue SideBarContainerBridge::SetShowSideBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> showSideBarArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = nativeNodeArg->IsBoolean() && nativeNodeArg->ToBoolean(vm)->Value();
    if (isJsView) {
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc < NUM_2 || argc > NUM_3) {
            return panda::JSValueRef::Undefined(vm);
        }
        bool isShow = true;
        if (argc > NUM_1 && showSideBarArg->IsBoolean()) {
            isShow = showSideBarArg->ToBoolean(vm)->Value();
        }
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setShowSideBar(nativeNode, isShow);
        Local<JSValueRef> showSideBarFucArg = runtimeCallInfo->GetCallArgRef(NUM_2);
        if (argc > NUM_2 && showSideBarFucArg->IsFunction(vm)) {
            ParseShowSideBarObject(vm, showSideBarFucArg);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (showSideBarArg->IsBoolean()) {
        bool isShow = showSideBarArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setShowSideBar(nativeNode, isShow);
    } else {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->resetShowSideBar(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetShowSideBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetShowSideBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ProcessDividerProperties(const Local<panda::ObjectRef>& obj, EcmaVM* vm)
{
    Dimension strokeWidth = DEFAULT_DIVIDER_STROKE_WIDTH;
    RefPtr<ResourceObject> strokeWidthResObj;
    if (!ArkTSUtils::ConvertFromJSValueNG(
        vm, obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "strokeWidth")), strokeWidth, strokeWidthResObj) ||
        (strokeWidth.Value() < 0.0f)) {
        strokeWidth = DEFAULT_DIVIDER_STROKE_WIDTH;
    }
    if (SystemProperties::ConfigChangePerform() && strokeWidthResObj) {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setDividerStrokeWidth(
            nullptr, AceType::RawPtr(strokeWidthResObj));
    } else {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setDividerStrokeWidth(&strokeWidth, nullptr);
    }

    Color color = DEFAULT_DIVIDER_COLOR;
    RefPtr<ResourceObject> colorResObj;
    if (!ArkTSUtils::ConvertFromJSValue(
        vm, obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "color")), color, colorResObj)) {
        color = DEFAULT_DIVIDER_COLOR;
    }
    if (SystemProperties::ConfigChangePerform() && colorResObj) {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setDividerColor(nullptr, AceType::RawPtr(colorResObj));
    } else {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setDividerColor(&color, nullptr);
    }

    Dimension startMargin = DEFAULT_DIVIDER_START_MARGIN;
    RefPtr<ResourceObject> startMarginResObj;
    if (!ArkTSUtils::ConvertFromJSValueNG(
        vm, obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "startMargin")), startMargin, startMarginResObj) ||
        (startMargin.Value() < 0.0f)) {
        startMargin = DEFAULT_DIVIDER_START_MARGIN;
    }
    if (SystemProperties::ConfigChangePerform() && startMarginResObj) {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setDividerStartMargin(
            nullptr, AceType::RawPtr(startMarginResObj));
    } else {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setDividerStartMargin(&startMargin, nullptr);
    }

    Dimension endMargin = DEFAULT_DIVIDER_END_MARGIN;
    RefPtr<ResourceObject> endMarginResObj;
    if (!ArkTSUtils::ConvertFromJSValueNG(
        vm, obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "endMargin")), endMargin, endMarginResObj) ||
        (endMargin.Value() < 0.0f)) {
        endMargin = DEFAULT_DIVIDER_END_MARGIN;
    }
    if (SystemProperties::ConfigChangePerform() && endMarginResObj) {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setDividerEndMargin(
            nullptr, AceType::RawPtr(endMarginResObj));
    } else {
        GetArkUINodeModifiers()->getSideBarContainerModifier()->setDividerEndMargin(&endMargin, nullptr);
    }
}

ArkUINativeModuleValue JSSetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc < NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> dividerArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetResObjDivider();
    Dimension strokeWidth = DEFAULT_DIVIDER_STROKE_WIDTH;
    if (dividerArg->IsNull() || dividerArg->IsUndefined()) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            // sideBar divider set default width when input illegal value
            GetArkUINodeModifiers()->getSideBarContainerModifier()->setDividerStrokeWidth(&strokeWidth, nullptr);
        } else if (dividerArg->IsNull()) {
            strokeWidth = ZERO_DIVIDER_STROKE_WIDTH;
            GetArkUINodeModifiers()->getSideBarContainerModifier()->setDividerStrokeWidth(&strokeWidth, nullptr);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (dividerArg->IsObject(vm)) {
        ProcessDividerProperties(dividerArg->ToObject(vm), vm);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> strokeWidthArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> startMarginArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> endMarginArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = nativeNodeArg->IsBoolean() && nativeNodeArg->ToBoolean(vm)->Value();
    if (isJsView) {
        JSSetDivider(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }
    CalcDimension strokeWidth;
    CalcDimension startMargin;
    CalcDimension endMargin;
    RefPtr<ResourceObject> strokeWidthObj;
    RefPtr<ResourceObject> startMarginObj;
    RefPtr<ResourceObject> endMarginObj;
    RefPtr<ResourceObject> colorObj;
    ArkUI_Float32 values[NUM_3] = { 1.0, 0.0, 0.0 };
    int32_t units[NUM_3] = { static_cast<int32_t>(DimensionUnit::VP) };
    if (ArkTSUtils::ParseJsDimensionNG(vm, strokeWidthArg, strokeWidth, DimensionUnit::VP, strokeWidthObj, true) &&
        strokeWidth.Value() >= 0) {
        values[NUM_0] = strokeWidth.Value();
        units[NUM_0] = static_cast<int32_t>(strokeWidth.Unit());
    } else {
        strokeWidth.SetValue(1.0);
        strokeWidth.SetUnit(DimensionUnit::VP);
    }
    if (ArkTSUtils::ParseJsDimensionNG(vm, startMarginArg, startMargin, DimensionUnit::VP, startMarginObj, true) &&
        startMargin.Value() >= 0) {
        values[NUM_1] = startMargin.Value();
        units[NUM_1] = static_cast<int32_t>(startMargin.Unit());
    } else {
        startMargin.SetValue(0.0);
        startMargin.SetUnit(DimensionUnit::VP);
    }
    if (ArkTSUtils::ParseJsDimensionNG(vm, endMarginArg, endMargin, DimensionUnit::VP, endMarginObj, true) &&
        endMargin.Value() >= 0) {
        values[NUM_2] = endMargin.Value();
        units[NUM_2] = static_cast<int32_t>(endMargin.Unit());
    } else {
        endMargin.SetValue(0.0);
        endMargin.SetUnit(DimensionUnit::VP);
    }

    Color color(DEFAULT_SIDE_BAR_DIVIDER_COLOR);
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, colorObj, nodeInfo)) {
        color.SetValue(DEFAULT_SIDE_BAR_DIVIDER_COLOR);
    }
    auto strokeWidthPtr = AceType::RawPtr(strokeWidthObj);
    auto startMarginPtr = AceType::RawPtr(startMarginObj);
    auto endMarginPtr = AceType::RawPtr(endMarginObj);
    auto colorPtr = AceType::RawPtr(colorObj);
    GetArkUINodeModifiers()->getSideBarContainerModifier()->setSideBarContainerDivider(
        nativeNode, values, units, NUM_3, color.GetValue(), strokeWidthPtr, startMarginPtr, endMarginPtr, colorPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSideBarContainerModifier()->resetSideBarContainerDivider(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::SetSideBarOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto frameNode = GetFrameNode(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getSideBarContainerModifier()->resetSideBarOnChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    std::function<void(bool)> callback = [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](
                                             bool isOnChange) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[1] = { panda::BooleanRef::New(vm, isOnChange) };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    nodeModifiers->getSideBarContainerModifier()->setSideBarOnChange(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::ResetSideBarOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    nodeModifiers->getSideBarContainerModifier()->resetSideBarOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SideBarContainerBridge::CreateSideBarContainer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc < NUM_1) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    nodeModifiers->getSideBarContainerModifier()->create();
    SideBarContainerType style = SideBarContainerType::EMBED;
    if (!firstArg->IsNull() && !firstArg->IsUndefined()) {
        if (firstArg->IsBoolean()) {
            style = static_cast<SideBarContainerType>(firstArg->ToBoolean(vm)->Value());
        } else if (firstArg->IsNumber()) {
            style = static_cast<SideBarContainerType>(firstArg->ToNumber(vm)->Value());
        } else {
            return panda::JSValueRef::Undefined(vm);
        }
    }
    nodeModifiers->getSideBarContainerModifier()->setSideBarContainerType(
        static_cast<ArkUISideBarContainerType>(style));
    return panda::JSValueRef::Undefined(vm);
}

void SideBarContainerBridge::RegisterSideBarContainerAttributes(
    panda::Local<panda::ObjectRef> object, panda::EcmaVM* vm)
{
    static const char* functionNames[] = { "create", "setSideBarWidth", "resetSideBarWidth", "setMinSideBarWidth",
        "resetMinSideBarWidth", "setControlButton", "resetControlButton", "setShowControlButton",
        "resetShowControlButton", "setAutoHide", "resetAutoHide", "setMaxSideBarWidth", "resetMaxSideBarWidth",
        "setMinContentWidth", "resetMinContentWidth", "setSideBarPosition", "resetSideBarPosition", "setShowSideBar",
        "resetShowSideBar", "setDivider", "resetDivider", "setSideBarOnChange", "resetSideBarOnChange" };

    static panda::Local<panda::JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::CreateSideBarContainer),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetSideBarWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetSideBarWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetMinSideBarWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetMinSideBarWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetControlButton),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetControlButton),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetShowControlButton),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetShowControlButton),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetAutoHide),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetAutoHide),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetMaxSideBarWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetMaxSideBarWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetMinContentWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetMinContentWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetSideBarPosition),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetSideBarPosition),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetShowSideBar),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetShowSideBar),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetDivider),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetDivider),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetSideBarOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetSideBarOnChange) };
    auto sideBarContainer = panda::ObjectRef::NewWithNamedProperties(
        vm, sizeof(functionNames) / sizeof(functionNames[0]), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "sideBarContainer"), sideBarContainer);
}

} // namespace OHOS::Ace::NG
