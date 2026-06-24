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

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_font_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"
#undef private
#undef protected

#include "base/memory/ace_type.h"
#include "core/components/badge/badge_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/badge/badge_pattern.h"
#include "core/components_ng/property/property.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {

constexpr char BADGE_TAG[] = "Badge";
constexpr int32_t BADGE_NODE_ID = 1;

class TestBadgeFrameNode : public FrameNode {
    DECLARE_ACE_TYPE(TestBadgeFrameNode, FrameNode);

public:
    TestBadgeFrameNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : FrameNode(tag, nodeId, pattern)
    {}

    void MarkDirtyNode(PropertyChangeFlag extraFlag) override
    {
        markDirtyCalled_ = true;
        lastDirtyFlag_ = extraFlag;
        FrameNode::MarkDirtyNode(extraFlag);
    }

    void ResetCapturedDirty()
    {
        markDirtyCalled_ = false;
        lastDirtyFlag_ = PROPERTY_UPDATE_NORMAL;
    }

    bool IsMarkDirtyCalled() const
    {
        return markDirtyCalled_;
    }

    PropertyChangeFlag GetLastDirtyFlag() const
    {
        return lastDirtyFlag_;
    }

private:
    bool markDirtyCalled_ { false };
    PropertyChangeFlag lastDirtyFlag_ { PROPERTY_UPDATE_NORMAL };
};

RefPtr<TestBadgeFrameNode> CreateBadgeHost(const RefPtr<BadgePattern>& pattern)
{
    auto host = AceType::MakeRefPtr<TestBadgeFrameNode>(BADGE_TAG, BADGE_NODE_ID, pattern);
    pattern->AttachToFrameNode(host);
    return host;
}

} // namespace

class BadgeWithThemeTestNg : public TestNG {
public:
    static void SetUpTestSuite()
    {
        TestNG::SetUpTestSuite();
    }

    static void TearDownTestSuite()
    {
        TestNG::TearDownTestSuite();
    }

    void SetUp() override
    {
        TestNG::SetUp();
    }

    void TearDown() override
    {
        TestNG::TearDown();
    }
};

/**
 * @tc.name: BadgeOnThemeScopeUpdate001
 * @tc.desc: TDD: Should return false when host is null (CHECK_NULL_RETURN branch).
 * @tc.type: FUNC
 */
HWTEST_F(BadgeWithThemeTestNg, BadgeOnThemeScopeUpdate001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<BadgePattern>();
    EXPECT_FALSE(pattern->OnThemeScopeUpdate(0));
}

/**
 * @tc.name: BadgeOnThemeScopeUpdate002
 * @tc.desc: TDD: For API < 26, should return false and must not call MarkDirtyNode.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeWithThemeTestNg, BadgeOnThemeScopeUpdate002, TestSize.Level1)
{
    auto backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE));

    auto pattern = AceType::MakeRefPtr<BadgePattern>();
    auto host = CreateBadgeHost(pattern);
    ASSERT_NE(host, nullptr);
    host->ResetCapturedDirty();

    EXPECT_FALSE(pattern->OnThemeScopeUpdate(1));
    EXPECT_FALSE(host->IsMarkDirtyCalled());

    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: BadgeOnThemeScopeUpdate003
 * @tc.desc: TDD: Following Gauge behavior, for API >= 26 it should call MarkDirtyNode(PROPERTY_UPDATE_RENDER)
 *          and return true.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeWithThemeTestNg, BadgeOnThemeScopeUpdate003, TestSize.Level1)
{
    auto backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));

    auto pattern = AceType::MakeRefPtr<BadgePattern>();
    auto host = CreateBadgeHost(pattern);
    ASSERT_NE(host, nullptr);
    host->ResetCapturedDirty();

    const bool ret = pattern->OnThemeScopeUpdate(1);

    EXPECT_TRUE(host->IsMarkDirtyCalled());
    EXPECT_EQ(host->GetLastDirtyFlag(), PROPERTY_UPDATE_RENDER);
    EXPECT_TRUE(ret);

    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: BadgeThemeGetBadgeCircleSize001
 * @tc.desc: TDD: GetBadgeCircleSize returns badgeSize_ when fallbackLineSpacingStyleOptimizeFlag is false.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeWithThemeTestNg, BadgeThemeGetBadgeCircleSize001, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<BadgeTheme>();
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto backupApiVersion = pipeline->GetApiTargetVersion();
    
    auto fontManager = AceType::MakeRefPtr<MockFontManager>();
    pipeline->fontManager_ = fontManager;
    fontManager->fallbackLineSpacingStyleOptimizeFlag_ = false;
    pipeline->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));

    auto result = theme->GetBadgeCircleSize();
    EXPECT_EQ(result, Dimension(16.0_vp));

    pipeline->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: BadgeThemeGetBadgeCircleSize002
 * @tc.desc: TDD: GetBadgeCircleSize returns badgeSizeForMinorLanguage_ when conditions are met.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeWithThemeTestNg, BadgeThemeGetBadgeCircleSize002, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<BadgeTheme>();
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto backupApiVersion = pipeline->GetApiTargetVersion();

    auto fontManager = AceType::MakeRefPtr<MockFontManager>();
    pipeline->fontManager_ = fontManager;
    fontManager->fallbackLineSpacingStyleOptimizeFlag_ = true;
    pipeline->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));

    auto result = theme->GetBadgeCircleSize();
    EXPECT_EQ(result, Dimension(18.0_vp));

    pipeline->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: BadgeThemeGetBadgeCircleSize003
 * @tc.desc: TDD: GetBadgeCircleSize returns badgeSize_ when API version < 26.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeWithThemeTestNg, BadgeThemeGetBadgeCircleSize003, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<BadgeTheme>();
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto backupApiVersion = pipeline->GetApiTargetVersion();

    auto fontManager = AceType::MakeRefPtr<MockFontManager>();
    pipeline->fontManager_ = fontManager;
    fontManager->fallbackLineSpacingStyleOptimizeFlag_ = true;
    pipeline->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE));

    auto result = theme->GetBadgeCircleSize();
    EXPECT_EQ(result, Dimension(16.0_vp));

    pipeline->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: BadgeThemeGetBadgeCircleSize004
 * @tc.desc: TDD: GetBadgeCircleSize returns badgeSize_ when flag=false but API<26.
 * @tc.type: FUNC
 */
HWTEST_F(BadgeWithThemeTestNg, BadgeThemeGetBadgeCircleSize004, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<BadgeTheme>();
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto backupApiVersion = pipeline->GetApiTargetVersion();

    auto fontManager = AceType::MakeRefPtr<MockFontManager>();
    pipeline->fontManager_ = fontManager;
    fontManager->fallbackLineSpacingStyleOptimizeFlag_ = false;
    pipeline->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE));

    EXPECT_FALSE(pipeline->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX));
    auto result = theme->GetBadgeCircleSize();
    EXPECT_EQ(result, Dimension(16.0_vp));

    pipeline->SetApiTargetVersion(backupApiVersion);
}

} // namespace OHOS::Ace::NG