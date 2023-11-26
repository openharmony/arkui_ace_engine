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
        if (isResource(options.radius) || isResource(options.color) ||
            isResource(options.offsetX) || isResource(options.offsetY)) {
            return false;
        }
        var arkColor = new ArkColor();
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
        return (this.overflow === another.overflow && this.maxLines === another.maxLines &&
            this.minFontSize === another.minFontSize && this.maxFontSize === another.maxFontSize &&
            this.heightAdaptivePolicy === another.heightAdaptivePolicy && this.font.isEqual(another.font));
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
        return (this.size === another.size && this.weight === another.weight && this.family === another.family &&
            this.style === another.style);
    }
}
function ArkDeepCompareArrays(arr1, arr2) {
    return Array.isArray(arr1)
        && Array.isArray(arr2)
        && arr1.length === arr2.length
        && arr1.every((value, index) => {
            if (Array.isArray(value) && Array.isArray(arr2[index])) {
                return ArkDeepCompareArrays(value, arr2[index]);
            }
            else {
                return (value === arr2[index]);
            }
        });
}
class ArkLinearGradient {
    constructor(angle, direction, colors, repeating) {
        this.angle = angle;
        this.direction = direction;
        this.colors = colors;
        this.repeating = repeating;
    }
    isEqual(another) {
        return ((this.angle === another.angle) && (this.direction === another.direction) &&
            (ArkDeepCompareArrays(this.colors, another.colors)) && (this.repeating === another.repeating));
    }
}
class ArkRadialGradient {
    constructor(center, radius, colors, repeating) {
        this.center = center;
        this.radius = radius;
        this.colors = colors;
        this.repeating = repeating;
    }
    isEqual(another) {
        return ((ArkDeepCompareArrays(this.center, another.center)) &&
            (this.radius === another.radius) &&
            (ArkDeepCompareArrays(this.colors, another.colors)) &&
            (this.repeating === another.repeating));
    }
}
class ArkSweepGradient {
    constructor(center, start, end, rotation, colors, repeating) {
        this.center = center;
        this.start = start;
        this.end = end;
        this.rotation = rotation;
        this.colors = colors;
        this.repeating = repeating;
    }
    isEqual(another) {
        return ((ArkDeepCompareArrays(this.center, another.center)) &&
            (this.start === another.start) && (this.end === another.end) &&
            (this.rotation === another.rotation) &&
            (ArkDeepCompareArrays(this.colors, another.colors)) &&
            (this.repeating === another.repeating));
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
        return ((this.blurStyle === another.blurStyle) &&
            (this.colorMode === another.colorMode) && (this.adaptiveColor === another.adaptiveColor) &&
            (this.scale === another.scale));
    }
}
class ArkLinearGradientBlur {
    constructor() {
        this.blurRadius = undefined;
        this.fractionStops = undefined;
        this.direction = undefined;
    }
    isEqual(another) {
        return ((this.blurRadius === another.blurRadius) &&
            (ArkDeepCompareArrays(this.fractionStops, another.fractionStops)) &&
            (this.direction === another.direction));
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
        return ((this.blurStyle === another.blurStyle) &&
            (this.colorMode === another.colorMode) && (this.adaptiveColor === another.adaptiveColor) &&
            (this.scale === another.scale));
    }
}
class ArkFont {
    constructor() {
        this.size = "16fp";
        this.weight = "400";
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
        return this.size === another.size && this.weight === another.weight && this.family === another.family && this.style === another.style;
    }
    parseFontWeight(value) {
        if (typeof value === 'number') {
            if (value === 0) {
                this.weight = "Lighter";
            }
            else if (value === 1) {
                this.weight = "Normal";
            }
            else if (value === 2) {
                this.weight = "Regular";
            }
            else if (value === 3) {
                this.weight = "Medium";
            }
            else if (value === 4) {
                this.weight = "Bold";
            }
            else if (value === 5) {
                this.weight = "Bolder";
            }
            else {
                this.weight = value.toString();
            }
        }
        else if (typeof value === 'string') {
            this.weight = value;
        }
        else {
            this.weight = "400";
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
        return (this.alignType === another.alignType) && (this.dx === another.dx) && (this.dy === another.dy);
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
        return (this.checkedBackgroundColor === another.checkedBackgroundColor
            && this.uncheckedBorderColor === another.uncheckedBorderColor
            && this.indicatorColor === another.indicatorColor);
    }
}
class ArkStarStyle {
    constructor() {
        this.backgroundUri = undefined;
        this.foregroundUri = undefined;
        this.secondaryUri = undefined;
    }
    isEqual(another) {
        return this.backgroundUri === another.backgroundUri
            && this.foregroundUri === another.foregroundUri
            && this.secondaryUri === another.secondaryUri;
    }
}
class ArkMarkStyle {
    constructor() {
        this.strokeColor = undefined;
        this.size = undefined;
        this.strokeWidth = undefined;
    }
    isEqual(another) {
        return (this.strokeColor === another.strokeColor) && (this.size === another.size) &&
            (this.strokeWidth === another.strokeWidth);
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
        return Array.isArray(arr1)
            && Array.isArray(arr2)
            && arr1.length === arr2.length
            && arr1.every((value, index) => value === arr2[index]);
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
        return (this.width === another.width) && (this.height === another.height);
    }
}
class ArkDecoration {
    constructor() {
        this.type = TextDecorationType.None;
        this.color = undefined;
    }
    isEqual(another) {
        return (this.type === another.type) && (this.color === another.color);
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
        return (this.arkWidth.isEqual(another.arkWidth) && this.arkColor.isEqual(another.arkColor) && this.arkRadius.isEqual(another.arkRadius) && this.arkStyle.isEqual(another.arkStyle));
    }
}
class ArkBackgroundImagePosition {
    constructor() {
        this.alignment = undefined;
        this.x = undefined;
        this.y = undefined;
    }
    isEqual(another) {
        return (this.alignment === another.alignment) && (this.x === another.x) &&
            (this.y === another.y);
    }
}
class ArkBackgroundImageSize {
    constructor() {
        this.imageSize = undefined;
        this.width = undefined;
        this.height = undefined;
    }
    isEqual(another) {
        return (this.imageSize === another.imageSize) && (this.width === another.width) &&
            (this.height === another.height);
    }
}
class ArkBackgroundImage {
    constructor() {
        this.src = undefined;
        this.repeat = undefined;
    }
    isEqual(another) {
        return (this.src === another.src) && (this.repeat === another.repeat);
    }
}
class ArkTranslate {
    constructor() {
        this.x = undefined;
        this.y = undefined;
        this.z = undefined;
    }
    isEqual(another) {
        return (this.x === another.x) && (this.y === another.y) && (this.z === another.z);
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
        return (this.x === another.x) && (this.y === another.y) && (this.z === another.z) && (this.centerX === another.centerX) && (this.centerY === another.centerY);
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
        return (this.x === another.x) && (this.y === another.y) && (this.z === another.z) && (this.angle === another.angle) &&
            (this.centerX === another.centerX) && (this.centerY === another.centerY) && (this.centerZ === another.centerZ) && (this.perspective === another.perspective);
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
        return ((this.top === another.top) && (this.right === another.right) &&
            (this.bottom === another.bottom) && (this.left === another.left));
    }
}
class ArkForegroundColor {
    constructor() {
        this.color = undefined;
        this.strategy = undefined;
    }
    isEqual(another) {
        return ((this.color === another.color) && (this.strategy === another.strategy));
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
        return (this.path === another.path) && (this.from === another.from) && (this.to === another.to)
            && (this.rotatable === another.rotatable);
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
        return (this.xs === another.xs) && (this.sm === another.sm) && (this.md === another.md) &&
            (this.lg === another.lg) && (this.xl === another.xl) && (this.xxl === another.xxl);
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
/// <reference path="./import.ts" />
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
            if(this.value === undefined)
            {                
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
        if (this.stageValue === this.value) {
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
        throw new Error("Method not implemented.");
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
        var arkBackgroundImage = new ArkBackgroundImage();
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
        var arkBackgroundImageSize = new ArkBackgroundImageSize();
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
        var arkBackgroundImagePosition = new ArkBackgroundImagePosition();
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
        var _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p, _q, _r, _s, _t, _u, _v, _w, _x, _y, _z, _0, _1, _2, _3;
        var arkBorder = new ArkBorder();
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
            var arkColor = new ArkColor();
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
            var arkBorderStyle = new ArkBorderStyle();
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
        throw new Error("Method not implemented.");
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
        var arkColor = new ArkColor();
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
        var arkTranslate = new ArkTranslate();
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
        var arkScale = new ArkScale();
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
        throw new Error("Method not implemented.");
    }
    gridOffset(value) {
        throw new Error("Method not implemented.");
    }
    rotate(value) {
        var arkRotate = new ArkRotate();
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
        throw new Error("Method not implemented.");
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
        modifier(this._modifiers, RenderFitModifier, fitMode);
        return this;
    }
    attributeModifier(modifier) {
        return this;
    }
}
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
        var arkColor = new ArkColor();
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
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
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
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
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
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
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
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
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
    onGestureJudgeBegin(callback) {
        throw new Error("Method not implemented.");
    }
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
class ArkTextComponent extends ArkComponent {
    enableDataDetector(enable) {
        throw new Error("Method not implemented.");
    }
    dataDetectorConfig(config) {
        throw new Error("Method not implemented.");
    }
    onGestureJudgeBegin(callback) {
        throw new Error("Method not implemented.");
    }
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
        throw new Error("Method not implemented.");
    }
    maxLines(value) {
        throw new Error("Method not implemented.");
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
            if (value.color !== null && value.color !== undefined) {
                arkDecoration.color = value.color;
            }
            modifier(this._modifiers, TextDecorationModifier, arkDecoration);
        }
        return this;
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
    onGestureJudgeBegin(callback) {
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
    cancelButton(value) {
        throw new Error("Method not implemented.");
    }
    onGestureJudgeBegin(callback) {
        throw new Error("Method not implemented.");
    }
    selectAll(value) {
        throw new Error("Method not implemented.");
    }
    enableAutoFill(value) {
        throw new Error("Method not implemented.");
    }
    passwordRules(value) {
        throw new Error("Method not implemented.");
    }
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
    onGestureJudgeBegin(callback) {
        throw new Error("Method not implemented.");
    }
    onChange(callback) {
        throw new Error("Method not implemented.");
    }
    selectedColor(value) {
        var arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, ToggleSelectedColorModifier, arkColor.color);
        }
        else {
            modifier(this._modifiers, ToggleSelectedColorModifier, undefined);
        }
        return this;
    }
    switchPointColor(value) {
        var arkColor = new ArkColor();
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
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
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
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
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
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
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
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
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
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
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
        throw new Error("Method not implemented.");
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
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
        return new ArkSliderComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
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
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
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
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
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
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
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
        var arkMarkStyle = new ArkMarkStyle();
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
class ArkPanelComponent extends ArkComponent {
    mode(value) {
        throw new Error("Method not implemented.");
    }
    type(value) {
        throw new Error("Method not implemented.");
    }
    dragBar(value) {
        if (typeof value === "boolean") {
            modifier(this._modifiers, DragBarModifier, value);
        }
        else {
            modifier(this._modifiers, DragBarModifier, undefined);
        }
        return this;
    }
    customHeight(value) {
        throw new Error("Method not implemented.");
    }
    fullHeight(value) {
        throw new Error("Method not implemented.");
    }
    halfHeight(value) {
        throw new Error("Method not implemented.");
    }
    miniHeight(value) {
        throw new Error("Method not implemented.");
    }
    show(value) {
        if (typeof value === "boolean") {
            modifier(this._modifiers, ShowModifier, value);
        }
        else {
            modifier(this._modifiers, ShowModifier, undefined);
        }
        return this;
    }
    backgroundMask(color) {
        throw new Error("Method not implemented.");
    }
    showCloseIcon(value) {
        if (typeof value === "boolean") {
            modifier(this._modifiers, ShowCloseIconModifier, value);
        }
        else {
            modifier(this._modifiers, ShowCloseIconModifier, undefined);
        }
        return this;
    }
    onChange(event) {
        throw new Error("Method not implemented.");
    }
    onHeightChange(callback) {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.Refresh.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
        return new ArkPanelComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
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
ShowCloseIconModifier.identity = Symbol("showCloseIcon");
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
DragBarModifier.identity = Symbol("dragBar");
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
ShowModifier.identity = Symbol("show");
//@ts-nocheck
class ArkNavigationComponent extends ArkComponent {
    navBarWidth(value) {
        throw new Error("Method not implemented.");
    }
    navBarPosition(value) {
        throw new Error("Method not implemented.");
    }
    navBarWidthRange(value) {
        throw new Error("Method not implemented.");
    }
    minContentWidth(value) {
        throw new Error("Method not implemented.");
    }
    mode(value) {
        throw new Error("Method not implemented.");
    }
    backButtonIcon(value) {
        throw new Error("Method not implemented.");
    }
    hideNavBar(value) {
        throw new Error("Method not implemented.");
    }
    title(value) {
        throw new Error("Method not implemented.");
    }
    subTitle(value) {
        throw new Error("Method not implemented.");
    }
    hideTitleBar(value) {
        throw new Error("Method not implemented.");
    }
    hideBackButton(value) {
        throw new Error("Method not implemented.");
    }
    titleMode(value) {
        throw new Error("Method not implemented.");
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
//@ts-ignore
globalThis.Navigation.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkNavigationComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
};
