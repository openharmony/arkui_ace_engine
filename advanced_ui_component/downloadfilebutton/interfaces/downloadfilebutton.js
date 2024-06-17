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
(function (b2) {
    b2[b2["FULL_FILLED"] = 1] = "FULL_FILLED";
    b2[b2["LINES"] = 2] = "LINES";
})(DownloadIconStyle || (DownloadIconStyle = {}));

export var DownloadDescription;
(function (a2) {
    a2[a2["DOWNLOAD"] = 1] = "DOWNLOAD";
    a2[a2["DOWNLOAD_FILE"] = 2] = "DOWNLOAD_FILE";
    a2[a2["SAVE"] = 3] = "SAVE";
    a2[a2["SAVE_IMAGE"] = 4] = "SAVE_IMAGE";
    a2[a2["SAVE_FILE"] = 5] = "SAVE_FILE";
    a2[a2["DOWNLOAD_AND_SHARE"] = 6] = "DOWNLOAD_AND_SHARE";
    a2[a2["RECEIVE"] = 7] = "RECEIVE";
    a2[a2["CONTINUE_TO_RECEIVE"] = 8] = "CONTINUE_TO_RECEIVE";
})(DownloadDescription || (DownloadDescription = {}));

export var DownloadLayoutDirection;
(function (z1) {
    z1[z1["HORIZONTAL"] = 0] = "HORIZONTAL";
    z1[z1["VERTICAL"] = 1] = "VERTICAL";
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
    constructor(t1, u1, v1, w1 = -1, x1 = undefined, y1) {
        super(t1, v1, w1, y1);
        if (typeof x1 === "function") {
            this.paramsGenerator_ = x1;
        }
        this.__contentOptions = new ObservedPropertyObjectPU({
            icon: DownloadIconStyle.FULL_FILLED,
            text: DownloadDescription.DOWNLOAD
        }, this, "contentOptions");
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
        this.setInitiallyProvidedValue(u1);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(s1) {
        if (s1.contentOptions !== undefined) {
            this.contentOptions = s1.contentOptions;
        }
        if (s1.styleOptions !== undefined) {
            this.styleOptions = s1.styleOptions;
        }
    }

    updateStateVars(r1) {
    }

    purgeVariableDependenciesOnElmtId(q1) {
        this.__contentOptions.purgeDependencyOnElmtId(q1);
        this.__styleOptions.purgeDependencyOnElmtId(q1);
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

    set contentOptions(p1) {
        this.__contentOptions.set(p1);
    }

    get styleOptions() {
        return this.__styleOptions.get();
    }

    set styleOptions(o1) {
        this.__styleOptions.set(o1);
    }

    getTextContent(n1) {
        return downloadDescriptionResourceMap.get(n1);
    }

    downloadImage(j1 = null) {
        this.observeComponentCreation2((l1, m1) => {
            Image.create(this.contentOptions.icon === DownloadIconStyle.LINES ? {
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

    downloadText(f1 = null) {
        this.observeComponentCreation2((h1, i1) => {
            Text.create(!this.contentOptions.text || !this.getTextContent(this.contentOptions.text) ? {
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
        this.observeComponentCreation2((b, c) => {
            If.create();
            if (this.styleOptions.layoutDirection === DownloadLayoutDirection.HORIZONTAL) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d1, e1) => {
                        Row.create();
                    }, Row);
                    this.observeComponentCreation2((z, a1) => {
                        If.create();
                        if (this.contentOptions.icon) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.downloadImage.bind(this)();
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((v, w) => {
                        If.create();
                        if (this.contentOptions.text) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.downloadText.bind(this)();
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    Row.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((p, q) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((l, m) => {
                        If.create();
                        if (this.contentOptions.icon) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.downloadImage.bind(this)();
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((h, i) => {
                        If.create();
                        if (this.contentOptions.text) {
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
            }
        }, If);
        If.pop();
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