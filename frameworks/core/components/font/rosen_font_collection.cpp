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

#ifndef USE_GRAPHIC_TEXT_GINE
#include "txt/src/minikin/FontFamily.h"
#include "txt/src/minikin/FontLanguageListCache.h"
#else
#include "core/components_ng/render/adapter/txt_font_collection.h"
#include "rosen_text/font_collection.h"
#endif
#ifndef USE_ROSEN_DRAWING
#include "include/core/SkTypeface.h"
#endif
#include "core/common/ace_engine.h"

namespace OHOS::Ace {

RosenFontCollection RosenFontCollection::instance;

#ifndef USE_GRAPHIC_TEXT_GINE
std::shared_ptr<txt::FontCollection> RosenFontCollection::GetFontCollection()
{
    std::call_once(fontFlag_, [this]() {
        auto rosenCollection = RSFontCollection::GetInstance(false);
        auto collectionTxtBase = rosenCollection->GetFontCollection();
        auto collectionTxt = std::static_pointer_cast<rosen::FontCollectionTxt>(collectionTxtBase);
        if (collectionTxt) {
            fontCollection_ = collectionTxt->GetFontCollection();
            dynamicFontManager_ = collectionTxt->GetDynamicFontManager();
        } else {
            TAG_LOGW(AceLogTag::ACE_FONT, "Fail to get font Follection!");
        }
    });
    return fontCollection_;
}

#ifndef USE_ROSEN_DRAWING
sk_sp<txt::DynamicFontManager> RosenFontCollection::GetDynamicFontManager()
#else
std::shared_ptr<RSFontMgr> RosenFontCollection::GetDynamicFontManager()
#endif
{
    return dynamicFontManager_;
}
#else
std::shared_ptr<Rosen::FontCollection> RosenFontCollection::GetFontCollection()
{
    std::call_once(fontFlag_, [this]() {
        auto fontCollection = AceType::DynamicCast<NG::TxtFontCollection>(NG::FontCollection::Current());
        fontCollection_ = fontCollection->GetRawFontCollection();
    });
    return fontCollection_;
}
#endif

void RosenFontCollection::LoadFontFromList(const uint8_t* fontData, size_t length, std::string familyName)
{
    std::call_once(fontFlag_, [this]() {
#ifndef USE_GRAPHIC_TEXT_GINE
        auto rosenCollection = RSFontCollection::GetInstance(false);
        auto collectionTxtBase = rosenCollection->GetFontCollection();
        auto collectionTxt = std::static_pointer_cast<rosen::FontCollectionTxt>(collectionTxtBase);
        if (collectionTxt) {
            fontCollection_ = collectionTxt->GetFontCollection();
            dynamicFontManager_ = collectionTxt->GetDynamicFontManager();
        }
#else
        auto fontCollection = AceType::DynamicCast<NG::TxtFontCollection>(NG::FontCollection::Current());
        fontCollection_ = fontCollection->GetRawFontCollection();
#endif
    });

    if (families_.find(familyName) != families_.end()) {
        return;
    }

    families_.emplace(familyName);

    if (fontCollection_) {
#ifndef USE_GRAPHIC_TEXT_GINE
#ifndef USE_ROSEN_DRAWING
        std::unique_ptr<SkStreamAsset> font_stream = std::make_unique<SkMemoryStream>(fontData, length, true);
        sk_sp<SkTypeface> typeface = SkTypeface::MakeFromStream(std::move(font_stream));
        txt::TypefaceFontAssetProvider& font_provider = dynamicFontManager_->font_provider();
        if (familyName.empty()) {
            font_provider.RegisterTypeface(typeface);
        } else {
            font_provider.RegisterTypeface(typeface, familyName);
        }
        fontCollection_->ClearFontFamilyCache();
#else
        TAG_LOGW(AceLogTag::ACE_FONT, "Drawing is not supported dynamic font");
#endif
#else
        TAG_LOGI(AceLogTag::ACE_FONT, "LoadFontFromList familyName:%{public}s, length:%{public}d", familyName.c_str(),
            static_cast<int32_t>(length));
        fontCollection_->LoadFont(familyName, fontData, length);
#endif
    }
}

void RosenFontCollection::InitializeFontCollection()
{
    std::call_once(fontFlag_, [this]() {
#ifndef USE_GRAPHIC_TEXT_GINE
    auto rosenCollection = RSFontCollection::GetInstance(false);
    auto collectionTxtBase = rosenCollection->GetFontCollection();
    auto collectionTxt = std::static_pointer_cast<rosen::FontCollectionTxt>(collectionTxtBase);
    if (collectionTxt) {
        fontCollection_ = collectionTxt->GetFontCollection();
        dynamicFontManager_ = collectionTxt->GetDynamicFontManager();
    }
#else
    auto fontCollection = AceType::DynamicCast<NG::TxtFontCollection>(NG::FontCollection::Current());
    fontCollection_ = fontCollection->GetRawFontCollection();
#endif
    });
}

void RosenFontCollection::LoadThemeFont(const char* fontFamily, std::unique_ptr<char[]> buffer, size_t size)
{
    const std::string familyName = fontFamily;
    const uint8_t* data = reinterpret_cast<uint8_t*>(buffer.get());
    if (fontCollection_) {
#ifndef USE_GRAPHIC_TEXT_GINE
#ifndef USE_ROSEN_DRAWING
        std::unique_ptr<SkStreamAsset> font_stream = std::make_unique<SkMemoryStream>(data, size, true);
        sk_sp<SkTypeface> typeface = SkTypeface::MakeFromStream(std::move(font_stream));
        txt::TypefaceFontAssetProvider& font_provider = dynamicFontManager_->font_provider();
        if (familyName.empty()) {
            font_provider.RegisterTypeface(typeface);
        } else {
            font_provider.RegisterTypeface(typeface, familyName);
        }
        fontCollection_->ClearFontFamilyCache();
#else
        TAG_LOGW(AceLogTag::ACE_FONT, "Drawing is not supported");
#endif
#else
        fontCollection_->LoadThemeFont("", nullptr, 0);
        TAG_LOGI(AceLogTag::ACE_FONT, "LoadThemeFont [%{public}s:%{public}d]", familyName.c_str(),
            static_cast<int32_t>(size));
        fontCollection_->LoadThemeFont(familyName, data, size);
#endif
    }
}

void RosenFontCollection::LoadFontFamily(const char* fontFamily, const char* familySrc)
{
    const std::string path = familySrc;
    if (currentFamily_ == path) {
        TAG_LOGI(AceLogTag::ACE_FONT, "This font has already been registered.");
        return;
    }
    InitializeFontCollection();
    auto ret = StdFilesystemExists(path);
    if (!ret) {
        TAG_LOGW(AceLogTag::ACE_FONT, "FontFamily %{public}s not exist", path.c_str());
        return;
    }

    std::ifstream ifs(path, std::ios_base::in);
    if (!ifs.is_open()) {
        TAG_LOGW(AceLogTag::ACE_FONT, "FontFamily file open fail, %{public}s", path.c_str());
        return;
    }
    ifs.seekg(0, ifs.end);
    if (!ifs.good()) {
        ifs.close();
        TAG_LOGW(AceLogTag::ACE_FONT, "font file is bad");
        return;
    }
    auto size = ifs.tellg();
    if (ifs.fail()) {
        ifs.close();
        TAG_LOGW(AceLogTag::ACE_FONT, "get size failed");
        return;
    }
    ifs.seekg(ifs.beg);
    if (!ifs.good()) {
        ifs.close();
        TAG_LOGW(AceLogTag::ACE_FONT, "file seek failed");
        return;
    }
    std::unique_ptr<char[]> buffer = std::make_unique<char[]>(size);
    ifs.read(buffer.get(), size);
    if (!ifs.good()) {
        ifs.close();
        TAG_LOGW(AceLogTag::ACE_FONT, "read file failed");
        return;
    }
    ifs.close();
    currentFamily_ = path;
    LoadThemeFont(fontFamily, std::move(buffer), size);
}

bool RosenFontCollection::StdFilesystemExists(const std::string &path)
{
    std::ifstream f(path.c_str());
    return f.good();
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

#ifndef USE_GRAPHIC_TEXT_GINE
    if (fontCollection_) {
        fontCollection_->VaryFontCollectionWithFontWeightScale(fontWeightScale);
    }
#endif
}

void RosenFontCollection::LoadSystemFont()
{
    ACE_FUNCTION_TRACE();

#ifndef USE_GRAPHIC_TEXT_GINE
    if (fontCollection_) {
        fontCollection_->LoadSystemFont();
    }
#endif
}

void RosenFontCollection::SetIsZawgyiMyanmar(bool isZawgyiMyanmar)
{
    ACE_FUNCTION_TRACE();

    if (isZawgyiMyanmar_ == isZawgyiMyanmar) {
        return;
    }
    isZawgyiMyanmar_ = isZawgyiMyanmar;

#ifndef USE_GRAPHIC_TEXT_GINE
    if (fontCollection_) {
        fontCollection_->SetIsZawgyiMyanmar(isZawgyiMyanmar);
    }
#endif

    AceEngine::Get().NotifyContainers([](const RefPtr<Container>& container) {
        if (container) {
            container->NotifyFontNodes();
        }
    });
}

} // namespace OHOS::Ace
