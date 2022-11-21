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

#include "frameworks/core/accessibility/js_inspector/inspect_switch.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectSwitchTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectSwitchTest001
 * @tc.desc: InspectSwitch::InspectSwitch
 * @tc.type: FUNC
 */
HWTEST_F(InspectSwitchTest, InspectSwitchTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSwitch inspectSwitch(nodeId, tag);
    EXPECT_EQ(inspectSwitch.nodeId_, nodeId);
    EXPECT_EQ(inspectSwitch.tag_, tag);
}

/**
 * @tc.name: InspectSwitchTest002
 * @tc.desc: InspectSwitch::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectSwitchTest, InspectSwitchTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSwitch inspectSwitch(nodeId, tag);
    auto attrsSize = inspectSwitch.attrs_.size();
    auto stylesSize = inspectSwitch.styles_.size();
    uint16_t attrsSizeInsert = 6;
    uint16_t stylesSizeInsert = 7;

    inspectSwitch.PackAttrAndStyle();
    EXPECT_EQ(inspectSwitch.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectSwitch.attrs_["checked"], "false");
    EXPECT_EQ(inspectSwitch.attrs_["showtext"], "false");
    EXPECT_EQ(inspectSwitch.attrs_["texton"], "On");
    EXPECT_EQ(inspectSwitch.attrs_["textoff"], "Off");
    EXPECT_EQ(inspectSwitch.attrs_["disabled"], "false");
    EXPECT_EQ(inspectSwitch.attrs_["focusable"], "true");
    EXPECT_EQ(inspectSwitch.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectSwitch.styles_["texton-color"], "#000000");
    EXPECT_EQ(inspectSwitch.styles_["textoff-color"], "#000000");
    EXPECT_EQ(inspectSwitch.styles_["text-padding"], "0px");
    EXPECT_EQ(inspectSwitch.styles_["allow-scale"], "true");
    EXPECT_EQ(inspectSwitch.styles_["font-style"], "normal");
    EXPECT_EQ(inspectSwitch.styles_["font-weight"], "normal");
    EXPECT_EQ(inspectSwitch.styles_["font-family"], "sans-serif");
}
} // namespace OHOS::Ace::Framework
