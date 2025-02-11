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

#include "core/components_ng/base/view_full_update_model_ng.h"

#include "core/components_ng/pattern/custom/custom_node.h"

namespace OHOS::Ace::NG {

RefPtr<AceType> ViewFullUpdateModelNG::CreateNode(NodeInfo&& info)
{
    ACE_SCOPED_TRACE("JSView::CreateSpecializedComponent");
    // create component, return new something, need to set proper ID
    std::string key = NG::ViewStackProcessor::GetInstance()->ProcessViewId(info.viewId);
    auto composedNode = NG::CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), key);
    if (info.appearFunc) {
        info.appearFunc();
    }
    if (info.updateNodeFunc) {
        info.updateNodeFunc(composedNode);
    }

    auto renderFunction =
        [internalRender = std::move(info.renderFunc)](int64_t deadline, bool& isTimeout) -> RefPtr<UINode> {
        auto uiNode = internalRender();
        return AceType::DynamicCast<UINode>(uiNode);
    };
    composedNode->SetRenderFunction(std::move(renderFunction));
    composedNode->SetPageTransitionFunction(std::move(info.pageTransitionFunc));
    return composedNode;
}

} // namespace OHOS::Ace::NG
