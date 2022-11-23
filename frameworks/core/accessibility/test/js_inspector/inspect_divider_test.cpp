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

#include "frameworks/core/accessibility/js_inspector/inspect_divider.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectDividerTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectDividerTest001
 * @tc.desc: InspectDivider::InspectDivider
 * @tc.type: FUNC
 */
HWTEST_F(InspectDividerTest, InspectDividerTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDivider inspectDivider(nodeId, tag);
    EXPECT_EQ(inspectDivider.nodeId_, nodeId);
    EXPECT_EQ(inspectDivider.tag_, tag);
}

/**
 * @tc.name: InspectDividerTest002
 * @tc.desc: InspectDivider::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectDividerTest, InspectDividerTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDivider inspectDivider(nodeId, tag);
    auto attrsSize = inspectDivider.attrs_.size();
    auto stylesSize = inspectDivider.styles_.size();
    uint16_t attrsSizeInsert = 1;
    uint16_t stylesSizeInsert = 11;

    inspectDivider.PackAttrAndStyle();
    EXPECT_EQ(inspectDivider.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectDivider.attrs_["vertical"], "false");
    EXPECT_EQ(inspectDivider.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectDivider.styles_["color"], "#08000000");
    EXPECT_EQ(inspectDivider.styles_["stroke-width"], "1");
    EXPECT_EQ(inspectDivider.styles_["line-cap"], "butt");
    EXPECT_EQ(inspectDivider.styles_["margin-left"], "0");
    EXPECT_EQ(inspectDivider.styles_["margin-top"], "0");
    EXPECT_EQ(inspectDivider.styles_["margin-right"], "0");
    EXPECT_EQ(inspectDivider.styles_["margin-bottom"], "0");
    EXPECT_EQ(inspectDivider.styles_["display"], "flex");
    EXPECT_EQ(inspectDivider.styles_["visibility"], "visible");
    EXPECT_EQ(inspectDivider.styles_["flex-grow"], "0");
    EXPECT_EQ(inspectDivider.styles_["flex-shrink"], "1");
}
} // namespace OHOS::Ace::Framework
