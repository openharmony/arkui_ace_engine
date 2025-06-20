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

#include "bridge/common/utils/engine_helper.h"

namespace OHOS::Ace {
std::shared_mutex EngineHelper::mutex_;
std::unordered_map<int32_t, WeakPtr<Framework::JsEngine>> EngineHelper::engineWeakMap_;

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
    engineWeakMap_.emplace(id, engine);
}

RefPtr<Framework::JsEngine> EngineHelper::GetEngine(int32_t id)
{
    return nullptr;
}

void EngineHelper::RemoveEngine(int32_t id)
{
    engineWeakMap_.erase(id);
}

RefPtr<Framework::JsEngine> EngineHelper::GetCurrentEngine()
{
    return nullptr;
}

RefPtr<Framework::JsEngine> EngineHelper::GetCurrentEngineSafely()
{
    return nullptr;
}

ScopedDelegate EngineHelper::GetCurrentDelegate()
{
    return { nullptr, 0 };
}

ScopedDelegate EngineHelper::GetCurrentDelegateSafely()
{
    return { nullptr, 0 };
}

std::tuple<std::string, int32_t, int32_t> EngineHelper::GetPositionOnJsCode()
{
    return {"", 0, 0 };
}
} // namespace OHOS::Ace
