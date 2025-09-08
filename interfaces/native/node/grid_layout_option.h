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

#ifndef FOUNDATION_ACE_FRAMEWORKS_INTERFACE_NATIVE_NODE_GRID_LAYOUT_OPTION_H
#define FOUNDATION_ACE_FRAMEWORKS_INTERFACE_NATIVE_NODE_GRID_LAYOUT_OPTION_H

#include <cstdint>
#include <set>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ArkUI_GridLayoutOptions {
    std::set<int32_t> irregularIndexes;
    int32_t size;
    void* onGetIrregularSizeByIndex;
    void* onRectByIndexCallback;
    void* irregularSizeUserData;
    void* rectByIndexUserData;
} ArkUI_GridLayoutOptions;

#ifdef __cplusplus
}
#endif

#endif // FOUNDATION_ACE_FRAMEWORKS_INTERFACE_NATIVE_NODE_GRID_LAYOUT_OPTION_H