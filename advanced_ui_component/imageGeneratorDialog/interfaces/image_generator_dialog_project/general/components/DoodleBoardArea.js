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
import { Constants } from '../common/CommonConstants';
import { ImageOperate } from './ImageOperate';
export class DoodleBoardArea extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("imageInfoArr", (params && "imageInfoArr" in params) ? params.imageInfoArr : undefined);
        this.initParam("imageMatrixArr", (params && "imageMatrixArr" in params) ? params.imageMatrixArr : undefined);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("imageInfoArr", (params && "imageInfoArr" in params) ? params.imageInfoArr : undefined);
        this.resetParam("imageMatrixArr", (params && "imageMatrixArr" in params) ? params.imageMatrixArr : undefined);
    }
    invalidImageInfo(index) {
        if (index < 0 || index >= DoodleBoardArea.DEFAULT_COUNT) {
            return true;
        }
        return this.imageInfoArr[index].url === Constants.NOT_SELECTED_NAME;
    }
    getImageAspectRito(index) {
        let imageItem = this.imageInfoArr[index];
        if (imageItem.rect === undefined) {
            let ImageW = imageItem.image?.getImageInfoSync().size.width;
            let ImageH = imageItem.image?.getImageInfoSync().size.height;
            if (ImageW !== undefined) {
                return ImageW / ImageH;
            }
            return 1;
        }
        let left = this.imageInfoArr[index].rect?.left;
        let right = this.imageInfoArr[index].rect?.right;
        let top = this.imageInfoArr[index].rect?.top;
        let bottom = this.imageInfoArr[index].rect?.bottom;
        return (right - left) / (bottom - top);
    }
    getImageWidth(index) {
        if (this.imageInfoArr[index].rect === undefined) {
            return '100%';
        }
        let left = this.imageInfoArr[index].rect?.left;
        let right = this.imageInfoArr[index].rect?.right;
        return this.getUIContext().px2vp(right - left);
    }
    setMatrix(index, imageMatrixArr) {
        this.imageMatrixArr[index] = imageMatrixArr;
    }
    ImageBuilder(index, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.imageInfoArr[index].image) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        __Common__.create();
                        __Common__.position({ x: 0, y: 0 });
                        __Common__.zIndex(this.imageInfoArr[index].zIndex ?? undefined);
                        __Common__.hitTestBehavior(HitTestMode.Transparent);
                    }, __Common__);
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new ImageOperate(this, {
                                    pixelMap: this.imageInfoArr[index].image ?? ImageContent.EMPTY,
                                    imageAspectRito: this.getImageAspectRito(index),
                                    preTransform: this.imageMatrixArr[index],
                                    imageWidth: this.getImageWidth(index),
                                    setMatrixCallback: (imageMatrixArr) => {
                                        this.setMatrix(index, imageMatrixArr);
                                    }
                                }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/DoodleBoardArea.ets", line: 66, col: 7 });
                                ViewV2.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        pixelMap: this.imageInfoArr[index].image ?? ImageContent.EMPTY,
                                        imageAspectRito: this.getImageAspectRito(index),
                                        preTransform: this.imageMatrixArr[index],
                                        imageWidth: this.getImageWidth(index),
                                        setMatrixCallback: (imageMatrixArr) => {
                                            this.setMatrix(index, imageMatrixArr);
                                        }
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    pixelMap: this.imageInfoArr[index].image ?? ImageContent.EMPTY,
                                    imageAspectRito: this.getImageAspectRito(index),
                                    preTransform: this.imageMatrixArr[index],
                                    imageWidth: this.getImageWidth(index),
                                    setMatrixCallback: (imageMatrixArr) => {
                                        this.setMatrix(index, imageMatrixArr);
                                    }
                                });
                            }
                        }, { name: "ImageOperate" });
                    }
                    __Common__.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.width(386);
            Stack.height(386);
            Stack.borderRadius(24);
            Stack.borderWidth(2);
            Stack.borderColor('#33000000');
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.borderRadius(24);
            Stack.width('100%');
            Stack.height('100%');
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create('xx');
            Image.scale({ x: 1.36, y: 1.36 });
            Image.width('100%');
            Image.height('100%');
            Image.draggable(false);
            Image.borderRadius(24);
            Image.hitTestBehavior(HitTestMode.Transparent);
        }, Image);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width('100%');
            Column.height('100%');
            Column.draggable(false);
            Column.hitTestBehavior(HitTestMode.Transparent);
            Column.backgroundColor(Color.White);
            Column.blur(25);
            Column.borderRadius(24);
        }, Column);
        Column.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create('xx');
            Image.width('100%');
            Image.height('100%');
            Image.borderRadius(24);
            Image.padding(1);
            Image.draggable(false);
            Image.hitTestBehavior(HitTestMode.Transparent);
        }, Image);
        Stack.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width(386);
            Column.height(386);
            Column.borderRadius(24);
            Column.clip(true);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.invalidImageInfo(0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create();
                        Stack.alignContent(Alignment.Center);
                        Stack.width('100%');
                        Stack.height('100%');
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.justifyContent(FlexAlign.Center);
                        Column.width('100%');
                        Column.height('100%');
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create('xx');
                        Image.width(160);
                        Image.height(160);
                        Image.draggable(false);
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.linearGradient({
                            direction: GradientDirection.Left,
                            colors: [['#64DCFF', 0.0], ['#8999FF', 1]]
                        });
                        Row.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
                        Row.margin({ top: 8 });
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create("添加图片或涂鸦进行创作");
                        Text.blendMode(BlendMode.DST_IN, BlendApplyType.OFFSCREEN);
                        Text.fontFamily("HarmonyHeiTi");
                        Text.fontSize(16);
                        Text.fontWeight(500);
                        Text.lineHeight(19);
                        Text.textAlign(TextAlign.Center);
                    }, Text);
                    Text.pop();
                    Row.pop();
                    Column.pop();
                    Stack.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, index) => {
                const item = _item;
                this.ImageBuilder.bind(this)(index);
            };
            this.forEachUpdateFunction(elmtId, this.imageInfoArr, forEachItemGenFunction, (item, index) => '' + index + (item?.url ?? 'imageGeneration'), true, true);
        }, ForEach);
        ForEach.pop();
        Stack.pop();
        Column.pop();
        Stack.pop();
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
DoodleBoardArea.DEFAULT_COUNT = 4;
__decorate([
    Param
], DoodleBoardArea.prototype, "imageInfoArr", void 0);
__decorate([
    Param
], DoodleBoardArea.prototype, "imageMatrixArr", void 0);
