/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/components/font/rosen_font_collection.h"

#include "txt/src/minikin/FontFamily.h"
#include "txt/src/minikin/FontLanguageListCache.h"
#include "include/core/SkTypeface.h"
#include "base/i18n/localization.h"
#include "base/log/ace_trace.h"
#include "base/log/log.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"

namespace OHOS::Ace {

RosenFontCollection RosenFontCollection::instance;

std::shared_ptr<txt::FontCollection> RosenFontCollection::GetFontCollection()
{
    std::call_once(fontFlag_, [this]() {
        fontCollection_ = std::make_shared<txt::FontCollection>();
        fontCollection_->SetupDefaultFontManager();
        dynamicFontManager_ = sk_make_sp<txt::DynamicFontManager>();
        fontCollection_->SetDynamicFontManager(dynamicFontManager_);
    });
    return fontCollection_;
}

sk_sp<txt::DynamicFontManager> RosenFontCollection::GetDynamicFontManager()
{
    return dynamicFontManager_;
}

void RosenFontCollection::LoadFontFromList(const uint8_t* fontData, size_t length, std::string familyName)
{
    std::call_once(fontFlag_, [this]() {
        fontCollection_ = std::make_shared<txt::FontCollection>();
        fontCollection_->SetupDefaultFontManager();
        dynamicFontManager_ = sk_make_sp<txt::DynamicFontManager>();
        fontCollection_->SetDynamicFontManager(dynamicFontManager_);
    });
    
    auto it = std::find(families_.begin(), families_.end(), familyName);
    if (it != families_.end()) {
        return;
    }

    families_.emplace_back(familyName);

    if (fontCollection_) {
        std::unique_ptr<SkStreamAsset> font_stream = std::make_unique<SkMemoryStream>(fontData, length, true);
        sk_sp<SkTypeface> typeface = SkTypeface::MakeFromStream(std::move(font_stream));
        txt::TypefaceFontAssetProvider& font_provider = dynamicFontManager_->font_provider();
        if (familyName.empty()) {
            font_provider.RegisterTypeface(typeface);
        } else {
            font_provider.RegisterTypeface(typeface, familyName);
        }
        fontCollection_->ClearFontFamilyCache();
    }
}

RosenFontCollection& RosenFontCollection::GetInstance()
{
    return instance;
}

void RosenFontCollection::VaryFontCollectionWithFontWeightScale(float fontWeightScale)
{
    if (LessOrEqual(fontWeightScale, 0.0)) {
        return;
    }

    if (fontCollection_) {
        fontCollection_->VaryFontCollectionWithFontWeightScale(fontWeightScale);
    }
}

void RosenFontCollection::LoadSystemFont()
{
    ACE_FUNCTION_TRACE();

    if (fontCollection_) {
        fontCollection_->LoadSystemFont();
    }
}

void RosenFontCollection::SetIsZawgyiMyanmar(bool isZawgyiMyanmar)
{
    ACE_FUNCTION_TRACE();

    if (isZawgyiMyanmar_ == isZawgyiMyanmar) {
        return;
    }
    isZawgyiMyanmar_ = isZawgyiMyanmar;

    if (fontCollection_) {
        fontCollection_->SetIsZawgyiMyanmar(isZawgyiMyanmar);
    }

    AceEngine::Get().NotifyContainers([](const RefPtr<Container>& container) {
        if (container) {
            container->NotifyFontNodes();
        }
    });
}

} // namespace OHOS::Ace
