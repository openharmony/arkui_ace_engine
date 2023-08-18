/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_TEST_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_TEST_NG_H

#include "gtest/gtest.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {
namespace {
using namespace testing;
using namespace testing::ext;
constexpr int32_t PLATFORM_VERSION_TEN = 10;
constexpr float DEVICE_WIDTH = 480.f;
constexpr float DEVICE_HEIGHT = 800.f;
constexpr Dimension FILL_LENGTH = Dimension(1.0, DimensionUnit::PERCENT);
constexpr double DEFAULT_FRICTION = 0.6;
constexpr int32_t NULL_INDEX = -1;
} // namespace

class TestNG {
public:
    static void SetWidth(const Dimension& width);
    static void SetHeight(const Dimension& height);
    void RunMeasureAndLayout(const RefPtr<FrameNode>& frameNode,
        float width = DEVICE_WIDTH, float height = DEVICE_HEIGHT);
    void OldRunMeasureAndLayout(const RefPtr<FrameNode>& frameNode,
        float width = DEVICE_WIDTH, float height = DEVICE_HEIGHT);
    uint64_t GetActions(const RefPtr<AccessibilityProperty>& accessibilityProperty);

    testing::AssertionResult IsEqualOffset(Offset offset, Offset expectOffset);
    testing::AssertionResult IsEqualOverScrollOffset(OverScrollOffset offset, OverScrollOffset expectOffset);
    testing::AssertionResult IsEqualRect(Rect rect, Rect expectRect);
    testing::AssertionResult IsEqualRect(RectF rect, RectF expectRect);

    RefPtr<FrameNode> GetChildFrameNode(const RefPtr<FrameNode>& frameNode, int32_t index)
    {
        return AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(index));
    }

    RefPtr<FocusHub> GetChildFocusHub(const RefPtr<FrameNode>& frameNode, int32_t index)
    {
        return GetChildFrameNode(frameNode, index)->GetOrCreateFocusHub();
    }

    template<typename T>
    RefPtr<T> GetChildPattern(const RefPtr<FrameNode>& frameNode, int32_t index)
    {
        RefPtr<Pattern> pattern = GetChildFrameNode(frameNode, index)->GetPattern();
        return AceType::DynamicCast<T>(pattern);
    }

    template<typename T>
    RefPtr<T> GetChildLayoutProperty(const RefPtr<FrameNode>& frameNode, int32_t index)
    {
        RefPtr<LayoutProperty> layoutProperty = GetChildFrameNode(frameNode, index)->GetLayoutProperty();
        return AceType::DynamicCast<T>(layoutProperty);
    }

    template<typename T>
    RefPtr<T> GetChildAccessibilityProperty(const RefPtr<FrameNode>& frameNode, int32_t index)
    {
        return GetChildFrameNode(frameNode, index)->GetAccessibilityProperty<T>();
    }
    
    const RectF& GetChildRect(const RefPtr<FrameNode>& frameNode, int32_t index)
    {
        return GetChildFrameNode(frameNode, index)->GetGeometryNode()->GetFrameRect();
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_PATTERN_H
