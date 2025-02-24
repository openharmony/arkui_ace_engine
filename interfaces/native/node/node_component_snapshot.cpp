/*c
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

#include "node_component_snapshot.h"

#include "node/node_model.h"
#include "pixelmap_native_impl.h"

#include "base/utils/utils.h"
#include "frameworks/base/error/error_code.h"
#include "frameworks/core/components_ng/base/frame_node.h"

#ifdef __cplusplus
extern "C" {
#endif

ArkUI_SnapshotOptions* OH_ArkUI_CreateSnapshotOptions()
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, nullptr);
    auto snapshotOptions = impl->getSnapshotAPI()->createSnapshotOptions();
    return reinterpret_cast<ArkUI_SnapshotOptions*>(snapshotOptions);
}

void OH_ArkUI_DestroySnapshotOptions(ArkUI_SnapshotOptions* snapshotOptions)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_VOID(impl);
    auto options = reinterpret_cast<ArkUISnapshotOptions*>(snapshotOptions);
    impl->getSnapshotAPI()->destroySnapshotOptions(options);
}

int32_t OH_ArkUI_SnapshotOptions_SetScale(ArkUI_SnapshotOptions* snapshotOptions, float scale)
{
    CHECK_NULL_RETURN(snapshotOptions, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    if (!OHOS::Ace::GreatNotEqual(scale, 0.0)) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_INTERNAL_ERROR);
    auto result = impl->getSnapshotAPI()->snapshotOptionsSetScale(
        reinterpret_cast<ArkUISnapshotOptions*>(snapshotOptions), scale);
    return result;
}

int32_t OH_ArkUI_GetNodeSnapshot(
    ArkUI_NodeHandle node, ArkUI_SnapshotOptions* snapshotOptions, OH_PixelmapNative** pixelmap)
{
    CHECK_NULL_RETURN(node, ARKUI_ERROR_CODE_PARAM_INVALID);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_INTERNAL_ERROR);
    auto options = reinterpret_cast<ArkUISnapshotOptions*>(snapshotOptions);
    std::shared_ptr<OHOS::Media::PixelMap> tmpPixel;
    auto result = impl->getSnapshotAPI()->getSyncSnapshot(node->uiNodeHandle, options, &tmpPixel);
    switch (result) {
        case OHOS::Ace::ERROR_CODE_PARAM_INVALID:
            return ARKUI_ERROR_CODE_PARAM_INVALID;
        case OHOS::Ace::ERROR_CODE_NO_ERROR:
            if (tmpPixel) {
                *pixelmap = new (std::nothrow) OH_PixelmapNative(tmpPixel);
                return ARKUI_ERROR_CODE_NO_ERROR;
            }
            return ARKUI_ERROR_CODE_INTERNAL_ERROR;
        case OHOS::Ace::ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT:
            return ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT;
        default:
            return ARKUI_ERROR_CODE_INTERNAL_ERROR;
    }
}

#ifdef __cplusplus
};
#endif