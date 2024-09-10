/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
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

export default async function menuItemSelectIconTest() {
  /*
* MenuItem组件 SelectIcon属性
* 找到画面id为menuItemSelectIcon1,menuItemSelectIcon2的MenuItem组件
* 找到画面文本为MenuItemLabelFontColor1的Button1组件
* 找到画面文本为MenuItemLabelFontColor2的Button2组件
* 获取menuItemSelectIcon1的SelectIcon属性与期待值False比对
* 点击button1，变更menuItemSelectIcon1的SelectIcon属性值为True
* 获取menuItemSelectIcon1的SelectIcon属性与期待值True比对
* 点击button2，变更menuItemSelectIcon1的SelectIcon属性值为$r("sys.media.ohos_app_icon")
* 获取menuItemSelectIcon1的SelectIcon属性与期待值$r("sys.media.ohos_app_icon")比对
* 获取menuItemSelectIcon2的ContentFontColor属性与期待值"../../../resources/base/media/icon.png"比对
*/
  defineTest('menuItemSelectIconTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('menuItemSelectIconTestDemo running')
    let driver: Tester = Tester.create()
    let menuItemSelectIcon1: Component =
      await driver.findComponent(Matcher.create().id('menuItemSelectIcon1').enabled(true))
    let menuItemSelectIcon2: Component =
      await driver.findComponent(Matcher.create().id('menuItemSelectIcon2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('MenuItemSelectIcon1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('MenuItemSelectIcon2').enabled(true))

    let selectIcon1: string = await menuItemSelectIcon1.getInspectorInfo()
    assertFalse(JSON.parse(selectIcon1).$attrs.selectIcon)

    await button1.tap()
    let selectIcon2: string = await menuItemSelectIcon1.getInspectorInfo()
    assertTrue(JSON.parse(selectIcon2).$attrs.selectIcon)

    await button2.tap()
    let selectIcon3: string = await menuItemSelectIcon1.getInspectorInfo()
    assertEqual(JSON.parse(selectIcon3).$attrs.selectIcon, $r("sys.media.ohos_app_icon"))

    let selectIcon4: string = await menuItemSelectIcon2.getInspectorInfo()
    assertEqual(JSON.parse(selectIcon4).$attrs.selectIcon, "../../../resources/base/media/icon.png")
  }, 0)
}