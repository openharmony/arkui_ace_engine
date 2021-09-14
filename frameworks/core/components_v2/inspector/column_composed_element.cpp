/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components_v2/inspector/column_composed_element.h"

#include "base/log/dump_log.h"
#include "core/components/common/layout/constants.h"
#include "core/components/flex/flex_element.h"

namespace OHOS::Ace::V2 {

void ColumnComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    DumpLog::GetInstance().AddDesc(
        std::string("alignSelf: ").append(std::to_string(static_cast<int32_t>(GetAlignContent()))));
}

FlexAlign ColumnComposedElement::GetAlignContent()
{
    auto node = GetInspectorNode(ColumnElement::TypeId());
    if (!node) {
        return FlexAlign::CENTER;
    }

    RefPtr<RenderFlex> renderFlex = AceType::DynamicCast<RenderFlex>(node);
    if (renderFlex) {
        return renderFlex->GetAlignItem();
    }
    return FlexAlign::CENTER;
}

} // namespace OHOS::Ace::V2