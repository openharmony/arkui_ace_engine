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

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace std;

class MediaQueryTest : public TestNG {};

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
} // namespace OHOS::Ace::NG
