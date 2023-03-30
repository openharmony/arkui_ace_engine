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

#include "base/geometry/ng/rect_t.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/marquee/marquee_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_algorithm.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"
#include "core/components_ng/test/mock/syntax/mock_lazy_for_each_builder.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/menu/menu_view.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
class MenuLayoutAlgorithmTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void MenuLayoutAlgorithmTestNg::SetUpTestCase() {}
void MenuLayoutAlgorithmTestNg::TearDownTestCase() {}
void MenuLayoutAlgorithmTestNg::SetUp() {}
void MenuLayoutAlgorithmTestNg::TearDown() {}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg001
 * @tc.desc: Verify HorizontalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg001, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(50, 100);
    SizeF size_f(100, 200);
    float clickPosition = 50.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    auto result = menuLayoutAlgorithm->HorizontalLayout(size, clickPosition);
    EXPECT_EQ(result, clickPosition);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg002
 * @tc.desc: Verify HorizontalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg002, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(50, 100);
    SizeF size_f(100, 200);
    float clickPosition = 60.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    auto result = menuLayoutAlgorithm->HorizontalLayout(size, clickPosition);
    EXPECT_EQ(result, size_f.Width() - size.Width());
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg003
 * @tc.desc: Verify HorizontalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg003, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(70, 100);
    SizeF size_f(100, 200);
    float clickPosition = 60.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    auto result = menuLayoutAlgorithm->HorizontalLayout(size, clickPosition);
    EXPECT_EQ(result, menuLayoutAlgorithm->wrapperSize_.Width() - size.Width());
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg004
 * @tc.desc: Verify HorizontalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg004, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(100, 100);
    SizeF size_f(100, 200);
    float clickPosition = 60.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    auto result = menuLayoutAlgorithm->HorizontalLayout(size, clickPosition);
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg005
 * @tc.desc: Verify VerticalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg005, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(100, 100);
    SizeF size_f(100, 200);
    float clickPosition = 100.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    auto result = menuLayoutAlgorithm->VerticalLayout(size, clickPosition);
    EXPECT_EQ(result, clickPosition);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg006
 * @tc.desc: Verify VerticalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg006, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(100, 100);
    float clickPosition = 150.0f;
    menuLayoutAlgorithm->topSpace_ = 200.0f;
    auto result = menuLayoutAlgorithm->VerticalLayout(size, clickPosition);
    EXPECT_EQ(result, menuLayoutAlgorithm->topSpace_ - size.Height());
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg007
 * @tc.desc: Verify VerticalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg007, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(100, 150);
    SizeF size_f(100, 200);
    float clickPosition = 100.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    auto result = menuLayoutAlgorithm->VerticalLayout(size, clickPosition);
    EXPECT_EQ(result, menuLayoutAlgorithm->wrapperSize_.Height() - size.Height());
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg008
 * @tc.desc: Verify VerticalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg008, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(100, 200);
    SizeF size_f(100, 200);
    float clickPosition = 100.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    auto result = menuLayoutAlgorithm->VerticalLayout(size, clickPosition);
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg009
 * @tc.desc: Verify Initialize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg009, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    const std::string tag = "tag";
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<Pattern>();
    MenuView menuView;
    std::vector<SelectParam> params;
    params.emplace_back("A", "B");
    int32_t targetId = 1;
    auto frameNode = menuView.Create(params, targetId);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapper* layoutWrapper = new LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    menuLayoutAlgorithm->Initialize(layoutWrapper);
    EXPECT_EQ(menuLayoutAlgorithm->wrapperSize_.Width(), 0);
    delete layoutWrapper;
    layoutWrapper = nullptr;
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg010
 * @tc.desc: Verify Layout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAlgorithmTestNg, MenuLayoutAlgorithmTestNg010, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    OffsetF offset(10, 10);
    menuLayoutAlgorithm->position_ = offset;
    const std::string tag = "tag";
    int32_t nodeId = 1;
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<Pattern>();
    bool isRoot = false;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<FrameNode> frameNode = AceType::MakeRefPtr<FrameNode>(tag, nodeId, pattern, isRoot);
    LayoutWrapper* layoutWrapper = new LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    RefPtr<LazyForEachActuator> actuator = AceType::MakeRefPtr<LazyForEachActuator>();
    auto builder = AceType::DynamicCast<LazyForEachBuilder>(actuator);
    RefPtr<LazyForEachNode> host_ = AceType::MakeRefPtr<LazyForEachNode>(nodeId, builder);
    WeakPtr<LazyForEachNode> host(host_);
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(builder, host);
    wrapperBuilder->OnGetOrCreateWrapperByIndex(nodeId);
    auto children = wrapperBuilder->OnExpandChildLayoutWrapper();
    auto layoutWrapper_ = wrapperBuilder->GetOrCreateWrapperByIndex(nodeId);
    menuLayoutAlgorithm->Layout(layoutWrapper);
    EXPECT_EQ(menuLayoutAlgorithm->position_.GetX(), 10);
    delete layoutWrapper;
    layoutWrapper = nullptr;
}
} // namespace
} // namespace OHOS::Ace::NG