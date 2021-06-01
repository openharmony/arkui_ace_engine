/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONTAINER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONTAINER_H

#include "base/memory/ace_type.h"
#include "base/resource/asset_manager.h"
#include "base/resource/shared_image_manager.h"
#include "base/thread/task_executor.h"
#include "base/utils/noncopyable.h"
#include "core/common/frontend.h"
#include "core/common/platform_res_register.h"
#include "core/common/window.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace {

using PageTask = std::function<void()>;
using TouchEventCallback = std::function<void(const TouchPoint&)>;
using KeyEventCallback = std::function<bool(const KeyEvent&)>;
using MouseEventCallback = std::function<void(const MouseEvent&)>;
using RotationEventCallBack = std::function<bool(const RotationEvent&)>;
using CardViewPositionCallBack = std::function<void(int id, float offsetX, float offsetY)>;

class Container : public virtual AceType {
    DECLARE_ACE_TYPE(Container, AceType);

public:
    Container() = default;
    ~Container() override = default;

    // Get the instance id of this container
    virtual int32_t GetInstanceId() const = 0;

    // Get the package path of this container
    virtual std::string GetPackagePath() const
    {
        return "";
    };

    // Get the ability name of this container
    virtual std::string GetHostClassName() const = 0;

    // Get the frontend of container
    virtual RefPtr<Frontend> GetFrontend() const = 0;

    // Get task executor.
    virtual RefPtr<TaskExecutor> GetTaskExecutor() const = 0;

    // Get assert manager.
    virtual RefPtr<AssetManager> GetAssetManager() const = 0;

    // Get platform resource register.
    virtual RefPtr<PlatformResRegister> GetPlatformResRegister() const = 0;

    // Get the pipelineContext of container.
    virtual RefPtr<PipelineContext> GetPipelineContext() const = 0;

    // Dump container.
    virtual bool Dump(const std::vector<std::string>& params) = 0;

private:
    ACE_DISALLOW_COPY_AND_MOVE(Container);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONTAINER_H
