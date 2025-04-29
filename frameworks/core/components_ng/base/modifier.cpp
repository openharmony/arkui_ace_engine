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
    auto extensionHandler = extensionHandler_.Upgrade();
    if (extensionHandler) {
        extensionHandler->Draw(context);
    } else {
        onDraw(context);
    }
}

void ContentModifier::SetExtensionHandler(const RefPtr<ExtensionHandler>& extensionHandler)
{
    extensionHandler->SetInvalidateRenderImpl([weak = WeakClaim(this)]() {
        auto modifier = weak.Upgrade();
        if (modifier) {
            modifier->SetContentChange();
        }
    });
    extensionHandler->SetInnerDrawImpl([weak = WeakClaim(this)](DrawingContext& context) {
        auto modifier = weak.Upgrade();
        if (modifier) {
            modifier->onDraw(context);
        }
    });
    extensionHandler_ = AceType::WeakClaim(AceType::RawPtr(extensionHandler));
}

void OverlayModifier::Draw(DrawingContext& context)
{
    auto extensionHandler = extensionHandler_.Upgrade();
    if (extensionHandler) {
        extensionHandler->OverlayDraw(context);
    } else {
        onDraw(context);
    }
}

void OverlayModifier::SetExtensionHandler(const RefPtr<ExtensionHandler>& extensionHandler)
{
    extensionHandler->SetOverlayRenderImpl([weak = WeakClaim(this)]() {
        auto modifier = weak.Upgrade();
        if (modifier) {
            modifier->SetOverlayChange();
        }
    });
    extensionHandler->SetInnerOverlayDrawImpl([weak = WeakClaim(this)](DrawingContext& context) {
        auto modifier = weak.Upgrade();
        if (modifier) {
            modifier->onDraw(context);
        }
    });
    extensionHandler_ = AceType::WeakClaim(AceType::RawPtr(extensionHandler));
}

void ForegroundModifier::Draw(DrawingContext& context)
{
    auto extensionHandler = extensionHandler_.Upgrade();
    if (extensionHandler) {
        extensionHandler->ForegroundDraw(context);
    } else {
        onDraw(context);
    }
}

void ForegroundModifier::SetExtensionHandler(const RefPtr<ExtensionHandler>& extensionHandler)
{
    extensionHandler->SetForeGroundRenderImpl([weak = WeakClaim(this)]() {
        auto modifier = weak.Upgrade();
        if (modifier) {
            modifier->SetForegroundChange();
        }
    });
    extensionHandler->SetInnerForegroundDrawImpl([weak = WeakClaim(this)](DrawingContext& context) {
        auto modifier = weak.Upgrade();
        if (modifier) {
            modifier->onDraw(context);
        }
    });
    extensionHandler_ = AceType::WeakClaim(AceType::RawPtr(extensionHandler));
}

} // namespace OHOS::Ace::NG
