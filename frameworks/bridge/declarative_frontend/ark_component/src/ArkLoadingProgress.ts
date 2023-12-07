
/// <reference path='./import.ts' />
class ArkLoadingProgressComponent extends ArkComponent implements LoadingProgressAttribute {
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    throw new Error('Method not implemented.');
  }
  color(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, LoadingProgressColorModifier.identity, LoadingProgressColorModifier, value);
    return this;
  }
  enableLoading(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, LoadingProgressEnableLoadingModifier.identity, LoadingProgressEnableLoadingModifier, value);
    return this;
  }
}

class LoadingProgressColorModifier extends ModifierWithKey<ResourceColor> {
  static identity: Symbol = Symbol('loadingProgressColor');
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().loadingProgress.resetColor(node);
    }
    else {
      GetUINativeModule().loadingProgress.setColor(node, this.value);
    }
  }

  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class LoadingProgressEnableLoadingModifier extends ModifierWithKey<boolean> {
  static identity: Symbol = Symbol('loadingProgressEnableLoading');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().loadingProgress.resetEnableLoading(node);
    }
    else {
      GetUINativeModule().loadingProgress.setEnableLoading(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.LoadingProgress.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkLoadingProgressComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
