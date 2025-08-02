import { MultiComponent20 } from '../../framework/PComponent'

@Entry
@Component
struct Plugins {
  scroller : Scroller = new Scroller()

  build() {
    Scroll(this.scroller) {
      Column() {
        MultiComponent20()
      }
    }
  }
}