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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function actionSheetAlignmentTest() {
  /*
* ActionSheet组件 Alignment对象
* 找到画面id为actionSheetAlignment1，actionSheetAlignment2,actionSheetAlignment3，actionSheetAlignment4，actionSheetAlignment5的ActionSheet组件
* 找到画面文本为ActionSheetAlignment的Button组件
* 获取actionSheetAlignment1的Alignment对象与期待值DialogAlignment.Top比对
* 获取actionSheetAlignment2的Alignment对象与期待值DialogAlignment.Center比对
* 获取actionSheetAlignment3的Alignment对象与期待值DialogAlignment.Bottom比对
* 获取actionSheetAlignment4的Alignment对象与期待值DialogAlignment.Default比对
* 获取actionSheetAlignment5的Alignment对象与期待值DialogAlignment.TopStart比对
* 点击button，变更actionSheetAlignment1，actionSheetAlignment2,actionSheetAlignment3，actionSheetAlignment4，actionSheetAlignment5的对象值分别为
* DialogAlignment.TopEnd，DialogAlignment.CenterStart，DialogAlignment.CenterEnd，DialogAlignment.BottomStart，DialogAlignment.BottomEnd
* 获取actionSheetAlignment1的Alignment对象与期待值DialogAlignment.TopEnd比对
* 获取actionSheetAlignment2的Alignment对象与期待值DialogAlignment.CenterStart比对
* 获取actionSheetAlignment3的Alignment对象与期待值DialogAlignment.CenterEnd比对
* 获取actionSheetAlignment4的Alignment对象与期待值DialogAlignment.BottomStart比对
* 获取actionSheetAlignment5的Alignment对象与期待值DialogAlignment.BottomEnd比对
*/
  defineTest('actionSheetAlignmentTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('actionSheetAlignmentTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('ActionSheetAlignmentTest1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('ActionSheetAlignmentTest2').enabled(true))

    await button1.tap()
    let actionSheetAlignment1: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let alignment1: string = await actionSheetAlignment1.getInspectorInfo()
    assertEqual(JSON.parse(alignment1).$attrs.alignment, 'DialogAlignment.TOP')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let actionSheetAlignment2: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let alignment2: string = await actionSheetAlignment2.getInspectorInfo()
    assertEqual(JSON.parse(alignment2).$attrs.alignment, 'DialogAlignment.CENTER')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let actionSheetAlignment3: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let alignment3: string = await actionSheetAlignment3.getInspectorInfo()
    assertEqual(JSON.parse(alignment3).$attrs.alignment, 'DialogAlignment.BOTTOM')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let actionSheetAlignment4: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let alignment4: string = await actionSheetAlignment4.getInspectorInfo()
    assertEqual(JSON.parse(alignment4).$attrs.alignment, 'DialogAlignment.DEFAULT')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let actionSheetAlignment5: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let alignment5: string = await actionSheetAlignment5.getInspectorInfo()
    assertEqual(JSON.parse(alignment5).$attrs.alignment, 'DialogAlignment.TOP_START')
    await driver.tap(800, 800)

    await button2.tap()
    await button1.tap()
    let actionSheetAlignment6: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let alignment6: string = await actionSheetAlignment6.getInspectorInfo()
    assertEqual(JSON.parse(alignment6).$attrs.alignment, 'DialogAlignment.TOP_END')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let actionSheetAlignment7: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let alignment7: string = await actionSheetAlignment7.getInspectorInfo()
    assertEqual(JSON.parse(alignment7).$attrs.alignment, 'DialogAlignment.CENTER_START')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let actionSheetAlignment8: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let alignment8: string = await actionSheetAlignment8.getInspectorInfo()
    assertEqual(JSON.parse(alignment8).$attrs.alignment, 'DialogAlignment.CENTER_END')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let actionSheetAlignment9: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let alignment9: string = await actionSheetAlignment9.getInspectorInfo()
    assertEqual(JSON.parse(alignment9).$attrs.alignment, 'DialogAlignment.BOTTOM_START')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let actionSheetAlignment10: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let alignment10: string = await actionSheetAlignment10.getInspectorInfo()
    assertEqual(JSON.parse(alignment10).$attrs.alignment, 'DialogAlignment.BOTTOM_END')
    await driver.tap(1, 1)
  }, 0)
}