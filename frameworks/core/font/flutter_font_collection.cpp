/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/font/flutter_font_collection.h"

#include "flutter/lib/ui/ui_dart_state.h"

#include "base/log/log.h"

namespace OHOS::Ace {

FlutterFontCollection FlutterFontCollection::instance;

std::shared_ptr<txt::FontCollection> FlutterFontCollection::GetFontCollection()
{
    if (!isUseFlutterEngine) {
        if (!isCompleted_) {
            isCompleted_ = future_.get();
        }
        return fontCollection_->GetFontCollection();
    }

    auto* windowClient = GetFlutterEngineWindowClient();
    if (!windowClient) {
        return nullptr;
    }
    auto& fontCollection = windowClient->GetFontCollection();
    return fontCollection.GetFontCollection();
}

flutter::WindowClient* FlutterFontCollection::GetFlutterEngineWindowClient()
{
    if (!flutter::UIDartState::Current()) {
        LOGE("uiDartState is null");
        return nullptr;
    }

    auto* window = flutter::UIDartState::Current()->window();
    if (window == nullptr) {
        LOGW("UpdateParagraph: window or client is null");
        return nullptr;
    }
    return window->client();
}

void FlutterFontCollection::LoadFontFromList(const uint8_t* font_data, size_t length, std::string family_name)
{
    if (!isUseFlutterEngine) {
        if (!isCompleted_) {
            isCompleted_ = future_.get();
        }
        fontCollection_->LoadFontFromList(font_data, length, family_name);
        return;
    }

    auto* windowClient = GetFlutterEngineWindowClient();
    if (!windowClient) {
        return;
    }
    auto& fontCollection = windowClient->GetFontCollection();
    fontCollection.LoadFontFromList(font_data, length, family_name);
}

void FlutterFontCollection::CreateFontCollection(fml::RefPtr<fml::TaskRunner>& ioTaskRunner)
{
    if (isInit_ || !ioTaskRunner) {
        return;
    }
    isInit_ = true;
    isUseFlutterEngine = false;

    ioTaskRunner->PostTask([&fontCollection = fontCollection_, &promise = promise_]() mutable {
        fontCollection = std::make_unique<flutter::FontCollection>();
        if (fontCollection->GetFontCollection()) {
            std::string emptyLocale;
            // 0x4e2d is unicode for '中'.
            fontCollection->GetFontCollection()->MatchFallbackFont(0x4e2d, emptyLocale);
            fontCollection->GetFontCollection()->GetMinikinFontCollectionForFamilies({ "sans-serif" }, emptyLocale);
        }
        promise.set_value(true);
    });
}

FlutterFontCollection& FlutterFontCollection::GetInstance()
{
    return instance;
}

} // namespace OHOS::Ace