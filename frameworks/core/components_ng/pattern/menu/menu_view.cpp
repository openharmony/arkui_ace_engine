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

#include "core/components_ng/pattern/menu/menu_view.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/option/option_paint_property.h"
#include "core/components_ng/pattern/option/option_view.h"
#include "core/components_ng/pattern/text/span_view.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

// create menu with menuItems
RefPtr<FrameNode> MenuView::Create(
    const std::vector<optionParam>& params, const std::string& targetTag, int32_t targetId)
{
    auto wrapperId = ElementRegister::GetInstance()->MakeUniqueId();
    // use wrapper to detect click events outside menu
    auto wrapperNode = FrameNode::CreateFrameNode(
        V2::MENU_WRAPPER_ETS_TAG, wrapperId, AceType::MakeRefPtr<MenuWrapperPattern>(targetId));

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, nodeId, AceType::MakeRefPtr<MenuPattern>());

    // update menu props
    auto layoutProps = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    layoutProps->UpdateTargetId(targetId);
    layoutProps->UpdateTargetTag(targetTag);

    auto paintProps = menuNode->GetPaintProperty<PaintProperty>();
    paintProps->UpdatePropertyChangeFlag(PROPERTY_UPDATE_RENDER);

    menuNode->MountToParent(wrapperNode);
    menuNode->MarkModifyDone();

    // append options to menu
    for (size_t i = 0; i < params.size(); ++i) {
        auto optionNode = OptionView::Create(params[i].first, params[i].second, i);
        // first node never paints divider
        if (i == 0) {
            auto props = optionNode->GetPaintProperty<OptionPaintProperty>();
            props->UpdateNeedDivider(false);
        }
        optionNode->MountToParent(menuNode);
        optionNode->MarkModifyDone();
    }

    return wrapperNode;
}

} // namespace OHOS::Ace::NG
