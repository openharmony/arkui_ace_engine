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

#include "frameworks/core/accessibility/js_inspector/inspect_button.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectButtonTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectButtonTest001
 * @tc.desc: InspectButton::InspectButton
 * @tc.type: FUNC
 */
HWTEST_F(InspectButtonTest, InspectButtonTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectButton inspectButton(nodeId, tag);
    EXPECT_EQ(inspectButton.nodeId_, nodeId);
    EXPECT_EQ(inspectButton.tag_, tag);
}

/**
 * @tc.name: InspectButtonTest002
 * @tc.desc: InspectButton::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectButtonTest, InspectButtonTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectButton inspectButton(nodeId, tag);
    auto attrsSize = inspectButton.attrs_.size();
    auto stylesSize = inspectButton.styles_.size();
    uint16_t attrsSizeInsert = 4;
    uint16_t stylesSizeInsert = 6;

    inspectButton.PackAttrAndStyle();
    EXPECT_EQ(inspectButton.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectButton.attrs_["placement"], "end");
    EXPECT_EQ(inspectButton.attrs_["waiting"], "false");
    EXPECT_EQ(inspectButton.attrs_["disabled"], "false");
    EXPECT_EQ(inspectButton.attrs_["focusable"], "true");
    EXPECT_EQ(inspectButton.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectButton.styles_["text-color"], "#ff007dff");
    EXPECT_EQ(inspectButton.styles_["font-size"], "16px");
    EXPECT_EQ(inspectButton.styles_["allow-scale"], "true");
    EXPECT_EQ(inspectButton.styles_["font-style"], "normal");
    EXPECT_EQ(inspectButton.styles_["font-weight"], "normal");
    EXPECT_EQ(inspectButton.styles_["font-family"], "sans-serif");
}
} // namespace OHOS::Ace::Framework