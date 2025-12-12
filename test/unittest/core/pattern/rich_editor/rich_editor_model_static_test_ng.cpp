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
#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"

#include "core/components_ng/pattern/rich_editor/rich_editor_model_static.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_resource_adapter_v2.h"
#include "test/unittest/core/pattern/test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class RichEditorModelStaticTestNg : public TestNG {
};

/**
 * @tc.name: CreateFrameNode001
 * @tc.desc: test CreateFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, CreateFrameNode001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);

    /**
     * @tc.steps: step2. test CreateFrameNode
     */
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));
    auto controller = pattern->GetRichEditorController();
    EXPECT_TRUE(static_cast<bool>(controller));
}

/**
 * @tc.name: InitRichEditorModel001
 * @tc.desc: test InitRichEditorModel
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, InitRichEditorModel001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    auto richEditorPattern = frameNode->GetPattern<RichEditorPattern>();
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();

    EXPECT_TRUE(frameNode->IsFirstBuilding());

    EXPECT_TRUE(richEditorPattern->isTextPreviewSupported_);
    richEditorPattern->SetSupportPreviewText(false);
    EXPECT_FALSE(richEditorPattern->isTextPreviewSupported_);

    /**
     * @tc.steps: step2. init theme
     */
    auto theme = AceType::MakeRefPtr<RichEditorTheme>();
    theme->draggable_ = true;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;

    /**
     * @tc.steps: step3. test InitRichEditorModel
     */
    RichEditorModelStatic::InitRichEditorModel(frameNode);
    EXPECT_TRUE(richEditorPattern->HasSurfaceChangedCallback());
    EXPECT_TRUE(richEditorPattern->HasSurfacePositionChangedCallback());
    EXPECT_TRUE(richEditorPattern->selectionMenuMap_.empty());
    EXPECT_FALSE(frameNode->draggable_);
    EXPECT_TRUE(gestureHub->GetTextDraggable());
}

/**
 * @tc.name: IsStyledStringMode001
 * @tc.desc: test IsStyledStringMode
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, IsStyledStringMode001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    auto node = frameNode.GetRawPtr();

    /**
     * @tc.steps: step2. test IsStyledStringMode
     */
    EXPECT_FALSE(RichEditorModelStatic::IsStyledStringMode(node));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    pattern->isSpanStringMode_ = true;
    EXPECT_TRUE(RichEditorModelStatic::IsStyledStringMode(node));
}

/**
 * @tc.name: GetRichEditorController001
 * @tc.desc: test GetRichEditorController
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetRichEditorController001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    auto node = frameNode.GetRawPtr();

    /**
     * @tc.steps: step2. test GetRichEditorController
     */
    EXPECT_TRUE(RichEditorModelStatic::GetRichEditorController(node));
}

/**
 * @tc.name: GetRichEditorController002
 * @tc.desc: test GetRichEditorController
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetRichEditorController002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto node = frameNode.GetRawPtr();

    /**
     * @tc.steps: step2. test GetRichEditorController
     */
    EXPECT_FALSE(RichEditorModelStatic::GetRichEditorController(node));
}

/**
 * @tc.name: GetRichEditorStyledStringController001
 * @tc.desc: test GetRichEditorStyledStringController
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetRichEditorStyledStringController001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    auto node = frameNode.GetRawPtr();

    /**
     * @tc.steps: step2. test GetRichEditorStyledStringController
     */
    EXPECT_FALSE(RichEditorModelStatic::GetRichEditorStyledStringController(node));
}

/**
 * @tc.name: SetStyledStringMode001
 * @tc.desc: test SetStyledStringMode
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, SetStyledStringMode001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    auto controller = pattern->GetRichEditorController();
    EXPECT_NE(controller, nullptr);

    /**
     * @tc.steps: step2. test SetStyledStringMode
     */
    auto node = frameNode.GetRawPtr();
    RichEditorModelStatic::SetStyledStringMode(node, false);

    auto controller1 = pattern->GetRichEditorController();
    EXPECT_NE(controller1, nullptr);
    EXPECT_NE(controller, controller1);
}

/**
 * @tc.name: SetStyledStringMode002
 * @tc.desc: test SetStyledStringMode
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, SetStyledStringMode002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());

    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    auto controller = pattern->GetRichEditorController();
    EXPECT_NE(controller, nullptr);

    auto styledStringController = pattern->GetRichEditorStyledStringController();
    EXPECT_EQ(styledStringController, nullptr);

    auto styledString = pattern->styledString_;
    EXPECT_EQ(styledString, nullptr);

    /**
     * @tc.steps: step2. test SetStyledStringMode
     */
    auto node = frameNode.GetRawPtr();
    RichEditorModelStatic::SetStyledStringMode(node, true);

    auto controller1 = pattern->GetRichEditorController();
    EXPECT_EQ(controller, controller1);

    auto styledStringController1 = pattern->GetRichEditorStyledStringController();
    EXPECT_NE(styledStringController1, nullptr);
    EXPECT_NE(styledStringController, styledStringController1);

    auto styledString1 = pattern->styledString_;
    EXPECT_NE(styledString, styledString1);
}

/**
 * @tc.name: SetOnCut001
 * @tc.desc: test SetOnCut
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, SetOnCut001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());

    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test SetOnCut
     */
    auto node = frameNode.GetRawPtr();
    std::function<void(NG::TextCommonEvent&)> onCut = [] (NG::TextCommonEvent& event) {};
    RichEditorModelStatic::SetOnCut(node, std::move(onCut));
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    EXPECT_NE(eventHub->onCut_, nullptr);
}

/**
 * @tc.name: SetOnCut002
 * @tc.desc: test SetOnCut
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, SetOnCut002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test SetOnCut
     */
    auto node = frameNode.GetRawPtr();
    RichEditorModelStatic::SetOnCut(node, nullptr);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    EXPECT_EQ(eventHub->onCut_, nullptr);
}

/**
 * @tc.name: SetOnCopy001
 * @tc.desc: test SetOnCopy
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, SetOnCopy001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test SetOnCopy
     */
    auto node = frameNode.GetRawPtr();
    std::function<void(NG::TextCommonEvent&)> onCopy = [] (NG::TextCommonEvent& event) {};
    RichEditorModelStatic::SetOnCopy(node,  std::move(onCopy));
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    EXPECT_NE(eventHub->onCopy_, nullptr);
}

/**
 * @tc.name: SetOnCopy002
 * @tc.desc: test SetOnCopy
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, SetOnCopy002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test SetOnCopy
     */
    auto node = frameNode.GetRawPtr();
    RichEditorModelStatic::SetOnCopy(node, nullptr);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    EXPECT_EQ(eventHub->onCopy_, nullptr);
}

/**
 * @tc.name: SetOnPaste001
 * @tc.desc: test SetOnPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, SetOnPaste001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test SetOnPaste
     */
    auto node = frameNode.GetRawPtr();
    std::function<void(NG::TextCommonEvent&)> onPaste = [] (NG::TextCommonEvent& event) {};
    RichEditorModelStatic::SetOnPaste(node,  std::move(onPaste));
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    EXPECT_NE(eventHub->onPaste_, nullptr);
}

/**
 * @tc.name: SetOnPaste002
 * @tc.desc: test SetOnPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, SetOnPaste002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test SetOnPaste
     */
    auto node = frameNode.GetRawPtr();
    RichEditorModelStatic::SetOnPaste(node, nullptr);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    EXPECT_EQ(eventHub->onPaste_, nullptr);
}

/**
 * @tc.name: SetEnterKeyType001
 * @tc.desc: test SetEnterKeyType
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, SetEnterKeyType001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    auto defaultAction = pattern->GetDefaultTextInputAction();
    EXPECT_EQ(pattern->GetTextInputActionValue(defaultAction), defaultAction);

    /**
     * @tc.steps: step2. test SetEnterKeyType
     */
    auto node = frameNode.GetRawPtr();
    auto action = TextInputAction::GO;
    RichEditorModelStatic::SetEnterKeyType(node, action);
    EXPECT_EQ(pattern->GetTextInputActionValue(defaultAction), TextInputAction::GO);
    EXPECT_NE(pattern->GetTextInputActionValue(defaultAction), defaultAction);

    action = TextInputAction::NONE;
    RichEditorModelStatic::SetEnterKeyType(node, action);
    EXPECT_EQ(pattern->GetTextInputActionValue(defaultAction), TextInputAction::NONE);
    EXPECT_NE(pattern->GetTextInputActionValue(defaultAction), defaultAction);

    action = TextInputAction::SEARCH;
    RichEditorModelStatic::SetEnterKeyType(node, action);
    EXPECT_EQ(pattern->GetTextInputActionValue(defaultAction), TextInputAction::SEARCH);
    EXPECT_NE(pattern->GetTextInputActionValue(defaultAction), defaultAction);

    action = TextInputAction::SEND;
    RichEditorModelStatic::SetEnterKeyType(node, action);
    EXPECT_EQ(pattern->GetTextInputActionValue(defaultAction), TextInputAction::SEND);
    EXPECT_NE(pattern->GetTextInputActionValue(defaultAction), defaultAction);

    action = TextInputAction::NEXT;
    RichEditorModelStatic::SetEnterKeyType(node, action);
    EXPECT_EQ(pattern->GetTextInputActionValue(defaultAction), TextInputAction::NEXT);
    EXPECT_NE(pattern->GetTextInputActionValue(defaultAction), defaultAction);

    action = TextInputAction::DONE;
    RichEditorModelStatic::SetEnterKeyType(node, action);
    EXPECT_EQ(pattern->GetTextInputActionValue(defaultAction), TextInputAction::DONE);
    EXPECT_NE(pattern->GetTextInputActionValue(defaultAction), defaultAction);

    action = TextInputAction::PREVIOUS;
    RichEditorModelStatic::SetEnterKeyType(node, action);
    EXPECT_EQ(pattern->GetTextInputActionValue(defaultAction), TextInputAction::PREVIOUS);
    EXPECT_NE(pattern->GetTextInputActionValue(defaultAction), defaultAction);

    action = TextInputAction::NEW_LINE;
    RichEditorModelStatic::SetEnterKeyType(node, action);
    EXPECT_EQ(pattern->GetTextInputActionValue(defaultAction), TextInputAction::NEW_LINE);
    EXPECT_EQ(pattern->GetTextInputActionValue(defaultAction), defaultAction);

    action = TextInputAction::NEXT;
    RichEditorModelStatic::SetEnterKeyType(node, action);
    EXPECT_EQ(pattern->GetTextInputActionValue(defaultAction), TextInputAction::NEXT);
    EXPECT_NE(pattern->GetTextInputActionValue(defaultAction), defaultAction);
}

/**
 * @tc.name: SetEnterKeyType002
 * @tc.desc: test SetEnterKeyType
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, SetEnterKeyType002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test SetEnterKeyType
     */
    auto node = frameNode.GetRawPtr();
    std::optional<TextInputAction> action = std::nullopt;
    RichEditorModelStatic::SetEnterKeyType(node, action);
    frameNode->MarkModifyDone();
    EXPECT_EQ(pattern->GetTextInputActionValue(pattern->GetDefaultTextInputAction()),
        TextInputAction::NEW_LINE);
}

/**
 * @tc.name: SetAboutToDelete001
 * @tc.desc: test SetAboutToDelete
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, SetAboutToDelete001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test SetAboutToDelete
     */
    auto node = frameNode.GetRawPtr();
    std::function<bool(const RichEditorDeleteValue&)> onDel = [] (const RichEditorDeleteValue& value) { return true; };
    RichEditorModelStatic::SetAboutToDelete(node,  std::move(onDel));
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    EXPECT_NE(eventHub->aboutToDelete_, nullptr);
}

/**
 * @tc.name: SetAboutToDelete002
 * @tc.desc: test SetAboutToDelete
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, SetAboutToDelete002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test SetAboutToDelete
     */
    auto node = frameNode.GetRawPtr();
    RichEditorModelStatic::SetAboutToDelete(node, nullptr);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    EXPECT_EQ(eventHub->aboutToDelete_, nullptr);
}

/**
 * @tc.name: SetEnableHapticFeedback001
 * @tc.desc: test SetEnableHapticFeedback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, SetEnableHapticFeedback001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test SetEnableHapticFeedback
     */
    auto node = frameNode.GetRawPtr();
    RichEditorModelStatic::SetEnableHapticFeedback(node, true);
    EXPECT_TRUE(pattern->isEnableHapticFeedback_);
}

/**
 * @tc.name: SetEnableHapticFeedback002
 * @tc.desc: test SetEnableHapticFeedback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, SetEnableHapticFeedback002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test SetEnableHapticFeedback
     */
    auto node = frameNode.GetRawPtr();
    RichEditorModelStatic::SetEnableHapticFeedback(node, false);
    EXPECT_FALSE(pattern->isEnableHapticFeedback_);
}

/**
 * @tc.name: SetMaxLength001
 * @tc.desc: test SetMaxLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, SetMaxLength001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test SetMaxLength
     */
    auto node = frameNode.GetRawPtr();
    RichEditorModelStatic::SetMaxLength(node, 1);
    EXPECT_EQ(pattern->GetMaxLength(), 1);
}

/**
 * @tc.name: SetMaxLength002
 * @tc.desc: test SetMaxLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, SetMaxLength002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test SetMaxLength
     */
    auto node = frameNode.GetRawPtr();
    RichEditorModelStatic::SetMaxLength(node, std::nullopt);
    EXPECT_EQ(pattern->GetMaxLength(), INT_MAX);
}

/**
 * @tc.name: SetMaxLines
 * @tc.desc: test SetMaxLines
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, SetMaxLines, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    EXPECT_EQ(pattern->GetMaxLines(), INT32_MAX);

    /**
     * @tc.steps: step2. test SetMaxLines
     */
    auto node = frameNode.GetRawPtr();
    RichEditorModelStatic::SetMaxLines(node, 1);
    EXPECT_EQ(pattern->GetMaxLines(), 1);
}

/**
 * @tc.name: BindSelectionMenu
 * @tc.desc: test BindSelectionMenu
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, BindSelectionMenu, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));
    EXPECT_TRUE(pattern->selectionMenuMap_.empty());

    /**
     * @tc.steps: step2. test BindSelectionMenu
     */
    auto node = frameNode.GetRawPtr();
    std::function<void()> func = [] () {};
    SelectMenuParam params;
    auto type = TextSpanType::TEXT;
    auto responseType = TextResponseType::RIGHT_CLICK;
    RichEditorModelStatic::BindSelectionMenu(node, type, responseType, func, params);
    EXPECT_FALSE(pattern->selectionMenuMap_.empty());
    EXPECT_EQ(pattern->selectionMenuMap_.size(), 1);
}

/**
 * @tc.name: SetSelectionMenuOptions
 * @tc.desc: test SetSelectionMenuOptions
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, SetSelectionMenuOptions, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));
    EXPECT_TRUE(static_cast<bool>(pattern->selectOverlay_));
    auto overlay = pattern->selectOverlay_;
    auto callback = overlay->onCreateMenuCallback_;
    EXPECT_FALSE(static_cast<bool>(callback));
    auto click = overlay->onMenuItemClick_;
    EXPECT_FALSE(static_cast<bool>(click));
    auto callback1 = overlay->onPrepareMenuCallback_;
    EXPECT_FALSE(static_cast<bool>(callback1));

    /**
     * @tc.steps: step2. test BindSelectionMenu
     */
    auto node = frameNode.GetRawPtr();
    OnCreateMenuCallback onCreateMenuCallback = [] (const std::vector<NG::MenuItemParam>& params) {
        std::vector<MenuOptionsParam> results;
        return results;
    };
    OnMenuItemClickCallback onMenuItemClick = [] (const NG::MenuItemParam& param) {
        return true;
    };
    SelectMenuParam params;
    RichEditorModelStatic::SetSelectionMenuOptions(node, std::move(onCreateMenuCallback), std::move(onMenuItemClick));
    callback = overlay->onCreateMenuCallback_;
    EXPECT_TRUE(static_cast<bool>(callback));
    click = overlay->onMenuItemClick_;
    EXPECT_TRUE(static_cast<bool>(click));
    callback1 = overlay->onPrepareMenuCallback_;
    EXPECT_FALSE(static_cast<bool>(callback1));
}

/**
 * @tc.name: SetCustomKeyboard
 * @tc.desc: test SetCustomKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, SetCustomKeyboard, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));
    EXPECT_FALSE(pattern->keyboardAvoidance_);
    auto builder = pattern->customKeyboardBuilder_;
    EXPECT_FALSE(static_cast<bool>(builder));

    /**
     * @tc.steps: step2. test SetCustomKeyboard
     */
    auto node = frameNode.GetRawPtr();
    std::function<void()> func = [] () {};
    auto supportAvoidance = true;
    RichEditorModelStatic::SetCustomKeyboard(node, std::move(func), supportAvoidance);
    EXPECT_TRUE(pattern->keyboardAvoidance_);
    builder = pattern->customKeyboardBuilder_;
    EXPECT_TRUE(static_cast<bool>(builder));

    supportAvoidance = false;
    RichEditorModelStatic::SetCustomKeyboard(node, std::move(func), supportAvoidance);
    EXPECT_FALSE(pattern->keyboardAvoidance_);
}
}
