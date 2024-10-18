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

export default async function menuFontTest() {
  /*
* Menu组件 Font属性
* 找到画面id为menuFont1、 menuFont2、 menuFont3、 menuFont4、 menuFont5、 menuFont6的Menu组件
* 找到画面文本为MenuFont1、 MenuFont2的Button组件
* 获取menu1的Font属性与期待值{ size: '20.00fp', weight: 400, family: "Arial", style: FontStyle.Normal }比对
* 点击button1，变更menu1的Font属性值为{ size: "70px", weight: "16px", family: 'TESTFONTRawFile', style: FontStyle.Italic }
* 获取menu2的Font属性与期待值{ size: "70.00px", weight: "16.00px", family: 'TESTFONTRawFile', style: FontStyle.Italic }比对
* 点击button2，变更menu1的Font属性的weight值为FontWeight.Bolder
* 获取menu1的Font属性的weight值与期待值FontWeight.Bolder比对
* 获取menu2的Font属性与期待值{ size: $r('app.string.length'), weight: FontWeight.Lighter }比对
* 获取menu3的Font属性的weight值与期待值FontWeight.Normal比对
* 获取menu4的Font属性的weight值与期待值FontWeight.Regular比对
* 获取menu5的Font属性的weight值与期待值FontWeight.Medium比对
* 获取menu6的Font属性的weight值与期待值FontWeight.Bold比对
*/
  defineTest('menuFontTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('menuFontTestDemo running')
    let driver: Tester = Tester.create()
    let menu1: Component = await driver.findComponent(Matcher.create().id('menuFont1').enabled(true))
    let menu2: Component = await driver.findComponent(Matcher.create().id('menuFont2').enabled(true))
    let menu3: Component = await driver.findComponent(Matcher.create().id('menuFont3').enabled(true))
    let menu4: Component = await driver.findComponent(Matcher.create().id('menuFont4').enabled(true))
    let menu5: Component = await driver.findComponent(Matcher.create().id('menuFont5').enabled(true))
    let menu6: Component = await driver.findComponent(Matcher.create().id('menuFont6').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('MenuFont1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('MenuFont2').enabled(true))

    let font1: string = await menu1.getInspectorInfo()
    assertEqual(JSON.parse(font1).$attrs.font.size, '20.00fp')
    assertEqual(JSON.parse(font1).$attrs.font.weight, '400')
    assertEqual(JSON.parse(font1).$attrs.font.family, "Arial")
    assertEqual(JSON.parse(font1).$attrs.font.style, 'FontStyle.Normal')
    await button1.tap()
    let font2: string = await menu1.getInspectorInfo()
    assertEqual(JSON.parse(font2).$attrs.font.size, '70.00px')
    assertEqual(JSON.parse(font2).$attrs.font.weight, '200')
    assertEqual(JSON.parse(font2).$attrs.font.family, 'TESTFONTRawFile')
    assertEqual(JSON.parse(font2).$attrs.font.style, 'FontStyle.Italic')
    await button2.tap()
    let font3: string = await menu1.getInspectorInfo()
    assertEqual(JSON.parse(font3).$attrs.font.weight, 'FontWeight.Bolder')

    let font4: string = await menu2.getInspectorInfo()
    assertEqual(JSON.parse(font4).$attrs.font.size, $r('app.string.font_size'))
    assertEqual(JSON.parse(font4).$attrs.font.weight, 'FontWeight.Lighter')

    let font5: string = await menu3.getInspectorInfo()
    assertEqual(JSON.parse(font5).$attrs.font.weight, 'FontWeight.Normal')

    let font6: string = await menu4.getInspectorInfo()
    assertEqual(JSON.parse(font6).$attrs.font.weight, 'FontWeight.Regular')

    let font7: string = await menu5.getInspectorInfo()
    assertEqual(JSON.parse(font7).$attrs.font.weight, 'FontWeight.Medium')

    let font8: string = await menu6.getInspectorInfo()
    assertEqual(JSON.parse(font8).$attrs.font.weight, 'FontWeight.Bold')
  }, 0)
}