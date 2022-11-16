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

#include "frameworks/core/accessibility/js_inspector/inspect_progress.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectProgressTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectProgressTest001
 * @tc.desc: InspectProgress::InspectProgress
 * @tc.type: FUNC
 */
HWTEST_F(InspectProgressTest, InspectProgressTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectProgress inspectProgress(nodeId, tag);
    EXPECT_EQ(inspectProgress.nodeId_, nodeId);
    EXPECT_EQ(inspectProgress.tag_, tag);
}

/**
 * @tc.name: InspectProgressTest002
 * @tc.desc: InspectProgress::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectProgressTest, InspectProgressTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectProgress inspectProgress(nodeId, tag);
    auto attrsSize = inspectProgress.attrs_.size();
    auto stylesSize = inspectProgress.styles_.size();
    uint16_t attrsSizeInsert = 5;
    uint16_t stylesSizeInsert = 2;

    inspectProgress.PackAttrAndStyle();
    EXPECT_EQ(inspectProgress.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectProgress.attrs_["type"], "horizontal");
    EXPECT_EQ(inspectProgress.attrs_["focusable"], "true");
    EXPECT_EQ(inspectProgress.attrs_["percent"], "0");
    EXPECT_EQ(inspectProgress.attrs_["secondarypercent"], "0");
    EXPECT_EQ(inspectProgress.attrs_["clockwise"], "true");
    EXPECT_EQ(inspectProgress.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectProgress.styles_["color"], "#ff007dff");
    EXPECT_EQ(inspectProgress.styles_["stroke-width"], "4px");
    EXPECT_EQ(inspectProgress.styles_.find("background-size"), inspectProgress.styles_.end());
    EXPECT_EQ(inspectProgress.styles_.find("background-repeat"), inspectProgress.styles_.end());
    EXPECT_EQ(inspectProgress.styles_.find("background-position"), inspectProgress.styles_.end());
}
} // namespace OHOS::Ace::Framework
