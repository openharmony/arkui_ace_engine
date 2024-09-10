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

export default async function navDestinationTitleTest() {
  /*
* NavDestination组件 Title属性
* 找到画面文本为PushNavDestination的button组件
* 点击button1，跳转到NavDestination组件所在界面
* 找到画面id为navDestinationTitle的NavDestination组件
* 找到画面文本为NavDestinationTitle1,NavDestinationTitle2,NavDestinationTitle3,NavDestinationTitle4,NavDestinationTitle5的button组件
* 获取navDestination的Title属性与期待值'CustomBuilder'比对
* 点击button2，变更navDestination的Title属性值为'NavDestinationTitle1'
* 获取navDestination的Title属性与期待值'NavDestinationTitle1'比对
* 点击button3，变更navDestination的Title属性值为'NavDestination','Title2'
* 获取navDestination的Title属性与期待值'NavDestination','Title2'比对
* 点击button4，变更navDestination的Title属性值为'CustomBuilder',TitleHeight.MainOnly
* 获取navDestination的Title属性与期待值'CustomBuilder',TitleHeight.MainOnly比对
* 点击button5，变更navDestination的Title属性值为'CustomBuilder',TitleHeight.MainWithSub
* 获取navDestination的Title属性与期待值'CustomBuilder',TitleHeight.MainWithSub比对
* 点击button6，变更navDestination的Title属性值为'CustomBuilder',10
* 获取navDestination的Title属性与期待值'CustomBuilder',10比对
*/
  defineTest('navDestinationTitleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("navDestinationTitleTestDemo running")
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('PushNavDestination').enabled(true))
    await button1.tap()

    let navDestination: Component = await driver.findComponent(Matcher.create().id('navDestinationTitle').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('NavDestinationTitle1').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('NavDestinationTitle2').enabled(true))
    let button4: Component = await driver.findComponent(Matcher.create().text('NavDestinationTitle3').enabled(true))
    let button5: Component = await driver.findComponent(Matcher.create().text('NavDestinationTitle4').enabled(true))
    let button6: Component = await driver.findComponent(Matcher.create().text('NavDestinationTitle5').enabled(true))
    let title1: string = await navDestination.getInspectorInfo()
    assertFalse(JSON.parse(title1).$attrs.title == undefined)
    assertEqual(JSON.parse(title1).$attrs.title, 'CustomBuilder')

    await button2.tap()
    let title2: string = await navDestination.getInspectorInfo()
    assertEqual(JSON.parse(title2).$attrs.title, 'NavDestinationTitle1')

    await button3.tap()
    let title3: string = await navDestination.getInspectorInfo()
    assertEqual(JSON.parse(title3).$attrs.title.main, 'NavDestination')
    assertEqual(JSON.parse(title3).$attrs.title.sub, 'Title2')

    await button4.tap()
    let title4: string = await navDestination.getInspectorInfo()
    assertEqual(JSON.parse(title4)
      .$attrs
      .title
      .builder
      .CustomBuilder, 'CustomBuilder')
    assertEqual(JSON.parse(title4).$attrs.title.height, TitleHeight.MainOnly)

    await button5.tap()
    let title5: string = await navDestination.getInspectorInfo()
    assertEqual(JSON.parse(title5)
      .$attrs
      .title
      .builder
      .CustomBuilder, 'CustomBuilder')
    assertEqual(JSON.parse(title5).$attrs.title.height, TitleHeight.MainWithSub)

    await button6.tap()
    let title6: string = await navDestination.getInspectorInfo()
    assertEqual(JSON.parse(title6)
      .$attrs
      .title
      .builder
      .CustomBuilder, 'CustomBuilder')
    assertEqual(JSON.parse(title6).$attrs.title.height, 10)
  }, 0)
}