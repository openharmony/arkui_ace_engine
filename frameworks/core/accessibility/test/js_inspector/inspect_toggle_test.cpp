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

#include "frameworks/core/accessibility/js_inspector/inspect_toggle.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectToggleTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectToggleTest001
 * @tc.desc: InspectToggle::InspectToggle
 * @tc.type: FUNC
 */
HWTEST_F(InspectToggleTest, InspectToggleTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectToggle inspectToggle(nodeId, tag);
    EXPECT_EQ(inspectToggle.nodeId_, nodeId);
    EXPECT_EQ(inspectToggle.tag_, tag);
}

/**
 * @tc.name: InspectToggleTest002
 * @tc.desc: InspectToggle::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectToggleTest, InspectToggleTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectToggle inspectToggle(nodeId, tag);
    auto attrsSize = inspectToggle.attrs_.size();
    auto stylesSize = inspectToggle.styles_.size();
    uint16_t attrsSizeInsert = 3;
    uint16_t stylesSizeInsert = 6;

    inspectToggle.PackAttrAndStyle();
    EXPECT_EQ(inspectToggle.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectToggle.attrs_["checked"], "false");
    EXPECT_EQ(inspectToggle.attrs_["disabled"], "false");
    EXPECT_EQ(inspectToggle.attrs_["focusable"], "false");
    EXPECT_EQ(inspectToggle.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectToggle.styles_["color"], "#ff007dff");
    EXPECT_EQ(inspectToggle.styles_["font-size"], "16px");
    EXPECT_EQ(inspectToggle.styles_["allow-scale"], "true");
    EXPECT_EQ(inspectToggle.styles_["font-style"], "normal");
    EXPECT_EQ(inspectToggle.styles_["font-weight"], "normal");
    EXPECT_EQ(inspectToggle.styles_["font-family"], "sans-serif");
    EXPECT_EQ(inspectToggle.styles_.find("border"), inspectToggle.styles_.end());
    EXPECT_EQ(inspectToggle.styles_.find("border-left-style"), inspectToggle.styles_.end());
    EXPECT_EQ(inspectToggle.styles_.find("border-top-style"), inspectToggle.styles_.end());
    EXPECT_EQ(inspectToggle.styles_.find("border-right-style"), inspectToggle.styles_.end());
    EXPECT_EQ(inspectToggle.styles_.find("border-bottom-style"), inspectToggle.styles_.end());
    EXPECT_EQ(inspectToggle.styles_.find("border-left-width"), inspectToggle.styles_.end());
    EXPECT_EQ(inspectToggle.styles_.find("border-top-width"), inspectToggle.styles_.end());
    EXPECT_EQ(inspectToggle.styles_.find("border-right-width"), inspectToggle.styles_.end());
    EXPECT_EQ(inspectToggle.styles_.find("border-bottom-width"), inspectToggle.styles_.end());
    EXPECT_EQ(inspectToggle.styles_.find("border-left-color"), inspectToggle.styles_.end());
    EXPECT_EQ(inspectToggle.styles_.find("border-top-color"), inspectToggle.styles_.end());
    EXPECT_EQ(inspectToggle.styles_.find("border-right-color"), inspectToggle.styles_.end());
    EXPECT_EQ(inspectToggle.styles_.find("border-bottom-color"), inspectToggle.styles_.end());
}
} // namespace OHOS::Ace::Framework
