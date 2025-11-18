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

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TimePickerDialogAccessor {
void DestroyPeerImpl(Ark_TimePickerDialog peer)
{
}
Ark_TimePickerDialog ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
} // TimePickerDialogAccessor
const GENERATED_ArkUITimePickerDialogAccessor* GetTimePickerDialogAccessor()
{
    static const GENERATED_ArkUITimePickerDialogAccessor TimePickerDialogAccessorImpl {
        TimePickerDialogAccessor::DestroyPeerImpl,
        TimePickerDialogAccessor::ConstructImpl,
        TimePickerDialogAccessor::GetFinalizerImpl,
    };
    return &TimePickerDialogAccessorImpl;
}

}
