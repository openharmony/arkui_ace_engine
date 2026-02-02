/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 
#include "core/components_ng/pattern/form/form_snapshot_util.h"
#include "mock/mock_pixel_map.h"
 
using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class FormSnapshotUtilTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
};
 
void FormSnapshotUtilTest::SetUpTestSuite()
{}
 
void FormSnapshotUtilTest::TearDownTestSuite()
{}
 
void FormSnapshotUtilTest::SetUp()
{}
 
/**
 * @tc.name: FormSnapshotUtilTest_IsTransparent_001
 * @tc.desc: judge whether pixelmap is transparent
 * @tc.type: FUNC
 */
HWTEST_F(FormSnapshotUtilTest, FormSnapshotUtilTest_IsTransparent_001, TestSize.Level1)
{
    EXPECT_TRUE(FormSnapshotUtil::IsTransparent(nullptr));
 
    std::shared_ptr<Media::MockPixelMap> mockPixelMap = std::make_shared<Media::MockPixelMap>();
    EXPECT_CALL(*mockPixelMap, GetWidth()).WillRepeatedly(Return(200));
    EXPECT_CALL(*mockPixelMap, GetHeight()).WillRepeatedly(Return(200));
    EXPECT_EQ(FormSnapshotUtil::IsTransparent(mockPixelMap), true);
}
} // namespace OHOS::Ace::NG