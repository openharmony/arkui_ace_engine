/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => {
    });
}

export var DownloadIconStyle;
(function (p2) {
    p2[p2["FULL_FILLED"] = 0] = "FULL_FILLED";
    p2[p2["LINES"] = 1] = "LINES";
})(DownloadIconStyle || (DownloadIconStyle = {}));

export var DownloadDescription;
(function (o2) {
    o2[o2["DOWNLOAD"] = 0] = "DOWNLOAD";
    o2[o2["DOWNLOAD_FILE"] = 1] = "DOWNLOAD_FILE";
    o2[o2["SAVE"] = 2] = "SAVE";
    o2[o2["SAVE_IMAGE"] = 3] = "SAVE_IMAGE";
    o2[o2["SAVE_FILE"] = 4] = "SAVE_FILE";
    o2[o2["DOWNLOAD_AND_SHARE"] = 5] = "DOWNLOAD_AND_SHARE";
    o2[o2["RECEIVE"] = 6] = "RECEIVE";
    o2[o2["CONTINUE_TO_RECEIVE"] = 7] = "CONTINUE_TO_RECEIVE";
})(DownloadDescription || (DownloadDescription = {}));

export var DownloadLayoutDirection;
(function (n2) {
    n2[n2["HORIZONTAL"] = 0] = "HORIZONTAL";
    n2[n2["VERTICAL"] = 1] = "VERTICAL";
})(DownloadLayoutDirection || (DownloadLayoutDirection = {}));
const downloadDescriptionResourceMap = new Map([
    [DownloadDescription.DOWNLOAD, {
        "id": -1,
        "type": 10003,
        params: ['sys.string.ohos_id_text_save_button_description_download'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    }],
    [DownloadDescription.DOWNLOAD_FILE, {
        "id": -1,
        "type": 10003,
        params: ['sys.string.ohos_id_text_save_button_description_download_file'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    }],
    [DownloadDescription.SAVE, {
        "id": -1,
        "type": 10003,
        params: ['sys.string.ohos_id_text_save_button_description_save'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    }],
    [DownloadDescription.SAVE_IMAGE, {
        "id": -1,
        "type": 10003,
        params: ['sys.string.ohos_id_text_save_button_description_save_image'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    }],
    [DownloadDescription.SAVE_FILE, {
        "id": -1,
        "type": 10003,
        params: ['sys.string.ohos_id_text_save_button_description_save_file'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    }],
    [DownloadDescription.DOWNLOAD_AND_SHARE, {
        "id": -1,
        "type": 10003,
        params: ['sys.string.ohos_id_text_save_button_description_download_and_share'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    }],
    [DownloadDescription.RECEIVE, {
        "id": -1,
        "type": 10003,
        params: ['sys.string.ohos_id_text_save_button_description_receive'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    }],
    [DownloadDescription.CONTINUE_TO_RECEIVE, {
        "id": -1,
        "type": 10003,
        params: ['sys.string.ohos_id_text_save_button_description_continue_to_receive'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
    }]
]);
const MARGIN_DEFAULT = '0vp';

export class DownloadFileButton extends ViewPU {
    constructor(h2, i2, j2, k2 = -1, l2 = undefined, m2) {
        super(h2, j2, k2, m2);
        if (typeof l2 === "function") {
            this.paramsGenerator_ = l2;
        }
        this.__contentOptions = new ObservedPropertyObjectPU({}, this, "contentOptions");
        this.__styleOptions = new ObservedPropertyObjectPU({
            iconSize: '16vp',
            layoutDirection: DownloadLayoutDirection.HORIZONTAL,
            fontSize: '16fp',
            fontStyle: FontStyle.Normal,
            fontWeight: FontWeight.Medium,
            fontFamily: 'HarmonyOS Sans',
            fontColor: '#ffffffff',
            iconColor: '#ffffffff',
            textIconSpace: '4vp'
        }, this, "styleOptions");
        this.setInitiallyProvidedValue(i2);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(g2) {
        if (g2.contentOptions !== undefined) {
            this.contentOptions = g2.contentOptions;
        }
        if (g2.styleOptions !== undefined) {
            this.styleOptions = g2.styleOptions;
        }
    }

    updateStateVars(f2) {
    }

    purgeVariableDependenciesOnElmtId(e2) {
        this.__contentOptions.purgeDependencyOnElmtId(e2);
        this.__styleOptions.purgeDependencyOnElmtId(e2);
    }

    aboutToBeDeleted() {
        this.__contentOptions.aboutToBeDeleted();
        this.__styleOptions.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get contentOptions() {
        return this.__contentOptions.get();
    }

    set contentOptions(d2) {
        this.__contentOptions.set(d2);
    }

    get styleOptions() {
        return this.__styleOptions.get();
    }

    set styleOptions(c2) {
        this.__styleOptions.set(c2);
    }

    getTextContent(b2) {
        return downloadDescriptionResourceMap.get(b2);
    }

    downloadImage(x1 = null) {
        this.observeComponentCreation2((z1, a2) => {
            Image.create(this.contentOptions.icon === DownloadIconStyle.LINES
                ? {
                    "id": -1,
                    "type": 20000,
                    params: ['sys.media.ohos_save_button_line'],
                    "bundleName": "__harDefaultBundleName__",
                    "moduleName": "__harDefaultModuleName__"
                } : {
                    "id": -1,
                    "type": 20000,
                    params: ['sys.media.ohos_save_button_filled'],
                    "bundleName": "__harDefaultBundleName__",
                    "moduleName": "__harDefaultModuleName__"
                });
            Image.size({ width: this.styleOptions.iconSize, height: this.styleOptions.iconSize });
            Image.fillColor(this.styleOptions.iconColor);
        }, Image);
    }

    downloadText(t1 = null) {
        this.observeComponentCreation2((v1, w1) => {
            Text.create(!this.contentOptions.text || !downloadDescriptionResourceMap.get(this.contentOptions.text) ? {
                "id": -1,
                "type": 10003,
                params: ['sys.string.ohos_id_text_save_button_description_download'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
            } :
            this.getTextContent(this.contentOptions.text));
            Text.fontSize(this.styleOptions.fontSize);
            Text.fontColor(this.styleOptions.fontColor);
            Text.fontStyle(this.styleOptions.fontStyle);
            Text.fontWeight(this.styleOptions.fontWeight);
            Text.fontFamily(this.styleOptions.fontFamily);
            Text.margin({
                top: this.styleOptions.layoutDirection === DownloadLayoutDirection.VERTICAL ?
                this.styleOptions.textIconSpace :
                    MARGIN_DEFAULT,
                left: this.styleOptions.layoutDirection === DownloadLayoutDirection.HORIZONTAL ?
                this.styleOptions.textIconSpace :
                    MARGIN_DEFAULT
            });
        }, Text);
        Text.pop();
    }

    initialRender() {
        this.observeComponentCreation2((r1, s1) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((c, d) => {
            If.create();
            if (this.contentOptions.text === undefined && this.contentOptions.icon === undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((k1, l1) => {
                        If.create();
                        if (this.styleOptions.layoutDirection === DownloadLayoutDirection.HORIZONTAL) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.downloadImage.bind(this)();
                                this.downloadText.bind(this)();
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((o1, p1) => {
                                    Column.create();
                                }, Column);
                                this.downloadImage.bind(this)();
                                this.downloadText.bind(this)();
                                Column.pop();
                            });
                        }
                    }, If);
                    If.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((g, h) => {
                        If.create();
                        if (this.styleOptions.layoutDirection === DownloadLayoutDirection.HORIZONTAL) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((e1, f1) => {
                                    If.create();
                                    if (this.contentOptions.icon !== undefined) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.downloadImage.bind(this)();
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                        });
                                    }
                                }, If);
                                If.pop();
                                this.observeComponentCreation2((a1, b1) => {
                                    If.create();
                                    if (this.contentOptions.text !== undefined) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.downloadText.bind(this)();
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                        });
                                    }
                                }, If);
                                If.pop();
                            });
                        } else if (this.styleOptions.layoutDirection === DownloadLayoutDirection.VERTICAL) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((v, w) => {
                                    Column.create();
                                }, Column);
                                this.observeComponentCreation2((r, s) => {
                                    If.create();
                                    if (this.contentOptions.icon !== undefined) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.downloadImage.bind(this)();
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                        });
                                    }
                                }, If);
                                If.pop();
                                this.observeComponentCreation2((n, o) => {
                                    If.create();
                                    if (this.contentOptions.text !== undefined) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.downloadText.bind(this)();
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                        });
                                    }
                                }, If);
                                If.pop();
                                Column.pop();
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(2, () => {
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
        }, If);
        If.pop();
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default {
    DownloadIconStyle,
    DownloadDescription,
    DownloadLayoutDirection,
    DownloadFileButton
}