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

#include "core/components_ng/pattern/window_scene/screen/screen_pattern.h"

#include <mutex>

#include "ipc_skeleton.h"
#include "root_scene.h"
#include "screen_scene.h"
#include "screen_manager.h"

#include "core/common/container.h"
#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#include "core/components_ng/pattern/window_scene/scene/window_scene_layout_manager.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/adapter/rosen_window.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float DIRECTION0 = 0;
constexpr float DIRECTION90 = 90;
constexpr float DIRECTION180 = 180;
constexpr float DIRECTION270 = 270;
constexpr uint32_t DOT_PER_INCH = 160;

std::vector<MMI::DisplayInfo> g_displayInfoVector;

std::mutex g_vecLock;

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

float ScreenPattern::screenMaxWidth_;
float ScreenPattern::screenMaxHeight_;

ScreenPattern::ScreenPattern(const sptr<Rosen::ScreenSession>& screenSession)
{
    SetScreenSession(screenSession);
}

void ScreenPattern::SetScreenSession(const sptr<Rosen::ScreenSession>& screenSession)
{
    screenSession_ = screenSession;
    if (screenSession_ != nullptr) {
        screenSession_->SetUpdateToInputManagerCallback(std::bind(&ScreenPattern::UpdateToInputManager,
            this, std::placeholders::_1));
        screenSession_->SetUpdateScreenPivotCallback(std::bind(
            &ScreenPattern::UpdateRenderPivot, this, std::placeholders::_1, std::placeholders::_2));
    }
}

void ScreenPattern::OnAttachToFrameNode()
{
    CHECK_NULL_VOID(screenSession_);
    auto displayNode = screenSession_->GetDisplayNode();
    CHECK_NULL_VOID(displayNode);

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetScreenNode(host);

    auto context = AceType::DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
    CHECK_NULL_VOID(context);
    context->SetRSNode(displayNode);
    auto instance = WindowSceneLayoutManager::GetInstance();
    if (instance) {
        instance->RegisterScreenNode(screenSession_->GetScreenId(), host);
    }
}

void ScreenPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    if (screenSession_) {
        auto instance = WindowSceneLayoutManager::GetInstance();
        if (instance) {
            instance->UnregisterScreenNode(screenSession_->GetScreenId());
        }
    }
    CHECK_NULL_VOID(frameNode);
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(frameNode->GetRenderContext());
    CHECK_NULL_VOID(context);
    context->ClearModifiers();
}

void ScreenPattern::UpdateDisplayInfo()
{
    CHECK_NULL_VOID(screenSession_);
    auto displayNode = screenSession_->GetDisplayNode();
    CHECK_NULL_VOID(displayNode);
    auto displayNodeRotation = displayNode->GetStagingProperties().GetRotation();
    if (displayNodeRotation < DIRECTION0) {
        displayNodeRotation = -displayNodeRotation;
    }

    UpdateToInputManager(displayNodeRotation);
}

void ScreenPattern::UpdateRenderPivot(float pivotX, float pivotY)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->SetRenderPivot(pivotX, pivotY);
    WindowSceneHelper::FlushImplicitTransaction(host);
}

void ScreenPattern::UpdateToInputManager(float rotation)
{
    CHECK_NULL_VOID(screenSession_);
    auto pid = IPCSkeleton::GetCallingRealPid();
    auto uid = IPCSkeleton::GetCallingUid();
    auto screenId = screenSession_->GetScreenId();
    auto dpi = GetDensityInCurrentResolution() * DOT_PER_INCH;

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto paintRect = renderContext->GetPaintRectWithTransform();
    auto tempHeight = paintRect.Height();
    auto tempWidth = paintRect.Width();
    if (rotation != DIRECTION0 && rotation != DIRECTION180) {
        auto temp = tempWidth;
        tempWidth = tempHeight;
        tempHeight = temp;
    }
    screenMaxWidth_ = std::max(screenMaxWidth_, tempWidth);
    screenMaxHeight_ = std::max(screenMaxHeight_, tempHeight);

    MMI::Rect screenRect = {
        paintRect.Left(),
        paintRect.Top(),
        screenMaxWidth_,
        screenMaxHeight_,
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
        .direction = ConvertDegreeToMMIRotation(rotation)
    };
    InputManagerUpdateDisplayInfo(paintRect, displayInfo, windowInfo);
}

void ScreenPattern::InputManagerUpdateDisplayInfo(RectF paintRect,
    MMI::DisplayInfo displayInfo, MMI::WindowInfo windowInfo)
{
    std::lock_guard<std::mutex> lock(g_vecLock);
    DeduplicateDisplayInfo();
    g_displayInfoVector.insert(g_displayInfoVector.begin(), displayInfo);

    MMI::DisplayGroupInfo displayGroupInfo = {
        .focusWindowId = 0, // root scene id 0
        .windowsInfo = { windowInfo },
        .displaysInfo = g_displayInfoVector
    };
}

void ScreenPattern::DeduplicateDisplayInfo()
{
    auto screenId = screenSession_->GetScreenId();
    auto it = std::remove_if(g_displayInfoVector.begin(), g_displayInfoVector.end(),
        [screenId](MMI::DisplayInfo displayInfo) {
            return displayInfo.id == static_cast<int32_t>(screenId);
        });
    g_displayInfoVector.erase(it, g_displayInfoVector.end());
}

bool ScreenPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& changeConfig)
{
    UpdateDisplayInfo();
    if (screenSession_->GetScreenProperty().GetScreenType() == Rosen::ScreenType::VIRTUAL) {
        return false;
    }
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto window = static_cast<RosenWindow*>(container->GetWindow());
    CHECK_NULL_RETURN(window, false);
    auto rsWindow = window->GetRSWindow();
    CHECK_NULL_RETURN(rsWindow, false);
    auto screenBounds = screenSession_->GetScreenProperty().GetBounds();
    Rosen::Rect rect = { screenBounds.rect_.left_, screenBounds.rect_.top_,
        screenBounds.rect_.width_, screenBounds.rect_.height_ };
    float density = GetDensityInCurrentResolution();
    if (rsWindow->GetClassType() == "RootScene") {
        auto rootScene = static_cast<Rosen::RootScene*>(rsWindow.GetRefPtr());
        CHECK_NULL_RETURN(rootScene, false);
        rootScene->SetDisplayDensity(density);
        int32_t orientation = static_cast<int32_t>(screenSession_->GetScreenProperty().GetDisplayOrientation());
        rootScene->SetDisplayOrientation(orientation);
        rootScene->UpdateViewportConfig(rect, Rosen::WindowSizeChangeReason::UNDEFINED);
    } else if (rsWindow->GetClassType() == "ScreenScene") {
        auto screenScene = static_cast<Rosen::ScreenScene*>(rsWindow.GetRefPtr());
        CHECK_NULL_RETURN(screenScene, false);
        screenScene->SetDisplayDensity(density);
        int32_t orientation = static_cast<int32_t>(screenSession_->GetScreenProperty().GetDisplayOrientation());
        screenScene->SetDisplayOrientation(orientation);
        screenScene->UpdateViewportConfig(rect, Rosen::WindowSizeChangeReason::UNDEFINED);
    } else {
        LOGE("others type");
    }
    return true;
}

float ScreenPattern::GetDensityInCurrentResolution()
{
    sptr<Rosen::Screen> screen = Rosen::ScreenManager::GetInstance().GetScreenById(screenSession_->GetScreenId());
    float density = screenSession_->GetScreenProperty().GetDefaultDensity();
    if (screen != nullptr) {
        screen->GetDensityInCurResolution(density);
    }
    return density;
}

uint32_t ScreenPattern::GetWindowPatternType() const
{
    return static_cast<uint32_t>(WindowPatternType::SCREEN_SCENE);
}
} // namespace OHOS::Ace::NG
