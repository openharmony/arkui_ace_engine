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
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/option/option_event_hub.h"
#include "core/components_ng/pattern/option/option_pattern.h"
#include "core/components_ng/pattern/option/option_theme.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> OptionView::Create(const std::string& value, const std::function<void()>& onClickFunc, int index)
{
    auto Id = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, Id, AceType::MakeRefPtr<OptionPattern>(index));

    auto eventHub = node->GetEventHub<OptionEventHub>();
    CHECK_NULL_RETURN(eventHub, nullptr);
    eventHub->SetOnClick(onClickFunc);

    auto paintProps = node->GetPaintProperty<OptionPaintProperty>();
    // TODO: replace by theme
    paintProps->UpdateBackgroundColor(Color(DEFAULT_BACKGROUND_COLOR));
    paintProps->UpdateSelectedBackgroundColor(Color(DEFAULT_HOVER_BACKGROUND_COLOR));

    // create child text node
    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
    auto textProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    textProperty->UpdateContent(value);
    textNode->MountToParent(node);
    textNode->MarkModifyDone();

    return node;
}

} // namespace OHOS::Ace::NG