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

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public
#include "core/components_ng/pattern/richtext/richtext_model_ng.h"
#include "core/components_ng/pattern/web/web_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string DATA = "richText";
} // namespace

class RichtextPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void RichtextPatternTestNg::SetUpTestCase() {}
void RichtextPatternTestNg::TearDownTestCase() {}
void RichtextPatternTestNg::SetUp() {}
void RichtextPatternTestNg::TearDown() {}

/**
 * @tc.name: RichtextModelNGTest001
 * @tc.desc: Test Richtext Create And Get Data
 * @tc.type: FUNC
 */
HWTEST_F(RichtextPatternTestNg, RichtextModelNGTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Richtext and get frameNode.
     */
    RichTextModelNG RichTextModelNG;
    RichTextModelNG.Create(DATA);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. get WebPattern
     */
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    /**
     * @tc.steps: step3. get webdata and compare with set data.
     */
    auto WebData = webPattern->GetWebData();
    EXPECT_EQ(WebData, DATA);
}

/**
 * @tc.name: RichtextModelNGTest002
 * @tc.desc: create richtext node
 * @tc.type: FUNC
 */
HWTEST_F(RichtextPatternTestNg, RichtextModelNGTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init RichtextModelNG object
     */
    RichTextModelNG RichTextModelNG;
    RichTextModelNG.Create(DATA);

    /**
     * @tc.steps: step2. Set call methods
     * @tc.expected: step2. Check the RichtextModelNG pattern value
     */
    auto onPageStart = [](const BaseEventInfo* info) {};
    RichTextModelNG.SetOnPageStart(std::move(onPageStart));
    auto frameNodeonPageStart = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNodeonPageStart, nullptr);

    auto onPageFinish = [](const BaseEventInfo* info) {};
    RichTextModelNG.SetOnPageFinish(std::move(onPageFinish));
    auto frameNodeonPageFinish = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNodeonPageFinish, nullptr);
}
} // namespace OHOS::Ace::NG