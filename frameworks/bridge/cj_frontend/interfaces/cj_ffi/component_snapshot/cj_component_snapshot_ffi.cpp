/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/interfaces/cj_ffi/component_snapshot/cj_component_snapshot_ffi.h"
#include "cj_lambda.h"
#include "ffi_remote_data.h"
#include "pixel_map_impl.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/render/adapter/component_snapshot.h"
#include "core/components_ng/render/snapshot_param.h"
#include "core/components_ng/base/view_stack_model.h"

using namespace OHOS;
using namespace OHOS::Ace;

namespace {
    auto GetSnapshotCallback(void (*callback)(NativeOptionInt32 errCode, NativeOptionInt64 pixelMapId))
    {
        auto snapshotCallback = [
            ffiCallback = CJLambda::Create(callback)
        ](
            std::shared_ptr<Media::PixelMap> ptr,
            int32_t code,
            std::function<void()> finishCallback
        ) {
            NativeOptionInt32 errCode = {true, ERROR_CODE_INTERNAL_ERROR};
            NativeOptionInt64 pixelMapId = {false, -1};

            if (code == ERROR_CODE_NO_ERROR) {
                auto nativeImage = FFI::FFIData::Create<Media::PixelMapImpl>(move(ptr));
                pixelMapId = {true, nativeImage->GetID()};
                errCode = {false, -1};
            } else {
                errCode = {true, code};
            }

            ffiCallback(errCode, pixelMapId);

            if (finishCallback) {
                finishCallback();
            }
        };

        return snapshotCallback;
    }
} //namespace

extern "C" {
    void FfiOHOSAceFrameworkComponentSnapshotGet(
        const char* id,
        void (*callback)(NativeOptionInt32 errCode, NativeOptionInt64 pixelMapId),
        CSnapshotOptions options)
    {
#ifdef ENABLE_ROSEN_BACKEND
        NG::ComponentSnapshot::Get(
            std::string(id),
            GetSnapshotCallback(callback),
            NG::SnapshotOptions(options.scale, options.waitUntilRenderFinished));
#endif
    }

    void FfiOHOSAceFrameworkComponentSnapshotCreate(
        void (*builder)(),
        void (*callback)(NativeOptionInt32 errCode, NativeOptionInt64 pixelMapId),
        int32_t delay,
        bool checkImageStatus,
        CSnapshotOptions options)
    {
#ifdef ENABLE_ROSEN_BACKEND
        auto buildFunc = CJLambda::Create(builder);
        RefPtr<AceType> customNode;
        {
            ViewStackModel::GetInstance()->NewScope();
            buildFunc();
            customNode = ViewStackModel::GetInstance()->Finish();
        }
        auto param = NG::SnapshotParam(
            delay,
            checkImageStatus,
            NG::SnapshotOptions(options.scale, options.waitUntilRenderFinished));
        
        NG::ComponentSnapshot::Create(customNode, GetSnapshotCallback(callback), true, param);
#endif
    }

    CSnapshotGetSyncRet FfiOHOSAceFrameworkComponentSnapshotGetSync(
        const char* id,
        CSnapshotOptions options)
    {
#ifdef ENABLE_ROSEN_BACKEND
        auto pair = NG::ComponentSnapshot::GetSync(
            std::string(id),
            NG::SnapshotOptions(options.scale, options.waitUntilRenderFinished));
        if (pair.first == ERROR_CODE_NO_ERROR) {
            auto nativeImage = FFI::FFIData::Create<Media::PixelMapImpl>(move(pair.second));
            return {ERROR_CODE_NO_ERROR, nativeImage->GetID()};
        }
        if (pair.first == ERROR_CODE_INTERNAL_ERROR) {
            LOGE("ComponentSnapshot GetSync internal error! Error code: %{public}" PRId32, pair.first);
            return {ERROR_CODE_INTERNAL_ERROR, 0};
        }
        if (pair.first == ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT) {
            LOGE("ComponentSnapshot GetSync timeout! Error code: %{public}" PRId32, pair.first);
            return {ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT, 0};
        }
        LOGE("ComponentSnapshot GetSync unknown error!");
        return {ERROR_CODE_INTERNAL_ERROR, 0};
#endif
        LOGE("ComponentSnapshot GetSync error! ComponentSnapshot is not supported.");
        return {ERROR_CODE_INTERNAL_ERROR, 0};
    }
} //extern "C"