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
* 找到画面文本为CustomDialogMaskRectOpen的Button组件
* 点击button1弹出并找到画面文本为CustomDialogMaskRect的customDialog1弹窗
* 获取customDialog1的参数maskRect.x与期待值0比对
* 获取customDialog1的参数maskRect.y与期待值0比对
* 获取customDialog1的参数maskRect.width与期待值999比对
* 获取customDialog1的参数maskRect.height与期待值999比对
* 点击坐标(100,100)退出弹窗
* 点击button1弹出并找到画面文本为CustomDialogMaskRect的customDialog2弹窗
* 获取customDialog2的参数maskRect.x与期待值'0px'比对
* 获取customDialog2的参数maskRect.y与期待值'0px'比对
* 获取customDialog2的参数maskRect.width与期待值'80%'比对
* 获取customDialog2的参数maskRect.height与期待值'80%'比对
* 点击坐标(100,100)退出弹窗
* 点击button1弹出并找到画面文本为CustomDialogMaskRect的customDialog3弹窗
* 获取customDialog3的参数maskRect.x与期待值$r('app.string.custom_dialog_mask_rect_length')比对
* 获取customDialog3的参数maskRect.y与期待值$r('app.string.custom_dialog_mask_rect_length')比对
* 获取customDialog3的参数maskRect.width与期待值$r('app.string.custom_dialog_mask_rect_length')比对
* 获取customDialog3的参数maskRect.height与期待值$r('app.string.custom_dialog_mask_rect_length')比对
* 点击坐标(100,100)退出弹窗
* 点击button1弹出并找到画面文本为CustomDialogMaskRect的customDialog4弹窗
* 获取customDialog4的参数maskRect.x与期待值'0px'比对
* 获取customDialog4的参数maskRect.y与期待值'0px'比对
* 获取customDialog4的参数maskRect.width与期待值'80%'比对
* 获取customDialog4的参数maskRect.height与期待值'80%'比对
* 点击坐标(100,100)退出弹窗
*/
export default async function customDialogMaskRectTest() {
  defineTest('customDialogMaskRectTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('customDialogMaskRectTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('CustomDialogMaskRectOpen').enabled(true))

    await button1.tap()
    let customDialog1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let maskRect1: string = await customDialog1.getInspectorInfo()
    assertFalse(JSON.parse(maskRect1).$attrs.maskRect == null)
    assertEqual(JSON.parse(maskRect1).$attrs.maskRect.X, 0)
    assertEqual(JSON.parse(maskRect1).$attrs.maskRect.Y, 0)
    assertEqual(JSON.parse(maskRect1).$attrs.maskRect.width, 999)
    assertEqual(JSON.parse(maskRect1).$attrs.maskRect.height, 999)
    await driver.tap(100, 100)

    await button1.tap()
    let customDialog2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let maskRect2: string = await customDialog2.getInspectorInfo()
    assertEqual(JSON.parse(maskRect2).$attrs.maskRect.X, '0px')
    assertEqual(JSON.parse(maskRect2).$attrs.maskRect.Y, '0px')
    assertEqual(JSON.parse(maskRect2).$attrs.maskRect.width, '80%')
    assertEqual(JSON.parse(maskRect2).$attrs.maskRect.height, '80%')
    await driver.tap(100, 100)

    await button1.tap()
    let customDialog3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let maskRect3: string = await customDialog3.getInspectorInfo()
    assertEqual(JSON.parse(maskRect3).$attrs.maskRect.X, $r('app.string.custom_dialog_mask_rect_length'))
    assertEqual(JSON.parse(maskRect3).$attrs.maskRect.Y, $r('app.string.custom_dialog_mask_rect_length'))
    assertEqual(JSON.parse(maskRect3).$attrs.maskRect.width, $r('app.string.custom_dialog_mask_rect_length'))
    assertEqual(JSON.parse(maskRect3).$attrs.maskRect.height, $r('app.string.custom_dialog_mask_rect_length'))
    await driver.tap(100, 100)

    await button1.tap()
    let customDialog4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let maskRect4: string = await customDialog4.getInspectorInfo()
    assertEqual(JSON.parse(maskRect4).$attrs.maskRect.X, '0px')
    assertEqual(JSON.parse(maskRect4).$attrs.maskRect.Y, '0px')
    assertEqual(JSON.parse(maskRect4).$attrs.maskRect.width, '80%')
    assertEqual(JSON.parse(maskRect4).$attrs.maskRect.height, '80%')
  }, 0)
}