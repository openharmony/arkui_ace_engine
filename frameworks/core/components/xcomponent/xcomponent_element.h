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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_ELEMENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_ELEMENT_H

#include "core/components/xcomponent/native_render_context.h"
#include "core/components/xcomponent/resource/native_texture.h"
#include "core/pipeline/base/render_element.h"

namespace OHOS::Ace {
class XComponentComponent;

class XComponentElement : public RenderElement {
    DECLARE_ACE_TYPE(XComponentElement, RenderElement);

public:
    using EventCallback = std::function<void()>;
    ~XComponentElement();
    void Prepare(const WeakPtr<Element>& parent) override;
    void SetNewComponent(const RefPtr<Component>& newComponent) override;
    void OnXComponentSize(int64_t textureId, int32_t textureWidth, int32_t textureHeight);
    void OnTextureSize(int64_t textureId, std::string& result);
    void CreatePlatformResource();
    void ReleasePlatformResource();

    bool isExternalResource_ = false;
    RefPtr<NativeTexture> texture_;
    RefPtr<XComponentComponent> xcomponent_;

private:
    void InitEvent();
    void RegisterSurfaceDestroyEvent();
    void OnSurfaceDestroyEvent();
    void SetTouchEventType(const TouchPoint& event);
    void OnXComponentInit(const std::string& param);
    void OnSurfaceInit(const std::string& componentId, const uint32_t nodeId);
    void RegisterDispatchTouchEventCallback();
    void DispatchTouchEvent(const TouchPoint& event);

    std::function<void(const std::string&, const uint32_t)> onSurfaceInit_;
    EventCallback onXComponentInit_;
    EventCallback onXComponentDestroy_;
    TouchInfo touchEventPoint_;
    std::string name_;
    bool hasSendDestroyEvent_ = false;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_ELEMENT_H
