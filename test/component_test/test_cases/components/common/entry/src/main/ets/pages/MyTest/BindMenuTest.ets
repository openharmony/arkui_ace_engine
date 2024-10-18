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
import { assertEqual, assertFalse, assertTrue } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function bindMenuTest() {
  /*
   * bindMenu属性
   * 找到id为 SymbolGlyphBindMenu1 SymbolGlyphBindMenu2 的SymbolGlyph组件
   * 找到文本为ButtonBindMenu 的 Button
   * 找到id为bindMenuText1 的 builder
   * 获取他的getText值与 'message' 比对
   * 获取SymbolGlyphBindMenu1 SymbolGlyphBindMenu2 的值
   * SymbolGlyphBindMenu1 bindMenu.content 与 false 比对
   * SymbolGlyphBindMenu1 bindMenu.value 与 'Menu1' 比对
   * SymbolGlyphBindMenu1 bindMenu.icon 与 $r('sys.symbol.ohos_lungs') 比对
   * SymbolGlyphBindMenu1 bindMenu.enabled 与 true 比对
   * SymbolGlyphBindMenu1 bindMenu.options.title 与 'hello' 比对
   * SymbolGlyphBindMenu1 bindMenu.options.showInSubWindow 与 false 比对
   * SymbolGlyphBindMenu2 bindMenu.value 与 'Menu2' 比对
   * SymbolGlyphBindMenu2 bindMenu.enabled 与 false 比对
   * 获取文本为 Menu1 的button
   * 点击切换 text 的值
   * text的值与 message比对
   * 点击button1 切换symbolGlyphBindMenu2的值
   * bindMenu.content 与 true 比对
   * bindMenu.enabled 与 false 比对
   * */
  defineTest('bindMenuTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("bindMenuTestDemo running")
    let driver: Tester = Tester.create()
    let symbolGlyphBindMenu1: Component =
      await driver.findComponent(Matcher.create().id('symbolGlyphBindMenu1').enabled(true))
    let symbolGlyphBindMenu2: Component =
      await driver.findComponent(Matcher.create().id('symbolGlyphBindMenu2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonBindMenu').enabled(true))
    let text1: Component = await driver.findComponent(Matcher.create().id('bindMenuText1').enabled(true))
    let textValue1: string = await text1.getText()
    assertEqual(textValue1, 'message')
    let bindMenu2: string = await symbolGlyphBindMenu1.getInspectorInfo()
    let bindMenu3: string = await symbolGlyphBindMenu2.getInspectorInfo()

    assertFalse(JSON.parse(bindMenu2).$attrs.bindMenu == undefined)
    assertFalse(JSON.parse(bindMenu2).$attrs.bindMenu.content)
    assertEqual(JSON.parse(bindMenu2).$attrs.bindMenu.value, 'Menu1')
    assertEqual(JSON.parse(bindMenu2).$attrs.bindMenu.icon, $r('sys.symbol.ohos_lungs'))
    assertTrue(JSON.parse(bindMenu2).$attrs.bindMenu.enabled)
    assertEqual(JSON.parse(bindMenu2)
      .$attrs
      .bindMenu
      .options
      .title, 'hello')
    assertFalse(JSON.parse(bindMenu2)
      .$attrs
      .bindMenu
      .options
      .showInSubWindow)
    assertEqual(JSON.parse(bindMenu3).$attrs.bindMenu.value, 'Menu2')
    assertFalse(JSON.parse(bindMenu3).$attrs.bindMenu.enabled)

    let button2: Component = await driver.findComponent(Matcher.create().text('Menu1').enabled(true))
    await button2.tap()
    let textValue2: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(textValue2).$attrs.text.value, 'message')

    await button1.tap()
    let bindMenu4: string = await symbolGlyphBindMenu2.getInspectorInfo()
    assertTrue(JSON.parse(bindMenu4).$attrs.bindMenu.content)
    assertFalse(JSON.parse(bindMenu4).$attrs.bindMenu.enabled)

    let textBindMenu1: Component = await driver.findComponent(Matcher.create().text('MenuBuilder').enabled(true))
    let bindMenu1: string = await textBindMenu1.getType()
    assertEqual(bindMenu1, 'MenuBuilderMenuBuilder')
  }, 0)
}