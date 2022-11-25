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

#include "frameworks/core/accessibility/js_inspector/inspect_text.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectTextTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

    void CheckTextAttrAndStyle(InspectText& inspectText, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 2;
        uint16_t stylesSizeInsert = 11;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectText.attrs_["disabled"], "false");
        EXPECT_EQ(inspectText.attrs_["focusable"], "false");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectText.styles_["color"], "#e5000000");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectText.styles_["color"], "#e5ffffff");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::WATCH) {
            EXPECT_EQ(inspectText.styles_["color"], "#ffffffff");
            stylesSizeInsert++;
        }
        EXPECT_EQ(inspectText.styles_["font-size"], "30px");
        EXPECT_EQ(inspectText.styles_["allow-scale"], "true");
        EXPECT_EQ(inspectText.styles_["letter-spacing"], "0px");
        EXPECT_EQ(inspectText.styles_["font-style"], "normal");
        EXPECT_EQ(inspectText.styles_["font-weight"], "normal");
        EXPECT_EQ(inspectText.styles_["text-decoration"], "none");
        EXPECT_EQ(inspectText.styles_["text-align"], "start");
        EXPECT_EQ(inspectText.styles_["line-height"], "0px");
        EXPECT_EQ(inspectText.styles_["text-overflow"], "clip");
        EXPECT_EQ(inspectText.styles_["font-family"], "sans-serif");
        EXPECT_EQ(inspectText.styles_["font-size-step"], "1px");
        EXPECT_EQ(inspectText.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectText.styles_.size(), stylesSize + stylesSizeInsert);
    }
};

/**
 * @tc.name: InspectTextTest001
 * @tc.desc: InspectText::InspectText
 * @tc.type: FUNC
 */
HWTEST_F(InspectTextTest, InspectTextTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectText inspectText(nodeId, tag);
    EXPECT_EQ(inspectText.nodeId_, nodeId);
    EXPECT_EQ(inspectText.tag_, tag);
}

/**
 * @tc.name: InspectTextTest002
 * @tc.desc: InspectText::PackAttrAndStyle
 * @tc.type: FUNC
 */
HWTEST_F(InspectTextTest, InspectTextTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    uint16_t typeNum = 6;
    DeviceType deviceType = SystemProperties::GetDeviceType();
    for (uint16_t i = 0; i < typeNum; i++) {
        InspectText inspectText(nodeId, tag);
        auto attrsSize = inspectText.attrs_.size();
        auto stylesSize = inspectText.styles_.size();
        SystemProperties::SetDeviceType(static_cast<DeviceType>(i));
        inspectText.PackAttrAndStyle();
        CheckTextAttrAndStyle(inspectText, attrsSize, stylesSize);
    }
    SystemProperties::SetDeviceType(deviceType);
}
} // namespace OHOS::Ace::Framework
