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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_image_animator_ffi.h"

#include "cj_lambda.h"
#include "core/components_ng/pattern/image_animator/image_animator_model.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {

const std::vector<Animator::Status> ANIMATOR_STATUS = { Animator::Status::IDLE, Animator::Status::RUNNING,
    Animator::Status::PAUSED, Animator::Status::STOPPED };
const std::vector<FillMode> FILL_MODES = { FillMode::NONE, FillMode::FORWARDS, FillMode::BACKWARDS, FillMode::BOTH };

void ParseImages(const FfiImage& ffiImages, ImageProperties& imageProperties)
{
    imageProperties.src = ffiImages.src;
    imageProperties.duration = ffiImages.duration;

    Dimension widthDime(ffiImages.width, static_cast<DimensionUnit>(ffiImages.widthUnit));
    Dimension heightDime(ffiImages.height, static_cast<DimensionUnit>(ffiImages.heightUnit));
    Dimension topDime(ffiImages.top, static_cast<DimensionUnit>(ffiImages.topUnit));
    Dimension leftDime(ffiImages.left, static_cast<DimensionUnit>(ffiImages.leftUnit));

    imageProperties.width = widthDime;
    imageProperties.height = heightDime;
    imageProperties.top = topDime;
    imageProperties.left = leftDime;
}

} // namespace

extern "C" {
void FfiOHOSAceFrameworkImageAnimatorCreate()
{
    ImageAnimatorModel::GetInstance()->Create();
}

void FfiOHOSAceFrameworkImageAnimatorSetImages(VectorFfiImageHandle vecContent)
{
    auto imagesVec = *reinterpret_cast<std::vector<FfiImage>*>(vecContent);
    std::vector<ImageProperties> images;
    for (size_t i = 0; i< imagesVec.size(); ++i) {
        ImageProperties imageProperties;
        ParseImages(imagesVec[i], imageProperties);
        images.push_back(imageProperties);
    }
    ImageAnimatorModel::GetInstance()->SetImages(std::move(images));
}

void FfiOHOSAceFrameworkImageAnimatorSetState(int32_t state)
{
    if (!Utils::CheckParamsValid(state, ANIMATOR_STATUS.size())) {
        LOGE("invalid value for animator state");
        return;
    }
    ImageAnimatorModel::GetInstance()->SetState(static_cast<int32_t>(ANIMATOR_STATUS[state]));
}

void FfiOHOSAceFrameworkImageAnimatorSetDuration(int32_t duration)
{
    ImageAnimatorModel::GetInstance()->SetDuration(duration);
}

void FfiOHOSAceFrameworkImageAnimatorSetReverse(bool isReverse)
{
    ImageAnimatorModel::GetInstance()->SetIsReverse(isReverse);
}

void FfiOHOSAceFrameworkImageAnimatorSetFixedSize(bool fixedSize)
{
    ImageAnimatorModel::GetInstance()->SetFixedSize(fixedSize);
}

void FfiOHOSAceFrameworkImageAnimatorSetPreDecode(int32_t preDecode)
{
    ImageAnimatorModel::GetInstance()->SetPreDecode(preDecode);
}

void FfiOHOSAceFrameworkImageAnimatorSetFillMode(int32_t mode)
{
    if (!Utils::CheckParamsValid(mode, FILL_MODES.size())) {
        LOGE("invalid value for animator fillMode");
        return;
    }
    ImageAnimatorModel::GetInstance()->SetFillMode(static_cast<int32_t>(FILL_MODES[mode]));
}

void FfiOHOSAceFrameworkImageAnimatorSetIterations(int32_t iteration)
{
    ImageAnimatorModel::GetInstance()->SetIteration(iteration);
}

void FfiOHOSAceFrameworkImageAnimatorOnStart(void (*callback)())
{
    ImageAnimatorModel::GetInstance()->SetOnStart(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkImageAnimatorOnPause(void (*callback)())
{
    ImageAnimatorModel::GetInstance()->SetOnPause(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkImageAnimatorOnRepeat(void (*callback)())
{
    ImageAnimatorModel::GetInstance()->SetOnRepeat(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkImageAnimatorOnCancel(void (*callback)())
{
    ImageAnimatorModel::GetInstance()->SetOnCancel(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkImageAnimatorOnFinish(void (*callback)())
{
    ImageAnimatorModel::GetInstance()->SetOnFinish(CJLambda::Create(callback));
}

VectorFfiImageHandle FfiCJCreateVectorFfiImage(int64_t size)
{
    LOGE("Create FfiImage Vector");
    return new std::vector<FfiImage>(size);
}

void FfiCJVectorFfiImageSetElement(VectorFfiImageHandle vec, int64_t index, FfiImage image)
{
    LOGI("FfiImage Vector Set Element");
    auto actualVec = reinterpret_cast<std::vector<FfiImage>*>(vec);
    (*actualVec)[index] = image;
    LOGI("FfiImage Vector Set Element Success");
}

void FfiCJVectorFfiImageDelete(VectorFfiImageHandle vec)
{
    auto actualVec = reinterpret_cast<std::vector<FfiImage>*>(vec);
    delete actualVec;
}
}
