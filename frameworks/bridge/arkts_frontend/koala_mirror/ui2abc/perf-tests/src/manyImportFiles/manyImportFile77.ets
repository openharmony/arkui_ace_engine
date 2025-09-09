
import { Component, Column, Text } from "@ohos.arkui"
import { State } from "@ohos.arkui"
import { ManyImportComponent154 } from "./manyImportFile154"
import { ManyImportComponent155 } from "./manyImportFile155"


@Component
export struct ManyImportComponent77 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent154()
            ManyImportComponent155()

        }
    }
}
