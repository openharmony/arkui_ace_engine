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

export default async function actionSheetBackgroundBlurStyleTest() {
  /*
* ActionSheet组件 BackgroundBlurStyle对象
* 找到画面id为actionSheetBackgroundBlurStyle1，actionSheetBackgroundBlurStyle2,actionSheetBackgroundBlurStyle3，actionSheetBackgroundBlurStyle4，actionSheetBackgroundBlurStyle5的ActionSheet组件
* 找到画面文本为ActionSheetBackgroundBlurStyle的Button组件
* 获取actionSheetBackgroundBlurStyle1的BackgroundBlurStyle对象与期待值BlurStyle.Thin比对
* 获取actionSheetBackgroundBlurStyle2的BackgroundBlurStyle对象与期待值BlurStyle.Regular比对
* 获取actionSheetBackgroundBlurStyle3的BackgroundBlurStyle对象与期待值BlurStyle.Thick比对
* 获取actionSheetBackgroundBlurStyle4的BackgroundBlurStyle对象与期待值BlurStyle.BACKGROUND_THIN比对
* 获取actionSheetBackgroundBlurStyle5的BackgroundBlurStyle对象与期待值BlurStyle.BACKGROUND_REGULAR比对
* 获取actionSheetBackgroundBlurStyle6的BackgroundBlurStyle对象与期待值BlurStyle.BACKGROUND_THICK比对
* 获取actionSheetBackgroundBlurStyle7的BackgroundBlurStyle对象与期待值BlurStyle.COMPONENT_ULTRA_THICK比对
* 点击button，变更actionSheetBackgroundBlurStyle1，actionSheetBackgroundBlurStyle2,actionSheetBackgroundBlurStyle3，actionSheetBackgroundBlurStyle4，actionSheetBackgroundBlurStyle5,actionSheetBackgroundBlurStyle6,的对象值分别为
* BlurStyle.BACKGROUND_ULTRA_THICK，BlurStyle.NONE，BlurStyle.COMPONENT_ULTRA_THIN，BlurStyle.COMPONENT_THIN，BlurStyle.COMPONENT_REGULAR,BlurStyle.COMPONENT_THICK
* 获取actionSheetBackgroundBlurStyle1的BackgroundBlurStyle对象与期待值BlurStyle.BACKGROUND_ULTRA_THICK比对
* 获取actionSheetBackgroundBlurStyle2的BackgroundBlurStyle对象与期待值BlurStyle.NONE比对
* 获取actionSheetBackgroundBlurStyle3的BackgroundBlurStyle对象与期待值BlurStyle.COMPONENT_ULTRA_THIN比对
* 获取actionSheetBackgroundBlurStyle4的BackgroundBlurStyle对象与期待值BlurStyle.COMPONENT_THIN比对
* 获取actionSheetBackgroundBlurStyle5的BackgroundBlurStyle对象与期待值BlurStyle.COMPONENT_REGULAR比对
* 获取actionSheetBackgroundBlurStyle6的BackgroundBlurStyle对象与期待值BlurStyle.COMPONENT_THICK比对
*/
  defineTest('actionSheetBackgroundBlurStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('actionSheetBackgroundBlurStyleTestDemo running')
    let driver: Tester = Tester.create()
    let button: Component =
      await driver.findComponent(Matcher.create().text('ActionSheetBackgroundBlurStyleTest1').enabled(true))

    await button.tap()
    let actionSheetBackgroundBlurStyle1: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let backgroundBlurStyle1: string = await actionSheetBackgroundBlurStyle1.getInspectorInfo()
    assertFalse(JSON.parse(backgroundBlurStyle1).$attrs.actionSheetBackgroundBlurStyle == undefined)
    assertEqual(JSON.parse(backgroundBlurStyle1).$attrs.actionSheetBackgroundBlurStyle, BlurStyle.Thin)
    await driver.tap(1, 1)
    await button.tap()
    let actionSheetBackgroundBlurStyle2: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let backgroundBlurStyle2: string = await actionSheetBackgroundBlurStyle2.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle2).$attrs.actionSheetBackgroundBlurStyle, BlurStyle.Regular)
    await driver.tap(1, 1)
    await button.tap()
    let actionSheetBackgroundBlurStyle3: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let backgroundBlurStyle3: string = await actionSheetBackgroundBlurStyle3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle3).$attrs.actionSheetBackgroundBlurStyle, BlurStyle.Thick)
    await driver.tap(1, 1)
    await button.tap()
    let actionSheetBackgroundBlurStyle4: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let backgroundBlurStyle4: string = await actionSheetBackgroundBlurStyle4.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle4).$attrs.actionSheetBackgroundBlurStyle, BlurStyle.BACKGROUND_THIN)
    await driver.tap(1, 1)
    await button.tap()
    let actionSheetBackgroundBlurStyle5: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let backgroundBlurStyle5: string = await actionSheetBackgroundBlurStyle5.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle5).$attrs.actionSheetBackgroundBlurStyle,
      BlurStyle.BACKGROUND_REGULAR)
    await driver.tap(1, 1)
    await button.tap()
    let actionSheetBackgroundBlurStyle6: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let backgroundBlurStyle6: string = await actionSheetBackgroundBlurStyle6.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle6).$attrs.actionSheetBackgroundBlurStyle, BlurStyle.BACKGROUND_THICK)
    await driver.tap(1, 1)
    await button.tap()
    let actionSheetBackgroundBlurStyle7: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let backgroundBlurStyle7: string = await actionSheetBackgroundBlurStyle7.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle7).$attrs.actionSheetBackgroundBlurStyle,
      BlurStyle.COMPONENT_ULTRA_THICK)
    await driver.tap(1, 1)
    await button.tap()
    let actionSheetBackgroundBlurStyle8: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let backgroundBlurStyle8: string = await actionSheetBackgroundBlurStyle8.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle8).$attrs.actionSheetBackgroundBlurStyle, BlurStyle.NONE)
    await driver.tap(1, 1)
    await button.tap()
    let actionSheetBackgroundBlurStyle9: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let backgroundBlurStyle9: string = await actionSheetBackgroundBlurStyle9.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle9).$attrs.actionSheetBackgroundBlurStyle,
      BlurStyle.COMPONENT_ULTRA_THIN)
    await driver.tap(1, 1)
    await button.tap()
    let actionSheetBackgroundBlurStyle10: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let backgroundBlurStyle10: string = await actionSheetBackgroundBlurStyle10.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle10).$attrs.actionSheetBackgroundBlurStyle, BlurStyle.COMPONENT_THIN)
    await driver.tap(1, 1)
    await button.tap()
    let actionSheetBackgroundBlurStyle11: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let backgroundBlurStyle11: string = await actionSheetBackgroundBlurStyle11.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle11).$attrs.actionSheetBackgroundBlurStyle,
      BlurStyle.COMPONENT_REGULAR)
    await driver.tap(1, 1)
    await button.tap()
    let actionSheetBackgroundBlurStyle12: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let backgroundBlurStyle12: string = await actionSheetBackgroundBlurStyle12.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle12).$attrs.actionSheetBackgroundBlurStyle, BlurStyle.COMPONENT_THICK)
    await driver.tap(1, 1)
    await button.tap()
    let actionSheetBackgroundBlurStyle13: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let backgroundBlurStyle13: string = await actionSheetBackgroundBlurStyle13.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle13).$attrs.actionSheetBackgroundBlurStyle,
      BlurStyle.COMPONENT_ULTRA_THICK)
    await driver.tap(1, 1)
  }, 0)
}