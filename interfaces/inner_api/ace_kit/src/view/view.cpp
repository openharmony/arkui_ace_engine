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

#include "ui/view/view.h"

#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "ui/base/referenced.h"
#include "ui/view_stack/view_stack_processor.h"

#include "core/components_ng/base/view_abstract.h"

namespace OHOS::Ace::Kit {

View::View() = default;

View::~View() = default;

const RefPtr<FrameNode>& View::GetNode() const
{
    return node_;
}

void View::SetWidth(const CalcDimension& width)
{
    if (width.Unit() == DimensionUnit::CALC) {
        NG::ViewAbstract::SetWidth(reinterpret_cast<AceNode*>(node_->GetHandle()), NG::CalcLength(width.CalcValue()));
    } else {
        NG::ViewAbstract::SetWidth(reinterpret_cast<AceNode*>(node_->GetHandle()), NG::CalcLength(width));
    }
}

void View::SetHeight(const CalcDimension& height)
{
    if (height.Unit() == DimensionUnit::CALC) {
        NG::ViewAbstract::SetHeight(reinterpret_cast<AceNode*>(node_->GetHandle()), NG::CalcLength(height.CalcValue()));
    } else {
        NG::ViewAbstract::SetHeight(reinterpret_cast<AceNode*>(node_->GetHandle()), NG::CalcLength(height));
    }
}

} // namespace OHOS::Ace::Kit
