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

#include "base/geometry/calc_dimension.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_paint_method.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_paint_property.h"
#include "core/components_ng/render/paint_property.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
class MenuWrapperPaintMethodTestNg : public testing::Test {
protected:
    PaintWrapper* GetPaintWrapper(RefPtr<MenuWrapperPaintProperty> paintProperty);
};

PaintWrapper* MenuWrapperPaintMethodTestNg::GetPaintWrapper(RefPtr<MenuWrapperPaintProperty> paintProperty)
{
    RefPtr<MenuWrapperPaintProperty> paintProp = AceType::MakeRefPtr<MenuWrapperPaintProperty>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    return paintWrapper;
}
} // namespace
/**
 * @tc.name: MenuWrapperPaintMethodTestNg001
 * @tc.desc: Verify GetOverlayDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperPaintMethodTestNg, MenuWrapperPaintMethodTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paint method object.
     */
    RefPtr<MenuWrapperPaintProperty> paintProp = AceType::MakeRefPtr<MenuWrapperPaintProperty>();
    RefPtr<MenuWrapperPaintMethod> paintMethod = AceType::MakeRefPtr<MenuWrapperPaintMethod>();
    PaintWrapper* paintWrapper = GetPaintWrapper(paintProp);
    /**
     * @tc.steps: step2. excute GetOverlayDrawFunction.
     * @tc.expected:  return value are as expected.
     */
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: MenuWrapperPaintMethodTestNg002
 * @tc.desc: Verify UpdateArrowPath.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperPaintMethodTestNg, MenuWrapperPaintMethodTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paint method object.
     */
    RefPtr<MenuWrapperPaintProperty> paintProp = AceType::MakeRefPtr<MenuWrapperPaintProperty>();
    RefPtr<MenuWrapperPaintMethod> paintMethod = AceType::MakeRefPtr<MenuWrapperPaintMethod>();
    /**
     * @tc.steps: step2. update paint property and excute GetOverlayDrawFunction.
     * @tc.expected:  return value are as expected.
     */
    paintProp->UpdateEnableArrow(true);
    paintProp->UpdateArrowPosition(OffsetF(10.0f, 10.0f));
    Placement placements[] = {
        Placement::TOP,
        Placement::BOTTOM,
        Placement::RIGHT,
        Placement::LEFT
    };
    for (Placement placementValue : placements) {
        paintProp->UpdateArrowPlacement(placementValue);
        PaintWrapper* paintWrapper = GetPaintWrapper(paintProp);
        auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
        EXPECT_NE(result, nullptr);
        delete paintWrapper;
        paintWrapper = nullptr;
    }
}
} // namespace OHOS::Ace::NG