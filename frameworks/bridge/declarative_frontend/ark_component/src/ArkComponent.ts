/// <reference path="./import.ts" />
const HashMap = globalThis.requireNapi('util.HashMap')
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

class ArkComponent implements CommonMethod<CommonAttribute> {
    _modifiers: Map<Symbol, Modifier<number | string | boolean | Equable>>;
    nativePtr: KNode;

    constructor(nativePtr: KNode) {
        this._modifiers = new Map();
        this.nativePtr = nativePtr;
    }

    applyModifierPatch(): void {
        let expiringItems = [];
        this._modifiers.forEach((value, key) => {
            if (value.applyStage(this.nativePtr)) {
                expiringItems.push(key);
            }
        });

        expiringItems.forEach(key => {
            this._modifiers.delete(key);
        });
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
        throw new Error("Method not implemented.");
    }

    backgroundImageSize(value: SizeOptions | ImageSize): this {
        throw new Error("Method not implemented.");
    }

    backgroundImagePosition(value: Position | Alignment): this {
        throw new Error("Method not implemented.");
    }

    backgroundBlurStyle(value: BlurStyle, options?: BackgroundBlurStyleOptions): this {
        throw new Error("Method not implemented.");
    }

    foregroundBlurStyle(value: BlurStyle, options?: ForegroundBlurStyleOptions): this {
        throw new Error("Method not implemented.");
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
        throw new Error("Method not implemented.");
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
        throw new Error("Method not implemented.");
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
        throw new Error("Method not implemented.");
    }

    scale(value: ScaleOptions): this {
        throw new Error("Method not implemented.");
    }

    gridSpan(value: number): this {
        throw new Error("Method not implemented.");
    }

    gridOffset(value: number): this {
        throw new Error("Method not implemented.");
    }

    rotate(value: RotateOptions): this {
        throw new Error("Method not implemented.");
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
        throw new Error("Method not implemented.");
    }

    radialGradient(value: { center: Array<any>; radius: number | string; colors: Array<any>; repeating?: boolean }): this {
        throw new Error("Method not implemented.");
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
        throw new Error("Method not implemented.");
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
        throw new Error("Method not implemented.");
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