/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/checkbox/checkbox_accessibility_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_ng.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_content_pattern.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
using CheckboxBuilderFunc = std::optional<std::function<void()>>;

namespace OHOS::Ace::NG {
namespace {
const bool TRUE = true;
const bool FALSE = false;
const float ONE_FLOAT = 1.0f;
const float TWO_FLOAT = 2.0f;
const float THREE_FLOAT = 3.0f;
const float TEN_FLOAT = 10.0f;
const int NODE_ID = 10;
const int FRAMENODE_ID = 2;
const int32_t THEME_SCOPE_ID = 0;
const uint64_t ONE_NUMBER = 1;
const Dimension NEGATIVE_NUMBER = -1.0_vp;
const Dimension ZERO = 0.0_vp;
const Dimension TEN = 10.0_vp;
const std::string CURRENT_NAV_ID = "Checkbox";
const std::string GROUP_NAME = "CheckboxGroup";
const std::string TAG = "STAGE";
const std::string TYPE = "ToggleType.Checkbox";
} // namespace

class CheckBox2TestNG : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    CheckboxBuilderFunc CheckboxBuilder();
};

void CheckBox2TestNG::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CheckboxTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<CheckboxTheme>()));

    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>(TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
}

void CheckBox2TestNG::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

CheckboxBuilderFunc CheckBox2TestNG::CheckboxBuilder()
{
    return []() {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(10.f));
        ViewAbstract::SetHeight(CalcLength(10.f));
    };
}

/**
 * @tc.name: CreateNodePaintMethod001
 * @tc.desc: test function CreateNodePaintMethod
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, CreateNodePaintMethod001, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxNode->paintProperty_ = checkBoxPaintProperty;
    auto checkBoxPaintMethod = AceType::MakeRefPtr<CheckBoxPaintMethod>();
    checkBoxPattern->paintMethod_ = checkBoxPaintMethod;
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    EXPECT_FALSE(checkBoxNode->checkboxFlag_);
    auto nodePaintMethod = checkBoxPattern->CreateNodePaintMethod();
    EXPECT_TRUE(checkBoxNode->checkboxFlag_);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: test function OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto hostNode = FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(hostNode, nullptr);
    auto layoutWrapper = hostNode->CreateLayoutWrapper(TRUE, TRUE);
    ASSERT_NE(layoutWrapper, nullptr);
    checkBoxPattern->isUserSetResponseRegion_ = TRUE;
    EXPECT_TRUE(checkBoxPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, TRUE, FALSE));
}

/**
 * @tc.name: OnClick001
 * @tc.desc: test function OnClick
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, OnClick001, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, FRAMENODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(node, nullptr);
    checkBoxPattern->contentModifierNode_ = node;
    checkBoxPattern->OnClick();
    EXPECT_TRUE(checkBoxPattern->UseContentModifier());
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: test function ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, ToJsonValue001, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto json = std::make_unique<JsonValue>();
    ASSERT_NE(json, nullptr);
    auto filter = InspectorFilter();
    checkBoxPattern->ToJsonValue(json, filter);
    EXPECT_FALSE(filter.IsFastFilter());
}

/**
 * @tc.name: ToJsonValue002
 * @tc.desc: test function ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, ToJsonValue002, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto json = std::make_unique<JsonValue>();
    ASSERT_NE(json, nullptr);
    auto filter = InspectorFilter();
    filter.filterFixed = ONE_NUMBER;
    filter.filterExt.clear();
    checkBoxPattern->ToJsonValue(json, filter);
    EXPECT_TRUE(filter.IsFastFilter());
}

/**
 * @tc.name: OnTouchDown001
 * @tc.desc: test function OnTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, OnTouchDown001, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, FRAMENODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(node, nullptr);
    checkBoxPattern->contentModifierNode_ = node;
    checkBoxPattern->OnTouchDown();
    EXPECT_TRUE(checkBoxPattern->UseContentModifier());
}

/**
 * @tc.name: OnTouchUp001
 * @tc.desc: test function OnTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, OnTouchUp001, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, FRAMENODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(node, nullptr);
    checkBoxPattern->contentModifierNode_ = node;
    checkBoxPattern->OnTouchUp();
    EXPECT_TRUE(checkBoxPattern->UseContentModifier());
}

/**
 * @tc.name: UpdateUIStatus001
 * @tc.desc: test function UpdateUIStatus
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, UpdateUIStatus001, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, FRAMENODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(node, nullptr);
    checkBoxPattern->contentModifierNode_ = node;
    checkBoxPattern->UpdateUIStatus(TRUE);
    EXPECT_TRUE(checkBoxNode->GetPaintProperty<CheckBoxPaintProperty>()->GetCheckBoxSelect());
}

/**
 * @tc.name: UpdateCheckBoxGroupStatus001
 * @tc.desc: test function UpdateCheckBoxGroupStatus
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, UpdateCheckBoxGroupStatus001, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxGroupNode =
        FrameNode::CreateFrameNode(V2::CHECKBOXGROUP_ETS_TAG, FRAMENODE_ID, AceType::MakeRefPtr<CheckBoxGroupPattern>());
    ASSERT_NE(checkBoxGroupNode, nullptr);
    std::list<RefPtr<FrameNode>> list;
    list.push_back(nullptr);
    checkBoxPattern->UpdateCheckBoxGroupStatus(checkBoxGroupNode, list);
    EXPECT_FALSE(list.empty());
}

/**
 * @tc.name: ChangeGroupStatusAndNotify001
 * @tc.desc: test function ChangeGroupStatusAndNotify
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, ChangeGroupStatusAndNotify001, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxGroupNode =
        FrameNode::CreateFrameNode(V2::CHECKBOXGROUP_ETS_TAG, FRAMENODE_ID, AceType::MakeRefPtr<CheckBoxGroupPattern>());
    ASSERT_NE(checkBoxGroupNode, nullptr);
    auto checkBoxGroupPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxGroupPaintProperty, nullptr);
    checkBoxGroupNode->paintProperty_ = checkBoxGroupPaintProperty;
    std::vector<std::string> vec;
    checkBoxPattern->ChangeGroupStatusAndNotify(checkBoxGroupNode, vec, TRUE, TRUE);
    EXPECT_TRUE(checkBoxGroupNode->GetPattern<CheckBoxGroupPattern>()->skipFlag_);
}

/**
 * @tc.name: ChangeGroupStatusAndNotify002
 * @tc.desc: test function ChangeGroupStatusAndNotify
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, ChangeGroupStatusAndNotify002, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxGroupNode =
        FrameNode::CreateFrameNode(V2::CHECKBOXGROUP_ETS_TAG, FRAMENODE_ID, AceType::MakeRefPtr<CheckBoxGroupPattern>());
    ASSERT_NE(checkBoxGroupNode, nullptr);
    auto checkBoxGroupPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxGroupPaintProperty, nullptr);
    checkBoxGroupPaintProperty->propStatus_ = CheckBoxGroupPaintProperty::SelectStatus::ALL;
    checkBoxGroupNode->paintProperty_ = checkBoxGroupPaintProperty;
    std::vector<std::string> vec;
    checkBoxPattern->ChangeGroupStatusAndNotify(checkBoxGroupNode, vec, FALSE, FALSE);
    EXPECT_TRUE(checkBoxGroupNode->GetPattern<CheckBoxGroupPattern>()->skipFlag_);
}

/**
 * @tc.name: SetCheckBoxSelect001
 * @tc.desc: test function SetCheckBoxSelect
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, SetCheckBoxSelect001, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->enabled_ = false;
    checkBoxNode->eventHub_ = eventHub;
    checkBoxPattern->SetCheckBoxSelect(FALSE);
    EXPECT_FALSE(checkBoxNode->eventHub_->enabled_);
}

/**
 * @tc.name: InitCheckBoxStatusByGroup001
 * @tc.desc: test function InitCheckBoxStatusByGroup
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, InitCheckBoxStatusByGroup001, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxGroupNode =
        FrameNode::CreateFrameNode(V2::CHECKBOXGROUP_ETS_TAG, FRAMENODE_ID, AceType::MakeRefPtr<CheckBoxGroupPattern>());
    ASSERT_NE(checkBoxGroupNode, nullptr);
    auto checkBoxGroupPaintProperty = AceType::MakeRefPtr<CheckBoxGroupPaintProperty>();
    ASSERT_NE(checkBoxGroupPaintProperty, nullptr);
    std::list<RefPtr<FrameNode>> list;
    checkBoxPattern->InitCheckBoxStatusByGroup(checkBoxGroupNode, checkBoxGroupPaintProperty, list);
    EXPECT_FALSE(checkBoxGroupPaintProperty->HasCheckBoxGroupSelect());
}

/**
 * @tc.name: UpdatePaintPropertyBySettingData001
 * @tc.desc: test function UpdatePaintPropertyBySettingData
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, UpdatePaintPropertyBySettingData001, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    CheckboxSettingData checkboxSettingData;
    checkboxSettingData.selectedColor = Color::BLACK;
    checkboxSettingData.unselectedColor = Color::RED;
    checkboxSettingData.strokeColor = Color::BLUE;
    checkBoxPattern->checkboxSettingData_ = checkboxSettingData;
    checkBoxPattern->UpdatePaintPropertyBySettingData(checkBoxPaintProperty);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxSelectedColor(), Color::BLACK);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxUnSelectedColor(), Color::RED);
    EXPECT_EQ(checkBoxPaintProperty->GetCheckBoxCheckMarkColor(), Color::BLUE);
}

/**
 * @tc.name: GetGroupNameWithNavId001
 * @tc.desc: test function GetGroupNameWithNavId
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, GetGroupNameWithNavId001, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto eventHub = AceType::MakeRefPtr<CheckBoxEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetGroupName(GROUP_NAME);
    checkBoxNode->eventHub_ = eventHub;
    checkBoxPattern->currentNavId_ = CURRENT_NAV_ID;
    EXPECT_EQ(checkBoxPattern->GetGroupNameWithNavId(), GROUP_NAME + CURRENT_NAV_ID);
}

/**
 * @tc.name: OnThemeScopeUpdate001
 * @tc.desc: test function OnThemeScopeUpdate
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, OnThemeScopeUpdate001, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->UpdateCheckBoxSelectedColorFlagByUser(TRUE);
    checkBoxNode->paintProperty_ = checkBoxPaintProperty;
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    ASSERT_NE(checkBoxTheme, nullptr);
    checkBoxTheme->inactiveColor_ = Color::BLACK;
    EXPECT_TRUE(checkBoxPattern->OnThemeScopeUpdate(THEME_SCOPE_ID));
    auto paintProperty = checkBoxNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetCheckBoxUnSelectedColor(), Color::BLACK);
}

/**
 * @tc.name: OnThemeScopeUpdate002
 * @tc.desc: test function OnThemeScopeUpdate
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, OnThemeScopeUpdate002, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->UpdateCheckBoxUnSelectedColorFlagByUser(TRUE);
    checkBoxNode->paintProperty_ = checkBoxPaintProperty;
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    ASSERT_NE(checkBoxTheme, nullptr);
    checkBoxTheme->activeColor_ = Color::BLACK;
    EXPECT_TRUE(checkBoxPattern->OnThemeScopeUpdate(THEME_SCOPE_ID));
    auto paintProperty = checkBoxNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetCheckBoxSelectedColor(), Color::BLACK);
}

/**
 * @tc.name: OnThemeScopeUpdate003
 * @tc.desc: test function OnThemeScopeUpdate
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, OnThemeScopeUpdate003, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->UpdateCheckBoxCheckMarkColorFlagByUser(TRUE);
    checkBoxNode->paintProperty_ = checkBoxPaintProperty;
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    ASSERT_NE(checkBoxTheme, nullptr);
    checkBoxTheme->activeColor_ = Color::BLACK;
    EXPECT_TRUE(checkBoxPattern->OnThemeScopeUpdate(THEME_SCOPE_ID));
    auto paintProperty = checkBoxNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetCheckBoxSelectedColor(), Color::BLACK);
}

/**
 * @tc.name: DumpInfo001
 * @tc.desc: test function DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, DumpInfo001, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->UpdateCheckBoxSelectedStyle(CheckBoxStyle::CIRCULAR_STYLE);
    checkBoxNode->paintProperty_ = checkBoxPaintProperty;
    auto checkBoxEventHub = AceType::MakeRefPtr<CheckBoxEventHub>();
    ASSERT_NE(checkBoxEventHub, nullptr);
    checkBoxNode->eventHub_ = checkBoxEventHub;
    checkBoxPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "Shape: CIRCULAR\n");
}

/**
 * @tc.name: DumpInfo002
 * @tc.desc: test function DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, DumpInfo002, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->UpdateCheckBoxSelect(TRUE);
    checkBoxNode->paintProperty_ = checkBoxPaintProperty;
    auto checkBoxEventHub = AceType::MakeRefPtr<CheckBoxEventHub>();
    ASSERT_NE(checkBoxEventHub, nullptr);
    checkBoxNode->eventHub_ = checkBoxEventHub;
    checkBoxPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "IsSelected: true\n");
}

/**
 * @tc.name: DumpInfo003
 * @tc.desc: test function DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, DumpInfo003, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->UpdateCheckBoxSelectedColor(Color::BLACK);
    checkBoxNode->paintProperty_ = checkBoxPaintProperty;
    auto checkBoxEventHub = AceType::MakeRefPtr<CheckBoxEventHub>();
    ASSERT_NE(checkBoxEventHub, nullptr);
    checkBoxNode->eventHub_ = checkBoxEventHub;
    checkBoxPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "SelectedColor: #FF000000\n");
}

/**
 * @tc.name: DumpInfo004
 * @tc.desc: test function DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, DumpInfo004, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->UpdateCheckBoxUnSelectedColor(Color::BLACK);
    checkBoxNode->paintProperty_ = checkBoxPaintProperty;
    auto checkBoxEventHub = AceType::MakeRefPtr<CheckBoxEventHub>();
    ASSERT_NE(checkBoxEventHub, nullptr);
    checkBoxNode->eventHub_ = checkBoxEventHub;
    checkBoxPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "UnSelectedColor: #FF000000\n");
}

/**
 * @tc.name: DumpInfo005
 * @tc.desc: test function DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, DumpInfo005, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->UpdateCheckBoxCheckMarkSize(TEN);
    checkBoxNode->paintProperty_ = checkBoxPaintProperty;
    auto checkBoxEventHub = AceType::MakeRefPtr<CheckBoxEventHub>();
    ASSERT_NE(checkBoxEventHub, nullptr);
    checkBoxNode->eventHub_ = checkBoxEventHub;
    checkBoxPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "MarkSize: 10.00vp\n");
}

/**
 * @tc.name: DumpInfo006
 * @tc.desc: test function DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, DumpInfo006, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->UpdateCheckBoxCheckMarkWidth(TEN);
    checkBoxNode->paintProperty_ = checkBoxPaintProperty;
    auto checkBoxEventHub = AceType::MakeRefPtr<CheckBoxEventHub>();
    ASSERT_NE(checkBoxEventHub, nullptr);
    checkBoxNode->eventHub_ = checkBoxEventHub;
    checkBoxPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "MarkWidth: 10.00vp\n");
}

/**
 * @tc.name: DumpInfo007
 * @tc.desc: test function DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, DumpInfo007, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->UpdateCheckBoxCheckMarkColor(Color::BLUE);
    checkBoxNode->paintProperty_ = checkBoxPaintProperty;
    auto checkBoxEventHub = AceType::MakeRefPtr<CheckBoxEventHub>();
    ASSERT_NE(checkBoxEventHub, nullptr);
    checkBoxNode->eventHub_ = checkBoxEventHub;
    checkBoxPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "MarkColor: #FF0000FF\n");
}

/**
 * @tc.name: OnAttachToMainTree001
 * @tc.desc: test function OnAttachToMainTree
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, OnAttachToMainTree001, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    auto groupManager = AceType::MakeRefPtr<GroupManager>();
    ASSERT_NE(groupManager, nullptr);
    checkBoxPattern->groupManager_ = std::move(groupManager);
    checkBoxPattern->OnAttachToMainTree();
    EXPECT_TRUE(checkBoxPattern->currentNavId_.value_or("").empty());
}

/**
 * @tc.name: OnAttachToMainTree002
 * @tc.desc: test function OnAttachToMainTree
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, OnAttachToMainTree002, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    auto frameNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, FRAMENODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    checkBoxNode->parent_ = std::move(frameNode);
    auto groupManager = AceType::MakeRefPtr<GroupManager>();
    ASSERT_NE(groupManager, nullptr);
    checkBoxPattern->groupManager_ = std::move(groupManager);
    checkBoxPattern->currentNavId_ = CURRENT_NAV_ID;
    checkBoxPattern->OnAttachToMainTree();
    EXPECT_EQ(checkBoxPattern->currentNavId_, "");
}

/**
 * @tc.name: OnAttachToMainTree003
 * @tc.desc: test function OnAttachToMainTree
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, OnAttachToMainTree003, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(
        V2::NAVDESTINATION_CONTENT_ETS_TAG, FRAMENODE_ID, AceType::MakeRefPtr<NavigationContentPattern>());
    checkBoxNode->parent_ = std::move(frameNode);
    auto groupManager = AceType::MakeRefPtr<GroupManager>();
    ASSERT_NE(groupManager, nullptr);
    checkBoxPattern->groupManager_ = std::move(groupManager);
    checkBoxPattern->currentNavId_ = CURRENT_NAV_ID;
    checkBoxPattern->OnAttachToMainTree();
    EXPECT_EQ(checkBoxPattern->currentNavId_, "2");
}

/**
 * @tc.name: ToJsonValue003
 * @tc.desc: test CheckBoxPaintProperty function ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, ToJsonValue003, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(checkBoxPattern, nullptr);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxNode->paintProperty_ = checkBoxPaintProperty;
    auto paintProperty = checkBoxNode->GetPaintProperty<CheckBoxPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto json = std::make_unique<JsonValue>();
    ASSERT_NE(json, nullptr);
    auto filter = InspectorFilter();
    filter.filterFixed = ONE_NUMBER;
    filter.filterExt.clear();
    paintProperty->ToJsonValue(json, filter);
    EXPECT_TRUE(filter.IsFastFilter());
}

/**
 * @tc.name: GetContentModifier001
 * @tc.desc: test function GetContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, GetContentModifier001, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPaintMethod = AceType::MakeRefPtr<CheckBoxPaintMethod>();
    ASSERT_NE(checkBoxPaintMethod, nullptr);
    SizeF size;
    OffsetF offset;
    auto checkBoxModifier = AceType::MakeRefPtr<CheckBoxModifier>(
        TRUE, Color::BLACK, Color::RED, Color::BLUE, Color::GREEN, size, offset, ONE_FLOAT, TWO_FLOAT);
    ASSERT_NE(checkBoxModifier, nullptr);
    checkBoxPaintMethod->checkboxModifier_ = checkBoxModifier;
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    PaintWrapper* paintWrapper =
        new PaintWrapper(std::move(checkBoxNode->renderContext_), geometryNode, checkBoxPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    EXPECT_EQ(checkBoxPaintMethod->GetContentModifier(paintWrapper), checkBoxModifier);
    delete paintWrapper;
}

/**
 * @tc.name: GetContentModifier002
 * @tc.desc: test function GetContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, GetContentModifier002, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPaintMethod = AceType::MakeRefPtr<CheckBoxPaintMethod>();
    ASSERT_NE(checkBoxPaintMethod, nullptr);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->UpdateCheckBoxCheckMarkWidth(TEN);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    PaintWrapper* paintWrapper =
        new PaintWrapper(std::move(checkBoxNode->renderContext_), geometryNode, checkBoxPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    ASSERT_NE(checkBoxTheme, nullptr);
    checkBoxPaintMethod->GetContentModifier(paintWrapper);
    EXPECT_TRUE(checkBoxPaintProperty->HasCheckBoxCheckMarkWidth());
    delete paintWrapper;
}

/**
 * @tc.name: GetContentModifier003
 * @tc.desc: test function GetContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, GetContentModifier003, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPaintMethod = AceType::MakeRefPtr<CheckBoxPaintMethod>();
    ASSERT_NE(checkBoxPaintMethod, nullptr);
    SizeF size(TEN_FLOAT, TEN_FLOAT);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->UpdateCheckBoxCheckMarkWidth(ZERO);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(size);
    PaintWrapper* paintWrapper =
        new PaintWrapper(std::move(checkBoxNode->renderContext_), geometryNode, checkBoxPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    ASSERT_NE(checkBoxTheme, nullptr);
    checkBoxPaintMethod->GetContentModifier(paintWrapper);
    EXPECT_TRUE(checkBoxPaintProperty->HasCheckBoxCheckMarkWidth());
    delete paintWrapper;
}

/**
 * @tc.name: GetContentModifier004
 * @tc.desc: test function GetContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, GetContentModifier004, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPaintMethod = AceType::MakeRefPtr<CheckBoxPaintMethod>();
    ASSERT_NE(checkBoxPaintMethod, nullptr);
    SizeF size(THREE_FLOAT, THREE_FLOAT);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->UpdateCheckBoxCheckMarkSize(TEN);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(size);
    PaintWrapper* paintWrapper =
        new PaintWrapper(std::move(checkBoxNode->renderContext_), geometryNode, checkBoxPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    ASSERT_NE(checkBoxTheme, nullptr);
    checkBoxPaintMethod->GetContentModifier(paintWrapper);
    EXPECT_TRUE(checkBoxPaintProperty->HasCheckBoxCheckMarkSize());
    delete paintWrapper;
}

/**
 * @tc.name: GetContentModifier005
 * @tc.desc: test function GetContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, GetContentModifier005, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto checkBoxPaintMethod = AceType::MakeRefPtr<CheckBoxPaintMethod>();
    ASSERT_NE(checkBoxPaintMethod, nullptr);
    SizeF size(THREE_FLOAT, THREE_FLOAT);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->UpdateCheckBoxCheckMarkSize(NEGATIVE_NUMBER);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(size);
    PaintWrapper* paintWrapper =
        new PaintWrapper(std::move(checkBoxNode->renderContext_), geometryNode, checkBoxPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    ASSERT_NE(checkBoxTheme, nullptr);
    checkBoxPaintMethod->GetContentModifier(paintWrapper);
    EXPECT_TRUE(checkBoxPaintProperty->HasCheckBoxCheckMarkSize());
    delete paintWrapper;
}

/**
 * @tc.name: UpdateCheckboxColors001
 * @tc.desc: test function UpdateCheckboxColors
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, UpdateCheckboxColors001, TestSize.Level1)
{
    auto checkBoxPaintMethod = AceType::MakeRefPtr<CheckBoxPaintMethod>();
    ASSERT_NE(checkBoxPaintMethod, nullptr);
    SizeF size(THREE_FLOAT, THREE_FLOAT);
    OffsetF offset;
    auto checkBoxModifier = AceType::MakeRefPtr<CheckBoxModifier>(
        TRUE, Color::BLACK, Color::RED, Color::BLUE, Color::GREEN, size, offset, ONE_FLOAT, TWO_FLOAT);
    ASSERT_NE(checkBoxModifier, nullptr);
    checkBoxPaintMethod->checkboxModifier_ = checkBoxModifier;
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->UpdateCheckBoxSelectedStyle(CheckBoxStyle::CIRCULAR_STYLE);
    checkBoxPaintMethod->UpdateCheckboxColors(checkBoxPaintProperty);
    EXPECT_EQ(checkBoxPaintMethod->checkboxModifier_->checkBoxStyle_, CheckBoxStyle::CIRCULAR_STYLE);
}

/**
 * @tc.name: SetHoverEffectType001
 * @tc.desc: test function SetHoverEffectType
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, SetHoverEffectType001, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    checkBoxNode->eventHub_ = eventHub;
    auto checkBoxPaintMethod = AceType::MakeRefPtr<CheckBoxPaintMethod>();
    ASSERT_NE(checkBoxPaintMethod, nullptr);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->host_ = std::move(checkBoxNode);
    checkBoxPaintMethod->SetHoverEffectType(checkBoxPaintProperty);
    EXPECT_EQ(checkBoxNode->eventHub_->GetInputEventHub(), nullptr);
}

/**
 * @tc.name: SetHoverEffectType002
 * @tc.desc: test function SetHoverEffectType
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, SetHoverEffectType002, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->inputEventHub_ = eventHub->GetOrCreateInputEventHub();
    eventHub->inputEventHub_->hoverEffectType_ = HoverEffectType::OPACITY;
    checkBoxNode->eventHub_ = eventHub;
    auto checkBoxPaintMethod = AceType::MakeRefPtr<CheckBoxPaintMethod>();
    ASSERT_NE(checkBoxPaintMethod, nullptr);
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxPaintProperty->host_ = std::move(checkBoxNode);
    checkBoxPaintMethod->SetHoverEffectType(checkBoxPaintProperty);
    EXPECT_NE(checkBoxNode->eventHub_->GetInputEventHub(), nullptr);
}

/**
 * @tc.name: SetHoverEffectType003
 * @tc.desc: test function SetHoverEffectType
 * @tc.type: FUNC
 */
HWTEST_F(CheckBox2TestNG, SetHoverEffectType003, TestSize.Level1)
{
    auto checkBoxNode =
        FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, NODE_ID, AceType::MakeRefPtr<CheckBoxPattern>());
    ASSERT_NE(checkBoxNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->inputEventHub_ = eventHub->GetOrCreateInputEventHub();
    eventHub->inputEventHub_->hoverEffectType_ = HoverEffectType::AUTO;
    checkBoxNode->eventHub_ = eventHub;
    auto checkBoxPaintMethod = AceType::MakeRefPtr<CheckBoxPaintMethod>();
    ASSERT_NE(checkBoxPaintMethod, nullptr);
    SizeF size(THREE_FLOAT, THREE_FLOAT);
    OffsetF offset;
    auto checkBoxPaintProperty = AceType::MakeRefPtr<CheckBoxPaintProperty>();
    ASSERT_NE(checkBoxPaintProperty, nullptr);
    checkBoxNode->paintProperty_ = checkBoxPaintProperty;
    checkBoxPaintProperty->host_ = std::move(checkBoxNode);
    auto checkBoxModifier = AceType::MakeRefPtr<CheckBoxModifier>(
        TRUE, Color::BLACK, Color::RED, Color::BLUE, Color::GREEN, size, offset, ONE_FLOAT, TWO_FLOAT);
    ASSERT_NE(checkBoxModifier, nullptr);
    checkBoxPaintMethod->checkboxModifier_ = checkBoxModifier;
    checkBoxPaintMethod->SetHoverEffectType(checkBoxPaintProperty);
    EXPECT_EQ(checkBoxPaintMethod->checkboxModifier_->hoverEffectType_, HoverEffectType::AUTO);
}
} // namespace OHOS::Ace::NG
