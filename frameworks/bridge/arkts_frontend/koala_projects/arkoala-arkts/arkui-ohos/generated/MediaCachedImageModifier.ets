/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { ImageModifier } from "./ImageModifier"
import { CommonMethodModifier } from "./CommonMethodModifier"
import { AttributeModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkMediaCachedImagePeer, MediaCachedImageAttribute } from "./component/mediaCachedImage"
import { int32 } from "@koalaui/common"
import { ImageAttribute } from "./component/image"
import { CommonMethod } from "./component/common"
export class MediaCachedImageModifier extends ImageModifier implements MediaCachedImageAttribute,AttributeModifier<MediaCachedImageAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: MediaCachedImageAttribute): void { }
    applyPressedAttribute(instance: MediaCachedImageAttribute): void { }
    applyFocusedAttribute(instance: MediaCachedImageAttribute): void { }
    applyDisabledAttribute(instance: MediaCachedImageAttribute): void { }
    applySelectedAttribute(instance: MediaCachedImageAttribute): void { }
    applyModifierPatch(node: PeerNode): void {
        super.applyModifierPatch(node)
        const peer = node as ArkMediaCachedImagePeer;
    }
    mergeModifier(modifier: MediaCachedImageModifier): void {
        super.mergeModifier(modifier)
    }
    public attributeModifier(value: AttributeModifier<MediaCachedImageAttribute> | AttributeModifier<ImageAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
