/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "interfaces/inner_api/ace/ui_event.h"

#include "ui_event_func.h"
#include "ui_event_observer.h"

namespace OHOS::Ace {
void UIEvent::RegisterUIEventObserver(const std::string& config, const std::shared_ptr<UIEventObserver>& observer)
{
    UIEventFunc::RegisterUIEventObserver(config, observer);
}

void UIEvent::UnregisterUIEventObserver(const std::shared_ptr<UIEventObserver>& observer)
{
    UIEventFunc::UnregisterUIEventObserver(observer);
}

void UIEvent::GetNodeProperty(
    const std::string& pageUrl, std::unordered_map<std::string, std::string>& nodeProperties)
{
    UIEventFunc::GetNodeProperty(pageUrl, nodeProperties);
}

void UIEvent::GetSimplifiedInspectorTree(std::string& tree)
{
    UIEventFunc::GetSimplifiedInspectorTree({ false }, tree);
}

void UIEvent::GetSimplifiedInspectorTree(const TreeParams& params, std::string& tree)
{
    UIEventFunc::GetSimplifiedInspectorTree(params, tree);
}

void UIEvent::GetSimplifiedInspectorTreeAsync(const TreeParams& params, OnInspectorTreeResult&& callback)
{
    UIEventFunc::GetSimplifiedInspectorTreeAsync(params, std::move(callback));
}
} // namespace OHOS::Ace
