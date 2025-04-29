/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ContextAccessor {
void DestroyPeerImpl(Ark_Context peer)
{
}
Ark_Context CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Context CreateBundleContextImpl(Ark_VMContext vmContext,
                                    Ark_Context peer,
                                    const Ark_String* bundleName)
{
    return {};
}
Ark_Context CreateModuleContext0Impl(Ark_VMContext vmContext,
                                     Ark_Context peer,
                                     const Ark_String* moduleName)
{
    return {};
}
Ark_Context CreateModuleContext1Impl(Ark_VMContext vmContext,
                                     Ark_Context peer,
                                     const Ark_String* bundleName,
                                     const Ark_String* moduleName)
{
    return {};
}
void GetGroupDir0Impl(Ark_VMContext vmContext,
                      Ark_Context peer,
                      const Ark_String* dataGroupID,
                      const Context_getGroupDir_Callback* callback_)
{
}
Ark_String GetGroupDir1Impl(Ark_VMContext vmContext,
                            Ark_Context peer,
                            const Ark_String* dataGroupID)
{
    return {};
}
Ark_String GetCacheDirImpl(Ark_Context peer)
{
    return {};
}
void SetCacheDirImpl(Ark_Context peer,
                     const Ark_String* cacheDir)
{
}
Ark_String GetTempDirImpl(Ark_Context peer)
{
    return {};
}
void SetTempDirImpl(Ark_Context peer,
                    const Ark_String* tempDir)
{
}
Ark_String GetFilesDirImpl(Ark_Context peer)
{
    return {};
}
void SetFilesDirImpl(Ark_Context peer,
                     const Ark_String* filesDir)
{
}
Ark_String GetDatabaseDirImpl(Ark_Context peer)
{
    return {};
}
void SetDatabaseDirImpl(Ark_Context peer,
                        const Ark_String* databaseDir)
{
}
Ark_String GetPreferencesDirImpl(Ark_Context peer)
{
    return {};
}
void SetPreferencesDirImpl(Ark_Context peer,
                           const Ark_String* preferencesDir)
{
}
Ark_String GetBundleCodeDirImpl(Ark_Context peer)
{
    return {};
}
void SetBundleCodeDirImpl(Ark_Context peer,
                          const Ark_String* bundleCodeDir)
{
}
Ark_String GetDistributedFilesDirImpl(Ark_Context peer)
{
    return {};
}
void SetDistributedFilesDirImpl(Ark_Context peer,
                                const Ark_String* distributedFilesDir)
{
}
Ark_String GetResourceDirImpl(Ark_Context peer)
{
    return {};
}
void SetResourceDirImpl(Ark_Context peer,
                        const Ark_String* resourceDir)
{
}
Ark_String GetCloudFileDirImpl(Ark_Context peer)
{
    return {};
}
void SetCloudFileDirImpl(Ark_Context peer,
                         const Ark_String* cloudFileDir)
{
}
} // ContextAccessor
const GENERATED_ArkUIContextAccessor* GetContextAccessor()
{
    static const GENERATED_ArkUIContextAccessor ContextAccessorImpl {
        ContextAccessor::DestroyPeerImpl,
        ContextAccessor::CtorImpl,
        ContextAccessor::GetFinalizerImpl,
        ContextAccessor::CreateBundleContextImpl,
        ContextAccessor::CreateModuleContext0Impl,
        ContextAccessor::CreateModuleContext1Impl,
        ContextAccessor::GetGroupDir0Impl,
        ContextAccessor::GetGroupDir1Impl,
        ContextAccessor::GetCacheDirImpl,
        ContextAccessor::SetCacheDirImpl,
        ContextAccessor::GetTempDirImpl,
        ContextAccessor::SetTempDirImpl,
        ContextAccessor::GetFilesDirImpl,
        ContextAccessor::SetFilesDirImpl,
        ContextAccessor::GetDatabaseDirImpl,
        ContextAccessor::SetDatabaseDirImpl,
        ContextAccessor::GetPreferencesDirImpl,
        ContextAccessor::SetPreferencesDirImpl,
        ContextAccessor::GetBundleCodeDirImpl,
        ContextAccessor::SetBundleCodeDirImpl,
        ContextAccessor::GetDistributedFilesDirImpl,
        ContextAccessor::SetDistributedFilesDirImpl,
        ContextAccessor::GetResourceDirImpl,
        ContextAccessor::SetResourceDirImpl,
        ContextAccessor::GetCloudFileDirImpl,
        ContextAccessor::SetCloudFileDirImpl,
    };
    return &ContextAccessorImpl;
}

}
