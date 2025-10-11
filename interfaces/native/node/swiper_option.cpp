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

#include "node_model.h"

#include "base/error/error_code.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t OH_ArkUI_Swiper_FinishAnimation(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    CHECK_NE_RETURN(node->type, ARKUI_NODE_SWIPER, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto nodeModifiers = fullImpl->getNodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto swiperModifier = nodeModifiers->getSwiperModifier();
    CHECK_NULL_RETURN(swiperModifier, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    swiperModifier->setSwiperFinishAnimation(node->uiNodeHandle);
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

#ifdef __cplusplus
};
#endif
