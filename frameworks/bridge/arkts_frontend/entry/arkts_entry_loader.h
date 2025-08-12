/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ENTRY_ARKTS_ENTRY_LOADER_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ENTRY_ARKTS_ENTRY_LOADER_H

#include <string>
#include <vector>
#include <ani.h>

namespace OHOS::Ace {
class EntryLoader {
public:
    EntryLoader(std::string url, ani_env* env): url_(url), env_(env) {}
    ~EntryLoader() = default;

    ani_object GetPageEntryObj();

private:
    std::string url_;
    ani_env* env_;
};

namespace NG {
class EntryLoader {
public:
    EntryLoader(ani_env* env, const std::string& abcModulePath);
    EntryLoader(ani_env* env, const std::vector<uint8_t>& abcContent);
    ~EntryLoader() = default;

    ani_object GetPageEntryObj(const std::string& entryPath) const;

    operator bool() const
    {
        return loadClass_;
    }

private:
    ani_env* env_ {};
    ani_object runtimeLinkerObj_ {};
    ani_method loadClass_ {};
};
}
}

#endif