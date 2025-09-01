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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ARKTS_FRONTEND_LOADER_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ARKTS_FRONTEND_LOADER_H

#include <memory>
#include <string>

#include "base/utils/macros.h"
#include "bridge/plugin_frontend/plugin_frontend.h"
#include "core/common/frontend.h"
#include "interfaces/inner_api/ace/utils.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace {
using CreateArktsFrontendFunc = Frontend* (*)(const void*);
using CreateArktsPluginFrontendFunc = PluginFrontend* (*)(const void*);
using CreateAniReferenceFunc = void* (*)(const void*, const void*);
using DeleteAniReferenceFunc = void (*)(const void*, const void*);

class ACE_FORCE_EXPORT ArktsFrontendLoader {
public:
    static ArktsFrontendLoader& GetInstance()
    {
        static ArktsFrontendLoader instance;
        return instance;
    }
    Frontend* CreatArkTsFrontend(const void* sharedRuntime);
    void* CreateAniReference(const void* runtime, const void* storage);
    void DeleteAniReference(const void* runtime, const void* storage);
    PluginFrontend* CreateArktsPluginFrontend(const void* sharedRuntime);

private:
    ArktsFrontendLoader()
    {
        DynamicLoadLibrary();
    }

    ~ArktsFrontendLoader()
    {
        CloseLibrary();
    }
    void CloseLibrary();
    void* LoadSymbol(const char* symName);
    bool DynamicLoadLibrary();

    LIBHANDLE handle_ = nullptr;
    CreateArktsFrontendFunc createArktsFrontendFunc_ = nullptr;
    CreateAniReferenceFunc createAniReferenceFunc_ = nullptr;
    DeleteAniReferenceFunc deleteAniReferenceFunc_ = nullptr;
    CreateArktsPluginFrontendFunc createArktsPluginFrontendFunc_ = nullptr;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ARKTS_FRONTEND_LODER_H
