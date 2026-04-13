/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

/**
 * @file image_pattern_test_events_edge_cases.cpp
 * @brief TDD test coverage for ImagePattern events and edge cases - only tests that cover branches
 */

#include "image_base.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"

namespace OHOS::Ace::NG {

class ImagePatternEventsEdgeCasesTestNg : public ImageBases {};

HWTEST_F(ImagePatternEventsEdgeCasesTestNg, AllowVisibleAreaCheck001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_FALSE(pattern->AllowVisibleAreaCheck());
}

HWTEST_F(ImagePatternEventsEdgeCasesTestNg, AllowVisibleAreaCheckOverlayParent001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto parentNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, -1, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    EXPECT_NE(parentNode, nullptr);
    auto parentLayoutProperty = parentNode->GetLayoutProperty();
    EXPECT_NE(parentLayoutProperty, nullptr);
    parentLayoutProperty->SetIsOverlayNode(true);

    frameNode->SetParent(parentNode);

    EXPECT_TRUE(pattern->AllowVisibleAreaCheck());
}

HWTEST_F(ImagePatternEventsEdgeCasesTestNg, hasSceneChanged001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto result = pattern->hasSceneChanged();
    EXPECT_TRUE(result);
}

} // namespace OHOS::Ace::NG