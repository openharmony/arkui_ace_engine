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

#include "adapter/ohos/osal/screen_lock_manager_ohos.h"

#if defined(ENABLE_SCREEN_LOCK_MANAGER)
#include "screenlock_manager.h"
#endif

namespace OHOS::Ace {
bool ScreenLockManager::IsScreenLocked()
{
#if defined(ENABLE_SCREEN_LOCK_MANAGER)
    return ScreenLock::ScreenLockManager::GetInstance()->IsScreenLocked();
#else
    return false;
#endif
}

} // namespace OHOS::Ace
