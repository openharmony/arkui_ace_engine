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

export default async function swiperPrevMarginTest() {
  /*
* Swiper组件 PrevMargin属性
* 找到画面id为swiperPrevMargin1，swiperPrevMargin2,swiperPrevMargin3,swiper的Swiper组件
* 找到画面文本为SwiperPrevMargin1的Button组件
* 获取swiperPrevMargin1的PrevMargin属性与期待值'10.00vp'比对
* 获取swiperPrevMargin2的PrevMargin属性与期待值$r('sys.float.ohos_id_text_size_headline9')比对
* 获取swiperPrevMargin3的PrevMargin属性与期待值'20.00vp'比对
* 点击button1，变更swiperPrevMargin1的PrevMargin属性值为'40.00px'
* 获取swiper3的PrevMargin属性与期待值'40.00px'比对
*/
  defineTest('swiperPrevMarginTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('swiperPrevMarginTestDemo running')
    let driver: Tester = Tester.create()
    let swiper1: Component = await driver.findComponent(Matcher.create().id('swiperPrevMargin1').enabled(true))
    let swiper2: Component = await driver.findComponent(Matcher.create().id('swiperPrevMargin2').enabled(true))
    let swiper3: Component = await driver.findComponent(Matcher.create().id('swiperPrevMargin3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SwiperPrevMargin1').enabled(true))
    let prevMargin1: string = await swiper1.getInspectorInfo()
    assertEqual(JSON.parse(prevMargin1).$attrs.prevMargin, '10.00vp')
    let prevMargin2: string = await swiper2.getInspectorInfo()
    assertEqual(JSON.parse(prevMargin2).$attrs.prevMargin, $r('sys.float.ohos_id_text_size_headline9'))
    let prevMargin3: string = await swiper3.getInspectorInfo()
    assertEqual(JSON.parse(prevMargin3).$attrs.prevMargin, '20.00vp')
    await button1.tap()
    let prevMargin4: string = await swiper3.getInspectorInfo()
    assertEqual(JSON.parse(prevMargin4).$attrs.prevMargin, '40.00px')
  }, 0)
}