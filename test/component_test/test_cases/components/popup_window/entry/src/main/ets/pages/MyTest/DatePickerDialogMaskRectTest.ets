/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import {
  assertEqual,
  assertFalse,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function datePickerDialogMaskRectTest() {
  /*
   * DatePickerDialog组件 MaskRect对象
   * 找到画面text为DatePickerDialogMaskRect1，DatePickerDialogMaskRect2的Button组件
   * 点击button1，弹出弹窗
   * 获取datePickerDialogMaskRect1的MaskRect对象与期待值{ x: 50, y: 50, width: 450, height: 100 }对比
   * 点击坐标(1, 1)，退出弹窗
   * 获取datePickerDialogMaskRect2的MaskRect对象与期待值{ x: '510px', y: '510px', width: '600px', height: '600px' }对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogMaskRect3的MaskRect对象为{ x: $r('app.string.mask_rect'), y: $r('app.string.mask_rect'),
                 width: $r('app.string.mask_rect'), height: $r('app.string.mask_rect') }
   * 点击button1，弹出弹窗
   * 获取datePickerDialogMaskRect3的MaskRect对象与期待值{ x: $r('app.string.mask_rect'), y: $r('app.string.mask_rect'),
                 width: $r('app.string.mask_rect'), height: $r('app.string.mask_rect') }对比
   * 点击坐标(1, 1)，退出弹窗
   */

  defineTest('datePickerDialogMaskRectTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('datePickerDialogMaskRectTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('DatePickerDialogMaskRect1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('DatePickerDialogMaskRect2').enabled(true))

    await button1.tap()
    let datePickerDialogMaskRect1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let maskRect1: string = await datePickerDialogMaskRect1.getInspectorInfo()
    assertFalse(JSON.parse(maskRect1).$attrs.maskRect == undefined)
    assertEqual(JSON.parse(maskRect1).$attrs.maskRect.x, 50)
    assertEqual(JSON.parse(maskRect1).$attrs.maskRect.y, 50)
    assertEqual(JSON.parse(maskRect1).$attrs.maskRect.width, 450)
    assertEqual(JSON.parse(maskRect1).$attrs.maskRect.height, 100)
    await driver.tap(1, 1)

    let datePickerDialogMaskRect2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let maskRect2: string = await datePickerDialogMaskRect2.getInspectorInfo()
    assertEqual(JSON.parse(maskRect2).$attrs.maskRect.x, '510px')
    assertEqual(JSON.parse(maskRect2).$attrs.maskRect.y, '510px')
    assertEqual(JSON.parse(maskRect2).$attrs.maskRect.width, '600px')
    assertEqual(JSON.parse(maskRect2).$attrs.maskRect.height, '600px')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogMaskRect3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let maskRect3: string = await datePickerDialogMaskRect3.getInspectorInfo()
    assertEqual(JSON.parse(maskRect3).$attrs.maskRect.x, $r('app.string.mask_rect'))
    assertEqual(JSON.parse(maskRect3).$attrs.maskRect.y, $r('app.string.mask_rect'))
    assertEqual(JSON.parse(maskRect3).$attrs.maskRect.width, $r('app.string.mask_rect'))
    assertEqual(JSON.parse(maskRect3).$attrs.maskRect.height, $r('app.string.mask_rect'))
    await driver.tap(1, 1)
  }, 0)
}