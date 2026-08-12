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
        class ArkTextTimerComponent extends globalThis.__ArkComponent__ {
            constructor(nativePtr: any, classType: any) {
                super(nativePtr, classType);
            }
            allowChildCount(): number {
                return 0;
            }
            initialize(value: any): ArkTextTimerComponent {
                if (value.length === 1 && isObject(value[0])) {
                modifierWithKey(this._modifiersWithKeys, TextTimerOptionsModifier.identity, TextTimerOptionsModifier, value[0]);
                } else {
                modifierWithKey(this._modifiersWithKeys, TextTimerOptionsModifier.identity, TextTimerOptionsModifier, undefined);
                }
                return this;
            }
            fontColor(value: any): ArkTextTimerComponent {
                modifierWithKey(this._modifiersWithKeys, TextTimerFontColorModifier.identity, TextTimerFontColorModifier, value);
                return this;
            }
            fontSize(value: any): ArkTextTimerComponent {
                modifierWithKey(this._modifiersWithKeys, TextTimerFontSizeModifier.identity, TextTimerFontSizeModifier, value);
                return this;
            }
            fontWeight(value: any): ArkTextTimerComponent {
                modifierWithKey(this._modifiersWithKeys, TextTimerFontWeightModifier.identity, TextTimerFontWeightModifier, value);
                return this;
            }
            fontStyle(value: any): ArkTextTimerComponent {
                modifierWithKey(this._modifiersWithKeys, TextTimerFontStyleModifier.identity, TextTimerFontStyleModifier, value);
                return this;
            }
            fontFamily(value: any): ArkTextTimerComponent {
                modifierWithKey(this._modifiersWithKeys, TextTimerFontFamilyModifier.identity, TextTimerFontFamilyModifier, value);
                return this;
            }
            format(value: any): ArkTextTimerComponent {
                modifierWithKey(this._modifiersWithKeys, TextTimerFormatModifier.identity, TextTimerFormatModifier, value);
                return this;
            }
            textShadow(value: any): ArkTextTimerComponent {
                modifierWithKey(this._modifiersWithKeys, TextTimerTextShadowModifier.identity, TextTimerTextShadowModifier, value);
                return this;
            }
            contentModifier(value: any): ArkTextTimerComponent {
                modifierWithKey(this._modifiersWithKeys, TextTimerContentModifier.identity, TextTimerContentModifier, value);
                return this;
            }
            setContentModifier(modifier: any): void {
                if (modifier === undefined || modifier === null) {
                getUINativeModule().texttimer.setContentModifierBuilder(this.nativePtr, false);
                return;
                }
                this.needRebuild = false;
                this.applyContent = modifier.applyContent();
                if (this.builder !== this.applyContent) {
                this.needRebuild = true;
                }
                this.builder = modifier.applyContent();
                this.modifier = modifier;
                getUINativeModule().texttimer.setContentModifierBuilder(this.nativePtr, this);
            }
            makeContentModifierNode(context: any, textTimerConfiguration: any) {
                textTimerConfiguration.contentModifier = this.modifier;
                if (isUndefined(this.textTimerNode) || this.needRebuild) {
                let xNode = globalThis.requireNapi('arkui.node');
                this.textTimerNode = new xNode.BuilderNode(context);
                this.textTimerNode.build(this.builder, textTimerConfiguration);
                this.needRebuild = false;
                } else {
                this.textTimerNode.update(textTimerConfiguration);
                }
                return this.textTimerNode.getFrameNode();
            }
            onTimer(event: any): ArkTextTimerComponent {
                modifierWithKey(this._modifiersWithKeys, TextTimerOnTimerModifier.identity, TextTimerOnTimerModifier, event);
                return this;
            }
        }

        class TextTimerOnTimerModifier extends ModifierWithKey {
            constructor(value: any) {
                super(value);
            }
            applyPeer(node: any, reset: boolean) {
                if (reset) {
                    getUINativeModule().texttimer.resetTextTimerOnTimer(node);
                } else {
                    getUINativeModule().texttimer.setTextTimerOnTimer(node, this.value);
                }
            }
        }
        TextTimerOnTimerModifier.identity = Symbol('textTimerOnTimer');

        class TextTimerOptionsModifier extends ModifierWithKey {
            constructor(value: any) {
                super(value);
            }
            applyPeer(node: any, reset: boolean) {
                let _a, _b, _c, _d;
                if (reset) {
                    getUINativeModule().texttimer.setTextTimerOptions(node, undefined, undefined, undefined, undefined);
                }
                else {
                    getUINativeModule().texttimer.setTextTimerOptions(node,
                    (_a = this.value) === null || _a === void 0 ? void 0 : _a.isCountDown,
                    (_b = this.value) === null || _b === void 0 ? void 0 : _b.count,
                    (_c = this.value) === null || _c === void 0 ? void 0 : _c.controller,
                    (_d = this.value) === null || _d === void 0 ? void 0 : _d.startTime);
                }
            }
            checkObjectDiff() {
                let _a, _b, _c, _d, _e, _f, _g, _h;
                return !isBaseOrResourceEqual((_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.isCountDown,
                    (_b = this.value) === null || _b === void 0 ? void 0 : _b.isCountDown) ||
                    !isBaseOrResourceEqual((_c = this.stageValue) === null || _c === void 0 ? void 0 : _c.count,
                        (_d = this.value) === null || _d === void 0 ? void 0 : _d.count) ||
                    !isBaseOrResourceEqual((_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.controller,
                        (_f = this.value) === null || _f === void 0 ? void 0 : _f.controller) ||
                    !isBaseOrResourceEqual((_g = this.stageValue) === null || _g === void 0 ? void 0 : _g.startTime,
                        (_h = this.value) === null || _h === void 0 ? void 0 : _h.startTime);
            }
        }
        TextTimerOptionsModifier.identity = Symbol('textTimerOptions');

        class TextTimerFontColorModifier extends ModifierWithKey {
            applyPeer(node: any, reset: boolean) {
                if (reset) {
                    getUINativeModule().texttimer.resetFontColor(node);
                }
                else {
                    getUINativeModule().texttimer.setFontColor(node, this.value);
                }
            }
            checkObjectDiff() {
                return !isBaseOrResourceEqual(this.stageValue, this.value);
            }
        }
        TextTimerFontColorModifier.identity = Symbol('fontColor');

        class TextTimerFontSizeModifier extends ModifierWithKey {
            applyPeer(node: any, reset: boolean) {
                if (reset) {
                    getUINativeModule().texttimer.resetFontSize(node);
                }
                else {
                    getUINativeModule().texttimer.setFontSize(node, this.value);
                }
            }
            checkObjectDiff() {
                return !isBaseOrResourceEqual(this.stageValue, this.value);
            }
        }
        TextTimerFontSizeModifier.identity = Symbol('fontSize');

        class TextTimerFontWeightModifier extends ModifierWithKey {
            applyPeer(node: any, reset: boolean) {
                if (reset) {
                    getUINativeModule().texttimer.resetFontWeight(node);
                }
                else {
                    getUINativeModule().texttimer.setFontWeight(node, this.value);
                }
            }
        }
        TextTimerFontWeightModifier.identity = Symbol('fontWeight');

        class TextTimerFontStyleModifier extends ModifierWithKey {
            applyPeer(node: any, reset: boolean) {
                if (reset) {
                    getUINativeModule().texttimer.resetFontStyle(node);
                }
                else {
                    getUINativeModule().texttimer.setFontStyle(node, this.value);
                }
            }
            checkObjectDiff() {
                return !isBaseOrResourceEqual(this.stageValue, this.value);
            }
        }
        TextTimerFontStyleModifier.identity = Symbol('fontStyle');

        class TextTimerFontFamilyModifier extends ModifierWithKey {
            applyPeer(node: any, reset: boolean) {
                if (reset) {
                    getUINativeModule().texttimer.resetFontFamily(node);
                }
                else {
                    getUINativeModule().texttimer.setFontFamily(node, this.value);
                }
            }
            checkObjectDiff() {
                return !isBaseOrResourceEqual(this.stageValue, this.value);
            }
        }
        TextTimerFontFamilyModifier.identity = Symbol('fontFamily');

        class TextTimerFormatModifier extends ModifierWithKey {
            applyPeer(node: any, reset: boolean) {
                if (reset) {
                    getUINativeModule().texttimer.resetFormat(node);
                }
                else {
                    getUINativeModule().texttimer.setFormat(node, this.value);
                }
            }
        }
        TextTimerFormatModifier.identity = Symbol('textTimerFormat');

        class TextTimerTextShadowModifier extends ModifierWithKey {
            constructor(value: any) {
                super(value);
            }
            applyPeer(node: any, reset: boolean) {
                if (reset) {
                    getUINativeModule().texttimer.resetTextShadow(node);
                }
                else {
                    let shadow = new ArkShadowInfoToArray();
                    if (!shadow.convertShadowOptions(this.value)) {
                        getUINativeModule().texttimer.resetTextShadow(node);
                    }
                    else {
                        getUINativeModule().texttimer.setTextShadow(node, shadow.radius, shadow.type, shadow.color,
                        shadow.offsetX, shadow.offsetY, shadow.fill, shadow.radius.length);
                    }
                }
            }
            checkObjectDiff() {
                let checkDiff = true;
                let arkShadow = new ArkShadowInfoToArray();
                if (Object.getPrototypeOf(this.stageValue).constructor === Object &&
                Object.getPrototypeOf(this.value).constructor === Object) {
                    checkDiff = arkShadow.checkDiff(this.stageValue, this.value);
                }
                else if (Object.getPrototypeOf(this.stageValue).constructor === Array &&
                Object.getPrototypeOf(this.value).constructor === Array &&
                this.stageValue.length === this.value.length) {
                    let isDiffItem = false;
                    for (let i = 0; i < this.value.length; i++) {
                        if (arkShadow.checkDiff(this.stageValue[i], this.value[i])) {
                            isDiffItem = true;
                            break;
                        }
                    }
                    if (!isDiffItem) {
                        checkDiff = false;
                    }
                }
                return checkDiff;
            }
        }
        TextTimerTextShadowModifier.identity = Symbol('textTimerTextShadow');

        class TextTimerContentModifier extends ModifierWithKey {
            constructor(value: any) {
                super(value);
            }
            applyPeer(node: any, reset: boolean, component: any) {
                let textTimerComponent = component;
                textTimerComponent.setContentModifier(this.value);
            }
        }
        TextTimerContentModifier.identity = Symbol('textTimerContentModifier');
    loadComponent.componentObj = {'component' : ArkTextTimerComponent };
  }
  return loadComponent.componentObj;
}

class JSTextTimer extends JSViewAbstract {
    static create(value: any): void {
        getUINativeModule().texttimer.create(value?.isCountDown, value?.count, value?.controller, value?.startTime);
    }

    static fontColor(value: any): void {
        getUINativeModule().texttimer.setFontColor(true, value);
    }

    static fontSize(value: any): void {
        getUINativeModule().texttimer.setFontSize(true, value);
    }

    static fontWeight(value: any): void {
        getUINativeModule().texttimer.setFontWeight(true, value);
    }

    static fontStyle(value: any): void {
        getUINativeModule().texttimer.setFontStyle(true, value);
    }

    static fontFamily(value: any): void {
        getUINativeModule().texttimer.setFontFamily(true, value);
    }

    static format(value: any): void {
        getUINativeModule().texttimer.setFormat(true, value);
    }

    static textShadow(value: any): void {
        let shadow = new ArkShadowInfoToArray();
        if (value && shadow.convertShadowOptions(value)) {
            getUINativeModule().texttimer.setTextShadow(true, shadow.radius, shadow.type, shadow.color,
                shadow.offsetX, shadow.offsetY, shadow.fill, shadow.radius.length);
        }
    }

    static onTimer(value: any): void {
        getUINativeModule().texttimer.setTextTimerOnTimer(true, value);
    }

    static onClick(event: any): void {
        __Common__.onClick(event);
    }
    static onTouch(event: any): void {
        __Common__.onTouch(event);
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
          return new modifierJS.TextTimerModifier(nativePtr, classType);
        });
    }
    
    static contentModifier(modifier: any): void {
        const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
        let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
        let component = this.createOrGetNode(elmtId, () => {
            return createComponent(nativeNode, 'texttimer');
        });
        component.setContentModifier(modifier);
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
  globalThis.ArkTextTimerComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.TextTimer = JSTextTimer;
}

export default { loadComponent, createComponent, exportComponent, exportView };
