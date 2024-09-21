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

export default async function swiperItemSpaceTest() {
  /*
* Swiper组件 ItemSpace属性
* 找到画面id为swiperItemSpace1,swiperItemSpace2的Swiper组件
* 找到画面文本为SwiperItemSpace1的Button组件
* 获取swiperItemSpace1的ItemSpace属性与期待值'20.00%'比对
* 获取swiperItemSpace2的ItemSpace属性与期待值'2.00vp'比对
* 点击button1，变更swiperItemSpace2的ItemSpace属性值为'15.00px'
* 获取swiperItemSpace2的ItemSpace属性与期待值'15.00px'比对
*/
  defineTest('swiperItemSpaceTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('swiperItemSpaceTestDemo running')
    let driver: Tester = Tester.create()
    let swiper1: Component = await driver.findComponent(Matcher.create().id('swiperItemSpace1').enabled(true))
    let swiper2: Component = await driver.findComponent(Matcher.create().id('swiperItemSpace2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SwiperItemSpace1').enabled(true))
    let itemSpace1: string = await swiper1.getInspectorInfo()
    assertEqual(JSON.parse(itemSpace1).$attrs.itemSpace, "20.00%")
    let itemSpace2: string = await swiper2.getInspectorInfo()
    assertEqual(JSON.parse(itemSpace2).$attrs.itemSpace, '2.00vp')
    await button1.tap()
    let itemSpace3: string = await swiper2.getInspectorInfo()
    assertEqual(JSON.parse(itemSpace3).$attrs.itemSpace, '15.00px')
  }, 0)
}