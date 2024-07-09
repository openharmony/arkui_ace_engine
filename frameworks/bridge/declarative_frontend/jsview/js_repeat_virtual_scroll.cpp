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

RepeatVirtualScrollModel* RepeatVirtualScrollModel::GetInstance()
{
    if (!instance_) {
        instance_.reset(new NG::RepeatVirtualScrollModelNG());
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSRepeatVirtualScroll::Create(const JSCallbackInfo& info)
{
    int8_t numberIndex = 0;
    int8_t arrayIndex = 1;
    int8_t objectIndex = 2;
    if (!info[numberIndex]->IsNumber()) {
        TAG_LOGW(AceLogTag::ACE_REPEAT, "info[0] should be number.");
        return;
    }
    if (!info[arrayIndex]->IsArray()) {
        TAG_LOGW(AceLogTag::ACE_REPEAT, "info[1] should be array.");
        return;
    }
    if (!info[objectIndex]->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_REPEAT, "info[2] should be object.");
        return;
    }

    // arg 0
    auto totalCount = info[0]->ToNumber<uint32_t>();

    // arg 1
    auto templateOptsArray = JSRef<JSArray>::Cast(info[1]);
    std::map<std::string, uint32_t> templateCachedCountMap;
    for (size_t i = 0; i < templateOptsArray->Length(); i++) {
        JSRef<JSArray> pair = templateOptsArray->GetValueAt(i);
        if (!pair->GetValueAt(0)->IsString()) {
            TAG_LOGW(AceLogTag::ACE_REPEAT, "pair->GetValueAt(0) should be string.");
            continue;
        }
        if (!pair->GetValueAt(1)->IsObject()) {
            TAG_LOGW(AceLogTag::ACE_REPEAT, "pair->GetValueAt(1) should be object.");
            continue;
        }
        auto type = pair->GetValueAt(0)->ToString();
        auto opts = JSRef<JSObject>::Cast(pair->GetValueAt(1));
        if (!opts->GetProperty("cachedCount")->IsNumber()) {
            TAG_LOGW(AceLogTag::ACE_REPEAT, "opts->GetProperty(\"cachedCount\") should be number.");
            continue;
        }
        templateCachedCountMap[type] = opts->GetProperty("cachedCount")->ToNumber<uint32_t>();
    }

    // arg 2
    auto handlers = JSRef<JSObject>::Cast(info[2]);
    if (!handlers->GetProperty("onCreateNode")->IsFunction()) {
        TAG_LOGW(AceLogTag::ACE_REPEAT, "handlers->GetProperty(\"onCreateNode\") should be function.");
        return;
    }
    if (!handlers->GetProperty("onUpdateNode")->IsFunction()) {
        TAG_LOGW(AceLogTag::ACE_REPEAT, "handlers->GetProperty(\"onUpdateNode\") should be function.");
        return;
    }
    if (!handlers->GetProperty("onGetKeys4Range")->IsFunction()) {
        TAG_LOGW(AceLogTag::ACE_REPEAT, "handlers->GetProperty(\"onGetKeys4Range\") should be function.");
        return;
    }
    if (!handlers->GetProperty("onGetTypes4Range")->IsFunction()) {
        TAG_LOGW(AceLogTag::ACE_REPEAT, "handlers->GetProperty(\"onGetTypes4Range\") should be function.");
        return;
    }

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

    RepeatVirtualScrollModel::GetInstance()->Create(
        totalCount, templateCachedCountMap, onCreateNode, onUpdateNode, onGetKeys4Range, onGetTypes4Range);
}

void JSRepeatVirtualScroll::InvalidateKeyCache(const JSCallbackInfo& info)
{
    ACE_SCOPED_TRACE("RepeatVirtualScroll:InvalidateKeyCache");
    TAG_LOGD(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll::InvalidateKeyCache");
    if (info[0]->IsNumber()) {
        auto totalCount = info[0]->ToNumber<uint32_t>();
        RepeatVirtualScrollModel::GetInstance()->InvalidateKeyCache(totalCount);
    } else {
        TAG_LOGW(AceLogTag::ACE_REPEAT, "info[0] should be number.");
    }
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

void JSRepeatVirtualScroll::JSBind(BindingTarget globalObj)
{
    JSClass<JSRepeatVirtualScroll>::Declare("RepeatVirtualScrollNative");
    JSClass<JSRepeatVirtualScroll>::StaticMethod("create", &JSRepeatVirtualScroll::Create);
    JSClass<JSRepeatVirtualScroll>::StaticMethod("invalidateKeyCache", &JSRepeatVirtualScroll::InvalidateKeyCache);
    JSClass<JSRepeatVirtualScroll>::StaticMethod("onMove", &JSRepeatVirtualScroll::OnMove);
    JSClass<JSRepeatVirtualScroll>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
