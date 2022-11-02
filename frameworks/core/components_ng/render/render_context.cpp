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

#include "core/components_ng/render/render_context.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
void RenderContext::SetRequestFrame(const std::function<void()>& requestFrame)
{
    requestFrame_ = requestFrame;
}

void RenderContext::RequestNextFrame() const
{
    if (requestFrame_) {
        requestFrame_();
    }
}

void RenderContext::SetHostNode(const WeakPtr<FrameNode>& host)
{
    host_ = host;
}

RefPtr<FrameNode> RenderContext::GetHost() const
{
    return host_.Upgrade();
}

void RenderContext::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    ACE_PROPERTY_TO_JSON_VALUE(propBorder_, BorderProperty);
    ACE_PROPERTY_TO_JSON_VALUE(propBackDecoration_, DecorationProperty);
    json->Put("zIndex", propZIndex_.value_or(0));
}
} // namespace OHOS::Ace::NG
