/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/window_scene/scene/host/host_window_pattern.h"

#include "core/common/container.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace OHOS::Ace::NG {

class LifecycleListener : public Rosen::ILifecycleListener {
public:
    LifecycleListener(const WeakPtr<HostWindowPattern>& hostWindowPattern) : hostWindowPattern_(hostWindowPattern) {}
    virtual ~LifecycleListener() = default;

    void OnForeground() override
    {
        auto hostWindowPattern = hostWindowPattern_.Upgrade();
        CHECK_NULL_VOID(hostWindowPattern);
        hostWindowPattern->OnForeground();
    }

    void OnBackground() override
    {
        auto hostWindowPattern = hostWindowPattern_.Upgrade();
        CHECK_NULL_VOID(hostWindowPattern);
        hostWindowPattern->OnBackground();
    }

private:
    WeakPtr<HostWindowPattern> hostWindowPattern_;
};

HostWindowPattern::HostWindowPattern(const sptr<Rosen::Session>& session) : session_(session)
{
    LOGI("create HostWindowPattern");
    CHECK_NULL_VOID(session_);

    instanceId_ = Container::CurrentId();

    auto lifecycleListener = std::make_shared<LifecycleListener>(WeakClaim(this));
    session_->RegisterLifecycleListener(lifecycleListener);
}

bool HostWindowPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (!config.frameSizeChange) {
        LOGI("frame size not changed, just return");
        return false;
    }
    CHECK_NULL_RETURN(dirty, false);
    auto geometryNode = dirty->GetGeometryNode();
    auto windowRect = geometryNode->GetFrameRect();
    Rosen::WSRect rect = {
        .posX_ = std::round(windowRect.GetX()),
        .posY_ = std::round(windowRect.GetY()),
        .width_ = std::round(windowRect.Width()),
        .height_ = std::round(windowRect.Height())
    };

    CHECK_NULL_RETURN(session_, false);
    LOGI("update session rect: [%{public}d, %{public}d, %{public}d, %{public}d]",
        rect.posX_, rect.posY_, rect.width_, rect.height_);
    session_->UpdateSessionRect(rect, Rosen::SessionSizeChangeReason::SHOW);
    return false;
}

void HostWindowPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    auto renderContext = AceType::DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
    renderContext->SetClipToBounds(true);
}

void HostWindowPattern::OnModifyDone()
{
    if (clickListener_) {
        return;
    }
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto hostWindowPattern = weak.Upgrade();
        CHECK_NULL_VOID(hostWindowPattern);
        hostWindowPattern->OnClick();
    };
    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    gesture->AddClickEvent(clickListener_);
}

void HostWindowPattern::OnClick()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

} // namespace OHOS::Ace::NG
