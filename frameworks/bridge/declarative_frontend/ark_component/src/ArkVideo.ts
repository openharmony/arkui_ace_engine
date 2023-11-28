/// <reference path="./import.ts" />
class ArkVideoComponent extends ArkComponent implements VideoAttribute {
  muted(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  autoPlay(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  controls(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  loop(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  objectFit(value: ImageFit): this {
    throw new Error("Method not implemented.");
  }
  onStart(event: () => void): this {
    throw new Error("Method not implemented.");
  }
  onPause(event: () => void): this {
    throw new Error("Method not implemented.");
  }
  onFinish(event: () => void): this {
    throw new Error("Method not implemented.");
  }
  onFullscreenChange(callback: (event: { fullscreen: boolean; }) => void): this {
    throw new Error("Method not implemented.");
  }
  onPrepared(callback: (event: { duration: number; }) => void): this {
    throw new Error("Method not implemented.");
  }
  onSeeking(callback: (event: { time: number; }) => void): this {
    throw new Error("Method not implemented.");
  }
  onSeeked(callback: (event: { time: number; }) => void): this {
    throw new Error("Method not implemented.");
  }
  onUpdate(callback: (event: { time: number; }) => void): this {
    throw new Error("Method not implemented.");
  }
  onError(event: () => void): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.Video.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkVideoComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
