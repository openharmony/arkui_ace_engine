/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

import extension from '@ohos.app.ability.ServiceExtensionAbility'
import window from '@ohos.window';
import display from '@ohos.display';
import bundle from '@ohos.bundle';
import deviceInfo from '@ohos.deviceInfo';

let TAG = "[PickerDialogService]"

export default class ServiceExtAbility extends extension {

    // device type
    private lineNums = 0

    onCreate(want) {
        globalThis.context = this.context
        globalThis.want = want
        // 创建时获得页面样8
        this.getShareStyle()
    }


    onRequest(want, startId) {
        console.log(TAG, "onRequest execute")
        // 每次startAbility拉起页面的时候, 都传递want
        globalThis.want = want
        // 每次调用startAbility时可以在这里创建窗口
        display.getDefaultDisplay().then(dis => {
            // 获取像素密度系数
            let density = dis.densityPixels
            let homeHeight = 48
            let dialogRect = {
                left: (dis.width - ((globalThis.style["shareWidth"]) * density)) / 2,
                top: (dis.height - ((globalThis.style["shareHeight"] + homeHeight) * density)),
                width: (globalThis.style["shareWidth"]) * density,
                height: (globalThis.style["shareHeight"]) * density
            }
            // 注意: 必须在getSupportSharingApps执行完毕之后才能去createWindow
            this.getSupportSharingApps().then(() => {
                console.log(TAG, "sharing apps received successfully")
                this.createWindow("picker Dialog:" + startId, window.WindowType.TYPE_DIALOG, dialogRect)
            })
        })
    }


    getShareStyle() {
        globalThis.style = {}
        if (deviceInfo.deviceType == "phone" || deviceInfo.deviceType == "default") {
            // 页面的默认类型是手机
            this.lineNums = 8
            globalThis.style["shareWidth"] = 360
            globalThis.style["shareHeight"] = 355
            globalThis.style["shareCardWidth"] = 336
            globalThis.style["shareCardHeight"] = 97
            globalThis.style["shareCardRadius"] = 16
            globalThis.style["shareContentMargin"] = { top: 16, right: 43.5, bottom: 6, left: 16 }
            globalThis.style["shareCardTextLeft"] = 12
            globalThis.style["shareCardTextTop"] = 6
            globalThis.style["shareBackTop"] = 0
            globalThis.style["shareCardTextWidth"] = 236
            globalThis.style["shareCardSubTop"] = 3
            globalThis.style["shareCardBtnLeft"] = 238
            globalThis.style["swiperHeight"] = 200
            globalThis.style["swiperSelectMarginTop"] = 8
        } else {
            // pad类型
            this.lineNums = 6
            globalThis.style["shareWidth"] = 519
            globalThis.style["shareHeight"] = 256
            globalThis.style["shareCardWidth"] = 495
            globalThis.style["shareCardHeight"] = 87
            globalThis.style["shareCardRadius"] = 24
            globalThis.style["shareContentMargin"] = { top: 16, right: 24, bottom: 8, left: 16 }
            globalThis.style["shareCardTextLeft"] = 16
            globalThis.style["shareCardTextTop"] = 3
            globalThis.style["shareBackTop"] = 6
            globalThis.style["shareCardTextWidth"] = 380
            globalThis.style["shareCardSubTop"] = 2
            globalThis.style["shareCardBtnLeft"] = 368
            globalThis.style["swiperHeight"] = 115
            globalThis.style["swiperSelectMarginTop"] = 16
        }
    }


    onDestroy() {
        console.log(TAG + "ServiceExtAbility onDestroy")
    }


    private async createWindow(name: string, windowType: number, rect) {
        console.log(TAG + "createWindow execute")
        try {
            // 创建window
            const win = await window.create(this.context, name, windowType)
            globalThis.extensionWin = win
            // 将弹窗绑定至拉起方
            await win.bindDialogTarget(globalThis.want.parameters["ohos.ability.params.token"].value, ()=> {
                // 应用销毁，分享服务也销毁
                this.context.terminateSelf()
            })
            await win.moveTo(rect.left, rect.top)
            await win.resetSize(rect.width, rect.height)
            await win.loadContent('pages/share')
            await win.setBackgroundColor("#00000000")
            await win.show()
            console.log(TAG + "window create successfully")
        } catch {
            console.info(TAG + "window create failed")
        }
    }


    private async getSupportSharingApps() {
        // 注意：每次获取应用时都清空一次shareHapList
        globalThis.shareHapList = []
        try {
            // 这里原文档出错，修改为将字段ability.want.params.INTENT作为want
            console.info(TAG, JSON.stringify(globalThis.want["parameters"]["ability.want.params.INTENT"]))
            const apps = await bundle.queryAbilityByWant(globalThis.want["parameters"]["ability.want.params.INTENT"], bundle.AbilityType.PAGE)
            let shareHap = []
            for (let i = 0; i < apps.length; i++) {
                let hap = {}
                hap['ability'] = apps[i].name
                hap['bundle'] = apps[i].bundleName
                const label = await bundle.getAbilityLabel(apps[i].bundleName, apps[i].name)
                const icon = await bundle.getAbilityIcon(apps[i].bundleName, apps[i].name)
                hap['name'] = label
                hap['icon'] = icon
                shareHap.push(hap)

                // 每一页最多App数
                if (i % this.lineNums == (this.lineNums - 1) || i == apps.length - 1) {
                    globalThis.shareHapList.push(shareHap)
                    shareHap = []
                }
            }
        } catch {
            console.log(TAG + "query support sharing apps failed")
        }
    }
};