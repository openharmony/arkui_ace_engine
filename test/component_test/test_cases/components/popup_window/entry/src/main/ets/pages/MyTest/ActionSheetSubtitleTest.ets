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

export default async function actionSheetSubtitleTest() {
  /*
   * ActionSheet组件 Subtitle对象
   * 找到画面id为actionSheetSubTitle的ActionSheet组件
   * 找到画面文本为ActionSheetTitle的Button组件
   * 获取actionSheet的Subtitle对象与期待值'subtitle1'比对
   * 点击button，变更actionSheet的Subtitle对象值为 $r('app.string.actionSheet_subtitle')
   * 获取actionSheet的Subtitle对象与期待值 $r('app.string.actionSheet_subtitle')比对
   */
  defineTest('actionSheetSubtitleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('actionSheetSubtitleTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('ActionSheetSubtitleTest1').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ActionSheetSubtitle1').enabled(true))

    await button1.tap()
    let actionSheetSubTitle1: Component = await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let subtitle1: string = await actionSheetSubTitle1.getInspectorInfo()
    assertEqual(JSON.parse(subtitle1).$attrs.subtitle, 'subtitle1')
    await driver.tap(1, 1)
    await button.tap()
    await button1.tap()
    let actionSheetSubTitle2: Component = await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let subtitle2: string = await actionSheetSubTitle2.getInspectorInfo()
    assertEqual(JSON.parse(subtitle2).$attrs.subtitle, $r('app.string.actionSheet_subtitle'))
    await driver.tap(1, 1)
  }, 0)
}