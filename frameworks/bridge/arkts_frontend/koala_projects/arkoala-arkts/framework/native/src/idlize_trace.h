/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_ARKTS_FRONTEND_IDLIZE_TRACE_H
#define FOUNDATION_ARKUI_ACE_ENGINE_ARKTS_FRONTEND_IDLIZE_TRACE_H

namespace OHOS::Ace {
class IdlizeScopedTrace final {
public:
    explicit IdlizeScopedTrace(const char* name);
    ~IdlizeScopedTrace();

    IdlizeScopedTrace(const IdlizeScopedTrace&) = delete;
    IdlizeScopedTrace& operator=(const IdlizeScopedTrace&) = delete;
    IdlizeScopedTrace(IdlizeScopedTrace&&) = delete;
    IdlizeScopedTrace& operator=(IdlizeScopedTrace&&) = delete;

private:
    bool active_ = false;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ARKUI_ACE_ENGINE_ARKTS_FRONTEND_IDLIZE_TRACE_H
