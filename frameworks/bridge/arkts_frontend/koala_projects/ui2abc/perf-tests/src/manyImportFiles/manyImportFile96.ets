
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent192 } from "./manyImportFile192"
import { ManyImportComponent193 } from "./manyImportFile193"


@Component
export struct ManyImportComponent96 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent192()
            ManyImportComponent193()

        }
    }
}
