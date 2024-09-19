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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest';

export default async function textDecorationTest() {
  /*
   * Text组件 Decoration属性
   * 找到画面id为textDecoration1,textDecoration2的Text组件
   * 找到画面文本为TextDecoration1,TextDecoration2的Button组件
   * 获取text1的Decoration属性decoration.type与期待值TextDecorationType.None比对
   * 获取text1的Decoration属性decoration.color与期待值Color.Red比对
   * 获取text2的Decoration属性decoration.type与期待值TextDecorationType.Overline比对
   * 获取text2的Decoration属性decoration.color与期待值'#ff2a65dd'比对
   * 点击button1，变更text2的Decoration属性decoration.type值为TextDecorationType.Underline
   * 变更text2的Decoration属性decoration.color值为$r('sys.color.ohos_id_color_text_hyperlink')
   * 获取text2的Decoration属性decoration.type与期待值TextDecorationType.Underline比对
   * 获取text2的Decoration属性decoration.color与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
   * 点击button2，变更text2的Decoration属性decoration.type值为TextDecorationType.LineThrough
   * 变更text2的Decoration属性decoration.color值为0xffffff
   * 获取text2的Decoration属性decoration.type与期待值TextDecorationType.LineThrough比对
   * 获取text2的Decoration属性decoration.color与期待值0xffffff比对
   */
  defineTest('textDecorationTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textDecorationTestDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textDecoration1').enabled(true))
    let text2: Component = await driver.findComponent(Matcher.create().id('textDecoration2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextDecoration1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextDecoration2').enabled(true))

    let decoration1: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(decoration1).$attrs.decoration,
      '{"type":"TextDecorationType.None","color":"#FFFF0000","style":"TextDecorationStyle.SOLID"}')
    let decoration2: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(decoration2).$attrs.decoration,
      '{"type":"TextDecorationType.Overline","color":"#FF2A65DD","style":"TextDecorationStyle.SOLID"}')

    await button1.tap()
    let decoration3: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(decoration3).$attrs.decoration,
      '{"type":"TextDecorationType.Underline","color":"#FF007DFF","style":"TextDecorationStyle.SOLID"}')

    await button2.tap()
    let decoration4: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(decoration4).$attrs.decoration,
      '{"type":"TextDecorationType.LineThrough","color":"#FFFFFFFF","style":"TextDecorationStyle.SOLID"}')
  }, 0)
}