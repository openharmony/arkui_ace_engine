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

function isResourceEqual(stageValue: Resource, value: Resource): boolean {
    return (stageValue.bundleName === value.bundleName) &&
            (stageValue.moduleName === value.moduleName) &&
            (stageValue.id === value.id) &&
            (stageValue.params === value.params) &&
            (stageValue.type === value.type);
}

const SAFE_AREA_TYPE_NONE = 0;
const SAFE_AREA_TYPE_SYSTEM = 1;
const SAFE_AREA_TYPE_CUTOUT = 2;
const SAFE_AREA_TYPE_KEYBOARD = 4;
const SAFE_AREA_TYPE_ALL = 7;

const SAFE_AREA_EDGE_NONE = 0;
const SAFE_AREA_EDGE_TOP = 1;
const SAFE_AREA_EDGE_BOTTOM = 2;
const SAFE_AREA_EDGE_START = 4;
const SAFE_AREA_EDGE_END = 8;
const SAFE_AREA_EDGE_ALL = 15;

const SAFE_AREA_TYPE_LIMIT = 3;
const SAFE_AREA_EDGE_LIMIT = 4;
const DIRECTION_RANGE = 3;

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
            if(this.value === undefined)
            {                
                this.applyPeer(node, true);                
            }
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
            if (this.stageValue === undefined) {
                this.applyPeer(node, true);
            } else {
                this.value = this.stageValue;
                this.applyPeer(node, false);
            }
        }
        this.stageValue = undefined;
        return false;
    }

    applyPeer(node: KNode, reset: boolean): void { }

    checkObjectDiff(): boolean {
        return true;
    }
}

class BackgroundColorModifier extends ModifierWithKey<ResourceColor> {
    static identity: Symbol = Symbol("backgroundColor");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetBackgroundColor(node);
        } else {
            GetUINativeModule().common.setBackgroundColor(node, this.value);
        }
    }

    checkObjectDiff(): boolean {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        } else {
            return true;
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

class BorderColorModifier extends ModifierWithKey<ResourceColor | EdgeColors> {
    static identity: Symbol = Symbol("borderColor");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetBorderColor(node);
        }
        else {
            if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
                GetUINativeModule().common.setBorderColor(node, this.value, this.value, this.value, this.value);
            } else {
                GetUINativeModule().common.setBorderColor(node, (this.value as EdgeColors).left,
                    (this.value as EdgeColors).right, (this.value as EdgeColors).top,
                    (this.value as EdgeColors).bottom);
            }

        }
    }

    checkObjectDiff(): boolean {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        } else if (!isResource(this.stageValue) && !isResource(this.value)) {
            return !((this.stageValue as EdgeColors).left === (this.value as EdgeColors).left &&
                (this.stageValue as EdgeColors).right === (this.value as EdgeColors).right &&
                (this.stageValue as EdgeColors).top === (this.value as EdgeColors).top &&
                (this.stageValue as EdgeColors).bottom === (this.value as EdgeColors).bottom);
        } else {
            return true;
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

class PixelStretchEffectModifier extends Modifier<ArkPixelStretchEffect> {
    static identity: Symbol = Symbol("pixelStretchEffect");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetPixelStretchEffect(node);
        }
        else {
            GetUINativeModule().common.setPixelStretchEffect(node,
                this.value.top, this.value.right, this.value.bottom, this.value.left);
        }
    }
}

class LightUpEffectModifier extends Modifier<number> {
    static identity: Symbol = Symbol("lightUpEffect");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetLightUpEffect(node);
        }
        else {
            GetUINativeModule().common.setLightUpEffect(node, this.value);
        }
    }
}

class SphericalEffectModifier extends Modifier<number> {
    static identity: Symbol = Symbol("sphericalEffect");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetSphericalEffect(node);
        }
        else {
            GetUINativeModule().common.setSphericalEffect(node, this.value);
        }
    }
}

class RenderGroupModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol("renderGroup");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetRenderGroup(node);
        }
        else {
            GetUINativeModule().common.setRenderGroup(node, this.value);
        }
    }
}

class RenderFitModifier extends Modifier<number> {
    static identity: Symbol = Symbol("renderFit");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetRenderFit(node);
        }
        else {
            GetUINativeModule().common.setRenderFit(node, this.value);
        }
    }
}

class UseEffectModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol("useEffect");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetUseEffect(node);
        }
        else {
            GetUINativeModule().common.setUseEffect(node, this.value);
        }
    }
}

class ForegroundColorModifier extends Modifier<ArkForegroundColor> {
    static identity: Symbol = Symbol("foregroundColor");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetForegroundColor(node);
        }
        else {
            GetUINativeModule().common.setForegroundColor(node,
                this.value.color, this.value.strategy);
        }
    }
}

class MotionPathModifier extends Modifier<ArkMotionPath> {
    static identity: Symbol = Symbol("motionPath");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetMotionPath(node);
        }
        else {
            GetUINativeModule().common.setMotionPath(node, this.value.path, this.value.from,
                this.value.to, this.value.rotatable);
        }
    }
}

class GroupDefaultFocusModifier extends Modifier <boolean> {
    static identity: Symbol = Symbol("groupDefaultFocus");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetGroupDefaultFocus(node);
        }
        else {
            GetUINativeModule().common.setGroupDefaultFocus(node, this.value);
        }
    }
}

class FocusOnTouchModifier extends Modifier <boolean> {
    static identity: Symbol = Symbol("focusOnTouch");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetFocusOnTouch(node);
        }
        else {
            GetUINativeModule().common.setFocusOnTouch(node, this.value);
        }
    }
}
class OffsetModifier extends Modifier<ArkPosition> {
  static identity: Symbol = Symbol('offset');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().common.resetOffset(node);
    } else {
      GetUINativeModule().common.setOffset(node, this.value.x, this.value.y);
    }
  }
}

class MarkAnchorModifier extends Modifier<ArkPosition> {
  static identity: Symbol = Symbol('markAnchor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().common.resetMarkAnchor(node);
    } else {
      GetUINativeModule().common.setMarkAnchor(node, this.value.x, this.value.y);
    }
  }
}
class DefaultFocusModifier extends Modifier<boolean>{
    static identity: Symbol = Symbol("defaultFocus");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetDefaultFocus(node);
        }
        else {
            GetUINativeModule().common.setDefaultFocus(node, this.value);
        }
    }
}

class FocusableModifier extends Modifier<boolean>{
    static identity: Symbol = Symbol("focusable");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetFocusable(node);
        }
        else {
            GetUINativeModule().common.setFocusable(node, this.value);
        }
    }
}

class TouchableModifier extends Modifier<boolean>{
    static identity: Symbol = Symbol("touchable");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetTouchable(node);
        }
        else {
            GetUINativeModule().common.setTouchable(node, this.value);
        }
    }
}

class MarginModifier extends Modifier<ArkPadding> {
  static identity: Symbol = Symbol('margin');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().common.resetMargin(node);
    } else {
      GetUINativeModule().common.setMargin(node, this.value.top,
        this.value.right, this.value.bottom, this.value.left);
    }

  }
}

class PaddingModifier extends Modifier<ArkPadding> {
  static identity: Symbol = Symbol('padding');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().common.resetPadding(node);
    } else {
      GetUINativeModule().common.setPadding(node, this.value.top,
        this.value.right, this.value.bottom, this.value.left);
    }
  }
}

class VisibilityModifier extends Modifier<number> {
  static identity: Symbol = Symbol('visibility');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().common.resetVisibility(node);
    } else {
      GetUINativeModule().common.setVisibility(node, this.value!);
    }
  }
}

class AccessibilityTextModifier extends Modifier<string> {
    static identity: Symbol = Symbol("accessibilityText");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetAccessibilityText(node);
        }
        else {
            GetUINativeModule().common.setAccessibilityText(node, this.value);
        }
    }
}

class AllowDropModifier extends Modifier<ArkAllowDrop> {
    static identity: Symbol = Symbol("allowDrop");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetAllowDrop(node);
        }
        else {
            GetUINativeModule().common.setAllowDrop(node, this.value.allowDropArray);
        }
    }
}

class AccessibilityLevelModifier extends Modifier<string> {
    static identity: Symbol = Symbol("accessibilityLevel");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetAccessibilityLevel(node);
        }
        else {
            GetUINativeModule().common.setAccessibilityLevel(node, this.value);
        }
    }
}

class AccessibilityDescriptionModifier extends Modifier<string> {
    static identity: Symbol = Symbol("accessibilityDescription");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetAccessibilityDescription(node);
        }
        else {
            GetUINativeModule().common.setAccessibilityDescription(node, this.value);
        }
    }
}


class DirectionModifier extends Modifier<string> {
  static identity: Symbol = Symbol('direction');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().common.resetDirection(node);
    } else {
      GetUINativeModule().common.setDirection(node, this.value!);
    }
  }
}
class AlignRulesModifier extends Modifier<ArkAlignRules> {
  static identity: Symbol = Symbol('alignRules');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().common.resetAlignRules(node);
    } else {
      GetUINativeModule().common.setAlignRules(node, this.value.left,
        this.value.middle, this.value.right, this.value.top, this.value.center, this.value.bottom);
    }
  }
}

class ExpandSafeAreaModifier extends Modifier<ArkSafeAreaExpandOpts | undefined> {
  static identity: Symbol = Symbol('expandSafeArea');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().common.resetExpandSafeArea(node);
    } else {
      GetUINativeModule().common.setExpandSafeArea(node, this.value.type, this.value.edges);
    }
  }
}

class GridSpanModifier extends Modifier<number> {
  static identity: Symbol = Symbol('gridSpan');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().common.resetGridSpan(node);
    } else {
      GetUINativeModule().common.setGridSpan(node, this.value!);
    }
  }
}

class GridOffsetModifier extends Modifier<number> {
  static identity: Symbol = Symbol('gridOffset');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().common.resetGridOffset(node);
    } else {
      GetUINativeModule().common.setGridOffset(node, this.value!);
    }
  }
}

class AlignSelfModifier extends Modifier<number> {
  static identity: Symbol = Symbol('alignSelf');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().common.resetAlignSelf(node);
    } else {
      GetUINativeModule().common.setAlignSelf(node, this.value!);
    }
  }
}

class SizeModifier extends Modifier<ArkSize> {
  static identity: Symbol = Symbol('size');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().common.resetSize(node);
    } else {
      GetUINativeModule().common.setSize(node, this.value.width, this.value.height);
    }
  }
}

class DisplayPriorityModifier extends Modifier<number> {
  static identity: Symbol = Symbol('displayPriority');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().common.resetDisplayPriority(node);
    } else {
      GetUINativeModule().common.setDisplayPriority(node, this.value!);
    }
  }
}

class IDModifier extends Modifier<string> {
    static identity: Symbol = Symbol("id");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetID(node);
        }
        else {
            GetUINativeModule().common.setID(node, this.value);
        }
    }
}

class KeyModifier extends Modifier<string> {
    static identity: Symbol = Symbol("key");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetKey(node);
        }
        else {
            GetUINativeModule().common.setKey(node, this.value);
        }
    }
}

class RestoreIdModifier extends Modifier<number> {
    static identity: Symbol = Symbol("restoreId");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetRestoreId(node);
        }
        else {
            GetUINativeModule().common.setRestoreId(node, this.value);
        }
    }
}

class TabIndexModifier extends Modifier<number> {
    static identity: Symbol = Symbol("tabIndex");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetTabIndex(node);
        }
        else {
            GetUINativeModule().common.setTabIndex(node, this.value);
        }
    }
}

class ObscuredModifier extends Modifier<ArkObscured> {
    static identity: Symbol = Symbol("obscured");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetObscured(node);
        }
        else {
            GetUINativeModule().common.setObscured(node, this.value.reasons);
        }
    }
}

class MouseResponseRegionModifier extends Modifier<ArkResponseRegion> {
    static identity = Symbol("mouseResponseRegion");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetMouseResponseRegion(node);
        }
        else {
            GetUINativeModule().common.setMouseResponseRegion(node, this.value.responseRegion);
        }
    }
}

class ResponseRegionModifier extends Modifier<ArkResponseRegion> {
    static identity = Symbol("responseRegion");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().common.resetResponseRegion(node);
        }
        else {
            GetUINativeModule().common.setResponseRegion(node, this.value.responseRegion);
        }
    }
}
class FlexGrowModifier extends Modifier<number> {
  static identity: Symbol = Symbol('flexGrow');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().common.resetFlexGrow(node);
    } else {
      GetUINativeModule().common.setFlexGrow(node, this.value!);
    }
  }
}

class FlexShrinkModifier extends Modifier<number> {
  static identity: Symbol = Symbol('flexShrink');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().common.resetFlexShrink(node);
    } else {
      GetUINativeModule().common.setFlexShrink(node, this.value!);
    }
  }
}

class AspectRatioModifier extends Modifier<number> {
  static identity: Symbol = Symbol('aspectRatio');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().common.resetAspectRatio(node);
    } else {
      GetUINativeModule().common.setAspectRatio(node, this.value!);
    }
  }
}

class ConstraintSizeModifier extends Modifier<ArkConstraintSizeOptions> {
  static identity: Symbol = Symbol('constraintSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().common.resetConstraintSize(node);
    } else {
      GetUINativeModule().common.setConstraintSize(node, this.value.minWidth,
        this.value.maxWidth, this.value.minHeight, this.value.maxHeight);
    }
  }
}

class FlexBasisModifier extends Modifier<number | string> {
  static identity: Symbol = Symbol('flexBasis');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().common.resetFlexBasis(node);
    } else {
      GetUINativeModule().common.setFlexBasis(node, this.value!);
    }
  }
}

class LayoutWeightModifier extends Modifier<number | string> {
  static identity: Symbol = Symbol('layoutWeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().common.resetLayoutWeight(node);
    } else {
      GetUINativeModule().common.setLayoutWeight(node, this.value!);
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
const isLengthType = (val: any) => typeof val === 'string' || typeof val === 'number'
const lessThenFunction = (val1: number, val2: number) => (val1 - val2) < 0.001

function CheckJSCallbackInfo(value: any, checklist: any[]) {
    let typeVerified = false;
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
    let opts = new ArkSafeAreaExpandOpts();
    opts.type = SAFE_AREA_TYPE_ALL;
    opts.edges = SAFE_AREA_EDGE_ALL;

    if (types && types.length > 0) {
      let safeAreaType: string | number = '';
      for (let param of types) {
        if (!isNumber(param) || param >= SAFE_AREA_TYPE_LIMIT) {
          safeAreaType = SAFE_AREA_TYPE_ALL;
          break;
        }
        if (safeAreaType) {
          safeAreaType += '|';
        } else {
          safeAreaType += param.toString();
        }
      }
      opts.type = safeAreaType;
    }
    if (edges && edges.length > 0) {
      let safeAreaEdge: string | number = '';
      for (let param of edges) {
        if (!isNumber(param) || param >= SAFE_AREA_EDGE_LIMIT) {
          safeAreaEdge = SAFE_AREA_EDGE_ALL;
          break;
        }
        if (safeAreaEdge) {
          safeAreaEdge += '|';
        } else {
          safeAreaEdge += param.toString();
        }
      }
      opts.edges = safeAreaEdge;
    }
    if (opts.type === SAFE_AREA_TYPE_ALL && opts.edges === SAFE_AREA_EDGE_ALL) {
      // modifier(this._modifiers, ExpandSafeAreaModifier, undefined);
    } else {
      modifier(this._modifiers, ExpandSafeAreaModifier, opts);
    }
    return this;
  }

    responseRegion(value: Array<Rectangle> | Rectangle): this {
        let arkResponseRegion = new ArkResponseRegion();
        if (arkResponseRegion.parseRegionValue(value)) {
            modifier(this._modifiers, ResponseRegionModifier, arkResponseRegion);
        } else {
            modifier(this._modifiers, ResponseRegionModifier, undefined);
        }
        return this;
    }

    mouseResponseRegion(value: Array<Rectangle> | Rectangle): this {
        let arkMouseResponseRegion = new ArkResponseRegion();
        if (arkMouseResponseRegion.parseRegionValue(value)) {
            modifier(this._modifiers, MouseResponseRegionModifier, arkMouseResponseRegion);
        } else {
            modifier(this._modifiers, MouseResponseRegionModifier, undefined);
        }
        return this;
    }

  size(value: SizeOptions): this {
    let arkValue: ArkSize = new ArkSize();
    if (!value || (!isLengthType(value.width) && !isLengthType(value.height))) {
      modifier(this._modifiers, SizeModifier, undefined);
    }

    if (value.width && isLengthType(value.width)) {
      arkValue.width = <string | number>value.width;
    }
    if (value.height && isLengthType(value.height)) {
      arkValue.height = <string | number>value.height;
    }
    modifier(this._modifiers, SizeModifier, arkValue);

    return this;
  }

  constraintSize(value: ConstraintSizeOptions): this {
    let arkValue: ArkConstraintSizeOptions = new ArkConstraintSizeOptions();

    if (!value ||
      (!isLengthType(value.minWidth) && !isLengthType(value.maxWidth) &&
        !isLengthType(value.minHeight) && !isLengthType(value.maxHeight))) {
      modifier(this._modifiers, ConstraintSizeModifier, undefined);
      return this;
    }
    if (value.minWidth && isLengthType(value.minWidth)) {
      arkValue.minWidth = <string | number>value?.minWidth;
    }
    if (value.maxWidth && isLengthType(value.maxWidth)) {
      arkValue.maxWidth = <string | number>value?.maxWidth;
    }
    if (value.minHeight && isLengthType(value.minHeight)) {
      arkValue.minHeight = <string | number>value?.minHeight;
    }
    if (value.maxHeight && isLengthType(value.maxHeight)) {
      arkValue.maxHeight = <string | number>value?.maxHeight;
    }
    modifier(this._modifiers, ConstraintSizeModifier, arkValue);
    return this;
  }

    touchable(value: boolean): this {
        if (typeof value === 'boolean') {
            modifier(this._modifiers, TouchableModifier, value);
        } else {
            modifier(this._modifiers, TouchableModifier, undefined);
        }
        return this;
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
    if (isNumber(value)) {
      modifier(this._modifiers, LayoutWeightModifier, value);
    }
    else if (isString(value) && !isNaN(Number(value))) {
      modifier(this._modifiers, LayoutWeightModifier, parseInt(value.toString()));
    } else {
      modifier(this._modifiers, LayoutWeightModifier, 0);
    }
    return this;
  }

  padding(value: Padding | Length): this {
    let arkValue = new ArkPadding();
    if (value !== null && value !== undefined) {
      if (isLengthType(value)) {
        arkValue.top = <string | number>value;
        arkValue.right = <string | number>value;
        arkValue.bottom = <string | number>value;
        arkValue.left = <string | number>value;
      } else {
        if ((<Padding>value).top && isLengthType((<Padding>value).top)) {
          arkValue.top = <string | number>(<Padding>value).top;
        }
        if ((<Padding>value).right && isLengthType((<Padding>value).right)) {
          arkValue.right = <string | number>(<Padding>value).right;
        }
        if ((<Padding>value).bottom && isLengthType((<Padding>value).bottom)) {
          arkValue.bottom = <string | number>(<Padding>value).bottom;
        }
        if ((<Padding>value).left && isLengthType((<Padding>value).left)) {
          arkValue.left = <string | number>(<Padding>value).left;
        }
      }
      modifier(this._modifiers, PaddingModifier, arkValue);
    } else {
      modifier(this._modifiers, PaddingModifier, undefined);
    }
    return this;
  }

  margin(value: Margin | Length): this {
    let arkValue = new ArkPadding();
    if (value !== null && value !== undefined) {
      if (!isNaN(Number(value)) && isLengthType(value)) {
        arkValue.top = <string | number>value;
        arkValue.right = <string | number>value;
        arkValue.bottom = <string | number>value;
        arkValue.left = <string | number>value;
      } else {
        if ((<Padding>value).top && isLengthType((<Padding>value).top)) {
          arkValue.top = <string | number>(<Padding>value).top;
        }
        if ((<Padding>value).right && isLengthType((<Padding>value).right)) {
          arkValue.right = <string | number>(<Padding>value).right;
        }
        if ((<Padding>value).bottom && isLengthType((<Padding>value).bottom)) {
          arkValue.bottom = <string | number>(<Padding>value).bottom;
        }
        if ((<Padding>value).left && isLengthType((<Padding>value).left)) {
          arkValue.left = <string | number>(<Padding>value).left;
        }
      }
      modifier(this._modifiers, MarginModifier, arkValue);
    } else {
      modifier(this._modifiers, MarginModifier, undefined);
    }
    return this;
  }

    background(builder: CustomBuilder, options?: { align?: Alignment }): this {
        throw new Error("Method not implemented.");
    }

    backgroundColor(value: ResourceColor): this {
        modifierWithKey(this._modifiersWithKeys, BackgroundColorModifier.identity, BackgroundColorModifier, value);
        return this;
    }

    backgroundImage(src: ResourceStr, repeat?: ImageRepeat): this {
        let arkBackgroundImage = new ArkBackgroundImage()
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
        let arkBackgroundImageSize = new ArkBackgroundImageSize()
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
        let arkBackgroundImagePosition = new ArkBackgroundImagePosition()
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
        let opacityDefault = 0.0;
        if(isResource(value)){
            modifier(this._modifiers, OpacityModifier, opacityDefault);
            return this;
        }
        let checklist = [JSCallbackInfoType.OBJECT, JSCallbackInfoType.NUMBER, JSCallbackInfoType.STRING];
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
        let arkBorder = new ArkBorder()
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
            let arkColor = new ArkColor();
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
            let arkBorderStyle = new ArkBorderStyle();
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
        let arkBorderStyle = new ArkBorderStyle();
        if (arkBorderStyle.parseBorderStyle(value)) {
            modifier(this._modifiers, BorderStyleModifier, arkBorderStyle);
        } else {
            modifier(this._modifiers, BorderStyleModifier, undefined);
        }
        return this;
    }

    borderWidth(value: Length | EdgeWidths): this {
        let borderWidth = new ArkBorderWidth()
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
        modifierWithKey(this._modifiersWithKeys, BorderColorModifier.identity, BorderColorModifier, value);
        return this;
    }

    borderRadius(value: Length | BorderRadiuses): this {
        if( isResource(value) || isUndefined(value))
        {
            modifier(this._modifiers, BorderRadiusModifier, undefined);
            return this;
        }

        let borderRadius = new ArkBorderRadius
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
        let arkForegroundColor = new ArkForegroundColor
        if (typeof value === "string") {
            let lowerValue = value.toLowerCase().trim();
            if (lowerValue === "invert") {
                arkForegroundColor.strategy = lowerValue;
                modifier(this._modifiers, ForegroundColorModifier, arkForegroundColor);
                return this;
            }
        }
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            arkForegroundColor.color = arkColor.getColor();
            modifier(this._modifiers, ForegroundColorModifier, arkForegroundColor);
        } else {
            modifier(this._modifiers, ForegroundColorModifier, undefined);
        }
        return this;
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
        if (typeof value === 'boolean') {
            modifier(this._modifiers, FocusableModifier, value);
        } else {
            modifier(this._modifiers, FocusableModifier, undefined);
        }
        return this;
    }

    onFocus(event: () => void): this {
        throw new Error("Method not implemented.");
    }

    onBlur(event: () => void): this {
        throw new Error("Method not implemented.");
    }

    tabIndex(index: number): this {
        if (typeof index !== "number") {
            modifier(this._modifiers, TabIndexModifier, undefined);
        }
        else {
            modifier(this._modifiers, TabIndexModifier, index);
        }
        return this;
    }

    defaultFocus(value: boolean): this {
        if (typeof value === 'boolean') {
            modifier(this._modifiers, DefaultFocusModifier, value);
        } else {
            modifier(this._modifiers, DefaultFocusModifier, undefined);
        }
        return this;
    }

    groupDefaultFocus(value: boolean): this {
        if (typeof value === "boolean") {
            modifier(this._modifiers, GroupDefaultFocusModifier, value);
        } else {
            modifier(this._modifiers, GroupDefaultFocusModifier, undefined);
        }
        return this;	
    }

    focusOnTouch(value: boolean): this {
        if (typeof value === "boolean") {
            modifier(this._modifiers, FocusOnTouchModifier, value);
        } else {
            modifier(this._modifiers, FocusOnTouchModifier, undefined);
        }
        return this;	
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
        let arkColor = new ArkColor();
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
        modifier(this._modifiers, UseEffectModifier, value);
        return this;
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
        modifier(this._modifiers, RenderGroupModifier, value);
        return this;
    }

    translate(value: TranslateOptions): this {
        let arkTranslate = new ArkTranslate()
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
        let arkScale = new ArkScale()
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
    if (value === null || value === undefined) {
      modifier(this._modifiers, GridSpanModifier, undefined);
    } else {
      modifier(this._modifiers, GridSpanModifier, value);
    }
    return this;
  }

  gridOffset(value: number): this {
    if (value === null || value === undefined) {
      modifier(this._modifiers, GridOffsetModifier, undefined);
    } else {
      modifier(this._modifiers, GridOffsetModifier, value);
    }
    return this;
  }

    rotate(value: RotateOptions): this {
        let arkRotate = new ArkRotate()
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
    if (isNaN(value)) {
      modifier(this._modifiers, VisibilityModifier, undefined);
    } else {
      modifier(this._modifiers, VisibilityModifier, value);
    }
    return this;
  }

  flexGrow(value: number): this {
    if (isNaN(value) || value < 0.0) {
      modifier(this._modifiers, FlexGrowModifier, undefined);
    } else {
      modifier(this._modifiers, FlexGrowModifier, value);
    }
    return this;
  }

  flexShrink(value: number): this {
    if (isNaN(value) || value < 0.0) {
      modifier(this._modifiers, FlexShrinkModifier, undefined);
    } else {
      modifier(this._modifiers, FlexShrinkModifier, value);
    }
    return this;
  }

  flexBasis(value: number | string): this {
    if (isLengthType(value)) {
      modifier(this._modifiers, FlexBasisModifier, value);
    } else {
      modifier(this._modifiers, FlexBasisModifier, undefined);
    }
    return this;
  }

  alignSelf(value: ItemAlign): this {
    if (value) {
      modifier(this._modifiers, AlignSelfModifier, value);
    } else {
      modifier(this._modifiers, AlignSelfModifier, ItemAlign.Auto);
    }
    return this;
  }

  displayPriority(value: number): this {
    if (isNaN(value)) {
      modifier(this._modifiers, DisplayPriorityModifier, undefined);
    } else {
      modifier(this._modifiers, DisplayPriorityModifier, value);
    }
    return this;
  }

    zIndex(value: number): this {
        if (value !== null) {
            let zIndex = 0;
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
    let direction: string = '';
    switch (value) {
      case 0: direction = 'Ltr'; break;
      case 1: direction = 'Rtl'; break;
      case 2:
      default: direction = 'Auto'; break;
    }
    modifier(this._modifiers, DirectionModifier, direction);
    return this;
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
            let position = new ArkPosition();
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
    let arkValue = new ArkPosition();
    if (!value || (!isLengthType(value.x) && !isLengthType(value.y))) {
      modifier(this._modifiers, MarkAnchorModifier, undefined);
      return this;
    }
    if (value.x && isLengthType(value.x)) {
      arkValue.x = value?.x;
    }
    if (value.y && isLengthType(value.y)) {
      arkValue.y = value?.y;
    }
    modifier(this._modifiers, MarkAnchorModifier, arkValue);
    return this;
  }

  offset(value: Position): this {
    let arkValue = new ArkPosition();
    if (!value || (!isLengthType(value.x) && !isLengthType(value.y))) {
      modifier(this._modifiers, OffsetModifier, undefined);
      return this;
    }
    if (value.x && isLengthType(value.x)) {
      arkValue.x = value?.x;
    }
    if (value.y && isLengthType(value.y)) {
      arkValue.y = value?.y;
    }
    modifier(this._modifiers, OffsetModifier, arkValue);
    return this;
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
    if (!isObject(value) || JSON.stringify(value) === '{}') {
      modifier(this._modifiers, AlignRulesModifier, undefined);
      return this;
    }
    let keys: string[] = ['left', 'middle', 'right', 'top', 'center', 'bottom'];
    let arkValue = new ArkAlignRules();
    for (let i = 0; i < keys.length; i++) {
      let rule = value[keys[i]];
      let alignRule: string = '';
      if (isObject(rule)) {
        let alignSign = false;
        let anchorSign = false;
        let align = rule.align;
        let anchor = rule.anchor;
        if (isString(anchor)) {
          anchorSign = true;
        }
        if (i < DIRECTION_RANGE) {
          if (align in HorizontalAlign) {
            alignSign = true;
          }
        } else {
          if (align in VerticalAlign) {
            alignSign = true;
          }
        }
        if (!alignSign && !anchorSign) {
          alignRule += '';
        } else if (!anchorSign) {
          alignRule += align.toString();
          alignRule += '|';
          alignRule += '__container__';
        } else if (!alignSign) {
          alignRule += '2';
          alignRule += '|';
          alignRule += anchor;
        } else {
          alignRule += align.toString();
          alignRule += '|';
          alignRule += anchor;
        }
      } else {
        alignRule += '';
      }
      switch (keys[i]) {
        case 'left':
          arkValue.left = alignRule;
          break;
        case 'middle':
          arkValue.middle = alignRule;
          break;
        case 'right':
          arkValue.right = alignRule;
          break;
        case 'top':
          arkValue.top = alignRule;
          break;
        case 'center':
          arkValue.center = alignRule;
          break;
        case 'bottom':
          arkValue.bottom = alignRule;
          break;
      }
    }
    modifier(this._modifiers, AlignRulesModifier, arkValue);
    return this;
  }

  aspectRatio(value: number): this {

    if (isNaN(value) || lessThenFunction(value, 0.0)) {
      modifier(this._modifiers, AspectRatioModifier, undefined);
    } else {
      modifier(this._modifiers, AspectRatioModifier, value);
    }
    return this;
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
        let allowDrop = new ArkAllowDrop();
        allowDrop.allowDropArray = value;
        modifier(this._modifiers, AllowDropModifier, allowDrop);
        return this;
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
        let arkMotionPath = new ArkMotionPath();
        arkMotionPath.path = "";
        arkMotionPath.rotatable = false;
        arkMotionPath.from = 0.0;
        arkMotionPath.to = 1.0;
        if (value) {
            if (typeof value.path === "string") {
                arkMotionPath.path = value.path;
            }
            if (typeof value.rotatable === "boolean") {
                arkMotionPath.rotatable = value.rotatable;
            }
            if (typeof value.from === "number" && typeof value.to === "number") {
                arkMotionPath.from = value.from;
                arkMotionPath.to = value.to;
            }
        }
        modifier(this._modifiers, MotionPathModifier, arkMotionPath);
        return this;
    }

    shadow(value: ShadowOptions | ShadowStyle): this {
        let arkShadow = new ArkShadow();
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
        if (typeof value === "string") {
            modifier(this._modifiers, IDModifier, value);
        } else {
            modifier(this._modifiers, IDModifier, undefined);
        }
        return this;		
    }

    id(value: string): this {
        if (typeof value === "string") {
            modifier(this._modifiers, KeyModifier, value);
        } else {
            modifier(this._modifiers, KeyModifier, undefined);
        }
        return this;		
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
        if (typeof value !== "number") {
            modifier(this._modifiers, RestoreIdModifier, undefined);
        }
        else {
            modifier(this._modifiers, RestoreIdModifier, value);
        }
        return this;
    }

    onVisibleAreaChange(ratios: Array<number>, event: (isVisible: boolean, currentRatio: number) => void): this {
        throw new Error("Method not implemented.");
    }

    sphericalEffect(value: number): this {
        modifier(this._modifiers, SphericalEffectModifier, value);
        return this;
    }

    lightUpEffect(value: number): this {
        modifier(this._modifiers, LightUpEffectModifier, value);
        return this;
    }

    pixelStretchEffect(options: PixelStretchEffectOptions): this {
        if (isResource(options.top) || isResource(options.right) ||
            isResource(options.bottom)|| isResource(options.left)) {
            modifier(this._modifiers, PixelStretchEffectModifier, undefined);
            return this;
        }
        let arkPixelStretchEffect = new ArkPixelStretchEffect
        arkPixelStretchEffect.top = options.top;
        arkPixelStretchEffect.right = options.right;
        arkPixelStretchEffect.bottom = options.bottom;
        arkPixelStretchEffect.left = options.left;
        modifier(this._modifiers, PixelStretchEffectModifier, arkPixelStretchEffect);
        return this;
    }

    keyboardShortcut(value: string | FunctionKey, keys: Array<ModifierKey>, action?: () => void): this {
        throw new Error("Method not implemented.");
    }

    accessibilityGroup(value: boolean): this {
        throw new Error("Method not implemented.");
    }

    accessibilityText(value: string): this {
        if (typeof value === "string") {
            modifier(this._modifiers, AccessibilityTextModifier, value);
        } else {
            modifier(this._modifiers, AccessibilityTextModifier, undefined);
        }
        return this;
    }


    accessibilityDescription(value: string): this {
        if (typeof value !== "string") {
            modifier(this._modifiers, AccessibilityDescriptionModifier, undefined);
        }
        else {
            modifier(this._modifiers, AccessibilityDescriptionModifier, value);
        }
        return this;
    }

    accessibilityLevel(value: string): this {
        if (typeof value !== "string") {
            modifier(this._modifiers, AccessibilityLevelModifier, undefined);
        }
        else {
            modifier(this._modifiers, AccessibilityLevelModifier, value);
        }
        return this;
    }

    obscured(reasons: Array<ObscuredReasons>): this {
        let arkObscured = new ArkObscured();
        if (arkObscured.parseReasonsArray(reasons)) {
            modifier(this._modifiers, ObscuredModifier, arkObscured);
        } else {
            modifier(this._modifiers, ObscuredModifier, undefined);
        }
        return this;
    }

    reuseId(id: string): this {
        throw new Error("Method not implemented.");
    }

    renderFit(fitMode: RenderFit): this {
        modifier(this._modifiers, RenderFitModifier, fitMode);
        return this;
    }

    attributeModifier(modifier: AttributeModifier<CommonAttribute>): this {
        return this;
    }
}
