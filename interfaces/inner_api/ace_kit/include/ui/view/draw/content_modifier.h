/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_DRAW_CONTENT_MODIFIER_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_DRAW_CONTENT_MODIFIER_H

#include <memory>

#include "ui/base/ace_type.h"
#include "ui/view/draw/modifier.h"

namespace OHOS::Ace::Kit {
class ContentModifierAdapter;
class ACE_FORCE_EXPORT ContentModifier : public Modifier {
    DECLARE_ACE_TYPE(ContentModifier, Modifier);

public:
    ContentModifier();
    ~ContentModifier() override;

    virtual void OnDraw(const DrawingContext& context) = 0;
    void AttachRSProperty(const std::shared_ptr<Rosen::RSPropertyBase>& property) override;

    void InitAdapter();
    const std::shared_ptr<ContentModifierAdapter>& GetRSModifier() const;

private:
    std::shared_ptr<ContentModifierAdapter> modifierAdapter_;
};
} // namespace OHOS::Ace::Kit

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_DRAW_CONTENT_MODIFIER_H
