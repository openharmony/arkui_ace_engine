/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/indexer/indexer_paint_property.h"
#define private public

#include <optional>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/indexer/indexer_layout_property.h"
#include "core/components_ng/pattern/indexer/indexer_model_ng.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"
#include "core/components_ng/pattern/indexer/indexer_view.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
std::vector<std::string> CREATE_ARRAY_VALUE = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N",
    "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
constexpr int32_t CREATE_SELECTED_VALUE = 0;
constexpr int32_t SELECTED_VALUE = 0;
constexpr Color COLOR_VALUE = Color(0x00000000);
const TextStyle SELECTED_FONT_VALUE = TextStyle();
const TextStyle POPUP_FONT_VALUE = TextStyle();
const TextStyle FONT_VALUE = TextStyle();
constexpr Dimension ITEM_SIZE_VALUE = Dimension(24.0, DimensionUnit::PX);
constexpr Dimension POPUP_X_VALUE = Dimension(-96.0, DimensionUnit::VP);
constexpr Dimension POPUP_Y_VALUE = Dimension(48.0, DimensionUnit::VP);

constexpr int32_t ALIGN_VALUE = 0;
} // namespace

class IndexerModelTestNg : public testing::Test {};

/**
 * @tc.name: IndexerModelNGTest001
 * @tc.desc: Set indexer value into indexerPaintProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, IndexerModelTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init indexer node
     */
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY_VALUE, SELECTED_VALUE);

    /**
     * @tc.steps: step2. Set parameters to indexer property
     */
    IndexerModelNG.SetSelectedColor(COLOR_VALUE);
    IndexerModelNG.SetColor(COLOR_VALUE);
    IndexerModelNG.SetPopupColor(COLOR_VALUE);
    IndexerModelNG.SetSelectedBackgroundColor(COLOR_VALUE);
    IndexerModelNG.SetPopupBackground(COLOR_VALUE);
    IndexerModelNG.SetUsingPopup(true);
    IndexerModelNG.SetSelectedFont(SELECTED_FONT_VALUE);
    IndexerModelNG.SetPopupFont(POPUP_FONT_VALUE);
    IndexerModelNG.SetFont(FONT_VALUE);
    IndexerModelNG.SetItemSize(ITEM_SIZE_VALUE);
    IndexerModelNG.SetAlignStyle(ALIGN_VALUE);
    IndexerModelNG.SetSelected(SELECTED_VALUE);
    IndexerModelNG.SetPopupPositionX(POPUP_X_VALUE);
    IndexerModelNG.SetPopupPositionY(POPUP_Y_VALUE);

    /**
     * @tc.steps: step3. Get indexer property and get indexer property
     * @tc.expected: step3. Check the indexer property value
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto indexerLayoutProperty = AceType::DynamicCast<IndexerLayoutProperty>(layoutProperty);
    EXPECT_NE(indexerLayoutProperty, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<IndexerPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);

    EXPECT_EQ(indexerLayoutProperty->GetArrayValue().value(), CREATE_ARRAY_VALUE);

    EXPECT_EQ(indexerLayoutProperty->GetSelected().value(), CREATE_SELECTED_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetColor().value(), COLOR_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetSelectedColor().value(), COLOR_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetPopupColor().value(), COLOR_VALUE);
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor().value(), COLOR_VALUE);
    EXPECT_EQ(paintProperty->GetPopupBackground().value(), COLOR_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetUsingPopup().value(), true);
    EXPECT_EQ(indexerLayoutProperty->GetPopupFont().value(), POPUP_FONT_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetFont().value(), FONT_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetItemSize().value(), ITEM_SIZE_VALUE);
    auto align = indexerLayoutProperty->GetAlignStyle().value();
    EXPECT_EQ((int32_t)align, ALIGN_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetSelected().value(), SELECTED_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetPopupPositionX().value(), POPUP_X_VALUE);
    EXPECT_EQ(indexerLayoutProperty->GetPopupPositionY().value(), POPUP_Y_VALUE);
}

/**
 * @tc.name: IndexerModelNGTest002
 * @tc.desc: create Indexer node
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, IndexerModelTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init IndexerModelNG object
     */
    IndexerModelNG IndexerModelNG;
    IndexerModelNG.Create(CREATE_ARRAY_VALUE, SELECTED_VALUE);

    /**
     * @tc.steps: step2. Set call methods
     * @tc.expected: step2. Check the IndexerModelNG pattern value
     */
    int32_t onSelectedValue;
    auto onSelected = [&onSelectedValue](const int32_t& param) { onSelectedValue = param; };
    IndexerModelNG.SetOnSelected(std::move(onSelected));
    auto frameNodeonSelected = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNodeonSelected, nullptr);

    int32_t onRequestPopupValue;
    auto onRequestPopupData = [&onRequestPopupValue](const int32_t& param) {
        std::vector<std::string> popupData;
        onRequestPopupValue = param;
        popupData.push_back("Indexer");
        return popupData;
    };
    IndexerModelNG.SetOnRequestPopupData(std::move(onRequestPopupData));
    auto frameNodeonRequestPopupData = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNodeonRequestPopupData, nullptr);

    int32_t onPopupSelectedValue;
    auto onPopupSelected = [&onPopupSelectedValue](const int32_t& param) { onPopupSelectedValue = param; };
    IndexerModelNG.SetOnSelected(std::move(onPopupSelected));
    auto frameNodeonPopupSelected = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNodeonPopupSelected, nullptr);
}
} // namespace OHOS::Ace::NG