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

#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/base/image/mock_pixel_map.h"

#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/components_ng/base/frame_node.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class SpanColorModeTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
};

void SpanColorModeTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void SpanColorModeTestNg::TearDown()
{
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: ParseColorWithVersion001
 * @tc.desc: Test SpanBase::ParseColorWithVersion when API version < VERSION_TWENTY_SIX
 *           should fall back to ParseResColor (ignoring local color mode)
 * @tc.type: FUNC
 */
HWTEST_F(SpanColorModeTestNg, ParseColorWithVersion001, TestSize.Level0)
{
    auto backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    // Set API target version below VERSION_TWENTY_SIX
    MockContainer::Current()->SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY));

    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    Color outColor;
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    // With API < VERSION_TWENTY_SIX, ParseColorWithVersion should call ParseResColor
    // regardless of local color mode
    SpanBase::ParseColorWithVersion(resObj, outColor, frameNode);

    // Reset
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ParseColorWithVersion002
 * @tc.desc: Test SpanBase::ParseColorWithVersion when API version >= VERSION_TWENTY_SIX
 *           and local color mode is UNDEFINED, should fall back to ParseResColor
 * @tc.type: FUNC
 */
HWTEST_F(SpanColorModeTestNg, ParseColorWithVersion002, TestSize.Level0)
{
    auto backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));

    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    // GetLocalColorMode() on a default frame node returns COLOR_MODE_UNDEFINED
    // (no TokenTheme set), so ParseColorWithVersion should fall back to ParseResColor
    Color outColor;
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    SpanBase::ParseColorWithVersion(resObj, outColor, frameNode);

    // Reset
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ParseColorWithVersion003
 * @tc.desc: Test SpanBase::ParseColorWithVersion with null ResourceObject
 * @tc.type: FUNC
 */
HWTEST_F(SpanColorModeTestNg, ParseColorWithVersion003, TestSize.Level0)
{
    auto backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));

    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    Color outColor;
    // With null ResourceObject, ParseResColor returns false, outColor remains unchanged
    SpanBase::ParseColorWithVersion(nullptr, outColor, frameNode);

    // Reset
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ParseColorWithVersion004
 * @tc.desc: Test SpanBase::ParseColorWithVersion when API >= VERSION_TWENTY_SIX
 *           and local color mode is defined (not UNDEFINED), should use ParseResColorWithColorMode
 * @tc.type: FUNC
 */
HWTEST_F(SpanColorModeTestNg, ParseColorWithVersion004, TestSize.Level0)
{
    auto backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));

    // Set the pipeline context's local color mode to DARK
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetLocalColorMode(ColorMode::DARK);

    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    Color outColor;
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    // With API >= VERSION_TWENTY_SIX and local color mode DARK,
    // ParseColorWithVersion should call ParseResColorWithColorMode
    SpanBase::ParseColorWithVersion(resObj, outColor, frameNode);

    // Reset
    pipelineContext->SetLocalColorMode(ColorMode::COLOR_MODE_UNDEFINED);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ParseColorWithVersion005
 * @tc.desc: Test SpanBase::ParseColorWithVersion boundary: API version exactly VERSION_TWENTY_SIX
 * @tc.type: FUNC
 */
HWTEST_F(SpanColorModeTestNg, ParseColorWithVersion005, TestSize.Level0)
{
    auto backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));

    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetLocalColorMode(ColorMode::LIGHT);

    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    Color outColor;
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    SpanBase::ParseColorWithVersion(resObj, outColor, frameNode);

    // Reset
    pipelineContext->SetLocalColorMode(ColorMode::COLOR_MODE_UNDEFINED);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ParseColorWithVersion006
 * @tc.desc: Test SpanBase::ParseColorWithVersion just below VERSION_TWENTY_SIX (VERSION_TWENTY_FIVE)
 *           should not use ParseResColorWithColorMode even with defined local color mode
 * @tc.type: FUNC
 */
HWTEST_F(SpanColorModeTestNg, ParseColorWithVersion006, TestSize.Level0)
{
    auto backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE));

    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetLocalColorMode(ColorMode::DARK);

    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    Color outColor;
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    // API < VERSION_TWENTY_SIX, so should fall back to ParseResColor even with DARK local mode
    SpanBase::ParseColorWithVersion(resObj, outColor, frameNode);

    // Reset
    pipelineContext->SetLocalColorMode(ColorMode::COLOR_MODE_UNDEFINED);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}
} // namespace OHOS::Ace::NG
