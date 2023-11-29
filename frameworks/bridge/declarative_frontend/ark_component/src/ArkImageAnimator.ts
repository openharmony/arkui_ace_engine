/// <reference path="./import.ts" />

class ImageAnimatorImagesModifier extends Modifier<ArkImageFrameInfoToArray> {
  static identity: Symbol = Symbol('imageAnimatorImages');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().imageAnimator.resetImages(node);
    } else {
      GetUINativeModule().imageAnimator.setImages(
        node,
        this.value.arrSrc,
        this.value.arrWidth,
        this.value.arrHeight,
        this.value.arrTop,
        this.value.arrLeft,
        this.value.arrDuration,
        this.value.arrSrc.length
      );
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
          array.arrWidth.push(item.width === undefined || item.width === null ? 0 : item.width);
          array.arrHeight.push(item.height === undefined || item.height === null ? 0 : item.height);
          array.arrTop.push(item.top === undefined || item.top === null ? 0 : item.top);
          array.arrLeft.push(item.left === undefined || item.left === null ? 0 : item.left);
          array.arrDuration.push(item.duration === undefined || item.duration === null ? 0 : item.duration);
        }
        modifier(this._modifiers, ImageAnimatorImagesModifier, array);
      } else {
        modifier(this._modifiers, ImageAnimatorImagesModifier, undefined);
      }
    } else {
      modifier(this._modifiers, ImageAnimatorImagesModifier, undefined);
    }
    return this;
  }
  state(value: AnimationStatus): ImageAnimatorAttribute {
    if (value) {
      modifier(this._modifiers, ImageAnimatorStateModifier, value);
    } else {
      modifier(this._modifiers, ImageAnimatorStateModifier, AnimationStatus.Initial);
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
    if (value) {
      modifier(this._modifiers, ImageAnimatorFillModeModifier, value);
    } else {
      modifier(this._modifiers, ImageAnimatorFillModeModifier, FillMode.Forwards);
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
