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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DISTORTION_COMPONENT_DISTORTION_COMPONENT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DISTORTION_COMPONENT_DISTORTION_COMPONENT_PATTERN_H

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/distortion_component/distortion_component_options.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT DistortionComponentPattern : public Pattern {
    DECLARE_ACE_TYPE(DistortionComponentPattern, Pattern);

public:
    DistortionComponentPattern() = default;
    ~DistortionComponentPattern() override = default;

    /**
     * Get current distortion parameters.
     *
     * @returns const DistortionParam& The distortion parameters
     */
    const DistortionParam& GetDistortion() const { return distortion_; }

    void SetDistortion(const DistortionParam& options);

    void UpdateDistortion();

    /**
     * Create the content node for mounting developer content.
     * The content node is created immediately after parent node creation.
     */
    void CreateContentNode(const RefPtr<FrameNode>& builderNode);
    
    /**
     * Get the content node.
     *
     * @returns RefPtr<FrameNode> The content node
     */
    RefPtr<FrameNode> GetContentNode() const { return contentNode_; }

    bool IsAtomicNode() const override
    {
        return true;
    }

    bool IsSupportDrawModifier() const override
    {
        return false;
    }

    const DistortionParam& GetOptions() const
    {
        return distortion_;
    }

    bool OnDirtyLayoutWrapperSwap(
        const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;
private:

    DistortionParam distortion_;
    RefPtr<FrameNode> contentNode_;
    ACE_DISALLOW_COPY_AND_MOVE(DistortionComponentPattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DISTORTION_COMPONENT_DISTORTION_COMPONENT_PATTERN_H