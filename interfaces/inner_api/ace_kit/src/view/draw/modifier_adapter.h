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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_SRC_VIEW_DRAW_MODIFIER_ADAPTER_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_SRC_VIEW_DRAW_MODIFIER_ADAPTER_H

#include <memory>

#include "render_service_client/core/modifier_ng/custom/rs_content_style_modifier.h"
#include "ui/view/draw/content_modifier.h"

using RSDrawingContext = OHOS::Rosen::ModifierNG::RSDrawingContext;
using RSContentStyleModifier = OHOS::Rosen::ModifierNG::RSContentStyleModifier;

namespace OHOS::Ace::Kit {
class ContentModifierAdapter : public RSContentStyleModifier {
public:
    explicit ContentModifierAdapter(const RefPtr<ContentModifier>& modifier);
    ~ContentModifierAdapter() override;

    void Draw(RSDrawingContext& context) const override;

    void AttachRSProperty(const std::shared_ptr<Rosen::RSPropertyBase>& property);

private:
    WeakPtr<ContentModifier> modifier_;

    ACE_DISALLOW_COPY_AND_MOVE(ContentModifierAdapter);
};
} // namespace OHOS::Ace::Kit
#endif
