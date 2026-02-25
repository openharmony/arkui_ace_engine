/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SWIPER_CONTROLLER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SWIPER_CONTROLLER_PEER_IMPL_H

#include <optional>
#include "base/error/error_code.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/swiper/swiper_controller.h"
#include "arkoala_api_generated.h"

#ifdef WINDOWS_PLATFORM
#include <windows.h>
inline void* LoadLibrary()
{
    const char* libPath = "libArkoalaNative_ark.dll";
    return LoadLibraryA(libPath);
}
inline void* FindSymbol(void* library, const char* name)
{
    return (void*)GetProcAddress(reinterpret_cast<HMODULE>(library), name);
}
#else
#include <dlfcn.h>
inline void* LoadLibrary()
{
    const char* libPath = "libArkoalaNative_ark.z.so";
    void* handle = dlopen(libPath, RTLD_LOCAL | RTLD_LAZY);
    if (!handle) {
        return nullptr;
    }
    return handle;
}
inline void* FindSymbol(void* library, const char* name)
{
    return dlsym(library, name);
}
#endif

namespace OHOS::Ace::NG::GeneratedModifier {
using AniThrowErrorFunc = void (*)(Ark_VMContext vmContext, int32_t errCode, const std::string& errorMsg);
class SwiperControllerPeerImpl : public Referenced {
public:
    SwiperControllerPeerImpl() = default;

    void AddTargetController(const WeakPtr<SwiperController> &handler)
    {
        CHECK_NULL_VOID(!handler.Invalid());
        handler_ = handler;
    }

    void TriggerShowNext()
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->ShowNext();
        }
    }

    void TriggerShowPrevious()
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->ShowPrevious();
        }
    }

    void SetFinishCallback(const CommonFunc &callbackFunc)
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->SetFinishCallback(callbackFunc);
        }
    }

    void TriggerFinishAnimation()
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->FinishAnimation();
        }
    }

    void TriggerChangeIndex(int32_t index, const SwiperAnimationMode& animationMode)
    {
        index = index < 0 ? 0 : index;
        if (auto controller = handler_.Upgrade(); controller) {
            controller->ChangeIndex(index, animationMode);
        }
    }

    void TriggerPreloadItems(const std::set<int32_t>& indexSet) const
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->PreloadItems(indexSet);
        }
    }

    void TriggerSetPreloadFinishCallback(PreloadItemsFinishFunc&& preloadFinishCallback) const
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->SetPreloadFinishCallback(preloadFinishCallback);
        } else {
            SwiperControllerPeerImpl::ThrowError(ERROR_CODE_NAMED_ROUTE_ERROR, "Controller not bound to component.");
        }
    }

    bool TriggerStartFakeDrag() const
    {
        if (auto controller = handler_.Upgrade(); controller) {
            return controller->StartFakeDrag();
        }
        return false;
    }

    bool TriggerFakeDragBy(float offset) const
    {
        if (auto controller = handler_.Upgrade(); controller) {
            return controller->FakeDragBy(offset);
        }
        return false;
    }

    bool TriggerStopFakeDrag() const
    {
        if (auto controller = handler_.Upgrade(); controller) {
            return controller->StopFakeDrag();
        }
        return false;
    }

    bool TriggerIsFakeDragging() const
    {
        if (auto controller = handler_.Upgrade(); controller) {
            return controller->IsFakeDragging();
        }
        return false;
    }

    static void ThrowError(int32_t errCode, const std::string& errorMsg)
    {
        auto container = Container::CurrentSafely();
        CHECK_NULL_VOID(container);
        auto frontEnd = container->GetFrontend();
        CHECK_NULL_VOID(frontEnd);
        if (!frontEnd->GetEnv() && container->GetSubFrontend()) {
            frontEnd = container->GetSubFrontend(); // return ArktsFrontend when 1.1 hybrid 1.2
        }
        auto vmContext = Ark_VMContext(frontEnd->GetEnv());
        CHECK_NULL_VOID(vmContext);
        auto handle = LoadLibrary();
        CHECK_NULL_VOID(handle);
        auto aniErrorFunc = reinterpret_cast<AniThrowErrorFunc>(FindSymbol(handle, "AniThrowError"));
        CHECK_NULL_VOID(aniErrorFunc);
        aniErrorFunc(vmContext, errCode, errorMsg);
    }
private:
    Ace::WeakPtr<SwiperController> handler_;
};
} // namespace OHOS::Ace::NG::GeneratedModifier

struct SwiperControllerPeer : public OHOS::Ace::NG::GeneratedModifier::SwiperControllerPeerImpl {};
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SWIPER_CONTROLLER_PEER_IMPL_H
