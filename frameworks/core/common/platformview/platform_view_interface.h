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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PLATFORMVIEW_PLATFORM_VIEW_INTERFACE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PLATFORMVIEW_PLATFORM_VIEW_INTERFACE_H

#include <cstdint>

#include "base/memory/ace_type.h"
#include "core/components_ng/render/render_surface.h"

namespace OHOS::Ace::NG {
using CommonEvent = std::function<void()>;
using TextureRefreshEvent = std::function<void(uint32_t, uint64_t)>;
using PlatformViewReadyEvent = std::function<void()>;

class PlatformViewInterface : public virtual AceType {
    DECLARE_ACE_TYPE(NG::PlatformViewInterface, AceType)

public:
    PlatformViewInterface() = default;
    ~PlatformViewInterface() override = default;

    static RefPtr<PlatformViewInterface> Create();

    virtual void InitPlatformView() {}
    virtual void UpdatePlatformViewLayout(const NG::SizeF& drawSize, const NG::OffsetF& offset) {}
    virtual void HandleTouchDown(const NG::OffsetF& offset) {}
    virtual void HandleTouchUp(const NG::OffsetF& offset) {}
    virtual void HandleTouchMove(const NG::OffsetF& offset) {}
    virtual void HandleTouchCancel(const NG::OffsetF& offset) {}

    virtual void SetRenderSurface(const RefPtr<RenderSurface>& renderSurface) {}
    virtual void RegisterTextureEvent(TextureRefreshEvent&& textureRefreshEvent) {}
    virtual void RegisterPlatformViewReadyEvent(PlatformViewReadyEvent&& platformViewReadyEvent) {}
    virtual int32_t SetSurface()
    {
        return -1;
    }
    virtual void Dispose() {}
protected:

    ACE_DISALLOW_COPY_AND_MOVE(PlatformViewInterface);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PLATFORMVIEW_PLATFORM_VIEW_INTERFACE_H
