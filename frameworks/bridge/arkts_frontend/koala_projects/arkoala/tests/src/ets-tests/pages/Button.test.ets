@Entry
@Component
struct ButtonTest {
  buttonOptions1: ButtonOptions = {type: ButtonType.Capsule, stateEffect: true, buttonStyle: ButtonStyleMode.NORMAL, controlSize: ControlSize.SMALL}
  buttonOptions2: ButtonOptions = {type: ButtonType.Circle, stateEffect: false, buttonStyle: ButtonStyleMode.EMPHASIZED, controlSize: ControlSize.NORMAL}
  buttonOptions3: ButtonOptions = {type: ButtonType.Normal, buttonStyle: ButtonStyleMode.TEXTUAL}
  labelStyle1: LabelStyle = { overflow: TextOverflow.None, maxLines: 5, minFontSize: 12, maxFontSize: 36,
    heightAdaptivePolicy: TextHeightAdaptivePolicy.MAX_LINES_FIRST,
    font: { weight: FontWeight.Lighter, size: 30, style: FontStyle.Italic, family: "Times" }}
  labelStyle2: LabelStyle = { overflow: TextOverflow.Clip, maxLines: 10, minFontSize: 0, maxFontSize: 48,
    heightAdaptivePolicy: TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST,
    font: { weight: "Bolder", size: "20vp", style: FontStyle.Normal, family: "Arial" }}
  labelStyle3: LabelStyle = { overflow: TextOverflow.Ellipsis, maxLines: 0,
    heightAdaptivePolicy: TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST,
    font: { weight: 400, size: "40px" }}
  labelStyle4: LabelStyle = { overflow: TextOverflow.MARQUEE,
    font: { weight: 900, size: "25lpx" }}
  labelStyle5: LabelStyle = { font: { weight: 10, size: "5%" }}
  labelStyle6: LabelStyle = { font: { }}
  labelStyle7: LabelStyle = { }

  build() {
    Button()
      .fontColor(Color.Blue)
      .fontSize(30)
      .fontWeight(FontWeight.Lighter)
      .fontStyle(FontStyle.Normal)
      .fontFamily("Arial")
      .labelStyle(this.labelStyle1)
    Button("Button1", this.buttonOptions1)
      .fontColor(333)
      .fontSize("20vp")
      .fontWeight("Bolder")
      .fontStyle(FontStyle.Italic)
      .labelStyle(this.labelStyle2)
    Button("Button2", this.buttonOptions2)
      .fontColor("#404040")
      .fontSize("40px")
      .fontWeight(400)
      .labelStyle(this.labelStyle3)
    Button("Button3", this.buttonOptions3)
      .fontSize("25lpx")
      .fontWeight(900)
      .labelStyle(this.labelStyle4)
    Button("Button4")
      .type(ButtonType.Capsule)
      .stateEffect(false)
      .buttonStyle(ButtonStyleMode.NORMAL)
      .controlSize(ControlSize.NORMAL)
      .fontSize("5%")
      .fontWeight(10)
      .labelStyle(this.labelStyle5)
    Button("Button5")
      .type(ButtonType.Circle)
      .stateEffect(true)
      .buttonStyle(ButtonStyleMode.EMPHASIZED)
      .controlSize(ControlSize.SMALL)
      .labelStyle(this.labelStyle6)
    Button("Button6")
      .type(ButtonType.Normal)
      .buttonStyle(ButtonStyleMode.TEXTUAL)
      .labelStyle(this.labelStyle7)
    Button("Button7")
  }
}
