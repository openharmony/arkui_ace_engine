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

#include "ace_pixelmap_stub.h"

#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/form/form_model_ng.h"
#include "core/components_ng/pattern/shape/circle_model_ng.h"
#include "core/components_ng/pattern/shape/circle_pattern.h"
#include "core/components_ng/pattern/shape/ellipse_model_ng.h"
#include "core/components_ng/pattern/shape/ellipse_pattern.h"
#include "core/components_ng/pattern/shape/path_layout_algorithm.h"
#include "core/components_ng/render/animation_utils.h"

namespace OHOS::Ace {
void PipelineBase::PrepareOpenImplicitAnimation() {}

void PipelineBase::PrepareCloseImplicitAnimation() {}

void PipelineBase::GetUIFontConfig(OHOS::Ace::FontConfigJsonInfo&) {}

bool PipelineBase::GetSystemFont(const std::string& fontName, FontInfo& fontInfo)
{
    return false;
}

void NG::PipelineContext::SetCallBackNode(const WeakPtr<NG::FrameNode>& node) {}

RefPtr<NG::FrameNode> NG::CircleModelNG::CreateFrameNode(int32_t nodeId)
{
    return FrameNode::CreateFrameNode(
        V2::CIRCLE_ETS_TAG, nodeId, AceType::MakeRefPtr<CirclePattern>());
}

RefPtr<NG::FrameNode> NG::FormModelNG::CreateFrameNode(int32_t nodeId)
{
    return nullptr;
}

std::optional<NG::SizeF> NG::PathLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    return {};
}

void NG::PathLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper) {}

void AnimationUtils::AddDurationKeyFrame(int duration, const RefPtr<Curve>& curve,
    const PropertyCallback& callback, const RefPtr<PipelineBase>& context) {}

bool SystemProperties::IsFormAnimationLimited()
{
    return true;
}

std::string SystemProperties::GetWebDebugRenderMode()
{
    return "none";
}

RefPtr<PixelMap> PixelMap::Create(std::unique_ptr<Media::PixelMap>&& pixmap)
{
    return AceType::MakeRefPtr<PixelMapStub>();
}
} // namespace OHOS::Ace