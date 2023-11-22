/// <reference path="./import.ts" />

class ArkBorderStyle implements Equable {
    type: boolean | undefined;
    style: number | undefined;
    top: number | undefined;
    right: number | undefined;
    bottom: number | undefined;
    left: number | undefined;

    constructor() {
        this.type = undefined;
        this.style = undefined;
        this.top = undefined;
        this.right = undefined;
        this.bottom = undefined;
        this.left = undefined;
    }
    isEqual(another: ArkBorderStyle): boolean {
        return (this.type === another.type) && (this.style === another.style) &&
            (this.top === another.top) && (this.right === another.right) &&
            (this.bottom === another.bottom) && (this.left === another.left);
    }
    parseBorderStyle(value: number | object): boolean {
        if (typeof value === "number") {
            this.style = value
            this.type = true
            return true;
        } else if (typeof value === "object") {
            return this.parseEdgeStyles(value);
        }
        return false;
    }
    parseEdgeStyles(options: object): boolean {
        this.top = (options as ArkBorderStyle).top;
        this.right = (options as ArkBorderStyle).right;
        this.bottom = (options as ArkBorderStyle).bottom;
        this.left = (options as ArkBorderStyle).left;
        this.type = true
        return true
    }
}

class ArkShadow {
    style: number | undefined;
    radius: number | undefined;
    type: number | undefined;
    color: number | undefined;
    offsetX: number | undefined;
    offsetY: number | undefined;
    fill: number | undefined;

    constructor() {
        this.style = undefined;
        this.radius = undefined;
        this.type = undefined;
        this.color = undefined;
        this.offsetX = undefined;
        this.offsetY = undefined;
        this.fill = undefined;
    }
    isEqual(another: ArkShadow): boolean {
        return (this.style === another.style) && (this.radius === another.radius) &&
            (this.type === another.type) && (this.color === another.color) &&
            (this.offsetX === another.offsetX) && (this.offsetY === another.offsetY) &&
            (this.fill === another.fill);
    }
    parseShadowValue(value: number | object): boolean {
        if (typeof value === "number") {
            this.style = value
            return true;
        } else if (typeof value === "object") {
            return this.parseShadowOptions(value);
        }
        return false;
    }
    parseShadowOptions(options: object): boolean {
        var arkColor = new ArkColor();
        if (!arkColor.parseColorValue((options as ArkShadow).color)) {
            return false
        }
        this.radius = (options as ArkShadow).radius
        this.type = (options as ArkShadow).type
        this.color = arkColor.getColor();
        this.offsetX = (options as ArkShadow).offsetX
        this.offsetY = (options as ArkShadow).offsetY
        this.fill = (options as ArkShadow).fill
        return true
    }
}

class ArkBorderColor {
    leftColor: number | undefined | Resource;
    rightColor: number | undefined | Resource;
    topColor: number | undefined | Resource;
    bottomColor: number | undefined | Resource;

    constructor() {
        this.leftColor = undefined;
        this.rightColor = undefined;
        this.topColor = undefined;
        this.bottomColor = undefined;
    }

    isEqual(another: ArkBorderColor): boolean {
        return (this.leftColor === another.leftColor && this.rightColor === another.rightColor && this.topColor === another.topColor && this.bottomColor === another.bottomColor);
    }
}

class ArkPosition implements Equable {
    x: number | string | undefined | Resource;
    y: number | string | undefined | Resource;

    constructor() {
        this.x = undefined;
        this.y = undefined;
    }

    isEqual(another: ArkPosition): boolean {
        return (this.x === another.x) && (this.y === another.y);
    }
}


class ArkBorderWidth implements Equable {
    left: number | string | undefined | Resource;
    right: number | string | undefined| Resource;
    top: number | string | undefined| Resource;
    bottom: number | string | undefined| Resource;

    constructor() {
        this.left = undefined;
        this.right = undefined;
        this.top = undefined;
        this.bottom = undefined;
    }

    isEqual(another: ArkBorderWidth): boolean {
        return (this.left === another.left && this.right === another.right && this.top === another.top && this.bottom === another.bottom);
    }
}

class ArkBorderRadius implements Equable {
    topLeft: number | string | undefined | Resource;
    topRight: number | string | undefined | Resource;
    bottomLeft: number | string | undefined | Resource;
    bottomRight: number | string | undefined | Resource;

    constructor() {
        this.topLeft = undefined;
        this.topRight = undefined;
        this.bottomLeft = undefined;
        this.bottomRight = undefined;
    }

    isEqual(another: ArkBorderRadius): boolean {
        return (this.topLeft === another.topLeft && this.topRight === another.topRight && this.bottomLeft === another.bottomLeft && this.bottomRight === another.bottomRight);
    }
}

class ArkTransformMatrix implements Equable  {
    matrix: [];
    length: number;

    constructor(matrix: []) {
        this.matrix = matrix;
        this.length = 16;
    }

    compareArrays(arr1: [], arr2: []): boolean {
        return Array.isArray(arr1)
            && Array.isArray(arr2)
            && arr1.length === arr2.length
            && arr1.every((value, index) => value === arr2[index]);
    }

    isEqual(another: ArkTransformMatrix): boolean {
        return this.compareArrays(this.matrix, another.matrix)
    }
}

class ArkLabelStyle {
    overflow: number | undefined;
    maxLines: number | undefined;
    minFontSize: number | string | undefined| Resource;
    maxFontSize: number | string | undefined| Resource;
    heightAdaptivePolicy: number | undefined;
    font: ArkLabelFont;

    constructor() {
        this.overflow = undefined;
        this.maxLines = undefined;
        this.minFontSize = undefined;
        this.maxFontSize = undefined;
        this.heightAdaptivePolicy = undefined;
        this.font = undefined;
    }

    isEqual(another: ArkLabelStyle): boolean {
        return (this.overflow === another.overflow && this.maxLines === another.maxLines &&
            this.minFontSize === another.minFontSize && this.maxFontSize === another.maxFontSize &&
            this.heightAdaptivePolicy === another.heightAdaptivePolicy && this.font.isEqual(another.font));
    }
}

class ArkLabelFont {
    size: number | string | undefined| Resource;
    weight: string | undefined;
    family: string | undefined;
    style:  number | undefined;
    constructor() {
        this.size = undefined;
        this.weight = undefined;
        this.family = undefined;
        this.style = undefined;
    }

    isEqual(another: ArkLabelFont): boolean {
        return (this.size === another.size && this.weight === another.weight && this.family === another.family &&
            this.style === another.style);
    }
}

function ArkDeepCompareArrays(arr1: Array<any>, arr2: Array<any>): boolean {
    return Array.isArray(arr1)
        && Array.isArray(arr2)
        && arr1.length === arr2.length
        && arr1.every((value, index) => {
            if (Array.isArray(value) && Array.isArray(arr2[index])) {
                return ArkDeepCompareArrays(value, arr2[index]);
            } else {
                return (value === arr2[index]);
            }
        });
}

class ArkLinearGradient {
    angle: number | string | undefined;
    direction: number | undefined;
    colors: Array<any>;
    repeating: boolean | undefined;

    constructor(angle: number | string | undefined,
        direction: number | undefined,
        colors: Array<any>,
        repeating: boolean | undefined) {
        this.angle = angle;
        this.direction = direction;
        this.colors = colors;
        this.repeating = repeating;
    }

    isEqual(another: ArkLinearGradient): boolean {
        return ((this.angle === another.angle) && (this.direction === another.direction) &&
            (ArkDeepCompareArrays(this.colors, another.colors)) && (this.repeating === another.repeating));
    }
}
