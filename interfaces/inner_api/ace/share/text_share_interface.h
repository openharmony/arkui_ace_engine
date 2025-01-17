/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_SHARE_TEXT_SHARE_INTERFACE_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_SHARE_TEXT_SHARE_INTERFACE_H

#include <memory>
#include <string>

namespace OHOS {
namespace AbilityRuntime {
class Context;
} // namespace AbilityRuntime

namespace Rosen {
struct Rect;
} // namespace Rosen

namespace Ace {
class TextShareInterface {
public:
    virtual int32_t StartUpShareFunc(const std::shared_ptr<AbilityRuntime::Context> &context,
        const Rosen::Rect &anchorRect, const std::string &windowName,
        const std::string &textContent) = 0;

protected:
    virtual ~TextShareInterface() {}
};
} // namespace Ace
} // namespace OHOS
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_SHARE_TEXT_SHARE_INTERFACE_H
