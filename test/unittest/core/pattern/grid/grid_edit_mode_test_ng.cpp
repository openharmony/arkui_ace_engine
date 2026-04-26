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

#include "grid_test_ng.h"

#include "test/mock/frameworks/core/animation/mock_animation_manager.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
} // namespace

class GridEditModeTestNg : public GridTestNg {
public:
    void SetUp() override
    {
        GridTestNg::SetUp();
    }
    void TearDown() override
    {
        GridTestNg::TearDown();
    }
};

// ============================================================
// Step 1: Pattern 数据层 — enableEditMode + EditModeOptions
// ============================================================

/**
 * @tc.name: EnableEditModeToJsonDefault001
 * @tc.desc: Test ToJsonValue outputs enableEditMode=false by default
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EnableEditModeToJsonDefault001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("enableEditMode"), "false");
}

/**
 * @tc.name: EnableEditModeToJsonAfterSet001
 * @tc.desc: Test ToJsonValue outputs enableEditMode=true after setting
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EnableEditModeToJsonAfterSet001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditMode(true);

    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("enableEditMode"), "true");
}

/**
 * @tc.name: EnableEditModeToJsonToggle001
 * @tc.desc: Test ToJsonValue reflects toggle between true and false
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EnableEditModeToJsonToggle001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditMode(true);
    auto json1 = JsonUtil::Create(true);
    pattern_->ToJsonValue(json1, filter);
    EXPECT_EQ(json1->GetString("enableEditMode"), "true");

    pattern_->SetEnableEditMode(false);
    auto json2 = JsonUtil::Create(true);
    pattern_->ToJsonValue(json2, filter);
    EXPECT_EQ(json2->GetString("enableEditMode"), "false");
}

/**
 * @tc.name: EnableEditModeGetEnable001
 * @tc.desc: Test GetEnableEditMode returns correct value
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EnableEditModeGetEnable001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    EXPECT_FALSE(pattern_->GetEnableEditMode());
    pattern_->SetEnableEditMode(true);
    EXPECT_TRUE(pattern_->GetEnableEditMode());
    pattern_->SetEnableEditMode(false);
    EXPECT_FALSE(pattern_->GetEnableEditMode());
}

/**
 * @tc.name: EditModeOptionsToJsonDefault001
 * @tc.desc: Test ToJsonValue outputs default EditModeOptions fields
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EditModeOptionsToJsonDefault001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);

    auto editModeOptions = json->GetObject("editModeOptions");
    EXPECT_EQ(editModeOptions->GetString("useDefaultMultiSelectStyle"), "true");
    EXPECT_EQ(editModeOptions->GetString("enableGatherSelectedItemsAnimation"), "false");
}

/**
 * @tc.name: EditModeOptionsToJsonCustom001
 * @tc.desc: Test ToJsonValue outputs custom EditModeOptions fields
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EditModeOptionsToJsonCustom001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    EditModeOptions options;
    options.useDefaultMultiSelectStyle = false;
    options.enableGatherSelectedItemsAnimation = true;
    pattern_->SetEditModeOptions(options);

    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);

    auto editModeOptions = json->GetObject("editModeOptions");
    EXPECT_EQ(editModeOptions->GetString("useDefaultMultiSelectStyle"), "false");
    EXPECT_EQ(editModeOptions->GetString("enableGatherSelectedItemsAnimation"), "true");
}

/**
 * @tc.name: EditModeOptionsGetAfterSet001
 * @tc.desc: Test GetEditModeOptions returns values set via SetEditModeOptions
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EditModeOptionsGetAfterSet001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    EditModeOptions options;
    options.useDefaultMultiSelectStyle = false;
    pattern_->SetEditModeOptions(options);

    auto retrieved = pattern_->GetEditModeOptions();
    EXPECT_FALSE(retrieved.useDefaultMultiSelectStyle);
}

/**
 * @tc.name: OnEditModeChangeNoCallback001
 * @tc.desc: Test no crash when onEditModeChange is not registered
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, OnEditModeChangeNoCallback001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    EXPECT_NO_FATAL_FAILURE(pattern_->SetEnableEditMode(true));
    EXPECT_NO_FATAL_FAILURE(pattern_->SetEnableEditMode(false));
}

// ============================================================
// Step 2: Grid Model 层 — GridModelNG 传递
// ============================================================

/**
 * @tc.name: GridModelNGSetEnableEditMode001
 * @tc.desc: Test GridModelNG::SetEnableEditMode sets value via Model
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, GridModelNGSetEnableEditMode001, TestSize.Level1)
{
    auto model = CreateGrid();
    CreateFixedItems(5);

    model.SetEnableEditMode(true);
    EXPECT_TRUE(pattern_->GetEnableEditMode());

    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("enableEditMode"), "true");
}

/**
 * @tc.name: GridModelNGSetEnableEditMode002
 * @tc.desc: Test GridModelNG::SetEnableEditMode(false) via Model
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, GridModelNGSetEnableEditMode002, TestSize.Level1)
{
    auto model = CreateGrid();
    CreateFixedItems(5);

    model.SetEnableEditMode(true);
    model.SetEnableEditMode(false);
    EXPECT_FALSE(pattern_->GetEnableEditMode());
}

/**
 * @tc.name: GridModelNGStaticSetEnableEditMode001
 * @tc.desc: Test GridModelNG static SetEnableEditMode on existing FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, GridModelNGStaticSetEnableEditMode001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    GridModelNG::SetEnableEditMode(AceType::RawPtr(frameNode_), true);
    EXPECT_TRUE(pattern_->GetEnableEditMode());

    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("enableEditMode"), "true");
}

/**
 * @tc.name: GridModelNGStaticGetEnableEditMode001
 * @tc.desc: Test GridModelNG static GetEnableEditMode reads from FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, GridModelNGStaticGetEnableEditMode001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    EXPECT_FALSE(GridModelNG::GetEnableEditMode(AceType::RawPtr(frameNode_)));
    GridModelNG::SetEnableEditMode(AceType::RawPtr(frameNode_), true);
    EXPECT_TRUE(GridModelNG::GetEnableEditMode(AceType::RawPtr(frameNode_)));
}

/**
 * @tc.name: GridModelNGStaticSetEditModeOptions001
 * @tc.desc: Test GridModelNG static SetEditModeOptions on existing FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, GridModelNGStaticSetEditModeOptions001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    EditModeOptions options;
    options.useDefaultMultiSelectStyle = false;
    GridModelNG::SetEditModeOptions(AceType::RawPtr(frameNode_), options);

    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);
    auto editModeOptions = json->GetObject("editModeOptions");
    EXPECT_EQ(editModeOptions->GetString("useDefaultMultiSelectStyle"), "false");
}

/**
 * @tc.name: GridModelNGStaticGetEditModeOptions001
 * @tc.desc: Test GridModelNG static GetEditModeOptions reads from FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, GridModelNGStaticGetEditModeOptions001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    EditModeOptions options;
    options.useDefaultMultiSelectStyle = false;
    GridModelNG::SetEditModeOptions(AceType::RawPtr(frameNode_), options);

    auto result = GridModelNG::GetEditModeOptions(AceType::RawPtr(frameNode_));
    EXPECT_FALSE(result.useDefaultMultiSelectStyle);
}

// ============================================================
// Step 1 补充: IsDefaultMultiSelectStyleEnabled
// ============================================================

/**
 * @tc.name: IsDefaultMultiSelectStyleEnabled001
 * @tc.desc: Test IsDefaultMultiSelectStyleEnabled combines enableEditMode and useDefaultMultiSelectStyle
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, IsDefaultMultiSelectStyleEnabled001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    EXPECT_FALSE(pattern_->IsDefaultMultiSelectStyleEnabled());

    pattern_->SetEnableEditMode(true);
    EXPECT_TRUE(pattern_->IsDefaultMultiSelectStyleEnabled());

    EditModeOptions options;
    options.useDefaultMultiSelectStyle = false;
    pattern_->SetEditModeOptions(options);
    EXPECT_FALSE(pattern_->IsDefaultMultiSelectStyleEnabled());

    pattern_->SetEnableEditMode(false);
    EXPECT_FALSE(pattern_->IsDefaultMultiSelectStyleEnabled());
}

// ============================================================
// Step 1 补充: SwipeSelectState 初始值验证
// ============================================================

/**
 * @tc.name: SwipeSelectInitValues001
 * @tc.desc: Test swipe-select related members have correct initial values
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, SwipeSelectInitValues001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    EXPECT_EQ(pattern_->swipeStartIndex_, -1);
    EXPECT_EQ(pattern_->swipeCurrentIndex_, -1);
    EXPECT_EQ(pattern_->swipeSelectState_, SelectableContainerPattern::SwipeSelectState::INACTIVE);
    EXPECT_TRUE(pattern_->swipeOriginalStates_.empty());
    EXPECT_EQ(pattern_->swipeSelectPanEvent_, nullptr);
}

} // namespace OHOS::Ace::NG
