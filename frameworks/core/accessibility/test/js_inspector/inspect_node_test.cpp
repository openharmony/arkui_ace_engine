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

#include "frameworks/core/accessibility/js_inspector/inspect_node.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
namespace {
constexpr char INSPECTOR_ATTRS[] = "$attrs";
constexpr char INSPECTOR_STYLES[] = "$styles";
}
class InspectNodeTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectNodeTest001
 * @tc.desc: InspectNode::InspectNode
 * @tc.type: FUNC
 */
HWTEST_F(InspectNodeTest, InspectNodeTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectNode inspectNode(nodeId, tag);
    EXPECT_EQ(inspectNode.nodeId_, nodeId);
    EXPECT_EQ(inspectNode.tag_, tag);
}

/**
 * @tc.name: InspectNodeTest002
 * @tc.desc: InspectNode::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectNodeTest, InspectNodeTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectNode inspectNode(nodeId, tag);
    auto attrsSize = inspectNode.attrs_.size();
    auto stylesSize = inspectNode.styles_.size();
    inspectNode.PackAttrAndStyle();
    EXPECT_EQ(inspectNode.attrs_.size(), attrsSize);
    EXPECT_EQ(inspectNode.styles_.size(), stylesSize);
}

/**
 * @tc.name: InspectNodeTest003
 * @tc.desc: InspectNode::InitCommonStyles
 * @tc.type: FUNC
 */
HWTEST_F(InspectNodeTest, InspectNodeTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectNode inspectNode(nodeId, tag);
    auto stylesSize = inspectNode.styles_.size();
    uint16_t stylesSizeInsert = 34;

    inspectNode.InitCommonStyles();
    EXPECT_EQ(inspectNode.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectNode.styles_["padding-left"], "0");
    EXPECT_EQ(inspectNode.styles_["padding-top"], "0");
    EXPECT_EQ(inspectNode.styles_["padding-right"], "0");
    EXPECT_EQ(inspectNode.styles_["padding-bottom"], "0");
    EXPECT_EQ(inspectNode.styles_["padding-start"], "0");
    EXPECT_EQ(inspectNode.styles_["padding-end"], "0");
    EXPECT_EQ(inspectNode.styles_["margin-left"], "0");
    EXPECT_EQ(inspectNode.styles_["margin-top"], "0");
    EXPECT_EQ(inspectNode.styles_["margin-right"], "0");
    EXPECT_EQ(inspectNode.styles_["margin-bottom"], "0");
    EXPECT_EQ(inspectNode.styles_["margin-start"], "0");
    EXPECT_EQ(inspectNode.styles_["margin-end"], "0");
    EXPECT_EQ(inspectNode.styles_["border"], "0");
    EXPECT_EQ(inspectNode.styles_["border-left-style"], "solid");
    EXPECT_EQ(inspectNode.styles_["border-top-style"], "solid");
    EXPECT_EQ(inspectNode.styles_["border-right-style"], "solid");
    EXPECT_EQ(inspectNode.styles_["border-bottom-style"], "solid");
    EXPECT_EQ(inspectNode.styles_["border-left-width"], "0");
    EXPECT_EQ(inspectNode.styles_["border-top-width"], "0");
    EXPECT_EQ(inspectNode.styles_["border-right-width"], "0");
    EXPECT_EQ(inspectNode.styles_["border-bottom-width"], "0");
    EXPECT_EQ(inspectNode.styles_["border-left-color"], "black");
    EXPECT_EQ(inspectNode.styles_["border-top-color"], "black");
    EXPECT_EQ(inspectNode.styles_["border-right-color"], "black");
    EXPECT_EQ(inspectNode.styles_["border-bottom-color"], "black");
    EXPECT_EQ(inspectNode.styles_["background-size"], "auto");
    EXPECT_EQ(inspectNode.styles_["background-repeat"], "repeat");
    EXPECT_EQ(inspectNode.styles_["background-position"], "0px 0px");
    EXPECT_EQ(inspectNode.styles_["opacity"], "1");
    EXPECT_EQ(inspectNode.styles_["display"], "flex");
    EXPECT_EQ(inspectNode.styles_["visibility"], "visible");
    EXPECT_EQ(inspectNode.styles_["flex-grow"], "0");
    EXPECT_EQ(inspectNode.styles_["flex-shrink"], "1");
    EXPECT_EQ(inspectNode.styles_["position"], "relative");
}

/**
 * @tc.name: InspectNodeTest004
 * @tc.desc: InspectNode::SetAllAttr
 * @tc.type: FUNC
 */
HWTEST_F(InspectNodeTest, InspectNodeTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectNode inspectNode(nodeId, tag);
    inspectNode.attrs_.insert(std::make_pair("disabled", "false"));
    auto rootJsonValue = JsonUtil::Create(true);
    auto attrsJsonValue = JsonUtil::Create(true);
    attrsJsonValue->Put("disabled", "false");
    inspectNode.SetAllAttr(rootJsonValue, INSPECTOR_ATTRS);
    EXPECT_EQ(rootJsonValue->GetObject(INSPECTOR_ATTRS)->ToString(), attrsJsonValue->ToString());
}

/**
 * @tc.name: InspectNodeTest005
 * @tc.desc: InspectNode::SetAllStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectNodeTest, InspectNodeTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectNode inspectNode(nodeId, tag);
    inspectNode.styles_.insert(std::make_pair("position", "relative"));
    auto rootJsonValue = JsonUtil::Create(true);
    auto stylesJsonValue = JsonUtil::Create(true);
    stylesJsonValue->Put("position", "relative");
    inspectNode.SetAllStyle(rootJsonValue, INSPECTOR_STYLES);
    EXPECT_EQ(rootJsonValue->GetObject(INSPECTOR_STYLES)->ToString(), stylesJsonValue->ToString());
}
} // namespace OHOS::Ace::Framework
