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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UI_EVENT_FUNC_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UI_EVENT_FUNC_H

#include <memory>
#include <string>
#include <unordered_map>

#include "ui_event_observer.h"
#include "utils.h"

namespace OHOS::Ace {
using RegisterUIEventObserverFunc = void (*)(const std::string&, const std::shared_ptr<UIEventObserver>&);
using UnregisterUIEventObserverFunc = void (*)(const std::shared_ptr<UIEventObserver>&);
using GetNodePropertyFunc = void (*)(const std::string&, std::unordered_map<std::string, std::string>&);
using GetSimplifiedInspectorTreeFunc = void (*)(const TreeParams&, std::string&);
using GetSimplifiedInspectorTreeAsyncFunc = void (*)(const TreeParams&, OnInspectorTreeResult&&);

class UIEventFunc final {
public:
    static void RegisterUIEventObserver(const std::string& config, const std::shared_ptr<UIEventObserver>& observer);

    static void UnregisterUIEventObserver(const std::shared_ptr<UIEventObserver>& observer);

    static void GetNodeProperty(
        const std::string& pageUrl, std::unordered_map<std::string, std::string>& nodeProperties);

    static void GetSimplifiedInspectorTree(const TreeParams& params, std::string& tree);

    static void GetSimplifiedInspectorTreeAsync(const TreeParams& params, OnInspectorTreeResult&& callback);

    bool IsAvailable() const;

private:
    static UIEventFunc& Get();
    UIEventFunc();
    ~UIEventFunc();
    UIEventFunc(const UIEventFunc&) = delete;
    const UIEventFunc& operator=(const UIEventFunc&) = delete;
    inline void ResetFunc();
    RegisterUIEventObserverFunc registerFunc_;
    UnregisterUIEventObserverFunc unregisterFunc_;
    GetNodePropertyFunc getPropFunc_;
    GetSimplifiedInspectorTreeFunc getTreeFunc_;
    GetSimplifiedInspectorTreeAsyncFunc getTreeAsyncFunc_;
    LIBHANDLE handle_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UI_EVENT_FUNC_H
