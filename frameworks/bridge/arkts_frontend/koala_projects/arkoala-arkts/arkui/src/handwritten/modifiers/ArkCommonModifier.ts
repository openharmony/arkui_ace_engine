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

import { AttributeModifier, CommonAttribute, Length, ResourceColor } from "../..";
import { ArkCommonMethodPeer } from "../../generated/peers/ArkCommonPeer";

enum ModifierType {
    ORIGIN = 0,
    STATE = 1,
    FRAME_NODE = 2,
    EXPOSE_MODIFIER = 3,
}

abstract class BaseModifier {
    abstract applyStage(node: ArkCommonMethodPeer): boolean

    abstract applyStageImmediately(node: ArkCommonMethodPeer): void

    abstract applyPeer(node: ArkCommonMethodPeer, reset: boolean): void

    abstract checkObjectDiff(): boolean

    abstract reset(): void
}

class ObservedMap {
    private map_: Map<string, BaseModifier> = new Map<string, BaseModifier>();
    private changeCallback?: (key: string, value: BaseModifier) => void;

    public clear(): void {
        this.map_.clear();
    }

    public delete(key: string): boolean {
        return this.map_.delete(key);
    }

    public forEach(callbackfn: (value: BaseModifier, key: string) => void): void {
        this.map_.forEach(callbackfn);
    }
    public get(key: string): BaseModifier | undefined {
        return this.map_.get(key);
    }
    public has(key: string): boolean {
        return this.map_.has(key);
    }
    public set(key: string, value: BaseModifier): this {
        this.map_.set(key, value);
        if (this.changeCallback) {
            this.changeCallback!(key, value)
        }
        return this;
    }
    public get size(): number {
        return this.map_.size;
    }
    public entries(): IterableIterator<[string, BaseModifier]> {
        return this.map_.entries();
    }
    public keys(): IterableIterator<string> {
        return this.map_.keys();
    }
    public values(): IterableIterator<BaseModifier> {
        return this.map_.values();
    }
    public setOnChange(callback: (key: string, value: BaseModifier) => void): void {
        if (!this.changeCallback) {
            this.changeCallback = callback;
        }
    }
}

const UI_STATE_NORMAL = 0;
const UI_STATE_PRESSED = 1;
const UI_STATE_FOCUSED = 1 << 1;
const UI_STATE_DISABLED = 1 << 2;
const UI_STATE_SELECTED = 1 << 3;

export function applyUIAttributes<T>(modifier: AttributeModifier<T>, nativeNode: ArkCommonMethodPeer): void {
    modifier.applyNormalAttribute(nativeNode._attributeSet! as T);
    modifier.applyPressedAttribute(nativeNode._attributeSet! as T);
    modifier.applyFocusedAttribute(nativeNode._attributeSet! as T);
    modifier.applyDisabledAttribute(nativeNode._attributeSet! as T);
    modifier.applySelectedAttribute(nativeNode._attributeSet! as T);
}

export class ModifierWithKey<T> extends BaseModifier {
    stageValue: T | undefined;
    value: T | undefined;
    constructor(value: T) {
        super()
        this.stageValue = value;
    }

    reset(): void {
        this.stageValue = undefined
    }

    applyStage(node: ArkCommonMethodPeer): boolean {
        if (this.stageValue === undefined || this.stageValue === null) {
            this.value = this.stageValue
            this.applyPeer(node, true)
            return true;
        }
        let needDiff = this.checkObjectDiff()
        if (needDiff) {
            this.value = this.stageValue
            this.applyPeer(node, false)
            return true
        }
        return false
    }

    applyStageImmediately(node: ArkCommonMethodPeer): void {
        this.value = this.stageValue;
        if (this.stageValue === undefined || this.stageValue === null) {
            this.applyPeer(node, true);
            return;
        }
        this.applyPeer(node, false);
    }

    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
     }

    checkObjectDiff(): boolean {
        const stageTypeInfo: string = typeof this.stageValue;
        const valueTypeInfo: string = typeof this.value;
        if (stageTypeInfo !== valueTypeInfo) {
            return true;
        }
        if (stageTypeInfo === 'number' || stageTypeInfo === 'string' || stageTypeInfo === 'boolean') {
            return (this.stageValue !== this.value);
        }
        // if (this.stageValue instanceof ArkResourceImpl) {
        //     return (this.stageValue as ArkResource).isEqual(this.value as ArkResource)
        // }
        return false;
    }
}

class BackgroundColorModifier extends ModifierWithKey<ResourceColor> {
    constructor(value: ResourceColor) {
        super(value);
    }
    static identity: string = 'backgroundColor';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetBackgroundColor();
        } else {
            node.backgroundColorAttribute(this.value!);
        }
    }
    static factory(value: ResourceColor): BackgroundColorModifier {
        return new BackgroundColorModifier(value)
    }
}

class WidthModifier extends ModifierWithKey<Length> {
    constructor(value: Length) {
        super(value);
    }
    static identity: string = 'width';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetWidthAttribute();
        } else {
            node.widthAttribute(this.value!);
        }
    }
    static factory(value: Length): WidthModifier {
        return new WidthModifier(value)
    }
}

class HeightModifier extends ModifierWithKey<Length> {
    constructor(value: Length) {
        super(value);
    }
    static identity: string = 'height';
    applyPeer(node: ArkCommonMethodPeer, reset: boolean): void {
        if (reset) {
            // commomPeerNode.resetWidthAttribute();
        } else {
            node.heightAttribute(this.value!);
        }
    }
    static factory(value: Length): HeightModifier {
        return new HeightModifier(value)
    }
}

export function modifierWithKey<T, M extends ModifierWithKey<T>>(
    modifiers: ObservedMap,
    identity: string,
    modifierClass: (value: T) => M, value: T) {
    let item = modifiers.get(identity)
    if (item == undefined) {
        modifiers.set(identity, modifierClass(value));
        return;
    }
    let item1 = item as ModifierWithKey<T>;
    item1.stageValue = value;
    modifiers.set(identity, item1);
}
export function modifierNullWithKey(modifiers: ObservedMap, identity: string) {
    const item = modifiers.get(identity)
    if (item) {
        item.reset()
        modifiers.set(identity, item);
    }
}

export class ArkCommonAttributeSet implements CommonAttribute {
    _modifiersWithKeys: ObservedMap = new ObservedMap();
    _instanceId: number = -1;

    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId;
    }

    cleanStageValue(): void {
        if (!this._modifiersWithKeys) {
            return;
        }
        this._modifiersWithKeys.forEach((value, key) => {
            value.reset();
        });
    }

    applyModifierPatch(peerNode: ArkCommonMethodPeer): void {
        let expiringItemsWithKeys = new Array<string>;
        this._modifiersWithKeys.forEach((value, key) => {
            if (value.applyStage(peerNode)) {
                expiringItemsWithKeys.push(key);
            }
        });
    }

    width(value: Length | undefined): this {
        if (value) {
            modifierWithKey(this._modifiersWithKeys, WidthModifier.identity, WidthModifier.factory, value);
        } else {
            modifierNullWithKey(this._modifiersWithKeys, WidthModifier.identity)
        }
        return this;
    }

    height(value: Length | undefined): this {
        if (value) {
            modifierWithKey(this._modifiersWithKeys, HeightModifier.identity, HeightModifier.factory, value);
        } else {
            modifierNullWithKey(this._modifiersWithKeys, HeightModifier.identity)
        }
        return this;
    }

    backgroundColor(value: ResourceColor | undefined): this {
        if (value) {
            modifierWithKey(this._modifiersWithKeys, BackgroundColorModifier.identity, BackgroundColorModifier.factory, value);
        } else {
            modifierNullWithKey(this._modifiersWithKeys, BackgroundColorModifier.identity)
        }
        return this;
    }
}
export class CommonModifier<CommonAttribute> extends ArkCommonAttributeSet implements AttributeModifier<CommonAttribute> {
    applyNormalAttribute(instance: CommonAttribute): void {
      
    }
    applyPressedAttribute(instance: CommonAttribute): void {
       
    }
    applyFocusedAttribute(instance: CommonAttribute): void {
        
    }
    applyDisabledAttribute(instance: CommonAttribute): void {
      
    }
    applySelectedAttribute(instance: CommonAttribute): void {
        
    }
   
}