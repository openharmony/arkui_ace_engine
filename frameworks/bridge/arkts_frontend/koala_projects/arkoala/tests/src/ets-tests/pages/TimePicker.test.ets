@Entry
@Component
struct TimePickerTest {
    font1: Font = { }
    font2: Font = { family: "Arial", style: FontStyle.Normal }
    font3: Font = { family: "Serif", style: FontStyle.Italic }
    font4: Font = { style: FontStyle.Normal }
    font5: Font = { family: "fontFamily" }
    textStyle1: PickerTextStyle = { }
    textStyle2: PickerTextStyle = { color: Color.Green, font: this.font1 }
    textStyle3: PickerTextStyle = { color: 333, font: this.font2 }
    textStyle4: PickerTextStyle = { color: "#404040", font: this.font3 }
    textStyle5: PickerTextStyle = { color: Color.Blue, font: this.font4 }
    textStyle6: PickerTextStyle = { font: this.font5 }
    options1: TimePickerOptions = { }
    options2: TimePickerOptions = { selected: this.getTime(), format: TimePickerFormat.HOUR_MINUTE }
    options3: TimePickerOptions = { format: TimePickerFormat.HOUR_MINUTE_SECOND }
    options4: TimePickerOptions = { selected: this.getTime() }

    getTime(): Date {
        let selected: Date = new Date()
        selected.setHours(1, 5, 20)
        return selected
    }

    build() {
        TimePicker(this.options1)
        .disappearTextStyle(this.textStyle1)
        .textStyle(this.textStyle2)
        .selectedTextStyle(this.textStyle3)
        .loop(false)
        .useMilitaryTime(true)
        TimePicker(this.options2)
        .disappearTextStyle(this.textStyle4)
        .textStyle(this.textStyle5)
        .selectedTextStyle(this.textStyle6)
        .loop(true)
        .useMilitaryTime(false)
        TimePicker(this.options3)
        TimePicker(this.options4)
    }
}
