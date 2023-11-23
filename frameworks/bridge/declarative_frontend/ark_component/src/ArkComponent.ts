/// <reference path="./import.ts" />
const arkUINativeModule = globalThis.getArkUINativeModule();
function GetUINativeModule() {
    if (arkUINativeModule) {
        return arkUINativeModule;
    }
    return arkUINativeModule;
}

function isResource(variable: any): variable is Resource {
    return (variable as Resource)?.bundleName!== undefined;
  }

type KNode = number | null

interface Equable {
    isEqual(value: Equable): boolean;
}

class Modifier<T extends number | string | boolean | Equable | Resource> {
    stageValue?: T;
    value?: T;
    constructor(value: T) {
        this.stageValue = value;
    }

    applyStage(node: KNode): boolean {
        if (this.stageValue === this.value) {
            delete this.stageValue;
            return;
        }
        if (typeof this.stageValue === "object" && typeof this.value === "object") {
            if ((this.stageValue as Equable).isEqual(this.value as Equable)) {
                delete this.stageValue;
                return;
            }
        }
        this.value = this.stageValue;
        delete this.stageValue;
        this.applyPeer(node, this.value === undefined);
        return (this.value === undefined);
    }

    applyPeer(node: KNode, reset: boolean): void { }
}

class ModifierWithKey<T extends number | string | boolean | object> {
    stageValue?: T;
    value?: T;
    constructor(value: T) {
        this.stageValue = value;
    }

    applyStage(node: KNode): boolean {
        if (this.stageValue === this.value) {  
            this.applyPeer(node, true);
            return true;
        }
        const stageTypeInfo: string = typeof this.stageValue;
        const valueTypeInfo: string = typeof this.value;
        let different: boolean = false;
        if (stageTypeInfo !== valueTypeInfo) {
            different = true;
        } else if (stageTypeInfo === "number" || stageTypeInfo === "string" || stageTypeInfo === "boolean") {
            different = (this.stageValue !== this.value);
        } else {
            different = this.checkObjectDiff();
        }
        if (different) {
            this.value = this.stageValue;
            this.applyPeer(node, false);
        }
        this.stageValue = undefined;
        return false;
    }

    applyPeer(node: KNode, reset: boolean): void { }

    checkObjectDiff(): boolean {
        return true;
    }
}
class BackgroundColorModifier extends Modifier<number | undefined > {
    static identity: Symbol = Symbol("backgroundColor");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetBackgroundColor(node);
        } else {
            GetUINativeModule().common.setBackgroundColor(node, this.value!);
        }
    }
}


class WidthModifier extends Modifier<number | string> {
    static identity: Symbol = Symbol("width");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetWidth(node);
        }
        else {
            GetUINativeModule().common.setWidth(node, this.value);
        }
    }
}

class BorderWidthModifier extends Modifier<ArkBorderWidth> {
    static identity: Symbol = Symbol("borderWidth");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetBorderWidth(node);
        }
        else {
            GetUINativeModule().common.setBorderWidth(node, this.value.left, this.value.right, this.value.top, this.value.bottom);
        }
    }
}


class HeightModifier extends Modifier<number | string> {
    static identity: Symbol = Symbol("height");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetHeight(node);
        }
        else {
            GetUINativeModule().common.setHeight(node, this.value);
        }
    }
}

class BorderRadiusModifier extends Modifier<ArkBorderRadius> {
    static identity: Symbol = Symbol("borderRadius");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetBorderRadius(node);
        }
        else {
            GetUINativeModule().common.setBorderRadius(node, this.value.topLeft, this.value.topRight, this.value.bottomLeft, this.value.bottomRight);
        }
    }
}

class PositionModifier extends Modifier<ArkPosition> {
    static identity: Symbol = Symbol("position");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetPosition(node);
        }
        else {
            GetUINativeModule().common.setPosition(node, this.value.x, this.value.y);
        }
    }
}

class BorderColorModifier extends Modifier<ArkBorderColor> {
    static identity: Symbol = Symbol("borderColor");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetBorderColor(node);
        }
        else {
            GetUINativeModule().common.setBorderColor(node, this.value.leftColor, this.value.rightColor, this.value.topColor, this.value.bottomColor);
        }
    }
}


class TransformModifier extends Modifier<ArkTransformMatrix> {
    static identity: Symbol = Symbol("transform");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetTransform(node);
        }
        else {
            GetUINativeModule().common.setTransform(node, this.value.matrix);
        }
    }
}

class BorderStyleModifier extends Modifier<ArkBorderStyle> {
    static identity: Symbol = Symbol("borderStyle");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetBorderStyle(node);
        }
        else {
            GetUINativeModule().common.setBorderStyle(node, this.value.type, this.value.style,
                this.value.top, this.value.right, this.value.bottom, this.value.left);
        }
    }
}

class ShadowModifier extends Modifier<ArkShadow> {
    static identity: Symbol = Symbol("shadow");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetShadow(node);
        }
        else {
            GetUINativeModule().common.setShadow(node, this.value.style,
                this.value.radius, this.value.type, this.value.color,
                this.value.offsetX, this.value.offsetY, this.value.fill);
        }
    }
}

class HitTestBehaviorModifier extends Modifier<number> {
    static identity: Symbol = Symbol("hitTestBehavior");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetHitTestBehavior(node);
        }
        else {
            GetUINativeModule().common.setHitTestBehavior(node, this.value);
        }
    }
}

class ZIndexModifier extends Modifier<number> {
    static identity: Symbol = Symbol("zIndex");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetZIndex(node);
        }
        else {
            GetUINativeModule().common.setZIndex(node, this.value);
        }
    }
}

class OpacityModifier extends Modifier<number> {
    static identity: Symbol = Symbol("opacity");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetOpacity(node);
        }
        else {
            GetUINativeModule().common.setOpacity(node, this.value);
        }
    }
}

class AlignModifier extends Modifier<number> {
    static identity: Symbol = Symbol("align");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetAlign(node);
        }
        else {
            GetUINativeModule().common.setAlign(node, this.value);
        }
    }
}

class BackdropBlurModifier extends Modifier<number> {
    static identity: Symbol = Symbol("backdropBlur");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
           GetUINativeModule().common.resetBackdropBlur(node);
        }
        else {
           GetUINativeModule().common.setBackdropBlur(node, this.value);
        }
    }
}

class HueRotateModifier extends Modifier<number | string> {
    static identity: Symbol = Symbol("hueRotate");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
           GetUINativeModule().common.resetHueRotate(node);
        }
        else {
           GetUINativeModule().common.setHueRotate(node, this.value);
        }
    }
}

class InvertModifier extends Modifier<number> {
    static identity: Symbol = Symbol("invert");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
           GetUINativeModule().common.resetInvert(node);
        }
        else {
           GetUINativeModule().common.setInvert(node, this.value);
        }
    }
}

class SepiaModifier extends Modifier<number> {
    static identity: Symbol = Symbol("sepia");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
           GetUINativeModule().common.resetSepia(node);
        }
        else {
           GetUINativeModule().common.setSepia(node, this.value);
        }
    }
}

class SaturateModifier extends Modifier<number> {
    static identity: Symbol = Symbol("saturate");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
           GetUINativeModule().common.resetSaturate(node);
        }
        else {
           GetUINativeModule().common.setSaturate(node, this.value);
        }
    }
}

class ColorBlendModifier extends Modifier<number | string> {
    static identity: Symbol = Symbol("colorBlend");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
           GetUINativeModule().common.resetColorBlend(node);
        }
        else {
           GetUINativeModule().common.setColorBlend(node, this.value);
        }
    }
}

class GrayscaleModifier extends Modifier<number> {
    static identity: Symbol = Symbol("grayscale");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
           GetUINativeModule().common.resetGrayscale(node);
        }
        else {
           GetUINativeModule().common.setGrayscale(node, this.value);
        }
    }
}

class ContrastModifier extends Modifier<number> {
    static identity: Symbol = Symbol("contrast");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
           GetUINativeModule().common.resetContrast(node);
        }
        else {
           GetUINativeModule().common.setContrast(node, this.value);
        }
    }
}

class BrightnessModifier extends Modifier<number> {
    static identity: Symbol = Symbol("brightness");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
           GetUINativeModule().common.resetBrightness(node);
        }
        else {
           GetUINativeModule().common.setBrightness(node, this.value);
        }
    }
}

class BlurModifier extends Modifier<number> {
    static identity: Symbol = Symbol("blur");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
           GetUINativeModule().common.resetBlur(node);
        }
        else {
           GetUINativeModule().common.setBlur(node, this.value);
        }
    }
}

class LinearGradientModifier extends Modifier<ArkLinearGradient> {
    static identity: Symbol = Symbol("linearGradient");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetLinearGradient(node);
        }
        else {
            GetUINativeModule().common.setLinearGradient(node,
                this.value.angle, this.value.direction,
                this.value.colors, this.value.repeating);
        }
    }
}

class RadialGradientModifier extends Modifier<ArkRadialGradient> {
    static identity: Symbol = Symbol("radialGradient");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetRadialGradient(node);
        }
        else {
            GetUINativeModule().common.setRadialGradient(node,
                this.value.center, this.value.radius, this.value.colors, this.value.repeating);
        }
    }
}

class SweepGradientModifier extends Modifier<ArkSweepGradient> {
    static identity: Symbol = Symbol("sweepGradient");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetSweepGradient(node);
        }
        else {
            GetUINativeModule().common.setSweepGradient(node,
                this.value.center,
                this.value.start, this.value.end, this.value.rotation,
                this.value.colors, this.value.repeating);
        }
    }
}

class BorderModifier extends Modifier<ArkBorder>{
    static identity: Symbol = Symbol("border");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetBorder(node);
        }
        else {
            GetUINativeModule().common.setBorder(node,
                this.value.arkWidth.left, this.value.arkWidth.right, this.value.arkWidth.top, this.value.arkWidth.bottom,
                this.value.arkColor.leftColor, this.value.arkColor.rightColor, this.value.arkColor.topColor, this.value.arkColor.bottomColor,
                this.value.arkRadius.topLeft, this.value.arkRadius.topRight, this.value.arkRadius.bottomLeft, this.value.arkRadius.bottomRight,
                this.value.arkStyle.top, this.value.arkStyle.right, this.value.arkStyle.bottom, this.value.arkStyle.left);
        }
    }
}

class ForegroundBlurStyleModifier extends Modifier<ArkForegroundBlurStyle> {
    static identity: Symbol = Symbol("foregroundBlurStyle");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetForegroundBlurStyle(node);
        }
        else {
            GetUINativeModule().common.setForegroundBlurStyle(node,
                this.value.blurStyle, this.value.colorMode, this.value.adaptiveColor, this.value.scale);
            }
        }
    }

class BackgroundImagePositionModifier extends Modifier<ArkBackgroundImagePosition>{
    static identity: Symbol = Symbol("backgroundImagePosition");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetBackgroundImagePosition(node);
        }
        else {
            GetUINativeModule().common.setBackgroundImagePosition(node, this.value.alignment, this.value.x, this.value.y);
        }
    }
}

class LinearGradientBlurModifier extends Modifier<ArkLinearGradientBlur> {
    static identity: Symbol = Symbol("linearGradientBlur");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetLinearGradientBlur(node);
        }
        else {
            GetUINativeModule().common.setLinearGradientBlur(node,
                this.value.blurRadius, this.value.fractionStops, this.value.direction);
            }
        }
    }

class BackgroundImageModifier extends Modifier<ArkBackgroundImage>{
    static identity: Symbol = Symbol("backgroundImage");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetBackgroundImage(node);
        }
        else {
            GetUINativeModule().common.setBackgroundImage(node, this.value.src, this.value.repeat);
        }
    }
}

class BackgroundBlurStyleModifier extends Modifier<ArkBackgroundBlurStyle> {
    static identity: Symbol = Symbol("backgroundBlurStyle");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetBackgroundBlurStyle(node);
        }
        else {
            GetUINativeModule().common.setBackgroundBlurStyle(node,
                this.value.blurStyle, this.value.colorMode, this.value.adaptiveColor, this.value.scale);
        }
    }
}


class BackgroundImageSizeModifier extends Modifier<ArkBackgroundImageSize>{
    static identity: Symbol = Symbol("backgroundImageSize");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetBackgroundImageSize(node);
        }
        else {
            GetUINativeModule().common.setBackgroundImageSize(node, this.value.imageSize, this.value.width, this.value.height);
        }
    }
}

class TranslateModifier extends Modifier<ArkTranslate>{
    static identity: Symbol = Symbol("translate");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetTranslate(node);
        }
        else {
            GetUINativeModule().common.setTranslate(node, this.value.x, this.value.y, this.value.z);
        }
    }
}

class ScaleModifier extends Modifier<ArkScale>{
    static identity: Symbol = Symbol("scale");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetScale(node);
        }
        else {
            GetUINativeModule().common.setScale(node, this.value.x, this.value.y, this.value.z, this.value.centerX, this.value.centerY);
        }
    }
}

class RotateModifier extends Modifier<ArkRotate>{
    static identity: Symbol = Symbol("rotate");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetRotate(node);
        }
        else {
            GetUINativeModule().common.setRotate(node, this.value.x, this.value.y, this.value.z, this.value.angle, 
                this.value.centerX, this.value.centerY, this.value.centerY, this.value.perspective);
        }
    }
}

class GeometryTransitionModifier extends Modifier<string>{
    static identity: Symbol = Symbol("geometryTransition");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetGeometryTransition(node);
        }
        else {
            GetUINativeModule().common.setGeometryTransition(node, this.value);
        }
    }
}

class ClipModifier extends ModifierWithKey<boolean | object> {
    static identity: Symbol = Symbol("clip");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetClip(node);
        }
        else {
            GetUINativeModule().common.setClip(node, this.value);
        }
    }

    checkObjectDiff(): boolean {
        return false;
    }
}

const JSCallbackInfoType = { STRING: 0, NUMBER: 1, OBJECT: 2, BOOLEAN: 3, FUNCTION: 4 };
type basicType = string | number | bigint | boolean | symbol | undefined | object | null;
const isString = (val: basicType) => typeof val === 'string'
const isNumber = (val: basicType) => typeof val === 'number'
const isBigint = (val: basicType) => typeof val === 'bigint'
const isBoolean = (val: basicType) => typeof val === 'boolean'
const isSymbol = (val: basicType) => typeof val === 'symbol'
const isUndefined = (val: basicType) => typeof val === 'undefined'
const isObject = (val: basicType) => typeof val === 'object'
const isFunction = (val: basicType) => typeof val === 'function'

function CheckJSCallbackInfo(value: any, checklist: any[]) {
    var typeVerified = false;
    checklist.forEach(function (infoType) {
        switch (infoType) {
            case JSCallbackInfoType.STRING:
                if (isString(value)) {
                    typeVerified = true;
                }
                break;
            case JSCallbackInfoType.NUMBER:
                if (isNumber(value)) {
                    typeVerified = true;
                }
                break;
            case JSCallbackInfoType.OBJECT:
                if (isObject(value)) {
                    typeVerified = true;
                }
                break;
            case JSCallbackInfoType.FUNCTION:
                if (isFunction(value)) {
                    typeVerified = true;
                }
                break;
            default:
                break;
        }

    });
    return typeVerified || checklist.length == 0;
}

function modifier<T extends number | string | boolean | Equable, M extends Modifier<T>>(
    modifiers: Map<Symbol, Modifier<number | string | boolean | Equable>>,
    modifierClass: new (value: T) => M,
    value: T
) {
    const identity: Symbol = (modifierClass as any)["identity"];
    const item = modifiers.get(identity);
    if (item) {
        item.stageValue = value;
    } else {
        modifiers.set(identity, new modifierClass(value));
    }
}

function modifierWithKey<T extends number | string | boolean | object, M extends ModifierWithKey<T>>(
    modifiers: Map<Symbol, ModifierWithKey<number | string | boolean | object>>,
    identity: Symbol,
    modifierClass: new (value: T) => M,
    value: T
) {
    const item = modifiers.get(identity);
    if (item) {
        item.stageValue = value;
    } else {
        modifiers.set(identity, new modifierClass(value));
    }
}

class ArkComponent implements CommonMethod<CommonAttribute> {
    _modifiers: Map<Symbol, Modifier<number | string | boolean | Equable>>;
    _modifiersWithKeys: Map<Symbol, ModifierWithKey<number | string | boolean | object>>;
    nativePtr: KNode;

    constructor(nativePtr: KNode) {
        this._modifiers = new Map();
        this._modifiersWithKeys = new Map();        
        this.nativePtr = nativePtr;
    }

    applyModifierPatch(): void {
        let expiringItems = [];
        let expiringItemsWithKeys = [];
        this._modifiers.forEach((value, key) => {
            if (value.applyStage(this.nativePtr)) {
                expiringItems.push(key);
            }
        });
        this._modifiersWithKeys.forEach((value, key) => {
            if (value.applyStage(this.nativePtr)) {              
                expiringItemsWithKeys.push(key);
            }
        });
        expiringItems.forEach(key => {
            this._modifiers.delete(key);
        });
        expiringItemsWithKeys.forEach(key => {
            this._modifiersWithKeys.delete(key);
        });
    }
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
        throw new Error("Method not implemented.");
    }
    width(value: Length): this {
        if (typeof value !== "number" && typeof value !== "string") {
            modifier(this._modifiers, WidthModifier, undefined);
        }
        else {
            modifier(this._modifiers, WidthModifier, value);
        }
        return this;
    }

    height(value: Length): this {
        if (typeof value !== "number" && typeof value !== "string") {
            modifier(this._modifiers, HeightModifier, undefined);
        }
        else {
            modifier(this._modifiers, HeightModifier, value);
        }
        return this;
    }

    expandSafeArea(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): this {
        throw new Error("Method not implemented.");
    }

    responseRegion(value: Array<Rectangle> | Rectangle): this {
        throw new Error("Method not implemented.");
    }

    mouseResponseRegion(value: Array<Rectangle> | Rectangle): this {
        throw new Error("Method not implemented.");
    }

    size(value: SizeOptions): this {
        throw new Error("Method not implemented.");
    }

    constraintSize(value: ConstraintSizeOptions): this {
        throw new Error("Method not implemented.");
    }

    touchable(value: boolean): this {
        throw new Error("Method not implemented.");
    }

    hitTestBehavior(value: HitTestMode): this {
        if (value) {
            modifier(this._modifiers, HitTestBehaviorModifier, value);
        } else {
            modifier(this._modifiers, HitTestBehaviorModifier, undefined);
        }
        return this;
    }

    layoutWeight(value: number | string): this {
        throw new Error("Method not implemented.");
    }

    padding(value: Padding | Length): this {
        throw new Error("Method not implemented.");
    }

    margin(value: Margin | Length): this {
        throw new Error("Method not implemented.");
    }

    background(builder: CustomBuilder, options?: { align?: Alignment }): this {
        throw new Error("Method not implemented.");
    }

    backgroundColor(value: ResourceColor): this {
        if(isResource(value)){
            modifier(this._modifiers, BackgroundColorModifier, undefined);
            return this;
        }
        var arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, BackgroundColorModifier, arkColor.color);
        } else {
            modifier(this._modifiers, BackgroundColorModifier, undefined);
        }
        return this;
    }

    backgroundImage(src: ResourceStr, repeat?: ImageRepeat): this {
        var arkBackgroundImage = new ArkBackgroundImage()
        if (isString(src)) {
            arkBackgroundImage.src = src
        }
        if (isNumber(repeat)) {
            arkBackgroundImage.repeat = repeat
        }
        modifier(this._modifiers, BackgroundImageModifier, arkBackgroundImage);
        return this;
    }

    backgroundImageSize(value: SizeOptions | ImageSize): this {
        if (isResource(value) || isUndefined(value)) {
            modifier(this._modifiers, BackgroundImageSizeModifier, undefined);
            return this
        }
        var arkBackgroundImageSize = new ArkBackgroundImageSize()
        if (isNumber(value)) {
            arkBackgroundImageSize.imageSize = value
        } else {
            if(isNumber((value as SizeOptions)?.width) || isString((value as SizeOptions)?.width)){
                arkBackgroundImageSize.width = (value as SizeOptions)?.width;
            }
            if(isNumber((value as SizeOptions)?.height) || isString((value as SizeOptions)?.height)){
                arkBackgroundImageSize.height = (value as SizeOptions)?.height;
            }
        }
        modifier(this._modifiers, BackgroundImageSizeModifier, arkBackgroundImageSize);
        return this;
    }

    backgroundImagePosition(value: Position | Alignment): this {
        if (isResource(value) || isUndefined(value)) {
            modifier(this._modifiers, BackgroundImagePositionModifier, undefined);
            return this
        }
        var arkBackgroundImagePosition = new ArkBackgroundImagePosition()
        if (isNumber(value)) {
            arkBackgroundImagePosition.alignment = value
        } else {
            if (isNumber((value as Position)?.x) || isString((value as Position)?.x)){
                arkBackgroundImagePosition.x = (value as Position)?.x;
            }
            if (isNumber((value as Position)?.y) || isString((value as Position)?.y)){
                arkBackgroundImagePosition.y = (value as Position)?.y;
            }
        }
        modifier(this._modifiers, BackgroundImagePositionModifier, arkBackgroundImagePosition);
        return this;
    }

    backgroundBlurStyle(value: BlurStyle, options?: BackgroundBlurStyleOptions): this {
        let arkBackgroundBlurStyle = new ArkBackgroundBlurStyle();
        arkBackgroundBlurStyle.blurStyle = value;
        if (typeof options === "object") {
            arkBackgroundBlurStyle.colorMode = options.colorMode;
            arkBackgroundBlurStyle.adaptiveColor = options.adaptiveColor;
            arkBackgroundBlurStyle.scale = options.scale;
        }
        modifier(this._modifiers, BackgroundBlurStyleModifier, arkBackgroundBlurStyle);
        return this;
    }

    foregroundBlurStyle(value: BlurStyle, options?: ForegroundBlurStyleOptions): this {
        let arkForegroundBlurStyle = new ArkForegroundBlurStyle();
        arkForegroundBlurStyle.blurStyle = value;
        if (typeof options === "object") {
            arkForegroundBlurStyle.colorMode = options.colorMode;
            arkForegroundBlurStyle.adaptiveColor = options.adaptiveColor;
            arkForegroundBlurStyle.scale = options.scale;
        }
        modifier(this._modifiers, ForegroundBlurStyleModifier, arkForegroundBlurStyle);
        return this;
    }

    opacity(value: number | Resource): this {
        var opacityDefault = 0.0;
        if(isResource(value)){
            modifier(this._modifiers, OpacityModifier, opacityDefault);
            return this;
        }
        var checklist = [JSCallbackInfoType.OBJECT, JSCallbackInfoType.NUMBER, JSCallbackInfoType.STRING];
        if (!CheckJSCallbackInfo(value, checklist)) {
            modifier(this._modifiers, OpacityModifier, 1.0);
        }
        else {
            if (isNumber(value)) {
                opacityDefault = value;
            }
            else if (isString(value)) {
                opacityDefault = Number(value);
            }
            modifier(this._modifiers, OpacityModifier, opacityDefault);
        }
        return this;
    }

    border(value: BorderOptions): this {
        var arkBorder = new ArkBorder()
        if(!isResource(value?.width) && !isUndefined(value?.width) &&  value?.width !== null)
        {
            if (isNumber(value.width)) {
                arkBorder.arkWidth.left = Number(value.width)
                arkBorder.arkWidth.right = Number(value.width)
                arkBorder.arkWidth.top = Number(value.width)
                arkBorder.arkWidth.bottom = Number(value.width)
            } else if (isString(value.width)) {
                arkBorder.arkWidth.left = String(value.width)
                arkBorder.arkWidth.right = String(value.width)
                arkBorder.arkWidth.top = String(value.width)
                arkBorder.arkWidth.bottom = String(value.width)
            } else {
                if (isNumber((value.width as EdgeWidths)?.left) || isString((value.width as EdgeWidths)?.left)) {
                    arkBorder.arkWidth.left = (value.width as EdgeWidths).left
                }
                if (isNumber((value.width as EdgeWidths)?.right) || isString((value.width as EdgeWidths)?.right)) {
                    arkBorder.arkWidth.right = (value.width as EdgeWidths).right
                }
                if (isNumber((value.width as EdgeWidths)?.top) || isString((value.width as EdgeWidths)?.top)) {
                    arkBorder.arkWidth.top = (value.width as EdgeWidths).top
                }
                if (isNumber((value.width as EdgeWidths)?.bottom) || isString((value.width as EdgeWidths)?.bottom)) {
                    arkBorder.arkWidth.bottom = (value.width as EdgeWidths).bottom
                }
            }
        }
        if (!isResource(value?.color) && !isUndefined(value?.color) && value?.color !== null) {
            var arkColor = new ArkColor();
            if (isNumber(value.color)) {
                arkColor.parseColorValue(Number(value.color))
                arkBorder.arkColor.leftColor = arkColor.color
                arkBorder.arkColor.rightColor = arkColor.color
                arkBorder.arkColor.topColor = arkColor.color
                arkBorder.arkColor.bottomColor = arkColor.color
            } else if (isString(value?.color)) {
                arkColor.parseColorValue(String(value.color))
                arkBorder.arkColor.leftColor = arkColor.color
                arkBorder.arkColor.rightColor = arkColor.color
                arkBorder.arkColor.topColor = arkColor.color
                arkBorder.arkColor.bottomColor = arkColor.color
            } else {
                if (isNumber((value.color as EdgeColors)?.left) || isString((value.color as EdgeColors)?.left)) {
                    arkColor.parseColorValue((value.color as EdgeColors).left)
                    arkBorder.arkColor.leftColor = arkColor?.color
                }
                if (isNumber((value.color as EdgeColors)?.right) || isString((value.color as EdgeColors)?.right)) {
                    arkColor.parseColorValue((value.color as EdgeColors).right)
                    arkBorder.arkColor.rightColor = arkColor?.color
                }
                if (isNumber((value.color as EdgeColors)?.top) || isString((value.color as EdgeColors)?.top)) {
                    arkColor.parseColorValue((value.color as EdgeColors).top)
                    arkBorder.arkColor.topColor = arkColor?.color
                }
                if (isNumber((value.color as EdgeColors)?.bottom) || isString((value.color as EdgeColors)?.bottom)) {
                    arkColor.parseColorValue((value.color as EdgeColors).bottom)
                    arkBorder.arkColor.bottomColor = arkColor?.color
                }
            }
        }

        if(!isResource(value?.radius) && !isUndefined(value?.radius) && value?.radius !== null){
            if (isNumber(value.radius)) {
                arkBorder.arkRadius.topLeft = Number(value.radius)
                arkBorder.arkRadius.topRight = Number(value.radius)
                arkBorder.arkRadius.bottomLeft = Number(value.radius)
                arkBorder.arkRadius.bottomRight = Number(value.radius)
            } else if (isString(value.radius)) {
                arkBorder.arkRadius.topLeft = String(value.radius)
                arkBorder.arkRadius.topRight = String(value.radius)
                arkBorder.arkRadius.bottomLeft = String(value.radius)
                arkBorder.arkRadius.bottomRight = String(value.radius)
            }
            else {
                if (isNumber((value.radius as BorderRadiuses)?.topLeft) || isString((value.radius as BorderRadiuses)?.topLeft)) {
                    arkBorder.arkRadius.topLeft = (value.radius as BorderRadiuses)?.topLeft
                }
                if (isNumber((value.radius as BorderRadiuses)?.topRight) || isString((value.radius as BorderRadiuses)?.topRight)) {
                    arkBorder.arkRadius.topRight = (value.radius as BorderRadiuses)?.topRight
                }
                if (isNumber((value.radius as BorderRadiuses)?.bottomLeft) || isString((value.radius as BorderRadiuses)?.bottomLeft)) {
                    arkBorder.arkRadius.bottomLeft = (value.radius as BorderRadiuses)?.bottomLeft
                }
                if (isNumber((value.radius as BorderRadiuses)?.bottomRight) || isString((value.radius as BorderRadiuses)?.bottomRight)) {
                    arkBorder.arkRadius.bottomRight = (value.radius as BorderRadiuses)?.bottomRight
                }
            }
        }
        if (!isUndefined(value?.style) && value?.style !== null) {
            var arkBorderStyle = new ArkBorderStyle();
            if (arkBorderStyle.parseBorderStyle(value.style)) {
                if (!isUndefined(arkBorderStyle.style)) {
                    arkBorder.arkStyle.top = arkBorderStyle.style
                    arkBorder.arkStyle.left = arkBorderStyle.style
                    arkBorder.arkStyle.bottom = arkBorderStyle.style
                    arkBorder.arkStyle.right = arkBorderStyle.style
                } else {
                    arkBorder.arkStyle.top = arkBorderStyle.top
                    arkBorder.arkStyle.left = arkBorderStyle.left
                    arkBorder.arkStyle.bottom = arkBorderStyle.bottom
                    arkBorder.arkStyle.right = arkBorderStyle.right
                }
            }
        }
        modifier(this._modifiers, BorderModifier, arkBorder);
        return this;
    }

    borderStyle(value: BorderStyle | EdgeStyles): this {
        var arkBorderStyle = new ArkBorderStyle();
        if (arkBorderStyle.parseBorderStyle(value)) {
            modifier(this._modifiers, BorderStyleModifier, arkBorderStyle);
        } else {
            modifier(this._modifiers, BorderStyleModifier, undefined);
        }
        return this;
    }

    borderWidth(value: Length | EdgeWidths): this {
        var borderWidth = new ArkBorderWidth()
        if( isResource(value) || isUndefined(value))
        {
            modifier(this._modifiers, BorderWidthModifier, undefined);
            return this;
        }

        if (typeof value === "number" || typeof value === "string") {
            borderWidth.left = value
            borderWidth.right = value
            borderWidth.top = value
            borderWidth.bottom = value
        }
        else {
            borderWidth.left = value?.left
            borderWidth.right = value?.right
            borderWidth.top = value?.top
            borderWidth.bottom = value?.bottom
        }
        modifier(this._modifiers, BorderWidthModifier, borderWidth);
        return this;
    }

    borderColor(value: ResourceColor | EdgeColors): this {
        if( isResource(value)  || isUndefined(value))
        {
            modifier(this._modifiers, BorderColorModifier, undefined);
            return this;
        }

        var arkColor = new ArkColor();
        var borderColorGroup = new ArkBorderColor()      
        if (typeof value === "number" || typeof value === "string") {
            arkColor.parseColorValue(value)
            borderColorGroup.leftColor = arkColor.color
            borderColorGroup.rightColor = arkColor.color
            borderColorGroup.topColor = arkColor.color
            borderColorGroup.bottomColor = arkColor.color
            modifier(this._modifiers, BorderColorModifier, borderColorGroup);
        }
        else if (!!value.left || !!value.right || !!value.top || !!value.bottom) {
            if (arkColor.parseColorValue(value.left)) {
                borderColorGroup.leftColor = arkColor.color;
            }
            if (arkColor.parseColorValue(value.right)) {
                borderColorGroup.rightColor = arkColor.color;
            }
            if (arkColor.parseColorValue(value.top)) {
                borderColorGroup.topColor = arkColor.color;
            }
            if (arkColor.parseColorValue(value.bottom)) {
                borderColorGroup.bottomColor = arkColor.color;
            }
            modifier(this._modifiers, BorderColorModifier, borderColorGroup);
        }
        else {
            modifier(this._modifiers, BorderColorModifier, undefined);
        }       
        return this;
    }

    borderRadius(value: Length | BorderRadiuses): this {
        if( isResource(value) || isUndefined(value))
        {
            modifier(this._modifiers, BorderRadiusModifier, undefined);
            return this;
        }

        var borderRadius = new ArkBorderRadius
        if (typeof value === "number" || typeof value === "string") {
            borderRadius.topLeft = value
            borderRadius.topRight = value
            borderRadius.bottomLeft = value
            borderRadius.bottomRight = value
        }
        else {
            borderRadius.topLeft = value?.topLeft
            borderRadius.topRight = value?.topRight
            borderRadius.bottomLeft = value?.bottomLeft
            borderRadius.bottomRight = value?.bottomRight
        }
        modifier(this._modifiers, BorderRadiusModifier, borderRadius);
        return this;
    }

    borderImage(value: BorderImageOption): this {
        throw new Error("Method not implemented.");
    }

    foregroundColor(value: ResourceColor | ColoringStrategy): this {
        throw new Error("Method not implemented.");
    }

    onClick(event: (event?: ClickEvent) => void): this {
        throw new Error("Method not implemented.");
    }

    onHover(event: (isHover?: boolean, event?: HoverEvent) => void): this {
        throw new Error("Method not implemented.");
    }

    hoverEffect(value: HoverEffect): this {
        throw new Error("Method not implemented.");
    }

    onMouse(event: (event?: MouseEvent) => void): this {
        throw new Error("Method not implemented.");
    }

    onTouch(event: (event?: TouchEvent) => void): this {
        throw new Error("Method not implemented.");
    }

    onKeyEvent(event: (event?: KeyEvent) => void): this {
        throw new Error("Method not implemented.");
    }

    focusable(value: boolean): this {
        throw new Error("Method not implemented.");
    }

    onFocus(event: () => void): this {
        throw new Error("Method not implemented.");
    }

    onBlur(event: () => void): this {
        throw new Error("Method not implemented.");
    }

    tabIndex(index: number): this {
        throw new Error("Method not implemented.");
    }

    defaultFocus(value: boolean): this {
        throw new Error("Method not implemented.");
    }

    groupDefaultFocus(value: boolean): this {
        throw new Error("Method not implemented.");
    }

    focusOnTouch(value: boolean): this {
        throw new Error("Method not implemented.");
    }

    animation(value: AnimateParam): this {
        throw new Error("Method not implemented.");
    }

    transition(value: TransitionOptions | TransitionEffect): this {
        throw new Error("Method not implemented.");
    }

    gesture(gesture: GestureType, mask?: GestureMask): this {
        throw new Error("Method not implemented.");
    }

    priorityGesture(gesture: GestureType, mask?: GestureMask): this {
        throw new Error("Method not implemented.");
    }

    parallelGesture(gesture: GestureType, mask?: GestureMask): this {
        throw new Error("Method not implemented.");
    }

    blur(value: number): this {
        if (!isNumber(value)) {
            modifier(this._modifiers, BlurModifier, undefined);
        }
        else {
            modifier(this._modifiers, BlurModifier, value);
        }
        return this;
    }

    linearGradientBlur(value: number, options: LinearGradientBlurOptions): this {
        let arkLinearGradientBlur = new ArkLinearGradientBlur();
        arkLinearGradientBlur.blurRadius = value;
        arkLinearGradientBlur.fractionStops = options.fractionStops;
        arkLinearGradientBlur.direction = options.direction;
        modifier(this._modifiers, LinearGradientBlurModifier, arkLinearGradientBlur);
        return this;
    }

    brightness(value: number): this {
        if (!isNumber(value)) {
            modifier(this._modifiers, BrightnessModifier, undefined);
        }
        else {
            modifier(this._modifiers, BrightnessModifier, value);
        }
        return this;
    }

    contrast(value: number): this {
        if (!isNumber(value)) {
            modifier(this._modifiers, ContrastModifier, undefined);
        }
        else {
            modifier(this._modifiers, ContrastModifier, value);
        }
        return this;
    }

    grayscale(value: number): this {
        if (!isNumber(value)) {
            modifier(this._modifiers, GrayscaleModifier, undefined);
        }
        else {
            modifier(this._modifiers, GrayscaleModifier, value);
        }
        return this;
    }

    colorBlend(value: Color | string | Resource): this {
        var arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, ColorBlendModifier, arkColor.color);
        } else {
            modifier(this._modifiers, ColorBlendModifier, undefined);
        }
        return this;
    }

    saturate(value: number): this {
        if (!isNumber(value)) {
            modifier(this._modifiers, SaturateModifier, undefined);
        }
        else {
            modifier(this._modifiers, SaturateModifier, value);
        }
        return this;
    }

    sepia(value: number): this {
        if (!isNumber(value)) {
            modifier(this._modifiers, SepiaModifier, undefined);
        }
        else {
            modifier(this._modifiers, SepiaModifier, value);
        }
        return this;
    }

    invert(value: number): this {
        if (!isNumber(value)) {
            modifier(this._modifiers, InvertModifier, undefined);
        }
        else {
            modifier(this._modifiers, InvertModifier, value);
        }
        return this;
    }

    hueRotate(value: number | string): this {
        if (!isNumber(value) && !isString(value)) {
            modifier(this._modifiers, HueRotateModifier, undefined);
        }
        else {
            modifier(this._modifiers, HueRotateModifier, value);
        }
        return this;
    }

    useEffect(value: boolean): this {
        throw new Error("Method not implemented.");
    }

    backdropBlur(value: number): this {
        if (!isNumber(value)) {
            modifier(this._modifiers, BackdropBlurModifier, undefined);
        }
        else {
            modifier(this._modifiers, BackdropBlurModifier, value);
        }
        return this;
    }

    renderGroup(value: boolean): this {
        throw new Error("Method not implemented.");
    }

    translate(value: TranslateOptions): this {
        var arkTranslate = new ArkTranslate()
        if (isNumber(value?.x) || isString(value?.x)) {
            arkTranslate.x = value.x
        }
        if (isNumber(value?.y) || isString(value?.y)) {
            arkTranslate.y = value.y
        }
        if (isNumber(value?.z) || isString(value?.z)) {
            arkTranslate.z = value.z
        }
        modifier(this._modifiers, TranslateModifier, arkTranslate);
        return this;
    }

    scale(value: ScaleOptions): this {
        var arkScale = new ArkScale()
        if (isNumber(value?.x)) {
            arkScale.x = value?.x
        }
        if (isNumber(value?.y)) {
            arkScale.y = value?.y
        }
        if (isNumber(value?.z)) {
            arkScale.z = value?.z
        }
        if (isNumber(value?.centerX) || isString(value?.centerX)) {
            arkScale.centerX = value?.centerX
        }
        if (isNumber(value?.centerY) || isString(value?.centerY)) {
            arkScale.centerY = value?.centerY
        }
        modifier(this._modifiers, ScaleModifier, arkScale);
        return this;
    }

    gridSpan(value: number): this {
        throw new Error("Method not implemented.");
    }

    gridOffset(value: number): this {
        throw new Error("Method not implemented.");
    }

    rotate(value: RotateOptions): this {
        var arkRotate = new ArkRotate()
        if ( isNumber(value?.x)){
            arkRotate.x = value?.x
        }
        if ( isNumber(value?.y)){
            arkRotate.y = value?.y
        }
        if ( isNumber(value?.z)){
            arkRotate.z = value?.z
        }
        if ( isNumber(value?.angle) || isString(value?.angle)){
            arkRotate.angle = value?.angle
        }
        if ( isNumber(value?.centerX) || isString(value?.centerX)){
            arkRotate.centerX = value?.centerX
        }
        if ( isNumber(value?.centerY) || isString(value?.centerY)){
            arkRotate.centerY = value?.centerY
        }
        if ( isNumber(value?.centerZ) || isString(value?.centerZ)){
            arkRotate.centerZ = value?.centerZ
        }
        if ( isNumber(value?.perspective)){
            arkRotate.perspective = value?.perspective
        }
        modifier(this._modifiers, RotateModifier, arkRotate);
        return this;
    }

    transform(value: object): this {
        if(isUndefined(value)){
            modifier(this._modifiers, TransformModifier, undefined);
        }
        else{
            modifier(this._modifiers, TransformModifier, new ArkTransformMatrix(value["matrix4x4"]));
        }        
        return this;
    }

    onAppear(event: () => void): this {
        throw new Error("Method not implemented.");
    }

    onDisAppear(event: () => void): this {
        throw new Error("Method not implemented.");
    }

    onAreaChange(event: (oldValue: Area, newValue: Area) => void): this {
        throw new Error("Method not implemented.");
    }

    visibility(value: Visibility): this {
        throw new Error("Method not implemented.");
    }

    flexGrow(value: number): this {
        throw new Error("Method not implemented.");
    }

    flexShrink(value: number): this {
        throw new Error("Method not implemented.");
    }

    flexBasis(value: number | string): this {
        throw new Error("Method not implemented.");
    }

    alignSelf(value: ItemAlign): this {
        throw new Error("Method not implemented.");
    }

    displayPriority(value: number): this {
        throw new Error("Method not implemented.");
    }

    zIndex(value: number): this {
        if (value !== null) {
            var zIndex = 0;
            if (typeof (value) === "number") {
                zIndex = value;
            }
            modifier(this._modifiers, ZIndexModifier, zIndex);
        }
        return this;
    }

    sharedTransition(id: string, options?: sharedTransitionOptions): this {
        throw new Error("Method not implemented.");
    }

    direction(value: Direction): this {
        throw new Error("Method not implemented.");
    }

    align(value: Alignment): this {
        if (isNumber(value)) {
            modifier(this._modifiers, AlignModifier, value);
        } else {
            modifier(this._modifiers, AlignModifier, undefined);
        }
        return this 
    }

    position(value: Position): this {
        if(isResource(value) || isUndefined(value)){
            modifier(this._modifiers, PositionModifier, undefined);
            return this;
        }
        if (isNumber(value?.x) || isString(value?.x) || isNumber(value?.y) || isString(value?.y)){
            var position = new ArkPosition();
            position.x = value?.x
            position.y = value?.y
            modifier(this._modifiers, PositionModifier, position);
        }
        else {
            modifier(this._modifiers, PositionModifier, undefined);
        }
        return this;
    }

    markAnchor(value: Position): this {
        throw new Error("Method not implemented.");
    }

    offset(value: Position): this {
        throw new Error("Method not implemented.");
    }

    enabled(value: boolean): this {
        throw new Error("Method not implemented.");
    }

    useSizeType(value: {
        xs?: number | { span: number; offset: number };
        sm?: number | { span: number; offset: number };
        md?: number | { span: number; offset: number };
        lg?: number | { span: number; offset: number };
    }): this {
        throw new Error("Method not implemented.");
    }

    alignRules(value: AlignRuleOption): this {
        throw new Error("Method not implemented.");
    }

    aspectRatio(value: number): this {
        throw new Error("Method not implemented.");
    }

    clickEffect(value: ClickEffect | null): this {
        throw new Error("Method not implemented.");
    }

    onDragStart(event: (event?: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo): this {
        throw new Error("Method not implemented.");
    }

    onDragEnter(event: (event?: DragEvent, extraParams?: string) => void): this {
        throw new Error("Method not implemented.");
    }

    onDragMove(event: (event?: DragEvent, extraParams?: string) => void): this {
        throw new Error("Method not implemented.");
    }

    onDragLeave(event: (event?: DragEvent, extraParams?: string) => void): this {
        throw new Error("Method not implemented.");
    }

    onDrop(event: (event?: DragEvent, extraParams?: string) => void): this {
        throw new Error("Method not implemented.");
    }

    onDragEnd(event: (event: DragEvent, extraParams?: string) => void): this {
        throw new Error("Method not implemented.");
    }

    allowDrop(value: Array<UniformDataType>): this {
        throw new Error("Method not implemented.");
    }

    draggable(value: boolean): this {
        throw new Error("Method not implemented.");
    }

    overlay(value: string | CustomBuilder, options?: { align?: Alignment; offset?: { x?: number; y?: number } }): this {
        throw new Error("Method not implemented.");
    }

    linearGradient(value: {
        angle?: number | string;
        direction?: GradientDirection;
        colors: Array<any>;
        repeating?: boolean;
    }): this {
        let arkLinearGradient = new ArkLinearGradient(value.angle, value.direction, value.colors, value.repeating);
        modifier(this._modifiers, LinearGradientModifier, arkLinearGradient);
        return this;
    }

    sweepGradient(value: {
        center: Array<any>;
        start?: number | string;
        end?: number | string;
        rotation?: number | string;
        colors: Array<any>;
        repeating?: boolean;
    }): this {
        let arkSweepGradient = new ArkSweepGradient(value.center, value.start, value.end, value.rotation,
            value.colors, value.repeating);
        modifier(this._modifiers, SweepGradientModifier, arkSweepGradient);
        return this;
    }

    radialGradient(value: { center: Array<any>; radius: number | string; colors: Array<any>; repeating?: boolean }): this {
        let arkRadialGradient = new ArkRadialGradient(value.center, value.radius, value.colors, value.repeating);
        modifier(this._modifiers, RadialGradientModifier, arkRadialGradient);
        return this;
    }

    motionPath(value: MotionPathOptions): this {
        throw new Error("Method not implemented.");
    }

    shadow(value: ShadowOptions | ShadowStyle): this {
        var arkShadow = new ArkShadow();
        if (arkShadow.parseShadowValue(value)) {
            modifier(this._modifiers, ShadowModifier, arkShadow);
        } else {
            modifier(this._modifiers, ShadowModifier, undefined);
        }
        return this;
    }

    mask(value: CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute | ProgressMask): this {
        throw new Error("Method not implemented.");
    }

    key(value: string): this {
        throw new Error("Method not implemented.");
    }

    id(value: string): this {
        throw new Error("Method not implemented.");
    }

    geometryTransition(id: string): this {
        if(isString(id))
        {
            modifier(this._modifiers, GeometryTransitionModifier, id);
        }
        return this;
    }

    bindPopup(show: boolean, popup: PopupOptions | CustomPopupOptions): this {
        throw new Error("Method not implemented.");
    }

    bindMenu(content: Array<MenuElement> | CustomBuilder, options?: MenuOptions): this {
        throw new Error("Method not implemented.");
    }

    bindContextMenu(content: CustomBuilder, responseType: ResponseType, options?: ContextMenuOptions): this {
        throw new Error("Method not implemented.");
    }

    bindContentCover(isShow: boolean, builder: CustomBuilder, type?: ModalTransition | ContentCoverOptions): this {
        throw new Error("Method not implemented.");
    }

    blendMode(value: BlendMode): this {
        throw new Error("Method not implemented.");
    }

    clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this {
        modifierWithKey(this._modifiersWithKeys, Symbol("clip"), ClipModifier, value);
        return this
    }

    bindSheet(isShow: boolean, builder: CustomBuilder, options?: SheetOptions): this {
        throw new Error("Method not implemented.");
    }

    stateStyles(value: StateStyles): this {
        throw new Error("Method not implemented.");
    }

    restoreId(value: number): this {
        throw new Error("Method not implemented.");
    }

    onVisibleAreaChange(ratios: Array<number>, event: (isVisible: boolean, currentRatio: number) => void): this {
        throw new Error("Method not implemented.");
    }

    sphericalEffect(value: number): this {
        throw new Error("Method not implemented.");
    }

    lightUpEffect(value: number): this {
        throw new Error("Method not implemented.");
    }

    pixelStretchEffect(options: PixelStretchEffectOptions): this {
        throw new Error("Method not implemented.");
    }

    keyboardShortcut(value: string | FunctionKey, keys: Array<ModifierKey>, action?: () => void): this {
        throw new Error("Method not implemented.");
    }

    accessibilityGroup(value: boolean): this {
        throw new Error("Method not implemented.");
    }

    accessibilityText(value: string): this {
        throw new Error("Method not implemented.");
    }

    accessibilityDescription(value: string): this {
        throw new Error("Method not implemented.");
    }

    accessibilityLevel(value: string): this {
        throw new Error("Method not implemented.");
    }

    obscured(reasons: Array<ObscuredReasons>): this {
        throw new Error("Method not implemented.");
    }

    reuseId(id: string): this {
        throw new Error("Method not implemented.");
    }

    renderFit(fitMode: RenderFit): this {
        throw new Error("Method not implemented.");
    }

    attributeModifier(modifier: AttributeModifier<CommonAttribute>): this {
        return this;
    }
}