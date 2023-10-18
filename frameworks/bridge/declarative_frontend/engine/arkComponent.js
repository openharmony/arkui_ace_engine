class Modifier {
    constructor(value) {
        this.stageValue = value;
    }
    applyStage(node) {
        console.log("linyihao3 applyStage(node)")
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
        console.log("linyihao applyPeer(node, reset)")
        if (reset) {
            globalThis.GetArkUINativeModule().ArkResetBackgroundColor(node);
        }
        else {
            globalThis.GetArkUINativeModule().ArkBackgroundColor(node, this.value);
        }
    }
}

BackgroundColorModifier.identity = Symbol("backgroundColor");
function modifier(modifiers, modifier, value) {
    console.log("linyihao function modifier")
    const identity = modifier["identity"];
    const item = modifiers.get(identity);
    if (item) {
        item.stageValue = value;
    }
    else {
        modifiers.set(identity, new modifier(value));
    }
}

class ArkComponent {
    constructor(nativePtr) {
        console.log("linyihao constructor(nativePtr)")
        this._modifiers = new Map();
        this.nativePtr = nativePtr
    }
    applyModifierPatch() {
        console.log("linyihao applyModifierPatch()")
        let expiringItem = [];
        for (const value of this._modifiers) {
            if (value[1].applyStage(this.nativePtr)) {
                expiringItem.push(value[0]);
            }
        }
        for (const key of expiringItem) {
            this._modifiers.delete(key);
        }
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
        console.log("linyihao backgroundColor(value)");
        var arkColor = new ArkColor();
        if (arkColor.ParseColorValue(value)) {
            modifier(this._modifiers, BackgroundColorModifier, arkColor.color);
        } else {
            throw new Error("Incorrect color notation: " + value)
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
}

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

globalThis.Button.normalStyle = (modifier) => {
    console.log("linyihao globalThis.Button.normalStyle");
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = globalThis.GetArkUINativeModule().ArkGetFrameNodeById(elmtId);
    console.log("linyihao ArkGetFrameNodeById(elmtId)");

    console.log("linyihao thisViewPu.length how long")
    if (thisViewPu.length != 0) {
        console.log("linyihao thisViewPu.length != 0")
        var viewPu = thisViewPu[thisViewPu.length - 1];
        var component = viewPu.getOrCreateArkComponent(elmtId, (nativePtr)=>new ArkButtonComponent(nativePtr), nativeNode);
        modifier.updateStyle(component);
        component.applyModifierPatch();
    }
}


    // var component = new ArkButtonComponent(nativeNode);
    // const viewPu = ViewStackProcessor.GetCustomNode();   //获取自定义组件，新开一个方法用来存储和获取viewPU
    // var component = viewPu.GetOrCreateComponent(elmtId, ()=>new ArkButtonComponent()) // -> create or get
    // modifier.updateStyle(component);
    // component.applyModifierPatch();


//通过当前组件id，获取前端的Ark组件实例，get or create，然后通过modifier的updateStyle调用Ark方法

//前端的Ark组件实例都要存在map里面



const COLOR_WITH_MAGIC = /#[0-9A-Fa-f]{6,8}/;
const COLOR_WITH_MAGIC_MINI = /#[0-9A-Fa-f]{3,4}/;
const COLOR_WITH_RGB = /rgb\(([0-9]{1,3})\,([0-9]{1,3})\,([0-9]{1,3})\)/i;
const COLOR_WITH_RGBA = /rgba\(([0-9]{1,3})\,([0-9]{1,3})\,([0-9]{1,3})\,(\d+\.?\d*)\)/i;

const COLOR_ALPHA_MASK = 0xff000000;
const MIN_RGB_VALUE = 0;
const MAX_RGB_VALUE = 255;
const COLOR_ALPHA_OFFSET = 24;

class ArkColor {
    constructor() {
        this.color = undefined;
        this.flag = false;
    }

    ParseColorValue(value) {
        this.flag = false;
        if (typeof value === "number") {
            this.flag = this.ParseColorUint(value);
        } else if (typeof value === "string") {
            this.flag = this.ParseColorString(value);
        } else if (value === undefined) {
            this.color = value;
            this.flag = true;
        }
        return this.flag;
    }

    ParseColorString(colorStr) {
        if (colorStr.length === 0) {
          return false;
        }
    
        colorStr = colorStr.replace(/\s/g, "");
    
        return (
          this.MatchColorWithMagic(colorStr) ||
          this.MatchColorWithMagicMini(colorStr) ||
          this.MatchColorWithRGB(colorStr) ||
          this.MatchColorWithRGBA(colorStr) ||
          this.MatchColorSpecialString(colorStr) ||
          this.ParseUintColorString(colorStr)
        );
    }

    MatchColorWithMagic(colorStr) {
        const matches = colorStr.match(COLOR_WITH_MAGIC);
        if (matches) {
            colorStr = colorStr.substr(1);
            let value = parseInt(colorStr, 16);
            if (colorStr.length < 8) {
                value |= COLOR_ALPHA_MASK;
            }
            this.color = value;
            return true;
        }
        return false;
    }

    MatchColorWithMagicMini(colorStr) {
        const matches = colorStr.match(COLOR_WITH_MAGIC_MINI);
        if (matches) {
            colorStr = colorStr.substr(1);
            let newColorStr = "";
            for (let i = 0; i < colorStr.length; i++) {
                newColorStr += colorStr[i];
                newColorStr += colorStr[i];
            }
            let value = parseInt(newColorStr, 16);
            if (newColorStr.length < 8) {
                value |= COLOR_ALPHA_MASK;
            }
            this.color = value;
            return true;
        }
        return false;
    }

    MatchColorWithRGB(colorStr) {
        const matches = colorStr.match(COLOR_WITH_RGB);
        if (matches && matches.length === 4) {
            const redInt = parseInt(matches[1]);
            const greenInt = parseInt(matches[2]);
            const blueInt = parseInt(matches[3]);
            if (
                isNaN(redInt) ||
                isNaN(greenInt) ||
                isNaN(blueInt) ||
                !this.IsRGBValid(redInt) ||
                !this.IsRGBValid(greenInt) ||
                !this.IsRGBValid(blueInt)
            ) {
                return false;
            }
            this.color = this.FromRGB(redInt, greenInt, blueInt);
            return true;
        }
    
        return false;
    }

    MatchColorWithRGBA(colorStr) {
        const matches = colorStr.match(COLOR_WITH_RGBA);
        if (matches && matches.length === 5) {
            const redInt = parseInt(matches[1]);
            const greenInt = parseInt(matches[2]);
            const blueInt = parseInt(matches[3]);
            const opacityDouble = parseFloat(matches[4]);
            if (
                isNaN(redInt) ||
                isNaN(greenInt) ||
                isNaN(blueInt) ||
                isNaN(opacityDouble) ||
                !this.IsRGBValid(redInt) ||
                !this.IsRGBValid(greenInt) ||
                !this.IsRGBValid(blueInt) ||
                !this.IsOpacityValid(opacityDouble)
            ) {
                return false;
            }
            this.color = this.FromRGBO(redInt, greenInt, blueInt, opacityDouble);
            return true;
        }
    
        return false;
    }
      
    MatchColorSpecialString(colorStr) {
        const colorTable = [
        { name: "black", colorValue: 0xff000000 },
        { name: "blue", colorValue: 0xff0000ff },
        { name: "gray", colorValue: 0xffc0c0c0 },
        { name: "green", colorValue: 0xff00ff00 },
        { name: "red", colorValue: 0xffff0000 },
        { name: "white", colorValue: 0xffffffff }
        ];
    
        const colorIndex = colorTable.findIndex(entry => entry.name === colorStr);
        if (colorIndex !== -1) {
            const colorValue = colorTable[colorIndex].colorValue;
            this.color = colorValue;
            return true;
        }
    
        return false;
    }

    ParseUintColorString(colorStr) {
        const colorInt = Number(colorStr);
        return this.ParseColorUint(colorInt);
    }

    ParseColorUint(colorInt) {
        if (colorInt > 0) {
            this.color = colorInt;
            if ((colorInt & COLOR_ALPHA_MASK) === 0) {
                this.color |= COLOR_ALPHA_MASK;
            }
            return true;
        }
        return false;
    }

    IsRGBValid(value) {
        return value >= MIN_RGB_VALUE && value <= MAX_RGB_VALUE;
    }

    FromARGB(alpha, red, green, blue) {
        const argb = (alpha << 24) | (red << 16) | (green << 8) | blue;
        return argb >>> 0;
    }

    FromRGBO(red, green, blue, opacity) {
        const alpha = Math.round(opacity * 0xff) & 0xff;
        return this.FromARGB(alpha, red, green, blue);
    }
      
    FromRGB(red, green, blue) {
        return this.FromARGB(0xff, red, green, blue);
    }
}

