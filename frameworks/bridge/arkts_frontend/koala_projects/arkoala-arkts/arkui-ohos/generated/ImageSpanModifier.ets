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

import { CommonMethod, PixelMap } from './component/common'
import { TextBackgroundStyle, BaseSpan } from './component/span'
import { LengthMetrics as arkui_Graphics_LengthMetrics } from '@arkui.Graphics'
import { BaseSpanModifier } from './BaseSpanModifier'
import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeModifier, extractors } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkImageSpanPeer, ImageCompleteCallback, ImageLoadResult, ImageSpanAttribute } from './component/imageSpan'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { ImageSpanAlignment, ImageFit } from './component/enums'
import { ColorFilter } from './component/units'
import { DrawingColorFilter, ImageErrorCallback, ImageError } from './component/image'
import { default as drawing } from '@ohos.graphics.drawing'
import { default as image } from '@ohos.multimedia.image'
export class ImageSpanModifier extends CommonMethodModifier implements ImageSpanAttribute,AttributeModifier<ImageSpanAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        super();
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: ImageSpanAttribute): void { }
    applyPressedAttribute(instance: ImageSpanAttribute): void { }
    applyFocusedAttribute(instance: ImageSpanAttribute): void { }
    applyDisabledAttribute(instance: ImageSpanAttribute): void { }
    applySelectedAttribute(instance: ImageSpanAttribute): void { }
    public _verticalAlign_0_0value?: ImageSpanAlignment | undefined
    public _colorFilter_0_0value?: ColorFilter | DrawingColorFilter | undefined
    public _objectFit_0_0value?: ImageFit | undefined
    public _onComplete_0_0value?: ImageCompleteCallback | undefined
    public _onError_0_0value?: ImageErrorCallback | undefined
    public _alt_0_0value?: PixelMap | undefined
    public _textBackgroundStyle_0_0value?: TextBackgroundStyle | undefined
    public _baselineOffset_0_0value?: arkui_Graphics_LengthMetrics | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkImageSpanPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkImageSpanPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setVerticalAlignAttribute((this._verticalAlign_0_0value as ImageSpanAlignment | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setVerticalAlignAttribute((undefined as ImageSpanAlignment | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setColorFilterAttribute((this._colorFilter_0_0value as ColorFilter | DrawingColorFilter | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setColorFilterAttribute((undefined as ColorFilter | DrawingColorFilter | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setObjectFitAttribute((this._objectFit_0_0value as ImageFit | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setObjectFitAttribute((undefined as ImageFit | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setOnCompleteAttribute((this._onComplete_0_0value as ImageCompleteCallback | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setOnCompleteAttribute((undefined as ImageCompleteCallback | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setOnErrorAttribute((this._onError_0_0value as ImageErrorCallback | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setOnErrorAttribute((undefined as ImageErrorCallback | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setAltAttribute((this._alt_0_0value as PixelMap | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setAltAttribute((undefined as PixelMap | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setTextBackgroundStyleAttribute((this._textBackgroundStyle_0_0value as TextBackgroundStyle | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setTextBackgroundStyleAttribute((undefined as TextBackgroundStyle | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setBaselineOffsetAttribute((this._baselineOffset_0_0value as arkui_Graphics_LengthMetrics | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setBaselineOffsetAttribute((undefined as arkui_Graphics_LengthMetrics | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ImageSpanModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: ImageSpanModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.verticalAlign(modifier._verticalAlign_0_0value);
                    break;
                }
                default: {
                    this.verticalAlign((undefined as ImageSpanAlignment | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.colorFilter(modifier._colorFilter_0_0value);
                    break;
                }
                default: {
                    this.colorFilter((undefined as ColorFilter | DrawingColorFilter | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.objectFit(modifier._objectFit_0_0value);
                    break;
                }
                default: {
                    this.objectFit((undefined as ImageFit | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.onComplete(modifier._onComplete_0_0value);
                    break;
                }
                default: {
                    this.onComplete((undefined as ImageCompleteCallback | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.onError(modifier._onError_0_0value);
                    break;
                }
                default: {
                    this.onError((undefined as ImageErrorCallback | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.alt(modifier._alt_0_0value);
                    break;
                }
                default: {
                    this.alt((undefined as PixelMap | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.textBackgroundStyle(modifier._textBackgroundStyle_0_0value);
                    break;
                }
                default: {
                    this.textBackgroundStyle((undefined as TextBackgroundStyle | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.baselineOffset(modifier._baselineOffset_0_0value);
                    break;
                }
                default: {
                    this.baselineOffset((undefined as arkui_Graphics_LengthMetrics | undefined));
                }
            }
        }
    }
    verticalAlign(value: ImageSpanAlignment | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._verticalAlign_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    colorFilter(value: ColorFilter | DrawingColorFilter | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._colorFilter_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    objectFit(value: ImageFit | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._objectFit_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    onComplete(value: ImageCompleteCallback | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._onComplete_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    onError(value: ImageErrorCallback | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._onError_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    alt(value: PixelMap | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._alt_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    textBackgroundStyle(value: TextBackgroundStyle | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._textBackgroundStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    baselineOffset(value: arkui_Graphics_LengthMetrics | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._baselineOffset_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ImageSpanAttribute> | AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}
