/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "base/json/json_util.h"
#include "core/components/xcomponent/render_xcomponent.h"
#include "core/components/xcomponent/xcomponent_component.h"

namespace OHOS::Ace {
#ifdef OHOS_STANDARD_SYSTEM
namespace {
const char* SURFACE_STRIDE_ALIGNMENT = "8";
constexpr int32_t SURFACE_QUEUE_SIZE = 5;
constexpr int32_t STATUS_BAR_HEIGHT = 100;
} // namespace

bool g_onload = false;
std::unordered_map<std::string, uint64_t> XComponentElement::surfaceIdMap_;
#endif

XComponentElement::~XComponentElement()
{
    ReleasePlatformResource();
}

void XComponentElement::SetNewComponent(const RefPtr<Component>& newComponent)
{
    if (newComponent == nullptr) {
        Element::SetNewComponent(newComponent);
        return;
    }
    auto xcomponent = AceType::DynamicCast<XComponentComponent>(newComponent);
    idStr_ = xcomponent->GetId();
    if (xcomponent) {
        if (texture_) {
            xcomponent->SetTextureId(texture_->GetId());
            xcomponent->SetTexture(texture_);
            isExternalResource_ = true;
        }
        name_ = xcomponent->GetName();
        Element::SetNewComponent(xcomponent);
    }
}

void XComponentElement::Prepare(const WeakPtr<Element>& parent)
{
    xcomponent_ = AceType::DynamicCast<XComponentComponent>(component_);
    InitEvent();
    RegisterSurfaceDestroyEvent();
    RegisterDispatchTouchEventCallback();
    if (xcomponent_) {
        if (!isExternalResource_) {
            CreatePlatformResource();
        }
    }
    RenderElement::Prepare(parent);
    if (renderNode_) {
        auto renderXComponent = AceType::DynamicCast<RenderXComponent>(renderNode_);
        if (renderXComponent) {
            renderXComponent->SetXComponentSizeChange(
                [weak = WeakClaim(this)](int64_t textureId, int32_t width, int32_t height) {
                    auto xcomponentElement = weak.Upgrade();
                    if (xcomponentElement) {
                        xcomponentElement->OnXComponentSize(textureId, width, height);
                    }
            });
#ifdef OHOS_STANDARD_SYSTEM
            renderXComponent->SetXComponentHiddenChange([weak = WeakClaim(this)](bool hidden) {
                    auto xcomponentElement = weak.Upgrade();
                    if (xcomponentElement) {
                        xcomponentElement->OnXComponentHiddenChange(hidden);
                    }
            });
#endif
        }
    }

#ifdef OHOS_STANDARD_SYSTEM
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    context->AddPageTransitionListener([weak = AceType::WeakClaim(this)](const TransitionEvent& event,
                                           const WeakPtr<PageElement>& in, const WeakPtr<PageElement>& out) {
        auto xcomponent = weak.Upgrade();
        if (!xcomponent) {
            return;
        }
        if (event == TransitionEvent::POP_START) {
            if (xcomponent->previewWindow_) {
                xcomponent->previewWindow_->Hide();
                xcomponent->previewWindow_->Destroy();
            }
        }
    });
#endif
}

void XComponentElement::InitEvent()
{
    if (!xcomponent_) {
        LOGE("XComponentElement::InitEvent xcomponent_ is null");
        return;
    }
    if (!xcomponent_->GetXComponentInitEventId().IsEmpty()) {
        onSurfaceInit_ = AceSyncEvent<void(const std::string&, const uint32_t)>::Create(
            xcomponent_->GetXComponentInitEventId(), context_);
        onXComponentInit_ =
            AceAsyncEvent<void(const std::string&)>::Create(xcomponent_->GetXComponentInitEventId(), context_);
    }
    if (!xcomponent_->GetXComponentDestroyEventId().IsEmpty()) {
        onXComponentDestroy_ =
            AceAsyncEvent<void(const std::string&)>::Create(xcomponent_->GetXComponentDestroyEventId(), context_);
    }
}

void XComponentElement::RegisterSurfaceDestroyEvent()
{
    auto context = context_.Upgrade();
    if (context) {
        context->SetDestroyHandler([weak = WeakClaim(this)] {
            auto element = weak.Upgrade();
            if (element) {
                element->OnSurfaceDestroyEvent();
            }
        });
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
        if (onXComponentDestroy_) {
            onXComponentDestroy_(param);
        }
        auto renderXComponent = AceType::DynamicCast<RenderXComponent>(renderNode_);
        if (renderXComponent) {
            renderXComponent->NativeXComponentDestroy();
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

void XComponentElement::RegisterDispatchTouchEventCallback()
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("RegisterDispatchTouchEventCallback pipelineContext is null");
        return;
    }
    pipelineContext->SetDispatchTouchEventHandler([weak = WeakClaim(this)](const TouchPoint& event) {
        auto element = weak.Upgrade();
        if (element) {
            element->DispatchTouchEvent(event);
        }
    });
}

void XComponentElement::DispatchTouchEvent(const TouchPoint& event)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("DispatchTouchEvent pipelineContext is null");
        return;
    }
    auto renderXComponent = AceType::DynamicCast<RenderXComponent>(renderNode_);
    if (renderXComponent) {
        touchEventPoint_.id = event.id;
        touchEventPoint_.x = event.x;
        touchEventPoint_.y = event.y;
        touchEventPoint_.size = event.size;
        touchEventPoint_.force = event.force;
        touchEventPoint_.deviceId = event.deviceId;
        touchEventPoint_.timeStamp = event.time.time_since_epoch().count();
        SetTouchEventType(event);
        renderXComponent->NativeXComponentDispatchTouchEvent(touchEventPoint_);
    }
}

void XComponentElement::SetTouchEventType(const TouchPoint& event)
{
    switch (event.type) {
        case TouchType::DOWN:
            touchEventPoint_.type = TouchInfoType::DOWN;
            break;
        case TouchType::UP:
            touchEventPoint_.type = TouchInfoType::UP;
            break;
        case TouchType::MOVE:
            touchEventPoint_.type = TouchInfoType::MOVE;
            break;
        case TouchType::CANCEL:
            touchEventPoint_.type = TouchInfoType::CANCEL;
            break;
        default:
            touchEventPoint_.type = TouchInfoType::UNKNOWN;
            break;
    }
}

void XComponentElement::CreatePlatformResource()
{
    ReleasePlatformResource();
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
        });
    };
    texture_ = AceType::MakeRefPtr<NativeTexture>(context_, errorCallback);
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
        },
        idStr_);
#ifdef OHOS_STANDARD_SYSTEM
    CreateSurface();
#endif
}

#ifdef OHOS_STANDARD_SYSTEM
void XComponentElement::CreateSurface()
{
    if (previewWindow_ == nullptr) {
        sptr<Rosen::WindowOption> option = new Rosen::WindowOption();
        option->SetWindowType(Rosen::WindowType::WINDOW_TYPE_APP_LAUNCHING);
        option->SetWindowMode(Rosen::WindowMode::WINDOW_MODE_FLOATING);
        previewWindow_ = Rosen::Window::Create("xcomponent_window", option);
    }

    if (previewWindow_ == nullptr || previewWindow_->GetSurfaceNode() == nullptr) {
        LOGE("Create xcomponent previewWindow failed");
        return;
    }

    producerSurface_ = previewWindow_->GetSurfaceNode()->GetSurface();
    if (producerSurface_ == nullptr) {
        LOGE("producerSurface is nullptr");
        return;
    }

    auto surfaceUtils = SurfaceUtils::GetInstance();
    auto ret = surfaceUtils->Add(producerSurface_->GetUniqueId(), producerSurface_);
    if (ret != SurfaceError::SURFACE_ERROR_OK) {
        LOGE("xcomponent add surface error: %{public}d", ret);
    }

    if (!xcomponentController_) {
        const auto& controller = xcomponent_->GetXComponentController();
        if (!controller) {
            return;
        }
        xcomponentController_ = controller;
        xcomponentController_->surfaceId_ = producerSurface_->GetUniqueId();
    }

    producerSurface_->SetQueueSize(SURFACE_QUEUE_SIZE);
    producerSurface_->SetUserData("SURFACE_STRIDE_ALIGNMENT", SURFACE_STRIDE_ALIGNMENT);
    producerSurface_->SetUserData("SURFACE_FORMAT", std::to_string(PIXEL_FMT_RGBA_8888));

    XComponentElement::surfaceIdMap_.emplace(xcomponent_->GetId(), producerSurface_->GetUniqueId());

    previewWindow_->Show();
}

void XComponentElement::OnXComponentHiddenChange(bool hidden)
{
    if (!previewWindow_) {
        return;
    }
    hidden_ = hidden;
    if (hidden) {
        previewWindow_->Hide();
    } else {
        previewWindow_->Show();
    }
}
#endif

void XComponentElement::ReleasePlatformResource()
{
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("XComponentElement ReleasePlatformResource context null");
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
        }
    }

#ifdef OHOS_STANDARD_SYSTEM
    if (previewWindow_) {
        previewWindow_->Hide();
        previewWindow_->Destroy();
    }

    if (!surfaceIdMap_.empty()) {
        auto surfaceUtils = SurfaceUtils::GetInstance();
        auto ret = surfaceUtils->Remove(XComponentElement::surfaceIdMap_[xcomponent_->GetId()]);
        if (ret != SurfaceError::SURFACE_ERROR_OK) {
            LOGE("xcomponent remove surface error: %{public}d", ret);
        }
    }
#endif
}

void XComponentElement::OnXComponentSize(int64_t textureId, int32_t textureWidth, int32_t textureHeight)
{
#ifdef OHOS_STANDARD_SYSTEM
    if (previewWindow_ != nullptr) {
        if (renderNode_ != nullptr) {
            Offset offset = renderNode_->GetGlobalOffset();
            auto context = context_.Upgrade();
            if (context == nullptr) {
                LOGE("context is nullptr");
                return;
            }

            float viewScale = context->GetViewScale();
            previewWindow_->MoveTo((int32_t)(offset.GetX() * viewScale),
                                   (int32_t)((offset.GetY() + STATUS_BAR_HEIGHT) * viewScale));
            previewWindow_->Resize(textureWidth * viewScale, textureHeight * viewScale);
            auto nativeWindow = CreateNativeWindowFromSurface(&producerSurface_);
            if (nativeWindow) {
                NativeWindowHandleOpt(nativeWindow, SET_BUFFER_GEOMETRY,
                                      (int)(textureWidth * viewScale), (int)(textureHeight * viewScale));
                xcomponent_->SetNativeWindow(nativeWindow);
            } else {
                LOGE("can not create NativeWindow frome surface");
            }

            if (!hidden_) {
                previewWindow_->Show();
            }
        }
    }
    std::string str = "";
    if (!g_onload) {
        g_onload = true;
        this->OnTextureSize(X_INVALID_ID, str);
    }
#endif

    if (texture_) {
        texture_->OnSize(textureId, textureWidth, textureHeight,
                         [weak = WeakClaim(this), textureId](std::string& result) {
                            auto xcomponentElement = weak.Upgrade();
                            if (xcomponentElement) {
                                xcomponentElement->OnTextureSize(textureId, result);
                            }
        });
    }
}

void XComponentElement::OnTextureSize(int64_t textureId, std::string& result)
{
    if (xcomponent_) {
        OnSurfaceInit(xcomponent_->GetId(), xcomponent_->GetNodeId());
        OnXComponentInit("");
    }
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
        onSurfaceInit_(componentId, nodeId);
    }
}
} // namespace OHOS::Ace
