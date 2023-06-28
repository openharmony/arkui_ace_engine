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

#include "base/utils/noncopyable.h"
#include "core/components_ng/pattern/pattern.h"
#include "root_layout_algorithm.h"

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
    }

    void SetAppBgColor(const Color& color, bool isContainerModal)
    {
        auto rootNode = GetHost();
        CHECK_NULL_VOID(rootNode);
        RefPtr<FrameNode> stage;
        if (isContainerModal) {
            auto container = DynamicCast<FrameNode>(rootNode->GetChildren().front());
            CHECK_NULL_VOID(container);
            auto column = DynamicCast<FrameNode>(container->GetChildren().front());
            CHECK_NULL_VOID(column);
            auto stack = DynamicCast<FrameNode>(column->GetChildren().back());
            CHECK_NULL_VOID(stack);
            stage = DynamicCast<FrameNode>(stack->GetChildren().front());
        } else {
            stage = DynamicCast<FrameNode>(rootNode->GetChildren().front());
        }
        CHECK_NULL_VOID(stage);
        LOGI("SetAppBgColor in page node successfully, bgColor is %{public}u", color.GetValue());
        stage->GetRenderContext()->UpdateBackgroundColor(color);
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(RootPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ROOT_ROOT_PATTERN_H
