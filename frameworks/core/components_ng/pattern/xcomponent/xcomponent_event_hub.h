/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {
using LoadEvent = std::function<void(const std::string&)>;
using DestroyEvent = std::function<void(const std::string&)>;
using ExternalEvent = std::function<void(const std::string&, const uint32_t, const bool)>;
using DetachEvent = std::function<void(const std::string&)>;
using SurfaceCreatedEvent = std::function<void(const std::string&, const std::string&)>;
using SurfaceChangedEvent = std::function<void(const std::string&, const RectF&)>;
using SurfaceDestroyedEvent = std::function<void(const std::string&, const std::string&)>;

class XComponentEventHub : public EventHub {
    DECLARE_ACE_TYPE(XComponentEventHub, EventHub)

public:
    XComponentEventHub() = default;
    ~XComponentEventHub() override = default;

    void SetOnLoad(LoadEvent&& loadEvent)
    {
        loadEvent_ = std::move(loadEvent);
    }

    void FireLoadEvent(const std::string& xcomponentId) const
    {
        CHECK_NULL_VOID(loadEvent_);
        loadEvent_(xcomponentId);
    }

    void SetOnDestroy(DestroyEvent&& destroyEvent)
    {
        destroyEvent_ = std::move(destroyEvent);
    }

    void FireDestroyEvent(const std::string& xcomponentId) const
    {
        CHECK_NULL_VOID(destroyEvent_);
        destroyEvent_(xcomponentId);
    }

    void SetOnSurfaceInitEvent(ExternalEvent&& surfaceInitEvent)
    {
        surfaceInitEvent_ = std::move(surfaceInitEvent);
    }

    void FireSurfaceInitEvent(const std::string& componentId, const uint32_t nodeId) const
    {
        CHECK_NULL_VOID(surfaceInitEvent_);
        surfaceInitEvent_(componentId, nodeId, false);
    }

    void SetDetachEvent(DetachEvent&& detachEvent)
    {
        detachEvent_ = std::move(detachEvent);
    }

    void FireDetachEvent(const std::string& componentId)
    {
        CHECK_NULL_VOID(detachEvent_);
        detachEvent_(componentId);
    }

    void SetControllerCreatedEvent(SurfaceCreatedEvent&& controllerCreatedEvent)
    {
        controllerCreatedEvent_ = std::move(controllerCreatedEvent);
    }

    void FireControllerCreatedEvent(const std::string& surfaceId, const std::string& xcomponentId) const
    {
        CHECK_NULL_VOID(controllerCreatedEvent_);
        controllerCreatedEvent_(surfaceId, xcomponentId);
    }

    void SetControllerChangedEvent(SurfaceChangedEvent&& controllerChangedEvent)
    {
        controllerChangedEvent_ = std::move(controllerChangedEvent);
    }

    void FireControllerChangedEvent(const std::string& surfaceId, const RectF& rect) const
    {
        CHECK_NULL_VOID(controllerChangedEvent_);
        controllerChangedEvent_(surfaceId, rect);
    }

    void SetControllerDestroyedEvent(SurfaceDestroyedEvent&& controllerDestroyedEvent)
    {
        controllerDestroyedEvent_ = std::move(controllerDestroyedEvent);
    }

    void FireControllerDestroyedEvent(const std::string& surfaceId, const std::string& xcomponentId) const
    {
        CHECK_NULL_VOID(controllerDestroyedEvent_);
        controllerDestroyedEvent_(surfaceId, xcomponentId);
    }

private:
    LoadEvent loadEvent_;
    DestroyEvent destroyEvent_;
    ExternalEvent surfaceInitEvent_;
    DetachEvent detachEvent_;
    SurfaceCreatedEvent controllerCreatedEvent_;
    SurfaceChangedEvent controllerChangedEvent_;
    SurfaceDestroyedEvent controllerDestroyedEvent_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_EVENT_HUB_H
