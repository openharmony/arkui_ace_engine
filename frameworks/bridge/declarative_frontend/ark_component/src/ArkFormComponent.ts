/// <reference path="./import.ts" />
class ArkFormComponentComponent extends ArkComponent implements FormComponentAttribute {
  size(value: { width: number; height: number }): this {
      if (isObject(value)) {
          let size = new ArkBlockSize();
          size.width = value.width;
          size.height = value.height;
          modifier(this._modifiers, FormComponentSizeModifier, size);
      } else {
          modifier(this._modifiers, FormComponentSizeModifier, undefined);
      }
      return this;
  }

  visibility(value: Visibility): this {
      if (isNumber(value)) {
          modifier(this._modifiers, FormComponentVisibilityModifier, value);
      } else {
          modifier(this._modifiers, FormComponentVisibilityModifier, undefined);
      }
      return this;
  }

  moduleName(value: string): this {
      if (isString(value)) {
          modifier(this._modifiers, FormComponentModuleNameModifier, value);
      } else {
          modifier(this._modifiers, FormComponentModuleNameModifier, undefined);
      }
      return this;
  }
  dimension(value: FormDimension): this {
      if (isNumber(value)) {
          modifier(this._modifiers, FormComponentDimensionModifier, value);
      } else {
          modifier(this._modifiers, FormComponentDimensionModifier, undefined);
      }
      return this;
  }
  allowUpdate(value: boolean): this {
      if (isBoolean(value)) {
          modifier(this._modifiers, FormComponentAllowUpdateModifier, value);
      } else {
          modifier(this._modifiers, FormComponentAllowUpdateModifier, undefined);
      }
      return this;
  }
  onAcquired(callback: (info: { id: number; }) => void): this {
      throw new Error("Method not implemented.");
  }
  onError(callback: (info: { errcode: number; msg: string; }) => void): this {
      throw new Error("Method not implemented.");
  }
  onRouter(callback: (info: any) => void): this {
      throw new Error("Method not implemented.");
  }
  onUninstall(callback: (info: { id: number; }) => void): this {
      throw new Error("Method not implemented.");
  }
  onLoad(callback: () => void): this {
      throw new Error("Method not implemented.");
  }
}

class FormComponentModuleNameModifier extends Modifier<string> {
  static identity: Symbol = Symbol("formComponentModuleName");
  applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
          GetUINativeModule().formComponent.resetModuleName(node);
      } else {
          GetUINativeModule().formComponent.setModuleName(node, this.value!);
      }
  }
}
class FormComponentDimensionModifier extends Modifier<number> {
  static identity: Symbol = Symbol("formComponentDimension");
  applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
          GetUINativeModule().formComponent.resetDimension(node);
      } else {
          GetUINativeModule().formComponent.setDimension(node, this.value!);
      }
  }
}
class FormComponentAllowUpdateModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol("formComponentAllowUpdate");
  applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
          GetUINativeModule().formComponent.resetAllowUpdate(node);
      } else {
          GetUINativeModule().formComponent.setAllowUpdate(node, this.value!);
      }
  }
}
class FormComponentSizeModifier extends Modifier<ArkBlockSize> {
  static identity: Symbol = Symbol("formComponentSize");
  applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
          GetUINativeModule().formComponent.resetSize(node);
      } else {
          GetUINativeModule().formComponent.setSize(node, this.value.width, this.value.width);
      }
  }
}
class FormComponentVisibilityModifier extends Modifier<number> {
  static identity: Symbol = Symbol("formComponentVisibility");
  applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
          GetUINativeModule().formComponent.resetVisibility(node);
      } else {
          GetUINativeModule().formComponent.setVisibility(node, this.value);
      }
  }
}

// @ts-ignore
globalThis.FormComponent.attributeModifier = function(modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () =>
  {
      return new ArkFormComponentComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
