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
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

/*
* CustomDialog弹窗 CustomDialogControllerOptions对象说明
* 找到画面文本为CustomDialogShowInSubWindowOpen和CustomDialogShowInSubWindow的Button组件
* 点击button1弹出并找到画面文本为CustomDialogShowInSubWindow的customDialog1弹窗
* 获取customDialog1的参数showInSubWindow与期待值false比对
* 点击坐标(100,100)退出弹窗
* 点击button2改变customDialog1弹窗参数showInSubWindow为true
* 点击button1弹出并找到画面文本为CustomDialogIsModal的customDialog2弹窗
* 获取customDialog2的参数showInSubWindow与期待值true比对
* 点击坐标(100,100)退出弹窗
*/
export default async function customDialogShowInSubWindowTest() {
  defineTest('customDialogShowInSubWindowTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('customDialogShowInSubWindowTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('CustomDialogShowInSubWindowOpen').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('CustomDialogShowInSubWindow').enabled(true))

    await button1.tap()
    let customDialog1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let showInSubWindow1: string = await customDialog1.getInspectorInfo()
    assertFalse(JSON.parse(showInSubWindow1).$attrs.showInSubWindow)
    await driver.tap(100, 100)

    await button2.tap()
    await button1.tap()
    let customDialog2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let showInSubWindow2: string = await customDialog2.getInspectorInfo()
    assertTrue(JSON.parse(showInSubWindow2).$attrs.showInSubWindow)
  }, 0)
}