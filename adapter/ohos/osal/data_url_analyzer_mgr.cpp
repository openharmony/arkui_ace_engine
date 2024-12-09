/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#include "core/common/ai/data_url_analyzer_mgr.h"

#include "core/common/ai/data_url_analyzer_default.h"

namespace OHOS::Ace {

DataUrlAnalyzerMgr& DataUrlAnalyzerMgr::GetInstance()
{
    static DataUrlAnalyzerMgr instance;
    return instance;
}

DataUrlAnalyzerMgr::DataUrlAnalyzerMgr()
{
    auto lib = DataUrlAnalyzerLoader::Load();
    if (lib == nullptr || (engine_ = lib->CreateDataDetector()) == nullptr) {
        engine_ = DataUrlAnalyzerInstance(new DataUrlAnalyzerDefault, [](DataUrlAnalyzer* e) {
            auto* p = reinterpret_cast<DataUrlAnalyzerDefault*>(e);
            delete p;
        });
    }
}

std::vector<UrlEntity> DataUrlAnalyzerMgr::AnalyzeUrls(const std::string &text)
{
    if (engine_) {
        return engine_->AnalyzeUrls(text);
    }
    std::vector<UrlEntity> data;
    return data;
}
} // namespace OHOS::Ace
