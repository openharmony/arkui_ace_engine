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

#ifndef FOUNDATION_ACE_INTERFACE_INNERAPI_BASE_MARCOS_H
#define FOUNDATION_ACE_INTERFACE_INNERAPI_BASE_MARCOS_H

#ifndef DRAWABLE_FORCE_EXPORT
#define DRAWABLE_FORCE_EXPORT __attribute__((visibility("default")))
#endif

#define CHECK_NULL_RETURN(ptr, ret) \
    do {                            \
        if (!(ptr)) {               \
            return ret;             \
        }                           \
    } while (0)

#define CHECK_NULL_VOID(ptr) \
    do {                     \
        if (!(ptr)) {        \
            return;          \
        }                    \
    } while (0)
#endif // FOUNDATION_ACE_INTERFACE_INNERAPI_BASE_MARCOS_H
