/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/menu/bridge/menu_item_group/arkts_native_menu_item_group_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_view.h"

using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
bool ParseJsHeaderString(EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<JSValueRef>& headerProp)
{
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, false);
    auto menuItemGroupModifier = nodeModifiers->getMenuItemGroupModifier();
    CHECK_NULL_RETURN(menuItemGroupModifier, false);
    std::string headerStr;
    RefPtr<ResourceObject> resObj;
    Local<JSValueRef> headerVal = headerProp;
    if (!ArkTSUtils::ParseJsString(vm, headerVal, headerStr, resObj)) {
        return false;
    }
    auto resRawPtr = AceType::RawPtr(resObj);
    menuItemGroupModifier->setMenuItemGroupHeaderStrRes(nativeNode, headerStr.c_str(), resRawPtr);
    return true;
}

bool ParseJsFooterString(EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<JSValueRef>& footerProp)
{
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, false);
    auto menuItemGroupModifier = nodeModifiers->getMenuItemGroupModifier();
    CHECK_NULL_RETURN(menuItemGroupModifier, false);
    std::string footerStr;
    RefPtr<ResourceObject> resObj;
    Local<JSValueRef> footerVal = footerProp;
    if (!ArkTSUtils::ParseJsString(vm, footerVal, footerStr, resObj)) {
        return false;
    }
    auto resRawPtr = AceType::RawPtr(resObj);
    menuItemGroupModifier->setMenuItemGroupFooterStrRes(nativeNode, footerStr.c_str(), resRawPtr);
    return true;
}
} // namespace

ArkUINativeModuleValue MenuItemGroupBridge::CreateMenuItemGroup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuItemGroupModifier = nodeModifiers->getMenuItemGroupModifier();
    CHECK_NULL_RETURN(menuItemGroupModifier, panda::JSValueRef::Undefined(vm));
    auto nativeNode = menuItemGroupModifier->createMenuItemGroup();
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> paramArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_EQUAL_RETURN(paramArg->IsObject(vm), false, panda::JSValueRef::Undefined(vm));
    auto obj = paramArg->ToObject(vm);
    auto headerProp = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "header"));
    if (!headerProp.IsEmpty()) {
        if (headerProp->IsFunction(vm)) {
            panda::Local<panda::FunctionRef> headerBuilderFunc = headerProp->ToObject(vm);
            NG::ScopedViewStackProcessor builderViewStackProcessor;
            panda::TryCatch trycatch(vm);
            auto func = panda::CopyableGlobal(vm, headerBuilderFunc);
            auto result = headerBuilderFunc->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            RefPtr<NG::UINode> header = NG::ViewStackProcessor::GetInstance()->Finish();
            CHECK_NULL_RETURN(header, panda::JSValueRef::Undefined(vm));
            auto nodeHandle = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(header));
            menuItemGroupModifier->setMenuItemGroupHeaderNode(nativeNode, nodeHandle);
        } else {
            CHECK_EQUAL_RETURN(
                ParseJsHeaderString(vm, nativeNode, headerProp), false, panda::JSValueRef::Undefined(vm));
        }
    }
    auto footerProp = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "footer"));
    if (!footerProp.IsEmpty()) {
        if (footerProp->IsFunction(vm)) {
            panda::Local<panda::FunctionRef> footerBuilderFunc = footerProp->ToObject(vm);
            NG::ScopedViewStackProcessor builderViewStackProcessor;
            panda::TryCatch trycatch(vm);
            auto func = panda::CopyableGlobal(vm, footerBuilderFunc);
            auto result = footerBuilderFunc->Call(vm, func.ToLocal(), nullptr, 0);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            RefPtr<NG::UINode> footer = NG::ViewStackProcessor::GetInstance()->Finish();
            CHECK_NULL_RETURN(footer, panda::JSValueRef::Undefined(vm));
            auto nodeHandle = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(footer));
            menuItemGroupModifier->setMenuItemGroupFooterNode(nativeNode, nodeHandle);
        } else {
            CHECK_EQUAL_RETURN(
                ParseJsFooterString(vm, nativeNode, footerProp), false, panda::JSValueRef::Undefined(vm));
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemGroupBridge::SetMenuItemGroupHeader(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuItemGroupModifier = nodeModifiers->getMenuItemGroupModifier();
    CHECK_NULL_RETURN(menuItemGroupModifier, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> headerArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    if (headerArg->IsUndefined() || headerArg->IsNull()) {
        return panda::JSValueRef::Undefined(vm);
    }

    if (headerArg->IsString(vm)) {
        std::string headerStr = headerArg->ToString(vm)->ToString(vm);
        menuItemGroupModifier->setMenuItemGroupHeaderStrRes(nativeNode, headerStr.c_str(), nullptr);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemGroupBridge::SetMenuItemGroupFooter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    auto menuItemGroupModifier = nodeModifiers->getMenuItemGroupModifier();
    CHECK_NULL_RETURN(menuItemGroupModifier, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> footerArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    if (footerArg->IsUndefined() || footerArg->IsNull()) {
        return panda::JSValueRef::Undefined(vm);
    }

    if (footerArg->IsString(vm)) {
        std::string footerStr = footerArg->ToString(vm)->ToString(vm);
        menuItemGroupModifier->setMenuItemGroupFooterStrRes(nativeNode, footerStr.c_str(), nullptr);
    }

    return panda::JSValueRef::Undefined(vm);
}

void MenuItemGroupBridge::RegisterMenuItemGroupAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "create",
        "setMenuItemGroupHeader",
        "setMenuItemGroupFooter",
    };
    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuItemGroupBridge::CreateMenuItemGroup),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuItemGroupBridge::SetMenuItemGroupHeader),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuItemGroupBridge::SetMenuItemGroupFooter),
    };
    auto menuItemGroup =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "menuitemgroup"), menuItemGroup);
}
} // namespace OHOS::Ace::NG