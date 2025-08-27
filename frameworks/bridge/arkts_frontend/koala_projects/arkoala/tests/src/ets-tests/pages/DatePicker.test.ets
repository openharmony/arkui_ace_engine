@Entry
@Component
struct DatePickerTest {
    font1: Font = { }
    font2: Font = { family: "Arial", style: FontStyle.Normal, size: 18, weight: FontWeight.Normal }
    font3: Font = { family: "Serif", style: FontStyle.Italic, size: "19fp", weight: 4 }
    font4: Font = { family: "Arial", size: "20px", weight: "Bold" }
    font5: Font = { family: "Serif", size: "21lpx", weight: 400 }
    font6: Font = { size: "22%", weight: 0 }
    font7: Font = { weight: "Bolder" }
    font8: Font = { style: FontStyle.Normal }
    font9: Font = { family: "fontFamily" }
    textStyle1: PickerTextStyle = { }
    textStyle2: PickerTextStyle = { color: Color.Green, font: this.font1 }
    textStyle3: PickerTextStyle = { color: 333, font: this.font2 }
    textStyle4: PickerTextStyle = { color: "#404040", font: this.font3 }
    textStyle5: PickerTextStyle = { color: Color.Blue, font: this.font4 }
    textStyle6: PickerTextStyle = { font: this.font5 }
    textStyle7: PickerTextStyle = { font: this.font6 }
    textStyle8: PickerTextStyle = { font: this.font7 }
    textStyle9: PickerTextStyle = { font: this.font8 }
    textStyle10: PickerTextStyle = { font: this.font9 }

    getOptions(): DatePickerOptions {
        let startDate: Date = new Date()
        let endDate: Date = new Date()
        let selectedDate: Date = new Date()
        startDate.setFullYear(1980, 1, 1)
        endDate.setFullYear(2026, 10, 25)
        selectedDate.setFullYear(2024, 4, 8)
        return { start: startDate, end: endDate, selected: selectedDate }
    }

    build() {
        DatePicker(this.getOptions())
        .disappearTextStyle(this.textStyle1)
        .textStyle(this.textStyle2)
        .selectedTextStyle(this.textStyle3)
        .lunar(false)
        DatePicker()
        .disappearTextStyle(this.textStyle4)
        .textStyle(this.textStyle5)
        .selectedTextStyle(this.textStyle6)
        .lunar(true)
        DatePicker()
        .disappearTextStyle(this.textStyle7)
        .textStyle(this.textStyle8)
        .selectedTextStyle(this.textStyle9)
        DatePicker()
        .selectedTextStyle(this.textStyle10)
    }
}
