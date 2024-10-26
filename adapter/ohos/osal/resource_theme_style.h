/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_RESOURCE_THEME_STYLE_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_RESOURCE_THEME_STYLE_H

#include <map>
#include <future>
#include <mutex>
#include <shared_mutex>

#include "core/components/theme/theme_style.h"
#include "core/components/theme/resource_adapter.h"

namespace OHOS::Ace {
class ResourceThemeStyle : public ThemeStyle {
    DECLARE_ACE_TYPE(ResourceThemeStyle, ThemeStyle);

public:
    friend class ResourceAdapterImpl;
    friend class ResourceAdapterImplV2;
    using RawAttrMap = std::map<std::string, std::string>;
    using RawPatternMap = std::map<std::string, RawAttrMap>;

    explicit ResourceThemeStyle(RefPtr<ResourceAdapter> resAdapter) : resAdapter_(resAdapter) {};
    ~ResourceThemeStyle() override = default;

    void ParseContent() override;
    void CheckThemeStyleLoaded(const std::string& patternName) override;
    void SetPromiseValue()
    {
        promise_.set_value();
    }
    void PushBackCheckThemeStyleVector(const std::string& patternName)
    {
        std::unique_lock<std::shared_mutex> lock(checkThemeStyleVectorMutex_);
        checkThemeStyleVector_.push_back(patternName);
    }
    bool CheckThemeStyle(const std::string& patternName)
    {
        std::shared_lock<std::shared_mutex> lock(checkThemeStyleVectorMutex_);
        auto it = std::find(checkThemeStyleVector_.begin(), checkThemeStyleVector_.end(), patternName.c_str());
        if (it == checkThemeStyleVector_.end()) {
            return false;
        }
        return true;
    }
protected:
    void OnParseStyle();
    void OnParseResourceMedia(const std::string& attrName, const std::string& attrValue);

private:
    RawAttrMap rawAttrs_; // key and value read from global resource api.
    RawPatternMap patternAttrs_;
    RefPtr<ResourceAdapter> resAdapter_;
    std::promise<void> promise_;
    std::shared_future<void> future_ = promise_.get_future();
    std::vector<std::string> checkThemeStyleVector_; // theme pattern name list for checking the preloaded theme style
    std::shared_mutex checkThemeStyleVectorMutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_RESOURCE_THEME_STYLE_H
