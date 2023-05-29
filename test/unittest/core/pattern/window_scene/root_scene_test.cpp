/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/window_scene/root/root_scene_model.h"
#include "core/components_ng/pattern/window_scene/root/root_scene_node.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class RootSceneTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
};

/**
 * @tc.name: RootSceneTest001
 * @tc.desc: RootScene test
 * @tc.type: FUNC
 */
HWTEST_F(RootSceneTest, RootSceneTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RootSceneModel.
     */
    auto model = RootSceneModel();
    model.Create();

    /**
     * @tc.steps: step2. Create RootScene.
     */
    auto rootSceneNode =
        AceType::DynamicCast<RootSceneNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(rootSceneNode, nullptr);
    auto isAtomic = rootSceneNode->IsAtomicNode();
    EXPECT_EQ(isAtomic, false);
}
} // namespace OHOS::Ace::NG
