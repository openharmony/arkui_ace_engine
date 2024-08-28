/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/xcomponent/xcomponent_element.h"

#include "core/common/container.h"
#include "core/components/xcomponent/rosen_render_xcomponent.h"

namespace OHOS::Ace {
#ifdef OHOS_STANDARD_SYSTEM
namespace {
const char* SURFACE_STRIDE_ALIGNMENT = "8";
constexpr int32_t SURFACE_QUEUE_SIZE = 5;
} // namespace

#endif

void XComponentSurfaceCallback::OnSurfaceCreated(const OHOS::sptr<OHOS::Surface>& surface)
{
    auto xcomponentElement = weakXComponentElement_.Upgrade();
    CHECK_NULL_VOID(xcomponentElement);
    xcomponentElement->OnSurfaceCreated(surface);
}

void XComponentSurfaceCallback::OnSurfaceChanged(
    const OHOS::sptr<OHOS::Surface>& surface, int32_t width, int32_t height)
{
    auto xcomponentElement = weakXComponentElement_.Upgrade();
    CHECK_NULL_VOID(xcomponentElement);
    xcomponentElement->OnSurfaceChanged(surface, width, height);
}

XComponentElement::~XComponentElement()
{
    // App release its res first and xcomponent release surface
    OnSurfaceDestroyEvent();
    ReleasePlatformResource();
}

void XComponentElement::SetNewComponent(const RefPtr<Component>& newComponent)
{
    if (newComponent == nullptr) {
        Element::SetNewComponent(newComponent);
        return;
    }
    auto xcomponent = AceType::DynamicCast<XComponentComponent>(newComponent);
    if (xcomponent) {
        idStr_ = xcomponent->GetId();
        name_ = xcomponent->GetName();
#ifndef OHOS_STANDARD_SYSTEM
        if (texture_) {
            isExternalResource_ = true;
            xcomponent->SetTextureId(texture_->GetId());
            xcomponent->SetTexture(texture_);
        }
#endif
        Element::SetNewComponent(xcomponent);
    }
}

void XComponentElement::Prepare(const WeakPtr<Element>& parent)
{
    xcomponent_ = AceType::DynamicCast<XComponentComponent>(component_);
    InitEvent();

    RenderElement::Prepare(parent);
    if (xcomponent_) {
        if (!isExternalResource_) {
            CreatePlatformResource();
        }
        SetMethodCall();
    }

    if (!renderNode_) {
        return;
    }
    auto renderXComponent = AceType::DynamicCast<RenderXComponent>(renderNode_);
    if (!renderXComponent) {
        return;
    }
    renderXComponent->SetXComponentSizeInit(
        [weak = WeakClaim(this)](int64_t textureId, int32_t width, int32_t height) {
            auto xcomponentElement = weak.Upgrade();
            if (xcomponentElement) {
                xcomponentElement->OnXComponentSizeInit(textureId, width, height);
            }
    });
    renderXComponent->SetXComponentSizeChange(
        [weak = WeakClaim(this)](int64_t textureId, int32_t width, int32_t height) {
            auto xcomponentElement = weak.Upgrade();
            if (xcomponentElement) {
                xcomponentElement->OnXComponentSizeChange(textureId, width, height);
            }
    });
    if (SystemProperties::GetExtSurfaceEnabled()) {
        renderXComponent->SetXComponentPositionChange(
            [weak = WeakClaim(this)](int32_t offsetX, int32_t offsetY) {
                auto xcomponentElement = weak.Upgrade();
                if (xcomponentElement) {
                    xcomponentElement->OnXComponentPositionChange(offsetX, offsetY);
                }
        });
    }
}

void XComponentElement::InitEvent()
{
    if (!xcomponent_) {
        LOGE("XComponentElement::InitEvent xcomponent_ is null");
        return;
    }
    if (!xcomponent_->GetXComponentInitEventId().IsEmpty()) {
        onSurfaceInit_ = AceSyncEvent<void(const std::string&, const uint32_t, const bool)>::Create(
            xcomponent_->GetXComponentInitEventId(), context_);
        onSurfaceDestroy_ = AceSyncEvent<void(const std::string&, const uint32_t, const bool)>::Create(
            xcomponent_->GetXComponentInitEventId(), context_);
        onXComponentInit_ =
            AceAsyncEvent<void(const std::string&)>::Create(xcomponent_->GetXComponentInitEventId(), context_);
    }
    if (!xcomponent_->GetXComponentDestroyEventId().IsEmpty()) {
        onXComponentDestroy_ =
            AceAsyncEvent<void(const std::string&)>::Create(xcomponent_->GetXComponentDestroyEventId(), context_);
    }
}

void XComponentElement::OnSurfaceDestroyEvent()
{
    std::string param;
    if (IsDeclarativePara()) {
        auto json = JsonUtil::Create(true);
        json->Put("destroy", "");
        param = json->ToString();
    } else {
        param = std::string("\"destroy\",{").append("}");
    }
    if (!hasSendDestroyEvent_) {
        auto renderXComponent = AceType::DynamicCast<RenderXComponent>(renderNode_);
        if (renderXComponent) {
            renderXComponent->NativeXComponentDestroy();
        }

        auto pipelineContext = context_.Upgrade();
        if (!pipelineContext) {
            LOGE("pipelineContext is nullptr");
            return;
        }
        pipelineContext->GetTaskExecutor()->PostTask(
            [weak = WeakClaim(this)] {
                auto element = weak.Upgrade();
                if (element) {
                    if (element->onSurfaceDestroy_) {
                        element->onSurfaceDestroy_(
                            element->xcomponent_->GetId(), element->xcomponent_->GetNodeId(), true);
                    }
                }
            },
            TaskExecutor::TaskType::JS, "ArkUIXComponentSurfaceDestroy");

        if (onXComponentDestroy_) {
            onXComponentDestroy_(param);
        }
        hasSendDestroyEvent_ = true;
    }
}

bool XComponentElement::IsDeclarativePara()
{
    auto context = context_.Upgrade();
    if (!context) {
        return false;
    }

    return context->GetIsDeclarative();
}

void XComponentElement::CreatePlatformResource()
{
    ReleasePlatformResource();
#ifdef OHOS_STANDARD_SYSTEM
    CreateSurface();
    isExternalResource_ = true;
#else
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("XComponentElement CreatePlatformResource context = null");
        return;
    }
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);

    auto errorCallback = [weak = WeakClaim(this), uiTaskExecutor](
            const std::string& errorId, const std::string& param) {
        uiTaskExecutor.PostTask([weak, errorId, param] {
            auto XComponentElement = weak.Upgrade();
            if (XComponentElement) {
                LOGE("XComponentElement errorCallback");
            }
        }, "ArkUIXComponentError");
    };

    texture_ = AceType::MakeRefPtr<NativeTexture>(context_, errorCallback);
    if (!texture_) {
        return;
    }
    texture_->Create(
        [weak = WeakClaim(this), errorCallback](int64_t id) mutable {
            auto XComponentElement = weak.Upgrade();
            if (XComponentElement) {
                auto component = XComponentElement->xcomponent_;
                if (component) {
                    XComponentElement->isExternalResource_ = true;
                    component->SetTextureId(id);
                    component->SetTexture(XComponentElement->texture_);
                    if (XComponentElement->renderNode_ != nullptr) {
                        XComponentElement->renderNode_->Update(component);
                    }
                }
            }
        }, idStr_);

    auto onTextureRefresh = [weak = WeakClaim(this), uiTaskExecutor]() {
        uiTaskExecutor.PostSyncTask([weak] {
            auto texture = weak.Upgrade();
            if (texture) {
                texture->OnTextureRefresh();
            }
        });
    };
    texture_->SetRefreshListener(onTextureRefresh);
#endif
}

#ifdef OHOS_STANDARD_SYSTEM
void XComponentElement::CreateSurface()
{
    if (SystemProperties::GetExtSurfaceEnabled()) {
        auto context = context_.Upgrade();
        uint32_t windowId = 0;
        if (context) {
            windowId = context->GetWindowId();
        }
        surfaceDelegate_ = new OHOS::SurfaceDelegate(windowId);
        surfaceDelegate_->CreateSurface();
        scopeId_ = Container::CurrentId();
        surfaceDelegate_->AddSurfaceCallback(new XComponentSurfaceCallback(WeakClaim(this)));
        producerSurface_ = surfaceDelegate_->GetSurface();
    } else {
#ifdef ENABLE_ROSEN_BACKEND
        auto rosenTexture = AceType::DynamicCast<RosenRenderXComponent>(renderNode_);
        if (rosenTexture) {
            producerSurface_ = rosenTexture->GetSurface();
        }
#endif
    }
    if (producerSurface_ == nullptr) {
        LOGE("producerSurface is nullptr");
        return;
    }

    auto surfaceUtils = SurfaceUtils::GetInstance();
    auto ret = surfaceUtils->Add(producerSurface_->GetUniqueId(), producerSurface_);
    if (ret != SurfaceError::SURFACE_ERROR_OK) {
        LOGE("xcomponent add surface error: %{public}d", ret);
    }

    producerSurface_->SetQueueSize(SURFACE_QUEUE_SIZE);
    producerSurface_->SetUserData("SURFACE_STRIDE_ALIGNMENT", SURFACE_STRIDE_ALIGNMENT);
    producerSurface_->SetUserData("SURFACE_FORMAT", std::to_string(PIXEL_FMT_RGBA_8888));
}

void XComponentElement::OnSurfaceCreated(const OHOS::sptr<OHOS::Surface>& surface)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    nativeWindow_ = CreateNativeWindowFromSurface(&producerSurface_);
    CHECK_NULL_VOID(nativeWindow_);
    xcomponent_->SetNativeWindow(nativeWindow_);
    auto platformTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::PLATFORM);
    platformTaskExecutor.PostTask([weak = WeakClaim(this), scopeId = scopeId_] {
        ContainerScope scope(scopeId);
        auto xcomponentElement = weak.Upgrade();
        if (xcomponentElement && xcomponentElement->xcomponent_) {
            xcomponentElement->OnSurfaceInit(
                xcomponentElement->xcomponent_->GetId(),
                xcomponentElement->xcomponent_->GetNodeId());
            xcomponentElement->OnXComponentInit("");
        }
    }, "ArkUIXComponentSurfaceInit");
}

void XComponentElement::OnSurfaceChanged(const OHOS::sptr<OHOS::Surface>& surface, int32_t width, int32_t height)
{
    auto renderNode = AceType::DynamicCast<RenderXComponent>(renderNode_);
    CHECK_NULL_VOID(renderNode);
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    float viewScale = context->GetViewScale();
    CHECK_NULL_VOID(nativeWindow_);
    NativeWindowHandleOpt(nativeWindow_, SET_BUFFER_GEOMETRY,
        (int)(width * viewScale), (int)(height * viewScale));
    renderNode->NativeXComponentChange();
}
#else
void XComponentElement::OnTextureRefresh()
{
    if (renderNode_) {
        renderNode_->MarkNeedRender();
    }
}
#endif

void XComponentElement::ConfigSurface(uint32_t surfaceWidth, uint32_t surfaceHeight)
{
#ifdef OHOS_STANDARD_SYSTEM
    if (producerSurface_) {
        producerSurface_->SetUserData("SURFACE_WIDTH", std::to_string(surfaceWidth));
        producerSurface_->SetUserData("SURFACE_HEIGHT", std::to_string(surfaceHeight));
    }
#else
    if (texture_ && xcomponent_) {
        texture_->SetSize(xcomponent_->GetTextureId(), surfaceWidth, surfaceHeight);
    }
#endif
}

void XComponentElement::SetMethodCall()
{
    if (!xcomponentController_) {
        auto controller = xcomponent_->GetXComponentController();
        if (!controller) {
            LOGE("invalid controller in xcomponent.");
            return;
        }
        xcomponentController_ = controller;
    }
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("context is nullptr");
        return;
    }
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    xcomponentController_->SetConfigSurfaceImpl([weak = WeakClaim(this), uiTaskExecutor]
                                                (uint32_t surfaceWidth, uint32_t surfaceHeight) {
        uiTaskExecutor.PostSyncTask([weak, surfaceWidth, surfaceHeight]() {
            auto xComponentElement = weak.Upgrade();
            if (xComponentElement) {
                xComponentElement->ConfigSurface(surfaceWidth, surfaceHeight);
            }
        }, "ArkUIXComponentSetSurfaceConfig");
    });

#ifdef OHOS_STANDARD_SYSTEM
    xcomponentController_->SetSurfaceId(std::to_string(producerSurface_->GetUniqueId()));
#else
    xcomponentController_->SetSurfaceId(xcomponent_->GetId());
#endif
}

void XComponentElement::ReleasePlatformResource()
{
#ifdef OHOS_STANDARD_SYSTEM
    if (producerSurface_) {
        auto surfaceUtils = SurfaceUtils::GetInstance();
        auto ret = surfaceUtils->Remove(producerSurface_->GetUniqueId());
        if (ret != SurfaceError::SURFACE_ERROR_OK) {
            LOGE("xcomponent remove surface error: %{public}d", ret);
        }
    }
    isExternalResource_ = false;
    if (SystemProperties::GetExtSurfaceEnabled()) {
        CHECK_NULL_VOID(surfaceDelegate_);
        surfaceDelegate_->ReleaseSurface();
    }
#else
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("context is nullptr");
        return;
    }

    // Reusing texture will cause a problem that last frame of last video will be display.
    if (texture_) {
        auto platformTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(),
                                                             TaskExecutor::TaskType::PLATFORM);
        if (platformTaskExecutor.IsRunOnCurrentThread()) {
            if (!isExternalResource_) {
                texture_->Release();
            }
            texture_.Reset();
            isExternalResource_ = false;
        }
    }

    if (xcomponent_) {
        xcomponent_->SetTextureId(X_INVALID_ID);
        xcomponent_->SetTexture(nullptr);
    }
#endif
}

void XComponentElement::OnXComponentSizeInit(int64_t textureId, int32_t textureWidth, int32_t textureHeight)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto context = context_.Upgrade();
    if (context == nullptr) {
        LOGE("context is nullptr");
        return;
    }

    if (producerSurface_ != nullptr) {
        float viewScale = context->GetViewScale();
        if (SystemProperties::GetExtSurfaceEnabled()) {
            CHECK_NULL_VOID(surfaceDelegate_);
            auto renderNode = AceType::DynamicCast<RenderXComponent>(renderNode_);
            CHECK_NULL_VOID(renderNode);
            auto paintOffset = renderNode->GetGlobalOffset();
            int32_t offsetX = paintOffset.GetX() * viewScale;
            int32_t offsetY = paintOffset.GetY() * viewScale;
            surfaceWidth_ = textureWidth * viewScale;
            surfaceHeight_ = textureHeight * viewScale;
            surfaceDelegate_->SetBounds(offsetX, offsetY, surfaceWidth_, surfaceHeight_);
            return;
        }
        nativeWindow_ = CreateNativeWindowFromSurface(&producerSurface_);
        if (nativeWindow_) {
            NativeWindowHandleOpt(nativeWindow_, SET_BUFFER_GEOMETRY,
                                  (int)(textureWidth * viewScale), (int)(textureHeight * viewScale));
            xcomponent_->SetNativeWindow(nativeWindow_);
        } else {
            LOGE("can not create NativeWindow");
        }
    }

    auto platformTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::PLATFORM);
    platformTaskExecutor.PostTask([weak = WeakClaim(this)] {
        auto xcomponentElement = weak.Upgrade();
        if (xcomponentElement) {
            if (xcomponentElement->xcomponent_) {
                xcomponentElement->OnSurfaceInit(
                    xcomponentElement->xcomponent_->GetId(),
                    xcomponentElement->xcomponent_->GetNodeId());
                xcomponentElement->OnXComponentInit("");
            }
        }
    }, "ArkUIXComponentSurfaceSizeInit");
#else
    if (texture_) {
        texture_->SetSize(textureId, textureWidth, textureHeight,
                          [weak = WeakClaim(this), textureId](std::string& result) {
                                auto xcomponentElement = weak.Upgrade();
                                if (xcomponentElement) {
                                    if (xcomponentElement->xcomponent_) {
                                        xcomponentElement->OnSurfaceInit(
                                            xcomponentElement->xcomponent_->GetId(),
                                            xcomponentElement->xcomponent_->GetNodeId());
                                        xcomponentElement->OnXComponentInit("");
                                    }
                                }
        });
    }
#endif
}

void XComponentElement::OnXComponentSizeChange(int64_t textureId, int32_t textureWidth, int32_t textureHeight)
{
    auto renderNode = AceType::DynamicCast<RenderXComponent>(renderNode_);
    if (renderNode != nullptr) {
#ifdef OHOS_STANDARD_SYSTEM
        auto context = context_.Upgrade();
        if (context == nullptr) {
            LOGE("context is nullptr");
            return;
        }
        float viewScale = context->GetViewScale();
        if (SystemProperties::GetExtSurfaceEnabled()) {
            CHECK_NULL_VOID(surfaceDelegate_);
            auto paintOffset = renderNode->GetGlobalOffset();
            int32_t offsetX = paintOffset.GetX() * viewScale;
            int32_t offsetY = paintOffset.GetY() * viewScale;
            surfaceWidth_ = textureWidth * viewScale;
            surfaceHeight_ = textureHeight * viewScale;
            surfaceDelegate_->SetBounds(offsetX, offsetY, surfaceWidth_, surfaceHeight_);
            return;
        }
        if (nativeWindow_) {
            NativeWindowHandleOpt(nativeWindow_, SET_BUFFER_GEOMETRY,
                (int)(textureWidth * viewScale), (int)(textureHeight * viewScale));
            renderNode->NativeXComponentChange();
        } else {
            LOGE("change nativewindow size failed, nativewindow NULL");
        }
#else
        if (texture_) {
            texture_->SetSize(textureId, textureWidth, textureHeight,
                              [renderNode, textureId](std::string& result) {
                                if (renderNode) {
                                    renderNode->NativeXComponentChange();
                                }
            });
        }
#endif
    }
}

void XComponentElement::OnXComponentPositionChange(int32_t offsetX, int32_t offsetY)
{
    auto renderNode = AceType::DynamicCast<RenderXComponent>(renderNode_);
    CHECK_NULL_VOID(renderNode);
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    float viewScale = context->GetViewScale();
    int32_t surfaceX = offsetX * viewScale;
    int32_t surfaceY = offsetY * viewScale;
    CHECK_NULL_VOID(surfaceDelegate_);
    surfaceDelegate_->SetBounds(surfaceX, surfaceY, surfaceWidth_, surfaceHeight_);
    CHECK_NULL_VOID(nativeWindow_);
    renderNode->NativeXComponentOffset(surfaceX, surfaceY);
}

void XComponentElement::OnXComponentInit(const std::string& param)
{
    std::string loadStr;
    if (IsDeclarativePara()) {
        auto json = JsonUtil::Create(true);
        json->Put("load", "");
        loadStr = json->ToString();
    } else {
        loadStr = std::string("\"load\",{").append("}");
    }

    if (onXComponentInit_) {
        onXComponentInit_(loadStr);
    }
}

void XComponentElement::OnSurfaceInit(const std::string& componentId, const uint32_t nodeId)
{
    if (onSurfaceInit_) {
        onSurfaceInit_(componentId, nodeId, false);
    }
}
} // namespace OHOS::Ace
