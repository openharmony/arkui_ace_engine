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

#define protected public
#define private public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/view_context/view_context_model_ng.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class ViewContextTestNG : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void ViewContextTestNG::SetUpTestCase()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

void ViewContextTestNG::TearDownTestCase()
{
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: closeAnimation001
 * @tc.desc: Test function closeAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextTestNG, closeAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create viewContext.
     */
    ViewContextModelNG viewContext;
    RefPtr<FrameNode> node = FrameNode::CreateCommonNode("node", 1, true, AceType::MakeRefPtr<Pattern>());
    auto funcVoid = []() -> void {};
    auto funcFloat = [](const float) -> void {};
    auto onWillDismiss = [](int32_t info) -> void {};
    NG::SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = false;

    /**
     * @tc.steps: step2. call the function closeAnimation.
     */
    int32_t ret = viewContext.OpenBindSheet(node, funcVoid, sheetStyle, funcVoid, funcVoid, funcVoid, onWillDismiss,
        funcVoid, funcVoid, funcFloat, funcFloat, funcFloat, funcFloat, funcVoid, 1, 1);
    EXPECT_EQ(ret, 0);
    AnimationOption option = AnimationOption();
    option.SetDuration(10); // 10 is ths duration of animation.
    viewContext.closeAnimation(option, true);
    EXPECT_EQ(NG::ViewStackProcessor::GetInstance()->GetImplicitAnimationOption().GetDuration(), 10);
}

/**
 * @tc.name: closeAnimation002
 * @tc.desc: Test function closeAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextTestNG, closeAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create viewContext.
     */
    ViewContextModelNG viewContext;
    RefPtr<FrameNode> node = FrameNode::CreateCommonNode("node", 1, true, AceType::MakeRefPtr<Pattern>());
    NG::SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = false;

    /**
     * @tc.steps: step2. call the function closeAnimation.
     */
    int32_t ret = viewContext.UpdateBindSheet(node, sheetStyle, true, 1);
    EXPECT_EQ(ret, 0);
    AnimationOption option = AnimationOption();
    option.SetDuration(10); // 10 is ths duration of animation.
    viewContext.closeAnimation(option, false);
    EXPECT_EQ(NG::ViewStackProcessor::GetInstance()->GetImplicitAnimationOption().GetDuration(), 10);
}

/**
 * @tc.name: openAnimation001
 * @tc.desc: Test function openAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ViewContextTestNG, openAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create viewContext.
     */
    ViewContextModelNG viewContext;
    RefPtr<FrameNode> node = FrameNode::CreateCommonNode("node", 1, true, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. call the function closeAnimation.
     */
    int32_t ret = viewContext.CloseBindSheet(node, 1);
    EXPECT_EQ(ret, 0);
    AnimationOption option = AnimationOption();
    option.SetDuration(10); // 10 is ths duration of animation.
    viewContext.openAnimation(option);
    EXPECT_EQ(NG::ViewStackProcessor::GetInstance()->GetImplicitAnimationOption().GetDuration(), 10);
}
} // namespace OHOS::Ace::NG
