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

#include "frameworks/core/accessibility/js_inspector/inspect_textarea.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectTextAreaTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

    void CheckTextAreaAttrAndStyle(InspectTextArea& inspectTextArea, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 4;
        uint16_t stylesSizeInsert = 3;
        uint16_t insertThree = 3;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectTextArea.attrs_["extend"], "false");
        EXPECT_EQ(inspectTextArea.attrs_["showcounter"], "false");
        EXPECT_EQ(inspectTextArea.attrs_["disabled"], "false");
        EXPECT_EQ(inspectTextArea.attrs_["focusable"], "true");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectTextArea.styles_["color"], "#e6000000");
            EXPECT_EQ(inspectTextArea.styles_["font-size"], "16px");
            EXPECT_EQ(inspectTextArea.styles_["placeholder-color"], "#99000000");
            stylesSizeInsert += insertThree;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectTextArea.styles_["color"], "#e6ffffff");
            EXPECT_EQ(inspectTextArea.styles_["font-size"], "18px");
            EXPECT_EQ(inspectTextArea.styles_["placeholder-color"], "#99ffffff");
            stylesSizeInsert += insertThree;
        }
        EXPECT_EQ(inspectTextArea.styles_["allow-scale"], "true");
        EXPECT_EQ(inspectTextArea.styles_["font-weight"], "normal");
        EXPECT_EQ(inspectTextArea.styles_["font-family"], "sans-serif");
        EXPECT_EQ(inspectTextArea.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectTextArea.styles_.size(), stylesSize + stylesSizeInsert);
    }
};

/**
 * @tc.name: InspectTextAreaTest001
 * @tc.desc: InspectTextArea::InspectTextArea
 * @tc.type: FUNC
 */
HWTEST_F(InspectTextAreaTest, InspectTextAreaTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectTextArea inspectTextArea(nodeId, tag);
    EXPECT_EQ(inspectTextArea.nodeId_, nodeId);
    EXPECT_EQ(inspectTextArea.tag_, tag);
}

/**
 * @tc.name: InspectTextAreaTest002
 * @tc.desc: InspectTextArea::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectTextAreaTest, InspectTextAreaTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    uint16_t typeNum = 6;
    DeviceType deviceType = SystemProperties::GetDeviceType();
    for (uint16_t i = 0; i < typeNum; i++) {
        InspectTextArea inspectTextArea(nodeId, tag);
        auto attrsSize = inspectTextArea.attrs_.size();
        auto stylesSize = inspectTextArea.styles_.size();
        SystemProperties::SetDeviceType(static_cast<DeviceType>(i));
        inspectTextArea.PackAttrAndStyle();
        CheckTextAreaAttrAndStyle(inspectTextArea, attrsSize, stylesSize);
    }
    SystemProperties::SetDeviceType(deviceType);
}
} // namespace OHOS::Ace::Framework
