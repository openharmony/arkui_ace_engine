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

#include "ark_native_engine.h"
#include "napi/native_api.h"
#include "napi/native_common.h"
#include "napi/native_node_api.h"
#include "native_create_env.h"


class NativeEngineMock {
public:
    NativeEngineMock()
    {
        panda::RuntimeOption option;
        option.SetGcType(panda::RuntimeOption::GC_TYPE::GEN_GC);
        const int64_t poolSize = 0x1000000;  // 16M
        option.SetGcPoolSize(poolSize);
        option.SetLogLevel(panda::RuntimeOption::LOG_LEVEL::ERROR);
        option.SetDebuggerLibraryPath("");
        vm_ = panda::JSNApi::CreateJSVM(option);
        if (vm_ == nullptr) {
            return;
        }

        engine_ = new ArkNativeEngine(vm_, nullptr);
        napi_open_handle_scope(reinterpret_cast<napi_env>(engine_), &scope_);
    }

    ~NativeEngineMock()
    {
        napi_close_handle_scope(reinterpret_cast<napi_env>(engine_), scope_);
        scope_ = nullptr;
        delete engine_;
        engine_ = nullptr;
        panda::JSNApi::DestroyJSVM(vm_);
        vm_ = nullptr;
    }

    inline ArkNativeEngine* operator->() const
    {
        return engine_;
    }

    inline operator napi_env() const
    {
        return reinterpret_cast<napi_env>(engine_);
    }

private:
    EcmaVM* vm_ {nullptr};
    ArkNativeEngine* engine_ {nullptr};
    napi_handle_scope scope_ = nullptr;
};