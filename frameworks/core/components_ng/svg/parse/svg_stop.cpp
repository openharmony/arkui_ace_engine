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

#include "frameworks/core/components_ng/svg/parse/svg_stop.h"

#include "frameworks/core/components/declaration/svg/svg_stop_declaration.h"

namespace OHOS::Ace::NG {

SvgStop::SvgStop() : SvgNode()
{
    declaration_ = AceType::MakeRefPtr<SvgStopDeclaration>();
    declaration_->Init();
    declaration_->InitializeStyle();
}

RefPtr<SvgNode> SvgStop::Create()
{
    return AceType::MakeRefPtr<SvgStop>();
}

const GradientColor& SvgStop::GetGradientColor() const
{
    auto declaration = AceType::DynamicCast<SvgStopDeclaration>(declaration_);
    return declaration->GetGradientColor();
}

} // namespace OHOS::Ace::NG
