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
            stage = DynamicCast<FrameNode>(column->GetChildren().back());
        } else {
            stage = DynamicCast<FrameNode>(rootNode->GetChildren().front());
        }
        CHECK_NULL_VOID(stage);
        LOGI("SetAppBgColor in page node successfully, bgColor is %{public}u", color.GetValue());
        auto pages = stage->GetChildren();
        for (const auto& page : pages) {
            auto pageNode = DynamicCast<FrameNode>(page);
            CHECK_NULL_VOID(pageNode);
            pageNode->GetRenderContext()->UpdateBackgroundColor(color);
        }
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(RootPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ROOT_ROOT_PATTERN_H
