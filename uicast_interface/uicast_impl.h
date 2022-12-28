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

#ifndef ACE_UICAST_IMPL_UICAST_IMPL_H
#define ACE_UICAST_IMPL_UICAST_IMPL_H

#include <string>

#include "base/utils/macros.h"

namespace OHOS::Ace::Framework {
class JSView;

class ACE_EXPORT UICastImpl {
public:
    UICastImpl() = delete;
    static int GetViewUniqueID(int parentUniqueId);
    static void CacheCmd(const std::string& cmd);
    static void CacheCmd(const std::string& cmd, const std::string& para);
    static void SendCmd();
    static void ViewCreate(const std::string& viewId, int uniqueId, JSView* view);
    static void ViewConstructor(
        const std::string& viewId, int uniqueId, const std::string& parentViewId, int parentUniqueId, JSView* view);
    static void Render(const std::string& viewId);
    static void CreateLazyForEach(const std::string& pviewID, int totalCount, const std::string& remoteInfo);
};
} // namespace OHOS::Ace::Framework

#endif // ACE_UICAST_IMPL_UICAST_IMPL_H