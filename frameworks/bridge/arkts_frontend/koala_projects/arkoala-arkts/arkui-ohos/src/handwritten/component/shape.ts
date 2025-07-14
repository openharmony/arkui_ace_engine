/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import { runtimeType, RuntimeType } from "@koalaui/interop"
import { PixelMap } from "#external"
import { ArkUIAniModule } from "arkui.ani"

function hookSetShapeOptions(component: ArkShapeComponent, value?: PixelMap): void {
    const value_casted = value as (PixelMap | undefined);
    const value_type = runtimeType(value)
    if ((RuntimeType.UNDEFINED) != (value_type)) {
        const pixelMap = value_casted as PixelMap;
        const peer = component.getPeer();
        if (peer !== undefined) {
            ArkUIAniModule._Shape_Transfer_PixelMap(peer.getPeerPtr() as KPointer, pixelMap);
        }
    } else {
        component.getPeer()?.setShapeOptions1Attribute()
    }
}
