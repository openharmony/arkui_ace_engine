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
    static identity = Symbol("backgroundColor");

    applyPeer(node, reset) {
        if (reset) {
            globalThis.getArkUINativeModule().common.resetBackgroundColor(node);
        }
        else {
            globalThis.getArkUINativeModule().common.setBackgroundColor(node, this.value);
        }
    }
}

function modifier(modifiers, modifierClass, value) {
    const identity = modifierClass.identity;
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
    backgroundColor(value) {
        var arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, BackgroundColorModifier, arkColor.color);
        } else {
            modifier(this._modifiers, BackgroundColorModifier, undefined);
        }
        return this;
    }
}

class ArkButtonComponent extends ArkComponent {
    // ...
}

globalThis.Button.attributeModifier = (modifier) => {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = globalThis.getArkUINativeModule().getFrameNodeById(elmtId);

    if (thisViewPu.length != 0) {
        var viewPu = thisViewPu[thisViewPu.length - 1];
        var component = viewPu.getOrCreateArkComponent(elmtId, (nativePtr)=>new ArkButtonComponent(nativePtr), nativeNode);
        modifier.applyNormalAttribute(component);
        component.applyModifierPatch();
    }
}


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
        } else if (typeof value === "string") {
            return this.parseColorString(value);
        } else if (value === undefined) {
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
        return (
          this.matchColorWithMagic(colorStr) ||
          this.matchColorWithMagicMini(colorStr) ||
          this.matchColorWithRGB(colorStr) ||
          this.matchColorWithRGBA(colorStr) ||
          this.matchColorSpecialString(colorStr) ||
          this.parseUintColorString(colorStr)
        );
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
            if (this.isRGBValid(redInt) && this.isRGBValid(greenInt) && this.isRGBValid(blueInt)) {
                this.color = this.fromRGB(redInt, greenInt, blueInt);
                return true;
            }
        }
        return false;
    }
    
    matchColorWithRGBA(colorStr) {
        const matches = colorStr.match(COLOR_WITH_RGBA);
        if (matches && matches.length === 5) {
            const [_, redInt, greenInt, blueInt, opacityDouble] = matches;
            if (this.isRGBValid(redInt) && this.isRGBValid(greenInt) && this.isRGBValid(blueInt) &&
                this.isOpacityValid(opacityDouble)) {
                this.color = this.fromRGBO(redInt, greenInt, blueInt, opacityDouble);
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

