/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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
#include "native_error_message_macros.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t OH_ArkUI_Swiper_FinishAnimation(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Swiper node is null");
    if (node->type != ARKUI_NODE_SWIPER) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID,
            __FUNCTION__, "Node type is not ARKUI_NODE_SWIPER");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Full implementation is null");
    auto nodeModifiers = fullImpl->getNodeModifiers();
    CHECK_NULL_RETURN_WITH_MESSAGE(nodeModifiers, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Node modifiers is null");
    auto swiperModifier = nodeModifiers->getSwiperModifier();
    CHECK_NULL_RETURN_WITH_MESSAGE(swiperModifier, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Swiper modifier is null");
    swiperModifier->setSwiperFinishAnimation(node->uiNodeHandle);
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_Swiper_StartFakeDrag(ArkUI_NodeHandle node, bool* isSuccessful)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Swiper node is null");
    if (node->type != ARKUI_NODE_SWIPER) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID,
            __FUNCTION__, "Node type is not ARKUI_NODE_SWIPER");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Full implementation is null");
    auto nodeModifiers = fullImpl->getNodeModifiers();
    CHECK_NULL_RETURN_WITH_MESSAGE(nodeModifiers, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Node modifiers is null");
    auto swiperModifier = nodeModifiers->getSwiperModifier();
    CHECK_NULL_RETURN_WITH_MESSAGE(swiperModifier, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Swiper modifier is null");
    swiperModifier->callSwiperStartFakeDrag(node->uiNodeHandle, isSuccessful);
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_Swiper_FakeDragBy(ArkUI_NodeHandle node, float offset, bool* isConsumedOffset)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Swiper node is null");
    if (node->type != ARKUI_NODE_SWIPER) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID,
            __FUNCTION__, "Node type is not ARKUI_NODE_SWIPER");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Full implementation is null");
    auto nodeModifiers = fullImpl->getNodeModifiers();
    CHECK_NULL_RETURN_WITH_MESSAGE(nodeModifiers, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Node modifiers is null");
    auto swiperModifier = nodeModifiers->getSwiperModifier();
    CHECK_NULL_RETURN_WITH_MESSAGE(swiperModifier, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Swiper modifier is null");
    swiperModifier->callSwiperFakeDragBy(node->uiNodeHandle, offset, isConsumedOffset);
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_Swiper_StopFakeDrag(ArkUI_NodeHandle node, bool* isSuccessful)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Swiper node is null");
    if (node->type != ARKUI_NODE_SWIPER) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID,
            __FUNCTION__, "Node type is not ARKUI_NODE_SWIPER");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Full implementation is null");
    auto nodeModifiers = fullImpl->getNodeModifiers();
    CHECK_NULL_RETURN_WITH_MESSAGE(nodeModifiers, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Node modifiers is null");
    auto swiperModifier = nodeModifiers->getSwiperModifier();
    CHECK_NULL_RETURN_WITH_MESSAGE(swiperModifier, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Swiper modifier is null");
    swiperModifier->callSwiperStopFakeDrag(node->uiNodeHandle, isSuccessful);
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_Swiper_IsFakeDragging(ArkUI_NodeHandle node, bool* isFakeDragging)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "current node is null");
    if (node->type != ARKUI_NODE_SWIPER) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID,
            __FUNCTION__, "Node type is not ARKUI_NODE_SWIPER");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "current fullImpl is null");
    auto nodeModifiers = fullImpl->getNodeModifiers();
    CHECK_NULL_RETURN_WITH_MESSAGE(nodeModifiers, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "node modifier is null");
    auto swiperModifier = nodeModifiers->getSwiperModifier();
    CHECK_NULL_RETURN_WITH_MESSAGE(swiperModifier, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "swiper modifier is null");
    swiperModifier->callSwiperIsFakeDragging(node->uiNodeHandle, isFakeDragging);
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_Swiper_ShowPrevious(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Swiper node is null");
    if (node->type != ARKUI_NODE_SWIPER) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID,
            __FUNCTION__, "Node type is not ARKUI_NODE_SWIPER");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Full implementation is null");
    auto nodeModifiers = fullImpl->getNodeModifiers();
    CHECK_NULL_RETURN_WITH_MESSAGE(nodeModifiers, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Node modifiers is null");
    auto swiperModifier = nodeModifiers->getSwiperModifier();
    CHECK_NULL_RETURN_WITH_MESSAGE(swiperModifier, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Swiper modifier is null");
    swiperModifier->callSwiperShowPrevious(node->uiNodeHandle);
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_Swiper_ShowNext(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Swiper node is null");
    if (node->type != ARKUI_NODE_SWIPER) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID,
            __FUNCTION__, "Node type is not ARKUI_NODE_SWIPER");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(fullImpl, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Full implementation is null");
    auto nodeModifiers = fullImpl->getNodeModifiers();
    CHECK_NULL_RETURN_WITH_MESSAGE(nodeModifiers, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Node modifiers is null");
    auto swiperModifier = nodeModifiers->getSwiperModifier();
    CHECK_NULL_RETURN_WITH_MESSAGE(swiperModifier, OHOS::Ace::ERROR_CODE_PARAM_INVALID,
        __FUNCTION__, "Swiper modifier is null");
    swiperModifier->callSwiperShowNext(node->uiNodeHandle);
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_ArcSwiper_ShowNext(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    CHECK_NE_RETURN(node->type, ARKUI_NODE_ARC_SWIPER, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto nodeModifiers = fullImpl->getNodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto arcSwiperModifier = nodeModifiers->getArcSwiperModifier();
    CHECK_NULL_RETURN(arcSwiperModifier, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    arcSwiperModifier->callArcSwiperShowNext(node->uiNodeHandle);
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_ArcSwiper_ShowPrevious(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    CHECK_NE_RETURN(node->type, ARKUI_NODE_ARC_SWIPER, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto nodeModifiers = fullImpl->getNodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto arcSwiperModifier = nodeModifiers->getArcSwiperModifier();
    CHECK_NULL_RETURN(arcSwiperModifier, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    arcSwiperModifier->callArcSwiperShowPrevious(node->uiNodeHandle);
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_ArcSwiper_FinishAnimation(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    CHECK_NE_RETURN(node->type, ARKUI_NODE_ARC_SWIPER, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto nodeModifiers = fullImpl->getNodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto arcSwiperModifier = nodeModifiers->getArcSwiperModifier();
    CHECK_NULL_RETURN(arcSwiperModifier, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    arcSwiperModifier->callArcSwiperFinishAnimation(node->uiNodeHandle);
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

#ifdef __cplusplus
};
#endif
