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

export default async function imageSpanTextBackgroundStyleTest() {
  /*
   * ImageSpan组件 TextBackgroundStyle属性
   * 找到画面id为ImageSpanTextBackgroundStyle1,ImageSpanTextBackgroundStyle2,ImageSpanTextBackgroundStyle3的ImageSpan组件
   * 找到画面文本为ImageSpanTextBackgroundStyle1,ImageSpanTextBackgroundStyle2,ImageSpanTextBackgroundStyle3的Button组件
   * 获取ImageSpan1的TextBackgroundStyle属性与期待值{radius:'10px',color:Color.Green}比对
   * 获取ImageSpan2的TextBackgroundStyle属性与期待值{ radius:'50vp',color:0xFF1493 }比对
   * 点击button1，变更ImageSpan2的TextBackgroundStyle属性值为{radius:'10fp',color:'#7FFFD4'}
   * 获取ImageSpan2的TextBackgroundStyle属性与期待值{radius:'10fp',color:'#7FFFD4'}比对
   * 点击button2，变更ImageSpan2的TextBackgroundStyle属性值为{radius:'40lpx',color:$r('sys.color.ohos_id_color_text_hyperlink')}
   * 获取ImageSpan2的TextBackgroundStyle属性与期待值{radius:'40lpx',color:$r('sys.color.ohos_id_color_text_hyperlink')}比对
   * 获取ImageSpan3的TextBackgroundStyle属性与期待值{ radius:'50%',color:0x7FFF00}比对
   * 点击button3，变更ImageSpan3的TextBackgroundStyle属性值为{ radius:$r('app.string.length'),color:0x7FFF00}
   * 获取ImageSpan3的TextBackgroundStyle属性与期待值{ radius:$r('app.string.length'),color:0x7FFF00}比对
   * 点击button3，变更ImageSpan3的TextBackgroundStyle属性值为{radius:{topLeft:10,topRight:10,bottomLeft:20,bottomRight:20},color:0x7FFF00}
   * 获取ImageSpan3的TextBackgroundStyle属性与期待值{radius:{topLeft:10,topRight:10,bottomLeft:20,bottomRight:20},color:0x7FFF00}比对
   * 点击button3，变更ImageSpan3的TextBackgroundStyle属性值为{radius:{topLeft:'10px',topRight:'10px',bottomLeft:'20px',bottomRight:'20px'},color:0x7FFF00}
   * 获取ImageSpan3的TextBackgroundStyle属性与期待值{radius:{topLeft:'10px',topRight:'10px',bottomLeft:'20px',bottomRight:'20px'},color:0x7FFF00}比对
   * 点击button3，变更ImageSpan3的TextBackgroundStyle属性值为{radius:{topLeft:'10px',topRight:'10px',bottomLeft:'20px',bottomRight:'20px'},color:0x7FFF00}
   * 获取ImageSpan3的TextBackgroundStyle属性与期待值{radius:{topLeft:'10px',topRight:'10px',bottomLeft:'20px',bottomRight:'20px'},color:0x7FFF00}比对
   * 点击button3，变更ImageSpan3的TextBackgroundStyle属性值为{radius:{topLeft:$r('app.string.length'),topRight:$r('app.string.length'),bottomLeft:$r('app.string.length'), bottomRight:$r('app.string.length')},color:0x7FFF00}
   * 获取ImageSpan3的TextBackgroundStyle属性与期待值{radius:{topLeft:$r('app.string.length'),topRight:$r('app.string.length'),bottomLeft:$r('app.string.length'), bottomRight:$r('app.string.length')},color:0x7FFF00}比对
   */
  defineTest('imageSpanTextBackgroundStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageSpanTextBackgroundStyleTestDemo running")
    let driver: Tester = Tester.create()
    let ImageSpan1: Component =
      await driver.findComponent(Matcher.create().id('imageSpanTextBackgroundStyle1').enabled(true))
    let ImageSpan2: Component =
      await driver.findComponent(Matcher.create().id('imageSpanTextBackgroundStyle2').enabled(true))
    let ImageSpan3: Component =
      await driver.findComponent(Matcher.create().id('imageSpanTextBackgroundStyle3').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('ImageSpanTextBackgroundStyle1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('ImageSpanTextBackgroundStyle2').enabled(true))
    let button3: Component =
      await driver.findComponent(Matcher.create().text('ImageSpanTextBackgroundStyle3').enabled(true))

    let textBackgroundStyle1: string = await ImageSpan1.getInspectorInfo()
    assertEqual(JSON.parse(textBackgroundStyle1).$attrs.textBackgroundStyle.radius, '10.00px')
    assertEqual(JSON.parse(textBackgroundStyle1)
      .$attrs
      .textBackgroundStyle
      .color
      .toLowerCase(), Color.Green)

    let textBackgroundStyle2: string = await ImageSpan2.getInspectorInfo()
    assertEqual(JSON.parse(textBackgroundStyle2).$attrs.textBackgroundStyle.radius, '50.00vp')
    assertEqual(JSON.parse(textBackgroundStyle2).$attrs.textBackgroundStyle.color, '#FFFF1493')

    let textBackgroundStyle3: string = await ImageSpan3.getInspectorInfo()
    assertEqual(JSON.parse(textBackgroundStyle3).$attrs.textBackgroundStyle.radius, '0.00px')
    assertEqual(JSON.parse(textBackgroundStyle3).$attrs.textBackgroundStyle.color, '#FF7FFF00')

    await button1.tap()
    let textBackgroundStyle4: string = await ImageSpan2.getInspectorInfo()
    assertEqual(JSON.parse(textBackgroundStyle4).$attrs.textBackgroundStyle.radius, '10.00fp')
    assertEqual(JSON.parse(textBackgroundStyle4).$attrs.textBackgroundStyle.color, '#FF7FFFD4')
    await button2.tap()
    let textBackgroundStyle5: string = await ImageSpan2.getInspectorInfo()
    assertEqual(JSON.parse(textBackgroundStyle5).$attrs.textBackgroundStyle.radius, '40.00lpx')
    assertEqual(JSON.parse(textBackgroundStyle5).$attrs.textBackgroundStyle.color,
      '#FF007DFF')
    await button3.tap()
    let textBackgroundStyle6: string = await ImageSpan3.getInspectorInfo()
    assertEqual(JSON.parse(textBackgroundStyle6).$attrs.textBackgroundStyle.radius, '10.00vp')
    await button3.tap()
    let textBackgroundStyle7: string = await ImageSpan3.getInspectorInfo()
    assertEqual(JSON.parse(textBackgroundStyle7)
      .$attrs
      .textBackgroundStyle
      .radius
      .topLeft, '10.00vp')
    assertEqual(JSON.parse(textBackgroundStyle7)
      .$attrs
      .textBackgroundStyle
      .radius
      .topRight, '10.00vp')
    assertEqual(JSON.parse(textBackgroundStyle7)
      .$attrs
      .textBackgroundStyle
      .radius
      .bottomLeft, '20.00vp')
    assertEqual(JSON.parse(textBackgroundStyle7)
      .$attrs
      .textBackgroundStyle
      .radius
      .bottomRight, '20.00vp')
    await button3.tap()
    let textBackgroundStyle8: string = await ImageSpan3.getInspectorInfo()
    assertEqual(JSON.parse(textBackgroundStyle8)
      .$attrs
      .textBackgroundStyle
      .radius
      .topLeft, '10.00px')
    assertEqual(JSON.parse(textBackgroundStyle8)
      .$attrs
      .textBackgroundStyle
      .radius
      .topRight, '10.00px')
    assertEqual(JSON.parse(textBackgroundStyle8)
      .$attrs
      .textBackgroundStyle
      .radius
      .bottomLeft, '20.00px')
    assertEqual(JSON.parse(textBackgroundStyle8)
      .$attrs
      .textBackgroundStyle
      .radius
      .bottomRight, '20.00px')

    await button3.tap()
    let textBackgroundStyle9: string = await ImageSpan3.getInspectorInfo()
    assertEqual(JSON.parse(textBackgroundStyle9)
      .$attrs
      .textBackgroundStyle
      .radius
      .topLeft, $r('app.string.vp_length'))
    assertEqual(JSON.parse(textBackgroundStyle9)
      .$attrs
      .textBackgroundStyle
      .radius
      .topRight, $r('app.string.vp_length'))
    assertEqual(JSON.parse(textBackgroundStyle9)
      .$attrs
      .textBackgroundStyle
      .radius
      .bottomLeft, $r('app.string.vp_length'))
    assertEqual(JSON.parse(textBackgroundStyle9)
      .$attrs
      .textBackgroundStyle
      .radius
      .bottomRight, $r('app.string.vp_length'))
  }, 0)
}