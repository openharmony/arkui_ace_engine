/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/image_provider/image_provider.h"

#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/image_provider/image_object.h"
#include "core/image/image_loader.h"

namespace OHOS::Ace::NG {

void ImageProvider::WrapTaskAndPostTo(
    std::function<void()>&& task, TaskExecutor::TaskType taskType, const char* taskTypeName)
{
    auto taskExecutor = Container::CurrentTaskExecutor();
    if (!taskExecutor) {
        LOGE("taskExecutor is null when try post task to %{public}s", taskTypeName);
        return;
    }
    taskExecutor->PostTask(
        [task, id = Container::CurrentId()] {
            ContainerScope scope(id);
            task();
        },
        taskType);
}

#define WRAP_TASK_AND_POST_TO(thread, threadName)                                                       \
    void ImageProvider::WrapTaskAndPostTo##threadName(std::function<void()>&& task)                     \
    {                                                                                                   \
        ImageProvider::WrapTaskAndPostTo(std::move(task), TaskExecutor::TaskType::thread, #threadName); \
    }
WRAP_TASK_AND_POST_TO(UI, UI);
WRAP_TASK_AND_POST_TO(BACKGROUND, Background);
WRAP_TASK_AND_POST_TO(IO, IO);

void ImageProvider::CreateImageObject(const ImageSourceInfo& sourceInfo, const LoadCallbacks& loadCallbacks)
{
    auto createImageObjectTask = [sourceInfo, loadCallbacks] {
        // step1: load image data
        auto imageLoader = ImageLoader::CreateImageLoader(sourceInfo);
        if (!imageLoader) {
            LOGE("Fail to create image loader. source info: %{public}s", sourceInfo.ToString().c_str());
            std::string errorMessage("Image source type not supported");
            auto notifyLoadFailTask = [errorMsg = std::move(errorMessage), sourceInfo, loadCallbacks] {
                loadCallbacks.loadFailCallback_(sourceInfo, errorMsg);
            };
            ImageProvider::WrapTaskAndPostToUI(std::move(notifyLoadFailTask));
            return;
        }
        RefPtr<ImageData> data =
            imageLoader->GetImageData(sourceInfo, WeakClaim(RawPtr(NG::PipelineContext::GetCurrentContext())));

        // step2: make codec to determine which ImageObject to create
        auto encodedInfo = ImageEncodedInfo::CreateImageEncodedInfo(data);
        if (!encodedInfo) {
            LOGE("Fail to make encoded info. source info: %{public}s", sourceInfo.ToString().c_str());
            std::string errorMessage("Image data is broken.");
            auto notifyLoadFailTask = [errorMsg = std::move(errorMessage), sourceInfo, loadCallbacks] {
                loadCallbacks.loadFailCallback_(sourceInfo, errorMsg);
            };
            ImageProvider::WrapTaskAndPostToUI(std::move(notifyLoadFailTask));
            return;
        }
        // step3: build ImageObject accroding to encoded info
        RefPtr<ImageObject> imageObj = nullptr;
        do {
            if (sourceInfo.IsSvg()) {
                // TODO: create SvgImageObject
                break;
            }
            if (encodedInfo->GetFrameCount() == 1) {
                imageObj = MakeRefPtr<NG::StaticImageObject>(
                    sourceInfo, encodedInfo->GetImageSize(), encodedInfo->GetFrameCount(), data);
                break;
            }
            // TODO: create AnimatedImageObject
        } while (0);
        auto notifyDataReadyTask = [loadCallbacks, imageObj, sourceInfo] {
            loadCallbacks.dataReadyCallback_(sourceInfo, imageObj);
        };
        ImageProvider::WrapTaskAndPostToUI(std::move(notifyDataReadyTask));
    };
    ImageProvider::WrapTaskAndPostToBackground(std::move(createImageObjectTask));
}

} // namespace OHOS::Ace::NG