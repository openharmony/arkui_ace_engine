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
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function navigationTitleTest() {
  /*
* Navigation组件 Title属性
* 找到画面id为navigationTitle1,navigationTitle2,navigationTitle3,navigationTitle4,navigationTitle5的Navigation组件
* 找到画面文本为NavigationTitle1,NavigationTitle2的Button组件
* 获取navigation1的Title属性与期待值'state'比对
* 获取navigation2的Title.value.builder属性与期待值'hello'比对
* 获取navigation2的Title.value.height属性与期待值TitleHeight.MainOnly比对
* 获取navigation2的Title.options.backgroundColor属性与期待值0x0000ff比对
* 获取navigation2的Title.options.backgroundBlurStyle属性与期待值BlurStyle.Thick比对
* 获取navigation3的Title.value.builder属性与期待值'hello'比对
* 获取navigation3的Title.value.height属性与期待值TitleHeight.MainWithSub比对
* 获取navigation3的Title.options.backgroundColor属性与期待值Color.Green比对
* 获取navigation3的Title.options.backgroundBlurStyle属性与期待值BlurStyle.Thin比对
* 获取navigation4的Title.builder属性与期待值'hello'比对
* 获取navigation4的Title.height属性与期待值50比对
* 点击button1，变更navigation1的Title.main属性值为'nihao'
* 点击button1，变更navigation1的Title.sub属性值为'world'
* 获取navigation1的Title.main属性与期待值'nihao'比对
* 获取navigation1的Title.sub属性与期待值'world'比对
* 点击button2，变更navigation1的Title属性值为$r("app.string.navigation_title")
* 获取navigation1的Title属性与期待值$r("app.string.navigation_title")比对
*/
  defineTest('navigationTitleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("navigationTitleTestDemo running")
    let driver: Tester = Tester.create()
    let navigation1: Component = await driver.findComponent(Matcher.create().id('navigationTitle1').enabled(true))
    let navigation2: Component = await driver.findComponent(Matcher.create().id('navigationTitle3').enabled(true))
    let navigation3: Component = await driver.findComponent(Matcher.create().id('navigationTitle4').enabled(true))
    let navigation4: Component = await driver.findComponent(Matcher.create().id('navigationTitle5').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('NavigationTitle1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('NavigationTitle2').enabled(true))
    let title1: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(title1).$attrs.title, 'state')
    let title2: Component = await driver.findComponent(Matcher.create().id('title2').enabled(true))
    let text: string = await title2.getText()
    assertEqual(text, 'Hi')
    let title3: string = await navigation2.getInspectorInfo()
    assertEqual(JSON.parse(title3).$attrs.title.builder, 'hello')
    assertEqual(JSON.parse(title3).$attrs.title.height, TitleHeight.MainOnly)
    assertEqual(JSON.parse(title3).$attrs.title.backgroundColor, 0x0000ff)
    assertEqual(JSON.parse(title3).$attrs.title.backgroundBlurStyle, BlurStyle.Thick)
    let title4: string = await navigation3.getInspectorInfo()
    assertEqual(JSON.parse(title4).$attrs.title.builder, 'hello')
    assertEqual(JSON.parse(title4).$attrs.title.height, TitleHeight.MainWithSub)
    assertEqual(JSON.parse(title4).$attrs.title.backgroundColor, Color.Green)
    assertEqual(JSON.parse(title4).$attrs.title.backgroundBlurStyle, BlurStyle.Thin)
    let title5: string = await navigation4.getInspectorInfo()
    assertEqual(JSON.parse(title5).$attrs.title.builder, 'hello')
    assertEqual(JSON.parse(title5).$attrs.title.height, 50)
    await button1.tap()
    let title6: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(title6).$attrs.title.main, 'nihao')
    assertEqual(JSON.parse(title6).$attrs.title.sub, 'world')
    await button2.tap()
    let title7: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(title7).$attrs.title, $r("app.string.navigation_title"))
  }, 0)
}