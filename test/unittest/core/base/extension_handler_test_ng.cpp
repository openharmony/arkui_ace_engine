/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include "core/components_ng/base/extension_handler.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/base/modifier.h"
 
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class ExtensionHandlerTestNg : public testing::Test {
};

/**
 * @tc.name: ExtensionHandlerTest001
 * @tc.desc: Measure
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, ExtensionHandlerTest001, TestSize.Level1)
{
    class ExtensionHandler test;
    struct ExtensionLayoutConstraint layoutConstraint;
    layoutConstraint.maxWidth = 10;
    test.Measure(layoutConstraint);
    int32_t width = 0;
    test.SetInnerMeasureImpl([&width](const ExtensionLayoutConstraint& layout) { width = layout.maxWidth; });
    test.Measure(layoutConstraint);
    EXPECT_EQ(layoutConstraint.maxWidth, 10);
}

/**
 * @tc.name: ExtensionHandlerTest002
 * @tc.desc: Layout
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, ExtensionHandlerTest002, TestSize.Level1)
{
    class ExtensionHandler test;
    int32_t width = 10;
    int32_t height = 10;
    int32_t positionX = 10;
    int32_t positionY = 10;
    int32_t count = 0;
    test.Layout(width, height, positionX, positionY);
    test.SetInnerLayoutImpl([&count](int32_t width, int32_t height, int32_t positionX, int32_t positionY)
        { count = height; });
    test.Layout(width, height, positionX, positionY);
    EXPECT_EQ(count, 10);
}

/**
 * @tc.name: ExtensionHandlerTest003
 * @tc.desc: Draw
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, ExtensionHandlerTest003, TestSize.Level1)
{
    class ExtensionHandler test;
    RSCanvas canvas;
    float width = 0;
    float height = 0;
    DrawingContext context {canvas, width, height};
    test.Draw(context);
    int32_t res = 5;
    test.SetInnerDrawImpl([&res](DrawingContext& context) { res = context.width; });
    test.Draw(context);
    EXPECT_EQ(context.width, 0);
}

/**
 * @tc.name: ExtensionHandlerTest004
 * @tc.desc: ForegroundDraw
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, ExtensionHandlerTest004, TestSize.Level1)
{
    class ExtensionHandler test;
    RSCanvas canvas;
    float width = 0;
    float height = 0;
    DrawingContext context {canvas, width, height};
    test.ForegroundDraw(context);
    int32_t res = 5;
    test.SetInnerForegroundDrawImpl([&res](DrawingContext& context) { res = context.width; });
    test.ForegroundDraw(context);
    EXPECT_EQ(context.height, 0);
}

/**
 * @tc.name: ExtensionHandlerTest005
 * @tc.desc: OverlayDraw
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, ExtensionHandlerTest005, TestSize.Level1)
{
    class ExtensionHandler test;
    RSCanvas canvas;
    float width = 0;
    float height = 0;
    DrawingContext context {canvas, width, height};
    test.OverlayDraw(context);
    int32_t res = 5;
    test.SetInnerOverlayDrawImpl([&res](DrawingContext& context) { res = context.width; });
    test.OverlayDraw(context);
    EXPECT_EQ(context.width, 0);
}
}