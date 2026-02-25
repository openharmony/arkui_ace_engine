/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/adapter/color_sampler.h"

#include "base/error/error_code.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace OHOS::Ace::NG {
namespace {
std::shared_ptr<Rosen::RSNode> GetRsNode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto renderContext = AceType::DynamicCast<RosenRenderContext>(node->GetRenderContext());
    CHECK_NULL_RETURN(renderContext, nullptr);
    return renderContext->GetRSNode();
}
} // namespace
namespace ColorSampler {

bool RegisterColorSampler(
    const std::string& componentId, uint64_t interval, ColorSamplerCallback callback, uint32_t notifyThreshold)
{
    auto node = Inspector::GetFrameNodeByKey(componentId);
    CHECK_NULL_RETURN(node && callback, false);

    auto rsNode = GetRsNode(node);
    CHECK_NULL_RETURN(rsNode, false);
    return false; // disabled
}

bool UnregisterColorSampler(const std::string& componentId)
{
    auto node = Inspector::GetFrameNodeByKey(componentId);
    CHECK_NULL_RETURN(node, false);

    auto rsNode = GetRsNode(node);
    CHECK_NULL_RETURN(rsNode, false);

    bool success = rsNode->UnregisterColorPickerCallback();

    if (!success) {
        TAG_LOGW(AceLogTag::ACE_COLOR_SAMPLER, "Failed to unregister color sampler callback");
        return false;
    }
    TAG_LOGI(AceLogTag::ACE_COLOR_SAMPLER, "Successfully unregistered color sampler callback");
    return true;
}
} // namespace ColorSampler
} // namespace OHOS::Ace::NG
