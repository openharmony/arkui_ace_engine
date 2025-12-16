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

#include "component_snapshot_ani_modifier.h"

#include "base/log/log.h"
#include "core/common/ace_engine.h"
#include "frameworks/core/interfaces/native/ani/frame_node_peer_impl.h"
#include "frameworks/core/components_ng/render/adapter/component_snapshot.h"

namespace OHOS::Ace::NG {

struct SnapshotAsyncCtx {
    ani_env* env = nullptr;
    ani_resolver deferred = nullptr;
    ani_object callbackRef = nullptr;
    ani_object destroyCallbackRef = nullptr;
    std::shared_ptr<void> pixelMap = nullptr;
    int32_t errCode = -1;
    std::function<void(std::shared_ptr<ArkUIComponentSnapshotAsync>)> callBackJsFunction;
};

void ConvertSnapshotParam(SnapshotParam& snapShotParam, const ArkUISnapshotParam& param)
{
    snapShotParam.delay = param.delay;
    snapShotParam.checkImageStatus = param.checkImageStatus;
    snapShotParam.options.scale = param.options.scale;
    snapShotParam.options.regionMode = static_cast<SnapshotRegionMode>(param.options.regionMode);
    snapShotParam.options.waitUntilRenderFinished = param.options.waitUntilRenderFinished;
    snapShotParam.options.snapshotRegion.bottom = param.options.snapshotRegion.bottom;
    snapShotParam.options.snapshotRegion.top = param.options.snapshotRegion.top;
    snapShotParam.options.snapshotRegion.end = param.options.snapshotRegion.end;
    snapShotParam.options.snapshotRegion.start = param.options.snapshotRegion.start;
    snapShotParam.options.colorSpaceModeOptions.colorSpaceMode = param.options.colorSpaceModeOptions.colorSpaceMode;
    snapShotParam.options.colorSpaceModeOptions.isAuto = param.options.colorSpaceModeOptions.isAuto;
    snapShotParam.options.dynamicRangeModeOptions.dynamicRangeMode =
        param.options.dynamicRangeModeOptions.dynamicRangeMode;
    snapShotParam.options.dynamicRangeModeOptions.isAuto = param.options.dynamicRangeModeOptions.isAuto;
}

void ConvertSnapShotAsync(
    std::shared_ptr<SnapshotAsyncCtx> asyncCtx, const ArkUIComponentSnapshotAsync& snapShotAsyncCtx)
{
    asyncCtx->env = snapShotAsyncCtx.env;
    asyncCtx->deferred = snapShotAsyncCtx.deferred;
    asyncCtx->callbackRef = snapShotAsyncCtx.callbackRef;
    asyncCtx->destroyCallbackRef = snapShotAsyncCtx.destroyCallbackRef;
    asyncCtx->callBackJsFunction = snapShotAsyncCtx.callBackJsFunction;
}

void prepareDataForCallback(
    std::shared_ptr<SnapshotAsyncCtx> asyncCtx, std::shared_ptr<ArkUIComponentSnapshotAsync> snapShotAsyncCtx)
{
    snapShotAsyncCtx->env = asyncCtx->env;
    snapShotAsyncCtx->errCode = asyncCtx->errCode;
    snapShotAsyncCtx->deferred = asyncCtx->deferred;
    snapShotAsyncCtx->callbackRef = asyncCtx->callbackRef;
    snapShotAsyncCtx->destroyCallbackRef = asyncCtx->destroyCallbackRef;
    snapShotAsyncCtx->pixelMap = asyncCtx->pixelMap;
}

void OnComplete(std::shared_ptr<SnapshotAsyncCtx> asyncCtx, std::function<void()> finishCallback)
{
    CHECK_NULL_VOID(asyncCtx);
    auto instanceId = OHOS::Ace::Container::CurrentIdSafely();
    auto container = OHOS::Ace::AceEngine::Get().GetContainer(instanceId);
    if (!container) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "container is null. %{public}d", instanceId);
        return;
    }
    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_COMPONENT_SNAPSHOT, "taskExecutor is null.");
        return;
    }
    
    auto callbackAsyncCtx = std::make_shared<ArkUIComponentSnapshotAsync>();
    prepareDataForCallback(asyncCtx, callbackAsyncCtx);
    taskExecutor->PostTask(
        [asyncCtx, callbackAsyncCtx, finishCallback]() {
            CHECK_NULL_VOID(asyncCtx);
            asyncCtx->callBackJsFunction(callbackAsyncCtx);
            if (finishCallback) {
                finishCallback();
            }
        },
        OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIComponentSnapshotComplete");
}

void CreateFromBuilder(
    ArkUINodeHandle node, const ArkUIComponentSnapshotAsync& snapShotAsyncCtx, const ArkUISnapshotParam& param)
{
    SnapshotParam snapShotParam;
    ConvertSnapshotParam(snapShotParam, param);
    auto asyncCtx = std::make_shared<SnapshotAsyncCtx>();
    ConvertSnapShotAsync(asyncCtx, snapShotAsyncCtx);
    CHECK_NULL_VOID(node);
    auto uinode = AceType::Claim(reinterpret_cast<UINode*>(node));
    CHECK_NULL_VOID(uinode);
    auto jsCallback = [asyncCtx](
        std::shared_ptr<OHOS::Media::PixelMap> pixmap, int32_t errCode, std::function<void()> finishCallback) {
        CHECK_NULL_VOID(asyncCtx);
        asyncCtx->pixelMap = std::move(pixmap);
        asyncCtx->errCode = errCode;
        OnComplete(asyncCtx, finishCallback);
    };
#ifdef ENABLE_ROSEN_BACKEND
    ComponentSnapshot::Create(uinode, std::move(jsCallback), true, snapShotParam);
#endif
}

void CreateFromComponent(
    ArkUINodeHandle node, const ArkUIComponentSnapshotAsync& snapShotAsyncCtx, const ArkUISnapshotParam& param)
{
    SnapshotParam snapShotParam;
    ConvertSnapshotParam(snapShotParam, param);
    auto asyncCtx = std::make_shared<SnapshotAsyncCtx>();
    ConvertSnapShotAsync(asyncCtx, snapShotAsyncCtx);
    CHECK_NULL_VOID(node);
    auto uinode = FrameNodePeer::GetFrameNodeByPeer(reinterpret_cast<FrameNodePeer*>(node));
    CHECK_NULL_VOID(uinode);
    auto jsCallback = [asyncCtx](
        std::shared_ptr<OHOS::Media::PixelMap> pixmap, int32_t errCode, std::function<void()> finishCallback) {
        CHECK_NULL_VOID(asyncCtx);
        asyncCtx->pixelMap = std::move(pixmap);
        asyncCtx->errCode = errCode;
        OnComplete(asyncCtx, finishCallback);
    };
#ifdef ENABLE_ROSEN_BACKEND
    ComponentSnapshot::Create(uinode, std::move(jsCallback), true, snapShotParam);
#endif
}

const ArkUIAniComponentSnapshotModifier* GetComponentSnapshotAniModifier()
{
    static const ArkUIAniComponentSnapshotModifier impl = {
        .createFromBuilder = OHOS::Ace::NG::CreateFromBuilder,
        .createFromComponent = OHOS::Ace::NG::CreateFromComponent,
    };
    return &impl;
}
} // namespace OHOS::Ace::NG