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
#define private public
#define protected public
#include <cstdint>

#include "gtest/gtest.h"

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/key_event.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
bool SystemProperties::GetDebugEnabled()
{
    return false;
}
} // namespace OHOS::Ace
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t FOCUS_NODE_SIZE = 2;
constexpr int32_t NODE_SIZE = 0;
const BlurReason BLUR_REASON_FOCUS_SWITCH = BlurReason::FOCUS_SWITCH;
const BlurReason BLUR_REASON_WINDOW_BLUR = BlurReason::WINDOW_BLUR;
} // namespace

class FocusHubTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void FocusHubTestNg::SetUpTestSuite()
{
    GTEST_LOG_(INFO) << "FocusHubTestNg SetUpTestCase";
}

void FocusHubTestNg::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "FocusHubTestNg TearDownTestCase";
}

void FocusHubTestNg::SetUp()
{
    MockPipelineBase::SetUp();
}

void FocusHubTestNg::TearDown()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: FocusHubCreateTest001
 * @tc.desc: Create FocusHub.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubCreateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusHub with passing is null as parameter.
     * @tc.expected: eventHub_ cannot be updated.
     */
    auto focusHub1 = AceType::MakeRefPtr<FocusHub>(nullptr);
    EXPECT_TRUE(focusHub1->GetFrameNode() == nullptr);
    EXPECT_TRUE(focusHub1->IsEnabled());
    EXPECT_TRUE(!focusHub1->IsFocusableNode());

    /**
     * @tc.steps: step2. Create FocusHub with the WeakPtr eventHub_ which does not own frameNode.
     * @tc.expected: eventHub can be updated, but cannot get frameNode and its related properties.
     */
    auto eventHub2 = AceType::MakeRefPtr<EventHub>();
    auto focusHub2 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub2)));
    EXPECT_TRUE(focusHub2 != nullptr);
    EXPECT_TRUE(focusHub2->GetFrameNode() == nullptr);
    EXPECT_TRUE(focusHub2->GetGeometryNode() == nullptr);
    EXPECT_EQ(focusHub2->GetFrameName(), "NULL");
    EXPECT_EQ(focusHub2->GetInspectorKey(), std::nullopt);

    /**
     * @tc.steps: step3. Invoke GetParentFocusHub without parameter.
     * @tc.expected: FocusHub will return frameNode' parent focusHub which is also nullptr.
     */
    EXPECT_TRUE(focusHub2->GetParentFocusHub() == nullptr);

    /**
     * @tc.steps: step4. Invoke GetParentFocusHub passing node as parameter which does not have parent.
     * @tc.expected: FocusHub will return node' parent focusHub which does not exist.
     */
    auto node = FrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_TRUE(focusHub2->GetParentFocusHub(&node) == nullptr);

    /**
     * @tc.steps: step5. Invoke GetParentFocusHub passing node as parameter which does not have parent.
     * @tc.expected: FocusHub will return node' parent focusHub which does not exist.
     */
    auto nodeParent = AceType::MakeRefPtr<FrameNode>(V2::BLANK_ETS_TAG, -1, AceType::MakeRefPtr<FlexLayoutPattern>());
    nodeParent->GetOrCreateFocusHub();
    node.SetParent(AceType::WeakClaim(AceType::RawPtr(nodeParent)));
    EXPECT_TRUE(focusHub2->GetParentFocusHub(&node) != nullptr);
}

/**
 * @tc.name: FocusHubCreateTest002
 * @tc.desc: Create FocusHub.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubCreateTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusHub with the WeakPtr eventHub_ owning frameNode.
     * @tc.expected: eventHub can be updated and can get frameNode and its related properties.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_TRUE(focusHub->GetFrameNode() != nullptr);
    EXPECT_TRUE(focusHub->GetGeometryNode() != nullptr);
    EXPECT_EQ(focusHub->GetFrameName(), V2::TEXT_ETS_TAG);
    EXPECT_EQ(focusHub->GetInspectorKey(), std::nullopt);

    /**
     * @tc.steps: step2. Invoke GetParentFocusHub without passing parameter.
     * @tc.expected: FocusHub will return frameNode' parent focusHub which is also nullptr.
     */
    EXPECT_TRUE(focusHub->GetParentFocusHub() == nullptr);

    /**
     * @tc.steps: step3. Create focusHub and its frameNode has parent node.
     * @tc.expected: FocusHub will return frameNode' parent focusHub.
     */
    auto nodeParent = AceType::MakeRefPtr<FrameNode>(V2::BLANK_ETS_TAG, -1, AceType::MakeRefPtr<FlexLayoutPattern>());
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(AceType::WeakClaim(AceType::RawPtr(nodeParent)));
    eventHub->AttachHost(frameNode);
    auto focusHub2 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_TRUE(focusHub2->GetParentFocusHub() != nullptr);
}

/**
 * @tc.name: FocusHubFlushChildrenFocusHubTest003
 * @tc.desc: Create FocusHub and invoke FlushChildrenFocusHub.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubFlushChildrenFocusHubTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and add button as its children which focus type is enable.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto child = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    auto child2 = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    child->GetOrCreateFocusHub();
    child2->GetOrCreateFocusHub();
    frameNode->AddChild(child);
    frameNode->AddChild(child2);

    /**
     * @tc.steps: step2. Create FocusHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps: step3. Invoke FlushChildrenFocusHub to get the focusable children.
     * @tc.expected: Button is the focusable child which will be emplace_back in focusNodes_.
     */
    focusHub->FlushChildrenFocusHub();
    EXPECT_EQ(focusHub->focusNodes_.size(), FOCUS_NODE_SIZE);
    EXPECT_EQ(focusHub->itLastFocusNode_, focusHub->focusNodes_.end());

    /**
     * @tc.steps: step4. lastWeakFocusNode_ is not nullptr.
     * @tc.expected: itLastFocusNode_ will be assigned the iter corresponding lastWeakFocusNode_ found in focusNodes_.
     */
    focusHub->lastWeakFocusNode_ = *(focusHub->focusNodes_.begin());
    focusHub->FlushChildrenFocusHub();
    EXPECT_EQ(focusHub->itLastFocusNode_, focusHub->focusNodes_.begin());
}

/**
 * @tc.name: FocusHubRemoveSelfTest004
 * @tc.desc: Create FocusHub and invoke RemoveSelf.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubRemoveSelfTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and add its parent.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto nodeParent = AceType::MakeRefPtr<FrameNode>(V2::BLANK_ETS_TAG, -1, AceType::MakeRefPtr<FlexLayoutPattern>());
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(AceType::WeakClaim(AceType::RawPtr(nodeParent)));

    /**
     * @tc.steps: step2. Create FocusHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps: step3. Remove self.
     * @tc.expected: The nodeParent children size is 0.
     */
    focusHub->RemoveSelf(AceType::RawPtr(frameNode));
    EXPECT_EQ(nodeParent->GetChildren().size(), NODE_SIZE);
}

/**
 * @tc.name: FocusHubLostFocusTest005
 * @tc.desc: Create FocusHub and invoke LostFocus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubLostFocusTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and add button as its children which focus type is enable.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create FocusHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps: step3. Invoke LostFocus, when FocusType is DISABLE and  the blur reason is FOCUS_SWITCH.
     * @tc.expected: currentFocus_ is false.
     */
    focusHub->currentFocus_ = true;
    focusHub->LostFocus(BLUR_REASON_FOCUS_SWITCH);
    EXPECT_EQ(focusHub->blurReason_, BLUR_REASON_FOCUS_SWITCH);
    EXPECT_FALSE(focusHub->currentFocus_);

    /**
     * @tc.steps: step4. Invoke LostFocus, when FocusType is NODE and  the blur reason is WINDOW_BLUR.
     * @tc.expected: currentFocus_ is false.
     */
    focusHub->currentFocus_ = true;
    focusHub->focusType_ = FocusType::NODE;
    focusHub->LostFocus(BLUR_REASON_WINDOW_BLUR);
    EXPECT_EQ(focusHub->blurReason_, BLUR_REASON_WINDOW_BLUR);
    EXPECT_FALSE(focusHub->currentFocus_);

    /**
     * @tc.steps: step5. Invoke LostFocus, when FocusType is SCOPE and  the blur reason is WINDOW_BLUR.
     * @tc.expected: currentFocus_ is false.
     */
    focusHub->currentFocus_ = true;
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->LostFocus(BLUR_REASON_WINDOW_BLUR);
    EXPECT_FALSE(focusHub->currentFocus_);
}

/**
 * @tc.name: FocusHubHandleKeyEventTest006
 * @tc.desc: Create FocusHub and invoke HandleKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubHandleKeyEventTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto child = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    auto child2 = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    child->GetOrCreateFocusHub();
    child2->GetOrCreateFocusHub();
    frameNode->AddChild(child);
    frameNode->AddChild(child2);

    /**
     * @tc.steps: step2. Create FocusHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps: step3. Focus hub does not currently focused and FocusType is DISABLE.
     * @tc.expected: Do not handle key event.
     */
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::TV_CONTROL_UP;
    EXPECT_FALSE(focusHub->HandleKeyEvent(keyEvent));

    /**
     * @tc.steps: step4. Focus hub is currently focused, FocusType is DISABLE and key code is TV_CONTROL_UP.
     * @tc.expected: OnKeyEventScope -> RequestNextFocus.
     */
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->currentFocus_ = true;
    EXPECT_FALSE(focusHub->HandleKeyEvent(keyEvent));
}
} // namespace OHOS::Ace::NG
