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
#include "core/components_ng/pattern/scrollable/selectable_item_pattern.h"

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
    EXPECT_EQ(editModeOptions->GetString("enableFingerMultiSelect"), "true");
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
    options.enableFingerMultiSelect = false;
    pattern_->SetEditModeOptions(options);

    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);

    auto editModeOptions = json->GetObject("editModeOptions");
    EXPECT_EQ(editModeOptions->GetString("useDefaultMultiSelectStyle"), "false");
    EXPECT_EQ(editModeOptions->GetString("enableGatherSelectedItemsAnimation"), "true");
    EXPECT_EQ(editModeOptions->GetString("enableFingerMultiSelect"), "false");
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
 * @tc.name: EditModeOptionsEnableFingerMultiSelectDefault001
 * @tc.desc: Test enableFingerMultiSelect defaults to true
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EditModeOptionsEnableFingerMultiSelectDefault001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    auto options = pattern_->GetEditModeOptions();
    EXPECT_TRUE(options.enableFingerMultiSelect);
}

/**
 * @tc.name: EditModeOptionsEnableFingerMultiSelectSetFalse001
 * @tc.desc: Test setting enableFingerMultiSelect to false
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EditModeOptionsEnableFingerMultiSelectSetFalse001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    EditModeOptions options;
    options.enableFingerMultiSelect = false;
    pattern_->SetEditModeOptions(options);

    auto retrieved = pattern_->GetEditModeOptions();
    EXPECT_FALSE(retrieved.enableFingerMultiSelect);
}

/**
 * @tc.name: EditModeOptionsEnableFingerMultiSelectViaModelNG001
 * @tc.desc: Test enableFingerMultiSelect via static GridModelNG
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EditModeOptionsEnableFingerMultiSelectViaModelNG001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    EditModeOptions options;
    options.enableFingerMultiSelect = false;
    GridModelNG::SetEditModeOptions(AceType::RawPtr(frameNode_), options);

    auto result = GridModelNG::GetEditModeOptions(AceType::RawPtr(frameNode_));
    EXPECT_FALSE(result.enableFingerMultiSelect);
}

/**
 * @tc.name: EditModeOptionsEnableFingerMultiSelectToJson001
 * @tc.desc: Test ToJsonValue for enableFingerMultiSelect toggle
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EditModeOptionsEnableFingerMultiSelectToJson001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    EditModeOptions options;
    options.enableFingerMultiSelect = false;
    pattern_->SetEditModeOptions(options);

    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);
    auto editModeOptions = json->GetObject("editModeOptions");
    EXPECT_EQ(editModeOptions->GetString("enableFingerMultiSelect"), "false");

    options.enableFingerMultiSelect = true;
    pattern_->SetEditModeOptions(options);
    auto json2 = JsonUtil::Create(true);
    pattern_->ToJsonValue(json2, filter);
    auto editModeOptions2 = json2->GetObject("editModeOptions");
    EXPECT_EQ(editModeOptions2->GetString("enableFingerMultiSelect"), "true");
}

/**
 * @tc.name: EditModeOptionsAllFieldsRoundTrip001
 * @tc.desc: Test all EditModeOptions fields survive set/get round trip
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EditModeOptionsAllFieldsRoundTrip001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    EditModeOptions options;
    options.enableGatherSelectedItemsAnimation = true;
    options.useDefaultMultiSelectStyle = false;
    options.enableFingerMultiSelect = false;
    pattern_->SetEditModeOptions(options);

    auto retrieved = pattern_->GetEditModeOptions();
    EXPECT_TRUE(retrieved.enableGatherSelectedItemsAnimation);
    EXPECT_FALSE(retrieved.useDefaultMultiSelectStyle);
    EXPECT_FALSE(retrieved.enableFingerMultiSelect);
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

    EXPECT_EQ(pattern_->swipeStartStateKey_.index, -1);
    EXPECT_EQ(pattern_->swipeCurrentStateKey_.index, -1);
    EXPECT_EQ(pattern_->swipeSelectState_, SelectableContainerPattern::SwipeSelectState::INACTIVE);
    EXPECT_TRUE(pattern_->swipeOriginalStates_.empty());
    EXPECT_EQ(pattern_->swipeSelectPanEvent_, nullptr);
}

// ============================================================
// Step 3: EnableEditModeChangeEvent — 双向绑定
// ============================================================

/**
 * @tc.name: EnableEditModeChangeEventFireOnChange001
 * @tc.desc: Test changeEvent fires when enableEditMode changes from false to true
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EnableEditModeChangeEventFireOnChange001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    bool callbackFired = false;
    bool callbackValue = false;
    pattern_->SetEnableEditModeChangeEvent([&](bool editMode) {
        callbackFired = true;
        callbackValue = editMode;
    });

    pattern_->SetEnableEditMode(true);
    EXPECT_TRUE(callbackFired);
    EXPECT_TRUE(callbackValue);
}

/**
 * @tc.name: EnableEditModeChangeEventFireOnFalse001
 * @tc.desc: Test changeEvent fires when enableEditMode changes from true to false
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EnableEditModeChangeEventFireOnFalse001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditMode(true);

    bool callbackFired = false;
    bool callbackValue = true;
    pattern_->SetEnableEditModeChangeEvent([&](bool editMode) {
        callbackFired = true;
        callbackValue = editMode;
    });

    pattern_->SetEnableEditMode(false);
    EXPECT_TRUE(callbackFired);
    EXPECT_FALSE(callbackValue);
}

/**
 * @tc.name: EnableEditModeChangeEventNoFireSameValue001
 * @tc.desc: Test changeEvent does NOT fire when setting same value
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EnableEditModeChangeEventNoFireSameValue001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditMode(true);

    int32_t fireCount = 0;
    pattern_->SetEnableEditModeChangeEvent([&](bool editMode) {
        fireCount++;
    });

    pattern_->SetEnableEditMode(true);
    EXPECT_EQ(fireCount, 0);
}

/**
 * @tc.name: EnableEditModeChangeEventNoCallback001
 * @tc.desc: Test no crash when no changeEvent registered and value changes
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EnableEditModeChangeEventNoCallback001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    EXPECT_NO_FATAL_FAILURE(pattern_->SetEnableEditMode(true));
    EXPECT_NO_FATAL_FAILURE(pattern_->SetEnableEditMode(false));
}

/**
 * @tc.name: EnableEditModeChangeEventFireTwice001
 * @tc.desc: Test changeEvent fires on each toggle
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EnableEditModeChangeEventFireTwice001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    std::vector<bool> receivedValues;
    pattern_->SetEnableEditModeChangeEvent([&](bool editMode) {
        receivedValues.push_back(editMode);
    });

    pattern_->SetEnableEditMode(true);
    pattern_->SetEnableEditMode(false);
    ASSERT_EQ(receivedValues.size(), 2U);
    EXPECT_TRUE(receivedValues[0]);
    EXPECT_FALSE(receivedValues[1]);
}

/**
 * @tc.name: EnableEditModeChangeEventViaModelNG001
 * @tc.desc: Test changeEvent fires when using GridModelNG::SetEnableEditMode
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EnableEditModeChangeEventViaModelNG001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    bool callbackFired = false;
    bool callbackValue = false;
    pattern_->SetEnableEditModeChangeEvent([&](bool editMode) {
        callbackFired = true;
        callbackValue = editMode;
    });

    GridModelNG::SetEnableEditMode(AceType::RawPtr(frameNode_), true);
    EXPECT_TRUE(callbackFired);
    EXPECT_TRUE(callbackValue);
}

/**
 * @tc.name: EnableEditModeChangeEventViaModelNGStatic001
 * @tc.desc: Test SetEnableEditModeChangeEvent via static GridModelNG
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EnableEditModeChangeEventViaModelNGStatic001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    bool callbackFired = false;
    bool callbackValue = false;
    GridModelNG::SetEnableEditModeChangeEvent(AceType::RawPtr(frameNode_), [&](bool editMode) {
        callbackFired = true;
        callbackValue = editMode;
    });

    GridModelNG::SetEnableEditMode(AceType::RawPtr(frameNode_), true);
    EXPECT_TRUE(callbackFired);
    EXPECT_TRUE(callbackValue);
}

// ============================================================
// Step 4: editModeChanged_ flag — OnModifyDone guard
// ============================================================

/**
 * @tc.name: EditModeChangedFlagDefaultFalse001
 * @tc.desc: Test editModeChanged_ defaults to false after creation
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EditModeChangedFlagDefaultFalse001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    EXPECT_FALSE(pattern_->IsEditModeChanged());
}

/**
 * @tc.name: EditModeChangedFlagSetOnValueChange001
 * @tc.desc: Test editModeChanged_ becomes true when SetEnableEditMode changes the value
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EditModeChangedFlagSetOnValueChange001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    EXPECT_FALSE(pattern_->editModeChanged_);
    pattern_->SetEnableEditMode(true);
    EXPECT_TRUE(pattern_->editModeChanged_);
}

/**
 * @tc.name: EditModeChangedFlagNotSetOnSameValue001
 * @tc.desc: Test editModeChanged_ remains false when SetEnableEditMode is called with the same value
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EditModeChangedFlagNotSetOnSameValue001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditMode(true);
    EXPECT_TRUE(pattern_->editModeChanged_);
    pattern_->ResetEditModeChanged();
    EXPECT_FALSE(pattern_->editModeChanged_);

    pattern_->SetEnableEditMode(true);
    EXPECT_FALSE(pattern_->editModeChanged_);
}

/**
 * @tc.name: EditModeChangedFlagReset001
 * @tc.desc: Test ResetEditModeChanged resets the flag to false
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EditModeChangedFlagReset001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditMode(true);
    EXPECT_TRUE(pattern_->IsEditModeChanged());

    pattern_->ResetEditModeChanged();
    EXPECT_FALSE(pattern_->IsEditModeChanged());
}

/**
 * @tc.name: EditModeChangedFlagToggleOff001
 * @tc.desc: Test editModeChanged_ becomes true when toggling edit mode off
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EditModeChangedFlagToggleOff001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    pattern_->SetEnableEditMode(true);
    pattern_->ResetEditModeChanged();

    pattern_->SetEnableEditMode(false);
    EXPECT_TRUE(pattern_->editModeChanged_);
}

/**
 * @tc.name: EditModeChangedOnModifyDoneAppliesToItems001
 * @tc.desc: Test OnModifyDone applies edit mode to visible items when editModeChanged_ is true
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EditModeChangedOnModifyDoneAppliesToItems001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    pattern_->SetEnableEditMode(true);
    EXPECT_TRUE(pattern_->IsEditModeChanged());

    pattern_->OnModifyDone();

    EXPECT_FALSE(pattern_->IsEditModeChanged());
    for (int32_t i = 0; i < 6; ++i) {
        auto child = GetChildFrameNode(frameNode_, i);
        ASSERT_NE(child, nullptr);
        auto itemPattern = child->GetPattern<SelectableItemPattern>();
        if (itemPattern) {
            EXPECT_NE(itemPattern->editModeCheckBoxNode_, nullptr) << "item " << i;
        }
    }
}

/**
 * @tc.name: EditModeChangedOnModifyDoneSkipsWhenFalse001
 * @tc.desc: Test OnModifyDone skips ApplyEditModeToVisibleItems when editModeChanged_ is false
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EditModeChangedOnModifyDoneSkipsWhenFalse001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    pattern_->SetEnableEditMode(true);
    pattern_->ResetEditModeChanged();
    EXPECT_FALSE(pattern_->IsEditModeChanged());

    pattern_->OnModifyDone();

    for (int32_t i = 0; i < 6; ++i) {
        auto child = GetChildFrameNode(frameNode_, i);
        ASSERT_NE(child, nullptr);
        auto itemPattern = child->GetPattern<SelectableItemPattern>();
        if (itemPattern) {
            EXPECT_EQ(itemPattern->editModeCheckBoxNode_, nullptr) << "item " << i;
        }
    }
}

/**
 * @tc.name: EditModeChangedOnModifyDoneRemovesFromItems001
 * @tc.desc: Test OnModifyDone removes edit mode from items when toggled off
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EditModeChangedOnModifyDoneRemovesFromItems001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    pattern_->SetEnableEditMode(true);
    pattern_->OnModifyDone();

    for (int32_t i = 0; i < 6; ++i) {
        auto child = GetChildFrameNode(frameNode_, i);
        ASSERT_NE(child, nullptr);
        auto itemPattern = child->GetPattern<SelectableItemPattern>();
        if (itemPattern) {
            EXPECT_NE(itemPattern->editModeCheckBoxNode_, nullptr) << "item " << i << " should have CheckBox";
        }
    }

    pattern_->SetEnableEditMode(false);
    EXPECT_TRUE(pattern_->IsEditModeChanged());
    pattern_->OnModifyDone();

    for (int32_t i = 0; i < 6; ++i) {
        auto child = GetChildFrameNode(frameNode_, i);
        ASSERT_NE(child, nullptr);
        auto itemPattern = child->GetPattern<SelectableItemPattern>();
        if (itemPattern) {
            EXPECT_EQ(itemPattern->editModeCheckBoxNode_, nullptr) << "item " << i << " should have no CheckBox";
        }
    }
}

/**
 * @tc.name: EditModeChangedOnModifyDoneNoDefaultMultiSelectStyle001
 * @tc.desc: Test OnModifyDone calls RemoveEditModeFromItems when useDefaultMultiSelectStyle is false
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EditModeChangedOnModifyDoneNoDefaultMultiSelectStyle001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EditModeOptions options;
    options.useDefaultMultiSelectStyle = false;
    pattern_->SetEditModeOptions(options);

    pattern_->SetEnableEditMode(true);
    EXPECT_TRUE(pattern_->IsEditModeChanged());

    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->IsEditModeChanged());

    for (int32_t i = 0; i < 6; ++i) {
        auto child = GetChildFrameNode(frameNode_, i);
        ASSERT_NE(child, nullptr);
        auto itemPattern = child->GetPattern<SelectableItemPattern>();
        if (itemPattern) {
            EXPECT_EQ(itemPattern->editModeCheckBoxNode_, nullptr) << "item " << i;
        }
    }
}

/**
 * @tc.name: EditModeChangedMultipleToggleCycle001
 * @tc.desc: Test editModeChanged_ flag correctness across multiple toggle cycles
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EditModeChangedMultipleToggleCycle001, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(5);

    EXPECT_FALSE(pattern_->editModeChanged_);

    pattern_->SetEnableEditMode(true);
    EXPECT_TRUE(pattern_->editModeChanged_);
    pattern_->ResetEditModeChanged();

    pattern_->SetEnableEditMode(false);
    EXPECT_TRUE(pattern_->editModeChanged_);
    pattern_->ResetEditModeChanged();

    pattern_->SetEnableEditMode(false);
    EXPECT_FALSE(pattern_->editModeChanged_);

    pattern_->SetEnableEditMode(true);
    EXPECT_TRUE(pattern_->editModeChanged_);
}

/**
 * @tc.name: EditModeChangedOnModifyDoneRepeatedCalls001
 * @tc.desc: Test that repeated OnModifyDone calls without value change do not re-apply edit mode
 * @tc.type: FUNC
 */
HWTEST_F(GridEditModeTestNg, EditModeChangedOnModifyDoneRepeatedCalls001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    pattern_->SetEnableEditMode(true);
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->IsEditModeChanged());

    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->IsEditModeChanged());
}

} // namespace OHOS::Ace::NG
