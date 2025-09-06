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
namespace PersistentStorageBackendAccessor {
Opt_String GetImpl(const Ark_String* key)
{
    return {};
}
Ark_Boolean HasImpl(const Ark_String* key)
{
    return {};
}
void RemoveImpl(const Ark_String* key)
{
}
void SetImpl(const Ark_String* key,
             const Ark_String* value)
{
}
void ClearImpl()
{
}
} // PersistentStorageBackendAccessor
const GENERATED_ArkUIPersistentStorageBackendAccessor* GetPersistentStorageBackendAccessor()
{
    static const GENERATED_ArkUIPersistentStorageBackendAccessor PersistentStorageBackendAccessorImpl {
        PersistentStorageBackendAccessor::GetImpl,
        PersistentStorageBackendAccessor::HasImpl,
        PersistentStorageBackendAccessor::RemoveImpl,
        PersistentStorageBackendAccessor::SetImpl,
        PersistentStorageBackendAccessor::ClearImpl,
    };
    return &PersistentStorageBackendAccessorImpl;
}

}
