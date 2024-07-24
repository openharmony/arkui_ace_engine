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
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

/*
* CustomDialog弹窗 CustomDialogControllerOptions对象说明
* 找到画面文本为CustomDialogCornerRadiusOpen的Button组件
* 点击button1,弹出并找到画面文本为CustomDialogCornerRadius的customDialog1弹窗
* 获取customDialog1的参数cornerRadius.topLeft与期待值30比对
* 获取customDialog1的参数cornerRadius.topRight与期待值30比对
* 获取customDialog1的参数cornerRadius.bottomLeft与期待值30比对
* 获取customDialog1的参数cornerRadius.bottomRight与期待值30比对
* 点击坐标(100,100)退出弹窗
* 点击button1,弹出并找到text文本为CustomDialogCornerRadius的customDialog2弹窗
* 获取customDialog2的参数cornerRadius.topLeft与期待值'30px'比对
* 获取customDialog2的参数cornerRadius.topRight与期待值'30px'比对
* 获取customDialog2的参数cornerRadius.bottomLeft与期待值'30px'比对
* 获取customDialog2的参数cornerRadius.bottomRight与期待值'30px'比对
* 点击坐标(100,100)退出弹窗
* 点击button1,弹出并找到text文本为CustomDialogCornerRadius的customDialog3弹窗
* 获取customDialog3的参数cornerRadius.topLeft与期待值$r('app.string.custom_dialog_length')比对
* 获取customDialog3的参数cornerRadius.topRight与期待值$r('app.string.custom_dialog_length')比对
* 获取customDialog3的参数cornerRadius.bottomLeft与期待值$r('app.string.custom_dialog_length')比对
* 获取customDialog3的参数cornerRadius.bottomRight与期待值$r('app.string.custom_dialog_length')比对
* 点击坐标(100,100)退出弹窗
* 点击button1,弹出并找到text文本为CustomDialogCornerRadius的customDialog4弹窗
* 获取customDialog4的参数cornerRadius与期待值'10px'比对
* 点击坐标(100,100)退出弹窗
* 点击button1,弹出并找到text文本为CustomDialogCornerRadius的customDialog5弹窗
* 获取customDialog5的参数cornerRadius与期待值'10vp'比对
* 点击坐标(100,100)退出弹窗
* 点击button1,弹出并找到text文本为CustomDialogCornerRadius的customDialog6弹窗
* 获取customDialog6的参数cornerRadius与期待值'10fp'比对
* 点击坐标(100,100)退出弹窗
* 点击button1,弹出并找到text文本为CustomDialogCornerRadius的customDialog7弹窗
* 获取customDialog7的参数cornerRadius与期待值'10lpx'比对
* 点击坐标(100,100)退出弹窗
* 点击button1,弹出并找到text文本为CustomDialogCornerRadius的customDialog8弹窗
* 获取customDialog8的参数cornerRadius与期待值'10%'比对
* 点击坐标(100,100)退出弹窗
* 点击button1,弹出并找到text文本为CustomDialogCornerRadius的customDialog9弹窗
* 获取customDialog9的参数cornerRadius与期待值$r('app.string.custom_dialog_length')比对
* 点击坐标(100,100)退出弹窗
*/
export default async function customDialogCornerRadiusTest() {
  defineTest('customDialogCornerRadiusTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('customDialogCornerRadiusTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('CustomDialogCornerRadiusOpen').enabled(true))

    await button1.tap()
    let customDialog1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let cornerRadius1: string = await customDialog1.getInspectorInfo()
    assertFalse(JSON.parse(cornerRadius1).$attrs.cornerRadius == undefined)
    assertEqual(JSON.parse(cornerRadius1).$attrs.cornerRadius.topLeft, 30)
    assertEqual(JSON.parse(cornerRadius1).$attrs.cornerRadius.topRight, 30)
    assertEqual(JSON.parse(cornerRadius1).$attrs.cornerRadius.bottomLeft, 30)
    assertEqual(JSON.parse(cornerRadius1).$attrs.cornerRadius.bottomRight, 30)
    await driver.tap(100, 100)

    await button1.tap()
    let customDialog2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let cornerRadius2: string = await customDialog2.getInspectorInfo()
    assertEqual(JSON.parse(cornerRadius2).$attrs.cornerRadius.topLeft, '30px')
    assertEqual(JSON.parse(cornerRadius2).$attrs.cornerRadius.topRight, '30px')
    assertEqual(JSON.parse(cornerRadius2).$attrs.cornerRadius.bottomLeft, '30px')
    assertEqual(JSON.parse(cornerRadius2).$attrs.cornerRadius.bottomRight, '30px')
    await driver.tap(100, 100)

    await button1.tap()
    let customDialog3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let cornerRadius3: string = await customDialog3.getInspectorInfo()
    assertEqual(JSON.parse(cornerRadius3).$attrs.cornerRadius.topLeft, $r('app.string.custom_dialog_length'))
    assertEqual(JSON.parse(cornerRadius3).$attrs.cornerRadius.topRight, $r('app.string.custom_dialog_length'))
    assertEqual(JSON.parse(cornerRadius3).$attrs.cornerRadius.bottomLeft, $r('app.string.custom_dialog_length'))
    assertEqual(JSON.parse(cornerRadius3).$attrs.cornerRadius.bottomRight, $r('app.string.custom_dialog_length'))
    await driver.tap(100, 100)

    await button1.tap()
    let customDialog4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let cornerRadius4: string = await customDialog4.getInspectorInfo()
    assertEqual(JSON.parse(cornerRadius4).$attrs.cornerRadius, '10px')
    await driver.tap(100, 100)

    await button1.tap()
    let customDialog5: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let cornerRadius5: string = await customDialog5.getInspectorInfo()
    assertEqual(JSON.parse(cornerRadius5).$attrs.cornerRadius, '10vp')
    await driver.tap(100, 100)

    await button1.tap()
    let customDialog6: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let cornerRadius6: string = await customDialog6.getInspectorInfo()
    assertEqual(JSON.parse(cornerRadius6).$attrs.cornerRadius, '10fp')
    await driver.tap(100, 100)

    await button1.tap()
    let customDialog7: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let cornerRadius7: string = await customDialog7.getInspectorInfo()
    assertEqual(JSON.parse(cornerRadius7).$attrs.cornerRadius, '10lpx')
    await driver.tap(100, 100)

    await button1.tap()
    let customDialog8: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let cornerRadius8: string = await customDialog8.getInspectorInfo()
    assertEqual(JSON.parse(cornerRadius8).$attrs.cornerRadius, '10%')
    await driver.tap(100, 100)

    await button1.tap()
    let customDialog9: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let cornerRadius9: string = await customDialog9.getInspectorInfo()
    assertEqual(JSON.parse(cornerRadius9).$attrs.cornerRadius, $r('app.string.custom_dialog_length'))
    await driver.tap(100, 100)
  }, 0)
}