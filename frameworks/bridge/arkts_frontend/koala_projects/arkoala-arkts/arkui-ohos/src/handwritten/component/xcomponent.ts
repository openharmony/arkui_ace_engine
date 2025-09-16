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


import { TypeChecker } from "#components"
import { ArkUIAniModule } from "arkui.ani";
import { ArkCommonMethodComponent, AttributeModifier, CommonMethod } from './common';
import { applyAttributeModifierBase, applyCommonModifier } from "../handwritten/modifiers/ArkCommonModifier";
import { PeerNode } from '../PeerNode';
import { CommonMethodModifier, AttributeUpdaterFlag } from '../CommonMethodModifier';
import { CommonModifier } from "../CommonModifier";

export interface XComponentControllerCallbackInternal {
    onSurfaceCreated: ((surfaceId: string) => void);
    onSurfaceChanged: ((surfaceId: string, surfaceRect: SurfaceRect) => void);
    onSurfaceDestroyed: ((surfaceId: string) => void);
}

export class SurfaceRectAniInternal implements SurfaceRect {
    offsetX?: number;
    offsetY?: number;
    surfaceWidth: number;
    surfaceHeight: number;
    constructor(w: number, h: number, x: number, y: number) {
        this.offsetX = x;
        this.offsetY = y;
        this.surfaceWidth = w;
        this.surfaceHeight = h;
    }
}

export class TypedXComponentPeerInternal extends ArkXComponentPeer {
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
}

function hookSetXComponentOptions(component: ArkXComponentComponent,
    value: XComponentParameters | XComponentOptions | NativeXComponentParameters): void {
    if (TypeChecker.isXComponentOptions(value, true, false, true, true)) {
        const options_casted = value as (XComponentOptions)
        const peer = component.getPeer();
        peer?.setXComponentOptions1Attribute(options_casted)
        if (peer !== undefined) {
            const controller = options_casted.controller;
            let callback: XComponentControllerCallbackInternal = {
                onSurfaceCreated: controller.onSurfaceCreated as ((surfaceId: string) => void),
                onSurfaceChanged: controller.onSurfaceChanged as ((surfaceId: string, surfaceRect: SurfaceRect) => void),
                onSurfaceDestroyed: controller.onSurfaceDestroyed as ((surfaceId: string) => void),
            } as XComponentControllerCallbackInternal;
            ArkUIAniModule._XComponent_SetSurfaceCallback(peer.getPeerPtr(), callback);
        }
        return;
    }
}

export class XComponentModifier extends CommonMethodModifier implements XComponentAttribute, AttributeModifier<XComponentAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: XComponentAttribute): void { }
    applyPressedAttribute(instance: XComponentAttribute): void { }
    applyFocusedAttribute(instance: XComponentAttribute): void { }
    applyDisabledAttribute(instance: XComponentAttribute): void { }
    applySelectedAttribute(instance: XComponentAttribute): void { }
    _onLoad_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onLoad_0_0value?: VoidCallback | undefined
    _onDestroy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDestroy_0_0value?: VoidCallback | undefined
    _enableAnalyzer_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableAnalyzer_0_0value?: boolean | undefined
    _enableSecure_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableSecure_0_0value?: boolean | undefined
    _hdrBrightness_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hdrBrightness_0_0value?: number | undefined
    _enableTransparentLayer_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableTransparentLayer_0_0value?: boolean | undefined
    applyModifierPatch(peerNode: PeerNode): void {
        super.applyModifierPatch(peerNode)
        const peer: ArkXComponentPeer = peerNode as ArkXComponentPeer
        if (this._onLoad_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onLoad_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onLoadAttribute((this._onLoad_0_0value as VoidCallback | undefined));
                    this._onLoad_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onLoad_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onLoad_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onLoadAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onDestroy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDestroy_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.onDestroyAttribute((this._onDestroy_0_0value as VoidCallback | undefined));
                    this._onDestroy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDestroy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDestroy_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.onDestroyAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._enableAnalyzer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableAnalyzer_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enableAnalyzerAttribute((this._enableAnalyzer_0_0value as boolean | undefined));
                    this._enableAnalyzer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableAnalyzer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableAnalyzer_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enableAnalyzerAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._enableSecure_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableSecure_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enableSecureAttribute((this._enableSecure_0_0value as boolean | undefined));
                    this._enableSecure_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableSecure_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableSecure_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enableSecureAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._hdrBrightness_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hdrBrightness_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.hdrBrightnessAttribute((this._hdrBrightness_0_0value as number | undefined));
                    this._hdrBrightness_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hdrBrightness_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hdrBrightness_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.hdrBrightnessAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._enableTransparentLayer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableTransparentLayer_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.enableTransparentLayerAttribute((this._enableTransparentLayer_0_0value as boolean | undefined));
                    this._enableTransparentLayer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableTransparentLayer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableTransparentLayer_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.enableTransparentLayerAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof XComponentModifier)) {
            return;
        }
        const modifier = value as XComponentModifier
        if (modifier._onLoad_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onLoad_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onLoad(modifier._onLoad_0_0value);
                    break;
                }
                default: {
                    this.onLoad((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onDestroy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDestroy_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDestroy(modifier._onDestroy_0_0value);
                    break;
                }
                default: {
                    this.onDestroy((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._enableAnalyzer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableAnalyzer_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableAnalyzer(modifier._enableAnalyzer_0_0value);
                    break;
                }
                default: {
                    this.enableAnalyzer((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._enableSecure_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableSecure_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableSecure(modifier._enableSecure_0_0value);
                    break;
                }
                default: {
                    this.enableSecure((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._hdrBrightness_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._hdrBrightness_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.hdrBrightness(modifier._hdrBrightness_0_0value);
                    break;
                }
                default: {
                    this.hdrBrightness((undefined as number | undefined));
                }
            }
        }
    }
    onLoad(value: VoidCallback | undefined): this {
        if (((this._onLoad_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onLoad_0_flag = AttributeUpdaterFlag.UPDATE
            this._onLoad_0_0value = value
        }
        else
        {
            this._onLoad_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDestroy(value: VoidCallback | undefined): this {
        if (((this._onDestroy_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDestroy_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDestroy_0_0value = value
        }
        else
        {
            this._onDestroy_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableAnalyzer(value: boolean | undefined): this {
        if (((this._enableAnalyzer_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableAnalyzer_0_0value) !== (value)))
        {
            this._enableAnalyzer_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableAnalyzer_0_0value = value
        }
        else
        {
            this._enableAnalyzer_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableSecure(value: boolean | undefined): this {
        if (((this._enableSecure_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableSecure_0_0value) !== (value)))
        {
            this._enableSecure_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableSecure_0_0value = value
        }
        else
        {
            this._enableSecure_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    hdrBrightness(value: number | undefined): this {
        if (((this._hdrBrightness_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._hdrBrightness_0_0value) !== (value)))
        {
            this._hdrBrightness_0_flag = AttributeUpdaterFlag.UPDATE
            this._hdrBrightness_0_0value = value
        }
        else
        {
            this._hdrBrightness_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableTransparentLayer(value: boolean | undefined): this {
        if (((this._enableTransparentLayer_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableTransparentLayer_0_0value) !== (value)))
        {
            this._enableTransparentLayer_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableTransparentLayer_0_0value = value
        }
        else
        {
            this._enableTransparentLayer_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
}

function hookXComponentAttributeModifier(component: ArkXComponentComponent, modifier: AttributeModifier<XComponentAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): XComponentModifier => {
        let isXComponentModifier: boolean = modifier instanceof XComponentModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new XComponentModifier();
        if (isXComponentModifier) {
            let xcomponentModifier = modifier as object as XComponentModifier;
            initModifier.mergeModifier(xcomponentModifier);
        }
        component.getPeer()._attributeSet = initModifier;
        return initModifier;
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkXComponentComponent => {
        let componentNew: ArkXComponentComponent = new ArkXComponentComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<XComponentAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}
