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

#ifndef OHOS_CJ_OBSERVER_LISTENER_H
#define OHOS_CJ_OBSERVER_LISTENER_H

#include <functional>
#include <string>

#include "core/components_ng/base/observer_handler.h"

namespace OHOS {
namespace Rosen {
const std::string EVENT_SCROLL = "scrollEvent";
const std::string EVENT_TAB_CONTENT_UPDATE = "tabContentUpdate";

class CJObserverListener {
public:
    explicit CJObserverListener();
    ~CJObserverListener();
    void AddCallback(const std::string& type, int64_t callbackObject);
    void RemoveAllCallback(const std::string& type);
    void RemoveCallback(const std::string& type, int64_t callbackObject);

    void OnScrollEventStateChange(
        const std::string& id, int32_t uniqueId, Ace::NG::ScrollEventType eventType, float offset, Ace::Axis axis);
    void OnTabContentUpdateStateChange(const Ace::NG::TabContentInfo& tabContentInfo);

private:
    void CallCJMethod(const std::string& methodName, void* argv);
    std::mutex mtx_;
    std::map<std::string, std::map<int64_t, std::function<void(void*)>>> cjCallBack_;
};

} // namespace Rosen
} // namespace OHOS

#endif // OHOS_CJ_OBSERVER_LISTENER_H