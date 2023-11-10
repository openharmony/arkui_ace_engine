//@ts-nocheck
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
            globalThis.getArkUINativeModule().common.resetBackgroundColor(node);
        }
        else {
            globalThis.getArkUINativeModule().common.setBackgroundColor(node, this.value);
        }
    }
}
BackgroundColorModifier.identity = Symbol("backgroundColor");
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
        throw new Error("Method not implemented.");
    }
    height(value) {
        throw new Error("Method not implemented.");
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
        throw new Error("Method not implemented.");
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
        throw new Error("Method not implemented.");
    }
    border(value) {
        throw new Error("Method not implemented.");
    }
    borderStyle(value) {
        throw new Error("Method not implemented.");
    }
    borderWidth(value) {
        throw new Error("Method not implemented.");
    }
    borderColor(value) {
        throw new Error("Method not implemented.");
    }
    borderRadius(value) {
        throw new Error("Method not implemented.");
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
        throw new Error("Method not implemented.");
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
        throw new Error("Method not implemented.");
    }
    sharedTransition(id, options) {
        throw new Error("Method not implemented.");
    }
    direction(value) {
        throw new Error("Method not implemented.");
    }
    align(value) {
        throw new Error("Method not implemented.");
    }
    position(value) {
        throw new Error("Method not implemented.");
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
        throw new Error("Method not implemented.");
    }
    clip(value) {
        throw new Error("Method not implemented.");
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
    bindContentCover(isShow, builder, options) {
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
    }
}
//@ts-nocheck
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
globalThis.Button.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = globalThis.getArkUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
        return new ArkButtonComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
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
}
