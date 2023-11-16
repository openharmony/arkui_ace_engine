const KeyCode = requireNapi("multimodalInput.keyCode").KeyCode;

export var ChipSize;
!function(e){
    e.NORMAL = "NORMAL";
    e.SMALL = "SMALL"
}(ChipSize || (ChipSize = {}));

export const defaultTheme = {
    prefixIcon: {
        size: { width: 16, height: 16 },
        fillColor: {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_secondary"],
            bundleName: "",
            moduleName: ""
        }
    },
    label: {
        fontSize: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_button3"],
            bundleName: "",
            moduleName: ""
        },
        fontColor: {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_text_primary"],
            bundleName: "",
            moduleName: ""
        },
        fontFamily: "HarmonyOS Sans",
        normalMargin: { left: 6, right: 6, top: 0, bottom: 0 },
        smallMargin: { left: 4, right: 4, top: 0, bottom: 0 }
    },
    suffixIcon: {
        size: { width: 16, height: 16 },
        fillColor: {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_primary"],
            bundleName: "",
            moduleName: ""
        },
        defaultDeleteIcon: {
            id: -1,
            type: 2e4,
            params: ["sys.media.ohos_ic_public_cancel", 16, 16],
            bundleName: "",
            moduleName: ""
        },
        focusable: !1
    },
    chipNode: {
        normalHeight: 36,
        smallHeight: 28,
        enabled: !0,
        backgroundColor: {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_button_normal"],
            bundleName: "",
            moduleName: ""
        },
        focusOutlineColor: {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_focused_outline"],
            bundleName: "",
            moduleName: ""
        },
        normalBorderRadius: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_corner_radius_button"],
            bundleName: "",
            moduleName: ""
        },
        smallBorderRadius: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_corner_radius_small_button"],
            bundleName: "",
            moduleName: ""
        },
        borderWidth: 2,
        normalPadding: { left: 16, right: 16, top: 0, bottom: 0 },
        smallPadding: { left: 12, right: 12, top: 0, bottom: 0 },
        hoverBlendColor: {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_hover"],
            bundleName: "",
            moduleName: ""
        },
        pressedBlendColor: {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_click_effect"],
            bundleName: "",
            moduleName: ""
        },
        opacity: { normal: 1, hover: .95, pressed: .9, disabled: .4 }
    }
};
const noop = () => {
};

export function Chip(e, i = null) {
    (i || this).observeComponentCreation2(((o, t) => {
        if (t) {
            let t = () => ({
                chipSize: e.size,
                prefixIcon: e.prefixIcon,
                label: e.label,
                suffixIcon: e.suffixIcon,
                allowClose: e.allowClose,
                chipEnabled: e.enabled,
                chipNodeBackgroundColor: e.backgroundColor,
                chipNodeRadius: e.borderRadius,
                onClose: e.onClose
            });
            ViewPU.create(new ChipComponent(i || this, {
                chipSize: e.size,
                prefixIcon: e.prefixIcon,
                label: e.label,
                suffixIcon: e.suffixIcon,
                allowClose: e.allowClose,
                chipEnabled: e.enabled,
                chipNodeBackgroundColor: e.backgroundColor,
                chipNodeRadius: e.borderRadius,
                onClose: e.onClose
            }, void 0, o, t))
        } else (i || this).updateStateVarsOfChildByElmtId(o, {
            chipSize: e.size,
            prefixIcon: e.prefixIcon,
            label: e.label,
            suffixIcon: e.suffixIcon,
            allowClose: e.allowClose,
            chipEnabled: e.enabled,
            chipNodeBackgroundColor: e.backgroundColor,
            chipNodeRadius: e.borderRadius
        })
    }), null)
}

export class ChipComponent extends ViewPU {
    constructor(e, i, o, t = -1, s = void 0) {
        super(e, o, t);
        "function" == typeof s && (this.paramsGenerator_ = s);
        this.theme = defaultTheme;
        this.__chipSize = new SynchedPropertyObjectOneWayPU(i.chipSize, this, "chipSize");
        this.__allowClose = new SynchedPropertySimpleOneWayPU(i.allowClose, this, "allowClose");
        this.__prefixIcon = new SynchedPropertyObjectOneWayPU(i.prefixIcon, this, "prefixIcon");
        this.__label = new SynchedPropertyObjectOneWayPU(i.label, this, "label");
        this.__suffixIcon = new SynchedPropertyObjectOneWayPU(i.suffixIcon, this, "suffixIcon");
        this.__chipNodeBackgroundColor = new SynchedPropertyObjectOneWayPU(i.chipNodeBackgroundColor, this, "chipNodeBackgroundColor");
        this.__chipNodeRadius = new SynchedPropertyObjectOneWayPU(i.chipNodeRadius, this, "chipNodeRadius");
        this.__chipEnabled = new SynchedPropertySimpleOneWayPU(i.chipEnabled, this, "chipEnabled");
        this.__isHover = new ObservedPropertySimplePU(!1, this, "isHover");
        this.__isPressed = new ObservedPropertySimplePU(!1, this, "isPressed");
        this.__chipScale = new ObservedPropertyObjectPU({ x: 1, y: 1 }, this, "chipScale");
        this.__chipOpacity = new ObservedPropertySimplePU(1, this, "chipOpacity");
        this.__chipBlendColor = new ObservedPropertyObjectPU(Color.Transparent, this, "chipBlendColor");
        this.__deleteChip = new ObservedPropertySimplePU(!1, this, "deleteChip");
        this.chipNodeSize = {};
        this.onClose = noop;
        this.useDefaultSuffixIcon = !1;
        this.setInitiallyProvidedValue(i)
    }

    setInitiallyProvidedValue(e) {
        void 0 !== e.theme && (this.theme = e.theme);
        void 0 === e.chipSize && this.__chipSize.set(ChipSize.NORMAL);
        void 0 === e.allowClose && this.__allowClose.set(!0);
        void 0 === e.prefixIcon && this.__prefixIcon.set({ src: "" });
        void 0 === e.label && this.__label.set({ text: "" });
        void 0 === e.suffixIcon && this.__suffixIcon.set({ src: "" });
        void 0 === e.chipNodeBackgroundColor && this.__chipNodeBackgroundColor.set(this.theme.chipNode.backgroundColor);
        void 0 === e.chipNodeRadius && this.__chipNodeRadius.set(this.theme.chipNode.normalBorderRadius);
        void 0 === e.chipEnabled && this.__chipEnabled.set(!0);
        void 0 !== e.isHover && (this.isHover = e.isHover);
        void 0 !== e.isPressed && (this.isPressed = e.isPressed);
        void 0 !== e.chipScale && (this.chipScale = e.chipScale);
        void 0 !== e.chipOpacity && (this.chipOpacity = e.chipOpacity);
        void 0 !== e.chipBlendColor && (this.chipBlendColor = e.chipBlendColor);
        void 0 !== e.deleteChip && (this.deleteChip = e.deleteChip);
        void 0 !== e.chipNodeSize && (this.chipNodeSize = e.chipNodeSize);
        void 0 !== e.onClose && (this.onClose = e.onClose);
        void 0 !== e.useDefaultSuffixIcon && (this.useDefaultSuffixIcon = e.useDefaultSuffixIcon)
    }

    updateStateVars(e) {
        this.__chipSize.reset(e.chipSize);
        this.__allowClose.reset(e.allowClose);
        this.__prefixIcon.reset(e.prefixIcon);
        this.__label.reset(e.label);
        this.__suffixIcon.reset(e.suffixIcon);
        this.__chipNodeBackgroundColor.reset(e.chipNodeBackgroundColor);
        this.__chipNodeRadius.reset(e.chipNodeRadius);
        this.__chipEnabled.reset(e.chipEnabled)
    }

    purgeVariableDependenciesOnElmtId(e) {
        this.__chipSize.purgeDependencyOnElmtId(e);
        this.__allowClose.purgeDependencyOnElmtId(e);
        this.__prefixIcon.purgeDependencyOnElmtId(e);
        this.__label.purgeDependencyOnElmtId(e);
        this.__suffixIcon.purgeDependencyOnElmtId(e);
        this.__chipNodeBackgroundColor.purgeDependencyOnElmtId(e);
        this.__chipNodeRadius.purgeDependencyOnElmtId(e);
        this.__chipEnabled.purgeDependencyOnElmtId(e);
        this.__isHover.purgeDependencyOnElmtId(e);
        this.__isPressed.purgeDependencyOnElmtId(e);
        this.__chipScale.purgeDependencyOnElmtId(e);
        this.__chipOpacity.purgeDependencyOnElmtId(e);
        this.__chipBlendColor.purgeDependencyOnElmtId(e);
        this.__deleteChip.purgeDependencyOnElmtId(e)
    }

    aboutToBeDeleted() {
        this.__chipSize.aboutToBeDeleted();
        this.__allowClose.aboutToBeDeleted();
        this.__prefixIcon.aboutToBeDeleted();
        this.__label.aboutToBeDeleted();
        this.__suffixIcon.aboutToBeDeleted();
        this.__chipNodeBackgroundColor.aboutToBeDeleted();
        this.__chipNodeRadius.aboutToBeDeleted();
        this.__chipEnabled.aboutToBeDeleted();
        this.__isHover.aboutToBeDeleted();
        this.__isPressed.aboutToBeDeleted();
        this.__chipScale.aboutToBeDeleted();
        this.__chipOpacity.aboutToBeDeleted();
        this.__chipBlendColor.aboutToBeDeleted();
        this.__deleteChip.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal()
    }

    get chipSize() {
        return this.__chipSize.get()
    }

    set chipSize(e) {
        this.__chipSize.set(e)
    }

    get allowClose() {
        return this.__allowClose.get()
    }

    set allowClose(e) {
        this.__allowClose.set(e)
    }

    get prefixIcon() {
        return this.__prefixIcon.get()
    }

    set prefixIcon(e) {
        this.__prefixIcon.set(e)
    }

    get label() {
        return this.__label.get()
    }

    set label(e) {
        this.__label.set(e)
    }

    get suffixIcon() {
        return this.__suffixIcon.get()
    }

    set suffixIcon(e) {
        this.__suffixIcon.set(e)
    }

    get chipNodeBackgroundColor() {
        return this.__chipNodeBackgroundColor.get()
    }

    set chipNodeBackgroundColor(e) {
        this.__chipNodeBackgroundColor.set(e)
    }

    get chipNodeRadius() {
        return this.__chipNodeRadius.get()
    }

    set chipNodeRadius(e) {
        this.__chipNodeRadius.set(e)
    }

    get chipEnabled() {
        return this.__chipEnabled.get()
    }

    set chipEnabled(e) {
        this.__chipEnabled.set(e)
    }

    get isHover() {
        return this.__isHover.get()
    }

    set isHover(e) {
        this.__isHover.set(e)
    }

    get isPressed() {
        return this.__isPressed.get()
    }

    set isPressed(e) {
        this.__isPressed.set(e)
    }

    get chipScale() {
        return this.__chipScale.get()
    }

    set chipScale(e) {
        this.__chipScale.set(e)
    }

    get chipOpacity() {
        return this.__chipOpacity.get()
    }

    set chipOpacity(e) {
        this.__chipOpacity.set(e)
    }

    get chipBlendColor() {
        return this.__chipBlendColor.get()
    }

    set chipBlendColor(e) {
        this.__chipBlendColor.set(e)
    }

    get deleteChip() {
        return this.__deleteChip.get()
    }

    set deleteChip(e) {
        this.__deleteChip.set(e)
    }

    isChipSizeEnum() {
        return "string" == typeof this.chipSize
    }

    getLabelFontSize() {
        var e, i;
        return null !== (i = null === (e = this.label) || void 0 === e ? void 0 : e.fontSize) && void 0 !== i ? i : this.theme.label.fontSize
    }

    getLabelFontColor() {
        var e, i;
        return null !== (i = null === (e = this.label) || void 0 === e ? void 0 : e.fontColor) && void 0 !== i ? i : this.theme.label.fontColor
    }

    getLabelFontFamily() {
        var e, i;
        return null !== (i = null === (e = this.label) || void 0 === e ? void 0 : e.fontFamily) && void 0 !== i ? i : this.theme.label.fontFamily
    }

    getLabelMargin() {
        var e, i, o, t, s, h;
        return {
            left: null !== (o = null === (i = null === (e = this.label) || void 0 === e ? void 0 : e.labelMargin) || void 0 === i ? void 0 : i.left) && void 0 !== o ? o : this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL ? this.theme.label.smallMargin.left : this.theme.label.normalMargin.left,
            right: null !== (h = null === (s = null === (t = this.label) || void 0 === t ? void 0 : t.labelMargin) || void 0 === s ? void 0 : s.right) && void 0 !== h ? h : this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL ? this.theme.label.smallMargin.right : this.theme.label.normalMargin.right
        }
    }

    getSuffixIconSize() {
        var e, i, o, t, s, h, l, n;
        return {
            width: null !== (o = null === (i = null === (e = this.suffixIcon) || void 0 === e ? void 0 : e.size) || void 0 === i ? void 0 : i.width) && void 0 !== o ? o : (null === (t = this.suffixIcon) || void 0 === t ? void 0 : t.src) || this.useDefaultSuffixIcon ? this.theme.suffixIcon.size.width : 0,
            height: null !== (l = null === (h = null === (s = this.suffixIcon) || void 0 === s ? void 0 : s.size) || void 0 === h ? void 0 : h.height) && void 0 !== l ? l : (null === (n = this.suffixIcon) || void 0 === n ? void 0 : n.src) || this.useDefaultSuffixIcon ? this.theme.suffixIcon.size.height : 0
        }
    }

    getPrefixIconSize() {
        var e, i, o, t, s, h, l, n;
        return {
            width: null !== (o = null === (i = null === (e = this.prefixIcon) || void 0 === e ? void 0 : e.size) || void 0 === i ? void 0 : i.width) && void 0 !== o ? o : (null === (t = this.prefixIcon) || void 0 === t ? void 0 : t.src) ? this.theme.prefixIcon.size.width : 0,
            height: null !== (l = null === (h = null === (s = this.prefixIcon) || void 0 === s ? void 0 : s.size) || void 0 === h ? void 0 : h.height) && void 0 !== l ? l : (null === (n = this.prefixIcon) || void 0 === n ? void 0 : n.src) ? this.theme.prefixIcon.size.height : 0
        }
    }

    getPrefixIconFilledColor() {
        var e, i;
        return null !== (i = null === (e = this.prefixIcon) || void 0 === e ? void 0 : e.fillColor) && void 0 !== i ? i : this.theme.prefixIcon.fillColor
    }

    getSuffixIconFilledColor() {
        var e, i;
        return null !== (i = null === (e = this.suffixIcon) || void 0 === e ? void 0 : e.fillColor) && void 0 !== i ? i : this.theme.suffixIcon.fillColor
    }

    getSuffixIconFocusable() {
        var e;
        return this.useDefaultSuffixIcon && this.allowClose || void 0 !== (null === (e = this.suffixIcon) || void 0 === e ? void 0 : e.action)
    }

    getChipNodePadding() {
        return this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL ? this.theme.chipNode.smallPadding : this.theme.chipNode.normalPadding
    }

    getChipNodeRadius() {
        var e;
        return null !== (e = this.chipNodeRadius) && void 0 !== e ? e : this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL ? this.theme.chipNode.smallBorderRadius : this.theme.chipNode.normalBorderRadius
    }

    getChipNodeBackGroundColor() {
        var e;
        return null !== (e = this.chipNodeBackgroundColor) && void 0 !== e ? e : this.theme.chipNode.backgroundColor
    }

    getChipNodeHeight() {
        var e, i;
        if (this.isChipSizeEnum()) return this.chipSize === ChipSize.SMALL ? this.theme.chipNode.smallHeight : this.theme.chipNode.normalHeight;
        this.chipNodeSize = this.chipSize;
        return null !== (i = null === (e = this.chipNodeSize) || void 0 === e ? void 0 : e.height) && void 0 !== i ? i : this.theme.chipNode.normalHeight
    }

    getChipNodeOpacity() {
        return this.chipEnabled ? this.chipOpacity : this.theme.chipNode.opacity.disabled
    }

    handleTouch(e) {
        if (this.chipEnabled) {
            this.isPressed = e.type === TouchType.Down;
            this.isHover ? e.type === TouchType.Down ? Context.animateTo({ curve: Curve.Sharp, duration: 100 }, (() => {
                this.chipBlendColor = this.theme.chipNode.pressedBlendColor;
                this.chipOpacity = this.theme.chipNode.opacity.pressed
            })) : e.type === TouchType.Up && Context.animateTo({ curve: Curve.Sharp, duration: 100 }, (() => {
                this.chipBlendColor = this.theme.chipNode.hoverBlendColor;
                this.chipOpacity = this.theme.chipNode.opacity.hover
            })) : e.type === TouchType.Down ? Context.animateTo({ curve: Curve.Friction, duration: 350 }, (() => {
                this.chipBlendColor = this.theme.chipNode.pressedBlendColor;
                this.chipOpacity = this.theme.chipNode.opacity.pressed
            })) : e.type === TouchType.Up && Context.animateTo({ curve: Curve.Friction, duration: 350 }, (() => {
                this.chipBlendColor = Color.Transparent;
                this.chipOpacity = this.theme.chipNode.opacity.normal
            }))
        }
    }

    hoverAnimate(e) {
        if (this.chipEnabled) {
            this.isHover = e;
            Context.animateTo({ curve: Curve.Friction, duration: 250 }, (() => {
                if (e) {
                    this.chipBlendColor = this.theme.chipNode.hoverBlendColor;
                    this.chipOpacity = this.theme.chipNode.opacity.hover
                } else {
                    this.chipBlendColor = Color.Transparent;
                    this.chipOpacity = this.theme.chipNode.opacity.normal
                }
            }))
        }
    }

    deleteChipNodeAnimate() {
        Context.animateTo({ duration: 150, curve: Curve.Sharp }, (() => {
            this.chipOpacity = 0
        }));
        Context.animateTo({ duration: 150, curve: Curve.FastOutLinearIn, onFinish: () => {
            this.deleteChip = !0
        } }, (() => {
            this.chipScale = { x: .85, y: .85 }
        }))
    }

    getSuffixIconSrc() {
        var e;
        if (!(null === (e = this.suffixIcon) || void 0 === e ? void 0 : e.src) && this.allowClose) {
            this.useDefaultSuffixIcon = !0;
            return this.theme.suffixIcon.defaultDeleteIcon
        }
        return this.suffixIcon.src
    }

    getChipNodeWidth() {
        var e;
        if (!this.isChipSizeEnum()) {
            this.chipNodeSize = this.chipSize;
            return null === (e = this.chipNodeSize) || void 0 === e ? void 0 : e.width
        }
    }

    chipBuilder(e = null) {
        this.observeComponentCreation2(((e, i) => {
            Row.create();
            Row.justifyContent(FlexAlign.Center);
            Row.clip(!0);
            Row.padding(this.getChipNodePadding());
            Row.height(this.getChipNodeHeight());
            Row.width(this.getChipNodeWidth());
            Row.backgroundColor(this.getChipNodeBackGroundColor());
            Row.borderRadius(this.getChipNodeRadius());
            Row.enabled(this.chipEnabled);
            Row.scale(ObservedObject.GetRawObject(this.chipScale));
            Row.focusable(!0);
            Row.colorBlend(ObservedObject.GetRawObject(this.chipBlendColor));
            Row.opacity(this.getChipNodeOpacity());
            Row.onTouch((e => {
                this.handleTouch(e)
            }));
            Row.onHover((e => {
                this.hoverAnimate(e)
            }));
            Row.onKeyEvent((e => {
                e.type === KeyType.Down && e.keyCode === KeyCode.KEYCODE_FORWARD_DEL && this.deleteChipNodeAnimate()
            }))
        }), Row);
        this.observeComponentCreation2(((e, i) => {
            If.create();
            this.prefixIcon.src ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation2(((e, i) => {
                    Image.create(this.prefixIcon.src);
                    Image.opacity(this.getChipNodeOpacity());
                    Image.size(this.getPrefixIconSize());
                    Image.fillColor(this.getPrefixIconFilledColor());
                    Image.enabled(this.chipEnabled);
                    Image.objectFit(ImageFit.Cover);
                    Image.focusable(!1);
                    Image.flexShrink(0)
                }), Image)
            })) : this.ifElseBranchUpdateFunction(1, (() => {
            }))
        }), If);
        If.pop();
        this.observeComponentCreation2(((e, i) => {
            Text.create(this.label.text);
            Text.opacity(this.getChipNodeOpacity());
            Text.fontSize(this.getLabelFontSize());
            Text.fontColor(this.getLabelFontColor());
            Text.fontFamily(this.getLabelFontFamily());
            Text.margin(this.getLabelMargin());
            Text.enabled(this.chipEnabled);
            Text.maxLines(1);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.flexShrink(1);
            Text.focusable(!0)
        }), Text);
        Text.pop();
        this.observeComponentCreation2(((e, i) => {
            Image.create(this.getSuffixIconSrc());
            Image.opacity(this.getChipNodeOpacity());
            Image.size(this.getSuffixIconSize());
            Image.fillColor(this.getSuffixIconFilledColor());
            Image.enabled(this.chipEnabled);
            Image.focusable(this.getSuffixIconFocusable());
            Image.objectFit(ImageFit.Cover);
            Image.flexShrink(0);
            ViewStackProcessor.visualState("focused");
            Image.borderColor(this.theme.chipNode.focusOutlineColor);
            Image.borderWidth(this.getSuffixIconFocusable() ? this.theme.chipNode.borderWidth : 0);
            ViewStackProcessor.visualState("normal");
            Image.borderColor(Color.Transparent);
            Image.borderWidth(0);
            ViewStackProcessor.visualState();
            Image.onClick((() => {
                var e;
                if (this.chipEnabled) if (null === (e = this.suffixIcon) || void 0 === e ? void 0 : e.action) this.suffixIcon.action(); else if (this.allowClose && this.useDefaultSuffixIcon) {
                    this.onClose();
                    this.deleteChipNodeAnimate()
                } else ;
            }))
        }), Image);
        Row.pop()
    }

    initialRender() {
        this.observeComponentCreation2(((e, i) => {
            If.create();
            this.deleteChip ? this.ifElseBranchUpdateFunction(1, (() => {
            })) : this.ifElseBranchUpdateFunction(0, (() => {
                this.chipBuilder.bind(this)()
            }))
        }), If);
        If.pop()
    }

    rerender() {
        this.updateDirtyElements()
    }
}
export default {
    Chip, ChipSize
}
