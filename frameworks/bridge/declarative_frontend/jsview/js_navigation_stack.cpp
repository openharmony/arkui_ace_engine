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
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_model.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::Framework {

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
    dataSourceObj_ = dataSourceObj;
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
    auto func = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("removeName"));
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
    JSRef<JSVal> params[2];
    params[0] = JSRef<JSVal>::Make(ToJSValue(name));
    params[1] = param;
    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext_, nullptr);
    NG::ScopedViewStackProcessor scopedViewStackProcessor;
    navDestBuilderFunc_->Call(JSRef<JSObject>(), 2, params);
    auto node = NG::ViewStackProcessor::GetInstance()->Finish();
    if (CheckNavDestinationNodeInUINode(node)) {
        return node;
    }
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
    if (CheckNavDestinationNodeInUINode(node)) {
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

bool JSNavigationStack::CheckNavDestinationNodeInUINode(RefPtr<NG::UINode> node)
{
    while (node) {
        if (node->GetTag() == V2::JS_VIEW_ETS_TAG) {
            auto customNode = AceType::DynamicCast<NG::CustomNode>(node);
            // render, and find deep further
            customNode->Render();
        } else if (node->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
            return true;
        }
        auto children = node->GetChildren();
        node = children.front();
    }
    return false;
}
} // namespace OHOS::Ace::Framework
