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

#include "core/components_ng/base/modifier.h"

#include "core/components_ng/base/extension_handler.h"

namespace OHOS::Ace::NG {
Modifier::Modifier()
{
    static std::atomic<int32_t> genId = 0;
    id_ = genId.fetch_add(1, std::memory_order_relaxed);
}

void ContentModifier::Draw(DrawingContext& context)
{
    if (extensionHandler_) {
        extensionHandler_->Draw(context);
    } else {
        onDraw(context);
    }
}

void ContentModifier::SetExtensionHandler(ExtensionHandler* extensionHandler)
{
    extensionHandler_ = extensionHandler;
    extensionHandler_->SetInvalidateRenderImpl([weak = WeakClaim(this)]() {
        auto modifier = weak.Upgrade();
        if (modifier) {
            modifier->SetContentChange();
        }
    });
    extensionHandler_->SetInnerDrawImpl([this](DrawingContext& context) { onDraw(context); });
}

void OverlayModifier::Draw(DrawingContext& context)
{
    if (extensionHandler_) {
        extensionHandler_->OverlayDraw(context);
    } else {
        onDraw(context);
    }
}

void OverlayModifier::SetExtensionHandler(ExtensionHandler* extensionHandler)
{
    extensionHandler_ = extensionHandler;
    extensionHandler_->SetOverlayRenderImpl([weak = WeakClaim(this)]() {
        auto modifier = weak.Upgrade();
        if (modifier) {
            modifier->SetOverlayChange();
        }
    });
    extensionHandler_->SetInnerOverlayDrawImpl([this](DrawingContext& context) { onDraw(context); });
}

void ForegroundModifier::Draw(DrawingContext& context)
{
    if (extensionHandler_) {
        extensionHandler_->ForegroundDraw(context);
    } else {
        onDraw(context);
    }
}

void ForegroundModifier::SetExtensionHandler(ExtensionHandler* extensionHandler)
{
    extensionHandler_ = extensionHandler;
    extensionHandler_->SetForeGroundRenderImpl([weak = WeakClaim(this)]() {
        auto modifier = weak.Upgrade();
        if (modifier) {
            modifier->SetForegroundChange();
        }
    });
    extensionHandler_->SetInnerForegroundDrawImpl([this](DrawingContext& context) { onDraw(context); });
}

} // namespace OHOS::Ace::NG