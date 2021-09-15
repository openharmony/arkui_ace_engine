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

#include "core/components/xcomponent/render_xcomponent.h"
#include "core/components/xcomponent/xcomponent_component.h"

namespace OHOS::Ace {
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
        }
    }
}

void XComponentElement::InitEvent()
{
    if (!xcomponent_) {
        return;
    }
    if (!xcomponent_->GetXComponentInitEventId().IsEmpty()) {
        onSurfaceInit_ = AceSyncEvent<void(const std::string&, const uint32_t)>::Create(
            xcomponent_->GetXComponentInitEventId(), context_);
        onXComponentInit_ = AceAsyncEvent<void()>::Create(xcomponent_->GetXComponentInitEventId(), context_);
    }
    if (!xcomponent_->GetXComponentDestroyEventId().IsEmpty()) {
        onXComponentDestroy_ = AceAsyncEvent<void()>::Create(xcomponent_->GetXComponentDestroyEventId(), context_);
    }
}

void XComponentElement::RegisterSurfaceDestroyEvent()
{
    auto context = context_.Upgrade();
    if (context) {
        context->SetKeyHandler([weak = WeakClaim(this)] {
            auto element = weak.Upgrade();
            if (element) {
                element->OnSurfaceDestroyEvent();
            }
        });
    }
}

void XComponentElement::OnSurfaceDestroyEvent()
{
    if (!hasSendDestroyEvent_) {
        if (onXComponentDestroy_) {
            onXComponentDestroy_();
        }
        auto renderXComponent = AceType::DynamicCast<RenderXComponent>(renderNode_);
        if (renderXComponent != nullptr && renderXComponent->GetPluginContext() != nullptr) {
            renderXComponent->GetPluginContext()->OnSurfaceDestroyed();
        }
        hasSendDestroyEvent_ = true;
    }
}

void XComponentElement::RegisterDispatchTouchEventCallback()
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("pipelineContext is null");
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
    auto renderXComponent = AceType::DynamicCast<RenderXComponent>(renderNode_);
    if (renderXComponent != nullptr && renderXComponent->GetPluginContext() != nullptr) {
        touchEventPoint_.id = event.id;
        touchEventPoint_.x = event.x;
        touchEventPoint_.y = event.y;
        touchEventPoint_.size = event.size;
        touchEventPoint_.force = event.force;
        touchEventPoint_.deviceId = event.deviceId;
        touchEventPoint_.time = event.time;
        SetTouchEventType(event);
        renderXComponent->GetPluginContext()->DispatchTouchEvent(touchEventPoint_);
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

    texture_->Create([weak = WeakClaim(this), errorCallback](int64_t id) mutable {
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
    });
}

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
}

void XComponentElement::OnXComponentSize(int64_t textureId, int32_t textureWidth, int32_t textureHeight)
{
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
        OnXComponentInit("");
        OnSurfaceInit(xcomponent_->GetId(), xcomponent_->GetNodeId());
    }
}

void XComponentElement::OnXComponentInit(const std::string& param)
{
    if (onXComponentInit_) {
        onXComponentInit_();
    }
}

void XComponentElement::OnSurfaceInit(const std::string& componentId, const uint32_t nodeId)
{
    if (onSurfaceInit_) {
        onSurfaceInit_(componentId, nodeId);
    }
}
} // namespace OHOS::Ace
