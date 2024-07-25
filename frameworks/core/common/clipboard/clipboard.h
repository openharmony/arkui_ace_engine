/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CLIPBOARD_CLIPBOARD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CLIPBOARD_CLIPBOARD_H

#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "base/thread/task_executor.h"
#include "core/common/clipboard/paste_data.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace {

class Clipboard : public AceType {
    DECLARE_ACE_TYPE(Clipboard, AceType);

public:
    ~Clipboard() override = default;

    virtual void SetData(
        const std::string& data, CopyOptions copyOption = CopyOptions::InApp, bool isDragData = false) = 0;
    virtual void GetData(const std::function<void(const std::string&)>& callback, bool syncMode = false) = 0;
    virtual void SetPixelMapData(const RefPtr<PixelMap>& pixmap, CopyOptions copyOption = CopyOptions::InApp) = 0;
    virtual void GetPixelMapData(
        const std::function<void(const RefPtr<PixelMap>&)>& callback, bool syncMode = false) = 0;
    virtual void HasData(const std::function<void(bool hasData)>& callback) = 0;
    virtual void HasDataType(
        const std::function<void(bool hasData)>& callback, const std::vector<std::string>& mimeTypes) = 0;
    virtual void AddPixelMapRecord(const RefPtr<PasteDataMix>& pasteData, const RefPtr<PixelMap>& pixmap) = 0;
    virtual void AddImageRecord(const RefPtr<PasteDataMix>& pasteData, const std::string& uri) = 0;
    virtual void AddTextRecord(const RefPtr<PasteDataMix>& pasteData, const std::string& selectedStr) = 0;
    virtual void AddSpanStringRecord(const RefPtr<PasteDataMix>& pasteData, std::vector<uint8_t>& data) = 0;
    virtual void SetData(const RefPtr<PasteDataMix>& pasteData, CopyOptions copyOption = CopyOptions::Distributed) = 0;
    virtual void GetData(const std::function<void(const std::string&, bool isLastRecord)>& textCallback,
        const std::function<void(const RefPtr<PixelMap>&, bool isLastRecord)>& pixelMapCallback,
        const std::function<void(const std::string&, bool isLastRecord)>& urlCallback, bool syncMode = false) = 0;
    virtual RefPtr<PasteDataMix> CreatePasteDataMix() = 0;
    virtual void Clear() = 0;
    virtual void GetSpanStringData(
        const std::function<void(std::vector<uint8_t>&, const std::string&)>& callback, bool syncMode = false) = 0;

protected:
    explicit Clipboard(const RefPtr<TaskExecutor>& taskExecutor) : taskExecutor_(taskExecutor) {}
    RefPtr<TaskExecutor> taskExecutor_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CLIPBOARD_CLIPBOARD_H
