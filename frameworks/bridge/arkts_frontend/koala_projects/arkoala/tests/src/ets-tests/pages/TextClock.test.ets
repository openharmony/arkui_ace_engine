@Entry
@Component
struct TextClockTest {
    shadow1: ShadowOptions = { radius: 24, type: ShadowType.COLOR, color: Color.Black, offsetX: 15, offsetY: 25 }
    shadow2: ShadowOptions = { radius: 48, type: ShadowType.BLUR, color: 333, offsetX: 25, offsetY: 15 }

    build() {
        TextClock( {timeZoneOffset: 2} )
        .format("hh:mm:ss")
        .fontFeature("normal")
        .fontColor(Color.Blue)
        .fontSize(30)
        .fontFamily("Arial")
        .fontStyle(FontStyle.Normal)
        .fontWeight(FontWeight.Lighter)
        .textShadow(this.shadow1)
        TextClock( {timeZoneOffset: 11} )
        .format("yyyy/mm/dd")
        .fontColor(333)
        .fontSize("20vp")
        .fontStyle(FontStyle.Italic)
        .fontWeight("Bolder")
        .textShadow(this.shadow2)
        TextClock( {timeZoneOffset: -5} )
        .fontColor("#404040")
        .fontSize("40px")
        .fontWeight(400)
        TextClock( {timeZoneOffset: -10} )
        .fontSize("25lpx")
        .fontWeight(900)
        TextClock( {timeZoneOffset: 0} )
        .fontSize("5%")
        .fontWeight(10)
    }
}
