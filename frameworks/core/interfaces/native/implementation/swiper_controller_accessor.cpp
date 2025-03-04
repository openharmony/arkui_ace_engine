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
namespace SwiperControllerAccessor {
void DestroyPeerImpl(Ark_SwiperController peer)
{
}
Ark_SwiperController CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void ShowNextImpl(Ark_SwiperController peer)
{
}
void ShowPreviousImpl(Ark_SwiperController peer)
{
}
void ChangeIndex0Impl(Ark_SwiperController peer,
                      const Ark_Number* index,
                      const Opt_Boolean* useAnimation)
{
}
void ChangeIndex1Impl(Ark_SwiperController peer,
                      const Ark_Number* index,
                      const Ark_Union_SwiperAnimationMode_Boolean* animationMode)
{
}
void FinishAnimationImpl(Ark_SwiperController peer,
                         const Opt_VoidCallback* callback_)
{
}
void PreloadItemsImpl(Ark_VMContext vmContext,
                      Ark_AsyncWorkerPtr asyncWorker,
                      Ark_SwiperController peer,
                      const Opt_Array_Number* indices,
                      const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
} // SwiperControllerAccessor
const GENERATED_ArkUISwiperControllerAccessor* GetSwiperControllerAccessor()
{
    static const GENERATED_ArkUISwiperControllerAccessor SwiperControllerAccessorImpl {
        SwiperControllerAccessor::DestroyPeerImpl,
        SwiperControllerAccessor::CtorImpl,
        SwiperControllerAccessor::GetFinalizerImpl,
        SwiperControllerAccessor::ShowNextImpl,
        SwiperControllerAccessor::ShowPreviousImpl,
        SwiperControllerAccessor::ChangeIndex0Impl,
        SwiperControllerAccessor::ChangeIndex1Impl,
        SwiperControllerAccessor::FinishAnimationImpl,
        SwiperControllerAccessor::PreloadItemsImpl,
    };
    return &SwiperControllerAccessorImpl;
}

}
