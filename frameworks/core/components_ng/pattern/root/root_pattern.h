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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ROOT_ROOT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ROOT_ROOT_PATTERN_H

#include "interfaces/inner_api/ace/arkui_rect.h"

#include "base/utils/noncopyable.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/root/root_layout_algorithm.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
// RootPattern is the base class for root render node.
class ACE_EXPORT RootPattern : public Pattern {
    DECLARE_ACE_TYPE(RootPattern, Pattern);

public:
    RootPattern() = default;
    ~RootPattern() override = default;

    bool IsRootPattern() const override
    {
        return true;
    }

    bool IsMeasureBoundary() const override
    {
        return true;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<RootLayoutAlgorithm>();
    }

    void OnAttachToFrameNode() override
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
        LOGI("root node OnAttachToFrameNode, id:%{public}d", host->GetId());
    }

    void OnDetachFromFrameNode(FrameNode* frameNode) override
    {
        LOGI("root node OnDetachFromFrameNode, id:%{public}d", frameNode->GetId());
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& /*unused*/, const DirtySwapConfig& /*unused*/) override
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        auto children = host->GetChildren();
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_RETURN(pipeline, false);
        auto iter = std::find_if(children.begin(), children.end(),
            [](const RefPtr<UINode>& node) { return node->GetTag() == V2::STAGE_ETS_TAG; });
        if (iter == children.end() || (*iter) == children.back()) {
            if (!pipeline->GetOverlayNodePositions().empty()) {
                pipeline->TriggerOverlayNodePositionsUpdateCallback({});
            }
            pipeline->SetOverlayNodePositions({});
            return false;
        }
        std::vector<Ace::RectF> positions;
        for (++iter; iter != children.end(); iter++) {
            auto frameNode = AceType::DynamicCast<FrameNode>(*iter);
            if (!frameNode) {
                continue;
            }
            auto frameRect = frameNode->GetGeometryNode()->GetFrameRect();
            auto item = Ace::RectF(frameRect.GetX(), frameRect.GetY(), frameRect.Width(), frameRect.Height());
            positions.emplace_back(item);
        }
        auto funcEqual = [](const Ace::RectF& newRect, const Ace::RectF& rect) {
            return NearEqual(newRect.GetX(), rect.GetX()) && NearEqual(newRect.GetY(), rect.GetY()) &&
                   NearEqual(newRect.Width(), rect.Width()) && NearEqual(newRect.Height(), rect.Height());
        };
        auto oldPositions = pipeline->GetOverlayNodePositions();
        if (std::equal(positions.begin(), positions.end(), oldPositions.begin(), oldPositions.end(), funcEqual)) {
            return false;
        }
        pipeline->TriggerOverlayNodePositionsUpdateCallback(positions);
        pipeline->SetOverlayNodePositions(positions);
        return false;
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(RootPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ROOT_ROOT_PATTERN_H
