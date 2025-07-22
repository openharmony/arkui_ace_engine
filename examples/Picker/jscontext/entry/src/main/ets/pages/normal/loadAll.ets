import * as comps from '../../framework/normalComponent'

@Entry
@Component
struct MainPage {
  scroller : Scroller = new Scroller()
  build() {
    Scroll(this.scroller) {
      Column() {
        comps.DatePickerComponent()
        comps.CalendarPickerComponent()
        comps.TimePickerComponent()
        comps.TextPickerComponent()
        comps.DatePickerDialogComponent()
        comps.CalendarPickerDialogComponent()
        comps.TimePickerDialogComponent()
        comps.TextPickerDialogComponent()
        comps.ImageComponent()
        comps.ImageAnimatorComponent()
        comps.CounterComponent()
        comps.PatternLockComponent()
        comps.TextClockComponent()
        comps.TextTimerComponent()
      }
    }
  }
}

