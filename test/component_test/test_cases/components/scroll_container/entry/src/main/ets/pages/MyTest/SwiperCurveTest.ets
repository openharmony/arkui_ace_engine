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
import Curves from '@ohos.curves'

export default async function swiperCurveTest() {
  /*
* Swiper组件 Curve属性
* 找到画面id为swiperCurve1，swiperCurve2,swiperCurve3,swiperCurve4,swiperCurve5,swiperCurve6,swiperCurve7,
* swiperCurve8,swiperCurve9,swiperCurve10,swiperCurve11,swiperCurve12,swiperCurve13的Swiper组件
* 找到画面文本为SwiperAutoPlay1,SwiperAutoPlay2,SwiperAutoPlay3的Button组件
* 获取swiperCurve1的Curve属性与期待值Curve.Linear比对
* 获取swiperCurve2的Curve属性与期待值Curve.Ease比对
* 获取swiperCurve3的Curve属性与期待值Curve.EaseIn比对
* 获取swiperCurve4的Curve属性与期待值Curve.EaseOut比对
* 获取swiperCurve5的Curve属性与期待值Curve.EaseInOut比对
* 获取swiperCurve6的Curve属性与期待值Curve.FastOutSlowIn比对
* 获取swiperCurve7的Curve属性与期待值Curve.LinearOutSlowIn比对
* 获取swiperCurve8的Curve属性与期待值Curve.FastOutLinearIn比对
* 获取swiperCurve9的Curve属性与期待值Curve.ExtremeDeceleration比对
* 获取swiperCurve10的Curve属性与期待值Curve.Sharp比对
* 获取swiperCurve11的Curve属性与期待值Curve.Smooth比对
* 获取swiperCurve12的Curve属性与期待值value比对
* 获取swiperCurve13的Curve属性与期待值Curve.Linear比对
* 点击button1，变更swiperCurve10属性值为Curve.Rhythm
* 获取swiperCurve10的Curve属性与期待值Curve.Rhythm比对
* 点击button2，变更swiperCurve11属性值为Curve.Friction
* 获取swiperCurve11的Curve属性与期待值Curve.Friction比对
* 点击button3，变更swiperCurve13属性值为2
* 获取swiperCurve13的Curve属性与期待值2比对
*/
  defineTest('swiperCurveTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('swiperCurveTestDemo running')
    let driver: Tester = Tester.create()
    let swiper1: Component = await driver.findComponent(Matcher.create().id('swiperCurve1').enabled(true))
    let swiper2: Component = await driver.findComponent(Matcher.create().id('swiperCurve2').enabled(true))
    let swiper3: Component = await driver.findComponent(Matcher.create().id('swiperCurve3').enabled(true))
    let swiper4: Component = await driver.findComponent(Matcher.create().id('swiperCurve4').enabled(true))
    let swiper5: Component = await driver.findComponent(Matcher.create().id('swiperCurve5').enabled(true))
    let swiper6: Component = await driver.findComponent(Matcher.create().id('swiperCurve6').enabled(true))
    let swiper7: Component = await driver.findComponent(Matcher.create().id('swiperCurve7').enabled(true))
    let swiper8: Component = await driver.findComponent(Matcher.create().id('swiperCurve8').enabled(true))
    let swiper9: Component = await driver.findComponent(Matcher.create().id('swiperCurve9').enabled(true))
    let swiper10: Component = await driver.findComponent(Matcher.create().id('swiperCurve10').enabled(true))
    let swiper11: Component = await driver.findComponent(Matcher.create().id('swiperCurve11').enabled(true))
    let swiper12: Component = await driver.findComponent(Matcher.create().id('swiperCurve12').enabled(true))
    let swiper13: Component = await driver.findComponent(Matcher.create().id('swiperCurve13').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SwiperCurveCurve1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('SwiperCurveCurve2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('SwiperCurveCurve3').enabled(true))

    let curve1: string = await swiper1.getInspectorInfo()
    assertEqual(JSON.parse(curve1).$attrs.curve, 'Curves.Linear')
    let curve2: string = await swiper2.getInspectorInfo()
    assertEqual(JSON.parse(curve2).$attrs.curve, 'Curves.Ease')
    let curve3: string = await swiper3.getInspectorInfo()
    assertEqual(JSON.parse(curve3).$attrs.curve, 'Curves.EaseIn')
    let curve4: string = await swiper4.getInspectorInfo()
    assertEqual(JSON.parse(curve4).$attrs.curve, 'Curves.EaseOut')
    let curve5: string = await swiper5.getInspectorInfo()
    assertEqual(JSON.parse(curve5).$attrs.curve, 'Curves.EaseInOut')
    let curve6: string = await swiper6.getInspectorInfo()
    assertEqual(JSON.parse(curve6).$attrs.curve, 'Curves.FastOutSlowIn')
    let curve7: string = await swiper7.getInspectorInfo()
    assertEqual(JSON.parse(curve7).$attrs.curve, 'Curves.LinearOutSlowIn')
    let curve8: string = await swiper8.getInspectorInfo()
    assertEqual(JSON.parse(curve8).$attrs.curve, 'Curves.FastOutLinearIn')
    let curve9: string = await swiper9.getInspectorInfo()
    assertEqual(JSON.parse(curve9).$attrs.curve, 'Curves.ExtremeDeceleration')
    let curve10: string = await swiper10.getInspectorInfo()
    assertEqual(JSON.parse(curve10).$attrs.curve, 'Curves.Sharp')
    let curve11: string = await swiper11.getInspectorInfo()
    assertEqual(JSON.parse(curve11).$attrs.curve, 'Curves.Smooth')
    let curve12: string = await swiper12.getInspectorInfo()
    assertEqual(JSON.parse(curve12).$attrs.curve, Curves.initCurve(Curve.EaseIn).interpolate(0.5))
    let curve13: string = await swiper13.getInspectorInfo()
    assertEqual(JSON.parse(curve13).$attrs.curve, 'Curves.Linear')
    await button1.tap()
    let curve14: string = await swiper10.getInspectorInfo()
    assertEqual(JSON.parse(curve14).$attrs.curve, 'Curves.Rhythm')
    await button2.tap()
    let curve15: string = await swiper11.getInspectorInfo()
    assertEqual(JSON.parse(curve15).$attrs.curve, 'Curves.Friction')
    await button3.tap()
    let curve16: string = await swiper13.getInspectorInfo()
    assertEqual(JSON.parse(curve16).$attrs.curve, 2)
  }, 0)
}