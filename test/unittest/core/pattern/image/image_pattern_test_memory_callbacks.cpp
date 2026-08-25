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
 * @file image_pattern_test_memory_callbacks.cpp
 * @brief TDD test coverage for ImagePattern memory management and callbacks,
 *        including FEAT-028 cached image decode eligibility lifecycle.
 */

#include "image_base.h"

#include "base/utils/system_properties.h"
#include "core/components_ng/pattern/scrollable/scrollable_utils.h"

namespace OHOS::Ace::NG {

class ImagePatternMemoryCallbacksTestNg : public ImageBases {};

/**
 * @tc.name: CachedImageDecodeActiveState001
 * @tc.desc: FEAT-028 SetCachedImageDecodeActive releases decoded resources when leaving the
 *           decode window and preserves the image source configuration.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, CachedImageDecodeActiveState001, TestSize.Level1)
{
    auto frameNode = ImageBases::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step1. default state keeps decode eligibility.
     * @tc.expected: active.
     */
    EXPECT_TRUE(pattern->IsCachedImageDecodeActive());

    /**
     * @tc.steps: step2. leaving the decode window releases decoded resources (AC-1.4 / R-4).
     * @tc.expected: loading contexts, canvas images and content modifier are all released.
     */
    pattern->SetCachedImageDecodeActive(false);
    EXPECT_FALSE(pattern->IsCachedImageDecodeActive());
    EXPECT_EQ(pattern->loadingCtx_, nullptr);
    EXPECT_EQ(pattern->image_, nullptr);
    EXPECT_EQ(pattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(pattern->altImage_, nullptr);
    EXPECT_EQ(pattern->altErrorCtx_, nullptr);
    EXPECT_EQ(pattern->altErrorImage_, nullptr);
    EXPECT_EQ(pattern->contentMod_, nullptr);
    EXPECT_TRUE(pattern->isRecycledImage_);

    /**
     * @tc.steps: step3. source configuration is preserved for reload.
     * @tc.expected: image source info is untouched.
     */
    auto layoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(layoutProperty->GetImageSourceInfo().has_value());

    /**
     * @tc.steps: step4. repeated deactivation is idempotent (AC-2.3 / ADR-5).
     * @tc.expected: state keeps false, no crash.
     */
    pattern->SetCachedImageDecodeActive(false);
    EXPECT_FALSE(pattern->IsCachedImageDecodeActive());
}

/**
 * @tc.name: CachedImageDecodeActiveState002
 * @tc.desc: FEAT-028 re-entering the decode window restores decode eligibility and reloads
 *           from the preserved source (AC-1.5 / R-5).
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, CachedImageDecodeActiveState002, TestSize.Level1)
{
    auto frameNode = ImageBases::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->SetCachedImageDecodeActive(false);
    EXPECT_FALSE(pattern->IsCachedImageDecodeActive());
    EXPECT_EQ(pattern->loadingCtx_, nullptr);

    /**
     * @tc.steps: step1. re-entering the decode window reloads from the preserved source.
     * @tc.expected: eligibility restored and a new loading context is created.
     */
    pattern->SetCachedImageDecodeActive(true);
    EXPECT_TRUE(pattern->IsCachedImageDecodeActive());
    EXPECT_NE(pattern->loadingCtx_, nullptr);

    /**
     * @tc.steps: step2. repeated activation is idempotent.
     * @tc.expected: loading context is kept, no reload churn.
     */
    auto firstCtx = pattern->loadingCtx_;
    pattern->SetCachedImageDecodeActive(true);
    EXPECT_TRUE(pattern->IsCachedImageDecodeActive());
    EXPECT_EQ(pattern->loadingCtx_, firstCtx);
}

/**
 * @tc.name: CachedImageDecodeLoadGuard001
 * @tc.desc: FEAT-028 LoadImageDataIfNeed and async load success obey the decode eligibility.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, CachedImageDecodeLoadGuard001, TestSize.Level1)
{
    auto frameNode = ImageBases::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto sourceInfo = layoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));

    /**
     * @tc.steps: step1. while decode is revoked, load entry does nothing (AC-1.4).
     * @tc.expected: no loading context is created.
     */
    pattern->SetCachedImageDecodeActive(false);
    pattern->loadingCtx_ = nullptr;
    pattern->LoadImageDataIfNeed();
    EXPECT_EQ(pattern->loadingCtx_, nullptr);

    /**
     * @tc.steps: step2. async load success arriving after deactivation is discarded (AC-2.3 / ADR-5).
     * @tc.expected: no decoded canvas image is committed.
     */
    pattern->OnImageLoadSuccess();
    EXPECT_EQ(pattern->image_, nullptr);

    /**
     * @tc.steps: step3. load success callback created while inactive drops the result.
     * @tc.expected: callback returns without touching pattern state.
     */
    auto successCallback = pattern->CreateLoadSuccessCallback();
    ASSERT_NE(successCallback, nullptr);
    successCallback(sourceInfo);
    EXPECT_EQ(pattern->image_, nullptr);

    /**
     * @tc.steps: step4. alt load success callbacks also obey the eligibility (ADR-4/ADR-5).
     * @tc.expected: callbacks return without committing alt resources.
     */
    auto altSuccessCallback = pattern->CreateLoadSuccessCallbackForAlt();
    ASSERT_NE(altSuccessCallback, nullptr);
    altSuccessCallback(sourceInfo);
    EXPECT_EQ(pattern->altImage_, nullptr);
    auto altErrorSuccessCallback = pattern->CreateLoadSuccessCallbackForAltError();
    ASSERT_NE(altErrorSuccessCallback, nullptr);
    altErrorSuccessCallback(sourceInfo);
    EXPECT_EQ(pattern->altErrorImage_, nullptr);
}

/**
 * @tc.name: ScrollableUtilsImageDecodeRange001
 * @tc.desc: FEAT-028 ScrollableUtils::UpdateCachedImageDecodeRange applies the decode window
 *           to already-built cached children on a low memory device only.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, ScrollableUtilsImageDecodeRange001, TestSize.Level1)
{
    const int32_t originDdrSize = SystemProperties::bootVendorDdrSize_;
    auto host = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(host, nullptr);
    std::vector<RefPtr<ImagePattern>> itemPatterns;
    for (int32_t i = 0; i < 10; ++i) {
        auto item = FrameNode::CreateFrameNode(V2::LIST_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        auto image = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, -1, AceType::MakeRefPtr<ImagePattern>());
        item->AddChild(image);
        host->AddChild(item);
        itemPatterns.push_back(image->GetPattern<ImagePattern>());
    }

    /**
     * @tc.steps: step1. low memory device (8 GiB), visible [4, 5], 5 cached items per side.
     * @tc.expected: window is 1 per side, items 3-6 stay active, others release decode (AC-1.1).
     */
    SystemProperties::bootVendorDdrSize_ = 8;
    ScrollableUtils::UpdateCachedImageDecodeRange(host, 4, 5, 5, 5);
    for (int32_t i = 0; i < 10; ++i) {
        bool expectActive = (i >= 3 && i <= 6);
        EXPECT_EQ(itemPatterns[i]->IsCachedImageDecodeActive(), expectActive) << "index: " << i;
    }

    /**
     * @tc.steps: step2. item re-enters the decode window after scrolling.
     * @tc.expected: eligibility is restored (AC-1.5).
     */
    ScrollableUtils::UpdateCachedImageDecodeRange(host, 7, 8, 5, 5);
    for (int32_t i = 0; i < 10; ++i) {
        bool expectActive = (i >= 6 && i <= 9);
        EXPECT_EQ(itemPatterns[i]->IsCachedImageDecodeActive(), expectActive) << "index: " << i;
    }

    /**
     * @tc.steps: step3. cacheCount == 0 on both sides keeps existing behavior (AC-1.3).
     * @tc.expected: no eligibility update.
     */
    ScrollableUtils::UpdateCachedImageDecodeRange(host, 0, 1, 0, 0);
    for (int32_t i = 0; i < 10; ++i) {
        bool expectActive = (i >= 6 && i <= 9);
        EXPECT_EQ(itemPatterns[i]->IsCachedImageDecodeActive(), expectActive) << "index: " << i;
    }

    /**
     * @tc.steps: step4. high memory device (> 8 GiB) keeps existing strategy (AC-2.1 / R-6).
     * @tc.expected: after re-activating every child as low memory device, switching to a high
     *               memory device never revokes eligibility again.
     */
    ScrollableUtils::UpdateCachedImageDecodeRange(host, 0, 9, 5, 5);
    for (int32_t i = 0; i < 10; ++i) {
        EXPECT_TRUE(itemPatterns[i]->IsCachedImageDecodeActive()) << "index: " << i;
    }
    SystemProperties::bootVendorDdrSize_ = 9;
    ScrollableUtils::UpdateCachedImageDecodeRange(host, 0, 1, 5, 5);
    for (int32_t i = 0; i < 10; ++i) {
        EXPECT_TRUE(itemPatterns[i]->IsCachedImageDecodeActive()) << "index: " << i;
    }

    SystemProperties::bootVendorDdrSize_ = originDdrSize;
}

/**
 * @tc.name: ScrollableUtilsImageDecodeRangeForItem001
 * @tc.desc: FEAT-028 ScrollableUtils::UpdateCachedImageDecodeActiveForItem applies eligibility
 *           to a single cached child for predict-build paths.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, ScrollableUtilsImageDecodeRangeForItem001, TestSize.Level1)
{
    const int32_t originDdrSize = SystemProperties::bootVendorDdrSize_;
    auto host = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(host, nullptr);
    std::vector<RefPtr<ImagePattern>> itemPatterns;
    for (int32_t i = 0; i < 10; ++i) {
        auto item = FrameNode::CreateFrameNode(V2::LIST_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
        auto image = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, -1, AceType::MakeRefPtr<ImagePattern>());
        item->AddChild(image);
        host->AddChild(item);
        itemPatterns.push_back(image->GetPattern<ImagePattern>());
    }

    /**
     * @tc.steps: step1. low memory device, item 0 is outside the decode window [3, 10].
     * @tc.expected: item 0 images become decode inactive.
     */
    SystemProperties::bootVendorDdrSize_ = 8;
    ScrollableUtils::UpdateCachedImageDecodeActiveForItem(host, 0, 4, 5, 5, 5);
    EXPECT_FALSE(itemPatterns[0]->IsCachedImageDecodeActive());

    /**
     * @tc.steps: step2. item 4 is the visible start, inside the decode window.
     * @tc.expected: item 4 images stay decode active.
     */
    ScrollableUtils::UpdateCachedImageDecodeActiveForItem(host, 4, 4, 5, 5, 5);
    EXPECT_TRUE(itemPatterns[4]->IsCachedImageDecodeActive());

    /**
     * @tc.steps: step3. item 3 is inside the one-item decode window before the visible range.
     * @tc.expected: item 3 images stay decode active.
     */
    ScrollableUtils::UpdateCachedImageDecodeActiveForItem(host, 3, 4, 5, 5, 5);
    EXPECT_TRUE(itemPatterns[3]->IsCachedImageDecodeActive());

    /**
     * @tc.steps: step4. high memory device never revokes eligibility (AC-2.1).
     * @tc.expected: after re-activating item 0 as low memory device, switching to a high memory
     *               device keeps it active.
     */
    ScrollableUtils::UpdateCachedImageDecodeActiveForItem(host, 0, 0, 1, 5, 5);
    EXPECT_TRUE(itemPatterns[0]->IsCachedImageDecodeActive());
    SystemProperties::bootVendorDdrSize_ = 12;
    ScrollableUtils::UpdateCachedImageDecodeActiveForItem(host, 0, 4, 5, 5, 5);
    EXPECT_TRUE(itemPatterns[0]->IsCachedImageDecodeActive());

    SystemProperties::bootVendorDdrSize_ = originDdrSize;
}
} // namespace OHOS::Ace::NG
