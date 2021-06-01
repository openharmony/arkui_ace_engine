/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_customview_base.h"

#include "base/log/ace_trace.h"

namespace OHOS::Ace::Framework {

JSCustomViewBase::JSCustomViewBase()
{
    LOGD("JSCustomViewBase constructor");
};

JSCustomViewBase::~JSCustomViewBase()
{
    LOGD("Destroy JSCustomViewBase");
};

void JSCustomViewBase::Destroy(JSViewAbstract* parentCustomView)
{
    LOGD("JSCustomViewBase::Destroy start");
    for (auto child : customViewChildren_) {
        child.second->Destroy(this);
    }
#ifdef USE_V8_ENGINE
    for (auto child : jsCustomViewChildren_) {
        child.second.Reset();
    }
#endif
    JSViewAbstract::Destroy(parentCustomView);
    LOGD("JSCustomViewBase::Destroy end");
}

void JSCustomViewBase::CleanUpAbandonedChild()
{
    auto startIter = customViewChildren_.begin();
    auto endIter = customViewChildren_.end();
    auto startJsIter = jsCustomViewChildren_.begin();
    std::vector<std::string> removedViewIds;
    while (startIter != endIter) {
        auto found = lastAccessedViewIds_.find(startIter->first);
        if (found == lastAccessedViewIds_.end()) {
            LOGD(" found abandoned view with id %s", startIter->first.c_str());
            removedViewIds.emplace_back(startIter->first);
            startIter->second->Destroy(this);
#ifdef USE_V8_ENGINE
            startJsIter->second.Reset();
#endif
#ifdef USE_QUICKJS_ENGINE
            JS_FreeValue(ctx_, startJsIter->second);
#endif
        }
        ++startIter;
        ++startJsIter;
    }

    for (auto& viewId : removedViewIds) {
        customViewChildren_.erase(viewId);
        jsCustomViewChildren_.erase(viewId);
    }

    lastAccessedViewIds_.clear();
}

bool JSCustomViewBase::FindChildById(const std::string& viewId)
{
    return jsCustomViewChildren_.find(ProcessViewId(viewId)) != jsCustomViewChildren_.end();
}

#ifdef USE_V8_ENGINE
std::pair<JSViewAbstract*, v8::Local<v8::Value>> JSCustomViewBase::GetChildById(const std::string& viewId)
{
    auto id = ProcessViewId(viewId);
    auto found = jsCustomViewChildren_.find(id);
    if (found != jsCustomViewChildren_.end()) {
        ChildAccessedById(id);
        return std::make_pair(customViewChildren_.find(id)->second, found->second.Get(v8::Isolate::GetCurrent()));
    }
    return std::make_pair(nullptr, v8::Object::New(v8::Isolate::GetCurrent()));
}
#elif USE_QUICKJS_ENGINE
std::pair<JSViewAbstract*, JSValue> JSCustomViewBase::GetChildById(const std::string& viewId)
{
    auto id = ProcessViewId(viewId);
    auto found = jsCustomViewChildren_.find(id);
    if (found != jsCustomViewChildren_.end()) {
        ChildAccessedById(id);
        return std::make_pair(customViewChildren_.find(id)->second, found->second);
    }
    return std::make_pair(nullptr, JS_UNDEFINED);
}
#endif

#ifdef USE_V8_ENGINE
void JSCustomViewBase::AddChildById(const std::string& viewId, JSViewAbstract* view, v8::Local<v8::Object> obj)
{
    auto id = ProcessViewId(viewId);
    customViewChildren_.emplace(id, view);
    jsCustomViewChildren_.emplace(id, V8Handle(v8::Isolate::GetCurrent(), obj));
    ChildAccessedById(id);
}
#elif USE_QUICKJS_ENGINE
void JSCustomViewBase::AddChildById(const std::string& viewId, JSViewAbstract* view, JSValue obj)
{
    auto id = ProcessViewId(viewId);
    customViewChildren_.emplace(id, view);
    jsCustomViewChildren_.emplace(id, obj);
    ChildAccessedById(id);
}
#endif

void JSCustomViewBase::ChildAccessedById(const std::string& viewId)
{
    lastAccessedViewIds_.emplace(viewId);
}

std::string JSCustomViewBase::ProcessViewId(const std::string& viewId)
{
    return forEachKey_.empty() ? viewId : forEachKey_ + "_" + viewId;
}

} // namespace OHOS::Ace::Framework
