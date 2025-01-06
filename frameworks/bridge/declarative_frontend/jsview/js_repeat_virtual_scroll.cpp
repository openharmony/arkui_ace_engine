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

#include "bridge/declarative_frontend/jsview/js_repeat_virtual_scroll.h"

#include <string>

#include "base/log/ace_trace.h"
#include "base/log/log_wrapper.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_model_ng.h"

#define JSFUNC(opts, propName) (JSRef<JSFunc>::Cast((opts)->GetProperty(propName)))

namespace OHOS::Ace {

std::unique_ptr<RepeatVirtualScrollModel> RepeatVirtualScrollModel::instance_ = nullptr;
#define UNUSED_CACHED_SIZE_PARAM 2

RepeatVirtualScrollModel* RepeatVirtualScrollModel::GetInstance()
{
    if (!instance_) {
        instance_.reset(new NG::RepeatVirtualScrollModelNG());
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

enum {
    PARAM_TOTAL_COUNT = 0,
    PARAM_TEMPLATE_OPTS = 1,
    PARAM_HANDLERS = 2,
    MIN_PARAM_SIZE = 3,
};

bool ParseAndVerifyParams(const JSCallbackInfo& info)
{
    if (info.Length() < MIN_PARAM_SIZE) {
        return false;
    }

    if (!info[PARAM_TOTAL_COUNT]->IsNumber()) {
        return false;
    }
    if (!info[PARAM_TEMPLATE_OPTS]->IsArray()) {
        return false;
    }
    if (!info[PARAM_HANDLERS]->IsObject()) {
        return false;
    }

    auto templateOptsArray = JSRef<JSArray>::Cast(info[PARAM_TEMPLATE_OPTS]);
    for (size_t i = 0; i < templateOptsArray->Length(); i++) {
        JSRef<JSArray> pair = templateOptsArray->GetValueAt(i);
        if (!pair->GetValueAt(0)->IsString()) {
            return false;
        }
        if (!pair->GetValueAt(1)->IsObject()) {
            return false;
        }
        auto type = pair->GetValueAt(0)->ToString();
        auto opts = JSRef<JSObject>::Cast(pair->GetValueAt(1));
        if (!opts->GetProperty("cachedCountSpecified")->IsBoolean()) {
            return false;
        }
    }

    auto handlers = JSRef<JSObject>::Cast(info[PARAM_HANDLERS]);
    if (!handlers->GetProperty("onCreateNode")->IsFunction() || !handlers->GetProperty("onUpdateNode")->IsFunction() ||
        !handlers->GetProperty("onGetKeys4Range")->IsFunction() ||
        !handlers->GetProperty("onGetTypes4Range")->IsFunction() ||
        !handlers->GetProperty("onSetActiveRange")->IsFunction()) {
        return false;
    }

    return true;
}

void JSRepeatVirtualScroll::Create(const JSCallbackInfo& info)
{
    if (!ParseAndVerifyParams(info)) {
        TAG_LOGW(AceLogTag::ACE_LAZY_FOREACH, "Invalid arguments for RepeatVirtualScroll");
        return;
    }

    // arg 0
    auto totalCount = info[PARAM_TOTAL_COUNT]->ToNumber<uint32_t>();

    // arg 1
    auto templateOptsArray = JSRef<JSArray>::Cast(info[PARAM_TEMPLATE_OPTS]);
    std::map<std::string, std::pair<bool, uint32_t>> templateCachedCountMap;
    for (size_t i = 0; i < templateOptsArray->Length(); i++) {
        JSRef<JSArray> pair = templateOptsArray->GetValueAt(i);
        auto type = pair->GetValueAt(0)->ToString();
        auto opts = JSRef<JSObject>::Cast(pair->GetValueAt(1));

        templateCachedCountMap[type] =
            opts->GetProperty("cachedCountSpecified")->ToNumber <bool>()
                ? std::pair<bool, uint32_t>(true, opts->GetProperty("cachedCount")->ToNumber<uint32_t>())
                : std::pair<bool, uint32_t>(false, UNUSED_CACHED_SIZE_PARAM);
    }

    // arg 2
    auto handlers = JSRef<JSObject>::Cast(info[PARAM_HANDLERS]);
    auto onCreateNode = [execCtx = info.GetExecutionContext(), func = JSFUNC(handlers, "onCreateNode")](
                            uint32_t forIndex) -> void {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto params = ConvertToJSValues(forIndex);
        func->Call(JSRef<JSObject>(), params.size(), params.data());
    };

    auto onUpdateNode = [execCtx = info.GetExecutionContext(), func = JSFUNC(handlers, "onUpdateNode")](
                            const std::string& fromKey, uint32_t forIndex) -> void {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto params = ConvertToJSValues(fromKey, forIndex);
        func->Call(JSRef<JSObject>(), params.size(), params.data());
    };

    auto onGetKeys4Range = [execCtx = info.GetExecutionContext(), func = JSFUNC(handlers, "onGetKeys4Range")](
                               uint32_t from, uint32_t to) -> std::list<std::string> {
        std::list<std::string> list;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, list);
        auto params = ConvertToJSValues(from, to);
        JSRef<JSVal> jsVal = func->Call(JSRef<JSObject>(), params.size(), params.data());
        // convert js-array to std::list
        if (!jsVal->IsArray()) {
            TAG_LOGW(AceLogTag::ACE_REPEAT, "jsVal should be array.");
            return list;
        }
        JSRef<JSArray> jsArr = JSRef<JSArray>::Cast(jsVal);
        for (size_t i = 0; i < jsArr->Length(); i++) {
            list.emplace_back(jsArr->GetValueAt(i)->ToString());
        }
        return list;
    };

    auto onGetTypes4Range = [execCtx = info.GetExecutionContext(), func = JSFUNC(handlers, "onGetTypes4Range")](
                                uint32_t from, uint32_t to) -> std::list<std::string> {
        std::list<std::string> list;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, list);
        auto params = ConvertToJSValues(from, to);
        JSRef<JSVal> jsVal = func->Call(JSRef<JSObject>(), params.size(), params.data());

        // convert js-array to std::list
        if (!jsVal->IsArray()) {
            TAG_LOGW(AceLogTag::ACE_REPEAT, "jsVal should be array.");
            return list;
        }
        JSRef<JSArray> jsArr = JSRef<JSArray>::Cast(jsVal);
        for (size_t i = 0; i < jsArr->Length(); i++) {
            list.emplace_back(jsArr->GetValueAt(i)->ToString());
        }
        return list;
    };

    auto onSetActiveRange = [execCtx = info.GetExecutionContext(), func = JSFUNC(handlers, "onSetActiveRange")](
                            int32_t from, int32_t to) -> void {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto params = ConvertToJSValues(from, to);
        func->Call(JSRef<JSObject>(), params.size(), params.data());
    };

    RepeatVirtualScrollModel::GetInstance()->Create(
        totalCount, templateCachedCountMap, onCreateNode, onUpdateNode, onGetKeys4Range, onGetTypes4Range,
        onSetActiveRange);
}

void JSRepeatVirtualScroll::UpdateRenderState(const JSCallbackInfo& info)
{
    ACE_SCOPED_TRACE("RepeatVirtualScroll:UpdateRenderState");
    TAG_LOGD(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll::UpdateRenderState");
    if (!info[0]->IsNumber() || !info[1]->IsBoolean()) {
        return;
    }
    auto totalCount = info[0]->ToNumber<uint32_t>();
    auto visibleItemsChanged = info[1]->ToBoolean();
    RepeatVirtualScrollModel::GetInstance()->UpdateRenderState(totalCount, visibleItemsChanged);
}

void JSRepeatVirtualScroll::OnMove(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        RepeatVirtualScrollModel::GetInstance()->OnMove(nullptr);
        return;
    }
    auto onMove = [execCtx = info.GetExecutionContext(), func = JSRef<JSFunc>::Cast(info[0])](
                      int32_t from, int32_t to) {
        auto params = ConvertToJSValues(from, to);
        func->Call(JSRef<JSObject>(), params.size(), params.data());
    };
    RepeatVirtualScrollModel::GetInstance()->OnMove(std::move(onMove));
}

void JSRepeatVirtualScroll::SetCreateByTemplate(const JSCallbackInfo& info)
{
    if (!info[0]->IsBoolean()) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll::SetCreateByTemplate wrong parameter, internal error.");
        return;
    }
    RepeatVirtualScrollModel::GetInstance()->SetCreateByTemplate(info[0]->ToBoolean());
}

void JSRepeatVirtualScroll::JSBind(BindingTarget globalObj)
{
    JSClass<JSRepeatVirtualScroll>::Declare("RepeatVirtualScrollNative");
    JSClass<JSRepeatVirtualScroll>::StaticMethod("create", &JSRepeatVirtualScroll::Create);
    JSClass<JSRepeatVirtualScroll>::StaticMethod("updateRenderState", &JSRepeatVirtualScroll::UpdateRenderState);
    JSClass<JSRepeatVirtualScroll>::StaticMethod("onMove", &JSRepeatVirtualScroll::OnMove);
    JSClass<JSRepeatVirtualScroll>::StaticMethod("setCreateByTemplate", &JSRepeatVirtualScroll::SetCreateByTemplate);
    JSClass<JSRepeatVirtualScroll>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
