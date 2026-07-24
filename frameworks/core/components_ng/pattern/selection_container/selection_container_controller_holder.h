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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECTION_CONTAINER_SELECTION_CONTAINER_CONTROLLER_HOLDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECTION_CONTAINER_SELECTION_CONTAINER_CONTROLLER_HOLDER_H

#include <memory>

namespace OHOS::Ace::NG {
// Abstract, JS-independent holder. The bridge layer supplies a concrete
// implementation that pins a JS controller object (panda CopyableGlobal) so it
// is not garbage-collected while the SelectionContainer is alive. Core holds a
// shared_ptr to this base type and never touches JSI/panda directly.
class SelectionContainerControllerHolder {
public:
    virtual ~SelectionContainerControllerHolder() = default;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECTION_CONTAINER_SELECTION_CONTAINER_CONTROLLER_HOLDER_H
