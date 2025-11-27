/*
 * Copyright (c) 2025 iSoftStone Information Technology (Group) Co.,Ltd.
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

#define protected public
#define private public
#include "base/subwindow/subwindow_manager.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/unittest/core/base/view_abstract_test_ng.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "core/components_ng/pattern/pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ViewAbstractModelStaticTestNg : public testing::Test {};

/**
 * @tc.name: SetBackgroundImagePosition
 * @tc.desc: Test SetBackgroundImagePosition
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, SetBackgroundImagePosition, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and renderContext
     */
    auto frameNode = AceType::RawPtr(FRAME_NODE_REGISTER);
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step2. set background image position and check renderContext's background image position
     * @tc.expected: renderContext's background image position is set correctly
     */
    BackgroundImagePosition bgImgPosition;
    ViewAbstractModelStatic::SetBackgroundImagePosition(frameNode, bgImgPosition, false);
    EXPECT_TRUE(renderContext->GetBackgroundImagePosition().has_value());
    EXPECT_EQ(renderContext->GetBackgroundImagePosition().value(), bgImgPosition);

    /**
     * @tc.steps: step3. reset background image position and check renderContext's background image position
     * @tc.expected: renderContext's background image position is reset correctly
     */
    ViewAbstractModelStatic::SetBackgroundImagePosition(frameNode, bgImgPosition, true);
    EXPECT_FALSE(renderContext->GetBackgroundImagePosition().has_value());
}
} // namespace OHOS::Ace::NG