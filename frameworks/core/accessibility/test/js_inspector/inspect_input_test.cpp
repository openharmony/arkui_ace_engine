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

#include "frameworks/core/accessibility/js_inspector/inspect_input.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectInputTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

    void CheckInputAttrAndStyle(InspectInput& inspectInput, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 6;
        uint16_t stylesSizeInsert = 3;
        uint16_t insertThree = 3;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectInput.attrs_["type"], "text");
        EXPECT_EQ(inspectInput.attrs_["checked"], "false");
        EXPECT_EQ(inspectInput.attrs_["enterkeytype"], "default");
        EXPECT_EQ(inspectInput.attrs_["showcounter"], "false");
        EXPECT_EQ(inspectInput.attrs_["disabled"], "false");
        EXPECT_EQ(inspectInput.attrs_["focusable"], "true");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectInput.styles_["color"], "#e6000000");
            EXPECT_EQ(inspectInput.styles_["font-size"], "16px");
            EXPECT_EQ(inspectInput.styles_["placeholder-color"], "#99000000");
            stylesSizeInsert += insertThree;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectInput.styles_["color"], "#e6ffffff");
            EXPECT_EQ(inspectInput.styles_["font-size"], "18px");
            EXPECT_EQ(inspectInput.styles_["placeholder-color"], "#99ffffff");
            stylesSizeInsert += insertThree;
        }
        EXPECT_EQ(inspectInput.styles_["allow-scale"], "true");
        EXPECT_EQ(inspectInput.styles_["font-weight"], "normal");
        EXPECT_EQ(inspectInput.styles_["font-family"], "sans-serif");
        EXPECT_EQ(inspectInput.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectInput.styles_.size(), stylesSize + stylesSizeInsert);
    }
};

/**
 * @tc.name: InspectInputTest001
 * @tc.desc: InspectInput::InspectInput
 * @tc.type: FUNC
 */
HWTEST_F(InspectInputTest, InspectInputTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectInput inspectInput(nodeId, tag);
    EXPECT_EQ(inspectInput.nodeId_, nodeId);
    EXPECT_EQ(inspectInput.tag_, tag);
}

/**
 * @tc.name: InspectInputTest002
 * @tc.desc: InspectInput::PackAttrAndStyle-PHONE
 * @tc.type: FUNC
 */
HWTEST_F(InspectInputTest, InspectInputTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectInput inspectInput(nodeId, tag);
    auto attrsSize = inspectInput.attrs_.size();
    auto stylesSize = inspectInput.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectInput.PackAttrAndStyle();
    CheckInputAttrAndStyle(inspectInput, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectInputTest003
 * @tc.desc: InspectInput::PackAttrAndStyle-TV
 * @tc.type: FUNC
 */
HWTEST_F(InspectInputTest, InspectInputTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectInput inspectInput(nodeId, tag);
    auto attrsSize = inspectInput.attrs_.size();
    auto stylesSize = inspectInput.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TV);
    inspectInput.PackAttrAndStyle();
    CheckInputAttrAndStyle(inspectInput, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectInputTest004
 * @tc.desc: InspectInput::PackAttrAndStyle-WATCH
 * @tc.type: FUNC
 */
HWTEST_F(InspectInputTest, InspectInputTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectInput inspectInput(nodeId, tag);
    auto attrsSize = inspectInput.attrs_.size();
    auto stylesSize = inspectInput.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    inspectInput.PackAttrAndStyle();
    CheckInputAttrAndStyle(inspectInput, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectInputTest005
 * @tc.desc: InspectInput::PackAttrAndStyle-CAR
 * @tc.type: FUNC
 */
HWTEST_F(InspectInputTest, InspectInputTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectInput inspectInput(nodeId, tag);
    auto attrsSize = inspectInput.attrs_.size();
    auto stylesSize = inspectInput.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::CAR);
    inspectInput.PackAttrAndStyle();
    CheckInputAttrAndStyle(inspectInput, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectInputTest006
 * @tc.desc: InspectInput::PackAttrAndStyle-TABLET
 * @tc.type: FUNC
 */
HWTEST_F(InspectInputTest, InspectInputTest006, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectInput inspectInput(nodeId, tag);
    auto attrsSize = inspectInput.attrs_.size();
    auto stylesSize = inspectInput.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    inspectInput.PackAttrAndStyle();
    CheckInputAttrAndStyle(inspectInput, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectInputTest007
 * @tc.desc: InspectInput::PackAttrAndStyle-UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(InspectInputTest, InspectInputTest007, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectInput inspectInput(nodeId, tag);
    auto attrsSize = inspectInput.attrs_.size();
    auto stylesSize = inspectInput.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
    inspectInput.PackAttrAndStyle();
    CheckInputAttrAndStyle(inspectInput, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}
} // namespace OHOS::Ace::Framework
