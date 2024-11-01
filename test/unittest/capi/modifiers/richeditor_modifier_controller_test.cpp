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
#include "richeditor_modifier_test.h"
#include "modifier_test_base.h"
#include "core/interfaces/arkoala/implementation/rich_editor_controller_peer_impl.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"

namespace OHOS::Ace::NG {
namespace Converter {
void AssignArkValue(Ark_RichEditorTextSpanOptions& dst, const OHOS::Ace::TextSpanOptions& src)
{
    dst.offset = Converter::ArkValue<Opt_Number>(src.offset);
}
} // Converter

static constexpr int TEST_OFFSET = 5;
static constexpr int TEST_OFFSET_2 = 7;
static constexpr int TEST_INDEX = 1;
static const auto TEST_VALUE = "test value";
static const auto TEST_VALUE_2 = "test value 2";
static constexpr int TEST_INDEX_2 = 2;

using namespace testing;
using namespace testing::ext;

class RichEditorModifierControllerTest : public ModifierTestBase<GENERATED_ArkUIRichEditorModifier,
    &GENERATED_ArkUINodeModifiers::getRichEditorModifier, GENERATED_ARKUI_RICH_EDITOR> {
};

/**
 * @tc.name: setRichEditorOptions0Test
 * @tc.desc: Check the functionality of setRichEditorOptions0
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorModifierControllerTest, setRichEditorOptions0Test, TestSize.Level1)
{
    ASSERT_NE(modifier_->setRichEditorOptions0, nullptr);

    // assume nothing bad with invalid and empty options
    modifier_->setRichEditorOptions0(node_, nullptr);

    auto controllerUndef = Converter::ArkValue<Opt_RichEditorOptions>(Ark_Empty());
    modifier_->setRichEditorOptions0(node_, &controllerUndef.value);

    // Check the internal controller
    auto frameNode = reinterpret_cast<FrameNode *>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto internalController = RichEditorModelNG::GetRichEditorController(frameNode);
    ASSERT_NE(internalController, nullptr);
    void* ptr = internalController.GetRawPtr();
    RichEditorController *rawPtr = reinterpret_cast<RichEditorController *>(ptr);
    ImageSpanOptions imageOptions;
    rawPtr->AddImageSpan(imageOptions);

    GeneratedModifier::RichEditorControllerPeerImpl peer;
    auto controller = Converter::ArkValue<Ark_RichEditorOptions>(&peer);
    modifier_->setRichEditorOptions0(node_, &controller);

    TextSpanOptions textSpanOptions;
    textSpanOptions.offset = TEST_OFFSET;
    textSpanOptions.value = TEST_VALUE;
    int32_t result = peer.AddTextSpanImpl(textSpanOptions);
    ASSERT_EQ(result, TEST_INDEX);

    TextSpanOptions textSpanOptions2;
    textSpanOptions.offset = TEST_OFFSET_2;
    textSpanOptions.value = TEST_VALUE_2;
    result = peer.AddTextSpanImpl(textSpanOptions2);
    ASSERT_EQ(result, TEST_INDEX_2);
}
} // namespace OHOS::Ace::NG
