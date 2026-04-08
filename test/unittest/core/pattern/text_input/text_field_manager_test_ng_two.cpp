/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include <memory>
#include <utility>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "text_input_base.h"

#include "base/memory/ace_type.h"
#include "core/common/ime/text_input_type.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/text_field/text_content_type.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/property/safe_area_insets.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class TextFieldManagerTestNGTwo : public TextInputBases {
public:
};

/**
 * @tc.name: FindCorrectScrollNode001
 * @tc.desc: Test FindCorrectScrollNode when onFocusTextField_ is null
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, FindCorrectScrollNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldManager without focused text field
     */
    TextFieldManagerNG textFieldManager;
    SafeAreaInsets::Inset bottomInset = { 100, 200 };

    /**
     * @tc.expected: step1. Should return nullptr when no focused text field
     */
    auto result = textFieldManager.FindCorrectScrollNode(bottomInset, true);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: FindCorrectScrollNode002
 * @tc.desc: Test FindCorrectScrollNode when frameNode is valid but no scrollable parent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, FindCorrectScrollNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldManager with focused text field but no scrollable parent
     */
    TextFieldManagerNG textFieldManager;

    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    WeakPtr<Pattern> weakPattern(pattern);
    textFieldManager.SetOnFocusTextField(weakPattern);

    SafeAreaInsets::Inset bottomInset = { 100, 200 };

    /**
     * @tc.expected: step1. Should return nullptr when no scrollable parent exists
     */
    auto result = textFieldManager.FindCorrectScrollNode(bottomInset, true);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: ScrollToSafeAreaHelper001
 * @tc.desc: Test ScrollToSafeAreaHelper when onFocusTextField_ is null
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, ScrollToSafeAreaHelper001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldManager without focused text field
     */
    TextFieldManagerNG textFieldManager;
    SafeAreaInsets::Inset bottomInset = { 100, 200 };

    /**
     * @tc.expected: step1. Should return false when no focused text field
     */
    auto result = textFieldManager.ScrollToSafeAreaHelper(bottomInset, true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ScrollToSafeAreaHelper002
 * @tc.desc: Test ScrollToSafeAreaHelper with valid text field but no scrollable parent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, ScrollToSafeAreaHelper002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldManager with focused text field but no scrollable parent
     */
    TextFieldManagerNG textFieldManager;

    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    WeakPtr<Pattern> weakPattern(pattern);
    textFieldManager.SetOnFocusTextField(weakPattern);

    SafeAreaInsets::Inset bottomInset = { 100, 200 };

    /**
     * @tc.expected: step1. Should return false when no scrollable parent exists
     */
    auto result = textFieldManager.ScrollToSafeAreaHelper(bottomInset, true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ScrollTextFieldToSafeArea001
 * @tc.desc: Test ScrollTextFieldToSafeArea when pipeline is null
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, ScrollTextFieldToSafeArea001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call ScrollTextFieldToSafeArea without setting up pipeline
     */
    TextFieldManagerNG textFieldManager;

    /**
     * @tc.expected: step1. Should return false when pipeline is null
     */
    auto result = textFieldManager.ScrollTextFieldToSafeArea();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ScrollTextFieldToSafeArea002
 * @tc.desc: Test ScrollTextFieldToSafeArea with pipeline but no safe area manager
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, ScrollTextFieldToSafeArea002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pipeline context but without safe area manager setup
     */
    TextFieldManagerNG textFieldManager;

    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);

    /**
     * @tc.expected: step1. Should return false when safe area manager is null
     */
    auto result = textFieldManager.ScrollTextFieldToSafeArea();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: FindNavNode001
 * @tc.desc: Test FindNavNode when textField is null
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, FindNavNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call FindNavNode with null parameter
     */
    TextFieldManagerNG textFieldManager;

    /**
     * @tc.expected: step1. Should return nullptr when textField is null
     */
    auto result = textFieldManager.FindNavNode(nullptr);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: FindNavNode002
 * @tc.desc: Test FindNavNode with text field but no navigation ancestor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, FindNavNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field without navigation ancestor
     */
    TextFieldManagerNG textFieldManager;

    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    /**
     * @tc.expected: step1. Should return nullptr when no navigation ancestor exists
     */
    auto result = textFieldManager.FindNavNode(textFieldNode);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: FindNavNode003
 * @tc.desc: Test FindNavNode with Dialog ancestor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, FindNavNode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Dialog node as ancestor
     */
    TextFieldManagerNG textFieldManager;

    auto dialogPattern = AceType::MakeRefPtr<Pattern>();
    auto dialogNode =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), dialogPattern);
    ASSERT_NE(dialogNode, nullptr);

    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    textFieldNode->SetParent(dialogNode);

    /**
     * @tc.expected: step1. Should return dialog node when DIALOG_ETS_TAG is found
     */
    auto result = textFieldManager.FindNavNode(textFieldNode);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result->GetHostTag(), V2::DIALOG_ETS_TAG);
}

/**
 * @tc.name: AvoidKeyboardInSheet001
 * @tc.desc: Test AvoidKeyboardInSheet with null parameter
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, AvoidKeyboardInSheet001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call AvoidKeyboardInSheet with null parameter
     */
    TextFieldManagerNG textFieldManager;
    float heightBefore = textFieldManager.GetHeight();

    /**
     * @tc.expected: step1. Should not crash and state unchanged when textField is null
     */
    textFieldManager.AvoidKeyboardInSheet(nullptr);
    EXPECT_EQ(textFieldManager.GetHeight(), heightBefore);
}

/**
 * @tc.name: AvoidKeyboardInSheet002
 * @tc.desc: Test AvoidKeyboardInSheet with text field but no Sheet ancestor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, AvoidKeyboardInSheet002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field without Sheet ancestor
     */
    TextFieldManagerNG textFieldManager;

    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    float heightBefore = textFieldManager.GetHeight();

    /**
     * @tc.expected: step1. Should not crash and state unchanged when no Sheet ancestor exists
     */
    textFieldManager.AvoidKeyboardInSheet(textFieldNode);
    EXPECT_EQ(textFieldManager.GetHeight(), heightBefore);
}

/**
 * @tc.name: GetOnFocusTextFieldInfo001
 * @tc.desc: Test GetOnFocusTextFieldInfo with null pattern
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, GetOnFocusTextFieldInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetOnFocusTextFieldInfo with null pattern
     */
    TextFieldManagerNG textFieldManager;
    WeakPtr<Pattern> nullPattern;

    /**
     * @tc.expected: step1. Should not crash when pattern is null
     */
    textFieldManager.GetOnFocusTextFieldInfo(nullPattern);
    EXPECT_FALSE(textFieldManager.IsScrollableChild());
}

/**
 * @tc.name: GetOnFocusTextFieldInfo002
 * @tc.desc: Test GetOnFocusTextFieldInfo with valid pattern but no host
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, GetOnFocusTextFieldInfo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without attaching to frame node
     */
    TextFieldManagerNG textFieldManager;

    auto pattern = AceType::MakeRefPtr<Pattern>();
    ASSERT_NE(pattern, nullptr);
    WeakPtr<Pattern> weakPattern(pattern);

    /**
     * @tc.expected: step1. Should not crash when host is null
     */
    textFieldManager.GetOnFocusTextFieldInfo(weakPattern);
    EXPECT_FALSE(textFieldManager.IsScrollableChild());
}

/**
 * @tc.name: GetOnFocusTextFieldInfo003
 * @tc.desc: Test GetOnFocusTextFieldInfo with valid pattern and host but no scrollable parent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, GetOnFocusTextFieldInfo003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field with pattern but no scrollable parent
     */
    TextFieldManagerNG textFieldManager;

    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    WeakPtr<Pattern> weakPattern(pattern);

    /**
     * @tc.expected: step1. Should not crash when scrollable parent is null
     */
    textFieldManager.GetOnFocusTextFieldInfo(weakPattern);
    EXPECT_FALSE(textFieldManager.IsScrollableChild());
}

/**
 * @tc.name: UpdateScrollableParentViewPort001
 * @tc.desc: Test UpdateScrollableParentViewPort with null parameter
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, UpdateScrollableParentViewPort001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call UpdateScrollableParentViewPort with null parameter
     */
    TextFieldManagerNG textFieldManager;
    float heightBefore = textFieldManager.GetHeight();

    /**
     * @tc.expected: step1. Should not crash and state unchanged when node is null
     */
    textFieldManager.UpdateScrollableParentViewPort(nullptr);
    EXPECT_EQ(textFieldManager.GetHeight(), heightBefore);
}

/**
 * @tc.name: UpdateScrollableParentViewPort002
 * @tc.desc: Test UpdateScrollableParentViewPort with valid node but no scrollable parent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, UpdateScrollableParentViewPort002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field without scrollable parent
     */
    TextFieldManagerNG textFieldManager;

    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    float heightBefore = textFieldManager.GetHeight();

    /**
     * @tc.expected: step1. Should not crash and state unchanged when no scrollable parent exists
     */
    textFieldManager.UpdateScrollableParentViewPort(textFieldNode);
    EXPECT_EQ(textFieldManager.GetHeight(), heightBefore);
}

/**
 * @tc.name: AvoidKeyBoardInNavigation001
 * @tc.desc: Test AvoidKeyBoardInNavigation without focused field or nav node
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, AvoidKeyBoardInNavigation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call AvoidKeyBoardInNavigation without setup
     */
    TextFieldManagerNG textFieldManager;

    auto pipeline = PipelineContext::GetCurrentContext();

    /**
     * @tc.expected: step1. Should not crash and state unchanged when pipeline is null or no nav node
     */
    float heightBefore = textFieldManager.GetHeight();
    textFieldManager.AvoidKeyBoardInNavigation();
    EXPECT_EQ(textFieldManager.GetHeight(), heightBefore);
}

/**
 * @tc.name: SetNavContentAvoidKeyboardOffset001
 * @tc.desc: Test SetNavContentAvoidKeyboardOffset with NavDestinationGroupNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, SetNavContentAvoidKeyboardOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create NavDestinationGroupNode and call SetNavContentAvoidKeyboardOffset
     */
    TextFieldManagerNG textFieldManager;

    auto navDestNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestNode, nullptr);

    /**
     * @tc.expected: step1. Should set avoid keyboard offset on NavDestinationPattern
     */
    textFieldManager.SetNavContentAvoidKeyboardOffset(navDestNode, 100.0f);
    auto pattern = navDestNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetAvoidKeyboardOffset(), 100.0f);
}

/**
 * @tc.name: TriggerAvoidOnCaretChange001
 * @tc.desc: Test TriggerAvoidOnCaretChange without focused field
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, TriggerAvoidOnCaretChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call TriggerAvoidOnCaretChange without focused field
     */
    TextFieldManagerNG textFieldManager;
    float heightBefore = textFieldManager.GetHeight();

    /**
     * @tc.expected: step1. Should not crash and state unchanged when no focused field
     */
    textFieldManager.TriggerAvoidOnCaretChange();
    EXPECT_EQ(textFieldManager.GetHeight(), heightBefore);
}

/**
 * @tc.name: TriggerAvoidOnCaretChange002
 * @tc.desc: Test TriggerAvoidOnCaretChange with focused field but no host
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, TriggerAvoidOnCaretChange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without attaching to frame node
     */
    TextFieldManagerNG textFieldManager;

    auto pattern = AceType::MakeRefPtr<Pattern>();
    ASSERT_NE(pattern, nullptr);

    WeakPtr<Pattern> weakPattern(pattern);
    textFieldManager.SetOnFocusTextField(weakPattern);

    float heightBefore = textFieldManager.GetHeight();

    /**
     * @tc.expected: step1. Should not crash and state unchanged when host is null
     */
    textFieldManager.TriggerAvoidOnCaretChange();
    EXPECT_EQ(textFieldManager.GetHeight(), heightBefore);
}

/**
 * @tc.name: TriggerCustomKeyboardAvoid001
 * @tc.desc: Test TriggerCustomKeyboardAvoid without custom keyboard avoid setting
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, TriggerCustomKeyboardAvoid001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call TriggerCustomKeyboardAvoid without setting UsingCustomKeyboardAvoid
     */
    TextFieldManagerNG textFieldManager;

    /**
     * @tc.expected: step1. UsingCustomKeyboardAvoid should be false by default
     */
    EXPECT_FALSE(textFieldManager.UsingCustomKeyboardAvoid());
    textFieldManager.TriggerCustomKeyboardAvoid();
    EXPECT_FALSE(textFieldManager.UsingCustomKeyboardAvoid());
}

/**
 * @tc.name: TriggerCustomKeyboardAvoid002
 * @tc.desc: Test TriggerCustomKeyboardAvoid with UsingCustomKeyboardAvoid but no focused field
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, TriggerCustomKeyboardAvoid002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UsingCustomKeyboardAvoid to true without focused field
     */
    TextFieldManagerNG textFieldManager;
    textFieldManager.SetUsingCustomKeyboardAvoid(true);

    /**
     * @tc.expected: step1. UsingCustomKeyboardAvoid should be true and function should not crash
     */
    EXPECT_TRUE(textFieldManager.UsingCustomKeyboardAvoid());
    textFieldManager.TriggerCustomKeyboardAvoid();
    EXPECT_TRUE(textFieldManager.UsingCustomKeyboardAvoid());
}

/**
 * @tc.name: GetFocusedNodeCaretRect001
 * @tc.desc: Test GetFocusedNodeCaretRect with null focused field
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, GetFocusedNodeCaretRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetFocusedNodeCaretRect without focused field
     */
    TextFieldManagerNG textFieldManager;

    /**
     * @tc.expected: step1. Should return empty RectF when no focused field
     */
    auto result = textFieldManager.GetFocusedNodeCaretRect();
    EXPECT_EQ(result, RectF());
}

/**
 * @tc.name: GetFocusedNodeCaretRect002
 * @tc.desc: Test GetFocusedNodeCaretRect with focused field but no host
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, GetFocusedNodeCaretRect002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without attaching to frame node
     */
    TextFieldManagerNG textFieldManager;

    auto pattern = AceType::MakeRefPtr<Pattern>();
    ASSERT_NE(pattern, nullptr);

    WeakPtr<Pattern> weakPattern(pattern);
    textFieldManager.SetOnFocusTextField(weakPattern);

    /**
     * @tc.expected: step1. Should return empty RectF when host is null
     */
    auto result = textFieldManager.GetFocusedNodeCaretRect();
    EXPECT_EQ(result, RectF());
}

/**
 * @tc.name: FindScrollableOfFocusedTextField001
 * @tc.desc: Test FindScrollableOfFocusedTextField with null parameter
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, FindScrollableOfFocusedTextField001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call FindScrollableOfFocusedTextField with null parameter
     */
    TextFieldManagerNG textFieldManager;

    /**
     * @tc.expected: step1. Should return empty RefPtr when parameter is null
     */
    auto result = textFieldManager.FindScrollableOfFocusedTextField(nullptr);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: FindScrollableOfFocusedTextField002
 * @tc.desc: Test FindScrollableOfFocusedTextField with node but no scrollable parent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNGTwo, FindScrollableOfFocusedTextField002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text field without scrollable parent
     */
    TextFieldManagerNG textFieldManager;

    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    /**
     * @tc.expected: step1. Should return empty RefPtr when no scrollable parent
     */
    auto result = textFieldManager.FindScrollableOfFocusedTextField(textFieldNode);
    EXPECT_EQ(result, nullptr);
}

} // namespace OHOS::Ace::NG