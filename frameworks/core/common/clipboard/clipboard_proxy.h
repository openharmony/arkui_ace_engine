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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CLIPBOARD_CLIPBOARD_PROXY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CLIPBOARD_CLIPBOARD_PROXY_H

#include "base/utils/singleton.h"
#include "core/common/clipboard/clipboard_interface.h"

namespace OHOS::Ace {

class ClipboardProxy : public Singleton<ClipboardProxy>, public ClipboardInterface {
    DECLARE_SINGLETON(ClipboardProxy);

public:
    void SetDelegate(std::unique_ptr<ClipboardInterface>&& delegate);
    RefPtr<Clipboard> GetClipboard(const RefPtr<TaskExecutor>& taskExecutor) const override;

private:
    std::unique_ptr<ClipboardInterface> delegate_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CLIPBOARD_CLIPBOARD_PROXY_H
