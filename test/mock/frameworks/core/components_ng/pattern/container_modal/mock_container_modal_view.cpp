/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/container_modal/container_modal_view.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_view_enhance.h"
#include "core/components_ng/pattern/container_modal/static/container_modal_static_view.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
namespace {
RefPtr<FrameNode> BuildMinimalContainerModal(const RefPtr<FrameNode>& content)
{
    auto container = FrameNode::CreateFrameNode("ContainerModal", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ContainerModalPattern>());
    if (content) {
        container->AddChild(content);
    }
    return container;
}
} // namespace

std::function<RefPtr<NG::FrameNode>()> ContainerModalView::customTitileBuilder_ = nullptr;
std::function<RefPtr<NG::FrameNode>(
    const WeakPtr<NG::ContainerModalPatternEnhance>& weakPattern, const RefPtr<NG::FrameNode>& containerTitleRow)>
    ContainerModalView::customControlButtonBuilder_ = nullptr;
float ContainerModalView::baseScale = 0.0f;

RefPtr<FrameNode> ContainerModalView::Create(RefPtr<FrameNode>& content)
{
    return BuildMinimalContainerModal(content);
}

bool ContainerModalView::ConfigCustomWindowMask(RefPtr<PipelineContext>& pipeline, bool enable)
{
    (void)pipeline;
    (void)enable;
    return false;
}

void ContainerModalView::RegistCustomBuilder(std::function<RefPtr<NG::FrameNode>()>& title,
    std::function<RefPtr<NG::FrameNode>(
        const WeakPtr<NG::ContainerModalPatternEnhance>& weakPattern, const RefPtr<NG::FrameNode>& containerTitleRow)>&
        button)
{
    customTitileBuilder_ = title;
    customControlButtonBuilder_ = button;
}

RefPtr<FrameNode> ContainerModalViewEnhance::Create(RefPtr<FrameNode>& content)
{
    return BuildMinimalContainerModal(content);
}

RefPtr<FrameNode> ContainerModalStaticView::Create(RefPtr<FrameNode>& content)
{
    return BuildMinimalContainerModal(content);
}
} // namespace OHOS::Ace::NG
