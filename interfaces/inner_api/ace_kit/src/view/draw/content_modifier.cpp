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

#include "ui/view/draw/content_modifier.h"

#include <memory>

#include "interfaces/inner_api/ace_kit/src/view/draw/modifier_adapter.h"

namespace OHOS::Ace::Kit {

ContentModifier::ContentModifier() {}

ContentModifier::~ContentModifier() {}

void ContentModifier::AttachRSProperty(const std::shared_ptr<Rosen::RSPropertyBase>& property)
{
    if (modifierAdapter_) {
        modifierAdapter_->AttachRSProperty(property);
    }
}

void ContentModifier::InitAdapter()
{
    if (!modifierAdapter_) {
        modifierAdapter_ = std::make_shared<ContentModifierAdapter>(Claim(this));
    }
}

const std::shared_ptr<ContentModifierAdapter>& ContentModifier::GetRSModifier() const
{
    return modifierAdapter_;
}

} // namespace OHOS::Ace::Kit
