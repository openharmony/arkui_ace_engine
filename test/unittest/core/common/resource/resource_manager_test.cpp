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
#include "gtest/gtest.h"
#include "base/utils/resource_configuration.h"

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
constexpr int32_t DEFAULT_INSTANCE_ID = 0;

std::string MakeCacheKey(const std::string& bundleName, const std::string& moduleName, int32_t instanceId)
{
    return bundleName + "." + moduleName + "." + std::to_string(instanceId);
}
}
class ResourceManagerTest : public testing::Test {};

/**
 * @tc.name: ResourceManagerTest001
 * @tc.desc: Test resourceManager.
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
    ResourceManager::GetInstance().AddResourceAdapter("", "", DEFAULT_INSTANCE_ID, resourceAdapter);
    EXPECT_EQ(ResourceManager::GetInstance().resourceAdapters_.size(), 1);

    /**
     * @tc.steps: step3. Create a resource object.
     * @tc.steps: step4. Add to resource manager.
     * @tc.expect: Will create a new resourceAdapter with bundleName and moduleName and will
        restore in ResourceManager
     */
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    auto resourceObject = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, DEFAULT_INSTANCE_ID);
    auto resAdapterCreate = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
    EXPECT_EQ(ResourceManager::GetInstance().cache_.size(), 1);
    EXPECT_NE(ResourceManager::GetInstance().cache_.find(MakeCacheKey(bundleName, moduleName, DEFAULT_INSTANCE_ID)),
        ResourceManager::GetInstance().cache_.end());

    /**
     * @tc.steps: step5. Get resource adapter by bundleName and moduleName.
     * @tc.expect: The resourceAdapter is equal to the adapter create in last step.
     */
    auto resAdapterGet = ResourceManager::GetInstance().GetResourceAdapter(bundleName, moduleName, DEFAULT_INSTANCE_ID);
    EXPECT_EQ(resAdapterCreate, resAdapterGet);

    /**
     * @tc.steps: step6. Delete resourceAdapter by bundleName and moduleName.
     * @tc.expect: The resourceAdapter of bundleName and moduleName is removed.
     */
    ResourceManager::GetInstance().RemoveResourceAdapter(bundleName, moduleName, DEFAULT_INSTANCE_ID);
    EXPECT_EQ(ResourceManager::GetInstance().resourceAdapters_.size(), 1);
    EXPECT_EQ(ResourceManager::GetInstance().resourceAdapters_.find(
                  MakeCacheKey(bundleName, moduleName, DEFAULT_INSTANCE_ID)),
        ResourceManager::GetInstance().resourceAdapters_.end());

    /**
     * @tc.steps: step7. Clear resource manager.
     * @tc.expect: The resourceAdapters_ is empty.
     */
    ResourceManager::GetInstance().Reset();
    EXPECT_FALSE(ResourceManager::GetInstance().resourceAdapters_.empty());

    /**
     * @tc.steps: step8. Get resourceAdapter with empty bundleName and moduleName.
     * @tc.expect: true.
     */
    EXPECT_EQ(ResourceManager::GetInstance().GetResourceAdapter(DEFAULT_INSTANCE_ID), resourceAdapter);

    ResourceManager::GetInstance().resourceAdapters_.clear();
}

/**
 * @tc.name: ResourceManagerTest002
 * @tc.desc: Test resourceManager.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceManagerTest, ResourceManagerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create empty bundleName and moduleName.
     * @tc.steps: step2. call MakeCacheKey.
     * @tc.expect: The key is empty.
     */
    std::string bundleName = "";
    std::string moduleName = "";
    std::string key = ResourceManager::GetInstance().MakeCacheKey(bundleName, moduleName, DEFAULT_INSTANCE_ID);
    EXPECT_EQ(key, std::to_string(DEFAULT_INSTANCE_ID));

    /**
     * @tc.steps: step3. create bundleName and moduleName.
     * @tc.steps: step4. call MakeCacheKey.
     * @tc.expect: The key is bundleName.moduleName.
     */
    bundleName = "com.example.test";
    moduleName = "entry";
    key = ResourceManager::GetInstance().MakeCacheKey(bundleName, moduleName, DEFAULT_INSTANCE_ID);
    EXPECT_EQ(key, MakeCacheKey(bundleName, moduleName, DEFAULT_INSTANCE_ID));

    /**
     * @tc.steps: step5. create bundleName and moduleName.
     * @tc.steps: step6. call MakeCacheKey.
     * @tc.expect: The key is bundleName.moduleName.
     */
    bundleName = "com.example.test";
    moduleName = "";
    key = ResourceManager::GetInstance().MakeCacheKey(bundleName, moduleName, DEFAULT_INSTANCE_ID);
    EXPECT_EQ(key, MakeCacheKey(bundleName, moduleName, DEFAULT_INSTANCE_ID));

    /**
     * @tc.steps: step7. create bundleName and moduleName.
     * @tc.steps: step8. call MakeCacheKey.
     * @tc.expect: The key is bundleName.moduleName.
     */
    bundleName = "";
    moduleName = "entry";
    key = ResourceManager::GetInstance().MakeCacheKey(bundleName, moduleName, DEFAULT_INSTANCE_ID);
    EXPECT_EQ(key, MakeCacheKey(bundleName, moduleName, DEFAULT_INSTANCE_ID));

    ResourceManager::GetInstance().Reset();
    ResourceManager::GetInstance().resourceAdapters_.clear();
}

/**
 * @tc.name: ResourceManagerTest003
 * @tc.desc: Test resourceManager.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceManagerTest, ResourceManagerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bundleName and moduleName.
     * @tc.steps: step2. create ResourceObject
     * @tc.steps: step3. create ResourceAdapter
     * @tc.steps: step4. IsResourceAdapterRecord
     * @tc.expect: true.
     */
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    auto resourceObject = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, DEFAULT_INSTANCE_ID);
    auto resAdapterCreate = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
    auto result = ResourceManager::GetInstance().IsResourceAdapterRecord(bundleName, moduleName, DEFAULT_INSTANCE_ID);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step5. call IsResourceAdapterRecord with empty bundleName and moduleName
     * @tc.expect: false.
     */
    result = ResourceManager::GetInstance().IsResourceAdapterRecord("", "", DEFAULT_INSTANCE_ID);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step6. remove other resourceAdapter from resourceManager
     * @tc.steps: step7. call IsResourceAdapterRecord with bundleName and moduleName
     * @tc.expect: true.
     */
    ResourceManager::GetInstance().RemoveResourceAdapter("", "", DEFAULT_INSTANCE_ID);
    result = ResourceManager::GetInstance().IsResourceAdapterRecord(bundleName, moduleName, DEFAULT_INSTANCE_ID);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step8. remove resourceAdapter from resourceManager
     * @tc.steps: step9. call IsResourceAdapterRecord with bundleName and moduleName
     * @tc.expect: false.
     */
    ResourceManager::GetInstance().RemoveResourceAdapter(bundleName, moduleName, DEFAULT_INSTANCE_ID);
    result = ResourceManager::GetInstance().IsResourceAdapterRecord(bundleName, moduleName, DEFAULT_INSTANCE_ID);
    EXPECT_FALSE(result);

    ResourceManager::GetInstance().Reset();
    ResourceManager::GetInstance().resourceAdapters_.clear();
}

/**
 * @tc.name: ResourceManagerTest004
 * @tc.desc: Test resourceManager.
 * @tc.type: FUNC
 */
HWTEST_F(ResourceManagerTest, ResourceManagerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bundleName and moduleName.
     * @tc.steps: step2. create ResourceObject
     * @tc.steps: step3. create ResourceAdapter
     * @tc.steps: step4. IsResourceAdapterRecord
     * @tc.expect: true.
     */
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    auto resourceObject = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, DEFAULT_INSTANCE_ID);
    auto resAdapterCreate = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
    auto result = ResourceManager::GetInstance().IsResourceAdapterRecord(bundleName, moduleName, DEFAULT_INSTANCE_ID);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step4. create new bundleName and moduleName
     * @tc.steps: step5. call RegisterMainResourceAdapter
     * @tc.steps: step6. call IsResourceAdapterRecord
     * @tc.expect: true.
     */
    bundleName = "com.example.test";
    moduleName = "entry2";
    ResourceManager::GetInstance().RegisterMainResourceAdapter(
        bundleName, moduleName, DEFAULT_INSTANCE_ID, resAdapterCreate);
    result = ResourceManager::GetInstance().IsResourceAdapterRecord(bundleName, moduleName, DEFAULT_INSTANCE_ID);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step7. create ResourceConfiguration
     * @tc.steps: step8. call UpdateResourceConfig
     * @tc.expect: resourceAdapters_ has a element.
     */
    ResourceConfiguration resConfig;
    ResourceManager::GetInstance().UpdateResourceConfig(resConfig);
    EXPECT_EQ(ResourceManager::GetInstance().resourceAdapters_.size(), 1);

    /**
     * @tc.steps: step9. create ColorMode
     * @tc.steps: step10. call UpdateResourceConfig
     * @tc.expect: resourceAdapters_ has a element.
     */
    ColorMode colorMode = ColorMode::DARK;
    ResourceManager::GetInstance().UpdateColorMode(colorMode);
    EXPECT_EQ(ResourceManager::GetInstance().resourceAdapters_.size(), 1);
}
} // namespace OHOS::Ace