@Entry
@Component
struct RatingTest {

  build() {
    Rating()
    Rating({ rating: 3 })
      .stars(6)
      .stepSize(0.5)
      .starStyle({ backgroundUri: "background", foregroundUri: "foreground", secondaryUri: "secondary" })
    Rating({ rating: 4, indicator: true })
      .stars(8)
      .stepSize(1)
      .starStyle({ backgroundUri: "background", foregroundUri: "foreground" })
    Rating({ rating: 5, indicator: false })
      .stars(10)
      .stepSize(2)
  }
}
