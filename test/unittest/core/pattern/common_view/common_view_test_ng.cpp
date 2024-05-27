/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/common_view/common_view_model_ng.h"
#include "core/components_ng/pattern/common_view/common_view_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace

class CommonViewTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: CommonViewTest001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonViewTestNg, CommonViewTest001, TestSize.Level1)
{
    CommonViewModelNG view;
    view.Create(false);
    auto blankNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(blankNode == nullptr);
    EXPECT_EQ(blankNode->GetTag(), V2::COMMON_VIEW_ETS_TAG);
    EXPECT_EQ(blankNode->IsAtomicNode(), false);
}

} // namespace OHOS::Ace::NG