/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
        class ArkProgressComponent extends globalThis.__ArkComponent__ {
            constructor(nativePtr: any, classType: any) {
                super(nativePtr, classType);
            }
            initialize(value: any): this {
                if (value?.[0] !== undefined) {
                    modifierWithKey(this._modifiersWithKeys, ProgressInitializeModifier.identity,
                        ProgressInitializeModifier, value[0]);
                }
                return this;
            }
            value(value: any): this {
                modifierWithKey(this._modifiersWithKeys, ProgressValueModifier.identity, ProgressValueModifier, value);
                return this;
            }
            color(value: any): this {
                modifierWithKey(this._modifiersWithKeys, ProgressColorModifier.identity, ProgressColorModifier, value);
                return this;
            }
            style(value: any): this {
                modifierWithKey(this._modifiersWithKeys, ProgressStyleModifier.identity, ProgressStyleModifier, value);
                return this;
            }
            backgroundColor(value: any): this {
                modifierWithKey(this._modifiersWithKeys, ProgressBackgroundColorModifier.identity, ProgressBackgroundColorModifier, value);
                return this;
            }
            privacySensitive(value: any): this {
                modifierWithKey(this._modifiersWithKeys, ProgressPrivacySensitiveModifier.identity, ProgressPrivacySensitiveModifier, value);
                return this;
            }
            contentModifier(value: any): this {
                modifierWithKey(this._modifiersWithKeys, ProgressContentModifier.identity, ProgressContentModifier, value);
                return this;
            }
            setContentModifier(modifier: any): this {
                if (modifier === undefined || modifier === null) {
                    getUINativeModule().progress.setContentModifierBuilder(this.nativePtr, false);
                    return this;
                }
                this.needRebuild = false;
                if (this.builder !== modifier.applyContent()) {
                    this.needRebuild = true;
                }
                this.builder = modifier.applyContent();
                this.modifier = modifier;
                getUINativeModule().progress.setContentModifierBuilder(this.nativePtr, this);
                return this;
            }
            makeContentModifierNode(context: any, progressConfig: any): any {
                progressConfig.contentModifier = this.modifier;
                if (isUndefined(this.progressNode) || this.needRebuild) {
                    let xNode = globalThis.requireNapi('arkui.node');
                    this.progressNode = new xNode.BuilderNode(context);
                    this.progressNode.build(this.builder, progressConfig);
                    this.needRebuild = false;
                } else {
                    this.progressNode.update(progressConfig);
                }
                return this.progressNode.getFrameNode();
            }
        }

    class ProgressPrivacySensitiveModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().progress.resetProgressPrivacySensitive(node);
            } else {
                getUINativeModule().progress.setProgressPrivacySensitive(node, this.value);
            }
        }
    }
    (ProgressPrivacySensitiveModifier as any).identity = Symbol('progressPrivacySensitive');

    class ProgressInitializeModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().progress.resetProgressInitialize(node);
            }
            else {
                getUINativeModule().progress.setProgressInitialize(
                    node, this.value.value, this.value.total, this.value.style, this.value.type);
            }
        }
    }
    (ProgressInitializeModifier as any).identity = Symbol('progressInitialize');

    class ProgressValueModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().progress.resetProgressValue(node);
            }
            else {
                getUINativeModule().progress.setProgressValue(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return true;
        }
    }
    (ProgressValueModifier as any).identity = Symbol('value');

    class ProgressColorModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().progress.resetProgressColor(node);
            }
            else {
                getUINativeModule().progress.setProgressColor(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return this.stageValue !== this.value;
        }
    }
    (ProgressColorModifier as any).identity = Symbol('color');

    class ProgressStyleModifier extends ModifierWithKey<any> {
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().progress.resetProgressStyle(node);
            }
            else {
                let strokeWidth = this.value?.strokeWidth;
                let scaleCount = this.value?.scaleCount;
                let scaleWidth = this.value?.scaleWidth;
                let enableSmoothEffect = this.value?.enableSmoothEffect;
                let borderColor = this.value?.borderColor;
                let borderWidth = this.value?.borderWidth;
                let content = this.value?.content;
                let fontSize;
                let fontWeight;
                let fontFamily;
                let fontStyle;
                if (this.value?.font) {
                    fontSize = this.value.font.size;
                    fontWeight = this.value.font.weight;
                    fontFamily = this.value.font.family;
                    fontStyle = this.value.font.style;
                }
                let fontColor = this.value?.fontColor;
                let enableScanEffect = this.value?.enableScanEffect;
                let showDefaultPercentage = this.value?.showDefaultPercentage;
                let shadow = this.value?.shadow;
                let status = this.value?.status;
                let strokeRadius = this.value?.strokeRadius;
                let borderRadius = this.value?.borderRadius;
                getUINativeModule().progress.setProgressStyle(node, strokeWidth, scaleCount,
                    scaleWidth, enableSmoothEffect, borderColor, borderWidth, content, fontSize,
                    fontWeight, fontFamily, fontStyle, fontColor, enableScanEffect, showDefaultPercentage,
                    shadow, status, strokeRadius, borderRadius);
            }
        }
        checkObjectDiff(): boolean {
            return true;
        }
    }
    (ProgressStyleModifier as any).identity = Symbol('style');

    class ProgressBackgroundColorModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().progress.resetProgressBackgroundColor(node);
            }
            else {
                getUINativeModule().progress.setProgressBackgroundColor(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
    }
    (ProgressBackgroundColorModifier as any).identity = Symbol('progressBackgroundColor');

    class ProgressContentModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        applyPeer(node: any, reset: boolean, component: any): void {
            let progressComponent = component;
            progressComponent.setContentModifier(this.value);
        }
    }
    (ProgressContentModifier as any).identity = Symbol('progressContentModifier');

    loadComponent.componentObj = {'component' : ArkProgressComponent };
  }
  return loadComponent.componentObj;
}

class JSProgress extends JSContainerBase {
    static create(value: any): void {
        getUINativeModule().progress.create(value?.value, value?.total, value?.style, value?.type);
    }
    static value(value: any): void {
        getUINativeModule().progress.setProgressValue(true, value);
    }
    static color(value: any): void {
        getUINativeModule().progress.setProgressColor(true, value);
    }
    static style(value: any): void {
        let strokeWidth = value?.strokeWidth;
        let scaleCount = value?.scaleCount;
        let scaleWidth = value?.scaleWidth;
        let enableSmoothEffect = value?.enableSmoothEffect;
        let borderColor = value?.borderColor;
        let borderWidth = value?.borderWidth;
        let content = value?.content;
        let fontSize = value?.font?.size;
        let fontWeight = value?.font?.weight;
        let fontFamily = value?.font?.family;
        let fontStyle = value?.font?.style;
        let fontColor = value?.fontColor;
        let enableScanEffect = value?.enableScanEffect;
        let showDefaultPercentage = value?.showDefaultPercentage;
        let shadow = value?.shadow;
        let status = value?.status;
        let strokeRadius = value?.strokeRadius;
        let borderRadius = value?.borderRadius;

        getUINativeModule().progress.setProgressStyle(true, strokeWidth, scaleCount,
            scaleWidth, enableSmoothEffect, borderColor, borderWidth, content, fontSize,
            fontWeight, fontFamily, fontStyle, fontColor, enableScanEffect, showDefaultPercentage,
            shadow, status, strokeRadius, borderRadius);
    }
    static backgroundColor(value: any): void {
        getUINativeModule().progress.setProgressBackgroundColor(true, value);
    }

    static contentModifier(modifier: any): void {
        const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
        let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
        let component = this.createOrGetNode(elmtId, () => {
            return createComponent(nativeNode, 'progress');
        });
        component.setContentModifier(modifier);
    }

    static onClick(event: any): void {
        __Common__.onClick(event);
    }
    static onTouch(event: any): void {
        __Common__.onTouch(event);
    }
    static onKeyEvent(event: any): void {
        __Common__.onKeyEvent(event);
    }
    static onDeleteEvent(event: any): void {
        __Common__.onDeleteEvent(event);
    }
    static onAttach(event: any): void {
        __Common__.onAttach(event);
    }
    static onAppear(event: any): void {
        __Common__.onAppear(event);
    }
    static onDetach(event: any): void {
        __Common__.onDetach(event);
    }
    static onDisAppear(event: any): void {
        __Common__.onDisAppear(event);
    }
    static attributeModifier(modifier: any): void {
        attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
          return createComponent(nativePtr);
        }, (nativePtr: any, classType: any, modifierJS: any) => {
          return new modifierJS.ProgressModifier(nativePtr, classType);
        });
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
  globalThis.ArkProgressComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.Progress = JSProgress;
}

export default { loadComponent, createComponent, exportComponent, exportView };
