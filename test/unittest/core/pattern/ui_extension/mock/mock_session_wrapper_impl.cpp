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
#define private public
#define protected public
#include "core/components_ng/pattern/ui_extension/session_wrapper_impl.h"

#include <cmath>
#include <memory>

#include "accessibility_event_info.h"
#include "refbase.h"
#include "session_manager/include/extension_session_manager.h"
#include "transaction/rs_sync_transaction_controller.h"
#include "transaction/rs_transaction.h"
#include "ui/rs_surface_node.h"
#include "want_params.h"
#include "wm/wm_common.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "base/error/error_code.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#include "core/components_ng/pattern/window_scene/scene/system_window_scene.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

SessionWrapperImpl::SessionWrapperImpl(const WeakPtr<UIExtensionPattern>& hostPattern, int32_t instanceId,
    bool isTransferringCaller, SessionType sessionType)
    : hostPattern_(hostPattern), instanceId_(instanceId), isTransferringCaller_(isTransferringCaller),
      sessionType_(sessionType)
{
    auto pattern = hostPattern.Upgrade();
    uiExtensionId_ = pattern ? pattern->GetUiExtensionId() : 0;
    taskExecutor_ = Container::CurrentTaskExecutor();
    Rosen::SessionInfo sessionInfo = {
        .bundleName_ = "123",
        .abilityName_ = "123",
    };
    session_ = new OHOS::Rosen::ExtensionSession(sessionInfo);
}

SessionWrapperImpl::~SessionWrapperImpl() {}

void SessionWrapperImpl::CreateSession(const AAFwk::Want& want, const SessionConfig& config)
{
}

void SessionWrapperImpl::UpdateSessionConfig()
{
}

void SessionWrapperImpl::DestroySession()
{
}

bool SessionWrapperImpl::IsSessionValid()
{
    if (session_) {
        return true;
    }
    return false;
}

int32_t SessionWrapperImpl::GetSessionId() const
{
    return 1;
}

const std::shared_ptr<AAFwk::Want> SessionWrapperImpl::GetWant()
{
    return nullptr;
}

bool SessionWrapperImpl::NotifyFocusEventSync(bool isFocus)
{
    return true;
}
bool SessionWrapperImpl::NotifyFocusStateSync(bool focusState)
{
    return true;
}

bool SessionWrapperImpl::NotifyBackPressedSync()
{
    return true;
}

bool SessionWrapperImpl::NotifyPointerEventSync(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    return true;
}

bool SessionWrapperImpl::NotifyKeyEventSync(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent, bool isPreIme)
{
    return true;
}

bool SessionWrapperImpl::NotifyKeyEventAsync(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent, bool isPreIme)
{
    return true;
}

bool SessionWrapperImpl::NotifyAxisEventSync(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent)
{
    return true;
}

bool SessionWrapperImpl::NotifyFocusEventAsync(bool isFocus)
{
    return true;
}

bool SessionWrapperImpl::NotifyFocusStateAsync(bool focusState)
{
    return true;
}

bool SessionWrapperImpl::NotifyBackPressedAsync()
{
    return false;
}
bool SessionWrapperImpl::NotifyPointerEventAsync(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    return true;
}
bool SessionWrapperImpl::NotifyKeyEventAsync(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent)
{
    return true;
}
bool SessionWrapperImpl::NotifyAxisEventAsync(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent)
{
    return true;
}

void SessionWrapperImpl::NotifyCreate()
{
}

int32_t SessionWrapperImpl::GetWindowSceneId()
{
    return 1;
}

void SessionWrapperImpl::NotifyForeground()
{
}

void SessionWrapperImpl::NotifyBackground()
{
}
void SessionWrapperImpl::NotifyDestroy(bool isHandleError)
{
}

void SessionWrapperImpl::NotifyConfigurationUpdate() {}

void SessionWrapperImpl::OnConnect()
{
}

void SessionWrapperImpl::OnDisconnect(bool isAbnormal)
{
}

void SessionWrapperImpl::OnExtensionTimeout(int32_t /* errorCode */)
{
}

void SessionWrapperImpl::OnAccessibilityEvent(const Accessibility::AccessibilityEventInfo& info, int64_t offset)
{
}

void SessionWrapperImpl::TransferAccessibilityHoverEvent(float pointX, float pointY, int32_t sourceType,
    int32_t eventType, int64_t timeMs)
{
}

void SessionWrapperImpl::TransferAccessibilityChildTreeRegister(
    uint32_t windowId, int32_t treeId, int64_t accessibilityId)
{
}

void SessionWrapperImpl::TransferAccessibilityChildTreeDeregister()
{
}

void SessionWrapperImpl::TransferAccessibilityDumpChildInfo(
    const std::vector<std::string>& params, std::vector<std::string>& info)
{
}

std::shared_ptr<Rosen::RSSurfaceNode> SessionWrapperImpl::GetSurfaceNode() const
{
    if (session_) {
        std::string surfaceNodeName = "UIExtensionSurfaceNode";
        struct Rosen::RSSurfaceNodeConfig surfaceNodeConfig = { .SurfaceNodeName = surfaceNodeName };
        std::shared_ptr<Rosen::RSSurfaceNode> rsSurfaceNode;
        rsSurfaceNode = std::make_shared<OHOS::Rosen::RSSurfaceNode>(surfaceNodeConfig, true);
        return rsSurfaceNode;
    }
    return nullptr;
}

void SessionWrapperImpl::NotifyDisplayArea(const RectF& displayArea)
{
}

void SessionWrapperImpl::NotifySizeChangeReason(
    WindowSizeChangeReason type, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
}

void SessionWrapperImpl::NotifyOriginAvoidArea(const Rosen::AvoidArea& avoidArea, uint32_t type) const
{
}

bool SessionWrapperImpl::NotifyOccupiedAreaChangeInfo(
    sptr<Rosen::OccupiedAreaChangeInfo> info, bool needWaitLayout)
{
    return true;
}

void SessionWrapperImpl::SendDataAsync(const AAFwk::WantParams& params) const
{
}

int32_t SessionWrapperImpl::SendDataSync(const AAFwk::WantParams& wantParams, AAFwk::WantParams& reWantParams) const
{
    return 1;
}

void SessionWrapperImpl::UpdateSessionViewportConfig()
{
}

uint32_t SessionWrapperImpl::GetReasonDump() const
{
    return 1;
}

void SessionWrapperImpl::NotifyUieDump(const std::vector<std::string>& params, std::vector<std::string>& info)
{
}

WindowSizeChangeReason SessionWrapperImpl::GetSizeChangeReason() const
{
    return static_cast<WindowSizeChangeReason>(0);
}
} // namespace OHOS::Ace::NG
