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
* 找到画面文本为CustomDialogMaskColorOpen的Button组件
* 点击button1弹出并找到画面文本为CustomDialogMaskColor的customDialog1弹窗
* 获取customDialog1的参数maskColor与期待值Color.Pink比对
* 点击坐标(100,100)退出弹窗
* 点击button1弹出并找到画面文本为CustomDialogMaskColor的customDialog2弹窗
* 获取customDialog2的参数maskColor与期待值0xffa500比对
* 点击坐标(100,100)退出弹窗
* 点击button1弹出并找到画面文本为CustomDialogMaskColor的customDialog3弹窗
* 获取customDialog3的参数maskColor与期待值'#ffff00'比对
* 点击坐标(100,100)退出弹窗
* 点击button1弹出并找到画面文本为CustomDialogMaskColor的customDialog4弹窗
* 获取customDialog4的参数maskColor与期待值$r('sys.color.jiohos_id_color_text_hyperlink')比对
* 点击坐标(100,100)退出弹窗
*/
export default async function customDialogMaskColorTest() {
  defineTest('customDialogMaskColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('customDialogMaskColorTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('CustomDialogMaskColorOpen').enabled(true))

    await button1.tap()
    let customDialog1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let maskColor1: string = await customDialog1.getInspectorInfo()
    assertFalse(JSON.parse(maskColor1).$attrs.maskColor == undefined)
    assertEqual(JSON.parse(maskColor1).$attrs.maskColor, Color.Pink)
    await driver.tap(100, 100)

    await button1.tap()
    let customDialog2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let maskColor2: string = await customDialog2.getInspectorInfo()
    assertEqual(JSON.parse(maskColor2).$attrs.maskColor, 0xffa500)
    await driver.tap(100, 100)

    await button1.tap()
    let customDialog3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let maskColor3: string = await customDialog3.getInspectorInfo()
    assertEqual(JSON.parse(maskColor3).$attrs.maskColor, '#ffff00')
    await driver.tap(100, 100)

    await button1.tap()
    let customDialog4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let maskColor4: string = await customDialog4.getInspectorInfo()
    assertEqual(JSON.parse(maskColor4).$attrs.maskColor, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}