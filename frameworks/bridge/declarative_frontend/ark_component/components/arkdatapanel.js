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

/// <reference path='./import.ts' />
function loadComponent() {
  if (globalThis.__ArkComponent__ !== undefined && loadComponent.componentObj === undefined) {
    class ArkDataPanelComponent extends ArkComponent {
      constructor(nativePtr, classType) {
        super(nativePtr, classType);
      }
      closeEffect(value) {
        modifierWithKey(this._modifiersWithKeys, DataPanelCloseEffectModifier.identity, DataPanelCloseEffectModifier, value);
        return this;
      }
      valueColors(value) {
        modifierWithKey(this._modifiersWithKeys, DataPanelValueColorsModifier.identity, DataPanelValueColorsModifier, value);
        return this;
      }
      trackBackgroundColor(value) {
        modifierWithKey(this._modifiersWithKeys, DataPanelTrackBackgroundColorModifier.identity, DataPanelTrackBackgroundColorModifier, value);
        return this;
      }
      strokeWidth(value) {
        modifierWithKey(this._modifiersWithKeys, DataPanelStrokeWidthModifier.identity, DataPanelStrokeWidthModifier, value);
        return this;
      }
      trackShadow(value) {
        modifierWithKey(this._modifiersWithKeys, DataPanelTrackShadowModifier.identity, DataPanelTrackShadowModifier, value);
        return this;
      }
      borderRadius(value) {
        return this;
      }
      contentModifier(value) {
        modifierWithKey(this._modifiersWithKeys, DataPanelContentModifier.identity, DataPanelContentModifier, value);
        return this;
      }
      setContentModifier(modifier) {
        if (modifier === undefined || modifier === null) {
          getUINativeModule().dataPanel.setContentModifierBuilder(this.nativePtr, false);
          return;
        }
        if (this.builder !== modifier.applyContent()) {
          this.needRebuild = true;
        }
        this.builder = modifier.applyContent();
        this.modifier = modifier;
        getUINativeModule().dataPanel.setContentModifierBuilder(this.nativePtr, this);
      }
      makeContentModifierNode(context, dataPanelConfig) {
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
    class DataPanelStrokeWidthModifier extends ModifierWithKey {
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().dataPanel.resetDataPanelStrokeWidth(node);
        }
        else {
          getUINativeModule().dataPanel.setDataPanelStrokeWidth(node, this.value);
        }
      }
      checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    DataPanelStrokeWidthModifier.identity = Symbol('dataPanelStrokeWidth');
    class DataPanelCloseEffectModifier extends ModifierWithKey {
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().dataPanel.resetCloseEffect(node);
        }
        else {
          getUINativeModule().dataPanel.setCloseEffect(node, this.value);
        }
      }
      checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    DataPanelCloseEffectModifier.identity = Symbol('dataPanelCloseEffect');
    class DataPanelTrackBackgroundColorModifier extends ModifierWithKey {
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().dataPanel.resetDataPanelTrackBackgroundColor(node);
        }
        else {
          getUINativeModule().dataPanel.setDataPanelTrackBackgroundColor(node, this.value);
        }
      }
      checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    DataPanelTrackBackgroundColorModifier.identity = Symbol('dataPanelTrackBackgroundColorModifier');
    class DataPanelTrackShadowModifier extends ModifierWithKey {
      applyPeer(node, reset) {
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
      checkObjectDiff() {
        return true;
      }
    }
    DataPanelTrackShadowModifier.identity = Symbol('dataPanelTrackShadow');
    class DataPanelContentModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset, component) {
        let dataPanelComponent = component;
        dataPanelComponent.setContentModifier(this.value);
      }
    }
    DataPanelContentModifier.identity = Symbol('dataPanelContentModifier');
    class DataPanelValueColorsModifier extends ModifierWithKey {
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().dataPanel.resetDataPanelValueColors(node);
          return;
        }
        else {
          getUINativeModule().dataPanel.setDataPanelValueColors(node, this.value);
        }
      }
      checkObjectDiff() {
        return true;
      }
    }
    DataPanelValueColorsModifier.identity = Symbol('dataPanelValueColors');
    loadComponent.componentObj = {'component' : ArkDataPanelComponent };
  }
  return loadComponent.componentObj;
}

class JSDataPanel extends JSViewAbstract {
    static create(params) {
        getUINativeModule().dataPanel.create(params);
    }

    static closeEffect(value) {
        getUINativeModule().dataPanel.setCloseEffect(true, value);
    }
    static valueColors(value) {
        getUINativeModule().dataPanel.setDataPanelValueColors(true, value);
    }
    static trackBackgroundColor(value) {
        getUINativeModule().dataPanel.setDataPanelTrackBackgroundColor(true, value);
    }
    static strokeWidth(value) {
        getUINativeModule().dataPanel.setDataPanelStrokeWidth(true, value);
    }
    static trackShadow(value) {
        getUINativeModule().dataPanel.setDataPanelTrackShadow(true, value);
    }
    static borderRadius(value) {
        getUINativeModule().dataPanel.setDataPanelBorderRadius(value);
    }
    static attributeModifier(modifier) {
        attributeModifierFunc.call(this, modifier, (nativePtr) => {
            return createComponent(nativePtr);
        }, (nativePtr, classType, modifierJS) => {
            return new modifierJS.DataPanelModifier(nativePtr, classType);
        });
    }

    static contentModifier(modifier) {
        const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
        let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
        let component = this.createOrGetNode(elmtId, () => {
            return createComponent(nativeNode, 'dataPanel');
        });
        component.setContentModifier(modifier);
    }

    static onClick(value) {
        __Common__.onClick(value);
    }
    static onKeyEvent(value) {
        __Common__.onKeyEvent(value);
    }
    static onDeleteEvent(value) {
        __Common__.onDeleteEvent(value);
    }
    static onAttach(value) {
        __Common__.onAttach(value);
    }
    static onAppear(value) {
        __Common__.onAppear(value);
    }
    static onDetach(value) {
        __Common__.onAttach(value);
    }
    static onDisAppear(value) {
        __Common__.onDisAppear(value);
    }
    static onTouch(value) {
        __Common__.onTouch(value);
    }
    static onHover(value) {
        __Common__.onHover(value);
    }
}

function createComponent(nativePtr, classType) {
 	if (loadComponent.componentObj !== undefined) {
 	    return new loadComponent.componentObj.component(nativePtr, classType);
 	}
    return undefined;
}

function exportComponent() {
    globalThis.ArkDataPanelComponent = ArkDataPanelComponent;
}

function exportView() {
    globalThis.DataPanel = JSDataPanel;
}

export default { loadComponent, createComponent, exportComponent, exportView };