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

export default async function actionSheetMaskRectTest() {
  /*
* ActionSheet组件 MaskRect对象
* 找到画面id为actionSheetMaskRect1,actionSheetMaskRect2的ActionSheet组件
* 找到画面文本为ActionSheetMaskRect的Button组件
* 获取actionSheetMaskRect1的MaskRect对象与期待值 { x: 1, y: 2, width: 200, height: 300 }比对
* 获取actionSheetMaskRect2的MaskRect对象与期待值 { x: '5px', y: '6px', width: '400px', height: '500px' }比对
* 点击button，变更actionSheetMaskRect2的对象值{ x: $r('app.float.actionSheet_maskRect_dx'), y: $r('app.float.actionSheet_maskRect_dy'), width: $r('app.integer.actionSheet_maskRect_width'), height: $r('app.integer.actionSheet_maskRect_height') }
* 获取actionSheetMaskRect2的MaskRect对象与期待值 { x: $r('app.float.actionSheet_maskRect_dx'), y: $r('app.float.actionSheet_maskRect_dy'), width: $r('app.integer.actionSheet_maskRect_width'), height: $r('app.integer.actionSheet_maskRect_height') }比对
*/
  defineTest('actionSheetMaskRectTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('actionSheetMaskRectTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('ActionSheetMaskRectTest1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ActionSheetMaskRectTest2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('ActionSheetMaskRectTest2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ActionSheetMaskRect1').enabled(true))

    await button1.tap()
    let actionSheetMaskRectTest1: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let maskRect1: string = await actionSheetMaskRectTest1.getInspectorInfo()
    assertFalse(JSON.parse(maskRect1).$attrs.maskRect == undefined)
    assertEqual(JSON.parse(maskRect1).$attrs.maskRect.x, 1)
    assertEqual(JSON.parse(maskRect1).$attrs.maskRect.y, 2)
    assertEqual(JSON.parse(maskRect1).$attrs.maskRect.width, 200)
    assertEqual(JSON.parse(maskRect1).$attrs.maskRect.height, 300)
    await driver.tap(1, 1)
    await button2.tap()
    let actionSheetMaskRectTest2: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let maskRect2: string = await actionSheetMaskRectTest2.getInspectorInfo()
    assertEqual(JSON.parse(maskRect2).$attrs.maskRect.x, '5px')
    assertEqual(JSON.parse(maskRect2).$attrs.maskRect.y, '6px')
    assertEqual(JSON.parse(maskRect2).$attrs.maskRect.width, '400px')
    assertEqual(JSON.parse(maskRect2).$attrs.maskRect.height, '500px')
    await driver.tap(1, 1)
    await button.tap()
    await button2.tap()
    let actionSheetMaskRectTest3: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let maskRect3: string = await actionSheetMaskRectTest3.getInspectorInfo()
    assertEqual(JSON.parse(maskRect3).$attrs.maskRect.x, $r('app.float.actionSheet_maskRect_dx'))
    assertEqual(JSON.parse(maskRect3).$attrs.maskRect.y, $r('app.float.actionSheet_maskRect_dy'))
    assertEqual(JSON.parse(maskRect3).$attrs.maskRect.width, $r('app.integer.actionSheet_maskRect_width'))
    assertEqual(JSON.parse(maskRect3).$attrs.maskRect.height, $r('app.integer.actionSheet_maskRect_height'))
    await driver.tap(1, 1)
    await button3.tap()
    let actionSheetMaskRectTest4: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let maskRect4: string = await actionSheetMaskRectTest4.getInspectorInfo()
    assertEqual(JSON.parse(maskRect4).$attrs.maskRect.x, 0)
    assertEqual(JSON.parse(maskRect4).$attrs.maskRect.y, 0)
    assertEqual(JSON.parse(maskRect4).$attrs.maskRect.width, 0)
    assertEqual(JSON.parse(maskRect4).$attrs.maskRect.height, 0)
  }, 0)
}