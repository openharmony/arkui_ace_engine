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

#include "core/components_ng/pattern/select/select_pattern.h"

namespace OHOS::Ace::NG {

void SelectPattern::OnAttachToFrameNodeMultiThread()
{
    // nothing, thread unsafe
}

void SelectPattern::OnAttachToMainTreeMultiThread()
{
    RegisterOnKeyEvent();
    RegisterOnClick();
    RegisterOnPress();
    RegisterOnHover();
}

void SelectPattern::ResetParamsMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = WeakClaim(this)]() {
        auto select = weak.Upgrade();
        CHECK_NULL_VOID(select);
        select->ResetParams();
    });
}

void SelectPattern::ResetOptionPropsMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = WeakClaim(this)]() {
        auto select = weak.Upgrade();
        CHECK_NULL_VOID(select);
        select->ResetOptionProps();
    });
}

void SelectPattern::SetFontSizeMultiThread(const Dimension& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = WeakClaim(this), value]() {
        auto select = weak.Upgrade();
        CHECK_NULL_VOID(select);
        auto props = select->text_->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(props);
        props->UpdateFontSize(value);
    });
}

void SelectPattern::SetFontColorMultiThread(const Color& color)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = WeakClaim(this), color]() {
        auto select = weak.Upgrade();
        CHECK_NULL_VOID(select);
        select->SetFontColorImpl(color);
    });
}

void SelectPattern::SetFontWeightMultiThread(const FontWeight& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = WeakClaim(this), value]() {
        auto select = weak.Upgrade();
        CHECK_NULL_VOID(select);
        select->SetFontWeightImpl(value);
    });
}

void SelectPattern::SetOptionFontSizeMultiThread(const Dimension& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = WeakClaim(this), value]() {
        auto select = weak.Upgrade();
        CHECK_NULL_VOID(select);
        select->SetOptionFontSizeImpl(value);
    });
}

void SelectPattern::SetFontFamilyMultiThread(const std::vector<std::string>& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = WeakClaim(this), value]() {
        auto select = weak.Upgrade();
        CHECK_NULL_VOID(select);
        select->SetFontFamilyImpl(value);
    });
}

void SelectPattern::SetItalicFontStyleMultiThread(const Ace::FontStyle& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = WeakClaim(this), value]() {
        auto select = weak.Upgrade();
        CHECK_NULL_VOID(select);
        select->SetItalicFontStyle(value);
    });
}

void SelectPattern::ResetFontColorMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = WeakClaim(this)]() {
        auto select = weak.Upgrade();
        CHECK_NULL_VOID(select);
        select->ResetFontColor();
    });
}
 
void SelectPattern::SetValueMultiThread(const std::string& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->PostAfterAttachMainTreeTask([weak = WeakClaim(this), value]() {
        auto select = weak.Upgrade();
        CHECK_NULL_VOID(select);
        select->SetValueImpl(value);
    });
}
} // namespace OHOS::Ace::NG