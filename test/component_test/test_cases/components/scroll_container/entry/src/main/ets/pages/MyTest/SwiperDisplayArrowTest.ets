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
  loadComponentTestEntry,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

/*
* Swiper组件 DisplayArrow属性
* 找到画面id为swiperDisplayArrow1，swiperDisplayArrow2，swiperDisplayArrow3，swiperDisplayArrow4，swiperDisplayArrow5的Swiper组件
* 找到画面文本为SwiperDisplayArrow1，SwiperDisplayArrow2的Button组件
* 获取swiperDisplayArrow1的DisplayArrow属性{value:true,isHoverShow:true}比对
* 获取swiperDisplayArrow2的DisplayArrow属性{{showBackground:true,isSidebarMiddle:true,backgroundSize:$r('sys.float.ohos_id_text_size_headline9'),backgroundColor:$r('sys.color.ohos_id_video_control_bar_background_color'),arrowSize:13.50vp,arrowColor:$r('sys.color.ohos_id_popup_mask_color')}}比对
* 获取swiperDisplayArrow3的DisplayArrow属性{{showBackground:true,isSidebarMiddle:true,backgroundSize:'20px',backgroundColor:Color.Black,arrowSize:'15px',arrowColor:Color.Red},isHoverShow:false}比对
* 获取swiperDisplayArrow4的DisplayArrow属性{{showBackground:true,isSidebarMiddle:true,backgroundSize:'40.00px',backgroundColor:Color.Black,arrowSize:'30%',arrowColor:Color.Red},isHoverShow:false}比对
* 获取swiperDisplayArrow5的DisplayArrow属性{{showBackground:false,isSidebarMiddle:false,backgroundSize:'60px',backgroundColor:'#85345616',arrowSize:'70px',arrowColor:'#858e3ed4'},isHoverShow:false}比对
* 点击button1，变更swiper1的DisplayArrow属性value值为true,isHoverShow值为false
* 获取swiperDisplayArrow1的DisplayArrow属性{value:false,isHoverShow:false}比对
* 点击button2，变更swiperDisplayArrow5的DisplayArrow属性{{backgroundSize:24.00vp,backgroundColor:0xb573c0,arrowSize:25.00vp,arrowColor:0xb56873},isHoverShow:false}
* 获取swiperDisplayArrow5的DisplayArrow属性{{showBackground:false,isSidebarMiddle:false,backgroundSize:24,backgroundColor:ffff0000,arrowSize:25,arrowColor:#ff00ff00},isHoverShow:false}比对
*/
export default async function swiperDisplayArrowTest() {
  defineTest('swiperDisplayArrowTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('swiperDisplayArrowTestDemo running')
    let driver: Tester = Tester.create()
    let swiper1: Component = await driver.findComponent(Matcher.create().id('swiperDisplayArrow1').enabled(true))
    let swiper2: Component = await driver.findComponent(Matcher.create().id('swiperDisplayArrow2').enabled(true))
    let swiper3: Component = await driver.findComponent(Matcher.create().id('swiperDisplayArrow3').enabled(true))
    let swiper4: Component = await driver.findComponent(Matcher.create().id('swiperDisplayArrow4').enabled(true))
    let swiper5: Component = await driver.findComponent(Matcher.create().id('swiperDisplayArrow5').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SwiperDisplayArrow1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('SwiperDisplayArrow2').enabled(true))
    let displayArrow1: string = await swiper1.getInspectorInfo()
    assertTrue(JSON.parse(displayArrow1).$attrs.displayArrow)
    assertTrue(JSON.parse(displayArrow1).$attrs.hoverShow)
    let displayArrow2: string = await swiper2.getInspectorInfo()
    assertTrue(JSON.parse(displayArrow2).$attrs.showBackground)
    assertTrue(JSON.parse(displayArrow2).$attrs.isSidebarMiddle)
    assertEqual(JSON.parse(displayArrow2).$attrs.arrowBackgroundSize, $r('sys.float.ohos_id_text_size_headline9'))
    assertEqual(JSON.parse(displayArrow2).$attrs.arrowBackgroundColor,
      $r('sys.color.ohos_id_video_control_bar_background_color'))
    assertEqual(JSON.parse(displayArrow2).$attrs.arrowSize, '13.50vp')
    assertEqual(JSON.parse(displayArrow2).$attrs.arrowColor, $r('sys.color.ohos_id_popup_mask_color'))
    let displayArrow3: string = await swiper3.getInspectorInfo()
    assertTrue(JSON.parse(displayArrow3).$attrs.showBackground)
    assertTrue(JSON.parse(displayArrow3).$attrs.isSidebarMiddle)
    assertEqual(JSON.parse(displayArrow3).$attrs.arrowBackgroundSize, '20.00px')
    assertEqual(JSON.parse(displayArrow3).$attrs.arrowBackgroundColor.toLowerCase(), Color.Black)
    assertEqual(JSON.parse(displayArrow3).$attrs.arrowSize, '15.00px')
    assertEqual(JSON.parse(displayArrow3).$attrs.arrowColor.toLowerCase(), Color.Red)
    let displayArrow4: string = await swiper4.getInspectorInfo()
    assertTrue(JSON.parse(displayArrow4).$attrs.showBackground)
    assertTrue(JSON.parse(displayArrow4).$attrs.isSidebarMiddle)
    assertEqual(JSON.parse(displayArrow4).$attrs.arrowBackgroundSize, '32.00vp')
    assertEqual(JSON.parse(displayArrow4).$attrs.arrowBackgroundColor.toLowerCase(), Color.Black)
    assertEqual(JSON.parse(displayArrow4).$attrs.arrowSize, '24.00vp')
    assertEqual(JSON.parse(displayArrow4).$attrs.arrowColor.toLowerCase(), Color.Red)
    assertFalse(JSON.parse(displayArrow4).$attrs.hoverShow)
    let displayArrow5: string = await swiper5.getInspectorInfo()
    assertFalse(JSON.parse(displayArrow5).$attrs.showBackground)
    assertFalse(JSON.parse(displayArrow5).$attrs.isSidebarMiddle)
    assertEqual(JSON.parse(displayArrow5).$attrs.arrowBackgroundSize, '60.00px')
    assertEqual(JSON.parse(displayArrow5).$attrs.arrowBackgroundColor, '#85345616')
    assertEqual(JSON.parse(displayArrow5).$attrs.arrowSize, '70.00px')
    assertEqual(JSON.parse(displayArrow5).$attrs.arrowColor.toLowerCase(), '#858e3ed4')
    assertFalse(JSON.parse(displayArrow5).$attrs.hoverShow)
    await button1.tap()
    let displayArrow6: string = await swiper1.getInspectorInfo()
    assertFalse(JSON.parse(displayArrow6).$attrs.displayArrow)
    await button2.tap()
    let displayArrow7: string = await swiper5.getInspectorInfo()
    assertTrue(JSON.parse(displayArrow7).$attrs.showBackground)
    assertFalse(JSON.parse(displayArrow7).$attrs.isSidebarMiddle)
    assertEqual(JSON.parse(displayArrow7).$attrs.arrowBackgroundSize, '24.00vp')
    assertEqual(JSON.parse(displayArrow7).$attrs.arrowBackgroundColor.toLowerCase(), '#ffff0000')
    assertEqual(JSON.parse(displayArrow7).$attrs.arrowSize, '25.00vp')
    assertEqual(JSON.parse(displayArrow7).$attrs.arrowColor.toLowerCase(), '#ff00ff00')
    assertFalse(JSON.parse(displayArrow7).$attrs.hoverShow)
  }, 0)
}