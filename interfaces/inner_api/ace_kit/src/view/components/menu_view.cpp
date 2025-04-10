/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "ui/view/components/menu_view.h"

#include "core/components_ng/pattern/menu/menu_view.h"
#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"

namespace OHOS::Ace::Kit {

RefPtr<FrameNode> MenuView::Create(std::vector<OptionParam>&& params, MenuType type, const MenuParam& menuParam)
{
    std::vector<NG::OptionParam> aceParams;
    for (const OptionParam& optionParam : params) {
        NG::OptionParam aceOptionParam;
        aceOptionParam.value = optionParam.value;
        aceOptionParam.icon = optionParam.icon;
        aceOptionParam.enabled = optionParam.enabled;
        aceOptionParam.action = optionParam.action;
        if (optionParam.symbol) {
            aceOptionParam.symbol = [symbol = optionParam.symbol](WeakPtr<NG::FrameNode> weakAceFrameNode) {
                RefPtr<NG::FrameNode> aceFrameNode = weakAceFrameNode.Upgrade();
                CHECK_NULL_VOID(aceFrameNode);
                symbol(reinterpret_cast<void*>(AceType::RawPtr(aceFrameNode)));
            };
        }
        aceOptionParam.symbolUserDefinedIdealFontSize = optionParam.symbolUserDefinedIdealFontSize;
        aceOptionParam.disableSystemClick = optionParam.disableSystemClick;
        aceOptionParam.isPasteOption = optionParam.isPasteOption;
        aceParams.push_back(aceOptionParam);
    }

    NG::MenuParam aceMenuParam;
    aceMenuParam.isShowInSubWindow = menuParam.isShowInSubWindow;
    aceMenuParam.placement = static_cast<Placement>(menuParam.placement);
    RefPtr<NG::FrameNode> aceNode = OHOS::Ace::NG::MenuView::Create(std::move(aceParams), menuParam.targetId,
        menuParam.targetTag, static_cast<NG::MenuType>(type), aceMenuParam);
    RefPtr<FrameNode> node = AceType::MakeRefPtr<FrameNodeImpl>(aceNode);
    return node;
}
} // OHOS::Ace::Kit