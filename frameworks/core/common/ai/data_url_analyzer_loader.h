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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_DATA_URL_ANALYZER_LOADER_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_DATA_URL_ANALYZER_LOADER_H

#include <memory>

#include "interfaces/inner_api/ace/ai/data_url_analyzer.h"
#include "interfaces/inner_api/ace/utils.h"

namespace OHOS::Ace {
using DataUrlAnalyzerInstance = std::unique_ptr<DataUrlAnalyzer, std::function<void (DataUrlAnalyzer*)>>;

class DataUrlAnalyzerLoader : public std::enable_shared_from_this<DataUrlAnalyzerLoader> {
public:
    static std::shared_ptr<DataUrlAnalyzerLoader> Load();
    ~DataUrlAnalyzerLoader();
    DataUrlAnalyzerLoader() = default;

    DataUrlAnalyzerLoader(const DataUrlAnalyzerLoader&) = delete;
    DataUrlAnalyzerLoader(DataUrlAnalyzerLoader&&) = delete;
    DataUrlAnalyzerLoader& operator=(const DataUrlAnalyzerLoader&) = delete;
    DataUrlAnalyzerLoader& operator=(DataUrlAnalyzerLoader&&) = delete;

    DataUrlAnalyzerInstance CreateDataDetector();

private:
    bool Init();
    void Close();

    LIBHANDLE mLibraryHandle_ = nullptr;
    DataUrlAnalyzer* (*mCreateDataUrlAnalyzer_)() = nullptr;
    void (*mDestoryDataUrlAnalyzer_)(DataUrlAnalyzer*) = nullptr;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_DATA_URL_ANALYZER_LOADER_H
