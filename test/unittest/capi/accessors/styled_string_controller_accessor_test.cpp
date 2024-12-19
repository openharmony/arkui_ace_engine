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
#include "accessor_test_base.h"
#include "core/interfaces/native/implementation/rich_editor_styled_string_controller_peer_impl.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "gmock/gmock.h"

static constexpr auto TEST_TEXT = "test text";

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


class StyledStringControllerAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIStyledStringControllerAccessor,
    &GENERATED_ArkUIAccessors::getStyledStringControllerAccessor, StyledStringControllerPeer> {
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
 * @tc.name: setStyledStringTest
 * @tc.desc: Check the functionality of setAndGetStyledString
 * @tc.type: FUNC
 */
HWTEST_F(StyledStringControllerAccessorTest, setStyledStringTest, TestSize.Level1) {
    auto peer1 = reinterpret_cast<StyledStringControllerPeer*>(accessor_->ctor());
    auto peer2 = reinterpret_cast<StyledStringControllerPeer*>(accessor_->ctor());
    auto peer3 = reinterpret_cast<StyledStringControllerPeer*>(accessor_->ctor());
    auto peerImpl1 = reinterpret_cast<GeneratedModifier::RichEditorStyledStringControllerPeerImpl *>(peer1);
    ASSERT_NE(peerImpl1, nullptr);
    auto peerImpl2 = reinterpret_cast<GeneratedModifier::RichEditorStyledStringControllerPeerImpl *>(peer2);
    ASSERT_NE(peerImpl2, nullptr);
    auto peerImpl3 = reinterpret_cast<GeneratedModifier::RichEditorStyledStringControllerPeerImpl *>(peer3);
    ASSERT_NE(peerImpl3, nullptr);
    EXPECT_EQ(peerImpl1->GetStyledString(), nullptr);
    EXPECT_EQ(peerImpl2->GetStyledString(), nullptr);
    EXPECT_EQ(peerImpl3->GetStyledString(), nullptr);
    finalyzer_(peer1);
    finalyzer_(peer2);
    finalyzer_(peer3);
}

/**
 * @tc.name: setAndGetStyledStringTest
 * @tc.desc: Check the functionality of setAndGetStyledString
 * @tc.type: FUNC
 */
HWTEST_F(StyledStringControllerAccessorTest, DISABLED_setAndGetStyledStringTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getStyledString, nullptr);
    ASSERT_NE(accessor_->setStyledString, nullptr);

    SpanString* inputString = new SpanString(TEST_TEXT);
    RefPtr<SpanStringBase> spanString;
    spanString = inputString;
    Ark_Materialized inStyledString {.ptr = &spanString};

    // set pattern
    auto patternRaw = new RichEditorPattern();
    RefPtr<RichEditorPattern> refPattern = Referenced::Claim(patternRaw);

    auto frameNodeRaw = new FrameNode("", -1, refPattern);
    WeakPtr<FrameNode> frameNode = Referenced::WeakClaim(frameNodeRaw);

    patternRaw->AttachToFrameNode(frameNode);
    WeakPtr<RichEditorPattern> weakPattern = Referenced::WeakClaim(patternRaw);

    auto peerImpl = reinterpret_cast<GeneratedModifier::RichEditorStyledStringControllerPeerImpl *>(peer_);
    ASSERT_NE(peerImpl, nullptr);
    peerImpl->SetPattern(weakPattern);

    EXPECT_CALL(*mockRichEditorController_, SetStyledString(spanString)).Times(1);
    accessor_->setStyledString(peer_, &inStyledString);

    auto outStyledString = accessor_->getStyledString(peer_);
    ASSERT_NE(outStyledString, nullptr);
}
}