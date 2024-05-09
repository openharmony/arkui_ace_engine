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
    RemoveStack();
    UpdateOnStateChangedCallback(dataSourceObj_, onStateChangedCallback_);
    auto checkNavDestinationExistsFunc = [weakStack = WeakClaim(this)](const JSRef<JSObject>& info) -> int32_t {
        auto stack = weakStack.Upgrade();
        if (stack == nullptr) {
            return ERROR_CODE_INTERNAL_ERROR;
        }
        auto errorCode = stack->CheckNavDestinationExists(info);
        if (errorCode != ERROR_CODE_NO_ERROR) {
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
    JSRef<JSVal> params[ARGC_COUNT_TWO];
    params[0] = JSRef<JSVal>::Make(ToJSValue(name));
    params[1] = param;
    pushFunc->Call(dataSourceObj_, ARGC_COUNT_TWO, params);
}

void JSNavigationStack::PushName(const std::string& name, const JSRef<JSVal>& param)
{
    // obtain param from routeInfo
    auto pushFunc = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("pushName"));
    JSRef<JSVal> params[ARGC_COUNT_TWO];
    params[0] = JSRef<JSVal>::Make(ToJSValue(name));
    params[1] = param;
    pushFunc->Call(dataSourceObj_, ARGC_COUNT_TWO, params);
}

void JSNavigationStack::Push(const std::string& name, int32_t index)
{
    auto getFunc = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("getParamByIndex"));
    auto param = JSRef<JSVal>::Cast(getFunc->Call(dataSourceObj_));
    auto pushFunc = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("pushName"));
    JSRef<JSVal> params[ARGC_COUNT_TWO];
    params[0] = JSRef<JSVal>::Make(ToJSValue(name));
    params[1] = param;
    pushFunc->Call(dataSourceObj_, ARGC_COUNT_TWO, params);
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

std::vector<int32_t> JSNavigationStack::GetAllPathIndex()
{
    if (dataSourceObj_->IsEmpty()) {
        return {};
    }
    auto func = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("getAllPathIndex"));
    auto array = JSRef<JSArray>::Cast(func->Call(dataSourceObj_));
    if (array->IsEmpty()) {
        return {};
    }
    std::vector<int32_t> pathIndex;
    for (size_t i = 0; i < array->Length(); i++) {
        auto value = array->GetValueAt(i);
        if (value->IsNumber()) {
            pathIndex.emplace_back(value->ToNumber<int32_t>());
        }
    }

    return pathIndex;
}

void JSNavigationStack::InitNavPathIndex(const std::vector<std::string>& pathNames)
{
    if (dataSourceObj_->IsEmpty()) {
        return;
    }

    JSRef<JSArray> nameArray = JSRef<JSArray>::New();
    JSRef<JSVal> params[1];
    for (size_t i = 0; i < pathNames.size(); i++) {
        JSRef<JSVal> info = JSRef<JSVal>::Make(ToJSValue(pathNames[i]));
        nameArray->SetValueAt(i, info);
    }
    params[0] = nameArray;
    auto func = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("initNavPathIndex"));
    func->Call(dataSourceObj_, 1, params);
}

RefPtr<NG::UINode> JSNavigationStack::CreateNodeByIndex(int32_t index, const WeakPtr<NG::UINode>& customNode)
{
    auto name = GetNameByIndex(index);
    auto param = GetParamByIndex(index);
    if (GetFlagByIndex(index)) {
        auto node = GetNodeFromPreBuildList(name, param);
        if (node != nullptr) {
            return node;
        }
    }
    RefPtr<NG::UINode> node;
    RefPtr<NG::NavDestinationGroupNode> desNode;
    NG::ScopedViewStackProcessor scopedViewStackProcessor;
    int32_t errorCode = LoadDestination(name, param, customNode, node, desNode);
    if (errorCode != ERROR_CODE_NO_ERROR) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "can't find target destination by index, create empty node");
        return AceType::DynamicCast<NG::UINode>(NavDestinationModel::GetInstance()->CreateEmpty());
    }
    auto pattern = AceType::DynamicCast<NG::NavDestinationPattern>(desNode->GetPattern());
    if (pattern) {
        pattern->SetName(name);
        pattern->SetIndex(index);
        auto onPop = GetOnPopByIndex(index);
        auto pathInfo = AceType::MakeRefPtr<JSNavPathInfo>(name, param, onPop);
        pattern->SetNavPathInfo(pathInfo);
        pattern->SetNavigationStack(WeakClaim(this));
    }
    return node;
}

RefPtr<NG::UINode> JSNavigationStack::CreateNodeByRouteInfo(const RefPtr<NG::RouteInfo>& routeInfo,
    const WeakPtr<NG::UINode>& customNode)
{
    auto jsRouteInfo = AceType::DynamicCast<JSRouteInfo>(routeInfo);
    if (!jsRouteInfo) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "route info is invalid");
        return DynamicCast<NG::UINode>(NavDestinationModel::GetInstance()->CreateEmpty());
    }
    auto name = jsRouteInfo->GetName();
    auto param = jsRouteInfo->GetParam();
    RefPtr<NG::UINode> node;
    RefPtr<NG::NavDestinationGroupNode> desNode;
    int32_t errorCode = LoadDestination(name, param, customNode, node, desNode);
    if (errorCode == ERROR_CODE_NO_ERROR) {
        auto pattern = AceType::DynamicCast<NG::NavDestinationPattern>(desNode->GetPattern());
        if (pattern) {
            auto pathInfo = AceType::MakeRefPtr<JSNavPathInfo>(name, param);
            pattern->SetNavPathInfo(pathInfo);
            pattern->SetName(name);
            pattern->SetNavigationStack(WeakClaim(this));
        }
        return node;
    }
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
            // record parent navigationNode before customNode is rendered in case of navDestinationNode
            auto navigationNode = GetNavigationNode();
            customNode->SetNavigationNode(navigationNode);
            // render, and find deep further
            customNode->Render();
        } else if (node->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
            desNode = AceType::DynamicCast<NG::NavDestinationGroupNode>(node);
            return true;
        }
        auto children = node->GetChildren();
        if (children.size() != 1) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION,
                "router map is invalid, child size is not one: %{public}zu", children.size());
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
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation necessary to immediately trigger a refresh");
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
    auto pathName = navPathInfo->GetProperty("name");
    auto param = navPathInfo->GetProperty("param");
    JSRef<JSVal> params[ARGC_COUNT_TWO] = { pathName, param };
    auto name = pathName->ToString();
    RefPtr<NG::UINode> node;
    auto navigationNode = AceType::DynamicCast<NG::NavigationGroupNode>(navigationNode_.Upgrade());
    CHECK_NULL_RETURN(navigationNode, ERROR_CODE_INTERNAL_ERROR);
    auto navigationPattern = AceType::DynamicCast<NG::NavigationPattern>(navigationNode->GetPattern());
    CHECK_NULL_RETURN(navigationPattern, ERROR_CODE_INTERNAL_ERROR);
    RefPtr<NG::NavDestinationGroupNode> desNode;
    int32_t errorCode = LoadDestination(name, param, navigationPattern->GetParentCustomNode(),
        node, desNode);
    if (errorCode != ERROR_CODE_NO_ERROR) {
        return errorCode;
    }
    auto pattern = AceType::DynamicCast<NG::NavDestinationPattern>(desNode->GetPattern());
    if (pattern) {
        auto onPop = navPathInfo->GetProperty("onPop");
        auto pathInfo = AceType::MakeRefPtr<JSNavPathInfo>(name, param, onPop);
        pattern->SetNavPathInfo(pathInfo);
        pattern->SetNavigationStack(WeakClaim(this));
    }
    SaveNodeToPreBuildList(name, param, node);
    return ERROR_CODE_NO_ERROR;
}

bool JSNavigationStack::GetFlagByIndex(int32_t index) const
{
    if (dataSourceObj_->IsEmpty()) {
        return false;
    }
    auto func = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("getCheckNavDestinationFlagByIndex"));
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(index));
    auto res = func->Call(dataSourceObj_, 1, params);
    if (res->IsBoolean()) {
        return res->ToBoolean();
    }
    return false;
}

std::vector<std::string> JSNavigationStack::DumpStackInfo() const
{
    std::vector<std::string> dumpInfos;
    for (size_t i = 0; i < navPathList_.size(); ++i) {
        const auto& name = navPathList_[i].first;
        std::string info = "[" + std::to_string(i) + "]{ name: \"" + name + "\"";
        std::string param = ConvertParamToString(GetParamByIndex(i));
        if (param.length() > 0) {
            info += ", param: " + param;
        }
        info += " }";
        dumpInfos.push_back(std::move(info));
    }
    return dumpInfos;
}

void JSNavigationStack::FireNavigationInterception(bool isBefore, const RefPtr<NG::NavDestinationContext>& from,
    const RefPtr<NG::NavDestinationContext>& to, NG::NavigationOperation operation, bool isAnimated)
{
    std::string targetName = isBefore ? "willShow" : "didShow";
    JSRef<JSFunc> targetFunc;
    if (!CheckAndGetInterceptionFunc(targetName, targetFunc)) {
        return;
    }
    const uint8_t argsNum = 4;
    JSRef<JSVal> params[argsNum];
    auto preDestination = AceType::DynamicCast<NG::NavDestinationContext>(from);
    if (!preDestination) {
        params[0] = JSRef<JSVal>::Make(ToJSValue("navBar"));
    } else if (preDestination->GetIsEmpty()) {
        params[0] = JSRef<JSObject>::New();
    } else {
        JSRef<JSObject> preObj = JSClass<JSNavDestinationContext>::NewInstance();
        auto preProxy = Referenced::Claim(preObj->Unwrap<JSNavDestinationContext>());
        preProxy->SetNavDestinationContext(from);
        params[0] = preObj;
    }
    auto topDestination = AceType::DynamicCast<NG::NavDestinationContext>(to);
    if (!topDestination) {
        params[1] = JSRef<JSVal>::Make(ToJSValue("navBar"));
    } else if (topDestination->GetIsEmpty()) {
        params[1] = JSRef<JSObject>::New();
    } else {
        JSRef<JSObject> topObj = JSClass<JSNavDestinationContext>::NewInstance();
        auto topProxy = Referenced::Claim(topObj->Unwrap<JSNavDestinationContext>());
        topProxy->SetNavDestinationContext(to);
        params[1] = topObj;
    }
    const uint8_t operationIndex = 2;
    params[operationIndex] = JSRef<JSVal>::Make(ToJSValue(static_cast<int32_t>(operation)));
    const uint8_t animatedIndex = 3;
    params[animatedIndex] = JSRef<JSVal>::Make(ToJSValue(isAnimated));
    targetFunc->Call(JSRef<JSObject>(), argsNum, params);
}

void JSNavigationStack::FireNavigationModeChange(NG::NavigationMode mode)
{
    JSRef<JSFunc> modeFunc;
    if (!CheckAndGetInterceptionFunc("modeChange", modeFunc)) {
        return;
    }
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(static_cast<int32_t>(mode)));
    modeFunc->Call(JSRef<JSObject>(), 1, params);
}

bool JSNavigationStack::CheckAndGetInterceptionFunc(const std::string& name, JSRef<JSFunc>& func)
{
    if (dataSourceObj_->IsEmpty()) {
        return false;
    }
    JSRef<JSVal> delegateProp = dataSourceObj_->GetProperty("interception");
    if (!delegateProp->IsObject()) {
        return false;
    }
    JSRef<JSObject> delegate = JSRef<JSObject>::Cast(delegateProp);
    JSRef<JSVal> funcProp = delegate->GetProperty(name.c_str());
    if (!funcProp->IsFunction()) {
        return false;
    }
    func = JSRef<JSFunc>::Cast(funcProp);
    return true;
}

bool JSNavigationStack::LoadDestinationByBuilder(const std::string& name, const JSRef<JSVal>& param,
    RefPtr<NG::UINode>& node, RefPtr<NG::NavDestinationGroupNode>& desNode)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, false);
    const int8_t paramSize = 2;
    if (navDestBuilderFunc_->IsEmpty()) {
        return false;
    }
    JSRef<JSVal> params[paramSize];
    params[0] = JSRef<JSVal>::Make(ToJSValue(name));
    params[1] = param;
    navDestBuilderFunc_->Call(JSRef<JSObject>(), paramSize, params);
    node = NG::ViewStackProcessor::GetInstance()->Finish();
    return GetNavDestinationNodeInUINode(node, desNode);
}

int32_t JSNavigationStack::LoadDestination(const std::string& name, const JSRef<JSVal>& param,
    const WeakPtr<NG::UINode>& customNode, RefPtr<NG::UINode>& node,
    RefPtr<NG::NavDestinationGroupNode>& desNode)
{
    NG::ScopedViewStackProcessor scopedViewStackProcessor;
    // execute navdestination attribute builder
    if (LoadDestinationByBuilder(name, param, node, desNode)) {
        return ERROR_CODE_NO_ERROR;
    }
    // deal route config and execute route config builder
    auto container = Container::Current();
    auto navigationRoute = container->GetNavigationRoute();
    if (!navigationRoute->HasLoaded(name)) {
        int32_t res = navigationRoute->LoadPage(name);
        if (res != 0) {
            TAG_LOGE(AceLogTag::ACE_NAVIGATION, "load page failed: %{public}s, errCode: %{public}d",
                name.c_str(), res);
            return res;
        }
    }
    auto parentCustomNode = AceType::DynamicCast<NG::CustomNode>(customNode.Upgrade());
    CHECK_NULL_RETURN(parentCustomNode, ERROR_CODE_INTERNAL_ERROR);
    auto thisObjTmp = parentCustomNode->FireThisFunc();
    CHECK_NULL_RETURN(thisObjTmp, ERROR_CODE_INTERNAL_ERROR);
    JSRef<JSObject> thisObj = *(JSRef<JSObject>*)(thisObjTmp);
    auto engine = AceType::DynamicCast<Framework::JsiDeclarativeEngine>(EngineHelper::GetCurrentEngine());
    CHECK_NULL_RETURN(engine, ERROR_CODE_INTERNAL_ERROR);
    JSRef<JSObject> wrapBuilder = JSRef<JSObject>::Make(engine->GetNavigationBuilder(name).ToLocal());
    if (wrapBuilder->IsEmpty()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "wrap builder is empty: %{public}s", name.c_str());
        return ERROR_CODE_BUILDER_FUNCTION_NOT_REGISTERED;
    }
    auto builderProp = wrapBuilder->GetProperty("builder");
    if (!builderProp->IsFunction()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "get builder failed: %{public}s", name.c_str());
        return ERROR_CODE_BUILDER_FUNCTION_NOT_REGISTERED;
    }
    auto builderObj = JSRef<JSObject>::Cast(builderProp);
    const int32_t number = builderObj->GetProperty("length")->ToNumber<int32_t>();
    JSRef<JSVal> params[number];
    if (number > 1) {
        params[0] = JSRef<JSVal>::Make(ToJSValue(name));
    }
    if (number >= ARGC_COUNT_TWO) {
        params[1] = param;
    }
    auto builder = JSRef<JSFunc>::Cast(builderProp);
    builder->Call(thisObj, number, params);
    node = NG::ViewStackProcessor::GetInstance()->Finish();
    if (!GetNavDestinationNodeInUINode(node, desNode)) {
        return ERROR_CODE_DESTINATION_NOT_FOUND;
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t JSNavigationStack::GetJsIndexFromNativeIndex(int32_t index)
{
    if (dataSourceObj_->IsEmpty()) {
        return -1;
    }
    auto func = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("getJsIndexFromNativeIndex"));
    JSRef<JSVal> param = JSRef<JSVal>::Make(ToJSValue(index));
    auto res = func->Call(dataSourceObj_, 1, &param);
    if (res->IsNumber()) {
        return res->ToNumber<int32_t>();
    }
    return -1;
}

void JSNavigationStack::MoveIndexToTop(int32_t index)
{
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto func = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("moveIndexToTop"));
    JSRef<JSVal> param = JSRef<JSVal>::Make(ToJSValue(index));
    func->Call(dataSourceObj_, 1, &param);
}
} // namespace OHOS::Ace::Framework
