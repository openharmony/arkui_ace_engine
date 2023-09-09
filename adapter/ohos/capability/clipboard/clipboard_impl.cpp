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

#include "adapter/ohos/capability/clipboard/clipboard_impl.h"

#include "adapter/ohos/osal/pixel_map_ohos.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {
#ifndef SYSTEM_CLIPBOARD_SUPPORTED
namespace {
std::string g_clipboard;
RefPtr<PixelMap> g_pixmap;
} // namespace
#endif

#ifdef SYSTEM_CLIPBOARD_SUPPORTED
MiscServices::ShareOption TransitionCopyOption(CopyOptions copyOption)
{
    auto shareOption = MiscServices::ShareOption::InApp;
    switch (copyOption) {
        case CopyOptions::InApp:
            shareOption = MiscServices::ShareOption::InApp;
            break;
        case CopyOptions::Local:
            shareOption = MiscServices::ShareOption::LocalDevice;
            break;
        case CopyOptions::Distributed:
            shareOption = MiscServices::ShareOption::CrossDevice;
            break;
        default:
            break;
    }
    return shareOption;
}
#endif

void ClipboardImpl::HasData(const std::function<void(bool hasData)>& callback)
{
#ifdef SYSTEM_CLIPBOARD_SUPPORTED
    bool hasData = false;
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostSyncTask(
        [&hasData]() { hasData = OHOS::MiscServices::PasteboardClient::GetInstance()->HasPasteData(); },
        TaskExecutor::TaskType::PLATFORM);
    callback(hasData);
#endif
}

void ClipboardImpl::SetData(const std::string& data, CopyOptions copyOption, bool isDragData)
{
    CHECK_NULL_VOID(taskExecutor_);
#ifdef SYSTEM_CLIPBOARD_SUPPORTED
    auto shareOption = TransitionCopyOption(copyOption);
    taskExecutor_->PostTask(
        [data, shareOption, isDragData]() {
            auto pasteData = OHOS::MiscServices::PasteboardClient::GetInstance()->CreatePlainTextData(data);
            CHECK_NULL_VOID(pasteData);
            pasteData->SetShareOption(shareOption);
            pasteData->SetDraggedDataFlag(isDragData);
            OHOS::MiscServices::PasteboardClient::GetInstance()->SetPasteData(*pasteData);
        },
        TaskExecutor::TaskType::PLATFORM);
#else
    LOGI("Current device doesn't support system clipboard");
    taskExecutor_->PostTask([data]() { g_clipboard = data; }, TaskExecutor::TaskType::UI);
#endif
}

void ClipboardImpl::SetPixelMapData(const RefPtr<PixelMap>& pixmap, CopyOptions copyOption)
{
    CHECK_NULL_VOID(taskExecutor_);
#ifdef SYSTEM_CLIPBOARD_SUPPORTED
    auto shareOption = TransitionCopyOption(copyOption);
    taskExecutor_->PostTask(
        [pixmap, shareOption]() {
            CHECK_NULL_VOID(pixmap);
            auto pixmapOhos = AceType::DynamicCast<PixelMapOhos>(pixmap);
            CHECK_NULL_VOID(pixmapOhos);
            auto pasteData = OHOS::MiscServices::PasteboardClient::GetInstance()->CreatePixelMapData(
                pixmapOhos->GetPixelMapSharedPtr());
            CHECK_NULL_VOID(pasteData);
            pasteData->SetShareOption(shareOption);
            LOGI("Set pixmap to system clipboard");
            OHOS::MiscServices::PasteboardClient::GetInstance()->SetPasteData(*pasteData);
        },
        TaskExecutor::TaskType::PLATFORM);
#else
    LOGI("Current device doesn't support system clipboard");
    taskExecutor_->PostTask([pixmap]() { g_pixmap = pixmap; }, TaskExecutor::TaskType::UI);
#endif
}

void ClipboardImpl::GetData(const std::function<void(const std::string&)>& callback, bool syncMode)
{
#ifdef SYSTEM_CLIPBOARD_SUPPORTED
    if (!taskExecutor_ || !callback) {
        return;
    }

    if (syncMode) {
        GetDataSync(callback);
    } else {
        GetDataAsync(callback);
    }
#else
    LOGI("Current device doesn't support system clipboard");
    if (syncMode) {
        callback(g_clipboard);
        return;
    }
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [callback, taskExecutor = WeakClaim(RawPtr(taskExecutor_)), textData = g_clipboard]() {
            callback(textData);
        },
        TaskExecutor::TaskType::UI);
#endif
}

void ClipboardImpl::GetPixelMapData(const std::function<void(const RefPtr<PixelMap>&)>& callback, bool syncMode)
{
    if (!taskExecutor_ || !callback) {
        return;
    }
#ifdef SYSTEM_CLIPBOARD_SUPPORTED
    if (syncMode) {
        GetPixelMapDataSync(callback);
    } else {
        GetPixelMapDataAsync(callback);
    }
#else
    LOGI("Current device doesn't support system clipboard");
    if (syncMode) {
        callback(g_pixmap);
    } else {
        taskExecutor_->PostTask([callback, taskExecutor = WeakClaim(RawPtr(taskExecutor_)),
                                    imageData = g_pixmap]() { callback(imageData); },
            TaskExecutor::TaskType::UI);
    }
#endif
}

RefPtr<PasteDataMix> ClipboardImpl::CreatePasteDataMix()
{
    return AceType::MakeRefPtr<PasteDataImpl>();
}

void ClipboardImpl::AddPixelMapRecord(const RefPtr<PasteDataMix>& pasteData, const RefPtr<PixelMap>& pixmap)
{
    CHECK_NULL_VOID(taskExecutor_);
    auto peData = AceType::DynamicCast<PasteDataImpl>(pasteData);
    CHECK_NULL_VOID(peData);
    auto pixmapOhos = AceType::DynamicCast<PixelMapOhos>(pixmap);
    CHECK_NULL_VOID(pixmapOhos);
    LOGI("add pixelMap record to pasteData");
    peData->GetPasteDataData()->AddPixelMapRecord(pixmapOhos->GetPixelMapSharedPtr());
}

void ClipboardImpl::AddImageRecord(const RefPtr<PasteDataMix>& pasteData, const std::string& uri)
{
    CHECK_NULL_VOID(taskExecutor_);
    auto peData = AceType::DynamicCast<PasteDataImpl>(pasteData);
    CHECK_NULL_VOID(peData);
    LOGI("add url record to pasteData, url:  %{public}s", uri.c_str());
    peData->GetPasteDataData()->AddUriRecord(OHOS::Uri(uri));
}

void ClipboardImpl::AddTextRecord(const RefPtr<PasteDataMix>& pasteData, const std::string& selectedStr)
{
    CHECK_NULL_VOID(taskExecutor_);
    auto peData = AceType::DynamicCast<PasteDataImpl>(pasteData);
    CHECK_NULL_VOID(peData);
    LOGI("add text record to pasteData, text:  %{public}s", selectedStr.c_str());
    peData->GetPasteDataData()->AddTextRecord(selectedStr);
}

void ClipboardImpl::SetData(const RefPtr<PasteDataMix>& pasteData, CopyOptions copyOption)
{
#ifdef SYSTEM_CLIPBOARD_SUPPORTED
    auto shareOption = TransitionCopyOption(copyOption);
    auto peData = AceType::DynamicCast<PasteDataImpl>(pasteData);
    CHECK_NULL_VOID(peData);
    taskExecutor_->PostTask(
        [peData, shareOption]() {
            auto pasteData = peData->GetPasteDataData();
            pasteData->SetShareOption(shareOption);
            LOGI("add pasteData to clipboard, shareOption:  %{public}d", shareOption);
            OHOS::MiscServices::PasteboardClient::GetInstance()->SetPasteData(*pasteData);
        },
        TaskExecutor::TaskType::PLATFORM);
#else
    LOGI("Current device doesn't support system clipboard");
#endif
}

void ClipboardImpl::GetData(const std::function<void(const std::string&, bool isLastRecord)>& textCallback,
    const std::function<void(const RefPtr<PixelMap>&, bool isLastRecord)>& pixelMapCallback,
    const std::function<void(const std::string&, bool isLastRecord)>& urlCallback, bool syncMode)
{
#ifdef SYSTEM_CLIPBOARD_SUPPORTED
    if (!taskExecutor_ || !textCallback || !pixelMapCallback || !urlCallback) {
        return;
    }

    if (syncMode) {
        GetDataSync(textCallback, pixelMapCallback, urlCallback);
    } else {
        GetDataAsync(textCallback, pixelMapCallback, urlCallback);
    }
#else
    LOGI("Current device doesn't support system clipboard");
#endif
}

#ifdef SYSTEM_CLIPBOARD_SUPPORTED
std::shared_ptr<MiscServices::PasteData> PasteDataImpl::GetPasteDataData()
{
    if (pasteData_ == nullptr) {
        pasteData_ = std::make_shared<MiscServices::PasteData>();
    }
    return pasteData_;
}
void PasteDataImpl::SetUnifiedData(std::shared_ptr<MiscServices::PasteData> pasteData)
{
    pasteData_ = pasteData;
}

void ClipboardImpl::GetDataSync(const std::function<void(const std::string&)>& callback)
{
    std::string result;
    taskExecutor_->PostSyncTask(
        [&result]() {
            auto has = OHOS::MiscServices::PasteboardClient::GetInstance()->HasPasteData();
            CHECK_NULL_VOID(has);
            OHOS::MiscServices::PasteData pasteData;
            auto ok = OHOS::MiscServices::PasteboardClient::GetInstance()->GetPasteData(pasteData);
            CHECK_NULL_VOID(ok);
            auto textData = pasteData.GetPrimaryText();
            CHECK_NULL_VOID(textData);
            result = *textData;
        },
        TaskExecutor::TaskType::PLATFORM);
    callback(result);
}

void ClipboardImpl::GetDataAsync(const std::function<void(const std::string&)>& callback)
{
    taskExecutor_->PostTask(
        [callback, weakExecutor = WeakClaim(RawPtr(taskExecutor_))]() {
            auto taskExecutor = weakExecutor.Upgrade();
            CHECK_NULL_VOID(taskExecutor);
            auto has = OHOS::MiscServices::PasteboardClient::GetInstance()->HasPasteData();
            if (!has) {
                LOGE("GetDataAsync: SystemKeyboardData is not exist from MiscServices");
                taskExecutor->PostTask([callback]() { callback(""); }, TaskExecutor::TaskType::UI);
                return;
            }
            OHOS::MiscServices::PasteData pasteData;
            auto ok = OHOS::MiscServices::PasteboardClient::GetInstance()->GetPasteData(pasteData);
            if (!ok) {
                LOGE("GetDataAsync: Get SystemKeyboardData fail from MiscServices");
                taskExecutor->PostTask([callback]() { callback(""); }, TaskExecutor::TaskType::UI);
                return;
            }
            auto textData = pasteData.GetPrimaryText();
            if (!textData) {
                LOGE("GetDataAsync: Get SystemKeyboardTextData fail from MiscServices");
                taskExecutor->PostTask([callback]() { callback(""); }, TaskExecutor::TaskType::UI);
                return;
            }
            auto result = *textData;
            taskExecutor->PostTask([callback, result]() { callback(result); }, TaskExecutor::TaskType::UI);
        },
        TaskExecutor::TaskType::PLATFORM);
}

void ClipboardImpl::GetDataSync(const std::function<void(const std::string&, bool isLastRecord)>& textCallback,
    const std::function<void(const RefPtr<PixelMap>&, bool isLastRecord)>& pixelMapCallback,
    const std::function<void(const std::string&, bool isLastRecord)>& urlCallback)
{
    LOGI("get data from clipboard, sync");
    OHOS::MiscServices::PasteData pasteData;
    taskExecutor_->PostSyncTask(
        [&pasteData]() {
            auto has = OHOS::MiscServices::PasteboardClient::GetInstance()->HasPasteData();
            CHECK_NULL_VOID(has);
            auto ok = OHOS::MiscServices::PasteboardClient::GetInstance()->GetPasteData(pasteData);
            CHECK_NULL_VOID(ok);
        },
        TaskExecutor::TaskType::PLATFORM);

    auto count = pasteData.GetRecordCount();
    size_t index = 0;
    for (const auto& pasteDataRecord : pasteData.AllRecords()) {
        index++;
        if (pasteDataRecord == nullptr) {
            continue;
        }
        bool isLastRecord = index == count;
        if (pasteDataRecord->GetPlainText() != nullptr) {
            auto textData = pasteDataRecord->GetPlainText();
            auto result = *textData;
            textCallback(result, isLastRecord);
        } else if (pasteDataRecord->GetPixelMap() != nullptr) {
            auto imageData = pasteDataRecord->GetPixelMap();
            auto result = AceType::MakeRefPtr<PixelMapOhos>(imageData);
            pixelMapCallback(result, isLastRecord);
        } else if (pasteDataRecord->GetUri() != nullptr) {
            auto textData = pasteDataRecord->GetUri();
            auto result = (*textData).ToString();
            urlCallback(result, isLastRecord);
        }
    }
}

void ClipboardImpl::GetDataAsync(const std::function<void(const std::string&, bool isLastRecord)>& textCallback,
    const std::function<void(const RefPtr<PixelMap>&, bool isLastRecord)>& pixelMapCallback,
    const std::function<void(const std::string&, bool isLastRecord)>& urlCallback)
{
    LOGI("get data from clipboard, async");
    taskExecutor_->PostTask(
        [textCallback, pixelMapCallback, urlCallback, weakExecutor = WeakClaim(RawPtr(taskExecutor_))]() {
            auto taskExecutor = weakExecutor.Upgrade();
            auto has = OHOS::MiscServices::PasteboardClient::GetInstance()->HasPasteData();
            CHECK_NULL_VOID(has);
            OHOS::MiscServices::PasteData pasteData;
            auto ok = OHOS::MiscServices::PasteboardClient::GetInstance()->GetPasteData(pasteData);
            CHECK_NULL_VOID(ok);
            auto count = pasteData.GetRecordCount();
            size_t index = 0;
            for (const auto& pasteDataRecord : pasteData.AllRecords()) {
                index++;
                if (pasteDataRecord == nullptr) {
                    continue;
                }
                bool isLastRecord = index == count;
                if (pasteDataRecord->GetPlainText() != nullptr) {
                    auto textData = pasteDataRecord->GetPlainText();
                    auto result = *textData;
                    taskExecutor->PostTask(
                        [textCallback, result, isLastRecord]() { textCallback(result, isLastRecord); },
                        TaskExecutor::TaskType::UI);
                } else if (pasteDataRecord->GetPixelMap() != nullptr) {
                    auto imageData = pasteDataRecord->GetPixelMap();
                    auto result = AceType::MakeRefPtr<PixelMapOhos>(imageData);
                    taskExecutor->PostTask(
                        [pixelMapCallback, result, isLastRecord]() { pixelMapCallback(result, isLastRecord); },
                        TaskExecutor::TaskType::UI);
                } else if (pasteDataRecord->GetUri() != nullptr) {
                    auto textData = pasteDataRecord->GetUri();
                    auto result = (*textData).ToString();
                    taskExecutor->PostTask([urlCallback, result, isLastRecord]() { urlCallback(result, isLastRecord); },
                        TaskExecutor::TaskType::UI);
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void ClipboardImpl::GetPixelMapDataSync(const std::function<void(const RefPtr<PixelMap>&)>& callback)
{
    RefPtr<PixelMap> pixmap;
    taskExecutor_->PostSyncTask(
        [&pixmap]() {
            auto has = OHOS::MiscServices::PasteboardClient::GetInstance()->HasPasteData();
            CHECK_NULL_VOID(has);
            OHOS::MiscServices::PasteData pasteData;
            auto ok = OHOS::MiscServices::PasteboardClient::GetInstance()->GetPasteData(pasteData);
            CHECK_NULL_VOID(ok);
            auto imageData = pasteData.GetPrimaryPixelMap();
            CHECK_NULL_VOID(imageData);
            pixmap = AceType::MakeRefPtr<PixelMapOhos>(imageData);
        },
        TaskExecutor::TaskType::PLATFORM);
    callback(pixmap);
}

void ClipboardImpl::GetPixelMapDataAsync(const std::function<void(const RefPtr<PixelMap>&)>& callback)
{
    taskExecutor_->PostTask(
        [callback, weakExecutor = WeakClaim(RawPtr(taskExecutor_))]() {
            auto taskExecutor = weakExecutor.Upgrade();
            CHECK_NULL_VOID(taskExecutor);
            auto has = OHOS::MiscServices::PasteboardClient::GetInstance()->HasPasteData();
            if (!has) {
                LOGE("SystemKeyboardData is not exist from MiscServices");
                taskExecutor->PostTask([callback]() { callback(nullptr); }, TaskExecutor::TaskType::UI);
                return;
            }
            OHOS::MiscServices::PasteData pasteData;
            auto ok = OHOS::MiscServices::PasteboardClient::GetInstance()->GetPasteData(pasteData);
            if (!ok) {
                LOGE("Get SystemKeyboardData fail from MiscServices");
                taskExecutor->PostTask([callback]() { callback(nullptr); }, TaskExecutor::TaskType::UI);
                return;
            }
            auto imageData = pasteData.GetPrimaryPixelMap();
            if (!imageData) {
                LOGE("Get SystemKeyboardImageData fail from MiscServices");
                taskExecutor->PostTask([callback]() { callback(nullptr); }, TaskExecutor::TaskType::UI);
                return;
            }
            auto result = AceType::MakeRefPtr<PixelMapOhos>(imageData);
            taskExecutor->PostTask([callback, result]() { callback(result); }, TaskExecutor::TaskType::UI);
        },
        TaskExecutor::TaskType::PLATFORM);
}
#endif

void ClipboardImpl::Clear() {}

} // namespace OHOS::Ace
