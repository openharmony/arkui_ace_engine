const arkUINativeModule = globalThis.getArkUINativeModule();
function GetUINativeModule() {
    if (arkUINativeModule) {
        return arkUINativeModule;
    }
    return arkUINativeModule;
}
function isResource(variable) {
    var _a;
    return ((_a = variable) === null || _a === void 0 ? void 0 : _a.bundleName) !== undefined;
}
function isResourceEqual(stageValue, value) {
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
class Modifier {
    constructor(value) {
        this.stageValue = value;
    }
    applyStage(node) {
        if (this.stageValue === this.value) {
            if (this.value === undefined) {
                this.applyPeer(node, true);
            }
            delete this.stageValue;
            return;
        }
        if (typeof this.stageValue === "object" && typeof this.value === "object") {
            if (this.stageValue.isEqual(this.value)) {
                delete this.stageValue;
                return;
            }
        }
        this.value = this.stageValue;
        delete this.stageValue;
        this.applyPeer(node, this.value === undefined);
        return (this.value === undefined);
    }
    applyPeer(node, reset) { }
}
class ModifierWithKey {
    constructor(value) {
        this.stageValue = value;
    }
    applyStage(node) {
        if (this.stageValue === undefined) {
            this.value = this.stageValue;
            this.applyPeer(node, true);
            return true;
        }
        const stageTypeInfo = typeof this.stageValue;
        const valueTypeInfo = typeof this.value;
        let different = false;
        if (stageTypeInfo !== valueTypeInfo) {
            different = true;
        }
        else if (stageTypeInfo === "number" || stageTypeInfo === "string" || stageTypeInfo === "boolean") {
            different = (this.stageValue !== this.value);
        }
        else {
            different = this.checkObjectDiff();
        }
        if (different) {
            this.value = this.stageValue;
            this.applyPeer(node, false);
        }
        this.stageValue = undefined;
        return false;
    }
    applyPeer(node, reset) { }
    checkObjectDiff() {
        return true;
    }
}
class BackgroundColorModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetBackgroundColor(node);
        }
        else {
            GetUINativeModule().common.setBackgroundColor(node, this.value);
        }
    }
    checkObjectDiff() {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        }
        else {
            return true;
        }
    }
}
BackgroundColorModifier.identity = Symbol("backgroundColor");
class WidthModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetWidth(node);
        }
        else {
            GetUINativeModule().common.setWidth(node, this.value);
        }
    }
    checkObjectDiff() {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        }
        else {
            return true;
        }
    }
}
WidthModifier.identity = Symbol("width");
class BorderWidthModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetBorderWidth(node);
        }
        else {
            if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
                GetUINativeModule().common.setBorderWidth(node, this.value, this.value, this.value, this.value);
            }
            else {
                GetUINativeModule().common.setBorderWidth(node, this.value.left, this.value.right, this.value.top, this.value.bottom);
            }
        }
    }
    checkObjectDiff() {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        }
        else if (!isResource(this.stageValue) && !isResource(this.value)) {
            return !(this.stageValue.left === this.value.left &&
                this.stageValue.right === this.value.right &&
                this.stageValue.top === this.value.top &&
                this.stageValue.bottom === this.value.bottom);
        }
        else {
            return true;
        }
    }
}
BorderWidthModifier.identity = Symbol("borderWidth");
class HeightModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetHeight(node);
        }
        else {
            GetUINativeModule().common.setHeight(node, this.value);
        }
    }
    checkObjectDiff() {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        }
        else {
            return true;
        }
    }
}
HeightModifier.identity = Symbol("height");
class BorderRadiusModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetBorderRadius(node);
        }
        else {
            if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
                GetUINativeModule().common.setBorderRadius(node, this.value, this.value, this.value, this.value);
            }
            else {
                GetUINativeModule().common.setBorderRadius(node, this.value.topLeft, this.value.topRight, this.value.bottomLeft, this.value.bottomRight);
            }
        }
    }
    checkObjectDiff() {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        }
        else if (!isResource(this.stageValue) && !isResource(this.value)) {
            return !(this.stageValue.topLeft === this.value.topLeft &&
                this.stageValue.topRight === this.value.topRight &&
                this.stageValue.bottomLeft === this.value.bottomLeft &&
                this.stageValue.bottomRight === this.value.bottomRight);
        }
        else {
            return true;
        }
    }
}
BorderRadiusModifier.identity = Symbol("borderRadius");
class PositionModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        var _a, _b;
        if (reset) {
            GetUINativeModule().common.resetPosition(node);
        }
        else {
            GetUINativeModule().common.setPosition(node, (_a = this.value) === null || _a === void 0 ? void 0 : _a.x, (_b = this.value) === null || _b === void 0 ? void 0 : _b.y);
        }
    }
}
PositionModifier.identity = Symbol("position");
class BorderColorModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetBorderColor(node);
        }
        else {
            const valueType = typeof this.value;
            if (valueType === "number" || valueType === "string" || isResource(this.value)) {
                GetUINativeModule().common.setBorderColor(node, this.value, this.value, this.value, this.value);
            }
            else {
                GetUINativeModule().common.setBorderColor(node, this.value.left, this.value.right, this.value.top, this.value.bottom);
            }
        }
    }
    checkObjectDiff() {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        }
        else if (!isResource(this.stageValue) && !isResource(this.value)) {
            return !(this.stageValue.left === this.value.left &&
                this.stageValue.right === this.value.right &&
                this.stageValue.top === this.value.top &&
                this.stageValue.bottom === this.value.bottom);
        }
        else {
            return true;
        }
    }
}
BorderColorModifier.identity = Symbol("borderColor");
class TransformModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetTransform(node);
        }
        else {
            GetUINativeModule().common.setTransform(node, this.value.matrix);
        }
    }
}
TransformModifier.identity = Symbol("transform");
class BorderStyleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetBorderStyle(node);
        }
        else {
            GetUINativeModule().common.setBorderStyle(node, this.value.type, this.value.style, this.value.top, this.value.right, this.value.bottom, this.value.left);
        }
    }
}
BorderStyleModifier.identity = Symbol("borderStyle");
class ShadowModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetShadow(node);
        }
        else {
            GetUINativeModule().common.setShadow(node, this.value.style, this.value.radius, this.value.type, this.value.color, this.value.offsetX, this.value.offsetY, this.value.fill);
        }
    }
}
ShadowModifier.identity = Symbol("shadow");
class HitTestBehaviorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetHitTestBehavior(node);
        }
        else {
            GetUINativeModule().common.setHitTestBehavior(node, this.value);
        }
    }
}
HitTestBehaviorModifier.identity = Symbol("hitTestBehavior");
class ZIndexModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetZIndex(node);
        }
        else {
            GetUINativeModule().common.setZIndex(node, this.value);
        }
    }
}
ZIndexModifier.identity = Symbol("zIndex");
class OpacityModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetOpacity(node);
        }
        else {
            GetUINativeModule().common.setOpacity(node, this.value);
        }
    }
    checkObjectDiff() {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        }
        else {
            return true;
        }
    }
}
OpacityModifier.identity = Symbol("opacity");
class AlignModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetAlign(node);
        }
        else {
            GetUINativeModule().common.setAlign(node, this.value);
        }
    }
}
AlignModifier.identity = Symbol("align");
class BackdropBlurModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetBackdropBlur(node);
        }
        else {
            GetUINativeModule().common.setBackdropBlur(node, this.value);
        }
    }
}
BackdropBlurModifier.identity = Symbol("backdropBlur");
class HueRotateModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetHueRotate(node);
        }
        else {
            GetUINativeModule().common.setHueRotate(node, this.value);
        }
    }
}
HueRotateModifier.identity = Symbol("hueRotate");
class InvertModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetInvert(node);
        }
        else {
            GetUINativeModule().common.setInvert(node, this.value);
        }
    }
}
InvertModifier.identity = Symbol("invert");
class SepiaModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetSepia(node);
        }
        else {
            GetUINativeModule().common.setSepia(node, this.value);
        }
    }
}
SepiaModifier.identity = Symbol("sepia");
class SaturateModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetSaturate(node);
        }
        else {
            GetUINativeModule().common.setSaturate(node, this.value);
        }
    }
}
SaturateModifier.identity = Symbol("saturate");
class ColorBlendModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetColorBlend(node);
        }
        else {
            GetUINativeModule().common.setColorBlend(node, this.value);
        }
    }
}
ColorBlendModifier.identity = Symbol("colorBlend");
class GrayscaleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetGrayscale(node);
        }
        else {
            GetUINativeModule().common.setGrayscale(node, this.value);
        }
    }
}
GrayscaleModifier.identity = Symbol("grayscale");
class ContrastModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetContrast(node);
        }
        else {
            GetUINativeModule().common.setContrast(node, this.value);
        }
    }
}
ContrastModifier.identity = Symbol("contrast");
class BrightnessModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetBrightness(node);
        }
        else {
            GetUINativeModule().common.setBrightness(node, this.value);
        }
    }
}
BrightnessModifier.identity = Symbol("brightness");
class BlurModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetBlur(node);
        }
        else {
            GetUINativeModule().common.setBlur(node, this.value);
        }
    }
}
BlurModifier.identity = Symbol("blur");
class LinearGradientModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetLinearGradient(node);
        }
        else {
            GetUINativeModule().common.setLinearGradient(node, this.value.angle, this.value.direction, this.value.colors, this.value.repeating);
        }
    }
}
LinearGradientModifier.identity = Symbol("linearGradient");
class RadialGradientModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetRadialGradient(node);
        }
        else {
            GetUINativeModule().common.setRadialGradient(node, this.value.center, this.value.radius, this.value.colors, this.value.repeating);
        }
    }
}
RadialGradientModifier.identity = Symbol("radialGradient");
class SweepGradientModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetSweepGradient(node);
        }
        else {
            GetUINativeModule().common.setSweepGradient(node, this.value.center, this.value.start, this.value.end, this.value.rotation, this.value.colors, this.value.repeating);
        }
    }
}
SweepGradientModifier.identity = Symbol("sweepGradient");
class OverlayModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetOverlay(node);
        }
        else {
            GetUINativeModule().common.setOverlay(node, this.value.value, this.value.align, this.value.offsetX, this.value.offsetY);
        }
    }
}
OverlayModifier.identity = Symbol("overlay");
class BorderImageModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetBorderImage(node);
        }
        else {
            GetUINativeModule().common.setBorderImage(node, this.value.sliceTop, this.value.sliceRight, this.value.sliceBottom, this.value.sliceLeft, this.value.repeat, this.value.source, this.value.sourceAngle, this.value.sourceDirection, this.value.sourceColors, this.value.sourceRepeating, this.value.widthTop, this.value.widthRight, this.value.widthBottom, this.value.widthLeft, this.value.outsetTop, this.value.outsetRight, this.value.outsetBottom, this.value.outsetLeft, this.value.fill);
        }
    }
}
BorderImageModifier.identity = Symbol("borderImage");
class BorderModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetBorder(node);
        }
        else {
            GetUINativeModule().common.setBorder(node, this.value.arkWidth.left, this.value.arkWidth.right, this.value.arkWidth.top, this.value.arkWidth.bottom, this.value.arkColor.leftColor, this.value.arkColor.rightColor, this.value.arkColor.topColor, this.value.arkColor.bottomColor, this.value.arkRadius.topLeft, this.value.arkRadius.topRight, this.value.arkRadius.bottomLeft, this.value.arkRadius.bottomRight, this.value.arkStyle.top, this.value.arkStyle.right, this.value.arkStyle.bottom, this.value.arkStyle.left);
        }
    }
}
BorderModifier.identity = Symbol("border");
class ForegroundBlurStyleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetForegroundBlurStyle(node);
        }
        else {
            GetUINativeModule().common.setForegroundBlurStyle(node, this.value.blurStyle, this.value.colorMode, this.value.adaptiveColor, this.value.scale);
        }
    }
}
ForegroundBlurStyleModifier.identity = Symbol("foregroundBlurStyle");
class BackgroundImagePositionModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetBackgroundImagePosition(node);
        }
        else {
            GetUINativeModule().common.setBackgroundImagePosition(node, this.value.alignment, this.value.x, this.value.y);
        }
    }
}
BackgroundImagePositionModifier.identity = Symbol("backgroundImagePosition");
class LinearGradientBlurModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetLinearGradientBlur(node);
        }
        else {
            GetUINativeModule().common.setLinearGradientBlur(node, this.value.blurRadius, this.value.fractionStops, this.value.direction);
        }
    }
}
LinearGradientBlurModifier.identity = Symbol("linearGradientBlur");
class BackgroundImageModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetBackgroundImage(node);
        }
        else {
            GetUINativeModule().common.setBackgroundImage(node, this.value.src, this.value.repeat);
        }
    }
}
BackgroundImageModifier.identity = Symbol("backgroundImage");
class BackgroundBlurStyleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetBackgroundBlurStyle(node);
        }
        else {
            GetUINativeModule().common.setBackgroundBlurStyle(node, this.value.blurStyle, this.value.colorMode, this.value.adaptiveColor, this.value.scale);
        }
    }
}
BackgroundBlurStyleModifier.identity = Symbol("backgroundBlurStyle");
class BackgroundImageSizeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetBackgroundImageSize(node);
        }
        else {
            GetUINativeModule().common.setBackgroundImageSize(node, this.value.imageSize, this.value.width, this.value.height);
        }
    }
}
BackgroundImageSizeModifier.identity = Symbol("backgroundImageSize");
class TranslateModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetTranslate(node);
        }
        else {
            GetUINativeModule().common.setTranslate(node, this.value.x, this.value.y, this.value.z);
        }
    }
}
TranslateModifier.identity = Symbol("translate");
class ScaleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetScale(node);
        }
        else {
            GetUINativeModule().common.setScale(node, this.value.x, this.value.y, this.value.z, this.value.centerX, this.value.centerY);
        }
    }
}
ScaleModifier.identity = Symbol("scale");
class RotateModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetRotate(node);
        }
        else {
            GetUINativeModule().common.setRotate(node, this.value.x, this.value.y, this.value.z, this.value.angle, this.value.centerX, this.value.centerY, this.value.centerY, this.value.perspective);
        }
    }
}
RotateModifier.identity = Symbol("rotate");
class GeometryTransitionModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetGeometryTransition(node);
        }
        else {
            GetUINativeModule().common.setGeometryTransition(node, this.value);
        }
    }
}
GeometryTransitionModifier.identity = Symbol("geometryTransition");
class ClipModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetClip(node);
        }
        else {
            GetUINativeModule().common.setClip(node, this.value);
        }
    }
    checkObjectDiff() {
        return false;
    }
}
ClipModifier.identity = Symbol("clip");
class MaskModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetMask(node);
        }
        else {
            GetUINativeModule().common.setMask(node, this.value);
        }
    }
    checkObjectDiff() {
        return false;
    }
}
MaskModifier.identity = Symbol("mask");
class PixelStretchEffectModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetPixelStretchEffect(node);
        }
        else {
            GetUINativeModule().common.setPixelStretchEffect(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
        }
    }
}
PixelStretchEffectModifier.identity = Symbol("pixelStretchEffect");
class LightUpEffectModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetLightUpEffect(node);
        }
        else {
            GetUINativeModule().common.setLightUpEffect(node, this.value);
        }
    }
}
LightUpEffectModifier.identity = Symbol("lightUpEffect");
class SphericalEffectModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetSphericalEffect(node);
        }
        else {
            GetUINativeModule().common.setSphericalEffect(node, this.value);
        }
    }
}
SphericalEffectModifier.identity = Symbol("sphericalEffect");
class RenderGroupModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetRenderGroup(node);
        }
        else {
            GetUINativeModule().common.setRenderGroup(node, this.value);
        }
    }
}
RenderGroupModifier.identity = Symbol("renderGroup");
class RenderFitModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetRenderFit(node);
        }
        else {
            GetUINativeModule().common.setRenderFit(node, this.value);
        }
    }
}
RenderFitModifier.identity = Symbol("renderFit");
class UseEffectModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetUseEffect(node);
        }
        else {
            GetUINativeModule().common.setUseEffect(node, this.value);
        }
    }
}
UseEffectModifier.identity = Symbol("useEffect");
class ForegroundColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetForegroundColor(node);
        }
        else {
            GetUINativeModule().common.setForegroundColor(node, this.value.color, this.value.strategy);
        }
    }
}
ForegroundColorModifier.identity = Symbol("foregroundColor");
class MotionPathModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetMotionPath(node);
        }
        else {
            GetUINativeModule().common.setMotionPath(node, this.value.path, this.value.from, this.value.to, this.value.rotatable);
        }
    }
}
MotionPathModifier.identity = Symbol("motionPath");
class GroupDefaultFocusModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetGroupDefaultFocus(node);
        }
        else {
            GetUINativeModule().common.setGroupDefaultFocus(node, this.value);
        }
    }
}
GroupDefaultFocusModifier.identity = Symbol("groupDefaultFocus");
class FocusOnTouchModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetFocusOnTouch(node);
        }
        else {
            GetUINativeModule().common.setFocusOnTouch(node, this.value);
        }
    }
}
FocusOnTouchModifier.identity = Symbol("focusOnTouch");
class OffsetModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetOffset(node);
        }
        else {
            GetUINativeModule().common.setOffset(node, this.value.x, this.value.y);
        }
    }
}
OffsetModifier.identity = Symbol('offset');
class MarkAnchorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetMarkAnchor(node);
        }
        else {
            GetUINativeModule().common.setMarkAnchor(node, this.value.x, this.value.y);
        }
    }
}
MarkAnchorModifier.identity = Symbol('markAnchor');
class DefaultFocusModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetDefaultFocus(node);
        }
        else {
            GetUINativeModule().common.setDefaultFocus(node, this.value);
        }
    }
}
DefaultFocusModifier.identity = Symbol("defaultFocus");
class FocusableModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetFocusable(node);
        }
        else {
            GetUINativeModule().common.setFocusable(node, this.value);
        }
    }
}
FocusableModifier.identity = Symbol("focusable");
class TouchableModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetTouchable(node);
        }
        else {
            GetUINativeModule().common.setTouchable(node, this.value);
        }
    }
}
TouchableModifier.identity = Symbol("touchable");
class MarginModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetMargin(node);
        }
        else {
            GetUINativeModule().common.setMargin(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
        }
    }
}
MarginModifier.identity = Symbol('margin');
class PaddingModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetPadding(node);
        }
        else {
            GetUINativeModule().common.setPadding(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
        }
    }
}
PaddingModifier.identity = Symbol('padding');
class VisibilityModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetVisibility(node);
        }
        else {
            GetUINativeModule().common.setVisibility(node, this.value);
        }
    }
}
VisibilityModifier.identity = Symbol('visibility');
class AccessibilityTextModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetAccessibilityText(node);
        }
        else {
            GetUINativeModule().common.setAccessibilityText(node, this.value);
        }
    }
}
AccessibilityTextModifier.identity = Symbol("accessibilityText");
class AllowDropModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetAllowDrop(node);
        }
        else {
            GetUINativeModule().common.setAllowDrop(node, this.value.allowDropArray);
        }
    }
}
AllowDropModifier.identity = Symbol("allowDrop");
class AccessibilityLevelModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetAccessibilityLevel(node);
        }
        else {
            GetUINativeModule().common.setAccessibilityLevel(node, this.value);
        }
    }
}
AccessibilityLevelModifier.identity = Symbol("accessibilityLevel");
class AccessibilityDescriptionModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetAccessibilityDescription(node);
        }
        else {
            GetUINativeModule().common.setAccessibilityDescription(node, this.value);
        }
    }
}
AccessibilityDescriptionModifier.identity = Symbol("accessibilityDescription");
class DirectionModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetDirection(node);
        }
        else {
            GetUINativeModule().common.setDirection(node, this.value);
        }
    }
}
DirectionModifier.identity = Symbol('direction');
class AlignRulesModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetAlignRules(node);
        }
        else {
            GetUINativeModule().common.setAlignRules(node, this.value.left, this.value.middle, this.value.right, this.value.top, this.value.center, this.value.bottom);
        }
    }
}
AlignRulesModifier.identity = Symbol('alignRules');
class ExpandSafeAreaModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetExpandSafeArea(node);
        }
        else {
            GetUINativeModule().common.setExpandSafeArea(node, this.value.type, this.value.edges);
        }
    }
}
ExpandSafeAreaModifier.identity = Symbol('expandSafeArea');
class GridSpanModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetGridSpan(node);
        }
        else {
            GetUINativeModule().common.setGridSpan(node, this.value);
        }
    }
}
GridSpanModifier.identity = Symbol('gridSpan');
class GridOffsetModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetGridOffset(node);
        }
        else {
            GetUINativeModule().common.setGridOffset(node, this.value);
        }
    }
}
GridOffsetModifier.identity = Symbol('gridOffset');
class AlignSelfModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetAlignSelf(node);
        }
        else {
            GetUINativeModule().common.setAlignSelf(node, this.value);
        }
    }
}
AlignSelfModifier.identity = Symbol('alignSelf');
class SizeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetSize(node);
        }
        else {
            GetUINativeModule().common.setSize(node, this.value.width, this.value.height);
        }
    }
}
SizeModifier.identity = Symbol('size');
class DisplayPriorityModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetDisplayPriority(node);
        }
        else {
            GetUINativeModule().common.setDisplayPriority(node, this.value);
        }
    }
}
DisplayPriorityModifier.identity = Symbol('displayPriority');
class IDModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetID(node);
        }
        else {
            GetUINativeModule().common.setID(node, this.value);
        }
    }
}
IDModifier.identity = Symbol("id");
class KeyModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetKey(node);
        }
        else {
            GetUINativeModule().common.setKey(node, this.value);
        }
    }
}
KeyModifier.identity = Symbol("key");
class RestoreIdModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetRestoreId(node);
        }
        else {
            GetUINativeModule().common.setRestoreId(node, this.value);
        }
    }
}
RestoreIdModifier.identity = Symbol("restoreId");
class TabIndexModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetTabIndex(node);
        }
        else {
            GetUINativeModule().common.setTabIndex(node, this.value);
        }
    }
}
TabIndexModifier.identity = Symbol("tabIndex");
class ObscuredModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetObscured(node);
        }
        else {
            GetUINativeModule().common.setObscured(node, this.value.reasons);
        }
    }
}
ObscuredModifier.identity = Symbol("obscured");
class MouseResponseRegionModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetMouseResponseRegion(node);
        }
        else {
            GetUINativeModule().common.setMouseResponseRegion(node, this.value.responseRegion);
        }
    }
}
MouseResponseRegionModifier.identity = Symbol("mouseResponseRegion");
class ResponseRegionModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetResponseRegion(node);
        }
        else {
            GetUINativeModule().common.setResponseRegion(node, this.value.responseRegion);
        }
    }
}
ResponseRegionModifier.identity = Symbol("responseRegion");
class FlexGrowModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetFlexGrow(node);
        }
        else {
            GetUINativeModule().common.setFlexGrow(node, this.value);
        }
    }
}
FlexGrowModifier.identity = Symbol('flexGrow');
class FlexShrinkModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetFlexShrink(node);
        }
        else {
            GetUINativeModule().common.setFlexShrink(node, this.value);
        }
    }
}
FlexShrinkModifier.identity = Symbol('flexShrink');
class AspectRatioModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetAspectRatio(node);
        }
        else {
            GetUINativeModule().common.setAspectRatio(node, this.value);
        }
    }
}
AspectRatioModifier.identity = Symbol('aspectRatio');
class ConstraintSizeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetConstraintSize(node);
        }
        else {
            GetUINativeModule().common.setConstraintSize(node, this.value.minWidth, this.value.maxWidth, this.value.minHeight, this.value.maxHeight);
        }
    }
}
ConstraintSizeModifier.identity = Symbol('constraintSize');
class FlexBasisModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetFlexBasis(node);
        }
        else {
            GetUINativeModule().common.setFlexBasis(node, this.value);
        }
    }
}
FlexBasisModifier.identity = Symbol('flexBasis');
class LayoutWeightModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetLayoutWeight(node);
        }
        else {
            GetUINativeModule().common.setLayoutWeight(node, this.value);
        }
    }
}
LayoutWeightModifier.identity = Symbol('layoutWeight');
class EnabledModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetEnabled(node);
        }
        else {
            GetUINativeModule().common.setEnabled(node, this.value);
        }
    }
}
EnabledModifier.identity = Symbol("enabled");
class DraggableModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetDraggable(node);
        }
        else {
            GetUINativeModule().common.setDraggable(node, this.value);
        }
    }
}
DraggableModifier.identity = Symbol("draggable");
class AccessibilityGroupModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetAccessibilityGroup(node);
        }
        else {
            GetUINativeModule().common.setAccessibilityGroup(node, this.value);
        }
    }
}
AccessibilityGroupModifier.identity = Symbol("accessibilityGroup");
class HoverEffectModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetHoverEffect(node);
        }
        else {
            GetUINativeModule().common.setHoverEffect(node, this.value);
        }
    }
}
HoverEffectModifier.identity = Symbol("hoverEffect");
class ClickEffectModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetClickEffect(node);
        }
        else {
            GetUINativeModule().common.setClickEffect(node, this.value.level, this.value.scale);
        }
    }
}
ClickEffectModifier.identity = Symbol("clickEffect");
class KeyBoardShortCutModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetKeyBoardShortCut(node);
        }
        else {
            GetUINativeModule().common.setKeyBoardShortCut(node, this.value.value, this.value.keys);
        }
    }
}
KeyBoardShortCutModifier.identity = Symbol("keyboardShortcut");
class TransitionModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetTransition(node);
        }
        else {
            GetUINativeModule().common.setTransition(node, this.value);
        }
    }
    checkObjectDiff() {
        return false;
    }
}
TransitionModifier.identity = Symbol("transition");
class SharedTransitionModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetSharedTransition(node);
        }
        else {
            GetUINativeModule().common.setSharedTransition(node, this.value.id, this.value.options);
        }
    }
    checkObjectDiff() {
        return false;
    }
}
SharedTransitionModifier.identity = Symbol("sharedTransition");
const JSCallbackInfoType = { STRING: 0, NUMBER: 1, OBJECT: 2, BOOLEAN: 3, FUNCTION: 4 };
const isString = (val) => typeof val === 'string';
const isNumber = (val) => typeof val === 'number';
const isBigint = (val) => typeof val === 'bigint';
const isBoolean = (val) => typeof val === 'boolean';
const isSymbol = (val) => typeof val === 'symbol';
const isUndefined = (val) => typeof val === 'undefined';
const isObject = (val) => typeof val === 'object';
const isFunction = (val) => typeof val === 'function';
const isLengthType = (val) => typeof val === 'string' || typeof val === 'number';
const lessThenFunction = (val1, val2) => (val1 - val2) < 0.001;
function CheckJSCallbackInfo(value, checklist) {
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
function modifier(modifiers, modifierClass, value) {
    const identity = modifierClass["identity"];
    const item = modifiers.get(identity);
    if (item) {
        item.stageValue = value;
    }
    else {
        modifiers.set(identity, new modifierClass(value));
    }
}
function modifierWithKey(modifiers, identity, modifierClass, value) {
    const item = modifiers.get(identity);
    if (item) {
        item.stageValue = value;
    }
    else {
        modifiers.set(identity, new modifierClass(value));
    }
}
class ArkComponent {
    constructor(nativePtr) {
        this._modifiers = new Map();
        this._modifiersWithKeys = new Map();
        this.nativePtr = nativePtr;
    }
    applyModifierPatch() {
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
    onGestureJudgeBegin(callback) {
        throw new Error("Method not implemented.");
    }
    width(value) {
        modifierWithKey(this._modifiersWithKeys, WidthModifier.identity, WidthModifier, value);
        return this;
    }
    height(value) {
        modifierWithKey(this._modifiersWithKeys, HeightModifier.identity, HeightModifier, value);
        return this;
    }
    expandSafeArea(types, edges) {
        let opts = new ArkSafeAreaExpandOpts();
        opts.type = SAFE_AREA_TYPE_ALL;
        opts.edges = SAFE_AREA_EDGE_ALL;
        if (types && types.length > 0) {
            let safeAreaType = '';
            for (let param of types) {
                if (!isNumber(param) || param >= SAFE_AREA_TYPE_LIMIT) {
                    safeAreaType = SAFE_AREA_TYPE_ALL;
                    break;
                }
                if (safeAreaType) {
                    safeAreaType += '|';
                }
                else {
                    safeAreaType += param.toString();
                }
            }
            opts.type = safeAreaType;
        }
        if (edges && edges.length > 0) {
            let safeAreaEdge = '';
            for (let param of edges) {
                if (!isNumber(param) || param >= SAFE_AREA_EDGE_LIMIT) {
                    safeAreaEdge = SAFE_AREA_EDGE_ALL;
                    break;
                }
                if (safeAreaEdge) {
                    safeAreaEdge += '|';
                }
                else {
                    safeAreaEdge += param.toString();
                }
            }
            opts.edges = safeAreaEdge;
        }
        if (opts.type === SAFE_AREA_TYPE_ALL && opts.edges === SAFE_AREA_EDGE_ALL) {
            // modifier(this._modifiers, ExpandSafeAreaModifier, undefined);
        }
        else {
            modifier(this._modifiers, ExpandSafeAreaModifier, opts);
        }
        return this;
    }
    responseRegion(value) {
        let arkResponseRegion = new ArkResponseRegion();
        if (arkResponseRegion.parseRegionValue(value)) {
            modifier(this._modifiers, ResponseRegionModifier, arkResponseRegion);
        }
        else {
            modifier(this._modifiers, ResponseRegionModifier, undefined);
        }
        return this;
    }
    mouseResponseRegion(value) {
        let arkMouseResponseRegion = new ArkResponseRegion();
        if (arkMouseResponseRegion.parseRegionValue(value)) {
            modifier(this._modifiers, MouseResponseRegionModifier, arkMouseResponseRegion);
        }
        else {
            modifier(this._modifiers, MouseResponseRegionModifier, undefined);
        }
        return this;
    }
    size(value) {
        let arkValue = new ArkSize();
        if (!value || (!isLengthType(value.width) && !isLengthType(value.height))) {
            modifier(this._modifiers, SizeModifier, undefined);
        }
        if (value.width && isLengthType(value.width)) {
            arkValue.width = value.width;
        }
        if (value.height && isLengthType(value.height)) {
            arkValue.height = value.height;
        }
        modifier(this._modifiers, SizeModifier, arkValue);
        return this;
    }
    constraintSize(value) {
        let arkValue = new ArkConstraintSizeOptions();
        if (!value ||
            (!isLengthType(value.minWidth) && !isLengthType(value.maxWidth) &&
                !isLengthType(value.minHeight) && !isLengthType(value.maxHeight))) {
            modifier(this._modifiers, ConstraintSizeModifier, undefined);
            return this;
        }
        if (value.minWidth && isLengthType(value.minWidth)) {
            arkValue.minWidth = value === null || value === void 0 ? void 0 : value.minWidth;
        }
        if (value.maxWidth && isLengthType(value.maxWidth)) {
            arkValue.maxWidth = value === null || value === void 0 ? void 0 : value.maxWidth;
        }
        if (value.minHeight && isLengthType(value.minHeight)) {
            arkValue.minHeight = value === null || value === void 0 ? void 0 : value.minHeight;
        }
        if (value.maxHeight && isLengthType(value.maxHeight)) {
            arkValue.maxHeight = value === null || value === void 0 ? void 0 : value.maxHeight;
        }
        modifier(this._modifiers, ConstraintSizeModifier, arkValue);
        return this;
    }
    touchable(value) {
        if (typeof value === 'boolean') {
            modifier(this._modifiers, TouchableModifier, value);
        }
        else {
            modifier(this._modifiers, TouchableModifier, undefined);
        }
        return this;
    }
    hitTestBehavior(value) {
        if (value) {
            modifier(this._modifiers, HitTestBehaviorModifier, value);
        }
        else {
            modifier(this._modifiers, HitTestBehaviorModifier, undefined);
        }
        return this;
    }
    layoutWeight(value) {
        if (isNumber(value)) {
            modifier(this._modifiers, LayoutWeightModifier, value);
        }
        else if (isString(value) && !isNaN(Number(value))) {
            modifier(this._modifiers, LayoutWeightModifier, parseInt(value.toString()));
        }
        else {
            modifier(this._modifiers, LayoutWeightModifier, 0);
        }
        return this;
    }
    padding(value) {
        let arkValue = new ArkPadding();
        if (value !== null && value !== undefined) {
            if (isLengthType(value)) {
                arkValue.top = value;
                arkValue.right = value;
                arkValue.bottom = value;
                arkValue.left = value;
            }
            else {
                if (value.top && isLengthType(value.top)) {
                    arkValue.top = value.top;
                }
                if (value.right && isLengthType(value.right)) {
                    arkValue.right = value.right;
                }
                if (value.bottom && isLengthType(value.bottom)) {
                    arkValue.bottom = value.bottom;
                }
                if (value.left && isLengthType(value.left)) {
                    arkValue.left = value.left;
                }
            }
            modifier(this._modifiers, PaddingModifier, arkValue);
        }
        else {
            modifier(this._modifiers, PaddingModifier, undefined);
        }
        return this;
    }
    margin(value) {
        let arkValue = new ArkPadding();
        if (value !== null && value !== undefined) {
            if (!isNaN(Number(value)) && isLengthType(value)) {
                arkValue.top = value;
                arkValue.right = value;
                arkValue.bottom = value;
                arkValue.left = value;
            }
            else {
                if (value.top && isLengthType(value.top)) {
                    arkValue.top = value.top;
                }
                if (value.right && isLengthType(value.right)) {
                    arkValue.right = value.right;
                }
                if (value.bottom && isLengthType(value.bottom)) {
                    arkValue.bottom = value.bottom;
                }
                if (value.left && isLengthType(value.left)) {
                    arkValue.left = value.left;
                }
            }
            modifier(this._modifiers, MarginModifier, arkValue);
        }
        else {
            modifier(this._modifiers, MarginModifier, undefined);
        }
        return this;
    }
    background(builder, options) {
        throw new Error("Method not implemented.");
    }
    backgroundColor(value) {
        modifierWithKey(this._modifiersWithKeys, BackgroundColorModifier.identity, BackgroundColorModifier, value);
        return this;
    }
    backgroundImage(src, repeat) {
        let arkBackgroundImage = new ArkBackgroundImage();
        if (isString(src)) {
            arkBackgroundImage.src = src;
        }
        if (isNumber(repeat)) {
            arkBackgroundImage.repeat = repeat;
        }
        modifier(this._modifiers, BackgroundImageModifier, arkBackgroundImage);
        return this;
    }
    backgroundImageSize(value) {
        var _a, _b, _c, _d, _e, _f;
        if (isResource(value) || isUndefined(value)) {
            modifier(this._modifiers, BackgroundImageSizeModifier, undefined);
            return this;
        }
        let arkBackgroundImageSize = new ArkBackgroundImageSize();
        if (isNumber(value)) {
            arkBackgroundImageSize.imageSize = value;
        }
        else {
            if (isNumber((_a = value) === null || _a === void 0 ? void 0 : _a.width) || isString((_b = value) === null || _b === void 0 ? void 0 : _b.width)) {
                arkBackgroundImageSize.width = (_c = value) === null || _c === void 0 ? void 0 : _c.width;
            }
            if (isNumber((_d = value) === null || _d === void 0 ? void 0 : _d.height) || isString((_e = value) === null || _e === void 0 ? void 0 : _e.height)) {
                arkBackgroundImageSize.height = (_f = value) === null || _f === void 0 ? void 0 : _f.height;
            }
        }
        modifier(this._modifiers, BackgroundImageSizeModifier, arkBackgroundImageSize);
        return this;
    }
    backgroundImagePosition(value) {
        var _a, _b, _c, _d, _e, _f;
        if (isResource(value) || isUndefined(value)) {
            modifier(this._modifiers, BackgroundImagePositionModifier, undefined);
            return this;
        }
        let arkBackgroundImagePosition = new ArkBackgroundImagePosition();
        if (isNumber(value)) {
            arkBackgroundImagePosition.alignment = value;
        }
        else {
            if (isNumber((_a = value) === null || _a === void 0 ? void 0 : _a.x) || isString((_b = value) === null || _b === void 0 ? void 0 : _b.x)) {
                arkBackgroundImagePosition.x = (_c = value) === null || _c === void 0 ? void 0 : _c.x;
            }
            if (isNumber((_d = value) === null || _d === void 0 ? void 0 : _d.y) || isString((_e = value) === null || _e === void 0 ? void 0 : _e.y)) {
                arkBackgroundImagePosition.y = (_f = value) === null || _f === void 0 ? void 0 : _f.y;
            }
        }
        modifier(this._modifiers, BackgroundImagePositionModifier, arkBackgroundImagePosition);
        return this;
    }
    backgroundBlurStyle(value, options) {
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
    foregroundBlurStyle(value, options) {
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
    opacity(value) {
        modifierWithKey(this._modifiersWithKeys, OpacityModifier.identity, OpacityModifier, value);
        return this;
    }
    border(value) {
        var _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p, _q, _r, _s, _t, _u, _v, _w, _x, _y, _z, _0, _1, _2, _3;
        let arkBorder = new ArkBorder();
        if (!isResource(value === null || value === void 0 ? void 0 : value.width) && !isUndefined(value === null || value === void 0 ? void 0 : value.width) && (value === null || value === void 0 ? void 0 : value.width) !== null) {
            if (isNumber(value.width)) {
                arkBorder.arkWidth.left = Number(value.width);
                arkBorder.arkWidth.right = Number(value.width);
                arkBorder.arkWidth.top = Number(value.width);
                arkBorder.arkWidth.bottom = Number(value.width);
            }
            else if (isString(value.width)) {
                arkBorder.arkWidth.left = String(value.width);
                arkBorder.arkWidth.right = String(value.width);
                arkBorder.arkWidth.top = String(value.width);
                arkBorder.arkWidth.bottom = String(value.width);
            }
            else {
                if (isNumber((_a = value.width) === null || _a === void 0 ? void 0 : _a.left) || isString((_b = value.width) === null || _b === void 0 ? void 0 : _b.left)) {
                    arkBorder.arkWidth.left = value.width.left;
                }
                if (isNumber((_c = value.width) === null || _c === void 0 ? void 0 : _c.right) || isString((_d = value.width) === null || _d === void 0 ? void 0 : _d.right)) {
                    arkBorder.arkWidth.right = value.width.right;
                }
                if (isNumber((_e = value.width) === null || _e === void 0 ? void 0 : _e.top) || isString((_f = value.width) === null || _f === void 0 ? void 0 : _f.top)) {
                    arkBorder.arkWidth.top = value.width.top;
                }
                if (isNumber((_g = value.width) === null || _g === void 0 ? void 0 : _g.bottom) || isString((_h = value.width) === null || _h === void 0 ? void 0 : _h.bottom)) {
                    arkBorder.arkWidth.bottom = value.width.bottom;
                }
            }
        }
        if (!isResource(value === null || value === void 0 ? void 0 : value.color) && !isUndefined(value === null || value === void 0 ? void 0 : value.color) && (value === null || value === void 0 ? void 0 : value.color) !== null) {
            let arkColor = new ArkColor();
            if (isNumber(value.color)) {
                arkColor.parseColorValue(Number(value.color));
                arkBorder.arkColor.leftColor = arkColor.color;
                arkBorder.arkColor.rightColor = arkColor.color;
                arkBorder.arkColor.topColor = arkColor.color;
                arkBorder.arkColor.bottomColor = arkColor.color;
            }
            else if (isString(value === null || value === void 0 ? void 0 : value.color)) {
                arkColor.parseColorValue(String(value.color));
                arkBorder.arkColor.leftColor = arkColor.color;
                arkBorder.arkColor.rightColor = arkColor.color;
                arkBorder.arkColor.topColor = arkColor.color;
                arkBorder.arkColor.bottomColor = arkColor.color;
            }
            else {
                if (isNumber((_j = value.color) === null || _j === void 0 ? void 0 : _j.left) || isString((_k = value.color) === null || _k === void 0 ? void 0 : _k.left)) {
                    arkColor.parseColorValue(value.color.left);
                    arkBorder.arkColor.leftColor = arkColor === null || arkColor === void 0 ? void 0 : arkColor.color;
                }
                if (isNumber((_l = value.color) === null || _l === void 0 ? void 0 : _l.right) || isString((_m = value.color) === null || _m === void 0 ? void 0 : _m.right)) {
                    arkColor.parseColorValue(value.color.right);
                    arkBorder.arkColor.rightColor = arkColor === null || arkColor === void 0 ? void 0 : arkColor.color;
                }
                if (isNumber((_o = value.color) === null || _o === void 0 ? void 0 : _o.top) || isString((_p = value.color) === null || _p === void 0 ? void 0 : _p.top)) {
                    arkColor.parseColorValue(value.color.top);
                    arkBorder.arkColor.topColor = arkColor === null || arkColor === void 0 ? void 0 : arkColor.color;
                }
                if (isNumber((_q = value.color) === null || _q === void 0 ? void 0 : _q.bottom) || isString((_r = value.color) === null || _r === void 0 ? void 0 : _r.bottom)) {
                    arkColor.parseColorValue(value.color.bottom);
                    arkBorder.arkColor.bottomColor = arkColor === null || arkColor === void 0 ? void 0 : arkColor.color;
                }
            }
        }
        if (!isResource(value === null || value === void 0 ? void 0 : value.radius) && !isUndefined(value === null || value === void 0 ? void 0 : value.radius) && (value === null || value === void 0 ? void 0 : value.radius) !== null) {
            if (isNumber(value.radius)) {
                arkBorder.arkRadius.topLeft = Number(value.radius);
                arkBorder.arkRadius.topRight = Number(value.radius);
                arkBorder.arkRadius.bottomLeft = Number(value.radius);
                arkBorder.arkRadius.bottomRight = Number(value.radius);
            }
            else if (isString(value.radius)) {
                arkBorder.arkRadius.topLeft = String(value.radius);
                arkBorder.arkRadius.topRight = String(value.radius);
                arkBorder.arkRadius.bottomLeft = String(value.radius);
                arkBorder.arkRadius.bottomRight = String(value.radius);
            }
            else {
                if (isNumber((_s = value.radius) === null || _s === void 0 ? void 0 : _s.topLeft) || isString((_t = value.radius) === null || _t === void 0 ? void 0 : _t.topLeft)) {
                    arkBorder.arkRadius.topLeft = (_u = value.radius) === null || _u === void 0 ? void 0 : _u.topLeft;
                }
                if (isNumber((_v = value.radius) === null || _v === void 0 ? void 0 : _v.topRight) || isString((_w = value.radius) === null || _w === void 0 ? void 0 : _w.topRight)) {
                    arkBorder.arkRadius.topRight = (_x = value.radius) === null || _x === void 0 ? void 0 : _x.topRight;
                }
                if (isNumber((_y = value.radius) === null || _y === void 0 ? void 0 : _y.bottomLeft) || isString((_z = value.radius) === null || _z === void 0 ? void 0 : _z.bottomLeft)) {
                    arkBorder.arkRadius.bottomLeft = (_0 = value.radius) === null || _0 === void 0 ? void 0 : _0.bottomLeft;
                }
                if (isNumber((_1 = value.radius) === null || _1 === void 0 ? void 0 : _1.bottomRight) || isString((_2 = value.radius) === null || _2 === void 0 ? void 0 : _2.bottomRight)) {
                    arkBorder.arkRadius.bottomRight = (_3 = value.radius) === null || _3 === void 0 ? void 0 : _3.bottomRight;
                }
            }
        }
        if (!isUndefined(value === null || value === void 0 ? void 0 : value.style) && (value === null || value === void 0 ? void 0 : value.style) !== null) {
            let arkBorderStyle = new ArkBorderStyle();
            if (arkBorderStyle.parseBorderStyle(value.style)) {
                if (!isUndefined(arkBorderStyle.style)) {
                    arkBorder.arkStyle.top = arkBorderStyle.style;
                    arkBorder.arkStyle.left = arkBorderStyle.style;
                    arkBorder.arkStyle.bottom = arkBorderStyle.style;
                    arkBorder.arkStyle.right = arkBorderStyle.style;
                }
                else {
                    arkBorder.arkStyle.top = arkBorderStyle.top;
                    arkBorder.arkStyle.left = arkBorderStyle.left;
                    arkBorder.arkStyle.bottom = arkBorderStyle.bottom;
                    arkBorder.arkStyle.right = arkBorderStyle.right;
                }
            }
        }
        modifier(this._modifiers, BorderModifier, arkBorder);
        return this;
    }
    borderStyle(value) {
        let arkBorderStyle = new ArkBorderStyle();
        if (arkBorderStyle.parseBorderStyle(value)) {
            modifier(this._modifiers, BorderStyleModifier, arkBorderStyle);
        }
        else {
            modifier(this._modifiers, BorderStyleModifier, undefined);
        }
        return this;
    }
    borderWidth(value) {
        modifierWithKey(this._modifiersWithKeys, BorderWidthModifier.identity, BorderWidthModifier, value);
        return this;
    }
    borderColor(value) {
        modifierWithKey(this._modifiersWithKeys, BorderColorModifier.identity, BorderColorModifier, value);
        return this;
    }
    borderRadius(value) {
        modifierWithKey(this._modifiersWithKeys, BorderRadiusModifier.identity, BorderRadiusModifier, value);
        return this;
    }
    borderImage(value) {
        let arkBorderImage = new ArkBorderImage();
        if (!arkBorderImage.parseOption(value)) {
            modifier(this._modifiers, BorderImageModifier, undefined);
            return this;
        }
        modifier(this._modifiers, BorderImageModifier, arkBorderImage);
        return this;
    }
    foregroundColor(value) {
        let arkForegroundColor = new ArkForegroundColor;
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
        }
        else {
            modifier(this._modifiers, ForegroundColorModifier, undefined);
        }
        return this;
    }
    onClick(event) {
        throw new Error("Method not implemented.");
    }
    onHover(event) {
        throw new Error("Method not implemented.");
    }
    hoverEffect(value) {
        modifier(this._modifiers, HoverEffectModifier, value);
        return this;
    }
    onMouse(event) {
        throw new Error("Method not implemented.");
    }
    onTouch(event) {
        throw new Error("Method not implemented.");
    }
    onKeyEvent(event) {
        throw new Error("Method not implemented.");
    }
    focusable(value) {
        if (typeof value === 'boolean') {
            modifier(this._modifiers, FocusableModifier, value);
        }
        else {
            modifier(this._modifiers, FocusableModifier, undefined);
        }
        return this;
    }
    onFocus(event) {
        throw new Error("Method not implemented.");
    }
    onBlur(event) {
        throw new Error("Method not implemented.");
    }
    tabIndex(index) {
        if (typeof index !== "number") {
            modifier(this._modifiers, TabIndexModifier, undefined);
        }
        else {
            modifier(this._modifiers, TabIndexModifier, index);
        }
        return this;
    }
    defaultFocus(value) {
        if (typeof value === 'boolean') {
            modifier(this._modifiers, DefaultFocusModifier, value);
        }
        else {
            modifier(this._modifiers, DefaultFocusModifier, undefined);
        }
        return this;
    }
    groupDefaultFocus(value) {
        if (typeof value === "boolean") {
            modifier(this._modifiers, GroupDefaultFocusModifier, value);
        }
        else {
            modifier(this._modifiers, GroupDefaultFocusModifier, undefined);
        }
        return this;
    }
    focusOnTouch(value) {
        if (typeof value === "boolean") {
            modifier(this._modifiers, FocusOnTouchModifier, value);
        }
        else {
            modifier(this._modifiers, FocusOnTouchModifier, undefined);
        }
        return this;
    }
    animation(value) {
        throw new Error("Method not implemented.");
    }
    transition(value) {
        modifierWithKey(this._modifiersWithKeys, TransitionModifier.identity, TransitionModifier, value);
        return this;
    }
    gesture(gesture, mask) {
        throw new Error("Method not implemented.");
    }
    priorityGesture(gesture, mask) {
        throw new Error("Method not implemented.");
    }
    parallelGesture(gesture, mask) {
        throw new Error("Method not implemented.");
    }
    blur(value) {
        if (!isNumber(value)) {
            modifier(this._modifiers, BlurModifier, undefined);
        }
        else {
            modifier(this._modifiers, BlurModifier, value);
        }
        return this;
    }
    linearGradientBlur(value, options) {
        let arkLinearGradientBlur = new ArkLinearGradientBlur();
        arkLinearGradientBlur.blurRadius = value;
        arkLinearGradientBlur.fractionStops = options.fractionStops;
        arkLinearGradientBlur.direction = options.direction;
        modifier(this._modifiers, LinearGradientBlurModifier, arkLinearGradientBlur);
        return this;
    }
    brightness(value) {
        if (!isNumber(value)) {
            modifier(this._modifiers, BrightnessModifier, undefined);
        }
        else {
            modifier(this._modifiers, BrightnessModifier, value);
        }
        return this;
    }
    contrast(value) {
        if (!isNumber(value)) {
            modifier(this._modifiers, ContrastModifier, undefined);
        }
        else {
            modifier(this._modifiers, ContrastModifier, value);
        }
        return this;
    }
    grayscale(value) {
        if (!isNumber(value)) {
            modifier(this._modifiers, GrayscaleModifier, undefined);
        }
        else {
            modifier(this._modifiers, GrayscaleModifier, value);
        }
        return this;
    }
    colorBlend(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, ColorBlendModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, ColorBlendModifier, undefined);
        }
        return this;
    }
    saturate(value) {
        if (!isNumber(value)) {
            modifier(this._modifiers, SaturateModifier, undefined);
        }
        else {
            modifier(this._modifiers, SaturateModifier, value);
        }
        return this;
    }
    sepia(value) {
        if (!isNumber(value)) {
            modifier(this._modifiers, SepiaModifier, undefined);
        }
        else {
            modifier(this._modifiers, SepiaModifier, value);
        }
        return this;
    }
    invert(value) {
        if (!isNumber(value)) {
            modifier(this._modifiers, InvertModifier, undefined);
        }
        else {
            modifier(this._modifiers, InvertModifier, value);
        }
        return this;
    }
    hueRotate(value) {
        if (!isNumber(value) && !isString(value)) {
            modifier(this._modifiers, HueRotateModifier, undefined);
        }
        else {
            modifier(this._modifiers, HueRotateModifier, value);
        }
        return this;
    }
    useEffect(value) {
        modifier(this._modifiers, UseEffectModifier, value);
        return this;
    }
    backdropBlur(value) {
        if (!isNumber(value)) {
            modifier(this._modifiers, BackdropBlurModifier, undefined);
        }
        else {
            modifier(this._modifiers, BackdropBlurModifier, value);
        }
        return this;
    }
    renderGroup(value) {
        modifier(this._modifiers, RenderGroupModifier, value);
        return this;
    }
    translate(value) {
        let arkTranslate = new ArkTranslate();
        if (isNumber(value === null || value === void 0 ? void 0 : value.x) || isString(value === null || value === void 0 ? void 0 : value.x)) {
            arkTranslate.x = value.x;
        }
        if (isNumber(value === null || value === void 0 ? void 0 : value.y) || isString(value === null || value === void 0 ? void 0 : value.y)) {
            arkTranslate.y = value.y;
        }
        if (isNumber(value === null || value === void 0 ? void 0 : value.z) || isString(value === null || value === void 0 ? void 0 : value.z)) {
            arkTranslate.z = value.z;
        }
        modifier(this._modifiers, TranslateModifier, arkTranslate);
        return this;
    }
    scale(value) {
        let arkScale = new ArkScale();
        if (isNumber(value === null || value === void 0 ? void 0 : value.x)) {
            arkScale.x = value === null || value === void 0 ? void 0 : value.x;
        }
        if (isNumber(value === null || value === void 0 ? void 0 : value.y)) {
            arkScale.y = value === null || value === void 0 ? void 0 : value.y;
        }
        if (isNumber(value === null || value === void 0 ? void 0 : value.z)) {
            arkScale.z = value === null || value === void 0 ? void 0 : value.z;
        }
        if (isNumber(value === null || value === void 0 ? void 0 : value.centerX) || isString(value === null || value === void 0 ? void 0 : value.centerX)) {
            arkScale.centerX = value === null || value === void 0 ? void 0 : value.centerX;
        }
        if (isNumber(value === null || value === void 0 ? void 0 : value.centerY) || isString(value === null || value === void 0 ? void 0 : value.centerY)) {
            arkScale.centerY = value === null || value === void 0 ? void 0 : value.centerY;
        }
        modifier(this._modifiers, ScaleModifier, arkScale);
        return this;
    }
    gridSpan(value) {
        if (value === null || value === undefined) {
            modifier(this._modifiers, GridSpanModifier, undefined);
        }
        else {
            modifier(this._modifiers, GridSpanModifier, value);
        }
        return this;
    }
    gridOffset(value) {
        if (value === null || value === undefined) {
            modifier(this._modifiers, GridOffsetModifier, undefined);
        }
        else {
            modifier(this._modifiers, GridOffsetModifier, value);
        }
        return this;
    }
    rotate(value) {
        let arkRotate = new ArkRotate();
        if (isNumber(value === null || value === void 0 ? void 0 : value.x)) {
            arkRotate.x = value === null || value === void 0 ? void 0 : value.x;
        }
        if (isNumber(value === null || value === void 0 ? void 0 : value.y)) {
            arkRotate.y = value === null || value === void 0 ? void 0 : value.y;
        }
        if (isNumber(value === null || value === void 0 ? void 0 : value.z)) {
            arkRotate.z = value === null || value === void 0 ? void 0 : value.z;
        }
        if (isNumber(value === null || value === void 0 ? void 0 : value.angle) || isString(value === null || value === void 0 ? void 0 : value.angle)) {
            arkRotate.angle = value === null || value === void 0 ? void 0 : value.angle;
        }
        if (isNumber(value === null || value === void 0 ? void 0 : value.centerX) || isString(value === null || value === void 0 ? void 0 : value.centerX)) {
            arkRotate.centerX = value === null || value === void 0 ? void 0 : value.centerX;
        }
        if (isNumber(value === null || value === void 0 ? void 0 : value.centerY) || isString(value === null || value === void 0 ? void 0 : value.centerY)) {
            arkRotate.centerY = value === null || value === void 0 ? void 0 : value.centerY;
        }
        if (isNumber(value === null || value === void 0 ? void 0 : value.centerZ) || isString(value === null || value === void 0 ? void 0 : value.centerZ)) {
            arkRotate.centerZ = value === null || value === void 0 ? void 0 : value.centerZ;
        }
        if (isNumber(value === null || value === void 0 ? void 0 : value.perspective)) {
            arkRotate.perspective = value === null || value === void 0 ? void 0 : value.perspective;
        }
        modifier(this._modifiers, RotateModifier, arkRotate);
        return this;
    }
    transform(value) {
        if (isUndefined(value)) {
            modifier(this._modifiers, TransformModifier, undefined);
        }
        else {
            modifier(this._modifiers, TransformModifier, new ArkTransformMatrix(value["matrix4x4"]));
        }
        return this;
    }
    onAppear(event) {
        throw new Error("Method not implemented.");
    }
    onDisAppear(event) {
        throw new Error("Method not implemented.");
    }
    onAreaChange(event) {
        throw new Error("Method not implemented.");
    }
    visibility(value) {
        if (isNaN(value)) {
            modifier(this._modifiers, VisibilityModifier, undefined);
        }
        else {
            modifier(this._modifiers, VisibilityModifier, value);
        }
        return this;
    }
    flexGrow(value) {
        if (isNaN(value) || value < 0.0) {
            modifier(this._modifiers, FlexGrowModifier, undefined);
        }
        else {
            modifier(this._modifiers, FlexGrowModifier, value);
        }
        return this;
    }
    flexShrink(value) {
        if (isNaN(value) || value < 0.0) {
            modifier(this._modifiers, FlexShrinkModifier, undefined);
        }
        else {
            modifier(this._modifiers, FlexShrinkModifier, value);
        }
        return this;
    }
    flexBasis(value) {
        if (isLengthType(value)) {
            modifier(this._modifiers, FlexBasisModifier, value);
        }
        else {
            modifier(this._modifiers, FlexBasisModifier, undefined);
        }
        return this;
    }
    alignSelf(value) {
        if (value) {
            modifier(this._modifiers, AlignSelfModifier, value);
        }
        else {
            modifier(this._modifiers, AlignSelfModifier, ItemAlign.Auto);
        }
        return this;
    }
    displayPriority(value) {
        if (isNaN(value)) {
            modifier(this._modifiers, DisplayPriorityModifier, undefined);
        }
        else {
            modifier(this._modifiers, DisplayPriorityModifier, value);
        }
        return this;
    }
    zIndex(value) {
        if (value !== null) {
            let zIndex = 0;
            if (typeof (value) === "number") {
                zIndex = value;
            }
            modifier(this._modifiers, ZIndexModifier, zIndex);
        }
        return this;
    }
    sharedTransition(id, options) {
        let arkSharedTransition = new ArkSharedTransition();
        if (isString(id)) {
            arkSharedTransition.id = id;
        }
        if (typeof options === "object") {
            arkSharedTransition.options = options;
        }
        modifierWithKey(this._modifiersWithKeys, SharedTransitionModifier.identity, SharedTransitionModifier, arkSharedTransition);
        return this;
    }
    direction(value) {
        let direction = '';
        switch (value) {
            case 0:
                direction = 'Ltr';
                break;
            case 1:
                direction = 'Rtl';
                break;
            case 2:
            default:
                direction = 'Auto';
                break;
        }
        modifier(this._modifiers, DirectionModifier, direction);
        return this;
    }
    align(value) {
        if (isNumber(value)) {
            modifier(this._modifiers, AlignModifier, value);
        }
        else {
            modifier(this._modifiers, AlignModifier, undefined);
        }
        return this;
    }
    position(value) {
        modifierWithKey(this._modifiersWithKeys, PositionModifier.identity, PositionModifier, value);
        return this;
    }
    markAnchor(value) {
        let arkValue = new ArkPosition();
        if (!value || (!isLengthType(value.x) && !isLengthType(value.y))) {
            modifier(this._modifiers, MarkAnchorModifier, undefined);
            return this;
        }
        if (value.x && isLengthType(value.x)) {
            arkValue.x = value === null || value === void 0 ? void 0 : value.x;
        }
        if (value.y && isLengthType(value.y)) {
            arkValue.y = value === null || value === void 0 ? void 0 : value.y;
        }
        modifier(this._modifiers, MarkAnchorModifier, arkValue);
        return this;
    }
    offset(value) {
        let arkValue = new ArkPosition();
        if (!value || (!isLengthType(value.x) && !isLengthType(value.y))) {
            modifier(this._modifiers, OffsetModifier, undefined);
            return this;
        }
        if (value.x && isLengthType(value.x)) {
            arkValue.x = value === null || value === void 0 ? void 0 : value.x;
        }
        if (value.y && isLengthType(value.y)) {
            arkValue.y = value === null || value === void 0 ? void 0 : value.y;
        }
        modifier(this._modifiers, OffsetModifier, arkValue);
        return this;
    }
    enabled(value) {
        if (typeof value === "boolean") {
            modifier(this._modifiers, EnabledModifier, value);
        }
        else {
            modifier(this._modifiers, EnabledModifier, undefined);
        }
        return this;
    }
    useSizeType(value) {
        throw new Error("Method not implemented.");
    }
    alignRules(value) {
        if (!isObject(value) || JSON.stringify(value) === '{}') {
            modifier(this._modifiers, AlignRulesModifier, undefined);
            return this;
        }
        let keys = ['left', 'middle', 'right', 'top', 'center', 'bottom'];
        let arkValue = new ArkAlignRules();
        for (let i = 0; i < keys.length; i++) {
            let rule = value[keys[i]];
            let alignRule = '';
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
                }
                else {
                    if (align in VerticalAlign) {
                        alignSign = true;
                    }
                }
                if (!alignSign && !anchorSign) {
                    alignRule += '';
                }
                else if (!anchorSign) {
                    alignRule += align.toString();
                    alignRule += '|';
                    alignRule += '__container__';
                }
                else if (!alignSign) {
                    alignRule += '2';
                    alignRule += '|';
                    alignRule += anchor;
                }
                else {
                    alignRule += align.toString();
                    alignRule += '|';
                    alignRule += anchor;
                }
            }
            else {
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
    aspectRatio(value) {
        if (isNaN(value) || lessThenFunction(value, 0.0)) {
            modifier(this._modifiers, AspectRatioModifier, undefined);
        }
        else {
            modifier(this._modifiers, AspectRatioModifier, value);
        }
        return this;
    }
    clickEffect(value) {
        let arkClickEffect = new ArkClickEffect();
        arkClickEffect.level = 0;
        arkClickEffect.scale = 0.9;
        if (value) {
            arkClickEffect.level = value.level;
            arkClickEffect.scale = value.scale;
        }
        modifier(this._modifiers, ClickEffectModifier, arkClickEffect);
        return this;
    }
    onDragStart(event) {
        throw new Error("Method not implemented.");
    }
    onDragEnter(event) {
        throw new Error("Method not implemented.");
    }
    onDragMove(event) {
        throw new Error("Method not implemented.");
    }
    onDragLeave(event) {
        throw new Error("Method not implemented.");
    }
    onDrop(event) {
        throw new Error("Method not implemented.");
    }
    onDragEnd(event) {
        throw new Error("Method not implemented.");
    }
    allowDrop(value) {
        let allowDrop = new ArkAllowDrop();
        allowDrop.allowDropArray = value;
        modifier(this._modifiers, AllowDropModifier, allowDrop);
        return this;
    }
    draggable(value) {
        if (typeof value === "boolean") {
            modifier(this._modifiers, DraggableModifier, value);
        }
        else {
            modifier(this._modifiers, DraggableModifier, undefined);
        }
        return this;
    }
    overlay(value, options) {
        if (typeof value === 'string') {
            let arkOverlay = new ArkOverlay(value, options.align, options.offset.x, options.offset.y);
            modifier(this._modifiers, OverlayModifier, arkOverlay);
        }
        else {
            modifier(this._modifiers, OverlayModifier, undefined);
        }
        return this;
    }
    linearGradient(value) {
        let arkLinearGradient = new ArkLinearGradient(value.angle, value.direction, value.colors, value.repeating);
        modifier(this._modifiers, LinearGradientModifier, arkLinearGradient);
        return this;
    }
    sweepGradient(value) {
        let arkSweepGradient = new ArkSweepGradient(value.center, value.start, value.end, value.rotation, value.colors, value.repeating);
        modifier(this._modifiers, SweepGradientModifier, arkSweepGradient);
        return this;
    }
    radialGradient(value) {
        let arkRadialGradient = new ArkRadialGradient(value.center, value.radius, value.colors, value.repeating);
        modifier(this._modifiers, RadialGradientModifier, arkRadialGradient);
        return this;
    }
    motionPath(value) {
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
    shadow(value) {
        let arkShadow = new ArkShadow();
        if (arkShadow.parseShadowValue(value)) {
            modifier(this._modifiers, ShadowModifier, arkShadow);
        }
        else {
            modifier(this._modifiers, ShadowModifier, undefined);
        }
        return this;
    }
    mask(value) {
        modifierWithKey(this._modifiersWithKeys, MaskModifier.identity, MaskModifier, value);
        return this;
    }
    key(value) {
        if (typeof value === "string") {
            modifier(this._modifiers, IDModifier, value);
        }
        else {
            modifier(this._modifiers, IDModifier, undefined);
        }
        return this;
    }
    id(value) {
        if (typeof value === "string") {
            modifier(this._modifiers, KeyModifier, value);
        }
        else {
            modifier(this._modifiers, KeyModifier, undefined);
        }
        return this;
    }
    geometryTransition(id) {
        if (isString(id)) {
            modifier(this._modifiers, GeometryTransitionModifier, id);
        }
        return this;
    }
    bindPopup(show, popup) {
        throw new Error("Method not implemented.");
    }
    bindMenu(content, options) {
        throw new Error("Method not implemented.");
    }
    bindContextMenu(content, responseType, options) {
        throw new Error("Method not implemented.");
    }
    bindContentCover(isShow, builder, type) {
        throw new Error("Method not implemented.");
    }
    blendMode(value) {
        throw new Error("Method not implemented.");
    }
    clip(value) {
        modifierWithKey(this._modifiersWithKeys, Symbol("clip"), ClipModifier, value);
        return this;
    }
    bindSheet(isShow, builder, options) {
        throw new Error("Method not implemented.");
    }
    stateStyles(value) {
        throw new Error("Method not implemented.");
    }
    restoreId(value) {
        if (typeof value !== "number") {
            modifier(this._modifiers, RestoreIdModifier, undefined);
        }
        else {
            modifier(this._modifiers, RestoreIdModifier, value);
        }
        return this;
    }
    onVisibleAreaChange(ratios, event) {
        throw new Error("Method not implemented.");
    }
    sphericalEffect(value) {
        modifier(this._modifiers, SphericalEffectModifier, value);
        return this;
    }
    lightUpEffect(value) {
        modifier(this._modifiers, LightUpEffectModifier, value);
        return this;
    }
    pixelStretchEffect(options) {
        if (isResource(options.top) || isResource(options.right) ||
            isResource(options.bottom) || isResource(options.left)) {
            modifier(this._modifiers, PixelStretchEffectModifier, undefined);
            return this;
        }
        let arkPixelStretchEffect = new ArkPixelStretchEffect;
        arkPixelStretchEffect.top = options.top;
        arkPixelStretchEffect.right = options.right;
        arkPixelStretchEffect.bottom = options.bottom;
        arkPixelStretchEffect.left = options.left;
        modifier(this._modifiers, PixelStretchEffectModifier, arkPixelStretchEffect);
        return this;
    }
    keyboardShortcut(value, keys, action) {
        let keyboardShortCut = new ArkKeyBoardShortCut();
        keyboardShortCut.value = value;
        keyboardShortCut.keys = keys;
        if (action) {
            throw new Error("Method not implemented.");
        }
        else {
            modifier(this._modifiers, KeyBoardShortCutModifier, keyboardShortCut);
            return this;
        }
    }
    accessibilityGroup(value) {
        if (typeof value === "boolean") {
            modifier(this._modifiers, AccessibilityGroupModifier, value);
        }
        else {
            modifier(this._modifiers, AccessibilityGroupModifier, undefined);
        }
        return this;
    }
    accessibilityText(value) {
        if (typeof value === "string") {
            modifier(this._modifiers, AccessibilityTextModifier, value);
        }
        else {
            modifier(this._modifiers, AccessibilityTextModifier, undefined);
        }
        return this;
    }
    accessibilityDescription(value) {
        if (typeof value !== "string") {
            modifier(this._modifiers, AccessibilityDescriptionModifier, undefined);
        }
        else {
            modifier(this._modifiers, AccessibilityDescriptionModifier, value);
        }
        return this;
    }
    accessibilityLevel(value) {
        if (typeof value !== "string") {
            modifier(this._modifiers, AccessibilityLevelModifier, undefined);
        }
        else {
            modifier(this._modifiers, AccessibilityLevelModifier, value);
        }
        return this;
    }
    obscured(reasons) {
        let arkObscured = new ArkObscured();
        if (arkObscured.parseReasonsArray(reasons)) {
            modifier(this._modifiers, ObscuredModifier, arkObscured);
        }
        else {
            modifier(this._modifiers, ObscuredModifier, undefined);
        }
        return this;
    }
    reuseId(id) {
        throw new Error("Method not implemented.");
    }
    renderFit(fitMode) {
        modifier(this._modifiers, RenderFitModifier, fitMode);
        return this;
    }
    attributeModifier(modifier) {
        return this;
    }
}
const isNull = (val) => typeof val === 'object' && val === null;
const isArray = (val) => Array.isArray(val);
const isDate = (val) => val instanceof Date;
const isRegExp = (val) => val instanceof RegExp;
const isError = (val) => val instanceof Error;
const isFloat = (val) => Number.isFinite(val) && !Number.isInteger(val);
const isInteger = (val) => Number.isInteger(val);
const isNonEmptyMap = (val) => val instanceof Map && val.size > 0;
const isTruthyString = (val) => typeof val === 'string' && val.trim() !== '';
/// <reference path="./import.ts" />
class ArkButtonComponent extends ArkComponent {
    onGestureJudgeBegin(callback) {
        throw new Error("Method not implemented.");
    }
    type(value) {
        if (typeof value === "number") {
            modifier(this._modifiers, ButtonTypeModifier, value);
        }
        else {
            modifier(this._modifiers, ButtonTypeModifier, undefined);
        }
        return this;
    }
    stateEffect(value) {
        if (typeof value === "boolean") {
            modifier(this._modifiers, ButtonStateEffectModifier, value);
        }
        else {
            modifier(this._modifiers, ButtonStateEffectModifier, undefined);
        }
        return this;
    }
    fontColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, ButtonFontColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, ButtonFontColorModifier, undefined);
        }
        return this;
    }
    fontSize(value) {
        if (typeof value === "number" || typeof value === "string") {
            modifier(this._modifiers, ButtonFontSizeModifier, value);
        }
        else {
            modifier(this._modifiers, ButtonFontSizeModifier, undefined);
        }
        return this;
    }
    fontWeight(value) {
        if (typeof value === "string") {
            modifier(this._modifiers, ButtonFontWeightModifier, value);
        }
        else {
            modifier(this._modifiers, ButtonFontWeightModifier, undefined);
        }
        return this;
    }
    fontStyle(value) {
        if (typeof value === "number" && value >= 0 && value < 2) {
            modifier(this._modifiers, ButtonFontStyleModifier, value);
        }
        else {
            modifier(this._modifiers, ButtonFontStyleModifier, undefined);
        }
        return this;
    }
    fontFamily(value) {
        if (typeof value === "string") {
            modifier(this._modifiers, ButtonFontFamilyModifier, value);
        }
        else {
            modifier(this._modifiers, ButtonFontFamilyModifier, undefined);
        }
        return this;
    }
    labelStyle(value) {
        if (typeof value === "object") {
            let data = new ArkLabelStyle();
            data.heightAdaptivePolicy = value.heightAdaptivePolicy;
            data.maxFontSize = value.maxFontSize;
            data.maxLines = value.maxLines;
            data.minFontSize = value.minFontSize;
            data.overflow = value.overflow;
            if (typeof value.font === "object") {
                data.font.family = value.font.family;
                data.font.size = value.font.size;
                data.font.style = value.font.style;
                data.font.weight = value.font.weight;
            }
            modifier(this._modifiers, ButtonLabelStyleModifier, data);
        }
        else {
            modifier(this._modifiers, ButtonLabelStyleModifier, undefined);
        }
        return this;
    }
}
class ButtonStateEffectModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().button.resetStateEffect(node);
        }
        else {
            GetUINativeModule().button.setStateEffect(node, this.value);
        }
    }
}
ButtonStateEffectModifier.identity = Symbol("buttonStateEffect");
class ButtonFontStyleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().button.resetFontStyle(node);
        }
        else {
            GetUINativeModule().button.setFontStyle(node, this.value);
        }
    }
}
ButtonFontStyleModifier.identity = Symbol("buttonFontStyle");
class ButtonFontFamilyModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().button.resetFontFamily(node);
        }
        else {
            GetUINativeModule().button.setFontFamily(node, this.value);
        }
    }
}
ButtonFontFamilyModifier.identity = Symbol("buttonFontFamily");
class ButtonLabelStyleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().button.resetLabelStyle(node);
        }
        else {
            if (typeof this.value === "object") {
                let textOverflow = this.value.overflow; // number -> Ace::TextOverflow
                let maxLines = this.value.maxLines; // number -> uint32_t
                let minFontSize = this.value.minFontSize; // number/string -> Dimension
                let maxFontSize = this.value.maxFontSize; // number/string -> Dimension
                let heightAdaptivePolicy = this.value.heightAdaptivePolicy; // number -> Ace::TextHeightAdaptivePolicy
                let fontSize = undefined; // number/string ->Dimension
                let fontWeight = undefined; // string -> Ace::FontWeight
                let fontStyle = undefined; // number -> Ace::FontStyle
                let fontFamily = undefined; // string ->std::vector<std::string>
                if (typeof this.value.font === "object") {
                    fontSize = this.value.font.size;
                    fontWeight = this.value.font.weight;
                    fontStyle = this.value.font.style;
                    fontFamily = this.value.font.family;
                }
                GetUINativeModule().button.setLabelStyle(node, textOverflow, maxLines, minFontSize, maxFontSize, heightAdaptivePolicy, fontSize, fontWeight, fontStyle, fontFamily);
            }
        }
    }
}
ButtonLabelStyleModifier.identity = Symbol("buttonLabelStyle");
class ButtonTypeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().button.resetType(node);
        }
        else {
            GetUINativeModule().button.setType(node, this.value);
        }
    }
}
ButtonTypeModifier.identity = Symbol("buttonType");
class ButtonFontColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().button.resetFontColor(node);
        }
        else {
            GetUINativeModule().button.setFontColor(node, this.value);
        }
    }
}
ButtonFontColorModifier.identity = Symbol("buttonFontColor");
class ButtonFontSizeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().button.resetFontSize(node);
        }
        else {
            GetUINativeModule().button.setFontSize(node, this.value);
        }
    }
}
ButtonFontSizeModifier.identity = Symbol("buttonFontSize");
class ButtonFontWeightModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().button.resetFontWeight(node);
        }
        else {
            GetUINativeModule().button.setFontWeight(node, this.value);
        }
    }
}
ButtonFontWeightModifier.identity = Symbol("buttonFontWeight");
// @ts-ignore
globalThis.Button.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkButtonComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkLoadingProgressComponent extends ArkComponent {
    onGestureJudgeBegin(callback) {
        throw new Error("Method not implemented.");
    }
    color(value) {
        throw new Error("Method not implemented.");
    }
    enableLoading(value) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.LoadingProgress.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkLoadingProgressComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkRefreshComponent extends ArkComponent {
    onGestureJudgeBegin(callback) {
        throw new Error("Method not implemented.");
    }
    onStateChange(callback) {
        throw new Error("Method not implemented.");
    }
    onRefreshing(callback) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Refresh.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkRefreshComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkScrollComponent extends ArkComponent {
    onGestureJudgeBegin(callback) {
        throw new Error("Method not implemented.");
    }
    scrollable(value) {
        throw new Error("Method not implemented.");
    }
    onScroll(event) {
        throw new Error("Method not implemented.");
    }
    onScrollEdge(event) {
        throw new Error("Method not implemented.");
    }
    onScrollStart(event) {
        throw new Error("Method not implemented.");
    }
    onScrollEnd(event) {
        throw new Error("Method not implemented.");
    }
    onScrollStop(event) {
        throw new Error("Method not implemented.");
    }
    scrollBar(barState) {
        throw new Error("Method not implemented.");
    }
    scrollBarColor(color) {
        throw new Error("Method not implemented.");
    }
    scrollBarWidth(value) {
        throw new Error("Method not implemented.");
    }
    edgeEffect(edgeEffect) {
        throw new Error("Method not implemented.");
    }
    onScrollFrameBegin(event) {
        throw new Error("Method not implemented.");
    }
    nestedScroll(value) {
        throw new Error("Method not implemented.");
    }
    enableScrollInteraction(value) {
        throw new Error("Method not implemented.");
    }
    friction(value) {
        throw new Error("Method not implemented.");
    }
    scrollSnap(value) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Scroll.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkScrollComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkStackComponent extends ArkComponent {
    onGestureJudgeBegin(callback) {
        throw new Error("Method not implemented.");
    }
    alignContent(value) {
        if (value) {
            modifier(this._modifiers, StackAlignContentModifier, value);
        }
        else {
            modifier(this._modifiers, StackAlignContentModifier, undefined);
        }
        return this;
    }
}
class StackAlignContentModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().stack.resetAlignContent(node);
        }
        else {
            GetUINativeModule().stack.setAlignContent(node, this.value);
        }
    }
}
StackAlignContentModifier.identity = Symbol('stackAlignContent');
// @ts-ignore
globalThis.Stack.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkStackComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ImageColorFilterModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().image.resetColorFilter(node);
        }
        else {
            GetUINativeModule().image.setColorFilter(node, JSON.parse(this.value));
        }
    }
}
ImageColorFilterModifier.identity = Symbol('imageColorFilter');
class ImageFillColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().image.resetFillColor(node);
        }
        else {
            GetUINativeModule().image.setFillColor(node, this.value);
        }
    }
}
ImageFillColorModifier.identity = Symbol('imageFillColor');
class ImageAltModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().image.resetAlt(node);
        }
        else {
            GetUINativeModule().image.setAlt(node, this.value);
        }
    }
}
ImageAltModifier.identity = Symbol('imageAlt');
class ImageCopyOptionModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().image.resetCopyOption(node);
        }
        else {
            GetUINativeModule().image.setCopyOption(node, this.value);
        }
    }
}
ImageCopyOptionModifier.identity = Symbol('imageCopyOption');
class ImageAutoResizeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().image.resetAutoResize(node);
        }
        else {
            GetUINativeModule().image.setAutoResize(node, this.value);
        }
    }
}
ImageAutoResizeModifier.identity = Symbol('imageAutoResize');
class ImageFitOriginalSizeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().image.resetFitOriginalSize(node);
        }
        else {
            GetUINativeModule().image.setFitOriginalSize(node, this.value);
        }
    }
}
ImageFitOriginalSizeModifier.identity = Symbol('imageFitOriginalSize');
class ImageDraggableModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().image.resetDraggable(node);
        }
        else {
            GetUINativeModule().image.setDraggable(node, this.value);
        }
    }
}
ImageDraggableModifier.identity = Symbol('imageDraggable');
class ImageInterpolationModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().image.resetImageInterpolation(node);
        }
        else {
            GetUINativeModule().image.setImageInterpolation(node, this.value);
        }
    }
}
ImageInterpolationModifier.identity = Symbol('imageInterpolation');
class ImageSourceSizeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().image.resetSourceSize(node);
        }
        else {
            let values = this.value.split("|");
            let w = parseFloat(values[0]);
            let h = parseFloat(values[1]);
            GetUINativeModule().image.setSourceSize(node, w, h);
        }
    }
}
ImageSourceSizeModifier.identity = Symbol("imageSourceSize");
class ImageMatchTextDirectionModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().image.resetMatchTextDirection(node);
        }
        else {
            GetUINativeModule().image.setMatchTextDirection(node, this.value);
        }
    }
}
ImageMatchTextDirectionModifier.identity = Symbol('imageMatchTextDirection');
class ImageObjectRepeatModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().image.resetObjectRepeat(node);
        }
        else {
            GetUINativeModule().image.setObjectRepeat(node, this.value);
        }
    }
}
ImageObjectRepeatModifier.identity = Symbol('imageObjectRepeat');
class ImageRenderModeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().image.resetRenderMode(node);
        }
        else {
            GetUINativeModule().image.setRenderMode(node, this.value);
        }
    }
}
ImageRenderModeModifier.identity = Symbol('imageRenderMode');
class ImageSyncLoadModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().image.resetSyncLoad(node);
        }
        else {
            GetUINativeModule().image.setSyncLoad(node, this.value);
        }
    }
}
ImageSyncLoadModifier.identity = Symbol('imageSyncLoad');
class ImageObjectFitModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().image.resetObjectFit(node);
        }
        else {
            GetUINativeModule().image.setObjectFit(node, this.value);
        }
    }
}
ImageObjectFitModifier.identity = Symbol('imageObjectFit');
class ArkImageComponent extends ArkComponent {
    onGestureJudgeBegin(callback) {
        throw new Error("Method not implemented.");
    }
    draggable(value) {
        let arkValue = false;
        if (isBoolean(value)) {
            arkValue = value;
        }
        modifier(this._modifiers, ImageDraggableModifier, arkValue);
        return this;
    }
    alt(value) {
        let arkValue = null;
        if (isString(value)) {
            arkValue = value;
        }
        modifier(this._modifiers, ImageAltModifier, arkValue);
        return this;
    }
    matchTextDirection(value) {
        let matchTextDirection = false;
        if (isBoolean(value)) {
            matchTextDirection = value;
        }
        modifier(this._modifiers, ImageMatchTextDirectionModifier, matchTextDirection);
        return this;
    }
    fitOriginalSize(value) {
        let arkValue = false;
        if (isBoolean(value)) {
            arkValue = value;
        }
        modifier(this._modifiers, ImageFitOriginalSizeModifier, arkValue);
        return this;
    }
    fillColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, ImageFillColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, ImageFillColorModifier, undefined);
        }
        return this;
    }
    objectFit(value) {
        if (value) {
            modifier(this._modifiers, ImageObjectFitModifier, value);
        }
        else {
            modifier(this._modifiers, ImageObjectFitModifier, undefined);
        }
        return this;
    }
    objectRepeat(value) {
        if (value) {
            modifier(this._modifiers, ImageObjectRepeatModifier, value);
        }
        else {
            modifier(this._modifiers, ImageObjectRepeatModifier, undefined);
        }
        return this;
    }
    autoResize(value) {
        let arkValue = true;
        if (isBoolean(value)) {
            arkValue = value;
        }
        modifier(this._modifiers, ImageAutoResizeModifier, arkValue);
        return this;
    }
    renderMode(value) {
        if (value) {
            modifier(this._modifiers, ImageRenderModeModifier, value);
        }
        else {
            modifier(this._modifiers, ImageRenderModeModifier, undefined);
        }
        return this;
    }
    interpolation(value) {
        if (value) {
            modifier(this._modifiers, ImageInterpolationModifier, value);
        }
        else {
            modifier(this._modifiers, ImageInterpolationModifier, undefined);
        }
        return this;
    }
    sourceSize(value) {
        let w = "0.0";
        let h = "0.0";
        if (isNumber(value.width)) {
            w = value.width.toString();
        }
        if (isNumber(value.height)) {
            h = value.height.toString();
        }
        modifier(this._modifiers, ImageSourceSizeModifier, w + "|" + h);
        return this;
    }
    syncLoad(value) {
        let syncLoad = false;
        if (isBoolean(value)) {
            syncLoad = value;
        }
        modifier(this._modifiers, ImageSyncLoadModifier, syncLoad);
        return this;
    }
    colorFilter(value) {
        if (isUndefined(value) || Object.prototype.toString.call(value) !== '[object Array]') {
            modifier(this._modifiers, ImageColorFilterModifier, undefined);
            return this;
        }
        if (Object.prototype.toString.call(value) === '[object Array]') {
            let _value = value;
            if (_value.length !== 20) {
                modifier(this._modifiers, ImageColorFilterModifier, undefined);
                return this;
            }
        }
        modifier(this._modifiers, ImageColorFilterModifier, JSON.stringify(value));
        return this;
    }
    copyOption(value) {
        if (value in CopyOptions) {
            modifier(this._modifiers, ImageCopyOptionModifier, value);
        }
        else {
            modifier(this._modifiers, ImageCopyOptionModifier, undefined);
        }
        return this;
    }
    onComplete(callback) {
        throw new Error('Method not implemented.');
    }
    onError(callback) {
        throw new Error('Method not implemented.');
    }
    onFinish(event) {
        throw new Error('Method not implemented.');
    }
}
// @ts-ignore
globalThis.Image.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkImageComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class FontColorModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetFontColor(node);
        }
        else {
            GetUINativeModule().text.setFontColor(node, this.value);
        }
    }
    checkObjectDiff() {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        }
        else {
            return true;
        }
    }
}
FontColorModifier.identity = Symbol('fontColor');
class FontSizeModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetFontSize(node);
        }
        else {
            GetUINativeModule().text.setFontSize(node, this.value);
        }
    }
    checkObjectDiff() {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        }
        else {
            return true;
        }
    }
}
FontSizeModifier.identity = Symbol('fontSize');
class FontWeightModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetFontWeight(node);
        }
        else {
            GetUINativeModule().text.setFontWeight(node, this.value);
        }
    }
}
FontWeightModifier.identity = Symbol('fontWeight');
class FontStyleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetFontStyle(node);
        }
        else {
            GetUINativeModule().text.setFontStyle(node, this.value);
        }
    }
}
FontStyleModifier.identity = Symbol('fontStyle');
class TextAlignModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetTextAlign(node);
        }
        else {
            GetUINativeModule().text.setTextAlign(node, this.value);
        }
    }
}
TextAlignModifier.identity = Symbol('textAlign');
class TextHeightAdaptivePolicyModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetHeightAdaptivePolicy(node);
        }
        else {
            GetUINativeModule().text.setHeightAdaptivePolicy(node, this.value);
        }
    }
}
TextHeightAdaptivePolicyModifier.identity = Symbol('textHeightAdaptivePolicy');
class TextDraggableModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetDraggable(node);
        }
        else {
            GetUINativeModule().text.setDraggable(node, this.value);
        }
    }
}
TextDraggableModifier.identity = Symbol('textDraggable');
class TextMinFontSizeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetMinFontSize(node);
        }
        else {
            GetUINativeModule().text.setMinFontSize(node, this.value);
        }
    }
}
TextMinFontSizeModifier.identity = Symbol('textMinFontSize');
class TextMaxFontSizeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetMaxFontSize(node);
        }
        else {
            GetUINativeModule().text.setMaxFontSize(node, this.value);
        }
    }
}
TextMaxFontSizeModifier.identity = Symbol('textMaxFontSize');
class TextLineHeightModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetLineHeight(node);
        }
        else {
            GetUINativeModule().text.setLineHeight(node, this.value);
        }
    }
}
TextLineHeightModifier.identity = Symbol('textLineHeight');
class TextCopyOptionModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetCopyOption(node);
        }
        else {
            GetUINativeModule().text.setCopyOption(node, this.value);
        }
    }
}
TextCopyOptionModifier.identity = Symbol('textCopyOption');
class TextFontFamilyModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetFontFamily(node);
        }
        else {
            GetUINativeModule().text.setFontFamily(node, this.value);
        }
    }
}
TextFontFamilyModifier.identity = Symbol('textFontFamily');
class TextMaxLinesModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetMaxLines(node);
        }
        else {
            GetUINativeModule().text.setMaxLines(node, this.value);
        }
    }
}
TextMaxLinesModifier.identity = Symbol('textMaxLines');
class TextLetterSpacingModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetLetterSpacing(node);
        }
        else {
            GetUINativeModule().text.setLetterSpacing(node, this.value);
        }
    }
}
TextLetterSpacingModifier.identity = Symbol('textLetterSpacing');
class TextTextOverflowModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetTextOverflow(node);
        }
        else {
            GetUINativeModule().text.setTextOverflow(node, this.value);
        }
    }
}
TextTextOverflowModifier.identity = Symbol('textTextOverflow');
class TextBaselineOffsetModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetBaselineOffset(node);
        }
        else {
            GetUINativeModule().text.setBaselineOffset(node, this.value);
        }
    }
}
TextBaselineOffsetModifier.identity = Symbol('textBaselineOffset');
class TextTextCaseModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetTextCase(node);
        }
        else {
            GetUINativeModule().text.setTextCase(node, this.value);
        }
    }
}
TextTextCaseModifier.identity = Symbol('textTextCase');
class TextTextIndentModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetTextIndent(node);
        }
        else {
            GetUINativeModule().text.setTextIndent(node, this.value);
        }
    }
}
TextTextIndentModifier.identity = Symbol('textTextIndent');
class TextTextShadowModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetTextShadow(node);
        }
        else {
            GetUINativeModule().text.setTextShadow(node, this.value.radius, this.value.color, this.value.offsetX, this.value.offsetY, this.value.fill, this.value.radius.length);
        }
    }
}
TextTextShadowModifier.identity = Symbol('textTextShadow');
class TextDecorationModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetDecoration(node);
        }
        else {
            GetUINativeModule().text.setDecoration(node, this.value.type, this.value.color);
        }
    }
}
TextDecorationModifier.identity = Symbol('textDecoration');
class TextFontModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetFont(node);
        }
        else {
            GetUINativeModule().text.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
    }
}
TextFontModifier.identity = Symbol('textFont');
class ArkTextComponent extends ArkComponent {
    enableDataDetector(enable) {
        throw new Error('Method not implemented.');
    }
    dataDetectorConfig(config) {
        throw new Error('Method not implemented.');
    }
    onGestureJudgeBegin(callback) {
        throw new Error('Method not implemented.');
    }
    font(value) {
        let arkValue = new ArkFont();
        if (isLengthType(value.size)) {
            arkValue.size = value.size;
        }
        if (isLengthType(value.weight)) {
            arkValue.weight = value.weight;
        }
        if (isString(value.family)) {
            arkValue.family = value.family;
        }
        if (isNumber(value.style)) {
            if (value.style in FontStyle) {
                arkValue.style = value.style;
            }
            else {
                arkValue.style = FontStyle.Normal;
            }
        }
        modifier(this._modifiers, TextFontModifier, arkValue);
        return this;
    }
    fontColor(value) {
        modifierWithKey(this._modifiersWithKeys, FontColorModifier.identity, FontColorModifier, value);
        return this;
    }
    fontSize(value) {
        modifierWithKey(this._modifiersWithKeys, FontSizeModifier.identity, FontSizeModifier, value);
        return this;
    }
    minFontSize(value) {
        if (isLengthType(value)) {
            let arkValue = value;
            modifier(this._modifiers, TextMinFontSizeModifier, arkValue);
        }
        else {
            modifier(this._modifiers, TextMinFontSizeModifier, undefined);
        }
        return this;
    }
    maxFontSize(value) {
        if (isLengthType(value)) {
            let arkValue = value;
            modifier(this._modifiers, TextMaxFontSizeModifier, arkValue);
        }
        else {
            modifier(this._modifiers, TextMaxFontSizeModifier, undefined);
        }
        return this;
    }
    fontStyle(value) {
        if (isNumber(value)) {
            modifier(this._modifiers, FontStyleModifier, value);
        }
        return this;
    }
    fontWeight(value) {
        let fontWeightStr = '400';
        if (isNumber(value)) {
            if (value === 0) {
                fontWeightStr = 'Lighter';
            }
            else if (value === 1) {
                fontWeightStr = 'Normal';
            }
            else if (value === 2) {
                fontWeightStr = 'Regular';
            }
            else if (value === 3) {
                fontWeightStr = 'Medium';
            }
            else if (value === 4) {
                fontWeightStr = 'Bold';
            }
            else if (value === 5) {
                fontWeightStr = 'Bolder';
            }
            else {
                fontWeightStr = value.toString();
            }
        }
        else if (isString(value)) {
            fontWeightStr = value;
        }
        modifier(this._modifiers, FontWeightModifier, fontWeightStr);
        return this;
    }
    textAlign(value) {
        let textAlignNum = 0;
        if (isNumber(value)) {
            textAlignNum = value;
        }
        modifier(this._modifiers, TextAlignModifier, textAlignNum);
        return this;
    }
    lineHeight(value) {
        if (isLengthType(value)) {
            let arkValue = value;
            modifier(this._modifiers, TextLineHeightModifier, arkValue);
        }
        else {
            modifier(this._modifiers, TextLineHeightModifier, undefined);
        }
        return this;
    }
    textOverflow(value) {
        if (value === null || value === undefined) {
            modifier(this._modifiers, TextTextOverflowModifier, undefined);
        }
        else if (isObject(value)) {
            let overflowValue = value.overflow;
            if (isNumber(overflowValue)) {
                if (!(overflowValue in CopyOptions)) {
                    overflowValue = TextOverflow.Clip;
                }
                modifier(this._modifiers, TextTextOverflowModifier, overflowValue);
            }
            else {
                modifier(this._modifiers, TextTextOverflowModifier, undefined);
            }
        }
        return this;
    }
    fontFamily(value) {
        if (isLengthType(value)) {
            let arkValue = value;
            modifier(this._modifiers, TextFontFamilyModifier, arkValue);
        }
        else {
            modifier(this._modifiers, TextFontFamilyModifier, undefined);
        }
        return this;
    }
    maxLines(value) {
        if (value === null || value === undefined) {
            modifier(this._modifiers, TextMaxLinesModifier, undefined);
        }
        else {
            modifier(this._modifiers, TextMaxLinesModifier, value);
        }
        return this;
    }
    decoration(value) {
        let arkDecoration = new ArkDecoration();
        if (value === null || value === undefined) {
            modifier(this._modifiers, TextDecorationModifier, arkDecoration);
        }
        else if (isObject(value)) {
            let typeValue = value.type;
            if (!(typeValue in TextDecorationType)) {
                arkDecoration.type = TextDecorationType.None;
            }
            else {
                arkDecoration.type = typeValue;
            }
            let arkColor = new ArkColor();
            if (arkColor.parseColorValue(value.color)) {
                arkDecoration.color = arkColor.color;
            }
            modifier(this._modifiers, TextDecorationModifier, arkDecoration);
        }
        return this;
    }
    letterSpacing(value) {
        if (isLengthType(value)) {
            modifier(this._modifiers, TextLetterSpacingModifier, value);
        }
        else {
            modifier(this._modifiers, TextLetterSpacingModifier, undefined);
        }
        return this;
    }
    textCase(value) {
        if (!(value in TextCase)) {
            modifier(this._modifiers, TextTextCaseModifier, undefined);
        }
        else {
            modifier(this._modifiers, TextTextCaseModifier, value);
        }
        return this;
    }
    baselineOffset(value) {
        if (isLengthType(value)) {
            modifier(this._modifiers, TextBaselineOffsetModifier, value);
        }
        else {
            modifier(this._modifiers, TextBaselineOffsetModifier, undefined);
        }
        return this;
    }
    copyOption(value) {
        if (isNumber(value)) {
            modifier(this._modifiers, TextCopyOptionModifier, value);
        }
        else {
            modifier(this._modifiers, TextCopyOptionModifier, undefined);
        }
        return this;
    }
    draggable(value) {
        if (isBoolean(value)) {
            modifier(this._modifiers, TextDraggableModifier, value);
        }
        else {
            modifier(this._modifiers, TextDraggableModifier, undefined);
        }
        return this;
    }
    textShadow(value) {
        let array = new ArkShadowInfoToArray();
        if (value === null || value === undefined) {
            modifier(this._modifiers, TextTextShadowModifier, undefined);
        }
        else if (Object.getPrototypeOf(value).constructor === Object) {
            let objValue = value;
            if (objValue.radius === null || objValue.radius === undefined) {
                modifier(this._modifiers, TextTextShadowModifier, undefined);
            }
            else {
                array.radius.push(objValue.radius);
                array.color.push(objValue.color);
                array.offsetX.push(objValue.offsetX === undefined || objValue.offsetX === null ? 0 : objValue.offsetX);
                array.offsetY.push(objValue.offsetY === undefined || objValue.offsetY === null ? 0 : objValue.offsetY);
                array.fill.push(objValue.fill === undefined || objValue.fill === null ? false : objValue.fill);
                modifier(this._modifiers, TextTextShadowModifier, array);
            }
        }
        else if (Object.getPrototypeOf(value).constructor === Array) {
            let arrayValue = value;
            let isFlag = true;
            for (let item of arrayValue) {
                if (item.radius === undefined || item.radius === null) {
                    isFlag = false;
                    break;
                }
            }
            if (isFlag) {
                for (let objValue of arrayValue) {
                    array.radius.push(objValue.radius);
                    array.color.push(objValue.color);
                    array.offsetX.push(objValue.offsetX === undefined || objValue.offsetX === null ? 0 : objValue.offsetX);
                    array.offsetY.push(objValue.offsetY === undefined || objValue.offsetY === null ? 0 : objValue.offsetY);
                    array.fill.push(objValue.fill === undefined || objValue.fill === null ? false : objValue.fill);
                }
                modifier(this._modifiers, TextTextShadowModifier, array);
            }
            else {
                modifier(this._modifiers, TextTextShadowModifier, undefined);
            }
        }
        return this;
    }
    heightAdaptivePolicy(value) {
        if (!(value in TextHeightAdaptivePolicy)) {
            modifier(this._modifiers, TextHeightAdaptivePolicyModifier, undefined);
        }
        else {
            modifier(this._modifiers, TextHeightAdaptivePolicyModifier, value);
        }
        return this;
    }
    textIndent(value) {
        if (isLengthType(value)) {
            let arkValue = value;
            modifier(this._modifiers, TextTextIndentModifier, arkValue);
        }
        else {
            modifier(this._modifiers, TextTextIndentModifier, undefined);
        }
        return this;
    }
    wordBreak(value) {
        throw new Error('Method not implemented.');
    }
    onCopy(callback) {
        throw new Error('Method not implemented.');
    }
    selection(selectionStart, selectionEnd) {
        throw new Error('Method not implemented.');
    }
    ellipsisMode(value) {
        throw new Error('Method not implemented.');
    }
}
// @ts-ignore
globalThis.Text.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkTextComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class TextAreaFontStyleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textArea.resetFontStyle(node);
        }
        else {
            GetUINativeModule().textArea.setFontStyle(node, this.value);
        }
    }
}
TextAreaFontStyleModifier.identity = Symbol('textAreaFontStyle');
class TextAreaCopyOptionModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textArea.resetCopyOption(node);
        }
        else {
            GetUINativeModule().textArea.setCopyOption(node, this.value);
        }
    }
}
TextAreaCopyOptionModifier.identity = Symbol('textAreaCopyOption');
class TextAreaMaxLinesModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textArea.resetMaxLines(node);
        }
        else {
            GetUINativeModule().textArea.setMaxLines(node, this.value);
        }
    }
}
TextAreaMaxLinesModifier.identity = Symbol('textAreaMaxLines');
class TextAreaFontSizeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textArea.resetFontSize(node);
        }
        else {
            GetUINativeModule().textArea.setFontSize(node, this.value);
        }
    }
}
TextAreaFontSizeModifier.identity = Symbol('textAreaFontSize');
class TextAreaPlaceholderColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textArea.resetPlaceholderColor(node);
        }
        else {
            GetUINativeModule().textArea.setPlaceholderColor(node, this.value);
        }
    }
}
TextAreaPlaceholderColorModifier.identity = Symbol('textAreaPlaceholderColor');
class TextAreaFontColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textArea.resetFontColor(node);
        }
        else {
            GetUINativeModule().textArea.setFontColor(node, this.value);
        }
    }
}
TextAreaFontColorModifier.identity = Symbol('textAreaFontColor');
class TextAreaFontWeightModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textArea.resetFontWeight(node);
        }
        else {
            GetUINativeModule().textArea.setFontWeight(node, this.value);
        }
    }
}
TextAreaFontWeightModifier.identity = Symbol('textAreaFontWeight');
class TextAreaBarStateModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textArea.resetBarState(node);
        }
        else {
            GetUINativeModule().textArea.setBarState(node, this.value);
        }
    }
}
TextAreaBarStateModifier.identity = Symbol('textAreaBarState');
class TextAreaEnableKeyboardOnFocusModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textArea.resetEnableKeyboardOnFocus(node);
        }
        else {
            GetUINativeModule().textArea.setEnableKeyboardOnFocus(node, this.value);
        }
    }
}
TextAreaEnableKeyboardOnFocusModifier.identity = Symbol('textAreaEnableKeyboardOnFocus');
class TextAreaFontFamilyModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textArea.resetFontFamily(node);
        }
        else {
            GetUINativeModule().textArea.setFontFamily(node, this.value);
        }
    }
}
TextAreaFontFamilyModifier.identity = Symbol('textAreaFontFamily');
class TextAreaCaretColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textArea.resetCaretColor(node);
        }
        else {
            GetUINativeModule().textArea.setCaretColor(node, this.value);
        }
    }
}
TextAreaCaretColorModifier.identity = Symbol('textAreaCaretColor');
class TextAreaMaxLengthModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textArea.resetMaxLength(node);
        }
        else {
            GetUINativeModule().textArea.setMaxLength(node, this.value);
        }
    }
}
TextAreaMaxLengthModifier.identity = Symbol('textAreaMaxLength');
class TextAreaStyleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textArea.resetStyle(node);
        }
        else {
            GetUINativeModule().textArea.setStyle(node, this.value);
        }
    }
}
TextAreaStyleModifier.identity = Symbol('textAreaStyle');
class TextAreaSelectionMenuHiddenModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textArea.resetSelectionMenuHidden(node);
        }
        else {
            GetUINativeModule().textArea.setSelectionMenuHidden(node, this.value);
        }
    }
}
TextAreaSelectionMenuHiddenModifier.identity = Symbol('textAreaSelectionMenuHidden');
class TextAreaPlaceholderFontModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textArea.resetPlaceholderFont(node);
        }
        else {
            GetUINativeModule().textArea.setPlaceholderFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
    }
}
TextAreaPlaceholderFontModifier.identity = Symbol('textAreaPlaceholderFont');
class TextAreaTextAlignModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textArea.resetTextAlign(node);
        }
        else {
            GetUINativeModule().textArea.setTextAlign(node, this.value);
        }
    }
}
TextAreaTextAlignModifier.identity = Symbol('textAreaTextAlign');
class TextAreaShowCounterModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textArea.resetShowCounter(node);
        }
        else {
            GetUINativeModule().textArea.setShowCounter(node, this.value);
        }
    }
}
TextAreaShowCounterModifier.identity = Symbol('textAreaShowCounter');
class ArkTextAreaComponent extends ArkComponent {
    type(value) {
        throw new Error('Method not implemented.');
    }
    placeholderColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, TextAreaPlaceholderColorModifier, arkColor.color);
        }
        return this;
    }
    placeholderFont(value) {
        let arkValue = new ArkFont();
        if (isLengthType(value.size)) {
            arkValue.size = value.size;
        }
        if (isLengthType(value.weight)) {
            arkValue.weight = value.weight;
        }
        if (isString(value.family)) {
            arkValue.family = value.family;
        }
        if (value.style in FontStyle) {
            arkValue.style = value.style;
        }
        modifier(this._modifiers, TextAreaPlaceholderFontModifier, arkValue);
        return this;
    }
    textAlign(value) {
        if (value) {
            modifier(this._modifiers, TextAreaTextAlignModifier, value);
        }
        else {
            modifier(this._modifiers, TextAreaTextAlignModifier, TextAlign.Start);
        }
        return this;
    }
    caretColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, TextAreaCaretColorModifier, arkColor.color);
        }
        return this;
    }
    fontColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, TextAreaFontColorModifier, arkColor.color);
        }
        return this;
    }
    fontSize(value) {
        if (isLengthType(value)) {
            modifier(this._modifiers, TextAreaFontSizeModifier, value);
        }
        else {
            modifier(this._modifiers, TextAreaFontSizeModifier, 16);
        }
        return this;
    }
    fontStyle(value) {
        let arkValue = FontStyle.Normal;
        if (value) {
            arkValue = value;
        }
        modifier(this._modifiers, TextAreaFontStyleModifier, arkValue);
        return this;
    }
    fontWeight(value) {
        if (!isLengthType(value)) {
            modifier(this._modifiers, TextAreaFontWeightModifier, undefined);
        }
        else {
            modifier(this._modifiers, TextAreaFontWeightModifier, value);
        }
        return this;
    }
    fontFamily(value) {
        let arkValue = 'HarmonyOS Sans';
        if (isString(value)) {
            arkValue = value;
        }
        modifier(this._modifiers, TextAreaFontFamilyModifier, arkValue);
        return this;
    }
    inputFilter(value, error) {
        throw new Error('Method not implemented.');
    }
    onChange(callback) {
        throw new Error('Method not implemented.');
    }
    onTextSelectionChange(callback) {
        throw new Error('Method not implemented.');
    }
    onContentScroll(callback) {
        throw new Error('Method not implemented.');
    }
    onEditChange(callback) {
        throw new Error('Method not implemented.');
    }
    onCopy(callback) {
        throw new Error('Method not implemented.');
    }
    onCut(callback) {
        throw new Error('Method not implemented.');
    }
    onPaste(callback) {
        throw new Error('Method not implemented.');
    }
    copyOption(value) {
        if (value === undefined) {
            value = CopyOptions.LocalDevice;
            modifier(this._modifiers, TextAreaCopyOptionModifier, value);
        }
        let copyOptions = CopyOptions.None;
        if (isNumber(value)) {
            copyOptions = value;
        }
        modifier(this._modifiers, TextAreaCopyOptionModifier, copyOptions);
        return this;
    }
    enableKeyboardOnFocus(value) {
        if (value === undefined) {
            return this;
        }
        if (isUndefined(value) || !isBoolean(value)) {
            modifier(this._modifiers, TextAreaEnableKeyboardOnFocusModifier, true);
            return this;
        }
        modifier(this._modifiers, TextAreaEnableKeyboardOnFocusModifier, Boolean(value));
        return this;
    }
    maxLength(value) {
        if (!value || isNaN(value)) {
            modifier(this._modifiers, TextAreaMaxLengthModifier, undefined);
            return this;
        }
        modifier(this._modifiers, TextAreaMaxLengthModifier, value);
        return this;
    }
    showCounter(value) {
        let showCounter = false;
        if (isBoolean(value)) {
            showCounter = value;
        }
        modifier(this._modifiers, TextAreaShowCounterModifier, showCounter);
        return this;
    }
    style(value) {
        if (value) {
            modifier(this._modifiers, TextAreaStyleModifier, value);
        }
        else {
            modifier(this._modifiers, TextAreaStyleModifier, undefined);
        }
        return this;
    }
    barState(value) {
        if (value === null || value === undefined || !isNumber(value)) {
            modifier(this._modifiers, TextAreaBarStateModifier, BarState.Auto);
            return this;
        }
        modifier(this._modifiers, TextAreaBarStateModifier, value);
        return this;
    }
    selectionMenuHidden(value) {
        let selectionMenuHidden = false;
        if (isBoolean(value)) {
            selectionMenuHidden = value;
        }
        modifier(this._modifiers, TextAreaSelectionMenuHiddenModifier, selectionMenuHidden);
        return this;
    }
    maxLines(value) {
        if (!isNumber(value)) {
            modifier(this._modifiers, TextAreaMaxLinesModifier, undefined);
            return this;
        }
        if (Number(value) <= 0) {
            modifier(this._modifiers, TextAreaMaxLinesModifier, undefined);
            return this;
        }
        modifier(this._modifiers, TextAreaMaxLinesModifier, Number(value));
        return this;
    }
    customKeyboard(value) {
        throw new Error('Method not implemented.');
    }
}
// @ts-ignore
globalThis.TextArea.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkTextAreaComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class TextInputStyleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetStyle(node);
        }
        else {
            GetUINativeModule().textInput.setStyle(node, this.value);
        }
    }
}
TextInputStyleModifier.identity = Symbol('textInputStyle');
class TextInputMaxLengthModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetMaxLength(node);
        }
        else {
            GetUINativeModule().textInput.setMaxLength(node, this.value);
        }
    }
}
TextInputMaxLengthModifier.identity = Symbol('textInputMaxLength');
class TextInputMaxLinesModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetMaxLines(node);
        }
        else {
            GetUINativeModule().textInput.setMaxLines(node, this.value);
        }
    }
}
TextInputMaxLinesModifier.identity = Symbol('textInputMaxLines');
class TextInputShowPasswordIconModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetShowPasswordIcon(node);
        }
        else {
            GetUINativeModule().textInput.setShowPasswordIcon(node, this.value);
        }
    }
}
TextInputShowPasswordIconModifier.identity = Symbol('textInputShowPasswordIcon');
class TextInputTextAlignModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetTextAlign(node);
        }
        else {
            GetUINativeModule().textInput.setTextAlign(node, this.value);
        }
    }
}
TextInputTextAlignModifier.identity = Symbol('textInputTextAlign');
class TextInputPlaceholderFontModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetPlaceholderFont(node);
        }
        else {
            GetUINativeModule().textInput.setPlaceholderFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
    }
}
TextInputPlaceholderFontModifier.identity = Symbol('textInputPlaceholderFont');
class TextInputPlaceholderColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetPlaceholderColor(node);
        }
        else {
            GetUINativeModule().textInput.setPlaceholderColor(node, this.value);
        }
    }
}
TextInputPlaceholderColorModifier.identity = Symbol('textInputPlaceholderColor');
class TextInputPasswordIconModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetPasswordIcon(node);
        }
        else {
            GetUINativeModule().textInput.setPasswordIcon(node, this.value.onIconSrc, this.value.offIconSrc);
        }
    }
}
TextInputPasswordIconModifier.identity = Symbol('textInputPasswordIcon');
class TextInputSelectedBackgroundColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetSelectedBackgroundColor(node);
        }
        else {
            GetUINativeModule().textInput.setSelectedBackgroundColor(node, this.value);
        }
    }
}
TextInputSelectedBackgroundColorModifier.identity = Symbol('textInputSelectedBackgroundColor');
class TextInputSelectionMenuHiddenModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetSelectionMenuHidden(node);
        }
        else {
            GetUINativeModule().textInput.setSelectionMenuHidden(node, this.value);
        }
    }
}
TextInputSelectionMenuHiddenModifier.identity = Symbol('textInputSelectionMenuHidden');
class TextInputShowUnderlineModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetShowUnderline(node);
        }
        else {
            GetUINativeModule().textInput.setShowUnderline(node, this.value);
        }
    }
}
TextInputShowUnderlineModifier.identity = Symbol('textInputShowUnderLine');
class TextInputShowErrorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetShowError(node);
        }
        else {
            GetUINativeModule().textInput.setShowError(node, this.value);
        }
    }
}
TextInputShowErrorModifier.identity = Symbol('textInputShowError');
class TextInputTypeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetType(node);
        }
        else {
            GetUINativeModule().textInput.setType(node, this.value);
        }
    }
}
TextInputTypeModifier.identity = Symbol('textInputType');
class TextInputCaretPositionModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetCaretPosition(node);
        }
        else {
            GetUINativeModule().textInput.setCaretPosition(node, this.value);
        }
    }
}
TextInputCaretPositionModifier.identity = Symbol('textInputCaretPosition');
class TextInputCopyOptionModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetCopyOption(node);
        }
        else {
            GetUINativeModule().textInput.setCopyOption(node, this.value);
        }
    }
}
TextInputCopyOptionModifier.identity = Symbol('textInputCopyOption');
class TextInputEnableKeyboardOnFocusModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetEnableKeyboardOnFocus(node);
        }
        else {
            GetUINativeModule().textInput.setEnableKeyboardOnFocus(node, this.value);
        }
    }
}
TextInputEnableKeyboardOnFocusModifier.identity = Symbol('textInputEnableKeyboardOnFocus');
class TextInputCaretStyleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetCaretStyle(node);
        }
        else {
            GetUINativeModule().textInput.setCaretStyle(node, this.value);
        }
    }
}
TextInputCaretStyleModifier.identity = Symbol('textInputCaretStyle');
class TextInputEnterKeyTypeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetEnterKeyType(node);
        }
        else {
            GetUINativeModule().textInput.setEnterKeyType(node, this.value);
        }
    }
}
TextInputEnterKeyTypeModifier.identity = Symbol('textInputEnterKeyType');
class TextInputBarStateModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetBarState(node);
        }
        else {
            GetUINativeModule().textInput.setBarState(node, this.value);
        }
    }
}
TextInputBarStateModifier.identity = Symbol('textInputBarState');
class TextInputCaretColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetCaretColor(node);
        }
        else {
            GetUINativeModule().textInput.setCaretColor(node, this.value);
        }
    }
}
TextInputCaretColorModifier.identity = Symbol('textinputCaretColor');
class TextInputFontColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetFontColor(node);
        }
        else {
            GetUINativeModule().textInput.setFontColor(node, this.value);
        }
    }
}
TextInputFontColorModifier.identity = Symbol('textInputFontColor');
class TextInputFontSizeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetFontSize(node);
        }
        else {
            GetUINativeModule().textInput.setFontSize(node, this.value);
        }
    }
}
TextInputFontSizeModifier.identity = Symbol('textInputFontSize');
class TextInputFontStyleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetFontStyle(node);
        }
        else {
            GetUINativeModule().textInput.setFontStyle(node, this.value);
        }
    }
}
TextInputFontStyleModifier.identity = Symbol('textInputFontStyle');
class TextInputFontWeightModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetFontWeight(node);
        }
        else {
            GetUINativeModule().textInput.setFontWeight(node, this.value);
        }
    }
}
TextInputFontWeightModifier.identity = Symbol('textInputFontWeight');
class TextInputFontFamilyModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textInput.resetFontFamily(node);
        }
        else {
            GetUINativeModule().textInput.setFontFamily(node, this.value);
        }
    }
}
TextInputFontFamilyModifier.identity = Symbol('textInputFontFamily');
class ArkTextInputComponent extends ArkComponent {
    cancelButton(value) {
        throw new Error('Method not implemented.');
    }
    onGestureJudgeBegin(callback) {
        throw new Error("Method not implemented.");
    }
    selectAll(value) {
        throw new Error('Method not implemented.');
    }
    enableAutoFill(value) {
        throw new Error('Method not implemented.');
    }
    passwordRules(value) {
        throw new Error('Method not implemented.');
    }
    showCounter(value) {
        throw new Error('Method not implemented.');
    }
    type(value) {
        if (value) {
            modifier(this._modifiers, TextInputTypeModifier, value);
        }
        else {
            modifier(this._modifiers, TextInputTypeModifier, undefined);
        }
        return this;
    }
    placeholderColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, TextInputPlaceholderColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, TextInputPlaceholderColorModifier, undefined);
        }
        return this;
    }
    placeholderFont(value) {
        let arkValue = new ArkFont();
        if (isLengthType(value.size)) {
            arkValue.size = value.size;
        }
        if (isLengthType(value.weight)) {
            arkValue.weight = value.weight;
        }
        if (isString(value.family)) {
            arkValue.family = value.family;
        }
        if (value.style in FontStyle) {
            arkValue.style = value.style;
        }
        modifier(this._modifiers, TextInputPlaceholderFontModifier, arkValue);
        return this;
    }
    enterKeyType(value) {
        if (value) {
            modifier(this._modifiers, TextInputEnterKeyTypeModifier, value);
        }
        else {
            modifier(this._modifiers, TextInputEnterKeyTypeModifier, EnterKeyType.Done);
        }
        return this;
    }
    caretColor(value) {
        if (isNumber(value) || isString(value)) {
            modifier(this._modifiers, TextInputCaretColorModifier, value);
        }
        else {
            modifier(this._modifiers, TextInputCaretColorModifier, undefined);
        }
        return this;
    }
    onEditChanged(callback) {
        throw new Error('Method not implemented.');
    }
    onEditChange(callback) {
        throw new Error('Method not implemented.');
    }
    onSubmit(callback) {
        throw new Error('Method not implemented.');
    }
    onChange(callback) {
        throw new Error('Method not implemented.');
    }
    onTextSelectionChange(callback) {
        throw new Error('Method not implemented.');
    }
    onContentScroll(callback) {
        throw new Error('Method not implemented.');
    }
    maxLength(value) {
        if (!isNumber(value) || value === undefined || value === null) {
            modifier(this._modifiers, TextInputMaxLengthModifier, undefined);
        }
        else {
            modifier(this._modifiers, TextInputMaxLengthModifier, value);
        }
        return this;
    }
    fontColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, TextInputFontColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, TextInputFontColorModifier, undefined);
        }
        return this;
    }
    fontSize(value) {
        if (isLengthType(value)) {
            let arkValue = value;
            modifier(this._modifiers, TextInputFontSizeModifier, arkValue);
        }
        else {
            modifier(this._modifiers, TextInputFontSizeModifier, undefined);
        }
        return this;
    }
    fontStyle(value) {
        if (!(value in FontStyle)) {
            value = FontStyle.Normal;
        }
        modifier(this._modifiers, TextInputFontStyleModifier, value);
        return this;
    }
    fontWeight(value) {
        if (!isLengthType(value)) {
            modifier(this._modifiers, TextInputFontWeightModifier, undefined);
        }
        else {
            modifier(this._modifiers, TextInputFontWeightModifier, value);
        }
        return this;
    }
    fontFamily(value) {
        if (!(isString(value))) {
            value = 'HarmonyOS Sans';
        }
        let arkValue = value;
        modifier(this._modifiers, TextInputFontFamilyModifier, arkValue);
        return this;
    }
    inputFilter(value, error) {
        throw new Error('Method not implemented.');
    }
    onCopy(callback) {
        throw new Error('Method not implemented.');
    }
    onCut(callback) {
        throw new Error('Method not implemented.');
    }
    onPaste(callback) {
        throw new Error('Method not implemented.');
    }
    copyOption(value) {
        if (!(value in CopyOptions)) {
            value = CopyOptions.LocalDevice;
        }
        modifier(this._modifiers, TextInputCopyOptionModifier, value);
        return this;
    }
    showPasswordIcon(value) {
        if (isBoolean(value)) {
            modifier(this._modifiers, TextInputShowPasswordIconModifier, value);
        }
        else {
            modifier(this._modifiers, TextInputShowPasswordIconModifier, undefined);
        }
        return this;
    }
    textAlign(value) {
        if (value) {
            modifier(this._modifiers, TextInputTextAlignModifier, value);
        }
        else {
            modifier(this._modifiers, TextInputTextAlignModifier, undefined);
        }
        return this;
    }
    style(value) {
        if (value) {
            modifier(this._modifiers, TextInputStyleModifier, value);
        }
        else {
            modifier(this._modifiers, TextInputStyleModifier, undefined);
        }
        return this;
    }
    caretStyle(value) {
        if (isUndefined(value)) {
            modifier(this._modifiers, TextInputCaretStyleModifier, undefined);
        }
        else if (isObject(value)) {
            if ((value.width !== undefined) && ((isNumber(value.width)) || (isString(value.width)))) {
                modifier(this._modifiers, TextInputCaretStyleModifier, value.width);
            }
            else {
                modifier(this._modifiers, TextInputCaretStyleModifier, undefined);
            }
        }
        return this;
    }
    selectedBackgroundColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, TextInputSelectedBackgroundColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, TextInputSelectedBackgroundColorModifier, undefined);
        }
        return this;
    }
    caretPosition(value) {
        modifier(this._modifiers, TextInputCaretPositionModifier, value);
        return this;
    }
    enableKeyboardOnFocus(value) {
        modifier(this._modifiers, TextInputEnableKeyboardOnFocusModifier, value);
        return this;
    }
    passwordIcon(value) {
        let passwordIcon = new ArkPasswordIcon();
        if (!value ||
            (!isString(value.onIconSrc) && !isString(value.onIconSrc))) {
            passwordIcon.offIconSrc = value.offIconSrc;
            passwordIcon.onIconSrc = value.onIconSrc;
            modifier(this._modifiers, TextInputPasswordIconModifier, passwordIcon);
            return this;
        }
        else {
            modifier(this._modifiers, TextInputPasswordIconModifier, undefined);
        }
        return this;
    }
    showError(value) {
        if (isString(value)) {
            modifier(this._modifiers, TextInputShowErrorModifier, value);
        }
        else {
            modifier(this._modifiers, TextInputShowErrorModifier, undefined);
        }
        return this;
    }
    showUnit(event) {
        throw new Error('Method not implemented.');
    }
    showUnderline(value) {
        if (isBoolean(value)) {
            modifier(this._modifiers, TextInputShowUnderlineModifier, value);
        }
        else {
            modifier(this._modifiers, TextInputShowUnderlineModifier, undefined);
        }
        return this;
    }
    selectionMenuHidden(value) {
        if (isBoolean(value)) {
            modifier(this._modifiers, TextInputSelectionMenuHiddenModifier, value);
        }
        else {
            modifier(this._modifiers, TextInputSelectionMenuHiddenModifier, undefined);
        }
        return this;
    }
    barState(value) {
        if (value) {
            modifier(this._modifiers, TextInputBarStateModifier, value);
        }
        else {
            modifier(this._modifiers, TextInputBarStateModifier, undefined);
        }
        return this;
    }
    maxLines(value) {
        if (typeof value === "number") {
            modifier(this._modifiers, TextInputMaxLinesModifier, value);
        }
        else {
            modifier(this._modifiers, TextInputMaxLinesModifier, undefined);
        }
        return this;
    }
    customKeyboard(event) {
        throw new Error('Method not implemented.');
    }
}
// @ts-ignore
globalThis.TextInput.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkTextInputComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkToggleComponent extends ArkComponent {
    onGestureJudgeBegin(callback) {
        throw new Error("Method not implemented.");
    }
    onChange(callback) {
        throw new Error("Method not implemented.");
    }
    selectedColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, ToggleSelectedColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, ToggleSelectedColorModifier, undefined);
        }
        return this;
    }
    switchPointColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, ToggleSwitchPointColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, ToggleSwitchPointColorModifier, undefined);
        }
        return this;
    }
}
class ToggleSelectedColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().toggle.resetSelectedColor(node);
        }
        else {
            GetUINativeModule().toggle.setSelectedColor(node, this.value);
        }
    }
}
ToggleSelectedColorModifier.identity = Symbol("toggleSelectedColor");
class ToggleSwitchPointColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().toggle.resetSwitchPointColor(node);
        }
        else {
            GetUINativeModule().toggle.setSwitchPointColor(node, this.value);
        }
    }
}
ToggleSwitchPointColorModifier.identity = Symbol("toggleSwitchPointColor");
// @ts-ignore
globalThis.Toggle.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkToggleComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkSelectComponent extends ArkComponent {
    onGestureJudgeBegin(callback) {
        throw new Error("Method not implemented.");
    }
    optionWidth(value) {
        throw new Error("Method not implemented.");
    }
    optionHeight(value) {
        throw new Error("Method not implemented.");
    }
    selected(value) {
        if (typeof value === "number") {
            modifier(this._modifiers, SelectedModifier, value);
        }
        else {
            modifier(this._modifiers, SelectedModifier, undefined);
        }
        return this;
    }
    value(value) {
        if (typeof value === "string") {
            modifier(this._modifiers, ValueModifier, value);
        }
        else {
            modifier(this._modifiers, ValueModifier, undefined);
        }
        return this;
    }
    font(value) {
        let font = new ArkFont();
        if (isObject(value)) {
            font.setSize(value.size);
            font.parseFontWeight(value.weight);
            font.setFamily(value.family);
            font.setStyle(value.style);
            modifier(this._modifiers, FontModifier, font);
        }
        else {
            modifier(this._modifiers, FontModifier, undefined);
        }
        return this;
    }
    fontColor(value) {
        if (isResource(value) || isUndefined(value)) {
            modifier(this._modifiers, SelectFontColorModifier, undefined);
            return this;
        }
        let arkColor = new ArkColor();
        if (!arkColor.parseColorValue(value)) {
            arkColor.parseColorValue("#E6FFFFFF");
        }
        modifier(this._modifiers, SelectFontColorModifier, arkColor.color);
        return this;
    }
    selectedOptionBgColor(value) {
        if (isResource(value) || isUndefined(value)) {
            modifier(this._modifiers, SelectedOptionBgColorModifier, undefined);
            return this;
        }
        let arkColor = new ArkColor();
        if (!arkColor.parseColorValue(value)) {
            arkColor.parseColorValue("#33007DFF");
        }
        modifier(this._modifiers, SelectedOptionBgColorModifier, arkColor.color);
        return this;
    }
    selectedOptionFont(value) {
        let font = new ArkFont();
        if (isObject(value)) {
            font.setSize(value.size);
            font.parseFontWeight(value.weight);
            font.setFamily(value.family);
            font.setStyle(value.style);
            modifier(this._modifiers, SelectedOptionFontModifier, font);
        }
        else {
            modifier(this._modifiers, SelectedOptionFontModifier, undefined);
        }
        return this;
    }
    selectedOptionFontColor(value) {
        if (isResource(value) || isUndefined(value)) {
            modifier(this._modifiers, SelectedOptionFontColorModifier, undefined);
            return this;
        }
        let arkColor = new ArkColor();
        if (!arkColor.parseColorValue(value)) {
            arkColor.parseColorValue("#ff007dff");
        }
        modifier(this._modifiers, SelectedOptionFontColorModifier, arkColor.color);
        return this;
    }
    optionBgColor(value) {
        if (isResource(value) || isUndefined(value)) {
            modifier(this._modifiers, OptionBgColorModifier, undefined);
            return this;
        }
        let arkColor = new ArkColor();
        if (!arkColor.parseColorValue(value)) {
            arkColor.parseColorValue("#ffffffff");
        }
        modifier(this._modifiers, OptionBgColorModifier, arkColor.color);
        return this;
    }
    optionFont(value) {
        let font = new ArkFont();
        if (isObject(value)) {
            font.setSize(value.size);
            font.parseFontWeight(value.weight);
            font.setFamily(value.family);
            font.setStyle(value.style);
            modifier(this._modifiers, OptionFontModifier, font);
        }
        else {
            modifier(this._modifiers, OptionFontModifier, undefined);
        }
        return this;
    }
    optionFontColor(value) {
        if (isResource(value) || isUndefined(value)) {
            modifier(this._modifiers, OptionFontColorModifier, undefined);
            return this;
        }
        let arkColor = new ArkColor();
        if (!arkColor.parseColorValue(value)) {
            arkColor.parseColorValue("#ffffffff");
        }
        modifier(this._modifiers, OptionFontColorModifier, arkColor.color);
        return this;
    }
    onSelect(callback) {
        throw new Error("Method not implemented.");
    }
    space(value) {
        if (typeof value !== "number" && typeof value !== "string") {
            modifier(this._modifiers, SpaceModifier, undefined);
        }
        else {
            modifier(this._modifiers, SpaceModifier, value);
        }
        return this;
    }
    arrowPosition(value) {
        if (isNumber(value)) {
            modifier(this._modifiers, ArrowPositionModifier, value);
        }
        else {
            modifier(this._modifiers, ArrowPositionModifier, undefined);
        }
        return this;
    }
    menuAlign(alignType, offset) {
        let menuAlignType = new ArkMenuAlignType();
        if (isNumber(alignType)) {
            menuAlignType.alignType = alignType;
            if (typeof offset === "object") {
                menuAlignType.dx = offset.dx;
                menuAlignType.dy = offset.dy;
            }
            modifier(this._modifiers, MenuAlignModifier, menuAlignType);
        }
        else {
            modifier(this._modifiers, MenuAlignModifier, undefined);
        }
        return this;
    }
}
// @ts-ignore
globalThis.Select.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkSelectComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
class FontModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().select.resetFont(node);
        }
        else {
            GetUINativeModule().select.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
    }
}
FontModifier.identity = Symbol("selectFont");
class OptionFontModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().select.resetOptionFont(node);
        }
        else {
            GetUINativeModule().select.setOptionFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
    }
}
OptionFontModifier.identity = Symbol("selectOptionFont");
class SelectedOptionFontModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().select.resetSelectedOptionFont(node);
        }
        else {
            GetUINativeModule().select.setSelectedOptionFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
    }
}
SelectedOptionFontModifier.identity = Symbol("selectSelectedOptionFont");
class MenuAlignModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().select.resetMenuAlign(node);
        }
        else {
            GetUINativeModule().select.setMenuAlign(node, this.value.alignType, this.value.dx, this.value.dy);
        }
    }
}
MenuAlignModifier.identity = Symbol("selectMenuAlign");
class ArrowPositionModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().select.resetArrowPosition(node);
        }
        else {
            GetUINativeModule().select.setArrowPosition(node, this.value);
        }
    }
}
ArrowPositionModifier.identity = Symbol("selectArrowPosition");
class SpaceModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().select.resetSpace(node);
        }
        else {
            GetUINativeModule().select.setSpace(node, this.value);
        }
    }
}
SpaceModifier.identity = Symbol("selectSpace");
class ValueModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().select.resetValue(node);
        }
        else {
            GetUINativeModule().select.setValue(node, this.value);
        }
    }
}
ValueModifier.identity = Symbol("selectValue");
class SelectedModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().select.resetSelected(node);
        }
        else {
            GetUINativeModule().select.setSelected(node, this.value);
        }
    }
}
SelectedModifier.identity = Symbol("selectSelected");
class SelectFontColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().select.resetFontColor(node);
        }
        else {
            GetUINativeModule().select.setFontColor(node, this.value);
        }
    }
}
SelectFontColorModifier.identity = Symbol("selectFontColor");
class SelectedOptionBgColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().select.resetSelectedOptionBgColor(node);
        }
        else {
            GetUINativeModule().select.setSelectedOptionBgColor(node, this.value);
        }
    }
}
SelectedOptionBgColorModifier.identity = Symbol("selectSelectedOptionBgColor");
class OptionBgColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().select.resetOptionBgColor(node);
        }
        else {
            GetUINativeModule().select.setOptionBgColor(node, this.value);
        }
    }
}
OptionBgColorModifier.identity = Symbol("selectOptionBgColor");
class OptionFontColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().select.resetOptionFontColor(node);
        }
        else {
            GetUINativeModule().select.setOptionFontColor(node, this.value);
        }
    }
}
OptionFontColorModifier.identity = Symbol("selectOptionFontColor");
class SelectedOptionFontColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().select.resetSelectedOptionFontColor(node);
        }
        else {
            GetUINativeModule().select.setSelectedOptionFontColor(node, this.value);
        }
    }
}
SelectedOptionFontColorModifier.identity = Symbol("selectSelectedOptionFontColor");
/// <reference path="./import.ts" />
class ArkRadioComponent extends ArkComponent {
    onGestureJudgeBegin(callback) {
        throw new Error("Method not implemented.");
    }
    checked(value) {
        if (!!value) {
            modifier(this._modifiers, RadioCheckedModifier, value);
        }
        else {
            modifier(this._modifiers, RadioCheckedModifier, undefined);
        }
        return this;
    }
    onChange(callback) {
        throw new Error("Method not implemented.");
    }
    radioStyle(value) {
        let arkRadioStyle = new ArkRadioStyle();
        let getColor = new ArkColor();
        if (typeof value === "object") {
            if (getColor.parseColorValue(value === null || value === void 0 ? void 0 : value.checkedBackgroundColor)) {
                arkRadioStyle.checkedBackgroundColor = getColor.getColor();
            }
            if (getColor.parseColorValue(value === null || value === void 0 ? void 0 : value.uncheckedBorderColor)) {
                arkRadioStyle.uncheckedBorderColor = getColor.getColor();
            }
            if (getColor.parseColorValue(value === null || value === void 0 ? void 0 : value.indicatorColor)) {
                arkRadioStyle.indicatorColor = getColor.getColor();
            }
            modifier(this._modifiers, RadioStyleModifier, arkRadioStyle);
        }
        else {
            modifier(this._modifiers, RadioStyleModifier, undefined);
        }
        return this;
    }
}
class RadioCheckedModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().radio.resetRadioChecked(node);
        }
        else {
            GetUINativeModule().radio.setRadioChecked(node, this.value);
        }
    }
}
RadioCheckedModifier.identity = Symbol("radioChecked");
class RadioStyleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().radio.resetRadioStyle(node);
        }
        else {
            GetUINativeModule().radio.setRadioStyle(node, this.value.checkedBackgroundColor, this.value.uncheckedBorderColor, this.value.indicatorColor);
        }
    }
}
RadioStyleModifier.identity = Symbol("radioStyle");
// @ts-ignore
globalThis.Radio.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkRadioComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkTimePickerComponent extends ArkComponent {
    onGestureJudgeBegin(callback) {
        throw new Error("Method not implemented.");
    }
    loop(value) {
        throw new Error("Method not implemented.");
    }
    useMilitaryTime(value) {
        throw new Error("Method not implemented.");
    }
    disappearTextStyle(value) {
        let textStyle = new ArkTextStyle();
        if (isObject(value)) {
            textStyle.parseTextStyle(value, '#ff182431', '14fp', 'Regular');
            modifier(this._modifiers, TimepickerDisappearTextStyleModifier, textStyle);
        }
        else {
            modifier(this._modifiers, TimepickerDisappearTextStyleModifier, undefined);
        }
        return this;
    }
    textStyle(value) {
        let textStyle = new ArkTextStyle();
        if (isObject(value)) {
            textStyle.parseTextStyle(value, '#ff182431', '16fp', 'Regular');
            modifier(this._modifiers, TimepickerTextStyleModifier, textStyle);
        }
        else {
            modifier(this._modifiers, TimepickerTextStyleModifier, undefined);
        }
        return this;
    }
    selectedTextStyle(value) {
        let textStyle = new ArkTextStyle();
        if (isObject(value)) {
            textStyle.parseTextStyle(value, '#ff007dff', '20vp', 'Medium');
            modifier(this._modifiers, TimepickerSelectedTextStyleModifier, textStyle);
        }
        else {
            modifier(this._modifiers, TimepickerSelectedTextStyleModifier, undefined);
        }
        return this;
    }
    onChange(callback) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.TimePicker.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkTimePickerComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
class TimepickerTextStyleModifier extends Modifier {
    applyPeer(node, reset) {
        var _a, _b, _c, _d;
        if (reset) {
            GetUINativeModule().timepicker.resetTextStyle(node);
        }
        else {
            GetUINativeModule().timepicker.setTextStyle(node, this.value.color, (_a = this.value.font) === null || _a === void 0 ? void 0 : _a.size, (_b = this.value.font) === null || _b === void 0 ? void 0 : _b.weight, (_c = this.value.font) === null || _c === void 0 ? void 0 : _c.family, (_d = this.value.font) === null || _d === void 0 ? void 0 : _d.style);
        }
    }
}
TimepickerTextStyleModifier.identity = Symbol("textStyle");
class TimepickerSelectedTextStyleModifier extends Modifier {
    applyPeer(node, reset) {
        var _a, _b, _c, _d;
        if (reset) {
            GetUINativeModule().timepicker.resetSelectedTextStyle(node);
        }
        else {
            GetUINativeModule().timepicker.setSelectedTextStyle(node, this.value.color, (_a = this.value.font) === null || _a === void 0 ? void 0 : _a.size, (_b = this.value.font) === null || _b === void 0 ? void 0 : _b.weight, (_c = this.value.font) === null || _c === void 0 ? void 0 : _c.family, (_d = this.value.font) === null || _d === void 0 ? void 0 : _d.style);
        }
    }
}
TimepickerSelectedTextStyleModifier.identity = Symbol("selectedTextStyle");
class TimepickerDisappearTextStyleModifier extends Modifier {
    applyPeer(node, reset) {
        var _a, _b, _c, _d;
        if (reset) {
            GetUINativeModule().timepicker.resetDisappearTextStyle(node);
        }
        else {
            GetUINativeModule().timepicker.setDisappearTextStyle(node, this.value.color, (_a = this.value.font) === null || _a === void 0 ? void 0 : _a.size, (_b = this.value.font) === null || _b === void 0 ? void 0 : _b.weight, (_c = this.value.font) === null || _c === void 0 ? void 0 : _c.family, (_d = this.value.font) === null || _d === void 0 ? void 0 : _d.style);
        }
    }
}
TimepickerDisappearTextStyleModifier.identity = Symbol("disappearTextStyle");
/// <reference path="./import.ts" />
class ArkTextPickerComponent extends ArkComponent {
    onGestureJudgeBegin(callback) {
        throw new Error("Method not implemented.");
    }
    defaultPickerItemHeight(value) {
        if (typeof value !== "number" && typeof value !== "string") {
            modifier(this._modifiers, TextpickerDefaultPickerItemHeightModifier, undefined);
        }
        else {
            modifier(this._modifiers, TextpickerDefaultPickerItemHeightModifier, value);
        }
        return this;
    }
    canLoop(value) {
        if (typeof value === "boolean") {
            modifier(this._modifiers, TextpickerCanLoopModifier, value);
        }
        else {
            modifier(this._modifiers, TextpickerCanLoopModifier, undefined);
        }
        return this;
    }
    disappearTextStyle(value) {
        let disappearTextStyle = new ArkTextStyle();
        if (isObject(value)) {
            disappearTextStyle.parseTextStyle(value, '#ff182431', '14fp', 'Regular');
            modifier(this._modifiers, TextpickerDisappearTextStyleModifier, disappearTextStyle);
        }
        else {
            modifier(this._modifiers, TextpickerDisappearTextStyleModifier, undefined);
        }
        return this;
    }
    textStyle(value) {
        let textStyle = new ArkTextStyle();
        if (isObject(value)) {
            textStyle.parseTextStyle(value, '#ff182431', '16fp', 'Regular');
            modifier(this._modifiers, TextpickerTextStyleModifier, textStyle);
        }
        else {
            modifier(this._modifiers, TextpickerTextStyleModifier, undefined);
        }
        return this;
    }
    selectedTextStyle(value) {
        let textStyle = new ArkTextStyle();
        if (isObject(value)) {
            textStyle.parseTextStyle(value, '#ff007dff', '20vp', 'Medium');
            modifier(this._modifiers, TextpickerSelectedTextStyleModifier, textStyle);
        }
        else {
            modifier(this._modifiers, TextpickerSelectedTextStyleModifier, undefined);
        }
        return this;
    }
    onAccept(callback) {
        throw new Error("Method not implemented.");
    }
    onCancel(callback) {
        throw new Error("Method not implemented.");
    }
    onChange(callback) {
        throw new Error("Method not implemented.");
    }
    selectedIndex(value) {
        let input = new ArkSelectedIndices();
        if (!Array.isArray(value)) {
            if (!isNumber(value)) {
                modifier(this._modifiers, TextpickerSelectedIndexModifier, undefined);
                return this;
            }
            input.selectedValues[0] = value;
        }
        else {
            input.selectedValues = value;
        }
        modifier(this._modifiers, TextpickerSelectedIndexModifier, input);
        return this;
    }
}
// @ts-ignore
globalThis.TextPicker.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkTextPickerComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
class TextpickerCanLoopModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textpicker.resetCanLoop(node);
        }
        else {
            GetUINativeModule().textpicker.setCanLoop(node, this.value);
        }
    }
}
TextpickerCanLoopModifier.identity = Symbol("textpickerCanLoop");
class TextpickerSelectedIndexModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textpicker.resetSelectedIndex(node);
        }
        else {
            GetUINativeModule().textpicker.setSelectedIndex(node, this.value.selectedValues);
        }
    }
}
TextpickerSelectedIndexModifier.identity = Symbol("textpickerSelectedIndex");
class TextpickerTextStyleModifier extends Modifier {
    applyPeer(node, reset) {
        var _a, _b, _c, _d;
        if (reset) {
            GetUINativeModule().textpicker.resetTextStyle(node);
        }
        else {
            GetUINativeModule().textpicker.setTextStyle(node, this.value.color, (_a = this.value.font) === null || _a === void 0 ? void 0 : _a.size, (_b = this.value.font) === null || _b === void 0 ? void 0 : _b.weight, (_c = this.value.font) === null || _c === void 0 ? void 0 : _c.family, (_d = this.value.font) === null || _d === void 0 ? void 0 : _d.style);
        }
    }
}
TextpickerTextStyleModifier.identity = Symbol("textpickerTextStyle");
class TextpickerSelectedTextStyleModifier extends Modifier {
    applyPeer(node, reset) {
        var _a, _b, _c, _d;
        if (reset) {
            GetUINativeModule().textpicker.resetSelectedTextStyle(node);
        }
        else {
            GetUINativeModule().textpicker.setSelectedTextStyle(node, this.value.color, (_a = this.value.font) === null || _a === void 0 ? void 0 : _a.size, (_b = this.value.font) === null || _b === void 0 ? void 0 : _b.weight, (_c = this.value.font) === null || _c === void 0 ? void 0 : _c.family, (_d = this.value.font) === null || _d === void 0 ? void 0 : _d.style);
        }
    }
}
TextpickerSelectedTextStyleModifier.identity = Symbol("textpickerSelectedTextStyle");
class TextpickerDefaultPickerItemHeightModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().textpicker.resetDefaultPickerItemHeight(node);
        }
        else {
            GetUINativeModule().textpicker.setDefaultPickerItemHeight(node, this.value);
        }
    }
}
TextpickerDefaultPickerItemHeightModifier.identity = Symbol("textpickerDefaultPickerItemHeight");
class TextpickerDisappearTextStyleModifier extends Modifier {
    applyPeer(node, reset) {
        var _a, _b, _c, _d;
        if (reset) {
            GetUINativeModule().textpicker.resetDisappearTextStyle(node);
        }
        else {
            GetUINativeModule().textpicker.setDisappearTextStyle(node, this.value.color, (_a = this.value.font) === null || _a === void 0 ? void 0 : _a.size, (_b = this.value.font) === null || _b === void 0 ? void 0 : _b.weight, (_c = this.value.font) === null || _c === void 0 ? void 0 : _c.family, (_d = this.value.font) === null || _d === void 0 ? void 0 : _d.style);
        }
    }
}
TextpickerDisappearTextStyleModifier.identity = Symbol("textpickerDisappearTextStyle");
/// <reference path="./import.ts" />
class ArkSliderComponent extends ArkComponent {
    onGestureJudgeBegin(callback) {
        throw new Error("Method not implemented.");
    }
    blockColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, BlockColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, BlockColorModifier, undefined);
        }
        return this;
    }
    trackColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, TrackColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, TrackColorModifier, undefined);
        }
        return this;
    }
    selectedColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, SelectColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, SelectColorModifier, undefined);
        }
        return this;
    }
    minLabel(value) {
        throw new Error("Method not implemented.");
    }
    maxLabel(value) {
        throw new Error("Method not implemented.");
    }
    showSteps(value) {
        let showSteps = false;
        if (typeof value === "boolean") {
            modifier(this._modifiers, ShowStepsModifier, value);
        }
        else {
            modifier(this._modifiers, ShowStepsModifier, showSteps);
        }
        return this;
        ;
    }
    showTips(value, content) {
        let showTips = new ArkSliderTips();
        if (typeof value === "boolean") {
            showTips.showTip = value;
        }
        if (typeof content === "string") {
            showTips.tipText = content;
        }
        modifier(this._modifiers, ShowTipsModifier, showTips);
        return this;
    }
    trackThickness(value) {
        if (typeof value !== "number" && typeof value !== "string") {
            modifier(this._modifiers, TrackThicknessModifier, undefined);
        }
        else {
            modifier(this._modifiers, TrackThicknessModifier, value);
        }
        return this;
    }
    onChange(callback) {
        throw new Error("Method not implemented.");
    }
    blockBorderColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, BlockBorderColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, BlockBorderColorModifier, undefined);
        }
        return this;
    }
    blockBorderWidth(value) {
        if (typeof value !== "number" && typeof value !== "string") {
            modifier(this._modifiers, BlockBorderWidthModifier, undefined);
        }
        else {
            modifier(this._modifiers, BlockBorderWidthModifier, value);
        }
        return this;
    }
    stepColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, StepColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, StepColorModifier, undefined);
        }
        return this;
    }
    trackBorderRadius(value) {
        if (typeof value !== "number" && typeof value !== "string") {
            modifier(this._modifiers, TrackBorderRadiusModifier, undefined);
        }
        else {
            modifier(this._modifiers, TrackBorderRadiusModifier, value);
        }
        return this;
    }
    blockSize(value) {
        if (!value || (!!(value === null || value === void 0 ? void 0 : value.width) && typeof (value === null || value === void 0 ? void 0 : value.width) != "number" && typeof (value === null || value === void 0 ? void 0 : value.width) != "string") ||
            (!!(value === null || value === void 0 ? void 0 : value.height) && typeof (value === null || value === void 0 ? void 0 : value.height) != "number" && typeof (value === null || value === void 0 ? void 0 : value.height) != "string")) {
            modifier(this._modifiers, BlockSizeModifier, undefined);
        }
        else {
            let blockSize = new ArkBlockSize();
            blockSize.width = value === null || value === void 0 ? void 0 : value.width;
            blockSize.height = value === null || value === void 0 ? void 0 : value.height;
            modifier(this._modifiers, BlockSizeModifier, blockSize);
        }
        return this;
    }
    blockStyle(value) {
        modifierWithKey(this._modifiersWithKeys, BlockStyleModifier.identity, BlockStyleModifier, value);
        return this;
    }
    stepSize(value) {
        if (typeof value !== "number" && typeof value !== "string") {
            modifier(this._modifiers, StepSizeModifier, undefined);
        }
        else {
            modifier(this._modifiers, StepSizeModifier, value);
        }
        return this;
    }
}
// @ts-ignore
globalThis.Slider.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkSliderComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
class BlockStyleModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().slider.resetBlockStyle(node);
        }
        else {
            GetUINativeModule().slider.setBlockStyle(node, this.value);
        }
    }
    checkObjectDiff() {
        return false;
    }
}
BlockStyleModifier.identity = Symbol("sliderBlockStyle");
class ShowTipsModifier extends Modifier {
    applyPeer(node, reset) {
        var _a;
        if (reset) {
            GetUINativeModule().slider.resetShowTips(node);
        }
        else {
            GetUINativeModule().slider.setShowTips(node, this.value.showTip, (_a = this.value) === null || _a === void 0 ? void 0 : _a.tipText);
        }
    }
}
ShowTipsModifier.identity = Symbol("sliderShowTips");
class StepSizeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().slider.resetStepSize(node);
        }
        else {
            GetUINativeModule().slider.setStepSize(node, this.value);
        }
    }
}
StepSizeModifier.identity = Symbol("sliderStepSize");
class BlockSizeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().slider.resetBlockSize(node);
        }
        else {
            GetUINativeModule().slider.setBlockSize(node, this.value.width, this.value.height);
        }
    }
}
BlockSizeModifier.identity = Symbol("sliderBlockSize");
class TrackBorderRadiusModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().slider.resetTrackBorderRadius(node);
        }
        else {
            GetUINativeModule().slider.setTrackBorderRadius(node, this.value);
        }
    }
}
TrackBorderRadiusModifier.identity = Symbol("sliderTrackBorderRadius");
class StepColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().slider.resetStepColor(node);
        }
        else {
            GetUINativeModule().slider.setStepColor(node, this.value);
        }
    }
}
StepColorModifier.identity = Symbol("sliderStepColor");
class BlockBorderColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().slider.resetBlockBorderColor(node);
        }
        else {
            GetUINativeModule().slider.setBlockBorderColor(node, this.value);
        }
    }
}
BlockBorderColorModifier.identity = Symbol("sliderBlockBorderColor");
class BlockBorderWidthModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().slider.resetBlockBorderWidth(node);
        }
        else {
            GetUINativeModule().slider.setBlockBorderWidth(node, this.value);
        }
    }
}
BlockBorderWidthModifier.identity = Symbol("sliderBlockBorderWidth");
class BlockColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().slider.resetBlockColor(node);
        }
        else {
            GetUINativeModule().slider.setBlockColor(node, this.value);
        }
    }
}
BlockColorModifier.identity = Symbol("sliderBlockColor");
class TrackColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().slider.resetTrackBackgroundColor(node);
        }
        else {
            GetUINativeModule().slider.setTrackBackgroundColor(node, this.value);
        }
    }
}
TrackColorModifier.identity = Symbol("sliderTrackColor");
class SelectColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().slider.resetSelectColor(node);
        }
        else {
            GetUINativeModule().slider.setSelectColor(node, this.value);
        }
    }
}
SelectColorModifier.identity = Symbol("sliderSelectColor");
class ShowStepsModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().slider.resetShowSteps(node);
        }
        else {
            GetUINativeModule().slider.setShowSteps(node, this.value);
        }
    }
}
ShowStepsModifier.identity = Symbol("sliderShowSteps");
class TrackThicknessModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().slider.resetThickness(node);
        }
        else {
            GetUINativeModule().slider.setThickness(node, this.value);
        }
    }
}
TrackThicknessModifier.identity = Symbol("sliderTrackThickness");
/// <reference path="./import.ts" />
class RatingStarsModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().rating.resetStars(node);
        }
        else {
            GetUINativeModule().rating.setStars(node, this.value);
        }
    }
}
RatingStarsModifier.identity = Symbol("ratingStars");
class RatingStepSizeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().rating.resetStepSize(node);
        }
        else {
            GetUINativeModule().rating.setStepSize(node, this.value);
        }
    }
}
RatingStepSizeModifier.identity = Symbol("ratingStepSize");
class RatingStarStyleModifier extends Modifier {
    applyPeer(node, reset) {
        var _a, _b, _c;
        if (reset) {
            GetUINativeModule().rating.resetStarStyle(node);
        }
        else {
            GetUINativeModule().rating.setStarStyle(node, (_a = this.value) === null || _a === void 0 ? void 0 : _a.backgroundUri, (_b = this.value) === null || _b === void 0 ? void 0 : _b.foregroundUri, (_c = this.value) === null || _c === void 0 ? void 0 : _c.secondaryUri);
        }
    }
}
RatingStarStyleModifier.identity = Symbol("ratingStarStyle");
class ArkRatingComponent extends ArkComponent {
    onGestureJudgeBegin(callback) {
        throw new Error("Method not implemented.");
    }
    stars(value) {
        if (isUndefined(value)) {
            modifier(this._modifiers, RatingStarsModifier, value);
        }
        else {
            modifier(this._modifiers, RatingStarsModifier, undefined);
        }
        return this;
    }
    stepSize(value) {
        if (isNumber(value)) {
            modifier(this._modifiers, RatingStepSizeModifier, value);
        }
        else {
            modifier(this._modifiers, RatingStepSizeModifier, undefined);
        }
        return this;
    }
    starStyle(value) {
        let starStyle = new ArkStarStyle();
        if (!isUndefined(value)) {
            starStyle.backgroundUri = value.backgroundUri;
            starStyle.foregroundUri = value.foregroundUri;
            starStyle.secondaryUri = value.secondaryUri;
            modifier(this._modifiers, RatingStarStyleModifier, starStyle);
        }
        else {
            modifier(this._modifiers, RatingStarStyleModifier, undefined);
        }
        return this;
    }
    onChange(callback) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Rating.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkRatingComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkCheckboxComponent extends ArkComponent {
    shape(value) {
        throw new Error("Method not implemented.");
    }
    select(value) {
        if (!isUndefined(value)) {
            modifier(this._modifiers, CheckboxSelectModifier, value);
        }
        else {
            modifier(this._modifiers, CheckboxSelectModifier, undefined);
        }
        return this;
    }
    selectedColor(value) {
        if (isResource(value)) {
            modifier(this._modifiers, CheckboxSelectedColorModifier, undefined);
            return this;
        }
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, CheckboxSelectedColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, CheckboxSelectedColorModifier, undefined);
        }
        return this;
    }
    unselectedColor(value) {
        if (isResource(value)) {
            modifier(this._modifiers, CheckboxUnselectedColorModifier, undefined);
            return this;
        }
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, CheckboxUnselectedColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, CheckboxUnselectedColorModifier, undefined);
        }
        return this;
    }
    mark(value) {
        let arkMarkStyle = new ArkMarkStyle();
        if (arkMarkStyle.parseMarkStyle(value)) {
            modifier(this._modifiers, CheckboxMarkModifier, arkMarkStyle);
        }
        else {
            modifier(this._modifiers, CheckboxMarkModifier, undefined);
        }
        return this;
    }
    onChange(callback) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Checkbox.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkCheckboxComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
class CheckboxMarkModifier extends Modifier {
    applyPeer(node, reset) {
        var _a, _b, _c;
        if (reset) {
            GetUINativeModule().checkbox.resetMark(node);
        }
        else {
            GetUINativeModule().checkbox.setMark(node, (_a = this.value) === null || _a === void 0 ? void 0 : _a.strokeColor, (_b = this.value) === null || _b === void 0 ? void 0 : _b.size, (_c = this.value) === null || _c === void 0 ? void 0 : _c.strokeWidth);
        }
    }
}
CheckboxMarkModifier.identity = Symbol("checkboxMark");
class CheckboxSelectModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().checkbox.resetSelect(node);
        }
        else {
            GetUINativeModule().checkbox.setSelect(node, this.value);
        }
    }
}
CheckboxSelectModifier.identity = Symbol("checkboxSelect");
class CheckboxSelectedColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().checkbox.resetSelectedColor(node);
        }
        else {
            GetUINativeModule().checkbox.setSelectedColor(node, this.value);
        }
    }
}
CheckboxSelectedColorModifier.identity = Symbol("checkboxSelectedColor");
class CheckboxUnselectedColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().checkbox.resetUnSelectedColor(node);
        }
        else {
            GetUINativeModule().checkbox.setUnSelectedColor(node, this.value);
        }
    }
}
CheckboxUnselectedColorModifier.identity = Symbol("checkboxUnselectedColor");
/// <reference path="./import.ts" />
class DividerVerticalModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().divider.resetVertical(node);
        }
        else {
            GetUINativeModule().divider.setVertical(node, this.value);
        }
    }
}
DividerVerticalModifier.identity = Symbol('dividerVertical');
class DividerLineCapModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().divider.resetLineCap(node);
        }
        else {
            GetUINativeModule().divider.setLineCap(node, this.value);
        }
    }
}
DividerLineCapModifier.identity = Symbol('dividerLineCap');
class DividerColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().divider.resetDividerColor(node);
        }
        else {
            GetUINativeModule().divider.setDividerColor(node, this.value);
        }
    }
}
DividerColorModifier.identity = Symbol('dividerColor');
class DividerStrokeWidthModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().divider.resetStrokeWidth(node);
        }
        else {
            GetUINativeModule().divider.setStrokeWidth(node, this.value);
        }
    }
}
DividerStrokeWidthModifier.identity = Symbol('dividerStrokeWidth');
class ArkDividerComponent extends ArkComponent {
    vertical(value) {
        if (value === null || value === undefined) {
            modifier(this._modifiers, DividerVerticalModifier, undefined);
        }
        else {
            modifier(this._modifiers, DividerVerticalModifier, value);
        }
        return this;
    }
    color(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, DividerColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, DividerColorModifier, undefined);
        }
        return this;
    }
    strokeWidth(value) {
        if (!isNumber(value) || !isString(value)) {
            modifier(this._modifiers, DividerStrokeWidthModifier, undefined);
        }
        else {
            modifier(this._modifiers, DividerStrokeWidthModifier, value);
        }
        return this;
    }
    lineCap(value) {
        if (value) {
            modifier(this._modifiers, DividerLineCapModifier, value);
        }
        else {
            modifier(this._modifiers, DividerLineCapModifier, LineCapStyle.Butt);
        }
        return this;
    }
}
// @ts-ignore
globalThis.Divider.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkDividerComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkNavDestinationComponent extends ArkComponent {
    title(value) {
        throw new Error("Method not implemented.");
    }
    hideTitleBar(value) {
        modifier(this._modifiers, HideTitleBarModifier, value);
        return this;
    }
    onShown(callback) {
        throw new Error("Method not implemented.");
    }
    onHidden(callback) {
        throw new Error("Method not implemented.");
    }
    onBackPressed(callback) {
        throw new Error("Method not implemented.");
    }
}
class HideTitleBarModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().navDestination.resetHideTitleBar(node);
        }
        else {
            GetUINativeModule().navDestination.setHideTitleBar(node, this.value);
        }
    }
}
HideTitleBarModifier.identity = Symbol("hideTitleBar");
//@ts-ignore
globalThis.NavDestination.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkNavDestinationComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkCounterComponent extends ArkComponent {
    onInc(event) {
        throw new Error("Method not implemented.");
    }
    onDec(event) {
        throw new Error("Method not implemented.");
    }
    enableDec(value) {
        if (typeof value === "boolean") {
            modifier(this._modifiers, EnableDecModifier, value);
        }
        else {
            modifier(this._modifiers, EnableDecModifier, undefined);
        }
        return this;
    }
    enableInc(value) {
        if (typeof value === "boolean") {
            modifier(this._modifiers, EnableIncModifier, value);
        }
        else {
            modifier(this._modifiers, EnableIncModifier, undefined);
        }
        return this;
    }
}
// @ts-ignore
globalThis.Counter.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkCounterComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
class EnableIncModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().counter.resetEnableInc(node);
        }
        else {
            GetUINativeModule().counter.setEnableInc(node, this.value);
        }
    }
}
EnableIncModifier.identity = Symbol("enableInc");
class EnableDecModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().counter.resetEnableDec(node);
        }
        else {
            GetUINativeModule().counter.setEnableDec(node, this.value);
        }
    }
}
EnableDecModifier.identity = Symbol("enableDec");
/// <reference path="./ArkViewStackProcessor.ts" />
class CheckboxGroupSelectAllModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().checkboxgroup.resetSelectAll(node);
        }
        else {
            GetUINativeModule().checkboxgroup.setSelectAll(node, this.value);
        }
    }
}
CheckboxGroupSelectAllModifier.identity = Symbol("checkboxgroupSelectAll");
class CheckboxGroupSelectedColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().checkboxgroup.resetSelectedColor(node);
        }
        else {
            GetUINativeModule().checkboxgroup.setSelectedColor(node, this.value);
        }
    }
}
CheckboxGroupSelectedColorModifier.identity = Symbol("checkboxgroupSelectedColor");
class CheckboxGroupUnselectedColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().checkboxgroup.resetUnSelectedColor(node);
        }
        else {
            GetUINativeModule().checkboxgroup.setUnSelectedColor(node, this.value);
        }
    }
}
CheckboxGroupUnselectedColorModifier.identity = Symbol("checkboxgroupUnselectedColor");
class CheckboxGroupMarkModifier extends Modifier {
    applyPeer(node, reset) {
        var _a, _b, _c;
        if (reset) {
            GetUINativeModule().checkboxgroup.resetMark(node);
        }
        else {
            GetUINativeModule().checkboxgroup.setMark(node, (_a = this.value) === null || _a === void 0 ? void 0 : _a.strokeColor, (_b = this.value) === null || _b === void 0 ? void 0 : _b.size, (_c = this.value) === null || _c === void 0 ? void 0 : _c.strokeWidth);
        }
    }
}
CheckboxGroupMarkModifier.identity = Symbol("checkboxgroupMark");
class ArkCheckboxGroupComponent extends ArkComponent {
    selectAll(value) {
        if (typeof value === "boolean") {
            modifier(this._modifiers, CheckboxGroupSelectAllModifier, value);
        }
        else {
            modifier(this._modifiers, CheckboxGroupSelectAllModifier, undefined);
        }
        return this;
    }
    selectedColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, CheckboxGroupSelectedColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, CheckboxGroupSelectedColorModifier, undefined);
        }
        return this;
    }
    unselectedColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, CheckboxGroupUnselectedColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, CheckboxGroupUnselectedColorModifier, undefined);
        }
        return this;
    }
    mark(value) {
        let arkMarkStyle = new ArkMarkStyle();
        if (arkMarkStyle.parseMarkStyle(value)) {
            modifier(this._modifiers, CheckboxGroupMarkModifier, arkMarkStyle);
        }
        else {
            modifier(this._modifiers, CheckboxGroupMarkModifier, undefined);
        }
        return this;
    }
    onChange(callback) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.CheckboxGroup.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkCheckboxGroupComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class GridColSpanModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().gridCol.resetSpan(node);
        }
        else {
            GetUINativeModule().gridCol.setSpan(node, this.value.xs, this.value.sm, this.value.md, this.value.lg, this.value.xl, this.value.xxl);
        }
    }
}
GridColSpanModifier.identity = Symbol('gridColSpan');
class GridColOffsetModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().gridCol.resetGridColOffset(node);
        }
        else {
            GetUINativeModule().gridCol.setGridColOffset(node, this.value.xs, this.value.sm, this.value.md, this.value.lg, this.value.xl, this.value.xxl);
        }
    }
}
GridColOffsetModifier.identity = Symbol('gridColOffset');
class GridColOrderModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().gridCol.resetOrder(node);
        }
        else {
            GetUINativeModule().gridCol.setOrder(node, this.value.xs, this.value.sm, this.value.md, this.value.lg, this.value.xl, this.value.xxl);
        }
    }
}
GridColOrderModifier.identity = Symbol('gridColOrder');
class ArkGridColComponent extends ArkComponent {
    span(value) {
        modifier(this._modifiers, GridColSpanModifier, this.parserGridColColumnOption(value, 1));
        return this;
    }
    gridColOffset(value) {
        modifier(this._modifiers, GridColOffsetModifier, this.parserGridColColumnOption(value, 0));
        return this;
    }
    order(value) {
        modifier(this._modifiers, GridColOrderModifier, this.parserGridColColumnOption(value, 0));
        return this;
    }
    parserGridColColumnOption(jsValue, defaultVal) {
        let gridColColumnOption = new ArkGridColColumnOption();
        if (jsValue === null || jsValue === undefined) {
            gridColColumnOption.xs = defaultVal;
            gridColColumnOption.sm = defaultVal;
            gridColColumnOption.md = defaultVal;
            gridColColumnOption.lg = defaultVal;
            gridColColumnOption.xl = defaultVal;
            gridColColumnOption.xxl = defaultVal;
        }
        else if (isNumber(jsValue) && jsValue >= 0) {
            gridColColumnOption.xs = jsValue;
            gridColColumnOption.sm = jsValue;
            gridColColumnOption.md = jsValue;
            gridColColumnOption.lg = jsValue;
            gridColColumnOption.xl = jsValue;
            gridColColumnOption.xxl = jsValue;
        }
        else if (isObject(jsValue)) {
            let hasValue = false;
            let attributeNames = ['xs', 'sm', 'md', 'lg', 'xl', 'xxl'];
            for (let attributeName of attributeNames) {
                let attributeValue = jsValue[attributeName];
                if (attributeValue === null || attributeValue === undefined) {
                    jsValue[attributeName] = defaultVal;
                }
                else if (isNumber(attributeValue) && attributeValue >= 0) {
                    continue;
                }
                else {
                    jsValue[attributeName] = defaultVal;
                }
            }
            gridColColumnOption.xs = jsValue.xs;
            gridColColumnOption.sm = jsValue.sm;
            gridColColumnOption.md = jsValue.md;
            gridColColumnOption.lg = jsValue.lg;
            gridColColumnOption.xl = jsValue.xl;
            gridColColumnOption.xxl = jsValue.xxl;
        }
        return gridColColumnOption;
    }
}
// @ts-ignore
globalThis.GridCol.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkGridColComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
const COLOR_WITH_MAGIC = /#[0-9A-Fa-f]{6,8}/;
const COLOR_WITH_MAGIC_MINI = /#[0-9A-Fa-f]{3,4}/;
const COLOR_WITH_RGB = /rgb\(([0-9]{1,3})\,([0-9]{1,3})\,([0-9]{1,3})\)/i;
const COLOR_WITH_RGBA = /rgba\(([0-9]{1,3})\,([0-9]{1,3})\,([0-9]{1,3})\,(\d+\.?\d*)\)/i;
const COLOR_ALPHA_MASK = 0xff000000;
const MIN_RGB_VALUE = 0;
const MAX_RGB_VALUE = 255;
const COLOR_ALPHA_OFFSET = 24;
const MIN_RGBA_OPACITY = 0.0;
const MAX_RGBA_OPACITY = 1.0;
const MIN_COLOR_STR_LEN = 8;
const HEX_DECIMAL = 16;
class ArkColor {
    constructor() {
        this.color = undefined;
    }
    isEqual(another) {
        return (this.color === another.color);
    }
    parseColorValue(value) {
        if (isResource(value)) {
            return false;
        }
        if (typeof value === "number") {
            return this.parseColorUint(value);
        }
        else if (typeof value === "string") {
            return this.parseColorString(value);
        }
        else if (value === undefined) {
            this.color = value;
            return true;
        }
        return false;
    }
    parseColorString(colorStr) {
        if (colorStr.length === 0) {
            return false;
        }
        colorStr = colorStr.replace(/\s/g, "");
        return (this.matchColorWithMagic(colorStr) ||
            this.matchColorWithMagicMini(colorStr) ||
            this.matchColorWithRGB(colorStr) ||
            this.matchColorWithRGBA(colorStr) ||
            this.matchColorSpecialString(colorStr) ||
            this.parseUintColorString(colorStr));
    }
    matchColorWithMagic(colorStr) {
        const matches = colorStr.match(COLOR_WITH_MAGIC);
        if (matches) {
            colorStr = colorStr.substr(1);
            let value = parseInt(colorStr, HEX_DECIMAL);
            if (colorStr.length < MIN_COLOR_STR_LEN) {
                value |= COLOR_ALPHA_MASK;
            }
            this.color = value;
            return true;
        }
        return false;
    }
    matchColorWithMagicMini(colorStr) {
        const matches = colorStr.match(COLOR_WITH_MAGIC_MINI);
        if (matches) {
            colorStr = colorStr.substr(1);
            let newColorStr = colorStr.replace(/./g, (match) => match + match);
            let value = parseInt(newColorStr, HEX_DECIMAL);
            if (newColorStr.length < MIN_COLOR_STR_LEN) {
                value |= COLOR_ALPHA_MASK;
            }
            this.color = value;
            return true;
        }
        return false;
    }
    matchColorWithRGB(colorStr) {
        const matches = colorStr.match(COLOR_WITH_RGB);
        if (matches && matches.length === 4) {
            const [_, redInt, greenInt, blueInt] = matches;
            if (this.isRGBValid(parseInt(redInt)) && this.isRGBValid(parseInt(greenInt)) && this.isRGBValid(parseInt(blueInt))) {
                this.color = this.fromRGB(parseInt(redInt), parseInt(greenInt), parseInt(blueInt));
                return true;
            }
        }
        return false;
    }
    matchColorWithRGBA(colorStr) {
        const matches = colorStr.match(COLOR_WITH_RGBA);
        if (matches && matches.length === 5) {
            const [_, redInt, greenInt, blueInt, opacityDouble] = matches;
            if (this.isRGBValid(parseInt(redInt)) &&
                this.isRGBValid(parseInt(greenInt)) &&
                this.isRGBValid(parseInt(blueInt)) &&
                this.isOpacityValid(parseFloat(opacityDouble))) {
                this.color = this.fromRGBO(parseInt(redInt), parseInt(greenInt), parseInt(blueInt), parseFloat(opacityDouble));
                return true;
            }
        }
        return false;
    }
    matchColorSpecialString(colorStr) {
        const colorTable = {
            black: 0xff000000,
            blue: 0xff0000ff,
            gray: 0xffc0c0c0,
            green: 0xff00ff00,
            red: 0xffff0000,
            white: 0xffffffff,
        };
        if (colorStr in colorTable) {
            this.color = colorTable[colorStr];
            return true;
        }
        return false;
    }
    parseUintColorString(colorStr) {
        const colorInt = Number(colorStr);
        return this.parseColorUint(colorInt);
    }
    parseColorUint(colorInt) {
        if (colorInt > 0) {
            this.color = colorInt;
            if ((colorInt & COLOR_ALPHA_MASK) === 0) {
                this.color |= COLOR_ALPHA_MASK;
            }
            return true;
        }
        return false;
    }
    isRGBValid(value) {
        return value >= MIN_RGB_VALUE && value <= MAX_RGB_VALUE;
    }
    isOpacityValid(value) {
        return value >= MIN_RGBA_OPACITY && value <= MAX_RGBA_OPACITY;
    }
    fromARGB(alpha, red, green, blue) {
        const argb = (alpha << 24) | (red << 16) | (green << 8) | blue;
        return argb >>> 0;
    }
    fromRGBO(red, green, blue, opacity) {
        const alpha = Math.round(opacity * 0xff) & 0xff;
        return this.fromARGB(alpha, red, green, blue);
    }
    fromRGB(red, green, blue) {
        return this.fromARGB(0xff, red, green, blue);
    }
    getColor() {
        return this.color;
    }
}
/// <reference path="./import.ts" />
class ArkBorderStyle {
    constructor() {
        this.type = undefined;
        this.style = undefined;
        this.top = undefined;
        this.right = undefined;
        this.bottom = undefined;
        this.left = undefined;
    }
    isEqual(another) {
        return (this.type === another.type &&
            this.style === another.style &&
            this.top === another.top &&
            this.right === another.right &&
            this.bottom === another.bottom &&
            this.left === another.left);
    }
    parseBorderStyle(value) {
        if (typeof value === 'number') {
            this.style = value;
            this.type = true;
            return true;
        }
        else if (typeof value === 'object') {
            return this.parseEdgeStyles(value);
        }
        return false;
    }
    parseEdgeStyles(options) {
        this.top = options.top;
        this.right = options.right;
        this.bottom = options.bottom;
        this.left = options.left;
        this.type = true;
        return true;
    }
}
class ArkShadow {
    constructor() {
        this.style = undefined;
        this.radius = undefined;
        this.type = undefined;
        this.color = undefined;
        this.offsetX = undefined;
        this.offsetY = undefined;
        this.fill = undefined;
    }
    isEqual(another) {
        return (this.style === another.style &&
            this.radius === another.radius &&
            this.type === another.type &&
            this.color === another.color &&
            this.offsetX === another.offsetX &&
            this.offsetY === another.offsetY &&
            this.fill === another.fill);
    }
    parseShadowValue(value) {
        if (typeof value === 'number') {
            this.style = value;
            return true;
        }
        else if (typeof value === 'object') {
            return this.parseShadowOptions(value);
        }
        return false;
    }
    parseShadowOptions(options) {
        if (isResource(options.radius) ||
            isResource(options.color) ||
            isResource(options.offsetX) ||
            isResource(options.offsetY)) {
            return false;
        }
        let arkColor = new ArkColor();
        this.radius = options.radius;
        this.type = options.type;
        if (arkColor.parseColorValue(options.color)) {
            this.color = arkColor.getColor();
        }
        this.offsetX = options.offsetX;
        this.offsetY = options.offsetY;
        this.fill = options.fill;
        return true;
    }
}
class ArkBorderColor {
    constructor() {
        this.leftColor = undefined;
        this.rightColor = undefined;
        this.topColor = undefined;
        this.bottomColor = undefined;
    }
    isEqual(another) {
        return (this.leftColor === another.leftColor &&
            this.rightColor === another.rightColor &&
            this.topColor === another.topColor &&
            this.bottomColor === another.bottomColor);
    }
}
class ArkPosition {
    constructor() {
        this.x = undefined;
        this.y = undefined;
    }
    isEqual(another) {
        return this.x === another.x && this.y === another.y;
    }
}
class ArkBorderWidth {
    constructor() {
        this.left = undefined;
        this.right = undefined;
        this.top = undefined;
        this.bottom = undefined;
    }
    isEqual(another) {
        return (this.left === another.left &&
            this.right === another.right &&
            this.top === another.top &&
            this.bottom === another.bottom);
    }
}
class ArkBorderRadius {
    constructor() {
        this.topLeft = undefined;
        this.topRight = undefined;
        this.bottomLeft = undefined;
        this.bottomRight = undefined;
    }
    isEqual(another) {
        return (this.topLeft === another.topLeft &&
            this.topRight === another.topRight &&
            this.bottomLeft === another.bottomLeft &&
            this.bottomRight === another.bottomRight);
    }
}
class ArkTransformMatrix {
    constructor(matrix) {
        this.matrix = matrix;
        this.length = 16;
    }
    compareArrays(arr1, arr2) {
        return (Array.isArray(arr1) &&
            Array.isArray(arr2) &&
            arr1.length === arr2.length &&
            arr1.every((value, index) => value === arr2[index]));
    }
    isEqual(another) {
        return this.compareArrays(this.matrix, another.matrix);
    }
}
class ArkLabelStyle {
    constructor() {
        this.overflow = undefined;
        this.maxLines = undefined;
        this.minFontSize = undefined;
        this.maxFontSize = undefined;
        this.heightAdaptivePolicy = undefined;
        this.font = new ArkLabelFont();
    }
    isEqual(another) {
        return (this.overflow === another.overflow &&
            this.maxLines === another.maxLines &&
            this.minFontSize === another.minFontSize &&
            this.maxFontSize === another.maxFontSize &&
            this.heightAdaptivePolicy === another.heightAdaptivePolicy &&
            this.font.isEqual(another.font));
    }
}
class ArkLabelFont {
    constructor() {
        this.size = undefined;
        this.weight = undefined;
        this.family = undefined;
        this.style = undefined;
    }
    isEqual(another) {
        return (this.size === another.size &&
            this.weight === another.weight &&
            this.family === another.family &&
            this.style === another.style);
    }
}
function ArkDeepCompareArrays(arr1, arr2) {
    return (Array.isArray(arr1) &&
        Array.isArray(arr2) &&
        arr1.length === arr2.length &&
        arr1.every((value, index) => {
            if (Array.isArray(value) && Array.isArray(arr2[index])) {
                return ArkDeepCompareArrays(value, arr2[index]);
            }
            else {
                return value === arr2[index];
            }
        }));
}
function ArkDeepSimpleCopy(obj) {
    if (typeof obj === 'object') {
        if (Array.isArray(obj)) {
            let result = [];
            for (let i = 0; i < obj.length; i++) {
                result[i] = ArkDeepSimpleCopy(obj[i]);
            }
            return result;
        }
        else {
            let result = {};
            for (const key in obj) {
                if (obj.hasOwnProperty(key)) {
                    result[key] = ArkDeepSimpleCopy(obj[key]);
                }
            }
            return result;
        }
    }
    return obj;
}
function ArkCopyColorStop(colorStop) {
    if (Array.isArray(colorStop)) {
        let result = [];
        for (let index = 0; index < colorStop.length; index++) {
            let value = colorStop[index];
            if (index === 0) {
                let arkColor = new ArkColor();
                if (arkColor.parseColorValue(value)) {
                    result[0] = arkColor.getColor();
                }
                continue;
            }
            result[index] = ArkDeepSimpleCopy(value);
        }
        ;
        return result;
    }
    return ArkDeepSimpleCopy(colorStop);
}
function ArkCopyColorStops(colorStops) {
    let result = [];
    for (let index = 0; index < colorStops.length; index++) {
        result[index] = ArkCopyColorStop(colorStops[index]);
    }
    ;
    return result;
}
class ArkLinearGradient {
    constructor(angle, direction, colors, repeating) {
        this.angle = angle;
        this.direction = direction;
        this.colors = ArkCopyColorStops(colors);
        this.repeating = repeating;
    }
    isEqual(another) {
        return (this.angle === another.angle &&
            this.direction === another.direction &&
            ArkDeepCompareArrays(this.colors, another.colors) &&
            this.repeating === another.repeating);
    }
}
class ArkRadialGradient {
    constructor(center, radius, colors, repeating) {
        this.center = center;
        this.radius = radius;
        this.colors = ArkCopyColorStops(colors);
        this.repeating = repeating;
    }
    isEqual(another) {
        return (ArkDeepCompareArrays(this.center, another.center) &&
            this.radius === another.radius &&
            ArkDeepCompareArrays(this.colors, another.colors) &&
            this.repeating === another.repeating);
    }
}
class ArkSweepGradient {
    constructor(center, start, end, rotation, colors, repeating) {
        this.center = center;
        this.start = start;
        this.end = end;
        this.rotation = rotation;
        this.colors = ArkCopyColorStops(colors);
        this.repeating = repeating;
    }
    isEqual(another) {
        return (ArkDeepCompareArrays(this.center, another.center) &&
            this.start === another.start &&
            this.end === another.end &&
            this.rotation === another.rotation &&
            ArkDeepCompareArrays(this.colors, another.colors) &&
            this.repeating === another.repeating);
    }
}
class ArkForegroundBlurStyle {
    constructor() {
        this.blurStyle = undefined;
        this.colorMode = undefined;
        this.adaptiveColor = undefined;
        this.scale = undefined;
    }
    isEqual(another) {
        return (this.blurStyle === another.blurStyle &&
            this.colorMode === another.colorMode &&
            this.adaptiveColor === another.adaptiveColor &&
            this.scale === another.scale);
    }
}
class ArkLinearGradientBlur {
    constructor() {
        this.blurRadius = undefined;
        this.fractionStops = undefined;
        this.direction = undefined;
    }
    isEqual(another) {
        return (this.blurRadius === another.blurRadius &&
            ArkDeepCompareArrays(this.fractionStops, another.fractionStops) &&
            this.direction === another.direction);
    }
}
class ArkOverlay {
    constructor(value, align, offsetX, offsetY) {
        this.value = value;
        this.align = align;
        this.offsetX = offsetX;
        this.offsetY = offsetY;
    }
    isEqual(another) {
        return ((this.value === another.value) && (this.align === another.align) &&
            (this.offsetX === another.offsetX) && (this.offsetY === another.offsetY));
    }
}
class ArkSharedTransition {
    constructor() {
        this.id = undefined;
        this.options = undefined;
    }
    isEqual(another) {
        return (this.id === another.id) && (this.options === another.options);
    }
}
class ArkBorderImage {
    constructor() {
        this.sliceTop = undefined;
        this.sliceRight = undefined;
        this.sliceBottom = undefined;
        this.sliceLeft = undefined;
        this.repeat = undefined;
        this.source = undefined;
        this.sourceAngle = undefined;
        this.sourceDirection = undefined;
        this.sourceColors = undefined;
        this.sourceRepeating = undefined;
        this.widthTop = undefined;
        this.widthRight = undefined;
        this.widthBottom = undefined;
        this.widthLeft = undefined;
        this.outsetTop = undefined;
        this.outsetRight = undefined;
        this.outsetBottom = undefined;
        this.outsetLeft = undefined;
        this.fill = undefined;
    }
    isLength(val) {
        return (isNumber(val) || isString(val) || isResource(val));
    }
    parseSliceOption(slice) {
        if (isUndefined(slice)) {
            return true;
        }
        if (this.isLength(slice)) {
            if (isResource(slice)) {
                return true;
            }
            let tmpSlice = slice;
            this.sliceTop = tmpSlice;
            this.sliceRight = tmpSlice;
            this.sliceBottom = tmpSlice;
            this.sliceLeft = tmpSlice;
            return true;
        }
        let tmpSlice = slice;
        if (!isResource(tmpSlice.top)) {
            this.sliceTop = tmpSlice.top;
        }
        if (!isResource(tmpSlice.right)) {
            this.sliceRight = tmpSlice.right;
        }
        if (!isResource(tmpSlice.bottom)) {
            this.sliceBottom = tmpSlice.bottom;
        }
        if (!isResource(tmpSlice.left)) {
            this.sliceLeft = tmpSlice.left;
        }
        return true;
    }
    parseSourceOption(source) {
        if (isUndefined(source)) {
            return true;
        }
        if (isString(source)) {
            this.source = source;
            return true;
        }
        if (isResource(source)) {
            return true;
        }
        let tmpSource = source;
        this.sourceAngle = tmpSource.angle;
        this.sourceDirection = tmpSource.direction;
        this.sourceColors = ArkCopyColorStops(tmpSource.colors);
        this.sourceRepeating = tmpSource.repeating;
        return true;
    }
    parseWidthOption(width) {
        if (isUndefined(width)) {
            return true;
        }
        if (this.isLength(width)) {
            if (isResource(width)) {
                return true;
            }
            let tmpWidth = width;
            this.widthTop = tmpWidth;
            this.widthRight = tmpWidth;
            this.widthBottom = tmpWidth;
            this.widthLeft = tmpWidth;
            return true;
        }
        let tmpWidth = width;
        if (!isResource(tmpWidth.top)) {
            this.widthTop = tmpWidth.top;
        }
        if (!isResource(tmpWidth.right)) {
            this.widthRight = tmpWidth.right;
        }
        if (!isResource(tmpWidth.bottom)) {
            this.widthBottom = tmpWidth.bottom;
        }
        if (!isResource(tmpWidth.left)) {
            this.widthLeft = tmpWidth.left;
        }
        return true;
    }
    parseOutsetOption(outset) {
        if (isUndefined(outset)) {
            return true;
        }
        if (this.isLength(outset)) {
            if (isResource(outset)) {
                return true;
            }
            let tmpOutset = outset;
            this.outsetTop = tmpOutset;
            this.outsetRight = tmpOutset;
            this.outsetBottom = tmpOutset;
            this.outsetLeft = tmpOutset;
            return true;
        }
        let tmpOutset = outset;
        if (!isResource(tmpOutset.top)) {
            this.outsetTop = tmpOutset.top;
        }
        if (!isResource(tmpOutset.right)) {
            this.outsetRight = tmpOutset.right;
        }
        if (!isResource(tmpOutset.bottom)) {
            this.outsetBottom = tmpOutset.bottom;
        }
        if (!isResource(tmpOutset.left)) {
            this.outsetLeft = tmpOutset.left;
        }
        return true;
    }
    parseOption(value) {
        if (!this.parseSliceOption(value.slice)) {
            return false;
        }
        this.repeat = value.repeat;
        if (!this.parseSourceOption(value.source)) {
            return false;
        }
        if (!this.parseWidthOption(value.width)) {
            return false;
        }
        if (!this.parseOutsetOption(value.outset)) {
            return false;
        }
        this.fill = value.fill;
        return true;
    }
    isSliceEqual(another) {
        return ((this.sliceTop === another.sliceTop) && (this.sliceRight === another.sliceRight) &&
            (this.sliceBottom === another.sliceBottom) && (this.sliceLeft === another.sliceLeft));
    }
    isLinearGradientEqual(another) {
        return ((this.sourceAngle === another.sourceAngle) &&
            (this.sourceDirection === another.sourceDirection) &&
            (ArkDeepCompareArrays(this.sourceColors, another.sourceColors)) &&
            (this.sourceRepeating === another.sourceRepeating));
    }
    isSourceEqual(another) {
        return ((this.source === another.source) && this.isLinearGradientEqual(another));
    }
    isWidthEqual(another) {
        return ((this.widthTop === another.widthTop) && (this.widthRight === another.widthRight) &&
            (this.widthBottom === another.widthBottom) && (this.widthLeft === another.widthLeft));
    }
    isOutsetEqual(another) {
        return ((this.outsetTop === another.outsetTop) && (this.outsetRight === another.outsetRight) &&
            (this.outsetBottom === another.outsetBottom) && (this.outsetLeft === another.outsetLeft));
    }
    isEqual(another) {
        return (this.isSliceEqual(another) && (this.repeat = another.repeat) &&
            this.isSourceEqual(another) && this.isWidthEqual(another) &&
            this.isOutsetEqual(another) && (this.fill === another.fill));
    }
}
class ArkFont {
    constructor() {
        this.size = '16fp';
        this.weight = '400';
    }
    setFamily(family) {
        this.family = family;
    }
    setSize(size) {
        this.size = size;
    }
    setStyle(style) {
        this.style = style;
    }
    isEqual(another) {
        return (this.size === another.size &&
            this.weight === another.weight &&
            this.family === another.family &&
            this.style === another.style);
    }
    parseFontWeight(value) {
        const valueWeightMap = {
            [0]: 'Lighter',
            [1]: 'Normal',
            [2]: 'Regular',
            [3]: 'Medium',
            [4]: 'Bold',
            [5]: 'Bolder'
        };
        if (value in valueWeightMap) {
            this.weight = valueWeightMap[value];
        }
        else {
            this.weight = value.toString();
        }
    }
}
class ArkMenuAlignType {
    constructor() {
        this.alignType = 2;
        this.dx = 0;
        this.dy = 0;
    }
    isEqual(another) {
        return this.alignType === another.alignType && this.dx === another.dx && this.dy === another.dy;
    }
}
class ArkSliderTips {
    constructor() {
        this.showTip = false;
        this.tipText = undefined;
    }
    isEqual(another) {
        return this.showTip === another.showTip && this.tipText === another.tipText;
    }
}
class ArkTextStyle {
    constructor() {
        this.color = undefined;
        this.font = new ArkFont();
    }
    parseTextStyle(value, defaultColor, defaultSize, defaultWeight) {
        if (isObject(value)) {
            let color = new ArkColor();
            let inputFont = value.font;
            let inputColor = value.color;
            if (!isUndefined(inputColor) && (isNumber(inputColor) || isString(inputColor))) {
                color.parseColorValue(inputColor);
                this.color = color.getColor();
            }
            if (!isUndefined(inputFont) && isObject(inputFont)) {
                if (!isUndefined(inputFont.size)) {
                    this.font.size = inputFont.size;
                }
                if (!isUndefined(inputFont.weight)) {
                    this.font.parseFontWeight(inputFont.weight);
                }
                this.font.family = inputFont.family;
                this.font.style = inputFont.style;
            }
        }
        else {
            this.color = defaultColor;
            this.font.size = defaultSize;
            this.font.parseFontWeight(defaultWeight);
        }
    }
    isEqual(another) {
        return this.color === another.color && this.font.isEqual(another.font);
    }
}
class ArkRadioStyle {
    constructor() {
        this.checkedBackgroundColor = undefined;
        this.uncheckedBorderColor = undefined;
        this.indicatorColor = undefined;
    }
    isEqual(another) {
        return (this.checkedBackgroundColor === another.checkedBackgroundColor &&
            this.uncheckedBorderColor === another.uncheckedBorderColor &&
            this.indicatorColor === another.indicatorColor);
    }
}
class ArkStarStyle {
    constructor() {
        this.backgroundUri = undefined;
        this.foregroundUri = undefined;
        this.secondaryUri = undefined;
    }
    isEqual(another) {
        return (this.backgroundUri === another.backgroundUri &&
            this.foregroundUri === another.foregroundUri &&
            this.secondaryUri === another.secondaryUri);
    }
}
class ArkBackgroundBlurStyle {
    constructor() {
        this.blurStyle = undefined;
        this.colorMode = undefined;
        this.adaptiveColor = undefined;
        this.scale = undefined;
    }
    isEqual(another) {
        return (this.blurStyle === another.blurStyle &&
            this.colorMode === another.colorMode &&
            this.adaptiveColor === another.adaptiveColor &&
            this.scale === another.scale);
    }
}
class ArkMarkStyle {
    constructor() {
        this.strokeColor = undefined;
        this.size = undefined;
        this.strokeWidth = undefined;
    }
    isEqual(another) {
        return (this.strokeColor === another.strokeColor && this.size === another.size && this.strokeWidth === another.strokeWidth);
    }
    parseMarkStyle(options) {
        let arkColor = new ArkColor();
        if (!arkColor.parseColorValue(options.strokeColor)) {
            return false;
        }
        this.strokeColor = arkColor.getColor();
        this.size = options.size;
        this.strokeWidth = options.strokeWidth;
        return true;
    }
}
class ArkSelectedIndices {
    constructor() {
        this.selectedValues = [];
    }
    compareArrays(arr1, arr2) {
        return (Array.isArray(arr1) &&
            Array.isArray(arr2) &&
            arr1.length === arr2.length &&
            arr1.every((value, index) => value === arr2[index]));
    }
    isEqual(another) {
        return this.compareArrays(this.selectedValues, another.selectedValues);
    }
}
class ArkBlockSize {
    constructor() {
        this.width = undefined;
        this.height = undefined;
    }
    isEqual(another) {
        return this.width === another.width && this.height === another.height;
    }
}
class ArkDecoration {
    constructor() {
        this.type = TextDecorationType.None;
        this.color = undefined;
    }
    isEqual(another) {
        return this.type === another.type && this.color === another.color;
    }
}
class ArkBorder {
    constructor() {
        this.arkWidth = new ArkBorderWidth();
        this.arkColor = new ArkBorderColor();
        this.arkRadius = new ArkBorderRadius();
        this.arkStyle = new ArkBorderStyle();
    }
    isEqual(another) {
        return (this.arkWidth.isEqual(another.arkWidth) &&
            this.arkColor.isEqual(another.arkColor) &&
            this.arkRadius.isEqual(another.arkRadius) &&
            this.arkStyle.isEqual(another.arkStyle));
    }
}
class ArkBackgroundImagePosition {
    constructor() {
        this.alignment = undefined;
        this.x = undefined;
        this.y = undefined;
    }
    isEqual(another) {
        return this.alignment === another.alignment && this.x === another.x && this.y === another.y;
    }
}
class ArkBackgroundImageSize {
    constructor() {
        this.imageSize = undefined;
        this.width = undefined;
        this.height = undefined;
    }
    isEqual(another) {
        return this.imageSize === another.imageSize && this.width === another.width && this.height === another.height;
    }
}
class ArkBackgroundImage {
    constructor() {
        this.src = undefined;
        this.repeat = undefined;
    }
    isEqual(another) {
        return this.src === another.src && this.repeat === another.repeat;
    }
}
class ArkTranslate {
    constructor() {
        this.x = undefined;
        this.y = undefined;
        this.z = undefined;
    }
    isEqual(another) {
        return this.x === another.x && this.y === another.y && this.z === another.z;
    }
}
class ArkScale {
    constructor() {
        this.x = undefined;
        this.y = undefined;
        this.z = undefined;
        this.centerX = undefined;
        this.centerY = undefined;
    }
    isEqual(another) {
        return (this.x === another.x &&
            this.y === another.y &&
            this.z === another.z &&
            this.centerX === another.centerX &&
            this.centerY === another.centerY);
    }
}
class ArkRotate {
    constructor() {
        this.x = undefined;
        this.y = undefined;
        this.z = undefined;
        this.angle = undefined;
        this.centerX = undefined;
        this.centerY = undefined;
        this.centerZ = undefined;
        this.perspective = undefined;
    }
    isEqual(another) {
        return (this.x === another.x &&
            this.y === another.y &&
            this.z === another.z &&
            this.angle === another.angle &&
            this.centerX === another.centerX &&
            this.centerY === another.centerY &&
            this.centerZ === another.centerZ &&
            this.perspective === another.perspective);
    }
}
class ArkPixelStretchEffect {
    constructor() {
        this.top = undefined;
        this.right = undefined;
        this.bottom = undefined;
        this.left = undefined;
    }
    isEqual(another) {
        return (this.top === another.top &&
            this.right === another.right &&
            this.bottom === another.bottom &&
            this.left === another.left);
    }
}
class ArkForegroundColor {
    constructor() {
        this.color = undefined;
        this.strategy = undefined;
    }
    isEqual(another) {
        return this.color === another.color && this.strategy === another.strategy;
    }
}
class ArkMotionPath {
    constructor() {
        this.path = undefined;
        this.from = undefined;
        this.to = undefined;
        this.rotatable = undefined;
    }
    isEqual(another) {
        return (this.path === another.path &&
            this.from === another.from &&
            this.to === another.to &&
            this.rotatable === another.rotatable);
    }
}
class ArkGridColColumnOption {
    constructor() {
        this.xs = 0;
        this.sm = 0;
        this.md = 0;
        this.lg = 0;
        this.xl = 0;
        this.xxl = 0;
    }
    isEqual(another) {
        return (this.xs === another.xs &&
            this.sm === another.sm &&
            this.md === another.md &&
            this.lg === another.lg &&
            this.xl === another.xl &&
            this.xxl === another.xxl);
    }
}
class ArkConstraintSizeOptions {
    constructor() {
        this.minWidth = undefined;
        this.maxWidth = undefined;
        this.minHeight = undefined;
        this.maxHeight = undefined;
    }
    isEqual(another) {
        return (this.minWidth === another.minWidth &&
            this.maxWidth === another.maxWidth &&
            this.minHeight === another.minHeight &&
            this.maxHeight === another.maxHeight);
    }
}
class ArkSize {
    constructor() {
        this.width = undefined;
        this.height = undefined;
    }
    isEqual(another) {
        return this.width === another.width && this.height === another.height;
    }
}
class ArkPadding {
    constructor() {
        this.top = undefined;
        this.right = undefined;
        this.bottom = undefined;
        this.left = undefined;
    }
    isEqual(another) {
        return (this.top === another.top &&
            this.right === another.right &&
            this.bottom === another.bottom &&
            this.left === another.left);
    }
}
class ArkAllowDrop {
    constructor() {
        this.allowDropArray = undefined;
    }
    isEqual(another) {
        return this.allowDropArray === another.allowDropArray;
    }
}
class ArkBarMode {
    isEqual(another) {
        return (this.barMode === another.barMode) && (this.options === another.options);
    }
}
class ArkDivider {
    isEqual(another) {
        return (this.value === another.value);
    }
}
class ArkBarBackgroundColor {
    isEqual(another) {
        return (this.value === another.value);
    }
}
class ArkBarGridAlign {
    isEqual(another) {
        return (this.value === another.value);
    }
}
class ArkScrollableBarModeOptions {
    isEqual(another) {
        return (this.value === another.value);
    }
}
class ArkObscured {
    constructor() {
        this.reasons = undefined;
    }
    parseReasonsArray(reasonObject) {
        if (Array.isArray(reasonObject)) {
            for (let i = 0; i < reasonObject.length; i++) {
                this.reasons.push(reasonObject[i]);
            }
            return true;
        }
        return false;
    }
    isEqual(another) {
        return this.reasons === another.reasons;
    }
}
class ArkResponseRegion {
    constructor() {
        this.responseRegion = undefined;
    }
    isObject(region) {
        return region !== null && !Array.isArray(region) && typeof region === 'object';
    }
    parseRegionValue(value) {
        if (Array.isArray(value)) {
            return this.parseArrayList(value);
        }
        else if (this.isObject(value)) {
            return this.parseArray(value);
        }
        else if (value === undefined) {
            this.responseRegion = [];
            return true;
        }
        return false;
    }
    parseArray(regionObject) {
        if (this.isObject(regionObject)) {
            let x = regionObject['x'].toString();
            let y = regionObject['y'].toString();
            let width = regionObject['width'].toString();
            let height = regionObject['height'].toString();
            this.responseRegion.push(x);
            this.responseRegion.push(y);
            this.responseRegion.push(width);
            this.responseRegion.push(height);
            return true;
        }
        return false;
    }
    parseArrayList(regionObject) {
        if (Array.isArray(regionObject)) {
            for (let i = 0; i < regionObject.length; i++) {
                this.parseArray(regionObject[i]);
            }
            return true;
        }
        return false;
    }
    isEqual(another) {
        return this.responseRegion === another.responseRegion;
    }
}
class ArkAlignRules {
    constructor() {
        this.left = undefined;
        this.middle = undefined;
        this.right = undefined;
        this.top = undefined;
        this.center = undefined;
        this.bottom = undefined;
    }
    isEqual(another) {
        return (this.left === another.left &&
            this.middle === another.middle &&
            this.right === another.right &&
            this.top === another.top &&
            this.center === another.center &&
            this.bottom === another.bottom);
    }
}
class ArkSafeAreaExpandOpts {
    constructor() {
        this.type = undefined;
        this.edges = undefined;
    }
    isEqual(another) {
        return false;
    }
}
class ArkSideBarDividerStyle {
    constructor() {
        this.startMargin = 0;
        this.endMargin = 0;
    }
    isEqual(another) {
        return (this.strokeWidth === another.strokeWidth &&
            this.color === another.color &&
            this.startMargin === another.startMargin &&
            this.endMargin === another.endMargin);
    }
}
class ArkColumnSplitDividerStyle {
    constructor() {
        this.startMargin = '0';
        this.endMargin = '0';
    }
    isEqual(another) {
        return false;
    }
}
class ArkButtonStyle {
    constructor() {
        this.left = 16;
        this.top = 48;
        this.width = 24;
        this.height = 24;
        this.icons = {
            shown: undefined,
            hidden: undefined,
            switching: undefined
        };
    }
    isEqual(another) {
        return (this.left === another.left &&
            this.top === another.top &&
            this.width === another.width &&
            this.height === another.height &&
            this.icons === another.icons);
    }
}
class ArkShadowInfoToArray {
    constructor() {
        this.radius = [];
        this.color = [];
        this.offsetX = [];
        this.offsetX = [];
        this.offsetY = [];
        this.fill = [];
    }
    isEqual(another) {
        return (this.radius === another.radius &&
            this.color === another.color &&
            this.offsetX === another.offsetX &&
            this.offsetY === another.offsetY &&
            this.fill === another.fill);
    }
}
class ArkPasswordIcon {
    constructor() {
        this.onIconSrc = undefined;
        this.offIconSrc = undefined;
    }
    isEqual(another) {
        return this.onIconSrc === another.onIconSrc && this.offIconSrc === another.offIconSrc;
    }
}
class ArkCaretStyle {
    constructor() {
        this.width = undefined;
        this.color = undefined;
    }
    isEqual(another) {
        return this.width === another.width && this.color === another.color;
    }
}
class ArkIconOptions {
    constructor() {
        this.size = undefined;
        this.color = undefined;
        this.src = undefined;
    }
    isEqual(another) {
        return this.size === another.color && this.color === another.color && this.src === another.src;
    }
}
class ArkSearchButton {
    constructor() {
        this.value = undefined;
        this.fontSize = undefined;
        this.fontColor = undefined;
    }
    isEqual(another) {
        return this.value === another.value && this.fontSize === another.fontSize && this.fontColor === another.fontColor;
    }
}
class ArkCancelButton {
    constructor() {
        this.style = undefined;
        this.color = undefined;
        this.size = undefined;
        this.src = undefined;
    }
    isEqual(another) {
        return (this.style === another.style &&
            this.color === another.color &&
            this.size === another.size &&
            this.src === another.src);
    }
}
class ArkImageFrameInfoToArray {
    constructor() {
        this.arrSrc = [];
        this.arrWidth = [];
        this.arrHeight = [];
        this.arrTop = [];
        this.arrLeft = [];
        this.arrDuration = [];
    }
    isEqual(another) {
        return (this.arrSrc.toString() === another.arrSrc.toString()) &&
            (this.arrWidth.toString() === another.arrWidth.toString()) &&
            (this.arrHeight.toString() === another.arrHeight.toString()) &&
            (this.arrTop.toString() === another.arrTop.toString()) &&
            (this.arrLeft.toString() === another.arrLeft.toString()) &&
            (this.arrDuration.toString() === another.arrDuration.toString());
    }
}
class ArkPickerTextStyle {
    constructor() {
        this.color = undefined;
        this.size = "16fp";
        this.weight = "Regular";
    }
    setColor(color) {
        let arkColor = new ArkColor();
        arkColor.parseColorValue(color);
        this.color = arkColor.color;
    }
    setSize(size) {
        this.size = size.toString();
    }
    setWeight(value) {
        const valueWeightMap = {
            [0]: 'Lighter',
            [1]: 'Normal',
            [2]: 'Regular',
            [3]: 'Medium',
            [4]: 'Bold',
            [5]: 'Bolder'
        };
        if (value in valueWeightMap) {
            this.weight = valueWeightMap[value];
        }
        else {
            this.weight = value.toString();
        }
    }
    isEqual(another) {
        return this.color === another.color && this.size === another.size && this.weight === another.weight;
    }
}
class ArkEdgeAlign {
    constructor() {
        this.alignType = undefined;
        this.offset = undefined;
    }
    isEqual(another) {
        return (this.alignType === another.alignType && this.offset === another.offset);
    }
}
class ArkDatePickerTextStyle {
    constructor() {
        this.color = undefined;
        this.font = undefined;
    }
    isEqual(another) {
        return (this.color === another.color && this.font === another.font);
    }
}
class ArkClickEffect {
    constructor() {
        this.level = undefined;
        this.scale = undefined;
    }
    isEqual(another) {
        return (this.level === another.level) && (this.scale === another.scale);
    }
}
class ArkKeyBoardShortCut {
    constructor() {
        this.value = undefined;
        this.keys = undefined;
        this.action = undefined;
    }
    isEqual(another) {
        return (this.value === another.value) && (this.keys === another.keys) &&
            (this.action === another.action);
    }
}
class ArkAlignStyle {
    constructor() {
        this.indexerAlign = undefined;
        this.offset = undefined;
    }
    isEqual(another) {
        return (this.indexerAlign === another.indexerAlign && this.offset === another.offset);
    }
}
class ArkResourceColor {
    constructor() {
        this.color = undefined;
    }
    isEqual(another) {
        return (this.color === another.color);
    }
}
/// <reference path="./import.ts" />
class ArkPanelComponent extends ArkComponent {
    mode(value) {
        if (typeof value === 'number') {
            modifier(this._modifiers, PanelModeModifier, value);
        }
        else {
            modifier(this._modifiers, PanelModeModifier, undefined);
        }
        return this;
    }
    type(value) {
        if (typeof value === 'number') {
            modifier(this._modifiers, PanelTypeModifier, value);
        }
        else {
            modifier(this._modifiers, PanelTypeModifier, undefined);
        }
        return this;
    }
    dragBar(value) {
        if (typeof value === 'boolean') {
            modifier(this._modifiers, DragBarModifier, value);
        }
        else {
            modifier(this._modifiers, DragBarModifier, undefined);
        }
        return this;
    }
    customHeight(value) {
        if (typeof value !== 'number' && typeof value !== 'string') {
            modifier(this._modifiers, PanelCustomHeightModifier, undefined);
        }
        else {
            modifier(this._modifiers, PanelCustomHeightModifier, value);
        }
        return this;
    }
    fullHeight(value) {
        if (typeof value !== 'number' && typeof value !== 'string') {
            modifier(this._modifiers, PanelFullHeightModifier, undefined);
        }
        else {
            modifier(this._modifiers, PanelFullHeightModifier, value);
        }
        return this;
    }
    halfHeight(value) {
        if (typeof value !== 'number' && typeof value !== 'string') {
            modifier(this._modifiers, PanelHalfHeightModifier, undefined);
        }
        else {
            modifier(this._modifiers, PanelHalfHeightModifier, value);
        }
        return this;
    }
    miniHeight(value) {
        if (typeof value !== 'number' && typeof value !== 'string') {
            modifier(this._modifiers, PanelMiniHeightModifier, undefined);
        }
        else {
            modifier(this._modifiers, PanelMiniHeightModifier, value);
        }
        return this;
    }
    show(value) {
        if (typeof value === 'boolean') {
            modifier(this._modifiers, ShowModifier, value);
        }
        else {
            modifier(this._modifiers, ShowModifier, undefined);
        }
        return this;
    }
    backgroundMask(color) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(color)) {
            modifier(this._modifiers, PanelBackgroundMaskModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, PanelBackgroundMaskModifier, undefined);
        }
        return this;
    }
    showCloseIcon(value) {
        if (typeof value === 'boolean') {
            modifier(this._modifiers, ShowCloseIconModifier, value);
        }
        else {
            modifier(this._modifiers, ShowCloseIconModifier, undefined);
        }
        return this;
    }
    onChange(event) {
        throw new Error('Method not implemented.');
    }
    onHeightChange(callback) {
        throw new Error('Method not implemented.');
    }
}
class PanelBackgroundMaskModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().panel.resetBackgroundMask(node);
        }
        else {
            GetUINativeModule().panel.setBackgroundMask(node, this.value);
        }
    }
}
PanelBackgroundMaskModifier.identity = Symbol('panelBackgroundMask');
class PanelModeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().panel.ResetPanelMode(node);
        }
        else {
            GetUINativeModule().panel.SetPanelMode(node, this.value);
        }
    }
}
PanelModeModifier.identity = Symbol('panelMode');
class PanelTypeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().panel.ResetPanelType(node);
        }
        else {
            GetUINativeModule().panel.SetPanelType(node, this.value);
        }
    }
}
PanelTypeModifier.identity = Symbol('panelType');
class PanelCustomHeightModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().panel.resetPanelCustomHeight(node);
        }
        else {
            GetUINativeModule().panel.setPanelCustomHeight(node, this.value);
        }
    }
}
PanelCustomHeightModifier.identity = Symbol('panelCustomHeight');
class PanelFullHeightModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().panel.resetPanelFullHeight(node);
        }
        else {
            GetUINativeModule().panel.setPanelFullHeight(node, this.value);
        }
    }
}
PanelFullHeightModifier.identity = Symbol('panelFullHeight');
class PanelHalfHeightModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().panel.resetPanelHalfHeight(node);
        }
        else {
            GetUINativeModule().panel.setPanelHalfHeight(node, this.value);
        }
    }
}
PanelHalfHeightModifier.identity = Symbol('panelHalfHeight');
class PanelMiniHeightModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().panel.resetPanelMiniHeight(node);
        }
        else {
            GetUINativeModule().panel.setPanelMiniHeight(node, this.value);
        }
    }
}
PanelMiniHeightModifier.identity = Symbol('panelMiniHeight');
class ShowCloseIconModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().panel.resetShowCloseIconModifier(node);
        }
        else {
            GetUINativeModule().panel.setShowCloseIconModifier(node, this.value);
        }
    }
}
ShowCloseIconModifier.identity = Symbol('showCloseIcon');
class DragBarModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().panel.resetDragBar(node);
        }
        else {
            GetUINativeModule().panel.setDragBar(node, this.value);
        }
    }
}
DragBarModifier.identity = Symbol('dragBar');
class ShowModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().panel.resetDragBar(node);
        }
        else {
            GetUINativeModule().panel.setDragBar(node, this.value);
        }
    }
}
ShowModifier.identity = Symbol('show');
// @ts-ignore
globalThis.Panel.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkPanelComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
const TITLE_MODE_RANGE = 2;
const NAV_BAR_POSITION_RANGE = 1;
const NAVIGATION_MODE_RANGE = 2;
const DEFAULT_NAV_BAR_WIDTH = 240;
const MIN_NAV_BAR_WIDTH_DEFAULT = "0vp";
const NAVIGATION_TITLE_MODE_DEFAULT = 0;
const DEFAULT_UNIT = "vp";
class ArkNavigationComponent extends ArkComponent {
    navBarWidth(value) {
        if (isNumber(value)) {
            value = value + DEFAULT_UNIT;
        }
        if (isString(value)) {
            modifier(this._modifiers, NavBarWidthModifier, value.toString());
        }
        return this;
    }
    navBarPosition(value) {
        if (value >= 0 && value <= NAV_BAR_POSITION_RANGE) {
            modifier(this._modifiers, NavBarPositionModifier, value);
        }
        return this;
    }
    navBarWidthRange(value) {
        if (!value) {
            return this;
        }
        if (!!value && (value === null || value === void 0 ? void 0 : value.length) > 0 && !!value[0]) {
            let min;
            if (isNumber(value[0])) {
                min = value[0] + DEFAULT_UNIT;
            }
            else {
                min = value[0].toString();
            }
            modifier(this._modifiers, MinNavBarWidthModifier, min);
        }
        else {
            modifier(this._modifiers, MinNavBarWidthModifier, MIN_NAV_BAR_WIDTH_DEFAULT);
        }
        if (!!value && (value === null || value === void 0 ? void 0 : value.length) > 1 && !!value[1]) {
            let max;
            if (isNumber(value[1])) {
                max = max + DEFAULT_UNIT;
            }
            else {
                max = value[1].toString();
            }
            modifier(this._modifiers, MaxNavBarWidthModifier, max);
        }
        else {
            modifier(this._modifiers, MaxNavBarWidthModifier, MIN_NAV_BAR_WIDTH_DEFAULT);
        }
        return this;
    }
    minContentWidth(value) {
        let minContentWidth = 0 + DEFAULT_UNIT;
        if ((isNumber(value) && Number(value) > 0)) {
            minContentWidth = value + DEFAULT_UNIT;
        }
        if (isString(value)) {
            minContentWidth = value.toString();
        }
        modifier(this._modifiers, MinContentWidthModifier, minContentWidth);
        return this;
    }
    mode(value) {
        if (!isNumber(value)) {
            modifier(this._modifiers, ModeModifier, NavigationMode.Auto);
        }
        else if (value >= NavigationMode.Stack && value <= NAVIGATION_MODE_RANGE) {
            modifier(this._modifiers, ModeModifier, value);
        }
        return this;
    }
    backButtonIcon(value) {
        modifierWithKey(this._modifiersWithKeys, BackButtonIconModifier.identity, BackButtonIconModifier, value);
        return this;
    }
    hideNavBar(value) {
        modifier(this._modifiers, HideNavBarModifier, isBoolean(value) ? value : false);
        return this;
    }
    title(value) {
        throw new Error("Method not implemented.");
    }
    subTitle(value) {
        modifier(this._modifiers, SubTitleModifier, value);
        return this;
    }
    hideTitleBar(value) {
        modifier(this._modifiers, NavigationHideTitleBarModifier, isBoolean(value) ? value : false);
        return this;
    }
    hideBackButton(value) {
        modifier(this._modifiers, HideBackButtonModifier, isBoolean(value) ? value : false);
        return this;
    }
    titleMode(value) {
        if (value >= NAVIGATION_TITLE_MODE_DEFAULT && value <= TITLE_MODE_RANGE) {
            modifier(this._modifiers, TitleModeModifier, value);
        }
        return this;
    }
    menus(value) {
        throw new Error("Method not implemented.");
    }
    toolBar(value) {
        throw new Error("Method not implemented.");
    }
    toolbarConfiguration(value) {
        throw new Error("Method not implemented.");
    }
    hideToolBar(value) {
        modifier(this._modifiers, HideToolBarModifier, isBoolean(value) ? value : false);
        return this;
    }
    onTitleModeChange(callback) {
        throw new Error("Method not implemented.");
    }
    onNavBarStateChange(callback) {
        throw new Error("Method not implemented.");
    }
    onNavigationModeChange(callback) {
        throw new Error("Method not implemented.");
    }
    navDestination(builder) {
        throw new Error("Method not implemented.");
    }
}
class BackButtonIconModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().navigation.resetBackButtonIcon(node);
        }
        else {
            GetUINativeModule().navigation.setBackButtonIcon(node, this.value);
        }
    }
    checkObjectDiff() {
        return false;
    }
}
BackButtonIconModifier.identity = Symbol("backButtonIcon");
class MinNavBarWidthModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().navigation.resetMinNavBarWidth(node);
        }
        else {
            GetUINativeModule().navigation.setMinNavBarWidth(node, this.value);
        }
    }
}
MinNavBarWidthModifier.identity = Symbol("minNavBarWidth");
class MaxNavBarWidthModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().navigation.resetMaxNavBarWidth(node);
        }
        else {
            GetUINativeModule().navigation.setMaxNavBarWidth(node, this.value);
        }
    }
}
MaxNavBarWidthModifier.identity = Symbol("maxNavBarWidth");
class MinContentWidthModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().navigation.resetMinContentWidth(node);
        }
        else {
            GetUINativeModule().navigation.setMinContentWidth(node, this.value);
        }
    }
}
MinContentWidthModifier.identity = Symbol("minContentWidth");
class NavBarWidthModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().navigation.resetNavBarWidth(node);
        }
        else {
            GetUINativeModule().navigation.setNavBarWidth(node, this.value);
        }
    }
}
NavBarWidthModifier.identity = Symbol("navBarWidth");
class NavBarPositionModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().navigation.resetNavBarPosition(node);
        }
        else {
            GetUINativeModule().navigation.setNavBarPosition(node, this.value);
        }
    }
}
NavBarPositionModifier.identity = Symbol("navBarPosition");
class ModeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().navigation.resetMode(node);
        }
        else {
            GetUINativeModule().navigation.setMode(node, this.value);
        }
    }
}
ModeModifier.identity = Symbol("mode");
class HideToolBarModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().navigation.resetHideToolBar(node);
        }
        else {
            GetUINativeModule().navigation.setHideToolBar(node, this.value);
        }
    }
}
HideToolBarModifier.identity = Symbol("hideToolBar");
class TitleModeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().navigation.resetTitleMode(node);
        }
        else {
            GetUINativeModule().navigation.setTitleMode(node, this.value);
        }
    }
}
TitleModeModifier.identity = Symbol("titleMode");
class HideBackButtonModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().navigation.resetHideBackButton(node);
        }
        else {
            GetUINativeModule().navigation.setHideBackButton(node, this.value);
        }
    }
}
HideBackButtonModifier.identity = Symbol("hideBackButton");
class SubTitleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().navigation.resetSubTitle(node);
        }
        else {
            GetUINativeModule().navigation.setSubTitle(node, this.value);
        }
    }
}
SubTitleModifier.identity = Symbol("subTitle");
class NavigationHideTitleBarModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().navigation.resetHideTitleBar(node);
        }
        else {
            GetUINativeModule().navigation.setHideTitleBar(node, this.value);
        }
    }
}
NavigationHideTitleBarModifier.identity = Symbol("hideTitleBar");
class HideNavBarModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().navigation.resetHideNavBar(node);
        }
        else {
            GetUINativeModule().navigation.setHideNavBar(node, this.value);
        }
    }
}
HideNavBarModifier.identity = Symbol("hideNavBar");
// @ts-ignore
globalThis.Navigation.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkNavigationComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class RichEditorCopyOptionsModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().richEditor.resetCopyOptions(node);
        }
        else {
            GetUINativeModule().richEditor.setCopyOptions(node, this.value);
        }
    }
}
RichEditorCopyOptionsModifier.identity = Symbol('richEditorCopyOptions');
class ArkRichEditorComponent extends ArkComponent {
    enableDataDetector(enable) {
        throw new Error('Method not implemented.');
    }
    dataDetectorConfig(config) {
        throw new Error('Method not implemented.');
    }
    copyOptions(value) {
        if (value) {
            modifier(this._modifiers, RichEditorCopyOptionsModifier, value);
        }
        else {
            modifier(this._modifiers, RichEditorCopyOptionsModifier, undefined);
        }
        return this;
    }
    onPaste(callback) {
        throw new Error('Method not implemented.');
    }
    onReady(callback) {
        throw new Error('Method not implemented.');
    }
    onSelect(callback) {
        throw new Error('Method not implemented.');
    }
    aboutToIMEInput(callback) {
        throw new Error('Method not implemented.');
    }
    onIMEInputComplete(callback) {
        throw new Error('Method not implemented.');
    }
    aboutToDelete(callback) {
        throw new Error('Method not implemented.');
    }
    onDeleteComplete(callback) {
        throw new Error('Method not implemented.');
    }
    bindSelectionMenu(spanType, content, responseType, options) {
        throw new Error('Method not implemented.');
    }
    customKeyboard(value) {
        throw new Error('Method not implemented.');
    }
}
// @ts-ignore
globalThis.RichEditor.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkRichEditorComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
const NAV_ROUTE_MODE_RANGE = 2;
const NAV_ROUTE_MODE_DEFAULT = 0;
class ArkNavRouterComponent extends ArkComponent {
    onStateChange(callback) {
        throw new Error("Method not implemented.");
    }
    mode(mode) {
        if (isNumber(mode) && mode >= NAV_ROUTE_MODE_DEFAULT && mode <= NAV_ROUTE_MODE_RANGE) {
            modifier(this._modifiers, NavRouterModeModifier, mode);
        }
        else {
            modifier(this._modifiers, NavRouterModeModifier, NAV_ROUTE_MODE_DEFAULT);
        }
        return this;
    }
}
class NavRouterModeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().navRouter.resetMode(node);
        }
        else {
            GetUINativeModule().navRouter.setMode(node, this.value);
        }
    }
}
NavRouterModeModifier.identity = Symbol("mode");
// @ts-ignore
globalThis.NavRouter.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkNavRouterComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
var NavigatorType;
(function (NavigatorType) {
    NavigatorType[NavigatorType["DEFAULT"] = 0] = "DEFAULT";
    NavigatorType[NavigatorType["PUSH"] = 1] = "PUSH";
    NavigatorType[NavigatorType["REPLACE"] = 2] = "REPLACE";
    NavigatorType[NavigatorType["BACK"] = 3] = "BACK";
})(NavigatorType || (NavigatorType = {}));
;
class ArkNavigatorComponent extends ArkComponent {
    active(value) {
        if (isBoolean(value)) {
            modifier(this._modifiers, ActiveModifier, value);
        }
        return this;
    }
    type(value) {
        if (isNumber(value) && value > NavigatorType.DEFAULT && value <= NavigatorType.REPLACE) {
            modifier(this._modifiers, TypeModifier, value);
        }
        else {
            modifier(this._modifiers, TypeModifier, NavigatorType.DEFAULT);
        }
        return this;
    }
    target(value) {
        if (isString(value)) {
            modifier(this._modifiers, TargetModifier, value);
        }
        return this;
    }
    params(value) {
        modifier(this._modifiers, ParamsModifier, JSON.stringify(value));
        return this;
    }
}
class ParamsModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().navigator.resetParams(node);
        }
        else {
            GetUINativeModule().navigator.setParams(node, this.value);
        }
    }
}
ParamsModifier.identity = Symbol("params");
class TypeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().navigator.resetType(node);
        }
        else {
            GetUINativeModule().navigator.setType(node, this.value);
        }
    }
}
TypeModifier.identity = Symbol("type");
class ActiveModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().navigator.resetActive(node);
        }
        else {
            GetUINativeModule().navigator.setActive(node, this.value);
        }
    }
}
ActiveModifier.identity = Symbol("active");
class TargetModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().navigator.resetTarget(node);
        }
        else {
            GetUINativeModule().navigator.setTarget(node, this.value);
        }
    }
}
TargetModifier.identity = Symbol("target");
// @ts-ignore
globalThis.Navigator.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkNavigatorComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkAlphabetIndexerComponent extends ArkComponent {
    onSelected(callback) {
        throw new Error("Method not implemented.");
    }
    color(value) {
        let arkResourceColor = new ArkResourceColor();
        arkResourceColor.color = value;
        if (value) {
            modifier(this._modifiers, ColorModifier, arkResourceColor);
        }
        else {
            modifier(this._modifiers, ColorModifier, undefined);
        }
        return this;
    }
    selectedColor(value) {
        let arkResourceColor = new ArkResourceColor();
        arkResourceColor.color = value;
        if (value) {
            modifier(this._modifiers, SelectedColorModifier, arkResourceColor);
        }
        else {
            modifier(this._modifiers, SelectedColorModifier, undefined);
        }
        return this;
    }
    popupColor(value) {
        let arkResourceColor = new ArkResourceColor();
        arkResourceColor.color = value;
        if (value) {
            modifier(this._modifiers, PopupColorModifier, arkResourceColor);
        }
        else {
            modifier(this._modifiers, PopupColorModifier, undefined);
        }
        return this;
    }
    selectedBackgroundColor(value) {
        let arkResourceColor = new ArkResourceColor();
        arkResourceColor.color = value;
        if (value) {
            modifier(this._modifiers, SelectedBackgroundColorModifier, arkResourceColor);
        }
        else {
            modifier(this._modifiers, SelectedBackgroundColorModifier, undefined);
        }
        return this;
    }
    popupBackground(value) {
        let arkResourceColor = new ArkResourceColor();
        arkResourceColor.color = value;
        if (value) {
            modifier(this._modifiers, PopupBackgroundModifier, arkResourceColor);
        }
        else {
            modifier(this._modifiers, PopupBackgroundModifier, undefined);
        }
        return this;
    }
    popupSelectedColor(value) {
        let arkResourceColor = new ArkResourceColor();
        arkResourceColor.color = value;
        if (value) {
            modifier(this._modifiers, PopupSelectedColorModifier, arkResourceColor);
        }
        else {
            modifier(this._modifiers, PopupSelectedColorModifier, undefined);
        }
        return this;
    }
    popupUnselectedColor(value) {
        let arkResourceColor = new ArkResourceColor();
        arkResourceColor.color = value;
        if (value) {
            modifier(this._modifiers, PopupUnselectedColorModifier, arkResourceColor);
        }
        else {
            modifier(this._modifiers, PopupUnselectedColorModifier, undefined);
        }
        return this;
    }
    popupItemBackgroundColor(value) {
        let arkResourceColor = new ArkResourceColor();
        arkResourceColor.color = value;
        if (value) {
            modifier(this._modifiers, PopupItemBackgroundColorModifier, arkResourceColor);
        }
        else {
            modifier(this._modifiers, PopupItemBackgroundColorModifier, undefined);
        }
        return this;
    }
    usingPopup(value) {
        if (typeof value === 'boolean') {
            modifier(this._modifiers, UsingPopupModifier, value);
        }
        else {
            modifier(this._modifiers, UsingPopupModifier, undefined);
        }
        return this;
    }
    selectedFont(value) {
        let font = new ArkFont();
        if (isObject(value)) {
            font.setSize(value.size);
            font.parseFontWeight(value.weight);
            font.setFamily(value.family);
            font.setStyle(value.style);
            modifier(this._modifiers, SelectedFontModifier, font);
        }
        else {
            modifier(this._modifiers, SelectedFontModifier, undefined);
        }
        return this;
    }
    popupFont(value) {
        let font = new ArkFont();
        if (isObject(value)) {
            font.setSize(value.size);
            font.parseFontWeight(value.weight);
            font.setFamily(value.family);
            font.setStyle(value.style);
            modifier(this._modifiers, PopupFontModifier, font);
        }
        else {
            modifier(this._modifiers, PopupFontModifier, undefined);
        }
        return this;
    }
    popupItemFont(value) {
        let font = new ArkFont();
        if (isObject(value)) {
            font.setSize(value.size);
            font.setStyle(value.style);
            modifier(this._modifiers, PopupItemFontModifier, font);
        }
        else {
            modifier(this._modifiers, PopupItemFontModifier, undefined);
        }
        return this;
    }
    itemSize(value) {
        if (typeof value !== "number" && typeof value !== "string") {
            modifier(this._modifiers, ItemSizeModifier, undefined);
        }
        else {
            modifier(this._modifiers, ItemSizeModifier, value);
        }
        return this;
    }
    font(value) {
        let font = new ArkFont();
        if (isObject(value)) {
            font.setSize(value.size);
            font.parseFontWeight(value.weight);
            font.setFamily(value.family);
            font.setStyle(value.style);
            modifier(this._modifiers, AlphabetIndexerFontModifier, font);
        }
        else {
            modifier(this._modifiers, AlphabetIndexerFontModifier, font);
        }
        return this;
    }
    alignStyle(value, offset) {
        let alignStyle = new ArkAlignStyle;
        if (typeof value === "number") {
            alignStyle.indexerAlign = value;
            alignStyle.offset = offset;
            modifier(this._modifiers, AlignStyleModifier, alignStyle);
        }
        else {
            modifier(this._modifiers, AlignStyleModifier, undefined);
        }
        return this;
    }
    onSelect(callback) {
        throw new Error("Method not implemented.");
    }
    onRequestPopupData(callback) {
        throw new Error("Method not implemented.");
    }
    onPopupSelect(callback) {
        throw new Error("Method not implemented.");
    }
    selected(index) {
        if (typeof index === "number") {
            modifier(this._modifiers, AlphabetIndexerSelectedModifier, index);
        }
        else {
            modifier(this._modifiers, AlphabetIndexerSelectedModifier, undefined);
        }
        return this;
    }
    popupPosition(value) {
        if (!value || (!!(value === null || value === void 0 ? void 0 : value.x) && typeof (value === null || value === void 0 ? void 0 : value.x) != "number" && typeof (value === null || value === void 0 ? void 0 : value.x) != "string") ||
            (!!(value === null || value === void 0 ? void 0 : value.y) && typeof (value === null || value === void 0 ? void 0 : value.y) != "number" && typeof (value === null || value === void 0 ? void 0 : value.x) != "string")) {
            modifier(this._modifiers, PopupPositionModifier, undefined);
        }
        else {
            let position = new ArkPosition();
            position.x = value === null || value === void 0 ? void 0 : value.x;
            position.y = value === null || value === void 0 ? void 0 : value.y;
            modifier(this._modifiers, PopupPositionModifier, position);
        }
        return this;
    }
}
// @ts-ignore
globalThis.AlphabetIndexer.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkAlphabetIndexerComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
class PopupItemFontModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().alphabetIndexer.resetPopupItemFont(node);
        }
        else {
            GetUINativeModule().alphabetIndexer.setPopupItemFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
    }
}
PopupItemFontModifier.identity = Symbol("popupItemFont");
class SelectedFontModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().alphabetIndexer.resetSelectedFont(node);
        }
        else {
            GetUINativeModule().alphabetIndexer.setSelectedFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
    }
}
SelectedFontModifier.identity = Symbol("alphaBetIndexerSelectedFont");
class PopupFontModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().alphabetIndexer.resetPopupFont(node);
        }
        else {
            GetUINativeModule().alphabetIndexer.setPopupFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
    }
}
PopupFontModifier.identity = Symbol("popupFont");
class AlphabetIndexerFontModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().alphabetIndexer.resetFont(node);
        }
        else {
            GetUINativeModule().alphabetIndexer.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
    }
}
AlphabetIndexerFontModifier.identity = Symbol("alphaBetIndexerFont");
class PopupItemBackgroundColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().alphabetIndexer.resetPopupItemBackgroundColor(node);
        }
        else {
            GetUINativeModule().alphabetIndexer.setPopupItemBackgroundColor(node, this.value.color);
        }
    }
}
PopupItemBackgroundColorModifier.identity = Symbol("popupItemBackgroundColor");
class ColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().alphabetIndexer.resetColor(node);
        }
        else {
            GetUINativeModule().alphabetIndexer.setColor(node, this.value.color);
        }
    }
}
ColorModifier.identity = Symbol("alphabetColor");
class PopupColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().alphabetIndexer.resetPopupColor(node);
        }
        else {
            GetUINativeModule().alphabetIndexer.setPopupColor(node, this.value.color);
        }
    }
}
PopupColorModifier.identity = Symbol("popupColor");
class SelectedColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().alphabetIndexer.resetSelectedColor(node);
        }
        else {
            GetUINativeModule().alphabetIndexer.setSelectedColor(node, this.value.color);
        }
    }
}
SelectedColorModifier.identity = Symbol("selectedColor");
class PopupBackgroundModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().alphabetIndexer.resetPopupBackground(node);
        }
        else {
            GetUINativeModule().alphabetIndexer.setPopupBackground(node, this.value.color);
        }
    }
}
PopupBackgroundModifier.identity = Symbol("popupBackground");
class SelectedBackgroundColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().alphabetIndexer.resetSelectedBackgroundColor(node);
        }
        else {
            GetUINativeModule().alphabetIndexer.setSelectedBackgroundColor(node, this.value.color);
        }
    }
}
SelectedBackgroundColorModifier.identity = Symbol("selectedBackgroundColor");
class PopupUnselectedColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().alphabetIndexer.resetPopupUnselectedColor(node);
        }
        else {
            GetUINativeModule().alphabetIndexer.setSelectedPopupUnselectedColor(node, this.value.color);
        }
    }
}
PopupUnselectedColorModifier.identity = Symbol("popupUnselectedColor");
class PopupSelectedColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().alphabetIndexer.resetPopupSelectedColor(node);
        }
        else {
            GetUINativeModule().alphabetIndexer.setSelectedPopupSelectedColor(node, this.value.color);
        }
    }
}
PopupSelectedColorModifier.identity = Symbol("popupSelectedColor");
class AlignStyleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().alphabetIndexer.resetAlignStyle(node);
        }
        else {
            GetUINativeModule().alphabetIndexer.setAlignStyle(node, this.value.indexerAlign, this.value.offset);
        }
    }
}
AlignStyleModifier.identity = Symbol("alignStyle");
class UsingPopupModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().alphabetIndexer.resetUsingPopup(node);
        }
        else {
            GetUINativeModule().alphabetIndexer.setUsingPopup(node, this.value);
        }
    }
}
UsingPopupModifier.identity = Symbol("usingPopup");
class AlphabetIndexerSelectedModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().alphabetIndexer.resetSelected(node);
        }
        else {
            GetUINativeModule().alphabetIndexer.setSelected(node, this.value);
        }
    }
}
AlphabetIndexerSelectedModifier.identity = Symbol("alphabetIndexerSelected");
class ItemSizeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().alphabetIndexer.resetItemSize(node);
        }
        else {
            GetUINativeModule().alphabetIndexer.setItemSize(node, this.value);
        }
    }
}
ItemSizeModifier.identity = Symbol("itemSize");
class PopupPositionModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().alphabetIndexer.resetPopupPosition(node);
        }
        else {
            GetUINativeModule().alphabetIndexer.setPopupPosition(node, this.value.x, this.value.y);
        }
    }
}
PopupPositionModifier.identity = Symbol("popupPosition");
/// <reference path="./import.ts" />
class BlankColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().blank.resetColor(node);
        }
        else {
            GetUINativeModule().blank.setColor(node, this.value);
        }
    }
}
BlankColorModifier.identity = Symbol('blankColor');
class ArkBlankComponent extends ArkComponent {
    color(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, BlankColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, BlankColorModifier, undefined);
        }
        return this;
    }
}
// @ts-ignore
globalThis.Blank.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkBlankComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class TextStyleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().calendarPicker.resetTextStyle(node);
        }
        else {
            GetUINativeModule().calendarPicker.setTextStyle(node, this.value.color, this.value.size, this.value.weight);
        }
    }
}
TextStyleModifier.identity = Symbol("textStyle");
class EdgeAlignModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().calendarPicker.resetEdgeAlign(node);
        }
        else {
            GetUINativeModule().calendarPicker.setEdgeAlign(node, this.value.alignType, this.value.offset);
        }
    }
}
EdgeAlignModifier.identity = Symbol("edgeAlign");
class ArkCalendarPickerComponent extends ArkComponent {
    edgeAlign(alignType, offset) {
        if (typeof alignType === "object") {
            modifier(this._modifiers, EdgeAlignModifier, alignType);
        }
        else {
            modifier(this._modifiers, EdgeAlignModifier, undefined);
        }
        return this;
    }
    textStyle(value) {
        if (typeof value === "object") {
            let pickerTextStyle = new ArkPickerTextStyle();
            pickerTextStyle.setColor(value.color);
            pickerTextStyle.setSize(value.font.size);
            pickerTextStyle.setWeight(value.font.weight);
            modifier(this._modifiers, TextStyleModifier, pickerTextStyle);
        }
        else {
            modifier(this._modifiers, TextStyleModifier, undefined);
        }
        return this;
    }
    onChange(callback) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.CalendarPicker.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkCalendarPickerComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkDataPanelComponent extends ArkComponent {
    closeEffect(value) {
        throw new Error("Method not implemented.");
    }
    valueColors(value) {
        throw new Error("Method not implemented.");
    }
    trackBackgroundColor(value) {
        throw new Error("Method not implemented.");
    }
    strokeWidth(value) {
        throw new Error("Method not implemented.");
    }
    trackShadow(value) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.DataPanel.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkDataPanelComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkDatePickerComponent extends ArkComponent {
    lunar(value) {
        modifier(this._modifiers, DatePickerLunarModifier, isBoolean(value) ? value : false);
        return this;
    }
    disappearTextStyle(value) {
        let pickerText = new ArkDatePickerTextStyle();
        pickerText.color = value.color;
        pickerText.font = value.font;
        modifier(this._modifiers, DatePickerDisappearTextStyleModifier, pickerText);
        return this;
    }
    textStyle(value) {
        let pickerText = new ArkDatePickerTextStyle();
        pickerText.color = value.color;
        pickerText.font = value.font;
        modifier(this._modifiers, DatePickerTextStyleModifier, pickerText);
        return this;
    }
    selectedTextStyle(value) {
        let pickerText = new ArkDatePickerTextStyle();
        pickerText.color = value.color;
        pickerText.font = value.font;
        modifier(this._modifiers, DatePickerSelectedTextStyleModifier, pickerText);
        return this;
    }
    onChange(callback) {
        throw new Error("Method not implemented.");
    }
    onDateChange(callback) {
        throw new Error("Method not implemented.");
    }
}
class DatePickerLunarModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().datePicker.resetShowLunar(node);
        }
        else {
            GetUINativeModule().datePicker.setShowLunar(node, this.value);
        }
    }
}
DatePickerLunarModifier.identity = Symbol("lunar");
class DatePickerTextStyleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().datePicker.resetNormalTextStyle(node);
        }
        else {
            GetUINativeModule().datePicker.setNormalTextStyle(node, this.value.color, this.value.font.size, this.value.font.weight, this.value.font.family, this.value.font.style);
        }
    }
}
DatePickerTextStyleModifier.identity = Symbol("textStyle");
class DatePickerSelectedTextStyleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().datePicker.resetSelectedTextStyle(node);
        }
        else {
            GetUINativeModule().datePicker.setSelectedTextStyle(node, this.value.color, this.value.font.size, this.value.font.weight, this.value.font.family, this.value.font.style);
        }
    }
}
DatePickerSelectedTextStyleModifier.identity = Symbol("selectedTextStyle");
class DatePickerDisappearTextStyleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().datePicker.resetDisappearTextStyle(node);
        }
        else {
            GetUINativeModule().datePicker.setDisappearTextStyle(node, this.value.color, this.value.font.size, this.value.font.weight, this.value.font.family, this.value.font.style);
        }
    }
}
DatePickerDisappearTextStyleModifier.identity = Symbol("disappearTextStyle");
//@ts-ignore
globalThis.DatePicker.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkDatePickerComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkFormComponentComponent extends ArkComponent {
    size(value) {
        if (isObject(value)) {
            let size = new ArkBlockSize();
            size.width = value.width;
            size.height = value.height;
            modifier(this._modifiers, FormComponentSizeModifier, size);
        }
        else {
            modifier(this._modifiers, FormComponentSizeModifier, undefined);
        }
        return this;
    }
    visibility(value) {
        if (isNumber(value)) {
            modifier(this._modifiers, FormComponentVisibilityModifier, value);
        }
        else {
            modifier(this._modifiers, FormComponentVisibilityModifier, undefined);
        }
        return this;
    }
    moduleName(value) {
        if (isString(value)) {
            modifier(this._modifiers, FormComponentModuleNameModifier, value);
        }
        else {
            modifier(this._modifiers, FormComponentModuleNameModifier, undefined);
        }
        return this;
    }
    dimension(value) {
        if (isNumber(value)) {
            modifier(this._modifiers, FormComponentDimensionModifier, value);
        }
        else {
            modifier(this._modifiers, FormComponentDimensionModifier, undefined);
        }
        return this;
    }
    allowUpdate(value) {
        if (isBoolean(value)) {
            modifier(this._modifiers, FormComponentAllowUpdateModifier, value);
        }
        else {
            modifier(this._modifiers, FormComponentAllowUpdateModifier, undefined);
        }
        return this;
    }
    onAcquired(callback) {
        throw new Error("Method not implemented.");
    }
    onError(callback) {
        throw new Error("Method not implemented.");
    }
    onRouter(callback) {
        throw new Error("Method not implemented.");
    }
    onUninstall(callback) {
        throw new Error("Method not implemented.");
    }
    onLoad(callback) {
        throw new Error("Method not implemented.");
    }
}
class FormComponentModuleNameModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().formComponent.resetModuleName(node);
        }
        else {
            GetUINativeModule().formComponent.setModuleName(node, this.value);
        }
    }
}
FormComponentModuleNameModifier.identity = Symbol("formComponentModuleName");
class FormComponentDimensionModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().formComponent.resetDimension(node);
        }
        else {
            GetUINativeModule().formComponent.setDimension(node, this.value);
        }
    }
}
FormComponentDimensionModifier.identity = Symbol("formComponentDimension");
class FormComponentAllowUpdateModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().formComponent.resetAllowUpdate(node);
        }
        else {
            GetUINativeModule().formComponent.setAllowUpdate(node, this.value);
        }
    }
}
FormComponentAllowUpdateModifier.identity = Symbol("formComponentAllowUpdate");
class FormComponentSizeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().formComponent.resetSize(node);
        }
        else {
            GetUINativeModule().formComponent.setSize(node, this.value.width, this.value.width);
        }
    }
}
FormComponentSizeModifier.identity = Symbol("formComponentSize");
class FormComponentVisibilityModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().formComponent.resetVisibility(node);
        }
        else {
            GetUINativeModule().formComponent.setVisibility(node, this.value);
        }
    }
}
FormComponentVisibilityModifier.identity = Symbol("formComponentVisibility");
// @ts-ignore
globalThis.FormComponent.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkFormComponentComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkGaugeComponent extends ArkComponent {
    value(value) {
        throw new Error("Method not implemented.");
    }
    startAngle(angle) {
        throw new Error("Method not implemented.");
    }
    endAngle(angle) {
        throw new Error("Method not implemented.");
    }
    colors(colors) {
        throw new Error("Method not implemented.");
    }
    strokeWidth(length) {
        throw new Error("Method not implemented.");
    }
    description(value) {
        throw new Error("Method not implemented.");
    }
    trackShadow(value) {
        throw new Error("Method not implemented.");
    }
    indicator(value) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Gauge.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkGaugeComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ImageAnimatorImagesModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().imageAnimator.resetImages(node);
        }
        else {
            GetUINativeModule().imageAnimator.setImages(node, this.value.arrSrc, this.value.arrWidth, this.value.arrHeight, this.value.arrTop, this.value.arrLeft, this.value.arrDuration, this.value.arrSrc.length);
        }
    }
}
ImageAnimatorImagesModifier.identity = Symbol('imageAnimatorImages');
class ImageAnimatorDurationModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().imageAnimator.resetDuration(node);
        }
        else {
            GetUINativeModule().imageAnimator.setDuration(node, this.value);
        }
    }
}
ImageAnimatorDurationModifier.identity = Symbol('imageAnimatorDuration');
class ImageAnimatorReverseModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().imageAnimator.resetReverse(node);
        }
        else {
            GetUINativeModule().imageAnimator.setReverse(node, this.value);
        }
    }
}
ImageAnimatorReverseModifier.identity = Symbol('imageAnimatorReverse');
class ImageAnimatorPreDecodeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().imageAnimator.resetPreDecode(node);
        }
        else {
            GetUINativeModule().imageAnimator.setPreDecode(node, this.value);
        }
    }
}
ImageAnimatorPreDecodeModifier.identity = Symbol('imageAnimatorPreDecode');
class ImageAnimatorStateModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().imageAnimator.resetState(node);
        }
        else {
            GetUINativeModule().imageAnimator.setState(node, this.value);
        }
    }
}
ImageAnimatorStateModifier.identity = Symbol('imageAnimatorState');
class ImageAnimatorFixedSizeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().imageAnimator.resetFixedSize(node);
        }
        else {
            GetUINativeModule().imageAnimator.setFixedSize(node, this.value);
        }
    }
}
ImageAnimatorFixedSizeModifier.identity = Symbol('imageAnimatorFixedSize');
class ImageAnimatorFillModeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().imageAnimator.resetFillMode(node);
        }
        else {
            GetUINativeModule().imageAnimator.setFillMode(node, this.value);
        }
    }
}
ImageAnimatorFillModeModifier.identity = Symbol('imageAnimatorFillMode');
class ImageAnimatorIterationsModeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().imageAnimator.resetIterations(node);
        }
        else {
            GetUINativeModule().imageAnimator.setIterations(node, this.value);
        }
    }
}
ImageAnimatorIterationsModeModifier.identity = Symbol('imageAnimatorIterationsMode');
class ArkImageAnimatorComponent extends ArkComponent {
    images(value) {
        if (value && value.length > 0) {
            let isFlag = true;
            for (let item of value) {
                if (item.src === undefined || item.src === null) {
                    isFlag = false;
                    break;
                }
            }
            if (isFlag) {
                let array = new ArkImageFrameInfoToArray();
                for (let item of value) {
                    array.arrSrc.push(item.src);
                    array.arrWidth.push(item.width === undefined || item.width === null ? 0 : item.width);
                    array.arrHeight.push(item.height === undefined || item.height === null ? 0 : item.height);
                    array.arrTop.push(item.top === undefined || item.top === null ? 0 : item.top);
                    array.arrLeft.push(item.left === undefined || item.left === null ? 0 : item.left);
                    array.arrDuration.push(item.duration === undefined || item.duration === null ? 0 : item.duration);
                }
                modifier(this._modifiers, ImageAnimatorImagesModifier, array);
            }
            else {
                modifier(this._modifiers, ImageAnimatorImagesModifier, undefined);
            }
        }
        else {
            modifier(this._modifiers, ImageAnimatorImagesModifier, undefined);
        }
        return this;
    }
    state(value) {
        if (value) {
            modifier(this._modifiers, ImageAnimatorStateModifier, value);
        }
        else {
            modifier(this._modifiers, ImageAnimatorStateModifier, AnimationStatus.Initial);
        }
        return this;
    }
    duration(value) {
        modifier(this._modifiers, ImageAnimatorDurationModifier, value);
        return this;
    }
    reverse(value) {
        modifier(this._modifiers, ImageAnimatorReverseModifier, value);
        return this;
    }
    fixedSize(value) {
        modifier(this._modifiers, ImageAnimatorFixedSizeModifier, value);
        return this;
    }
    preDecode(value) {
        throw new Error('Method not implemented.');
    }
    fillMode(value) {
        if (value) {
            modifier(this._modifiers, ImageAnimatorFillModeModifier, value);
        }
        else {
            modifier(this._modifiers, ImageAnimatorFillModeModifier, FillMode.Forwards);
        }
        return this;
    }
    iterations(value) {
        modifier(this._modifiers, ImageAnimatorIterationsModeModifier, value);
        return this;
    }
    onStart(event) {
        throw new Error('Method not implemented.');
    }
    onPause(event) {
        throw new Error('Method not implemented.');
    }
    onRepeat(event) {
        throw new Error('Method not implemented.');
    }
    onCancel(event) {
        throw new Error('Method not implemented.');
    }
    onFinish(event) {
        throw new Error('Method not implemented.');
    }
    monopolizeEvents(monopolize) {
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
/// <reference path="./import.ts" />
class ImageSpanObjectFitModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().imageSpan.resetObjectFit(node);
        }
        else {
            GetUINativeModule().imageSpan.setObjectFit(node, this.value);
        }
    }
}
ImageSpanObjectFitModifier.identity = Symbol('imageSpanObjectFit');
class ImageSpanVerticalAlignModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().imageSpan.resetVerticalAlign(node);
        }
        else {
            GetUINativeModule().imageSpan.setVerticalAlign(node, this.value);
        }
    }
}
ImageSpanVerticalAlignModifier.identity = Symbol('imageSpanVerticalAlign');
class ArkImageSpanComponent extends ArkComponent {
    objectFit(value) {
        if (value) {
            modifier(this._modifiers, ImageSpanObjectFitModifier, value);
        }
        else {
            modifier(this._modifiers, ImageSpanObjectFitModifier, undefined);
        }
        return this;
    }
    verticalAlign(value) {
        if (value) {
            modifier(this._modifiers, ImageSpanVerticalAlignModifier, value);
        }
        else {
            modifier(this._modifiers, ImageSpanVerticalAlignModifier, undefined);
        }
        return this;
    }
}
// @ts-ignore
globalThis.ImageSpan.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkImageSpanComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkMarqueeComponent extends ArkComponent {
    fontColor(value) {
        throw new Error("Method not implemented.");
    }
    fontSize(value) {
        throw new Error("Method not implemented.");
    }
    allowScale(value) {
        throw new Error("Method not implemented.");
    }
    fontWeight(value) {
        throw new Error("Method not implemented.");
    }
    fontFamily(value) {
        throw new Error("Method not implemented.");
    }
    onStart(event) {
        throw new Error("Method not implemented.");
    }
    onBounce(event) {
        throw new Error("Method not implemented.");
    }
    onFinish(event) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Marquee.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkMarqueeComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class MenuFontColorModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetMenuFontColor(node);
        }
        else {
            GetUINativeModule().common.setMenuFontColor(node, this.value);
        }
    }
    checkObjectDiff() {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        }
        else {
            return true;
        }
    }
}
MenuFontColorModifier.identity = Symbol("fontColor");
class MenuFontModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().menu.resetFont(node);
        }
        else {
            GetUINativeModule().menu.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
    }
}
MenuFontModifier.identity = Symbol("font");
class RadiusModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().menu.resetRadius(node);
        }
        else {
            GetUINativeModule().menu.setRadius(node, this.value.topLeft, this.value.topRight, this.value.bottomLeft, this.value.bottomRight);
        }
    }
}
RadiusModifier.identity = Symbol("radius");
class ArkMenuComponent extends ArkComponent {
    fontSize(value) {
        throw new Error("Method not implemented.");
    }
    font(value) {
        let font = new ArkFont();
        if (isObject(value)) {
            font.setSize(value.size);
            font.parseFontWeight(value.weight);
            font.setFamily(value.family);
            font.setStyle(value.style);
        }
        modifier(this._modifiers, MenuFontModifier, font);
        return this;
    }
    fontColor(value) {
        modifierWithKey(this._modifiersWithKeys, MenuFontColorModifier.identity, MenuFontColorModifier, value);
        return this;
    }
    radius(value) {
        let radius = new ArkBorderRadius();
        if (typeof value === "number" || typeof value === "string") {
            radius.topLeft = value;
            radius.topRight = value;
            radius.bottomLeft = value;
            radius.bottomRight = value;
        }
        else {
            radius.topLeft = value === null || value === void 0 ? void 0 : value.topRight;
            radius.topRight = value === null || value === void 0 ? void 0 : value.topRight;
            radius.bottomLeft = value === null || value === void 0 ? void 0 : value.bottomLeft;
            radius.bottomRight = value === null || value === void 0 ? void 0 : value.bottomRight;
        }
        modifier(this._modifiers, RadiusModifier, radius);
        return this;
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Menu.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkMenuComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class MenuItemSelectedModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().menuitem.resetSelected(node);
        }
        else {
            GetUINativeModule().menuitem.setSelected(node, this.value);
        }
    }
}
MenuItemSelectedModifier.identity = Symbol("selected");
class LabelFontColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().menuitem.resetLabelFontColor(node);
        }
        else {
            GetUINativeModule().menuitem.setLabelFontColor(node, this.value);
        }
    }
}
LabelFontColorModifier.identity = Symbol("labelfontColor");
class ContentFontColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().menuitem.resetContentFontColor(node);
        }
        else {
            GetUINativeModule().menuitem.setContentFontColor(node, this.value);
        }
    }
}
ContentFontColorModifier.identity = Symbol("contentfontColor");
class LabelFontModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().menu.resetLabelFont(node);
        }
        else {
            GetUINativeModule().menu.setLabelFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
    }
}
LabelFontModifier.identity = Symbol("labelFont");
class ContentFontModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().menu.resetContentFont(node);
        }
        else {
            GetUINativeModule().menu.setContentFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
    }
}
ContentFontModifier.identity = Symbol("contentFont");
class ArkMenuItemComponent extends ArkComponent {
    selected(value) {
        if (typeof value === "boolean") {
            modifier(this._modifiers, MenuItemSelectedModifier, value);
        }
        else {
            modifier(this._modifiers, MenuItemSelectedModifier, false);
        }
        return this;
    }
    selectIcon(value) {
        throw new Error("Method not implemented.");
    }
    onChange(callback) {
        throw new Error("Method not implemented.");
    }
    contentFont(value) {
        let font = new ArkFont();
        if (isObject(value)) {
            font.setSize(value.size);
            font.parseFontWeight(value.weight);
            font.setFamily(value.family);
            font.setStyle(value.style);
        }
        modifier(this._modifiers, ContentFontModifier, font);
        return this;
    }
    contentFontColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, ContentFontColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, ContentFontColorModifier, undefined);
        }
        return this;
    }
    labelFont(value) {
        let font = new ArkFont();
        if (isObject(value)) {
            font.setSize(value.size);
            font.parseFontWeight(value.weight);
            font.setFamily(value.family);
            font.setStyle(value.style);
        }
        modifier(this._modifiers, LabelFontModifier, font);
        return this;
    }
    labelFontColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, LabelFontColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, LabelFontColorModifier, undefined);
        }
        return this;
    }
}
// @ts-ignore
globalThis.MenuItem.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkMenuItemComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkMenuItemGroupComponent extends ArkComponent {
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.MenuItemGroup.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkMenuItemGroupComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class PatternLockActiveColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().patternLock.resetActiveColor(node);
        }
        else {
            GetUINativeModule().patternLock.setActiveColor(node, this.value);
        }
    }
}
PatternLockActiveColorModifier.identity = Symbol('patternLockActiveColor');
class PatternLockSelectedColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().patternLock.resetSelectedColor(node);
        }
        else {
            GetUINativeModule().patternLock.setSelectedColor(node, this.value);
        }
    }
}
PatternLockSelectedColorModifier.identity = Symbol('patternLockSelectedColor');
class PatternLockPathColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().patternLock.resetPathColor(node);
        }
        else {
            GetUINativeModule().patternLock.setPathColor(node, this.value);
        }
    }
}
PatternLockPathColorModifier.identity = Symbol('patternLockPathColor');
class PatternLockRegularColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().patternLock.resetRegularColor(node);
        }
        else {
            GetUINativeModule().patternLock.setRegularColor(node, this.value);
        }
    }
}
PatternLockRegularColorModifier.identity = Symbol('patternLockRegularColor');
class PatternLockSideLengthModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().patternLock.resetSideLength(node);
        }
        else {
            GetUINativeModule().patternLock.setSideLength(node, this.value);
        }
    }
}
PatternLockSideLengthModifier.identity = Symbol('patternLockSideLength');
class PatternLockPathStrokeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().patternLock.resetPathStrokeWidth(node);
        }
        else {
            GetUINativeModule().patternLock.setPathStrokeWidth(node, this.value);
        }
    }
}
PatternLockPathStrokeModifier.identity = Symbol('patternLockPathStroke');
class PatternLockCircleRadiusModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().patternLock.resetCircleRadius(node);
        }
        else {
            GetUINativeModule().patternLock.setCircleRadius(node, this.value);
        }
    }
}
PatternLockCircleRadiusModifier.identity = Symbol('patternLockCircleRadius');
class PatternLockAutoResetModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().patternLock.resetAutoReset(node);
        }
        else {
            GetUINativeModule().patternLock.setAutoReset(node, this.value);
        }
    }
}
PatternLockAutoResetModifier.identity = Symbol('patternlockautoreset');
class ArkPatternLockComponent extends ArkComponent {
    sideLength(value) {
        let arkValue = 288;
        if (isLengthType(value)) {
            let _value = value;
            modifier(this._modifiers, PatternLockSideLengthModifier, _value);
        }
        else {
            modifier(this._modifiers, PatternLockSideLengthModifier, arkValue);
        }
        return this;
    }
    circleRadius(value) {
        let arkValue = 6;
        if (isLengthType(value)) {
            let _value = value;
            modifier(this._modifiers, PatternLockSideLengthModifier, _value);
        }
        else {
            modifier(this._modifiers, PatternLockCircleRadiusModifier, arkValue);
        }
        return this;
    }
    regularColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, PatternLockRegularColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, PatternLockRegularColorModifier, undefined);
        }
        return this;
    }
    selectedColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, PatternLockSelectedColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, PatternLockSelectedColorModifier, undefined);
        }
        return this;
    }
    activeColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, PatternLockActiveColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, PatternLockActiveColorModifier, undefined);
        }
        return this;
    }
    pathColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, PatternLockPathColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, PatternLockPathColorModifier, undefined);
        }
        return this;
    }
    pathStrokeWidth(value) {
        let arkValue = 12;
        if (isLengthType(value)) {
            let _value = value;
            modifier(this._modifiers, PatternLockPathStrokeModifier, _value);
        }
        else {
            modifier(this._modifiers, PatternLockPathStrokeModifier, arkValue);
        }
        return this;
    }
    autoReset(value) {
        let arkValue = false;
        if (isBoolean(value)) {
            arkValue = value;
        }
        modifier(this._modifiers, PatternLockAutoResetModifier, arkValue);
        return this;
    }
    onPatternComplete(callback) {
        throw new Error('Method not implemented.');
    }
    onDotConnect(callback) {
        throw new Error('Method not implemented.');
    }
    monopolizeEvents(monopolize) {
        throw new Error('Method not implemented.');
    }
}
// @ts-ignore
globalThis.PatternLock.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkPatternLockComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkPluginComponentComponent extends ArkComponent {
    onComplete(callback) {
        throw new Error("Method not implemented.");
    }
    onError(callback) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.PluginComponent.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkPluginComponentComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkProgressComponent extends ArkComponent {
    value(value) {
        throw new Error("Method not implemented.");
    }
    color(value) {
        throw new Error("Method not implemented.");
    }
    style(value) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Progress.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkProgressComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkQRCodeComponent extends ArkComponent {
    color(value) {
        throw new Error("Method not implemented.");
    }
    contentOpacity(value) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.QRCode.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkQRCodeComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkRemoteWindowComponent extends ArkComponent {
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.RemoteWindow.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkRemoteWindowComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkRichTextComponent extends ArkComponent {
    onStart(callback) {
        throw new Error('Method not implemented.');
    }
    onComplete(callback) {
        throw new Error('Method not implemented.');
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.RichText.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkRichTextComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkScrollBarComponent extends ArkComponent {
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.ScrollBar.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkScrollBarComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class SearchSelectionMenuHiddenModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().search.resetSelectionMenuHidden(node);
        }
        else {
            GetUINativeModule().search.setSelectionMenuHidden(node, this.value);
        }
    }
}
SearchSelectionMenuHiddenModifier.identity = Symbol('searchSelectionMenuHidden');
class SearchCaretStyleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().search.resetCaretStyle(node);
        }
        else {
            GetUINativeModule().search.setCaretStyle(node, this.value.width, this.value.color);
        }
    }
}
SearchCaretStyleModifier.identity = Symbol('searchCaretStyle');
class SearchEnableKeyboardOnFocusModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().search.resetEnableKeyboardOnFocus(node);
        }
        else {
            GetUINativeModule().search.setEnableKeyboardOnFocus(node, this.value);
        }
    }
}
SearchEnableKeyboardOnFocusModifier.identity = Symbol('searchEnableKeyboardOnFocus');
class SearchSearchIconModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().search.resetSearchIcon(node);
        }
        else {
            GetUINativeModule().search.setSearchIcon(node, this.value.size, this.value.color, this.value.src);
        }
    }
}
SearchSearchIconModifier.identity = Symbol('searchSearchIcon');
class SearchPlaceholderFontModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().search.resetPlaceholderFont(node);
        }
        else {
            GetUINativeModule().search.setPlaceholderFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
    }
}
SearchPlaceholderFontModifier.identity = Symbol('searchPlaceholderFont');
class SearchSearchButtonModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().search.resetSearchButton(node);
        }
        else {
            GetUINativeModule().search.setSearchButton(node, this.value.value, this.value.fontSize, this.value.fontColor);
        }
    }
}
SearchSearchButtonModifier.identity = Symbol('searchSearchButton');
class SearchFontColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().search.resetFontColor(node);
        }
        else {
            GetUINativeModule().search.setFontColor(node, this.value);
        }
    }
}
SearchFontColorModifier.identity = Symbol('searchFontColor');
class SearchCopyOptionModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().search.resetCopyOption(node);
        }
        else {
            GetUINativeModule().search.setCopyOption(node, this.value);
        }
    }
}
SearchCopyOptionModifier.identity = Symbol('searchCopyOption');
class SearchTextFontModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().search.resetTextFont(node);
        }
        else {
            GetUINativeModule().search.setTextFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
    }
}
SearchTextFontModifier.identity = Symbol('searchTextFont');
class SearchPlaceholderColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().search.resetPlaceholderColor(node);
        }
        else {
            GetUINativeModule().search.setPlaceholderColor(node, this.value);
        }
    }
}
SearchPlaceholderColorModifier.identity = Symbol('searchPlaceholderColor');
class SearchCancelButtonModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().search.resetCancelButton(node);
        }
        else {
            GetUINativeModule().search.setCancelButton(node, this.value.style, this.value.size, this.value.color, this.value.src);
        }
    }
}
SearchCancelButtonModifier.identity = Symbol('searchCancelButton');
class SearchTextAlignModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().search.resetTextAlign(node);
        }
        else {
            GetUINativeModule().search.setTextAlign(node, this.value);
        }
    }
}
SearchTextAlignModifier.identity = Symbol('searchTextAlign');
class ArkSearchComponent extends ArkComponent {
    onEditChange(callback) {
        throw new Error('Method not implemented.');
    }
    type(value) {
        throw new Error('Method not implemented.');
    }
    maxLength(value) {
        throw new Error('Method not implemented.');
    }
    onEditChanged(callback) {
        throw new Error('Method not implemented.');
    }
    customKeyboard(event) {
        throw new Error('Method not implemented.');
    }
    showUnit(event) {
        throw new Error('Method not implemented.');
    }
    onContentScroll(callback) {
        throw new Error('Method not implemented.');
    }
    onChange(callback) {
        throw new Error('Method not implemented.');
    }
    onTextSelectionChange(callback) {
        throw new Error('Method not implemented.');
    }
    onCopy(callback) {
        throw new Error('Method not implemented.');
    }
    onCut(callback) {
        throw new Error('Method not implemented.');
    }
    onSubmit(callback) {
        throw new Error('Method not implemented.');
    }
    onPaste(callback) {
        throw new Error('Method not implemented.');
    }
    showCounter(value) {
        throw new Error('Method not implemented.');
    }
    searchButton(value, option) {
        let searchButton = new ArkSearchButton();
        if (!isString(value)) {
            value = '';
        }
        if (isObject(option)) {
            if (!isLengthType(option.fontSize)) {
                option.fontSize = '';
            }
            let fontColor = option.fontColor;
            let arkColor = new ArkColor();
            if (fontColor === undefined || fontColor === null || !arkColor.parseColorValue(fontColor)) {
                option.fontColor = undefined;
            }
            else {
                option.fontColor = arkColor.color;
            }
        }
        else {
            option.fontSize = '';
            option.fontColor = undefined;
        }
        searchButton.value = value;
        searchButton.fontColor = option.fontColor;
        searchButton.fontSize = option.fontSize;
        modifier(this._modifiers, SearchSearchButtonModifier, searchButton);
        return this;
    }
    selectionMenuHidden(value) {
        if (value === undefined || !isBoolean(value)) {
            modifier(this._modifiers, SearchSelectionMenuHiddenModifier, false);
            return this;
        }
        modifier(this._modifiers, SearchSelectionMenuHiddenModifier, value);
        return this;
    }
    enableKeyboardOnFocus(value) {
        if (value === undefined || !isBoolean(value)) {
            modifier(this._modifiers, SearchEnableKeyboardOnFocusModifier, true);
            return this;
        }
        modifier(this._modifiers, SearchEnableKeyboardOnFocusModifier, value);
        return this;
    }
    caretStyle(value) {
        let arkCaretStyle = new ArkCaretStyle();
        if (isObject(value)) {
            let caretWidth = value.width;
            if (!isLengthType(caretWidth)) {
                arkCaretStyle.width = undefined;
            }
            else {
                arkCaretStyle.width = caretWidth;
            }
            let caretColor = value.color;
            let arkColor = new ArkColor();
            if (!caretColor || !arkColor.parseColorValue(caretColor)) {
                caretColor = undefined;
            }
            else {
                caretColor = arkColor.color;
            }
            arkCaretStyle.color = caretColor;
            modifier(this._modifiers, SearchCaretStyleModifier, arkCaretStyle);
        }
        return this;
    }
    cancelButton(value) {
        let cancelButton = new ArkCancelButton();
        if (!isObject(value)) {
            return this;
        }
        let style = value.style;
        if (!style || isNaN(style)) {
            style = CancelButtonStyle.INPUT;
        }
        value.style = style;
        cancelButton.style = value.style;
        let icon = value.icon;
        if (!icon || !isObject(icon)) {
            icon.size = '';
            icon.color = undefined;
            icon.src = '';
        }
        else {
            if (!icon.size || !isLengthType(icon.size)) {
                icon.size = '';
            }
            if (!icon.src || !isString(icon.src)) {
                icon.src = '';
            }
            let arkColor = new ArkColor();
            if (!icon.color || !arkColor.parseColorValue(icon.color)) {
                icon.color = undefined;
            }
            else {
                icon.color = arkColor.color;
            }
        }
        cancelButton.color = icon.color;
        cancelButton.size = icon.size;
        cancelButton.src = icon.src;
        modifier(this._modifiers, SearchCancelButtonModifier, cancelButton);
        return this;
    }
    searchIcon(value) {
        let iconOptions = new ArkIconOptions();
        if (!isObject(value)) {
            iconOptions.size = '';
            iconOptions.color = undefined;
            iconOptions.src = '';
        }
        else {
            iconOptions.size = value.size;
            iconOptions.color = value.color;
            iconOptions.src = value.src;
            if (!iconOptions.size || !isLengthType(iconOptions.size)) {
                iconOptions.size = '';
            }
            if (!iconOptions.src || !isString(iconOptions.src)) {
                iconOptions.src = '';
            }
            let arkColor = new ArkColor();
            if (!iconOptions.color || !arkColor.parseColorValue(iconOptions.color)) {
                iconOptions.color = undefined;
            }
            else {
                iconOptions.color = arkColor.color;
            }
            modifier(this._modifiers, SearchSearchIconModifier, iconOptions);
        }
        return this;
    }
    fontColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, SearchFontColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, SearchFontColorModifier, undefined);
        }
        return this;
    }
    placeholderColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, SearchPlaceholderColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, SearchPlaceholderColorModifier, undefined);
        }
        return this;
    }
    placeholderFont(value) {
        let arkValue = new ArkFont();
        if (isLengthType(value.size)) {
            arkValue.size = value.size;
        }
        if (isLengthType(value.weight)) {
            arkValue.weight = value.weight;
        }
        if (isString(value.family)) {
            arkValue.family = value.family;
        }
        if (value.style in FontStyle) {
            arkValue.style = value.style;
        }
        modifier(this._modifiers, SearchPlaceholderFontModifier, arkValue);
        return this;
    }
    textFont(value) {
        let arkValue = new ArkFont();
        if (isLengthType(value.size)) {
            arkValue.size = value.size;
        }
        if (isLengthType(value.weight)) {
            arkValue.weight = value.weight;
        }
        if (isString(value.family)) {
            arkValue.family = value.family;
        }
        if (value.style in FontStyle) {
            arkValue.style = value.style;
        }
        modifier(this._modifiers, SearchTextFontModifier, arkValue);
        return this;
    }
    copyOption(value) {
        if (value === undefined) {
            value = CopyOptions.LocalDevice;
            modifier(this._modifiers, SearchCopyOptionModifier, value);
        }
        let copyOptions = CopyOptions.None;
        if (isNumber(value)) {
            copyOptions = value;
        }
        modifier(this._modifiers, SearchCopyOptionModifier, copyOptions);
        return this;
    }
    textAlign(value) {
        let TEXT_ALIGNS = [
            TextAlign.Start, TextAlign.Center, TextAlign.End, TextAlign.JUSTIFY
        ];
        if (value >= 0 && value <= TEXT_ALIGNS.length) {
            modifier(this._modifiers, SearchTextAlignModifier, value);
        }
        return this;
    }
}
// @ts-ignore
globalThis.Search.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkSearchComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class SpanFontSizeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().span.resetFontSize(node);
        }
        else {
            GetUINativeModule().span.setFontSize(node, this.value);
        }
    }
}
SpanFontSizeModifier.identity = Symbol('spanFontSize');
class SpanFontFamilyModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().span.resetFontFamily(node);
        }
        else {
            GetUINativeModule().span.setFontFamily(node, this.value);
        }
    }
}
SpanFontFamilyModifier.identity = Symbol('spanFontFamily');
class SpanLineHeightModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().span.resetLineHeight(node);
        }
        else {
            GetUINativeModule().span.setLineHeight(node, this.value);
        }
    }
}
SpanLineHeightModifier.identity = Symbol('spanLineHeight');
class SpanFontStyleModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().span.resetFontStyle(node);
        }
        else {
            GetUINativeModule().span.setFontStyle(node, this.value);
        }
    }
}
SpanFontStyleModifier.identity = Symbol('spanFontStyle');
class SpanTextCaseModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().span.resetTextCase(node);
        }
        else {
            GetUINativeModule().span.setTextCase(node, this.value);
        }
    }
}
SpanTextCaseModifier.identity = Symbol('spanTextCase');
class SpanFontColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().span.resetFontColor(node);
        }
        else {
            GetUINativeModule().span.setFontColor(node, this.value);
        }
    }
}
SpanFontColorModifier.identity = Symbol('spanFontColor');
class SpanLetterSpacingModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().span.resetLetterSpacing(node);
        }
        else {
            GetUINativeModule().span.setLetterSpacing(node, this.value);
        }
    }
}
SpanLetterSpacingModifier.identity = Symbol('spanLetterSpacing');
class SpanFontModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().span.resetFont(node);
        }
        else {
            GetUINativeModule().span.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
        }
    }
}
SpanFontModifier.identity = Symbol('spanFont');
class SpanDecorationModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().span.resetDecoration(node);
        }
        else {
            GetUINativeModule().span.setDecoration(node, this.value.type, this.value.color);
        }
    }
}
SpanDecorationModifier.identity = Symbol('spanDecoration');
class SpanFontWeightModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().span.resetFontWeight(node);
        }
        else {
            GetUINativeModule().span.setFontWeight(node, this.value);
        }
    }
}
SpanFontWeightModifier.identity = Symbol('spanfontweight');
class ArkSpanComponent extends ArkComponent {
    decoration(value) {
        let arkValue = new ArkDecoration();
        if (!isNumber(value.type) && !(value.type in TextDecorationType)) {
            arkValue.type = undefined;
        } else {
            arkValue.type = value.type;
        }
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value.color)) {
            arkValue.color = arkColor.color;
        }
        else {
            arkValue.color = undefined;
        }
        modifier(this._modifiers, SpanDecorationModifier, arkValue);
        return this;
    }
    font(value) {
        let arkValue = new ArkFont();
        if (isLengthType(value.size)) {
            arkValue.size = value.size;
        }
        if (isLengthType(value.weight)) {
            arkValue.weight = value.weight;
        }
        if (isString(value.family)) {
            arkValue.family = value.family;
        }
        if (value.style in FontStyle) {
            arkValue.style = value.style;
        }
        modifier(this._modifiers, SpanFontModifier, arkValue);
        return this;
    }
    lineHeight(value) {
        if (isString(value) || isNumber(value)) {
            modifier(this._modifiers, SpanLineHeightModifier, value);
        }
        else {
            modifier(this._modifiers, SpanLineHeightModifier, undefined);
        }
        return this;
    }
    fontSize(value) {
        if (isLengthType(value)) {
            modifier(this._modifiers, SpanFontSizeModifier, value);
        }
        else {
            modifier(this._modifiers, SpanFontSizeModifier, undefined);
        }
        return this;
    }
    fontColor(value) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, SpanFontColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, SpanFontColorModifier, undefined);
        }
        return this;
    }
    fontStyle(value) {
        if (!(value in FontStyle)) {
            value = FontStyle.Normal;
        }
        modifier(this._modifiers, SpanFontStyleModifier, value);
        return this;
    }
    fontWeight(value) {
        if (!isLengthType(value)) {
            modifier(this._modifiers, SpanFontWeightModifier, undefined);
        }
        else {
            modifier(this._modifiers, SpanFontWeightModifier, value);
        }
        return this;
    }
    fontFamily(value) {
        if (isString(value)) {
            modifier(this._modifiers, SpanFontFamilyModifier, value);
        }
        else {
            modifier(this._modifiers, SpanFontFamilyModifier, undefined);
        }
        return this;
    }
    letterSpacing(value) {
        if (isLengthType(value)) {
            modifier(this._modifiers, SpanLetterSpacingModifier, value);
        }
        else {
            modifier(this._modifiers, SpanLetterSpacingModifier, undefined);
        }
        return this;
    }
    textCase(value) {
        if (value in TextCase) {
            modifier(this._modifiers, SpanTextCaseModifier, value);
        }
        else {
            modifier(this._modifiers, SpanTextCaseModifier, undefined);
        }
        return this;
    }
}
// @ts-ignore
globalThis.Span.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkSpanComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkStepperComponent extends ArkComponent {
    onFinish(callback) {
        throw new Error("Method not implemented.");
    }
    onSkip(callback) {
        throw new Error("Method not implemented.");
    }
    onChange(callback) {
        throw new Error("Method not implemented.");
    }
    onNext(callback) {
        throw new Error("Method not implemented.");
    }
    onPrevious(callback) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Stepper.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkStepperComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkStepperItemComponent extends ArkComponent {
    prevLabel(value) {
        throw new Error("Method not implemented.");
    }
    nextLabel(value) {
        throw new Error("Method not implemented.");
    }
    status(value) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.StepperItem.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkStepperItemComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkTextClockComponent extends ArkComponent {
    format(value) {
        throw new Error("Method not implemented.");
    }
    onDateChange(event) {
        throw new Error("Method not implemented.");
    }
    fontColor(value) {
        throw new Error("Method not implemented.");
    }
    fontSize(value) {
        throw new Error("Method not implemented.");
    }
    fontStyle(value) {
        throw new Error("Method not implemented.");
    }
    fontWeight(value) {
        throw new Error("Method not implemented.");
    }
    fontFamily(value) {
        throw new Error("Method not implemented.");
    }
    textShadow(value) {
        throw new Error("Method not implemented.");
    }
    fontFeature(value) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.TextClock.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkTextClockComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkTextTimerComponent extends ArkComponent {
    format(value) {
        throw new Error("Method not implemented.");
    }
    fontColor(value) {
        throw new Error("Method not implemented.");
    }
    fontSize(value) {
        throw new Error("Method not implemented.");
    }
    fontStyle(value) {
        throw new Error("Method not implemented.");
    }
    fontWeight(value) {
        throw new Error("Method not implemented.");
    }
    fontFamily(value) {
        throw new Error("Method not implemented.");
    }
    onTimer(event) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.TextTimer.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkTextTimerComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkWebComponent extends ArkComponent {
    javaScriptAccess(javaScriptAccess) {
        throw new Error("Method not implemented.");
    }
    fileAccess(fileAccess) {
        throw new Error("Method not implemented.");
    }
    onlineImageAccess(onlineImageAccess) {
        throw new Error("Method not implemented.");
    }
    domStorageAccess(domStorageAccess) {
        throw new Error("Method not implemented.");
    }
    imageAccess(imageAccess) {
        throw new Error("Method not implemented.");
    }
    mixedMode(mixedMode) {
        throw new Error("Method not implemented.");
    }
    zoomAccess(zoomAccess) {
        throw new Error("Method not implemented.");
    }
    geolocationAccess(geolocationAccess) {
        throw new Error("Method not implemented.");
    }
    javaScriptProxy(javaScriptProxy) {
        throw new Error("Method not implemented.");
    }
    password(password) {
        throw new Error("Method not implemented.");
    }
    cacheMode(cacheMode) {
        throw new Error("Method not implemented.");
    }
    darkMode(mode) {
        throw new Error("Method not implemented.");
    }
    forceDarkAccess(access) {
        throw new Error("Method not implemented.");
    }
    mediaOptions(options) {
        throw new Error("Method not implemented.");
    }
    tableData(tableData) {
        throw new Error("Method not implemented.");
    }
    wideViewModeAccess(wideViewModeAccess) {
        throw new Error("Method not implemented.");
    }
    overviewModeAccess(overviewModeAccess) {
        throw new Error("Method not implemented.");
    }
    overScrollMode(mode) {
        throw new Error("Method not implemented.");
    }
    textZoomAtio(textZoomAtio) {
        throw new Error("Method not implemented.");
    }
    textZoomRatio(textZoomRatio) {
        throw new Error("Method not implemented.");
    }
    databaseAccess(databaseAccess) {
        throw new Error("Method not implemented.");
    }
    initialScale(percent) {
        throw new Error("Method not implemented.");
    }
    userAgent(userAgent) {
        throw new Error("Method not implemented.");
    }
    onPageEnd(callback) {
        throw new Error("Method not implemented.");
    }
    onPageBegin(callback) {
        throw new Error("Method not implemented.");
    }
    onProgressChange(callback) {
        throw new Error("Method not implemented.");
    }
    onTitleReceive(callback) {
        throw new Error("Method not implemented.");
    }
    onGeolocationHide(callback) {
        throw new Error("Method not implemented.");
    }
    onGeolocationShow(callback) {
        throw new Error("Method not implemented.");
    }
    onRequestSelected(callback) {
        throw new Error("Method not implemented.");
    }
    onAlert(callback) {
        throw new Error("Method not implemented.");
    }
    onBeforeUnload(callback) {
        throw new Error("Method not implemented.");
    }
    onConfirm(callback) {
        throw new Error("Method not implemented.");
    }
    onPrompt(callback) {
        throw new Error("Method not implemented.");
    }
    onConsole(callback) {
        throw new Error("Method not implemented.");
    }
    onErrorReceive(callback) {
        throw new Error("Method not implemented.");
    }
    onHttpErrorReceive(callback) {
        throw new Error("Method not implemented.");
    }
    onDownloadStart(callback) {
        throw new Error("Method not implemented.");
    }
    onRefreshAccessedHistory(callback) {
        throw new Error("Method not implemented.");
    }
    onUrlLoadIntercept(callback) {
        throw new Error("Method not implemented.");
    }
    onSslErrorReceive(callback) {
        throw new Error("Method not implemented.");
    }
    onRenderExited(callback) {
        throw new Error("Method not implemented.");
    }
    onShowFileSelector(callback) {
        throw new Error("Method not implemented.");
    }
    onFileSelectorShow(callback) {
        throw new Error("Method not implemented.");
    }
    onResourceLoad(callback) {
        throw new Error("Method not implemented.");
    }
    onFullScreenExit(callback) {
        throw new Error("Method not implemented.");
    }
    onFullScreenEnter(callback) {
        throw new Error("Method not implemented.");
    }
    onScaleChange(callback) {
        throw new Error("Method not implemented.");
    }
    onHttpAuthRequest(callback) {
        throw new Error("Method not implemented.");
    }
    onInterceptRequest(callback) {
        throw new Error("Method not implemented.");
    }
    onPermissionRequest(callback) {
        throw new Error("Method not implemented.");
    }
    onScreenCaptureRequest(callback) {
        throw new Error("Method not implemented.");
    }
    onContextMenuShow(callback) {
        throw new Error("Method not implemented.");
    }
    mediaPlayGestureAccess(access) {
        throw new Error("Method not implemented.");
    }
    onSearchResultReceive(callback) {
        throw new Error("Method not implemented.");
    }
    onScroll(callback) {
        throw new Error("Method not implemented.");
    }
    onSslErrorEventReceive(callback) {
        throw new Error("Method not implemented.");
    }
    onClientAuthenticationRequest(callback) {
        throw new Error("Method not implemented.");
    }
    onWindowNew(callback) {
        throw new Error("Method not implemented.");
    }
    onWindowExit(callback) {
        throw new Error("Method not implemented.");
    }
    multiWindowAccess(multiWindow) {
        throw new Error("Method not implemented.");
    }
    onInterceptKeyEvent(callback) {
        throw new Error("Method not implemented.");
    }
    webStandardFont(family) {
        throw new Error("Method not implemented.");
    }
    webSerifFont(family) {
        throw new Error("Method not implemented.");
    }
    webSansSerifFont(family) {
        throw new Error("Method not implemented.");
    }
    webFixedFont(family) {
        throw new Error("Method not implemented.");
    }
    webFantasyFont(family) {
        throw new Error("Method not implemented.");
    }
    webCursiveFont(family) {
        throw new Error("Method not implemented.");
    }
    defaultFixedFontSize(size) {
        throw new Error("Method not implemented.");
    }
    defaultFontSize(size) {
        throw new Error("Method not implemented.");
    }
    minFontSize(size) {
        throw new Error("Method not implemented.");
    }
    minLogicalFontSize(size) {
        throw new Error("Method not implemented.");
    }
    blockNetwork(block) {
        throw new Error("Method not implemented.");
    }
    horizontalScrollBarAccess(horizontalScrollBar) {
        throw new Error("Method not implemented.");
    }
    verticalScrollBarAccess(verticalScrollBar) {
        throw new Error("Method not implemented.");
    }
    onTouchIconUrlReceived(callback) {
        throw new Error("Method not implemented.");
    }
    onFaviconReceived(callback) {
        throw new Error("Method not implemented.");
    }
    onPageVisible(callback) {
        throw new Error("Method not implemented.");
    }
    onDataResubmitted(callback) {
        throw new Error("Method not implemented.");
    }
    pinchSmooth(isEnabled) {
        throw new Error("Method not implemented.");
    }
    allowWindowOpenMethod(flag) {
        throw new Error("Method not implemented.");
    }
    onAudioStateChanged(callback) {
        throw new Error("Method not implemented.");
    }
    onFirstContentfulPaint(callback) {
        throw new Error("Method not implemented.");
    }
    onLoadIntercept(callback) {
        throw new Error("Method not implemented.");
    }
    onControllerAttached(callback) {
        throw new Error("Method not implemented.");
    }
    onOverScroll(callback) {
        throw new Error("Method not implemented.");
    }
    javaScriptOnDocumentStart(scripts) {
        throw new Error("Method not implemented.");
    }
    layoutMode(mode) {
        throw new Error("Method not implemented.");
    }
    nestedScroll(value) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Web.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkWebComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkXComponentComponent extends ArkComponent {
    onLoad(callback) {
        throw new Error("Method not implemented.");
    }
    onDestroy(event) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.XComponent.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkXComponentComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkBadgeComponent extends ArkComponent {
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Badge.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkBadgeComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ColumnAlignItemsModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().column.resetAlignItems(node);
        }
        else {
            GetUINativeModule().column.setAlignItems(node, this.value);
        }
    }
}
ColumnAlignItemsModifier.identity = Symbol('columnAlignItems');
class ColumnJustifyContentModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().column.resetJustifyContent(node);
        }
        else {
            GetUINativeModule().column.setJustifyContent(node, this.value);
        }
    }
}
ColumnJustifyContentModifier.identity = Symbol('columnJustifyContent');
class ArkColumnComponent extends ArkComponent {
    alignItems(value) {
        if (value === null || value === undefined) {
            modifier(this._modifiers, ColumnAlignItemsModifier, undefined);
        }
        else if (!(value in HorizontalAlign)) {
            value = HorizontalAlign.Center;
            modifier(this._modifiers, ColumnAlignItemsModifier, value);
        }
        else {
            modifier(this._modifiers, ColumnAlignItemsModifier, value);
        }
        return this;
    }
    justifyContent(value) {
        if (value === null || value === undefined) {
            modifier(this._modifiers, ColumnJustifyContentModifier, undefined);
        }
        else if (!(value in FlexAlign)) {
            value = FlexAlign.Start;
            modifier(this._modifiers, ColumnJustifyContentModifier, value);
        }
        else {
            modifier(this._modifiers, ColumnJustifyContentModifier, value);
        }
        return this;
    }
    pointLight(value) {
        throw new Error('Method not implemented.');
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Column.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkColumnComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ColumnSplitDividerModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().columnSplit.resetDivider(node);
        }
        else {
            GetUINativeModule().columnSplit.setDivider(node, this.value.startMargin, this.value.endMargin);
        }
    }
}
ColumnSplitDividerModifier.identity = Symbol('columnSplitDivider');
class ColumnSplitResizeableModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().columnSplit.resetResizeable(node);
        }
        else {
            GetUINativeModule().columnSplit.setResizeable(node, this.value);
        }
    }
}
ColumnSplitResizeableModifier.identity = Symbol('columnSplitResizeable');
class ArkColumnSplitComponent extends ArkComponent {
    resizeable(value) {
        let arkResizeable = false;
        if (isBoolean(value)) {
            arkResizeable = value;
        }
        modifier(this._modifiers, ColumnSplitResizeableModifier, arkResizeable);
        return this;
    }
    divider(value) {
        let arkValue = new ArkColumnSplitDividerStyle();
        if (!value || (!isLengthType(value.startMargin) && !isLengthType(value.endMargin))) {
            modifier(this._modifiers, ColumnSplitDividerModifier, undefined);
            return this;
        }
        if (value.startMargin && isLengthType(value.startMargin)) {
            arkValue.startMargin = value.startMargin.toString();
        }
        if (value.endMargin && isLengthType(value.endMargin)) {
            arkValue.endMargin = value.endMargin.toString();
        }
        modifier(this._modifiers, ColumnSplitDividerModifier, arkValue);
        return this;
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.ColumnSplit.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkColumnSplitComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkEffectComponentComponent extends ArkComponent {
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.EffectComponent.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkEffectComponentComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkFlexComponent extends ArkComponent {
    pointLight(value) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Flex.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkFlexComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkFlowItemComponent extends ArkComponent {
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.FlowItem.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkFlowItemComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkFormLinkComponent extends ArkComponent {
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.FormLink.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkFormLinkComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class GridRowAlignItemsModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().gridRow.resetAlignItems(node);
        }
        else {
            GetUINativeModule().gridRow.setAlignItems(node, this.value);
        }
    }
}
GridRowAlignItemsModifier.identity = Symbol('gridRowAlignItems');
class ArkGridRowComponent extends ArkComponent {
    onBreakpointChange(callback) {
        throw new Error("Method not implemented.");
    }
    alignItems(value) {
        if (value) {
            modifier(this._modifiers, GridRowAlignItemsModifier, value);
        }
        else {
            modifier(this._modifiers, GridRowAlignItemsModifier, undefined);
        }
        return this;
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.GridRow.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkGridRowComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkGridComponent extends ArkComponent {
    columnsTemplate(value) {
        throw new Error("Method not implemented.");
    }
    rowsTemplate(value) {
        throw new Error("Method not implemented.");
    }
    columnsGap(value) {
        throw new Error("Method not implemented.");
    }
    rowsGap(value) {
        throw new Error("Method not implemented.");
    }
    scrollBarWidth(value) {
        throw new Error("Method not implemented.");
    }
    scrollBarColor(value) {
        throw new Error("Method not implemented.");
    }
    scrollBar(value) {
        throw new Error("Method not implemented.");
    }
    onScrollBarUpdate(event) {
        throw new Error("Method not implemented.");
    }
    onScrollIndex(event) {
        throw new Error("Method not implemented.");
    }
    cachedCount(value) {
        throw new Error("Method not implemented.");
    }
    editMode(value) {
        throw new Error("Method not implemented.");
    }
    multiSelectable(value) {
        throw new Error("Method not implemented.");
    }
    maxCount(value) {
        throw new Error("Method not implemented.");
    }
    minCount(value) {
        throw new Error("Method not implemented.");
    }
    cellLength(value) {
        throw new Error("Method not implemented.");
    }
    layoutDirection(value) {
        throw new Error("Method not implemented.");
    }
    supportAnimation(value) {
        throw new Error("Method not implemented.");
    }
    onItemDragStart(event) {
        throw new Error("Method not implemented.");
    }
    onItemDragEnter(event) {
        throw new Error("Method not implemented.");
    }
    onItemDragMove(event) {
        throw new Error("Method not implemented.");
    }
    onItemDragLeave(event) {
        throw new Error("Method not implemented.");
    }
    onItemDrop(event) {
        throw new Error("Method not implemented.");
    }
    edgeEffect(value, options) {
        throw new Error("Method not implemented.");
    }
    nestedScroll(value) {
        throw new Error("Method not implemented.");
    }
    enableScrollInteraction(value) {
        throw new Error("Method not implemented.");
    }
    friction(value) {
        throw new Error("Method not implemented.");
    }
    onScroll(event) {
        throw new Error("Method not implemented.");
    }
    onReachStart(event) {
        throw new Error("Method not implemented.");
    }
    onReachEnd(event) {
        throw new Error("Method not implemented.");
    }
    onScrollStart(event) {
        throw new Error("Method not implemented.");
    }
    onScrollStop(event) {
        throw new Error("Method not implemented.");
    }
    onScrollFrameBegin(event) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Grid.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkGridComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkGridItemComponent extends ArkComponent {
    rowStart(value) {
        throw new Error("Method not implemented.");
    }
    rowEnd(value) {
        throw new Error("Method not implemented.");
    }
    columnStart(value) {
        throw new Error("Method not implemented.");
    }
    columnEnd(value) {
        throw new Error("Method not implemented.");
    }
    forceRebuild(value) {
        throw new Error("Method not implemented.");
    }
    selectable(value) {
        throw new Error("Method not implemented.");
    }
    selected(value) {
        throw new Error("Method not implemented.");
    }
    onSelect(event) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.GridItem.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkGridItemComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkHyperlinkComponent extends ArkComponent {
    color(value) {
        if (!!value) {
            let color = new ArkBarBackgroundColor();
            color.value = value;
            modifier(this._modifiers, HyperlinkColorModifier, color);
        }
        else {
            modifier(this._modifiers, HyperlinkColorModifier, undefined);
        }
        return this;
    }
}
class HyperlinkColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().hyperlink.resetColor(node);
        }
        else {
            GetUINativeModule().hyperlink.setColor(node, this.value);
        }
    }
}
HyperlinkColorModifier.identity = Symbol("hyperlinkColor");
// @ts-ignore
globalThis.Hyperlink.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkHyperlinkComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkListComponent extends ArkComponent {
    lanes(value, gutter) {
        throw new Error("Method not implemented.");
    }
    alignListItem(value) {
        throw new Error("Method not implemented.");
    }
    listDirection(value) {
        throw new Error("Method not implemented.");
    }
    scrollBar(value) {
        throw new Error("Method not implemented.");
    }
    edgeEffect(value, options) {
        throw new Error("Method not implemented.");
    }
    contentStartOffset(value) {
        throw new Error("Method not implemented.");
    }
    contentEndOffset(value) {
        throw new Error("Method not implemented.");
    }
    divider(value) {
        throw new Error("Method not implemented.");
    }
    editMode(value) {
        throw new Error("Method not implemented.");
    }
    multiSelectable(value) {
        throw new Error("Method not implemented.");
    }
    cachedCount(value) {
        throw new Error("Method not implemented.");
    }
    chainAnimation(value) {
        throw new Error("Method not implemented.");
    }
    chainAnimationOptions(value) {
        throw new Error("Method not implemented.");
    }
    sticky(value) {
        throw new Error("Method not implemented.");
    }
    scrollSnapAlign(value) {
        throw new Error("Method not implemented.");
    }
    nestedScroll(value) {
        throw new Error("Method not implemented.");
    }
    enableScrollInteraction(value) {
        throw new Error("Method not implemented.");
    }
    friction(value) {
        throw new Error("Method not implemented.");
    }
    onScroll(event) {
        throw new Error("Method not implemented.");
    }
    onScrollIndex(event) {
        throw new Error("Method not implemented.");
    }
    onReachStart(event) {
        throw new Error("Method not implemented.");
    }
    onReachEnd(event) {
        throw new Error("Method not implemented.");
    }
    onScrollStart(event) {
        throw new Error("Method not implemented.");
    }
    onScrollStop(event) {
        throw new Error("Method not implemented.");
    }
    onItemDelete(event) {
        throw new Error("Method not implemented.");
    }
    onItemMove(event) {
        throw new Error("Method not implemented.");
    }
    onItemDragStart(event) {
        throw new Error("Method not implemented.");
    }
    onItemDragEnter(event) {
        throw new Error("Method not implemented.");
    }
    onItemDragMove(event) {
        throw new Error("Method not implemented.");
    }
    onItemDragLeave(event) {
        throw new Error("Method not implemented.");
    }
    onItemDrop(event) {
        throw new Error("Method not implemented.");
    }
    onScrollFrameBegin(event) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.List.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkListComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkListItemComponent extends ArkComponent {
    sticky(value) {
        throw new Error("Method not implemented.");
    }
    editable(value) {
        throw new Error("Method not implemented.");
    }
    selectable(value) {
        throw new Error("Method not implemented.");
    }
    selected(value) {
        throw new Error("Method not implemented.");
    }
    swipeAction(value) {
        throw new Error("Method not implemented.");
    }
    onSelect(event) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.ListItem.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkListItemComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkListItemGroupComponent extends ArkComponent {
    divider(value) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.ListItemGroup.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkListItemGroupComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkRelativeContainerComponent extends ArkComponent {
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.RelativeContainer.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkRelativeContainerComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class RowAlignItemsModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().row.resetAlignItems(node);
        }
        else {
            GetUINativeModule().row.setAlignItems(node, this.value);
        }
    }
}
RowAlignItemsModifier.identity = Symbol('rowAlignItems');
class RowJustifyContentlModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().row.resetJustifyContent(node);
        }
        else {
            GetUINativeModule().row.setJustifyContent(node, this.value);
        }
    }
}
RowJustifyContentlModifier.identity = Symbol('rowJustifyContent');
class ArkRowComponent extends ArkComponent {
    alignItems(value) {
        if (value === null || value === undefined) {
            modifier(this._modifiers, RowAlignItemsModifier, undefined);
        }
        else if (!(value in VerticalAlign)) {
            value = VerticalAlign.Center;
            modifier(this._modifiers, RowAlignItemsModifier, value);
        }
        else {
            modifier(this._modifiers, RowAlignItemsModifier, value);
        }
        return this;
    }
    justifyContent(value) {
        if (value === null || value === undefined) {
            modifier(this._modifiers, RowJustifyContentlModifier, undefined);
        }
        else if (!(value in FlexAlign)) {
            value = FlexAlign.Start;
            modifier(this._modifiers, RowJustifyContentlModifier, value);
        }
        else {
            modifier(this._modifiers, RowJustifyContentlModifier, value);
        }
        return this;
    }
    pointLight(value) {
        throw new Error('Method not implemented.');
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Row.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkRowComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class RowSplitResizeableModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().rowSplit.ResetResizeable(node);
        }
        else {
            GetUINativeModule().rowSplit.setResizeable(node, this.value);
        }
    }
}
RowSplitResizeableModifier.identity = Symbol('rowSplitResizeable');
class ArkRowSplitComponent extends ArkComponent {
    resizeable(value) {
        let arkResizeable = false;
        if (isBoolean(value)) {
            arkResizeable = value;
        }
        modifier(this._modifiers, RowSplitResizeableModifier, arkResizeable);
        return this;
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.RowSplit.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkRowSplitComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class SideBarContainerPositionModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().sideBarContainer.resetSideBarPosition(node);
        }
        else {
            GetUINativeModule().sideBarContainer.setSideBarPosition(node, this.value);
        }
    }
}
SideBarContainerPositionModifier.identity = Symbol('sideBarContainerPosition');
class SideBarContainerAutoHideModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().sideBarContainer.resetAutoHide(node);
        }
        else {
            GetUINativeModule().sideBarContainer.setAutoHide(node, this.value);
        }
    }
}
SideBarContainerAutoHideModifier.identity = Symbol('sideBarContainerautoHide');
class SideBarContainerShowSideBarModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().sideBarContainer.resetShowSideBar(node);
        }
        else {
            GetUINativeModule().sideBarContainer.setShowSideBar(node, this.value);
        }
    }
}
SideBarContainerShowSideBarModifier.identity = Symbol('sideBarContainerShowSideBar');
class SideBarContainerMaxSideBarWidthModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().sideBarContainer.resetMaxSideBarWidth(node);
        }
        else {
            GetUINativeModule().sideBarContainer.setMaxSideBarWidth(node, this.value);
        }
    }
}
SideBarContainerMaxSideBarWidthModifier.identity = Symbol('sideBarContainerMaxSideBarWidth');
class SideBarContainerWidthModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().sideBarContainer.resetSideBarWidth(node);
        }
        else {
            GetUINativeModule().sideBarContainer.setSideBarWidth(node, this.value);
        }
    }
}
SideBarContainerWidthModifier.identity = Symbol('sideBarContainerWidth');
class SideBarContainerMinContentWidthModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().sideBarContainer.resetMinContentWidth(node);
        }
        else {
            GetUINativeModule().sideBarContainer.setMinContentWidth(node, this.value);
        }
    }
}
SideBarContainerMinContentWidthModifier.identity = Symbol('sideBarContainerMinContentWidth');
class SideBarContainerShowControlButtonModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().sideBarContainer.resetShowControlButton(node);
        }
        else {
            GetUINativeModule().sideBarContainer.setShowControlButton(node, this.value);
        }
    }
}
SideBarContainerShowControlButtonModifier.identity = Symbol('sideBarContainerShowControlButton');
class SideBarContainerMinSideBarWidthModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().sideBarContainer.resetMinSideBarWidth(node);
        }
        else {
            GetUINativeModule().sideBarContainer.setMinSideBarWidth(node, this.value);
        }
    }
}
SideBarContainerMinSideBarWidthModifier.identity = Symbol('sideBarContainerMinSideBarWidth');
class SideBarContainerControlButtonModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().sideBarContainer.resetControlButton(node);
        }
        else {
            GetUINativeModule().sideBarContainer.setControlButton(node, this.value.left, this.value.top, this.value.width, this.value.height, this.value.icons.shown, this.value.icons.hidden, this.value.icons.switching);
        }
    }
}
SideBarContainerControlButtonModifier.identity = Symbol('sideBarContainercontrolButton');
class SideBarContainerDividerModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().sideBarContainer.resetDivider(node);
        }
        else {
            GetUINativeModule().sideBarContainer.setDivider(node, this.value.strokeWidth, this.value.color, this.value.startMargin, this.value.endMargin);
        }
    }
}
SideBarContainerDividerModifier.identity = Symbol('sideBarContainerdivider');
class ArkSideBarContainerComponent extends ArkComponent {
    onChange(callback) {
        throw new Error("Method not implemented.");
    }
    autoHide(value) {
        if (isBoolean(value)) {
            modifier(this._modifiers, SideBarContainerAutoHideModifier, value);
        }
        else {
            modifier(this._modifiers, SideBarContainerAutoHideModifier, true);
        }
        return this;
    }
    showSideBar(value) {
        let isShow = true;
        if (isBoolean(value)) {
            isShow = value;
        }
        modifier(this._modifiers, SideBarContainerShowSideBarModifier, isShow);
        return this;
    }
    maxSideBarWidth(value) {
        let maxSideBarWidth = 280;
        if (isNumber(value)) {
            let numberValue = value;
            if (numberValue < 0) {
                modifier(this._modifiers, SideBarContainerMaxSideBarWidthModifier, maxSideBarWidth);
            }
            else {
                modifier(this._modifiers, SideBarContainerMaxSideBarWidthModifier, numberValue);
            }
        }
        else if (isLengthType(value)) {
            let arkValue = value;
            modifier(this._modifiers, SideBarContainerMaxSideBarWidthModifier, arkValue);
        }
        else {
            modifier(this._modifiers, SideBarContainerMaxSideBarWidthModifier, maxSideBarWidth);
        }
        return this;
    }
    minSideBarWidth(value) {
        let minSideBarWidth = 240;
        if (isNumber(value)) {
            let numberValue = value;
            if (numberValue < 0) {
                modifier(this._modifiers, SideBarContainerMinSideBarWidthModifier, minSideBarWidth);
            }
            else {
                modifier(this._modifiers, SideBarContainerMinSideBarWidthModifier, numberValue);
            }
        }
        else if (isLengthType(value)) {
            let _lengthValue = value;
            modifier(this._modifiers, SideBarContainerMinSideBarWidthModifier, _lengthValue);
        }
        else {
            modifier(this._modifiers, SideBarContainerMinSideBarWidthModifier, minSideBarWidth);
        }
        return this;
    }
    minContentWidth(value) {
        let minContentWidth = '360vp';
        if (isLengthType(value)) {
            let _lengthValue = value;
            modifier(this._modifiers, SideBarContainerMinContentWidthModifier, _lengthValue);
        }
        else {
            modifier(this._modifiers, SideBarContainerMinContentWidthModifier, minContentWidth);
        }
        return this;
    }
    controlButton(value) {
        let arkValue = new ArkButtonStyle();
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
                arkValue.icons.shown = value.icons.shown;
            }
            if (isString(value.icons.hidden)) {
                arkValue.icons.hidden = value.icons.hidden;
            }
            if (isString(value.icons.switching)) {
                arkValue.icons.switching = value.icons.switching;
            }
        }
        modifier(this._modifiers, SideBarContainerControlButtonModifier, arkValue);
        return this;
    }
    divider(value) {
        let arkValue = new ArkSideBarDividerStyle();
        if (value === null || !isObject(value) || !isLengthType(value.strokeWidth)) {
            modifier(this._modifiers, SideBarContainerDividerModifier, arkValue);
        }
        else {
            arkValue.strokeWidth = value.strokeWidth;
            let arkColor = new ArkColor();
            if (arkColor.parseColorValue(value.color)) {
                arkValue.color = value.color;
            }
            if (isLengthType(value.startMargin)) {
                arkValue.startMargin = value.startMargin;
            }
            if (isLengthType(value.endMargin)) {
                arkValue.endMargin = value.endMargin;
            }
            modifier(this._modifiers, SideBarContainerDividerModifier, arkValue);
        }
        return this;
    }
    sideBarPosition(value) {
        if (!(value in SideBarPosition)) {
            modifier(this._modifiers, SideBarContainerPositionModifier, SideBarPosition.Start);
        }
        modifier(this._modifiers, SideBarContainerPositionModifier, value);
        return this;
    }
    sideBarWidth(value) {
        let sideBarWidthValue = 240;
        if (isNumber(value)) {
            let numberValue = value;
            if (numberValue < 0) {
                modifier(this._modifiers, SideBarContainerWidthModifier, sideBarWidthValue);
            }
            else {
                let lengthValue = value;
                modifier(this._modifiers, SideBarContainerWidthModifier, lengthValue);
            }
        }
        else if (isLengthType(value)) {
            let lengthValue = value;
            modifier(this._modifiers, SideBarContainerWidthModifier, lengthValue);
        }
        else {
            modifier(this._modifiers, SideBarContainerWidthModifier, sideBarWidthValue);
        }
        return this;
    }
    showControlButton(value) {
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
};
/// <reference path="./import.ts" />
class ArkSwiperComponent extends ArkComponent {
    index(value) {
        throw new Error("Method not implemented.");
    }
    autoPlay(value) {
        throw new Error("Method not implemented.");
    }
    interval(value) {
        throw new Error("Method not implemented.");
    }
    indicator(value) {
        throw new Error("Method not implemented.");
    }
    displayArrow(value, isHoverShow) {
        throw new Error("Method not implemented.");
    }
    loop(value) {
        throw new Error("Method not implemented.");
    }
    duration(value) {
        throw new Error("Method not implemented.");
    }
    vertical(value) {
        throw new Error("Method not implemented.");
    }
    itemSpace(value) {
        throw new Error("Method not implemented.");
    }
    displayMode(value) {
        throw new Error("Method not implemented.");
    }
    cachedCount(value) {
        throw new Error("Method not implemented.");
    }
    displayCount(value) {
        throw new Error("Method not implemented.");
    }
    effectMode(value) {
        throw new Error("Method not implemented.");
    }
    disableSwipe(value) {
        throw new Error("Method not implemented.");
    }
    curve(value) {
        throw new Error("Method not implemented.");
    }
    onChange(event) {
        throw new Error("Method not implemented.");
    }
    indicatorStyle(value) {
        throw new Error("Method not implemented.");
    }
    prevMargin(value) {
        throw new Error("Method not implemented.");
    }
    nextMargin(value) {
        throw new Error("Method not implemented.");
    }
    onAnimationStart(event) {
        throw new Error("Method not implemented.");
    }
    onAnimationEnd(event) {
        throw new Error("Method not implemented.");
    }
    onGestureSwipe(event) {
        throw new Error("Method not implemented.");
    }
    nestedScroll(value) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Swiper.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkSwiperComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkTabsComponent extends ArkComponent {
    onAnimationStart(handler) {
        throw new Error("Method not implemented.");
    }
    onAnimationEnd(handler) {
        throw new Error("Method not implemented.");
    }
    onGestureSwipe(handler) {
        throw new Error("Method not implemented.");
    }
    vertical(value) {
        modifier(this._modifiers, VerticalModifier, value);
        return this;
    }
    barPosition(value) {
        if (isNumber(value) && value >= BarPosition.Start && value < BarPosition.End) {
            modifier(this._modifiers, BarPositionModifier, value);
        }
        else {
            modifier(this._modifiers, BarPositionModifier, BarPosition.Start);
        }
        return this;
    }
    scrollable(value) {
        modifier(this._modifiers, ScrollableModifier, isBoolean(value) ? value : true);
        return this;
    }
    barMode(value, options) {
        let barMode;
        let arkBarMode = new ArkBarMode();
        let arkScrollableBarModeOptions = new ArkScrollableBarModeOptions();
        arkScrollableBarModeOptions.value = options;
        arkBarMode.barMode = barMode;
        arkBarMode.options = arkScrollableBarModeOptions;
        modifier(this._modifiers, ScrollableBarModeOptionsModifier, arkBarMode.options);
        modifier(this._modifiers, TabBarModeModifier, arkBarMode);
        return this;
    }
    barWidth(value) {
        if (isUndefined(value) || isNull(value)) {
            return;
        }
        modifier(this._modifiers, BarWidthModifier, value.toString());
        return this;
    }
    barHeight(value) {
        if (isUndefined(value) || isNull(value)) {
            return;
        }
        let adaptiveHeight = false;
        modifier(this._modifiers, BarAdaptiveHeightModifier, adaptiveHeight);
        modifier(this._modifiers, BarHeightModifier, value.toString());
        return this;
    }
    animationDuration(value) {
        let time = (isNumber(value) && value > 0) ? value : 300;
        modifier(this._modifiers, AnimationDurationModifier, time);
        return this;
    }
    onChange(event) {
        throw new Error("Method not implemented.");
    }
    onTabBarClick(event) {
        throw new Error("Method not implemented.");
    }
    fadingEdge(value) {
        modifier(this._modifiers, FadingEdgeModifier, value);
        return this;
    }
    divider(value) {
        let arkDrivider = new ArkDivider();
        if (!value) {
            arkDrivider.value.strokeWidth = undefined;
            arkDrivider.value.color = undefined;
            arkDrivider.value.startMargin = undefined;
            arkDrivider.value.endMargin = undefined;
        }
        modifier(this._modifiers, DividerModifier, arkDrivider);
        return this;
    }
    barOverlap(value) {
        modifier(this._modifiers, BarOverlapModifier, value);
        return this;
    }
    barBackgroundColor(value) {
        let arkBarBackgroundColor = new ArkBarBackgroundColor();
        arkBarBackgroundColor.value = value;
        modifier(this._modifiers, BarBackgroundColorModifier, arkBarBackgroundColor);
        return this;
    }
    barGridAlign(value) {
        let arkBarGridAlign = new ArkBarGridAlign();
        if (isObject(value)) {
            modifier(this._modifiers, BarGridAlignModifier, arkBarGridAlign);
        }
        return this;
    }
}
class BarGridAlignModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().tabs.resetBarGridAlign(node);
        }
        else {
            GetUINativeModule().tabs.setBarGridAlign(node, this.value);
        }
    }
}
BarGridAlignModifier.identity = Symbol("barGridAlign");
class DividerModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().tabs.resetDivider(node);
        }
        else {
            GetUINativeModule().tabs.setDivider(node, this.value);
        }
    }
}
DividerModifier.identity = Symbol("Divider");
class BarWidthModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().tabs.resetBarWidth(node);
        }
        else {
            GetUINativeModule().tabs.setBarWidth(node, this.value);
        }
    }
}
BarWidthModifier.identity = Symbol("barWidth");
class BarAdaptiveHeightModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().tabs.resetBarAdaptiveHeight(node);
        }
        else {
            GetUINativeModule().tabs.setBarAdaptiveHeight(node, this.value);
        }
    }
}
BarAdaptiveHeightModifier.identity = Symbol("barAdaptiveHeight");
class BarHeightModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().tabs.resetBarHeight(node);
        }
        else {
            GetUINativeModule().tabs.setBarHeight(node, this.value);
        }
    }
}
BarHeightModifier.identity = Symbol("barHeight");
class BarOverlapModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().tabs.resetBarOverlap(node);
        }
        else {
            GetUINativeModule().tabs.setBarOverlap(node, this.value);
        }
    }
}
BarOverlapModifier.identity = Symbol("barOverlap");
class VerticalModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().tabs.resetVertical(node);
        }
        else {
            GetUINativeModule().tabs.setVertical(node, this.value);
        }
    }
}
VerticalModifier.identity = Symbol("vertical");
class AnimationDurationModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().tabs.resetAnimationDuration(node);
        }
        else {
            GetUINativeModule().tabs.setAnimationDuration(node, this.value);
        }
    }
}
AnimationDurationModifier.identity = Symbol("animationduration");
class ScrollableModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().tabs.resetScrollable(node);
        }
        else {
            GetUINativeModule().tabs.setScrollable(node, this.value);
        }
    }
}
ScrollableModifier.identity = Symbol("scrollable");
class TabBarModeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().tabs.resetTabBarMode(node);
        }
        else {
            GetUINativeModule().tabs.setTabBarMode(node, this.value);
        }
    }
}
TabBarModeModifier.identity = Symbol("tabsbarMode");
class BarPositionModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().tabs.resetBarPosition(node);
        }
        else {
            GetUINativeModule().tabs.setBarPosition(node, this.value);
        }
    }
}
BarPositionModifier.identity = Symbol("barPosition");
class TabsHideTitleBarModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().tabs.resetHideTitleBar(node);
        }
        else {
            GetUINativeModule().tabs.setHideTitleBar(node, this.value);
        }
    }
}
TabsHideTitleBarModifier.identity = Symbol("hideTitleBar");
class BarBackgroundColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().tabs.resetBarBackgroundColor(node);
        }
        else {
            GetUINativeModule().tabs.setBarBackgroundColor(node, this.value);
        }
    }
}
BarBackgroundColorModifier.identity = Symbol("barbackgroundcolor");
class FadingEdgeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().tabs.resetFadingEdge(node);
        }
        else {
            GetUINativeModule().tabs.setFadingEdge(node, this.value);
        }
    }
}
FadingEdgeModifier.identity = Symbol("fadingedge");
class ScrollableBarModeOptionsModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().tabs.resetScrollableBarModeOptions(node);
        }
        else {
            GetUINativeModule().tabs.setScrollableBarModeOptions(node, this.value["margin"], this.value["nonScrollableLayoutStyle"]);
        }
    }
}
ScrollableBarModeOptionsModifier.identity = Symbol("tabsscrollableBarModeOptions");
// @ts-ignore
globalThis.Tabs.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkTabsComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkTabContentComponent extends ArkComponent {
    tabBar(value) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.TabContent.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkTabContentComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkUIExtensionComponentComponent extends ArkComponent {
    onRemoteReady(callback) {
        throw new Error("Method not implemented.");
    }
    onReceive(callback) {
        throw new Error("Method not implemented.");
    }
    onResult(callback) {
        throw new Error("Method not implemented.");
    }
    onRelease(callback) {
        throw new Error("Method not implemented.");
    }
    onError(callback) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.UIExtensionComponent.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = globalThis.getArkUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkUIExtensionComponentComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkWaterFlowComponent extends ArkComponent {
    columnsTemplate(value) {
        throw new Error("Method not implemented.");
    }
    itemConstraintSize(value) {
        throw new Error("Method not implemented.");
    }
    rowsTemplate(value) {
        throw new Error("Method not implemented.");
    }
    columnsGap(value) {
        throw new Error("Method not implemented.");
    }
    rowsGap(value) {
        throw new Error("Method not implemented.");
    }
    layoutDirection(value) {
        throw new Error("Method not implemented.");
    }
    nestedScroll(value) {
        throw new Error("Method not implemented.");
    }
    enableScrollInteraction(value) {
        throw new Error("Method not implemented.");
    }
    friction(value) {
        throw new Error("Method not implemented.");
    }
    cachedCount(value) {
        throw new Error("Method not implemented.");
    }
    onReachStart(event) {
        throw new Error("Method not implemented.");
    }
    onReachEnd(event) {
        throw new Error("Method not implemented.");
    }
    onScrollFrameBegin(event) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.WaterFlow.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkWaterFlowComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class VideoObjectFitModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().video.resetObjectFit(node);
        }
        else {
            GetUINativeModule().video.setObjectFit(node, this.value);
        }
    }
}
VideoObjectFitModifier.identity = Symbol('videoObjectFit');
class VideoAutoPlayModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().video.resetAutoPlay(node);
        }
        else {
            GetUINativeModule().video.setAutoPlay(node, this.value);
        }
    }
}
VideoAutoPlayModifier.identity = Symbol('videoAutoPlayr');
class VideoControlsModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().video.resetControls(node);
        }
        else {
            GetUINativeModule().video.setControls(node, this.value);
        }
    }
}
VideoControlsModifier.identity = Symbol('videoControls');
class VideoLoopModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().video.resetLoop(node);
        }
        else {
            GetUINativeModule().video.setLoop(node, this.value);
        }
    }
}
VideoLoopModifier.identity = Symbol('videoLoop');
class VideoMutedModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().video.resetMuted(node);
        }
        else {
            GetUINativeModule().video.setMuted(node, this.value);
        }
    }
}
VideoMutedModifier.identity = Symbol('videoMuted');
class ArkVideoComponent extends ArkComponent {
    muted(value) {
        let muted = false;
        if (isBoolean(value)) {
            muted = value;
        }
        modifier(this._modifiers, VideoMutedModifier, muted);
        return this;
    }
    autoPlay(value) {
        let autoPlay = false;
        if (isBoolean(value)) {
            autoPlay = value;
        }
        modifier(this._modifiers, VideoAutoPlayModifier, autoPlay);
        return this;
    }
    controls(value) {
        let controls = true;
        if (isBoolean(value)) {
            controls = value;
        }
        modifier(this._modifiers, VideoControlsModifier, controls);
        return this;
    }
    loop(value) {
        let loop = false;
        if (isBoolean(value)) {
            loop = value;
        }
        modifier(this._modifiers, VideoLoopModifier, loop);
        return this;
    }
    objectFit(value) {
        if (value) {
            modifier(this._modifiers, VideoObjectFitModifier, value);
        }
        else {
            modifier(this._modifiers, VideoObjectFitModifier, undefined);
        }
        return this;
    }
    onStart(callback) {
        throw new Error('Method not implemented.');
    }
    onPause(callback) {
        throw new Error('Method not implemented.');
    }
    onFinish(event) {
        throw new Error('Method not implemented.');
    }
    onFullscreenChange(callback) {
        throw new Error('Method not implemented.');
    }
    onPrepared(callback) {
        throw new Error('Method not implemented.');
    }
    onSeeking(callback) {
        throw new Error('Method not implemented.');
    }
    onSeeked(callback) {
        throw new Error('Method not implemented.');
    }
    onUpdate(callback) {
        throw new Error('Method not implemented.');
    }
    onError(callback) {
        throw new Error('Method not implemented.');
    }
    monopolizeEvents(monopolize) {
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
};
/// <reference path="./import.ts" />
class ArkCircleComponent extends ArkComponent {
    stroke(value) {
        throw new Error("Method not implemented.");
    }
    fill(value) {
        throw new Error("Method not implemented.");
    }
    strokeDashOffset(value) {
        throw new Error("Method not implemented.");
    }
    strokeLineCap(value) {
        throw new Error("Method not implemented.");
    }
    strokeLineJoin(value) {
        throw new Error("Method not implemented.");
    }
    strokeMiterLimit(value) {
        throw new Error("Method not implemented.");
    }
    strokeOpacity(value) {
        throw new Error("Method not implemented.");
    }
    fillOpacity(value) {
        throw new Error("Method not implemented.");
    }
    strokeWidth(value) {
        throw new Error("Method not implemented.");
    }
    antiAlias(value) {
        throw new Error("Method not implemented.");
    }
    strokeDashArray(value) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Circle.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkCircleComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkEllipseComponent extends ArkComponent {
    stroke(value) {
        throw new Error("Method not implemented.");
    }
    fill(value) {
        throw new Error("Method not implemented.");
    }
    strokeDashOffset(value) {
        throw new Error("Method not implemented.");
    }
    strokeLineCap(value) {
        throw new Error("Method not implemented.");
    }
    strokeLineJoin(value) {
        throw new Error("Method not implemented.");
    }
    strokeMiterLimit(value) {
        throw new Error("Method not implemented.");
    }
    strokeOpacity(value) {
        throw new Error("Method not implemented.");
    }
    fillOpacity(value) {
        throw new Error("Method not implemented.");
    }
    strokeWidth(value) {
        throw new Error("Method not implemented.");
    }
    antiAlias(value) {
        throw new Error("Method not implemented.");
    }
    strokeDashArray(value) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Ellipse.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkEllipseComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkLineComponent extends ArkComponent {
    startPoint(value) {
        throw new Error("Method not implemented.");
    }
    endPoint(value) {
        throw new Error("Method not implemented.");
    }
    stroke(value) {
        throw new Error("Method not implemented.");
    }
    fill(value) {
        throw new Error("Method not implemented.");
    }
    strokeDashOffset(value) {
        throw new Error("Method not implemented.");
    }
    strokeLineCap(value) {
        throw new Error("Method not implemented.");
    }
    strokeLineJoin(value) {
        throw new Error("Method not implemented.");
    }
    strokeMiterLimit(value) {
        throw new Error("Method not implemented.");
    }
    strokeOpacity(value) {
        throw new Error("Method not implemented.");
    }
    fillOpacity(value) {
        throw new Error("Method not implemented.");
    }
    strokeWidth(value) {
        throw new Error("Method not implemented.");
    }
    antiAlias(value) {
        throw new Error("Method not implemented.");
    }
    strokeDashArray(value) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Line.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkLineComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkPolylineComponent extends ArkComponent {
    points(value) {
        throw new Error("Method not implemented.");
    }
    stroke(value) {
        throw new Error("Method not implemented.");
    }
    fill(value) {
        throw new Error("Method not implemented.");
    }
    strokeDashOffset(value) {
        throw new Error("Method not implemented.");
    }
    strokeLineCap(value) {
        throw new Error("Method not implemented.");
    }
    strokeLineJoin(value) {
        throw new Error("Method not implemented.");
    }
    strokeMiterLimit(value) {
        throw new Error("Method not implemented.");
    }
    strokeOpacity(value) {
        throw new Error("Method not implemented.");
    }
    fillOpacity(value) {
        throw new Error("Method not implemented.");
    }
    strokeWidth(value) {
        throw new Error("Method not implemented.");
    }
    antiAlias(value) {
        throw new Error("Method not implemented.");
    }
    strokeDashArray(value) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Polyline.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkPolylineComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkPolygonComponent extends ArkComponent {
    points(value) {
        throw new Error("Method not implemented.");
    }
    stroke(value) {
        throw new Error("Method not implemented.");
    }
    fill(value) {
        throw new Error("Method not implemented.");
    }
    strokeDashOffset(value) {
        throw new Error("Method not implemented.");
    }
    strokeLineCap(value) {
        throw new Error("Method not implemented.");
    }
    strokeLineJoin(value) {
        throw new Error("Method not implemented.");
    }
    strokeMiterLimit(value) {
        throw new Error("Method not implemented.");
    }
    strokeOpacity(value) {
        throw new Error("Method not implemented.");
    }
    fillOpacity(value) {
        throw new Error("Method not implemented.");
    }
    strokeWidth(value) {
        throw new Error("Method not implemented.");
    }
    antiAlias(value) {
        throw new Error("Method not implemented.");
    }
    strokeDashArray(value) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Polygon.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkPolygonComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkPathComponent extends ArkComponent {
    commands(value) {
        throw new Error("Method not implemented.");
    }
    stroke(value) {
        throw new Error("Method not implemented.");
    }
    fill(value) {
        throw new Error("Method not implemented.");
    }
    strokeDashOffset(value) {
        throw new Error("Method not implemented.");
    }
    strokeLineCap(value) {
        throw new Error("Method not implemented.");
    }
    strokeLineJoin(value) {
        throw new Error("Method not implemented.");
    }
    strokeMiterLimit(value) {
        throw new Error("Method not implemented.");
    }
    strokeOpacity(value) {
        throw new Error("Method not implemented.");
    }
    fillOpacity(value) {
        throw new Error("Method not implemented.");
    }
    strokeWidth(value) {
        throw new Error("Method not implemented.");
    }
    antiAlias(value) {
        throw new Error("Method not implemented.");
    }
    strokeDashArray(value) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Path.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkPathComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkRectComponent extends ArkComponent {
    radiusWidth(value) {
        throw new Error("Method not implemented.");
    }
    radiusHeight(value) {
        throw new Error("Method not implemented.");
    }
    radius(value) {
        throw new Error("Method not implemented.");
    }
    stroke(value) {
        throw new Error("Method not implemented.");
    }
    fill(value) {
        throw new Error("Method not implemented.");
    }
    strokeDashOffset(value) {
        throw new Error("Method not implemented.");
    }
    strokeLineCap(value) {
        throw new Error("Method not implemented.");
    }
    strokeLineJoin(value) {
        throw new Error("Method not implemented.");
    }
    strokeMiterLimit(value) {
        throw new Error("Method not implemented.");
    }
    strokeOpacity(value) {
        throw new Error("Method not implemented.");
    }
    fillOpacity(value) {
        throw new Error("Method not implemented.");
    }
    strokeWidth(value) {
        throw new Error("Method not implemented.");
    }
    antiAlias(value) {
        throw new Error("Method not implemented.");
    }
    strokeDashArray(value) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Rect.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkRectComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkShapeComponent extends ArkComponent {
    viewPort(value) {
        throw new Error("Method not implemented.");
    }
    stroke(value) {
        throw new Error("Method not implemented.");
    }
    fill(value) {
        throw new Error("Method not implemented.");
    }
    strokeDashOffset(value) {
        throw new Error("Method not implemented.");
    }
    strokeDashArray(value) {
        throw new Error("Method not implemented.");
    }
    strokeLineCap(value) {
        throw new Error("Method not implemented.");
    }
    strokeLineJoin(value) {
        throw new Error("Method not implemented.");
    }
    strokeMiterLimit(value) {
        throw new Error("Method not implemented.");
    }
    strokeOpacity(value) {
        throw new Error("Method not implemented.");
    }
    fillOpacity(value) {
        throw new Error("Method not implemented.");
    }
    strokeWidth(value) {
        throw new Error("Method not implemented.");
    }
    antiAlias(value) {
        throw new Error("Method not implemented.");
    }
    mesh(value, column, row) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Shape.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkShapeComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkCanvasComponent extends ArkComponent {
    onReady(event) {
        throw new Error("Method not implemented.");
    }
    monopolizeEvents(monopolize) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Canvas.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkCanvasComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkGridContainerComponent extends ArkComponent {
    alignItems(value) {
        throw new Error('Method not implemented.');
    }
    justifyContent(value) {
        throw new Error('Method not implemented.');
    }
    pointLight(value) {
        throw new Error('Method not implemented.');
    }
}
// @ts-ignore
globalThis.GridContainer.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkGridContainerComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkWindowSceneComponent extends ArkComponent {
}
// @ts-ignore
globalThis.WindowScene.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkWindowSceneComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
