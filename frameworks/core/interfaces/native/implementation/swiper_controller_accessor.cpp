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

#include "swiper_controller_modifier_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/promise_helper.h"

namespace OHOS::Ace::NG {
using SwiperAnimationModeVariantType = std::variant<SwiperAnimationMode, bool>;
}

namespace OHOS::Ace::NG::Converter {
template<>
inline void AssignCast(std::optional<Ark_Function>& dst, const Ark_Function& src)
{
    dst = src;
}

template<>
SwiperAnimationModeVariantType Convert(const Ark_SwiperAnimationMode& src)
{
    auto animationModeOpt = Converter::OptConvert<SwiperAnimationMode>(src);
    SwiperAnimationMode defualtMode = SwiperAnimationMode::NO_ANIMATION;
    return animationModeOpt.value_or(defualtMode);
}

template<>
SwiperAnimationModeVariantType Convert(const Ark_Boolean& src)
{
    return Convert<bool>(src);
}

template<>
inline void AssignCast(std::optional<SwiperAnimationMode>& dst, const Ark_SwiperAnimationMode& src)
{
    switch (src) {
        case SELECTOR_ID_0: dst = SwiperAnimationMode::NO_ANIMATION; break;
        case SELECTOR_ID_1: dst = SwiperAnimationMode::DEFAULT_ANIMATION; break;
        case SELECTOR_ID_2: dst = SwiperAnimationMode::FAST_ANIMATION; break;
        default: LOGE("Unexpected enum value in Ark_SwiperAnimationMode: %{public}d", src);
    }
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SwiperControllerAccessor {
void DestroyPeerImpl(Ark_SwiperController peer)
{
    auto peerImpl = reinterpret_cast<SwiperControllerPeerImpl *>(peer);
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
Ark_SwiperController CtorImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<SwiperControllerPeerImpl>();
    peerImpl->IncRefCount();
    return reinterpret_cast<SwiperControllerPeer *>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void ShowNextImpl(Ark_SwiperController peer)
{
    auto peerImpl = reinterpret_cast<SwiperControllerPeerImpl *>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerShowNext();
}
void ShowPreviousImpl(Ark_SwiperController peer)
{
    auto peerImpl = reinterpret_cast<SwiperControllerPeerImpl *>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerShowPrevious();
}
void ChangeIndex0Impl(Ark_SwiperController peer,
                      const Ark_Number* index,
                      const Opt_Boolean* useAnimation)
{
    auto peerImpl = reinterpret_cast<SwiperControllerPeerImpl *>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(index);
    auto aceIdx = Converter::Convert<Ark_Int32>(*index);
    auto aceUseAnim = useAnimation ? Converter::OptConvert<bool>(*useAnimation) : std::nullopt;
    peerImpl->TriggerChangeIndex(aceIdx, aceUseAnim);
}
void ChangeIndex1Impl(Ark_SwiperController peer,
                      const Ark_Number* index,
                      const Opt_Union_SwiperAnimationMode_Boolean* animationMode)
{
    auto peerImpl = reinterpret_cast<SwiperControllerPeerImpl *>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(index);
    auto aceIdx = Converter::Convert<Ark_Int32>(*index);
    auto optMode = Converter::OptConvert<SwiperAnimationModeVariantType>(*animationMode);
    CHECK_NULL_VOID(optMode);

    if (auto modeStylePtr = std::get_if<SwiperAnimationMode>(&(*optMode)); modeStylePtr) {
        peerImpl->TriggerChangeIndex(aceIdx, *modeStylePtr);
    } else if (auto modeBoolPtr = std::get_if<bool>(&(*optMode)); modeBoolPtr) {
        peerImpl->TriggerChangeIndex(aceIdx, modeBoolPtr);
    } else {
        peerImpl->TriggerChangeIndex(aceIdx, SwiperAnimationMode::NO_ANIMATION);
    }
}
void FinishAnimationImpl(Ark_SwiperController peer,
                         const Opt_VoidCallback* callback_)
{
    auto peerImpl = reinterpret_cast<SwiperControllerPeerImpl *>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto arkCallbackOpt = callback_ ? Converter::OptConvert<VoidCallback>(*callback_) : std::nullopt;
    if (arkCallbackOpt) {
        auto onFinish = [arkCallback = CallbackHelper(*arkCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        peerImpl->SetFinishCallback(onFinish);
    }
    peerImpl->TriggerFinishAnimation();
}
void PreloadItemsImpl(Ark_VMContext vmContext,
                      Ark_AsyncWorkerPtr asyncWorker,
                      Ark_SwiperController peer,
                      const Opt_Array_Number* indices,
                      const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    CHECK_NULL_VOID(asyncWorker);
    auto peerImpl = reinterpret_cast<SwiperControllerPeerImpl *>(peer);
    CHECK_NULL_VOID(peerImpl);

    auto indexVectOpt = !indices ? std::nullopt : Converter::OptConvert<std::vector<int32_t>>(*indices);
    auto execFunc = [peerImpl, indexVectOpt = std::move(indexVectOpt)]() {
        if (indexVectOpt) {
            std::set<int32_t> indexSet(indexVectOpt->begin(), indexVectOpt->end());
            peerImpl->TriggerPreloadItems(indexSet);
        } else {
            peerImpl->TriggerPreloadItems({});
        }
    };
    PromiseHelper promise(outputArgumentForReturningPromise, vmContext, *asyncWorker, std::move(execFunc));

    auto finishFunc = [promise = std::move(promise)](const int32_t errCode, const std::string errStr) {
        if (errCode == ERROR_CODE_NO_ERROR) {
            promise.Resolve();
        } else {
            promise.Reject({std::to_string(errCode), errStr});
        }
    };
    peerImpl->TriggerSetPreloadFinishCallback(finishFunc);
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
