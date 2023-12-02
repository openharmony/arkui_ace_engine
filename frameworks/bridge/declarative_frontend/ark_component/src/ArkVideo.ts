/// <reference path="./import.ts" />

class VideoObjectFitModifier extends Modifier<ImageFit> {
  static identity: Symbol = Symbol('videoObjectFit');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().video.resetObjectFit(node);
    } else {
      GetUINativeModule().video.setObjectFit(node, this.value!);
    }
  }
}
class VideoAutoPlayModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('videoAutoPlayr');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().video.resetAutoPlay(node);
    } else {
      GetUINativeModule().video.setAutoPlay(node, this.value!);
    }
  }
}
class VideoControlsModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('videoControls');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().video.resetControls(node);
    } else {
      GetUINativeModule().video.setControls(node, this.value!);
    }
  }
}
class VideoLoopModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('videoLoop');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().video.resetLoop(node);
    } else {
      GetUINativeModule().video.setLoop(node, this.value!);
    }
  }
}
class VideoMutedModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('videoMuted');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().video.resetMuted(node);
    } else {
      GetUINativeModule().video.setMuted(node, this.value!);
    }
  }
}
class ArkVideoComponent extends ArkComponent implements CommonMethod<VideoAttribute> {
  muted(value: boolean): VideoAttribute {
    if (isBoolean(value)) {
      modifier(this._modifiers, VideoMutedModifier, value);
    } else {
      modifier(this._modifiers, VideoMutedModifier, undefined);
    }
    return this;
  }
  autoPlay(value: boolean): VideoAttribute {
    if (isBoolean(value)) {
      modifier(this._modifiers, VideoAutoPlayModifier, value);
    } else {
      modifier(this._modifiers, VideoAutoPlayModifier, undefined);
    }
    return this;
  }
  controls(value: boolean): VideoAttribute {
    if (isBoolean(value)) {
      modifier(this._modifiers, VideoControlsModifier, value);
    } else {
      modifier(this._modifiers, VideoControlsModifier, undefined);
    }
    return this;
  }
  loop(value: boolean): VideoAttribute {
    if (isBoolean(value)) {
      modifier(this._modifiers, VideoLoopModifier, value);
    } else {
      modifier(this._modifiers, VideoLoopModifier, undefined);
    }
    return this;
  }
  objectFit(value: ImageFit): VideoAttribute {
    if (value in ImageFit) {
      modifier(this._modifiers, VideoObjectFitModifier, value);
    } else {
      modifier(this._modifiers, VideoObjectFitModifier, undefined);
    }
    return this;
  }
  onStart(callback: () => void): VideoAttribute {
    throw new Error('Method not implemented.');
  }
  onPause(callback: () => void): VideoAttribute {
    throw new Error('Method not implemented.');
  }
  onFinish(event: () => void): VideoAttribute {
    throw new Error('Method not implemented.');
  }
  onFullscreenChange(callback: (event: { fullscreen: boolean}) => void): VideoAttribute {
    throw new Error('Method not implemented.');
  }
  onPrepared(callback: (event: { duration: number }) => void): VideoAttribute {
    throw new Error('Method not implemented.');
  }
  onSeeking(callback: (event: { time: number }) => void): VideoAttribute {
    throw new Error('Method not implemented.');
  }
  onSeeked(callback: (event: { time: number }) => void): VideoAttribute {
    throw new Error('Method not implemented.');
  }
  onUpdate(callback: (event: { time: number }) => void): VideoAttribute {
    throw new Error('Method not implemented.');
  }
  onError(callback: () => void): VideoAttribute {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}
// @ts-ignore
globalThis.Video.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);

  let component = this.createOrGetNode(elmtId, () => {
    return new ArkVideoComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}