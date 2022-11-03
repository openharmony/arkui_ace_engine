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

 #include "core/components_ng/pattern/toast/toast_view.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string BOTTOM_HEIGHT = "200";
const std::string MESSAGE_INFO = "Message_Info";

} // namespace

class ToastPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void ToastPatternTestNg::SetUpTestCase() {}
void ToastPatternTestNg::TearDownTestCase() {}
void ToastPatternTestNg::SetUp() {}
void ToastPatternTestNg::TearDown() {}

/**
 * @tc.name: ToastFrameNodeCreator001
 * @tc.desc: Test ActionSheet toast with image icon (internal source)
 * @tc.type: FUNC
 * @tc.author: lijuan
 */
 HWTEST_F(ToastPatternTestNg, ToastFrameNodeCreator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ToastNode
     */
    auto toastNode = ToastView::CreateToastNode(MESSAGE_INFO, BOTTOM_HEIGHT, false);

    /**
     * @tc.steps: step2. check if position are initiated correctly
     */
    EXPECT_EQ(toastNode == nullptr, false);
}

}// namespace OHOS::Ace::NG