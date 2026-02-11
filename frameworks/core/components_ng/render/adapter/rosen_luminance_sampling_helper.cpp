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
 
#include "core/components_ng/render/adapter/rosen_luminance_sampling_helper.h"
 
#include "base/error/error_code.h"
#include "base/utils/utils.h"
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
LuminanceSamplingHelper::LuminanceSamplingHelper() {}

void LuminanceSamplingHelper::SetSamplingOptions(const WeakPtr<FrameNode>& node, int32_t samplingInterval,
    int32_t brightThreshold, int32_t darkThreshold, const std::optional<EdgesParam>& region)
{
    auto rsNode = GetRsNode(node.Upgrade());
    CHECK_NULL_VOID(rsNode);
    std::optional<Rosen::Vector4f> setRegion = std::nullopt;
    if (region) {
        float top = 0;
        float bottom = 0;
        float left = 0;
        float right = 0;
        if (!region->top || !region->bottom || !region->left || !region->right) {
            return;
        } else {
            top = region->top->ConvertToPx();
            bottom = region->bottom->ConvertToPx();
            left = region->left->ConvertToPx();
            right = region->right->ConvertToPx();
            setRegion = Rosen::Vector4f(left, top, right, bottom);
        }
    }
    rsNode->SetColorPickerOptions(samplingInterval, std::make_pair(darkThreshold, brightThreshold), setRegion);
}

void LuminanceSamplingHelper::RegisterSamplingCallback(const WeakPtr<NG::FrameNode>& node, const SamplingCallback& func)
{
    auto rsNode = GetRsNode(node.Upgrade());
    CHECK_NULL_VOID(rsNode);
    rsNode->SetColorPickerCallback(func);
}

void LuminanceSamplingHelper::UnRegisterSamplingCallback(const WeakPtr<NG::FrameNode>& node)
{
    auto rsNode = GetRsNode(node.Upgrade());
    CHECK_NULL_VOID(rsNode);
    rsNode->UnregisterColorPickerCallback();
}
} // namespace OHOS::Ace::NG
