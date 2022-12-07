/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#define private public
#define protected public
#include "gtest/gtest.h"

#include "base/geometry/calc_dimension.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/pattern/menu/menu_paint_method.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/render/paint_property.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
class MenuPaintMethodTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void MenuPaintMethodTestNg::SetUpTestCase() {}
void MenuPaintMethodTestNg::TearDownTestCase() {}
void MenuPaintMethodTestNg::SetUp() {}
void MenuPaintMethodTestNg::TearDown() {}

/**
 * @tc.name: MenuPaintMethodTestNg001
 * @tc.desc: Verify GetOverlayDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintMethodTestNg, MenuPaintMethodTestNg001, TestSize.Level1)
{
    RefPtr<MenuPaintMethod> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuPaintMethod>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<PaintProperty> layoutProperty = AceType::MakeRefPtr<PaintProperty>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, layoutProperty);
    auto result = menuLayoutAlgorithm->GetOverlayDrawFunction(paintWrapper);
    EXPECT_FALSE(result == nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: MenuPaintMethodTestNg002
 * @tc.desc: Verify PaintGradient.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintMethodTestNg, MenuPaintMethodTestNg002, TestSize.Level1)
{
    RefPtr<MenuPaintMethod> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuPaintMethod>();
    RSCanvas canvas;
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<PaintProperty> layoutProperty = AceType::MakeRefPtr<PaintProperty>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, layoutProperty);
    bool isTop = true;
    menuLayoutAlgorithm->PaintGradient(canvas, paintWrapper, isTop);
    EXPECT_EQ(OUT_PADDING.ConvertToPx(), 0.0);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: MenuPaintMethodTestNg003
 * @tc.desc: Verify PaintGradient.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintMethodTestNg, MenuPaintMethodTestNg003, TestSize.Level1)
{
    RefPtr<MenuPaintMethod> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuPaintMethod>();
    RSCanvas canvas;
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<PaintProperty> layoutProperty = AceType::MakeRefPtr<PaintProperty>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, layoutProperty);
    bool isTop = false;
    menuLayoutAlgorithm->PaintGradient(canvas, paintWrapper, isTop);
    EXPECT_EQ(OUT_PADDING.ConvertToPx(), 0.0);
    delete paintWrapper;
    paintWrapper = nullptr;
}
} // namespace
} // namespace OHOS::Ace::NG