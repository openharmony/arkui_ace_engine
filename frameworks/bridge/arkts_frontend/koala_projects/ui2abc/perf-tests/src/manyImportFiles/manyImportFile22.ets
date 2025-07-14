
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent44 } from "./manyImportFile44"
import { ManyImportComponent45 } from "./manyImportFile45"


@Component
export struct ManyImportComponent22 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent44()
            ManyImportComponent45()

        }
    }
}
