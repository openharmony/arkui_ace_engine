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

#include "core/components_ng/pattern/window_scene/scene/window_scene.h"

#include "ui/rs_surface_node.h"

#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t COLOR_BLACK = 0xff000000;
constexpr uint32_t COLOR_WHITE = 0xffffffff;
} // namespace

WindowScene::WindowScene(const sptr<Rosen::Session>& session)
{
    session_ = session;
    RegisterLifecycleListener();
}

WindowScene::~WindowScene()
{
    UnregisterLifecycleListener();
}

void WindowScene::UpdateSession(const sptr<Rosen::Session>& session)
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(session);
    if (session_->GetPersistentId() == session->GetPersistentId()) {
        return;
    }

    LOGI("session %{public}" PRIu64 " changes to %{public}" PRIu64,
        session_->GetPersistentId(), session->GetPersistentId());
    session_ = session;
    auto surfaceNode = session_->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);

    CHECK_NULL_VOID(contentNode_);
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(contentNode_->GetRenderContext());
    CHECK_NULL_VOID(context);
    context->SetRSNode(surfaceNode);
}

void WindowScene::OnForeground()
{
    CHECK_NULL_VOID(snapshotNode_);

    ContainerScope scope(instanceId_);

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    host->RemoveChild(snapshotNode_);
    snapshotNode_.Reset();
    host->AddChild(contentNode_);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void WindowScene::OnBackground()
{
    ContainerScope scope(instanceId_);

    snapshotNode_ = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto imageLayoutProperty = snapshotNode_->GetLayoutProperty<ImageLayoutProperty>();
    imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    auto backgroundColor = SystemProperties::GetColorMode() == ColorMode::DARK ? COLOR_BLACK : COLOR_WHITE;
    snapshotNode_->GetRenderContext()->UpdateBackgroundColor(Color(backgroundColor));

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveChild(contentNode_);
    host->AddChild(snapshotNode_);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    CHECK_NULL_VOID(session_);
    auto snapshot = session_->GetSnapshot();
    auto pixelMap = PixelMap::CreatePixelMap(&snapshot);

    CHECK_NULL_VOID(pixelMap);
    imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(pixelMap));
    imageLayoutProperty->UpdateImageFit(ImageFit::FILL);
    snapshotNode_->MarkModifyDone();
}

void WindowScene::OnSetDepth(const int32_t depth)
{
    CHECK_NULL_VOID(session_);
    session_->SetZOrder(static_cast<uint32_t>(depth));
}
} // namespace OHOS::Ace::NG
