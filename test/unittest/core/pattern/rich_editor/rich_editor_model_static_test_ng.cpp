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
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/common/mock_resource_adapter_v2.h"
#include "test/unittest/core/pattern/test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class RichEditorModelStaticTestNg : public TestNG {
private:
    static constexpr uint32_t DEFAULT_BLACK_COLOR = 0xff000000;
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

/**
 * @tc.name: CreateRichEditorStyledStringNode001
 * @tc.desc: test CreateRichEditorStyledStringNode
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, CreateRichEditorStyledStringNode001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. mock theme manager
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto richEditorTheme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(richEditorTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(richEditorTheme));
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    /**
     * @tc.steps: step2. create styled string node
     */
    int32_t nodeId = 100;
    auto frameNode = RichEditorModelNG::CreateRichEditorStyledStringNode(nodeId);

    /**
     * @tc.steps: step3. test CreateRichEditorStyledStringNode
     */
    EXPECT_TRUE(static_cast<bool>(frameNode));
    EXPECT_EQ(V2::RICH_EDITOR_ETS_TAG, frameNode->GetTag());
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));
    
    // Check if it's in styled string mode
    EXPECT_TRUE(pattern->isSpanStringMode_);
    
    // Check if styled string controller is created
    auto styledStringController = pattern->GetRichEditorStyledStringController();
    EXPECT_TRUE(static_cast<bool>(styledStringController));
    
    // Check if styled string is created
    auto styledString = pattern->styledString_;
    EXPECT_TRUE(static_cast<bool>(styledString));
}

/**
 * @tc.name: CreateRichEditorStyledStringNode002
 * @tc.desc: test CreateRichEditorStyledStringNode with same node id
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, CreateRichEditorStyledStringNode002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. mock theme manager
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto richEditorTheme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(richEditorTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(richEditorTheme));
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    /**
     * @tc.steps: step2. create styled string node with same node id twice
     */
    int32_t nodeId = 200;
    auto frameNode1 = RichEditorModelNG::CreateRichEditorStyledStringNode(nodeId);
    auto frameNode2 = RichEditorModelNG::CreateRichEditorStyledStringNode(nodeId);
    // test that same node is returned for same node id
    EXPECT_EQ(frameNode1, frameNode2);
}

/**
 * @tc.name: GetCustomKeyboardNode001
 * @tc.desc: test GetCustomKeyboardNode with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetCustomKeyboardNode001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetCustomKeyboardNode with no custom keyboard node
     */
    auto customKeyboardNode = RichEditorModelNG::GetCustomKeyboardNode(frameNode.GetRawPtr());
    EXPECT_FALSE(static_cast<bool>(customKeyboardNode));

    /**
     * @tc.steps: step3. set custom keyboard node and test again
     */
    auto uiNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1000, AceType::MakeRefPtr<TextPattern>());
    pattern->customKeyboardNode_ = uiNode;
    customKeyboardNode = RichEditorModelNG::GetCustomKeyboardNode(frameNode.GetRawPtr());
    EXPECT_TRUE(static_cast<bool>(customKeyboardNode));
    EXPECT_EQ(customKeyboardNode, uiNode);
    
    /**
     * @tc.steps: step4. test GetCustomKeyboardNode with null frame node
     */
    customKeyboardNode = RichEditorModelNG::GetCustomKeyboardNode(nullptr);
    EXPECT_FALSE(static_cast<bool>(customKeyboardNode));
}

/**
 * @tc.name: GetCustomKeyboardOption001
 * @tc.desc: test GetCustomKeyboardOption with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetCustomKeyboardOption001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetCustomKeyboardOption with default value
     */
    bool option = RichEditorModelNG::GetCustomKeyboardOption(frameNode.GetRawPtr());
    EXPECT_FALSE(option);

    /**
     * @tc.steps: step3. set keyboard avoidance and test again
     */
    pattern->keyboardAvoidance_ = true;
    option = RichEditorModelNG::GetCustomKeyboardOption(frameNode.GetRawPtr());
    EXPECT_TRUE(option);

    /**
     * @tc.steps: step4. test GetCustomKeyboardOption with null frame node
     */
    option = RichEditorModelNG::GetCustomKeyboardOption(nullptr);
    // Should return false for null frame node
    EXPECT_FALSE(option);
}

/**
 * @tc.name: GetTextDetectEnable001
 * @tc.desc: test GetTextDetectEnable with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetTextDetectEnable001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetTextDetectEnable with default value
     */
    bool textDetectEnable = RichEditorModelNG::GetTextDetectEnable(frameNode.GetRawPtr());
    // Default value should be false
    EXPECT_FALSE(textDetectEnable);

    /**
     * @tc.steps: step3. set text detect enable and test again
     */
    pattern->SetTextDetectEnable(true);
    textDetectEnable = RichEditorModelNG::GetTextDetectEnable(frameNode.GetRawPtr());
    EXPECT_TRUE(textDetectEnable);

    /**
     * @tc.steps: step4. test GetTextDetectEnable with null frame node
     */
    textDetectEnable = RichEditorModelNG::GetTextDetectEnable(nullptr);
    // Should return false for null frame node
    EXPECT_FALSE(textDetectEnable);
}

/**
 * @tc.name: GetSelectedBackgroundColor001
 * @tc.desc: test GetSelectedBackgroundColor with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetSelectedBackgroundColor001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetSelectedBackgroundColor
     */
    Color selectedBackgroundColor = RichEditorModelNG::GetSelectedBackgroundColor(frameNode.GetRawPtr());
    // Should not be default black color
    EXPECT_NE(selectedBackgroundColor.GetValue(), DEFAULT_BLACK_COLOR);
    
    /**
     * @tc.steps: step3. test GetSelectedBackgroundColor with null frame node
     */
    selectedBackgroundColor = RichEditorModelNG::GetSelectedBackgroundColor(nullptr);
    // Should return default black color for null frame node
    EXPECT_EQ(selectedBackgroundColor.GetValue(), DEFAULT_BLACK_COLOR);
}

/**
 * @tc.name: GetCaretColor001
 * @tc.desc: test GetCaretColor with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetCaretColor001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetCaretColor
     */
    Color caretColor = RichEditorModelNG::GetCaretColor(frameNode.GetRawPtr());
    EXPECT_NE(caretColor.GetValue(), DEFAULT_BLACK_COLOR);

    /**
     * @tc.steps: step3. test GetCaretColor with null frame node
     */
    caretColor = RichEditorModelNG::GetCaretColor(nullptr);
    EXPECT_EQ(caretColor.GetValue(), DEFAULT_BLACK_COLOR);
}

/**
 * @tc.name: GetLineCount001
 * @tc.desc: test GetLineCount with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetLineCount001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetLineCount
     */
    size_t lineCount = RichEditorModelNG::GetLineCount(frameNode.GetRawPtr());
    // Empty rich editor should have 0 lines
    EXPECT_EQ(lineCount, 0);

    /**
     * @tc.steps: step3. test GetLineCount with null frame node
     */
    lineCount = RichEditorModelNG::GetLineCount(nullptr);
    EXPECT_EQ(lineCount, 0);
}

/**
 * @tc.name: GetLineMetrics001
 * @tc.desc: test GetLineMetrics with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetLineMetrics001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetLineMetrics with invalid line number
     */
    TextLineMetrics lineMetrics = RichEditorModelNG::GetLineMetrics(frameNode.GetRawPtr(), 0);
    EXPECT_EQ(lineMetrics.lineNumber, 0);
    EXPECT_EQ(lineMetrics.height, 0);

    /**
     * @tc.steps: step3. test GetLineMetrics with null frame node
     */
    lineMetrics = RichEditorModelNG::GetLineMetrics(nullptr, 0);
    EXPECT_EQ(lineMetrics.lineNumber, 0);
    EXPECT_EQ(lineMetrics.height, 0);
}

/**
 * @tc.name: GetRectsForRange001
 * @tc.desc: test GetRectsForRange with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetRectsForRange001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));
    auto rectHeightStyle = RectHeightStyle::TIGHT;
    auto rectWidthStyle = RectWidthStyle::TIGHT;

    /**
     * @tc.steps: step2. test GetRectsForRange
     */
    auto rects = RichEditorModelNG::GetRectsForRange(frameNode.GetRawPtr(), 0, 10, rectHeightStyle, rectWidthStyle);
    EXPECT_TRUE(rects.empty());

    /**
     * @tc.steps: step3. test GetRectsForRange with null frame node
     */
    rects = RichEditorModelNG::GetRectsForRange(nullptr, 0, 10, rectHeightStyle, rectWidthStyle);
    EXPECT_TRUE(rects.empty());
}

/**
 * @tc.name: GetGlyphPositionAtCoordinate001
 * @tc.desc: test GetGlyphPositionAtCoordinate with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetGlyphPositionAtCoordinate001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetGlyphPositionAtCoordinate
     */
    PositionWithAffinity result = RichEditorModelNG::GetGlyphPositionAtCoordinate(frameNode.GetRawPtr(), 0, 0);
    EXPECT_EQ(result.position_, 0);

    /**
     * @tc.steps: step3. test GetGlyphPositionAtCoordinate with null frame node
     */
    result = RichEditorModelNG::GetGlyphPositionAtCoordinate(nullptr, 0, 0);
    EXPECT_EQ(result.position_, 0);
    EXPECT_EQ(result.affinity_, TextAffinity::UPSTREAM);
}

/**
 * @tc.name: GetCharacterPositionAtCoordinate001
 * @tc.desc: test GetCharacterPositionAtCoordinate with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetCharacterPositionAtCoordinate001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetCharacterPositionAtCoordinate
     */
    PositionWithAffinity result = RichEditorModelNG::GetCharacterPositionAtCoordinate(frameNode.GetRawPtr(), 0, 0);
    EXPECT_EQ(result.position_, 0);

    /**
     * @tc.steps: step3. test GetCharacterPositionAtCoordinate with null frame node
     */
    result = RichEditorModelNG::GetCharacterPositionAtCoordinate(nullptr, 0, 0);
    EXPECT_EQ(result.position_, 0);
    EXPECT_EQ(result.affinity_, TextAffinity::UPSTREAM);
}

/**
 * @tc.name: GetGlyphRangeForCharacterRange001
 * @tc.desc: test GetGlyphRangeForCharacterRange with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetGlyphRangeForCharacterRange001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetGlyphRangeForCharacterRange
     * When paragraphs_ is empty, returns default TextRange{-1, -1}
     */
    auto result = RichEditorModelNG::GetGlyphRangeForCharacterRange(frameNode.GetRawPtr(), 0, 10);
    EXPECT_EQ(result.first.start, -1);
    EXPECT_EQ(result.first.end, -1);
    EXPECT_EQ(result.second.start, -1);
    EXPECT_EQ(result.second.end, -1);

    /**
     * @tc.steps: step3. test GetGlyphRangeForCharacterRange with null frame node
     * Returns default constructed pair with TextRange{-1, -1}
     */
    result = RichEditorModelNG::GetGlyphRangeForCharacterRange(nullptr, 0, 10);
    EXPECT_EQ(result.first.start, -1);
    EXPECT_EQ(result.first.end, -1);
    EXPECT_EQ(result.second.start, -1);
    EXPECT_EQ(result.second.end, -1);
}

/**
 * @tc.name: GetCharacterRangeForGlyphRange001
 * @tc.desc: test GetCharacterRangeForGlyphRange with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetCharacterRangeForGlyphRange001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetCharacterRangeForGlyphRange
     * When paragraphs_ is empty, returns default TextRange{-1, -1}
     */
    auto result = RichEditorModelNG::GetCharacterRangeForGlyphRange(frameNode.GetRawPtr(), 0, 10);
    EXPECT_EQ(result.first.start, -1);
    EXPECT_EQ(result.first.end, -1);
    EXPECT_EQ(result.second.start, -1);
    EXPECT_EQ(result.second.end, -1);

    /**
     * @tc.steps: step3. test GetCharacterRangeForGlyphRange with null frame node
     * Returns default constructed pair with TextRange{-1, -1}
     */
    result = RichEditorModelNG::GetCharacterRangeForGlyphRange(nullptr, 0, 10);
    EXPECT_EQ(result.first.start, -1);
    EXPECT_EQ(result.first.end, -1);
    EXPECT_EQ(result.second.start, -1);
    EXPECT_EQ(result.second.end, -1);
}

/**
 * @tc.name: GetTypingStyle001
 * @tc.desc: test GetTypingStyle with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetTypingStyle001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetTypingStyle
     */
    auto typingStyle = RichEditorModelNG::GetTypingStyle(frameNode.GetRawPtr());
    // Default should be nullopt
    EXPECT_FALSE(typingStyle.has_value());

    /**
     * @tc.steps: step3. test GetTypingStyle with null frame node
     */
    typingStyle = RichEditorModelNG::GetTypingStyle(nullptr);
    // Should return nullopt
    EXPECT_FALSE(typingStyle.has_value());
}

/**
 * @tc.name: GetRequestKeyboardOnFocus001
 * @tc.desc: test GetRequestKeyboardOnFocus with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetRequestKeyboardOnFocus001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetRequestKeyboardOnFocus
     */
    bool requestKeyboard = RichEditorModelNG::GetRequestKeyboardOnFocus(frameNode.GetRawPtr());
    // Default should be true
    EXPECT_TRUE(requestKeyboard);

    /**
     * @tc.steps: step3. test GetRequestKeyboardOnFocus with null frame node
     */
    requestKeyboard = RichEditorModelNG::GetRequestKeyboardOnFocus(nullptr);
    // Should return true for null frame node
    EXPECT_TRUE(requestKeyboard);
}

/**
 * @tc.name: IsSupportPreviewText001
 * @tc.desc: test IsSupportPreviewText with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, IsSupportPreviewText001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test IsSupportPreviewText
     */
    bool supportPreview = RichEditorModelNG::IsSupportPreviewText(frameNode.GetRawPtr());
    // Default should be true
    EXPECT_TRUE(supportPreview);

    /**
     * @tc.steps: step3. test IsSupportPreviewText with null frame node
     */
    supportPreview = RichEditorModelNG::IsSupportPreviewText(nullptr);
    // Should return false for null frame node
    EXPECT_FALSE(supportPreview);
}

/**
 * @tc.name: IsIncludeFontPadding001
 * @tc.desc: test IsIncludeFontPadding with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, IsIncludeFontPadding001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test IsIncludeFontPadding
     */
    bool isIncludeFontPadding = RichEditorModelNG::IsIncludeFontPadding(frameNode.GetRawPtr());
    EXPECT_FALSE(isIncludeFontPadding);

    /**
     * @tc.steps: step3. test IsIncludeFontPadding with null frame node
     */
    isIncludeFontPadding = RichEditorModelNG::IsIncludeFontPadding(nullptr);
    EXPECT_FALSE(isIncludeFontPadding);
}

/**
 * @tc.name: IsCompressLeadingPunctuation001
 * @tc.desc: test IsCompressLeadingPunctuation with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, IsCompressLeadingPunctuation001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test IsCompressLeadingPunctuation
     */
    bool isCompressLeadingPunctuation = RichEditorModelNG::IsCompressLeadingPunctuation(frameNode.GetRawPtr());
    EXPECT_FALSE(isCompressLeadingPunctuation);

    /**
     * @tc.steps: step3. test IsCompressLeadingPunctuation with null frame node
     */
    isCompressLeadingPunctuation = RichEditorModelNG::IsCompressLeadingPunctuation(nullptr);
    EXPECT_FALSE(isCompressLeadingPunctuation);
}

/**
 * @tc.name: GetEnterKeyType001
 * @tc.desc: test GetEnterKeyType with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetEnterKeyType001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetEnterKeyType
     */
    TextInputAction enterKeyType = RichEditorModelNG::GetEnterKeyType(frameNode.GetRawPtr());
    EXPECT_EQ(enterKeyType, TextInputAction::NEW_LINE);

    /**
     * @tc.steps: step3. test GetEnterKeyType with null frame node
     */
    enterKeyType = RichEditorModelNG::GetEnterKeyType(nullptr);
    EXPECT_EQ(enterKeyType, TextInputAction::UNSPECIFIED);
}

/**
 * @tc.name: IsFallbackLineSpacing001
 * @tc.desc: test IsFallbackLineSpacing with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, IsFallbackLineSpacing001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test IsFallbackLineSpacing
     */
    bool isFallbackLineSpacing = RichEditorModelNG::IsFallbackLineSpacing(frameNode.GetRawPtr());
    EXPECT_FALSE(isFallbackLineSpacing);

    /**
     * @tc.steps: step3. test IsFallbackLineSpacing with null frame node
     */
    isFallbackLineSpacing = RichEditorModelNG::IsFallbackLineSpacing(nullptr);
    EXPECT_FALSE(isFallbackLineSpacing);
}

/**
 * @tc.name: IsStopBackPress001
 * @tc.desc: test IsStopBackPress with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, IsStopBackPress001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test IsStopBackPress
     */
    bool isStopBackPress = RichEditorModelNG::IsStopBackPress(frameNode.GetRawPtr());
    EXPECT_TRUE(isStopBackPress);

    /**
     * @tc.steps: step3. test IsStopBackPress with null frame node
     */
    isStopBackPress = RichEditorModelNG::IsStopBackPress(nullptr);
    EXPECT_TRUE(isStopBackPress);
}

/**
 * @tc.name: GetKeyboardAppearance001
 * @tc.desc: test GetKeyboardAppearance with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetKeyboardAppearance001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetKeyboardAppearance
     */
    KeyboardAppearance keyboardAppearance = RichEditorModelNG::GetKeyboardAppearance(frameNode.GetRawPtr());
    EXPECT_EQ(keyboardAppearance, KeyboardAppearance::NONE_IMMERSIVE);

    /**
     * @tc.steps: step3. test GetKeyboardAppearance with null frame node
     */
    keyboardAppearance = RichEditorModelNG::GetKeyboardAppearance(nullptr);
    EXPECT_EQ(keyboardAppearance, KeyboardAppearance::NONE_IMMERSIVE);
}

/**
 * @tc.name: GetEnableHapticFeedback001
 * @tc.desc: test GetEnableHapticFeedback with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetEnableHapticFeedback001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetEnableHapticFeedback
     */
    bool enableHapticFeedback = RichEditorModelNG::GetEnableHapticFeedback(frameNode.GetRawPtr());
    EXPECT_TRUE(enableHapticFeedback);

    /**
     * @tc.steps: step3. test GetEnableHapticFeedback with null frame node
     */
    enableHapticFeedback = RichEditorModelNG::GetEnableHapticFeedback(nullptr);
    EXPECT_FALSE(enableHapticFeedback);
}

/**
 * @tc.name: IsSupportStyledUndo001
 * @tc.desc: test IsSupportStyledUndo with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, IsSupportStyledUndo001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test IsSupportStyledUndo
     */
    bool isSupportStyledUndo = RichEditorModelNG::IsSupportStyledUndo(frameNode.GetRawPtr());
    EXPECT_FALSE(isSupportStyledUndo);

    /**
     * @tc.steps: step3. test IsSupportStyledUndo with null frame node
     */
    isSupportStyledUndo = RichEditorModelNG::IsSupportStyledUndo(nullptr);
    EXPECT_FALSE(isSupportStyledUndo);
}

/**
 * @tc.name: GetScrollBarColor001
 * @tc.desc: test GetScrollBarColor with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetScrollBarColor001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetScrollBarColor
     */
    Color scrollBarColor = RichEditorModelNG::GetScrollBarColor(frameNode.GetRawPtr());
    EXPECT_EQ(scrollBarColor.GetValue(), Color().GetValue());

    /**
     * @tc.steps: step3. test GetScrollBarColor with null frame node
     */
    scrollBarColor = RichEditorModelNG::GetScrollBarColor(nullptr);
    EXPECT_EQ(scrollBarColor.GetValue(), Color().GetValue());
}

/**
 * @tc.name: GetCaretOffset001
 * @tc.desc: test GetCaretOffset with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetCaretOffset001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetCaretOffset
     */
    int32_t caretOffset = RichEditorModelNG::GetCaretOffset(frameNode.GetRawPtr());
    EXPECT_EQ(caretOffset, 0);

    /**
     * @tc.steps: step3. test GetCaretOffset with null frame node
     */
    caretOffset = RichEditorModelNG::GetCaretOffset(nullptr);
    EXPECT_EQ(caretOffset, -1);
}

/**
 * @tc.name: IsEditing001
 * @tc.desc: test IsEditing with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, IsEditing001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test IsEditing
     */
    bool isEditing = RichEditorModelNG::IsEditing(frameNode.GetRawPtr());
    EXPECT_FALSE(isEditing);

    /**
     * @tc.steps: step3. test IsEditing with null frame node
     */
    isEditing = RichEditorModelNG::IsEditing(nullptr);
    EXPECT_FALSE(isEditing);
}

/**
 * @tc.name: GetCaretRect001
 * @tc.desc: test GetCaretRect with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetCaretRect001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetCaretRect
     */
    RectF caretRect = RichEditorModelNG::GetCaretRect(frameNode.GetRawPtr());
    EXPECT_EQ(caretRect.GetX(), -1.0f);
    EXPECT_EQ(caretRect.GetY(), -1.0f);
    EXPECT_EQ(caretRect.Width(), -1.0f);
    EXPECT_EQ(caretRect.Height(), -1.0f);

    /**
     * @tc.steps: step3. test GetCaretRect with null frame node
     */
    caretRect = RichEditorModelNG::GetCaretRect(nullptr);
    EXPECT_EQ(caretRect.GetX(), -1.0f);
    EXPECT_EQ(caretRect.GetY(), -1.0f);
    EXPECT_EQ(caretRect.Width(), -1.0f);
    EXPECT_EQ(caretRect.Height(), -1.0f);
}

/**
 * @tc.name: GetPreviewTextInfo001
 * @tc.desc: test GetPreviewTextInfo with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetPreviewTextInfo001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetPreviewTextInfo
     */
    PreviewTextInfo previewTextInfo = RichEditorModelNG::GetPreviewTextInfo(frameNode.GetRawPtr());
    EXPECT_FALSE(previewTextInfo.value.has_value());
    EXPECT_FALSE(previewTextInfo.offset.has_value());

    /**
     * @tc.steps: step3. test GetPreviewTextInfo with null frame node
     */
    previewTextInfo = RichEditorModelNG::GetPreviewTextInfo(nullptr);
    EXPECT_FALSE(previewTextInfo.value.has_value());
    EXPECT_FALSE(previewTextInfo.offset.has_value());
}

/**
 * @tc.name: GetSelectDetectConfig001
 * @tc.desc: test GetSelectDetectConfig with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetSelectDetectConfig001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetSelectDetectConfig
     */
    auto selectDetectConfig = RichEditorModelNG::GetSelectDetectConfig(frameNode.GetRawPtr());
    EXPECT_TRUE(selectDetectConfig.empty());
}


/**
 * @tc.name: GetSelectionRangeInfo001
 * @tc.desc: test GetSelectionRangeInfo with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetSelectionRangeInfo001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetSelectionRangeInfo
     */
    SelectionRangeInfo selectionRangeInfo = RichEditorModelNG::GetSelectionRangeInfo(frameNode.GetRawPtr());
    EXPECT_EQ(selectionRangeInfo.start_, 0);
    EXPECT_EQ(selectionRangeInfo.end_, 0);

    /**
     * @tc.steps: step3. test GetSelectionRangeInfo with null frame node
     */
    selectionRangeInfo = RichEditorModelNG::GetSelectionRangeInfo(nullptr);
    EXPECT_EQ(selectionRangeInfo.start_, 0);
    EXPECT_EQ(selectionRangeInfo.end_, 0);
}

/**
 * @tc.name: GetStyledString001
 * @tc.desc: test GetStyledString with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetStyledString001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetStyledString
     */
    SpanStringBase* styledString = RichEditorModelNG::GetStyledString(frameNode.GetRawPtr());
    EXPECT_TRUE(styledString != nullptr);
    delete styledString;

    /**
     * @tc.steps: step3. test GetStyledString with null frame node
     */
    styledString = RichEditorModelNG::GetStyledString(nullptr);
    EXPECT_TRUE(styledString != nullptr);
    delete styledString;
}

/**
 * @tc.name: GetMaxLength001
 * @tc.desc: test GetMaxLength with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetMaxLength001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetMaxLength
     */
    int32_t maxLength = RichEditorModelNG::GetMaxLength(frameNode.GetRawPtr());
    EXPECT_EQ(maxLength, INT_MAX);

    /**
     * @tc.steps: step3. test GetMaxLength with null frame node
     */
    maxLength = RichEditorModelNG::GetMaxLength(nullptr);
    EXPECT_EQ(maxLength, INT_MAX);
}

/**
 * @tc.name: GetMaxLines001
 * @tc.desc: test GetMaxLines with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, GetMaxLines001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test GetMaxLines
     */
    int32_t maxLines = RichEditorModelNG::GetMaxLines(frameNode.GetRawPtr());
    EXPECT_EQ(maxLines, INT32_MAX);

    /**
     * @tc.steps: step3. test GetMaxLines with null frame node
     */
    maxLines = RichEditorModelNG::GetMaxLines(nullptr);
    EXPECT_EQ(maxLines, INT32_MAX);
}

/**
 * @tc.name: IsOrphanCharOptimization001
 * @tc.desc: test IsOrphanCharOptimization with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, IsOrphanCharOptimization001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test IsOrphanCharOptimization
     */
    bool isOrphanCharOptimization = RichEditorModelNG::IsOrphanCharOptimization(frameNode.GetRawPtr());
    EXPECT_FALSE(isOrphanCharOptimization);

    /**
     * @tc.steps: step3. test IsOrphanCharOptimization with null frame node
     */
    isOrphanCharOptimization = RichEditorModelNG::IsOrphanCharOptimization(nullptr);
    EXPECT_FALSE(isOrphanCharOptimization);
}

/**
 * @tc.name: IsEnableAutoSpacing001
 * @tc.desc: test IsEnableAutoSpacing with valid frame node
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModelStaticTestNg, IsEnableAutoSpacing001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto frameNode = RichEditorModelStatic::CreateFrameNode(0);
    EXPECT_TRUE(static_cast<bool>(frameNode));
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    EXPECT_TRUE(static_cast<bool>(pattern));

    /**
     * @tc.steps: step2. test IsEnableAutoSpacing
     */
    bool isEnableAutoSpacing = RichEditorModelNG::IsEnableAutoSpacing(frameNode.GetRawPtr());
    EXPECT_FALSE(isEnableAutoSpacing);

    /**
     * @tc.steps: step3. test IsEnableAutoSpacing with null frame node
     */
    isEnableAutoSpacing = RichEditorModelNG::IsEnableAutoSpacing(nullptr);
    EXPECT_FALSE(isEnableAutoSpacing);
}
}
