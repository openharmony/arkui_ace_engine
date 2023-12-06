/// <reference path='./import.ts' />
class ArkDataPanelComponent extends ArkComponent implements DataPanelAttribute {
  closeEffect(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, DataPanelCloseEffectModifier.identity, DataPanelCloseEffectModifier, value);
    return this;
  }
  valueColors(value: any[]): this {
    throw new Error('Method not implemented.');
  }
  trackBackgroundColor(value: any): this {
    modifierWithKey(this._modifiersWithKeys, DataPanelTrackBackgroundColorModifier.identity, DataPanelTrackBackgroundColorModifier, value);
    return this;
  }
  strokeWidth(value: any): this {
    modifierWithKey(this._modifiersWithKeys, DataPanelStrokeWidthModifier.identity, DataPanelStrokeWidthModifier, value);
    return this;
  }
  trackShadow(value: DataPanelShadowOptions): this {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

class DataPanelStrokeWidthModifier extends ModifierWithKey<Length> {
  static identity: Symbol = Symbol('dataPanelStrokeWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().dataPanel.resetDataPanelStrokeWidth(node);
    } else {
      GetUINativeModule().dataPanel.setDataPanelStrokeWidth(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

class DataPanelCloseEffectModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('dataPanelCloseEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().dataPanel.resetCloseEffect(node);
    } else {
      GetUINativeModule().dataPanel.setCloseEffect(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

class DataPanelTrackBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  static identity: Symbol = Symbol('dataPanelTrackBackgroundColorModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().dataPanel.resetDataPanelTrackBackgroundColor(node);
    } else {
      GetUINativeModule().dataPanel.setDataPanelTrackBackgroundColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

// @ts-ignore
globalThis.DataPanel.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkDataPanelComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
