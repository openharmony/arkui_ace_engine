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

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/web/web_content_modifier.h"
#include "core/components_ng/render/adapter/rosen_render_surface.h"
#include "test/mock/core/render/mock_render_surface.h"
#include "test/mock/core/rosen/mock_canvas.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;

namespace OHOS::Ace::NG {

class WebContentModifierTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebContentModifierTest::SetUpTestCase() {}
void WebContentModifierTest::TearDownTestCase() {}
void WebContentModifierTest::SetUp() {}
void WebContentModifierTest::TearDown() {}

/**
 * @tc.name: WebContentModifierTest_001
 * @tc.desc: Test function onDraw.
 * @tc.type: FUNC
 */
HWTEST_F(WebContentModifierTest, onDraw_001, TestSize.Level1)
{
    RefPtr<NG::RenderSurface> renderSuface;
    WebContentModifier modifier(renderSuface);
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 100.0f, 100.0f };
    modifier.onDraw(context);
}

/**
 * @tc.name: WebContentModifierTest_002
 * @tc.desc: Test function onDraw.
 * @tc.type: FUNC
 */
HWTEST_F(WebContentModifierTest, onDraw_002, TestSize.Level1)
{
    RefPtr<NG::RenderSurface> renderSuface = Referenced::MakeRefPtr<NG::RosenRenderSurface>();
    WebContentModifier modifier(renderSuface);
    Testing::MockCanvas rsCanvas;
    DrawingContext context { rsCanvas, 100.0f, 100.0f };
    modifier.onDraw(context);
}

} // namespace OHOS::Ace::NG
