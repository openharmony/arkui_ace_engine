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

#include "bridge/arkts_frontend/arkts_frontend_loader.h"

namespace OHOS::Ace {
namespace {
const char* CREATE_ARKTS_FRONTEND = "OHOS_ACE_CreateArktsFrontend";
const char* CREATE_ARKTS_PLUGIN_FRONTEND = "OHOS_ACE_CreateArktsPluginFrontend";
const char* CREATE_ANI_REFERENCE = "OHOS_ACE_CreateAniReference";
const char* DELETE_ANI_REFERENCE = "OHOS_ACE_DeleteAniReference";
const char* ARKTS_FRONTEND_LIB = "libarkts_frontend.z.so";
}

Frontend* ArktsFrontendLoader::CreatArkTsFrontend(const void* sharedRuntime)
{
    if (!sharedRuntime) {
        return nullptr;
    }
    if (!createArktsFrontendFunc_) {
        createArktsFrontendFunc_ =
            reinterpret_cast<CreateArktsFrontendFunc>(LoadSymbol(CREATE_ARKTS_FRONTEND));
    }
    CHECK_NULL_RETURN(createArktsFrontendFunc_, nullptr);

    return createArktsFrontendFunc_(sharedRuntime);
}

void* ArktsFrontendLoader::CreateAniReference(const void* runtime, const void* storage)
{
    if (!runtime || !storage) {
        return nullptr;
    }

    if (!createAniReferenceFunc_) {
        createAniReferenceFunc_ =
            reinterpret_cast<CreateAniReferenceFunc>(LoadSymbol(CREATE_ANI_REFERENCE));
    }
    CHECK_NULL_RETURN(createAniReferenceFunc_, nullptr);

    return createAniReferenceFunc_(runtime, storage);
}

void ArktsFrontendLoader::DeleteAniReference(const void* runtime, const void* storage)
{
    if (!runtime || !storage) {
        return;
    }

    if (!deleteAniReferenceFunc_) {
        deleteAniReferenceFunc_ =
            reinterpret_cast<DeleteAniReferenceFunc>(LoadSymbol(DELETE_ANI_REFERENCE));
    }
    CHECK_NULL_VOID(deleteAniReferenceFunc_);

    deleteAniReferenceFunc_(runtime, storage);
}

PluginFrontend* ArktsFrontendLoader::CreateArktsPluginFrontend(const void* sharedRuntime)
{
    if (!sharedRuntime) {
        return nullptr;
    }
    if (!createArktsPluginFrontendFunc_) {
        createArktsPluginFrontendFunc_ =
            reinterpret_cast<CreateArktsPluginFrontendFunc>(LoadSymbol(CREATE_ARKTS_PLUGIN_FRONTEND));
    }
    CHECK_NULL_RETURN(createArktsPluginFrontendFunc_, nullptr);

    return createArktsPluginFrontendFunc_(sharedRuntime);
}

void ArktsFrontendLoader::CloseLibrary()
{
    if (dlclose(handle_) != 0) {
        return;
    }
    handle_ = nullptr;
    createArktsFrontendFunc_ = nullptr;
    createAniReferenceFunc_ = nullptr;
    deleteAniReferenceFunc_ = nullptr;
    createArktsPluginFrontendFunc_ = nullptr;
}

void* ArktsFrontendLoader::LoadSymbol(const char* symName)
{
    CHECK_NULL_RETURN(handle_, nullptr);
    return dlsym(handle_, symName);
}

bool ArktsFrontendLoader::DynamicLoadLibrary()
{
    if (!handle_) {
        handle_ = dlopen(ARKTS_FRONTEND_LIB, RTLD_LAZY);
        CHECK_NULL_RETURN(handle_, false);
    }
    return true;
}
} // namespace OHOS::Ace