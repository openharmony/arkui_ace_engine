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

export default async function customDialogBackgroundColorTest() {
  /*
 * CustomDialog弹窗 CustomDialogControllerOptions对象说明
 * 找到画面文本为CustomDialogBackgroundColorOpen的Button组件
 * 点击button1，弹出并找到text为CustomDialogBackgroundColor的customDialog1弹窗和画面文本为CustomDialogBackgroundColorClose的Button组件
 * 获取customDialog1的参数backgroundColor与期待值Color.Green比对
 * 点击button2退出弹窗
 * 点击button1，弹出并找到text为CustomDialogBackgroundColor的customDialog2弹窗
 * 获取customDialog2的参数backgroundColor与期待值0xffa500比对
 * 点击坐标(100,100)退出弹窗
 * 点击button1，弹出并找到text为CustomDialogBackgroundColor的customDialog3弹窗
 * 获取customDialog3的参数backgroundColor与期待值'#ffc0cb'比对
 * 点击坐标(100,100)退出弹窗
 * 点击button1，弹出并找到text为CustomDialogBackgroundColor的customDialog4弹窗
 * 获取customDialog4的参数backgroundColor与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
 * 点击坐标(100,100)退出弹窗
*/
  defineTest('customDialogBackgroundColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('customDialogBackgroundColorTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('CustomDialogBackgroundColorOpen').enabled(true))

    await button1.tap()
    let customDialog1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundColor1: string = await customDialog1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor1).$attrs.backgroundColor, Color.Green)
    await driver.tap(100, 100)

    await button1.tap()
    let customDialog2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundColor2: string = await customDialog2.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor2).$attrs.backgroundColor, 0xffa500)
    await driver.tap(100, 100)

    await button1.tap()
    let customDialog3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundColor3: string = await customDialog3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor3).$attrs.backgroundColor, '#ffc0cb')
    await driver.tap(100, 100)

    await button1.tap()
    let customDialog4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundColor4: string = await customDialog4.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor4).$attrs.backgroundColor, $r('sys.color.ohos_id_color_text_hyperlink'))
    await driver.tap(100, 100)
  }, 0)
}