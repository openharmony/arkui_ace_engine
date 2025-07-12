/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <tuple>
#include <string>

#include "dynamic-loader.h"
#include "callbacks.h"
#include "interop-logging.h"
#include "arkoala_api_generated.h"
#include "securec.h"

// TODO: rework for generic OHOS case.
void* FindModule(int kind) {
    std::tuple<const char*, bool> candidates[] = {
        { "ace_compatible", true},
        { "ace", true },
        { "ace_compatible_mock", true},
        { nullptr, false }
    };
    char* envValue = getenv("ACE_LIBRARY_PATH");
    std::string prefix = envValue ? std::string(envValue) : "";
    LOGE("Search ACE in \"%s\" (env ACE_LIBRARY_PATH) for API %d", prefix.c_str(), kind);
    for (auto* candidate = candidates; std::get<0>(*candidate); candidate++) {
        std::string name = std::get<0>(*candidate);
        if (std::get<1>(*candidate)) {
            name = libName(name.c_str());
        }
        std::string libraryName = prefix + "/" + name;
        void* module = loadLibrary(libraryName);
        if (module) {
            LOGE("ACE module at: %s", libraryName.c_str());
            return module;
        } else {}
    }
    return nullptr;
}

static GENERATED_ArkUIAnyAPI* impls[GENERATED_Ark_APIVariantKind::GENERATED_COUNT] = { 0 };
const char* getArkAnyAPIFuncName = "GENERATED_GetArkAnyAPI";

const GENERATED_ArkUIAnyAPI* GetAnyImpl(int kind, int version, std::string* result) {
    if (!impls[kind]) {
        static const GroupLogger* logger = GetDefaultLogger();

        GENERATED_ArkUIAnyAPI* impl = nullptr;
        typedef GENERATED_ArkUIAnyAPI* (*GetAPI_t)(int, int);
        static GetAPI_t getAPI = nullptr;

        char* envValue = getenv("__LIBACE_ENTRY_POINT");
        if (envValue) {
            long long value = strtoll(envValue, NULL, 16);
            if (value != 0) {
                getAPI = reinterpret_cast<GetAPI_t>(static_cast<uintptr_t>(value));
            }
        }
        if (getAPI == nullptr) {
            void* module = FindModule(kind);
            if (!module) {
                if (result)
                    *result = "Cannot find dynamic module";
                else
                    LOG("Cannot find dynamic module");
                return nullptr;
            }
            getAPI = reinterpret_cast<GetAPI_t>(findSymbol(module, getArkAnyAPIFuncName));
            if (!getAPI) {
                if (result)
                    *result = std::string("Cannot find ") + getArkAnyAPIFuncName;
                else
                    LOGE("Cannot find %s", getArkAnyAPIFuncName);
                return nullptr;
            }
        }
        // Provide custom logger and callback caller to loaded libs.
        auto service = (const GenericServiceAPI*)(*getAPI)(GENERIC_SERVICE, GENERIC_SERVICE_API_VERSION);
        if (service) {
            if (logger) service->setLogger(reinterpret_cast<const ServiceLogger*>(logger));
        }

        impl = (*getAPI)(kind, version);
        if (!impl) {
            if (result)
                *result = "getAPI() returned null";
            else
                LOG("getAPI() returned null")
            return nullptr;
        }
        if (impl->version != version) {
            if (result) {
                char buffer[256];
                if (snprintf_s(buffer, sizeof(buffer), sizeof(buffer) - 1,
                    "FATAL: API version mismatch, expected %d got %d", version, impl->version) < 0) {
                    return nullptr;
                }
                *result = buffer;
            } else {
                LOGE("API version mismatch for API %d: expected %d got %d", kind, version, impl->version);
            }
            return nullptr;
        }
        impls[kind] = impl;
    }
    return impls[kind];
}

const GENERATED_ArkUIBasicNodeAPI* GetArkUIBasicNodeAPI() {
    return reinterpret_cast<const GENERATED_ArkUIBasicNodeAPI*>(
        GetAnyImpl(static_cast<int>(GENERATED_Ark_APIVariantKind::GENERATED_BASIC),
        GENERATED_ARKUI_BASIC_NODE_API_VERSION, nullptr));
}

const GENERATED_ArkUIExtendedNodeAPI* GetArkUIExtendedNodeAPI() {
    return reinterpret_cast<const GENERATED_ArkUIExtendedNodeAPI*>(
        GetAnyImpl(static_cast<int>(GENERATED_Ark_APIVariantKind::GENERATED_EXTENDED),
        GENERATED_ARKUI_EXTENDED_NODE_API_VERSION, nullptr));
}