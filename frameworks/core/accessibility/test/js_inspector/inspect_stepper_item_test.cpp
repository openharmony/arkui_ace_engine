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

#include "frameworks/core/accessibility/js_inspector/inspect_stepper_item.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectStepperItemTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectStepperItemTest001
 * @tc.desc: InspectStepperItem::InspectStepperItem
 * @tc.type: FUNC
 */
HWTEST_F(InspectStepperItemTest, InspectStepperItemTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectStepperItem inspectStepperItem(nodeId, tag);
    EXPECT_EQ(inspectStepperItem.nodeId_, nodeId);
    EXPECT_EQ(inspectStepperItem.tag_, tag);
}

/**
 * @tc.name: InspectStepperItemTest002
 * @tc.desc: InspectStepperItem::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectStepperItemTest, InspectStepperItemTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectStepperItem inspectStepperItem(nodeId, tag);
    auto attrsSize = inspectStepperItem.attrs_.size();
    auto stylesSize = inspectStepperItem.styles_.size();
    uint16_t attrsSizeInsert = 1;
    uint16_t stylesSizeInsert = 7;

    inspectStepperItem.PackAttrAndStyle();
    EXPECT_EQ(inspectStepperItem.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectStepperItem.attrs_["disabled"], "false");
    EXPECT_EQ(inspectStepperItem.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectStepperItem.styles_["color"], "#e600000");
    EXPECT_EQ(inspectStepperItem.styles_["font-size"], "16px");
    EXPECT_EQ(inspectStepperItem.styles_["allow-scale"], "true");
    EXPECT_EQ(inspectStepperItem.styles_["font-style"], "normal");
    EXPECT_EQ(inspectStepperItem.styles_["font-weight"], "normal");
    EXPECT_EQ(inspectStepperItem.styles_["text-decoration"], "none");
    EXPECT_EQ(inspectStepperItem.styles_["font-family"], "sans-serif");
    EXPECT_EQ(inspectStepperItem.styles_.find("flex-grow"), inspectStepperItem.styles_.end());
    EXPECT_EQ(inspectStepperItem.styles_.find("flex-shrink"), inspectStepperItem.styles_.end());
    EXPECT_EQ(inspectStepperItem.styles_.find("position"), inspectStepperItem.styles_.end());
}
} // namespace OHOS::Ace::Framework
