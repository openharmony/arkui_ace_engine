/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "mock_clipboard.h"

#include "adapter/ohos/capability/clipboard/clipboard_impl.h"
#include "core/common/clipboard/clipboard_proxy.h"

namespace OHOS::Ace {
namespace {
std::optional<std::string> saveData;
} // namespace
ClipboardProxy* ClipboardProxy::inst_ = nullptr;
std::mutex ClipboardProxy::mutex_;

ClipboardProxy* ClipboardProxy::GetInstance()
{
    if (inst_ == nullptr) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (inst_ == nullptr) {
            inst_ = new ClipboardProxy();
        }
    }
    return inst_;
}

void ClipboardProxy::SetDelegate(std::unique_ptr<ClipboardInterface>&& delegate)
{
    delegate_ = std::move(delegate);
}

RefPtr<Clipboard> ClipboardProxy::GetClipboard(const RefPtr<TaskExecutor>& taskExecutor) const
{
    auto clipboard = AceType::MakeRefPtr<MockClipBoard>(taskExecutor);
    return clipboard;
}

void MockClipBoard::HasData(const std::function<void(bool hasData)>& callback)
{
    if (callback) {
        callback(saveData.has_value());
    }
}

void MockClipBoard::HasDataType(
    const std::function<void(bool hasData)>& callback, const std::vector<std::string>& mimeTypes)
{
    if (callback) {
        callback(saveData.has_value());
    }
}

void MockClipBoard::SetData(const std::string& data, CopyOptions /* copyOption */, bool /* isDragData */)
{
    saveData = data;
}

void MockClipBoard::GetData(const std::function<void(const std::string&)>& callback, bool syncMode)
{
    if (callback) {
        callback(saveData.value_or(""));
    }
}

void MockClipBoard::AddPixelMapRecord(const RefPtr<PasteDataMix>& pasteData, const RefPtr<PixelMap>& pixmap) {}
void MockClipBoard::AddImageRecord(const RefPtr<PasteDataMix>& pasteData, const std::string& uri) {}
void MockClipBoard::AddTextRecord(const RefPtr<PasteDataMix>& pasteData, const std::string& selectedStr) {}
void MockClipBoard::AddSpanStringRecord(const RefPtr<PasteDataMix>& pasteData, std::vector<uint8_t>& data) {}
void MockClipBoard::AddMultiTypeRecord(
    const RefPtr<PasteDataMix>& pasteData, const RefPtr<MultiTypeRecordMix>& multiTypeRecord)
{}
void MockClipBoard::SetData(const RefPtr<PasteDataMix>& pasteData, CopyOptions copyOption) {}
void MockClipBoard::GetData(const std::function<void(const std::string&, bool isLastRecord)>& textCallback,
    const std::function<void(const RefPtr<PixelMap>&, bool isLastRecord)>& pixelMapCallback,
    const std::function<void(const std::string&, bool isLastRecord)>& urlCallback, bool syncMode)
{}
void MockClipBoard::GetSpanStringData(
    const std::function<void(std::vector<std::vector<uint8_t>>&, const std::string&, bool&)>& callback, bool syncMode)
{}

RefPtr<PasteDataMix> MockClipBoard::CreatePasteDataMix()
{
    return AceType::MakeRefPtr<PasteDataMix>();
}

void MultiTypeRecordImpl::SetPlainText(const std::string plainText) {}
void MultiTypeRecordImpl::SetUri(const std::string uri) {}
void MultiTypeRecordImpl::SetHtmlText(const std::string& htmlText) {}
void MultiTypeRecordImpl::SetPixelMap(RefPtr<PixelMap> pixelMap) {}

const RefPtr<PixelMap> MultiTypeRecordImpl::GetPixelMap()
{
    return nullptr;
}
const std::string MultiTypeRecordImpl::GetPlainText()
{
    return "";
}
const std::string MultiTypeRecordImpl::GetUri()
{
    return "";
}
const std::string MultiTypeRecordImpl::GetHtmlText()
{
    return "";
}
std::vector<uint8_t>& MultiTypeRecordImpl::GetSpanStringBuffer()
{
    return spanStringBuffer_;
}
} // namespace OHOS::Ace
