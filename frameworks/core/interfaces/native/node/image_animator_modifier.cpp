/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/image_animator_modifier.h"

#include "ui/base/utils/utils.h"

#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG {

namespace NodeModifier {
const ArkUIImageAnimatorModifier* GetImageAnimatorModifier()
{
    static const ArkUIImageAnimatorModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("ImageAnimator");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUIImageAnimatorModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

const CJUIImageAnimatorModifier* GetCJUIImageAnimatorModifier()
{
    static const CJUIImageAnimatorModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("ImageAnimator");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const CJUIImageAnimatorModifier*>(module->GetCjModifier());
    }
    return cachedModifier;
}

void SetImageAnimatorOnStart(ArkUINodeHandle node, void* extraParam)
{
    CHECK_NULL_VOID(node);
    auto modifier = GetImageAnimatorModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setImageAnimatorOnStartExt(node, extraParam);
}

void SetImageAnimatorOnPause(ArkUINodeHandle node, void* extraParam)
{
    CHECK_NULL_VOID(node);
    auto modifier = GetImageAnimatorModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setImageAnimatorOnPauseExt(node, extraParam);
}

void SetImageAnimatorOnRepeat(ArkUINodeHandle node, void* extraParam)
{
    CHECK_NULL_VOID(node);
    auto modifier = GetImageAnimatorModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setImageAnimatorOnRepeatExt(node, extraParam);
}

void SetImageAnimatorOnCancel(ArkUINodeHandle node, void* extraParam)
{
    CHECK_NULL_VOID(node);
    auto modifier = GetImageAnimatorModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setImageAnimatorOnCancelExt(node, extraParam);
}

void SetImageAnimatorOnFinish(ArkUINodeHandle node, void* extraParam)
{
    CHECK_NULL_VOID(node);
    auto modifier = GetImageAnimatorModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setImageAnimatorOnFinishExt(node, extraParam);
}

void ResetImageAnimatorOnStart(ArkUINodeHandle node)
{
    CHECK_NULL_VOID(node);
    auto modifier = GetImageAnimatorModifier();
    CHECK_NULL_VOID(modifier);
    modifier->resetImageAnimatorOnStart(node);
}
void ResetImageAnimatorOnPause(ArkUINodeHandle node)
{
    CHECK_NULL_VOID(node);
    auto modifier = GetImageAnimatorModifier();
    CHECK_NULL_VOID(modifier);
    modifier->resetImageAnimatorOnPause(node);
}
void ResetImageAnimatorOnRepeat(ArkUINodeHandle node)
{
    CHECK_NULL_VOID(node);
    auto modifier = GetImageAnimatorModifier();
    CHECK_NULL_VOID(modifier);
    modifier->resetImageAnimatorOnRepeat(node);
}
void ResetImageAnimatorOnCancel(ArkUINodeHandle node)
{
    CHECK_NULL_VOID(node);
    auto modifier = GetImageAnimatorModifier();
    CHECK_NULL_VOID(modifier);
    modifier->resetImageAnimatorOnCancel(node);
}
void ResetImageAnimatorOnFinish(ArkUINodeHandle node)
{
    CHECK_NULL_VOID(node);
    auto modifier = GetImageAnimatorModifier();
    CHECK_NULL_VOID(modifier);
    modifier->resetImageAnimatorOnFinish(node);
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
