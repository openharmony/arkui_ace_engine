/*
 * Copyright (c) 2026-2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

var __decorate = (this && this.__decorate) || function (n90, o90, p90, q90) {
    var r90 = arguments.length,
        s90 = r90 < 3 ? o90 : q90 === null ? q90 = Object.getOwnPropertyDescriptor(o90, p90) : q90, t90;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function') {
        s90 = Reflect.decorate(n90, o90, p90, q90);
    } else {
        for (var u90 = n90.length - 1; u90 >= 0; u90--) {
            if (t90 = n90[u90]) {
                s90 = (r90 < 3 ? t90(s90) : r90 > 3 ? t90(o90, p90, s90) : t90(o90, p90)) || s90;
            }
        }
    }
    return r90 > 3 && s90 && Object.defineProperty(o90, p90, s90), s90;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const hilog = requireNapi('ohos.hilog');
const DEFAULT_MARGIN = 16;
const ITEM_SPACE = 4;
const MIN_SIZE = 24;
const MID_SIZE = 40;
const MAX_SIZE = 48;
const MAX_FONT_SIZE = 2;

export class SwipeRefresherV2 extends ViewV2 {
    constructor(h90, i90, j90, k90 = -1, l90, m90) {
        super(h90, k90, m90);
        this.initParam('content', (i90 && 'content' in i90) ? i90.content : '');
        this.initParam('isLoading', (i90 && 'isLoading' in i90) ? i90.isLoading : false);
        this.initParam('minFontSize', (i90 && 'minFontSize' in i90) ? i90.minFontSize : 1.75);
        this.initParam('maxFontSize', (i90 && 'maxFontSize' in i90) ? i90.maxFontSize : 2);
        this.maxAppFontScale = 1;
        this.isFollowingSystemFontScale = false;
        this.currentFontScale = 1;
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(g90) {
        this.resetParam('content', (g90 && 'content' in g90) ? g90.content : '');
        this.resetParam('isLoading', (g90 && 'isLoading' in g90) ? g90.isLoading : false);
        this.resetParam('minFontSize', (g90 && 'minFontSize' in g90) ? g90.minFontSize : 1.75);
        this.resetParam('maxFontSize', (g90 && 'maxFontSize' in g90) ? g90.maxFontSize : 2);
        this.maxAppFontScale = 1;
        this.isFollowingSystemFontScale = false;
        this.currentFontScale = 1;
    }

    aboutToAppear() {
        try {
            let f90 = this.getUIContext();
            this.isFollowingSystemFontScale = f90.isFollowingSystemFontScale();
            this.maxAppFontScale = f90.getMaxFontScale();
        } catch (c90) {
            let d90 = c90.code;
            let e90 = c90.message;
            hilog.error(0x3900, 'SwipeRefresherV2',
                `Failed to init fontsizescale info, cause, code: ${d90}, message: ${e90}`);
        }
        this.currentFontScale = this.updateFontScale();
    }

    updateFontScale() {
        try {
            let a90 = this.getUIContext();
            let b90 = a90.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(b90, this.maxAppFontScale);
        } catch (x89) {
            let y89 = x89.code;
            let z89 = x89.message;
            hilog.error(0x3900, 'SwipeRefresherV2', `Failed to update font scale, code: ${y89}, message: ${z89}`);
            return 1;
        }
    }

    initialRender() {
        this.observeComponentCreation2((v89, w89) => {
            Flex.create({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center });
        }, Flex);
        this.observeComponentCreation2((r89, s89) => {
            If.create();
            if (this.isLoading) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t89, u89) => {
                        LoadingProgress.create();
                        LoadingProgress.height(Math.min(this.currentFontScale, MAX_FONT_SIZE) === this.maxFontSize ?
                            MAX_SIZE :
                            (Math.min(this.currentFontScale, MAX_FONT_SIZE) === this.minFontSize ? MID_SIZE :
                                MIN_SIZE));
                        LoadingProgress.width(Math.min(this.currentFontScale, MAX_FONT_SIZE) === this.maxFontSize ?
                            MAX_SIZE :
                            (Math.min(this.currentFontScale, MAX_FONT_SIZE) === this.minFontSize ? MID_SIZE :
                                MIN_SIZE));
                        LoadingProgress.margin({
                            end: LengthMetrics.vp(ITEM_SPACE)
                        });
                    }, LoadingProgress);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((p89, q89) => {
            Text.create(this.content);
            Text.fontColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_text_secondary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body2'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.minFontScale(1);
            Text.maxFontScale(Math.min(this.currentFontScale, 2));
            Text.padding({
                top: DEFAULT_MARGIN,
                bottom: DEFAULT_MARGIN
            });
        }, Text);
        Text.pop();
        Flex.pop();
    }

    updateStateVars(o89) {
        if (o89 === undefined) {
            return;
        }
        if ('content' in o89) {
            this.updateParam('content', o89.content);
        }
        if ('isLoading' in o89) {
            this.updateParam('isLoading', o89.isLoading);
        }
        if ('minFontSize' in o89) {
            this.updateParam('minFontSize', o89.minFontSize);
        }
        if ('maxFontSize' in o89) {
            this.updateParam('maxFontSize', o89.maxFontSize);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], SwipeRefresherV2.prototype, 'content', void 0);
__decorate([
    Param
], SwipeRefresherV2.prototype, 'isLoading', void 0);
__decorate([
    Param
], SwipeRefresherV2.prototype, 'minFontSize', void 0);
__decorate([
    Param
], SwipeRefresherV2.prototype, 'maxFontSize', void 0);
__decorate([
    Local
], SwipeRefresherV2.prototype, 'maxAppFontScale', void 0);
__decorate([
    Local
], SwipeRefresherV2.prototype, 'isFollowingSystemFontScale', void 0);
__decorate([
    Local
], SwipeRefresherV2.prototype, 'currentFontScale', void 0);

export default { SwipeRefresherV2 };