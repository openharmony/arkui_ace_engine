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
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'
import { logLibrary } from '@kit.PerformanceAnalysisKit'

export default async function tabContentTabBarTest() {
  /*
* TabContent组件 TabBar属性
* 找到画面id为tabContentTabBar1、 tabContentTabBar2、 tabContentTabBar3、
* tabContentTabBar4、 tabContentTabBar5、 tabContentTabBar6的TabContent组件
* 找到画面文本为TabContentTabBar1、 TabContentTabBar2、 TabContentTabBar3的Button组件
* 获取tabContent1的text属性与期待值'Pink'比对
* 获取tabContent2的text属性与期待值$r('app.string.tabs_string1')比对
* 获取tabContent3的text属性与期待值'green'比对
* 获取tabContent4的icon,text属性与期待值{ icon: '../../../resources/base/media/Tab.jpg', text: 'tabBar1' }比对
* 点击button1，变更tabContent4的icon,text属性值为{ icon: $r('sys.media.ohos_app_icon'), text: $r('app.string.tabs_string1') }
* 获取tabContent4的icon,text属性与期待值{ icon: $r('sys.media.ohos_app_icon'), text: $r('app.string.tabs_string1') }比对
* 获取tabContent5的text属性与期待值'tabBar3'比对
* 点击button3，变更tabContent5的text属性值为$r('app.string.tabs_string1')
* 获取tabContent5的text属性与期待值$r('app.string.tabs_string1')比对
* 获取tabContent6的icon,text属性与期待值{ icon: $r('sys.media.ohos_app_icon'), text: $r('app.string.tabs_string1') }比对
* 点击button2，变更tabContent6的icon,text属性值为{ icon: 'pages/tabContent/Tab.jpg', text: 'tabBar2' }
* 获取tabContent6的icon,text属性与期待值{ icon: 'pages/tabContent/Tab.jpg', text: 'tabBar2' }比对
*/
  defineTest('tabContentTabBarTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('tabContentTabBarTestDemo running')
    let driver: Tester = Tester.create()
    let tabContent1: Component = await driver.findComponent(Matcher.create().id('tabContentTabBar1').enabled(true))
    let tabContent2: Component = await driver.findComponent(Matcher.create().id('tabContentTabBar2').enabled(true))
    let tabContent3: Component = await driver.findComponent(Matcher.create().text('blue').enabled(true))
    let tabContent4: Component = await driver.findComponent(Matcher.create().id('tabContentTabBar4').enabled(true))
    let tabContent5: Component = await driver.findComponent(Matcher.create().id('tabContentTabBar5').enabled(true))
    let tabContent6: Component = await driver.findComponent(Matcher.create().id('tabContentTabBar6').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TabContentTabBar1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TabContentTabBar2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('TabContentTabBar3').enabled(true))

    let tabBar1: string = await tabContent1.getInspectorInfo()
    assertEqual(JSON.parse(tabBar1).$attrs.text, 'Pink')

    let tabBar2: string = await tabContent2.getInspectorInfo()
    assertEqual(JSON.parse(tabBar2).$attrs.text, $r("app.string.tabs_string"))

    let tabBar3: string = await tabContent3.getType()
    assertEqual(tabBar3, 'Text')

    let tabBar4: string = await tabContent4.getInspectorInfo()
    assertEqual(JSON.parse(tabBar4).$attrs.icon, '../../../resources/base/media/Tab.jpg')
    assertEqual(JSON.parse(tabBar4).$attrs.text, 'tabBar1')

    await button1.tap()
    let tabBar5: string = await tabContent4.getInspectorInfo()
    assertEqual(JSON.parse(tabBar5).$attrs.icon, $r('sys.media.ohos_app_icon'))
    assertEqual(JSON.parse(tabBar5).$attrs.text, $r("app.string.tabs_string"))

    let tabBar6: string = await tabContent5.getInspectorInfo()
    assertEqual(JSON.parse(tabBar6).$attrs.text, 'tabBar3')

    await button3.tap()
    let tabBar7: string = await tabContent5.getInspectorInfo()
    assertEqual(JSON.parse(tabBar7).$attrs.text, $r("app.string.tabs_string"))

    let tabBar8: string = await tabContent6.getInspectorInfo()
    assertEqual(JSON.parse(tabBar8).$attrs.icon, $r('sys.media.ohos_app_icon'))
    assertEqual(JSON.parse(tabBar8).$attrs.text, $r("app.string.tabs_string"))

    await button2.tap()
    let tabBar9: string = await tabContent6.getInspectorInfo()
    assertEqual(JSON.parse(tabBar9).$attrs.icon, 'pages/tabContent/Tab.jpg')
    assertEqual(JSON.parse(tabBar9).$attrs.text, 'tabBar2')
  }, 0)
}