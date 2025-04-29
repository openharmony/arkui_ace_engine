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
import { assertEqual, assertFalse } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function spanTextBackgroundStyleTest() {
  /*
   * Span组件 TextBackgroundStyle属性
   * 找到画面id为spanTextBackgroundStyle1,spanTextBackgroundStyle2,spanTextBackgroundStyle3的Span组件
   * 找到画面文本为SpanTextBackgroundStyle1,SpanTextBackgroundStyle2,SpanTextBackgroundStyle3的Button组件
   * 获取span1的TextBackgroundStyle属性与期待值{radius:'10px',color:Color.Green}比对
   * 获取span2的TextBackgroundStyle属性与期待值{ radius:'50vp',color:0xFF1493 }比对
   * 点击button1，变更span2的TextBackgroundStyle属性值为{radius:'10fp',color:'#7FFFD4'}
   * 获取span2的TextBackgroundStyle属性与期待值{radius:'10fp',color:'#7FFFD4'}比对
   * 点击button2，变更span2的TextBackgroundStyle属性值为{radius:'40lpx',color:$r('sys.color.ohos_id_color_text_hyperlink')}
   * 获取span2的TextBackgroundStyle属性与期待值{radius:'40lpx',color:$r('sys.color.ohos_id_color_text_hyperlink')}比对
   * 获取span3的TextBackgroundStyle属性与期待值{ radius:'50%',color:0x7FFF00}比对
   * 点击button3，变更span3的TextBackgroundStyle属性值为{ radius:$r('app.string.length'),color:0x7FFF00}
   * 获取span3的TextBackgroundStyle属性与期待值{ radius:$r('app.string.length'),color:0x7FFF00}比对
   * 点击button3，变更span3的TextBackgroundStyle属性值为{radius:{topLeft:10,topRight:10,bottomLeft:20,bottomRight:20},color:0x7FFF00}
   * 获取span3的TextBackgroundStyle属性与期待值{radius:{topLeft:10,topRight:10,bottomLeft:20,bottomRight:20},color:0x7FFF00}比对
   * 点击button3，变更span3的TextBackgroundStyle属性值为{radius:{topLeft:'10px',topRight:'10px',bottomLeft:'20px',bottomRight:'20px'},color:0x7FFF00}
   * 获取span3的TextBackgroundStyle属性与期待值{radius:{topLeft:'10px',topRight:'10px',bottomLeft:'20px',bottomRight:'20px'},color:0x7FFF00}比对
   * 点击button3，变更span3的TextBackgroundStyle属性值为{radius:{topLeft:'10px',topRight:'10px',bottomLeft:'20px',bottomRight:'20px'},color:0x7FFF00}
   * 获取span3的TextBackgroundStyle属性与期待值{radius:{topLeft:'10px',topRight:'10px',bottomLeft:'20px',bottomRight:'20px'},color:0x7FFF00}比对
   * 点击button3，变更span3的TextBackgroundStyle属性值为{radius:{topLeft:$r('app.string.length'),topRight:$r('app.string.length'),bottomLeft:$r('app.string.length'), bottomRight:$r('app.string.length')},color:0x7FFF00}
   * 获取span3的TextBackgroundStyle属性与期待值{radius:{topLeft:$r('app.string.length'),topRight:$r('app.string.length'),bottomLeft:$r('app.string.length'), bottomRight:$r('app.string.length')},color:0x7FFF00}比对
   */
  defineTest('spanTextBackgroundStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("spanTextBackgroundStyleTestDemo running")
    let driver: Tester = Tester.create()
    let span1: Component = await driver.findComponent(Matcher.create().id('spanTextBackgroundStyle1').enabled(true))
    let span2: Component = await driver.findComponent(Matcher.create().id('spanTextBackgroundStyle2').enabled(true))
    let span3: Component = await driver.findComponent(Matcher.create().id('spanTextBackgroundStyle3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SpanTextBackgroundStyle1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('SpanTextBackgroundStyle2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('SpanTextBackgroundStyle3').enabled(true))

    assertFalse(span1 == null)
    let textBackgroundStyle1: string = await span1.getInspectorInfo()
    assertEqual(JSON.parse(textBackgroundStyle1).$attrs.textBackgroundStyle.radius, '10px')
    assertEqual(JSON.parse(textBackgroundStyle1).$attrs.textBackgroundStyle.color, Color.Green)
    let textBackgroundStyle2: string = await span2.getInspectorInfo()
    assertEqual(JSON.parse(textBackgroundStyle2).$attrs.textBackgroundStyle.radius, '50vp')
    assertEqual(JSON.parse(textBackgroundStyle2).$attrs.textBackgroundStyle.color, 0xFF1493)
    let textBackgroundStyle3: string = await span3.getInspectorInfo()
    assertEqual(JSON.parse(textBackgroundStyle3).$attrs.textBackgroundStyle.radius, '50%')
    assertEqual(JSON.parse(textBackgroundStyle3).$attrs.textBackgroundStyle.color, 0x7FFF00)


    await button1.tap()
    let textBackgroundStyle4: string = await span2.getInspectorInfo()
    assertEqual(JSON.parse(textBackgroundStyle4).$attrs.textBackgroundStyle.radius, '10fp')
    assertEqual(JSON.parse(textBackgroundStyle4).$attrs.textBackgroundStyle.color, '#7FFFD4')
    await button2.tap()
    let textBackgroundStyle5: string = await span2.getInspectorInfo()
    assertEqual(JSON.parse(textBackgroundStyle5).$attrs.textBackgroundStyle.radius, '40lpx')
    assertEqual(JSON.parse(textBackgroundStyle5).$attrs.textBackgroundStyle.color,
      $r('sys.color.ohos_id_color_text_hyperlink'))
    await button3.tap()
    let textBackgroundStyle6: string = await span3.getInspectorInfo()
    assertEqual(JSON.parse(textBackgroundStyle6).$attrs.textBackgroundStyle.radius, $r('app.string.length'))
    await button3.tap()
    let textBackgroundStyle7: string = await span3.getInspectorInfo()
    assertEqual(JSON.parse(textBackgroundStyle7).$attrs.textBackgroundStyle.radius, {
      topLeft: 10,
      topRight: 10,
      bottomLeft: 20,
      bottomRight: 20
    })
    await button3.tap()
    let textBackgroundStyle8: string = await span3.getInspectorInfo()
    assertEqual(JSON.parse(textBackgroundStyle8).$attrs.textBackgroundStyle.radius, {
      topLeft: '10px',
      topRight: '10px',
      bottomLeft: '20px',
      bottomRight: '20px'
    })
    await button3.tap()
    let textBackgroundStyle9: string = await span3.getInspectorInfo()
    assertEqual(JSON.parse(textBackgroundStyle9).$attrs.textBackgroundStyle.radius, {
      topLeft: $r('app.string.length'),
      topRight: $r('app.string.length'),
      bottomLeft: $r('app.string.length'),
      bottomRight: $r('app.string.length')
    })
  }, 0)
}