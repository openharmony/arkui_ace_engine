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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_ACE_AUTO_FILL_ERROR_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_ACE_AUTO_FILL_ERROR_H

#include "base/memory/ace_type.h"

namespace OHOS::Ace {
enum AceAutoFillError {
    ACE_AUTO_FILL_DEFAULT = -1,
    /* the following error codes match the error codes defined in the ability autofill manager */
    ACE_AUTO_FILL_SUCCESS = 0,
    ACE_AUTO_FILL_FAILED,
    ACE_AUTO_FILL_CANCEL,
    ACE_AUTO_FILL_CANCEL_TIME_OUT,
    ACE_AUTO_FILL_RELEASE_FAILED,
    ACE_AUTO_FILL_ON_ERROR,
    ACE_AUTO_FILL_OBJECT_IS_NULL,
    ACE_AUTO_FILL_CREATE_MODULE_UI_EXTENSION_FAILED,
    ACE_AUTO_FILL_REQUEST_TIME_OUT,
    ACE_AUTO_FILL_TYPE_INVALID,
    ACE_AUTO_FILL_PREVIOUS_REQUEST_NOT_FINISHED
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_ACE_AUTO_FILL_ERROR_H