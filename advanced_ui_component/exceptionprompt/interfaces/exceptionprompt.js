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
!function(o){
    o[o.DEFAULT_MARGIN=0] = "DEFAULT_MARGIN";
    o[o.FIT_MARGIN=1] = "FIT_MARGIN"
}(MarginType || (MarginType = {}));

export class ExceptionPrompt extends ViewPU {
    constructor(o, e, t, i = -1, a = void 0) {
        super(o, t, i);
        "function" == typeof a && (this.paramsGenerator_ = a);
        this.__options = new SynchedPropertyObjectOneWayPU(e.options, this, "options");
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
        this.setInitiallyProvidedValue(e)
    }

    setInitiallyProvidedValue(o) {
        void 0 !== o.touchBackgroundColor && (this.touchBackgroundColor = o.touchBackgroundColor);
        void 0 !== o.onTipClick && (this.onTipClick = o.onTipClick);
        void 0 !== o.onActionTextClick && (this.onActionTextClick = o.onActionTextClick)
    }

    updateStateVars(o) {
        this.__options.reset(o.options)
    }

    purgeVariableDependenciesOnElmtId(o) {
        this.__options.purgeDependencyOnElmtId(o)
    }

    aboutToBeDeleted() {
        this.__options.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal()
    }

    get options() {
        return this.__options.get()
    }

    set options(o) {
        this.__options.set(o)
    }

    initialRender() {
        this.observeComponentCreation2(((o, e) => {
            Column.create();
            Column.width("100%");
            Column.position({ y: this.options.marginTop });
            Column.zIndex(9)
        }), Column);
        this.observeComponentCreation2(((o, e) => {
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
        this.observeComponentCreation2(((o, e) => {
            Column.create();
            Column.width("100%");
            Column.borderRadius(12);
            Column.backgroundColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_background"],
                bundleName: "",
                moduleName: ""
            })
        }), Column);
        this.observeComponentCreation2(((o, e) => {
            Column.create();
            Column.width("100%");
            Column.borderRadius(12);
            Column.backgroundColor("#fdd9d9");
            Column.zIndex(9)
        }), Column);
        this.observeComponentCreation2(((o, e) => {
            Column.create();
            Column.padding({
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
        }), Column);
        this.observeComponentCreation2(((o, e) => {
            Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center })
        }), Flex);
        this.observeComponentCreation2(((o, e) => {
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
        this.observeComponentCreation2(((o, e) => {
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
        this.observeComponentCreation2(((o, e) => {
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
        this.observeComponentCreation2(((o, e) => {
            If.create();
            this.options.actionText ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation2(((o, e) => {
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
                    Button.onTouch((o => {
                        if (o.type === TouchType.Down) {
                            this.touchBackgroundColor = {
                                id: -1,
                                type: 10001,
                                params: ["sys.color.ohos_id_color_click_effect"],
                                bundleName: "",
                                moduleName: ""
                            };
                            this.onActionTextClick()
                        } else o.type === TouchType.Up && (this.touchBackgroundColor = {
                            id: -1,
                            type: 10001,
                            params: ["sys.color.ohos_id_color_sub_background_transparent"],
                            bundleName: "",
                            moduleName: ""
                        })
                    }))
                }), Button);
                this.observeComponentCreation2(((o, e) => {
                    Row.create()
                }), Row);
                this.observeComponentCreation2(((o, e) => {
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
                this.observeComponentCreation2(((o, e) => {
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
        Flex.pop();
        Column.pop();
        Column.pop();
        Column.pop();
        Column.pop();
        Column.pop()
    }

    rerender() {
        this.updateDirtyElements()
    }
}

export default {
    MarginType,
    ExceptionPrompt
}