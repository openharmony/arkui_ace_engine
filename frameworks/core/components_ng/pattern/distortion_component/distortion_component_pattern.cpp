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

#include "core/components_ng/pattern/distortion_component/distortion_component_pattern.h"

#include "core/components_ng/base/frame_node.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {

void DistortionComponentPattern::SetDistortion(const DistortionParam& options)
{
    distortion_ = options;
    UpdateDistortion();
}

void DistortionComponentPattern::CreateContentNode(const RefPtr<FrameNode>& builderNode)
{
    if (contentNode_) {
        return; // Already created
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    // Create content node with same distortion parameters
    contentNode_ = FrameNode::GetOrCreateFrameNode(
        V2::DISTORTION_CONTENT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<Pattern>(); });
    
    // Add content node as child of distortion component
    host->AddChild(contentNode_);
    
    contentNode_->AddChild(builderNode);

    // Apply same size as parent
    auto contentLayoutProperty = contentNode_->GetLayoutProperty();
    CHECK_NULL_VOID(contentLayoutProperty);

    contentLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    // Mark dirty to trigger layout
    contentNode_->MarkModifyDone();
}

/**
 * @brief Apply distortion transformation when components bounds is ready.
 * The update time must be after the component size is confirmed. 
 */
void DistortionComponentPattern::UpdateDistortion()
{
    // 1. Apply distortion to parent node (DistortionComponent)
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    // Set distortion parameters to SDF Shape
    context->UpdateDistortionParam(distortion_);

    // 2. Apply same distortion to content node
    if (!contentNode_) {
        ACE_SCOPED_TRACE("DistortionComponent's contentNode is null");
        return;
    }
    auto contentNodeContext = contentNode_->GetRenderContext();
    CHECK_NULL_VOID(contentNodeContext);
    if (contentNodeContext) {
        contentNodeContext->UpdateForegroundFilterDistortionParam(distortion_);
    }
}

bool DistortionComponentPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool /*skipLayout*/)
{
    if (skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }

    UpdateDistortion();
    return true;
}

} // namespace OHOS::Ace::NG
