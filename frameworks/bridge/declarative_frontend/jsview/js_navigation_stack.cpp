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

#include "bridge/declarative_frontend/jsview/js_navigation_stack.h"

#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_execution_scope_defines.h"
#include "bridge/declarative_frontend/jsview/js_nav_path_stack.h"
#include "bridge/declarative_frontend/jsview/js_navdestination_context.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_model.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "frameworks/base/json/json_util.h"

namespace OHOS::Ace::Framework {
namespace {
constexpr int32_t ARGC_COUNT_TWO = 2;
constexpr int32_t MAX_PARSE_DEPTH = 3;
constexpr char JS_NAV_PATH_STACK_GETNATIVESTACK_FUNC[] = "getNativeStack";
constexpr char JS_NAV_PATH_STACK_SETPARENT_FUNC[] = "setParent";
}

std::string JSRouteInfo::GetName()
{
    return name_;
}

void JSRouteInfo::SetName(const std::string& name)
{
    name_ = name;
}

void JSRouteInfo::SetParam(const JSRef<JSVal>& param)
{
    param_ = param;
}

JSRef<JSVal> JSRouteInfo::GetParam() const
{
    return param_;
}

void JSNavigationStack::SetDataSourceObj(const JSRef<JSObject>& dataSourceObj)
{
    // clean callback from old JSNavPathStack
    UpdateOnStateChangedCallback(dataSourceObj_, nullptr);
    UpdateCheckNavDestinationExistsFunc(dataSourceObj_, nullptr);
    dataSourceObj_ = dataSourceObj;
    // add callback to new JSNavPathStack
    UpdateOnStateChangedCallback(dataSourceObj_, onStateChangedCallback_);
    auto checkNavDestinationExistsFunc = [weakStack = WeakClaim(this)](const JSRef<JSObject>& info) -> int32_t {
        auto stack = weakStack.Upgrade();
        if (stack == nullptr) {
            return Framework::ERROR_CODE_INTERNAL_ERROR;
        }
        auto errorCode = stack->CheckNavDestinationExists(info);
        if (errorCode != Framework::ERROR_CODE_NO_ERROR) {
            stack->RemoveInvalidPage(info);
        }
        return errorCode;
    };
    UpdateCheckNavDestinationExistsFunc(dataSourceObj_, checkNavDestinationExistsFunc);
}

void JSNavigationStack::UpdateCheckNavDestinationExistsFunc(JSRef<JSObject> obj,
    std::function<int32_t(JSRef<JSObject>)> checkFunc)
{
    if (obj->IsEmpty()) {
        return;
    }

    auto property = obj->GetProperty(JS_NAV_PATH_STACK_GETNATIVESTACK_FUNC);
    if (!property->IsFunction()) {
        return;
    }

    auto getNativeStackFunc = JSRef<JSFunc>::Cast(property);
    auto nativeStack = getNativeStackFunc->Call(obj);
    if (nativeStack->IsEmpty() || !nativeStack->IsObject()) {
        return;
    }

    auto nativeStackObj = JSRef<JSObject>::Cast(nativeStack);
    JSNavPathStack* stack = nativeStackObj->Unwrap<JSNavPathStack>();
    CHECK_NULL_VOID(stack);

    stack->SetCheckNavDestinationExistsFunc(checkFunc);
}

const JSRef<JSObject>& JSNavigationStack::GetDataSourceObj()
{
    return dataSourceObj_;
}

void JSNavigationStack::SetNavDestBuilderFunc(const JSRef<JSFunc>& navDestBuilderFunc)
{
    navDestBuilderFunc_ = navDestBuilderFunc;
}

bool JSNavigationStack::IsEmpty()
{
    return dataSourceObj_->IsEmpty();
}

void JSNavigationStack::Pop()
{
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto popFunc = dataSourceObj_->GetProperty("pop");
    if (!popFunc->IsFunction()) {
        return;
    }
    auto func = JSRef<JSFunc>::Cast(popFunc);
    JSRef<JSVal>::Cast(func->Call(dataSourceObj_));
}

void JSNavigationStack::Push(const std::string& name, const RefPtr<NG::RouteInfo>& routeInfo)
{
    // obtain param from NavPathStack
    JSRef<JSVal> param;
    if (routeInfo) {
        auto jsRouteInfo = AceType::DynamicCast<JSRouteInfo>(routeInfo);
        param = jsRouteInfo->GetParam();
    } else {
        auto getFunc = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("getParamByName"));
        auto result = JSRef<JSArray>::Cast(getFunc->Call(dataSourceObj_));
        param = result->GetValueAt(0);
    }

    auto pushFunc = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("pushName"));
    JSRef<JSVal> params[2];
    params[0] = JSRef<JSVal>::Make(ToJSValue(name));
    params[1] = param;
    pushFunc->Call(dataSourceObj_, 2, params);
}

void JSNavigationStack::PushName(const std::string& name, const JSRef<JSVal>& param)
{
    // obtain param from routeInfo
    auto pushFunc = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("pushName"));
    JSRef<JSVal> params[2];
    params[0] = JSRef<JSVal>::Make(ToJSValue(name));
    params[1] = param;
    pushFunc->Call(dataSourceObj_, 2, params);
}

void JSNavigationStack::Push(const std::string& name, int32_t index)
{
    auto getFunc = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("getParamByIndex"));
    auto param = JSRef<JSVal>::Cast(getFunc->Call(dataSourceObj_));
    auto pushFunc = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("pushName"));
    JSRef<JSVal> params[2];
    params[0] = JSRef<JSVal>::Make(ToJSValue(name));
    params[1] = param;
    pushFunc->Call(dataSourceObj_, 2, params);
}

void JSNavigationStack::RemoveName(const std::string& name)
{
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto func = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("removeByName"));
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(name));
    func->Call(dataSourceObj_, 1, params);
}

void JSNavigationStack::RemoveIndex(int32_t index)
{
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto func = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("removeIndex"));
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(index));
    func->Call(dataSourceObj_, 1, params);
}

void JSNavigationStack::Clear()
{
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto func = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("clear"));
    func->Call(dataSourceObj_);
}

std::vector<std::string> JSNavigationStack::GetAllPathName()
{
    if (dataSourceObj_->IsEmpty()) {
        return {};
    }
    auto func = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("getAllPathName"));
    auto array = JSRef<JSArray>::Cast(func->Call(dataSourceObj_));
    if (array->IsEmpty()) {
        return {};
    }
    std::vector<std::string> pathNames;
    for (size_t i = 0; i < array->Length(); i++) {
        auto value = array->GetValueAt(i);
        if (value->IsString()) {
            pathNames.emplace_back(value->ToString());
        }
    }

    return pathNames;
}

RefPtr<NG::UINode> JSNavigationStack::CreateNodeByIndex(int32_t index)
{
    auto name = GetNameByIndex(index);
    auto param = GetParamByIndex(index);
    if (GetFlagByIndex(index)) {
        auto node = GetNodeFromPreBuildList(name, param);
        if (node != nullptr) {
            return node;
        }
    }
    JSRef<JSVal> params[2];
    params[0] = JSRef<JSVal>::Make(ToJSValue(name));
    params[1] = param;
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, nullptr);
    NG::ScopedViewStackProcessor scopedViewStackProcessor;
    if (navDestBuilderFunc_->IsEmpty()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navDestination builder function is nullptr, add default page");
        return AceType::DynamicCast<NG::UINode>(NavDestinationModel::GetInstance()->CreateEmpty());
    }
    navDestBuilderFunc_->Call(JSRef<JSObject>(), 2, params);
    auto node = NG::ViewStackProcessor::GetInstance()->Finish();
    if (node == nullptr) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "router map is invalid, current path name is %{public}s", name.c_str());
    }
    RefPtr<NG::NavDestinationGroupNode> desNode;
    if (GetNavDestinationNodeInUINode(node, desNode)) {
        auto pattern = AceType::DynamicCast<NG::NavDestinationPattern>(desNode->GetPattern());
        if (pattern) {
            auto onPop = GetOnPopByIndex(index);
            auto pathInfo = AceType::MakeRefPtr<JSNavPathInfo>(name, param, onPop);
            pattern->SetNavPathInfo(pathInfo);
            pattern->SetNavigationStack(WeakClaim(this));
        }
        return node;
    }
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "can't find target destination by index, create empty node");
    return AceType::DynamicCast<NG::UINode>(NavDestinationModel::GetInstance()->CreateEmpty());
}

RefPtr<NG::UINode> JSNavigationStack::CreateNodeByRouteInfo(const RefPtr<NG::RouteInfo>& routeInfo)
{
    auto jsRouteInfo = AceType::DynamicCast<JSRouteInfo>(routeInfo);
    auto name = jsRouteInfo->GetName();
    auto param = jsRouteInfo->GetParam();
    JSRef<JSVal> params[2];
    params[0] = JSRef<JSVal>::Make(ToJSValue(name));
    params[1] = param;
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, nullptr);
    NG::ScopedViewStackProcessor scopedViewStackProcessor;
    navDestBuilderFunc_->Call(JSRef<JSObject>(), 2, params);
    auto node = NG::ViewStackProcessor::GetInstance()->Finish();
    if (node == nullptr) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "create destination by builder failed");
    }
    RefPtr<NG::NavDestinationGroupNode> desNode;
    if (GetNavDestinationNodeInUINode(node, desNode)) {
        auto pattern = AceType::DynamicCast<NG::NavDestinationPattern>(desNode->GetPattern());
        if (pattern) {
            auto pathInfo = AceType::MakeRefPtr<JSNavPathInfo>(name, param);
            pattern->SetNavPathInfo(pathInfo);
            pattern->SetNavigationStack(WeakClaim(this));
        }
        return node;
    }
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "can't find navDestination by route info, create empty node");
    return DynamicCast<NG::UINode>(NavDestinationModel::GetInstance()->CreateEmpty());
}

void JSNavigationStack::SetJSExecutionContext(const JSExecutionContext& context)
{
    executionContext_ = context;
}

std::string JSNavigationStack::GetNameByIndex(int32_t index)
{
    auto pathNames = GetAllPathName();
    if (index < 0 || index >= static_cast<int32_t>(pathNames.size())) {
        return "";
    }

    return pathNames[index];
}

JSRef<JSVal> JSNavigationStack::GetParamByIndex(int32_t index) const
{
    if (dataSourceObj_->IsEmpty()) {
        return JSRef<JSVal>::Make();
    }
    auto func = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("getParamByIndex"));
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(index));
    return func->Call(dataSourceObj_, 1, params);
}

JSRef<JSVal> JSNavigationStack::GetOnPopByIndex(int32_t index) const
{
    if (dataSourceObj_->IsEmpty()) {
        return JSRef<JSVal>::Make();
    }
    auto func = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("getOnPopByIndex"));
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(index));
    return func->Call(dataSourceObj_, 1, params);
}

bool JSNavigationStack::GetNavDestinationNodeInUINode(
    RefPtr<NG::UINode> node, RefPtr<NG::NavDestinationGroupNode>& desNode)
{
    while (node) {
        if (node->GetTag() == V2::JS_VIEW_ETS_TAG) {
            auto customNode = AceType::DynamicCast<NG::CustomNode>(node);
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "render current custom node: %{public}s",
                customNode->GetCustomTag().c_str());
            // render, and find deep further
            customNode->Render();
        } else if (node->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
            desNode = AceType::DynamicCast<NG::NavDestinationGroupNode>(node);
            return true;
        }
        auto children = node->GetChildren();
        if (children.size() != 1) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "router map is invalid, child size is more than one");
        }
        node = children.front();
    }
    return false;
}

int32_t JSNavigationStack::GetReplaceValue() const
{
    if (dataSourceObj_->IsEmpty()) {
        return false;
    }
    auto replace = dataSourceObj_->GetProperty("isReplace");
    return replace->ToNumber<int32_t>();
}

void JSNavigationStack::UpdateReplaceValue(int32_t replaceValue) const
{
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto replaceFunc = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("setIsReplace"));
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(replaceValue));
    replaceFunc->Call(dataSourceObj_, 1, params);
}

bool JSNavigationStack::GetAnimatedValue() const
{
    if (dataSourceObj_->IsEmpty()) {
        return true;
    }
    auto animated = dataSourceObj_->GetProperty("animated");
    return animated->ToBoolean();
}

void JSNavigationStack::UpdateAnimatedValue(bool animated)
{
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto animatedFunc = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("setAnimated"));
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(animated));
    animatedFunc->Call(dataSourceObj_, 1, params);
}


bool JSNavigationStack::GetDisableAnimation() const
{
    if (dataSourceObj_->IsEmpty()) {
        return false;
    }
    auto disableAllAnimation = dataSourceObj_->GetProperty("disableAllAnimation");
    return disableAllAnimation->ToBoolean();
}

std::string JSNavigationStack::GetRouteParam() const
{
    auto size = GetSize();
    if (size > 0) {
        auto param = GetParamByIndex(size - 1);
        return ConvertParamToString(param);
    }
    return "";
}

int32_t JSNavigationStack::GetSize() const
{
    if (dataSourceObj_->IsEmpty()) {
        return 0;
    }
    auto func = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("size"));
    auto jsValue = JSRef<JSVal>::Cast(func->Call(dataSourceObj_));
    if (jsValue->IsNumber()) {
        return jsValue->ToNumber<int32_t>();
    }
    return 0;
}

std::string JSNavigationStack::ConvertParamToString(const JSRef<JSVal>& param)
{
    if (param->IsBoolean()) {
        bool ret = param->ToBoolean();
        return ret ? "true" : "false";
    } else if (param->IsNumber()) {
        double ret = param->ToNumber<double>();
        std::ostringstream oss;
        oss<< ret;
        return oss.str();
    } else if (param->IsString()) {
        std::string ret = param->ToString();
        return ret;
    } else if (param->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(param);
        auto jsonObj = JsonUtil::Create(true);
        ParseJsObject(jsonObj, obj, MAX_PARSE_DEPTH);
        return jsonObj->ToString();
    }
    return "";
}

void JSNavigationStack::ParseJsObject(std::unique_ptr<JsonValue>& json, const JSRef<JSObject>& obj, int32_t depthLimit)
{
    if (depthLimit == 0) {
        return;
    }
    depthLimit--;
    auto propertyNames = obj->GetPropertyNames();
    if (!propertyNames->IsArray()) {
        return;
    }
    for (size_t i = 0; i < propertyNames->Length(); i++) {
        JSRef<JSVal> name = propertyNames->GetValueAt(i);
        if (!name->IsString()) {
            continue;
        }
        auto propertyName = name->ToString();
        auto key = propertyName.c_str();
        JSRef<JSVal> value = obj->GetProperty(key);
        if (value->IsBoolean()) {
            bool ret = value->ToBoolean();
            json->Put(key, ret ? "true" : "false");
        } else if (value->IsNumber()) {
            double ret = value->ToNumber<double>();
            std::ostringstream oss;
            oss<< ret;
            json->Put(key, oss.str().c_str());
        } else if (value->IsString()) {
            std::string ret = value->ToString();
            json->Put(key, ret.c_str());
        } else if (value->IsObject()) {
            JSRef<JSObject> childObj = JSRef<JSObject>::Cast(value);
            auto childJson = JsonUtil::Create(true);
            ParseJsObject(childJson, childObj, depthLimit);
            json->Put(key, childJson);
        }
    }
}

void JSNavigationStack::UpdateOnStateChangedCallback(JSRef<JSObject> obj, std::function<void()> callback)
{
    if (obj->IsEmpty()) {
        return;
    }

    auto property = obj->GetProperty(JS_NAV_PATH_STACK_GETNATIVESTACK_FUNC);
    if (!property->IsFunction()) {
        return;
    }

    auto getNativeStackFunc = JSRef<JSFunc>::Cast(property);
    auto nativeStack = getNativeStackFunc->Call(obj);
    if (nativeStack->IsEmpty() || !nativeStack->IsObject()) {
        return;
    }

    auto nativeStackObj = JSRef<JSObject>::Cast(nativeStack);
    JSNavPathStack* stack = nativeStackObj->Unwrap<JSNavPathStack>();
    CHECK_NULL_VOID(stack);
    stack->SetOnStateChangedCallback(callback);
    // When switching the navigation stack, it is necessary to immediately trigger a refresh
    stack->OnStateChanged();
}

void JSNavigationStack::OnAttachToParent(RefPtr<NG::NavigationStack> parent)
{
    auto parentStack = AceType::DynamicCast<JSNavigationStack>(parent);
    if (!parentStack) {
        return;
    }

    SetJSParentStack(JSRef<JSVal>::Cast(parentStack->GetDataSourceObj()));
}

void JSNavigationStack::OnDetachFromParent()
{
    JSRef<JSVal> undefined(JSVal::Undefined());
    SetJSParentStack(undefined);
}

void JSNavigationStack::SetJSParentStack(JSRef<JSVal> parent)
{
    if (dataSourceObj_->IsEmpty()) {
        return;
    }

    auto property = dataSourceObj_->GetProperty(JS_NAV_PATH_STACK_SETPARENT_FUNC);
    if (!property->IsFunction()) {
        return;
    }

    auto func = JSRef<JSFunc>::Cast(property);
    JSRef<JSVal> params[1];
    params[0] = parent;
    func->Call(dataSourceObj_, 1, params);
}

void JSNavigationStack::RemoveInvalidPage(const JSRef<JSObject>& info)
{
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto func = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("removeInvalidPage"));
    auto pathName = info->GetProperty("name");
    auto param = info->GetProperty("param");
    JSRef<JSVal> params[ARGC_COUNT_TWO] = { pathName, param };
    func->Call(dataSourceObj_, ARGC_COUNT_TWO, params);
}

void JSNavigationStack::SaveNodeToPreBuildList(const std::string& name, const JSRef<JSVal>& param,
    RefPtr<NG::UINode>& node)
{
    preBuildNodeList_.emplace_back(name, param, node);
}

RefPtr<NG::UINode> JSNavigationStack::GetNodeFromPreBuildList(const std::string& name, const JSRef<JSVal>& param)
{
    auto isJsObjEqual = [](const JSRef<JSVal>& objLeft, const JSRef<JSVal>& objRight) {
        return (objLeft->IsEmpty() && objRight->IsEmpty()) ||
            (objLeft->GetLocalHandle()->IsStrictEquals(objLeft->GetEcmaVM(), objRight->GetLocalHandle()));
    };
    for (auto it = preBuildNodeList_.begin(); it != preBuildNodeList_.end(); ++it) {
        if (it->name == name && isJsObjEqual(it->param, param)) {
            auto uiNode = it->uiNode;
            preBuildNodeList_.erase(it);
            return uiNode;
        }
    }
    return nullptr;
}

void JSNavigationStack::ClearPreBuildNodeList()
{
    preBuildNodeList_.clear();
}

int32_t JSNavigationStack::CheckNavDestinationExists(const JSRef<JSObject>& navPathInfo)
{
    if (navDestBuilderFunc_->IsEmpty()) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "navDestBuilderFunc_ is empty.");
        return Framework::ERROR_CODE_BUILDER_FUNCTION_NOT_REGISTERED;
    }
    
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, Framework::ERROR_CODE_INTERNAL_ERROR);
    NG::ScopedViewStackProcessor scopedViewStackProcessor;

    auto pathName = navPathInfo->GetProperty("name");
    auto param = navPathInfo->GetProperty("param");
    JSRef<JSVal> params[ARGC_COUNT_TWO] = { pathName, param };
    navDestBuilderFunc_->Call(JSRef<JSObject>(), ARGC_COUNT_TWO, params);

    auto node = NG::ViewStackProcessor::GetInstance()->Finish();
    RefPtr<NG::NavDestinationGroupNode> desNode;
    if (GetNavDestinationNodeInUINode(node, desNode)) {
        auto pattern = AceType::DynamicCast<NG::NavDestinationPattern>(desNode->GetPattern());
        if (pattern) {
            auto onPop = navPathInfo->GetProperty("onPop");
            auto pathInfo = AceType::MakeRefPtr<JSNavPathInfo>(pathName->ToString(), param, onPop);
            pattern->SetNavPathInfo(pathInfo);
            pattern->SetNavigationStack(WeakClaim(this));
        }
        SaveNodeToPreBuildList(pathName->ToString(), param, node);
        return Framework::ERROR_CODE_NO_ERROR;
    }
    return Framework::ERROR_CODE_DESTINATION_NOT_FOUND;
}

bool JSNavigationStack::GetFlagByIndex(int32_t index) const
{
    if (dataSourceObj_->IsEmpty()) {
        return false;
    }
    auto func = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("getFlagByIndex"));
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(index));
    auto res = func->Call(dataSourceObj_, 1, params);
    if (res->IsBoolean()) {
        return res->ToBoolean();
    }
    return false;
}
} // namespace OHOS::Ace::Framework
