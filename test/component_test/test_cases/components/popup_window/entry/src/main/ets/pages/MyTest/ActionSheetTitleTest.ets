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

export default async function actionSheetCancelTest() {
  /*
   * ActionSheet组件 Title对象
   * 找到画面id为actionSheetTitle的ActionSheet组件
   * 找到画面文本为ActionSheetTitle的Button组件
   * 获取actionSheet的Title对象与期待值'title1'比对
   * 点击button，变更actionSheet的Title对象值为$r('app.string.actionSheet_title')
   * 获取actionSheet的Title对象与期待值$r('app.string.actionSheet_title')比对
   */
  defineTest('actionSheetTitleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('actionSheetTitleTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('ActionSheetTitleTest1').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ActionSheetTitle1').enabled(true))

    await button1.tap()
    let ActionSheetTitle1: Component = await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let title1: string = await ActionSheetTitle1.getInspectorInfo()
    assertEqual(JSON.parse(title1).$attrs.title, 'title1')
    await driver.tap(1, 1)
    await button.tap()
    await button1.tap()
    let ActionSheetTitle2: Component = await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let title2: string = await ActionSheetTitle2.getInspectorInfo()
    assertEqual(JSON.parse(title2).$attrs.title, $r('app.string.actionSheet_title'))
    await driver.tap(1, 1)
  }, 0)
}