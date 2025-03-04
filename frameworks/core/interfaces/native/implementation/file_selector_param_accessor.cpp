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
namespace FileSelectorParamAccessor {
void DestroyPeerImpl(Ark_FileSelectorParam peer)
{
}
Ark_FileSelectorParam CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetTitleImpl(Ark_FileSelectorParam peer)
{
    return {};
}
Ark_FileSelectorMode GetModeImpl(Ark_FileSelectorParam peer)
{
    return {};
}
Array_String GetAcceptTypeImpl(Ark_FileSelectorParam peer)
{
    return {};
}
Ark_Boolean IsCaptureImpl(Ark_FileSelectorParam peer)
{
    return {};
}
} // FileSelectorParamAccessor
const GENERATED_ArkUIFileSelectorParamAccessor* GetFileSelectorParamAccessor()
{
    static const GENERATED_ArkUIFileSelectorParamAccessor FileSelectorParamAccessorImpl {
        FileSelectorParamAccessor::DestroyPeerImpl,
        FileSelectorParamAccessor::CtorImpl,
        FileSelectorParamAccessor::GetFinalizerImpl,
        FileSelectorParamAccessor::GetTitleImpl,
        FileSelectorParamAccessor::GetModeImpl,
        FileSelectorParamAccessor::GetAcceptTypeImpl,
        FileSelectorParamAccessor::IsCaptureImpl,
    };
    return &FileSelectorParamAccessorImpl;
}

}
