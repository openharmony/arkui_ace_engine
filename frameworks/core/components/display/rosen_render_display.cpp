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

#include "core/components/display/rosen_render_display.h"

#include "render_service_client/core/ui/rs_node.h"

namespace OHOS::Ace {

void RosenRenderDisplay::Update(const RefPtr<Component>& component)
{
    RenderDisplay::Update(component);
    if (auto rsNode = GetRSNode()) {
        rsNode->SetAlpha(opacity_ / 255.0);
    }
}

void RosenRenderDisplay::OnOpacityAnimationCallback()
{
    double value = animatableOpacity_.GetValue();
    opacity_ = static_cast<uint8_t>(round(value * UINT8_MAX));

    if (auto rsNode = GetRSNode()) {
        rsNode->SetAlpha(value);
    }
}

void RosenRenderDisplay::Paint(RenderContext& context, const Offset& offset)
{
    LOGD("Paint");
    if (visible_ == VisibleType::VISIBLE) {
        RenderNode::Paint(context, offset);
    }
}

} // namespace OHOS::Ace