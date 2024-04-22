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

#include "node/animate_impl.h"

#include "node/node_model.h"

#include "base/error/error_code.h"

namespace OHOS::Ace::AnimateModel {

int32_t AnimateTo(ArkUI_ContextHandle context, ArkUI_AnimateOption* option, ArkUI_ContextCallback* update,
    ArkUI_AnimateCompleteCallback* complete)
{
    auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (!impl || !context || !option || !update || !update->callback) {
        return ERROR_CODE_PARAM_INVALID;
    }

    ArkUIAnimateOption animateOption {};
    animateOption.duration = option->duration;
    animateOption.tempo = option->tempo;
    animateOption.curve = static_cast<ArkUI_Int32>(option->curve);
    animateOption.delay = option->delay;
    animateOption.iterations = option->iterations;
    animateOption.playMode = static_cast<ArkUI_Int32>(option->playMode);
    if (option->expectedFrameRateRange) {
        animateOption.expectedFrameRateRange =
            reinterpret_cast<ArkUIExpectedFrameRateRange*>(option->expectedFrameRateRange);
    }

    if (complete && complete->callback) {
        animateOption.onFinishCallback = reinterpret_cast<void*>(complete->callback);
    }

    if (complete && complete->userData) {
        animateOption.user = complete->userData;
    }
    auto finishCallbackType = static_cast<ArkUI_Int32>(ARKUI_FINISH_CALLBACK_REMOVED);
    if (complete && complete->type == ARKUI_FINISH_CALLBACK_LOGICALLY) {
        finishCallbackType = static_cast<ArkUI_Int32>(ARKUI_FINISH_CALLBACK_LOGICALLY);
    }
    animateOption.finishCallbackType = finishCallbackType;

    impl->getAnimation()->animateTo(reinterpret_cast<ArkUIContext*>(context), animateOption,
        reinterpret_cast<void*>(update->callback), update->userData);
    return ERROR_CODE_NO_ERROR;
}

} // namespace OHOS::Ace::AnimateModel