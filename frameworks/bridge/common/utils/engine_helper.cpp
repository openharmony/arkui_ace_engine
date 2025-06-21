/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "bridge/common/utils/engine_helper.h"

#include "base/log/ace_checker.h"
#include "base/subwindow/subwindow_manager.h"

namespace OHOS::Ace {
std::shared_mutex EngineHelper::mutex_;
std::unordered_map<int32_t, WeakPtr<Framework::JsEngine>> EngineHelper::engineWeakMap_;

std::function<void(int32_t)> EngineHelper::removeUIContextFunc_;

ScopedDelegate::ScopedDelegate(const RefPtr<Framework::FrontendDelegate>& delegate, int32_t id)
    : delegate_(delegate), scope_(new ContainerScope(id))
{}

ScopedDelegate::~ScopedDelegate()
{
    delete scope_;
    scope_ = nullptr;
}

void EngineHelper::AddEngine(int32_t id, WeakPtr<Framework::JsEngine> engine)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    engineWeakMap_.emplace(id, engine);
}

RefPtr<Framework::JsEngine> EngineHelper::GetEngine(int32_t id)
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    if (id >= MIN_SUBCONTAINER_ID && id < MIN_PLUGIN_SUBCONTAINER_ID) {
        id = SubwindowManager::GetInstance()->GetParentContainerId(id);
    }
    auto iter = engineWeakMap_.find(id);
    if (iter != engineWeakMap_.end()) {
        return iter->second.Upgrade();
    }
    return nullptr;
}

void EngineHelper::RemoveEngine(int32_t id)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    engineWeakMap_.erase(id);

    if (removeUIContextFunc_) {
        removeUIContextFunc_(id);
    }
}

RefPtr<Framework::JsEngine> EngineHelper::GetCurrentEngine()
{
    return GetEngine(Container::CurrentId());
}

RefPtr<Framework::JsEngine> EngineHelper::GetCurrentEngineSafely()
{
    return GetEngine(Container::CurrentIdSafely());
}

ScopedDelegate EngineHelper::GetCurrentDelegate()
{
    auto engine = GetCurrentEngine();
    if (engine) {
        return { engine->GetFrontend(), Container::CurrentId() };
    }
    auto container = Container::GetActive();
    return GetDelegateByContainer(container);
}

ScopedDelegate EngineHelper::GetCurrentDelegateSafely()
{
    auto engine = GetCurrentEngineSafely();
    if (engine) {
        return { engine->GetFrontend(), Container::CurrentIdSafely() };
    }
    auto container = Container::CurrentSafely();
    return GetDelegateByContainer(container);
}

ScopedDelegate EngineHelper::GetDefaultDelegate()
{
    auto engine = GetCurrentEngine();
    if (engine) {
        return { engine->GetFrontend(), Container::CurrentId() };
    }
    auto container = Container::GetDefault();
    return GetDelegateByContainer(container);
}

ScopedDelegate EngineHelper::GetDelegateByContainer(RefPtr<Container> container)
{
    if (!container) {
        return { nullptr, -1 };
    }
    auto engine = GetEngine(container->GetInstanceId());
    return { engine ? engine->GetFrontend() : nullptr, container->GetInstanceId() };
}

std::tuple<std::string, int32_t, int32_t> EngineHelper::GetPositionOnJsCode()
{
    if (!AceChecker::IsPerformanceCheckEnabled()) {
        return {"", 0, 0 };
    }
    auto jsEngine = GetCurrentEngine();
    std::string stack;
    CHECK_NULL_RETURN(jsEngine, std::make_tuple("", 0, 0));
    jsEngine->GetStackTrace(stack);
    std::regex reg("([^|]+)\\|([^|]+)\\|[^|]+\\|([^:]+):(\\d+):(\\d+)");
    std::smatch match;
    if (std::regex_search(stack, match, reg)) {
        std::string filePath = match[2].str() + "/" + match[3].str();
        return {
            filePath,
            StringUtils::StringToInt(match[4].str()),
            StringUtils::StringToInt(match[5].str())
        };
    }
    return {"", 0, 0 };
}

void EngineHelper::RegisterRemoveUIContextFunc(const std::function<void(int32_t)>& removeUIContextFunc)
{
    if (!removeUIContextFunc_) {
        removeUIContextFunc_ = removeUIContextFunc;
    }
}
} // namespace OHOS::Ace
