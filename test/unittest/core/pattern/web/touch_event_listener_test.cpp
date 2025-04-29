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

#include "gtest/gtest.h"

#include "core/components_ng/base/view_stack_processor.h"
#define private public
#include "core/components_ng/pattern/web/touch_event_listener.h"
#undef private
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;

namespace OHOS::Ace::NG {

class TouchEventListenerTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void TouchEventListenerTest::SetUpTestCase() {}
void TouchEventListenerTest::TearDownTestCase() {}
void TouchEventListenerTest::SetUp() {}
void TouchEventListenerTest::TearDown() {}

/**
 * @tc.name: TouchEventListenerTest_001
 * @tc.desc: Test function GetPatternFromListener.
 * @tc.type: FUNC
 */
HWTEST_F(TouchEventListenerTest, GetPatternFromListener_001, TestSize.Level1)
{
    TouchEventListener touchEventListener;
    WeakPtr<NG::Pattern> patternSet;
    touchEventListener.SetPatternToListener(patternSet);
    auto patternGet = touchEventListener.GetPatternFromListener();
    EXPECT_EQ(patternSet, patternGet);
}

/**
 * @tc.name: TouchEventListenerTest_002
 * @tc.desc: Test function OnTouchEvent in abnormal condition.
 * @tc.type: FUNC
 */
HWTEST_F(TouchEventListenerTest, OnTouchEvent_001, TestSize.Level1)
{
    TouchEventListener touchEventListener;
    WeakPtr<NG::Pattern> patternSet;
    touchEventListener.SetPatternToListener(patternSet);
    touchEventListener.OnTouchEvent();
    EXPECT_EQ(touchEventListener.pattern_.Upgrade(), nullptr);
}

/**
 * @tc.name: TouchEventListenerTest_003
 * @tc.desc: Test function OnTouchEvent in normal condition.
 * @tc.type: FUNC
 */
HWTEST_F(TouchEventListenerTest, OnTouchEvent_002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    TouchEventListener touchEventListener;
    touchEventListener.SetPatternToListener(webPattern);
    touchEventListener.OnTouchEvent();
}

} // namespace OHOS::Ace::NG
