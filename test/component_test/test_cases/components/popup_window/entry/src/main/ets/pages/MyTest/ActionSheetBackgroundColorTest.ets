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

export default async function actionSheetBackgroundColorTest() {
  /*
* ActionSheet组件 BackgroundColor对象
* 找到画面id为actionSheetBackgroundColor1,actionSheetBackgroundColor2的ActionSheet组件
* 找到画面文本为ActionSheetBackgroundColor的Button组件
* 获取actionSheetBackgroundColor1的BackgroundColor对象与期待值 Color.Gray比对
* 获取actionSheetBackgroundColor2的BackgroundColor对象与期待值 "#FFBC3535"比对
* 点击button，变更actionSheetBackgroundColor1,actionSheetBackgroundColor2的对象值$r('app.color.listItemGroup_color'),0x00dd77
* 获取actionSheetBackgroundColor1的BackgroundColor对象与期待值 $r('app.color.listItemGroup_color')比对
* 获取actionSheetBackgroundColor2的BackgroundColor对象与期待值 0x00dd77比对
*/
  defineTest('actionSheetBackgroundColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('actionSheetBackgroundColorTestDemo running')
    let driver: Tester = Tester.create()

    let button1: Component =
      await driver.findComponent(Matcher.create().text('ActionSheetBackgroundColorTest1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('ActionSheetBackgroundColorTest2').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('ActionSheetBackgroundColor1').enabled(true))

    await button1.tap()
    let actionSheetBackgroundBlurStyle1: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let backgroundColor1: string = await actionSheetBackgroundBlurStyle1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor1).$attrs.backgroundColor.toLowerCase(), Color.Gray)

    await driver.tap(1, 1)
    await button2.tap()
    let actionSheetBackgroundBlurStyle2: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let backgroundColor2: string = await actionSheetBackgroundBlurStyle2.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor2).$attrs.backgroundColor, "#FFBC3535")

    await driver.tap(1, 1)
    await button.tap()
    await button1.tap()
    let actionSheetBackgroundBlurStyle3: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let backgroundColor3: string = await actionSheetBackgroundBlurStyle3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor3).$attrs.backgroundColor, $r("app.color.action_sheet_color"))

    await driver.tap(1, 1)
    await button2.tap()
    let actionSheetBackgroundBlurStyle4: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let backgroundColor4: string = await actionSheetBackgroundBlurStyle4.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor4).$attrs.backgroundColor, '#FF00DD77')
    await driver.tap(1, 1)
  }, 0)
}