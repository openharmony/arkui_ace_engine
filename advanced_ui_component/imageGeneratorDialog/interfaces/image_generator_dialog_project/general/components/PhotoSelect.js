/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

var __decorate = (this && this.__decorate) || function (v20, w20, x20, y20) {
    var z20 = arguments.length, a21 = z20 < 3 ? w20 : y20 === null ? y20 = Object.getOwnPropertyDescriptor(w20, x20) : y20, b21;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        a21 = Reflect.decorate(v20, w20, x20, y20);
    else
        for (var c21 = v20.length - 1; c21 >= 0; c21--)
            if (b21 = v20[c21])
                a21 = (z20 < 3 ? b21(a21) : z20 > 3 ? b21(w20, x20, a21) : b21(w20, x20)) || a21;
    return z20 > 3 && a21 && Object.defineProperty(w20, x20, a21), a21;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import photoAccessHelper from "@ohos.file.photoAccessHelper";
import { Constants } from '../common/CommonConstants';
import { FileUtils } from '../utils/FileUtils';
const tag = 'PhotoSelect';
export class PhotoSelect extends ViewV2 {
    constructor(p20, q20, r20, s20 = -1, t20, u20) {
        super(p20, s20, u20);
        this.initParam("imageInfoArr", (q20 && "imageInfoArr" in q20) ? q20.imageInfoArr : undefined);
        this.initParam("imageMatrixArr", (q20 && "imageMatrixArr" in q20) ? q20.imageMatrixArr : undefined);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(o20) {
        this.resetParam("imageInfoArr", (o20 && "imageInfoArr" in o20) ? o20.imageInfoArr : undefined);
        this.resetParam("imageMatrixArr", (o20 && "imageMatrixArr" in o20) ? o20.imageMatrixArr : undefined);
    }
    getSelectPhotoLength() {
        let m20 = 0;
        for (let n20 = 0; n20 < this.imageInfoArr.length; n20++) {
            if (!this.invalidImageInfo(n20)) {
                m20++;
            }
        }
        return m20;
    }
    openPhotoPicker() {
        if (this.getSelectPhotoLength() >= 4) {
            return;
        }
        let k20 = new photoAccessHelper.PhotoViewPicker();
        k20.select({
            MIMEType: photoAccessHelper.PhotoViewMIMETypes.IMAGE_TYPE,
            isOriginalSupported: true,
            maxSelectNumber: PhotoSelect.DEFAULT_COUNT - this.getSelectPhotoLength(),
            combinedMediaTypeFilter: ['image|*|image/jpeg,image/png,image/heic,image/bmp,image/webp']
        }).then((l20) => {
            this.handleSelectedUri(l20.photoUris);
        });
    }
    deleteImageInfo(j20) {
        if (j20 < 0 || j20 > PhotoSelect.DEFAULT_COUNT) {
            console.log(tag, `invalid index: ${j20}`);
            return;
        }
        this.imageInfoArr[j20].url = Constants.NOT_SELECTED_NAME;
        this.imageInfoArr[j20].image?.release();
        this.imageMatrixArr[j20] = [
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        ];
        this.resortImageList();
    }
    moveImageInfo(a20, b20) {
        if (a20 === b20) {
            return;
        }
        let c20 = [];
        for (let i20 = 0; i20 < this.imageInfoArr.length; i20++) {
            c20.push(this.imageInfoArr[a20].zIndex ?? 0);
        }
        if (a20 > b20) {
            let g20 = this.imageInfoArr[a20];
            this.imageInfoArr.splice(a20, 1);
            this.imageInfoArr.splice(b20, 0, g20);
            let h20 = this.imageMatrixArr[a20];
            this.imageMatrixArr.splice(a20, 1);
            this.imageMatrixArr.splice(b20, 0, h20);
        }
        else {
            let e20 = this.imageInfoArr[a20];
            this.imageInfoArr.splice(a20, 1);
            this.imageInfoArr.splice(b20 - 1, 0, e20);
            let f20 = this.imageMatrixArr[a20];
            this.imageMatrixArr.splice(a20, 1);
            this.imageMatrixArr.splice(b20 - 1, 0, f20);
        }
        this.resortImageList();
        for (let d20 = 0; d20 < c20.length; d20++) {
            this.imageInfoArr[d20].zIndex = c20[d20];
        }
    }
    resortImageList() {
        let w19 = [];
        let x19 = [];
        for (let z19 = 0; z19 < this.imageInfoArr.length; z19++) {
            if (!this.invalidImageInfo(z19)) {
                w19.push(this.imageInfoArr[z19]);
                x19.push(this.imageMatrixArr[z19]);
            }
            this.imageInfoArr[z19] = { image: undefined, url: Constants.NOT_SELECTED_NAME };
            this.imageMatrixArr[z19] = [
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            ];
        }
        for (let y19 = 0; y19 < w19.length; y19++) {
            this.imageInfoArr[y19] = w19[y19];
            this.imageMatrixArr[y19] = x19[y19];
        }
    }
    enablePhotoPicker(v19) {
        if (!this.invalidImageInfo(v19)) {
            return false;
        }
        if (v19 === 0) {
            return true;
        }
        return !this.invalidImageInfo(v19 - 1);
    }
    getMaxZIndex() {
        let t19 = 0;
        for (let u19 = 0; u19 < this.imageInfoArr.length; u19++) {
            if (!this.invalidImageInfo(u19)) {
                t19 = this.imageInfoArr[u19].zIndex ?? 0;
            }
            else {
                return t19;
            }
        }
        return t19;
    }
    handleSelectedUri(p19) {
        for (let q19 = 0, r19 = 0; q19 < this.imageInfoArr.length && r19 < p19.length; q19++, r19++) {
            if (!this.invalidImageInfo(q19)) {
                r19--;
                continue;
            }
            let s19 = FileUtils.createPixelMap(p19[r19]);
            if (s19 === undefined) {
                q19--;
                console.log(tag, 'parse selected uri error');
                return;
            }
            s19.zIndex = this.getMaxZIndex() + 1;
            this.imageInfoArr[q19] = s19;
        }
    }
    invalidImageInfo(o19) {
        if (o19 < 0 || o19 > PhotoSelect.DEFAULT_COUNT) {
            console.log(tag, `invalid index: ${o19}`);
            return true;
        }
        return this.imageInfoArr[o19].url === Constants.NOT_SELECTED_NAME;
    }
    previewImageInfo(e19, f19 = null) {
        this.observeComponentCreation2((g19, h19) => {
            If.create();
            if (!this.invalidImageInfo(e19)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m19, n19) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((k19, l19) => {
                        Stack.create();
                        Stack.alignContent(Alignment.Top);
                        Stack.width(56);
                        Stack.height(56);
                        Stack.borderRadius(12);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((i19, j19) => {
                        Image.create((this.imageInfoArr[e19]).image);
                        Image.syncLoad(true);
                        Image.draggable(false);
                        Image.borderRadius(12);
                        Image.clip(true);
                    }, Image);
                    Stack.pop();
                    Column.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    MyMagicCanvasSquaredBuilder(a18, b18 = null) {
        this.observeComponentCreation2((c18, d18) => {
            If.create();
            if (this.invalidImageInfo(a18)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c19, d19) => {
                        Stack.create();
                        Stack.onClick(() => {
                            if (!this.enablePhotoPicker(a18)) {
                                return;
                            }
                            this.openPhotoPicker();
                        });
                        Stack.height(56);
                        Stack.width(56);
                        Stack.borderRadius(12);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((a19, b19) => {
                        Column.create();
                        Column.backgroundColor({ "id": 125831008, "type": 10001, params: ['sys.color.comp_background_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Column.height(56);
                        Column.width(56);
                        Column.borderRadius(12);
                    }, Column);
                    Column.pop();
                    this.observeComponentCreation2((w18, x18) => {
                        If.create();
                        if (this.enablePhotoPicker(a18)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((y18, z18) => {
                                    SymbolGlyph.create({ "id": 125831481, "type": 40000, params: ['sys.symbol.plus'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    SymbolGlyph.height(24);
                                    SymbolGlyph.width(24);
                                    SymbolGlyph.fontSize(24);
                                    SymbolGlyph.position({ x: 16, y: 16 });
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.fontColor([{ "id": 125830993, "type": 10001, params: ['sys.color.icon_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    Stack.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((u18, v18) => {
                        Stack.create();
                        Stack.align(Alignment.Center);
                        Stack.alignContent(Alignment.Top);
                        Stack.height(56);
                        Stack.width(56);
                        Stack.borderRadius(12);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((s18, t18) => {
                        Column.create();
                        Column.backgroundColor({ "id": 125831008, "type": 10001, params: ['sys.color.comp_background_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Column.height(56);
                        Column.width(56);
                        Column.borderRadius(12);
                    }, Column);
                    Column.pop();
                    this.observeComponentCreation2((q18, r18) => {
                        Image.create((this.imageInfoArr[a18]).image);
                        Image.borderRadius(12);
                        Image.draggable(false);
                        Image.syncLoad(true);
                    }, Image);
                    this.observeComponentCreation2((o18, p18) => {
                        Row.create();
                        Row.width('100%');
                        Row.justifyContent(FlexAlign.End);
                    }, Row);
                    this.observeComponentCreation2((m18, n18) => {
                        Stack.create();
                    }, Stack);
                    this.observeComponentCreation2((k18, l18) => {
                        Column.create();
                        Column.borderRadius('50%');
                        Column.backgroundColor('#66000000');
                        Column.width(16);
                        Column.height(16);
                        Column.margin(4);
                    }, Column);
                    Column.pop();
                    this.observeComponentCreation2((i18, j18) => {
                        Image.create('xx');
                        Image.fillColor(Color.White);
                        Image.width(16);
                        Image.height(16);
                        Image.onClick(() => {
                            this.deleteImageInfo(a18);
                        });
                        Image.draggable(false);
                        Image.margin(4);
                        Image.borderRadius('50%');
                        Image.responseRegion({
                            x: -4,
                            y: -4,
                            width: 24,
                            height: 24
                        });
                    }, Image);
                    Stack.pop();
                    Row.pop();
                    this.observeComponentCreation2((g18, h18) => {
                        Row.create();
                        Row.linearGradient({
                            angle: 180,
                            colors: [['#00000000', 0], ['#11000000', 0.5], ['#66000000', 1]]
                        });
                        Row.height(56);
                        Row.width(56);
                        Row.hitTestBehavior(HitTestMode.Transparent);
                    }, Row);
                    this.observeComponentCreation2((e18, f18) => {
                        Text.create('图' + (a18 + 1));
                        Text.fontColor('#FFFFFF');
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontSize(12);
                        Text.position({ x: 4, y: 36 });
                        Text.width(48);
                        Text.height(16);
                        Text.textAlign(TextAlign.Center);
                        Text.textShadow({
                            offsetX: 0,
                            offsetY: -2,
                            radius: 8,
                            color: '#66000000',
                            type: ShadowType.COLOR
                        });
                    }, Text);
                    Text.pop();
                    Row.pop();
                    Stack.pop();
                });
            }
        }, If);
        If.pop();
    }
    initialRender() {
        this.observeComponentCreation2((y17, z17) => {
            Column.create();
            Column.width(56);
            Column.height(260);
            Column.margin({ bottom: 6 });
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((q17, r17) => {
            List.create();
            List.onItemDragStart((w17, x17) => {
                if (this.getSelectPhotoLength() <= 1) {
                    return;
                }
                if (this.invalidImageInfo(x17)) {
                    return;
                }
                return { builder: () => {
                        this.previewImageInfo.call(this, x17);
                    } };
            });
            List.onItemDrop((s17, t17, u17, v17) => {
                if (!v17 || u17 < 0 || u17 >= this.imageInfoArr.length) {
                    return;
                }
                this.moveImageInfo(t17, u17);
            });
            List.listDirection(Axis.Horizontal);
            List.width('100%');
            List.height('100%');
            List.alignListItem(ListItemAlign.Center);
            List.lanes(4, '12px');
        }, List);
        this.observeComponentCreation2((z16, a17) => {
            ForEach.create();
            const b17 = (e17, f17) => {
                const g17 = e17;
                {
                    const h17 = (o17, p17) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(o17);
                        ListItem.create(j17, true);
                        if (!p17) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const i17 = (m17, n17) => {
                        ListItem.create(j17, true);
                        ListItem.height(56);
                        ListItem.width(56);
                    };
                    const j17 = (k17, l17) => {
                        h17(k17, l17);
                        this.MyMagicCanvasSquaredBuilder.bind(this)(f17);
                        ListItem.pop();
                    };
                    this.observeComponentCreation2(i17, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(z16, this.imageInfoArr, b17, (c17, d17) => {
                return '' + d17 + (c17?.url ?? 'imageGeneration') + this.enablePhotoPicker(d17);
            }, true, true);
        }, ForEach);
        ForEach.pop();
        List.pop();
        Column.pop();
    }
    updateStateVars(y16) {
        if (y16 === undefined) {
            return;
        }
        if ("imageInfoArr" in y16) {
            this.updateParam("imageInfoArr", y16.imageInfoArr);
        }
        if ("imageMatrixArr" in y16) {
            this.updateParam("imageMatrixArr", y16.imageMatrixArr);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
PhotoSelect.DEFAULT_COUNT = 4;
__decorate([
    Param
], PhotoSelect.prototype, "imageInfoArr", void 0);
__decorate([
    Param
], PhotoSelect.prototype, "imageMatrixArr", void 0);
