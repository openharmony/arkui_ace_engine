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
#include <dlfcn.h>

#include "base/log/log_wrapper.h"
#include "core/common/ai/data_url_analyzer_loader.h"
namespace OHOS::Ace {
namespace {
#ifdef __aarch64__
constexpr char AI_ADAPTER_SO_PATH[] = "system/lib64/libai_nlu_innerapi.z.so";
#else
constexpr char AI_ADAPTER_SO_PATH[] = "system/lib/libai_nlu_innerapi.z.so";
#endif
} // namespace

// static
std::shared_ptr<DataUrlAnalyzerLoader> DataUrlAnalyzerLoader::Load()
{
    auto engLib(std::make_shared<DataUrlAnalyzerLoader>());
    return engLib->Init() ? engLib : nullptr;
}

DataUrlAnalyzerLoader::~DataUrlAnalyzerLoader()
{
    Close();
}

bool DataUrlAnalyzerLoader::Init()
{
    mLibraryHandle_ = LOADLIB(AI_ADAPTER_SO_PATH);
    if (mLibraryHandle_ == nullptr) {
        return false;
    }
    mCreateDataUrlAnalyzer_ = (DataUrlAnalyzer* (*)())dlsym(mLibraryHandle_,
        "OHOS_ACE_createDataUrlAnalyzerInstance");
    mDestoryDataUrlAnalyzer_ = (void (*)(DataUrlAnalyzer*))dlsym(
        mLibraryHandle_, "OHOS_ACE_destroyDataUrlAnalyzerInstance");
    if (mCreateDataUrlAnalyzer_ == nullptr || mDestoryDataUrlAnalyzer_ == nullptr) {
        LOGE("Could not find engine interface function in %s", AI_ADAPTER_SO_PATH);
        Close();
        return false;
    }
    return true;
}

DataUrlAnalyzerInstance DataUrlAnalyzerLoader::CreateDataDetector()
{
    if (mCreateDataUrlAnalyzer_ == nullptr || mDestoryDataUrlAnalyzer_ == nullptr) {
        return DataUrlAnalyzerInstance();
    }
    return DataUrlAnalyzerInstance(mCreateDataUrlAnalyzer_(), [lib = shared_from_this(),
        destroy = mDestoryDataUrlAnalyzer_](DataUrlAnalyzer* e) {
            destroy(e);
        });
}

void DataUrlAnalyzerLoader::Close()
{
    if (mLibraryHandle_ != nullptr) {
        FREELIB(mLibraryHandle_);
    }
    mLibraryHandle_ = nullptr;
    mCreateDataUrlAnalyzer_ = nullptr;
    mDestoryDataUrlAnalyzer_ = nullptr;
}
} // namespace OHOS::Ace
