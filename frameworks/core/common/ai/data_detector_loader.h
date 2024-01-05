/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_DATA_DETECTOR_LOADER_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_DATA_DETECTOR_LOADER_H

#include <memory>
#include "interfaces/inner_api/ace/ai/data_detector_interface.h"
namespace OHOS::Ace {
using DataDetectorInstance = std::unique_ptr<DataDetectorInterface, std::function<void (DataDetectorInterface*)>>;

class DataDetectorLoader : public std::enable_shared_from_this<DataDetectorLoader> {
public:
    static std::shared_ptr<DataDetectorLoader> Load();
    ~DataDetectorLoader();
    DataDetectorLoader() = default;

    DataDetectorLoader(const DataDetectorLoader&) = delete;
    DataDetectorLoader(DataDetectorLoader&&) = delete;
    DataDetectorLoader& operator=(const DataDetectorLoader&) = delete;
    DataDetectorLoader& operator=(DataDetectorLoader&&) = delete;

    DataDetectorInstance CreateDataDetector();

private:
    bool Init();
    void Close();

    void *mLibraryHandle_ = nullptr;
    DataDetectorInterface* (*mCreateDataDetectorInstance_)() = nullptr;
    void (*mDestoryDataDetectorInstance_)(DataDetectorInterface*) = nullptr;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_DATA_DETECTOR_LOADER_H
