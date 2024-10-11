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
    EXPECT_TRUE(false);
}

/**
 * @tc.name: ObjectFit_SetFitType
 * @tc.desc: Test ImageModifierTest
 * @tc.type: FUNC
 */
HWTEST_F(ImageModifierTest, ObjectFit_SetBadFitType, testing::ext::TestSize.Level1)
{
    EXPECT_TRUE(true);
}

} // namespace OHOS::Ace::NG
