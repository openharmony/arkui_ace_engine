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
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/interfaces/native/implementation/rich_editor_styled_string_controller_peer_impl.h"
#include "accessor_test_base.h"
#include "node_api.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "gmock/gmock.h"

static constexpr auto TEST_TEXT = "test text";
static constexpr int TEST_RESOURCE_ID = 1000;

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
class MockRichEditorStyledStringController : public RichEditorStyledStringController {
public:
    MockRichEditorStyledStringController() = default;
    ~MockRichEditorStyledStringController() override = default;
    MOCK_METHOD(void, SetStyledString, (const RefPtr<SpanStringBase>&));
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

        auto peerImpl = reinterpret_cast<GeneratedModifier::RichEditorStyledStringControllerPeerImpl *>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->AddTargetController(mockRichEditorControllerKeeper_);

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
    ASSERT_NE(accessor_->getStyledString, nullptr);

    MutableSpanString* inputString = new MutableSpanString(TEST_TEXT);
    RefPtr<SpanStringBase> spanString;
    spanString = inputString;
    Ark_Materialized inStyledString {.ptr = &spanString};

    EXPECT_CALL(*mockRichEditorController_, SetStyledString(spanString)).Times(1);
    accessor_->setStyledString(peer_, &inStyledString);
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

    auto peerImpl = reinterpret_cast<GeneratedModifier::RichEditorStyledStringControllerPeerImpl *>(peer_);
    ASSERT_NE(peerImpl, nullptr);
    peerImpl->SetPattern(weakPattern);

    auto eventHub = frameNodeRaw->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto testHub = patternRaw->GetEventHub<NG::RichEditorEventHub>();
    ASSERT_NE(testHub, nullptr);

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

} // namespace OHOS::Ace::NG
