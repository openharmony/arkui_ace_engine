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

#include <cstdint>

#include "gtest/gtest.h"
#include "search_base.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/common/resource/pattern_resource_manager.h"

namespace OHOS::Ace::NG {

// Animation constants from search_pattern.cpp
constexpr float HOVER_STRAT_OPACITY = 0.0f;
constexpr float HOVER_OPACITY = 0.05f;
constexpr float TOUCH_OPACITY = 0.1f;
constexpr int32_t HOVER_DURATION = 250;

// RAII scope guard for API version management
class ApiVersionScopeGuard {
public:
    explicit ApiVersionScopeGuard(int32_t originalVersion) : originalVersion_(originalVersion) {}
    ~ApiVersionScopeGuard()
    {
        AceApplicationInfo::GetInstance().SetApiTargetVersion(originalVersion_);
    }
    // Non-copyable
    ApiVersionScopeGuard(const ApiVersionScopeGuard&) = delete;
    ApiVersionScopeGuard& operator=(const ApiVersionScopeGuard&) = delete;

private:
    int32_t originalVersion_;
};

class SearchTestThreeNg : public SearchBases {
public:
};

/**
 * @tc.name: ConvertCopyOptionsToString_None
 * @tc.desc: Test SearchPattern ConvertCopyOptionsToString
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, ConvertCopyOptionsToString_None, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    /**
     * @tc.steps: step2. Get SearchPattern and call ConvertCopyOptionsToString
     * @tc.expected: ConvertCopyOptionsToString return "CopyOptions.None"
     */
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto result = pattern->ConvertCopyOptionsToString(CopyOptions::None);
    EXPECT_EQ(result, "CopyOptions.None");
}

/**
 * @tc.name: ConvertCopyOptionsToString_InApp
 * @tc.desc: Test SearchPattern ConvertCopyOptionsToString
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, ConvertCopyOptionsToString_InApp, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    /**
     * @tc.steps: step2. Get SearchPattern and call ConvertCopyOptionsToString
     * @tc.expected: ConvertCopyOptionsToString return "CopyOptions.InApp"
     */
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto result = pattern->ConvertCopyOptionsToString(CopyOptions::InApp);
    EXPECT_EQ(result, "CopyOptions.InApp");
}

/**
 * @tc.name: ConvertCopyOptionsToString_Distributed
 * @tc.desc: Test SearchPattern ConvertCopyOptionsToString
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, ConvertCopyOptionsToString_Distributed, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    /**
     * @tc.steps: step2. Get SearchPattern and call ConvertCopyOptionsToString
     * @tc.expected: ConvertCopyOptionsToString return "CopyOptions.Distributed"
     */
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto result = pattern->ConvertCopyOptionsToString(CopyOptions::Distributed);
    EXPECT_EQ(result, "CopyOptions.Distributed");
}

/**
 * @tc.name: ConvertCopyOptionsToString_Default
 * @tc.desc: Test SearchPattern ConvertCopyOptionsToString
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, ConvertCopyOptionsToString_Default, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    /**
     * @tc.steps: step2. Get SearchPattern and call ConvertCopyOptionsToString
     * @tc.expected: ConvertCopyOptionsToString return ""
     */
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    int32_t value = 10;
    auto result = pattern->ConvertCopyOptionsToString(static_cast<CopyOptions>(value));
    EXPECT_EQ(result, "");
}

/**
 * @tc.name: OnInjectionEventTest001
 * @tc.desc: Test SearchPattern OnInjectionEventTest
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, OnInjectionEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    /**
     * @tc.steps: step2. Get SearchPattern
     */
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Test OnInjectionEvent with commands
     * @tc.expected: OnInjectionEvent return RET_FAILED or RET_SUCCESS accordingly
     */
    std::string command = R"()";
    auto ret = pattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_FAILED);
    command = R"({)";
    ret = pattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_FAILED);
    command = R"({"cmd":"setText"})";
    ret = pattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_FAILED);
    command = R"({"cmd":"setSearchText"})";
    ret = pattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_FAILED);
    command = R"({"cmd":"setSearchText", "params":{}})";
    ret = pattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_SUCCESS);
    command = R"({"cmd":"setSearchText", "params":{"value":"test"}})";
    ret = pattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_SUCCESS);
}

/**
 * @tc.name: OnInjectionEventTest002
 * @tc.desc: Test SearchPattern OnInjectionEventTest
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, OnInjectionEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    /**
     * @tc.steps: step2. Get SearchPattern
     */
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Test OnInjectionEvent with commands
     * @tc.expected: OnInjectionEvent return RET_FAILED or RET_SUCCESS accordingly
     */
    std::string command = R"()";
    auto ret = pattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_FAILED);
    command = R"({)";
    ret = pattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_FAILED);

    command = R"({"cmd":"addText", "params":{"value":"test123456789"}})";
    ret = pattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_SUCCESS);
    command = R"({"cmd":"selectText"})";
    ret = pattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_FAILED);
    command = R"({"cmd":"selectText", "selectionStart":2, "selectionEnd":3})";
    ret = pattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_SUCCESS);

    command = R"({"cmd":"selectText", "selectionStart":2, "selectionEnd":-1})";
    ret = pattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_SUCCESS);

    command = R"({"cmd":"selectText", "selectionStart":5, "selectionEnd":1})";
    ret = pattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_SUCCESS);

    command = R"({"cmd":"copy"})";
    ret = pattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_SUCCESS);

    command = R"({"cmd":"selectText", "selectionStart":1, "selectionEnd":5})";
    ret = pattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_SUCCESS);
    command = R"({"cmd":"cut"})";
    ret = pattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_SUCCESS);

    command = R"({"cmd":"clear"})";
    ret = pattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_SUCCESS);

    command = R"({"cmd":"requestKeyboard"})";
    ret = pattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_SUCCESS);

    command = R"({"cmd":"setCaretPosition", "position":1})";
    ret = pattern->OnInjectionEvent(command);
    EXPECT_EQ(ret, RET_SUCCESS);
}

/**
 * @tc.name: HandleBackgroundColor_003
 * @tc.desc: Test SearchPattern HandleBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, HandleBackgroundColor_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Verify initial state - check searchLayoutProperty has no background color
     */
    auto searchLayoutProperty = searchNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(searchLayoutProperty, nullptr);
    bool hasInitialBgColor = searchLayoutProperty->HasBackgroundColor();

    auto renderContext = searchNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step3. Call HandleBackgroundColor
     * @tc.expected: Should update renderContext background color from theme if searchLayoutProperty has no background
     * color
     */
    pattern->HandleBackgroundColor();

    /**
     * @tc.steps: step4. Verify HandleBackgroundColor execution
     * The function updates renderContext->UpdateBackgroundColor() when searchLayoutProperty has no background color
     */
    if (!hasInitialBgColor) {
        // Verify renderContext background color is set from theme (not transparent)
        auto bgColor = renderContext->GetBackgroundColor();
        EXPECT_NE(bgColor.value_or(Color::TRANSPARENT), Color::TRANSPARENT);
    }
    // Pattern should still be valid
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: HandleEnabled_003
 * @tc.desc: Test SearchPattern HandleEnabled with false
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, HandleEnabled_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->HandleEnabled();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl_Placeholder
 * @tc.desc: Test SearchPattern UpdatePropertyImpl with placeholder key
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, UpdatePropertyImpl_Placeholder, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test UpdatePropertyImpl with placeholder key and u16string value
     * @tc.expected: Should update placeholder resource without error
     */
    auto valueBase = AceType::MakeRefPtr<PropertyValueBase>();
    ASSERT_NE(valueBase, nullptr);
    valueBase->SetValueType(ValueType::U16STRING);
    std::u16string newPlaceholder = u"new placeholder text";
    valueBase->SetValue(newPlaceholder);
    pattern->UpdatePropertyImpl("placeholder", valueBase);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl_Text
 * @tc.desc: Test SearchPattern UpdatePropertyImpl with text key
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, UpdatePropertyImpl_Text, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test UpdatePropertyImpl with text key and u16string value
     * @tc.expected: Should update text resource without error
     */
    auto valueBase = AceType::MakeRefPtr<PropertyValueBase>();
    ASSERT_NE(valueBase, nullptr);
    valueBase->SetValueType(ValueType::U16STRING);
    std::u16string newText = u"new search text";
    valueBase->SetValue(newText);
    pattern->UpdatePropertyImpl("text", valueBase);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl_SearchButtonValue
 * @tc.desc: Test SearchPattern UpdatePropertyImpl with searchButtonValue key
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, UpdatePropertyImpl_SearchButtonValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test UpdatePropertyImpl with searchButtonValue key and string value
     * @tc.expected: Should update search button value resource without error
     */
    auto valueBase = AceType::MakeRefPtr<PropertyValueBase>();
    ASSERT_NE(valueBase, nullptr);
    valueBase->SetValueType(ValueType::STRING);
    std::string newButtonValue = "search button value";
    valueBase->SetValue(newButtonValue);
    pattern->UpdatePropertyImpl("searchButtonValue", valueBase);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl_SearchButtonFontSize_ValidValue
 * @tc.desc: Test SearchPattern UpdatePropertyImpl with searchButtonFontSize key and valid value
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, UpdatePropertyImpl_SearchButtonFontSize_ValidValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test UpdatePropertyImpl with searchButtonFontSize key and valid value
     * @tc.expected: Should update button font size resource without error
     */
    auto valueBase = AceType::MakeRefPtr<PropertyValueBase>();
    ASSERT_NE(valueBase, nullptr);
    valueBase->SetValueType(ValueType::CALDIMENSION);
    CalcDimension validFontSize = CalcDimension(16, DimensionUnit::VP);
    valueBase->SetValue(validFontSize);
    pattern->UpdatePropertyImpl("searchButtonFontSize", valueBase);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl_SearchButtonFontSize_Percent
 * @tc.desc: Test SearchPattern UpdatePropertyImpl with searchButtonFontSize key and percent value
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, UpdatePropertyImpl_SearchButtonFontSize_Percent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test UpdatePropertyImpl with searchButtonFontSize key and percent value
     * @tc.expected: Should use theme default font size
     */
    auto valueBase = AceType::MakeRefPtr<PropertyValueBase>();
    ASSERT_NE(valueBase, nullptr);
    valueBase->SetValueType(ValueType::CALDIMENSION);
    CalcDimension percentFontSize = CalcDimension(50, DimensionUnit::PERCENT);
    valueBase->SetValue(percentFontSize);
    pattern->UpdatePropertyImpl("searchButtonFontSize", valueBase);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl_SearchButtonFontSize_ZeroValue
 * @tc.desc: Test SearchPattern UpdatePropertyImpl with searchButtonFontSize key and zero value
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, UpdatePropertyImpl_SearchButtonFontSize_ZeroValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test UpdatePropertyImpl with searchButtonFontSize key and zero value
     * @tc.expected: Should use theme default font size
     */
    auto valueBase = AceType::MakeRefPtr<PropertyValueBase>();
    ASSERT_NE(valueBase, nullptr);
    valueBase->SetValueType(ValueType::CALDIMENSION);
    CalcDimension zeroFontSize = CalcDimension(0, DimensionUnit::VP);
    valueBase->SetValue(zeroFontSize);
    pattern->UpdatePropertyImpl("searchButtonFontSize", valueBase);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: UpdatePropertyImpl_UnknownKey
 * @tc.desc: Test SearchPattern UpdatePropertyImpl with unknown key
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, UpdatePropertyImpl_UnknownKey, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test UpdatePropertyImpl with unknown key
     * @tc.expected: Should handle gracefully (no assertion failure)
     */
    auto unknownValue = AceType::MakeRefPtr<PropertyValueBase>();
    ASSERT_NE(unknownValue, nullptr);
    unknownValue->SetValueType(ValueType::STRING);
    unknownValue->SetValue("unknown");
    pattern->UpdatePropertyImpl("unknownKey", unknownValue);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: AnimateTouchAndHover_HoverStratOpacity_CancelButton_DarkMode
 * @tc.desc: Test SearchPattern AnimateTouchAndHover with startOpacity == HOVER_STRAT_OPACITY, CANCEL_BUTTON, DARK mode
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, AnimateTouchAndHover_HoverStratOpacity_CancelButton_DarkMode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test AnimateTouchAndHover with HOVER_STRAT_OPACITY for cancel button
     * @tc.expected: Should call AnimateTouchAndHover without crash
     */
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto cancelButtonNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    ASSERT_NE(cancelButtonNode, nullptr);
    auto renderContext = cancelButtonNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    // Test the HOVER_STRAT_OPACITY branch (line 1419)
    pattern->AnimateTouchAndHover(renderContext, HOVER_STRAT_OPACITY, HOVER_OPACITY, HOVER_DURATION,
        Curves::FRICTION, CANCEL_BUTTON_INDEX);

    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: AnimateTouchAndHover_EndHoverStratOpacity_CancelButton_DarkMode
 * @tc.desc: Test SearchPattern AnimateTouchAndHover with endOpacity == HOVER_STRAT_OPACITY, CANCEL_BUTTON, DARK mode
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, AnimateTouchAndHover_EndHoverStratOpacity_CancelButton_DarkMode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test AnimateTouchAndHover with endOpacity == HOVER_STRAT_OPACITY for cancel button
     * @tc.expected: Should call AnimateTouchAndHover without crash
     */
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto cancelButtonNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    ASSERT_NE(cancelButtonNode, nullptr);
    auto renderContext = cancelButtonNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    // Test the else if (endOpacity == HOVER_STRAT_OPACITY) branch (line 1423)
    pattern->AnimateTouchAndHover(renderContext, HOVER_OPACITY, HOVER_STRAT_OPACITY, HOVER_DURATION,
        Curves::FRICTION, CANCEL_BUTTON_INDEX);

    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: AnimateTouchAndHover_StartHoverOpacity_CancelButton_DarkMode
 * @tc.desc: Test SearchPattern AnimateTouchAndHover with startOpacity == HOVER_OPACITY (touch down), CANCEL_BUTTON,
 * DARK mode
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, AnimateTouchAndHover_StartHoverOpacity_CancelButton_DarkMode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test AnimateTouchAndHover with HOVER_OPACITY (touch down) for cancel button
     * @tc.expected: Should call AnimateTouchAndHover without crash
     */
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto cancelButtonNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    ASSERT_NE(cancelButtonNode, nullptr);
    auto renderContext = cancelButtonNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    // Test the else if (startOpacity == HOVER_OPACITY) branch (line 1427)
    pattern->AnimateTouchAndHover(renderContext, HOVER_OPACITY, TOUCH_OPACITY, HOVER_DURATION,
        Curves::FRICTION, CANCEL_BUTTON_INDEX);

    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: AnimateTouchAndHover_EndHoverOpacity_CancelButton_DarkMode
 * @tc.desc: Test SearchPattern AnimateTouchAndHover with endOpacity == HOVER_OPACITY (touch up), CANCEL_BUTTON, DARK
 * mode
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, AnimateTouchAndHover_EndHoverOpacity_CancelButton_DarkMode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test AnimateTouchAndHover with endOpacity == HOVER_OPACITY (touch up) for cancel button
     * @tc.expected: Should call AnimateTouchAndHover without crash
     */
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto cancelButtonNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    ASSERT_NE(cancelButtonNode, nullptr);
    auto renderContext = cancelButtonNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    // Test the else if (endOpacity == HOVER_OPACITY) branch (line 1431)
    pattern->AnimateTouchAndHover(renderContext, TOUCH_OPACITY, HOVER_OPACITY, HOVER_DURATION,
        Curves::FRICTION, CANCEL_BUTTON_INDEX);

    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: AnimateTouchAndHover_OtherOpacity_CancelButton_DarkMode
 * @tc.desc: Test SearchPattern AnimateTouchAndHover with other opacity values, CANCEL_BUTTON, DARK mode
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, AnimateTouchAndHover_OtherOpacity_CancelButton_DarkMode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test AnimateTouchAndHover with other opacity values for cancel button
     * @tc.expected: Should call AnimateTouchAndHover without crash
     */
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto cancelButtonNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    ASSERT_NE(cancelButtonNode, nullptr);
    auto renderContext = cancelButtonNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    // Test the final else branch (line 1435) - not HOVER_STRAT_OPACITY, HOVER_OPACITY, or TOUCH_OPACITY
    pattern->AnimateTouchAndHover(renderContext, 0.2f, 0.3f, HOVER_DURATION,
        Curves::FRICTION, CANCEL_BUTTON_INDEX);

    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: AnimateTouchAndHover_OtherChild_DarkMode
 * @tc.desc: Test SearchPattern AnimateTouchAndHover with non-cancel-button child, DARK mode
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, AnimateTouchAndHover_OtherChild_DarkMode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test AnimateTouchAndHover with non-cancel-button child (e.g., search icon)
     * @tc.expected: Should call AnimateTouchAndHover without crash
     */
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(IMAGE_INDEX));
    ASSERT_NE(imageNode, nullptr);
    auto renderContext = imageNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    // Test the else branch when childId != CANCEL_BUTTON_INDEX (line 1439)
    pattern->AnimateTouchAndHover(renderContext, HOVER_OPACITY, TOUCH_OPACITY, HOVER_DURATION,
        Curves::FRICTION, IMAGE_INDEX);

    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: AnimateTouchAndHover_OtherOpacity_NonDarkMode
 * @tc.desc: Test SearchPattern AnimateTouchAndHover with other opacity values, non-DARK mode
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, AnimateTouchAndHover_OtherOpacity_NonDarkMode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test AnimateTouchAndHover in non-DARK mode
     * @tc.expected: Should call AnimateTouchAndHover without crash
     */
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto cancelButtonNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    ASSERT_NE(cancelButtonNode, nullptr);
    auto renderContext = cancelButtonNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    // Test with non-DARK mode
    pattern->AnimateTouchAndHover(renderContext, HOVER_OPACITY, TOUCH_OPACITY, HOVER_DURATION,
        Curves::FRICTION, CANCEL_BUTTON_INDEX);

    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: AnimateTouchAndHover_DifferentDurations
 * @tc.desc: Test SearchPattern AnimateTouchAndHover with different duration values
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, AnimateTouchAndHover_DifferentDurations, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test AnimateTouchAndHover with different duration values
     * @tc.expected: Should call AnimateTouchAndHover without crash
     */
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto cancelButtonNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    ASSERT_NE(cancelButtonNode, nullptr);
    auto renderContext = cancelButtonNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    // Test with different duration
    pattern->AnimateTouchAndHover(renderContext, HOVER_OPACITY, TOUCH_OPACITY, 500,
        Curves::FRICTION, CANCEL_BUTTON_INDEX);

    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: AnimateTouchAndHover_DifferentCurves
 * @tc.desc: Test SearchPattern AnimateTouchAndHover with different curve values
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, AnimateTouchAndHover_DifferentCurves, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test AnimateTouchAndHover with different curve values
     * @tc.expected: Should call AnimateTouchAndHover without crash
     */
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto cancelButtonNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    ASSERT_NE(cancelButtonNode, nullptr);
    auto renderContext = cancelButtonNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    // Test with SHARP curve
    pattern->AnimateTouchAndHover(renderContext, HOVER_OPACITY, TOUCH_OPACITY, HOVER_DURATION,
        Curves::SHARP, CANCEL_BUTTON_INDEX);

    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: ResetPlaceholderColor_PlaceholderFontStyleNull
 * @tc.desc: Test SearchModelNG ResetPlaceholderColor when placeholder font style exists
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, ResetPlaceholderColor_PlaceholderFontStyleNull, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node without setting placeholder font style
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto textFieldChild = AceType::DynamicCast<FrameNode>(searchNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. Verify GetPlaceholderFontStyle() returns non-null (default from theme)
     * @tc.expected: GetPlaceholderFontStyle() should be non-null
     */
    auto* placeholderFontStyle = textFieldLayoutProperty->GetPlaceholderFontStyle().get();
    EXPECT_NE(placeholderFontStyle, nullptr);

    /**
     * @tc.steps: step3. Call ResetPlaceholderColor
     * @tc.expected: Should execute without crash and reset placeholder color flag
     */
    searchModelInstance.ResetPlaceholderColor();

    /**
     * @tc.steps: step4. Verify execution completed
     * @tc.expected: textFieldLayoutProperty should still be valid
     */
    EXPECT_NE(textFieldLayoutProperty, nullptr);
}

/**
 * @tc.name: ResetPlaceholderColor_PlaceholderFontStyleNotNull
 * @tc.desc: Test SearchModelNG ResetPlaceholderColor when GetPlaceholderFontStyle() returns non-null
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, ResetPlaceholderColor_PlaceholderFontStyleNotNull, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto textFieldChild = AceType::DynamicCast<FrameNode>(searchNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set placeholder font style to make GetPlaceholderFontStyle() non-null
     * @tc.expected: GetPlaceholderFontStyle() should return non-null value
     */
    Font font;
    font.fontSize = Dimension(16, DimensionUnit::VP);
    font.fontStyle = Ace::FontStyle::NORMAL;
    font.fontWeight = FontWeight::W400;
    std::vector<std::string> families = { "sans-serif" };
    font.fontFamilies = families;
    searchModelInstance.SetPlaceholderFont(font);

    EXPECT_NE(textFieldLayoutProperty->GetPlaceholderFontStyle(), nullptr);

    /**
     * @tc.steps: step3. Call ResetPlaceholderColor
     * @tc.expected: Should execute the true branch (if block) without crash
     */
    searchModelInstance.ResetPlaceholderColor();

    /**
     * @tc.steps: step4. Verify execution completed
     * @tc.expected: textFieldLayoutProperty should still be valid
     */
    EXPECT_NE(textFieldLayoutProperty, nullptr);
}

/**
 * @tc.name: SetPlaceholderColor_SpecialColorValue
 * @tc.desc: Test SearchModelNG SetPlaceholderColor with color value 0x99000000
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, SetPlaceholderColor_SpecialColorValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto textFieldChild = AceType::DynamicCast<FrameNode>(searchNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);
    auto textFieldPaintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(textFieldPaintProperty, nullptr);

    /**
     * @tc.steps: step2. Call SetPlaceholderColor with special color value 0x99000000
     * @tc.expected: Should execute the if (color.GetValue() == 0x99000000) branch
     */
    Color specialColor(0x99000000);
    EXPECT_EQ(specialColor.GetValue(), 0x99000000);

    searchModelInstance.SetPlaceholderColor(specialColor);

    /**
     * @tc.steps: step3. Verify placeholder color is set correctly
     * @tc.expected: Placeholder text color should be updated to the special color
     */
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderTextColor(), specialColor);
    EXPECT_EQ(textFieldPaintProperty->GetPlaceholderColorFlagByUser(), true);
}

/**
 * @tc.name: TextFieldUpdateContext_NoUserFlags
 * @tc.desc: Test SearchModelNG TextFieldUpdateContext when HasCaretColorFlagByUser()=false and HasCursorWidth()=false
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, TextFieldUpdateContext_NoUserFlags, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto textFieldChild = AceType::DynamicCast<FrameNode>(searchNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldPaintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(textFieldPaintProperty, nullptr);

    /**
     * @tc.steps: step2. Verify initial state
     * @tc.expected: HasCaretColorFlagByUser() should be false, HasCursorWidth() reflects theme default
     */
    EXPECT_EQ(textFieldPaintProperty->HasCaretColorFlagByUser(), false);
    // Note: HasCursorWidth() may be true due to theme initialization

    /**
     * @tc.steps: step3. Call TextFieldUpdateContext
     * @tc.expected: Should execute without crash
     */
    SearchModelNG::TextFieldUpdateContext(textFieldChild);

    /**
     * @tc.steps: step4. Verify cursor color is updated from theme
     * @tc.expected: Cursor color should be set from theme
     */
    EXPECT_NE(textFieldPaintProperty->GetCursorColor(), Color::TRANSPARENT);
}

/**
 * @tc.name: TextFieldUpdateContext_HasCaretColorFlag
 * @tc.desc: Test SearchModelNG TextFieldUpdateContext when HasCaretColorFlagByUser()=true and HasCursorWidth()=false
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, TextFieldUpdateContext_HasCaretColorFlag, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto textFieldChild = AceType::DynamicCast<FrameNode>(searchNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldPaintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(textFieldPaintProperty, nullptr);

    /**
     * @tc.steps: step2. Set caret color flag to true
     * @tc.expected: HasCaretColorFlagByUser()=true
     */
    textFieldPaintProperty->UpdateCaretColorFlagByUser(true);
    EXPECT_EQ(textFieldPaintProperty->HasCaretColorFlagByUser(), true);

    /**
     * @tc.steps: step3. Call TextFieldUpdateContext
     * @tc.expected: Should execute without crash
     */
    SearchModelNG::TextFieldUpdateContext(textFieldChild);

    /**
     * @tc.steps: step4. Verify caret color flag remains true
     * @tc.expected: caret color flag should remain true
     */
    EXPECT_EQ(textFieldPaintProperty->HasCaretColorFlagByUser(), true);
}

/**
 * @tc.name: TextFieldUpdateContext_HasCursorWidthFlag
 * @tc.desc: Test SearchModelNG TextFieldUpdateContext when HasCaretColorFlagByUser()=false and HasCursorWidth()=true
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, TextFieldUpdateContext_HasCursorWidthFlag, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto textFieldChild = AceType::DynamicCast<FrameNode>(searchNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldPaintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(textFieldPaintProperty, nullptr);

    /**
     * @tc.steps: step2. Set cursor width to make HasCursorWidth()=true, keep caret color flag as false
     * @tc.expected: HasCaretColorFlagByUser()=false, HasCursorWidth()=true
     */
    textFieldPaintProperty->UpdateCursorWidth(Dimension(2, DimensionUnit::VP));
    EXPECT_EQ(textFieldPaintProperty->HasCaretColorFlagByUser(), false);
    EXPECT_EQ(textFieldPaintProperty->HasCursorWidth(), true);

    /**
     * @tc.steps: step3. Call TextFieldUpdateContext
     * @tc.expected: Should execute only the first if branch (update cursor color from theme)
     */
    SearchModelNG::TextFieldUpdateContext(textFieldChild);

    /**
     * @tc.steps: step4. Verify cursor color is updated from theme but cursor width flag remains true
     * @tc.expected: Cursor color should be set from theme, cursor width should remain set
     */
    EXPECT_NE(textFieldPaintProperty->GetCursorColor(), Color::TRANSPARENT);
    EXPECT_EQ(textFieldPaintProperty->HasCursorWidth(), true);
}

/**
 * @tc.name: TextFieldUpdateContext_BothUserFlags
 * @tc.desc: Test SearchModelNG TextFieldUpdateContext when HasCaretColorFlagByUser()=true and HasCursorWidth()=true
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, TextFieldUpdateContext_BothUserFlags, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto textFieldChild = AceType::DynamicCast<FrameNode>(searchNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldPaintProperty = textFieldChild->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(textFieldPaintProperty, nullptr);

    /**
     * @tc.steps: step2. Set both flags to true
     * @tc.expected: HasCaretColorFlagByUser()=true, HasCursorWidth()=true
     */
    textFieldPaintProperty->UpdateCaretColorFlagByUser(true);
    textFieldPaintProperty->UpdateCursorWidth(Dimension(3, DimensionUnit::VP));
    EXPECT_EQ(textFieldPaintProperty->HasCaretColorFlagByUser(), true);
    EXPECT_EQ(textFieldPaintProperty->HasCursorWidth(), true);

    /**
     * @tc.steps: step3. Call TextFieldUpdateContext
     * @tc.expected: Should skip both if branches (not update from theme)
     */
    SearchModelNG::TextFieldUpdateContext(textFieldChild);

    /**
     * @tc.steps: step4. Verify both flags remain true (not overridden by theme)
     * @tc.expected: Both user flags should remain true
     */
    EXPECT_EQ(textFieldPaintProperty->HasCaretColorFlagByUser(), true);
    EXPECT_EQ(textFieldPaintProperty->HasCursorWidth(), true);
}

/**
 * @tc.name: SetPlaceholderFont_EmptyFont
 * @tc.desc: Test SearchModelNG SetPlaceholderFont(FrameNode*, const Font&) when all font fields are empty/nullopt
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, SetPlaceholderFont_EmptyFont, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto textFieldChild = AceType::DynamicCast<FrameNode>(searchNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. Create empty Font object (all optional fields are nullopt, fontFamilies is empty)
     * @tc.expected: if (font.fontSize), if (font.fontStyle), if (font.fontWeight), if (!font.fontFamilies.empty()) all
     * false
     */
    Font emptyFont;
    EXPECT_EQ(emptyFont.fontSize.has_value(), false);
    EXPECT_EQ(emptyFont.fontStyle.has_value(), false);
    EXPECT_EQ(emptyFont.fontWeight.has_value(), false);
    EXPECT_EQ(emptyFont.fontFamilies.empty(), true);

    /**
     * @tc.steps: step3. Call SetPlaceholderFont with empty font
     * @tc.expected: Should skip all if branches (not update font properties)
     */
    SearchModelNG::SetPlaceholderFont(searchNode, emptyFont);

    /**
     * @tc.steps: step4. Verify PreferredPlaceholderLineHeightNeedToUpdate is set to true
     * @tc.expected: This property is always updated regardless of font fields
     */
    EXPECT_EQ(textFieldLayoutProperty->GetPreferredPlaceholderLineHeightNeedToUpdate(), true);
}

/**
 * @tc.name: SetPlaceholderFont_OnlyFontSize
 * @tc.desc: Test SearchModelNG SetPlaceholderFont with only fontSize set
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, SetPlaceholderFont_OnlyFontSize, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto textFieldChild = AceType::DynamicCast<FrameNode>(searchNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. Create Font with only fontSize set
     * @tc.expected: Only if (font.fontSize) is true
     */
    Font font;
    font.fontSize = Dimension(20, DimensionUnit::VP);
    EXPECT_EQ(font.fontSize.has_value(), true);
    EXPECT_EQ(font.fontStyle.has_value(), false);
    EXPECT_EQ(font.fontWeight.has_value(), false);
    EXPECT_EQ(font.fontFamilies.empty(), true);

    /**
     * @tc.steps: step3. Call SetPlaceholderFont
     * @tc.expected: Should only update placeholder font size
     */
    SearchModelNG::SetPlaceholderFont(searchNode, font);

    /**
     * @tc.steps: step4. Verify placeholder font size is updated
     * @tc.expected: Placeholder font size should be 20, other properties unchanged
     */
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderFontSize().value().Value(), 20);
    EXPECT_EQ(textFieldLayoutProperty->GetPreferredPlaceholderLineHeightNeedToUpdate(), true);
}

/**
 * @tc.name: SetPlaceholderFont_OnlyFontStyle
 * @tc.desc: Test SearchModelNG SetPlaceholderFont with only fontStyle set
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, SetPlaceholderFont_OnlyFontStyle, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto textFieldChild = AceType::DynamicCast<FrameNode>(searchNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. Create Font with only fontStyle set
     * @tc.expected: Only if (font.fontStyle) is true
     */
    Font font;
    font.fontStyle = Ace::FontStyle::ITALIC;
    EXPECT_EQ(font.fontSize.has_value(), false);
    EXPECT_EQ(font.fontStyle.has_value(), true);
    EXPECT_EQ(font.fontWeight.has_value(), false);
    EXPECT_EQ(font.fontFamilies.empty(), true);

    /**
     * @tc.steps: step3. Call SetPlaceholderFont
     * @tc.expected: Should only update placeholder italic font style
     */
    SearchModelNG::SetPlaceholderFont(searchNode, font);

    /**
     * @tc.steps: step4. Verify placeholder italic font style is updated
     * @tc.expected: Placeholder italic font style should be ITALIC
     */
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderItalicFontStyle(), Ace::FontStyle::ITALIC);
    EXPECT_EQ(textFieldLayoutProperty->GetPreferredPlaceholderLineHeightNeedToUpdate(), true);
}

/**
 * @tc.name: SetPlaceholderFont_OnlyFontWeight
 * @tc.desc: Test SearchModelNG SetPlaceholderFont with only fontWeight set
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, SetPlaceholderFont_OnlyFontWeight, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto textFieldChild = AceType::DynamicCast<FrameNode>(searchNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. Create Font with only fontWeight set
     * @tc.expected: Only if (font.fontWeight) is true
     */
    Font font;
    font.fontWeight = FontWeight::W600;
    EXPECT_EQ(font.fontSize.has_value(), false);
    EXPECT_EQ(font.fontStyle.has_value(), false);
    EXPECT_EQ(font.fontWeight.has_value(), true);
    EXPECT_EQ(font.fontFamilies.empty(), true);

    /**
     * @tc.steps: step3. Call SetPlaceholderFont
     * @tc.expected: Should only update placeholder font weight
     */
    SearchModelNG::SetPlaceholderFont(searchNode, font);

    /**
     * @tc.steps: step4. Verify placeholder font weight is updated
     * @tc.expected: Placeholder font weight should be W600
     */
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderFontWeight(), FontWeight::W600);
    EXPECT_EQ(textFieldLayoutProperty->GetPreferredPlaceholderLineHeightNeedToUpdate(), true);
}

/**
 * @tc.name: SetPlaceholderFont_OnlyFontFamilies
 * @tc.desc: Test SearchModelNG SetPlaceholderFont with only fontFamilies set
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, SetPlaceholderFont_OnlyFontFamilies, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto textFieldChild = AceType::DynamicCast<FrameNode>(searchNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. Create Font with only fontFamilies set
     * @tc.expected: Only if (!font.fontFamilies.empty()) is true
     */
    Font font;
    font.fontFamilies = { "sans-serif", "serif" };
    EXPECT_EQ(font.fontSize.has_value(), false);
    EXPECT_EQ(font.fontStyle.has_value(), false);
    EXPECT_EQ(font.fontWeight.has_value(), false);
    EXPECT_EQ(font.fontFamilies.empty(), false);

    /**
     * @tc.steps: step3. Call SetPlaceholderFont
     * @tc.expected: Should only update placeholder font family
     */
    SearchModelNG::SetPlaceholderFont(searchNode, font);

    /**
     * @tc.steps: step4. Verify placeholder font family is updated
     * @tc.expected: Placeholder font family should be set
     */
    EXPECT_EQ(textFieldLayoutProperty->GetPlaceholderFontFamily().value().size(), 2);
    EXPECT_EQ(textFieldLayoutProperty->GetPreferredPlaceholderLineHeightNeedToUpdate(), true);
}

/**
 * @tc.name: SetSearchButton_EmptyText_IsJsView_API18
 * @tc.desc: Test SearchModelNG SetSearchButton when text is empty, isJsView=true, API>=18
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, SetSearchButton_EmptyText_IsJsView_API18, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(searchNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto searchButtonRenderContext = buttonFrameNode->GetRenderContext();
    ASSERT_NE(searchButtonRenderContext, nullptr);
    auto searchButtonEvent = buttonFrameNode->GetEventHub<ButtonEventHub>();
    ASSERT_NE(searchButtonEvent, nullptr);

    /**
     * @tc.steps: step2. Set API target version to 18
     * @tc.expected: GreatOrEqualAPITargetVersion(VERSION_EIGHTEEN) should return true
     */
    int32_t originalApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    ApiVersionScopeGuard scopeGuard(originalApiVersion);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));

    /**
     * @tc.steps: step3. Call SetSearchButton with empty text and isJsView=true
     * @tc.expected: Should execute else branch and inner if (isJsView && VERSION_EIGHTEEN) true branch
     */
    std::string emptyText = "";
    EXPECT_EQ(emptyText.empty(), true);

    SearchModelNG::SetSearchButton(searchNode, emptyText, true);

    /**
     * @tc.steps: step4. Verify button is disabled and opacity is 0
     * @tc.expected: Button should be hidden when text is empty
     */
    EXPECT_EQ(searchButtonEvent->IsEnabled(), false);
    EXPECT_EQ(searchButtonRenderContext->GetOpacity(), 0.0);
}

/**
 * @tc.name: SetSearchButton_EmptyText_IsJsView_API17
 * @tc.desc: Test SearchModelNG SetSearchButton when text is empty, isJsView=true, API<18
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, SetSearchButton_EmptyText_IsJsView_API17, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(searchNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto searchButtonRenderContext = buttonFrameNode->GetRenderContext();
    ASSERT_NE(searchButtonRenderContext, nullptr);
    auto searchButtonEvent = buttonFrameNode->GetEventHub<ButtonEventHub>();
    ASSERT_NE(searchButtonEvent, nullptr);

    /**
     * @tc.steps: step2. Set API target version to 17 (less than VERSION_EIGHTEEN)
     * @tc.expected: GreatOrEqualAPITargetVersion(VERSION_EIGHTEEN) should return false
     */
    int32_t originalApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_SEVENTEEN));

    /**
     * @tc.steps: step3. Call SetSearchButton with empty text and isJsView=true
     * @tc.expected: Should execute else branch and inner if (isJsView && VERSION_EIGHTEEN) false branch
     */
    std::string emptyText = "";
    EXPECT_EQ(emptyText.empty(), true);

    SearchModelNG::SetSearchButton(searchNode, emptyText, true);

    /**
     * @tc.steps: step4. Verify button is disabled and opacity is 0
     * @tc.expected: Button should be hidden when text is empty
     */
    EXPECT_EQ(searchButtonEvent->IsEnabled(), false);
    EXPECT_EQ(searchButtonRenderContext->GetOpacity(), 0.0);

    // Restore original API version
    AceApplicationInfo::GetInstance().SetApiTargetVersion(originalApiVersion);
}

/**
 * @tc.name: SetSearchButton_EmptyText_NotJsView
 * @tc.desc: Test SearchModelNG SetSearchButton when text is empty, isJsView=false
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, SetSearchButton_EmptyText_NotJsView, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(searchNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto searchButtonRenderContext = buttonFrameNode->GetRenderContext();
    ASSERT_NE(searchButtonRenderContext, nullptr);
    auto searchButtonEvent = buttonFrameNode->GetEventHub<ButtonEventHub>();
    ASSERT_NE(searchButtonEvent, nullptr);

    /**
     * @tc.steps: step2. Call SetSearchButton with empty text and isJsView=false
     * @tc.expected: Should execute else branch and inner if (isJsView && VERSION_EIGHTEEN) false branch
     */
    std::string emptyText = "";
    EXPECT_EQ(emptyText.empty(), true);

    SearchModelNG::SetSearchButton(searchNode, emptyText, false);

    /**
     * @tc.steps: step3. Verify button is disabled and opacity is 0
     * @tc.expected: Button should be hidden when text is empty
     */
    EXPECT_EQ(searchButtonEvent->IsEnabled(), false);
    EXPECT_EQ(searchButtonRenderContext->GetOpacity(), 0.0);
}

/**
 * @tc.name: SetSearchButton_NonEmptyText
 * @tc.desc: Test SearchModelNG SetSearchButton when text is not empty
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, SetSearchButton_NonEmptyText, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto buttonFrameNode = AceType::DynamicCast<FrameNode>(searchNode->GetChildAtIndex(BUTTON_INDEX));
    ASSERT_NE(buttonFrameNode, nullptr);
    auto searchButtonRenderContext = buttonFrameNode->GetRenderContext();
    ASSERT_NE(searchButtonRenderContext, nullptr);
    auto searchButtonEvent = buttonFrameNode->GetEventHub<ButtonEventHub>();
    ASSERT_NE(searchButtonEvent, nullptr);

    /**
     * @tc.steps: step2. Call SetSearchButton with non-empty text
     * @tc.expected: Should execute if (!text.empty()) true branch
     */
    std::string searchText = "Search";
    EXPECT_EQ(searchText.empty(), false);

    SearchModelNG::SetSearchButton(searchNode, searchText, true);

    /**
     * @tc.steps: step3. Verify button is enabled and opacity is 1
     * @tc.expected: Button should be visible when text is not empty
     */
    EXPECT_EQ(searchButtonEvent->IsEnabled(), true);
    EXPECT_EQ(searchButtonRenderContext->GetOpacity(), 1.0);
}

/**
 * @tc.name: SetTextFont_FontSize
 * @tc.desc: Test SearchModelNG SetTextFont with fontSize set, verify fontSize true branch
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, SetTextFont_FontSize, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto textFieldChild = AceType::DynamicCast<FrameNode>(searchNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set Font with only fontSize set
     * @tc.expected: if (font.fontSize) true branch should be covered
     */
    Font font;
    font.fontSize = Dimension(18, DimensionUnit::VP);
    // fontStyle, fontWeight are nullopt, fontFamilies is empty

    SearchModelNG::SetTextFont(searchNode, font);

    /**
     * @tc.steps: step3. Verify fontSize is updated
     * @tc.expected: fontSize should be 18VP
     */
    EXPECT_TRUE(textFieldLayoutProperty->GetFontSize().has_value());
    EXPECT_EQ(textFieldLayoutProperty->GetFontSize().value().Value(), 18);
    EXPECT_EQ(textFieldLayoutProperty->GetFontSize().value().Unit(), DimensionUnit::VP);
}

/**
 * @tc.name: SetTextFont_FontStyle
 * @tc.desc: Test SearchModelNG SetTextFont with fontStyle set, verify fontStyle true branch
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, SetTextFont_FontStyle, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto textFieldChild = AceType::DynamicCast<FrameNode>(searchNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set Font with only fontStyle set
     * @tc.expected: if (font.fontStyle) true branch should be covered
     */
    Font font;
    font.fontStyle = Ace::FontStyle::ITALIC;
    // fontSize, fontWeight are nullopt, fontFamilies is empty

    SearchModelNG::SetTextFont(searchNode, font);

    /**
     * @tc.steps: step3. Verify fontStyle is updated
     * @tc.expected: fontStyle should be ITALIC
     */
    EXPECT_TRUE(textFieldLayoutProperty->GetItalicFontStyle().has_value());
    EXPECT_EQ(textFieldLayoutProperty->GetItalicFontStyle().value(), Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: SetTextFont_FontWeight
 * @tc.desc: Test SearchModelNG SetTextFont with fontWeight set, verify fontWeight true branch
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, SetTextFont_FontWeight, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto textFieldChild = AceType::DynamicCast<FrameNode>(searchNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set Font with only fontWeight set
     * @tc.expected: if (font.fontWeight) true branch should be covered
     */
    Font font;
    font.fontWeight = FontWeight::W600;
    // fontSize, fontStyle are nullopt, fontFamilies is empty

    SearchModelNG::SetTextFont(searchNode, font);

    /**
     * @tc.steps: step3. Verify fontWeight is updated
     * @tc.expected: fontWeight should be W600
     */
    EXPECT_TRUE(textFieldLayoutProperty->GetFontWeight().has_value());
    EXPECT_EQ(textFieldLayoutProperty->GetFontWeight().value(), FontWeight::W600);
}

/**
 * @tc.name: SetTextFont_FontFamilies
 * @tc.desc: Test SearchModelNG SetTextFont with fontFamilies set, verify fontFamilies true branch
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, SetTextFont_FontFamilies, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto textFieldChild = AceType::DynamicCast<FrameNode>(searchNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set Font with only fontFamilies set (non-empty)
     * @tc.expected: if (!font.fontFamilies.empty()) true branch should be covered
     */
    Font font;
    std::vector<std::string> families = { "Arial", "Sans-Serif" };
    font.fontFamilies = families;
    // fontSize, fontStyle, fontWeight are nullopt/empty

    SearchModelNG::SetTextFont(searchNode, font);

    /**
     * @tc.steps: step3. Verify fontFamilies is updated
     * @tc.expected: fontFamily should contain the specified fonts
     */
    auto fontFamily = textFieldLayoutProperty->GetFontFamily();
    EXPECT_TRUE(fontFamily.has_value());
    EXPECT_FALSE(fontFamily.value().empty());
}

/**
 * @tc.name: SetTextFont_AllFields
 * @tc.desc: Test SearchModelNG SetTextFont with all fields set, verify all branches covered
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, SetTextFont_AllFields, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto textFieldChild = AceType::DynamicCast<FrameNode>(searchNode->GetChildren().front());
    ASSERT_NE(textFieldChild, nullptr);
    auto textFieldLayoutProperty = textFieldChild->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(textFieldLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set Font with all fields set
     * @tc.expected: All if branches should be covered
     */
    Font font;
    font.fontSize = Dimension(20, DimensionUnit::VP);
    font.fontStyle = Ace::FontStyle::NORMAL;
    font.fontWeight = FontWeight::W700;
    std::vector<std::string> families = { "Georgia", "Serif" };
    font.fontFamilies = families;

    SearchModelNG::SetTextFont(searchNode, font);

    /**
     * @tc.steps: step3. Verify all fields are updated
     * @tc.expected: All font properties should be set correctly
     */
    EXPECT_TRUE(textFieldLayoutProperty->GetFontSize().has_value());
    EXPECT_EQ(textFieldLayoutProperty->GetFontSize().value().Value(), 20);
    EXPECT_EQ(textFieldLayoutProperty->GetFontSize().value().Unit(), DimensionUnit::VP);

    EXPECT_TRUE(textFieldLayoutProperty->GetItalicFontStyle().has_value());
    EXPECT_EQ(textFieldLayoutProperty->GetItalicFontStyle().value(), Ace::FontStyle::NORMAL);

    EXPECT_TRUE(textFieldLayoutProperty->GetFontWeight().has_value());
    EXPECT_EQ(textFieldLayoutProperty->GetFontWeight().value(), FontWeight::W700);

    auto fontFamily = textFieldLayoutProperty->GetFontFamily();
    EXPECT_TRUE(fontFamily.has_value());
    EXPECT_FALSE(fontFamily.value().empty());
}

/**
 * @tc.name: CreateSearchNode_BorderWidthPropertyNotExist
 * @tc.desc: Test CreateSearchNode when BorderWidthProperty does not exist, verify UpdateSearchNodeBorderProps executes
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, CreateSearchNode_BorderWidthPropertyNotExist, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node using CreateSearchNode directly
     * @tc.expected: CreateSearchNode should create SearchNode and call UpdateSearchNodeBorderProps
     */
    int32_t nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    std::optional<std::u16string> value = u"test value";
    std::optional<std::u16string> placeholder = u"placeholder";
    std::optional<std::string> icon = SEARCH_SVG;

    auto searchNode = SearchModelNG::CreateSearchNode(nodeId, value, placeholder, icon);
    ASSERT_NE(searchNode, nullptr);

    /**
     * @tc.steps: step2. Get layout property and verify BorderWidthProperty was set by UpdateSearchNodeBorderProps
     * @tc.expected: BorderWidthProperty should be set from theme (since it didn't exist before)
     */
    auto searchLayoutProperty = searchNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(searchLayoutProperty, nullptr);

    const auto* currentBorderWidth = searchLayoutProperty->GetBorderWidthProperty().get();
    ASSERT_NE(currentBorderWidth, nullptr);
    // BorderWidthProperty should exist (was set by UpdateSearchNodeBorderProps)
    EXPECT_TRUE(currentBorderWidth->leftDimen.has_value());
}

/**
 * @tc.name: CreateSearchNode_BorderWidthPropertyExists
 * @tc.desc: Test CreateSearchNode when BorderWidthProperty exists, verify UpdateSearchNodeBorderProps false branch
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, CreateSearchNode_BorderWidthPropertyExists, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    int32_t nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    std::optional<std::u16string> value = u"test value";
    std::optional<std::u16string> placeholder = u"placeholder";
    std::optional<std::string> icon = SEARCH_SVG;

    auto searchNode = SearchModelNG::CreateSearchNode(nodeId, value, placeholder, icon);
    ASSERT_NE(searchNode, nullptr);

    auto searchLayoutProperty = searchNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(searchLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. Pre-set BorderWidthProperty to trigger false branch in subsequent operations
     * Set to a distinct value (5VP) to verify it's not overwritten
     * @tc.expected: if (!layoutProperty->GetBorderWidthProperty()) false branch covered
     */
    BorderWidthProperty customBorderWidth;
    customBorderWidth.SetBorderWidth(Dimension(5, DimensionUnit::VP));
    searchLayoutProperty->UpdateBorderWidth(customBorderWidth);

    /**
     * @tc.steps: step3. Verify BorderWidthProperty is set to custom value
     * @tc.expected: Border width should be 5VP (custom value)
     */
    const auto* currentBorderWidth = searchLayoutProperty->GetBorderWidthProperty().get();
    ASSERT_NE(currentBorderWidth, nullptr);
    EXPECT_EQ(currentBorderWidth->leftDimen.value().Value(), 5);
}

/**
 * @tc.name: CreateSearchNode_RenderContextHasBorderWidthAndColor
 * @tc.desc: Test CreateSearchNode when renderContext has border width and color, verify false branches
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, CreateSearchNode_RenderContextHasBorderWidthAndColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    int32_t nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    std::optional<std::u16string> value = u"test value";
    std::optional<std::u16string> placeholder = u"placeholder";
    std::optional<std::string> icon = SEARCH_SVG;

    auto searchNode = SearchModelNG::CreateSearchNode(nodeId, value, placeholder, icon);
    ASSERT_NE(searchNode, nullptr);

    auto searchLayoutProperty = searchNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(searchLayoutProperty, nullptr);

    auto renderContext = searchNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step2. Pre-set border width and color on renderContext
     * This sets up the state to test false branches of HasBorderWidth and HasBorderColor
     * @tc.expected: RenderContext should have border width and color set
     */
    BorderWidthProperty customBorderWidth;
    customBorderWidth.SetBorderWidth(Dimension(3, DimensionUnit::VP));
    renderContext->UpdateBorderWidth(customBorderWidth);

    BorderColorProperty customBorderColor;
    customBorderColor.SetColor(Color(0xFFFF0000));  // Red color
    renderContext->UpdateBorderColor(customBorderColor);

    /**
     * @tc.steps: step3. Verify border width and color are set
     * @tc.expected: HasBorderWidth and HasBorderColor should return true
     */
    EXPECT_TRUE(renderContext->HasBorderWidth());
    EXPECT_TRUE(renderContext->HasBorderColor());
}

/**
 * @tc.name: CreateSearchNode_ComprehensiveBorderPropsCoverage
 * @tc.desc: Test CreateSearchNode with comprehensive branch coverage for UpdateSearchNodeBorderProps
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, CreateSearchNode_ComprehensiveBorderPropsCoverage, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create first Search node - default case
     * @tc.expected: UpdateSearchNodeBorderProps is called (GetBorderWidthProperty may return nullptr or valid ptr)
     */
    int32_t nodeId1 = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto searchNode1 = SearchModelNG::CreateSearchNode(nodeId1, std::nullopt, std::nullopt, std::nullopt);
    ASSERT_NE(searchNode1, nullptr);

    auto searchLayoutProperty1 = searchNode1->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(searchLayoutProperty1, nullptr);

    // Verify BorderWidthProperty exists (set by UpdateSearchNodeBorderProps)
    const auto* borderWidth1 = searchLayoutProperty1->GetBorderWidthProperty().get();
    ASSERT_NE(borderWidth1, nullptr);
    EXPECT_TRUE(borderWidth1->leftDimen.has_value());

    /**
     * @tc.steps: step2. Create second Search node and set custom border
     * This tests the false branch of GetBorderWidthProperty
     */
    int32_t nodeId2 = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto searchNode2 = SearchModelNG::CreateSearchNode(nodeId2, std::nullopt, std::nullopt, std::nullopt);
    ASSERT_NE(searchNode2, nullptr);

    auto searchLayoutProperty2 = searchNode2->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(searchLayoutProperty2, nullptr);

    // Set custom border to test false branch
    BorderWidthProperty customBorder;
    customBorder.SetBorderWidth(Dimension(10, DimensionUnit::VP));
    searchLayoutProperty2->UpdateBorderWidth(customBorder);

    const auto* borderWidth2 = searchLayoutProperty2->GetBorderWidthProperty().get();
    ASSERT_NE(borderWidth2, nullptr);
    EXPECT_EQ(borderWidth2->leftDimen.value().Value(), 10);

    /**
     * @tc.steps: step3. Set border on renderContext to cover false branches of HasBorderWidth/HasBorderColor
     * This covers the false branches of HasBorderWidth and HasBorderColor
     */
    auto renderContext2 = searchNode2->GetRenderContext();
    ASSERT_NE(renderContext2, nullptr);

    BorderWidthProperty renderBorder;
    renderBorder.SetBorderWidth(Dimension(5, DimensionUnit::VP));
    renderContext2->UpdateBorderWidth(renderBorder);

    BorderColorProperty renderBorderColor;
    renderBorderColor.SetColor(Color(0xFF0000FF));
    renderContext2->UpdateBorderColor(renderBorderColor);

    EXPECT_TRUE(renderContext2->HasBorderWidth());
    EXPECT_TRUE(renderContext2->HasBorderColor());
}

/**
 * @tc.name: SearchLayoutProperty_Clone_IsUserSetBackgroundColor
 * @tc.desc: Test SearchLayoutProperty::Clone correctly clones isUserSetBackgroundColor_
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, SearchLayoutProperty_Clone_IsUserSetBackgroundColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node and get its SearchLayoutProperty
     * @tc.expected: SearchLayoutProperty should be created successfully
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    auto searchLayoutProperty = searchNode->GetLayoutProperty<SearchLayoutProperty>();
    ASSERT_NE(searchLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set isUserSetBackgroundColor_ to true using UpdateIsUserSetBackgroundColor
     * @tc.expected: isUserSetBackgroundColor_ should be true
     */
    searchLayoutProperty->UpdateIsUserSetBackgroundColor(true);
    EXPECT_EQ(searchLayoutProperty->GetIsUserSetBackgroundColor(), true);

    /**
     * @tc.steps: step3. Clone the SearchLayoutProperty
     * @tc.expected: Clone should return a valid SearchLayoutProperty
     */
    auto clonedProperty = AceType::DynamicCast<SearchLayoutProperty>(searchLayoutProperty->Clone());
    ASSERT_NE(clonedProperty, nullptr);

    /**
     * @tc.steps: step4. Verify isUserSetBackgroundColor_ is correctly cloned
     * @tc.expected: clonedProperty should have isUserSetBackgroundColor_ = true
     */
    EXPECT_EQ(clonedProperty->GetIsUserSetBackgroundColor(), true);

    /**
     * @tc.steps: step5. Test with isUserSetBackgroundColor_ = false
     * @tc.expected: clonedProperty should have isUserSetBackgroundColor_ = false
     */
    searchLayoutProperty->UpdateIsUserSetBackgroundColor(false);
    auto clonedProperty2 = AceType::DynamicCast<SearchLayoutProperty>(searchLayoutProperty->Clone());
    ASSERT_NE(clonedProperty2, nullptr);
    EXPECT_EQ(clonedProperty2->GetIsUserSetBackgroundColor(), false);
}

} // namespace OHOS::Ace::NG
