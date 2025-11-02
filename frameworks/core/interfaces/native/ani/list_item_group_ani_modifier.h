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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_LIST_ITEM_GROUP_ANI_MODIFIER
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_LIST_ITEM_GROUP_ANI_MODIFIER

#include "core/interfaces/ani/ani_api.h"
#include "base/log/log.h"

namespace OHOS::Ace::NG {
const ArkUIAniListItemGroupModifier* GetArkUIAniListItemGroupModifier();
void SetListItemGroupHeader(ArkUINodeHandle node, ArkUINodeHandle headerPtr);
void SetListItemGroupHeaderContent(ArkUINodeHandle node, ArkUINodeHandle headerPtr);
void ResetListItemGroupHeader(ArkUINodeHandle node);
void SetListItemGroupFooter(ArkUINodeHandle node, ArkUINodeHandle footerPtr);
void SetListItemGroupFooterContent(ArkUINodeHandle node, ArkUINodeHandle footerPtr);
void ResetListItemGroupFooter(ArkUINodeHandle node);
void SetListItemGroupStyle(ArkUINodeHandle node, int32_t style);
void SetListItemGroupSpace(ArkUINodeHandle node, ArkUIListItemGroupSpace space);
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_ANI_LIST_ITEM_GROUP_ANI_MODIFIER