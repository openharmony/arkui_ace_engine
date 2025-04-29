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

export default async function menuItemContentFontTest() {
  /*
* MenuItem组件 ContentFont属性
* 找到画面id为menuItemContentFont1,menuItemContentFont2,menuItemContentFont3,menuItemContentFont4,menuItemContentFont5,menuItemContentFont6的MenuItem组件
* 找到画面文本为MenuItemContentFont1的Button1组件
* 找到画面文本为MenuItemContentFont2的Button2组件
* 获取menuItemContentFont1的{ ContentFont.Size,ContentFont.Weight,ContentFont.Family,ContentFont.Style }属性与期待值{'20.00fp',500,'Arial',FontStyle.Normal }比对
* 点击button1，变更menuItemContentFont1的ContentFont属性值为{$r('app.string.font_size'),FontWeight.Bolder,'Arial',FontStyle.Normal }
* 获取menuItemContentFont1的{ ContentFont.Size,ContentFont.Weight,ContentFont.Family,ContentFont.Style }属性与期待值{$r('app.string.font_size'),FontWeight.Bolder,'Arial',FontStyle.Normal }比对
* 点击button2，变更menuItemContentFont1的ContentFont.Weight属性值为FontWeight.Bold
* 获取menuItemContentFont1的ContentFont.Weight属性与期待值FontWeight.Bold比对
* 获取menuItemContentFont2的{ ContentFont.Size,ContentFont.Weight,ContentFont.Family,ContentFont.Style }属性与期待值{'30.00px','40px','TESTFONTRawFile',FontStyle.Italic }比对
* 获取menuItemContentFont3的ContentFont.Weight属性与期待值FontWeight.Lighter比对
* 获取menuItemContentFont4的ContentFont.Weight属性与期待值FontWeight.Normal比对
* 获取menuItemContentFont5的ContentFont.Weight属性与期待值FontWeight.Regular比对
* 获取menuItemContentFont6的ContentFont.Weight属性与期待值FontWeight.Medium比对
*/
  defineTest('menuItemContentFontTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('menuItemContentFontTestDemo running')
    let driver: Tester = Tester.create()
    let menuItemContentFont1: Component =
      await driver.findComponent(Matcher.create().id('menuItemContentFont1').enabled(true))
    let menuItemContentFont2: Component =
      await driver.findComponent(Matcher.create().id('menuItemContentFont2').enabled(true))
    let menuItemContentFont3: Component =
      await driver.findComponent(Matcher.create().id('menuItemContentFont3').enabled(true))
    let menuItemContentFont4: Component =
      await driver.findComponent(Matcher.create().id('menuItemContentFont4').enabled(true))
    let menuItemContentFont5: Component =
      await driver.findComponent(Matcher.create().id('menuItemContentFont5').enabled(true))
    let menuItemContentFont6: Component =
      await driver.findComponent(Matcher.create().id('menuItemContentFont6').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('MenuItemContentFont1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('MenuItemContentFont2').enabled(true))

    let contentFont1: string = await menuItemContentFont1.getInspectorInfo()
    assertEqual(JSON.parse(contentFont1).$attrs.contentFont.size, '20.00fp')
    assertEqual(JSON.parse(contentFont1).$attrs.contentFont.weight, '500')
    assertEqual(JSON.parse(contentFont1).$attrs.contentFont.family, 'Arial')
    assertEqual(JSON.parse(contentFont1).$attrs.contentFont.style, 'FontStyle.Normal')

    await button1.tap()
    let contentFont2: string = await menuItemContentFont1.getInspectorInfo()
    assertEqual(JSON.parse(contentFont2).$attrs.contentFont.size, $r('app.string.font_size'))
    assertEqual(JSON.parse(contentFont2).$attrs.contentFont.weight, 'FontWeight.Bolder')
    assertEqual(JSON.parse(contentFont2).$attrs.contentFont.family, 'Arial')
    assertEqual(JSON.parse(contentFont2).$attrs.contentFont.style, 'FontStyle.Normal')

    await button2.tap()
    let contentFont3: string = await menuItemContentFont1.getInspectorInfo()
    assertEqual(JSON.parse(contentFont3).$attrs.contentFont.weight, 'FontWeight.Bold')

    let contentFont4: string = await menuItemContentFont2.getInspectorInfo()
    assertEqual(JSON.parse(contentFont4).$attrs.contentFont.size, '30.00px')
    assertEqual(JSON.parse(contentFont4).$attrs.contentFont.weight, '200')
    assertEqual(JSON.parse(contentFont4).$attrs.contentFont.family, 'TESTFONTRawFile')
    assertEqual(JSON.parse(contentFont4).$attrs.contentFont.style, 'FontStyle.Italic')

    let contentFont5: string = await menuItemContentFont3.getInspectorInfo()
    assertEqual(JSON.parse(contentFont5).$attrs.contentFont.weight, 'FontWeight.Lighter')

    let contentFont6: string = await menuItemContentFont4.getInspectorInfo()
    assertEqual(JSON.parse(contentFont6).$attrs.contentFont.weight, 'FontWeight.Normal')

    let contentFont7: string = await menuItemContentFont5.getInspectorInfo()
    assertEqual(JSON.parse(contentFont7).$attrs.contentFont.weight, 'FontWeight.Regular')

    let contentFont8: string = await menuItemContentFont6.getInspectorInfo()
    assertEqual(JSON.parse(contentFont8).$attrs.contentFont.weight, 'FontWeight.Medium')
  }, 0)
}