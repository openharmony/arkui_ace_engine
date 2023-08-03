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

#define protected public
#define private public
#include "core/components_ng/test/pattern/test_ng.h"

namespace OHOS::Ace::NG {
void TestNG::SetWidth(const Dimension& width)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(width), std::nullopt));
}

void TestNG::SetHeight(const Dimension& height)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(height)));
}

void TestNG::RunMeasureAndLayout(const RefPtr<FrameNode>& frameNode, float width, float height)
{
    frameNode->SetActive();
    frameNode->SetRootMeasureNode();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEVICE_WIDTH, DEVICE_HEIGHT };
    LayoutConstraint.percentReference = { DEVICE_WIDTH, DEVICE_HEIGHT };
    if (NonNegative(width) && NonNegative(height)) {
        LayoutConstraint.selfIdealSize = { width, height };
    }
    LayoutConstraint.maxSize = { DEVICE_WIDTH, DEVICE_HEIGHT };
    frameNode->Measure(LayoutConstraint);
    frameNode->Layout();
}

void TestNG::OldRunMeasureAndLayout(const RefPtr<FrameNode>& frameNode, float width, float height)
{
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    layoutWrapper->SetActive();
    layoutWrapper->SetRootMeasureNode();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEVICE_WIDTH, DEVICE_HEIGHT };
    LayoutConstraint.percentReference = { DEVICE_WIDTH, DEVICE_HEIGHT };
    if (NonNegative(width) && NonNegative(height)) {
        LayoutConstraint.selfIdealSize = { width, height };
    }
    LayoutConstraint.maxSize = { DEVICE_WIDTH, DEVICE_HEIGHT };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();
}

uint64_t TestNG::GetActions(const RefPtr<AccessibilityProperty>& accessibilityProperty)
{
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty->GetSupportAction();
    uint64_t actions = 0;
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    return actions;
}

testing::AssertionResult TestNG::IsEqualOffset(Offset offset, Offset expectOffset)
{
    if (offset == expectOffset) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() <<
        "offset: " << offset.ToString() <<
        " != " <<
        "expectOffset: " << expectOffset.ToString();
}

testing::AssertionResult TestNG::IsEqualOverScrollOffset(OverScrollOffset offset, OverScrollOffset expectOffset)
{
    if (NearEqual(offset.start, expectOffset.start) && NearEqual(offset.end, expectOffset.end)) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() << "offset: "
                                       << "{ " << offset.start << " , " << offset.end << " }"
                                       << " != "
                                       << "expectOffset: "
                                       << "{ " << expectOffset.start << " , " << expectOffset.end << " }";
}

testing::AssertionResult TestNG::IsEqualRect(Rect rect, Rect expectRect)
{
    if (rect == expectRect) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() <<
        "rect: " << rect.ToString() <<
        " != " <<
        "expectRect: " << expectRect.ToString();
}

testing::AssertionResult TestNG::IsEqualRect(RectF rect, RectF expectRect)
{
    if (rect == expectRect) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() <<
        "rect: " << rect.ToString() <<
        " != " <<
        "expectRect: " << expectRect.ToString();
}
} // namespace OHOS::Ace::NG
