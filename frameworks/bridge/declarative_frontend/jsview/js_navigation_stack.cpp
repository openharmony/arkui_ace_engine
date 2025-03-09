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
#include "bridge/declarative_frontend/engine/js_converter.h"
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
constexpr int32_t INVALID_DESTINATION_MODE = -1;
constexpr char JS_STRINGIFIED_UNDEFINED[] = "undefined";
constexpr char JS_NAV_PATH_STACK_GETNATIVESTACK_FUNC[] = "getNativeStack";
constexpr char JS_NAV_PATH_STACK_SETPARENT_FUNC[] = "setParent";

napi_env GetNapiEnv()
{
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, nullptr);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, nullptr);
    return reinterpret_cast<napi_env>(nativeEngine);
}
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
    dataSourceObj_ = dataSourceObj;
    // add callback to new JSNavPathStack
    RemoveStack();
    UpdateOnStateChangedCallback(dataSourceObj_, onStateChangedCallback_);
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
            JSRef<JSVal> params[1];
            params[0] = JSRef<JSVal>::Make(ToJSValue(name));
            auto funcArray = getFunc->Call(dataSourceObj_, 1, params);
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

bool JSNavigationStack::CreateNodeByIndex(int32_t index, const WeakPtr<NG::UINode>& customNode,
    RefPtr<NG::UINode>& node)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, false);
    auto pathInfo = GetJsPathInfo(index);
    auto name = pathInfo->GetPropertyValue<std::string>("name", "");
    auto param = pathInfo->GetProperty("param");
    RefPtr<NG::UINode> targetNode;
    RefPtr<NG::NavDestinationGroupNode> desNode;
    NG::ScopedViewStackProcessor scopedViewStackProcessor;
    int32_t errorCode = LoadDestination(name, param, customNode, targetNode, desNode);
    // isRemove true, set destination info, false, current destination create failed
    bool isRemove = RemoveDestinationIfNeeded(pathInfo, errorCode, index);
    if (!isRemove) {
        return false;
    }
    if (errorCode != ERROR_CODE_NO_ERROR) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "can't find target destination by index, create empty node");
        node = AceType::DynamicCast<NG::UINode>(NavDestinationModel::GetInstance()->CreateEmpty());
        return true;
    }
    node = targetNode;
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
    return true;
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
        oss << ret;
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
    stack->SetOnPopCallback([weakStack = AceType::WeakClaim(this)](const JSRef<JSVal>& param) {
        auto navigationStack = weakStack.Upgrade();
        CHECK_NULL_VOID(navigationStack);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(navigationStack->executionContext_);
        auto size = navigationStack->GetSize();
        if (size == 0) {
            return;
        }
        auto pathInfo = navigationStack->GetJsPathInfo(size - 1);
        if (pathInfo->IsEmpty()) {
            return;
        }
        auto navDestinationId = pathInfo->GetProperty("navDestinationId");
        if (!navDestinationId->IsString()) {
            return;
        }
        auto id = navDestinationId->ToString();
        auto navPathList = navigationStack->GetAllNavDestinationNodes();
        for (auto iter : navPathList) {
            if (navigationStack->ExecutePopCallback(iter.second, std::atoi(id.c_str()), param)) {
                return;
            }
        }
    });
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

void JSNavigationStack::RemoveInvalidPage(int32_t index)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto removeInvalidPage = dataSourceObj_->GetProperty("removeInvalidPage");
    if (removeInvalidPage->IsFunction()) {
        auto func = JSRef<JSFunc>::Cast(removeInvalidPage);
        JSRef<JSVal> params[1] = { JSRef<JSVal>::Make(ToJSValue(index)) };
        func->Call(dataSourceObj_, 1, params);
    }
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
    CHECK_NULL_RETURN(container, ERROR_CODE_INTERNAL_ERROR);
    auto navigationRoute = container->GetNavigationRoute();
    if (!navigationRoute) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation route is invalid");
        return ERROR_CODE_INTERNAL_ERROR;
    }
    if (!navigationRoute->HasLoaded(name) && navigationRoute->LoadPage(name) != 0) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "load page failed: %{public}s", name.c_str());
        return navDestBuilderFunc_->IsEmpty() ? ERROR_CODE_BUILDER_FUNCTION_NOT_REGISTERED
            : ERROR_CODE_DESTINATION_NOT_FOUND;
    }
    int32_t result = ExecuteBuilderByConfig(name, customNode, param);
    if (result != ERROR_CODE_NO_ERROR) {
        return result;
    }
    node = NG::ViewStackProcessor::GetInstance()->Finish();
    if (!GetNavDestinationNodeInUINode(node, desNode)) {
        return ERROR_CODE_DESTINATION_NOT_FOUND;
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t JSNavigationStack::ExecuteBuilderByConfig(const std::string& name,
    const WeakPtr<NG::UINode>& customNode, const JSRef<JSVal>& param)
{
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

std::string JSNavigationStack::GetStringifyParamByIndex(int32_t index) const
{
    auto env = GetNapiEnv();
    if (!env) {
        return JS_STRINGIFIED_UNDEFINED;
    }
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(env, &scope);
    if (scope == nullptr) {
        return JS_STRINGIFIED_UNDEFINED;
    }
    if (dataSourceObj_->IsEmpty()) {
        napi_close_handle_scope(env, scope);
        return JS_STRINGIFIED_UNDEFINED;
    }
    napi_value navPathStack = JsConverter::ConvertJsValToNapiValue(dataSourceObj_);
    napi_value getParamByIndex;
    napi_get_named_property(env, navPathStack, "getParamByIndex", &getParamByIndex);
    napi_value napiIndex;
    napi_create_int32(env, index, &napiIndex);
    napi_value param;
    napi_call_function(env, navPathStack, getParamByIndex, 1, &napiIndex, &param);

    napi_value globalValue;
    napi_get_global(env, &globalValue);
    napi_value jsonClass;
    napi_get_named_property(env, globalValue, "JSON", &jsonClass);
    napi_value stringifyFunc;
    napi_get_named_property(env, jsonClass, "stringify", &stringifyFunc);
    napi_value stringifyParam;
    if (napi_call_function(env, jsonClass, stringifyFunc, 1, &param, &stringifyParam) != napi_ok) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "Can not stringify current param!");
        napi_get_and_clear_last_exception(env, &stringifyParam);
        napi_close_handle_scope(env, scope);
        return JS_STRINGIFIED_UNDEFINED;
    }
    size_t len = 0;
    napi_get_value_string_utf8(env, stringifyParam, nullptr, 0, &len);
    std::unique_ptr<char[]> paramChar = std::make_unique<char[]>(len + 1);
    napi_get_value_string_utf8(env, stringifyParam, paramChar.get(), len + 1, &len);
    napi_close_handle_scope(env, scope);
    return paramChar.get();
}

void JSNavigationStack::SetPathArray(const std::vector<NG::NavdestinationRecoveryInfo>& navdestinationsInfo)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    JSRef<JSArray> newPathArray = JSRef<JSArray>::New();
    for (int32_t index = 0; index < static_cast<int32_t>(navdestinationsInfo.size()); ++index) {
        auto infoName = navdestinationsInfo[index].name;
        auto infoParam = navdestinationsInfo[index].param;
        auto infoMode = navdestinationsInfo[index].mode;

        JSRef<JSObject> navPathInfo = JSRef<JSObject>::New();
        navPathInfo->SetProperty<std::string>("name", infoName);
        if (!infoParam.empty() && infoParam != JS_STRINGIFIED_UNDEFINED) {
            navPathInfo->SetPropertyObject("param", JSRef<JSObject>::New()->ToJsonObject(infoParam.c_str()));
        }
        navPathInfo->SetProperty<bool>("fromRecovery", true);
        navPathInfo->SetProperty<int32_t>("mode", infoMode);
        newPathArray->SetValueAt(index, navPathInfo);
    }
    dataSourceObj_->SetPropertyObject("pathArray", newPathArray);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "Set navPathArray by recovery info success");
}

bool JSNavigationStack::IsFromRecovery(int32_t index)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, false);
    auto pathInfo = GetJsPathInfo(index);
    if (pathInfo->IsEmpty()) {
        return false;
    }
    auto fromRecovery = pathInfo->GetProperty("fromRecovery");
    if (!fromRecovery->IsBoolean()) {
        return false;
    }
    return fromRecovery->ToBoolean();
}

void JSNavigationStack::SetFromRecovery(int32_t index, bool fromRecovery)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    auto pathInfo = GetJsPathInfo(index);
    if (pathInfo->IsEmpty()) {
        return;
    }
    pathInfo->SetProperty<bool>("fromRecovery", fromRecovery);
}

int32_t JSNavigationStack::GetRecoveredDestinationMode(int32_t index)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, 0);
    auto pathInfo = GetJsPathInfo(index);
    if (pathInfo->IsEmpty()) {
        return INVALID_DESTINATION_MODE;
    }
    auto mode = pathInfo->GetProperty("mode");
    if (!mode->IsNumber()) {
        return INVALID_DESTINATION_MODE;
    }
    return mode->ToNumber<int32_t>();
}

std::string JSNavigationStack::ErrorToMessage(int32_t code)
{
    switch (code) {
        case ERROR_CODE_INTERNAL_ERROR:
            return "Internal error.";
        case ERROR_CODE_DESTINATION_NOT_FOUND:
            return "NavDestination not found.";
        case ERROR_CODE_BUILDER_FUNCTION_NOT_REGISTERED:
            return "Builder function not registered.";
        case ERROR_CODE_PARAM_INVALID:
            return "Paramter error.";
        default:
            return "Error code is not supported.";
    }
}

bool JSNavigationStack::RemoveDestinationIfNeeded(const JSRef<JSObject>& pathInfo, int32_t errorCode, int32_t index)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, false);
    if (!pathInfo->HasProperty("promise")) {
        // not use pushDestination， return true
        return true;
    }
    auto promise = pathInfo->GetProperty("promise");
    if (!promise->IsFunction()) {
        return true;
    }
    auto promiseFunc = JSRef<JSFunc>::Cast(promise);
    if (errorCode == ERROR_CODE_NO_ERROR) {
        JSRef<JSVal> params[1];
        params[0] = JSRef<JSVal>::Make(ToJSValue(errorCode));
        promiseFunc->Call(dataSourceObj_, 1, params);
        return true;
    }
    // push destination failed, remove page in pathStack
    RemoveInvalidPage(index);
    const int32_t argc = 2;
    JSRef<JSVal> params[argc];
    JSRef<JSObject> errorInfo = JSRef<JSObject>::New();
    params[0] = JSRef<JSVal>::Make(ToJSValue(errorCode));
    params[1] = JSRef<JSVal>::Make(ToJSValue(ErrorToMessage(errorCode)));
    promiseFunc->Call(dataSourceObj_, argc, params);
    return false;
}

bool JSNavigationStack::CheckIsReplacedDestination(int32_t index, std::string& replacedName, int32_t& replacedIndex)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, false);
    auto pathInfo = GetJsPathInfo(index);
    if (pathInfo->IsEmpty()) {
        return false;
    }
    auto recoveryFromReplaceDestination = pathInfo->GetProperty("recoveryFromReplaceDestination");
    if (!recoveryFromReplaceDestination->IsBoolean() || !recoveryFromReplaceDestination->ToBoolean()) {
        return false;
    }
    auto jsReplacedName = pathInfo->GetProperty("name");
    if (!jsReplacedName->IsString()) {
        return false;
    }
    replacedName = jsReplacedName->ToString();
    auto jsReplacedIndex = pathInfo->GetProperty("index");
    if (!jsReplacedIndex->IsNumber()) {
        return false;
    }
    replacedIndex = jsReplacedIndex->ToNumber<int32_t>();
    return true;
}

void JSNavigationStack::SetRecoveryFromReplaceDestination(int32_t index, bool value)
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    auto pathInfo = GetJsPathInfo(index);
    if (pathInfo->IsEmpty()) {
        return;
    }
    pathInfo->SetProperty<bool>("recoveryFromReplaceDestination", value);
}

bool JSNavigationStack::ExecutePopCallback(const RefPtr<NG::UINode>& uiNode,
    uint64_t navDestinationId, const JSRef<JSVal>& param)
{
    auto navDestinationNode = AceType::DynamicCast<NG::NavDestinationGroupNode>(
        NG::NavigationGroupNode::GetNavDestinationNode(uiNode));
    CHECK_NULL_RETURN(navDestinationNode, false);
    auto pattern = navDestinationNode->GetPattern<NG::NavDestinationPattern>();
    CHECK_NULL_RETURN(pattern, false);
    if (pattern->GetNavDestinationId() != navDestinationId) {
        return false;
    }
    auto navPathInfo = AceType::DynamicCast<JSNavPathInfo>(pattern->GetNavPathInfo());
    CHECK_NULL_RETURN(navPathInfo, false);
    auto callback = navPathInfo->GetNavDestinationPopCallback();
    if (callback->IsEmpty()) {
        return false;
    }
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "fire onPop callback: %{public}s", pattern->GetName().c_str());
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, false);
    JSRef<JSVal> params[1];
    params[0] = param;
    callback->Call(JSRef<JSObject>(), 1, params);
    return true;
}

bool JSNavigationStack::HasSingletonMoved()
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, false);
    if (dataSourceObj_->IsEmpty()) {
        return false;
    }
    auto hasSingletonMoved = dataSourceObj_->GetProperty("hasSingletonMoved");
    if (!hasSingletonMoved->IsBoolean()) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "hasSingletonMoved invalid!");
        return false;
    }
    return hasSingletonMoved->ToBoolean();
}

bool JSNavigationStack::IsTopFromSingletonMoved()
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, false);
    auto len = GetSize();
    if (len == 0) {
        return false;
    }
    auto top = GetJsPathInfo(len - 1);
    if (top->IsEmpty()) {
        return false;
    }
    auto isFromSingletonMoved = top->GetProperty("singletonMoved");
    if (!isFromSingletonMoved->IsBoolean()) {
        return false;
    }
    return isFromSingletonMoved->ToBoolean();
}

void JSNavigationStack::ResetSingletonMoved()
{
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_);
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto hasSingletonMoved = dataSourceObj_->GetProperty("hasSingletonMoved");
    if (!hasSingletonMoved->IsBoolean() || !hasSingletonMoved->ToBoolean()) {
        return;
    }
    auto len = GetSize();
    for (auto index = 0; index < len; index++) {
        auto info = GetJsPathInfo(index);
        if (info->IsEmpty()) {
            continue;
        }
        info->SetProperty<bool>("singletonMoved", false);
    }
    dataSourceObj_->SetProperty<bool>("hasSingletonMoved", false);
}
} // namespace OHOS::Ace::Framework
