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

import { int32 } from "@koalaui/common"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeModifier, ImageAttribute, DrawableDescriptor, DrawingLattice } from "../..";
import { ResourceStr, ResourceColor } from "../../component/units"
import { Resource } from "../../../global/resource/resource";
import { CommonMethod } from "../../component/common"
import { ArkImagePeer } from "../../generated/peers/ArkImagePeer";
import { ArkCommonMethodPeer } from "../../generated/peers/ArkCommonPeer";
import { PixelMap } from "../../generated/ArkPixelMapMaterialized"
import { ArkCommonAttributeSet, modifierNullWithKey, modifierWithKey, ModifierWithKey } from "./ArkCommonModifier";
import { ImageAIOptions, ImageFit, ImageRepeat, ImageRenderMode, DynamicRangeMode, ImageInterpolation, ImageSourceSize, ImageContent, ColorFilter, DrawingColorFilter, CopyOptions, PointLightStyle, Type_ImageAttribute_onComplete_callback_event, ImageErrorCallback, ImageAnalyzerConfig, ResizableOptions, ResolutionQuality } from "../../generated";


export class ArkImageAttributeSet extends ArkCommonAttributeSet {
}

export class ImageModifier implements AttributeModifier<ImageAttribute> {

    private attributeSet: ArkImageAttributeSet = new ArkImageAttributeSet()

    get attribute(): ArkImageAttributeSet {
        return this.attributeSet;
    }

    applyNormalAttribute(instance: ImageAttribute): void { }

    applyPressedAttribute(instance: ImageAttribute): void { }

    applyFocusedAttribute(instance: ImageAttribute): void { }

    applyDisabledAttribute(instance: ImageAttribute): void { }

    applySelectedAttribute(instance: ImageAttribute): void { }
}