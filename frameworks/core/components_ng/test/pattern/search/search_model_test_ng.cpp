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

#include "gtest/gtest.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/search/search_model_ng.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t BUTTON_INDEX = 4;
}
  
class SearchModelTestNG : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void SearchModelTestNG::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void SearchModelTestNG::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

void SearchModelTestNG::SetUp() {}

void SearchModelTestNG::TearDown()
{
    ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

/**
 * @tc.name: Pattern001
 * @tc.desc: HandleMouseEvent while mouse not in button
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, Pattern001, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    pattern->isHover_ = true;
    MouseInfo info;
    const Offset offset1(-1000000.0, -1000000.0);
    info.SetLocalLocation(offset1);
    EXPECT_NE(pattern, nullptr);
    pattern->HandleMouseEvent(info);
}

/**
 * @tc.name: Pattern002
 * @tc.desc: InitTouchEvent TouchType = DOWN
 * @tc.type: FUNC
 */
HWTEST_F(SearchModelTestNG, Pattern002, TestSize.Level1)
{
    SearchModelNG searchModelInstance;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SearchPattern>();
    EXPECT_NE(pattern, nullptr);

    TouchTestResult result;
    pattern->InitTouchEvent();
    EXPECT_FALSE(pattern->touchListener_ == nullptr);
    pattern->InitTouchEvent();
    const Offset offset1(-1000000.0, -1000000.0);
    TouchEventInfo info("onTouch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::DOWN);
    touchInfo1.SetLocalLocation(offset1);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    pattern->touchListener_->GetTouchEventCallback()(info);
}
} // namespace OHOS::Ace::NG

