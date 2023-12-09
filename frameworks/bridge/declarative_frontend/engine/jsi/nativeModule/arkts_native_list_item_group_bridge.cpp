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

#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr int CALL_ARG_0 = 0;
constexpr int CALL_ARG_1 = 1;
constexpr int CALL_ARG_2 = 2;
constexpr int CALL_ARG_3 = 3;
constexpr int CALL_ARG_4 = 4;
constexpr int ARG_LENGTH = 3;

ArkUINativeModuleValue ListeItemGroupBridege::SetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> strokeWidthArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    Local<JSValueRef> startMarginArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_3);
    Local<JSValueRef> endMarginArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_4);

    CalcDimension strokeWidth;
    Color color;
    CalcDimension startMargin;
    CalcDimension endMargin;
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    if (strokeWidthArg->IsNull() || strokeWidthArg->IsUndefined() ||
        !ArkTSUtils::ParseJsDimension(vm, strokeWidthArg, strokeWidth, DimensionUnit::VP)) {
        strokeWidth = 0.0_vp;
    };
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color)) {
        RefPtr<ListTheme> listTheme = Framework::JSViewAbstract::GetTheme<ListTheme>();
        if (listTheme) {
            color = listTheme->GetDividerColor();
        }
    };
    if (startMarginArg->IsNull() || startMarginArg->IsUndefined() ||
        !ArkTSUtils::ParseJsDimension(vm, startMarginArg, startMargin, DimensionUnit::VP)) {
        startMargin = 0.0_vp;
    };
    if (endMarginArg->IsNull() || endMarginArg->IsUndefined() ||
        !ArkTSUtils::ParseJsDimension(vm, endMarginArg, endMargin, DimensionUnit::VP)) {
        endMargin = 0.0_vp;
    };
    double values[ARG_LENGTH];
    int units[ARG_LENGTH];
    values[CALL_ARG_0] = strokeWidth.Value();
    values[CALL_ARG_1] = startMargin.Value();
    values[CALL_ARG_2] = endMargin.Value();
    units[CALL_ARG_0] = static_cast<int>(strokeWidth.Unit());
    units[CALL_ARG_1] = static_cast<int>(startMargin.Unit());
    units[CALL_ARG_2] = static_cast<int>(endMargin.Unit());
    GetArkUIInternalNodeAPI()->GetListItemGroupModifier().ListItemGroupSetDivider(
        nativeNode, color.GetValue(), values, units);

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue ListeItemGroupBridege::ResetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetListItemGroupModifier().ListItemGroupResetDivider(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG