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

#ifndef OHOS_OBSERVER_H
#define OHOS_OBSERVER_H

#include <list>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

#include "observer_listener.h"

#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/observer_handler.h"

namespace OHOS {
namespace Rosen {

class CJObserver final {
public:
    CJObserver() = delete;
    ~CJObserver() = delete;

    static void RegisterScrollEventCallback(int64_t callbackId);
    static void RegisterScrollEventCallback(const std::string& id, int64_t callbackId);
    static void UnRegisterScrollEventCallback(int64_t callbackId);
    static void UnRegisterScrollEventCallback(const std::string& id, int64_t callbackId);
    static void HandleScrollEventStateChange(
        const std::string& id, int32_t uniqueId, Ace::NG::ScrollEventType eventType, float offset, Ace::Axis axis);

    static void RegisterTabContentUpdateCallback(int64_t callbackId);
    static void RegisterTabContentUpdateCallback(const std::string& id, int64_t callbackId);
    static void UnRegisterTabContentUpdateCallback(int64_t callbackId);
    static void UnRegisterTabContentUpdateCallback(const std::string& id, int64_t callbackId);
    static void HandleTabContentUpdateStateChange(const Ace::NG::TabContentInfo& tabContentInfo);

private:
    static std::unordered_map<int64_t, std::shared_ptr<CJObserverListener>> scrollEventListeners_;
    static std::unordered_map<std::string, std::unordered_map<int64_t, std::shared_ptr<CJObserverListener>>>
        specifiedScrollEventListeners_;

    static std::unordered_map<int64_t, std::shared_ptr<CJObserverListener>> tabContentUpdateListeners_;
    static std::unordered_map<std::string, std::unordered_map<int64_t, std::shared_ptr<CJObserverListener>>>
        specifiedTabContentUpdateListeners_;
};

} // namespace Rosen
} // namespace OHOS

#endif // OHOS_OBSERVER_H