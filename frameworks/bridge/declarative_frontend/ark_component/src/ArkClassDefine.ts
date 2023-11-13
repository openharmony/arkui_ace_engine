

class ArkBorderStyle {
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
    leftColor: number | undefined;
    rightColor: number | undefined;
    topColor: number | undefined;
    bottomColor: number | undefined;

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

class ArkPosition {
    x: number | undefined;
    y: number | undefined;

    constructor() {
        this.x = undefined;
        this.y = undefined;
    }

    isEqual(another: ArkPosition): boolean {
        return (this.x === another.x) && (this.y === another.y);
    }
}


class ArkBorderWidth {
    left: number | undefined;
    right: number | undefined;
    top: number | undefined;
    bottom: number | undefined;

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

class ArkBorderRadius {
    topLeft: number | undefined;
    topRight: number | undefined;
    bottomLeft: number | undefined;
    bottomRight: number | undefined;

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

class ArkTransformMatrix {
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

    isEqual(another: ArkTransformMatrix): void {
        this.compareArrays(this.matrix, another.matrix)
    }
}