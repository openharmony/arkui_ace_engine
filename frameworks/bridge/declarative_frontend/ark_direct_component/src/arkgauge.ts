/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/// <reference path='./../../ark_component/src/import.ts' />
type ComponentObj = { component: any }

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class ArkGaugeComponent extends globalThis.__ArkComponent__ {
        constructor(nativePtr: any, classType: any) {
            super(nativePtr, classType);
        }
        value(value: number): this {
            modifierWithKey(this._modifiersWithKeys, GaugeValueModifier.identity, GaugeValueModifier, value);
            return this;
        }
        startAngle(angle: number): this {
            modifierWithKey(this._modifiersWithKeys, GaugeStartAngleModifier.identity, GaugeStartAngleModifier, angle);
            return this;
        }
        endAngle(angle: number): this {
            modifierWithKey(this._modifiersWithKeys, GaugeEndAngleModifier.identity, GaugeEndAngleModifier, angle);
            return this;
        }
        colors(colors: ResourceColor | LinearGradient | Array<[ResourceColor | LinearGradient, number]>): this {
            modifierWithKey(this._modifiersWithKeys, GaugeColorsModifier.identity, GaugeColorsModifier, colors);
            return this;
        }
        strokeWidth(length: any): this {
            modifierWithKey(this._modifiersWithKeys, GaugeStrokeWidthModifier.identity, GaugeStrokeWidthModifier, length);
            return this;
        }
        description(value: CustomBuilder): this {
            throw new BusinessError(100201, 'description function not supported in attributeModifier scenario.');
        }
        trackShadow(value: GaugeShadowOptions): this {
            modifierWithKey(this._modifiersWithKeys, GaugeTrackShadowModifier.identity, GaugeTrackShadowModifier, value);
            return this;
        }
        indicator(value: GaugeIndicatorOptions): this {
            modifierWithKey(this._modifiersWithKeys, GaugeIndicatorModifier.identity, GaugeIndicatorModifier, value);
            return this;
        }
        contentModifier(value: ContentModifier<GaugeConfiguration>): this {
            modifierWithKey(this._modifiersWithKeys, GaugeContentModifier.identity, GaugeContentModifier, value);
            return this;
        }
        setContentModifier(modifier: any): this {
            if (modifier === undefined || modifier === null) {
                getUINativeModule().gauge.setContentModifierBuilder(this.nativePtr, false);
                return this;
            }
            this.needRebuild = false;
            if (this.builder !== modifier.applyContent()) {
                this.needRebuild = true;
            }
            this.builder = modifier.applyContent();
            this.modifier = modifier;
            getUINativeModule().gauge.setContentModifierBuilder(this.nativePtr, this);
            return this;
        }
        makeContentModifierNode(context: any, gaugeConfiguration: any): any {
            gaugeConfiguration.contentModifier = this.modifier;
            if (isUndefined(this.gaugeNode) || this.needRebuild) {
                let xNode = globalThis.requireNapi('arkui.node');
                this.gaugeNode = new xNode.BuilderNode(context);
                this.gaugeNode.build(this.builder, gaugeConfiguration);
                this.needRebuild = false;
            } else {
                this.gaugeNode.update(gaugeConfiguration);
            }
            return this.gaugeNode.getFrameNode();
        }
        privacySensitive(value: boolean): this {
            modifierWithKey(this._modifiersWithKeys, GaugePrivacySensitiveModifier.identity, GaugePrivacySensitiveModifier, value);
            return this;
        }
    }
    
    class GaugeIndicatorModifier extends ModifierWithKey<any> {
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().gauge.resetGaugeIndicator(node, this.value);
            }
            else {
                getUINativeModule().gauge.setGaugeIndicator(node, this.value.icon, this.value.space);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue.icon, this.value.icon) ||
                !isBaseOrResourceEqual(this.stageValue.space, this.value.space);
        }
    }
    (GaugeIndicatorModifier as any).identity = Symbol('gaugeIndicator');
    
    class GaugeContentModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        applyPeer(node: any, reset: boolean, component: any): void {
            let gaugeComponent = component;
            gaugeComponent.setContentModifier(this.value);
        }
    }
    (GaugeContentModifier as any).identity = Symbol('gaugeContentModifier');
    
    class GaugeColorsModifier extends ModifierWithKey<any> {
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().gauge.resetGaugeColors(node);
            }
            else {
                getUINativeModule().gauge.setGaugeColors(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return true;
        }
    }
    (GaugeColorsModifier as any).identity = Symbol('gaugeColors');
    
    class GaugeValueModifier extends ModifierWithKey<any> {
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().gauge.resetGaugeVaule(node);
            }
            else {
                getUINativeModule().gauge.setGaugeVaule(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
    }
    (GaugeValueModifier as any).identity = Symbol('gaugeVaule');
    
    class GaugeStartAngleModifier extends ModifierWithKey<any> {
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().gauge.resetGaugeStartAngle(node);
            }
            else {
                getUINativeModule().gauge.setGaugeStartAngle(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
    }
    (GaugeStartAngleModifier as any).identity = Symbol('gaugeStartAngle');
    
    class GaugeEndAngleModifier extends ModifierWithKey<any> {
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().gauge.resetGaugeEndAngle(node);
            }
            else {
                getUINativeModule().gauge.setGaugeEndAngle(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
    }
    (GaugeEndAngleModifier as any).identity = Symbol('gaugeEndAngle');
    
    class GaugeStrokeWidthModifier extends ModifierWithKey<any> {
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().gauge.resetGaugeStrokeWidth(node);
            }
            else {
                getUINativeModule().gauge.setGaugeStrokeWidth(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
    }
    (GaugeStrokeWidthModifier as any).identity = Symbol('gaugeStrokeWidth');
    
    class GaugeTrackShadowModifier extends ModifierWithKey<any> {
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().gauge.resetGaugeTrackShadow(node);
            }
            else {
                getUINativeModule().gauge.setGaugeTrackShadow(node, this.value, this.value.radius, this.value.offsetX, this.value.offsetY);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
    }
    (GaugeTrackShadowModifier as any).identity = Symbol('gaugeTrackShadow');
    
    class GaugePrivacySensitiveModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().gauge.resetGaugePrivacySensitive(node);
            } else {
                getUINativeModule().gauge.setGaugePrivacySensitive(node, this.value);
            }
        }
    }
    (GaugePrivacySensitiveModifier as any).identity = Symbol('gaugePrivacySensitive');
    
    loadComponent.componentObj = {'component' : ArkGaugeComponent };
  }
  return loadComponent.componentObj;
}

class JSGauge extends JSViewAbstract {
    static create(params: any): void {
        getUINativeModule().gauge.create(params);
    }

    static value(value: any): void {
        getUINativeModule().gauge.setGaugeVaule(true, value);
    }
    static startAngle(angle: any): void {
        getUINativeModule().gauge.setGaugeStartAngle(true, angle);
    }
    static endAngle(angle: any): void {
        getUINativeModule().gauge.setGaugeEndAngle(true, angle);
    }
    static colors(colors: any): void {
        getUINativeModule().gauge.setGaugeColors(true, colors);
    }
    static strokeWidth(length: any): void {
        getUINativeModule().gauge.setGaugeStrokeWidth(true, length);
    }
    static description(value: any): void {
        getUINativeModule().gauge.setDescription(value);
    }
    static trackShadow(value: any): void {
        getUINativeModule().gauge.setGaugeTrackShadow(true, value);
    }
    static indicator(value: any): void {
        getUINativeModule().gauge.setGaugeIndicator(true, value);
    }
    static attributeModifier(modifier: any): void {
        attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
            return createComponent(nativePtr);
        }, (nativePtr: any, classType: any, modifierJS: any) => {
            return new modifierJS.GaugeModifier(nativePtr, classType);
        });
    }
    static contentModifier(modifier: any): void {
        const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
        let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
        let component = this.createOrGetNode(elmtId, () => {
            return createComponent(nativeNode, 'gauge');
        });
        component.setContentModifier(modifier);
    }

    static onClick(value: any): void {
        __Common__.onClick(value);
    }
    static onKeyEvent(value: any): void {
        __Common__.onKeyEvent(value);
    }
    static onDeleteEvent(value: any): void {
        __Common__.onDeleteEvent(value);
    }
    static onAttach(value: any): void {
        __Common__.onAttach(value);
    }
    static onAppear(value: any): void {
        __Common__.onAppear(value);
    }
    static onDetach(value: any): void {
        __Common__.onDetach(value);
    }
    static onDisAppear(value: any): void {
        __Common__.onDisAppear(value);
    }

    static onTouch(value: any): void {
        __Common__.onTouch(value);
    }
}

function createComponent(nativePtr: any, classType: any): any {
    loadComponent();
 	if (loadComponent.componentObj !== undefined) {
 	    return new loadComponent.componentObj.component(nativePtr, classType);
 	}
    return undefined;
}

function exportComponent(): void {
    globalThis.ArkGaugeComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
    globalThis.Gauge = JSGauge;
}

export default { loadComponent, createComponent, exportComponent, exportView };
