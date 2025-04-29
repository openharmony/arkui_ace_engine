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

#include "bridge/declarative_frontend/jsview/models/line_model_impl.h"
#include "bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void LineModelImpl::Create()
{
    RefPtr<ShapeComponent> lineComponent = AceType::MakeRefPtr<OHOS::Ace::ShapeComponent>(ShapeType::LINE);
    ViewStackProcessor::GetInstance()->ClaimElementId(lineComponent);
    lineComponent->SetStroke(Color::BLACK);
    ViewStackProcessor::GetInstance()->Push(lineComponent);
}

void LineModelImpl::StartPoint(const ShapePoint &value)
{
    auto line = AceType::DynamicCast<ShapeComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!line) {
        LOGE("startPointComponent is null.");
        return;
    }
    line->SetStart(value);
}

void LineModelImpl::EndPoint(const ShapePoint &value)
{
    auto line = AceType::DynamicCast<ShapeComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!line) {
        LOGE("startPointComponent is null.");
        return;
    }
    line->SetEnd(value);
}

} // namespace OHOS::Ace::Framework