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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_MULTI_THREAD_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_MULTI_THREAD_H

// All functions that are not thread safe operations need to add the FREE_NODE_CHECK macro at the entrance
// and implement the corresponding thread safe function with the MultiThread suffix.
#define FREE_NODE_CHECK(node, func, ...)                    \
    if (node && node->IsFree()) {                           \
        return func##MultiThread(__VA_ARGS__);              \
    }                                                       \

#define THREAD_SAFE_NODE_CHECK(node, func, ...)             \
    if (node && node->IsThreadSafeNode()) {                 \
        return func##MultiThread(__VA_ARGS__);              \
    }                                                       \

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_MULTI_THREAD_H