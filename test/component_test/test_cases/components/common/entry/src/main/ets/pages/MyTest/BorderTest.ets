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
import { assertEqual } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function borderTest() {
  /*
  * 使用TextInput、Menu组件 Row容器 Border属性
  * 找到画面id为rowBorder1,textInputBorder,rowBorder2,menuBorder的row,textInput,menu组件
  * 找到画面文本为ButtonBorder的Button组件
  * 获取rowBorder1的Border属性与期待值
  * { width: 10, color: Color.Black, radius: 30, style: BorderStyle.Solid }比对
  * 获取textInputBorder的Border属性与期待值
  * { width: $r('app.string.common_width'),color: $r('sys.color.ohos_id_color_button_normal'),
  * radius: $r('app.string.common_radius'),style: BorderStyle.Dashed }比对
  * 获取rowBorder2的Border属性与期待值
  * {width: { left: 3, right: 6, top: 10, bottom: 15 }, color: { left: 0x0000ff, right: 0xff0000,
  * top: 0x00ff00, bottom: 0x0000ff }, radius: { topLeft: 10, topRight: 20, bottomLeft: 40, bottomRight: 80 },
  * style: { left: BorderStyle.Dotted, right: BorderStyle.Dotted, top: BorderStyle.Solid, bottom: BorderStyle.Dashed } }比对
  * 获取menuBorder的Border属性与期待值
  * {width: { left: $r('app.string.commonPosition_length'), right: $r('app.string.commonPosition_length'),
  * top: $r('app.string.commonPosition_length'), bottom: $r('app.string.commonPosition_length') },
  * color: {left: $r('sys.color.ohos_id_radio_shadow_color'),right: $r('sys.color.ohos_toggle_bg_transparent'),
  * top: $r('sys.color.ohos_id_toolbar_item_focus_color'),bottom: $r('sys.color.ohos_fa_emphasize_outline')
  * radius: {topLeft: $r('app.string.commonPosition_length'),topRight: $r('app.string.commonPosition_length'),
  * bottomLeft: $r('app.string.commonPosition_length'),bottomRight: $r('app.string.commonPosition_length')},
  * style: {left: BorderStyle.Dotted,right: BorderStyle.Dotted,top: BorderStyle.Solid,bottom: BorderStyle.Dashed} }比对
  * 点击button，变更rowBorder1的Border属性值与期待值
  * { width: '10px', color: '#e3bbbb', radius: '50px', style: BorderStyle.Dotted }比对
  * 点击button，变更rowBorder1的Border属性值与期待值
  * { width: { left: '10px', right: '20px', top: '30px', bottom: '40px' },
  * color: { left: '#e3bbbb', right: '#ff0000', top: '#00ff00', bottom: '#0000ff' },
  * radius: { topLeft: '50px', topRight: '70px', bottomLeft: '90px', bottomRight: '110px' },
  * style: {left: BorderStyle.Dotted,right: BorderStyle.Dotted,top: BorderStyle.Solid,bottom: BorderStyle.Dashed}}比对
  */
  defineTest('borderTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('borderTestDemo running')
    let driver: Tester = Tester.create()
    let rowBorder1: Component = await driver.findComponent(Matcher.create().id('rowBorder1').enabled(true))
    let rowBorder2: Component = await driver.findComponent(Matcher.create().id('rowBorder2').enabled(true))
    let menuBorder: Component = await driver.findComponent(Matcher.create().id('menuBorder').enabled(true))
    let textInputBorder: Component = await driver.findComponent(Matcher.create().id('textInputBorder').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonBorder').enabled(true))

    let border1: string = await rowBorder1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(border1).$attrs.border).width, '10.00vp')
    assertEqual(JSON.parse(JSON.parse(border1).$attrs.border).color.toLowerCase(), Color.Black)
    assertEqual(JSON.parse(JSON.parse(border1).$attrs.border).radius, '30.00vp')
    assertEqual(JSON.parse(JSON.parse(border1).$attrs.border).style, 'BorderStyle.Solid')

    let border2: string = await textInputBorder.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(border2).$attrs.border).width, $r('app.string.common_width'))
    assertEqual(JSON.parse(JSON.parse(border2).$attrs.border).color, $r('sys.color.ohos_id_color_button_normal'))
    assertEqual(JSON.parse(JSON.parse(border2).$attrs.border).radius, $r('app.string.common_width'))
    assertEqual(JSON.parse(JSON.parse(border2).$attrs.border).style, 'BorderStyle.Dashed')

    let border3: string = await rowBorder2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(border3).$attrs.border).width.left, '3.00vp')
    assertEqual(JSON.parse(JSON.parse(border3).$attrs.border).width.right, '6.00vp')
    assertEqual(JSON.parse(JSON.parse(border3).$attrs.border).width.top, '10.00vp')
    assertEqual(JSON.parse(JSON.parse(border3).$attrs.border).width.bottom, '15.00vp')
    assertEqual(JSON.parse(JSON.parse(border3).$attrs.border).color.left, '#FF0000FF')
    assertEqual(JSON.parse(JSON.parse(border3).$attrs.border).color.right, '#FFFF0000')
    assertEqual(JSON.parse(JSON.parse(border3).$attrs.border).color.top, '#FF00FF00')
    assertEqual(JSON.parse(JSON.parse(border3).$attrs.border).color.bottom, '#FF0000FF')
    assertEqual(JSON.parse(JSON.parse(border3).$attrs.border).radius.topLeft, '10.00vp')
    assertEqual(JSON.parse(JSON.parse(border3).$attrs.border).radius.topRight, '20.00vp')
    assertEqual(JSON.parse(JSON.parse(border3).$attrs.border).radius.bottomLeft, '40.00vp')
    assertEqual(JSON.parse(JSON.parse(border3).$attrs.border).radius.bottomRight, '80.00vp')
    assertEqual(JSON.parse(JSON.parse(border3).$attrs.border).style.left, 'BorderStyle.Dotted')
    assertEqual(JSON.parse(JSON.parse(border3).$attrs.border).style.right, 'BorderStyle.Dotted')
    assertEqual(JSON.parse(JSON.parse(border3).$attrs.border).style.top, 'BorderStyle.Solid')
    assertEqual(JSON.parse(JSON.parse(border3).$attrs.border).style.bottom, 'BorderStyle.Dashed')

    let border4: string = await menuBorder.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(border4).$attrs.border).width.left, $r('app.string.common_width'))
    assertEqual(JSON.parse(JSON.parse(border4).$attrs.border).width.right, $r('app.string.common_width'))
    assertEqual(JSON.parse(JSON.parse(border4).$attrs.border).width.top, $r('app.string.common_width'))
    assertEqual(JSON.parse(JSON.parse(border4).$attrs.border).width.bottom, $r('app.string.common_width'))
    assertEqual(JSON.parse(JSON.parse(border4).$attrs.border).color.left, $r('sys.color.ohos_id_radio_shadow_color'))
    assertEqual(JSON.parse(JSON.parse(border4).$attrs.border).color.right, $r('sys.color.ohos_toggle_bg_transparent'))
    assertEqual(JSON.parse(JSON.parse(border4).$attrs.border).color.top,
      $r('sys.color.ohos_id_toolbar_item_focus_color'))
    assertEqual(JSON.parse(JSON.parse(border4).$attrs.border).color.bottom, $r('sys.color.ohos_fa_emphasize_outline'))
    assertEqual(JSON.parse(JSON.parse(border4).$attrs.border).radius.topLeft, $r('app.string.commonPosition_length'))
    assertEqual(JSON.parse(JSON.parse(border4).$attrs.border).radius.topRight, $r('app.string.commonPosition_length'))
    assertEqual(JSON.parse(JSON.parse(border4).$attrs.border).radius.bottomLeft, $r('app.string.commonPosition_length'))
    assertEqual(JSON.parse(JSON.parse(border4).$attrs.border).radius.bottomRight,
      $r('app.string.commonPosition_length'))
    assertEqual(JSON.parse(JSON.parse(border4).$attrs.border).style.left, 'BorderStyle.Dotted')
    assertEqual(JSON.parse(JSON.parse(border4).$attrs.border).style.right, 'BorderStyle.Dotted')
    assertEqual(JSON.parse(JSON.parse(border4).$attrs.border).style.top, 'BorderStyle.Solid')
    assertEqual(JSON.parse(JSON.parse(border4).$attrs.border).style.bottom, 'BorderStyle.Dashed')

    await button.tap()
    let border5: string = await rowBorder1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(border5).$attrs.border).width, '10.00px')
    assertEqual(JSON.parse(JSON.parse(border5).$attrs.border).color, '#FFE3BBBB')
    assertEqual(JSON.parse(JSON.parse(border5).$attrs.border).radius, '50.00px')
    assertEqual(JSON.parse(JSON.parse(border5).$attrs.border).style, 'BorderStyle.Dotted')

    await button.tap()
    let border6: string = await rowBorder1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(border6).$attrs.border).width.left, '10.00px')
    assertEqual(JSON.parse(JSON.parse(border6).$attrs.border).width.right, '20.00px')
    assertEqual(JSON.parse(JSON.parse(border6).$attrs.border).width.top, '30.00px')
    assertEqual(JSON.parse(JSON.parse(border6).$attrs.border).width.bottom, '40.00px')
    assertEqual(JSON.parse(JSON.parse(border6).$attrs.border).color.left, '#FFE3BBBB')
    assertEqual(JSON.parse(JSON.parse(border6).$attrs.border).color.right, '#FFFF0000')
    assertEqual(JSON.parse(JSON.parse(border6).$attrs.border).color.top, '#FF00FF00')
    assertEqual(JSON.parse(JSON.parse(border6).$attrs.border).color.bottom, '#FF0000FF')
    assertEqual(JSON.parse(JSON.parse(border6).$attrs.border).radius.topLeft, '50.00px')
    assertEqual(JSON.parse(JSON.parse(border6).$attrs.border).radius.topRight, '70.00px')
    assertEqual(JSON.parse(JSON.parse(border6).$attrs.border).radius.bottomLeft, '90.00px')
    assertEqual(JSON.parse(JSON.parse(border6).$attrs.border).radius.bottomRight, '110.00px')
    assertEqual(JSON.parse(JSON.parse(border6).$attrs.border).style.left, 'BorderStyle.Dotted')
    assertEqual(JSON.parse(JSON.parse(border6).$attrs.border).style.right, 'BorderStyle.Dotted')
    assertEqual(JSON.parse(JSON.parse(border6).$attrs.border).style.top, 'BorderStyle.Solid')
    assertEqual(JSON.parse(JSON.parse(border6).$attrs.border).style.bottom, 'BorderStyle.Dashed')
  }, 0)
}