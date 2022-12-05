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

    void CheckButtonAttrAndStyle(InspectButton& inspectButton, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 4;
        uint16_t stylesSizeInsert = 4;
        uint16_t insertTwo = 2;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectButton.attrs_["placement"], "end");
        EXPECT_EQ(inspectButton.attrs_["waiting"], "false");
        EXPECT_EQ(inspectButton.attrs_["disabled"], "false");
        EXPECT_EQ(inspectButton.attrs_["focusable"], "true");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectButton.styles_["text-color"], "#ff007dff");
            EXPECT_EQ(inspectButton.styles_["font-size"], "16px");
            stylesSizeInsert += insertTwo;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectButton.styles_["text-color"], "#e5ffffff");
            EXPECT_EQ(inspectButton.styles_["font-size"], "18px");
            stylesSizeInsert += insertTwo;
        } else if (deviceType == DeviceType::WATCH) {
            EXPECT_EQ(inspectButton.styles_["text-color"], "#ff45a5ff");
            EXPECT_EQ(inspectButton.styles_["font-size"], "16px");
            stylesSizeInsert += insertTwo;
        }
        EXPECT_EQ(inspectButton.styles_["allow-scale"], "true");
        EXPECT_EQ(inspectButton.styles_["font-style"], "normal");
        EXPECT_EQ(inspectButton.styles_["font-weight"], "normal");
        EXPECT_EQ(inspectButton.styles_["font-family"], "sans-serif");
        EXPECT_EQ(inspectButton.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectButton.styles_.size(), stylesSize + stylesSizeInsert);
    }
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
 * @tc.desc: InspectButton::PackAttrAndStyle-PHONE
 * @tc.type: FUNC
 */
HWTEST_F(InspectButtonTest, InspectButtonTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectButton inspectButton(nodeId, tag);
    auto attrsSize = inspectButton.attrs_.size();
    auto stylesSize = inspectButton.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectButton.PackAttrAndStyle();
    CheckButtonAttrAndStyle(inspectButton, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectButtonTest003
 * @tc.desc: InspectButton::PackAttrAndStyle-TV
 * @tc.type: FUNC
 */
HWTEST_F(InspectButtonTest, InspectButtonTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectButton inspectButton(nodeId, tag);
    auto attrsSize = inspectButton.attrs_.size();
    auto stylesSize = inspectButton.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TV);
    inspectButton.PackAttrAndStyle();
    CheckButtonAttrAndStyle(inspectButton, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectButtonTest004
 * @tc.desc: InspectButton::PackAttrAndStyle-WATCH
 * @tc.type: FUNC
 */
HWTEST_F(InspectButtonTest, InspectButtonTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectButton inspectButton(nodeId, tag);
    auto attrsSize = inspectButton.attrs_.size();
    auto stylesSize = inspectButton.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    inspectButton.PackAttrAndStyle();
    CheckButtonAttrAndStyle(inspectButton, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectButtonTest005
 * @tc.desc: InspectButton::PackAttrAndStyle-CAR
 * @tc.type: FUNC
 */
HWTEST_F(InspectButtonTest, InspectButtonTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectButton inspectButton(nodeId, tag);
    auto attrsSize = inspectButton.attrs_.size();
    auto stylesSize = inspectButton.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::CAR);
    inspectButton.PackAttrAndStyle();
    CheckButtonAttrAndStyle(inspectButton, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectButtonTest006
 * @tc.desc: InspectButton::PackAttrAndStyle-TABLET
 * @tc.type: FUNC
 */
HWTEST_F(InspectButtonTest, InspectButtonTest006, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectButton inspectButton(nodeId, tag);
    auto attrsSize = inspectButton.attrs_.size();
    auto stylesSize = inspectButton.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    inspectButton.PackAttrAndStyle();
    CheckButtonAttrAndStyle(inspectButton, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectButtonTest007
 * @tc.desc: InspectButton::PackAttrAndStyle-UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(InspectButtonTest, InspectButtonTest007, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectButton inspectButton(nodeId, tag);
    auto attrsSize = inspectButton.attrs_.size();
    auto stylesSize = inspectButton.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
    inspectButton.PackAttrAndStyle();
    CheckButtonAttrAndStyle(inspectButton, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}
} // namespace OHOS::Ace::Framework
