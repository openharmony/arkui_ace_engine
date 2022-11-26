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

#include "frameworks/core/accessibility/js_inspector/inspect_divider.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectDividerTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

    void CheckDividerAttrAndStyle(InspectDivider& inspectDivider, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 1;
        uint16_t stylesSizeInsert = 10;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectDivider.attrs_["vertical"], "false");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectDivider.styles_["color"], "#08000000");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectDivider.styles_["color"], "#33ffffff");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::WATCH) {
            EXPECT_EQ(inspectDivider.styles_["color"], "#33ffffff");
            stylesSizeInsert++;
        }
        EXPECT_EQ(inspectDivider.styles_["stroke-width"], "1");
        EXPECT_EQ(inspectDivider.styles_["line-cap"], "butt");
        EXPECT_EQ(inspectDivider.styles_["margin-left"], "0");
        EXPECT_EQ(inspectDivider.styles_["margin-top"], "0");
        EXPECT_EQ(inspectDivider.styles_["margin-right"], "0");
        EXPECT_EQ(inspectDivider.styles_["margin-bottom"], "0");
        EXPECT_EQ(inspectDivider.styles_["display"], "flex");
        EXPECT_EQ(inspectDivider.styles_["visibility"], "visible");
        EXPECT_EQ(inspectDivider.styles_["flex-grow"], "0");
        EXPECT_EQ(inspectDivider.styles_["flex-shrink"], "1");
        EXPECT_EQ(inspectDivider.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectDivider.styles_.size(), stylesSize + stylesSizeInsert);
    }
};

/**
 * @tc.name: InspectDividerTest001
 * @tc.desc: InspectDivider::InspectDivider
 * @tc.type: FUNC
 */
HWTEST_F(InspectDividerTest, InspectDividerTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDivider inspectDivider(nodeId, tag);
    EXPECT_EQ(inspectDivider.nodeId_, nodeId);
    EXPECT_EQ(inspectDivider.tag_, tag);
}

/**
 * @tc.name: InspectDividerTest002
 * @tc.desc: InspectDivider::PackAttrAndStyle-PHONE
 * @tc.type: FUNC
 */
HWTEST_F(InspectDividerTest, InspectDividerTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDivider inspectDivider(nodeId, tag);
    auto attrsSize = inspectDivider.attrs_.size();
    auto stylesSize = inspectDivider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectDivider.PackAttrAndStyle();
    CheckDividerAttrAndStyle(inspectDivider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectDividerTest003
 * @tc.desc: InspectDivider::PackAttrAndStyle-TV
 * @tc.type: FUNC
 */
HWTEST_F(InspectDividerTest, InspectDividerTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDivider inspectDivider(nodeId, tag);
    auto attrsSize = inspectDivider.attrs_.size();
    auto stylesSize = inspectDivider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TV);
    inspectDivider.PackAttrAndStyle();
    CheckDividerAttrAndStyle(inspectDivider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectDividerTest004
 * @tc.desc: InspectDivider::PackAttrAndStyle-WATCH
 * @tc.type: FUNC
 */
HWTEST_F(InspectDividerTest, InspectDividerTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDivider inspectDivider(nodeId, tag);
    auto attrsSize = inspectDivider.attrs_.size();
    auto stylesSize = inspectDivider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    inspectDivider.PackAttrAndStyle();
    CheckDividerAttrAndStyle(inspectDivider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectDividerTest005
 * @tc.desc: InspectDivider::PackAttrAndStyle-CAR
 * @tc.type: FUNC
 */
HWTEST_F(InspectDividerTest, InspectDividerTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDivider inspectDivider(nodeId, tag);
    auto attrsSize = inspectDivider.attrs_.size();
    auto stylesSize = inspectDivider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::CAR);
    inspectDivider.PackAttrAndStyle();
    CheckDividerAttrAndStyle(inspectDivider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectDividerTest006
 * @tc.desc: InspectDivider::PackAttrAndStyle-TABLET
 * @tc.type: FUNC
 */
HWTEST_F(InspectDividerTest, InspectDividerTest006, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDivider inspectDivider(nodeId, tag);
    auto attrsSize = inspectDivider.attrs_.size();
    auto stylesSize = inspectDivider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    inspectDivider.PackAttrAndStyle();
    CheckDividerAttrAndStyle(inspectDivider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectDividerTest007
 * @tc.desc: InspectDivider::PackAttrAndStyle-UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(InspectDividerTest, InspectDividerTest007, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectDivider inspectDivider(nodeId, tag);
    auto attrsSize = inspectDivider.attrs_.size();
    auto stylesSize = inspectDivider.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
    inspectDivider.PackAttrAndStyle();
    CheckDividerAttrAndStyle(inspectDivider, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}
} // namespace OHOS::Ace::Framework
