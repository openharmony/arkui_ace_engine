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

import { CommonMethod } from "./component/common"
import { TextBackgroundStyle, BaseSpan } from "./component/span"
import { LengthMetrics } from "arkui.Graphics"
import { BaseSpanModifier } from "./BaseSpanModifier"
import { CommonMethodModifier } from "./CommonMethodModifier"
import { AttributeModifier, extractors } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkImageSpanPeer, ImageCompleteCallback, ImageLoadResult, ImageSpanAttribute } from "./component/imageSpan"
import { int32 } from "@koalaui/common"
import { ImageSpanAlignment, ImageFit } from "./component/enums"
import { ColorFilter } from "./component/units"
import { default as drawing } from "@ohos.graphics.drawing"
import { ImageErrorCallback, ImageError } from "./component/image"
import { default as image } from "@ohos.multimedia.image"
export class ImageSpanModifier extends CommonMethodModifier implements ImageSpanAttribute,AttributeModifier<ImageSpanAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: ImageSpanAttribute): void { }
    applyPressedAttribute(instance: ImageSpanAttribute): void { }
    applyFocusedAttribute(instance: ImageSpanAttribute): void { }
    applyDisabledAttribute(instance: ImageSpanAttribute): void { }
    applySelectedAttribute(instance: ImageSpanAttribute): void { }
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
    _textBackgroundStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textBackgroundStyle_0_0value?: TextBackgroundStyle | undefined
    _baselineOffset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _baselineOffset_0_0value?: LengthMetrics | undefined
    applyModifierPatch(node: PeerNode): void {
        super.applyModifierPatch(node)
        const peer = node as ArkImageSpanPeer;
        if (this._verticalAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._verticalAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setVerticalAlignAttribute((this._verticalAlign_0_0value as ImageSpanAlignment | undefined));
                    this._verticalAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._verticalAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._verticalAlign_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setVerticalAlignAttribute((undefined as ImageSpanAlignment | undefined));
                }
            }
        }
        if (this._colorFilter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._colorFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColorFilterAttribute((this._colorFilter_0_0value as ColorFilter | drawing.ColorFilter | undefined));
                    this._colorFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._colorFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._colorFilter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColorFilterAttribute((undefined as ColorFilter | drawing.ColorFilter | undefined));
                }
            }
        }
        if (this._objectFit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._objectFit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setObjectFitAttribute((this._objectFit_0_0value as ImageFit | undefined));
                    this._objectFit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._objectFit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._objectFit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setObjectFitAttribute((undefined as ImageFit | undefined));
                }
            }
        }
        if (this._onComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnCompleteAttribute((this._onComplete_0_0value as ImageCompleteCallback | undefined));
                    this._onComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onComplete_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnCompleteAttribute((undefined as ImageCompleteCallback | undefined));
                }
            }
        }
        if (this._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnErrorAttribute((this._onError_0_0value as ImageErrorCallback | undefined));
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onError_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnErrorAttribute((undefined as ImageErrorCallback | undefined));
                }
            }
        }
        if (this._alt_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._alt_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAltAttribute((this._alt_0_0value as image.PixelMap | undefined));
                    this._alt_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alt_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alt_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAltAttribute((undefined as image.PixelMap | undefined));
                }
            }
        }
        if (this._textBackgroundStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textBackgroundStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextBackgroundStyleAttribute((this._textBackgroundStyle_0_0value as TextBackgroundStyle | undefined));
                    this._textBackgroundStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textBackgroundStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textBackgroundStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextBackgroundStyleAttribute((undefined as TextBackgroundStyle | undefined));
                }
            }
        }
        if (this._baselineOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._baselineOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBaselineOffsetAttribute((this._baselineOffset_0_0value as LengthMetrics | undefined));
                    this._baselineOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._baselineOffset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._baselineOffset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBaselineOffsetAttribute((undefined as LengthMetrics | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ImageSpanModifier): void {
        super.mergeModifier(modifier)
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
        if (modifier._textBackgroundStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textBackgroundStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textBackgroundStyle(modifier._textBackgroundStyle_0_0value);
                    break;
                }
                default: {
                    this.textBackgroundStyle((undefined as TextBackgroundStyle | undefined));
                }
            }
        }
        if (modifier._baselineOffset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._baselineOffset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.baselineOffset(modifier._baselineOffset_0_0value);
                    break;
                }
                default: {
                    this.baselineOffset((undefined as LengthMetrics | undefined));
                }
            }
        }
    }
    verticalAlign(value: ImageSpanAlignment | undefined): this {
        if (((this._verticalAlign_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
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
        if (((this._colorFilter_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
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
        if (((this._objectFit_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
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
        if (((this._onComplete_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
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
        if (((this._onError_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
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
        if (((this._alt_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._alt_0_flag = AttributeUpdaterFlag.UPDATE
            this._alt_0_0value = value
        } else
        {
            this._alt_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textBackgroundStyle(value: TextBackgroundStyle | undefined): this {
        if (((this._textBackgroundStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textBackgroundStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._textBackgroundStyle_0_0value = value
        } else
        {
            this._textBackgroundStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    baselineOffset(value: LengthMetrics | undefined): this {
        if (((this._baselineOffset_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._baselineOffset_0_flag = AttributeUpdaterFlag.UPDATE
            this._baselineOffset_0_0value = value
        } else
        {
            this._baselineOffset_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ImageSpanAttribute> | AttributeModifier<BaseSpan> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
