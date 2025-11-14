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


import { AttributeUpdater } from '../../AttributeUpdater';
import { CommonModifier } from '../../CommonModifier';
import {CommonMethod, ArkCommonMethodComponent, AttributeModifier, ModifierEventType , ArkCommonMethodPeer } from  '#generated';
import { int32} from "@koalaui/common"
import { PeerNode } from '../../PeerNode';
import { CommonMethodModifier } from '../../CommonMethodModifier';
import { ComponentBase } from '../../ComponentBase';
import { SerializerBase } from '@koalaui/interop';
import { ArkUIGeneratedNativeModule } from '#components';
import { ArkUIAniModule } from 'arkui.ani';

const UI_STATE_NORMAL = 0;
const UI_STATE_PRESSED = 1;
const UI_STATE_FOCUSED = 1 << 1;
const UI_STATE_DISABLED = 1 << 2;
const UI_STATE_SELECTED = 1 << 3;

export function applyUIAttributes<T, MethodSet extends T>(modifier: AttributeModifier<T>, attributeSet: MethodSet, state: int32 = 0): void {     
    modifier.applyNormalAttribute(attributeSet as T);
    if (state & UI_STATE_PRESSED) {
        modifier.applyPressedAttribute(attributeSet as T);
    }
    if (state & UI_STATE_FOCUSED) {
        modifier.applyFocusedAttribute(attributeSet as T);
    }
    if (state & UI_STATE_DISABLED) {
        modifier.applyDisabledAttribute(attributeSet as T);
    }
    if (state & UI_STATE_SELECTED) {
        modifier.applySelectedAttribute(attributeSet as T);
    }
}

export function applyUIAttributesUpdate<T, MethodSet extends T>(modifier: AttributeModifier<T>, attributeSet: MethodSet, state: int32 = 0, isInit:boolean = true): void {
    if (state == UI_STATE_NORMAL && !isInit) {
        modifier.applyNormalAttribute(attributeSet as T);
    }
    if (state & UI_STATE_PRESSED) {
        modifier.applyPressedAttribute(attributeSet as T);
    }
    if (state & UI_STATE_FOCUSED) {
        modifier.applyFocusedAttribute(attributeSet as T);
    }
    if (state & UI_STATE_DISABLED) {
        modifier.applyDisabledAttribute(attributeSet as T);
    }
    if (state & UI_STATE_SELECTED) {
        modifier.applySelectedAttribute(attributeSet as T);
    }
}
 

export function applyAttributeModifierNoCommonMethod<T, MethodSet extends T, MethodComponent extends ComponentBase>
    (modifier: AttributeModifier<T>, attributeSet: () => MethodSet, func: (component: MethodComponent, ...params: FixedArray<Object>) => void, updaterReceiver: () => MethodComponent, node: PeerNode,
    isStateStyle: boolean = true): MethodSet {
    let attributeSet_ = attributeSet();
    let isInit: boolean = true;
    let attributeUpdater : AttributeUpdater<T> | undefined = undefined;
    let isAttributeUpdater: boolean = (modifier instanceof AttributeUpdater);
    if (isAttributeUpdater) {
        attributeUpdater = modifier as object as AttributeUpdater<T>
        isInit = attributeUpdater!.isInit;
        attributeUpdater!.isInit = false;
        let needUpdate: boolean = false;
        if (!attributeUpdater.peerNode_) {
            attributeUpdater.initializeModifier(attributeSet_ as Object as T);
            needUpdate = true;
        } else if (node !== attributeUpdater.peerNode_) {
            attributeUpdater.onComponentChanged(attributeSet_ as Object as T);
            needUpdate = true;
        }
        if (needUpdate) {
            attributeUpdater.peerNode_ = node;
            let receiver = updaterReceiver();
            receiver.setPeer(node);
            receiver.setAttributeHook(setFrameCallback);
            attributeUpdater.attribute = receiver as Object as T;
            attributeUpdater.updateConstructorParams = (...params: FixedArray<Object>) => {
                func(receiver, ...params);
                receiver.applyAttributesFinish();
                return receiver as Object as T;
            };
        }
    }
    let stateValue = 0;
    let currentState = node.getStateStyleMutable();
    let isNormal: boolean = ModifierEventType.UI_STATE_NORMAL === modifier.monitorEventType();
    if (!isNormal) {
        if (currentState === undefined) {
            currentState = node.getOrCreateStateStyleMutable(Number.toInt(modifier.monitorEventType()))!;
        }
        stateValue = currentState.value;
    }
    if (isAttributeUpdater) {
        applyUIAttributesUpdate(modifier, attributeSet_, stateValue, isInit);
    } else {
        applyUIAttributes(modifier, attributeSet_, stateValue);
    }
    return attributeSet_;
}

export function applyAttributeModifierBase<T, MethodSet extends CommonMethodModifier, MethodComponent extends ArkCommonMethodComponent>
    (modifier: AttributeModifier<T>, attributeSet: () => MethodSet, func: (component: MethodComponent, ...params: FixedArray<Object>) => void, updaterReceiver: () => MethodComponent, node: ArkCommonMethodPeer,
    isStateStyle: boolean = true): void {
    let attributeSet_ = applyAttributeModifierNoCommonMethod(modifier, attributeSet, func, updaterReceiver, node, isStateStyle) as CommonMethodModifier;
    attributeSet_!.applyModifierPatch(node);
}

export function applyCommonModifier(peerNode: ArkCommonMethodPeer, modifier: AttributeModifier<CommonMethod>) {
    let attributeSet = (): CommonMethodModifier => {
        let commonModifier = modifier as object as CommonModifier;
        let initModifier = peerNode.attributeSet ? peerNode.attributeSet! : new CommonMethodModifier();
        initModifier.mergeModifier(commonModifier);
        peerNode.attributeSet = initModifier;
        return initModifier;
    }
    let constructParam = (component:ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkCommonMethodComponent => {
        let component: ArkCommonMethodComponent = new ArkCommonMethodComponent();
        component.setPeer(peerNode);
        return component;
    };
    applyAttributeModifierBase(modifier, attributeSet, constructParam, updaterReceiver, peerNode);
}

function setFrameCallback(peer?: PeerNode): void {
    ArkUIAniModule._FrameNode_MarkDirtyNode(peer!.getPeerPtr());
    const thisSerializer: SerializerBase = SerializerBase.hold()
    thisSerializer.holdAndWriteCallback((index: number) => { })
    thisSerializer.holdAndWriteCallback((index: number) => { })
    ArkUIGeneratedNativeModule._SystemOps_setFrameCallback(thisSerializer.asBuffer(),
        thisSerializer.length(), 0);
    thisSerializer.release()
}   