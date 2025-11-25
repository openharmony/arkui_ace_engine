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

#include <gmock/gmock.h>

#include "richeditor_accessor_test.h"

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/interfaces/native/implementation/rich_editor_styled_string_controller_peer_impl.h"
#include "core/interfaces/native/implementation/mutable_styled_string_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "accessor_test_base.h"

static constexpr auto TEST_TEXT = u"test text";
static constexpr int TEST_RESOURCE_ID = 1000;
static constexpr int TEST_SELECTION_START = 1;
static constexpr int TEST_SELECTION_END = 3;

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class MockRichEditorStyledStringController : public RichEditorStyledStringController {
public:
    MockRichEditorStyledStringController()
    {
        SetPattern(mockPattern_);
    }
    ~MockRichEditorStyledStringController() override = default;

    RefPtr<RichEditorPattern> mockPattern_ = AceType::MakeRefPtr<RichEditorPattern>();
};
} // namespace

class RichEditorStyledStringControllerAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIRichEditorStyledStringControllerAccessor,
    &GENERATED_ArkUIAccessors::getRichEditorStyledStringControllerAccessor, RichEditorStyledStringControllerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();

        mockRichEditorController_ = new MockRichEditorStyledStringController();
        mockRichEditorControllerKeeper_ = AceType::Claim(mockRichEditorController_);
        ASSERT_NE(mockRichEditorControllerKeeper_, nullptr);

        peer_->AddTargetController(mockRichEditorControllerKeeper_);

        ASSERT_NE(mockRichEditorController_, nullptr);
    }

    void TearDown() override
    {
        mockRichEditorControllerKeeper_ = nullptr;
        mockRichEditorController_ = nullptr;
    }

    MockRichEditorStyledStringController *mockRichEditorController_ = nullptr;
    RefPtr<MockRichEditorStyledStringController> mockRichEditorControllerKeeper_ = nullptr;
};

/**
 * @tc.name: setAndGetStyledStringTest
 * @tc.desc: Check the functionality of setAndGetStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringControllerAccessorTest, DISABLED_setAndGetStyledStringTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setStyledString, nullptr);
    ASSERT_NE(accessor_->getStyledString, nullptr);
    const auto stringAccessor = accessors_->getMutableStyledStringAccessor();
    ASSERT_NE(stringAccessor, nullptr);
    ASSERT_NE(stringAccessor->construct, nullptr);
    ASSERT_NE(stringAccessor->destroyPeer, nullptr);
    const auto stringPeer = reinterpret_cast<MutableStyledStringPeer*>(stringAccessor->construct(nullptr, nullptr));
    const auto refString = AceType::MakeRefPtr<MutableSpanString>(TEST_TEXT);
    stringPeer->spanString = refString;

    accessor_->setStyledString(peer_, stringPeer);

    auto stringPeer2 = accessor_->getStyledString(peer_);
#ifdef WRONG_GEN
    auto resultOpt = Converter::GetOpt(result);
    ASSERT_TRUE(resultOpt.has_value());
    const auto stringPeer2 = reinterpret_cast<MutableStyledStringPeer*>(resultOpt.value());
#endif

    ASSERT_NE(stringPeer2, nullptr);
    EXPECT_NE(stringPeer, stringPeer2);
    const auto refString2 = stringPeer2->GetMutableString();
    ASSERT_NE(refString2, nullptr);
    EXPECT_EQ(*refString, *refString2);

    stringAccessor->destroyPeer(stringPeer);
    stringAccessor->destroyPeer(stringPeer2);
}

static bool g_onWillChangeCalled = false;
static bool g_onDidChangeCalled = false;

/**
 * @tc.name: onContentChangedTest
 * @tc.desc: Check the functionality of onContentChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringControllerAccessorTest, DISABLED_onContentChangedTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->onContentChanged, nullptr);

    // Setup FrameNode to be able to access EventHub from accessor's tests
    auto patternRaw = new RichEditorPattern();
    RefPtr<RichEditorPattern> refPattern = Referenced::Claim(patternRaw);

    auto frameNodeRaw = new FrameNode("", -1, refPattern);
    WeakPtr<FrameNode> frameNode = Referenced::WeakClaim(frameNodeRaw);

    patternRaw->AttachToFrameNode(frameNode);
    WeakPtr<RichEditorPattern> weakPattern = Referenced::WeakClaim(patternRaw);

    peer_->SetPattern(weakPattern);

    auto eventHub = frameNodeRaw->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto onWillChangeCallback = [](const Ark_Int32 resourceId,
        const Ark_StyledStringChangeValue parameter, const Callback_Boolean_Void continuation) {
        EXPECT_EQ(resourceId, TEST_RESOURCE_ID);
        g_onWillChangeCalled = true;
    };

    auto onDidChangeCallback = [](const Ark_Int32 resourceId,
        const Ark_TextRange rangeBefore, const Ark_TextRange rangeAfter) {
        EXPECT_EQ(resourceId, TEST_RESOURCE_ID);
        g_onDidChangeCalled = true;
    };

    auto func1 = Converter::ArkValue<Callback_StyledStringChangeValue_Boolean>(
        onWillChangeCallback, TEST_RESOURCE_ID);

    auto func2 = Converter::ArkValue<OnDidChangeCallback>(
        onDidChangeCallback, TEST_RESOURCE_ID);

    Ark_StyledStringChangedListener listener;
    listener.onWillChange.value = func1;
    listener.onDidChange.value = func2;
    accessor_->onContentChanged(peer_, &listener);

    StyledStringChangeValue event;
    eventHub->FireOnStyledStringWillChange(event);
    eventHub->FireOnStyledStringDidChange(event);
    ASSERT_TRUE(g_onWillChangeCalled);
    ASSERT_TRUE(g_onDidChangeCalled);
}

/**
 * @tc.name: getSelectionTest
 * @tc.desc: Check the functionality of getSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorStyledStringControllerAccessorTest, getSelectionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getSelection, nullptr);
    ASSERT_NE(mockRichEditorController_, nullptr);

    auto raw = mockRichEditorController_->mockPattern_;
    raw->SetStyledString(AceType::MakeRefPtr<SpanString>(TEST_TEXT));
    raw->UpdateSelector(TEST_SELECTION_START, TEST_SELECTION_END);

    auto selection = accessor_->getSelection(peer_);
#ifdef WRONG_GEN
    auto resultOpt = Converter::GetOpt(result);
    ASSERT_TRUE(resultOpt.has_value());
    auto selection = resultOpt.value();
#endif
    int32_t start = Converter::OptConvert<int32_t>(selection.start).value_or(-1);
    int32_t end = Converter::OptConvert<int32_t>(selection.end).value_or(-1);
    EXPECT_EQ(start, TEST_SELECTION_START);
    EXPECT_EQ(end, TEST_SELECTION_END);
}
} // namespace OHOS::Ace::NG
