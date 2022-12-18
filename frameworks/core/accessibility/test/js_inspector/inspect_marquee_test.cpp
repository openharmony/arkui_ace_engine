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

#include "frameworks/core/accessibility/js_inspector/inspect_marquee.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectMarqueeTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

    void CheckMarqueeAttrAndStyle(InspectMarquee& inspectMarquee, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 5;
        uint16_t stylesSizeInsert = 4;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectMarquee.attrs_["scrollamount"], "6");
        EXPECT_EQ(inspectMarquee.attrs_["loop"], "-1");
        EXPECT_EQ(inspectMarquee.attrs_["direction"], "left");
        EXPECT_EQ(inspectMarquee.attrs_["disabled"], "false");
        EXPECT_EQ(inspectMarquee.attrs_["focusable"], "false");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectMarquee.styles_["color"], "#e5000000");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectMarquee.styles_["color"], "#e5ffffff");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::WATCH) {
            EXPECT_EQ(inspectMarquee.styles_["color"], "#ffffffff");
            stylesSizeInsert++;
        }
        EXPECT_EQ(inspectMarquee.styles_["font-size"], "37.5");
        EXPECT_EQ(inspectMarquee.styles_["allow-scale"], "true");
        EXPECT_EQ(inspectMarquee.styles_["font-weight"], "normal");
        EXPECT_EQ(inspectMarquee.styles_["font-family"], "sans-serif");
        EXPECT_EQ(inspectMarquee.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectMarquee.styles_.size(), stylesSize + stylesSizeInsert);
    }
};

/**
 * @tc.name: InspectMarqueeTest001
 * @tc.desc: InspectMarquee::InspectMarquee
 * @tc.type: FUNC
 */
HWTEST_F(InspectMarqueeTest, InspectMarqueeTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectMarquee inspectMarquee(nodeId, tag);
    EXPECT_EQ(inspectMarquee.nodeId_, nodeId);
    EXPECT_EQ(inspectMarquee.tag_, tag);
}

/**
 * @tc.name: InspectMarqueeTest002
 * @tc.desc: InspectMarquee::PackAttrAndStyle-PHONE
 * @tc.type: FUNC
 */
HWTEST_F(InspectMarqueeTest, InspectMarqueeTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectMarquee inspectMarquee(nodeId, tag);
    auto attrsSize = inspectMarquee.attrs_.size();
    auto stylesSize = inspectMarquee.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectMarquee.PackAttrAndStyle();
    CheckMarqueeAttrAndStyle(inspectMarquee, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectMarqueeTest003
 * @tc.desc: InspectMarquee::PackAttrAndStyle-TV
 * @tc.type: FUNC
 */
HWTEST_F(InspectMarqueeTest, InspectMarqueeTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectMarquee inspectMarquee(nodeId, tag);
    auto attrsSize = inspectMarquee.attrs_.size();
    auto stylesSize = inspectMarquee.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TV);
    inspectMarquee.PackAttrAndStyle();
    CheckMarqueeAttrAndStyle(inspectMarquee, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectMarqueeTest004
 * @tc.desc: InspectMarquee::PackAttrAndStyle-WATCH
 * @tc.type: FUNC
 */
HWTEST_F(InspectMarqueeTest, InspectMarqueeTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectMarquee inspectMarquee(nodeId, tag);
    auto attrsSize = inspectMarquee.attrs_.size();
    auto stylesSize = inspectMarquee.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    inspectMarquee.PackAttrAndStyle();
    CheckMarqueeAttrAndStyle(inspectMarquee, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectMarqueeTest005
 * @tc.desc: InspectMarquee::PackAttrAndStyle-CAR
 * @tc.type: FUNC
 */
HWTEST_F(InspectMarqueeTest, InspectMarqueeTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectMarquee inspectMarquee(nodeId, tag);
    auto attrsSize = inspectMarquee.attrs_.size();
    auto stylesSize = inspectMarquee.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::CAR);
    inspectMarquee.PackAttrAndStyle();
    CheckMarqueeAttrAndStyle(inspectMarquee, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectMarqueeTest006
 * @tc.desc: InspectMarquee::PackAttrAndStyle-TABLET
 * @tc.type: FUNC
 */
HWTEST_F(InspectMarqueeTest, InspectMarqueeTest006, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectMarquee inspectMarquee(nodeId, tag);
    auto attrsSize = inspectMarquee.attrs_.size();
    auto stylesSize = inspectMarquee.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    inspectMarquee.PackAttrAndStyle();
    CheckMarqueeAttrAndStyle(inspectMarquee, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectMarqueeTest007
 * @tc.desc: InspectMarquee::PackAttrAndStyle-UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(InspectMarqueeTest, InspectMarqueeTest007, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectMarquee inspectMarquee(nodeId, tag);
    auto attrsSize = inspectMarquee.attrs_.size();
    auto stylesSize = inspectMarquee.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
    inspectMarquee.PackAttrAndStyle();
    CheckMarqueeAttrAndStyle(inspectMarquee, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}
} // namespace OHOS::Ace::Framework
