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

#include "frameworks/core/accessibility/js_inspector/inspect_picker.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectPickerTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectPickerTest001
 * @tc.desc: InspectPicker::InspectPicker
 * @tc.type: FUNC
 */
HWTEST_F(InspectPickerTest, InspectPickerTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectPicker inspectPicker(nodeId, tag);
    EXPECT_EQ(inspectPicker.nodeId_, nodeId);
    EXPECT_EQ(inspectPicker.tag_, tag);
}

/**
 * @tc.name: InspectPickerTest002
 * @tc.desc: InspectPicker::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectPickerTest, InspectPickerTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectPicker inspectPicker(nodeId, tag);
    auto attrsSize = inspectPicker.attrs_.size();
    auto stylesSize = inspectPicker.styles_.size();
    uint16_t attrsSizeInsert = 10;
    uint16_t stylesSizeInsert = 8;

    inspectPicker.PackAttrAndStyle();
    EXPECT_EQ(inspectPicker.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectPicker.attrs_["disabled"], "false");
    EXPECT_EQ(inspectPicker.attrs_["focusable"], "true");
    EXPECT_EQ(inspectPicker.attrs_["vibrate"], "true");
    EXPECT_EQ(inspectPicker.attrs_["selected"], "0");
    EXPECT_EQ(inspectPicker.attrs_["start"], "1970-1-1");
    EXPECT_EQ(inspectPicker.attrs_["end"], "2100-12-31");
    EXPECT_EQ(inspectPicker.attrs_["lunar"], "false");
    EXPECT_EQ(inspectPicker.attrs_["lunarswitch"], "false");
    EXPECT_EQ(inspectPicker.attrs_["containsecond"], "false");
    EXPECT_EQ(inspectPicker.attrs_["hours"], "24");
    EXPECT_EQ(inspectPicker.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectPicker.styles_["text-color"], "#e6000000");
    EXPECT_EQ(inspectPicker.styles_["font-size"], "30px");
    EXPECT_EQ(inspectPicker.styles_["allow-scale"], "true");
    EXPECT_EQ(inspectPicker.styles_["letter-spacing"], "0");
    EXPECT_EQ(inspectPicker.styles_["font-style"], "normal");
    EXPECT_EQ(inspectPicker.styles_["font-weight"], "normal");
    EXPECT_EQ(inspectPicker.styles_["font-family"], "sans-serif");
    EXPECT_EQ(inspectPicker.styles_["line-height"], "0px");
}
} // namespace OHOS::Ace::Framework
