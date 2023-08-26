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

#include <csignal>
#include <memory>
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_font_manager.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/font_manager.h"
#include "core/common/watch_dog.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline/pipeline_context.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using ::testing::_;

namespace OHOS::Ace {
namespace {
const std::string FIRST_FRAME_NODE = "TabContent";
constexpr int32_t NODE_ID_0 = 0;

RefPtr<NG::FrameNode> CreateNodeAndWrapper(const std::string& tag, int32_t nodeId)
{
    auto node = NG::FrameNode::CreateFrameNode(tag, nodeId, AceType::MakeRefPtr<NG::Pattern>());
    return node;
}
} // namespace
class FontManagerTestNG : public testing::Test {};

/**
 * @tc.name: FontManagerTest001
 * @tc.desc: Verify the RegisterCallbackNG.
 * @tc.type: FUNC
 */
HWTEST_F(FontManagerTestNG, FontManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FontManager object.
     */
    auto fontManager = MockFontManager::Create();
    std::string familyName = "sans-serif";
    std::string familySrc = "/usr/share/fonts/sans-serif.ttf";

    /**
     * @tc.steps: step2. Call RegisterCallbackNG.
     */
    auto node = CreateNodeAndWrapper(FIRST_FRAME_NODE, NODE_ID_0);
    auto callback = []() -> void {};
    auto retFlag = fontManager->RegisterCallbackNG(node, familyName, callback);
    EXPECT_TRUE(fontManager->fontLoaders_.empty());
    EXPECT_FALSE(retFlag);
}

/**
 * @tc.name: FontManagerTest002
 * @tc.desc: Verify the AddFontNodeNG.
 * @tc.type: FUNC
 */
HWTEST_F(FontManagerTestNG, FontManagerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FontManager object.
     */
    auto fontManager = MockFontManager::Create();
    EXPECT_TRUE(fontManager->fontNodesNG_.empty());

    /**
     * @tc.steps: step2. Call AddFontNodeNG.
     * @tc.expect: fontNodesNG_ is empty for the fontLoader_ is empty.
     */
    auto node = CreateNodeAndWrapper(FIRST_FRAME_NODE, NODE_ID_0);
    fontManager->AddFontNodeNG(node);
    EXPECT_FALSE(fontManager->fontNodesNG_.empty());
}

/**
 * @tc.name: FontManagerTest003
 * @tc.desc: Verify the RemoveFontNodeNG.
 * @tc.type: FUNC
 */
HWTEST_F(FontManagerTestNG, FontManagerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FontManager object.
     */
    auto fontManager = MockFontManager::Create();

    /**
     * @tc.steps: step2. Call AddFontNodeNG.
     * @tc.expect: fontNodesNG_ is not empty.
     */
    auto node = CreateNodeAndWrapper(FIRST_FRAME_NODE, NODE_ID_0);
    fontManager->AddFontNodeNG(node);
    EXPECT_FALSE(fontManager->fontNodesNG_.empty());

    /**
     * @tc.steps: step3. Call RemoveFontNodeNG.
     * @tc.expect: fontNodesNG_ is empty.
     */
    fontManager->RemoveFontNodeNG(node);
    EXPECT_TRUE(fontManager->fontNodesNG_.empty());
}

/**
 * @tc.name: FontManagerTest003
 * @tc.desc: Verify the RemoveFontNodeNG.
 * @tc.type: FUNC
 */
HWTEST_F(FontManagerTestNG, FontManagerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FontManager object.
     */
    auto fontManager = MockFontManager::Create();
    EXPECT_TRUE(fontManager->variationNodesNG_.empty());

    /**
     * @tc.steps: step2. Call AddVariationNodeNG.
     * @tc.expect: variationNodesNG_ is not empty.
     */
    auto node = CreateNodeAndWrapper(FIRST_FRAME_NODE, NODE_ID_0);
    fontManager->AddVariationNodeNG(node);
    EXPECT_FALSE(fontManager->variationNodesNG_.empty());

    /**
     * @tc.steps: step3. Call RemoveVariationNodeNG.
     * @tc.expect: variationNodesNG_ is empty.
     */
    fontManager->RemoveVariationNodeNG(node);
    EXPECT_TRUE(fontManager->fontNodesNG_.empty());
}
} // namespace OHOS::Ace
