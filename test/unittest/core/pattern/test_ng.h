/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <type_traits>

#define private public
#define protected public
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern//linear_layout/column_model_ng.h"
#include "core/components_ng/pattern//linear_layout/row_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_animation_consts.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
constexpr Dimension FILL_LENGTH = Dimension(1.0, DimensionUnit::PERCENT);
constexpr int32_t NULL_VALUE = -1;
constexpr double DEFAULT_FRICTION = 0.6;
constexpr double NEW_DEFAULT_FRICTION = 0.7;
constexpr float DRAG_VELOCITY = 200.f;

class TestNG : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void FlushUITasks();
    void FlushUITasks(const RefPtr<FrameNode>& frameNode);
    void CreateDone();
    RefPtr<FrameNode> GetStageNode();
    void MountToStageNode(const RefPtr<FrameNode>& frameNode);
    void RemoveFromStageNode();
    uint64_t GetActions(const RefPtr<AccessibilityProperty>& accessibilityProperty);
    TouchEventInfo CreateTouchEventInfo(TouchType touchType, Offset location);
    static RefPtr<ThemeConstants> CreateThemeConstants(const std::string& patternName);
    void FlushExpandSafeAreaTask();
    void CreateLayoutTask(const RefPtr<FrameNode>& frameNode);
    RefPtr<FrameNode> CreateText(const std::u16string& content, const std::function<void(TextModelNG)>& callback);
    RefPtr<FrameNode> CreateRow(const std::function<void(RowModelNG)>& callback);
    RefPtr<FrameNode> CreateColumn(const std::function<void(ColumnModelNG)>& callback);
    RefPtr<FrameNode> CreateStack(const std::function<void(StackModelNG)>& callback);
    void SetSize(std::optional<Axis> axis, const CalcLength& crossSize, const CalcLength& mainSize);
    AssertionResult IsExist(const RefPtr<FrameNode>& frameNode, int32_t index);
    AssertionResult IsExistAndActive(const RefPtr<FrameNode>& frameNode, int32_t index);
    AssertionResult IsExistAndInActive(const RefPtr<FrameNode>& frameNode, int32_t index);

    AssertionResult IsEqual(const double& actual, const double& expected)
    {
        if (NearEqual(actual, expected)) {
            return AssertionSuccess();
        }
        return AssertionFailure() << "Actual: " << actual << " Expected: " << expected;
    }

    AssertionResult IsEqual(const float& actual, const float& expected)
    {
        if (NearEqual(actual, expected)) {
            return AssertionSuccess();
        }
        return AssertionFailure() << "Actual: " << actual << " Expected: " << expected;
    }

    AssertionResult IsEqual(const int32_t& actual, const int32_t& expected)
    {
        if (NearEqual(actual, expected)) {
            return AssertionSuccess();
        }
        return AssertionFailure() << "Actual: " << actual << " Expected: " << expected;
    }

    AssertionResult IsEqual(const std::string& actual, const std::string& expected)
    {
        if (NearEqual(actual, expected)) {
            return AssertionSuccess();
        }
        return AssertionFailure() << "Actual: " << actual << " Expected: " << expected;
    }

    template<typename T>
    AssertionResult IsEqual(const T& actual, const T& expected)
    {
        if (NearEqual(actual, expected)) {
            return AssertionSuccess();
        }
        return AssertionFailure() << "Actual: " << actual.ToString() << " Expected: " << expected.ToString();
    }

    AssertionResult IsEqual(const NG::OverScrollOffset& actual, const NG::OverScrollOffset& expected)
    {
        if (NearEqual(actual.start, expected.start) && NearEqual(actual.end, expected.end)) {
            return AssertionSuccess();
        }
        return AssertionFailure() << "Actual: " << "{ " << actual.start << " , " << actual.end << " }"
                                  << " Expected: " << "{ " << expected.start << " , " << expected.end << " }";
    }

    AssertionResult IsEqual(const ListItemIndex& actual, const ListItemIndex& expected)
    {
        if (actual.index == expected.index && actual.area == expected.area &&
            actual.indexInGroup == expected.indexInGroup) {
            return AssertionSuccess();
        }
        return AssertionFailure() << "Actual: " << "{ " << actual.index << " , " << actual.area << " , "
                                  << actual.indexInGroup << " }" << " Expected: " << "{ " << expected.index << " , "
                                  << expected.area << " , " << expected.indexInGroup << " }";
    }

    RefPtr<FrameNode> GetChildFrameNode(const RefPtr<FrameNode>& frameNode, int32_t index)
    {
        return AceType::DynamicCast<FrameNode>(frameNode->GetChildByIndex(index));
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

    template<typename T>
    RefPtr<T> GetChildEventHub(const RefPtr<FrameNode>& frameNode, int32_t index)
    {
        return GetChildFrameNode(frameNode, index)->GetOrCreateEventHub<T>();
    }

    RectF GetChildRect(const RefPtr<FrameNode>& frameNode, int32_t index)
    {
        return GetChildFrameNode(frameNode, index)->GetGeometryNode()->GetFrameRect();
    }

    SizeF GetChildSize(const RefPtr<FrameNode>& frameNode, int32_t index)
    {
        return GetChildFrameNode(frameNode, index)->GetGeometryNode()->GetFrameSize();
    }

    OffsetF GetChildOffset(const RefPtr<FrameNode>& frameNode, int32_t index)
    {
        return GetChildFrameNode(frameNode, index)->GetGeometryNode()->GetFrameOffset();
    }

    float GetChildX(const RefPtr<FrameNode>& frameNode, int32_t index)
    {
        return GetChildRect(frameNode, index).GetX();
    }

    float GetChildY(const RefPtr<FrameNode>& frameNode, int32_t index)
    {
        return GetChildRect(frameNode, index).GetY();
    }

    float GetChildWidth(const RefPtr<FrameNode>& frameNode, int32_t index)
    {
        return GetChildRect(frameNode, index).Width();
    }

    float GetChildHeight(const RefPtr<FrameNode>& frameNode, int32_t index)
    {
        return GetChildRect(frameNode, index).Height();
    }

    void ClearOldNodes()
    {
        ElementRegister::GetInstance()->Clear();
    }

    ElementIdType GetElmtId()
    {
        elmtId_++;
        return elmtId_;
    }

    void ResetElmtId()
    {
        elmtId_ = 10000;
    }

    ElementIdType elmtId_ = 10000;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_SCROLL_PATTERN_H
