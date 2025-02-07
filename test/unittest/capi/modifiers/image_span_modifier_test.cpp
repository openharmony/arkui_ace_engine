/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/image/image_event_hub.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class ImageSpanModifierTest : public ModifierTestBase<
    GENERATED_ArkUIImageSpanModifier,
    &GENERATED_ArkUINodeModifiers::getImageSpanModifier,
    GENERATED_ARKUI_IMAGE_SPAN
> {
};

const std::vector<LoadImageSuccessEvent> COMPLETE_EVENT_TEST_PLAN = {
    { LoadImageSuccessEvent(100, 100, 100, 100, 1, 100, 100, 100, 100) },
    { LoadImageSuccessEvent(10, 10, 10, 10, 1, 0, 0, 0, 0) },
    { LoadImageSuccessEvent(100, 100, 100, 100, 0, 100, 100, 0, 0) },
    { LoadImageSuccessEvent(10, 20, 30, 40, 1, 50, 60, 70, 80) },
};

/*
 * @tc.name: setOnCompleteTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageSpanModifierTest, setOnCompleteTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnComplete, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static double width = 0.0;
    static double height = 0.0;
    static double componentWidth = 0.0;
    static double componentHeight = 0.0;
    static int32_t loadingStatus = 1;
    static double contentWidth = 0.0;
    static double contentHeight = 0.0;
    static double contentOffsetX = 0.0;
    static double contentOffsetY = 0.0;
    auto onComplete = [](const Ark_Int32 resourceId, const Ark_ImageLoadResult parameter) {
        width = Converter::Convert<float>(parameter.width);
        height = Converter::Convert<float>(parameter.height);
        componentWidth = Converter::Convert<float>(parameter.componentWidth);
        componentHeight = Converter::Convert<float>(parameter.componentHeight);
        loadingStatus = Converter::Convert<int32_t>(parameter.loadingStatus);
        contentWidth = Converter::Convert<float>(parameter.contentWidth);
        contentHeight = Converter::Convert<float>(parameter.contentHeight);
        contentOffsetX = Converter::Convert<float>(parameter.contentOffsetX);
        contentOffsetY = Converter::Convert<float>(parameter.contentOffsetY);
    };
    ImageCompleteCallback func = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onComplete
    };
    modifier_->setOnComplete(node_, &func);

    for (const auto& testValue : COMPLETE_EVENT_TEST_PLAN) {
        eventHub->FireCompleteEvent(testValue);

        EXPECT_NEAR(width, testValue.GetWidth(), FLT_EPSILON);
        EXPECT_NEAR(height, testValue.GetHeight(), FLT_EPSILON);
        EXPECT_NEAR(componentWidth, testValue.GetComponentWidth(), FLT_EPSILON);
        EXPECT_NEAR(componentHeight, testValue.GetComponentHeight(), FLT_EPSILON);
        EXPECT_EQ(loadingStatus, testValue.GetLoadingStatus());
        EXPECT_NEAR(contentWidth, testValue.GetContentWidth(), FLT_EPSILON);
        EXPECT_NEAR(contentHeight, testValue.GetContentHeight(), FLT_EPSILON);
        EXPECT_NEAR(contentOffsetX, testValue.GetContentOffsetX(), FLT_EPSILON);
        EXPECT_NEAR(contentOffsetY, testValue.GetContentOffsetY(), FLT_EPSILON);
    };
}

const std::vector<LoadImageFailEvent> ERROR_EVENT_TEST_PLAN = {
    { LoadImageFailEvent(100, 100, "Error 1") },
    { LoadImageFailEvent(100, 10, "Error 2") },
    { LoadImageFailEvent(10, 100, "Error 3") },
    { LoadImageFailEvent(0, 0, "") },
};

/*
 * @tc.name: setOnErrorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageSpanModifierTest, setOnErrorTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnComplete, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    ASSERT_NE(eventHub, nullptr);

    static double componentWidth = 0.0;
    static double componentHeight = 0.0;
    static std::string message;
    auto onError = [](const Ark_Int32 resourceId, const Ark_ImageError parameter) {
        componentWidth = Converter::Convert<float>(parameter.componentWidth);
        componentHeight = Converter::Convert<float>(parameter.componentHeight);
        message = Converter::Convert<std::string>(parameter.message);
    };
    ImageErrorCallback func = {
        .resource = Ark_CallbackResource {
            .resourceId = frameNode->GetId(),
            .hold = nullptr,
            .release = nullptr,
        },
        .call = onError
    };
    modifier_->setOnError(node_, &func);

    for (const auto& testValue : ERROR_EVENT_TEST_PLAN) {
        eventHub->FireErrorEvent(testValue);
        EXPECT_NEAR(componentWidth, testValue.GetComponentWidth(), FLT_EPSILON);
        EXPECT_NEAR(componentHeight, testValue.GetComponentHeight(), FLT_EPSILON);
        EXPECT_EQ(message, testValue.GetErrorMessage());
    };
}

} // namespace OHOS::Ace::NG
