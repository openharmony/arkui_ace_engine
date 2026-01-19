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

#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"
#include "core/interfaces/native/implementation/drawing_canvas_peer_impl.h"
#include "drawing_rendering_context_peer_impl.h"
#include "canvas_rendering_context2d_peer_impl.h"
#ifdef WINDOWS_PLATFORM
const char* LIBARKOALA_MODULE = "libArkoalaNative_ark.dll";
#else
const char* LIBARKOALA_MODULE = "libArkoalaNative_ark.z.so";
#endif
#ifdef WINDOWS_PLATFORM
#include <windows.h>
inline void* LoadLibrary(const char* libPath)
{
    return LoadLibraryA(libPath);
}
inline void* FindSymbol(void* library, const char* name)
{
    return (void*)GetProcAddress(reinterpret_cast<HMODULE>(library), name);
}
#else
#include <dlfcn.h>
inline void* LoadLibrary(const char* libPath)
{
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

DrawingRenderingContextPeerImpl::DrawingRenderingContextPeerImpl()
{
    SetInstanceId(Ace::Container::CurrentIdSafely());
}
void DrawingRenderingContextPeerImpl::SetOptions(const std::optional<CanvasUnit>& optUnit)
{
    if (optUnit && optUnit.value() == CanvasUnit::PX) {
        SetUnit(CanvasUnit::PX);
    }
}
void DrawingRenderingContextPeerImpl::SetInvalidate()
{
    auto customPaintPattern = AceType::DynamicCast<NG::CanvasPattern>(canvasPattern_.Upgrade());
    CHECK_NULL_VOID(customPaintPattern);
    customPaintPattern->SetInvalidate();
}
SizeF DrawingRenderingContextPeerImpl::GetSize()
{
    auto width = size_.Width().value_or(0.0);
    auto height = size_.Height().value_or(0.0);
    return SizeF(width, height);
}
std::shared_ptr<drawing_CanvasPeer> DrawingRenderingContextPeerImpl::GetCanvas() const
{
    return rsCanvas_;
}
void DrawingRenderingContextPeerImpl::SetRSCanvasCallback(WeakPtr<AceType>& canvasPattern)
{
    std::function<void(std::shared_ptr<RSCanvas>, double, double)> callback =
        [wp = WeakClaim(this)](std::shared_ptr<RSCanvas> canvas, double width, double height) {
        auto context = wp.Upgrade();
        CHECK_NULL_VOID(context);
        double density = context->GetDensity();
        if (density == 0) {
            return;
        }
        height /= density;
        width /= density;
        context->size_.SetHeight(height);
        context->size_.SetWidth(width);
#ifndef ACE_UNITTEST
        context->rsCanvas_ = std::make_shared<drawing_CanvasPeer>(canvas.get());
#endif
    };
    auto customPaintPattern = AceType::DynamicCast<NG::CanvasPattern>(canvasPattern.Upgrade());
    if (customPaintPattern) {
        customPaintPattern->SetRSCanvasCallback(callback);
    }
}
void DrawingRenderingContextPeerImpl::ThrowError(int32_t errCode, const std::string& errorMsg)
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
    auto handle = LoadLibrary(LIBARKOALA_MODULE);
    CHECK_NULL_VOID(handle);
    auto aniErrorFunc = reinterpret_cast<AniThrowErrorFunc>(FindSymbol(handle, "AniThrowError"));
    CHECK_NULL_VOID(aniErrorFunc);
    aniErrorFunc(vmContext, errCode, errorMsg);
}
CanvasRenderingContext2DPeer* DrawingRenderingContextPeerImpl::GetOrCreateContext2D()
{
    auto pattern = canvasPattern_.Upgrade();
    if (!pattern) {
        DrawingRenderingContextPeerImpl::ThrowError(
            ERROR_CODE_CANVAS_CONTEXT_NOT_BOUND, "The drawingContext is not bound to a canvas component.");
        return nullptr;
    }
    if (!context2d_) {
        context2d_ = new CanvasRenderingContext2DPeer();
        auto context2dImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl*>(context2d_);
        CHECK_NULL_RETURN(context2dImpl, nullptr);
        context2dImpl->IncRefCount();
        context2dImpl->SetBuiltIn(true);
        context2dImpl->SetInstanceId(Container::CurrentId());
        context2dImpl->SetCanvasPattern(pattern);
        context2dImpl->SetUnit(unit_);
        context2dImpl->CanvasRendererPeerImpl::SetDensity();
    }
    return context2d_;
}
void DrawingRenderingContextPeerImpl::SetCanvasPattern(const RefPtr<AceType>& canvas)
{
    if (canvasPattern_.Upgrade() != canvas) {
        context2d_ = nullptr;
        canvasPattern_ = canvas;
        SetRSCanvasCallback(canvasPattern_);
    }
}
void DrawingRenderingContextPeerImpl::SetUnit(CanvasUnit unit)
{
    unit_ = unit;
    if (context2d_) {
        context2d_->SetUnit(unit);
    }
}
} // namespace OHOS::Ace::NG::GeneratedModifier
