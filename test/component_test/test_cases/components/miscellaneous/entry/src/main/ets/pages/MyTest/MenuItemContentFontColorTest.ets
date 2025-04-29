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

import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function menuItemContentFontColorTest() {
  /*
* MenuItem组件 ContentFontColor属性
* 找到画面id为menuItemContentFontColor1,menuItemContentFontColor2的MenuItem组件
* 找到画面文本为MenuItemContentFontColor1的Button1组件
* 找到画面文本为MenuItemContentFontColor2的Button2组件
* 获取menuItemContentFontColor1的ContentFontColor属性与期待值Color.Red比对
* 点击button1，变更menuItemContentFontColor1的ContentFontColor属性值为$r('sys.color.ohos_fa_connected')
* 获取menuItemContentFontColor1的ContentFontColor属性与期待值$r('sys.color.ohos_fa_connected')比对
* 点击button2，变更menuItemContentFontColor1的ContentFontColor属性值为0xfff000
* 获取menuItemContentFontColor1的ContentFontColor属性与期待值'#FFFFF000'比对
* 获取menuItemContentFontColor2的ContentFontColor属性与期待值'#FFFF79F2'比对
*/
  defineTest('menuItemContentFontColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('menuItemContentFontColorTestDemo running')
    let driver: Tester = Tester.create()
    let menuItemContentFontColor1: Component =
      await driver.findComponent(Matcher.create().id('menuItemContentFontColor1').enabled(true))
    let menuItemContentFontColor2: Component =
      await driver.findComponent(Matcher.create().id('menuItemContentFontColor2').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('MenuItemContentFontColor1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('MenuItemContentFontColor2').enabled(true))

    let contentFontColor1: string = await menuItemContentFontColor1.getInspectorInfo()
    assertEqual(JSON.parse(contentFontColor1).$attrs.contentFontColor.toLowerCase(), Color.Red)

    await button1.tap()
    let contentFontColor2: string = await menuItemContentFontColor1.getInspectorInfo()
    assertEqual(JSON.parse(contentFontColor2).$attrs.contentFontColor, $r('sys.color.ohos_fa_connected'))

    await button2.tap()
    let contentFontColor3: string = await menuItemContentFontColor1.getInspectorInfo()
    assertEqual(JSON.parse(contentFontColor3).$attrs.contentFontColor, '#FFFFF000')

    let contentFontColor4: string = await menuItemContentFontColor2.getInspectorInfo()
    assertEqual(JSON.parse(contentFontColor4).$attrs.contentFontColor, '#FFFF79F2')
  }, 0)
}