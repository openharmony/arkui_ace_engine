/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import {
  assertEqual,
  assertFalse,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

/*
* CustomDialog弹窗 CustomDialogControllerOptions对象说明
* 找到画面文本为CustomDialogOffsetOpen的Button组件
* 点击button1弹出并找到画面文本为CustomDialogOffset的customDialog1弹窗
* 获取customDialog1的参数offset.dx与期待值0比对
* 获取customDialog1的参数offset.dy与期待值-25比对
* 点击坐标(100,100)退出弹窗
* 点击button1弹出并找到画面文本为CustomDialogOffset的customDialog2弹窗
* 获取customDialog2的参数offset.dx与期待值'15px'比对
* 获取customDialog2的参数offset.dy与期待值'15px'比对
* 点击坐标(100,100)退出弹窗
* 点击button1弹出并找到画面文本为CustomDialogOffset的customDialog3弹窗
* 获取customDialog3的参数offset.dx与期待值$r('app.string.custom_dialog_length')比对
* 获取customDialog3的参数offset.dy与期待值$r('app.string.custom_dialog_length')比对
* 点击坐标(100,100)退出弹窗
*/
export default async function customDialogOffsetTest() {
  defineTest('customDialogOffsetTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('customDialogOffsetTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('CustomDialogOffsetOpen').enabled(true))

    await button1.tap()
    let customDialog1: Component = await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let offset1: string = await customDialog1.getInspectorInfo()
    assertEqual(JSON.parse(offset1).$attrs.offset.dX, 0)
    assertEqual(JSON.parse(offset1).$attrs.offset.dY, -25)
    await driver.tap(100, 100)

    await button1.tap()
    let customDialog2: Component = await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let offset2: string = await customDialog2.getInspectorInfo()
    assertEqual(String(JSON.parse(offset2).$attrs.offset.dX), '15')
    assertEqual(String(JSON.parse(offset2).$attrs.offset.dY), '15')
    await driver.tap(100, 100)

    await button1.tap()
    let customDialog3: Component = await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let offset3: string = await customDialog3.getInspectorInfo()
    assertEqual(String(JSON.parse(offset3).$attrs.offset.dX), $r('app.string.custom_dialog_length'))
    assertEqual(String(JSON.parse(offset3).$attrs.offset.dY), $r('app.string.custom_dialog_length'))
  }, 0)
}