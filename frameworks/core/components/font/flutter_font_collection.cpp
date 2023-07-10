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

#include "core/components/font/flutter_font_collection.h"

#include "txt/src/minikin/FontFamily.h"
#include "txt/src/minikin/FontLanguageListCache.h"

#include "base/i18n/localization.h"
#include "base/log/ace_trace.h"
#include "base/log/log.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "rosen_text/font_collection.h"

namespace OHOS::Ace {

FlutterFontCollection FlutterFontCollection::instance;

std::shared_ptr<Rosen::FontCollection> FlutterFontCollection::GetFontCollection()
{
    if (!isUseFlutterEngine) {
        if (!isCompleted_) {
            isCompleted_ = future_.get();
        }
        return Rosen::FontCollection::From(fontCollection_->GetFontCollection());
    }
    std::call_once(fontFlag_, [this]() {
        fontCollection_ = std::make_unique<flutter::FontCollection>();
        if (fontCollection_->GetFontCollection()) {
            std::string emptyLocale;
            // 0x4e2d is unicode for '中'.
            fontCollection_->GetFontCollection()->MatchFallbackFont(0x4e2d, emptyLocale);
            fontCollection_->GetFontCollection()->GetMinikinFontCollectionForFamilies({ "sans-serif" }, emptyLocale);
        }
    });
    return Rosen::FontCollection::From(fontCollection_->GetFontCollection());
}

void FlutterFontCollection::LoadFontFromList(const uint8_t* fontData, size_t length, std::string familyName)
{
    auto it = std::find(families_.begin(), families_.end(), familyName);
    if (it != families_.end()) {
        return;
    }

    families_.emplace_back(familyName);

    if (!isUseFlutterEngine) {
        if (!isCompleted_) {
            isCompleted_ = future_.get();
        }
        fontCollection_->LoadFontFromList(fontData, length, familyName);
        return;
    }

    if (fontCollection_) {
        fontCollection_->LoadFontFromList(fontData, length, familyName);
    }
}

void FlutterFontCollection::CreateFontCollection(const fml::RefPtr<fml::TaskRunner>& ioTaskRunner)
{
    Localization::GetInstance()->SetOnMymrChange([ioTaskRunner](bool isZawgyiMyanmar) {
        if (ioTaskRunner) {
            ioTaskRunner->PostTask(
                [isZawgyiMyanmar]() { FlutterFontCollection::GetInstance().SetIsZawgyiMyanmar(isZawgyiMyanmar); });
        }
    });

    if (isInit_ || !ioTaskRunner) {
        return;
    }
    isInit_ = true;
    isUseFlutterEngine = false;

    ioTaskRunner->PostTask([&fontCollection = fontCollection_, &promise = promise_]() mutable {
        fontCollection = std::make_unique<flutter::FontCollection>();
        if (fontCollection->GetFontCollection()) {
            // Initialize weight scale
            float fontWeightScale = SystemProperties::GetFontWeightScale();
            if (GreatNotEqual(fontWeightScale, 0.0)) {
                fontCollection->GetFontCollection()->VaryFontCollectionWithFontWeightScale(fontWeightScale);
            }

            auto locale = Localization::GetInstance()->GetFontLocale();
            uint32_t langListId = locale.empty() ? minikin::FontLanguageListCache::kEmptyListId
                                                 : minikin::FontStyle::registerLanguageList(locale);
            const minikin::FontLanguages& langs = minikin::FontLanguageListCache::getById(langListId);
            locale = langs.size() ? langs[0].getString() : "";
            // 0x4e2d is unicode for '中'.
            fontCollection->GetFontCollection()->MatchFallbackFont(0x4e2d, locale);
            fontCollection->GetFontCollection()->GetMinikinFontCollectionForFamilies({ "sans-serif" }, locale);
        }
        promise.set_value(true);
    });
}

FlutterFontCollection& FlutterFontCollection::GetInstance()
{
    return instance;
}

void FlutterFontCollection::VaryFontCollectionWithFontWeightScale(float fontWeightScale)
{
    if (LessOrEqual(fontWeightScale, 0.0)) {
        return;
    }

    if (!isUseFlutterEngine) {
        if (!isCompleted_) {
            return;
        }
        if (fontCollection_ && fontCollection_->GetFontCollection()) {
            fontCollection_->GetFontCollection()->VaryFontCollectionWithFontWeightScale(fontWeightScale);
        }
        return;
    }

    if (fontCollection_ && fontCollection_->GetFontCollection()) {
        fontCollection_->GetFontCollection()->VaryFontCollectionWithFontWeightScale(fontWeightScale);
    }
}

void FlutterFontCollection::LoadSystemFont()
{
    ACE_FUNCTION_TRACE();
    if (!isUseFlutterEngine) {
        if (!isCompleted_) {
            return;
        }
        if (fontCollection_ && fontCollection_->GetFontCollection()) {
            fontCollection_->GetFontCollection()->LoadSystemFont();
        }
        return;
    }

    if (fontCollection_ && fontCollection_->GetFontCollection()) {
        fontCollection_->GetFontCollection()->LoadSystemFont();
    }
}

void FlutterFontCollection::SetIsZawgyiMyanmar(bool isZawgyiMyanmar)
{
    ACE_FUNCTION_TRACE();

    if (isZawgyiMyanmar_ == isZawgyiMyanmar) {
        return;
    }
    isZawgyiMyanmar_ = isZawgyiMyanmar;

    if (!isUseFlutterEngine) {
        if (!isCompleted_) {
            isCompleted_ = future_.get();
        }
        if (fontCollection_ && fontCollection_->GetFontCollection()) {
            fontCollection_->GetFontCollection()->SetIsZawgyiMyanmar(isZawgyiMyanmar);
        }
        return;
    }

    if (fontCollection_ && fontCollection_->GetFontCollection()) {
        fontCollection_->GetFontCollection()->SetIsZawgyiMyanmar(isZawgyiMyanmar);
    }

    AceEngine::Get().NotifyContainers([](const RefPtr<Container>& container) {
        if (container) {
            container->NotifyFontNodes();
        }
    });
}

void FlutterFontCollection::UnloadFont()
{
    families_.clear();
}

} // namespace OHOS::Ace
