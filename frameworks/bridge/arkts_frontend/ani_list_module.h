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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ANI_LIST_MODULE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ANI_LIST_MODULE_H

#include <cstdint>
#include "core/components_ng/pattern/list/list_children_main_size.h"
#include "core/components_ng/pattern/list/list_item_group_model_static.h"
#include "core/components_ng/pattern/list/list_model_static.h"

typedef class __ani_object* ani_object;
typedef struct __ani_env ani_env;
typedef int64_t ani_long;
typedef class __ani_fn_object* ani_fn_object;
typedef class __ani_ref* ani_ref;

namespace OHOS::Ace::Framework {

class AniListModule {
public:
    static void SetListChildrenMainSize(ani_env* env, ani_long ptr, ani_object obj);
    static void SetChildrenMainSize(ani_env* env, const ani_object& obj, NG::FrameNode* node, bool isList);
};

} // namespace OHOS::Ace::Framework
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ANI_LIST_MODULE_H
