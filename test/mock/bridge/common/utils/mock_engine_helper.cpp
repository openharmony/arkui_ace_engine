/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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


#include <mutex>
#include <shared_mutex>
#include <unordered_map>

#include "bridge/common/utils/engine_helper.h"
#include "test/mock/core/common/mock_container.h"

namespace OHOS::Ace {
namespace {
const int32_t INSTANCE_ID = 1000;
}

std::shared_mutex EngineHelper::mutex_;
std::unordered_map<int32_t, WeakPtr<Framework::JsEngine>> EngineHelper::engineWeakMap_;

ScopedDelegate::ScopedDelegate(Framework::FrontendDelegate* delegate, int32_t id)
    : delegate_(delegate), scope_(new ContainerScope(id))
{}

ScopedDelegate::~ScopedDelegate() {}

void EngineHelper::AddEngine(int32_t id, WeakPtr<Framework::JsEngine> engine) {}

RefPtr<Framework::JsEngine> EngineHelper::GetEngine(int32_t id)
{
    return nullptr;
}

void EngineHelper::RemoveEngine(int32_t id) {}

RefPtr<Framework::JsEngine> EngineHelper::GetCurrentEngine()
{
    return GetEngine(Container::CurrentId());
}

ScopedDelegate EngineHelper::GetCurrentDelegate()
{
    return { nullptr, INSTANCE_ID };
}

} // namespace OHOS::Ace
