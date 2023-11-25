
/// <reference path="./import.ts" />
class ArkImageComponent extends ArkComponent implements ImageAttribute {
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
        throw new Error("Method not implemented.");
    }
    alt(value: any): this {
        throw new Error("Method not implemented.");
    }
    matchTextDirection(value: boolean): this {
        throw new Error("Method not implemented.");
    }
    fitOriginalSize(value: boolean): this {
        throw new Error("Method not implemented.");
    }
    fillColor(value: ResourceColor): this {
        throw new Error("Method not implemented.");
    }
    objectFit(value: ImageFit): this {
        throw new Error("Method not implemented.");
    }
    objectRepeat(value: ImageRepeat): this {
        throw new Error("Method not implemented.");
    }
    autoResize(value: boolean): this {
        throw new Error("Method not implemented.");
    }
    renderMode(value: ImageRenderMode): this {
        throw new Error("Method not implemented.");
    }
    interpolation(value: ImageInterpolation): this {
        throw new Error("Method not implemented.");
    }
    sourceSize(value: { width: number; height: number; }): this {
        throw new Error("Method not implemented.");
    }
    syncLoad(value: boolean): this {
        throw new Error("Method not implemented.");
    }
    colorFilter(value: ColorFilter): this {
        throw new Error("Method not implemented.");
    }
    copyOption(value: CopyOptions): this {
        throw new Error("Method not implemented.");
    }
    onComplete(callback: (event?: { width: number; height: number; componentWidth: number; componentHeight: number; loadingStatus: number; contentWidth: number; contentHeight: number; contentOffsetX: number; contentOffsetY: number; } | undefined) => void): this {
        throw new Error("Method not implemented.");
    }
    onError(callback: (event: { componentWidth: number; componentHeight: number; message: string; }) => void): this {
        throw new Error("Method not implemented.");
    }
    onFinish(event: () => void): this {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Image.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkImageComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
