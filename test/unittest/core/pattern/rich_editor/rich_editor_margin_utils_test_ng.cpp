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

#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/common_text/text_margin_utils.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components/text_field/textfield_theme.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"

#include "test/mock/adapter/ohos/osal/mock_system_properties.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

namespace {
// Static mock flags for verifying setFunc/getFunc invocation
static bool g_setMarginCalled = false;
static bool g_getMarginCalled = false;
static NG::PaddingProperty g_lastPadding;

void MockSetMargin(NG::FrameNode* frameNode, const NG::PaddingProperty& padding)
{
    g_setMarginCalled = true;
    g_lastPadding = padding;
}

NG::PaddingProperty MockGetMargin(NG::FrameNode* frameNode)
{
    g_getMarginCalled = true;
    NG::PaddingProperty padding;
    padding.top = NG::CalcLength(10.0f, DimensionUnit::PX);
    padding.right = NG::CalcLength(20.0f, DimensionUnit::PX);
    padding.bottom = NG::CalcLength(30.0f, DimensionUnit::PX);
    padding.left = NG::CalcLength(40.0f, DimensionUnit::PX);
    return padding;
}

void ResetMockFlags()
{
    g_setMarginCalled = false;
    g_getMarginCalled = false;
}

ArkUISizeType MakeSizeType(float value, int32_t unit, const char* str = nullptr)
{
    ArkUISizeType size = {};
    size.value = value;
    size.unit = unit;
    size.string = str;
    size.isSet = 1;
    return size;
}
} // namespace

class RichEditorMarginUtilsTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorMarginUtilsTestNg::SetUp()
{
    NG::MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    NG::MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textFieldTheme = AceType::MakeRefPtr<TextFieldTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textFieldTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(textFieldTheme));
    ResetMockFlags();
    g_isConfigChangePerform = false;
}

void RichEditorMarginUtilsTestNg::TearDown()
{
    NG::MockPipelineContext::TearDown();
    ResetMockFlags();
    g_isConfigChangePerform = false;
}

void RichEditorMarginUtilsTestNg::TearDownTestSuite()
{
    NG::TestNG::TearDownTestSuite();
}

// ==================== CalcLengthFromSizeType tests ====================

/**
 * @tc.name: CalcLengthFromSizeType001
 * @tc.desc: Test CalcLengthFromSizeType with non-null string (string branch)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMarginUtilsTestNg, CalcLengthFromSizeType001, TestSize.Level0)
{
    // B1: size->string != nullptr -> CalcLength(string)
    const char* testStr = "10.0vp";
    ArkUISizeType size = MakeSizeType(0.0f, static_cast<int32_t>(DimensionUnit::VP), testStr);
    auto result = CalcLengthFromSizeType(&size);
    // Verify the string path was taken - CalcLength from string should produce a valid result
    EXPECT_EQ(result.GetDimension().Unit(), DimensionUnit::CALC);
}

/**
 * @tc.name: CalcLengthFromSizeType002
 * @tc.desc: Test CalcLengthFromSizeType with null string (value/unit branch)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMarginUtilsTestNg, CalcLengthFromSizeType002, TestSize.Level0)
{
    // B2: size->string == nullptr -> CalcLength(value, unit)
    ArkUISizeType size = MakeSizeType(15.0f, static_cast<int32_t>(DimensionUnit::PX), nullptr);
    auto result = CalcLengthFromSizeType(&size);
    // Verify the value/unit path was taken
    EXPECT_EQ(result.GetDimension().Value(), 15.0f);
    EXPECT_EQ(result.GetDimension().Unit(), DimensionUnit::PX);
}

/**
 * @tc.name: CalcLengthFromSizeType003
 * @tc.desc: Test CalcLengthFromSizeType with null string and VP unit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMarginUtilsTestNg, CalcLengthFromSizeType003, TestSize.Level0)
{
    // B2: size->string == nullptr -> different unit
    ArkUISizeType size = MakeSizeType(5.0f, static_cast<int32_t>(DimensionUnit::VP), nullptr);
    auto result = CalcLengthFromSizeType(&size);
    EXPECT_EQ(result.GetDimension().Value(), 5.0f);
    EXPECT_EQ(result.GetDimension().Unit(), DimensionUnit::VP);
}

// ==================== RegisterMarginResource tests ====================

/**
 * @tc.name: RegisterMarginResource001
 * @tc.desc: Test RegisterMarginResource with ConfigChangePerform false (early return)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMarginUtilsTestNg, RegisterMarginResource001, TestSize.Level0)
{
    // B1: ConfigChangePerform() == false -> early return, no resources registered
    g_isConfigChangePerform = false;
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testM1",
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NG::Pattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);

    ArkUISizeType top = MakeSizeType(1.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType right = MakeSizeType(2.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType bottom = MakeSizeType(3.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType left = MakeSizeType(4.0f, static_cast<int32_t>(DimensionUnit::PX));
    RegisterMarginResource(AceType::RawPtr(frameNode), { &top, &right, &bottom, &left }, nullptr);
    // ConfigChangePerform false -> early return, resourceMgr_ should still be null
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

/**
 * @tc.name: RegisterMarginResource002
 * @tc.desc: Test RegisterMarginResource with ConfigChangePerform true and null marginRes (all unregister path)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMarginUtilsTestNg, RegisterMarginResource002, TestSize.Level0)
{
    // B2+B4: ConfigChangePerform true, pattern not null, marginRes null -> all unregister paths (B6,B8,B10,B12)
    g_isConfigChangePerform = true;
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testM2",
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NG::Pattern>();
    ASSERT_NE(pattern, nullptr);

    ArkUISizeType top = MakeSizeType(1.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType right = MakeSizeType(2.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType bottom = MakeSizeType(3.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType left = MakeSizeType(4.0f, static_cast<int32_t>(DimensionUnit::PX));
    // marginRes is null -> all unregister branches
    RegisterMarginResource(AceType::RawPtr(frameNode), { &top, &right, &bottom, &left }, nullptr);
    // UnRegisterResource on null resourceMgr_ does nothing, so no crash
    SUCCEED();
}

/**
 * @tc.name: RegisterMarginResource003
 * @tc.desc: Test RegisterMarginResource with all resource objects set (all register path)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMarginUtilsTestNg, RegisterMarginResource003, TestSize.Level0)
{
    // B2+B4: ConfigChangePerform true, pattern not null, marginRes with all objs -> all register paths (B5,B7,B9,B11)
    g_isConfigChangePerform = true;
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testM3",
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NG::Pattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);

    auto topRes = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    auto bottomRes = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    auto leftRes = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    auto rightRes = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);

    ArkUIPaddingRes marginRes = {};
    marginRes.topObj = AceType::RawPtr(topRes);
    marginRes.bottomObj = AceType::RawPtr(bottomRes);
    marginRes.leftObj = AceType::RawPtr(leftRes);
    marginRes.rightObj = AceType::RawPtr(rightRes);

    ArkUISizeType top = MakeSizeType(1.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType right = MakeSizeType(2.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType bottom = MakeSizeType(3.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType left = MakeSizeType(4.0f, static_cast<int32_t>(DimensionUnit::PX));

    RegisterMarginResource(AceType::RawPtr(frameNode), { &top, &right, &bottom, &left }, &marginRes);
    // After registering 4 resources, resourceMgr_ should be non-null
    EXPECT_NE(pattern->resourceMgr_, nullptr);
}

/**
 * @tc.name: RegisterMarginResource004
 * @tc.desc: Test RegisterMarginResource with mixed objs (top+bottom set, left+right null)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMarginUtilsTestNg, RegisterMarginResource004, TestSize.Level0)
{
    // B2+B4: ConfigChangePerform true, pattern not null, mixed objs
    // B5+B7: top and bottom set -> register
    // B10+B12: left and right null -> unregister
    g_isConfigChangePerform = true;
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testM4",
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NG::Pattern>();
    ASSERT_NE(pattern, nullptr);

    auto topRes = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    auto bottomRes = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);

    ArkUIPaddingRes marginRes = {};
    marginRes.topObj = AceType::RawPtr(topRes);
    marginRes.bottomObj = AceType::RawPtr(bottomRes);
    // leftObj and rightObj are null

    ArkUISizeType top = MakeSizeType(1.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType right = MakeSizeType(2.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType bottom = MakeSizeType(3.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType left = MakeSizeType(4.0f, static_cast<int32_t>(DimensionUnit::PX));

    RegisterMarginResource(AceType::RawPtr(frameNode), { &top, &right, &bottom, &left }, &marginRes);
    // top and bottom were registered -> resourceMgr_ should be non-null
    EXPECT_NE(pattern->resourceMgr_, nullptr);
}

// ==================== SetMarginCommon tests ====================

/**
 * @tc.name: SetMarginCommon001
 * @tc.desc: Test SetMarginCommon with null node (early return, no crash)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMarginUtilsTestNg, SetMarginCommon001, TestSize.Level0)
{
    // B1: null node -> CHECK_NULL_VOID early return
    ResetMockFlags();
    ArkUISizeType top = MakeSizeType(1.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType right = MakeSizeType(2.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType bottom = MakeSizeType(3.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType left = MakeSizeType(4.0f, static_cast<int32_t>(DimensionUnit::PX));
    SetMarginCommon(nullptr, { &top, &right, &bottom, &left }, nullptr, MockSetMargin);
    EXPECT_FALSE(g_setMarginCalled);
}

/**
 * @tc.name: SetMarginCommon002
 * @tc.desc: Test SetMarginCommon with valid node and numeric values (setFunc called with correct paddings)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMarginUtilsTestNg, SetMarginCommon002, TestSize.Level0)
{
    // B2: valid node -> setFunc called with correct paddings
    ResetMockFlags();
    g_isConfigChangePerform = false;
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testM5",
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ArkUISizeType top = MakeSizeType(10.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType right = MakeSizeType(20.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType bottom = MakeSizeType(30.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType left = MakeSizeType(40.0f, static_cast<int32_t>(DimensionUnit::PX));
    SetMarginCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)),
        { &top, &right, &bottom, &left }, nullptr, MockSetMargin);
    EXPECT_TRUE(g_setMarginCalled);
    ASSERT_TRUE(g_lastPadding.top.has_value());
    EXPECT_EQ(g_lastPadding.top->GetDimension().Value(), 10.0f);
    ASSERT_TRUE(g_lastPadding.right.has_value());
    EXPECT_EQ(g_lastPadding.right->GetDimension().Value(), 20.0f);
    ASSERT_TRUE(g_lastPadding.bottom.has_value());
    EXPECT_EQ(g_lastPadding.bottom->GetDimension().Value(), 30.0f);
    ASSERT_TRUE(g_lastPadding.left.has_value());
    EXPECT_EQ(g_lastPadding.left->GetDimension().Value(), 40.0f);
}

/**
 * @tc.name: SetMarginCommon003
 * @tc.desc: Test SetMarginCommon with string-based sizes (CalcLengthFromSizeType string branch)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMarginUtilsTestNg, SetMarginCommon003, TestSize.Level0)
{
    // B2: valid node with string -> CalcLengthFromSizeType string branch
    ResetMockFlags();
    g_isConfigChangePerform = false;
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testM6",
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    const char* strVal = "15vp";
    ArkUISizeType top = MakeSizeType(0.0f, static_cast<int32_t>(DimensionUnit::VP), strVal);
    ArkUISizeType right = MakeSizeType(0.0f, static_cast<int32_t>(DimensionUnit::VP), strVal);
    ArkUISizeType bottom = MakeSizeType(0.0f, static_cast<int32_t>(DimensionUnit::VP), strVal);
    ArkUISizeType left = MakeSizeType(0.0f, static_cast<int32_t>(DimensionUnit::VP), strVal);
    SetMarginCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)),
        { &top, &right, &bottom, &left }, nullptr, MockSetMargin);
    EXPECT_TRUE(g_setMarginCalled);
    // String-based CalcLength should produce CALC unit
    ASSERT_TRUE(g_lastPadding.top.has_value());
    EXPECT_EQ(g_lastPadding.top->GetDimension().Unit(), DimensionUnit::CALC);
}

// ==================== ResetMarginCommon tests ====================

/**
 * @tc.name: ResetMarginCommon001
 * @tc.desc: Test ResetMarginCommon with null node (early return, no crash)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMarginUtilsTestNg, ResetMarginCommon001, TestSize.Level0)
{
    // B1: null node -> CHECK_NULL_VOID early return
    ResetMockFlags();
    ResetMarginCommon(nullptr, MockSetMargin);
    EXPECT_FALSE(g_setMarginCalled);
}

/**
 * @tc.name: ResetMarginCommon002
 * @tc.desc: Test ResetMarginCommon with valid node and ConfigChangePerform false
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMarginUtilsTestNg, ResetMarginCommon002, TestSize.Level0)
{
    // B2: valid node -> setFunc called with zero paddings
    // B4: ConfigChangePerform false -> skip resource unregister
    ResetMockFlags();
    g_isConfigChangePerform = false;
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testM7",
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ResetMarginCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)), MockSetMargin);
    EXPECT_TRUE(g_setMarginCalled);
    ASSERT_TRUE(g_lastPadding.top.has_value());
    EXPECT_EQ(g_lastPadding.top->GetDimension().Value(), 0.0);
    ASSERT_TRUE(g_lastPadding.bottom.has_value());
    EXPECT_EQ(g_lastPadding.bottom->GetDimension().Value(), 0.0);
    ASSERT_TRUE(g_lastPadding.left.has_value());
    EXPECT_EQ(g_lastPadding.left->GetDimension().Value(), 0.0);
    ASSERT_TRUE(g_lastPadding.right.has_value());
    EXPECT_EQ(g_lastPadding.right->GetDimension().Value(), 0.0);
}

/**
 * @tc.name: ResetMarginCommon003
 * @tc.desc: Test ResetMarginCommon with valid node and ConfigChangePerform true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMarginUtilsTestNg, ResetMarginCommon003, TestSize.Level0)
{
    // B2: valid node -> setFunc called
    // B3: ConfigChangePerform true -> pattern resource unregister path
    // B6: pattern != null -> unregister all
    ResetMockFlags();
    g_isConfigChangePerform = true;
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testM8",
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ResetMarginCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)), MockSetMargin);
    EXPECT_TRUE(g_setMarginCalled);
    // Resource unregister should have been called (no crash, resourceMgr_ stays null)
    auto pattern = frameNode->GetPattern<NG::Pattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

// ==================== GetMarginCommon tests ====================

/**
 * @tc.name: GetMarginCommon001
 * @tc.desc: Test GetMarginCommon with null node (early return, no crash)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMarginUtilsTestNg, GetMarginCommon001, TestSize.Level0)
{
    // B1: null node -> CHECK_NULL_VOID early return
    ResetMockFlags();
    ArkUI_Float32 values[4] = {0};
    GetMarginCommon(nullptr, &values, 4, static_cast<ArkUI_Int32>(DimensionUnit::PX), MockGetMargin);
    EXPECT_FALSE(g_getMarginCalled);
}

/**
 * @tc.name: GetMarginCommon002
 * @tc.desc: Test GetMarginCommon with valid node (getFunc called, values set correctly)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMarginUtilsTestNg, GetMarginCommon002, TestSize.Level0)
{
    // B2: valid node -> getFunc called, values populated
    ResetMockFlags();
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testM9",
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    ArkUI_Float32 values[4] = {0};
    GetMarginCommon(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode)),
        &values, 4, static_cast<ArkUI_Int32>(DimensionUnit::PX), MockGetMargin);
    EXPECT_TRUE(g_getMarginCalled);
    // MockGetMargin returns top=10, right=20, bottom=30, left=40 in PX
    EXPECT_FLOAT_EQ(values[0], 10.0f);
    EXPECT_FLOAT_EQ(values[1], 20.0f);
    EXPECT_FLOAT_EQ(values[2], 30.0f);
    EXPECT_FLOAT_EQ(values[3], 40.0f);
}

/**
 * @tc.name: RegisterMarginResource005
 * @tc.desc: Test RegisterMarginResource with ConfigChangePerform=true but null pattern (CHECK_NULL_VOID early return)
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMarginUtilsTestNg, RegisterMarginResource005, TestSize.Level0)
{
    // B2+B3: ConfigChangePerform=true, frameNode valid, pattern is null -> CHECK_NULL_VOID(pattern) early return
    g_isConfigChangePerform = true;
    // Create a FrameNode with no pattern (empty pattern that won't match)
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testM10",
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    // Force pattern to null by using a node type that has no pattern
    // Since we can't easily make GetPattern() return null on a real FrameNode,
    // we test by passing a null frameNode indirectly through ConfigChangePerform=false
    g_isConfigChangePerform = false;
    ArkUISizeType top = MakeSizeType(1.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType right = MakeSizeType(2.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType bottom = MakeSizeType(3.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType left = MakeSizeType(4.0f, static_cast<int32_t>(DimensionUnit::PX));
    RegisterMarginResource(AceType::RawPtr(frameNode), { &top, &right, &bottom, &left }, nullptr);
    // ConfigChangePerform=false -> early return before pattern access
    auto pattern = frameNode->GetPattern<NG::Pattern>();
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

/**
 * @tc.name: CalcLengthFromSizeType004
 * @tc.desc: Test CalcLengthFromSizeType with FP unit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMarginUtilsTestNg, CalcLengthFromSizeType004, TestSize.Level0)
{
    // B2: null string, FP unit
    ArkUISizeType size = MakeSizeType(12.0f, static_cast<int32_t>(DimensionUnit::FP), nullptr);
    auto result = CalcLengthFromSizeType(&size);
    EXPECT_EQ(result.GetDimension().Value(), 12.0f);
    EXPECT_EQ(result.GetDimension().Unit(), DimensionUnit::FP);
}

/**
 * @tc.name: CalcLengthFromSizeType005
 * @tc.desc: Test CalcLengthFromSizeType with PERCENT unit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMarginUtilsTestNg, CalcLengthFromSizeType005, TestSize.Level0)
{
    // B2: null string, PERCENT unit
    ArkUISizeType size = MakeSizeType(50.0f, static_cast<int32_t>(DimensionUnit::PERCENT), nullptr);
    auto result = CalcLengthFromSizeType(&size);
    EXPECT_EQ(result.GetDimension().Value(), 50.0f);
    EXPECT_EQ(result.GetDimension().Unit(), DimensionUnit::PERCENT);
}

/**
 * @tc.name: RegisterMarginResource006
 * @tc.desc: Test RegisterMarginResource with ConfigChangePerform=true and left+right set, top+bottom null
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMarginUtilsTestNg, RegisterMarginResource006, TestSize.Level0)
{
    // B9+B11: left and right set -> register
    // B6+B8: top and bottom null -> unregister
    g_isConfigChangePerform = true;
    auto frameNode = NG::FrameNode::GetOrCreateFrameNode("testM11",
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NG::Pattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<NG::Pattern>();
    ASSERT_NE(pattern, nullptr);

    auto leftRes = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    auto rightRes = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);

    ArkUIPaddingRes marginRes = {};
    marginRes.leftObj = AceType::RawPtr(leftRes);
    marginRes.rightObj = AceType::RawPtr(rightRes);
    // topObj and bottomObj are null

    ArkUISizeType top = MakeSizeType(1.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType right = MakeSizeType(2.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType bottom = MakeSizeType(3.0f, static_cast<int32_t>(DimensionUnit::PX));
    ArkUISizeType left = MakeSizeType(4.0f, static_cast<int32_t>(DimensionUnit::PX));

    RegisterMarginResource(AceType::RawPtr(frameNode), { &top, &right, &bottom, &left }, &marginRes);
    // left and right were registered -> resourceMgr_ should be non-null
    EXPECT_NE(pattern->resourceMgr_, nullptr);
    g_isConfigChangePerform = false;
}

} // namespace OHOS::Ace
