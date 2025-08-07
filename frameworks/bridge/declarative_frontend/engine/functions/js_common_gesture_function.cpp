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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_common_gesture_function.h"

namespace OHOS::Ace::Framework {

JSRef<JSObject> JsCommonGestureFunction::GetTapLocation(const FingerInfo& fingerInfo)
{
    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    JSRef<JSObject> tapLocation = objectTemplate->NewInstance();
    const OHOS::Ace::Offset& localOffset = fingerInfo.localLocation_;
    const OHOS::Ace::Offset& globalOffset = fingerInfo.globalLocation_;
    const OHOS::Ace::Offset& screenOffset = fingerInfo.screenLocation_;
    tapLocation->SetProperty<double>("windowX", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    tapLocation->SetProperty<double>("windowY", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));
    tapLocation->SetProperty<double>("x", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX()));
    tapLocation->SetProperty<double>("y", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY()));
    tapLocation->SetProperty<double>("displayX", PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetX()));
    tapLocation->SetProperty<double>("displayY", PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetY()));

    return tapLocation;
}

} // namespace OHOS::Ace::Framework
