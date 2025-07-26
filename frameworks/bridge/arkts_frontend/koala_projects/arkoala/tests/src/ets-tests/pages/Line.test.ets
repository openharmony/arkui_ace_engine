@Entry
@Component
struct LineTest {
    build() {
        Line()
          .startPoint([10, 11])
          .endPoint([110, 111])
        Line()
          .startPoint(["12px", "13px"])
          .endPoint(["112px", "113px"])
        Line()
          .startPoint(["14lpx", "15lpx"])
          .endPoint(["114lpx", "115lpx"])
        Line()
          .startPoint(["16fp", "17fp"])
          .endPoint(["116fp", "117fp"])
        Line()
          .startPoint(["5%", "6%"])
          .endPoint(["95%", "96%"])
    }
}
