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

#include <gtest/gtest.h>

#include "accessor_test_base.h"
#include "core/components_ng/pattern/rating/rating_pattern.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RatingContentModifierHelperAccessor : public StaticAccessorTest<GENERATED_ArkUIContentModifierHelperAccessor,
                                &GENERATED_ArkUIAccessors::getContentModifierHelperAccessor> {
public:
    void FireBuilder(RatingPattern* pattern)
    {
        pattern->FireBuilder();
    }
};

static constexpr int TEST_NODE_ID = 333;
static constexpr int TEST_OBJ_ID = 1001;
static constexpr int TEST_BUILDER_ID = 1002;
static constexpr bool TEST_DEFAULT_ENABLED = true;
static constexpr bool TEST_DEFAULT_INDICATOR = false;
static constexpr int TEST_DEFAULT_RATING = 0;
static constexpr int TEST_DEFAULT_STARS = 5;
static constexpr double TEST_DEFAULT_STEP_SIZE = 0.5;

/**
 * @tc.name: RatingContentModifierHelperAccessorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierHelperAccessor, RatingContentModifierHelperAccessorTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->contentModifierRating, nullptr);

    RefPtr<FrameNode> testNode = FrameNode::GetOrCreateFrameNode(
            V2::RATING_ETS_TAG, TEST_NODE_ID, []() { return AceType::MakeRefPtr<RatingPattern>(); });
    ASSERT_NE(testNode, nullptr);
    auto pattern = testNode->GetPattern<RatingPattern>();
    ASSERT_NE(pattern, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        int32_t resourceId;
        int32_t objId;
        std::optional<bool> enabled;
        std::optional<float> rating;
        std::optional<float> stars;
        std::optional<float> stepSize;
        std::optional<bool> indicator;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto obj = Converter::ArkCreate<Ark_Object>(TEST_OBJ_ID);

    auto modifierCallback = [](const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
        const Ark_RatingConfiguration config, const Callback_Pointer_Void continuation) {
            auto navigationNode = reinterpret_cast<FrameNode *>(parentNode);
            checkEvent = {
                .nodeId = navigationNode->GetId(),
                .resourceId = resourceId,
                .objId = config.contentModifier.resource.resourceId,
                .enabled = Converter::OptConvert<bool>(config.enabled),
                .rating = Converter::OptConvert<float>(config.rating),
                .stars = Converter::OptConvert<float>(config.stars),
                .stepSize = Converter::OptConvert<float>(config.stepSize),
                .indicator = Converter::OptConvert<bool>(config.indicator),
            };
    };

    EXPECT_CALL(*MockContainer::Current(), GetFrontend()).WillRepeatedly(Return(nullptr));

    auto builder = Converter::ArkValue<RatingModifierBuilder>(modifierCallback, TEST_BUILDER_ID);
    Ark_NativePointer nodePtr = reinterpret_cast<Ark_NativePointer>(testNode.GetRawPtr());
    accessor_->contentModifierRating(nodePtr, &obj, &builder);

    FireBuilder(pattern.GetRawPtr());

    EXPECT_EQ(checkEvent->nodeId, TEST_NODE_ID);
    EXPECT_EQ(checkEvent->resourceId, TEST_BUILDER_ID);
    EXPECT_EQ(checkEvent->objId, TEST_OBJ_ID);
    ASSERT_TRUE(checkEvent->enabled.has_value()) << "enabled is not set";
    EXPECT_EQ(checkEvent->enabled.value(), TEST_DEFAULT_ENABLED);
    EXPECT_EQ(checkEvent->rating.value(), TEST_DEFAULT_RATING);
    EXPECT_EQ(checkEvent->stars.value(), TEST_DEFAULT_STARS);
    EXPECT_EQ(checkEvent->stepSize.value(), TEST_DEFAULT_STEP_SIZE);
    EXPECT_EQ(checkEvent->indicator.value(), TEST_DEFAULT_INDICATOR);
}
}