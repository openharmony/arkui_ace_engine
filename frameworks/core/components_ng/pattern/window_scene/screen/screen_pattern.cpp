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

#include "core/components_ng/pattern/window_scene/screen/screen_pattren.h"

#include "input_manager.h"
#include "ipc_skeleton.h"
#include "root_scene.h"
#include "ui/rs_display_node.h"

#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/adapter/rosen_window.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float DIRECTION0 = 0;
constexpr float DIRECTION90 = 90;
constexpr float DIRECTION180 = 180;
constexpr float DIRECTION270 = 270;
constexpr uint32_t DOT_PER_INCH = 160;

MMI::Direction ConvertDegreeToMMIRotation(float degree)
{
    if (NearEqual(degree, DIRECTION0)) {
        return MMI::DIRECTION0;
    }
    if (NearEqual(degree, DIRECTION90)) {
        return MMI::DIRECTION90;
    }
    if (NearEqual(degree, DIRECTION180)) {
        return MMI::DIRECTION180;
    }
    if (NearEqual(degree, DIRECTION270)) {
        return MMI::DIRECTION270;
    }
    return MMI::DIRECTION0;
}
} // namespace

void ScreenPattern::OnAttachToFrameNode()
{
    CHECK_NULL_VOID(screenSession_);
    auto displayNode = screenSession_->GetDisplayNode();
    CHECK_NULL_VOID(displayNode);

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto context = AceType::DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
    CHECK_NULL_VOID(context);
    context->SetRSNode(displayNode);

    UpdateDisplayInfo();

    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto window = static_cast<RosenWindow*>(container->GetWindow());
    CHECK_NULL_VOID(window);
    auto rootScene = static_cast<Rosen::RootScene*>(window->GetRSWindow().GetRefPtr());
    CHECK_NULL_VOID(rootScene);
    auto screenBounds = screenSession_->GetScreenProperty().GetBounds();
    Rosen::Rect rect = { screenBounds.rect_.left_, screenBounds.rect_.top_,
        screenBounds.rect_.width_, screenBounds.rect_.height_ };
    float density = screenSession_->GetScreenProperty().GetDensity();
    rootScene->SetDisplayDensity(density);
    rootScene->UpdateViewportConfig(rect, Rosen::WindowSizeChangeReason::UNDEFINED);
}

void ScreenPattern::UpdateDisplayInfo()
{
    CHECK_NULL_VOID(screenSession_);

    auto pid = IPCSkeleton::GetCallingPid();
    auto uid = IPCSkeleton::GetCallingUid();
    auto screenId = screenSession_->GetScreenId();
    auto screenProperty = screenSession_->GetScreenProperty();
    auto dpi = screenProperty.GetDensity() * DOT_PER_INCH;

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintRect = host->GetPaintRectWithTransform();
    MMI::Rect screenRect = {
        paintRect.Left(),
        paintRect.Top(),
        paintRect.Width(),
        paintRect.Height()
    };

    MMI::WindowInfo windowInfo = {
        .id = 0,    // root scene id 0
        .pid = pid,
        .uid = uid,
        .area = screenRect,
        .defaultHotAreas = { screenRect },
        .pointerHotAreas = { screenRect },
        .agentWindowId = 0, // root scene id 0
        .flags = 0  // touchable
    };

    MMI::DisplayInfo displayInfo = {
        .id = screenId,
        .x = paintRect.Left(),
        .y = paintRect.Top(),
        .width = paintRect.Width(),
        .height = paintRect.Height(),
        .dpi = dpi,
        .name = "display" + std::to_string(screenId),
        .uniq = "default" + std::to_string(screenId),
        .direction = ConvertDegreeToMMIRotation(DIRECTION0)
    };

    MMI::DisplayGroupInfo displayGroupInfo = {
        .width = paintRect.Width(),
        .height = paintRect.Height(),
        .focusWindowId = 0, // root scene id 0
        .windowsInfo = { windowInfo },
        .displaysInfo = { displayInfo }
    };
    MMI::InputManager::GetInstance()->UpdateDisplayInfo(displayGroupInfo);
}

bool ScreenPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& changeConfig)
{
    UpdateDisplayInfo();
    return true;
}
} // namespace OHOS::Ace::NG
