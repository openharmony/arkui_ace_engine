/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "display_sync_impl.h"

#include <cstring>
#include "cj_lambda.h"
#include "display_sync_error.h"
#include "ffi_remote_data.h"
#include "securec.h"

using namespace OHOS::DisplaySync;
using namespace OHOS::FFI;

namespace OHOS::DisplaySync {
void DisplaySync::RegisterOnFrameCallback(void (*callback)(CIntervalInfo))
{
    callbackRef_ = callback;
    auto callbackCJ = CJLambda::Create(callback);
    uiDisplaySync_->RegisterOnFrameWithData([&callbackCJ] (Ace::RefPtr<Ace::DisplaySyncData> displaySyncData) {
        CIntervalInfo intervalInfo;
        intervalInfo.timestamp = displaySyncData->timestamp_;
        intervalInfo.targetTimestamp = displaySyncData->targetTimestamp_;
        callbackCJ(intervalInfo);
    });
}

void DisplaySync::UnregisterOnFrameCallback(void (*callback)(CIntervalInfo))
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (callbackRef_ == nullptr) {
        return;
    }
    callbackRef_ = nullptr;
    uiDisplaySync_->UnregisterOnFrame();
}

DisplaySyncImpl::DisplaySyncImpl()
{
    auto uiDisplaySync = Ace::AceType::MakeRefPtr<Ace::UIDisplaySync>();
    displaySync_ = std::make_shared<DisplaySync>(uiDisplaySync);
    if (displaySync_ == nullptr) {
        return;
    }
}

int32_t DisplaySyncImpl::SetExpectedFrameRateRange(CFrameRateRange cRateRange)
{
    const auto uiDisplaySync = displaySync_->GetUIDisplaySync();
    if (!uiDisplaySync) {
        return ERR_CJ_INNER_EXCEPTION;
    }

    Ace::FrameRateRange rateRange(cRateRange.min, cRateRange.max, cRateRange.expected);
    if (!rateRange.IsValid()) {
        return ERR_CJ_PARAMETER_ERROR;
    }
    uiDisplaySync->SetExpectedFrameRateRange(rateRange);
    return ERR_CJ_SUCCESS;
}

int32_t DisplaySyncImpl::On(char* type, void (*callback)(CIntervalInfo))
{
    if (strcmp(type, "frame") != 0) {
        return ERR_CJ_PARAMETER_ERROR;
    }
    displaySync_->RegisterOnFrameCallback(callback);
    return ERR_CJ_SUCCESS;
}

int32_t DisplaySyncImpl::Off(char* type, void (*callback)(CIntervalInfo))
{
    if (strcmp(type, "frame") != 0) {
        return ERR_CJ_PARAMETER_ERROR;
    }
    displaySync_->UnregisterOnFrameCallback(callback);
    return ERR_CJ_SUCCESS;
}

int32_t DisplaySyncImpl::Start()
{
    const auto uiDisplaySync = displaySync_->GetUIDisplaySync();
    if (!uiDisplaySync) {
        return ERR_CJ_INNER_EXCEPTION;
    }
    uiDisplaySync->AddToPipelineOnContainer();
    return ERR_CJ_SUCCESS;
}

int32_t DisplaySyncImpl::Stop()
{
    const auto uiDisplaySync = displaySync_->GetUIDisplaySync();
    if (!uiDisplaySync) {
        return ERR_CJ_INNER_EXCEPTION;
    }
    uiDisplaySync->DelFromPipelineOnContainer();
    return ERR_CJ_SUCCESS;
}
}
