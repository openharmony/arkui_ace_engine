/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/adapter/txt_font_collection.h"

namespace OHOS::Ace::NG {
namespace {
void OnLoadFontFinished(const Rosen::FontCollection* collection, const std::string& name)
{
    auto txtFontCollection = AceType::DynamicCast<TxtFontCollection>(FontCollection::Current());
    if (!txtFontCollection || txtFontCollection->GetRawFontCollection().get() != collection) {
        return;
    }
    auto loadFinishCallback = FontCollection::Current()->GetLoadFontFinishCallback();
    for (const auto& callback : loadFinishCallback) {
        if (callback) {
            callback(name);
        }
    }
}

void OnUnLoadFontFinished(const Rosen::FontCollection* collection, const std::string& name)
{
    auto txtFontCollection = AceType::DynamicCast<TxtFontCollection>(FontCollection::Current());
    if (!txtFontCollection || txtFontCollection->GetRawFontCollection().get() != collection) {
        return;
    }
    auto unLoadFinishCallback = FontCollection::Current()->GetUnloadFontFinishCallback();
    for (const auto& callback : unLoadFinishCallback) {
        if (callback) {
            callback(name);
        }
    }
}
}

RefPtr<FontCollection> TxtFontCollection::GetInstance()
{
    static RefPtr<TxtFontCollection> instance = AceType::MakeRefPtr<TxtFontCollection>();
    return instance;
}

RefPtr<FontCollection> FontCollection::Current()
{
    return TxtFontCollection::GetInstance();
}

TxtFontCollection::TxtFontCollection()
{
    collection_ = Rosen::FontCollection::Create();
    /* texgine not support
    dynamicFontManager_ = RosenFontCollection::GetInstance().GetDynamicFontManager();
    if (collection_) {
        std::string emptyLocale;
        // 0x4e2d is unicode for '中'.
        collection_->MatchFallbackFont(0x4e2d, emptyLocale);
        collection_->GetMinikinFontCollectionForFamilies({ "sans-serif" }, emptyLocale);
    }
    */
    Rosen::FontCollection::RegisterLoadFontFinishCallback(OnLoadFontFinished);
    Rosen::FontCollection::RegisterUnloadFontFinishCallback(OnUnLoadFontFinished);
}

TxtFontCollection::TxtFontCollection(const std::shared_ptr<Rosen::FontCollection>& fontCollection)
    : collection_(fontCollection)
{}
} // namespace OHOS::Ace::NG
