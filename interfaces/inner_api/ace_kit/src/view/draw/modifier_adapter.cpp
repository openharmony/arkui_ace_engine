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

#include "interfaces/inner_api/ace_kit/src/view/draw/modifier_adapter.h"

#ifndef MODIFIER_NG
#include "render_service_client/core/modifier/rs_modifier.h"
#endif
#include "ui/base/utils/utils.h"
#include "ui/view/draw/content_modifier.h"
#include "ui/view/draw/modifier.h"

namespace OHOS::Ace::Kit {

ContentModifierAdapter::ContentModifierAdapter(const RefPtr<ContentModifier>& modifier) : modifier_(modifier) {}
ContentModifierAdapter::~ContentModifierAdapter() {}

void ContentModifierAdapter::Draw(RSDrawingContext& context) const
{
    auto modifier = modifier_.Upgrade();
    CHECK_NULL_VOID(modifier);
    DrawingContext drawContext = { .canvas = context.canvas, .width = context.width, .height = context.height };
    modifier->OnDraw(drawContext);
}

void ContentModifierAdapter::AttachRSProperty(const std::shared_ptr<Rosen::RSPropertyBase>& property)
{
    AttachProperty(property);
}
} // namespace OHOS::Ace::Kit
