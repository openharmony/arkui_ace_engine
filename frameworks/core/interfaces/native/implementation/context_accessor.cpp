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
namespace Common_ContextAccessor {
void DestroyPeerImpl(Ark_common_Context peer)
{
}
Ark_common_Context CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_common_Context CreateBundleContextImpl(Ark_VMContext vmContext,
                                           Ark_common_Context peer,
                                           const Ark_String* bundleName)
{
    return {};
}
Ark_common_Context CreateModuleContext0Impl(Ark_VMContext vmContext,
                                            Ark_common_Context peer,
                                            const Ark_String* moduleName)
{
    return {};
}
Ark_common_Context CreateModuleContext1Impl(Ark_VMContext vmContext,
                                            Ark_common_Context peer,
                                            const Ark_String* bundleName,
                                            const Ark_String* moduleName)
{
    return {};
}
void GetGroupDir0Impl(Ark_VMContext vmContext,
                      Ark_common_Context peer,
                      const Ark_String* dataGroupID,
                      const Context_getGroupDir_Callback* callback_)
{
}
Ark_String GetGroupDir1Impl(Ark_VMContext vmContext,
                            Ark_common_Context peer,
                            const Ark_String* dataGroupID)
{
    return {};
}
Ark_String GetCacheDirImpl(Ark_common_Context peer)
{
    return {};
}
void SetCacheDirImpl(Ark_common_Context peer,
                     const Ark_String* cacheDir)
{
}
Ark_String GetTempDirImpl(Ark_common_Context peer)
{
    return {};
}
void SetTempDirImpl(Ark_common_Context peer,
                    const Ark_String* tempDir)
{
}
Ark_String GetFilesDirImpl(Ark_common_Context peer)
{
    return {};
}
void SetFilesDirImpl(Ark_common_Context peer,
                     const Ark_String* filesDir)
{
}
Ark_String GetDatabaseDirImpl(Ark_common_Context peer)
{
    return {};
}
void SetDatabaseDirImpl(Ark_common_Context peer,
                        const Ark_String* databaseDir)
{
}
Ark_String GetPreferencesDirImpl(Ark_common_Context peer)
{
    return {};
}
void SetPreferencesDirImpl(Ark_common_Context peer,
                           const Ark_String* preferencesDir)
{
}
Ark_String GetBundleCodeDirImpl(Ark_common_Context peer)
{
    return {};
}
void SetBundleCodeDirImpl(Ark_common_Context peer,
                          const Ark_String* bundleCodeDir)
{
}
Ark_String GetDistributedFilesDirImpl(Ark_common_Context peer)
{
    return {};
}
void SetDistributedFilesDirImpl(Ark_common_Context peer,
                                const Ark_String* distributedFilesDir)
{
}
Ark_String GetResourceDirImpl(Ark_common_Context peer)
{
    return {};
}
void SetResourceDirImpl(Ark_common_Context peer,
                        const Ark_String* resourceDir)
{
}
Ark_String GetCloudFileDirImpl(Ark_common_Context peer)
{
    return {};
}
void SetCloudFileDirImpl(Ark_common_Context peer,
                         const Ark_String* cloudFileDir)
{
}
} // Common_ContextAccessor
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
} // ContextAccessor
const GENERATED_ArkUICommon_ContextAccessor* GetCommon_ContextAccessor()
{
    static const GENERATED_ArkUICommon_ContextAccessor Common_ContextAccessorImpl {
        Common_ContextAccessor::DestroyPeerImpl,
        Common_ContextAccessor::CtorImpl,
        Common_ContextAccessor::GetFinalizerImpl,
        Common_ContextAccessor::CreateBundleContextImpl,
        Common_ContextAccessor::CreateModuleContext0Impl,
        Common_ContextAccessor::CreateModuleContext1Impl,
        Common_ContextAccessor::GetGroupDir0Impl,
        Common_ContextAccessor::GetGroupDir1Impl,
        Common_ContextAccessor::GetCacheDirImpl,
        Common_ContextAccessor::SetCacheDirImpl,
        Common_ContextAccessor::GetTempDirImpl,
        Common_ContextAccessor::SetTempDirImpl,
        Common_ContextAccessor::GetFilesDirImpl,
        Common_ContextAccessor::SetFilesDirImpl,
        Common_ContextAccessor::GetDatabaseDirImpl,
        Common_ContextAccessor::SetDatabaseDirImpl,
        Common_ContextAccessor::GetPreferencesDirImpl,
        Common_ContextAccessor::SetPreferencesDirImpl,
        Common_ContextAccessor::GetBundleCodeDirImpl,
        Common_ContextAccessor::SetBundleCodeDirImpl,
        Common_ContextAccessor::GetDistributedFilesDirImpl,
        Common_ContextAccessor::SetDistributedFilesDirImpl,
        Common_ContextAccessor::GetResourceDirImpl,
        Common_ContextAccessor::SetResourceDirImpl,
        Common_ContextAccessor::GetCloudFileDirImpl,
        Common_ContextAccessor::SetCloudFileDirImpl,
    };
    return &Common_ContextAccessorImpl;
}

const GENERATED_ArkUIContextAccessor* GetContextAccessor()
{
    static const GENERATED_ArkUIContextAccessor ContextAccessorImpl {
        ContextAccessor::DestroyPeerImpl,
        ContextAccessor::CtorImpl,
        ContextAccessor::GetFinalizerImpl,
    };
    return &ContextAccessorImpl;
}

}
