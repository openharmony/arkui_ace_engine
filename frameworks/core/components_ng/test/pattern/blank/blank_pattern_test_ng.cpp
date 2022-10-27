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

#include <optional>
#include "gtest/gtest.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/blank/blank_layout_property.h"
#include "core/components_ng/pattern/blank/blank_pattern.h"
#include "core/components_ng/pattern/blank/blank_view.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {

} // namespace

class BlankPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
protected:
};

/**
 * @tc.name: BlankFrameNodeCreator001
 * @tc.desc: Test all the properties of Blank.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BlankPatternTestNg, BlankFrameNodeCreator001, TestSize.Level1)
{
    BlankView blank;
    Dimension blankMin;
    blank.Create();
    blankMin.SetValue(10);
    blank.SetBlankMin(blankMin);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto blankLayoutProperty = frameNode->GetLayoutProperty<BlankLayoutProperty>();
    EXPECT_FALSE(blankLayoutProperty == nullptr);
}

/**
 * @tc.name: BlankFrameNodeCreator002
 * @tc.desc: Test all the properties of Blank.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(BlankPatternTestNg, BlankFrameNodeCreator002, TestSize.Level1)
{
    BlankView blank;
    Dimension blankMin;
    blank.Create();
    blankMin.SetValue(10);
    blank.SetBlankMin(blankMin);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto blankLayoutProperty = frameNode->GetLayoutProperty<BlankLayoutProperty>();
    EXPECT_FALSE(blankLayoutProperty == nullptr);

    auto blankPattern = frameNode->GetPattern<BlankPattern>();
    EXPECT_FALSE(blankPattern == nullptr);
    auto layoutProperty = blankPattern->CreateLayoutProperty();
    EXPECT_FALSE(layoutProperty == nullptr);
    auto paintProperty = blankPattern->CreatePaintProperty();
    EXPECT_FALSE(paintProperty == nullptr);

    blankPattern->OnMountToParentDone();
}
} // namespace OHOS::Ace::NG
