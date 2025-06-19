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

import { PixelMap } from "../../generated/ArkPixelMapMaterialized"
import { InteropNativeModule } from "@koalaui/interop";
import { ResourceStr, ResourceColor } from "../../component/units"
import { Resource } from "../../../global/resource/resource";
import { ColorFilter, CopyOptions, DrawingColorFilter, DynamicRangeMode, ImageAIOptions, ImageContent, DrawableDescriptor, ImageAnalyzerConfig, ImageAttribute, ImageErrorCallback, ImageFit, ImageInterpolation, ImageRenderMode, ImageRepeat, ImageSourceSize, PointLightStyle, ResizableOptions, ResolutionQuality, Type_ImageAttribute_onComplete_callback_event } from "../../generated";
import { ArkImagePeer } from "../../generated/peers/ArkImagePeer";
import { ArkBaseNode } from "./ArkBaseNode";

export class ArkImageNode extends ArkBaseNode {

    constructParam(...param: Object[]): this {
        let peerNode = this.getPeer() as ArkImagePeer
        peerNode.setImageOptions0Attribute(param[0] as PixelMap | ResourceStr | DrawableDescriptor)
        return this
    }

}