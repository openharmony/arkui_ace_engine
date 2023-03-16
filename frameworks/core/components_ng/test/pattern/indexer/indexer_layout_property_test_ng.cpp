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

#include <optional>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/indexer/indexer_layout_property.h"
#include "core/components_ng/pattern/indexer/indexer_paint_property.h"
#include "core/components_ng/pattern/indexer/indexer_pattern.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"
#include "core/components_ng/pattern/indexer/indexer_view.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
class IndexerLayoutPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void IndexerLayoutPropertyTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void IndexerLayoutPropertyTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
    PipelineContext::GetCurrentContext()->Destroy();
}

void IndexerLayoutPropertyTestNg::SetUp() {}
void IndexerLayoutPropertyTestNg::TearDown() {}

/**
 * @tc.name: IndexerLayoutPropertyTestNg001
 * @tc.desc: Verify GetFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutPropertyTestNg, IndexerLayoutPropertyTestNg001, TestSize.Level1)
{
    IndexerLayoutProperty property;
    EXPECT_FALSE(property.GetFontSize().has_value());
    property.UpdateFontSize(Dimension(24, DimensionUnit::VP));
    ASSERT_TRUE(property.GetFontSize().has_value());
    EXPECT_EQ(property.GetFontSize().value(), Dimension(24, DimensionUnit::VP));
}

/**
 * @tc.name: IndexerLayoutPropertyTestNg002
 * @tc.desc: Verify GetFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutPropertyTestNg, IndexerLayoutPropertyTestNg002, TestSize.Level1)
{
    IndexerLayoutProperty property;
    EXPECT_FALSE(property.GetFontWeight().has_value());
    property.UpdateFontWeight(FontWeight::MEDIUM);
    ASSERT_TRUE(property.GetFontWeight().has_value());
    EXPECT_EQ(property.GetFontWeight().value(), FontWeight::MEDIUM);
}

/**
 * @tc.name: IndexerLayoutPropertyTestNg003
 * @tc.desc: Verify Reset.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutPropertyTestNg, IndexerLayoutPropertyTestNg003, TestSize.Level1)
{
    IndexerLayoutProperty property;
    property.UpdateFontSize(Dimension(25.0f));
    property.UpdateFontWeight(FontWeight::BOLD);
    EXPECT_TRUE(property.GetFontSize().has_value());
    EXPECT_TRUE(property.GetFontWeight().has_value());
    property.Reset();
    EXPECT_FALSE(property.GetFontSize().has_value());
    EXPECT_FALSE(property.GetFontWeight().has_value());
}

/**
 * @tc.name: IndexerLayoutPropertyTestNg004
 * @tc.desc: Verify Clone.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutPropertyTestNg, IndexerLayoutPropertyTestNg004, TestSize.Level1)
{
    IndexerLayoutProperty property;
    property.UpdateFontSize(Dimension(25.0f));
    property.UpdateFontWeight(FontWeight::BOLD);

    auto cloneProperty = AceType::DynamicCast<IndexerLayoutProperty>(property.Clone());
    ASSERT_NE(cloneProperty, nullptr);
    EXPECT_EQ(property.GetFontSize().value(), cloneProperty->GetFontSize().value());
    EXPECT_EQ(property.GetFontWeight().value(), cloneProperty->GetFontWeight().value());
}

/**
 * @tc.name: IndexerLayoutPropertyTestNg005
 * @tc.desc: Verify ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutPropertyTestNg, IndexerLayoutPropertyTestNg005, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineContext::GetCurrentContext()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<IndexerTheme>()));

    IndexerLayoutProperty property;
    property.UpdateFontSize(Dimension(25.0f));
    property.UpdateFontWeight(FontWeight::BOLD);

    auto json = JsonUtil::Create(true);
    property.ToJsonValue(json);
    EXPECT_EQ(json->GetString("popupItemFontSize"), Dimension(25.0f).ToString());
    EXPECT_EQ(json->GetString("popupItemFontWeight"), V2::ConvertWrapFontWeightToStirng(FontWeight::BOLD));
}
} // namespace
} // namespace OHOS::Ace::NG
