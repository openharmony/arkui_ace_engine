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

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_navigation_utils.h"

#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/common/resource/resource_parse_utils.h"

namespace OHOS::Ace::NG {
void NativeNavigationUtils::ParseBarItems(
    EcmaVM* vm, const Local<JSValueRef>& jsValue, std::vector<ArkUIBarItem>& items)
{
    auto array = panda::Local<panda::ArrayRef>(jsValue);
    auto length = array->Length(vm);
    for (uint32_t index = 0; index < length; index++) {
        auto item = panda::ArrayRef::GetValueAt(vm, array, index);
        if (!item->IsObject(vm)) {
            continue;
        }
        auto obj = item->ToObject(vm);
        ArkUIBarItem menuItem;
        ParseBarItemsValue(vm, obj, menuItem);
        ParseBarItemsIcon(vm, obj, menuItem);
        auto itemEnabledObject = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "isEnabled"));
        if (itemEnabledObject->IsBoolean()) {
            menuItem.isEnable = { 1, itemEnabledObject->ToBoolean(vm)->Value() };
        }
        items.push_back(menuItem);
    }
}

void NativeNavigationUtils::ParseBarItemsValue(
    EcmaVM* vm, const Local<panda::ObjectRef>& itemObject, ArkUIBarItem& toolBarItem)
{
    std::string value;
    auto itemValueObject = itemObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
    toolBarItem.isStringText = true;
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> itemValueResObj;
        if (ArkTSUtils::ParseJsString(vm, itemValueObject, value, itemValueResObj)) {
            toolBarItem.text.isSet = 1;
            toolBarItem.text.value = new char[value.length() + 1];
            DeepCopyStringValue(toolBarItem.text.value, value.length() + 1, value);
        }
        if (itemValueResObj) {
            toolBarItem.isStringText = false;
            auto&& updateFunc = [](const RefPtr<ResourceObject>& itemValueResObj, ArkUIBarItem& toolBarItem) {
                std::string valueResult;
                if (ResourceParseUtils::ParseResString(itemValueResObj, valueResult)) {
                    toolBarItem.text.isSet = 1;
                    toolBarItem.text.value = new char[valueResult.length() + 1];
                    DeepCopyStringValue(toolBarItem.text.value, valueResult.length() + 1, valueResult);
                }
            };
            toolBarItem.AddResource("toolBarItem.value", itemValueResObj, std::move(updateFunc));
        }
    } else {
        if (ArkTSUtils::ParseJsString(vm, itemValueObject, value)) {
            toolBarItem.text.isSet = 1;
            toolBarItem.text.value = new char[value.length() + 1];
            DeepCopyStringValue(toolBarItem.text.value, value.length() + 1, value);
        }
    }
}

void NativeNavigationUtils::ParseBarItemsIcon(
    EcmaVM* vm, const Local<panda::ObjectRef>& itemObject, ArkUIBarItem& toolBarItem)
{
    std::string icon;
    auto itemIconObject = itemObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "icon"));
    toolBarItem.isStringIcon = true;
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> itemIconResObj;
        if (ArkTSUtils::ParseJsMedia(vm, itemIconObject, icon, itemIconResObj)) {
            toolBarItem.icon.isSet = 1;
            toolBarItem.icon.value = new char[icon.length() + 1];
            DeepCopyStringValue(toolBarItem.icon.value, icon.length() + 1, icon);
        }
        if (itemIconResObj) {
            toolBarItem.isStringIcon = false;
            auto&& updateFunc = [](const RefPtr<ResourceObject>& itemIconResObj, ArkUIBarItem& toolBarItem) {
                std::string iconResult;
                if (ResourceParseUtils::ParseResMedia(itemIconResObj, iconResult)) {
                    toolBarItem.icon.isSet = 1;
                    toolBarItem.icon.value = new char[iconResult.length() + 1];
                    DeepCopyStringValue(toolBarItem.icon.value, iconResult.length() + 1, iconResult);
                }
            };
            toolBarItem.AddResource("navigation.barItem.icon", itemIconResObj, std::move(updateFunc));
        }
    } else {
        if (ArkTSUtils::ParseJsMedia(vm, itemIconObject, icon)) {
            toolBarItem.icon.isSet = 1;
            toolBarItem.icon.value = new char[icon.length() + 1];
            DeepCopyStringValue(toolBarItem.icon.value, icon.length() + 1, icon);
        }
    }
}

void NativeNavigationUtils::ParseTitleOptions(const EcmaVM* vm, const Local<JSValueRef>& jsValue,
    ArkUINodeHandle nativeNode, ArkUINavigationTitlebarOptions& options)
{
    auto obj = jsValue->ToObject(vm);
    UpdateNavigationBackgroundColor(vm, obj, nativeNode, options);
    auto blurProperty = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "backgroundBlurStyle"));
    if (blurProperty->IsNumber()) {
        auto blurStyle = blurProperty->Int32Value(vm);
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            options.blurStyle = ArkUIOptionalInt { 1, blurStyle };
        }
    }
    auto barStyleProperty = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "barStyle"));
    if (barStyleProperty->IsNumber()) {
        auto barStyle = barStyleProperty->Int32Value(vm);
        if (barStyle >= static_cast<int32_t>(NG::BarStyle::STANDARD) &&
            barStyle <= static_cast<int32_t>(NG::BarStyle::STACK)) {
            options.barStyle = ArkUIOptionalInt { 1, barStyle };
        } else {
            options.barStyle = ArkUIOptionalInt { 1, static_cast<int32_t>(NG::BarStyle::STANDARD) };
        }
    }
    CalcDimension paddingStart;
    auto paddingStartProperty = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "paddingStart"));
    if (ArkTSUtils::ParseJsLengthMetrics(vm, paddingStartProperty, paddingStart)) {
        options.paddingStart.isSet = 1;
        options.paddingStart.dimension.value = paddingStart.Value();
        options.paddingStart.dimension.units = static_cast<int32_t>(paddingStart.Unit());
    }
    CalcDimension paddingEnd;
    auto paddingEndProperty = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "paddingEnd"));
    if (ArkTSUtils::ParseJsLengthMetrics(vm, paddingEndProperty, paddingEnd)) {
        options.paddingEnd.isSet = 1;
        options.paddingEnd.dimension.value = paddingEnd.Value();
        options.paddingEnd.dimension.units = static_cast<int32_t>(paddingEnd.Unit());
    }
    auto enableHoverModeProperty = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "enableHoverMode"));
    if (enableHoverModeProperty->IsBoolean()) {
        options.enableHoverMode.isSet = 1;
        options.enableHoverMode.value = enableHoverModeProperty->ToBoolean(vm)->Value();
    }
}

void NativeNavigationUtils::UpdateNavigationBackgroundColor(const EcmaVM* vm, const Local<panda::ObjectRef>& obj,
    ArkUINodeHandle nativeNode, ArkUINavigationTitlebarOptions& options)
{
    auto colorProperty = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "backgroundColor"));
    Color color;
    if (!SystemProperties::ConfigChangePerform()) {
        if (ArkTSUtils::ParseJsColor(vm, colorProperty, color)) {
            options.colorValue = ArkUIOptionalUint { 1, color.GetValue() };
        }
        return;
    }
    RefPtr<ResourceObject> backgroundColorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::ParseJsColor(vm, colorProperty, color, backgroundColorResObj, nodeInfo)) {
        options.colorValue = ArkUIOptionalUint { 1, color.GetValue() };
    }
    if (backgroundColorResObj) {
        AddBackgroundColorResource(backgroundColorResObj, options);
    }
}

void NativeNavigationUtils::AddBackgroundColorResource(
    const RefPtr<ResourceObject>& backgroundColorResObj, ArkUINavigationTitlebarOptions& options)
{
    auto&& updateBackgroundColorFunc = [](const RefPtr<ResourceObject>& resObj,
                                           ArkUINavigationTitlebarOptions& options) {
        Color backgroundColor;
        if (ResourceParseUtils::ParseResColor(resObj, backgroundColor)) {
            options.colorValue = ArkUIOptionalUint { 1, backgroundColor.GetValue() };
        }
    };
    options.AddResource(
        "navigationTitleOptionsModifier.backgroundColor", backgroundColorResObj, std::move(updateBackgroundColorFunc));
}

void NativeNavigationUtils::ParseAndSendFunctionParam(ArkUIRuntimeCallInfo* runtimeCallInfo,
    const Local<JSValueRef>& jsValue, ParamSendFunction& actionSendFunc, ParamSendFunction& symbolSendFunc)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_VOID(frameNode);
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    auto jsArray = Framework::JSRef<Framework::JSArray>::Cast(info[1]);
    auto array = panda::Local<panda::ArrayRef>(jsValue);
    auto length = array->Length(vm);
    for (uint32_t index = 0; index < length; index++) {
        auto item = panda::ArrayRef::GetValueAt(vm, array, index);
        if (!item->IsObject(vm)) {
            continue;
        }
        auto obj = item->ToObject(vm);
        auto itemSymbolIconObject = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "symbolIcon"));
        if (itemSymbolIconObject->IsObject(vm)) {
            std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = nullptr;
            auto jsItem = jsArray->GetValueAt(index);
            auto jsItemObject = Framework::JSRef<Framework::JSObject>::Cast(jsItem);
            auto jsItemSymbolIconObject = jsItemObject->GetProperty("symbolIcon");
            Framework::JSViewAbstract::SetSymbolOptionApply(runtimeCallInfo, iconSymbol, jsItemSymbolIconObject);
            symbolSendFunc(nativeNode, reinterpret_cast<void*>(&iconSymbol), index);
        }
        auto itemActionValue = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "action"));
        if (itemActionValue->IsFunction(vm)) {
            panda::Local<panda::FunctionRef> func = itemActionValue->ToObject(vm);
            std::function<void(void)> onItemClick = [vm, frameNode, func = panda::CopyableGlobal(vm, func)] () {
                panda::LocalScope pandaScope(vm);
                panda::TryCatch trycatch(vm);
                PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
                func->Call(vm, func.ToLocal(), nullptr, 0);
            };
            actionSendFunc(nativeNode, reinterpret_cast<void*>(&onItemClick), index);
        }
    }
}

void NativeNavigationUtils::DeepCopyStringValue(char* des, uint32_t desLength, const std::string& src)
{
    if (des == nullptr || desLength == 0) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "destination char space allocated failed");
        return;
    }
    if (src.length() == 0) {
        des[0] = '\0';
        return;
    }
    auto copyedSize = src.copy(des, desLength - 1 < src.length() ? desLength - 1 : src.length());
    if (copyedSize == 0) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "copy string to destination char failed");
    }
    des[copyedSize] = '\0';
}
} // namespace OHOS::Ace::NG