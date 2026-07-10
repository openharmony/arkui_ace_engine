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

/**
 * @tc.name: PatternResourceManagerTest002
 * @tc.desc: Test PatternResourceManager.
 * @tc.type: FUNC
 */
HWTEST_F(PatternResourceManagerTest, PatternResourceManagerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. AddResource.
     * @tc.expect: resMap_ size is 1
     */
    auto manager = AceType::MakeRefPtr<PatternResourceManager>();
    auto func = [](const RefPtr<ResourceObject>& resObj) { return; };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    manager->AddResource("key", resObj, func);
    EXPECT_FALSE(manager->Empty());
}

/**
 * @tc.name: PatternResourceManagerTest003
 * @tc.desc: Test PatternResourceManager.
 * @tc.type: FUNC
 */
HWTEST_F(PatternResourceManagerTest, PatternResourceManagerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. AddResource.
     * @tc.steps: step2. AddResource as same key.
     * @tc.expect: resMap_ size is 1
     */
    auto manager = AceType::MakeRefPtr<PatternResourceManager>();
    auto func = [](const RefPtr<ResourceObject>& resObj) { return; };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    manager->AddResource("key", resObj, func);
    manager->AddResource("key", resObj, func);
    EXPECT_EQ(manager->resKeyArray_.size(), 1);
}

/**
 * @tc.name: PatternResourceManagerTest004
 * @tc.desc: Test ParsePropertyValue with STRING type when ParseResString returns true.
 * @tc.type: FUNC
 */
HWTEST_F(PatternResourceManagerTest, PatternResourceManagerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ResourceObject and PropertyValueBase.
     * @tc.expect: Value is set correctly and ValueType remains UNKNOWN
     */
    std::vector<ResourceObjectParams> params;
    auto manager = AceType::MakeRefPtr<PatternResourceManager>();
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    auto valueBase = AceType::MakeRefPtr<PropertyValueBase>();

    /**
     * @tc.steps: step1. Test ParsePropertyValue with UNKNOWN type.
     * @tc.expect: Value is set correctly
     */
    manager->ParsePropertyValue(resObj, valueBase);
    EXPECT_EQ(valueBase->GetValueType(), ValueType::UNKNOWN);
}

/**
 * @tc.name: PatternResourceManagerTest005
 * @tc.desc: Test ParsePropertyValue with STRING type when ParseResString returns false.
 * @tc.type: FUNC
 */
HWTEST_F(PatternResourceManagerTest, PatternResourceManagerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ResourceObject and PropertyValueBase.
     * @tc.expect: Value is set correctly and ValueType remains STRING
     */
    auto manager = AceType::MakeRefPtr<PatternResourceManager>();
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    auto valueBase = AceType::MakeRefPtr<PropertyValueBase>();

    /**
     * @tc.steps: step1. Test ParsePropertyValue with MEDIA type.
     * @tc.expect: Value is set correctly
     */
    valueBase->SetValueType(ValueType::STRING);
    manager->ParsePropertyValue(resObj, valueBase);
    EXPECT_EQ(valueBase->GetValueType(), ValueType::MEDIA);
}

/**
 * @tc.name: PatternResourceManagerTest006
 * @tc.desc: Test ParsePropertyValue with U16STRING type.
 * @tc.type: FUNC
 */
HWTEST_F(PatternResourceManagerTest, PatternResourceManagerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ResourceObject and PropertyValueBase.
     * @tc.expect: Value is set correctly and ValueType remains U16STRING
     */
    auto manager = AceType::MakeRefPtr<PatternResourceManager>();
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    auto valueBase = AceType::MakeRefPtr<PropertyValueBase>();

    /**
     * @tc.steps: step2. Test ParsePropertyValue with U16STRING type.
     * @tc.expect: Value is set correctly
     */
    valueBase->SetValueType(ValueType::U16STRING);
    manager->ParsePropertyValue(resObj, valueBase);
    EXPECT_EQ(valueBase->GetValueType(), ValueType::U16STRING);
}

/**
 * @tc.name: PatternResourceManagerTest007
 * @tc.desc: Test ParsePropertyValue with COLOR type.
 * @tc.type: FUNC
 */
HWTEST_F(PatternResourceManagerTest, PatternResourceManagerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ResourceObject and PropertyValueBase.
     * @tc.expect: Value is set correctly and ValueType remains COLOR
     */
    auto manager = AceType::MakeRefPtr<PatternResourceManager>();
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    auto valueBase = AceType::MakeRefPtr<PropertyValueBase>();

    /**
     * @tc.steps: step3. Test ParsePropertyValue with COLOR type.
     * @tc.expect: Value is set correctly
     */
    valueBase->SetValueType(ValueType::COLOR);
    manager->ParsePropertyValue(resObj, valueBase);
    EXPECT_EQ(valueBase->GetValueType(), ValueType::COLOR);
}

/**
 * @tc.name: PatternResourceManagerTest008
 * @tc.desc: Test ParsePropertyValue with DOUBLE type.
 * @tc.type: FUNC
 */
HWTEST_F(PatternResourceManagerTest, PatternResourceManagerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ResourceObject and PropertyValueBase.
     * @tc.expect: Value is set correctly and ValueType remains DOUBLE
     */
    auto manager = AceType::MakeRefPtr<PatternResourceManager>();
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    auto valueBase = AceType::MakeRefPtr<PropertyValueBase>();

    /**
     * @tc.steps: step4. Test ParsePropertyValue with DOUBLE type.
     * @tc.expect: Value is set correctly
     */
    valueBase->SetValueType(ValueType::DOUBLE);
    manager->ParsePropertyValue(resObj, valueBase);
    EXPECT_EQ(valueBase->GetValueType(), ValueType::DOUBLE);
}

/**
 * @tc.name: PatternResourceManagerTest009
 * @tc.desc: Test ParsePropertyValue with CALDIMENSION type.
 * @tc.type: FUNC
 */
HWTEST_F(PatternResourceManagerTest, PatternResourceManagerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ResourceObject and PropertyValueBase.
     * @tc.expect: Value is set correctly and ValueType remains CALDIMENSION
     */
    auto manager = AceType::MakeRefPtr<PatternResourceManager>();
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    auto valueBase = AceType::MakeRefPtr<PropertyValueBase>();

    /**
     * @tc.steps: step5. Test ParsePropertyValue with CALDIMENSION type.
     * @tc.expect: Value is set correctly
     */
    valueBase->SetValueType(ValueType::CALDIMENSION);
    manager->ParsePropertyValue(resObj, valueBase);
    EXPECT_EQ(valueBase->GetValueType(), ValueType::CALDIMENSION);
}

/**
 * @tc.name: PatternResourceManagerTest010
 * @tc.desc: Test ParsePropertyValue with FLOAT type.
 * @tc.type: FUNC
 */
HWTEST_F(PatternResourceManagerTest, PatternResourceManagerTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ResourceObject and PropertyValueBase.
     * @tc.expect: Value is set correctly and ValueType remains FLOAT
     */
    auto manager = AceType::MakeRefPtr<PatternResourceManager>();
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    auto valueBase = AceType::MakeRefPtr<PropertyValueBase>();

    /**
     * @tc.steps: step6. Test ParsePropertyValue with FLOAT type.
     * @tc.expect: Value is set correctly
     */

    valueBase->SetValueType(ValueType::FLOAT);
    manager->ParsePropertyValue(resObj, valueBase);
    EXPECT_EQ(valueBase->GetValueType(), ValueType::FLOAT);
}

/**
 * @tc.name: PatternResourceManagerTest011
 * @tc.desc: Test ParsePropertyValue with VECTOR_STRING type.
 * @tc.type: FUNC
 */
HWTEST_F(PatternResourceManagerTest, PatternResourceManagerTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ResourceObject and PropertyValueBase.
     * @tc.expect: Value is set correctly and ValueType remains VECTOR_STRING
     */
    auto manager = AceType::MakeRefPtr<PatternResourceManager>();
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    auto valueBase = AceType::MakeRefPtr<PropertyValueBase>();

    /**
     * @tc.steps: step2. Test ParsePropertyValue with VECTOR_STRING type.
     * @tc.expect: Value is set correctly
     */
    valueBase->SetValueType(ValueType::VECTOR_STRING);
    manager->ParsePropertyValue(resObj, valueBase);
    EXPECT_EQ(valueBase->GetValueType(), ValueType::VECTOR_STRING);
}

/**
 * @tc.name: PatternResourceManagerTest012
 * @tc.desc: Test ParsePropertyValue with unknown type.
 * @tc.type: FUNC
 */
HWTEST_F(PatternResourceManagerTest, PatternResourceManagerTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ResourceObject and PropertyValueBase.
     * @tc.expect: Value is set correctly and ValueType remains UNKNOWN
     */
    auto manager = AceType::MakeRefPtr<PatternResourceManager>();
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    auto valueBase = AceType::MakeRefPtr<PropertyValueBase>();

    /**
     * @tc.steps: step2. Test ParsePropertyValue with unknown type.
     * @tc.expect: Value type remains unchanged
     */
    valueBase->SetValueType(ValueType::UNKNOWN);
    manager->ParsePropertyValue(resObj, valueBase);
    EXPECT_EQ(valueBase->GetValueType(), ValueType::UNKNOWN);
}

/**
 * @tc.name: PatternResourceManagerTest013
 * @tc.desc: Test RemoveResource with TailIndents key - precise removal without clearing entire cache.
 * @tc.type: FUNC
 */
HWTEST_F(PatternResourceManagerTest, PatternResourceManagerTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add TailIndents resources and other properties.
     * @tc.expect: resCacheMap_ size is 3
     */
    auto manager = AceType::MakeRefPtr<PatternResourceManager>();
    auto func = [](const RefPtr<ResourceObject>& resObj) { return; };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    
    manager->AddResource("TailIndents_0", resObj, func);
    manager->AddResource("TailIndents_1", resObj, func);
    manager->AddResource("FontSize", resObj, func);
    manager->AddResCache("TailIndents_0", "50");
    manager->AddResCache("TailIndents_1", "30");
    manager->AddResCache("FontSize", "14");
    EXPECT_EQ(manager->resCacheMap_.size(), 3);

    /**
     * @tc.steps: step2. Remove TailIndents_0 - should use precise removal.
     * @tc.expect: TailIndents_0 cache removed, but FontSize cache preserved
     */
    manager->RemoveResource("TailIndents_0");
    EXPECT_EQ(manager->resMap_.size(), 2);
    EXPECT_EQ(manager->resCacheMap_.size(), 2);  // TailIndents_1 and FontSize preserved
    EXPECT_FALSE(manager->GetResCacheMapByKey("TailIndents_0").empty() == false);
    
    /**
     * @tc.steps: step3. Remove TailIndents_1 - should use precise removal.
     * @tc.expect: TailIndents_1 cache removed, but FontSize cache preserved
     */
    manager->RemoveResource("TailIndents_1");
    EXPECT_EQ(manager->resMap_.size(), 1);
    EXPECT_EQ(manager->resCacheMap_.size(), 1);  // Only FontSize preserved
}

/**
 * @tc.name: PatternResourceManagerTest014
 * @tc.desc: Test RemoveResource with non-TailIndents key - should clear entire cache.
 * @tc.type: FUNC
 */
HWTEST_F(PatternResourceManagerTest, PatternResourceManagerTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add multiple properties including TailIndents.
     * @tc.expect: resCacheMap_ size is 3
     */
    auto manager = AceType::MakeRefPtr<PatternResourceManager>();
    auto func = [](const RefPtr<ResourceObject>& resObj) { return; };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    
    manager->AddResource("TailIndents_0", resObj, func);
    manager->AddResource("FontSize", resObj, func);
    manager->AddResource("FontColor", resObj, func);
    manager->AddResCache("TailIndents_0", "50");
    manager->AddResCache("FontSize", "14");
    manager->AddResCache("FontColor", "#FF000000");
    EXPECT_EQ(manager->resCacheMap_.size(), 3);

    /**
     * @tc.steps: step2. Remove FontSize - should clear entire cache (backward compatible).
     * @tc.expect: Entire cache cleared
     */
    manager->RemoveResource("FontSize");
    EXPECT_EQ(manager->resMap_.size(), 2);
    EXPECT_EQ(manager->resCacheMap_.size(), 0);  // Entire cache cleared
}

/**
 * @tc.name: PatternResourceManagerTest015
 * @tc.desc: Test RemoveResource with TailIndents key not in cache.
 * @tc.type: FUNC
 */
HWTEST_F(PatternResourceManagerTest, PatternResourceManagerTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add resources with cache.
     * @tc.expect: resCacheMap_ size is 2
     */
    auto manager = AceType::MakeRefPtr<PatternResourceManager>();
    auto func = [](const RefPtr<ResourceObject>& resObj) { return; };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    
    manager->AddResource("TailIndents_0", resObj, func);
    manager->AddResource("FontSize", resObj, func);
    manager->AddResCache("TailIndents_0", "50");
    manager->AddResCache("FontSize", "14");
    EXPECT_EQ(manager->resCacheMap_.size(), 2);

    /**
     * @tc.steps: step2. Remove TailIndents_1 (not in cache).
     * @tc.expect: Cache unchanged
     */
    manager->RemoveResource("TailIndents_1");
    EXPECT_EQ(manager->resMap_.size(), 2);
    EXPECT_EQ(manager->resCacheMap_.size(), 2);  // Cache unchanged
}

/**
 * @tc.name: PatternResourceManagerTest016
 * @tc.desc: Test RemoveResource with mixed TailIndents and non-TailIndents keys.
 * @tc.type: FUNC
 */
HWTEST_F(PatternResourceManagerTest, PatternResourceManagerTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add multiple TailIndents and other properties.
     * @tc.expect: resCacheMap_ size is 4
     */
    auto manager = AceType::MakeRefPtr<PatternResourceManager>();
    auto func = [](const RefPtr<ResourceObject>& resObj) { return; };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    
    manager->AddResource("TailIndents_0", resObj, func);
    manager->AddResource("TailIndents_1", resObj, func);
    manager->AddResource("FontSize", resObj, func);
    manager->AddResource("FontColor", resObj, func);
    manager->AddResCache("TailIndents_0", "50");
    manager->AddResCache("TailIndents_1", "30");
    manager->AddResCache("FontSize", "14");
    manager->AddResCache("FontColor", "#FF000000");
    EXPECT_EQ(manager->resCacheMap_.size(), 4);

    /**
     * @tc.steps: step2. Remove TailIndents_0 - precise removal.
     * @tc.expect: TailIndents_0 cache removed, others preserved
     */
    manager->RemoveResource("TailIndents_0");
    EXPECT_EQ(manager->resCacheMap_.size(), 3);  // TailIndents_1, FontSize, FontColor preserved
    
    /**
     * @tc.steps: step3. Remove TailIndents_1 - precise removal.
     * @tc.expect: TailIndents_1 cache removed, others preserved
     */
    manager->RemoveResource("TailIndents_1");
    EXPECT_EQ(manager->resCacheMap_.size(), 2);  // FontSize, FontColor preserved
    
    /**
     * @tc.steps: step4. Remove FontSize - clear entire cache.
     * @tc.expect: Entire cache cleared
     */
    manager->RemoveResource("FontSize");
    EXPECT_EQ(manager->resCacheMap_.size(), 0);  // Entire cache cleared
}

/**
 * @tc.name: PatternResourceManagerTest017
 * @tc.desc: Test RemoveResource with TailIndents_ key prefix matching.
 * @tc.type: FUNC
 */
HWTEST_F(PatternResourceManagerTest, PatternResourceManagerTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add resources with various key patterns.
     * @tc.expect: resCacheMap_ size is 3
     */
    auto manager = AceType::MakeRefPtr<PatternResourceManager>();
    auto func = [](const RefPtr<ResourceObject>& resObj) { return; };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    
    manager->AddResource("TailIndents_0", resObj, func);
    manager->AddResource("TailIndents_10", resObj, func);
    manager->AddResource("FontSize", resObj, func);
    manager->AddResCache("TailIndents_0", "50");
    manager->AddResCache("TailIndents_10", "100");
    manager->AddResCache("FontSize", "14");
    EXPECT_EQ(manager->resCacheMap_.size(), 3);

    /**
     * @tc.steps: step2. Remove TailIndents_0 and TailIndents_10.
     * @tc.expect: Both TailIndents removed precisely, FontSize preserved
     */
    manager->RemoveResource("TailIndents_0");
    EXPECT_EQ(manager->resCacheMap_.size(), 2);  // TailIndents_10, FontSize preserved
    
    manager->RemoveResource("TailIndents_10");
    EXPECT_EQ(manager->resCacheMap_.size(), 1);  // Only FontSize preserved
}
} // namespace OHOS::Ace
