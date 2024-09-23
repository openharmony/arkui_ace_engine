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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "session_manager/include/scene_session_manager.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/window_scene/scene/window_node.h"
#include "core/components_ng/pattern/window_scene/scene/window_scene_model.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string BUNDLE_NAME = "com.example.helloworld";
const std::string ABILITY_NAME = "MainAbility";
const int32_t NODE_ID = 1000;
} // namespace

class WindowSceneTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
};

/**
 * @tc.name: WindowSceneTest01
 * @tc.desc: Create WindowScene with invalid persistentId
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, WindowSceneTest01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create WindowPatternModel.
     */
    int32_t persistentId = 0;
    WindowSceneModel::Create(persistentId);
    /**
     * @tc.steps: step2. Get and check WindowSceneModel.
     */
    auto windowSceneNode =
        AceType::DynamicCast<WindowNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_EQ(windowSceneNode, nullptr);
}

/**
 * @tc.name: WindowSceneTest02
 * @tc.desc: Create WindowScene with invalid persistentId
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, WindowSceneTest02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Request sceneSession.
     */
    Rosen::SessionInfo sessionInfo = {
        .bundleName_ = BUNDLE_NAME,
        .abilityName_ = ABILITY_NAME
    };
    auto session = Rosen::SceneSessionManager::GetInstance().RequestSceneSession(sessionInfo);
    /**
     * @tc.steps: step2. Create WindowPatternModel with persistentId.
     */
    int32_t persistentId = session->GetPersistentId();
    WindowSceneModel::Create(persistentId);
    /**
     * @tc.steps: step3. Get and check WindowSceneModel.
     */
    auto windowSceneNode =
        AceType::DynamicCast<WindowNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(windowSceneNode, nullptr);
}
}