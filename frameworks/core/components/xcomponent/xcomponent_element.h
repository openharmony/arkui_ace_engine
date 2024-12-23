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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_ELEMENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_ELEMENT_H

#include "core/components/xcomponent/native_interface_xcomponent_impl.h"
#include "core/components/xcomponent/resource/native_texture.h"
#include "core/components/xcomponent/xcomponent_component.h"
#include "core/pipeline/base/render_element.h"

#ifdef OHOS_STANDARD_SYSTEM
#include "surface/window.h"
#include "wm/window.h"
#include "render_service_client/core/ui/rs_node.h"
#include "render_service_client/core/ui/rs_surface_node.h"
#include "surface_delegate.h"
#include "surface_utils.h"
#endif

namespace OHOS::Ace {
class XComponentComponent;
class XComponentElement;

class XComponentSurfaceCallback : public OHOS::SurfaceDelegate::ISurfaceCallback {
public:
    explicit XComponentSurfaceCallback(const WeakPtr<XComponentElement>& xcomponentElement)
        : weakXComponentElement_(xcomponentElement) {}
    ~XComponentSurfaceCallback() override = default;

    // override OHOS::SurfaceDelegate::ISurfaceCallback virtual callback function
    void OnSurfaceCreated(const OHOS::sptr<OHOS::Surface>& surface) override;
    void OnSurfaceChanged(const OHOS::sptr<OHOS::Surface>& surface, int32_t width, int32_t height) override;
    void OnSurfaceDestroyed() override {};
private:
    WeakPtr<XComponentElement>weakXComponentElement_;
};

class XComponentElement : public RenderElement {
    DECLARE_ACE_TYPE(XComponentElement, RenderElement);
    friend class XComponentSurfaceCallback;

public:
    using InitEventCallback = std::function<void(const std::string&)>;
    using DestroyEventCallback = std::function<void(const std::string&)>;
    using ExternalEventCallback = std::function<void(const std::string&, const uint32_t, const bool)>;

    ~XComponentElement();
    void Prepare(const WeakPtr<Element>& parent) override;
    void SetNewComponent(const RefPtr<Component>& newComponent) override;

    RefPtr<XComponentComponent> xcomponent_;

private:
    void InitEvent();
    void OnSurfaceDestroyEvent();
    void OnXComponentInit(const std::string& param);
    void OnSurfaceInit(const std::string& componentId, const uint32_t nodeId);
    void OnXComponentSizeInit(int64_t textureId, int32_t textureWidth, int32_t textureHeight);
    void OnXComponentSizeChange(int64_t textureId, int32_t textureWidth, int32_t textureHeight);
    void OnXComponentPositionChange(int32_t offsetX, int32_t offsetY);

    void OnSurfaceCreated(const OHOS::sptr<OHOS::Surface>& surface);
    void OnSurfaceChanged(const OHOS::sptr<OHOS::Surface>& surface, int32_t width, int32_t height);

    void CreatePlatformResource();
    void ReleasePlatformResource();
    bool IsDeclarativePara();

    void SetMethodCall();
    void ConfigSurface(uint32_t surfaceWidth, uint32_t surfaceHeight);

    ExternalEventCallback onSurfaceInit_;
    ExternalEventCallback onSurfaceDestroy_;
    InitEventCallback onXComponentInit_;
    DestroyEventCallback onXComponentDestroy_;
    std::string name_;
    std::string idStr_;
    bool hasSendDestroyEvent_ = false;
    bool isExternalResource_ = false;
    RefPtr<NativeTexture> texture_;
    std::shared_ptr<InnerXComponentController> xcomponentController_;

#ifdef OHOS_STANDARD_SYSTEM
    void CreateSurface();

    sptr<OHOS::Surface> producerSurface_ = nullptr;
    struct NativeWindow *nativeWindow_ = nullptr;
    sptr<OHOS::SurfaceDelegate> surfaceDelegate_;
    int32_t surfaceWidth_ = 0;
    int32_t surfaceHeight_ = 0;
    int32_t scopeId_ = 0;
#else
    void OnTextureRefresh();
#endif
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_ELEMENT_H
