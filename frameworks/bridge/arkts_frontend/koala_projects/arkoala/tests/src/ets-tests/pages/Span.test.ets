@Entry
@Component
struct SpanTest {
    build() {
        Span("Span Check 1\n")
        .font({size:30, weight:FontWeight.Lighter, family:"testString", style:FontStyle.Normal})
        .decoration({type:TextDecorationType.Overline, color:Color.Blue})
        Span("Span Check 2\n")
        .fontColor(Color.White)
        .fontSize(17)
        .fontStyle(FontStyle.Normal)
        .fontWeight(20)
        .fontFamily("testString")
        .decoration({type:TextDecorationType.Underline, color:Color.Red})
        .letterSpacing(17)
        .textCase(TextCase.Normal)
        .lineHeight(37)
        Span("Span Check 3\n")
        .fontColor(0xFFFFFFFF)
        .fontSize('17vp')
        .fontWeight(FontWeight.Bolder)
        .fontStyle(FontStyle.Italic)
    }
}
