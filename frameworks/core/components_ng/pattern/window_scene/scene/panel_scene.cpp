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

#include "core/components_ng/pattern/window_scene/scene/panel_scene.h"

#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace OHOS::Ace::NG {
PanelScene::PanelScene(const sptr<Rosen::Session>& session) : SystemWindowScene(session)
{}

void PanelScene::OnAttachToFrameNode()
{
    SystemWindowScene::OnAttachToFrameNode();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
    CHECK_NULL_VOID(context);
    auto rsNode = Rosen::RSCanvasNode::Create(false, false, WindowSceneHelper::GetRSUIContext(host));
    TAG_LOGD(AceLogTag::ACE_WINDOW, "Create RSCanvasNode: %{public}s",
             WindowSceneHelper::RSNodeToStr(rsNode).c_str());
    CHECK_NULL_VOID(rsNode);
    rsNode->SetSkipCheckInMultiInstance(true);
    context->SetRSNode(rsNode);
    rsNode->SetBoundsChangedCallback(boundsChangedCallback_);
}

uint32_t PanelScene::GetWindowPatternType() const
{
    return static_cast<uint32_t>(WindowPatternType::PANEL_SCENE);
}
} // namespace OHOS::Ace::NG
