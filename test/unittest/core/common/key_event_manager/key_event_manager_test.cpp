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

#include "gtest/gtest.h"
#include "interfaces/inner_api/ace_kit/include/ui/base/lifecycle_checkable.h"
#include "core/common/key_event_manager.h"
#include "base/input_manager/input_manager.h"
#include "base/ressched/ressched_report.h"
#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/overlay/sheet_manager.h"
#include "core/components/theme/app_theme.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class MockKeyEventManager : public KeyEventManager {
public:
    MockKeyEventManager() = default;
    ~MockKeyEventManager() override = default;
protected:
    int32_t GetInstanceId() override
    {
        return 0;
    }
};

class KeyEventManagerTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: IsSystemKeyboardShortcut001
 * @tc.desc: Verify the AddSubContainer Interface of FormManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventManagerTest, IsSystemKeyboardShortcut001, TestSize.Level1)
{
    KeyEvent event;

    auto keyEventManager = AceType::MakeRefPtr<MockKeyEventManager>();
    std::vector<HotKey> systemHotKeys;

    auto ret = keyEventManager->IsSystemKeyboardShortcut(event);
    EXPECT_FALSE(ret);

    std::set<int32_t> mySet = {static_cast<int32_t>(KeyCode::KEY_1)};
    int32_t myInt = static_cast<int32_t>(KeyCode::KEY_1);
    std::tuple<std::set<int32_t>, int32_t> a(mySet, myInt);
    systemHotKeys.push_back(a);
    event.pressedCodes.push_back(KeyCode::KEY_1);
    event.code = KeyCode::KEY_1;
    ret = keyEventManager->IsSystemKeyboardShortcut(event);
    EXPECT_FALSE(ret);
}
} // namespace OHOS::Ace::NG