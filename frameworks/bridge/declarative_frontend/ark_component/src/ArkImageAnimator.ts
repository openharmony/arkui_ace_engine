/// <reference path="./import.ts" />
class ImageAnimatorImagesModifier extends ModifierWithKey<Array<ImageFrameInfo>> {
  static identity: Symbol = Symbol('imageAnimatorImages');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().imageAnimator.resetImages(node);
    } else {
      let arkImageFrame: ArkImageFrameInfoToArray = this.convertImageFrames(this.value);
      GetUINativeModule().imageAnimator.setImages(node, arkImageFrame.arrSrc,
        arkImageFrame.arrWidth, arkImageFrame.arrHeight, arkImageFrame.arrTop, arkImageFrame.arrLeft,
        arkImageFrame.arrDuration, arkImageFrame.arrSrc.length);
    }
  }

  checkObjectDiff(): boolean {
    let checkDiff = true;
    if (this.value && this.value.length > 0 &&
      this.stageValue && this.stageValue.length > 0 &&
      this.value.length === this.stageValue.length) {
      let checkItemEqual: Boolean = false;

      for (let i: number = 0; i < this.value.length; i++) {
        this.isEqual(this.stageValue[i], this.value[i])
        if (!checkItemEqual) {
          checkDiff = !checkItemEqual;
          break;
        }
      }
    }
    return checkDiff;
  }

  isEqual(one: ImageFrameInfo, another: ImageFrameInfo): boolean {
    if (!(one.width === another.width &&
      one.height === another.height &&
      one.top === another.top &&
      one.left === another.left &&
      one.duration === another.duration)) {
      return true;
    }
    else {
      return !isBaseOrResourceEqual(one.src, another.src);
    }
  }

  convertImageFrames(value: Array<ImageFrameInfo>): ArkImageFrameInfoToArray {
    if (value && value.length > 0) {
      let isFlag: Boolean = true;
      for (let item of value) {
        if (item.src === undefined || item.src === null) {
          isFlag = false;
          break;
        }
      }
      if (isFlag) {
        let array: ArkImageFrameInfoToArray = new ArkImageFrameInfoToArray();
        for (let item of value) {
          array.arrSrc.push(<string>item.src);
          array.arrWidth.push((item.width === undefined || item.width === null) ? 0 : item.width);
          array.arrHeight.push((item.height === undefined || item.height === null) ? 0 : item.height);
          array.arrTop.push((item.top === undefined || item.top === null) ? 0 : item.top);
          array.arrLeft.push((item.left === undefined || item.left === null) ? 0 : item.left);
          array.arrDuration.push((item.duration === undefined || item.duration === null) ? 0 : item.duration);
        }
        return array;
      } else {
        return undefined;
      }
    } else {
      return undefined;
    }
  }
}

class ImageAnimatorDurationModifier extends Modifier<number> {
  static identity: Symbol = Symbol('imageAnimatorDuration');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().imageAnimator.resetDuration(node);
    } else {
      GetUINativeModule().imageAnimator.setDuration(node, this.value);
    }
  }
}

class ImageAnimatorReverseModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('imageAnimatorReverse');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().imageAnimator.resetReverse(node);
    } else {
      GetUINativeModule().imageAnimator.setReverse(node, this.value);
    }
  }
}

class ImageAnimatorPreDecodeModifier extends Modifier<number> {
  static identity: Symbol = Symbol('imageAnimatorPreDecode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().imageAnimator.resetPreDecode(node);
    } else {
      GetUINativeModule().imageAnimator.setPreDecode(node, this.value);
    }
  }
}

class ImageAnimatorStateModifier extends Modifier<number> {
  static identity: Symbol = Symbol('imageAnimatorState');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().imageAnimator.resetState(node);
    } else {
      GetUINativeModule().imageAnimator.setState(node, this.value);
    }
  }
}

class ImageAnimatorFixedSizeModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('imageAnimatorFixedSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().imageAnimator.resetFixedSize(node);
    } else {
      GetUINativeModule().imageAnimator.setFixedSize(node, this.value);
    }
  }
}

class ImageAnimatorFillModeModifier extends Modifier<number> {
  static identity: Symbol = Symbol('imageAnimatorFillMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().imageAnimator.resetFillMode(node);
    } else {
      GetUINativeModule().imageAnimator.setFillMode(node, this.value);
    }
  }
}

class ImageAnimatorIterationsModeModifier extends Modifier<number> {
  static identity: Symbol = Symbol('imageAnimatorIterationsMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().imageAnimator.resetIterations(node);
    } else {
      GetUINativeModule().imageAnimator.setIterations(node, this.value);
    }
  }
}

class ArkImageAnimatorComponent extends ArkComponent implements CommonMethod<ImageAnimatorAttribute> {
  images(value: Array<ImageFrameInfo>): ImageAnimatorAttribute {
    if (value && value.length > 0) {
      modifierWithKey(this._modifiersWithKeys, ImageAnimatorImagesModifier.identity,
        ImageAnimatorImagesModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, ImageAnimatorImagesModifier.identity,
        ImageAnimatorImagesModifier, undefined);
    }
    return this;
  }
  state(value: AnimationStatus): ImageAnimatorAttribute {
    if (value) {
      modifier(this._modifiers, ImageAnimatorStateModifier, value);
    } else {
      modifier(this._modifiers, ImageAnimatorStateModifier, undefined);
    }
    return this;
  }
  duration(value: number): ImageAnimatorAttribute {
    modifier(this._modifiers, ImageAnimatorDurationModifier, value);
    return this;
  }
  reverse(value: boolean): ImageAnimatorAttribute {
    modifier(this._modifiers, ImageAnimatorReverseModifier, value);
    return this;
  }
  fixedSize(value: boolean): ImageAnimatorAttribute {
    modifier(this._modifiers, ImageAnimatorFixedSizeModifier, value);
    return this;
  }
  preDecode(value: number): ImageAnimatorAttribute {
    throw new Error('Method not implemented.');
  }
  fillMode(value: FillMode): ImageAnimatorAttribute {
    if (value in FillMode) {
      modifier(this._modifiers, ImageAnimatorFillModeModifier, value);
    } else {
      modifier(this._modifiers, ImageAnimatorFillModeModifier, undefined);
    }
    return this;
  }
  iterations(value: number): ImageAnimatorAttribute {
    modifier(this._modifiers, ImageAnimatorIterationsModeModifier, value);
    return this;
  }
  onStart(event: () => void): ImageAnimatorAttribute {
    throw new Error('Method not implemented.');
  }
  onPause(event: () => void): ImageAnimatorAttribute {
    throw new Error('Method not implemented.');
  }
  onRepeat(event: () => void): ImageAnimatorAttribute {
    throw new Error('Method not implemented.');
  }
  onCancel(event: () => void): ImageAnimatorAttribute {
    throw new Error('Method not implemented.');
  }
  onFinish(event: () => void): ImageAnimatorAttribute {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.ImageAnimator.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkImageAnimatorComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
};
