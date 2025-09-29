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
import { ArkCommonMethodComponent, AttributeModifier, CommonMethod } from './common';
import { applyAttributeModifierBase, applyCommonModifier } from "../handwritten/modifiers/ArkCommonModifier";
import { CommonModifier } from '../CommonModifier';
import { ShapeModifier } from '../ShapeModifier';
import { runtimeType, RuntimeType } from "@koalaui/interop"


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

function hookShapeAttributeModifier(component: ArkShapeComponent, modifier: AttributeModifier<ShapeAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): ShapeModifier => {
        let isShapeModifier: boolean = modifier instanceof ShapeModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new ShapeModifier();
        if (isShapeModifier) {
            let shapeModifier = modifier as object as ShapeModifier;
            initModifier.mergeModifier(shapeModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
        if (params.length < 1) {
            return;
        }
        let peer: ArkShapePeer = component.getPeer() as Object as ArkShapePeer;
        const param1_type = runtimeType(params[0])
        if ((RuntimeType.UNDEFINED) !== param1_type) {
            const pixelMap = params[0] as PixelMap;
            ArkUIAniModule._Shape_Transfer_PixelMap(peer.getPeerPtr() as KPointer, pixelMap);
        } else {
            peer?.setShapeOptions1Attribute();
        }
    };
    let updaterReceiver = (): ArkShapeComponent => {
        let componentNew: ArkShapeComponent = new ArkShapeComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<ShapeAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}
