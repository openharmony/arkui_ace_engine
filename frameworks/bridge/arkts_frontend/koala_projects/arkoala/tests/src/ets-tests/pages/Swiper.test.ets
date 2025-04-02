/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct SwiperTest {
  displayCount1: SwiperAutoFill = { minSize: 33 }
  displayCount2: SwiperAutoFill = { minSize: "55vp" }
  displayArrow1: ArrowStyle = { showBackground: true, isSidebarMiddle: true, backgroundSize: 10,
    backgroundColor: Color.Transparent, arrowSize: 24, arrowColor: Color.Blue };
  displayArrow2: ArrowStyle = { showBackground: false, isSidebarMiddle: false, backgroundSize: "10fp",
    backgroundColor: 333, arrowSize: "24fp", arrowColor: Color.Red };
  displayArrow3: ArrowStyle = { isSidebarMiddle: false, backgroundSize: "10%",
    backgroundColor: Color.Green, arrowSize: "24vp", arrowColor: "#123456" };
  displayArrow4: ArrowStyle = { backgroundSize: "10px",
    backgroundColor: "#77ffffff", arrowSize: "24%", arrowColor: Color.Yellow };
  displayArrow5: ArrowStyle = { backgroundColor: Color.Black, arrowSize: "24px", arrowColor: Color.Red };
  displayArrow6: ArrowStyle = { arrowSize: "24lpx", arrowColor: Color.Pink };
  displayArrow7: ArrowStyle = { arrowColor: 255 };
  displayArrow8: ArrowStyle = { };

  dotIndicator1: DotIndicator = Indicator.dot().left(10).top("20fp").right("30px").bottom("2%").itemWidth(20).itemHeight("20fp")
    .selectedItemWidth(24).selectedItemHeight("24fp").mask(true).color(Color.Gray).selectedColor(Color.White);
  dotIndicator2: DotIndicator = Indicator.dot().left(10).top("20fp").right("30px").bottom("2%").itemWidth("10px").itemHeight("10lpx")
    .selectedItemWidth("12vp").selectedItemHeight("1%").mask(false).color("#ff77777777").selectedColor("#ffffffff");
  dotIndicator3: DotIndicator = Indicator.dot().left(10).top("20fp").right("30px").bottom("2%").itemWidth("10px").itemHeight("10lpx")
    .selectedItemWidth("12vp").selectedItemHeight("1%").color(255).selectedColor("#ffffff");
  dotIndicator4: DotIndicator = Indicator.dot().top("20fp").right("30px").itemWidth("10px").itemHeight("10lpx")
    .selectedItemWidth("12vp").selectedItemHeight("1%").color(255);
  dotIndicator5: DotIndicator = Indicator.dot().selectedItemWidth("12vp").selectedItemHeight("1%");
  dotIndicator6: DotIndicator = Indicator.dot();

  digitIndicator1: DigitIndicator = Indicator.digit().left(10).top("20fp").right("30px").bottom("2%").fontColor(Color.Blue)
    .selectedFontColor(Color.Yellow).digitFont({weight: FontWeight.Normal, size: 20}).selectedDigitFont({weight: 4, size: 24});
  digitIndicator2: DigitIndicator = Indicator.digit().top("20fp").right("30px")
    .digitFont({weight: "normal", size: "20px"}).selectedDigitFont({weight: "bold", size: "24px"});
  digitIndicator3: DigitIndicator = Indicator.digit().left(10).bottom("2%")
    .digitFont({weight: "bolder", size: "20fp"}).selectedDigitFont({weight: "bolder", size: "24fp"});
  digitIndicator4: DigitIndicator = Indicator.digit()
    .digitFont({weight: 0, size: "20lpx"}).selectedDigitFont({weight: 5, size: "24lpx"});
  digitIndicator5: DigitIndicator = Indicator.digit()
    .digitFont({weight: "notKnown", size: "1%"}).selectedDigitFont({ size: "2%"});
  digitIndicator6: DigitIndicator = Indicator.digit().digitFont({size: "1%"}).selectedDigitFont({ });
  digitIndicator7: DigitIndicator = Indicator.digit();

  build() {
    Column() {
      Swiper()
      .index(0)
      .autoPlay(false)
      .interval(10)
      .indicator(false)
      .displayArrow(false)
      .loop(false)
      .duration(0)
      .vertical(false)
      .itemSpace(28)
      .displayMode(SwiperDisplayMode.Stretch)
      .cachedCount(0)
      .displayCount(8)
      .effectMode(EdgeEffect.Spring)
      .disableSwipe(false)
      .curve("Unknown curve")
      .prevMargin(10)
      .nextMargin(10)
      .nestedScroll(0)
      .enabled(false)
      Swiper()
      .index(5)
      .autoPlay(true)
      .interval(10)
      .indicator(true)
      .displayArrow(true, false)
      .loop(true)
      .duration(100)
      .vertical(true)
      .itemSpace("34")
      .displayMode(SwiperDisplayMode.AutoLinear)
      .cachedCount(5)
      .displayCount("16")
      .effectMode(EdgeEffect.Fade)
      .disableSwipe(true)
      .curve(Curve.Linear)
      .prevMargin("10px")
      .nextMargin("10px")
      .nestedScroll(1)
      .enabled(true)
      Swiper()
      .displayArrow(true, true)
      .itemSpace("34px")
      .indicator(this.dotIndicator1)
      .displayCount(this.displayCount1)
      .effectMode(EdgeEffect.None)
      .curve(Curve.Ease)
      .prevMargin("10fp")
      .nextMargin("10fp")
      Swiper()
      .displayArrow(false, true)
      .itemSpace("44lpx")
      .indicator(this.dotIndicator2)
      .displayCount(this.displayCount2)
      .curve(Curve.EaseIn)
      .prevMargin("10vp")
      .nextMargin("10vp")
      Swiper()
      .displayArrow(this.displayArrow1)
      .itemSpace("54fp")
      .indicator(this.dotIndicator3)
      .curve(Curve.EaseOut)
      .prevMargin("10%")
      .nextMargin("10%")
      Swiper()
      .displayArrow(this.displayArrow2, false)
      .indicator(this.dotIndicator4)
      .curve(Curve.EaseInOut)
      .prevMargin("10lpx")
      .nextMargin("10lpx")
      Swiper()
      .displayArrow(this.displayArrow3, true)
      .indicator(this.dotIndicator5)
      .curve(Curve.FastOutSlowIn)
      Swiper()
      .displayArrow(this.displayArrow4)
      .indicator(this.dotIndicator6)
      .curve(Curve.LinearOutSlowIn)
      Swiper()
      .displayArrow(this.displayArrow5, false)
      .indicator(this.digitIndicator1)
      .curve(Curve.FastOutLinearIn)
      Swiper()
      .displayArrow(this.displayArrow6, true)
      .indicator(this.digitIndicator2)
      .curve(Curve.ExtremeDeceleration)
      Swiper()
      .displayArrow(this.displayArrow7)
      .indicator(this.digitIndicator3)
      .curve(Curve.Sharp)
      Swiper()
      .displayArrow(this.displayArrow8, true)
      .indicator(this.digitIndicator4)
      .curve(Curve.Rhythm)
      Swiper()
      .indicator(this.digitIndicator5)
      .curve(Curve.Smooth)
      Swiper()
      .indicator(this.digitIndicator6)
      .curve(Curve.Friction)
      Swiper()
      .indicator(this.digitIndicator7)
    }
  }
}
