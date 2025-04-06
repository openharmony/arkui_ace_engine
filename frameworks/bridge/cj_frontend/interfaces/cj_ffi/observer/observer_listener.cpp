/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "observer_listener.h"

#include "cj_lambda.h"

namespace OHOS {
namespace Rosen {

CJObserverListener::CJObserverListener()
{
    LOGI("Constructor execution");
}

CJObserverListener::~CJObserverListener()
{
    LOGI("Destructor execution");
}

void CJObserverListener::AddCallback(const std::string& type, int64_t callbackObject)
{
    std::lock_guard<std::mutex> lock(mtx_);
    LOGI("CJObserverListener::AddCallback is called with type %{public}s", type.c_str());
    auto callback = CJLambda::Create(reinterpret_cast<void (*)(void*)>(callbackObject));
    cjCallBack_[type][callbackObject] = callback;
}

void CJObserverListener::RemoveAllCallback(const std::string& type)
{
    std::lock_guard<std::mutex> lock(mtx_);
    LOGI("CJObserverListener::RemoveAllCallback is called with type %{public}s", type.c_str());
    auto it = cjCallBack_.find(type);
    if (it == cjCallBack_.end()) {
        LOGE("CJObserverListener::RemoveAllCallback no callback to remove");
        return;
    }
    cjCallBack_.erase(it);
}

void CJObserverListener::RemoveCallback(const std::string& type, int64_t callbackObject)
{
    std::lock_guard<std::mutex> lock(mtx_);
    LOGI("CJObserverListener::RemoveCallback is called with type %{public}s", type.c_str());
    auto it = cjCallBack_.find(type);
    if (it == cjCallBack_.end()) {
        LOGE("CJObserverListener::RemoveCallback no callback to remove");
        return;
    }
    auto& callbacks = it->second;
    for (auto iter = callbacks.begin(); iter != callbacks.end();) {
        if (iter->first == callbackObject) {
            iter = callbacks.erase(iter);
        } else {
            iter++;
        }
    }
    LOGI("CJObserverListener::RemoveCallback success, cjCallBack_ size %{public}u!",
        static_cast<uint32_t>(callbacks.size()));
}

void CJObserverListener::CallCJMethod(const std::string& methodName, void* argv)
{
    if (methodName.empty()) {
        LOGE("Empty method name str, call method failed");
        return;
    }
    LOGI("CallCJMethod methodName = %{public}s", methodName.c_str());
    for (auto callback : cjCallBack_[methodName]) {
        callback.second(argv);
    }
}

void CJObserverListener::OnScrollEventStateChange(
    const std::string& id, int32_t uniqueId, Ace::NG::ScrollEventType eventType, float offset)
{
    std::lock_guard<std::mutex> lock(mtx_);
    LOGI("CJObserverListener::OnScrollEventStateChange is called");
    if (cjCallBack_.empty()) {
        LOGI("CJObserverListener::OnScrollEventStateChange not register!");
        return;
    }
    if (cjCallBack_.find(EVENT_SCROLL) == cjCallBack_.end()) {
        LOGE("CJObserverListener::OnScrollEventStateChange not this event!");
        return;
    }

    struct ScrollEventInfo {
        char* id;
        int32_t uniqueId;
        uint32_t eventType;
        float offset;
    } info = { const_cast<char*>(id.c_str()), uniqueId, static_cast<uint32_t>(eventType), offset };

    CallCJMethod(EVENT_SCROLL, &info);
}

void CJObserverListener::OnTabContentUpdateStateChange(const Ace::NG::TabContentInfo& tabContentInfo)
{
    std::lock_guard<std::mutex> lock(mtx_);
    LOGI("CJObserverListener::OnTabContentUpdateStateChange is called");
    if (cjCallBack_.empty()) {
        LOGI("CJObserverListener::OnTabContentUpdateStateChange not register!");
        return;
    }
    if (cjCallBack_.find(EVENT_TAB_CONTENT_UPDATE) == cjCallBack_.end()) {
        LOGE("CJObserverListener::OnTabContentUpdateStateChange not this event!");
        return;
    }

    struct TabContentInfo {
        char* tabContentId;
        int32_t tabContentUniqueId;
        uint32_t state;
        char* id;
        int32_t uniqueId;
    } info = { const_cast<char*>(tabContentInfo.tabContentId.c_str()), tabContentInfo.tabContentUniqueId,
        static_cast<uint32_t>(tabContentInfo.state), const_cast<char*>(tabContentInfo.id.c_str()),
        tabContentInfo.uniqueId };

    CallCJMethod(EVENT_TAB_CONTENT_UPDATE, &info);
}

} // namespace Rosen
} // namespace OHOS