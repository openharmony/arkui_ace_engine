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

#include "frameworks/core/accessibility/js_inspector/inspect_slider.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectSliderTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

    void CheckSliderAttrAndStyle(InspectSlider& inspectSlider, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 10;
        uint16_t stylesSizeInsert = 1;
        uint16_t insertTwo = 2;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectSlider.attrs_["min"], "0");
        EXPECT_EQ(inspectSlider.attrs_["max"], "100");
        EXPECT_EQ(inspectSlider.attrs_["step"], "1");
        EXPECT_EQ(inspectSlider.attrs_["value"], "0");
        EXPECT_EQ(inspectSlider.attrs_["type"], "continuous");
        EXPECT_EQ(inspectSlider.attrs_["mode"], "outset");
        EXPECT_EQ(inspectSlider.attrs_["showsteps"], "false");
        EXPECT_EQ(inspectSlider.attrs_["showtips"], "false");
        EXPECT_EQ(inspectSlider.attrs_["disabled"], "false");
        EXPECT_EQ(inspectSlider.attrs_["focusable"], "true");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectSlider.styles_["color"], "#19000000");
            EXPECT_EQ(inspectSlider.styles_["selected-color"], "#ff007dff");
            stylesSizeInsert += insertTwo;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectSlider.styles_["color"], "#33ffffff");
            EXPECT_EQ(inspectSlider.styles_["selected-color"], "#ff0d9ffb");
            stylesSizeInsert += insertTwo;
        } else if (deviceType == DeviceType::WATCH) {
            EXPECT_EQ(inspectSlider.styles_["color"], "#26ffffff");
            EXPECT_EQ(inspectSlider.styles_["selected-color"], "#ff007dff");
            stylesSizeInsert += insertTwo;
        }
        EXPECT_EQ(inspectSlider.styles_["block-color"], "#ffffff");
        EXPECT_EQ(inspectSlider.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectSlider.styles_.size(), stylesSize + stylesSizeInsert);
    }
};

/**
 * @tc.name: InspectSliderTest001
 * @tc.desc: InspectSlider::InspectSlider
 * @tc.type: FUNC
 */
HWTEST_F(InspectSliderTest, InspectSliderTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSlider inspectSlider(nodeId, tag);
    EXPECT_EQ(inspectSlider.nodeId_, nodeId);
    EXPECT_EQ(inspectSlider.tag_, tag);
}

/**
 * @tc.name: InspectSliderTest002
 * @tc.desc: InspectSlider::PackAttrAndStyle-PHONE
 * @tc.type: FUNC
 */
HWTEST_F(InspectSliderTest, InspectSliderTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSlider inspectSlider(nodeId, tag);
    auto attrsSize = inspectSlider.attrs_.size();
    auto stylesSize = inspectSlider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectSlider.PackAttrAndStyle();
    CheckSliderAttrAndStyle(inspectSlider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSliderTest003
 * @tc.desc: InspectSlider::PackAttrAndStyle-TV
 * @tc.type: FUNC
 */
HWTEST_F(InspectSliderTest, InspectSliderTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSlider inspectSlider(nodeId, tag);
    auto attrsSize = inspectSlider.attrs_.size();
    auto stylesSize = inspectSlider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TV);
    inspectSlider.PackAttrAndStyle();
    CheckSliderAttrAndStyle(inspectSlider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSliderTest004
 * @tc.desc: InspectSlider::PackAttrAndStyle-WATCH
 * @tc.type: FUNC
 */
HWTEST_F(InspectSliderTest, InspectSliderTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSlider inspectSlider(nodeId, tag);
    auto attrsSize = inspectSlider.attrs_.size();
    auto stylesSize = inspectSlider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    inspectSlider.PackAttrAndStyle();
    CheckSliderAttrAndStyle(inspectSlider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSliderTest005
 * @tc.desc: InspectSlider::PackAttrAndStyle-CAR
 * @tc.type: FUNC
 */
HWTEST_F(InspectSliderTest, InspectSliderTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSlider inspectSlider(nodeId, tag);
    auto attrsSize = inspectSlider.attrs_.size();
    auto stylesSize = inspectSlider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::CAR);
    inspectSlider.PackAttrAndStyle();
    CheckSliderAttrAndStyle(inspectSlider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSliderTest006
 * @tc.desc: InspectSlider::PackAttrAndStyle-TABLET
 * @tc.type: FUNC
 */
HWTEST_F(InspectSliderTest, InspectSliderTest006, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSlider inspectSlider(nodeId, tag);
    auto attrsSize = inspectSlider.attrs_.size();
    auto stylesSize = inspectSlider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    inspectSlider.PackAttrAndStyle();
    CheckSliderAttrAndStyle(inspectSlider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectSliderTest007
 * @tc.desc: InspectSlider::PackAttrAndStyle-UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(InspectSliderTest, InspectSliderTest007, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectSlider inspectSlider(nodeId, tag);
    auto attrsSize = inspectSlider.attrs_.size();
    auto stylesSize = inspectSlider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
    inspectSlider.PackAttrAndStyle();
    CheckSliderAttrAndStyle(inspectSlider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}
} // namespace OHOS::Ace::Framework
