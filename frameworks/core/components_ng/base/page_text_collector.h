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
#ifndef FOUNDATION_ACE_PAGE_TEXT_COLLECTOR_H
#define FOUNDATION_ACE_PAGE_TEXT_COLLECTOR_H
#include <cstdint>
#include "base/utils/macros.h"
namespace OHOS::Ace::NG {
ACE_FORCE_EXPORT int32_t CollectPageText(int32_t instanceId, char** data, uint32_t* size, const char** reason);
}
#endif
