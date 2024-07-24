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
} from '@ohos.arkui.componentTest';

export default async function textPickerDialogMaskRectTest() {
  /*
   * TextPickerDialog组件 MaskRect对象
   * 找到画面文本为TextPickerDialogMaskRect1,TextPickerDialogMaskRect2,TextPickerDialogMaskRect3的Button组件
   * 点击Button1改变MaskRect对象x属性为0,
   * 改变MaskRect对象y属性为0,
   * 改变MaskRect对象width属性为2560,
   * 改变MaskRect对象height属性为1600
   * 找到可以滚动的TextPickerDialog组件
   * 获取maskRect1的MaskRect对象x属性与期待值0比对
   * 获取maskRect1的MaskRect对象y属性与期待值0比对
   * 获取maskRect1的MaskRect对象width属性与期待值2560比对
   * 获取maskRect1的MaskRect对象height属性与期待值1600比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变MaskRect对象x属性为'100',
   * 改变MaskRect对象y属性为'100',
   * 改变MaskRect对象width属性为'800',
   * 改变MaskRect对象height属性为'500'
   * 找到可以滚动的TextPickerDialog组件
   * 获取maskRect2的MaskRect对象x属性与期待值'100'比对
   * 获取maskRect2的MaskRect对象y属性与期待值'100'比对
   * 获取maskRect2的MaskRect对象width属性与期待值'800'比对
   * 获取maskRect2的MaskRect对象height属性与期待值'500'比对
   * 点击屏幕坐标(100，100)
   * 点击Button3改变MaskRect对象x属性为$r('app.integer.textPickerDialog_maskRect_x'),
   * 改变MaskRect对象y属性为$r('app.integer.textPickerDialog_maskRect_y'),
   * 改变MaskRect对象width属性为$r('app.integer.textPickerDialog_maskRect_width'),
   * 改变MaskRect对象height属性为$r('app.integer.textPickerDialog_maskRect_height')
   * 找到可以滚动的TextPickerDialog组件
   * 获取maskRect3的MaskRect对象x属性与期待值$r('app.integer.textPickerDialog_maskRect_x')比对
   * 获取maskRect3的MaskRect对象y属性与期待值$r('app.integer.textPickerDialog_maskRect_y')比对
   * 获取maskRect3的MaskRect对象width属性与期待值$r('app.integer.textPickerDialog_maskRect_width')比对
   * 获取maskRect3的MaskRect对象height属性与期待值$r('app.integer.textPickerDialog_maskRect_height')比对
   * 点击屏幕坐标(100，100)
   */
  defineTest('textPickerDialogMaskRectTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textPickerDialogMaskRectTestDemo running")
    let driver: Tester = Tester.create()

    let button1: Component =
      await driver.findComponent(Matcher.create().text('TextPickerDialogMaskRect1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('TextPickerDialogMaskRect2').enabled(true))
    let button3: Component =
      await driver.findComponent(Matcher.create().text('TextPickerDialogMaskRect3').enabled(true))

    await button1.tap()
    let textMaskRect1: Component = await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let maskRect1: string = await textMaskRect1.getInspectorInfo()
    assertFalse(JSON.parse(maskRect1).$attrs.maskRect == undefined)
    assertEqual(JSON.parse(maskRect1).$attrs.maskRect.x, 0)
    assertEqual(JSON.parse(maskRect1).$attrs.maskRect.y, 0)
    assertEqual(JSON.parse(maskRect1).$attrs.maskRect.width, 2560)
    assertEqual(JSON.parse(maskRect1).$attrs.maskRect.height, 1600)
    await driver.tap(100, 100)

    await button2.tap()
    let textMaskRect2: Component = await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let maskRect2: string = await textMaskRect2.getInspectorInfo()
    assertEqual(JSON.parse(maskRect2).$attrs.maskRect.x, '100')
    assertEqual(JSON.parse(maskRect2).$attrs.maskRect.y, '100')
    assertEqual(JSON.parse(maskRect2).$attrs.maskRect.width, '800')
    assertEqual(JSON.parse(maskRect2).$attrs.maskRect.height, '500')
    await driver.tap(100, 100)

    await button3.tap()
    let textMaskRect3: Component = await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let maskRect3: string = await textMaskRect3.getInspectorInfo()
    assertEqual(JSON.parse(maskRect3).$attrs.maskRect.x, $r('app.integer.textPickerDialog_maskRect_x'))
    assertEqual(JSON.parse(maskRect3).$attrs.maskRect.y, $r('app.integer.textPickerDialog_maskRect_y'))
    assertEqual(JSON.parse(maskRect3).$attrs.maskRect.width, $r('app.integer.textPickerDialog_maskRect_width'))
    assertEqual(JSON.parse(maskRect3).$attrs.maskRect.height, $r('app.integer.textPickerDialog_maskRect_height'))
    await driver.tap(100, 100)
  }, 0)
}