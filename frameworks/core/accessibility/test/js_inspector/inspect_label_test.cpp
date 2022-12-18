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

#include "frameworks/core/accessibility/js_inspector/inspect_label.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectLabelTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

    void CheckLabelAttrAndStyle(InspectLabel& inspectLabel, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 2;
        uint16_t stylesSizeInsert = 11;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectLabel.attrs_["disabled"], "false");
        EXPECT_EQ(inspectLabel.attrs_["focusable"], "false");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectLabel.styles_["color"], "#e5000000");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectLabel.styles_["color"], "#e5ffffff");
            stylesSizeInsert++;
        } else if (deviceType == DeviceType::WATCH) {
            EXPECT_EQ(inspectLabel.styles_["color"], "#ffffffff");
            stylesSizeInsert++;
        }
        EXPECT_EQ(inspectLabel.styles_["font-size"], "30px");
        EXPECT_EQ(inspectLabel.styles_["allow-scale"], "true");
        EXPECT_EQ(inspectLabel.styles_["letter-spacing"], "0px");
        EXPECT_EQ(inspectLabel.styles_["font-style"], "normal");
        EXPECT_EQ(inspectLabel.styles_["font-weight"], "normal");
        EXPECT_EQ(inspectLabel.styles_["text-decoration"], "none");
        EXPECT_EQ(inspectLabel.styles_["text-align"], "start");
        EXPECT_EQ(inspectLabel.styles_["line-height"], "0px");
        EXPECT_EQ(inspectLabel.styles_["text-overflow"], "clip");
        EXPECT_EQ(inspectLabel.styles_["font-family"], "sans-serif");
        EXPECT_EQ(inspectLabel.styles_["font-size-step"], "1px");
        EXPECT_EQ(inspectLabel.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectLabel.styles_.size(), stylesSize + stylesSizeInsert);
    }
};

/**
 * @tc.name: InspectLabelTest001
 * @tc.desc: InspectLabel::InspectLabel
 * @tc.type: FUNC
 */
HWTEST_F(InspectLabelTest, InspectLabelTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectLabel inspectLabel(nodeId, tag);
    EXPECT_EQ(inspectLabel.nodeId_, nodeId);
    EXPECT_EQ(inspectLabel.tag_, tag);
}

/**
 * @tc.name: InspectLabelTest002
 * @tc.desc: InspectLabel::PackAttrAndStyle-PHONE
 * @tc.type: FUNC
 */
HWTEST_F(InspectLabelTest, InspectLabelTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectLabel inspectLabel(nodeId, tag);
    auto attrsSize = inspectLabel.attrs_.size();
    auto stylesSize = inspectLabel.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectLabel.PackAttrAndStyle();
    CheckLabelAttrAndStyle(inspectLabel, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectLabelTest003
 * @tc.desc: InspectLabel::PackAttrAndStyle-TV
 * @tc.type: FUNC
 */
HWTEST_F(InspectLabelTest, InspectLabelTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectLabel inspectLabel(nodeId, tag);
    auto attrsSize = inspectLabel.attrs_.size();
    auto stylesSize = inspectLabel.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TV);
    inspectLabel.PackAttrAndStyle();
    CheckLabelAttrAndStyle(inspectLabel, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectLabelTest004
 * @tc.desc: InspectLabel::PackAttrAndStyle-WATCH
 * @tc.type: FUNC
 */
HWTEST_F(InspectLabelTest, InspectLabelTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectLabel inspectLabel(nodeId, tag);
    auto attrsSize = inspectLabel.attrs_.size();
    auto stylesSize = inspectLabel.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    inspectLabel.PackAttrAndStyle();
    CheckLabelAttrAndStyle(inspectLabel, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectLabelTest005
 * @tc.desc: InspectLabel::PackAttrAndStyle-CAR
 * @tc.type: FUNC
 */
HWTEST_F(InspectLabelTest, InspectLabelTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectLabel inspectLabel(nodeId, tag);
    auto attrsSize = inspectLabel.attrs_.size();
    auto stylesSize = inspectLabel.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::CAR);
    inspectLabel.PackAttrAndStyle();
    CheckLabelAttrAndStyle(inspectLabel, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectLabelTest006
 * @tc.desc: InspectLabel::PackAttrAndStyle-TABLET
 * @tc.type: FUNC
 */
HWTEST_F(InspectLabelTest, InspectLabelTest006, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectLabel inspectLabel(nodeId, tag);
    auto attrsSize = inspectLabel.attrs_.size();
    auto stylesSize = inspectLabel.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    inspectLabel.PackAttrAndStyle();
    CheckLabelAttrAndStyle(inspectLabel, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectLabelTest007
 * @tc.desc: InspectLabel::PackAttrAndStyle-UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(InspectLabelTest, InspectLabelTest007, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectLabel inspectLabel(nodeId, tag);
    auto attrsSize = inspectLabel.attrs_.size();
    auto stylesSize = inspectLabel.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
    inspectLabel.PackAttrAndStyle();
    CheckLabelAttrAndStyle(inspectLabel, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}
} // namespace OHOS::Ace::Framework
