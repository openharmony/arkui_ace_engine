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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/interfaces/arkoala/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class ImageModifierTest : public ModifierTestBase<GENERATED_ArkUIImageModifier,
                              &GENERATED_ArkUINodeModifiers::getImageModifier, GENERATED_ARKUI_IMAGE> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
    }
};

/**
 * @tc.name: ObjectFit_SetFitType
 * @tc.desc: Test ImageModifierTest
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, ObjectFit_SetFitType, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    modifier_->setObjectFit(frameNode, Ark_ImageFit::ARK_IMAGE_FIT_SCALE_DOWN);
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    ASSERT_EQ("ImageFit.FitHeight", GetAttrValue<std::string>(json, "objectFit"));
}

/**
 * @tc.name: ObjectFit_SetDefaultedFitType
 * @tc.desc: Test ImageModifierTest
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, ObjectFit_SetDefaultedFitType, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    std::string key = "objectFit";
    std::string defaultedFit = "ImageFit.Cover";

    modifier_->setObjectFit(frameNode, static_cast<Ark_ImageFit>(static_cast<int>(ImageFit::FILL) - 1));
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    ASSERT_EQ(defaultedFit, GetAttrValue<std::string>(json, key));

    modifier_->setObjectFit(frameNode, static_cast<Ark_ImageFit>(static_cast<int>(ImageFit::SCALE_DOWN) + 1));
    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    ASSERT_EQ(defaultedFit, GetAttrValue<std::string>(json, key));
}

/**
 * @tc.name: Ctor_InitWithUrl
 * @tc.desc: Test ImageModifierTest
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, Ctor_InitWithUrl, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    std::string urlString = "https://www.example.com/xxx.png";
    Union_CustomObject_Ark_ResourceStr_CustomObject url = {
        .selector = 1,
        .value1 = {
            .selector = 0,
            .value0 = {.chars = urlString.c_str(), .length = urlString.size()}
        }
    };
    modifier_->setImageOptions0(node_, &url);
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    ASSERT_EQ(urlString, GetAttrValue<std::string>(json, "src"));
    ASSERT_EQ(urlString, GetAttrValue<std::string>(json, "rawSrc"));
}

} // namespace OHOS::Ace::NG
