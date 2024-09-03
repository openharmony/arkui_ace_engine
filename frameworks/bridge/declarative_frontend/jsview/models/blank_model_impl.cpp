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

#include "frameworks/bridge/declarative_frontend/jsview/models/blank_model_impl.h"

#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
void BlankModelImpl::Create()
{
    auto specializedBox = AceType::MakeRefPtr<OHOS::Ace::BoxComponent>();

    // specialized component should be firstly pushed.
    ViewStackProcessor::GetInstance()->ClaimElementId(specializedBox);
    ViewStackProcessor::GetInstance()->Push(specializedBox);

    // Blank fill the remain space.
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flexItem->SetFlexGrow(1);
    flexItem->SetFlexShrink(0);
    flexItem->SetMustStretch(true);
}

void BlankModelImpl::SetBlankMin(const Dimension& blankMin)
{
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    flexItem->SetFlexBasis(blankMin.IsValid() ? blankMin : Dimension());
}

void BlankModelImpl::SetHeight(const Dimension& height)
{
    auto flexItem = ViewStackProcessor::GetInstance()->GetFlexItemComponent();
    if (height > flexItem->GetFlexBasis()) {
        flexItem->SetFlexBasis(height);
    }
}

void BlankModelImpl::SetColor(const Color& color)
{
    auto blank = ViewStackProcessor::GetInstance()->GetBoxComponent();
    CHECK_NULL_VOID(blank);
    blank->SetColor(color);
}
} // namespace OHOS::Ace::Framework
