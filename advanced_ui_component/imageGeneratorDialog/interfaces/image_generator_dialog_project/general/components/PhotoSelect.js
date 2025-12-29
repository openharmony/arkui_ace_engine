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

var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        r = Reflect.decorate(decorators, target, key, desc);
    else
        for (var i = decorators.length - 1; i >= 0; i--)
            if (d = decorators[i])
                r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import photoAccessHelper from "@ohos.file.photoAccessHelper";
import { Constants } from '../common/CommonConstants';
import { FileUtils } from '../utils/FileUtils';
const tag = 'PhotoSelect';
export class PhotoSelect extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("imageInfoArr", (params && "imageInfoArr" in params) ? params.imageInfoArr : undefined);
        this.initParam("imageMatrixArr", (params && "imageMatrixArr" in params) ? params.imageMatrixArr : undefined);
        this.setImgCounts = "setImgCounts" in params ? params.setImgCounts : () => { };
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("imageInfoArr", (params && "imageInfoArr" in params) ? params.imageInfoArr : undefined);
        this.resetParam("imageMatrixArr", (params && "imageMatrixArr" in params) ? params.imageMatrixArr : undefined);
        this.setImgCounts = "setImgCounts" in params ? params.setImgCounts : (count) => { };
    }
    getSelectPhotoLength() {
        let result = 0;
        for (let i = 0; i < this.imageInfoArr.length; i++) {
            if (!this.invalidImageInfo(i)) {
                result++;
            }
        }
        return result;
    }
    openPhotoPicker() {
        if (this.getSelectPhotoLength() >= 4) {
            return;
        }
        let photoPicker = new photoAccessHelper.PhotoViewPicker();
        photoPicker.select({
            MIMEType: photoAccessHelper.PhotoViewMIMETypes.IMAGE_TYPE,
            isOriginalSupported: true,
            maxSelectNumber: PhotoSelect.DEFAULT_COUNT - this.getSelectPhotoLength(),
            combinedMediaTypeFilter: ['image|*|image/jpeg,image/png,image/heic,image/bmp,image/webp']
        }).then((result) => {
            this.handleSelectedUri(result.photoUris);
        });
    }
    deleteImageInfo(index) {
        if (index < 0 || index > PhotoSelect.DEFAULT_COUNT) {
            console.log(tag, `invalid index: ${index}`);
            return;
        }
        this.imageInfoArr[index].url = Constants.NOT_SELECTED_NAME;
        this.imageInfoArr[index].image?.release();
        this.imageMatrixArr[index] = [
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        ];
        this.resortImageList();
    }
    moveImageInfo(start, end) {
        if (start === end) {
            return;
        }
        let zIndexArr = [];
        for (let i = 0; i < this.imageInfoArr.length; i++) {
            zIndexArr.push(this.imageInfoArr[start].zIndex ?? 0);
        }
        if (start > end) {
            let imageInfo = this.imageInfoArr[start];
            this.imageInfoArr.splice(start, 1);
            this.imageInfoArr.splice(end, 0, imageInfo);
            let matrixInfo = this.imageMatrixArr[start];
            this.imageMatrixArr.splice(start, 1);
            this.imageMatrixArr.splice(end, 0, matrixInfo);
        }
        else {
            let imageInfo = this.imageInfoArr[start];
            this.imageInfoArr.splice(start, 1);
            this.imageInfoArr.splice(end - 1, 0, imageInfo);
            let matrixInfo = this.imageMatrixArr[start];
            this.imageMatrixArr.splice(start, 1);
            this.imageMatrixArr.splice(end - 1, 0, matrixInfo);
        }
        this.resortImageList();
        for (let i = 0; i < zIndexArr.length; i++) {
            this.imageInfoArr[i].zIndex = zIndexArr[i];
        }
    }
    resortImageList() {
        let images = [];
        let matrixTmp = [];
        for (let i = 0; i < this.imageInfoArr.length; i++) {
            if (!this.invalidImageInfo(i)) {
                images.push(this.imageInfoArr[i]);
                matrixTmp.push(this.imageMatrixArr[i]);
            }
            this.imageInfoArr[i] = { image: undefined, url: Constants.NOT_SELECTED_NAME };
            this.imageMatrixArr[i] = [
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            ];
        }
        for (let i = 0; i < images.length; i++) {
            this.imageInfoArr[i] = images[i];
            this.imageMatrixArr[i] = matrixTmp[i];
        }
        if (this.setImgCounts) {
            this.setImgCounts(images.length);
        }
    }
    enablePhotoPicker(index) {
        if (!this.invalidImageInfo(index)) {
            return false;
        }
        if (index === 0) {
            return true;
        }
        return !this.invalidImageInfo(index - 1);
    }
    getMaxZIndex() {
        let maxZIndex = 0;
        for (let i = 0; i < this.imageInfoArr.length; i++) {
            if (!this.invalidImageInfo(i)) {
                maxZIndex = this.imageInfoArr[i].zIndex ?? 0;
            }
            else {
                return maxZIndex;
            }
        }
        return maxZIndex;
    }
    handleSelectedUri(selectedUris) {
        for (let i = 0, j = 0; i < this.imageInfoArr.length && j < selectedUris.length; i++, j++) {
            if (!this.invalidImageInfo(i)) {
                j--;
                continue;
            }
            let imageInfo = FileUtils.createPixelMap(selectedUris[j]);
            if (imageInfo === undefined) {
                i--;
                console.log(tag, 'parse selected uri error');
                return;
            }
            imageInfo.zIndex = this.getMaxZIndex() + 1;
            this.imageInfoArr[i] = imageInfo;
            if (this.setImgCounts) {
                this.setImgCounts(i + 1);
            }
        }
    }
    invalidImageInfo(index) {
        if (index < 0 || index > PhotoSelect.DEFAULT_COUNT) {
            console.log(tag, `invalid index: ${index}`);
            return true;
        }
        return this.imageInfoArr[index].url === Constants.NOT_SELECTED_NAME;
    }
    previewImageInfo(index, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (!this.invalidImageInfo(index)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.alignContent(Alignment.Top);
                        Stack.width(56);
                        Stack.height(56);
                        Stack.borderRadius(12);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create((this.imageInfoArr[index]).image);
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
    MyMagicCanvasSquaredBuilder(index, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.invalidImageInfo(index)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.onClick(() => {
                            if (!this.enablePhotoPicker(index)) {
                                return;
                            }
                            this.openPhotoPicker();
                        });
                        Stack.height(56);
                        Stack.width(56);
                        Stack.borderRadius(12);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.backgroundColor({ "id": 125831008, "type": 10001, params: ['sys.color.comp_background_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Column.height(56);
                        Column.width(56);
                        Column.borderRadius(12);
                    }, Column);
                    Column.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.enablePhotoPicker(index)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.align(Alignment.Center);
                        Stack.alignContent(Alignment.Top);
                        Stack.height(56);
                        Stack.width(56);
                        Stack.borderRadius(12);
                        Stack.clip(true);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.backgroundColor({ "id": 125831008, "type": 10001, params: ['sys.color.comp_background_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Column.height(56);
                        Column.width(56);
                        Column.borderRadius(12);
                    }, Column);
                    Column.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create((this.imageInfoArr[index]).image);
                        Image.borderRadius(12);
                        Image.draggable(false);
                        Image.syncLoad(true);
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.width('100%');
                        Row.justifyContent(FlexAlign.End);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.borderRadius('50%');
                        Column.backgroundColor('#66000000');
                        Column.width(16);
                        Column.height(16);
                        Column.margin(4);
                    }, Column);
                    Column.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create('xx');
                        Image.fillColor(Color.White);
                        Image.width(16);
                        Image.height(16);
                        Image.onClick(() => {
                            this.deleteImageInfo(index);
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
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.linearGradient({
                            angle: 180,
                            colors: [['#00000000', 0], ['#11000000', 0.5], ['#66000000', 1]]
                        });
                        Row.height(56);
                        Row.width(56);
                        Row.hitTestBehavior(HitTestMode.Transparent);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create('图' + (index + 1));
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width(56);
            Column.height(260);
            Column.margin({ bottom: 6 });
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            List.create();
            List.onItemDragStart((event, index) => {
                if (this.getSelectPhotoLength() <= 1) {
                    return;
                }
                if (this.invalidImageInfo(index)) {
                    return;
                }
                return { builder: () => {
                        this.previewImageInfo.call(this, index);
                    } };
            });
            List.onItemDrop((event, itemIndex, insertIndex, isSuccess) => {
                if (!isSuccess || insertIndex < 0 || insertIndex >= this.imageInfoArr.length) {
                    return;
                }
                this.moveImageInfo(itemIndex, insertIndex);
            });
            List.listDirection(Axis.Horizontal);
            List.width('100%');
            List.height('100%');
            List.alignListItem(ListItemAlign.Center);
            List.lanes(4, '12px');
        }, List);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, index) => {
                const item = _item;
                {
                    const itemCreation = (elmtId, isInitialRender) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
                        ListItem.create(deepRenderFunction, true);
                        if (!isInitialRender) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const itemCreation2 = (elmtId, isInitialRender) => {
                        ListItem.create(deepRenderFunction, true);
                        ListItem.height(56);
                        ListItem.width(56);
                    };
                    const deepRenderFunction = (elmtId, isInitialRender) => {
                        itemCreation(elmtId, isInitialRender);
                        this.MyMagicCanvasSquaredBuilder.bind(this)(index);
                        ListItem.pop();
                    };
                    this.observeComponentCreation2(itemCreation2, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(elmtId, this.imageInfoArr, forEachItemGenFunction, (item, index) => {
                return '' + index + (item?.url ?? 'imageGeneration') + this.enablePhotoPicker(index);
            }, true, true);
        }, ForEach);
        ForEach.pop();
        List.pop();
        Column.pop();
    }
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("imageInfoArr" in params) {
            this.updateParam("imageInfoArr", params.imageInfoArr);
        }
        if ("imageMatrixArr" in params) {
            this.updateParam("imageMatrixArr", params.imageMatrixArr);
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
__decorate([
    Event
], PhotoSelect.prototype, "setImgCounts", void 0);
