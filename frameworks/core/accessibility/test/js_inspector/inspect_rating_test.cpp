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

#include "frameworks/core/accessibility/js_inspector/inspect_rating.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
class InspectRatingTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

    void CheckRatingAttrAndStyle(InspectRating& inspectRating, uint16_t attrsSize, uint16_t stylesSize)
    {
        uint16_t attrsSizeInsert = 6;
        uint16_t stylesSizeInsert = 1;
        uint16_t insertTwo = 2;
        DeviceType deviceType = SystemProperties::GetDeviceType();
        EXPECT_EQ(inspectRating.attrs_["numstars"], "5");
        EXPECT_EQ(inspectRating.attrs_["rating"], "0");
        EXPECT_EQ(inspectRating.attrs_["stepsize"], "0.5");
        EXPECT_EQ(inspectRating.attrs_["indicator"], "false");
        EXPECT_EQ(inspectRating.attrs_["disabled"], "false");
        EXPECT_EQ(inspectRating.attrs_["focusable"], "true");
        if (deviceType == DeviceType::PHONE) {
            EXPECT_EQ(inspectRating.styles_["width"], "120px");
            EXPECT_EQ(inspectRating.styles_["height"], "24px");
            stylesSizeInsert += insertTwo;
        } else if (deviceType == DeviceType::TV) {
            EXPECT_EQ(inspectRating.styles_["width"], "360px");
            EXPECT_EQ(inspectRating.styles_["height"], "72px");
            stylesSizeInsert += insertTwo;
        }
        EXPECT_EQ(inspectRating.styles_["rtl-flip"], "true");
        EXPECT_EQ(inspectRating.attrs_.size(), attrsSize + attrsSizeInsert);
        EXPECT_EQ(inspectRating.styles_.size(), stylesSize + stylesSizeInsert);
    }
};

/**
 * @tc.name: InspectRatingTest001
 * @tc.desc: InspectRating::InspectRating
 * @tc.type: FUNC
 */
HWTEST_F(InspectRatingTest, InspectRatingTest001, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRating inspectRating(nodeId, tag);
    EXPECT_EQ(inspectRating.nodeId_, nodeId);
    EXPECT_EQ(inspectRating.tag_, tag);
}

/**
 * @tc.name: InspectRatingTest002
 * @tc.desc: InspectRating::PackAttrAndStyle-PHONE
 * @tc.type: FUNC
 */
HWTEST_F(InspectRatingTest, InspectRatingTest002, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRating inspectRating(nodeId, tag);
    auto attrsSize = inspectRating.attrs_.size();
    auto stylesSize = inspectRating.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    inspectRating.PackAttrAndStyle();
    CheckRatingAttrAndStyle(inspectRating, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRatingTest003
 * @tc.desc: InspectRating::PackAttrAndStyle-TV
 * @tc.type: FUNC
 */
HWTEST_F(InspectRatingTest, InspectRatingTest003, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRating inspectRating(nodeId, tag);
    auto attrsSize = inspectRating.attrs_.size();
    auto stylesSize = inspectRating.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TV);
    inspectRating.PackAttrAndStyle();
    CheckRatingAttrAndStyle(inspectRating, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRatingTest004
 * @tc.desc: InspectRating::PackAttrAndStyle-WATCH
 * @tc.type: FUNC
 */
HWTEST_F(InspectRatingTest, InspectRatingTest004, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRating inspectRating(nodeId, tag);
    auto attrsSize = inspectRating.attrs_.size();
    auto stylesSize = inspectRating.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    inspectRating.PackAttrAndStyle();
    CheckRatingAttrAndStyle(inspectRating, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRatingTest005
 * @tc.desc: InspectRating::PackAttrAndStyle-CAR
 * @tc.type: FUNC
 */
HWTEST_F(InspectRatingTest, InspectRatingTest005, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRating inspectRating(nodeId, tag);
    auto attrsSize = inspectRating.attrs_.size();
    auto stylesSize = inspectRating.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::CAR);
    inspectRating.PackAttrAndStyle();
    CheckRatingAttrAndStyle(inspectRating, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRatingTest006
 * @tc.desc: InspectRating::PackAttrAndStyle-TABLET
 * @tc.type: FUNC
 */
HWTEST_F(InspectRatingTest, InspectRatingTest006, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRating inspectRating(nodeId, tag);
    auto attrsSize = inspectRating.attrs_.size();
    auto stylesSize = inspectRating.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    inspectRating.PackAttrAndStyle();
    CheckRatingAttrAndStyle(inspectRating, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}

/**
 * @tc.name: InspectRatingTest007
 * @tc.desc: InspectRating::PackAttrAndStyle-UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(InspectRatingTest, InspectRatingTest007, TestSize.Level1)
{
    NodeId nodeId = -1;
    std::string tag = "tagTest";
    InspectRating inspectRating(nodeId, tag);
    auto attrsSize = inspectRating.attrs_.size();
    auto stylesSize = inspectRating.styles_.size();

    DeviceType deviceType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
    inspectRating.PackAttrAndStyle();
    CheckRatingAttrAndStyle(inspectRating, attrsSize, stylesSize);
    SystemProperties::SetDeviceType(deviceType);
}
} // namespace OHOS::Ace::Framework
