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
#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "ui/view/components/badge.h"
#include "ui/base/ace_type.h"
#include "ui/resource/resource_object.h"
#include "core/components/badge/badge_theme.h"
#include "core/components_ng/pattern/badge/badge_model_ng.h"
#include "core/components_ng/pattern/badge/badge_layout_property.h"
#include "core/components_ng/pattern/badge/badge_pattern.h"
#include "core/components_ng/pattern/badge/badge_theme_wrapper.h"
#include "core/components/theme/theme_constants.h"
#include "test/unittest/core/pattern/test_ng.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;
using namespace OHOS::Ace::Kit;

namespace {
const std::string TEST_BADGE_VALUE("123");
const int TEST_BADGE_COUNT(1);
const int32_t TEST_NODE_ID = 10001;
}

namespace OHOS::Ace::Kit {

class BadgeResObjTest : public testing::Test {
protected:
    void SetUp() override
    {
        NG::MockPipelineContext::SetUp();
        g_isConfigChangePerform = true;
        CreateBadgeTheme();

        auto aceNode = NG::BadgeModelNG::CreateFrameNode(TEST_NODE_ID);
        ASSERT_NE(aceNode, nullptr);

        auto frameNodeImpl = AceType::MakeRefPtr<FrameNodeImpl>(aceNode);
        RefPtr<Kit::FrameNode> baseNode = frameNodeImpl;
        badge_ = Badge::Create(baseNode);
    }

    void CreateBadgeTheme()
    {
        auto themeManager = AceType::MakeRefPtr<testing::NiceMock<MockThemeManager>>();
        NG::MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        auto themeConstants = NG::TestNG::CreateThemeConstants(THEME_PATTERN_BADGE);
        auto badgeTheme = BadgeTheme::Builder().Build(themeConstants);
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(testing::Return(badgeTheme));
    }

    void TearDown() override
    {
        badge_ = nullptr;
        g_isConfigChangePerform = false;
        NG::MockPipelineContext::TearDown();
    }

    RefPtr<NG::FrameNode> GetFrameNode()
    {
        auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(badge_->node_);
        if (!frameNodeImpl) {
            return nullptr;
        }
        auto aceFrameNode = frameNodeImpl->GetAceNode();
        if (!aceFrameNode) {
            return nullptr;
        }
        return aceFrameNode;
    }

    NG::BadgePattern* GetBadgePattern()
    {
        auto badgeNode = GetFrameNode();
        if (!badgeNode) {
            return nullptr;
        }
        auto pattern = badgeNode->GetPattern<NG::BadgePattern>();
        return pattern ? pattern.GetRawPtr() : nullptr;
    }

    NG::BadgeLayoutProperty* GetBadgeLayoutProperty()
    {
        auto badgeNode = GetFrameNode();
        if (!badgeNode) {
            return nullptr;
        }
        auto layoutProperty = badgeNode->GetLayoutProperty<NG::BadgeLayoutProperty>();
        return layoutProperty ? layoutProperty.GetRawPtr() : nullptr;
    }

    RefPtr<ResourceObject> MakeResObj()
    {
        return AceType::MakeRefPtr<ResourceObject>();
    }

protected:
    RefPtr<Badge> badge_;
};

// ===== SetBadgeParams resObj overload =====

HWTEST_F(BadgeResObjTest, SetBadgeParams_BadgeValue, TestSize.Level1)
{
    BadgeParametersKit params;
    params.badgeValue = TEST_BADGE_VALUE;
    badge_->SetBadgeParams(params, false, false);

    auto badgeLayoutProperty = GetBadgeLayoutProperty();
    ASSERT_NE(badgeLayoutProperty, nullptr);
    EXPECT_TRUE(badgeLayoutProperty->GetBadgeValue().has_value());
    EXPECT_EQ(badgeLayoutProperty->GetBadgeValue().value(), TEST_BADGE_VALUE);
}

HWTEST_F(BadgeResObjTest, SetBadgeParams_badgeCount, TestSize.Level1)
{
    BadgeParametersKit params;
    params.badgeCount = TEST_BADGE_COUNT;
    badge_->SetBadgeParams(params, false, false);

    auto badgeLayoutProperty = GetBadgeLayoutProperty();
    ASSERT_NE(badgeLayoutProperty, nullptr);
    EXPECT_TRUE(badgeLayoutProperty->GetBadgeCount().has_value());
    EXPECT_EQ(badgeLayoutProperty->GetBadgeCount().value(), TEST_BADGE_COUNT);
}

HWTEST_F(BadgeResObjTest, SetBadgeParams_BadgeColorRes, TestSize.Level1)
{
    auto resObj = MakeResObj();
    BadgeParametersKit params;
    params.resourceBadgeColorObject = resObj;
    badge_->SetBadgeParams(params, false, false);

    auto badgeLayoutProperty = GetBadgeLayoutProperty();
    ASSERT_NE(badgeLayoutProperty, nullptr);
    EXPECT_TRUE(badgeLayoutProperty->GetBadgeColorByuser());

    auto pattern = GetBadgePattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->resourceMgr_, nullptr);
}

HWTEST_F(BadgeResObjTest, SetBadgeParams_BadgeColorRes_Disable, TestSize.Level1)
{
    g_isConfigChangePerform = false;

    auto resObj = MakeResObj();
    BadgeParametersKit params;
    params.resourceBadgeColorObject = resObj;
    badge_->SetBadgeParams(params, false, false);

    auto badgeLayoutProperty = GetBadgeLayoutProperty();
    ASSERT_NE(badgeLayoutProperty, nullptr);
    EXPECT_FALSE(badgeLayoutProperty->GetBadgeColorByuser());

    auto pattern = GetBadgePattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}


HWTEST_F(BadgeResObjTest, SetBadgeParams_BadgeTextColorRes, TestSize.Level1)
{
    auto resObj = MakeResObj();
    BadgeParametersKit params;
    params.resourceColorObject = resObj;
    badge_->SetBadgeParams(params, false, false);

    auto badgeLayoutProperty = GetBadgeLayoutProperty();
    ASSERT_NE(badgeLayoutProperty, nullptr);
    EXPECT_TRUE(badgeLayoutProperty->GetBadgeTextColorByuser());

    auto pattern = GetBadgePattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->resourceMgr_, nullptr);
}

HWTEST_F(BadgeResObjTest, SetBadgeParams_BadgeTextColorRes_Disable, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto resObj = MakeResObj();
    BadgeParametersKit params;
    params.resourceColorObject = resObj;
    badge_->SetBadgeParams(params, false, false);

    auto badgeLayoutProperty = GetBadgeLayoutProperty();
    ASSERT_NE(badgeLayoutProperty, nullptr);
    EXPECT_FALSE(badgeLayoutProperty->GetBadgeTextColorByuser());

    auto pattern = GetBadgePattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

} // namespace OHOS::Ace::Kit
