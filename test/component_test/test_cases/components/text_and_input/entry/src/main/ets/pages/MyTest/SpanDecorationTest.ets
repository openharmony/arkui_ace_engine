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
} from '@ohos.arkui.componentTest';

export default async function spanDecorationTest() {
  /*
   * Span组件 Decoration属性
   * 找到画面id为spanDecoration1,spanDecoration2,spanDecoration3的Span组件
   * 找到画面文本为SpanDecoration的Button组件
   * 获取span1的Decoration属性decoration.type与期待值TextDecorationType.LineThrough比对
   * 获取span1的Decoration属性decoration.color与期待值Color.Red比对
   * 获取span2的Decoration属性decoration.type与期待值TextDecorationType.None比对
   * 获取span2的Decoration属性decoration.color与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
   * 获取span3的Decoration属性decoration.type与期待值TextDecorationType.Overline比对
   * 获取span3的Decoration属性decoration.color与期待值'rgb(255, 100, 255)'比对
   * 点击button，变更span3的Decoration属性decoration.type值为TextDecorationType.Underline
   * 变更span3的Decoration属性decoration.color值为0x0000FF
   * 获取span3的Decoration属性decoration.type与期待值TextDecorationType.Underline比对
   * 获取span3的Decoration属性decoration.color与期待值0x0000FF比对
   */
  defineTest('spanDecorationTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("spanDecorationTestDemo running")
    let driver: Tester = Tester.create()
    let span1: Component = await driver.findComponent(Matcher.create().id('spanDecoration1').enabled(true))
    let span2: Component = await driver.findComponent(Matcher.create().id('spanDecoration2').enabled(true))
    let span3: Component = await driver.findComponent(Matcher.create().id('spanDecoration3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SpanDecoration').enabled(true))

    assertFalse(span1 == null)
    let decoration1: string = await span1.getInspectorInfo()
    assertEqual(JSON.parse(decoration1).$attrs.decoration.type, TextDecorationType.LineThrough)
    assertEqual(JSON.parse(decoration1).$attrs.decoration.color, Color.Red)
    let decoration2: string = await span2.getInspectorInfo()
    assertEqual(JSON.parse(decoration2).$attrs.decoration.type, TextDecorationType.None)
    assertEqual(JSON.parse(decoration2).$attrs.decoration.color, $r('sys.color.ohos_id_color_text_hyperlink'))
    let decoration3: string = await span3.getInspectorInfo()
    assertEqual(JSON.parse(decoration3).$attrs.decoration.type, TextDecorationType.Overline)
    assertEqual(JSON.parse(decoration3).$attrs.decoration.color, 'rgb(255, 100, 255)')

    await button.tap()
    let decoration4: string = await span3.getInspectorInfo()
    assertEqual(JSON.parse(decoration4).$attrs.decoration.type, TextDecorationType.Underline)
    assertEqual(JSON.parse(decoration4).$attrs.decoration.color, 0x0000FF)
  }, 0)
}