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

import { ArkImageSpanPeer } from "./component/imageSpan"
import { AttributeModifier } from "./component/common"
import { AttributeUpdaterFlag, CommonMethodModifier } from './CommonMethodModifier'
import { BaseSpanModifier } from "./BaseSpanModifier"
import { ColorFilter } from "./component/units"
import { drawing } from "@ohos/graphics/drawing"
import { ImageCompleteCallback, ImageLoadResult, ImageSpanAttribute } from "./component/imageSpan"
import { ImageErrorCallback, ImageError } from "./component/image"
import { ImageSpanAlignment, ImageFit } from "./component/enums"
import image from "@ohos.multimedia.image"
import { PeerNode } from "./PeerNode";

export class ImageSpanModifier extends BaseSpanModifier implements ImageSpanAttribute,AttributeModifier<ImageSpanAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: ImageSpanAttribute): void { }
    _verticalAlign_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _verticalAlign_0_0value?: ImageSpanAlignment | undefined
    _colorFilter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _colorFilter_0_0value?: ColorFilter | drawing.ColorFilter | undefined
    _objectFit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _objectFit_0_0value?: ImageFit | undefined
    _onComplete_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onComplete_0_0value?: ImageCompleteCallback | undefined
    _onError_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onError_0_0value?: ImageErrorCallback | undefined
    _alt_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alt_0_0value?: image.PixelMap | undefined
    applyModifierPatch(value: PeerNode): void {
        super.applyModifierPatch(value)
        const peer: ArkImageSpanPeer = value as ArkImageSpanPeer
        if (this._verticalAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._verticalAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.verticalAlignAttribute((this._verticalAlign_0_0value as ImageSpanAlignment | undefined));
                    this._verticalAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._verticalAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._verticalAlign_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.verticalAlignAttribute((undefined as ImageSpanAlignment | undefined));
                }
            }
        }
        if (this._colorFilter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._colorFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.colorFilterAttribute((this._colorFilter_0_0value as ColorFilter | drawing.ColorFilter | undefined));
                    this._colorFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._colorFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._colorFilter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.colorFilterAttribute((undefined as ColorFilter | drawing.ColorFilter | undefined));
                }
            }
        }
        if (this._objectFit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._objectFit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.objectFitAttribute((this._objectFit_0_0value as ImageFit | undefined));
                    this._objectFit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._objectFit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._objectFit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.objectFitAttribute((undefined as ImageFit | undefined));
                }
            }
        }
        if (this._onComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onCompleteAttribute((this._onComplete_0_0value as ImageCompleteCallback | undefined));
                    this._onComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onComplete_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onCompleteAttribute((undefined as ImageCompleteCallback | undefined));
                }
            }
        }
        if (this._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onErrorAttribute((this._onError_0_0value as ImageErrorCallback | undefined));
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onError_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onErrorAttribute((undefined as ImageErrorCallback | undefined));
                }
            }
        }
        if (this._alt_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._alt_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.altAttribute((this._alt_0_0value as image.PixelMap | undefined));
                    this._alt_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alt_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alt_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.altAttribute((undefined as image.PixelMap | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof ImageSpanModifier)) {
            return
        }
        const modifier = value as ImageSpanModifier;
        if (modifier._verticalAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._verticalAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.verticalAlign(modifier._verticalAlign_0_0value);
                    break;
                }
                default: {
                    this.verticalAlign((undefined as ImageSpanAlignment | undefined));
                }
            }
        }
        if (modifier._colorFilter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._colorFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.colorFilter(modifier._colorFilter_0_0value);
                    break;
                }
                default: {
                    this.colorFilter((undefined as ColorFilter | drawing.ColorFilter | undefined));
                }
            }
        }
        if (modifier._objectFit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._objectFit_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.objectFit(modifier._objectFit_0_0value);
                    break;
                }
                default: {
                    this.objectFit((undefined as ImageFit | undefined));
                }
            }
        }
        if (modifier._onComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onComplete(modifier._onComplete_0_0value);
                    break;
                }
                default: {
                    this.onComplete((undefined as ImageCompleteCallback | undefined));
                }
            }
        }
        if (modifier._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onError(modifier._onError_0_0value);
                    break;
                }
                default: {
                    this.onError((undefined as ImageErrorCallback | undefined));
                }
            }
        }
        if (modifier._alt_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._alt_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alt(modifier._alt_0_0value);
                    break;
                }
                default: {
                    this.alt((undefined as image.PixelMap | undefined));
                }
            }
        }
    }
    verticalAlign(value: ImageSpanAlignment | undefined): this {
        if (((this._verticalAlign_0_flag) == (AttributeUpdaterFlag.INITIAL)) || this._verticalAlign_0_0value !== value)
        {
            this._verticalAlign_0_flag = AttributeUpdaterFlag.UPDATE
            this._verticalAlign_0_0value = value
        } else
        {
            this._verticalAlign_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    colorFilter(value: ColorFilter | drawing.ColorFilter | undefined): this {
        if (((this._colorFilter_0_flag) == (AttributeUpdaterFlag.INITIAL)) || this._colorFilter_0_0value !== value || !Type.of(value).isPrimitive())
        {
            this._colorFilter_0_flag = AttributeUpdaterFlag.UPDATE
            this._colorFilter_0_0value = value
        } else
        {
            this._colorFilter_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    objectFit(value: ImageFit | undefined): this {
        if (((this._objectFit_0_flag) == (AttributeUpdaterFlag.INITIAL)) || this._objectFit_0_0value !== value)
        {
            this._objectFit_0_flag = AttributeUpdaterFlag.UPDATE
            this._objectFit_0_0value = value
        } else
        {
            this._objectFit_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onComplete(value: ImageCompleteCallback | undefined): this {
        if (((this._onComplete_0_flag) == (AttributeUpdaterFlag.INITIAL)) || this._onComplete_0_0value !== value || !Type.of(value).isPrimitive())
        {
            this._onComplete_0_flag = AttributeUpdaterFlag.UPDATE
            this._onComplete_0_0value = value
        } else
        {
            this._onComplete_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onError(value: ImageErrorCallback | undefined): this {
        if (((this._onError_0_flag) == (AttributeUpdaterFlag.INITIAL)) || this._onError_0_0value !== value || !Type.of(value).isPrimitive())
        {
            this._onError_0_flag = AttributeUpdaterFlag.UPDATE
            this._onError_0_0value = value
        } else
        {
            this._onError_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    alt(value: image.PixelMap | undefined): this {
        if (((this._alt_0_flag) == (AttributeUpdaterFlag.INITIAL)) || this._alt_0_0value !== value || !Type.of(value).isPrimitive())
        {
            this._alt_0_flag = AttributeUpdaterFlag.UPDATE
            this._alt_0_0value = value
        } else
        {
            this._alt_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
}
