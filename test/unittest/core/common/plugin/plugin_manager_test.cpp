/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#define private public
#define protected public
#include "mock_plugin_utils.h"

#include "core/common/plugin_manager.h"
#include "core/components/plugin/plugin_sub_container.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const int64_t PLUGIN_ID = 10000;
const int32_t PARENT_ID = 1000;
} // namespace
class PluginManagerTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: AddPluginSubContainer001
 * @tc.desc: Verify the AddPluginSubContainer Interface of PluginManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(PluginManagerTest, AddPluginSubContainer001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a PluginManager.
     */
    PluginManager pluginManager;

    /**
     * @tc.steps: step2. Add Plugin Sub Container.
     * @tc.expected: step2. Add Plugin Sub Container success.
     */
    WeakPtr<PipelineContext> context = WeakPtr<PipelineContext>();
    RefPtr<PluginSubContainer> pluginSubContainer = AceType::MakeRefPtr<PluginSubContainer>(context.Upgrade());
    EXPECT_TRUE(pluginSubContainer != nullptr);
    pluginManager.AddPluginSubContainer(PLUGIN_ID, pluginSubContainer);
    EXPECT_TRUE(pluginManager.GetPluginSubContainer(PLUGIN_ID) != nullptr);
    pluginManager.RemovePluginSubContainer(PLUGIN_ID);
    EXPECT_TRUE(pluginManager.GetPluginSubContainer(PLUGIN_ID) == nullptr);

    /**
     * @tc.steps: step3. Add Plugin Sub Container.
     * @tc.expected: step3. When Plugin Sub Container id is exsits ,  Add Plugin Sub Container fail.
     */
    RefPtr<PluginSubContainer> secondPluginSubContainer = AceType::MakeRefPtr<PluginSubContainer>(context.Upgrade());
    EXPECT_TRUE(pluginSubContainer != nullptr);
    pluginManager.AddPluginSubContainer(PLUGIN_ID, pluginSubContainer);
    EXPECT_EQ(pluginManager.GetPluginSubContainer(PLUGIN_ID), pluginSubContainer);
    pluginManager.AddPluginSubContainer(PLUGIN_ID, secondPluginSubContainer);
    EXPECT_EQ(pluginManager.GetPluginSubContainer(PLUGIN_ID), pluginSubContainer);
}

/**
 * @tc.name: AddNonmatchedContainer001
 * @tc.desc: Verify the AddNonmatchedContainer Interface of PluginManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(PluginManagerTest, AddNonmatchedContainer001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a PluginManager.
     */
    PluginManager pluginManager;

    /**
     * @tc.steps: step2. Add Nonmatched Container.
     * @tc.expected: step2. Add Nonmatched Container success.
     */
    WeakPtr<PipelineContext> context = WeakPtr<PipelineContext>();
    RefPtr<PluginSubContainer> pluginSubContainer = AceType::MakeRefPtr<PluginSubContainer>(context.Upgrade());
    EXPECT_TRUE(pluginSubContainer != nullptr);
    pluginManager.AddNonmatchedContainer("PLUGIN_ID", pluginSubContainer);
    EXPECT_TRUE(pluginManager.MatchPluginSubContainerWithPluginId(PLUGIN_ID, "PLUGIN_ID") != nullptr);
    EXPECT_TRUE(pluginManager.GetPluginSubContainer(PLUGIN_ID) != nullptr);
    pluginManager.RemovePluginSubContainer(PLUGIN_ID);
    EXPECT_TRUE(pluginManager.GetPluginSubContainer(PLUGIN_ID) == nullptr);

    /**
     * @tc.steps: step3. Add Plugin Nonmatched Container..
     * @tc.expected: step3. When Plugin Nonmatched Container. id is exsits ,  Add Nonmatched Container. fail.
     */
    RefPtr<PluginSubContainer> secondPluginSubContainer = AceType::MakeRefPtr<PluginSubContainer>(context.Upgrade());
    EXPECT_TRUE(pluginSubContainer != nullptr);
    pluginManager.AddNonmatchedContainer("PLUGIN_ID", pluginSubContainer);
    pluginManager.AddNonmatchedContainer("PLUGIN_ID", secondPluginSubContainer);
    EXPECT_EQ(pluginManager.MatchPluginSubContainerWithPluginId(PLUGIN_ID, "PLUGIN_ID"), pluginSubContainer);
}

/**
 * @tc.name: MatchPluginSubContainerWithPluginId001
 * @tc.desc: Verify the MatchPluginSubContainerWithPluginId Interface of PluginManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(PluginManagerTest, MatchPluginSubContainerWithPluginId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a PluginManager.
     */
    PluginManager pluginManager;

    /**
     * @tc.steps: step2. Match Plugin SubContainer With Plugin Id.
     * @tc.expected: step2. When no Match Plugin SubContainer With Plugin Id return nullptr.
     */
    EXPECT_TRUE(pluginManager.MatchPluginSubContainerWithPluginId(PLUGIN_ID, "PLUGIN_ID") == nullptr);
}

/**
 * @tc.name: GetPluginSubContainerId001
 * @tc.desc: Verify the GetPluginSubContainerId Interface of PluginManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(PluginManagerTest, GetPluginSubContainerId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a PluginManager.
     */
    PluginManager pluginManager;

    /**
     * @tc.steps: step2. Get Plugin SubContainerId.
     * @tc.expected: step2. When the Map is empty ,get the id equals MIN_PLUGIN_SUBCONTAINER_ID.
     */
    auto pluginSubContainerId = pluginManager.GetPluginSubContainerId();
    EXPECT_EQ(pluginSubContainerId, MIN_PLUGIN_SUBCONTAINER_ID);

    /**
     * @tc.steps: step3. Get Plugin SubContainerId.
     * @tc.expected: step3. When the Map is not empty ,get the id by add to the last PluginSubContainerId.
     */
    WeakPtr<PipelineContext> context = WeakPtr<PipelineContext>();
    RefPtr<PluginSubContainer> pluginSubContainer = AceType::MakeRefPtr<PluginSubContainer>(context.Upgrade());
    pluginManager.AddPluginSubContainer(pluginSubContainerId, pluginSubContainer);
    pluginSubContainerId = pluginManager.GetPluginSubContainerId();
    EXPECT_EQ(pluginSubContainerId, MIN_PLUGIN_SUBCONTAINER_ID + 1);
}

/**
 * @tc.name: RemovePluginParentContainer001
 * @tc.desc: Verify the RemovePluginParentContainer Interface of PluginManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(PluginManagerTest, RemovePluginParentContainer001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a PluginManager.
     */
    PluginManager pluginManager;

    /**
     * @tc.steps: step2. Get Plugin SubContainerId.
     * @tc.expected: step2. When the Map is empty add the PluginParentContainer.
     */
    auto pluginSubContainerId = pluginManager.GetPluginSubContainerId();
    EXPECT_EQ(pluginSubContainerId, MIN_PLUGIN_SUBCONTAINER_ID);
    pluginManager.AddPluginParentContainer(pluginSubContainerId, PARENT_ID);

    /**
     * @tc.steps: step3. Add PluginParentContainerId.
     * @tc.expected: step3. When Plugin SubContainer id is exsits ,  Add Plugin Parent Container Id fail.
     */

    pluginManager.AddPluginParentContainer(pluginSubContainerId, PARENT_ID + 1);
    EXPECT_EQ(pluginManager.GetPluginParentContainerId(pluginSubContainerId), PARENT_ID);
    pluginManager.RemovePluginParentContainer(pluginSubContainerId);
    EXPECT_EQ(pluginManager.GetPluginParentContainerId(pluginSubContainerId), 0);
}

/**
 * @tc.name: StartAbility001
 * @tc.desc: Verify the StartAbility Interface of PluginManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(PluginManagerTest, StartAbility001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a PluginManager.
     */
    PluginManager pluginManager;
    auto pluginUtils = std::make_shared<MockPluginUtils>();
    pluginManager.SetAceAbility(nullptr, pluginUtils);

    /**
     * @tc.steps: step2. StartAbility.
     * @tc.expected: step2. return 1.
     */
    auto result = pluginManager.StartAbility("", "", "");
    EXPECT_EQ(result, 1);
}
} // namespace OHOS::Ace