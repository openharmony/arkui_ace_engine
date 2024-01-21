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
#ifndef I_ACE_MOCK_SECURITY_COMPONENT_PROPE_H
#define I_ACE_MOCK_SECURITY_COMPONENT_PROPE_H

#include <string>

namespace OHOS {
namespace Security {
namespace SecurityComponent {
class ISecCompProbe {
public:
    virtual int32_t GetComponentInfo(int32_t nodeId, std::string& componentInfo) = 0;
};
}  // namespace SecurityComponent
}  // namespace Security
}  // namespace OHOS
#endif  // I_ACE_MOCK_SECURITY_COMPONENT_PROPE_H
