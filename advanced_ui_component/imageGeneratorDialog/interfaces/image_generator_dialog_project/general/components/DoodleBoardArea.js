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

var __decorate = (this && this.__decorate) || function (r8, s8, t8, u8) {
    var v8 = arguments.length, w8 = v8 < 3 ? s8 : u8 === null ? u8 = Object.getOwnPropertyDescriptor(s8, t8) : u8, x8;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        w8 = Reflect.decorate(r8, s8, t8, u8);
    else
        for (var y8 = r8.length - 1; y8 >= 0; y8--)
            if (x8 = r8[y8])
                w8 = (v8 < 3 ? x8(w8) : v8 > 3 ? x8(s8, t8, w8) : x8(s8, t8)) || w8;
    return v8 > 3 && w8 && Object.defineProperty(s8, t8, w8), w8;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import { Constants } from '../common/CommonConstants';
import { ImageOperate } from './ImageOperate';
export class DoodleBoardArea extends ViewV2 {
    constructor(l8, m8, n8, o8 = -1, p8, q8) {
        super(l8, o8, q8);
        this.initParam("imageInfoArr", (m8 && "imageInfoArr" in m8) ? m8.imageInfoArr : undefined);
        this.initParam("imageMatrixArr", (m8 && "imageMatrixArr" in m8) ? m8.imageMatrixArr : undefined);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(k8) {
        this.resetParam("imageInfoArr", (k8 && "imageInfoArr" in k8) ? k8.imageInfoArr : undefined);
        this.resetParam("imageMatrixArr", (k8 && "imageMatrixArr" in k8) ? k8.imageMatrixArr : undefined);
    }
    invalidImageInfo(j8) {
        if (j8 < 0 || j8 >= DoodleBoardArea.DEFAULT_COUNT) {
            return true;
        }
        return this.imageInfoArr[j8].url === Constants.NOT_SELECTED_NAME;
    }
    getImageAspectRito(b8) {
        let c8 = this.imageInfoArr[b8];
        if (c8.rect === undefined) {
            let h8 = c8.image?.getImageInfoSync().size.width;
            let i8 = c8.image?.getImageInfoSync().size.height;
            if (h8 !== undefined) {
                return h8 / i8;
            }
            return 1;
        }
        let d8 = this.imageInfoArr[b8].rect?.left;
        let e8 = this.imageInfoArr[b8].rect?.right;
        let f8 = this.imageInfoArr[b8].rect?.top;
        let g8 = this.imageInfoArr[b8].rect?.bottom;
        return (e8 - d8) / (g8 - f8);
    }
    getImageWidth(y7) {
        if (this.imageInfoArr[y7].rect === undefined) {
            return '100%';
        }
        let z7 = this.imageInfoArr[y7].rect?.left;
        let a8 = this.imageInfoArr[y7].rect?.right;
        return this.getUIContext().px2vp(a8 - z7);
    }
    setMatrix(w7, x7) {
        this.imageMatrixArr[w7] = x7;
    }
    ImageBuilder(j7, k7 = null) {
        this.observeComponentCreation2((l7, m7) => {
            If.create();
            if (this.imageInfoArr[j7].image) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u7, v7) => {
                        __Common__.create();
                        __Common__.position({ x: 0, y: 0 });
                        __Common__.zIndex(this.imageInfoArr[j7].zIndex ?? undefined);
                        __Common__.hitTestBehavior(HitTestMode.Transparent);
                    }, __Common__);
                    {
                        this.observeComponentCreation2((n7, o7) => {
                            if (o7) {
                                let q7 = new ImageOperate(this, {
                                    pixelMap: this.imageInfoArr[j7].image ?? ImageContent.EMPTY,
                                    imageAspectRito: this.getImageAspectRito(j7),
                                    preTransform: this.imageMatrixArr[j7],
                                    imageWidth: this.getImageWidth(j7),
                                    setMatrixCallback: (t7) => {
                                        this.setMatrix(j7, t7);
                                    }
                                }, undefined, n7, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/DoodleBoardArea.ets", line: 66, col: 7 });
                                ViewV2.create(q7);
                                let r7 = () => {
                                    return {
                                        pixelMap: this.imageInfoArr[j7].image ?? ImageContent.EMPTY,
                                        imageAspectRito: this.getImageAspectRito(j7),
                                        preTransform: this.imageMatrixArr[j7],
                                        imageWidth: this.getImageWidth(j7),
                                        setMatrixCallback: (s7) => {
                                            this.setMatrix(j7, s7);
                                        }
                                    };
                                };
                                q7.paramsGenerator_ = r7;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(n7, {
                                    pixelMap: this.imageInfoArr[j7].image ?? ImageContent.EMPTY,
                                    imageAspectRito: this.getImageAspectRito(j7),
                                    preTransform: this.imageMatrixArr[j7],
                                    imageWidth: this.getImageWidth(j7),
                                    setMatrixCallback: (p7) => {
                                        this.setMatrix(j7, p7);
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
        this.observeComponentCreation2((h7, i7) => {
            Stack.create();
            Stack.width(386);
            Stack.height(386);
            Stack.borderRadius(24);
            Stack.borderWidth(2);
            Stack.borderColor('#33000000');
        }, Stack);
        this.observeComponentCreation2((f7, g7) => {
            Stack.create();
            Stack.borderRadius(24);
            Stack.width('100%');
            Stack.height('100%');
        }, Stack);
        this.observeComponentCreation2((d7, e7) => {
            Image.create('xx');
            Image.scale({ x: 1.36, y: 1.36 });
            Image.width('100%');
            Image.height('100%');
            Image.draggable(false);
            Image.borderRadius(24);
            Image.hitTestBehavior(HitTestMode.Transparent);
        }, Image);
        this.observeComponentCreation2((b7, c7) => {
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
        this.observeComponentCreation2((z6, a7) => {
            Image.create('xx');
            Image.width('100%');
            Image.height('100%');
            Image.borderRadius(24);
            Image.padding(1);
            Image.draggable(false);
            Image.hitTestBehavior(HitTestMode.Transparent);
        }, Image);
        Stack.pop();
        this.observeComponentCreation2((x6, y6) => {
            Column.create();
            Column.width(386);
            Column.height(386);
            Column.borderRadius(24);
            Column.clip(true);
        }, Column);
        this.observeComponentCreation2((v6, w6) => {
            Stack.create();
        }, Stack);
        this.observeComponentCreation2((j6, k6) => {
            If.create();
            if (this.invalidImageInfo(0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t6, u6) => {
                        Stack.create();
                        Stack.alignContent(Alignment.Center);
                        Stack.width('100%');
                        Stack.height('100%');
                    }, Stack);
                    this.observeComponentCreation2((r6, s6) => {
                        Column.create();
                        Column.justifyContent(FlexAlign.Center);
                        Column.width('100%');
                        Column.height('100%');
                    }, Column);
                    this.observeComponentCreation2((p6, q6) => {
                        Image.create('xx');
                        Image.width(160);
                        Image.height(160);
                        Image.draggable(false);
                    }, Image);
                    this.observeComponentCreation2((n6, o6) => {
                        Row.create();
                        Row.linearGradient({
                            direction: GradientDirection.Left,
                            colors: [['#64DCFF', 0.0], ['#8999FF', 1]]
                        });
                        Row.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
                        Row.margin({ top: 8 });
                    }, Row);
                    this.observeComponentCreation2((l6, m6) => {
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
        this.observeComponentCreation2((b6, c6) => {
            ForEach.create();
            const d6 = (g6, h6) => {
                const i6 = g6;
                this.ImageBuilder.bind(this)(h6);
            };
            this.forEachUpdateFunction(b6, this.imageInfoArr, d6, (e6, f6) => '' + f6 + (e6?.url ?? 'imageGeneration'), true, true);
        }, ForEach);
        ForEach.pop();
        Stack.pop();
        Column.pop();
        Stack.pop();
    }
    updateStateVars(a6) {
        if (a6 === undefined) {
            return;
        }
        if ("imageInfoArr" in a6) {
            this.updateParam("imageInfoArr", a6.imageInfoArr);
        }
        if ("imageMatrixArr" in a6) {
            this.updateParam("imageMatrixArr", a6.imageMatrixArr);
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
