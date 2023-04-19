/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "adapter/preview/entrance/rs_ace_view.h"

#include <cinttypes>

#include "base/log/dump_log.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "base/utils/macros.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/components/theme/theme_manager.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"
#include "core/image/image_cache.h"

namespace OHOS::Ace::Platform {
void RSAceView::RegisterTouchEventCallback(TouchEventCallback&& callback)
{
    ACE_DCHECK(callback);
    touchEventCallback_ = std::move(callback);
}

void RSAceView::RegisterKeyEventCallback(KeyEventCallback&& callback)
{
    ACE_DCHECK(callback);
    keyEventCallback_ = std::move(callback);
}

void RSAceView::RegisterMouseEventCallback(MouseEventCallback&& callback)
{
    ACE_DCHECK(callback);
    mouseEventCallback_ = std::move(callback);
}

void RSAceView::RegisterAxisEventCallback(AxisEventCallback&& callback)
{
    ACE_DCHECK(callback);
    axisEventCallback_ = std::move(callback);
}

void RSAceView::RegisterRotationEventCallback(RotationEventCallBack&& callback)
{
    ACE_DCHECK(callback);
    rotationEventCallBack_ = std::move(callback);
}

void RSAceView::Launch()
{
}

bool RSAceView::Dump(const std::vector<std::string>& params)
{
    return false;
}

void RSAceView::ProcessIdleEvent(int64_t deadline)
{
    if (idleCallback_) {
        idleCallback_(deadline);
    }
}

bool RSAceView::HandleTouchEvent(const TouchEvent& touchEvent)
{
    if (touchEvent.type == TouchType::UNKNOWN) {
        LOGW("Unknown event.");
        return false;
    }

    LOGD("HandleTouchEvent touchEvent.x: %{public}lf, touchEvent.y: %{public}lf, touchEvent.size: %{public}lf",
        touchEvent.x, touchEvent.y, touchEvent.size);
    auto event = touchEvent.UpdatePointers();
    if (touchEventCallback_) {
        touchEventCallback_(event, nullptr);
    }

    return true;
}

bool RSAceView::HandleKeyEvent(const KeyEvent& keyEvent)
{
    if (!keyEventCallback_) {
        return false;
    }

    return keyEventCallback_(keyEvent);
}

std::unique_ptr<DrawDelegate> RSAceView::GetDrawDelegate()
{
    auto drawDelegate = std::make_unique<DrawDelegate>();

    drawDelegate->SetDrawRSFrameCallback([this](std::shared_ptr<Rosen::RSNode>& node, const Rect& rect) {
        if (!node) {
            return;
        }
        LOGD("DrawRSFrameCallback called!!");
    });

    return drawDelegate;
}

std::unique_ptr<PlatformWindow> RSAceView::GetPlatformWindow()
{
    return nullptr;
}

const void* RSAceView::GetNativeWindowById(uint64_t textureId)
{
    return nullptr;
}
} // namespace OHOS::Ace::Platform
