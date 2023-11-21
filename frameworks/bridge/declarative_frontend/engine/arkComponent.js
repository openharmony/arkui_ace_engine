const HashMap = globalThis.requireNapi('util.HashMap');
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
class Modifier {
    constructor(value) {
        this.stageValue = value;
    }
    applyStage(node) {
        if (this.stageValue === this.value) {
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
class BackgroundColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetBackgroundColor(node);
        }
        else {
            GetUINativeModule().common.setBackgroundColor(node, this.value);
        }
    }
}
BackgroundColorModifier.identity = Symbol("backgroundColor");
class WidthModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetWidth(node);
        }
        else {
            GetUINativeModule().common.setWidth(node, this.value);
        }
    }
}
WidthModifier.identity = Symbol("width");
class BorderWidthModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetBorderWidth(node);
        }
        else {
            GetUINativeModule().common.setBorderWidth(node, this.value.left, this.value.right, this.value.top, this.value.bottom);
        }
    }
}
BorderWidthModifier.identity = Symbol("borderWidth");
class HeightModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetHeight(node);
        }
        else {
            GetUINativeModule().common.setHeight(node, this.value);
        }
    }
}
HeightModifier.identity = Symbol("height");
class BorderRadiusModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetBorderRadius(node);
        }
        else {
            GetUINativeModule().common.setBorderRadius(node, this.value.topLeft, this.value.topRight, this.value.bottomLeft, this.value.bottomRight);
        }
    }
}
BorderRadiusModifier.identity = Symbol("borderRadius");
class PositionModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetPosition(node);
        }
        else {
            GetUINativeModule().common.setPosition(node, this.value.x, this.value.y);
        }
    }
}
PositionModifier.identity = Symbol("position");
class BorderColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetBorderColor(node);
        }
        else {
            GetUINativeModule().common.setBorderColor(node, this.value.leftColor, this.value.rightColor, this.value.topColor, this.value.bottomColor);
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
class OpacityModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().common.resetOpacity(node);
        }
        else {
            GetUINativeModule().common.setOpacity(node, this.value);
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
const JSCallbackInfoType = { STRING: 0, NUMBER: 1, OBJECT: 2, BOOLEAN: 3, FUNCTION: 4 };
const isString = (val) => typeof val === 'string';
const isNumber = (val) => typeof val === 'number';
const isBigint = (val) => typeof val === 'bigint';
const isBoolean = (val) => typeof val === 'boolean';
const isSymbol = (val) => typeof val === 'symbol';
const isUndefined = (val) => typeof val === 'undefined';
const isObject = (val) => typeof val === 'object';
const isFunction = (val) => typeof val === 'function';
function CheckJSCallbackInfo(value, checklist) {
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
class ArkComponent {
    constructor(nativePtr) {
        this._modifiers = new Map();
        this.nativePtr = nativePtr;
    }
    applyModifierPatch() {
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
    width(value) {
        if (typeof value !== "number" && typeof value !== "string") {
            modifier(this._modifiers, WidthModifier, undefined);
        }
        else {
            modifier(this._modifiers, WidthModifier, value);
        }
        return this;
    }
    height(value) {
        if (typeof value !== "number" && typeof value !== "string") {
            modifier(this._modifiers, HeightModifier, undefined);
        }
        else {
            modifier(this._modifiers, HeightModifier, value);
        }
        return this;
    }
    expandSafeArea(types, edges) {
        throw new Error("Method not implemented.");
    }
    responseRegion(value) {
        throw new Error("Method not implemented.");
    }
    mouseResponseRegion(value) {
        throw new Error("Method not implemented.");
    }
    size(value) {
        throw new Error("Method not implemented.");
    }
    constraintSize(value) {
        throw new Error("Method not implemented.");
    }
    touchable(value) {
        throw new Error("Method not implemented.");
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
        throw new Error("Method not implemented.");
    }
    padding(value) {
        throw new Error("Method not implemented.");
    }
    margin(value) {
        throw new Error("Method not implemented.");
    }
    background(builder, options) {
        throw new Error("Method not implemented.");
    }
    backgroundColor(value) {
        if (isResource(value)) {
            modifier(this._modifiers, BackgroundColorModifier, undefined);
            return this;
        }
        var arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, BackgroundColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, BackgroundColorModifier, undefined);
        }
        return this;
    }
    backgroundImage(src, repeat) {
        throw new Error("Method not implemented.");
    }
    backgroundImageSize(value) {
        throw new Error("Method not implemented.");
    }
    backgroundImagePosition(value) {
        throw new Error("Method not implemented.");
    }
    backgroundBlurStyle(value, options) {
        throw new Error("Method not implemented.");
    }
    foregroundBlurStyle(value, options) {
        throw new Error("Method not implemented.");
    }
    opacity(value) {
        var opacityDefault = 0.0;
        if (isResource(value)) {
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
    border(value) {
        throw new Error("Method not implemented.");
    }
    borderStyle(value) {
        var arkBorderStyle = new ArkBorderStyle();
        if (arkBorderStyle.parseBorderStyle(value)) {
            modifier(this._modifiers, BorderStyleModifier, arkBorderStyle);
        }
        else {
            modifier(this._modifiers, BorderStyleModifier, undefined);
        }
        return this;
    }
    borderWidth(value) {
        var borderWidth = new ArkBorderWidth();
        if (isResource(value) || isUndefined(value)) {
            modifier(this._modifiers, BorderWidthModifier, undefined);
            return this;
        }
        if (typeof value === "number" || typeof value === "string") {
            borderWidth.left = value;
            borderWidth.right = value;
            borderWidth.top = value;
            borderWidth.bottom = value;
        }
        else {
            borderWidth.left = value === null || value === void 0 ? void 0 : value.left;
            borderWidth.right = value === null || value === void 0 ? void 0 : value.right;
            borderWidth.top = value === null || value === void 0 ? void 0 : value.top;
            borderWidth.bottom = value === null || value === void 0 ? void 0 : value.bottom;
        }
        modifier(this._modifiers, BorderWidthModifier, borderWidth);
        return this;
    }
    borderColor(value) {
        if (isResource(value) || isUndefined(value)) {
            modifier(this._modifiers, BorderColorModifier, undefined);
            return this;
        }
        var arkColor = new ArkColor();
        var borderColorGroup = new ArkBorderColor();
        if (typeof value === "number" || typeof value === "string") {
            arkColor.parseColorValue(value);
            borderColorGroup.leftColor = arkColor.color;
            borderColorGroup.rightColor = arkColor.color;
            borderColorGroup.topColor = arkColor.color;
            borderColorGroup.bottomColor = arkColor.color;
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
    borderRadius(value) {
        if (isResource(value) || isUndefined(value)) {
            modifier(this._modifiers, BorderRadiusModifier, undefined);
            return this;
        }
        var borderRadius = new ArkBorderRadius;
        if (typeof value === "number" || typeof value === "string") {
            borderRadius.topLeft = value;
            borderRadius.topRight = value;
            borderRadius.bottomLeft = value;
            borderRadius.bottomRight = value;
        }
        else {
            borderRadius.topLeft = value === null || value === void 0 ? void 0 : value.topLeft;
            borderRadius.topRight = value === null || value === void 0 ? void 0 : value.topRight;
            borderRadius.bottomLeft = value === null || value === void 0 ? void 0 : value.bottomLeft;
            borderRadius.bottomRight = value === null || value === void 0 ? void 0 : value.bottomRight;
        }
        modifier(this._modifiers, BorderRadiusModifier, borderRadius);
        return this;
    }
    borderImage(value) {
        throw new Error("Method not implemented.");
    }
    foregroundColor(value) {
        throw new Error("Method not implemented.");
    }
    onClick(event) {
        throw new Error("Method not implemented.");
    }
    onHover(event) {
        throw new Error("Method not implemented.");
    }
    hoverEffect(value) {
        throw new Error("Method not implemented.");
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
        throw new Error("Method not implemented.");
    }
    onFocus(event) {
        throw new Error("Method not implemented.");
    }
    onBlur(event) {
        throw new Error("Method not implemented.");
    }
    tabIndex(index) {
        throw new Error("Method not implemented.");
    }
    defaultFocus(value) {
        throw new Error("Method not implemented.");
    }
    groupDefaultFocus(value) {
        throw new Error("Method not implemented.");
    }
    focusOnTouch(value) {
        throw new Error("Method not implemented.");
    }
    animation(value) {
        throw new Error("Method not implemented.");
    }
    transition(value) {
        throw new Error("Method not implemented.");
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
        throw new Error("Method not implemented.");
    }
    linearGradientBlur(value, options) {
        throw new Error("Method not implemented.");
    }
    brightness(value) {
        throw new Error("Method not implemented.");
    }
    contrast(value) {
        throw new Error("Method not implemented.");
    }
    grayscale(value) {
        throw new Error("Method not implemented.");
    }
    colorBlend(value) {
        throw new Error("Method not implemented.");
    }
    saturate(value) {
        throw new Error("Method not implemented.");
    }
    sepia(value) {
        throw new Error("Method not implemented.");
    }
    invert(value) {
        throw new Error("Method not implemented.");
    }
    hueRotate(value) {
        throw new Error("Method not implemented.");
    }
    useEffect(value) {
        throw new Error("Method not implemented.");
    }
    backdropBlur(value) {
        throw new Error("Method not implemented.");
    }
    renderGroup(value) {
        throw new Error("Method not implemented.");
    }
    translate(value) {
        throw new Error("Method not implemented.");
    }
    scale(value) {
        throw new Error("Method not implemented.");
    }
    gridSpan(value) {
        throw new Error("Method not implemented.");
    }
    gridOffset(value) {
        throw new Error("Method not implemented.");
    }
    rotate(value) {
        throw new Error("Method not implemented.");
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
        throw new Error("Method not implemented.");
    }
    flexGrow(value) {
        throw new Error("Method not implemented.");
    }
    flexShrink(value) {
        throw new Error("Method not implemented.");
    }
    flexBasis(value) {
        throw new Error("Method not implemented.");
    }
    alignSelf(value) {
        throw new Error("Method not implemented.");
    }
    displayPriority(value) {
        throw new Error("Method not implemented.");
    }
    zIndex(value) {
        if (value !== null) {
            var zIndex = 0;
            if (typeof (value) === "number") {
                zIndex = value;
            }
            modifier(this._modifiers, ZIndexModifier, zIndex);
        }
        return this;
    }
    sharedTransition(id, options) {
        throw new Error("Method not implemented.");
    }
    direction(value) {
        throw new Error("Method not implemented.");
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
        if (isResource(value) || isUndefined(value)) {
            modifier(this._modifiers, PositionModifier, undefined);
            return this;
        }
        if (isNumber(value === null || value === void 0 ? void 0 : value.x) || isString(value === null || value === void 0 ? void 0 : value.x) || isNumber(value === null || value === void 0 ? void 0 : value.y) || isString(value === null || value === void 0 ? void 0 : value.y)) {
            var position = new ArkPosition();
            position.x = value === null || value === void 0 ? void 0 : value.x;
            position.y = value === null || value === void 0 ? void 0 : value.y;
            modifier(this._modifiers, PositionModifier, position);
        }
        else {
            modifier(this._modifiers, PositionModifier, undefined);
        }
        return this;
    }
    markAnchor(value) {
        throw new Error("Method not implemented.");
    }
    offset(value) {
        throw new Error("Method not implemented.");
    }
    enabled(value) {
        throw new Error("Method not implemented.");
    }
    useSizeType(value) {
        throw new Error("Method not implemented.");
    }
    alignRules(value) {
        throw new Error("Method not implemented.");
    }
    aspectRatio(value) {
        throw new Error("Method not implemented.");
    }
    clickEffect(value) {
        throw new Error("Method not implemented.");
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
        throw new Error("Method not implemented.");
    }
    draggable(value) {
        throw new Error("Method not implemented.");
    }
    overlay(value, options) {
        throw new Error("Method not implemented.");
    }
    linearGradient(value) {
        throw new Error("Method not implemented.");
    }
    sweepGradient(value) {
        throw new Error("Method not implemented.");
    }
    radialGradient(value) {
        throw new Error("Method not implemented.");
    }
    motionPath(value) {
        throw new Error("Method not implemented.");
    }
    shadow(value) {
        var arkShadow = new ArkShadow();
        if (arkShadow.parseShadowValue(value)) {
            modifier(this._modifiers, ShadowModifier, arkShadow);
        }
        else {
            modifier(this._modifiers, ShadowModifier, undefined);
        }
        return this;
    }
    mask(value) {
        throw new Error("Method not implemented.");
    }
    key(value) {
        throw new Error("Method not implemented.");
    }
    id(value) {
        throw new Error("Method not implemented.");
    }
    geometryTransition(id) {
        throw new Error("Method not implemented.");
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
        throw new Error("Method not implemented.");
    }
    bindSheet(isShow, builder, options) {
        throw new Error("Method not implemented.");
    }
    stateStyles(value) {
        throw new Error("Method not implemented.");
    }
    restoreId(value) {
        throw new Error("Method not implemented.");
    }
    onVisibleAreaChange(ratios, event) {
        throw new Error("Method not implemented.");
    }
    sphericalEffect(value) {
        throw new Error("Method not implemented.");
    }
    lightUpEffect(value) {
        throw new Error("Method not implemented.");
    }
    pixelStretchEffect(options) {
        throw new Error("Method not implemented.");
    }
    keyboardShortcut(value, keys, action) {
        throw new Error("Method not implemented.");
    }
    accessibilityGroup(value) {
        throw new Error("Method not implemented.");
    }
    accessibilityText(value) {
        throw new Error("Method not implemented.");
    }
    accessibilityDescription(value) {
        throw new Error("Method not implemented.");
    }
    accessibilityLevel(value) {
        throw new Error("Method not implemented.");
    }
    obscured(reasons) {
        throw new Error("Method not implemented.");
    }
    reuseId(id) {
        throw new Error("Method not implemented.");
    }
    renderFit(fitMode) {
        throw new Error("Method not implemented.");
    }
    attributeModifier(modifier) {
        return this;
    }
}
/// <reference path="./import.ts" />
class ArkButtonComponent extends ArkComponent {
    type(value) {
        throw new Error("Method not implemented.");
    }
    stateEffect(value) {
        throw new Error("Method not implemented.");
    }
    fontColor(value) {
        throw new Error("Method not implemented.");
    }
    fontSize(value) {
        throw new Error("Method not implemented.");
    }
    fontWeight(value) {
        throw new Error("Method not implemented.");
    }
    fontStyle(value) {
        throw new Error("Method not implemented.");
    }
    fontFamily(value) {
        throw new Error("Method not implemented.");
    }
    labelStyle(value) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Button.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
        return new ArkButtonComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkLoadingProgressComponent extends ArkComponent {
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
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
        return new ArkLoadingProgressComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkRefreshComponent extends ArkComponent {
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
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
        return new ArkRefreshComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkScrollComponent extends ArkComponent {
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
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
        return new ArkScrollComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkStackComponent extends ArkComponent {
    alignContent(value) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Stack.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
        return new ArkStackComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkImageComponent extends ArkComponent {
    alt(value) {
        throw new Error("Method not implemented.");
    }
    matchTextDirection(value) {
        throw new Error("Method not implemented.");
    }
    fitOriginalSize(value) {
        throw new Error("Method not implemented.");
    }
    fillColor(value) {
        throw new Error("Method not implemented.");
    }
    objectFit(value) {
        throw new Error("Method not implemented.");
    }
    objectRepeat(value) {
        throw new Error("Method not implemented.");
    }
    autoResize(value) {
        throw new Error("Method not implemented.");
    }
    renderMode(value) {
        throw new Error("Method not implemented.");
    }
    interpolation(value) {
        throw new Error("Method not implemented.");
    }
    sourceSize(value) {
        throw new Error("Method not implemented.");
    }
    syncLoad(value) {
        throw new Error("Method not implemented.");
    }
    colorFilter(value) {
        throw new Error("Method not implemented.");
    }
    copyOption(value) {
        throw new Error("Method not implemented.");
    }
    onComplete(callback) {
        throw new Error("Method not implemented.");
    }
    onError(callback) {
        throw new Error("Method not implemented.");
    }
    onFinish(event) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Image.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
        return new ArkImageComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class FontColorModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetFontColor(node);
        }
        else {
            GetUINativeModule().text.setFontColor(node, this.value);
        }
    }
}
FontColorModifier.identity = Symbol("fontColor");
class FontSizeModifier extends Modifier {
    applyPeer(node, reset) {
        if (reset) {
            GetUINativeModule().text.resetFontSize(node);
        }
        else {
            GetUINativeModule().text.setFontSize(node, this.value);
        }
    }
}
FontSizeModifier.identity = Symbol("fontSize");
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
FontWeightModifier.identity = Symbol("fontWeight");
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
FontStyleModifier.identity = Symbol("fontStyle");
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
TextAlignModifier.identity = Symbol("textAlign");
class ArkTextComponent extends ArkComponent {
    font(value) {
        throw new Error("Method not implemented.");
    }
    fontColor(value) {
        var arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, FontColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, FontColorModifier, undefined);
        }
        return this;
    }
    fontSize(value) {
        if (!isNumber(value) && !isString(value)) {
            modifier(this._modifiers, FontSizeModifier, undefined);
        }
        else {
            modifier(this._modifiers, FontSizeModifier, value);
        }
        return this;
    }
    minFontSize(value) {
        throw new Error("Method not implemented.");
    }
    maxFontSize(value) {
        throw new Error("Method not implemented.");
    }
    fontStyle(value) {
        if (isNumber(value)) {
            modifier(this._modifiers, FontStyleModifier, value);
        }
        return this;
    }
    fontWeight(value) {
        let fontWeightStr = "400";
        if (isNumber(value)) {
            if (value === 0) {
                fontWeightStr = "Lighter";
            }
            else if (value === 1) {
                fontWeightStr = "Normal";
            }
            else if (value === 2) {
                fontWeightStr = "Regular";
            }
            else if (value === 3) {
                fontWeightStr = "Medium";
            }
            else if (value === 4) {
                fontWeightStr = "Bold";
            }
            else if (value === 5) {
                fontWeightStr = "Bolder";
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
        throw new Error("Method not implemented.");
    }
    textOverflow(value) {
        throw new Error("Method not implemented.");
    }
    fontFamily(value) {
        throw new Error("Method not implemented.");
    }
    maxLines(value) {
        throw new Error("Method not implemented.");
    }
    decoration(value) {
        throw new Error("Method not implemented.");
    }
    letterSpacing(value) {
        throw new Error("Method not implemented.");
    }
    textCase(value) {
        throw new Error("Method not implemented.");
    }
    baselineOffset(value) {
        throw new Error("Method not implemented.");
    }
    copyOption(value) {
        throw new Error("Method not implemented.");
    }
    textShadow(value) {
        throw new Error("Method not implemented.");
    }
    heightAdaptivePolicy(value) {
        throw new Error("Method not implemented.");
    }
    textIndent(value) {
        throw new Error("Method not implemented.");
    }
    wordBreak(value) {
        throw new Error("Method not implemented.");
    }
    onCopy(callback) {
        throw new Error("Method not implemented.");
    }
    selection(selectionStart, selectionEnd) {
        throw new Error("Method not implemented.");
    }
    ellipsisMode(value) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Text.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
        return new ArkTextComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkTextAreaComponent extends ArkComponent {
    type(value) {
        throw new Error("Method not implemented.");
    }
    placeholderColor(value) {
        throw new Error("Method not implemented.");
    }
    placeholderFont(value) {
        throw new Error("Method not implemented.");
    }
    textAlign(value) {
        throw new Error("Method not implemented.");
    }
    caretColor(value) {
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
    inputFilter(value, error) {
        throw new Error("Method not implemented.");
    }
    onChange(callback) {
        throw new Error("Method not implemented.");
    }
    onTextSelectionChange(callback) {
        throw new Error("Method not implemented.");
    }
    onContentScroll(callback) {
        throw new Error("Method not implemented.");
    }
    onEditChange(callback) {
        throw new Error("Method not implemented.");
    }
    onCopy(callback) {
        throw new Error("Method not implemented.");
    }
    onCut(callback) {
        throw new Error("Method not implemented.");
    }
    onPaste(callback) {
        throw new Error("Method not implemented.");
    }
    copyOption(value) {
        throw new Error("Method not implemented.");
    }
    enableKeyboardOnFocus(value) {
        throw new Error("Method not implemented.");
    }
    maxLength(value) {
        throw new Error("Method not implemented.");
    }
    showCounter(value) {
        throw new Error("Method not implemented.");
    }
    style(value) {
        throw new Error("Method not implemented.");
    }
    barState(value) {
        throw new Error("Method not implemented.");
    }
    selectionMenuHidden(value) {
        throw new Error("Method not implemented.");
    }
    maxLines(value) {
        throw new Error("Method not implemented.");
    }
    customKeyboard(value) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.TextArea.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
        return new ArkTextAreaComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkTextInputComponent extends ArkComponent {
    showCounter(value) {
        throw new Error("Method not implemented.");
    }
    type(value) {
        throw new Error("Method not implemented.");
    }
    placeholderColor(value) {
        throw new Error("Method not implemented.");
    }
    placeholderFont(value) {
        throw new Error("Method not implemented.");
    }
    enterKeyType(value) {
        throw new Error("Method not implemented.");
    }
    caretColor(value) {
        throw new Error("Method not implemented.");
    }
    onEditChanged(callback) {
        throw new Error("Method not implemented.");
    }
    onEditChange(callback) {
        throw new Error("Method not implemented.");
    }
    onSubmit(callback) {
        throw new Error("Method not implemented.");
    }
    onChange(callback) {
        throw new Error("Method not implemented.");
    }
    onTextSelectionChange(callback) {
        throw new Error("Method not implemented.");
    }
    onContentScroll(callback) {
        throw new Error("Method not implemented.");
    }
    maxLength(value) {
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
    inputFilter(value, error) {
        throw new Error("Method not implemented.");
    }
    onCopy(callback) {
        throw new Error("Method not implemented.");
    }
    onCut(callback) {
        throw new Error("Method not implemented.");
    }
    onPaste(callback) {
        throw new Error("Method not implemented.");
    }
    copyOption(value) {
        throw new Error("Method not implemented.");
    }
    showPasswordIcon(value) {
        throw new Error("Method not implemented.");
    }
    textAlign(value) {
        throw new Error("Method not implemented.");
    }
    style(value) {
        throw new Error("Method not implemented.");
    }
    caretStyle(value) {
        throw new Error("Method not implemented.");
    }
    selectedBackgroundColor(value) {
        throw new Error("Method not implemented.");
    }
    caretPosition(value) {
        throw new Error("Method not implemented.");
    }
    enableKeyboardOnFocus(value) {
        throw new Error("Method not implemented.");
    }
    passwordIcon(value) {
        throw new Error("Method not implemented.");
    }
    showError(value) {
        throw new Error("Method not implemented.");
    }
    showUnit(value) {
        throw new Error("Method not implemented.");
    }
    showUnderline(value) {
        throw new Error("Method not implemented.");
    }
    selectionMenuHidden(value) {
        throw new Error("Method not implemented.");
    }
    barState(value) {
        throw new Error("Method not implemented.");
    }
    maxLines(value) {
        throw new Error("Method not implemented.");
    }
    customKeyboard(value) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.TextInput.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
        return new ArkTextInputComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
/// <reference path="./import.ts" />
class ArkToggleComponent extends ArkComponent {
    onChange(callback) {
        throw new Error("Method not implemented.");
    }
    selectedColor(value) {
        throw new Error("Method not implemented.");
    }
    switchPointColor(color) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Toggle.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
        return new ArkToggleComponent(nativeNode);
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
        return (this.type === another.type) && (this.style === another.style) &&
            (this.top === another.top) && (this.right === another.right) &&
            (this.bottom === another.bottom) && (this.left === another.left);
    }
    parseBorderStyle(value) {
        if (typeof value === "number") {
            this.style = value;
            this.type = true;
            return true;
        }
        else if (typeof value === "object") {
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
        return (this.style === another.style) && (this.radius === another.radius) &&
            (this.type === another.type) && (this.color === another.color) &&
            (this.offsetX === another.offsetX) && (this.offsetY === another.offsetY) &&
            (this.fill === another.fill);
    }
    parseShadowValue(value) {
        if (typeof value === "number") {
            this.style = value;
            return true;
        }
        else if (typeof value === "object") {
            return this.parseShadowOptions(value);
        }
        return false;
    }
    parseShadowOptions(options) {
        var arkColor = new ArkColor();
        if (!arkColor.parseColorValue(options.color)) {
            return false;
        }
        this.radius = options.radius;
        this.type = options.type;
        this.color = arkColor.getColor();
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
        return (this.leftColor === another.leftColor && this.rightColor === another.rightColor && this.topColor === another.topColor && this.bottomColor === another.bottomColor);
    }
}
class ArkPosition {
    constructor() {
        this.x = undefined;
        this.y = undefined;
    }
    isEqual(another) {
        return (this.x === another.x) && (this.y === another.y);
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
        return (this.left === another.left && this.right === another.right && this.top === another.top && this.bottom === another.bottom);
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
        return (this.topLeft === another.topLeft && this.topRight === another.topRight && this.bottomLeft === another.bottomLeft && this.bottomRight === another.bottomRight);
    }
}
class ArkTransformMatrix {
    constructor(matrix) {
        this.matrix = matrix;
        this.length = 16;
    }
    compareArrays(arr1, arr2) {
        return Array.isArray(arr1)
            && Array.isArray(arr2)
            && arr1.length === arr2.length
            && arr1.every((value, index) => value === arr2[index]);
    }
    isEqual(another) {
        return this.compareArrays(this.matrix, another.matrix);
    }
}
