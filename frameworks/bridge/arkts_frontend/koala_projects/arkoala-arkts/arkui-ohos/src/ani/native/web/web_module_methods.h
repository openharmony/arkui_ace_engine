/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_WEB_MODULE_METHODS_H
#define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_WEB_MODULE_METHODS_H

#include "ani.h"

namespace OHOS::Ace::Ani {
void SetWebOptions(ani_env* env, ani_class aniClass, ani_long node, ani_object object);
void SetWebControllerControllerHandler(ani_env* env, ani_class aniClass, ani_long handler, ani_object object);
} // namespace OHOS::Ace::Ani

#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_WEB_MODULE_METHODS_H