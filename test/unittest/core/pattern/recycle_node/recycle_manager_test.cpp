/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "gtest/gtest.h"
#include "gtest/hwext/gtest-ext.h"
#include "gtest/hwext/gtest-tag.h"

#include "core/common/resource/resource_configuration.h"

#define protected public
#define private public

#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/recycle_view/recycle_manager.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class RecycleManagerTest : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    void Clear();

private:
    int32_t GenerateId();
    bool CompareConfig(ConfigurationChange& c1, ConfigurationChange& c2);
    bool ContainConfig(ConfigurationChange& c1, ConfigurationChange& c2);
    int32_t id_ = 100;
};

void RecycleManagerTest::SetUp()
{
    MockPipelineContext::SetUp();
}

void RecycleManagerTest::TearDown()
{
    MockPipelineContext::TearDown();
}

int32_t RecycleManagerTest::GenerateId()
{
    return id_++;
}

bool RecycleManagerTest::CompareConfig(ConfigurationChange& c1, ConfigurationChange& c2)
{
    return c1.colorModeUpdate == c2.colorModeUpdate && c1.languageUpdate == c2.languageUpdate &&
           c1.directionUpdate == c2.directionUpdate && c1.dpiUpdate == c2.dpiUpdate && c1.fontUpdate == c2.fontUpdate &&
           c1.iconUpdate == c2.iconUpdate && c1.skinUpdate == c2.skinUpdate &&
           c1.fontScaleUpdate == c2.fontScaleUpdate && c1.fontWeightScaleUpdate == c2.fontWeightScaleUpdate;
}

bool RecycleManagerTest::ContainConfig(ConfigurationChange& c1, ConfigurationChange& c2)
{
    return c1.colorModeUpdate & c2.colorModeUpdate || c1.languageUpdate & c2.languageUpdate ||
           c1.directionUpdate & c2.directionUpdate || c1.dpiUpdate & c2.dpiUpdate || c1.fontUpdate & c2.fontUpdate ||
           c1.iconUpdate & c2.iconUpdate || c1.skinUpdate & c2.skinUpdate || c1.fontScaleUpdate & c2.fontScaleUpdate ||
           c1.fontWeightScaleUpdate & c2.fontWeightScaleUpdate;
}

void RecycleManagerTest::Clear()
{
    PipelineContext::GetCurrentContext()->recycleManager_->recyclePool_.clear();
}

HWTEST_F(RecycleManagerTest, RecyclePushTest001, TestSize.Level1)
{
    auto child0 = AceType::MakeRefPtr<CustomNode>(GenerateId(), "test");
    auto context = PipelineContext::GetCurrentContext();
    RecycleManager::Push(child0->GetId(), child0);
    ASSERT_EQ(context->GetRecycleManager()->recyclePool_.size(), 1);
    Clear();
}

HWTEST_F(RecycleManagerTest, RecyclePopTest001, TestSize.Level1)
{
    auto child1 = AceType::MakeRefPtr<CustomNode>(GenerateId(), "test");
    auto child2 = AceType::MakeRefPtr<CustomNode>(GenerateId(), "test");
    auto context = PipelineContext::GetCurrentContext();
    RecycleManager::Push(child1->GetId(), child1);
    RecycleManager::Push(child2->GetId(), child2);
    ASSERT_EQ(context->GetRecycleManager()->recyclePool_.size(), 2);

    // pop a invalid node;
    RecycleManager::Pop(103);
    ASSERT_EQ(context->GetRecycleManager()->recyclePool_.size(), 2);

    // pop a valid node;
    RecycleManager::Pop(child1->GetId());
    ASSERT_EQ(context->GetRecycleManager()->recyclePool_.size(), 1);

    // pop after delete
    auto id = child2->GetId();
    child2.Reset();
    RecycleManager::Pop(id);
    ASSERT_EQ(context->GetRecycleManager()->recyclePool_.size(), 0);
    Clear();
}

HWTEST_F(RecycleManagerTest, RecycleEraseTest001, TestSize.Level1)
{
    auto child1 = AceType::MakeRefPtr<CustomNode>(GenerateId(), "test");
    auto child2 = AceType::MakeRefPtr<CustomNode>(GenerateId(), "test");
    auto context = PipelineContext::GetCurrentContext();
    int32_t invalidId = -1000;
    
    //push node
    RecycleManager::Push(child1->GetId(), child1);
    ASSERT_EQ(context->GetRecycleManager()->recyclePool_.size(), 1);
    RecycleManager::Push(child2->GetId(), child2);
    ASSERT_EQ(context->GetRecycleManager()->recyclePool_.size(), 2);

    // erase invalid node;
    RecycleManager::Erase(invalidId);
    ASSERT_EQ(context->GetRecycleManager()->recyclePool_.size(), 2);

    // pop node
    RecycleManager::Pop(child1->GetId());
    RecycleManager::Pop(child2->GetId());
    ASSERT_EQ(context->GetRecycleManager()->recyclePool_.size(), 0);
    Clear();
}

HWTEST_F(RecycleManagerTest, RecycleEraseTest002, TestSize.Level1)
{
    auto child1 = AceType::MakeRefPtr<CustomNode>(GenerateId(), "test");
    auto child2 = AceType::MakeRefPtr<CustomNode>(GenerateId(), "test");
    auto context = PipelineContext::GetCurrentContext();
    
    //push node
    RecycleManager::Push(child1->GetId(), child1);
    ASSERT_EQ(context->GetRecycleManager()->recyclePool_.size(), 1);
    RecycleManager::Push(child2->GetId(), child2);
    ASSERT_EQ(context->GetRecycleManager()->recyclePool_.size(), 2);

    // erase valid node;
    RecycleManager::Erase(child1->GetId());
    ASSERT_EQ(context->GetRecycleManager()->recyclePool_.size(), 1);
    RecycleManager::Erase(child2->GetId());
    ASSERT_EQ(context->GetRecycleManager()->recyclePool_.size(), 0);
    Clear();
}

HWTEST_F(RecycleManagerTest, RecycleConfigTest001, TestSize.Level1)
{
    auto child1 = AceType::MakeRefPtr<CustomNode>(GenerateId(), "test");
    auto child2 = AceType::MakeRefPtr<CustomNode>(GenerateId(), "test");
    auto context = PipelineContext::GetCurrentContext();
    RecycleManager::Push(child1->GetId(), child1);

    ConfigurationChange config1;
    config1.colorModeUpdate = true;
    ConfigurationChange config2;
    config2.languageUpdate = true;
    RecycleManager::Notify(config1);
    auto it = context->recycleManager_->recyclePool_.find(child1->GetId());
    ASSERT_EQ(it->second->config.IsNeedUpdate(), true);
    ASSERT_EQ(CompareConfig(it->second->config, config1), true);
    RecycleManager::Pop(child1->GetId());

    RecycleManager::Push(child1->GetId(), child1);
    RecycleManager::Notify(config1);
    RecycleManager::Push(child2->GetId(), child2);
    RecycleManager::Notify(config2);
    auto it1 = context->recycleManager_->recyclePool_.find(child1->GetId());
    auto it2 = context->recycleManager_->recyclePool_.find(child2->GetId());
    ASSERT_EQ(it1->second->config.IsNeedUpdate(), true);
    ASSERT_EQ(it2->second->config.IsNeedUpdate(), true);
    ASSERT_EQ(ContainConfig(it1->second->config, config1), true);
    ASSERT_EQ(ContainConfig(it1->second->config, config2), true);
    ASSERT_EQ(ContainConfig(it2->second->config, config1), false);
    ASSERT_EQ(ContainConfig(it2->second->config, config2), true);
    Clear();
}
} // namespace OHOS::Ace::NG
