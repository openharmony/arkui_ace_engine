@Entry
@Component
struct TextTimerTest {
    shadow1: ShadowOptions = { radius: 24, type: ShadowType.COLOR, color: Color.Black, offsetX: 15, offsetY: 25 }
    shadow2: ShadowOptions = { radius: 48, type: ShadowType.BLUR, color: 333, offsetX: 25, offsetY: 15 }
    timerOptions1: TextTimerOptions = { isCountDown: true, count: 900 }
    timerOptions2: TextTimerOptions = { isCountDown: false }
    timerOptions3: TextTimerOptions = { count: 1000 }

    build() {
        TextTimer()
        .format("hh:mm:ss")
        .fontColor(Color.Blue)
        .fontSize(30)
        .fontFamily("Arial")
        .fontStyle(FontStyle.Normal)
        .fontWeight(FontWeight.Lighter)
        .textShadow(this.shadow1)
        TextTimer(this.timerOptions1)
        .format("yyyy/mm/dd")
        .fontColor(333)
        .fontSize("20vp")
        .fontStyle(FontStyle.Italic)
        .fontWeight("Bolder")
        .textShadow(this.shadow2)
        TextTimer(this.timerOptions2)
        .fontColor("#404040")
        .fontSize("40px")
        .fontWeight(400)
        TextTimer(this.timerOptions3)
        .fontSize("25lpx")
        .fontWeight(900)
        TextTimer()
        .fontSize("5%")
        .fontWeight(10)
    }
}
