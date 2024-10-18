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
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function swiperIndicatorTest() {
  /*
 * Swiper组件 Indicator属性
 * 找到画面id为swiperIndicator1，swiperIndicator2，swiperIndicator3，swiperIndicator4，swiperIndicator5的Swiper组件
 * 找到画面文本为SwiperIndicator1，SwiperIndicator2的Button组件
 * 获取swiperIndicator1的Indicator属性与期待值{itemWidth:'30.00px',itemHeight:'40.00px',selectedItemWidth:$r('sys.float.ohos_id_text_size_headline9'),selectedItemHeight:$r('sys.float.ohos_id_text_size_headline9'),mask:false,color: Color.Blue,selectedColor:Color.Pink}比对
 * 获取swiperIndicator2的Indicator属性与期待值{itemWidth:$r('sys.float.ohos_id_text_size_headline9'),itemHeight:$r('sys.float.ohos_id_text_size_headline9'),selectedItemWidth: $r('sys.float.ohos_id_text_size_headline9'),selectedItemHeight:$r('sys.float.ohos_id_text_size_headline9'),mask:false,color: $r('sys.color.ohos_id_icon_color_active_secondary'),selectedColor:$r('app.color.start_window_background')}比对
 * 获取swiperIndicator3的Indicator属性与期待值{itemWidth:3.00,itemHeight:3.00,selectedItemWidth: 4.00,selectedItemHeight:4.00,mask:true,color: 0x5d5d6c,selectedColor:0x5d5d3c}比对
 * 获取swiperIndicator4的Indicator属性与期待值{fontColor: $r('sys.color.ohos_id_navigation_group_color'),selectedFontColor:'sys.color.ohos_id_icon_color_active_secondary',digitFont.size:$r('sys.float.ohos_id_text_size_headline9')比对,digitFont.weight:10,selectedDigitFont.size:$r('sys.float.ohos_id_text_size_headline9'),selectedDigitFont.weight: 10}比对
 * 获取swiperIndicator5的Indicator属性与期待值{fontColor: Color.Gray,selectedFontColor:Color.Gray,digitFont.size:10.00,digitFont.weight: FontWeight.Bold,selectedDigitFont.size:10.00,selectedDigitFont.weight: FontWeight.Bold}比对
 * 获取swiperIndicator6的Indicator属性与期待值{fontColor:0x5d5d6c,selectedFontColor:0x5d5d6c,digitFont.size:5,digitFont.weight: 5,selectedDigitFont.size:6,selectedDigitFont.weight:6}比对
 * 点击button1，变更swiperIndicator3的Indicator属性{itemWidth:'23.00px',itemHeight:'23.00px',selectedItemWidth:'30.00px',selectedItemHeight:'30.00px',mask:true,color:'#125432',selectedColor:'#ff373dc3'}
 * 获取swiperIndicator3的Indicator属性与期待值{itemWidth:'23.00px',itemHeight:'23.00px',selectedItemWidth:'30.00px',selectedItemHeight:'30.00px',mask:true,color:'#125432',selectedColor:'#ff373dc3'}比对
 * 点击button2，变更swiperIndicator6的Indicator属性{itemWidth:'23.00px',itemHeight与:'23.00px',selectedItemWidth:'30.00px',selectedItemHeight与:'30.00px',mask:true,color:'#125432',selectedColor:'#ff373dc3'}
 * 获取swiperIndicator6的Indicator属性与期待值{itemWidth:'23.00px',itemHeight与:'23.00px',selectedItemWidth:'30.00px',selectedItemHeight与:'30.00px',mask:true,color:'#125432',selectedColor:'#ff373dc3'}比对
 */
  defineTest('swiperIndicatorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('swiperIndicatorTestDemo running')
    let driver: Tester = Tester.create()
    let swiper1: Component = await driver.findComponent(Matcher.create().id('swiperIndicator1').enabled(true))
    let swiper2: Component = await driver.findComponent(Matcher.create().id('swiperIndicator2').enabled(true))
    let swiper3: Component = await driver.findComponent(Matcher.create().id('swiperIndicator3').enabled(true))
    let swiper4: Component = await driver.findComponent(Matcher.create().id('swiperIndicator4').enabled(true))
    let swiper5: Component = await driver.findComponent(Matcher.create().id('swiperIndicator5').enabled(true))
    let swiper6: Component = await driver.findComponent(Matcher.create().id('swiperIndicator6').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SwiperIndicator1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('SwiperIndicator2').enabled(true))

    let indicator1: string = await swiper1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(indicator1).$attrs.indicator).itemWidth, '30.00px')
    assertEqual(JSON.parse(JSON.parse(indicator1).$attrs.indicator).itemHeight, '40.00px')
    assertEqual(JSON.parse(JSON.parse(indicator1).$attrs.indicator).selectedItemWidth,
      $r('sys.float.ohos_id_text_size_headline9'))
    assertEqual(JSON.parse(JSON.parse(indicator1).$attrs.indicator).selectedItemHeight,
      $r('sys.float.ohos_id_text_size_headline9'))
    assertFalse(JSON.parse(JSON.parse(indicator1).$attrs.indicator).mask)
    assertEqual(JSON.parse(JSON.parse(indicator1).$attrs.indicator).color.toLowerCase(), Color.Blue)
    assertEqual(JSON.parse(JSON.parse(indicator1).$attrs.indicator).selectedColor.toLowerCase(), Color.Pink)
    let indicator2: string = await swiper2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(indicator2).$attrs.indicator).itemWidth,
      $r('sys.float.ohos_id_text_size_headline9'))
    assertEqual(JSON.parse(JSON.parse(indicator2).$attrs.indicator).itemHeight,
      $r('sys.float.ohos_id_text_size_headline9'))
    assertEqual(JSON.parse(JSON.parse(indicator2).$attrs.indicator).selectedItemWidth,
      $r('sys.float.ohos_id_text_size_headline9'))
    assertEqual(JSON.parse(JSON.parse(indicator2).$attrs.indicator).selectedItemHeight,
      $r('sys.float.ohos_id_text_size_headline9'))
    assertFalse(JSON.parse(JSON.parse(indicator2).$attrs.indicator).mask)
    assertEqual(JSON.parse(JSON.parse(indicator2).$attrs.indicator).color,
      $r('sys.color.ohos_id_icon_color_active_secondary'))
    assertEqual(JSON.parse(JSON.parse(indicator2).$attrs.indicator).selectedColor,
      $r('app.color.start_window_background'))
    let indicator3: string = await swiper3.getInspectorInfo()
    assertEqual(JSON.parse(indicator3).$attrs.indicator.itemWidth, '3.00')
    assertEqual(JSON.parse(indicator3).$attrs.indicator.itemHeight, '3.00')
    assertEqual(JSON.parse(indicator3).$attrs.indicator.selectedItemWidth, '4.00')
    assertEqual(JSON.parse(indicator3).$attrs.indicator.selectedItemHeight, '4.00')
    assertTrue(JSON.parse(indicator3).$attrs.mask)
    assertEqual(JSON.parse(indicator3)
      .$attrs
      .indicator
      .color
      .toLowerCase(), 0x5d5d6c)
    assertEqual(JSON.parse(indicator3)
      .$attrs
      .indicator
      .selectedColor
      .toLowerCase(), 0x5d6d3c)
    let indicator4: string = await swiper4.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(indicator4).$attrs.indicator).fontColor,
      $r('sys.color.ohos_id_navigation_group_color'))
    assertEqual(JSON.parse(JSON.parse(indicator4).$attrs.indicator).selectedFontColor,
      'sys.color.ohos_id_icon_color_active_secondary')
    assertEqual(JSON.parse(JSON.parse(indicator4).$attrs.indicator).fontSize,
      $r('sys.float.ohos_id_text_size_headline9'))
    assertEqual(JSON.parse(JSON.parse(indicator4).$attrs.indicator).fontWeight, '10.00')
    assertEqual(JSON.parse(JSON.parse(indicator4).$attrs.indicator).selectedFontSize,
      $r('sys.float.ohos_id_text_size_headline9'))
    assertEqual(JSON.parse(JSON.parse(indicator4).$attrs.indicator).selectedFontWeight, '10.00')
    let indicator5: string = await swiper5.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(indicator5).$attrs.indicator).fontColor.toLowerCase(), Color.Gray)
    assertEqual(JSON.parse(JSON.parse(indicator5).$attrs.indicator).selectedFontColor.toLowerCase(), Color.Gray)
    assertEqual(JSON.parse(JSON.parse(indicator5).$attrs.indicator).fontSize, '10.00')
    assertEqual(JSON.parse(JSON.parse(indicator5).$attrs.indicator).fontWeight, 'FontWeight.Bold')
    assertEqual(JSON.parse(JSON.parse(indicator5).$attrs.indicator).selectedFontSize, '10.00')
    assertEqual(JSON.parse(JSON.parse(indicator5).$attrs.indicator).selectedFontWeight, 'FontWeight.Bold')
    let indicator6: string = await swiper6.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(indicator6).$attrs.indicator).fontColor.toLowerCase(), 0x5d5d6c)
    assertEqual(JSON.parse(JSON.parse(indicator6).$attrs.indicator).selectedFontColor.toLowerCase(), 0x5d6d3c)
    assertEqual(JSON.parse(JSON.parse(indicator6).$attrs.indicator).fontSize, '5.00')
    assertEqual(JSON.parse(JSON.parse(indicator6).$attrs.indicator).fontWeight, '5.00')
    assertEqual(JSON.parse(JSON.parse(indicator6).$attrs.indicator).selectedFontSize, '6.00')
    assertEqual(JSON.parse(JSON.parse(indicator6).$attrs.indicator).selectedFontWeight, '6.00')
    await button1.tap()
    let indicator7: string = await swiper3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(indicator7).$attrs.indicator).itemWidth, '23.00px')
    assertEqual(JSON.parse(JSON.parse(indicator7).$attrs.indicator).itemHeight, '23.00px')
    assertEqual(JSON.parse(JSON.parse(indicator7).$attrs.indicator).selectedItemWidth, '30.00px')
    assertEqual(JSON.parse(JSON.parse(indicator7).$attrs.indicator).selectedItemHeight, '30.00px')
    assertTrue(JSON.parse(JSON.parse(indicator7).$attrs.indicator).$attrs.mask)
    assertEqual(JSON.parse(JSON.parse(indicator7).$attrs.indicator).fontColor.toLowerCase(), '#125432')
    assertEqual(JSON.parse(JSON.parse(indicator7).$attrs.indicator).selectedColor.toLowerCase(), '#ff373dc3')
    await button2.tap()
    let indicator8: string = await swiper6.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(indicator6).$attrs.indicator).fontColor.toLowerCase(), '#ff26868f')
    assertEqual(JSON.parse(JSON.parse(indicator6).$attrs.indicator).selectedFontColor.toLowerCase(), '#ff9417a2')
    assertEqual(JSON.parse(JSON.parse(indicator8).$attrs.indicator).fontSize, '15.00px')
    assertEqual(JSON.parse(JSON.parse(indicator8).$attrs.indicator).fontWeight, '15.00px')
    assertEqual(JSON.parse(JSON.parse(indicator8).$attrs.indicator).selectedFontSize, '20.00px')
    assertEqual(JSON.parse(JSON.parse(indicator8).$attrs.indicator).selectedFontWeight, '20.00px')
  }, 0)
}