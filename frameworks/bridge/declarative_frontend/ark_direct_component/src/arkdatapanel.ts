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
    class ArkDataPanelComponent extends globalThis.__ArkComponent__ {
        constructor(nativePtr: any, classType: any) {
            super(nativePtr, classType);
        }
        closeEffect(value: boolean): this {
            modifierWithKey(this._modifiersWithKeys, DataPanelCloseEffectModifier.identity, DataPanelCloseEffectModifier, value);
            return this;
        }
        valueColors(value: any): this {
            modifierWithKey(this._modifiersWithKeys, DataPanelValueColorsModifier.identity, DataPanelValueColorsModifier, value);
            return this;
        }
        trackBackgroundColor(value: any): this {
            modifierWithKey(this._modifiersWithKeys, DataPanelTrackBackgroundColorModifier.identity, DataPanelTrackBackgroundColorModifier, value);
            return this;
        }
        strokeWidth(value: any): this {
            modifierWithKey(this._modifiersWithKeys, DataPanelStrokeWidthModifier.identity, DataPanelStrokeWidthModifier, value);
            return this;
        }
        trackShadow(value: any): this {
            modifierWithKey(this._modifiersWithKeys, DataPanelTrackShadowModifier.identity, DataPanelTrackShadowModifier, value);
            return this;
        }
        borderRadius(value: any): this {
            return this;
        }
        contentModifier(value: any): this {
            modifierWithKey(this._modifiersWithKeys, DataPanelContentModifier.identity, DataPanelContentModifier, value);
            return this;
        }
        setContentModifier(modifier: any): this {
            if (modifier === undefined || modifier === null) {
                getUINativeModule().dataPanel.setContentModifierBuilder(this.nativePtr, false);
                return this;
            }
            this.needRebuild = false;
            if (this.builder !== modifier.applyContent()) {
                this.needRebuild = true;
            }
            this.builder = modifier.applyContent();
            this.modifier = modifier;
            getUINativeModule().dataPanel.setContentModifierBuilder(this.nativePtr, this);
            return this;
        }
        makeContentModifierNode(context: any, dataPanelConfig: any): any {
            dataPanelConfig.contentModifier = this.modifier;
            if (isUndefined(this.dataPanelNode) || this.needRebuild) {
                let xNode = globalThis.requireNapi('arkui.node');
                this.dataPanelNode = new xNode.BuilderNode(context);
                this.dataPanelNode.build(this.builder, dataPanelConfig);
                this.needRebuild = false;
            } else {
                this.dataPanelNode.update(dataPanelConfig);
            }
            return this.dataPanelNode.getFrameNode();
        }
    }

    class DataPanelStrokeWidthModifier extends ModifierWithKey<any> {
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().dataPanel.resetDataPanelStrokeWidth(node);
            }
            else {
                getUINativeModule().dataPanel.setDataPanelStrokeWidth(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
    }
    (DataPanelStrokeWidthModifier as any).identity = Symbol('dataPanelStrokeWidth');

    class DataPanelCloseEffectModifier extends ModifierWithKey<any> {
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().dataPanel.resetCloseEffect(node);
            }
            else {
                getUINativeModule().dataPanel.setCloseEffect(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
    }
    (DataPanelCloseEffectModifier as any).identity = Symbol('dataPanelCloseEffect');

    class DataPanelTrackBackgroundColorModifier extends ModifierWithKey<any> {
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().dataPanel.resetDataPanelTrackBackgroundColor(node);
            }
            else {
                getUINativeModule().dataPanel.setDataPanelTrackBackgroundColor(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return !isBaseOrResourceEqual(this.stageValue, this.value);
        }
    }
    (DataPanelTrackBackgroundColorModifier as any).identity = Symbol('dataPanelTrackBackgroundColorModifier');

    class DataPanelTrackShadowModifier extends ModifierWithKey<any> {
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                if (this.value === null) {
                    getUINativeModule().dataPanel.setDataPanelTrackShadow(node, null);
                }
                getUINativeModule().dataPanel.resetDataPanelTrackShadow(node);
            }
            else {
                getUINativeModule().dataPanel.setDataPanelTrackShadow(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return true;
        }
    }
    (DataPanelTrackShadowModifier as any).identity = Symbol('dataPanelTrackShadow');

    class DataPanelContentModifier extends ModifierWithKey<any> {
        constructor(value: any) {
            super(value);
        }
        applyPeer(node: any, reset: boolean, component: any): void {
            let dataPanelComponent = component;
            dataPanelComponent.setContentModifier(this.value);
        }
    }
    (DataPanelContentModifier as any).identity = Symbol('dataPanelContentModifier');

    class DataPanelValueColorsModifier extends ModifierWithKey<any> {
        applyPeer(node: any, reset: boolean): void {
            if (reset) {
                getUINativeModule().dataPanel.resetDataPanelValueColors(node);
                return;
            }
            else {
                getUINativeModule().dataPanel.setDataPanelValueColors(node, this.value);
            }
        }
        checkObjectDiff(): boolean {
            return true;
        }
    }
    (DataPanelValueColorsModifier as any).identity = Symbol('dataPanelValueColors');

    loadComponent.componentObj = {'component' : ArkDataPanelComponent };
  }
  return loadComponent.componentObj;
}

class JSDataPanel extends JSViewAbstract {
    static create(params: any): void {
        getUINativeModule().dataPanel.create(params);
    }

    static closeEffect(value: any): void {
        getUINativeModule().dataPanel.setCloseEffect(true, value);
    }
    static valueColors(value: any): void {
        getUINativeModule().dataPanel.setDataPanelValueColors(true, value);
    }
    static trackBackgroundColor(value: any): void {
        getUINativeModule().dataPanel.setDataPanelTrackBackgroundColor(true, value);
    }
    static strokeWidth(value: any): void {
        getUINativeModule().dataPanel.setDataPanelStrokeWidth(true, value);
    }
    static trackShadow(value: any): void {
        getUINativeModule().dataPanel.setDataPanelTrackShadow(true, value);
    }
    static borderRadius(value: any): void {
        getUINativeModule().dataPanel.setDataPanelBorderRadius(value);
    }
    static attributeModifier(modifier: any): void {
        attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
            return createComponent(nativePtr);
        }, (nativePtr: any, classType: any, modifierJS: any) => {
            return new modifierJS.DataPanelModifier(nativePtr, classType);
        });
    }

    static contentModifier(modifier: any): void {
        const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
        let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
        let component = this.createOrGetNode(elmtId, () => {
            return createComponent(nativeNode, 'dataPanel');
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
        __Common__.onAttach(value);
    }
    static onDisAppear(value: any): void {
        __Common__.onDisAppear(value);
    }
    static onTouch(value: any): void {
        __Common__.onTouch(value);
    }
    static onHover(value: any): void {
        __Common__.onHover(value);
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
    globalThis.ArkDataPanelComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
    globalThis.DataPanel = JSDataPanel;
}

export default { loadComponent, createComponent, exportComponent, exportView };
