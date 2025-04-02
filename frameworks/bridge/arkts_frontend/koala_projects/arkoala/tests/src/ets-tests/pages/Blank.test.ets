@Entry
@Component
struct BlankTest {
    build() {
        Blank()
            .color(Color.Blue)
        Blank(10)
            .color(333)
        Blank("11px")
            .color("#123456")
        Blank("12lpx")
        Blank("13fp")
        Blank("14%")
    }
}
