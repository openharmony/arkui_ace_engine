/// <reference path="./import.ts" />
class SideBarContainerPositionModifier extends Modifier<number> {
  static identity: Symbol = Symbol('sideBarContainerPosition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().sideBarContainer.resetSideBarPosition(node);
    } else {
      GetUINativeModule().sideBarContainer.setSideBarPosition(node, this.value!);
    }
  }
}

class SideBarContainerAutoHideModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('sideBarContainerautoHide');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().sideBarContainer.resetAutoHide(node);
    } else {
      GetUINativeModule().sideBarContainer.setAutoHide(node, this.value!);
    }
  }
}

class SideBarContainerShowSideBarModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('sideBarContainerShowSideBar');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().sideBarContainer.resetShowSideBar(node);
    } else {
      GetUINativeModule().sideBarContainer.setShowSideBar(node, this.value!);
    }
  }
}

class SideBarContainerMaxSideBarWidthModifier extends Modifier<number | string> {
  static identity: Symbol = Symbol('sideBarContainerMaxSideBarWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().sideBarContainer.resetMaxSideBarWidth(node);
    } else {
      GetUINativeModule().sideBarContainer.setMaxSideBarWidth(node, this.value!);
    }
  }
}

class SideBarContainerWidthModifier extends Modifier<number | string> {
  static identity: Symbol = Symbol('sideBarContainerWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().sideBarContainer.resetSideBarWidth(node);
    } else {
      GetUINativeModule().sideBarContainer.setSideBarWidth(node, this.value!);
    }
  }
}

class SideBarContainerMinContentWidthModifier extends Modifier<string> {
  static identity: Symbol = Symbol('sideBarContainerMinContentWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().sideBarContainer.resetMinContentWidth(node);
    } else {
      GetUINativeModule().sideBarContainer.setMinContentWidth(node, this.value!);
    }
  }
}

class SideBarContainerShowControlButtonModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('sideBarContainerShowControlButton');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().sideBarContainer.resetShowControlButton(node);
    } else {
      GetUINativeModule().sideBarContainer.setShowControlButton(node, this.value!);
    }
  }
}

class SideBarContainerMinSideBarWidthModifier extends Modifier<number | string> {
  static identity: Symbol = Symbol('sideBarContainerMinSideBarWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().sideBarContainer.resetMinSideBarWidth(node);
    } else {
      GetUINativeModule().sideBarContainer.setMinSideBarWidth(node, this.value!);
    }
  }
}

class SideBarContainerControlButtonModifier extends Modifier<ArkButtonStyle> {
  static identity: Symbol = Symbol('sideBarContainercontrolButton');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().sideBarContainer.resetControlButton(node);
    } else {
      GetUINativeModule().sideBarContainer.setControlButton(node, this.value.left,
        this.value.top, this.value.width, this.value.height, this.value.icons.shown,
        this.value.icons.hidden, this.value.icons.switching);
    }
  }
}

class SideBarContainerDividerModifier extends Modifier<ArkSideBarDividerStyle> {
  static identity: Symbol = Symbol('sideBarContainerdivider');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().sideBarContainer.resetDivider(node);
    } else {
      GetUINativeModule().sideBarContainer.setDivider(node, this.value.strokeWidth,
        this.value.color, this.value.startMargin, this.value.endMargin);
    }
  }
}

class ArkSideBarContainerComponent extends ArkComponent implements SideBarContainerAttribute {
  onChange(callback: (value: boolean) => void): SideBarContainerAttribute {
    throw new Error("Method not implemented.");
  }
  autoHide(value: boolean): SideBarContainerAttribute {
    if (isBoolean(value)) {
      modifier(this._modifiers, SideBarContainerAutoHideModifier, value);
    } else {
      modifier(this._modifiers, SideBarContainerAutoHideModifier, true);
    }
    return this;
  }
  showSideBar(value: boolean): SideBarContainerAttribute {
    let isShow: boolean = true;
    if (isBoolean(value)) {
      isShow = value;
    }
    modifier(this._modifiers, SideBarContainerShowSideBarModifier, isShow);
    return this;
  }

  maxSideBarWidth(value: number | Length): SideBarContainerAttribute {
    let maxSideBarWidth: number = 280;
    if (isNumber(value)) {
      let numberValue = <number>value;
      if (numberValue < 0) {
        modifier(this._modifiers, SideBarContainerMaxSideBarWidthModifier, maxSideBarWidth);
      } else {
        modifier(this._modifiers, SideBarContainerMaxSideBarWidthModifier, numberValue);
      }
    } else if (isLengthType(value)) {
      let arkValue = <number | string>value;
      modifier(this._modifiers, SideBarContainerMaxSideBarWidthModifier, arkValue);
    } else {
      modifier(this._modifiers, SideBarContainerMaxSideBarWidthModifier, maxSideBarWidth);
    }
    return this;
  }

  minSideBarWidth(value: number | Length): SideBarContainerAttribute {
    let minSideBarWidth: number = 240;
    if (isNumber(value)) {
      let numberValue: number = <number>value;
      if (numberValue < 0) {
        modifier(this._modifiers, SideBarContainerMinSideBarWidthModifier, minSideBarWidth);
      } else {
        modifier(this._modifiers, SideBarContainerMinSideBarWidthModifier, numberValue);
      }
    } else if (isLengthType(value)) {
      let _lengthValue: number | string = <number | string>value;
      modifier(this._modifiers, SideBarContainerMinSideBarWidthModifier, _lengthValue);
    } else {
      modifier(this._modifiers, SideBarContainerMinSideBarWidthModifier, minSideBarWidth);
    }
    return this;
  }

  minContentWidth(value: Dimension): SideBarContainerAttribute {
    let minContentWidth: string = '360vp';
    if (isLengthType(value)) {
      let _lengthValue: number | string = <number | string>value;
      modifier(this._modifiers, SideBarContainerMinContentWidthModifier, _lengthValue);
    } else {
      modifier(this._modifiers, SideBarContainerMinContentWidthModifier, minContentWidth);
    }
    return this;
  }

  controlButton(value: ButtonStyle): SideBarContainerAttribute {
    let arkValue: ArkButtonStyle = new ArkButtonStyle();
    if (value.left && isNumber(value.left) && !isNaN(value.left)) {
      arkValue.left = value.left;
    }
    if (value.top && isNumber(value.top) && !isNaN(value.top)) {
      arkValue.top = value.top;
    }
    if (value.width && isNumber(value.width) && !isNaN(value.width)) {
      arkValue.width = value.width;
    }
    if (value.height && isNumber(value.height) && !isNaN(value.height)) {
      arkValue.height = value.height;
    }
    if (!value.icons || !isObject(value.icons)) {
      arkValue.icons = undefined;
    }
    else {
      if (isString(value.icons.shown)) {
        arkValue.icons!.shown = <string>value.icons.shown;
      }
      if (isString(value.icons.hidden)) {
        arkValue.icons!.hidden = <string>value.icons.hidden;
      }
      if (isString(value.icons.switching)) {
        arkValue.icons!.switching = <string>value.icons.switching;
      }
    }
    modifier(this._modifiers, SideBarContainerControlButtonModifier, arkValue);
    return this;

  }

  divider(value: DividerStyle | null): SideBarContainerAttribute {
    let arkValue: ArkSideBarDividerStyle = new ArkSideBarDividerStyle();
    if (value === null || !isObject(value) || !isLengthType(value.strokeWidth)) {
      modifier(this._modifiers, SideBarContainerDividerModifier, arkValue);
    } else {
      arkValue.strokeWidth = <number | string>value.strokeWidth;
      let arkColor: ArkColor = new ArkColor();
      if (arkColor.parseColorValue(value.color)) {
        arkValue.color = <number | string>value.color;
      }
      if (isLengthType(value.startMargin)) {
        arkValue.startMargin = <number | string>value.startMargin;
      }
      if (isLengthType(value.endMargin)) {
        arkValue.endMargin = <number | string>value.endMargin;
      }
      modifier(this._modifiers, SideBarContainerDividerModifier, arkValue);
    }
    return this;
  }

  sideBarPosition(value: SideBarPosition): SideBarContainerAttribute {
    if (!(value in SideBarPosition)) {
      modifier(this._modifiers, SideBarContainerPositionModifier, SideBarPosition.Start);
    }
    modifier(this._modifiers, SideBarContainerPositionModifier, value);
    return this;
  }

  sideBarWidth(value: number | Length): SideBarContainerAttribute {
    let sideBarWidthValue: number = 240;
    if (isNumber(value)) {
      let numberValue: number = <number>value;
      if (numberValue < 0) {
        modifier(this._modifiers, SideBarContainerWidthModifier, sideBarWidthValue);
      } else {
        let lengthValue: number | string = <number | string>value;
        modifier(this._modifiers, SideBarContainerWidthModifier, lengthValue);
      }
    } else if (isLengthType(value)) {
      let lengthValue: number | string = <number | string>value;
      modifier(this._modifiers, SideBarContainerWidthModifier, lengthValue);
    } else {
      modifier(this._modifiers, SideBarContainerWidthModifier, sideBarWidthValue);
    }
    return this;
  }

  showControlButton(value: boolean): SideBarContainerAttribute {
    modifier(this._modifiers, SideBarContainerShowControlButtonModifier, value);
    return this;
  }
}

// @ts-ignore
globalThis.SideBarContainer.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);

  let component = this.createOrGetNode(elmtId, () => {
    return new ArkSideBarContainerComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}