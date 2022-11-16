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

#include "frameworks/core/accessibility/js_inspector/inspect_picker_view.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectPickerViewTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: InspectPickerViewTest001
 * @tc.desc: InspectPickerView::InspectPickerView
 * @tc.type: FUNC
 */
HWTEST_F(InspectPickerViewTest, InspectPickerViewTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectPickerView inspectPickerView(nodeId, tag);
    EXPECT_EQ(inspectPickerView.nodeId_, nodeId);
    EXPECT_EQ(inspectPickerView.tag_, tag);
}

/**
 * @tc.name: InspectPickerViewTest002
 * @tc.desc: InspectPickerView::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectPickerViewTest, InspectPickerViewTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectPickerView inspectPickerView(nodeId, tag);
    auto attrsSize = inspectPickerView.attrs_.size();
    auto stylesSize = inspectPickerView.styles_.size();
    uint16_t attrsSizeInsert = 10;
    uint16_t stylesSizeInsert = 9;

    inspectPickerView.PackAttrAndStyle();
    EXPECT_EQ(inspectPickerView.attrs_.size(), attrsSize + attrsSizeInsert);
    EXPECT_EQ(inspectPickerView.attrs_["type"], "text");
    EXPECT_EQ(inspectPickerView.attrs_["disabled"], "false");
    EXPECT_EQ(inspectPickerView.attrs_["focusable"], "true");
    EXPECT_EQ(inspectPickerView.attrs_["selected"], "0");
    EXPECT_EQ(inspectPickerView.attrs_["start"], "1970-1-1");
    EXPECT_EQ(inspectPickerView.attrs_["end"], "2100-12-31");
    EXPECT_EQ(inspectPickerView.attrs_["lunar"], "false");
    EXPECT_EQ(inspectPickerView.attrs_["lunarswitch"], "false");
    EXPECT_EQ(inspectPickerView.attrs_["containsecond"], "false");
    EXPECT_EQ(inspectPickerView.attrs_["hours"], "24");
    EXPECT_EQ(inspectPickerView.styles_.size(), stylesSize + stylesSizeInsert);
    EXPECT_EQ(inspectPickerView.styles_["color"], "#808080");
    EXPECT_EQ(inspectPickerView.styles_["font-size"], "30px");
    EXPECT_EQ(inspectPickerView.styles_["selected-color"], "#ffffff");
    EXPECT_EQ(inspectPickerView.styles_["selected-font-size"], "38px");
    EXPECT_EQ(inspectPickerView.styles_["focus-color"], "#ffffff");
    EXPECT_EQ(inspectPickerView.styles_["focus-font-size"], "38px");
    EXPECT_EQ(inspectPickerView.styles_["disappear-color"], "#ffffff");
    EXPECT_EQ(inspectPickerView.styles_["disappear-font-size"], "14px");
    EXPECT_EQ(inspectPickerView.styles_["font-family"], "sans-serif");
}
} // namespace OHOS::Ace::Framework
