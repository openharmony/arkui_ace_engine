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

#ifdef SYSTEM_CLIPBOARD_SUPPORTED
#include "pasteboard_client.h"
#endif

namespace OHOS::Ace {
#ifndef SYSTEM_CLIPBOARD_SUPPORTED
namespace {
std::string g_clipboard;
RefPtr<PixelMap> g_pixmap;
}
#endif
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

void ClipboardImpl::SetData(const std::string& data, CopyOptions copyOption, bool isDragData)
{
#ifdef SYSTEM_CLIPBOARD_SUPPORTED
    auto shareOption = TransitionCopyOption(copyOption);
    if (taskExecutor_) {
        taskExecutor_->PostTask(
            [data, shareOption, isDragData]() {
                auto pasteData = OHOS::MiscServices::PasteboardClient::GetInstance()->CreatePlainTextData(data);
                if (!pasteData) {
                    LOGE("create SystemKeyboardData fail from MiscServices");
                    return;
                }
                pasteData->SetShareOption(shareOption);
                pasteData->SetDraggedDataFlag(isDragData);
                OHOS::MiscServices::PasteboardClient::GetInstance()->SetPasteData(*pasteData);
            },
            TaskExecutor::TaskType::PLATFORM);
    }
#else
    LOGI("Current device doesn't support system clipboard");
    taskExecutor_->PostTask([data]() { g_clipboard = data; }, TaskExecutor::TaskType::UI);
#endif
}

void ClipboardImpl::SetPixelMapData(const RefPtr<PixelMap>& pixmap, CopyOptions copyOption)
{
#ifdef SYSTEM_CLIPBOARD_SUPPORTED
    auto shareOption = TransitionCopyOption(copyOption);
    if (taskExecutor_) {
        taskExecutor_->PostTask(
            [pixmap, shareOption]() {
                if (!pixmap) {
                    LOGE("pixmap is nullptr");
                    return;
                }
                auto pixmapOhos = AceType::DynamicCast<PixelMapOhos>(pixmap);
                if (!pixmapOhos) {
                    return;
                }
                auto pasteData = OHOS::MiscServices::PasteboardClient::GetInstance()->CreatePixelMapData(
                    pixmapOhos->GetPixelMapSharedPtr());
                if (!pasteData) {
                    LOGE("create SystemKeyboardData fail from MiscServices");
                    return;
                }
                pasteData->SetShareOption(shareOption);
                LOGI("Set pixmap to system clipboard");
                OHOS::MiscServices::PasteboardClient::GetInstance()->SetPasteData(*pasteData);
            },
            TaskExecutor::TaskType::PLATFORM);
    }
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
    } else {
        taskExecutor_->PostTask(
            [callback, taskExecutor = WeakClaim(RawPtr(taskExecutor_)), textData = g_clipboard]() {
                callback(textData);
            },
            TaskExecutor::TaskType::UI);
    }
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
        taskExecutor_->PostTask(
            [callback, taskExecutor = WeakClaim(RawPtr(taskExecutor_)), imageData = g_pixmap]() {
                callback(imageData);
            },
            TaskExecutor::TaskType::UI);
    }
#endif
}

#ifdef SYSTEM_CLIPBOARD_SUPPORTED
void ClipboardImpl::GetDataSync(const std::function<void(const std::string&)>& callback)
{
    std::string result;
    taskExecutor_->PostSyncTask(
        [&result]() {
            auto has = OHOS::MiscServices::PasteboardClient::GetInstance()->HasPasteData();
            if (!has) {
                LOGE("GetDataSync: SystemKeyboardData is not exist from MiscServices");
                return;
            }
            OHOS::MiscServices::PasteData pasteData;
            auto ok = OHOS::MiscServices::PasteboardClient::GetInstance()->GetPasteData(pasteData);
            if (!ok) {
                LOGE("GetDataSync: Get SystemKeyboardData fail from MiscServices");
                return;
            }
            auto textData = pasteData.GetPrimaryText();
            if (!textData) {
                LOGE("GetDataSync: Get SystemKeyboardTextData fail from MiscServices");
                return;
            }
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
            if (!taskExecutor) {
                LOGE("GetDataAsync: TaskExecutor is not exist");
                return;
            }
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

void ClipboardImpl::GetPixelMapDataSync(const std::function<void(const RefPtr<PixelMap>&)>& callback)
{
    RefPtr<PixelMap> pixmap;
    taskExecutor_->PostSyncTask(
        [&pixmap]() {
            auto has = OHOS::MiscServices::PasteboardClient::GetInstance()->HasPasteData();
            if (!has) {
                LOGE("SystemKeyboardData is not exist from MiscServices");
                return;
            }
            OHOS::MiscServices::PasteData pasteData;
            auto ok = OHOS::MiscServices::PasteboardClient::GetInstance()->GetPasteData(pasteData);
            if (!ok) {
                LOGE("Get SystemKeyboardData fail from MiscServices");
                return;
            }
            auto imageData = pasteData.GetPrimaryPixelMap();
            if (!imageData) {
                LOGE("Get SystemKeyboardImageData fail from MiscServices");
                return;
            }
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
            if (!taskExecutor) {
                LOGE("TaskExecutor is not exist");
                return;
            }
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