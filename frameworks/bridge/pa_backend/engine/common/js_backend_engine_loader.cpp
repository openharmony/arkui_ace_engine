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

#include "frameworks/bridge/pa_backend/engine/common/js_backend_engine_loader.h"

#include <dlfcn.h>

#include "base/log/log.h"
#include "base/utils/singleton.h"
#include "base/utils/system_properties.h"
#include "core/common/ace_application_info.h"

namespace OHOS::Ace::Framework {
namespace {
constexpr char BACKEND_ENGINE_ENTRY[] = "OHOS_ACE_GetJsBackendEngineLoader";
constexpr char QUICK_JS_PA_ENGINE_SHARED_LIB[] = "libace_engine_pa_qjs.z.so";

using DynamicEntry = void* (*)();
class DummyJsBackendEngineLoader final : public JsBackendEngineLoader, public Singleton<DummyJsBackendEngineLoader> {
    DECLARE_SINGLETON(DummyJsBackendEngineLoader);

public:
    RefPtr<JsBackendEngine> CreateJsBackendEngine(int32_t instanceId) const override
    {
        return nullptr;
    }
};

DummyJsBackendEngineLoader::DummyJsBackendEngineLoader() = default;
DummyJsBackendEngineLoader::~DummyJsBackendEngineLoader() = default;

const char* GetSharedLibrary()
{
    return QUICK_JS_PA_ENGINE_SHARED_LIB;
}

JsBackendEngineLoader& GetJsBackendEngineLoader(const char* sharedLibrary)
{
    void* handle = dlopen(sharedLibrary, RTLD_LAZY);
    if (handle == nullptr) {
        LOGE("Failed to open shared library %{public}s, reason: %{public}sn", sharedLibrary, dlerror());
        return DummyJsBackendEngineLoader::GetInstance();
    }

    auto entry = reinterpret_cast<DynamicEntry>(dlsym(handle, BACKEND_ENGINE_ENTRY));
    if (entry == nullptr) {
        dlclose(handle);
        LOGE("Failed to get symbol %{public}s in %{public}s", BACKEND_ENGINE_ENTRY, sharedLibrary);
        return DummyJsBackendEngineLoader::GetInstance();
    }

    auto loader = reinterpret_cast<JsBackendEngineLoader*>(entry());
    if (loader == nullptr) {
        dlclose(handle);
        LOGE("Failed to get js engine loader in %{public}s", sharedLibrary);
        return DummyJsBackendEngineLoader::GetInstance();
    }

    return *loader;
}
} // namespace
JsBackendEngineLoader& JsBackendEngineLoader::Get()
{
    static JsBackendEngineLoader& instance = GetJsBackendEngineLoader(GetSharedLibrary());
    return instance;
}
} // namespace OHOS::Ace::Framework
