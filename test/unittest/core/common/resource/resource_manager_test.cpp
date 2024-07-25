/*
# Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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

#define protected public
#define private public
#include "base/log/log.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_object.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
std::string MakeCacheKey(const std::string& bundleName, const std::string& moduleName)
{
    return bundleName + "." + moduleName;
}
}
class ResourceManagerTest : public testing::Test {};

/**
 * @tc.name: CastToRegisterTest001
 * @tc.desc: Test cast to register.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceManagerTest, ResourceManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ResourceAdapter.
     * @tc.steps: step2. Add to resource manager.
     * @tc.expect: resourceAdapters_ in ResourceManager is 1 (contains the default adapter)
     */
    auto resourceAdapter = ResourceAdapter::Create();
    ResourceManager::GetInstance().AddResourceAdapter("", "", resourceAdapter);
    EXPECT_EQ(ResourceManager::GetInstance().resourceAdapters_.size(), 1);

    /**
     * @tc.steps: step3. Create a resource object.
     * @tc.steps: step4. Add to resource manager.
     * @tc.expect: Will create a new resourceAdapter with bundleName and moduleName and will
        restore in ResourceManager
     */
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    auto resourceObject = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName);
    auto resAdapterCreate = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
    EXPECT_EQ(ResourceManager::GetInstance().cache_.size(), 1);
    EXPECT_NE(ResourceManager::GetInstance().cache_.find(MakeCacheKey(bundleName, moduleName)),
        ResourceManager::GetInstance().cache_.end());

    /**
     * @tc.steps: step5. Get resource adapter by bundleName and moduleName.
     * @tc.expect: The resourceAdapter is equal to the adapter create in last step.
     */
    auto resAdapterGet = ResourceManager::GetInstance().GetResourceAdapter(bundleName, moduleName);
    EXPECT_EQ(resAdapterCreate, resAdapterGet);

    /**
     * @tc.steps: step6. Delete resourceAdapter by bundleName and moduleName.
     * @tc.expect: The resourceAdapter of bundleName and moduleName is removed.
     */
    ResourceManager::GetInstance().RemoveResourceAdapter(bundleName, moduleName);
    EXPECT_EQ(ResourceManager::GetInstance().resourceAdapters_.size(), 1);
    EXPECT_EQ(ResourceManager::GetInstance().resourceAdapters_.find(MakeCacheKey(bundleName, moduleName)),
        ResourceManager::GetInstance().resourceAdapters_.end());

    /**
     * @tc.steps: step7. Clear resource manager.
     * @tc.expect: The resourceAdapters_ is empty.
     */
    ResourceManager::GetInstance().Reset();
    EXPECT_FALSE(ResourceManager::GetInstance().resourceAdapters_.empty());
}
} // namespace OHOS::Ace