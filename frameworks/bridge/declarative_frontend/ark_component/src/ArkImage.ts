
/// <reference path="./import.ts" />
class ArkImageComponent extends ArkComponent implements ImageAttribute {
    alt(value: any): ImageAttribute {
        throw new Error("Method not implemented.");
    }
    matchTextDirection(value: boolean): ImageAttribute {
        throw new Error("Method not implemented.");
    }
    fitOriginalSize(value: boolean): ImageAttribute {
        throw new Error("Method not implemented.");
    }
    fillColor(value: ResourceColor): ImageAttribute {
        throw new Error("Method not implemented.");
    }
    objectFit(value: ImageFit): ImageAttribute {
        throw new Error("Method not implemented.");
    }
    objectRepeat(value: ImageRepeat): ImageAttribute {
        throw new Error("Method not implemented.");
    }
    autoResize(value: boolean): ImageAttribute {
        throw new Error("Method not implemented.");
    }
    renderMode(value: ImageRenderMode): ImageAttribute {
        throw new Error("Method not implemented.");
    }
    interpolation(value: ImageInterpolation): ImageAttribute {
        throw new Error("Method not implemented.");
    }
    sourceSize(value: { width: number; height: number; }): ImageAttribute {
        throw new Error("Method not implemented.");
    }
    syncLoad(value: boolean): ImageAttribute {
        throw new Error("Method not implemented.");
    }
    colorFilter(value: ColorFilter): ImageAttribute {
        throw new Error("Method not implemented.");
    }
    copyOption(value: CopyOptions): ImageAttribute {
        throw new Error("Method not implemented.");
    }
    onComplete(callback: (event?: { width: number; height: number; componentWidth: number; componentHeight: number; loadingStatus: number; contentWidth: number; contentHeight: number; contentOffsetX: number; contentOffsetY: number; } | undefined) => void): ImageAttribute {
        throw new Error("Method not implemented.");
    }
    onError(callback: (event: { componentWidth: number; componentHeight: number; message: string; }) => void): ImageAttribute {
        throw new Error("Method not implemented.");
    }
    onFinish(event: () => void): ImageAttribute {
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
