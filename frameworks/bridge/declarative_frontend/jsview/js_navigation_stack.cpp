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
constexpr uint32_t MAX_PARSE_LENGTH = 1024;
constexpr uint32_t MAX_PARSE_PROPERTY_SIZE = 15;
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
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
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
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    JSRef<JSVal> param;
    if (routeInfo) {
        auto jsRouteInfo = AceType::DynamicCast<JSRouteInfo>(routeInfo);
        param = jsRouteInfo->GetParam();
    } else {
        auto getParamByNameFunc = dataSourceObj_->GetProperty("getParamByName");
        if (getParamByNameFunc->IsFunction()) {
            auto getFunc = JSRef<JSFunc>::Cast(getParamByNameFunc);
            auto funcArray = getFunc->Call(dataSourceObj_);
            if (funcArray->IsArray()) {
                auto result = JSRef<JSArray>::Cast(funcArray);
                param = result->GetValueAt(0);
            }
        }
    }
    auto pushNameFunc = dataSourceObj_->GetProperty("pushName");
    if (pushNameFunc->IsFunction()) {
        auto pushFunc = JSRef<JSFunc>::Cast(pushNameFunc);
        JSRef<JSVal> params[2];
        params[0] = JSRef<JSVal>::Make(ToJSValue(name));
        params[1] = param;
        pushFunc->Call(dataSourceObj_, 2, params);
    }
}

void JSNavigationStack::PushName(const std::string& name, const JSRef<JSVal>& param)
{
    // obtain param from routeInfo
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    auto pushNameFunc = dataSourceObj_->GetProperty("pushName");
    if (pushNameFunc->IsFunction()) {
        auto pushFunc = JSRef<JSFunc>::Cast(pushNameFunc);
        JSRef<JSVal> params[2];
        params[0] = JSRef<JSVal>::Make(ToJSValue(name));
        params[1] = param;
        pushFunc->Call(dataSourceObj_, 2, params);
    }
}

void JSNavigationStack::Push(const std::string& name, int32_t index)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    auto getParamByIndexFunc = dataSourceObj_->GetProperty("getParamByIndex");
    if (!getParamByIndexFunc->IsFunction()) {
        return ;
    }
    auto pushNameFunc = dataSourceObj_->GetProperty("pushName");
    if (!pushNameFunc->IsFunction()) {
        return ;
    }
    auto getFunc = JSRef<JSFunc>::Cast(getParamByIndexFunc);
    auto param = JSRef<JSVal>::Cast(getFunc->Call(dataSourceObj_));
    auto pushFunc = JSRef<JSFunc>::Cast(pushNameFunc);
    JSRef<JSVal> params[ARGC_COUNT_TWO];
    params[0] = JSRef<JSVal>::Make(ToJSValue(name));
    params[1] = param;
    pushFunc->Call(dataSourceObj_, ARGC_COUNT_TWO, params);
}

void JSNavigationStack::RemoveName(const std::string& name)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto removeByNameFunc = dataSourceObj_->GetProperty("removeByName");
    if (!removeByNameFunc->IsFunction()) {
        return;
    }
    auto func = JSRef<JSFunc>::Cast(removeByNameFunc);
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(name));
    func->Call(dataSourceObj_, 1, params);
}

void JSNavigationStack::RemoveIndex(int32_t index)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto removeIndexFunc = dataSourceObj_->GetProperty("removeIndex");
    if (removeIndexFunc->IsFunction()) {
        auto func = JSRef<JSFunc>::Cast(removeIndexFunc);
        JSRef<JSVal> params[1];
        params[0] = JSRef<JSVal>::Make(ToJSValue(index));
        func->Call(dataSourceObj_, 1, params);
    }
}

void JSNavigationStack::Clear()
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto clearFunc = dataSourceObj_->GetProperty("clear");
    if (!clearFunc->IsFunction()) {
        return;
    }
    auto func = JSRef<JSFunc>::Cast(clearFunc);
    func->Call(dataSourceObj_);
}

std::vector<std::string> JSNavigationStack::GetAllPathName()
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, {});
    if (dataSourceObj_->IsEmpty()) {
        return {};
    }
    auto getAllPathNameFunc = dataSourceObj_->GetProperty("getAllPathName");
    if (!getAllPathNameFunc->IsFunction()) {
        return {};
    }
    auto func = JSRef<JSFunc>::Cast(getAllPathNameFunc);
    auto funcArray = func->Call(dataSourceObj_);
    if (!funcArray->IsArray()) {
        return {};
    }
    auto array = JSRef<JSArray>::Cast(funcArray);
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
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, {});
    if (dataSourceObj_->IsEmpty()) {
        return {};
    }
    auto getAllPathIndexFunc = dataSourceObj_->GetProperty("getAllPathIndex");
    if (!getAllPathIndexFunc->IsFunction()) {
        return {};
    }
    auto func = JSRef<JSFunc>::Cast(getAllPathIndexFunc);
    auto funcArray = func->Call(dataSourceObj_);
    if (!funcArray->IsArray()) {
        return {};
    }
    auto array = JSRef<JSArray>::Cast(funcArray);
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
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
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
    auto initNavPathIndexFunc = dataSourceObj_->GetProperty("initNavPathIndex");
    if (!initNavPathIndexFunc->IsFunction()) {
        return;
    }
    auto func = JSRef<JSFunc>::Cast(initNavPathIndexFunc);
    func->Call(dataSourceObj_, 1, params);
}

void JSNavigationStack::SetDestinationIdToJsStack(int32_t index, const std::string& navDestinationId)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    auto pathInfo = GetJsPathInfo(index);
    if (pathInfo->IsEmpty()) {
        return;
    }
    pathInfo->SetProperty<std::string>("navDestinationId", navDestinationId);
}

bool JSNavigationStack::CallByPushDestination(int32_t index)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, false);
    auto pathInfo = GetJsPathInfo(index);
    if (pathInfo->IsEmpty()) {
        return false;
    }
    auto isPushDestination = pathInfo->GetPropertyValue<bool>("pushDestination", false);
    return isPushDestination;
}

RefPtr<NG::UINode> JSNavigationStack::CreateNodeByIndex(int32_t index, const WeakPtr<NG::UINode>& customNode)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, nullptr);
    auto name = GetNameByIndex(index);
    auto param = GetParamByIndex(index);
    RefPtr<NG::UINode> node;
    if (GetNodeFromPreBuildList(index, name, param, node)) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "get node from prebuild list");
        return node;
    }
    RefPtr<NG::NavDestinationGroupNode> desNode;
    NG::ScopedViewStackProcessor scopedViewStackProcessor;
    int32_t errorCode = LoadDestination(name, param, customNode, node, desNode);
    if (errorCode != ERROR_CODE_NO_ERROR) {
        if (CallByPushDestination(index)) {
            return nullptr;
        }
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "can't find target destination by index, create empty node");
        return AceType::DynamicCast<NG::UINode>(NavDestinationModel::GetInstance()->CreateEmpty());
    }
    auto pattern = AceType::DynamicCast<NG::NavDestinationPattern>(desNode->GetPattern());
    if (pattern) {
        pattern->SetName(name);
        pattern->SetIndex(index);
        auto onPop = GetOnPopByIndex(index);
        auto isEntry = GetIsEntryByIndex(index);
        TAG_LOGD(AceLogTag::ACE_NAVIGATION, "create destination node, isEntry %{public}d", isEntry);
        auto pathInfo = AceType::MakeRefPtr<JSNavPathInfo>(name, param, onPop, isEntry);
        pattern->SetNavPathInfo(pathInfo);
        pattern->SetNavigationStack(WeakClaim(this));
    }
    return node;
}

RefPtr<NG::UINode> JSNavigationStack::CreateNodeByRouteInfo(const RefPtr<NG::RouteInfo>& routeInfo,
    const WeakPtr<NG::UINode>& customNode)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, nullptr);
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
    auto getParamByIndexFunc = dataSourceObj_->GetProperty("getParamByIndex");
    if (!getParamByIndexFunc->IsFunction()) {
        return JSRef<JSVal>::Make();
    }
    auto func = JSRef<JSFunc>::Cast(getParamByIndexFunc);
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(index));
    return func->Call(dataSourceObj_, 1, params);
}

JSRef<JSVal> JSNavigationStack::GetOnPopByIndex(int32_t index) const
{
    if (dataSourceObj_->IsEmpty()) {
        return JSRef<JSVal>::Make();
    }
    auto getOnPopByIndexFunc = dataSourceObj_->GetProperty("getOnPopByIndex");
    if (!getOnPopByIndexFunc->IsFunction()) {
        return JSRef<JSVal>::Make();
    }
    auto func = JSRef<JSFunc>::Cast(getOnPopByIndexFunc);
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(index));
    return func->Call(dataSourceObj_, 1, params);
}

bool JSNavigationStack::GetIsEntryByIndex(int32_t index)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, false);
    if (dataSourceObj_->IsEmpty()) {
        return false;
    }
    auto getIsEntryFunc = dataSourceObj_->GetProperty("getIsEntryByIndex");
    if (!getIsEntryFunc->IsFunction()) {
        return false;
    }
    auto func = JSRef<JSFunc>::Cast(getIsEntryFunc);
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(index));
    auto result = func->Call(dataSourceObj_, 1, params);
    if (!result->IsBoolean()) {
        return false;
    }
    return result->ToBoolean();
}

void JSNavigationStack::SetIsEntryByIndex(int32_t index, bool isEntry)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto setIsEntryFunc = dataSourceObj_->GetProperty("setIsEntryByIndex");
    if (!setIsEntryFunc->IsFunction()) {
        return;
    }
    auto func = JSRef<JSFunc>::Cast(setIsEntryFunc);
    JSRef<JSVal> params[ARGC_COUNT_TWO];
    params[0] = JSRef<JSVal>::Make(ToJSValue(index));
    params[1] = JSRef<JSVal>::Make(ToJSValue(isEntry));
    func->Call(dataSourceObj_, ARGC_COUNT_TWO, params);
}

bool JSNavigationStack::GetNavDestinationNodeInUINode(
    RefPtr<NG::UINode> node, RefPtr<NG::NavDestinationGroupNode>& desNode)
{
    RefPtr<NG::CustomNode> customNode;
    while (node) {
        if (node->GetTag() == V2::JS_VIEW_ETS_TAG) {
            customNode = AceType::DynamicCast<NG::CustomNode>(node);
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "render current custom node: %{public}s",
                customNode->GetCustomTag().c_str());
            // record parent navigationNode before customNode is rendered in case of navDestinationNode
            auto navigationNode = GetNavigationNode();
            customNode->SetNavigationNode(navigationNode);
            // render, and find deep further
            customNode->Render();
        } else if (node->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
            desNode = AceType::DynamicCast<NG::NavDestinationGroupNode>(node);
            if (desNode) {
                desNode->SetNavDestinationCustomNode(AceType::WeakClaim(AceType::RawPtr(customNode)));
            }
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
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto setIsReplaceFunc = dataSourceObj_->GetProperty("setIsReplace");
    if (!setIsReplaceFunc->IsFunction()) {
        return;
    }
    auto replaceFunc = JSRef<JSFunc>::Cast(setIsReplaceFunc);
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Make(ToJSValue(replaceValue));
    replaceFunc->Call(dataSourceObj_, 1, params);
}

std::string JSNavigationStack::GetRouteParam() const
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, "");
    auto size = GetSize();
    if (size > 0) {
        auto param = GetParamByIndex(size - 1);
        return ConvertParamToString(param, true);
    }
    return "";
}

int32_t JSNavigationStack::GetSize() const
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, 0);
    if (dataSourceObj_->IsEmpty()) {
        return 0;
    }
    auto sizeFunc = dataSourceObj_->GetProperty("size");
    if (!sizeFunc->IsFunction()) {
        return 0;
    }
    auto func = JSRef<JSFunc>::Cast(sizeFunc);
    auto jsValue = JSRef<JSVal>::Cast(func->Call(dataSourceObj_));
    if (jsValue->IsNumber()) {
        return jsValue->ToNumber<int32_t>();
    }
    return 0;
}

std::string JSNavigationStack::ConvertParamToString(const JSRef<JSVal>& param, bool needLimit) const
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, "");
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
        if (needLimit && ret.size() > MAX_PARSE_LENGTH) {
            return ret.substr(0, MAX_PARSE_LENGTH);
        }
        return ret;
    } else if (param->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(param);
        auto jsonObj = JsonUtil::Create(true);
        ParseJsObject(jsonObj, obj, MAX_PARSE_DEPTH, needLimit);
        return jsonObj->ToString();
    }
    return "";
}

void JSNavigationStack::ParseJsObject(
    std::unique_ptr<JsonValue>& json, const JSRef<JSObject>& obj, int32_t depthLimit, bool needLimit) const
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    if (depthLimit == 0) {
        return;
    }
    depthLimit--;
    auto propertyNames = obj->GetPropertyNames();
    if (!propertyNames->IsArray()) {
        return;
    }
    size_t size = propertyNames->Length();
    if (needLimit && size > MAX_PARSE_PROPERTY_SIZE) {
        size = MAX_PARSE_PROPERTY_SIZE;
    }
    for (size_t i = 0; i < size; i++) {
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
            oss << ret;
            json->Put(key, oss.str().c_str());
        } else if (value->IsString()) {
            std::string ret = value->ToString();
            if (needLimit && ret.size() > MAX_PARSE_LENGTH) {
                json->Put(key, ret.substr(0, MAX_PARSE_LENGTH).c_str());
            } else {
                json->Put(key, ret.c_str());
            }
        } else if (value->IsObject()) {
            JSRef<JSObject> childObj = JSRef<JSObject>::Cast(value);
            auto childJson = JsonUtil::Create(true);
            ParseJsObject(childJson, childObj, depthLimit, needLimit);
            json->Put(key, childJson);
        }
    }
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
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto setAnimatedFunc = dataSourceObj_->GetProperty("setAnimated");
    if (!setAnimatedFunc->IsFunction()) {
        return;
    }
    auto animatedFunc = JSRef<JSFunc>::Cast(setAnimatedFunc);
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
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
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
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto removeInvalidPage = dataSourceObj_->GetProperty("removeInvalidPage");
    if (removeInvalidPage->IsFunction()) {
        auto func = JSRef<JSFunc>::Cast(removeInvalidPage);
        auto pathName = info->GetProperty("name");
        auto param = info->GetProperty("param");
        JSRef<JSVal> params[ARGC_COUNT_TWO] = { pathName, param };
        func->Call(dataSourceObj_, ARGC_COUNT_TWO, params);
    }
}

void JSNavigationStack::SaveNodeToPreBuildList(const std::string& name, const JSRef<JSVal>& param,
    RefPtr<NG::UINode>& node)
{
    preBuildNodeList_.emplace_back(name, param, node, GetSize() - 1);
}

bool JSNavigationStack::GetNodeFromPreBuildList(int32_t index, const std::string& name,
    const JSRef<JSVal>& param, RefPtr<NG::UINode>& node)
{
    auto isJsObjEqual = [](const JSRef<JSVal>& objLeft, const JSRef<JSVal>& objRight) {
        return (objLeft->IsEmpty() && objRight->IsEmpty()) ||
            (objLeft->GetLocalHandle()->IsStrictEquals(objLeft->GetEcmaVM(), objRight->GetLocalHandle()));
    };
    for (auto it = preBuildNodeList_.begin(); it != preBuildNodeList_.end(); ++it) {
        if (it->name == name && isJsObjEqual(it->param, param) && it->index == index) {
            node = it->uiNode;
            preBuildNodeList_.erase(it);
            return true;
        }
    }
    return false;
}

void JSNavigationStack::ClearPreBuildNodeList()
{
    preBuildNodeList_.clear();
}

int32_t JSNavigationStack::CheckNavDestinationExists(const JSRef<JSObject>& navPathInfo)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, ERROR_CODE_DESTINATION_NOT_FOUND);
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
        auto isEntryVal = navPathInfo->GetProperty("isEntry");
        bool isEntry = isEntryVal->IsBoolean() ? isEntryVal->ToBoolean() : false;
        auto pathInfo = AceType::MakeRefPtr<JSNavPathInfo>(name, param, onPop, isEntry);
        pattern->SetName(name);
        pattern->SetIndex(GetSize() - 1);
        pattern->SetNavPathInfo(pathInfo);
        pattern->SetNavigationStack(WeakClaim(this));
    }
    SaveNodeToPreBuildList(name, param, node);
    return ERROR_CODE_NO_ERROR;
}

std::vector<std::string> JSNavigationStack::DumpStackInfo() const
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, {});
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
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
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
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
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
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, false);
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
    if (navDestBuilderFunc_->IsEmpty()) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Builder function is empty");
        return false;
    }
    auto builderObj = JSRef<JSObject>::Cast(navDestBuilderFunc_);
    const int32_t number = builderObj->GetProperty("length")->ToNumber<int32_t>();
    JSRef<JSVal> params[number];
    if (number >= 1) {
        params[0] = JSRef<JSVal>::Make(ToJSValue(name));
    }
    if (number >= ARGC_COUNT_TWO) {
        params[1] = param;
    }
    navDestBuilderFunc_->Call(JSRef<JSObject>(), number, params);
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
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "load destination by buildermap");
        return ERROR_CODE_NO_ERROR;
    }
    // deal route config and execute route config builder
    auto container = Container::Current();
    auto navigationRoute = container->GetNavigationRoute();
    if (!navigationRoute->HasLoaded(name)) {
        int32_t res = navigationRoute->LoadPage(name);
        if (res != 0) {
            TAG_LOGE(AceLogTag::ACE_NAVIGATION, "load page failed: %{public}s", name.c_str());
            return navDestBuilderFunc_->IsEmpty() ? ERROR_CODE_BUILDER_FUNCTION_NOT_REGISTERED
                : ERROR_CODE_DESTINATION_NOT_FOUND;
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
    if (number >= 1) {
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
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, -1);
    if (dataSourceObj_->IsEmpty()) {
        return -1;
    }
    auto getIndexFunc = dataSourceObj_->GetProperty("getJsIndexFromNativeIndex");
    if (!getIndexFunc->IsFunction()) {
        return -1;
    }
    auto func = JSRef<JSFunc>::Cast(getIndexFunc);
    JSRef<JSVal> param = JSRef<JSVal>::Make(ToJSValue(index));
    auto res = func->Call(dataSourceObj_, 1, &param);
    if (res->IsNumber()) {
        return res->ToNumber<int32_t>();
    }
    return -1;
}

void JSNavigationStack::MoveIndexToTop(int32_t index)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto moveIndexToTopFunc = dataSourceObj_->GetProperty("moveIndexToTop");
    if (!moveIndexToTopFunc->IsFunction()) {
        return;
    }
    auto func = JSRef<JSFunc>::Cast(moveIndexToTopFunc);
    JSRef<JSVal> param = JSRef<JSVal>::Make(ToJSValue(index));
    func->Call(dataSourceObj_, 1, &param);
}

void JSNavigationStack::UpdatePathInfoIfNeeded(RefPtr<NG::UINode>& uiNode, int32_t index)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    bool needUpdate = GetNeedUpdatePathInfo(index);
    if (!needUpdate) {
        return;
    }
    SetNeedUpdatePathInfo(index, false);
    RefPtr<NG::NavDestinationGroupNode> desNode;
    if (!GetNavDestinationNodeInUINode(uiNode, desNode)) {
        return;
    }
    auto pattern = AceType::DynamicCast<NG::NavDestinationPattern>(desNode->GetPattern());
    if (!pattern) {
        return;
    }

    auto name = GetNameByIndex(index);
    auto param = GetParamByIndex(index);
    auto onPop = GetOnPopByIndex(index);
    auto isEntry = GetIsEntryByIndex(index);
    TAG_LOGD(AceLogTag::ACE_NAVIGATION, "update destination node info, isEntry %{public}d", isEntry);
    auto pathInfo = AceType::MakeRefPtr<JSNavPathInfo>(name, param, onPop, isEntry);
    pattern->SetNavPathInfo(pathInfo);
}

bool JSNavigationStack::GetNeedUpdatePathInfo(int32_t index)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, false);
    auto path = GetJsPathInfo(index);
    if (path->IsEmpty()) {
        return false;
    }
    auto needUpdate = path->GetProperty("needUpdate");
    if (!needUpdate->IsBoolean()) {
        return false;
    }
    return needUpdate->ToBoolean();
}

void JSNavigationStack::SetNeedUpdatePathInfo(int32_t index, bool need)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    auto path = GetJsPathInfo(index);
    if (path->IsEmpty()) {
        return;
    }
    path->SetProperty<bool>("needUpdate", need);
}

void JSNavigationStack::RecoveryNavigationStack()
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    navPathList_ = preNavPathList_;
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    JSRef<JSArray> pathArray = JSRef<JSArray>::New();
    for (int32_t index = 0; index < static_cast<int32_t>(navPathList_.size()); index++) {
        auto node = navPathList_[index].second;
        auto navDestinationGroupNode = AceType::DynamicCast<NG::NavDestinationGroupNode>(
            NG::NavigationGroupNode::GetNavDestinationNode(node));
        if (!navDestinationGroupNode) {
            continue;
        }
        auto pattern = AceType::DynamicCast<NG::NavDestinationPattern>(navDestinationGroupNode->GetPattern());
        if (!pattern) {
            continue;
        }
        auto context = pattern->GetNavDestinationContext();
        if (!context) {
            continue;
        }
        JSRef<JSObject> item = CreatePathInfoWithNecessaryProperty(context);
        pathArray->SetValueAt(index, item);
    }
    dataSourceObj_->SetPropertyObject("pathArray", pathArray);
}

bool JSNavigationStack::NeedBuildNewInstance(int32_t index)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, false);
    auto pathInfo = GetJsPathInfo(index);
    if (pathInfo->IsEmpty()) {
        return false;
    }
    auto needBuildNewInstance = pathInfo->GetProperty("needBuildNewInstance");
    if (!needBuildNewInstance->IsBoolean()) {
        return false;
    }
    return needBuildNewInstance->ToBoolean();
}

void JSNavigationStack::SetNeedBuildNewInstance(int32_t index, bool need)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    auto pathInfo = GetJsPathInfo(index);
    if (pathInfo->IsEmpty()) {
        return;
    }
    pathInfo->SetProperty<bool>("needBuildNewInstance", need);
}

JSRef<JSArray> JSNavigationStack::GetJsPathArray()
{
    if (dataSourceObj_->IsEmpty()) {
        return JSRef<JSArray>();
    }
    auto objArray = dataSourceObj_->GetProperty("pathArray");
    if (!objArray->IsArray()) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "navPathArray invalid!");
        return JSRef<JSArray>();
    }
    return JSRef<JSArray>::Cast(objArray);
}

JSRef<JSObject> JSNavigationStack::GetJsPathInfo(int32_t index)
{
    auto navPathArray = GetJsPathArray();
    int32_t len = static_cast<int32_t>(navPathArray->Length());
    if (index < 0 || index >= len) {
        return JSRef<JSObject>();
    }
    auto pathInfo = navPathArray->GetValueAt(index);
    if (!pathInfo->IsObject()) {
        return JSRef<JSObject>();
    }
    return JSRef<JSObject>::Cast(pathInfo);
}

JSRef<JSObject> JSNavigationStack::CreatePathInfoWithNecessaryProperty(
    const RefPtr<NG::NavDestinationContext>& context)
{
    auto pathInfo = JSRef<JSObject>::New();
    CHECK_NULL_RETURN(context, pathInfo);
    auto jsPathInfo = AceType::DynamicCast<JSNavPathInfo>(context->GetNavPathInfo());
    CHECK_NULL_RETURN(jsPathInfo, pathInfo);

    pathInfo->SetProperty<std::string>("name", jsPathInfo->GetName());
    pathInfo->SetProperty<int32_t>("index", context->GetIndex());
    pathInfo->SetProperty<std::string>("navDestinationId", std::to_string(context->GetNavDestinationId()));
    pathInfo->SetProperty<bool>("isEntry", jsPathInfo->GetIsEntry());
    pathInfo->SetPropertyObject("param", jsPathInfo->GetParam());
    pathInfo->SetPropertyObject("onPop", jsPathInfo->GetOnPop());
    return pathInfo;
}

} // namespace OHOS::Ace::Framework
