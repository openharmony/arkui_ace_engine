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
#include "richeditor_accessor_test.h"
#include "core/interfaces/native/implementation/rich_editor_base_controller_peer_impl.h"
#include "accessor_test_base.h"
#include "node_api.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "gmock/gmock.h"

namespace OHOS::Ace {
bool operator==(const std::optional<OHOS::Ace::SelectionOptions>& lhs,
                const std::optional<OHOS::Ace::SelectionOptions>& rhs)
{
    if (!lhs.has_value() || !rhs.has_value()) {
        return false;
    }
    return lhs->menuPolicy == rhs->menuPolicy;
}
bool operator==(const std::optional<OHOS::Ace::UpdateSpanStyle>& lhs,
                const std::optional<OHOS::Ace::UpdateSpanStyle>& rhs)
{
    if (!lhs.has_value() || !rhs.has_value()) {
        return false;
    }
    bool textColorEq = lhs->updateTextColor && rhs->updateTextColor &&
        lhs->updateTextColor.value() == rhs->updateTextColor.value();
    bool fontSizeEq = lhs->updateFontSize && rhs->updateFontSize &&
        lhs->updateFontSize.value() == rhs->updateFontSize.value();
    bool italicFontStyleEq = lhs->updateItalicFontStyle && rhs->updateItalicFontStyle &&
        lhs->updateItalicFontStyle.value() == rhs->updateItalicFontStyle.value();
    bool fontWeightEq = lhs->updateFontWeight && rhs->updateFontWeight &&
        lhs->updateFontWeight.value() == rhs->updateFontWeight.value();
    return textColorEq && fontSizeEq && italicFontStyleEq && fontWeightEq;
}
} // OHOS::Ace

static constexpr int32_t TEST_IDX = 0;
static constexpr int32_t TEST_IDX_2 = 10;
static constexpr int32_t TEST_START = 1;
static constexpr int32_t TEST_END = 3;
static const std::vector<std::string> FONT_FAMILIES = { "serif" };
static constexpr double FONT_SIZE = 10.0;
static constexpr OHOS::Ace::FontWeight FONT_WEIGHT = OHOS::Ace::FontWeight::NORMAL;
static constexpr OHOS::Ace::FontStyle FONT_STYLE = OHOS::Ace::FontStyle::NORMAL;
static const OHOS::Ace::Color FONT_COLOUR = OHOS::Ace::Color::RED;

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class MockRichEditorBaseController : public RichEditorBaseController {
public:
    MockRichEditorBaseController() = default;
    ~MockRichEditorBaseController() override = default;
    MOCK_METHOD(int32_t, GetCaretOffset, ());
    MOCK_METHOD(bool, SetCaretOffset, (int32_t));
    MOCK_METHOD(void, CloseSelectionMenu, ());
    MOCK_METHOD(bool, IsEditing, ());
    MOCK_METHOD(void, StopEditing, ());
    MOCK_METHOD(void, SetSelection, (int32_t, int32_t, const std::optional<SelectionOptions>&, bool));
    MOCK_METHOD(void, SetTypingStyle, (std::optional<struct UpdateSpanStyle>, std::optional<TextStyle>));
    MOCK_METHOD(const PreviewTextInfo, GetPreviewTextInfo, (), (const));
    MOCK_METHOD(WeakPtr<LayoutInfoInterface>, GetLayoutInfoInterface, ());
};
} // namespace

class RichEditorBaseControllerAccessorTest : public AccessorTestBase<GENERATED_ArkUIRichEditorBaseControllerAccessor,
    &GENERATED_ArkUIAccessors::getRichEditorBaseControllerAccessor, RichEditorBaseControllerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();

        mockRichEditorController_ = new MockRichEditorBaseController();
        mockRichEditorControllerKeeper_ = AceType::Claim(mockRichEditorController_);
        ASSERT_NE(mockRichEditorControllerKeeper_, nullptr);

        auto peerImpl = reinterpret_cast<GeneratedModifier::RichEditorBaseControllerPeerImpl *>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->AddTargetController(mockRichEditorControllerKeeper_);

        ASSERT_NE(mockRichEditorController_, nullptr);
    }

    void TearDown() override
    {
        mockRichEditorControllerKeeper_ = nullptr;
        mockRichEditorController_ = nullptr;
    }

    MockRichEditorBaseController *mockRichEditorController_ = nullptr;
    RefPtr<MockRichEditorBaseController> mockRichEditorControllerKeeper_ = nullptr;
};

/**
 * @tc.name: getCaretOffsetTest
 * @tc.desc: Check the functionality of getCaretOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseControllerAccessorTest, getCaretOffsetTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getCaretOffset, nullptr);

    EXPECT_CALL(*mockRichEditorController_, GetCaretOffset()).Times(1);
    Ark_Int32 idx = accessor_->getCaretOffset(peer_);
    ASSERT_EQ(idx, TEST_IDX);
}

/**
 * @tc.name: setCaretOffsetTest
 * @tc.desc: Check the functionality of setCaretOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseControllerAccessorTest, setCaretOffsetTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getCaretOffset, nullptr);

    EXPECT_CALL(*mockRichEditorController_, SetCaretOffset(TEST_IDX_2)).Times(1);
    Ark_Number offset = Converter::ArkValue<Ark_Number>(TEST_IDX_2);
    bool result = accessor_->setCaretOffset(peer_, &offset);
    ASSERT_FALSE(result);
}

/**
 * @tc.name: closeSelectionMenuTest
 * @tc.desc: Check the functionality of closeSelectionMenu
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseControllerAccessorTest, closeSelectionMenuTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->closeSelectionMenu, nullptr);

    EXPECT_CALL(*mockRichEditorController_, CloseSelectionMenu()).Times(1);
    accessor_->closeSelectionMenu(peer_);
}

/**
 * @tc.name: isEditingTest
 * @tc.desc: Check the functionality of isEditing
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseControllerAccessorTest, isEditingTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->isEditing, nullptr);

    EXPECT_CALL(*mockRichEditorController_, IsEditing()).Times(1);
    bool result = accessor_->isEditing(peer_);
    ASSERT_FALSE(result);
}

/**
 * @tc.name: stopEditingTest
 * @tc.desc: Check the functionality of stopEditing
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseControllerAccessorTest, stopEditingTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->stopEditing, nullptr);

    EXPECT_CALL(*mockRichEditorController_, StopEditing()).Times(1);
    accessor_->stopEditing(peer_);
}

/**
 * @tc.name: setSelectionTest
 * @tc.desc: Check the functionality of setSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseControllerAccessorTest, setSelectionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setSelection, nullptr);

    SelectionOptions opts;
    opts.menuPolicy = MenuPolicy::SHOW;
    std::optional<SelectionOptions> checkOpts = opts;
    EXPECT_CALL(*mockRichEditorController_, SetSelection(TEST_START, TEST_END, checkOpts, true)).Times(1);
    auto start = Converter::ArkValue<Ark_Number>(TEST_START);
    auto end = Converter::ArkValue<Ark_Number>(TEST_END);
    Opt_SelectionOptions optsOpt;
    optsOpt.value.menuPolicy.value = Ark_MenuPolicy::ARK_MENU_POLICY_SHOW;
    accessor_->setSelection(peer_, &start, &end, &optsOpt);
}

/**
 * @tc.name: setTypingStyleTest
 * @tc.desc: Check the functionality of setTypingStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseControllerAccessorTest, setTypingStyleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setTypingStyle, nullptr);
    std::optional<struct UpdateSpanStyle> spanStyle = UpdateSpanStyle();
    spanStyle->updateTextColor = FONT_COLOUR;
    spanStyle->updateFontSize = CalcDimension(FONT_SIZE);
    spanStyle->updateItalicFontStyle = FONT_STYLE;
    spanStyle->updateFontWeight = FONT_WEIGHT;
    std::optional<TextStyle> textStyle = TextStyle(FONT_FAMILIES, FONT_SIZE, FONT_WEIGHT, FONT_STYLE, FONT_COLOUR);
    EXPECT_CALL(*mockRichEditorController_, SetTypingStyle(spanStyle, textStyle)).Times(1);
    auto value = Converter::ArkValue<Ark_RichEditorTextStyle>(*textStyle);
    accessor_->setTypingStyle(peer_, &value);
}

/**
 * @tc.name: GetPreviewTextTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseControllerAccessorTest, DISABLED_GetPreviewTextTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getPreviewText, nullptr);
    PreviewTextInfo previewText = {.offset = 1, .value = "info"};
    EXPECT_CALL(*mockRichEditorController_, GetPreviewTextInfo()).Times(1).WillOnce(Return(previewText));
    accessor_->getPreviewText(peer_); // fix after updating a return value
    // check a return value
}

/**
 * @tc.name: GetLayoutManagerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseControllerAccessorTest, GetLayoutManagerTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getLayoutManager, nullptr);
    auto layoutInfo = OHOS::Ace::NG::LayoutInfoInterface();
    EXPECT_CALL(*mockRichEditorController_,
        GetLayoutInfoInterface()).Times(1).WillOnce(Return(layoutInfo.GetLayoutInfoInterface()));
    Ark_NativePointer manager = accessor_->getLayoutManager(peer_);
    ASSERT_NE(manager, nullptr);
}

} // namespace OHOS::Ace::NG
