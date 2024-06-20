/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components/video/resource/ext_texture.h"

#include "base/log/log.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {
const char TEXTURE_ERRORCODE_CREATEFAIL[] = "error_texture_000001";
const char TEXTURE_ERRORMSG_CREATEFAIL[] = "Unable to initialize texture.";

const char TEXTURE_METHOD_REFRESH[] = "markTextureAvailable";

const char SET_TEXTURE_SIZE[] = "setTextureSize";
const char TEXTURE_HEIGHT[] = "textureHeight";
const char TEXTURE_ID[] = "textureId";
const char IS_ATTACH[] = "isAttach";
const char TEXTURE_WIDTH[] = "textureWidth";
const char INSTANCE_ID[] = "instanceId";
const char ATTACH_TO_GLCONTEXT[] = "attachToGLContext";
const char UPDATE_TEXTURE_IMAGE[] = "updateTextureImage";

ExtTexture::~ExtTexture()
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    auto resRegister = context->GetPlatformResRegister();
    CHECK_NULL_VOID(resRegister);
    auto platformTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::PLATFORM);
    if (platformTaskExecutor.IsRunOnCurrentThread()) {
        resRegister->UnregisterEvent(MakeEventHash(TEXTURE_METHOD_REFRESH));
    } else {
        WeakPtr<PlatformResRegister> weak = resRegister;
        platformTaskExecutor.PostTask([eventHash = MakeEventHash(TEXTURE_METHOD_REFRESH), weak] {
            auto resRegister = weak.Upgrade();
            CHECK_NULL_VOID(resRegister);
            resRegister->UnregisterEvent(eventHash);
        }, "ArkUIVideoExtTextureUnregisterEvent");
    }
}

void ExtTexture::Create(const std::function<void(int64_t)>& onCreate)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);

    auto platformTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::PLATFORM);
    platformTaskExecutor.PostTask([weak = WeakClaim(this), onCreate] {
        auto texture = weak.Upgrade();
        if (texture) {
            texture->CreateTexture(onCreate);
        }
    }, "ArkUIVideoCreateExtTexture");
}

void ExtTexture::CreateTexture(const std::function<void(int64_t)>& onCreate)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    auto resRegister = context->GetPlatformResRegister();
    CHECK_NULL_VOID(resRegister);
    id_ = resRegister->CreateResource(type_, PARAM_NONE);
    if (id_ == INVALID_ID) {
        if (onError_) {
            onError_(TEXTURE_ERRORCODE_CREATEFAIL, TEXTURE_ERRORMSG_CREATEFAIL);
        }
        return;
    }
    hash_ = MakeResourceHash();
    resRegister->RegisterEvent(
        MakeEventHash(TEXTURE_METHOD_REFRESH), [weak = WeakClaim(this)](const std::string& param) {
            auto texture = weak.Upgrade();
            if (texture) {
                texture->OnRefresh(param);
            }
        });

    if (onCreate) {
        onCreate(id_);
    }
    OnSurfaceCreated();
}

void ExtTexture::SetSize(int64_t textureId, int32_t textureWidth, int32_t textureHeight)
{
    std::stringstream paramStream;
    paramStream << TEXTURE_ID << PARAM_EQUALS << textureId << PARAM_AND
                << TEXTURE_WIDTH << PARAM_EQUALS << textureWidth << PARAM_AND
                << TEXTURE_HEIGHT << PARAM_EQUALS << textureHeight;
    std::string param = paramStream.str();
    CallResRegisterMethod(MakeMethodHash(SET_TEXTURE_SIZE), param);
}

void ExtTexture::OnRefresh(const std::string& param)
{
    instanceId_ = GetIntParam(param, INSTANCE_ID);
    textureId_ = GetIntParam(param, TEXTURE_ID);
    if (onTextureRefresh_) {
        onTextureRefresh_(instanceId_, textureId_);
    }
}

void ExtTexture::OnSurfaceCreated()
{
    if (onSurfaceCreated_) {
        onSurfaceCreated_();
    }
}

void ExtTexture::OnSurfaceChanged(int32_t width, int32_t height)
{
    LOGI("OnSurfaceChanged. width: %{public}d height: %{public}d", width, height);
    if (onSurfaceChanged_) {
        onSurfaceChanged_(width, height);
    }
}

void ExtTexture::AttachToGLContext(int64_t textureId, bool isAttach)
{
    std::stringstream paramStream;
    paramStream << TEXTURE_ID << PARAM_EQUALS << textureId << PARAM_AND
        << IS_ATTACH << PARAM_EQUALS << (isAttach ? "1" : "0");
    std::string param = paramStream.str();
    CallSyncResRegisterMethod(MakeMethodHash(ATTACH_TO_GLCONTEXT), param);
}

void ExtTexture::UpdateTextureImage(std::vector<float>& matrix)
{
    CallSyncResRegisterMethod(MakeMethodHash(UPDATE_TEXTURE_IMAGE), PARAM_NONE,
        [this, &matrix](std::string& result) mutable {
            GetFloatArrayParam(result, "transform", matrix);
    });
}
} // namespace OHOS::Ace