/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
const curves = requireNativeModule('ohos.curves');

const START_TIME = 250;
const END_TIME = 200;
const BORDER_RADIUS = 12;
const ZINDEX_NUM = 9;

export var MarginType;
!function(e){
    e[e.DEFAULT_MARGIN=0] = "DEFAULT_MARGIN";
    e[e.FIT_MARGIN=1] = "FIT_MARGIN"
}(MarginType || (MarginType = {}));

export class ExceptionPrompt extends ViewPU {
    constructor(e, o, t, i = -1, a = void 0) {
        super(e, t, i);
        "function" == typeof a && (this.paramsGenerator_ = a);
        this.__options = new SynchedPropertyObjectOneWayPU(o.options, this, "options");
        this.touchBackgroundColor = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_sub_background_transparent"],
            bundleName: "",
            moduleName: ""
        };
        this.onTipClick = () => {
        };
        this.onActionTextClick = () => {
        };
        this.setInitiallyProvidedValue(o)
    }

    setInitiallyProvidedValue(e) {
        void 0 !== e.touchBackgroundColor && (this.touchBackgroundColor = e.touchBackgroundColor);
        void 0 !== e.onTipClick && (this.onTipClick = e.onTipClick);
        void 0 !== e.onActionTextClick && (this.onActionTextClick = e.onActionTextClick)
    }

    updateStateVars(e) {
        this.__options.reset(e.options)
    }

    purgeVariableDependenciesOnElmtId(e) {
        this.__options.purgeDependencyOnElmtId(e)
    }

    aboutToBeDeleted() {
        this.__options.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal()
    }

    get options() {
        return this.__options.get()
    }

    set options(e) {
        this.__options.set(e)
    }

    TextBuilder(e = null) {
        this.observeComponentCreation2(((e, o) => {
            Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
            Flex.padding({
                left: {
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_notification_margin_start"],
                    bundleName: "",
                    moduleName: ""
                },
                right: {
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_text_paragraph_margin_s"],
                    bundleName: "",
                    moduleName: ""
                },
                top: {
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_default_padding_start"],
                    bundleName: "",
                    moduleName: ""
                },
                bottom: {
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_default_padding_end"],
                    bundleName: "",
                    moduleName: ""
                }
            })
        }), Flex);
        this.observeComponentCreation2(((e, o) => {
            Row.create();
            Row.padding({
                right: {
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_default_padding_end"],
                    bundleName: "",
                    moduleName: ""
                }
            });
            Row.width("100%");
            Row.onClick((() => {
                this.onTipClick()
            }))
        }), Row);
        this.observeComponentCreation2(((e, o) => {
            var t;
            Image.create(null !== (t = this.options.icon) && void 0 !== t ? t : {
                                                                                    id: -1,
                                                                                    type: 2e4,
                                                                                    params: ["sys.media.ohos_ic_public_fail"],
                                                                                    bundleName: "",
                                                                                    moduleName: ""
                                                                                });
            Image.width("24vp");
            Image.height("24vp");
            Image.fillColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_warning"],
                bundleName: "",
                moduleName: ""
            })
        }), Image);
        this.observeComponentCreation2(((e, o) => {
            Text.create(this.options.tip);
            Text.fontSize({
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_text_size_body1"],
                bundleName: "",
                moduleName: ""
            });
            Text.fontColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_warning"],
                bundleName: "",
                moduleName: ""
            });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.maxLines(2);
            Text.lineHeight(24);
            Text.margin({
                left: {
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_dialog_margin_end"],
                    bundleName: "",
                    moduleName: ""
                },
                right: {
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_dialog_margin_end"],
                    bundleName: "",
                    moduleName: ""
                }
            })
        }), Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2(((e, o) => {
            If.create();
            this.options.actionText ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation2(((e, o) => {
                    Button.createWithChild({ stateEffect: !0, type: ButtonType.Normal });
                    Button.backgroundColor(this.touchBackgroundColor);
                    Button.width(this.options.actionText ? 144 : 0);
                    Button.height(24);
                    Button.borderRadius({
                        id: -1,
                        type: 10002,
                        params: ["sys.float.ohos_id_corner_radius_subtab"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Button.padding({
                        right: {
                            id: -1,
                            type: 10002,
                            params: ["sys.float.ohos_id_elements_margin_vertical_l"],
                            bundleName: "",
                            moduleName: ""
                        },
                        left: {
                            id: -1,
                            type: 10002,
                            params: ["sys.float.ohos_id_elements_margin_vertical_l"],
                            bundleName: "",
                            moduleName: ""
                        }
                    });
                    Button.onTouch((e => {
                        if (e.type === TouchType.Down) {
                            this.touchBackgroundColor = {
                                id: -1,
                                type: 10001,
                                params: ["sys.color.ohos_id_color_click_effect"],
                                bundleName: "",
                                moduleName: ""
                            };
                            this.onActionTextClick()
                        } else e.type === TouchType.Up && (this.touchBackgroundColor = {
                            id: -1,
                            type: 10001,
                            params: ["sys.color.ohos_id_color_sub_background_transparent"],
                            bundleName: "",
                            moduleName: ""
                        })
                    }))
                }), Button);
                this.observeComponentCreation2(((e, o) => {
                    Row.create()
                }), Row);
                this.observeComponentCreation2(((e, o) => {
                    Text.create(this.options.actionText);
                    Text.fontSize({
                        id: -1,
                        type: 10002,
                        params: ["sys.float.ohos_id_text_size_body2"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Text.fontColor({
                        id: -1,
                        type: 10001,
                        params: ["sys.color.ohos_id_color_text_secondary"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Text.maxLines(1);
                    Text.padding(0);
                    Text.margin({
                        right: {
                            id: -1,
                            type: 10002,
                            params: ["sys.float.ohos_id_text_paragraph_margin_s"],
                            bundleName: "",
                            moduleName: ""
                        }
                    });
                    Text.textAlign(TextAlign.End)
                }), Text);
                Text.pop();
                this.observeComponentCreation2(((e, o) => {
                    Image.create({
                        id: -1,
                        type: 2e4,
                        params: ["sys.media.ohos_ic_public_arrow_right"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Image.width("12vp");
                    Image.height("24vp");
                    Image.fillColor({
                        id: -1,
                        type: 10001,
                        params: ["sys.color.ohos_id_color_tertiary"],
                        bundleName: "",
                        moduleName: ""
                    })
                }), Image);
                Row.pop();
                Button.pop()
            })) : this.ifElseBranchUpdateFunction(1, (() => {
            }))
        }), If);
        If.pop();
        Flex.pop()
    }

    initialRender() {
        this.observeComponentCreation2(((e, o) => {
            Row.create();
            Row.width("100%");
            Row.position({ y: this.options.marginTop });
            Row.zIndex(9)
        }), Row);
        this.observeComponentCreation2(((e, o) => {
            Column.create();
            Column.padding(this.options.marginType === MarginType.DEFAULT_MARGIN ? {
                                                                                       left: {
                                                                                           id: -1,
                                                                                           type: 10002,
                                                                                           params: ["sys.float.ohos_id_card_margin_start"],
                                                                                           bundleName: "",
                                                                                           moduleName: ""
                                                                                       },
                                                                                       right: {
                                                                                           id: -1,
                                                                                           type: 10002,
                                                                                           params: ["sys.float.ohos_id_card_margin_end"],
                                                                                           bundleName: "",
                                                                                           moduleName: ""
                                                                                       }
                                                                                   } : {
                                                                                           left: {
                                                                                               id: -1,
                                                                                               type: 10002,
                                                                                               params: ["sys.float.ohos_id_max_padding_start"],
                                                                                               bundleName: "",
                                                                                               moduleName: ""
                                                                                           },
                                                                                           right: {
                                                                                               id: -1,
                                                                                               type: 10002,
                                                                                               params: ["sys.float.ohos_id_max_padding_end"],
                                                                                               bundleName: "",
                                                                                               moduleName: ""
                                                                                           }
                                                                                       });
            Column.transition(TransitionEffect.OPACITY.animation({
                curve: curves.cubicBezierCurve(.33, 0, .67, 1),
                duration: this.options.isShown ? 250 : 200
            }));
            Column.visibility(this.options.isShown ? Visibility.Visible : Visibility.None)
        }), Column);
        this.observeComponentCreation2(((e, o) => {
            Column.create();
            Column.width("100%");
            Column.borderRadius(12);
            Column.backgroundColor("#fdd9d9");
            Column.zIndex(9)
        }), Column);
        this.TextBuilder.bind(this)();
        Column.pop();
        Column.pop();
        Row.pop()
    }

    rerender() {
        this.updateDirtyElements()
    }
}

export default {
    MarginType,
    ExceptionPrompt
}