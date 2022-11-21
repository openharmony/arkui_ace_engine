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

#include "frameworks/core/accessibility/js_inspector/inspect_div.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectDivTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectDivTest001
 * @tc.desc: InspectDiv::InspectDiv
 * @tc.type: FUNC
 */
HWTEST_F(InspectDivTest, InspectDivTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDiv inspectDiv(nodeId, tag);
    EXPECT_EQ(inspectDiv.nodeId_, nodeId);
    EXPECT_EQ(inspectDiv.tag_, tag);
}

/**
 * @tc.name: InspectDivTest002
 * @tc.desc: InspectDiv::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectDivTest, InspectDivTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDiv inspectDiv(nodeId, tag);
    auto attrsSize = inspectDiv.attrs_.size();
    auto stylesSize = inspectDiv.styles_.size();
    uint16_t attrsSizeInsert = 2;
    uint16_t stylesSizeInsert = 10;

    inspectDiv.PackAttrAndStyle();
    EXPECT_EQ(inspectDiv.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectDiv.attrs_["disabled"], "false");
    EXPECT_EQ(inspectDiv.attrs_["focusable"], "true");
    EXPECT_EQ(inspectDiv.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectDiv.styles_["flex-direction"], "row");
    EXPECT_EQ(inspectDiv.styles_["flex-wrap"], "nowrap");
    EXPECT_EQ(inspectDiv.styles_["justify-content"], "flex-start");
    EXPECT_EQ(inspectDiv.styles_["align-items"], "stretch");
    EXPECT_EQ(inspectDiv.styles_["align-content"], "flex-start");
    EXPECT_EQ(inspectDiv.styles_["display"], "flex");
    EXPECT_EQ(inspectDiv.styles_["grid-template-columns"], "1");
    EXPECT_EQ(inspectDiv.styles_["grid-template-rows"], "1");
    EXPECT_EQ(inspectDiv.styles_["grid-columns-gap"], "0");
    EXPECT_EQ(inspectDiv.styles_["grid-rows-gap"], "0");
}
} // namespace OHOS::Ace::Framework
