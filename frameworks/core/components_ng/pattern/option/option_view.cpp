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
#include "core/components_ng/pattern/option/option_view.h"

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/option/option_event_hub.h"
#include "core/components_ng/pattern/option/option_pattern.h"
#include "core/components_ng/pattern/option/option_theme.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {

namespace {

RefPtr<FrameNode> Create(int32_t targetId, int index)
{
    auto Id = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, Id, AceType::MakeRefPtr<OptionPattern>(targetId, index));

    auto paintProps = node->GetPaintProperty<OptionPaintProperty>();
    paintProps->UpdateBackgroundColor(Color(DEFAULT_BACKGROUND_COLOR));
    paintProps->UpdateSelectedBackgroundColor(Color(DEFAULT_HOVER_BACKGROUND_COLOR));

    // set border radius
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    BorderRadiusProperty border;
    border.SetRadius(ROUND_RADIUS_PHONE);
    renderContext->UpdateBorderRadius(border);

    return node;
}

RefPtr<FrameNode> CreateText(const std::string& value, const RefPtr<FrameNode>& parent)
{
    // create child text node
    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);

    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textProperty, nullptr);
    textProperty->UpdateContent(value);
    textNode->MountToParent(parent);
    textNode->MarkModifyDone();

    return textNode;
}

} // namespace

RefPtr<FrameNode> OptionView::CreateMenuOption(
    const std::string& value, const std::function<void()>& onClickFunc, int32_t targetId, int index)
{
    auto option = Create(targetId, index);
    CreateText(value, option);

    auto eventHub = option->GetEventHub<OptionEventHub>();
    CHECK_NULL_RETURN(eventHub, nullptr);
    eventHub->SetOnClick(onClickFunc);

    return option;
}

RefPtr<FrameNode> OptionView::CreateSelectOption(
    const std::string& value, const std::string& icon, int32_t targetId, int index)
{
    LOGI("create option value = %s", value.c_str());
    auto option = Create(targetId, index);
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    row->MountToParent(option);

    auto iconNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(iconNode, nullptr);
    auto props = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    props->UpdateImageSourceInfo(ImageSourceInfo(icon));
    iconNode->MountToParent(row);
    iconNode->MarkModifyDone();

    auto text = CreateText(value, row);
    auto pattern = option->GetPattern<OptionPattern>();
    pattern->SetTextNode(text);

    return option;
}

} // namespace OHOS::Ace::NG