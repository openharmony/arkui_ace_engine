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

#include "utilengine_fuzzer.h"

#include <securec.h>
#include "test/fuzztest/utilengine_fuzzer/utilengine_fuzzer.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine_loader.h"

namespace OHOS {
    using namespace OHOS::Ace;
    constexpr char DECLARATIVE_ENGINE_SHARED_LIB[] = "libace_engine_declarative_ark.z.so";
    constexpr int sizeInt = 4;
    bool DoSomethingInterestingWithMyAPI(const uint8_t* data, size_t size)
    {
        bool result = false;
        uint32_t id = 0;
        if (size < sizeInt) {
            return false;
        }
        memcpy_s(&id, sizeof(uint32_t), data, sizeof(uint32_t));
        auto& loader = Framework::JsEngineLoader::GetDeclarative(DECLARATIVE_ENGINE_SHARED_LIB);
        auto jsEngine = loader.CreateJsEngine(id);
        EngineHelper::AddEngine(id, jsEngine);
        EngineHelper::GetEngine(id);
        EngineHelper::RemoveEngine(id);
        EngineHelper::GetCurrentEngine();
        return result;
    }
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    OHOS::DoSomethingInterestingWithMyAPI(data, size);
    return 0;
}

