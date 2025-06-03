/*
# Copyright (c) 2025 iSoftStone Information Technology (Group) Co.,Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
*/

#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define protected public
#define private public
#include "core/common/resource/pattern_resource_manager.h"
#include "core/common/resource/resource_object.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class PatternResourceManagerTest : public testing::Test {};

/**
 * @tc.name: PatternResourceManagerTest001
 * @tc.desc: Test PatternResourceManager.
 * @tc.type: FUNC
 */
HWTEST_F(PatternResourceManagerTest, PatternResourceManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. AddResource.
     * @tc.expect: resMap_ size is 3
     */
    auto manager = AceType::MakeRefPtr<PatternResourceManager>();
    auto func = [](const RefPtr<ResourceObject>& resObj) { return; };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    manager->AddResource("key1", resObj, func);
    manager->AddResource("key2", resObj, func);
    manager->AddResource("key3", resObj, func);
    EXPECT_EQ(manager->resMap_.size(), 3);

    /**
     * @tc.steps: step2. RemoveResource witch in map.
     * @tc.expect: resMap_ size is 2
     */
    manager->RemoveResource("key2");
    EXPECT_EQ(manager->resMap_.size(), 2);

    /**
     * @tc.steps: step3. RemoveResource witch not in map.
     * @tc.expect: resMap_ size is 2
     */
    manager->RemoveResource("key4");
    EXPECT_EQ(manager->resMap_.size(), 2);

    /**
     * @tc.steps: step4. ReloadResources.
     * @tc.expect: resKeyArray_ size is 3
     */
    manager->ReloadResources();
    manager->resKeyArray_.push_back("key5");
    manager->ReloadResources();
    EXPECT_EQ(manager->resKeyArray_.size(), 3);
}
} // namespace OHOS::Ace
