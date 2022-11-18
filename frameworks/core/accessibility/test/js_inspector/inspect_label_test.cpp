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

#include "frameworks/core/accessibility/js_inspector/inspect_label.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectLabelTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectLabelTest001
 * @tc.desc: InspectLabel::InspectLabel
 * @tc.type: FUNC
 */
HWTEST_F(InspectLabelTest, InspectLabelTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectLabel inspectLabel(nodeId, tag);
    EXPECT_EQ(inspectLabel.nodeId_, nodeId);
    EXPECT_EQ(inspectLabel.tag_, tag);
}

/**
 * @tc.name: InspectLabelTest002
 * @tc.desc: InspectLabel::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectLabelTest, InspectLabelTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectLabel inspectLabel(nodeId, tag);
    auto attrsSize = inspectLabel.attrs_.size();
    auto stylesSize = inspectLabel.styles_.size();
    uint16_t attrsSizeInsert = 2;
    uint16_t stylesSizeInsert = 12;

    inspectLabel.PackAttrAndStyle();
    EXPECT_EQ(inspectLabel.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectLabel.attrs_["disabled"], "false");
    EXPECT_EQ(inspectLabel.attrs_["focusable"], "false");
    EXPECT_EQ(inspectLabel.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectLabel.styles_["color"], "#e5000000");
    EXPECT_EQ(inspectLabel.styles_["font-size"], "30px");
    EXPECT_EQ(inspectLabel.styles_["allow-scale"], "true");
    EXPECT_EQ(inspectLabel.styles_["letter-spacing"], "0px");
    EXPECT_EQ(inspectLabel.styles_["font-style"], "normal");
    EXPECT_EQ(inspectLabel.styles_["font-weight"], "normal");
    EXPECT_EQ(inspectLabel.styles_["text-decoration"], "none");
    EXPECT_EQ(inspectLabel.styles_["text-align"], "start");
    EXPECT_EQ(inspectLabel.styles_["line-height"], "0px");
    EXPECT_EQ(inspectLabel.styles_["text-overflow"], "clip");
    EXPECT_EQ(inspectLabel.styles_["font-family"], "sans-serif");
    EXPECT_EQ(inspectLabel.styles_["font-size-step"], "1px");
}
} // namespace OHOS::Ace::Framework