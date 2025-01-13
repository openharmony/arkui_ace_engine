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
#ifndef USE_GRAPHIC_TEXT_GINE
    auto rosenCollection = RSFontCollection::GetInstance(false);
    CHECK_NULL_VOID(rosenCollection);
    auto collectionTxtBase = rosenCollection->GetFontCollection();
    auto collectionTxt = std::static_pointer_cast<rosen::FontCollectionTxt>(collectionTxtBase);
    if (collectionTxt) {
        collection_ = collectionTxt->GetFontCollection();
    } else {
        LOGE("Fail to get FontFollectionTxt!");
    }
    if (collection_) {
        std::string emptyLocale;
        // 0x4e2d is unicode for '中'.
        collection_->MatchFallbackFont(0x4e2d, emptyLocale);
        collection_->GetMinikinFontCollectionForFamilies({ "sans-serif" }, emptyLocale);
    }
#else
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
#endif
}

#ifndef USE_GRAPHIC_TEXT_GINE
TxtFontCollection::TxtFontCollection(const std::shared_ptr<txt::FontCollection>& fontCollection)
    : collection_(fontCollection)
{}
#else
TxtFontCollection::TxtFontCollection(const std::shared_ptr<Rosen::FontCollection>& fontCollection)
    : collection_(fontCollection)
{}
#endif
} // namespace OHOS::Ace::NG
