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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_UTILS_ENGINE_HELPER_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_UTILS_ENGINE_HELPER_H

#include <mutex>
#include <shared_mutex>

#include "core/common/container.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "bridge/js_frontend/engine/common/js_engine.h"
#include "bridge/js_frontend/frontend_delegate.h"

namespace OHOS::Ace {
class ContainerScope;

class ACE_FORCE_EXPORT ScopedDelegate final {
public:
    ScopedDelegate(const RefPtr<Framework::FrontendDelegate>& delegate, int32_t id);
    ~ScopedDelegate();

    Framework::FrontendDelegate* operator->() const
    {
        return AceType::RawPtr(delegate_);
    }

    bool operator==(std::nullptr_t) const
    {
        return delegate_ == nullptr;
    }

    operator bool() const
    {
        return delegate_ != nullptr;
    }

private:
    RefPtr<Framework::FrontendDelegate> delegate_;
    ContainerScope* scope_;
};

class ACE_FORCE_EXPORT EngineHelper final {
public:
    static void AddEngine(int32_t id, WeakPtr<Framework::JsEngine> engine);

    static RefPtr<Framework::JsEngine> GetEngine(int32_t id);

    static void RemoveEngine(int32_t id);

    static RefPtr<Framework::JsEngine> GetCurrentEngine();

    static RefPtr<Framework::JsEngine> GetCurrentEngineSafely();

    static ScopedDelegate GetCurrentDelegate();

    static ScopedDelegate GetCurrentDelegateSafely();

    static ScopedDelegate GetDefaultDelegate();

    static std::tuple<std::string, int32_t, int32_t> GetPositionOnJsCode();

    static ScopedDelegate GetDelegateByContainer(RefPtr<Container> container);

    static void RegisterRemoveUIContextFunc(const std::function<void(int32_t)>& removeUIContextFunc);

private:

    static std::unordered_map<int32_t, WeakPtr<Framework::JsEngine>> engineWeakMap_;
    static std::shared_mutex mutex_;

    static std::function<void(int32_t)> removeUIContextFunc_;

    ACE_DISALLOW_COPY_AND_MOVE(EngineHelper);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_UTILS_ENGINE_HELPER_H
