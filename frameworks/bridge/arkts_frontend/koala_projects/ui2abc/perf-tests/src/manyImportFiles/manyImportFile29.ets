
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent58 } from "./manyImportFile58"
import { ManyImportComponent59 } from "./manyImportFile59"


@Component
export struct ManyImportComponent29 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent58()
            ManyImportComponent59()

        }
    }
}
