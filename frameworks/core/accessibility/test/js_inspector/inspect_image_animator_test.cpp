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

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public

#include "frameworks/core/accessibility/js_inspector/inspect_image_animator.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectImageAnimatorTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectImageAnimatorTest001
 * @tc.desc: InspectImageAnimator::InspectImageAnimator
 * @tc.type: FUNC
 */
HWTEST_F(InspectImageAnimatorTest, InspectImageAnimatorTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectImageAnimator inspectImageAnimator(nodeId, tag);
    EXPECT_EQ(inspectImageAnimator.nodeId_, nodeId);
    EXPECT_EQ(inspectImageAnimator.tag_, tag);
}

/**
 * @tc.name: InspectImageAnimatorTest002
 * @tc.desc: InspectImageAnimator::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectImageAnimatorTest, InspectImageAnimatorTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectImageAnimator inspectImageAnimator(nodeId, tag);
    auto attrsSize = inspectImageAnimator.attrs_.size();
    uint16_t attrsSizeInsert = 7;

    inspectImageAnimator.PackAttrAndStyle();
    EXPECT_EQ(inspectImageAnimator.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectImageAnimator.attrs_["predecode"], "0");
    EXPECT_EQ(inspectImageAnimator.attrs_["iteration"], "infinite");
    EXPECT_EQ(inspectImageAnimator.attrs_["reverse"], "false");
    EXPECT_EQ(inspectImageAnimator.attrs_["fixedsize"], "true");
    EXPECT_EQ(inspectImageAnimator.attrs_["fillmode"], "forwards");
    EXPECT_EQ(inspectImageAnimator.attrs_["disabled"], "false");
    EXPECT_EQ(inspectImageAnimator.attrs_["focusable"], "false");
}
} // namespace OHOS::Ace::Framework
