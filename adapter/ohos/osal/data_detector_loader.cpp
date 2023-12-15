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
#include <dlfcn.h>

#include "base/log/log.h"
#include "base/log/log_wrapper.h"
#include "core/common/ai/data_detector_loader.h"
namespace OHOS::Ace {
// static
std::shared_ptr<DataDetectorLoader> DataDetectorLoader::Load(std::string libPath)
{
    auto engLib(std::make_shared<DataDetectorLoader>());
    return engLib->Init(std::move(libPath)) ? engLib : nullptr;
}

DataDetectorLoader::~DataDetectorLoader()
{
    Close();
}

bool DataDetectorLoader::Init(std::string libPath)
{
    mLibraryHandle_ = dlopen(libPath.c_str(), RTLD_LAZY);
    if (mLibraryHandle_ == nullptr) {
        return false;
    }
    mCreateDataDetectorInstance_ = (DataDetectorInterface* (*)())dlsym(mLibraryHandle_,
        "OHOS_ACE_createDataDetectorInstance");
    mDestoryDataDetectorInstance_ = (void (*)(DataDetectorInterface*))dlsym(
        mLibraryHandle_, "OHOS_ACE_destroyDataDetectorInstance");
    if (mCreateDataDetectorInstance_ == nullptr || mDestoryDataDetectorInstance_ == nullptr) {
        LOGE("Could not find engine interface function in %s", libPath.c_str());
        Close();
        return false;
    }
    return true;
}

DataDetectorInstance DataDetectorLoader::CreateDataDetector()
{
    if (mCreateDataDetectorInstance_ == nullptr || mDestoryDataDetectorInstance_ == nullptr) {
        return DataDetectorInstance();
    }
    return DataDetectorInstance(mCreateDataDetectorInstance_(), [lib = shared_from_this(),
        destroy = mDestoryDataDetectorInstance_](DataDetectorInterface* e) {
            destroy(e);
        });
}

void DataDetectorLoader::Close()
{
    if (mLibraryHandle_ != nullptr) {
        dlclose(mLibraryHandle_);
    }
    mLibraryHandle_ = nullptr;
    mCreateDataDetectorInstance_ = nullptr;
    mDestoryDataDetectorInstance_ = nullptr;
}
} // namespace OHOS::Ace
