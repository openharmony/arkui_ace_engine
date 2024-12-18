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
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "text_base.h"
#include "test/mock/core/render/mock_canvas_image.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/text_content_modifier.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"
#include "test/mock/core/common/mock_font_manager.h"
#include "core/components/hyperlink/hyperlink_theme.h"

namespace OHOS::Ace::NG {

class TextTestNineNg : public TextBases {
public:
};

/**
 * @tc.name: OnHandleScrolling001
 * @tc.desc: test base_text_select_overlay.cpp OnHandleScrolling function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, OnHandleScrolling001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);
    RefPtr<FrameNode> scrollableNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto scrollNode = AccessibilityManager::WeakClaim(AceType::RawPtr(scrollableNode));
    textSelectOverlay->hasRegisterListener_ = true;
    textSelectOverlay->OnHandleScrolling(scrollNode);
    EXPECT_FALSE(textSelectOverlay->hasRegisterListener_);
}

/**
 * @tc.name: GlobalOffsetInSelectedArea001
 * @tc.desc: test text_pattern.cpp GlobalOffsetInSelectedArea function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNineNg, GlobalOffsetInSelectedArea001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->selectOverlay_->HasRenderTransform());
    Offset globalOffset(1.0, 1.0);
    EXPECT_FALSE(pattern->GlobalOffsetInSelectedArea(globalOffset));
}
}