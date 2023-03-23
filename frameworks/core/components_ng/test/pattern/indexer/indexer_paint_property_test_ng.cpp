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

#define protected public
#define private public

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
class IndexerPaintPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void IndexerPaintPropertyTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void IndexerPaintPropertyTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
    PipelineContext::GetCurrentContext()->Destroy();
}

void IndexerPaintPropertyTestNg::SetUp() {}
void IndexerPaintPropertyTestNg::TearDown() {}

/**
 * @tc.name: IndexerPaintPropertyTestNg001
 * @tc.desc: Verify GetPopupSelectedColor.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPaintPropertyTestNg, IndexerPaintPropertyTestNg001, TestSize.Level1)
{
    IndexerPaintProperty property;
    EXPECT_FALSE(property.GetPopupSelectedColor().has_value());
    property.UpdatePopupSelectedColor(Color::BLACK);
    ASSERT_TRUE(property.GetPopupSelectedColor().has_value());
    EXPECT_EQ(property.GetPopupSelectedColor().value(), Color::BLACK);
}

/**
 * @tc.name: IndexerPaintPropertyTestNg002
 * @tc.desc: Verify GetPopupUnselectedColor.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPaintPropertyTestNg, IndexerPaintPropertyTestNg002, TestSize.Level1)
{
    IndexerPaintProperty property;
    EXPECT_FALSE(property.GetPopupUnselectedColor().has_value());
    property.UpdatePopupUnselectedColor(Color::WHITE);
    ASSERT_TRUE(property.GetPopupUnselectedColor().has_value());
    EXPECT_EQ(property.GetPopupUnselectedColor().value(), Color::WHITE);
}

/**
 * @tc.name: IndexerPaintPropertyTestNg003
 * @tc.desc: Verify GetPopupItemBackground.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPaintPropertyTestNg, IndexerPaintPropertyTestNg003, TestSize.Level1)
{
    IndexerPaintProperty property;
    EXPECT_FALSE(property.GetPopupItemBackground().has_value());
    property.UpdatePopupItemBackground(Color::BLACK);
    ASSERT_TRUE(property.GetPopupItemBackground().has_value());
    EXPECT_EQ(property.GetPopupItemBackground().value(), Color::BLACK);
}

/**
 * @tc.name: IndexerPaintPropertyTestNg004
 * @tc.desc: Verify GetPopupHorizontalSpace.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPaintPropertyTestNg, IndexerPaintPropertyTestNg004, TestSize.Level1)
{
    IndexerPaintProperty property;
    EXPECT_FALSE(property.GetPopupHorizontalSpace().has_value());
    property.UpdatePopupHorizontalSpace(Dimension(5, DimensionUnit::VP));
    ASSERT_TRUE(property.GetPopupHorizontalSpace().has_value());
    EXPECT_EQ(property.GetPopupHorizontalSpace().value(), Dimension(5, DimensionUnit::VP));
}

/**
 * @tc.name: IndexerPaintPropertyTestNg005
 * @tc.desc: Verify Reset.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPaintPropertyTestNg, IndexerPaintPropertyTestNg005, TestSize.Level1)
{
    IndexerPaintProperty property;
    property.UpdatePopupSelectedColor(Color::RED);
    property.UpdatePopupUnselectedColor(Color::BLUE);
    property.UpdatePopupItemBackground(Color::BLACK);
    property.UpdatePopupHorizontalSpace(Dimension(5, DimensionUnit::VP));
    EXPECT_TRUE(property.GetPopupSelectedColor().has_value());
    EXPECT_TRUE(property.GetPopupUnselectedColor().has_value());
    EXPECT_TRUE(property.GetPopupItemBackground().has_value());
    EXPECT_TRUE(property.GetPopupHorizontalSpace().has_value());
    property.Reset();
    EXPECT_FALSE(property.GetPopupSelectedColor().has_value());
    EXPECT_FALSE(property.GetPopupUnselectedColor().has_value());
    EXPECT_FALSE(property.GetPopupItemBackground().has_value());
    EXPECT_FALSE(property.GetPopupHorizontalSpace().has_value());
}

/**
 * @tc.name: IndexerPaintPropertyTestNg006
 * @tc.desc: Verify Clone.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPaintPropertyTestNg, IndexerPaintPropertyTestNg006, TestSize.Level1)
{
    IndexerPaintProperty property;
    property.UpdatePopupSelectedColor(Color::RED);
    property.UpdatePopupUnselectedColor(Color::BLUE);
    property.UpdatePopupItemBackground(Color::BLACK);
    property.UpdatePopupHorizontalSpace(Dimension(5, DimensionUnit::VP));

    auto cloneProperty = AceType::DynamicCast<IndexerPaintProperty>(property.Clone());
    ASSERT_NE(cloneProperty, nullptr);
    EXPECT_EQ(property.GetPopupSelectedColor().value(), cloneProperty->GetPopupSelectedColor().value());
    EXPECT_EQ(property.GetPopupUnselectedColor().value(), cloneProperty->GetPopupUnselectedColor().value());
    EXPECT_EQ(property.GetPopupItemBackground().value(), cloneProperty->GetPopupItemBackground().value());
    EXPECT_EQ(property.GetPopupHorizontalSpace().value(), cloneProperty->GetPopupHorizontalSpace().value());
}

/**
 * @tc.name: IndexerPaintPropertyTestNg007
 * @tc.desc: Verify ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPaintPropertyTestNg, IndexerPaintPropertyTestNg007, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineContext::GetCurrentContext()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<IndexerTheme>()));

    IndexerPaintProperty property;
    property.UpdatePopupSelectedColor(Color::RED);
    property.UpdatePopupUnselectedColor(Color::BLUE);
    property.UpdatePopupItemBackground(Color::BLACK);
    property.UpdatePopupHorizontalSpace(Dimension(5, DimensionUnit::VP));

    auto json = JsonUtil::Create(true);
    property.ToJsonValue(json);
    EXPECT_EQ(json->GetString("popupSelectedColor"), Color::RED.ColorToString());
    EXPECT_EQ(json->GetString("popupUnselectedColor"), Color::BLUE.ColorToString());
    EXPECT_EQ(json->GetString("popupItemBackground"), Color::BLACK.ColorToString());
    EXPECT_EQ(json->GetString("popupHorizontalSpace"), Dimension(5, DimensionUnit::VP).ToString());
}
} // namespace
} // namespace OHOS::Ace::NG
