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

#include "core/components/test/unittest/relative_container/relative_container_test_utils.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/box/box_component.h"
#include "core/components/button/button_component.h"
#include "core/components/button/render_button.h"
#include "core/components/relative_container/relative_container_component.h"
#include "core/components/relative_container/render_relative_container.h"
#include "core/components/root/render_root.h"
#include "core/components/text/text_component.h"
#include "core/components/text_overlay/text_overlay_component.h"

namespace OHOS::Ace {
namespace {
constexpr double RECT_WIDTH = 2000.0;
constexpr double RECT_HEIGHT = 1000.0;
} // namespace

RefPtr<RenderRoot> RelativeContainerTestUtils::CreateRenderRoot()
{
    RefPtr<RenderRoot> root = AceType::MakeRefPtr<MockRenderRoot>();
    const Rect paintRect(0.0, 0.0, RECT_WIDTH, RECT_HEIGHT);
    root->SetPaintRect(paintRect);
    return root;
}

RefPtr<RenderRelativeContainer> RelativeContainerTestUtils::CreateRenderRelativeContainer(
    const RefPtr<PipelineContext>& context)
{
    RefPtr<RenderRelativeContainer> renderRelativeContainer = AceType::MakeRefPtr<MockRenderRelativeContainer>();
    std::list<RefPtr<Component>> children;
    RefPtr<OHOS::Ace::RelativeContainerComponent> relativeContainerComponent =
        AceType::MakeRefPtr<RelativeContainerComponent>(children);
    renderRelativeContainer->Update(relativeContainerComponent);
    renderRelativeContainer->Attach(context);
    return renderRelativeContainer;
}

RefPtr<RenderBox> RelativeContainerTestUtils::CreateRenderBox(
    const double width, const double height, const RefPtr<PipelineContext>& context)
{
    RefPtr<RenderBox> renderBox = AceType::MakeRefPtr<MockRenderBox>();
    RefPtr<BoxComponent> boxComponent = AceType::MakeRefPtr<BoxComponent>();
    boxComponent->SetWidth(width);
    boxComponent->SetHeight(height);
    renderBox->Update(boxComponent);
    renderBox->Attach(context);
    return renderBox;
}

void RelativeContainerTestUtils::AddAlignRule(const std::string id, const AlignDirection& direction,
    const HorizontalAlign& horizontalRule, std::map<AlignDirection, AlignRule>& alignRules)
{
    AlignRule alignRule;
    alignRule.anchor = id;
    alignRule.horizontal = horizontalRule;
    alignRules[direction] = alignRule;
}

void RelativeContainerTestUtils::AddAlignRule(const std::string id, const AlignDirection& direction,
    const VerticalAlign& verticalRule, std::map<AlignDirection, AlignRule>& alignRules)
{
    AlignRule alignRule;
    alignRule.anchor = id;
    alignRule.vertical = verticalRule;
    alignRules[direction] = alignRule;
}
} // namespace OHOS::Ace