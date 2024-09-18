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

export default async function navigationToolbarConfigurationTest() {
  /*
* Navigation组件 ToolbarConfiguration属性
* 找到画面id为navigationToolbarConfiguration1,navigationToolbarConfiguration2的Navigation组件
* 找到画面文本为NavigationToolbarConfiguration1,NavigationToolbarConfiguration2的Button组件
* 获取navigation1的toolbarConfiguration.value.value属性与期待值'hello'比对
* 获取navigation1的toolbarConfiguration.value.icon属性与期待值$r('sys.media.ohos_ic_public_drawer_open_filled')比对
* 获取navigation1的toolbarConfiguration.value.action属性与期待值'free'比对
* 获取navigation1的toolbarConfiguration.value.status属性与期待值ToolbarItemStatus.NORMAL比对
* 获取navigation1的toolbarConfiguration.value.activeIcon属性与期待值$r('sys.media.ohos_ic_public_location')比对
* 获取navigation1的toolbarConfiguration.options.backgroundColor属性与期待值Color.Yellow比对
* 获取navigation1的toolbarConfiguration.options.backgroundBlurStyle属性与期待值BlurStyle.Thin比对
* 获取navigation2的toolbarConfiguration属性与期待值BlurStyle.Thin比对
* 点击button1，变更navigation1的toolbarConfiguration.value.value属性值为'hello'
* 点击button1，变更navigation1的toolbarConfiguration.value.icon属性值为$r('sys.media.ohos_ic_public_drawer_open_filled')
* 点击button1，变更navigation1的toolbarConfiguration.value.action属性值为'free'
* 点击button1，变更navigation1的toolbarConfiguration.value.status属性值为ToolbarItemStatus.DISABLED
* 点击button1，变更navigation1的toolbarConfiguration.value.activeIcon属性值为$r('sys.media.ohos_ic_public_location')
* 点击button1，变更navigation1的toolbarConfiguration.value.options.backgroundColor属性值为$r('app.color.background_color')
* 点击button1，变更navigation1的toolbarConfiguration.value.options.backgroundBlurStyle属性值为BlurStyle.Thick
* 获取navigation1的toolbarConfiguration.value.value属性与期待值'hello'比对
* 获取navigation1的toolbarConfiguration.value.icon属性与期待值$r('sys.media.ohos_ic_public_drawer_open_filled')比对
* 获取navigation1的toolbarConfiguration.value.action属性与期待值'free'比对
* 获取navigation1的toolbarConfiguration.value.status属性与期待值ToolbarItemStatus.DISABLED比对
* 获取navigation1的toolbarConfiguration.value.activeIcon属性与期待值$r('sys.media.ohos_ic_public_location')比对
* 获取navigation1的toolbarConfiguration.options.backgroundColor属性与期待值$r('app.color.background_color')比对
* 获取navigation1的toolbarConfiguration.options.backgroundBlurStyle属性与期待值BlurStyle.Thick比对
* 获取navigation2的toolbarConfiguration属性与期待值BlurStyle.Thin比对
* 点击button2，变更navigation1的toolbarConfiguration.value.value属性值为'hello'
* 点击button2，变更navigation1的toolbarConfiguration.value.icon属性值为$r('sys.media.ohos_ic_public_drawer_open_filled')
* 点击button2，变更navigation1的toolbarConfiguration.value.action属性值为'free'
* 点击button2，变更navigation1的toolbarConfiguration.value.status属性值为ToolbarItemStatus.ACTIVE
* 点击button2，变更navigation1的toolbarConfiguration.value.activeIcon属性值为$r('sys.media.ohos_ic_public_location')
* 点击button2，变更navigation1的toolbarConfiguration.value.options.backgroundColor属性值为0x0000ff
* 点击button2，变更navigation1的toolbarConfiguration.value.options.backgroundBlurStyle属性值为BlurStyle.Regular
* 获取navigation1的toolbarConfiguration.value.value属性与期待值'hello'比对
* 获取navigation1的toolbarConfiguration.value.icon属性与期待值$r('sys.media.ohos_ic_public_drawer_open_filled')比对
* 获取navigation1的toolbarConfiguration.value.action属性与期待值'free'比对
* 获取navigation1的toolbarConfiguration.value.status属性与期待值ToolbarItemStatus.ACTIVE比对
* 获取navigation1的toolbarConfiguration.value.activeIcon属性与期待值$r('sys.media.ohos_ic_public_location')比对
* 获取navigation1的toolbarConfiguration.options.backgroundColor属性与期待值0x0000ff比对
* 获取navigation1的toolbarConfiguration.options.backgroundBlurStyle属性与期待值BlurStyle.Regular比对
* 获取navigation2的toolbarConfiguration属性与期待值BlurStyle.Thin比对
*/
  defineTest('navigationToolbarConfigurationTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("navigationToolbarConfigurationTestDemo running")
    let driver: Tester = Tester.create()
    let navigation1: Component =
      await driver.findComponent(Matcher.create().id('navigationToolbarConfiguration1').enabled(true))
    let navigation2: Component =
      await driver.findComponent(Matcher.create().id('navigationToolbarConfiguration2').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('NavigationToolbarConfiguration1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('NavigationToolbarConfiguration2').enabled(true))
    let builder = await driver.findComponent(Matcher.create().text('free').enabled(true))
    let myBuilder: string = await builder.getType()
    assertEqual(myBuilder, 'Text')
    let toolbarConfiguration1: string = await navigation1.getInspectorInfo()
    assertFalse(JSON.parse(toolbarConfiguration1).$attrs.toolbarConfiguration == undefined)
    assertEqual(JSON.parse(toolbarConfiguration1).$attrs.toolbarConfiguration.value, 'hello')
    assertEqual(JSON.parse(toolbarConfiguration1).$attrs.toolbarConfiguration.icon,
      $r('sys.media.ohos_ic_public_drawer_open_filled'))
    assertEqual(JSON.parse(toolbarConfiguration1).$attrs.toolbarConfiguration.action, 'free')
    assertEqual(JSON.parse(toolbarConfiguration1).$attrs.toolbarConfiguration.status, ToolbarItemStatus.NORMAL)
    assertEqual(JSON.parse(toolbarConfiguration1).$attrs.toolbarConfiguration.activeIcon,
      $r('sys.media.ohos_ic_public_location'))
    assertEqual(JSON.parse(toolbarConfiguration1).$attrs.toolbarConfiguration.backgroundColor, Color.Yellow)
    assertEqual(JSON.parse(toolbarConfiguration1).$attrs.toolbarConfiguration.backgroundBlurStyle, BlurStyle.Thin)
    let toolbarConfiguration2: string = await navigation2.getInspectorInfo()
    assertEqual(JSON.parse(toolbarConfiguration2).$attrs.toolbarConfiguration, 'free')
    await button1.tap()
    let toolbarConfiguration3: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(toolbarConfiguration3).$attrs.toolbarConfiguration.value, 'hello')
    assertEqual(JSON.parse(toolbarConfiguration3).$attrs.toolbarConfiguration.icon,
      $r('sys.media.ohos_ic_public_drawer_open_filled'))
    assertEqual(JSON.parse(toolbarConfiguration3).$attrs.toolbarConfiguration.action, 'free')
    assertEqual(JSON.parse(toolbarConfiguration3).$attrs.toolbarConfiguration.status, ToolbarItemStatus.DISABLED)
    assertEqual(JSON.parse(toolbarConfiguration3).$attrs.toolbarConfiguration.activeIcon,
      $r('sys.media.ohos_ic_public_location'))
    assertEqual(JSON.parse(toolbarConfiguration3).$attrs.toolbarConfiguration.backgroundColor,
      $r("app.color.navigation_color"))
    assertEqual(JSON.parse(toolbarConfiguration3).$attrs.toolbarConfiguration.backgroundBlurStyle, BlurStyle.Thick)
    await button2.tap()
    let toolbarConfiguration4: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(toolbarConfiguration4).$attrs.toolbarConfiguration.value, 'hello')
    assertEqual(JSON.parse(toolbarConfiguration4).$attrs.toolbarConfiguration.icon,
      $r('sys.media.ohos_ic_public_drawer_open_filled'))
    assertEqual(JSON.parse(toolbarConfiguration4).$attrs.toolbarConfiguration.action, 'free')
    assertEqual(JSON.parse(toolbarConfiguration4).$attrs.toolbarConfiguration.status, ToolbarItemStatus.ACTIVE)
    assertEqual(JSON.parse(toolbarConfiguration4).$attrs.toolbarConfiguration.activeIcon,
      $r('sys.media.ohos_ic_public_location'))
    assertEqual(JSON.parse(toolbarConfiguration4).$attrs.toolbarConfiguration.backgroundColor, 0x0000ff)
    assertEqual(JSON.parse(toolbarConfiguration4).$attrs.toolbarConfiguration.backgroundBlurStyle, BlurStyle.Regular)
  }, 0)
}