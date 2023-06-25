/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_MODEL_H

#include <functional>
#include <mutex>

#include "base/memory/ace_type.h"

namespace OHOS::Ace {
class ACE_EXPORT RichEditorControllerBase : public AceType {
    DECLARE_ACE_TYPE(RichEditorControllerBase, AceType);
};

class ACE_EXPORT RichEditorModel {
public:
    static RichEditorModel* GetInstance();
    virtual ~RichEditorModel() = default;
    virtual void Create() = 0;
    virtual RefPtr<RichEditorControllerBase> GetRichEditorController() = 0;
    virtual void SetOnReady(std::function<void()>&& func) = 0;

private:
    static std::unique_ptr<RichEditorModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_MODEL_H
