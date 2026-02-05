/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "test/mock/core/common/mock_container.h"
#include "test/unittest/core/pattern/test_ng.h"

#define protected public
#define private public

#include "frameworks/bridge/common/media_query/media_query_info.h"
#include "frameworks/bridge/common/media_query/media_queryer.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace std;

class MediaQueryTest : public TestNG {};
class MediaQueryerTest : public TestNG {};

/**
 * @tc.name: GetOrientationTest1
 * @tc.desc: Test GetOrientation
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryTest, GetOrientationTest1, TestSize.Level1)
{
    auto container = MockContainer::Current();
    ASSERT_TRUE(container);
    container->SetCurrentDisplayOrientation(DisplayOrientation::PORTRAIT);
    EXPECT_EQ(Framework::MediaQueryInfo::GetOrientation(container), "portrait");

    container->SetCurrentDisplayOrientation(DisplayOrientation::PORTRAIT_INVERTED);
    EXPECT_EQ(Framework::MediaQueryInfo::GetOrientation(container), "portrait");

    container->SetCurrentDisplayOrientation(DisplayOrientation::LANDSCAPE);
    EXPECT_EQ(Framework::MediaQueryInfo::GetOrientation(container), "landscape");

    container->SetCurrentDisplayOrientation(DisplayOrientation::LANDSCAPE_INVERTED);
    EXPECT_EQ(Framework::MediaQueryInfo::GetOrientation(container), "landscape");
}

/**
 * @tc.name: GetOrientationTest2
 * @tc.desc: Test GetOrientation, container == nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryTest, GetOrientationTest2, TestSize.Level1)
{
    SystemProperties::SetDeviceOrientation(0);
    EXPECT_EQ(Framework::MediaQueryInfo::GetOrientation(nullptr), "portrait");

    SystemProperties::SetDeviceOrientation(1);
    EXPECT_EQ(Framework::MediaQueryInfo::GetOrientation(nullptr), "landscape");

    // outliers don't change
    SystemProperties::SetDeviceOrientation(-1);
    EXPECT_EQ(Framework::MediaQueryInfo::GetOrientation(nullptr), "landscape");
}

/**
 * @tc.name: GetSystemOrientationTest
 * @tc.desc: Test GetSystemOrientation
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryTest, GetSystemOrientationTest, TestSize.Level1)
{
    auto container = MockContainer::Current();
    ASSERT_TRUE(container);
    SystemProperties::SetDeviceOrientation(1);
    EXPECT_EQ(Framework::MediaQueryInfo::GetSystemOrientation(), "landscape");
}

/**
 * @tc.name: GetDeviceTypeTest001
 * @tc.desc: Test GetDeviceType for phone
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryTest, GetDeviceTypeTest001, TestSize.Level1)
{
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    EXPECT_EQ(Framework::MediaQueryInfo::GetDeviceType(), "phone");
}

/**
 * @tc.name: GetDeviceTypeTest002
 * @tc.desc: Test GetDeviceType for tablet
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryTest, GetDeviceTypeTest002, TestSize.Level1)
{
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    EXPECT_EQ(Framework::MediaQueryInfo::GetDeviceType(), "tablet");
}

/**
 * @tc.name: GetDeviceTypeTest003
 * @tc.desc: Test GetDeviceType for tv
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryTest, GetDeviceTypeTest003, TestSize.Level1)
{
    SystemProperties::SetDeviceType(DeviceType::TV);
    EXPECT_EQ(Framework::MediaQueryInfo::GetDeviceType(), "tv");
}

/**
 * @tc.name: GetDeviceTypeTest004
 * @tc.desc: Test GetDeviceType for car
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryTest, GetDeviceTypeTest004, TestSize.Level1)
{
    SystemProperties::SetDeviceType(DeviceType::CAR);
    EXPECT_EQ(Framework::MediaQueryInfo::GetDeviceType(), "car");
}

/**
 * @tc.name: GetDeviceTypeTest005
 * @tc.desc: Test GetDeviceType for wearable
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryTest, GetDeviceTypeTest005, TestSize.Level1)
{
    SystemProperties::SetDeviceType(DeviceType::WATCH);
    EXPECT_EQ(Framework::MediaQueryInfo::GetDeviceType(), "wearable");
}

/**
 * @tc.name: GetDeviceTypeTest006
 * @tc.desc: Test GetDeviceType for 2in1
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryTest, GetDeviceTypeTest006, TestSize.Level1)
{
    SystemProperties::SetDeviceType(DeviceType::TWO_IN_ONE);
    EXPECT_EQ(Framework::MediaQueryInfo::GetDeviceType(), "2in1");
}


/**
 * @tc.name: GetMediaQueryInfoTest001
 * @tc.desc: Test GetMediaQueryInfo
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryTest, GetMediaQueryInfoTest001, TestSize.Level1)
{
    Framework::MediaQueryInfo info;
    auto result = info.GetMediaQueryInfo();
    EXPECT_FALSE(result.empty());
}

/**
 * @tc.name: GetMediaQueryJsonInfoTest001
 * @tc.desc: Test GetMediaQueryJsonInfo
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryTest, GetMediaQueryJsonInfoTest001, TestSize.Level1)
{
    auto json = Framework::MediaQueryInfo::GetMediaQueryJsonInfo();
    ASSERT_NE(json, nullptr);
    EXPECT_GE(json->GetInt("width", -1), 0);
    EXPECT_GE(json->GetInt("height", -1), 0);
}

/**
 * @tc.name: IsInitTest001
 * @tc.desc: Test GetIsInit and SetIsInit
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryTest, IsInitTest001, TestSize.Level1)
{
    Framework::MediaQueryInfo info;
    EXPECT_TRUE(info.GetIsInit());
    info.SetIsInit(false);
    EXPECT_FALSE(info.GetIsInit());
    info.SetIsInit(true);
    EXPECT_TRUE(info.GetIsInit());
}

/**
 * @tc.name: ListenerIdTest001
 * @tc.desc: Test SetListenerId and GetListenerId
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryTest, ListenerIdTest001, TestSize.Level1)
{
    Framework::MediaQueryInfo info;
    const std::string testId = "test_listener_id";
    info.SetListenerId(testId);
    EXPECT_EQ(info.GetListenerId(), testId);
}

/**
 * @tc.name: ListenerIdTest002
 * @tc.desc: Test ResetListenerId
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryTest, ListenerIdTest002, TestSize.Level1)
{
    Framework::MediaQueryInfo info;
    const std::string testId = "test_listener_id";
    info.SetListenerId(testId);
    EXPECT_EQ(info.GetListenerId(), testId);
    info.ResetListenerId();
    EXPECT_TRUE(info.GetListenerId().empty());
}

/**
 * @tc.name: ListenerIdTest003
 * @tc.desc: Test EnsureListenerIdValid
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryTest, ListenerIdTest003, TestSize.Level1)
{
    Framework::MediaQueryInfo info;
    const std::string testId = "test_listener_id";
    info.SetListenerId(testId);
    EXPECT_EQ(info.GetListenerId(), testId);
    info.ResetListenerId();
    EXPECT_TRUE(info.GetListenerId().empty());
    info.EnsureListenerIdValid();
    EXPECT_EQ(info.GetListenerId(), testId);
}

/**
 * @tc.name: ListenerIdTest004
 * @tc.desc: Test EnsureListenerIdValid when backup is empty
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryTest, ListenerIdTest004, TestSize.Level1)
{
    Framework::MediaQueryInfo info;
    info.EnsureListenerIdValid();
    EXPECT_TRUE(info.GetListenerId().empty());
}

/**
 * @tc.name: MediaQueryerMatchConditionTest001
 * @tc.desc: Test MediaQueryer MatchCondition with empty condition
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest001, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_FALSE(queryer.MatchCondition("", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest002
 * @tc.desc: Test MediaQueryer MatchCondition with screen condition
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest002, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_FALSE(queryer.MatchCondition("screen", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest003
 * @tc.desc: Test MediaQueryer MatchCondition with only screen
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest003, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_FALSE(queryer.MatchCondition("only screen", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest004
 * @tc.desc: Test MediaQueryer MatchCondition with not screen
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest004, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition("not screen", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest005
 * @tc.desc: Test MediaQueryer MatchCondition with width condition
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest005, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition("(width>=100)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest006
 * @tc.desc: Test MediaQueryer MatchCondition with min-width
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest006, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition("(min-width:100)", json));
    EXPECT_FALSE(queryer.MatchCondition("(min-width:200)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest007
 * @tc.desc: Test MediaQueryer MatchCondition with max-width
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest007, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition("(max-width:200)", json));
    EXPECT_FALSE(queryer.MatchCondition("(max-width:50)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest008
 * @tc.desc: Test MediaQueryer MatchCondition with orientation
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest008, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    json->Put("orientation", "portrait");
    EXPECT_TRUE(queryer.MatchCondition("(orientation:portrait)", json));
    EXPECT_FALSE(queryer.MatchCondition("(orientation:landscape)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest009
 * @tc.desc: Test MediaQueryer MatchCondition with device-type
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest009, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    json->Put("device-type", "phone");
    EXPECT_TRUE(queryer.MatchCondition("(device-type:phone)", json));
    EXPECT_FALSE(queryer.MatchCondition("(device-type:tablet)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest010
 * @tc.desc: Test MediaQueryer MatchCondition with device-type default
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest010, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    json->Put("device-type", "phone");
    EXPECT_TRUE(queryer.MatchCondition("(device-type:default)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest011
 * @tc.desc: Test MediaQueryer MatchCondition with round-screen
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest011, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    json->Put("round-screen", true);
    EXPECT_TRUE(queryer.MatchCondition("(round-screen:true)", json));
    EXPECT_FALSE(queryer.MatchCondition("(round-screen:false)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest012
 * @tc.desc: Test MediaQueryer MatchCondition with dark-mode
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest012, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    json->Put("dark-mode", true);
    EXPECT_TRUE(queryer.MatchCondition("(dark-mode:true)", json));
    EXPECT_FALSE(queryer.MatchCondition("(dark-mode:false)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest013
 * @tc.desc: Test MediaQueryer MatchCondition with and condition
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest013, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition("(width>=50)and(width<=200)", json));
    EXPECT_FALSE(queryer.MatchCondition("(width>=50)and(width<=80)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest014
 * @tc.desc: Test MediaQueryer MatchCondition with or condition
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest014, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition("(width>=100)or(width<=50)", json));
    EXPECT_TRUE(queryer.MatchCondition("(height>=200)or(height<=50)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest015
 * @tc.desc: Test MediaQueryer MatchCondition with range condition
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest015, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition("(50<width<200)", json));
    EXPECT_FALSE(queryer.MatchCondition("(150<width<200)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest016
 * @tc.desc: Test MediaQueryer MatchCondition with screen and condition
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest016, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition("screen and (width>=100)", json));
    EXPECT_TRUE(queryer.MatchCondition("only screen and (width>=100)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest017
 * @tc.desc: Test MediaQueryer MatchCondition with not screen and condition
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest017, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_FALSE(queryer.MatchCondition("not screen and (width>=100)", json));
    EXPECT_TRUE(queryer.MatchCondition("not screen or (width>=200)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest018
 * @tc.desc: Test MediaQueryer MatchCondition with zero width
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest018, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 0);
    json->Put("height", 200);
    EXPECT_FALSE(queryer.MatchCondition("(width>=100)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest019
 * @tc.desc: Test MediaQueryer MatchCondition with cached result
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest019, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition("(width>=100)", json));
}

/**
 * @tc.name: MediaQueryerGetMediaFeatureTest001
 * @tc.desc: Test MediaQueryer GetMediaFeature
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerGetMediaFeatureTest001, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    queryer.SetSurfaceSize(400, 800);
    queryer.SetColorMode(ColorMode::DARK);
    auto json = queryer.GetMediaFeature();
    ASSERT_NE(json, nullptr);
    EXPECT_EQ(json->GetInt("width", 0), 400);
    EXPECT_EQ(json->GetInt("height", 0), 800);
    EXPECT_TRUE(json->GetBool("dark-mode", false));
}

/**
 * @tc.name: MediaQueryerGetMediaFeatureTest002
 * @tc.desc: Test MediaQueryer GetMediaFeature with light mode
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerGetMediaFeatureTest002, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    queryer.SetSurfaceSize(300, 446);
    queryer.SetColorMode(ColorMode::LIGHT);
    auto json = queryer.GetMediaFeature();
    ASSERT_NE(json, nullptr);
    EXPECT_EQ(json->GetInt("width", 0), 300);
    EXPECT_EQ(json->GetInt("height", 0), 446);
    EXPECT_FALSE(json->GetBool("dark-mode", true));
}

/**
 * @tc.name: MediaQueryerGetMediaFeatureTest003
 * @tc.desc: Test MediaQueryer GetMediaFeature aspect ratio calculation
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerGetMediaFeatureTest003, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    queryer.SetSurfaceSize(400, 200);
    auto json = queryer.GetMediaFeature();
    ASSERT_NE(json, nullptr);
    double aspectRatio = json->GetDouble("aspect-ratio", 0.0);
    EXPECT_NEAR(aspectRatio, 2.0, 0.01);
}

/**
 * @tc.name: MediaQueryerGetMediaFeatureTest004
 * @tc.desc: Test MediaQueryer GetMediaFeature with zero height
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerGetMediaFeatureTest004, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    queryer.SetSurfaceSize(400, 0);
    auto json = queryer.GetMediaFeature();
    ASSERT_NE(json, nullptr);
    double aspectRatio = json->GetDouble("aspect-ratio", 0.0);
    EXPECT_NEAR(aspectRatio, 1.0, 0.01);
}

/**
 * @tc.name: MediaQueryerMatchConditionTest020
 * @tc.desc: Test MediaQueryer MatchCondition with height condition
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest020, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition("(height>=200)", json));
    EXPECT_FALSE(queryer.MatchCondition("(height>=300)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest021
 * @tc.desc: Test MediaQueryer MatchCondition with min-height
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest021, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition("(min-height:200)", json));
    EXPECT_FALSE(queryer.MatchCondition("(min-height:300)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest022
 * @tc.desc: Test MediaQueryer MatchCondition with max-height
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest022, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition("(max-height:400)", json));
    EXPECT_FALSE(queryer.MatchCondition("(max-height:100)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest023
 * @tc.desc: Test MediaQueryer MatchCondition with invalid condition
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest023, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_FALSE(queryer.MatchCondition("invalid_condition", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest024
 * @tc.desc: Test MediaQueryer MatchCondition with aspect-ratio
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest024, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    json->Put("aspect-ratio", 0.5);
    EXPECT_TRUE(queryer.MatchCondition("(aspect-ratio>=0.5)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest025
 * @tc.desc: Test MediaQueryer MatchCondition cached result with updated media feature
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest025, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json1 = JsonUtil::Create(true);
    json1->Put("width", 100);
    json1->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition("(width>=50)", json1));

    auto json2 = JsonUtil::Create(true);
    json2->Put("width", 200);
    json2->Put("height", 400);
    EXPECT_TRUE(queryer.MatchCondition("(width>=50)", json2));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest027
 * @tc.desc: Test MediaQueryer MatchCondition with CSS Level 4 left syntax
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest027, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_FALSE(queryer.MatchCondition("(width>100)", json));
    EXPECT_TRUE(queryer.MatchCondition("(width>=100)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest028
 * @tc.desc: Test MediaQueryer MatchCondition with CSS Level 4 right syntax
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest028, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition("(100<=width)", json));
    EXPECT_FALSE(queryer.MatchCondition("(200<width)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest029
 * @tc.desc: Test MediaQueryer MatchCondition with comma separated conditions
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest029, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    json->Put("orientation", "portrait");
    EXPECT_TRUE(queryer.MatchCondition("(width>=50),(orientation:portrait)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest030
 * @tc.desc: Test MediaQueryer MatchCondition with space handling
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest030, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition(" screen and ( width >= 100 ) ", json));
}
/**
 * @tc.name: MediaQueryerMatchConditionTest031
 * @tc.desc: Test MediaQueryer MatchCondition with viewport height
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest031, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 800);
    json->Put("vertical-viewport-height", 800);
    EXPECT_TRUE(queryer.MatchCondition("(vertical-viewport-height>=800)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest032
 * @tc.desc: Test MediaQueryer MatchCondition with dpi unit
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest032, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    json->Put("resolution", 96);
    EXPECT_TRUE(queryer.MatchCondition("(resolution>=96dpi)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest033
 * @tc.desc: Test MediaQueryer MatchCondition with dpcm unit
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest033, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    json->Put("resolution", 36);
    EXPECT_TRUE(queryer.MatchCondition("(resolution>=36dpcm)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest034
 * @tc.desc: Test MediaQueryer MatchCondition with complex and/or combination
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest034, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 400);
    json->Put("height", 800);
    json->Put("orientation", "portrait");
    EXPECT_TRUE(queryer.MatchCondition("(width>=300)and(height>=446)or(orientation:portrait)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest035
 * @tc.desc: Test MediaQueryer MatchCondition with not modifier and device-type
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest035, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    json->Put("device-type", "tablet");
    EXPECT_TRUE(queryer.MatchCondition("not screen and (device-type:phone)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest036
 * @tc.desc: Test MediaQueryer MatchCondition with wearable device type
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest036, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    json->Put("device-type", "wearable");
    EXPECT_TRUE(queryer.MatchCondition("(device-type:wearable)", json));
    EXPECT_FALSE(queryer.MatchCondition("(device-type:default)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest037
 * @tc.desc: Test MediaQueryer MatchCondition with multiple screen conditions
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest037, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition("screen and (min-width:100) and (max-height:300)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest038
 * @tc.desc: Test MediaQueryer MatchCondition cache with same feature
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest038, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition("(width>=50)", json));
    auto json2 = JsonUtil::Create(true);
    json2->Put("width", 100);
    json2->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition("(width>=50)", json2));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest039
 * @tc.desc: Test MediaQueryer MatchCondition with invalid syntax
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest039, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_FALSE(queryer.MatchCondition("(width>=)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest040
 * @tc.desc: Test MediaQueryer MatchCondition with landscape orientation
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest040, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 400);
    json->Put("height", 200);
    json->Put("orientation", "landscape");
    EXPECT_TRUE(queryer.MatchCondition("(orientation:landscape)", json));
    EXPECT_FALSE(queryer.MatchCondition("(orientation:portrait)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest041
 * @tc.desc: Test MediaQueryer MatchCondition with width greater than
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest041, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 200);
    json->Put("height", 300);
    EXPECT_TRUE(queryer.MatchCondition("(width>100)", json));
    EXPECT_FALSE(queryer.MatchCondition("(width>200)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest042
 * @tc.desc: Test MediaQueryer MatchCondition with width less than
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest042, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition("(width<200)", json));
    EXPECT_FALSE(queryer.MatchCondition("(width<100)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest043
 * @tc.desc: Test MediaQueryer MatchCondition with negative value
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest043, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_FALSE(queryer.MatchCondition("(width>=-100)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest044
 * @tc.desc: Test MediaQueryer MatchCondition with decimal value
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest044, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    json->Put("aspect-ratio", 1.5);
    EXPECT_TRUE(queryer.MatchCondition("(aspect-ratio>=1.5)", json));
}

/**
 * @tc.name: MediaQueryerMatchConditionTest045
 * @tc.desc: Test MediaQueryer MatchCondition with tablet device type
 * @tc.type: FUNC
 */
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest045, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    json->Put("device-type", "tablet");
    EXPECT_TRUE(queryer.MatchCondition("(device-type:tablet)", json));
    EXPECT_FALSE(queryer.MatchCondition("(device-type:phone)", json));
    EXPECT_FALSE(queryer.MatchCondition("(device-type:default)", json));
}

 /**
* @tc.name: MediaQueryerMatchConditionTest051
* @tc.desc: Test MediaQueryer MatchCondition with min-aspect-ratio
* @tc.type: FUNC
*/
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest051, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    json->Put("aspect-ratio", 0.5);
    EXPECT_TRUE(queryer.MatchCondition("(min-aspect-ratio:0.5)", json));
    EXPECT_FALSE(queryer.MatchCondition("(min-aspect-ratio:0.6)", json));
}

/**
* @tc.name: MediaQueryerMatchConditionTest052
* @tc.desc: Test MediaQueryer MatchCondition with max-aspect-ratio
* @tc.type: FUNC
*/
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest052, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    json->Put("aspect-ratio", 0.5);
    EXPECT_TRUE(queryer.MatchCondition("(max-aspect-ratio:0.5)", json));
    EXPECT_TRUE(queryer.MatchCondition("(max-aspect-ratio:1.0)", json));
}

/**
* @tc.name: MediaQueryerMatchConditionTest053
* @tc.desc: Test MediaQueryer MatchCondition with grid condition
* @tc.type: FUNC
*/
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest053, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    json->Put("grid", true);
    EXPECT_FALSE(queryer.MatchCondition("(grid:true)", json));
}

/**
* @tc.name: MediaQueryerMatchConditionTest054
* @tc.desc: Test MediaQueryer MatchCondition hover capability
* @tc.type: FUNC
*/
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest054, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    json->Put("hover", true);
    EXPECT_FALSE(queryer.MatchCondition("(hover:true)", json));
}

/**
* @tc.name: MediaQueryerMatchConditionTest026
* @tc.desc: Test MediaQueryer MatchCondition all and conditions true
* @tc.type: FUNC
*/
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest026, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 400);
    json->Put("height", 800);
    json->Put("orientation", "portrait");
    EXPECT_TRUE(queryer.MatchCondition("(width>=300)and(height>=446)and(orientation:portrait)", json));
}

/**
* @tc.name: MediaQueryerMatchConditionTest055
* @tc.desc: Test MediaQueryer MatchCondition round-screen false
* @tc.type: FUNC
*/
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest055, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    json->Put("round-screen", false);
    EXPECT_FALSE(queryer.MatchCondition("(round-screen:true)", json));
    EXPECT_TRUE(queryer.MatchCondition("(round-screen:false)", json));
}

/**
* @tc.name: MediaQueryerMatchConditionTest046
* @tc.desc: Test MediaQueryer MatchCondition with update cache after feature change
* @tc.type: FUNC
*/
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest046, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json1 = JsonUtil::Create(true);
    json1->Put("width", 100);
    json1->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition("(width>=50)", json1));

    auto json2 = JsonUtil::Create(true);
    json2->Put("width", 200);
    json2->Put("height", 400);
    EXPECT_TRUE(queryer.MatchCondition("(width>=50)", json2));
}

/**
* @tc.name: MediaQueryerGetMediaFeatureTest007
* @tc.desc: Test MediaQueryer GetMediaFeature color mode dark
* @tc.type: FUNC
*/
HWTEST_F(MediaQueryerTest, MediaQueryerGetMediaFeatureTest007, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    queryer.SetSurfaceSize(400, 800);
    queryer.SetColorMode(ColorMode::DARK);
    auto json = queryer.GetMediaFeature();
    ASSERT_NE(json, nullptr);
    EXPECT_TRUE(json->GetBool("dark-mode", false));
}

/**
* @tc.name: MediaQueryerMatchConditionTest047
* @tc.desc: Test MediaQueryer MatchCondition with extremely large width
* @tc.type: FUNC
*/
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest047, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 9999);
    json->Put("height", 200);
    EXPECT_TRUE(queryer.MatchCondition("(width>=5000)", json));
    EXPECT_FALSE(queryer.MatchCondition("(width>=10000)", json));
}

/**
* @tc.name: MediaQueryerMatchConditionTest048
* @tc.desc: Test MediaQueryer MatchCondition with zero values
* @tc.type: FUNC
*/
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest048, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 0);
    json->Put("height", 0);
    EXPECT_FALSE(queryer.MatchCondition("(width>=100)", json));
    EXPECT_FALSE(queryer.MatchCondition("(height>=100)", json));
}

/**
* @tc.name: MediaQueryerMatchConditionTest049
* @tc.desc: Test MediaQueryer MatchCondition with invalid media feature
* @tc.type: FUNC
*/
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest049, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    EXPECT_FALSE(queryer.MatchCondition("(invalid-feature>=100)", json));
}

/**
* @tc.name: MediaQueryerMatchConditionTest050
* @tc.desc: Test MediaQueryer MatchCondition comparison precision
* @tc.type: FUNC
*/
HWTEST_F(MediaQueryerTest, MediaQueryerMatchConditionTest050, TestSize.Level1)
{
    Framework::MediaQueryer queryer;
    auto json = JsonUtil::Create(true);
    json->Put("width", 100);
    json->Put("height", 200);
    json->Put("aspect-ratio", 0.33333);
    EXPECT_TRUE(queryer.MatchCondition("(aspect-ratio>=0.33)", json));
}

} // namespace OHOS::Ace::NG
