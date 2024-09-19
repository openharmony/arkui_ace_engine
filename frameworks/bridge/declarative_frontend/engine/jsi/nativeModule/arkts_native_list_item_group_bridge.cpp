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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_list_item_group_bridge.h"
#include "core/components_ng/pattern/list/list_item_group_model_ng.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_list_item_group.h"
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
constexpr int32_t NODE_INDEX = 0;
constexpr int32_t STROKE_WIDTH_INDEX = 1;
constexpr int32_t COLOR_INDEX = 2;
constexpr int32_t START_MARGIN_INDEX = 3;
constexpr int32_t END_MARGIN_INDEX = 4;

constexpr int32_t ARG_GROUP_LENGTH = 3;

ArkUINativeModuleValue ListItemGroupBridge::SetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NODE_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> dividerStrokeWidthArgs = runtimeCallInfo->GetCallArgRef(STROKE_WIDTH_INDEX);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(COLOR_INDEX);
    Local<JSValueRef> dividerStartMarginArgs = runtimeCallInfo->GetCallArgRef(START_MARGIN_INDEX);
    Local<JSValueRef> dividerEndMarginArgs = runtimeCallInfo->GetCallArgRef(END_MARGIN_INDEX);
    if (dividerStrokeWidthArgs->IsUndefined() && dividerStartMarginArgs->IsUndefined() &&
        dividerEndMarginArgs->IsUndefined() && colorArg->IsUndefined()) {
        GetArkUINodeModifiers()->getListItemGroupModifier()->listItemGroupResetDivider(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension dividerStrokeWidth;
    CalcDimension dividerStartMargin;
    CalcDimension dividerEndMargin;
    uint32_t color;
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, panda::NativePointerRef::New(vm, nullptr));
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, panda::NativePointerRef::New(vm, nullptr));
    auto listTheme = themeManager->GetTheme<ListTheme>();
    CHECK_NULL_RETURN(listTheme, panda::NativePointerRef::New(vm, nullptr));

    if (!ArkTSUtils::ParseJsDimensionVp(vm, dividerStrokeWidthArgs, dividerStrokeWidth, true) ||
        LessNotEqual(dividerStrokeWidth.Value(), 0.0f) || dividerStrokeWidth.Unit() == DimensionUnit::PERCENT) {
        dividerStrokeWidth.Reset();
    }

    Color colorObj;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, colorObj)) {
        color = listTheme->GetDividerColor().GetValue();
    } else {
        color = colorObj.GetValue();
    }
    if (!ArkTSUtils::ParseJsDimensionVp(vm, dividerStartMarginArgs, dividerStartMargin) ||
        LessNotEqual(dividerStartMargin.Value(), 0.0f) || dividerStartMargin.Unit() == DimensionUnit::PERCENT) {
        dividerStartMargin.Reset();
    }
    if (!ArkTSUtils::ParseJsDimensionVp(vm, dividerEndMarginArgs, dividerEndMargin) ||
        LessNotEqual(dividerEndMargin.Value(), 0.0f) || dividerEndMargin.Unit() == DimensionUnit::PERCENT) {
        dividerEndMargin.Reset();
    }
    uint32_t size = ARG_GROUP_LENGTH;
    ArkUI_Float32 values[size];
    int32_t units[size];
    values[NODE_INDEX] = static_cast<ArkUI_Float32>(dividerStrokeWidth.Value());
    values[STROKE_WIDTH_INDEX] = static_cast<ArkUI_Float32>(dividerStartMargin.Value());
    values[COLOR_INDEX] = static_cast<ArkUI_Float32>(dividerEndMargin.Value());
    units[NODE_INDEX] = static_cast<int32_t>(dividerStrokeWidth.Unit());
    units[STROKE_WIDTH_INDEX] = static_cast<int32_t>(dividerStartMargin.Unit());
    units[COLOR_INDEX] = static_cast<int32_t>(dividerEndMargin.Unit());
    GetArkUINodeModifiers()->getListItemGroupModifier()->listItemGroupSetDivider(
        nativeNode, color, values, units, size);

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue ListItemGroupBridge::ResetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NODE_INDEX);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListItemGroupModifier()->listItemGroupResetDivider(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListItemGroupBridge::SetChildrenMainSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    // 2: argument count.
    if (info.Length() != 2 || !(info[1]->IsObject())) {
        return panda::JSValueRef::Undefined(vm);
    }
    JSListItemGroup::SetChildrenMainSize(Framework::JSRef<Framework::JSObject>::Cast(info[1]));

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListItemGroupBridge::ResetChildrenMainSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NODE_INDEX);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListItemGroupModifier()->resetListItemGroupChildrenMainSize(nativeNode);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListItemGroupBridge::SetListItemGroupInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> spaceArg = runtimeCallInfo->GetCallArgRef(1); //1 is index of space
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(2); //2 is index of style
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    double space = 0.0;
    if (spaceArg->IsObject(vm) || !ArkTSUtils::ParseJsDouble(vm, spaceArg, space) || LessNotEqual(space, 0.0)) {
        space = 0.0;
    }
    GetArkUINodeModifiers()->getListItemGroupModifier()->setListItemGroupSpace(nativeNode, space);

    if (styleArg->IsUndefined() || styleArg->IsNull() || !styleArg->IsNumber()) {
        GetArkUINodeModifiers()->getListItemGroupModifier()->resetListItemGroupStyle(nativeNode);
    } else {
        uint32_t style = styleArg->Uint32Value(vm);
        if (style < static_cast<uint32_t>(V2::ListItemGroupStyle::NONE) ||
            style > static_cast<uint32_t>(V2::ListItemGroupStyle::CARD)) {
            style = static_cast<uint32_t>(V2::ListItemGroupStyle::NONE);
        }
        GetArkUINodeModifiers()->getListItemGroupModifier()->setListItemGroupStyle(nativeNode, style);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ListItemGroupBridge::ResetListItemGroupInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getListItemGroupModifier()->resetListItemGroupSpace(nativeNode);
    GetArkUINodeModifiers()->getListItemGroupModifier()->resetListItemGroupStyle(nativeNode);

    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG