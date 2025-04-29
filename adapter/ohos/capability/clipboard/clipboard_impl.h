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

#ifndef FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CAPABILITY_CLIPBOARD_CLIPBOARD_IMPL_H
#define FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CAPABILITY_CLIPBOARD_CLIPBOARD_IMPL_H

#ifdef SYSTEM_CLIPBOARD_SUPPORTED
#include "pasteboard_client.h"
#endif

#include "core/common/clipboard/clipboard_interface.h"
#include "core/common/clipboard/paste_data.h"

namespace OHOS::Ace {
class PasteDataImpl;
class ClipboardImpl : public Clipboard {
public:
    explicit ClipboardImpl(const RefPtr<TaskExecutor>& taskExecutor) : Clipboard(taskExecutor) {}
    ~ClipboardImpl() override = default;

    // Implement Clipboard
    void SetData(
        const std::string& data, CopyOptions copyOption = CopyOptions::InApp, bool isDragData = false) override;
    void GetData(const std::function<void(const std::string&)>& callback, bool syncMode = false) override;
    void SetPixelMapData(const RefPtr<PixelMap>& pixmap, CopyOptions copyOption = CopyOptions::InApp) override;
    void GetPixelMapData(const std::function<void(const RefPtr<PixelMap>&)>& callback, bool syncMode = false) override;
    void AddPixelMapRecord(const RefPtr<PasteDataMix>& pasteData, const RefPtr<PixelMap>& pixmap) override;
    void AddImageRecord(const RefPtr<PasteDataMix>& pasteData, const std::string& uri) override;
    void AddTextRecord(const RefPtr<PasteDataMix>& pasteData, const std::string& selectedStr) override;
    void AddSpanStringRecord(const RefPtr<PasteDataMix>& pasteData, std::vector<uint8_t>& data) override;
    void AddMultiTypeRecord(
        const RefPtr<PasteDataMix>& pasteData, const RefPtr<MultiTypeRecordMix>& multiTypeRecord) override;
    void SetData(const RefPtr<PasteDataMix>& pasteData, CopyOptions copyOption) override;
    void GetData(const std::function<void(const std::string&, bool isLastRecord)>& textCallback,
        const std::function<void(const RefPtr<PixelMap>&, bool isLastRecord)>& pixelMapCallback,
        const std::function<void(const std::string&, bool isLastRecord)>& urlCallback, bool syncMode = false) override;
    RefPtr<PasteDataMix> CreatePasteDataMix() override;
    void HasData(const std::function<void(bool hasData)>& callback) override;
    void HasDataType(
        const std::function<void(bool hasData)>& callback, const std::vector<std::string>& mimeTypes) override;
    void Clear() override;
    void GetSpanStringData(
        const std::function<void(std::vector<std::vector<uint8_t>>&, const std::string&, bool&)>& callback,
        bool syncMode = false) override;

#ifdef SYSTEM_CLIPBOARD_SUPPORTED
private:
    void GetDataSync(const std::function<void(const std::string&)>& callback);
    void GetDataAsync(const std::function<void(const std::string&)>& callback);
    void GetDataSync(const std::function<void(const std::string&, bool isLastRecord)>& textCallback,
        const std::function<void(const RefPtr<PixelMap>&, bool isLastRecord)>& pixelMapCallback,
        const std::function<void(const std::string&, bool isLastRecord)>& urlCallback);
    void GetDataAsync(const std::function<void(const std::string&, bool isLastRecord)>& textCallback,
        const std::function<void(const RefPtr<PixelMap>&, bool isLastRecord)>& pixelMapCallback,
        const std::function<void(const std::string&, bool isLastRecord)>& urlCallback);
    void ProcessPasteDataRecord(const std::shared_ptr<MiscServices::PasteDataRecord>& pasteDataRecord,
        std::string& resText, bool& hasPlainRecord);
    void GetPixelMapDataSync(const std::function<void(const RefPtr<PixelMap>&)>& callback);
    void GetPixelMapDataAsync(const std::function<void(const RefPtr<PixelMap>&)>& callback);
    void GetSpanStringDataHelper(
        const std::function<void(std::vector<std::vector<uint8_t>>&, const std::string&, bool&)>& callback,
        bool syncMode = false);
    void ProcessSpanStringData(std::vector<std::vector<uint8_t>>& arrays,
        const OHOS::MiscServices::PasteData& pasteData, std::string& text, bool& isMultiTypeRecord);
    const std::string GetMimeType(
        std::map<std::string, std::shared_ptr<OHOS::MiscServices::EntryValue>> multiTypeDataMap);
#endif
};

class ClipboardProxyImpl final : public ClipboardInterface {
public:
    ClipboardProxyImpl() = default;
    ~ClipboardProxyImpl() = default;

    // Implement ClipboardInterface
    RefPtr<Clipboard> GetClipboard(const RefPtr<TaskExecutor>& taskExecutor) const override
    {
        return AceType::MakeRefPtr<ClipboardImpl>(taskExecutor);
    }
};

class PasteDataImpl : public PasteDataMix {
    DECLARE_ACE_TYPE(PasteDataImpl, PasteDataMix);

public:
    PasteDataImpl() = default;
    ~PasteDataImpl() = default;

#ifdef SYSTEM_CLIPBOARD_SUPPORTED
    std::shared_ptr<OHOS::MiscServices::PasteData> GetPasteDataData();
    void SetUnifiedData(std::shared_ptr<OHOS::MiscServices::PasteData> pasteData);

private:
    std::shared_ptr<OHOS::MiscServices::PasteData> pasteData_;
#endif
};

class MultiTypeRecordImpl : public MultiTypeRecordMix {
    DECLARE_ACE_TYPE(MultiTypeRecordImpl, MultiTypeRecordMix);

public:
    MultiTypeRecordImpl() = default;
    ~MultiTypeRecordImpl() = default;

    void SetPlainText(const std::string plainText);
    void SetUri(const std::string uri);
    void SetPixelMap(RefPtr<PixelMap> pixelMap);
    const RefPtr<PixelMap> GetPixelMap();
    const std::string GetPlainText();
    const std::string GetUri();
    std::vector<uint8_t>& GetSpanStringBuffer();

private:
    RefPtr<PixelMap> pixelMap_;
    std::string plainText_;
    std::string uri_;
    std::vector<uint8_t> spanStringBuffer_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CAPABILITY_CLIPBOARD_CLIPBOARD_IMPL_H